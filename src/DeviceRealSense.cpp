#include "DepthSensor.h"

#ifdef RealSense_Enabled

#include "librealsense/include/librealsense/rs.hpp"

#include "cinder/app/app.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceRealSense : public Device
    {
        rs::context ctx;
        rs::device* dev = nullptr;
        float depthScale;

        rs::intrinsics depth_intrin;
        rs::extrinsics depth_to_color;
        rs::intrinsics color_intrin;

        ivec2 kDepthSize = { 640, 480 };
        ivec2 kColorSize = { 640, 480 };

        static uint32_t getDeviceCount()
        {
            // TODO:
            return 1;
        }

        virtual float getDepthToMmScale()
        {
            return depthScale;
        }

        ~DeviceRealSense()
        {
        }

        // TODO:
        ivec2 getDepthSize() const
        {
            return kDepthSize;
        }

        ivec2 getColorSize() const
        {
            return kColorSize;
        }

        bool isValid() const
        {
            return dev != nullptr;;
        }

        DeviceRealSense(Option option)
        {
            rs::log_to_console(rs::log_severity::warn);

            this->option = option;

            if (ctx.get_device_count() == 0)
            {
                CI_LOG_E("Failed to connect to RealSense devices.");
                return;
            }

            dev = ctx.get_device(option.deviceId);
            printf("\nUsing device %s, an %s\n", option.deviceId, dev->get_name());
            printf("    Serial number: %s\n", dev->get_serial());
            printf("    Firmware version: %s\n", dev->get_firmware_version());

            if (option.enableDepth)
            {
                dev->enable_stream(rs::stream::depth, kDepthSize.x, kDepthSize.y, rs::format::z16, 60);
                depthScale = dev->get_depth_scale() * 1000;
            }

            if (option.enablePointCloud && option.enableColor)
            {
                depthToColorTable = Surface32f(kDepthSize.x, kDepthSize.y, false, SurfaceChannelOrder::RGB);
            }

            if (option.enableColor)
            {
                dev->enable_stream(rs::stream::color, kColorSize.x, kColorSize.y, rs::format::rgb8, 60);
            }

            if (option.enableInfrared)
            {
                dev->enable_stream(rs::stream::infrared, kDepthSize.x, kDepthSize.y, rs::format::y16, 60);
            }

            dev->start();

            if (option.enableDepth)
            {
                depth_intrin = dev->get_stream_intrinsics(rs::stream::depth);
            }

            if (option.enableDepth && option.enableColor)
            {
                depth_to_color = dev->get_extrinsics(rs::stream::depth, rs::stream::color);
            }

            if (option.enableColor)
            {
                color_intrin = dev->get_stream_intrinsics(rs::stream::color);
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceRealSense::update, this));
        }

        void update()
        {
            dev->wait_for_frames();

            if (option.enableDepth)
            {
                auto depth_image = (uint16_t*)dev->get_frame_data(rs::stream::depth);
                for (int i = 0; i < kDepthSize.x*kDepthSize.y; i++)
                {
                    depth_image[i] = depth_image[i] * 0.1f;
                }
                depthChannel = Channel16u(kDepthSize.x, kDepthSize.y, sizeof(uint16_t) * kDepthSize.x, 1, depth_image);
                signalDepthDirty.emit();

                if (option.enablePointCloud)
                {
                    auto depthToMeter = dev->get_depth_scale();

                    vec3* dst = (vec3*)depthToColorTable.getData();
                    for (int dy = 0; dy < depth_intrin.height; ++dy)
                    {
                        for (int dx = 0; dx < depth_intrin.width; ++dx)
                        {
                            // Retrieve the 16-bit depth value and map it into a depth in meters
                            uint16_t depth_value = depth_image[dy * depth_intrin.width + dx];
                            if (depth_value == 0)
                            {
                                dst->x = 0;
                                dst->y = 0;
                            }
                            else
                            {
                                float depth_in_meters = depth_value * depthToMeter;

                                // Map from pixel coordinates in the depth image to pixel coordinates in the color image
                                rs::float2 depth_pixel = { (float)dx, (float)dy };
                                rs::float3 depth_point = depth_intrin.deproject(depth_pixel, depth_in_meters);
                                rs::float3 color_point = depth_to_color.transform(depth_point);
                                rs::float2 color_texcoord = color_intrin.project_to_texcoord(color_point);

                                dst->x = color_texcoord.x;
                                dst->y = color_texcoord.y;
                            }

                            dst++;
                        }
                    }
                    signalDepthToColorTableDirty.emit();
                }

                // signalDepthToCameraTableDirty
                if (depthToCameraTable.getWidth() == 0)
                {
                    depthToCameraTable = Surface32f(kDepthSize.x, kDepthSize.y, false, SurfaceChannelOrder::RGB);

                    for (int y = 0; y < kDepthSize.y; y++)
                        for (int x = 0; x < kDepthSize.x; x++)
                        {
                            // Map from pixel coordinates in the depth image to pixel coordinates in the color image
                            rs::float2 depth_pixel = { (float)x, (float)y };
                            rs::float3 depth_point = depth_intrin.deproject(depth_pixel, 1);
                            vec3* dst = (vec3*)depthToCameraTable.getData({ x, y });
                            dst->x = depth_point.x;
                            dst->y = depth_point.y;
                        }
                    signalDepthToCameraTableDirty.emit();
                }
            }

            if (option.enableInfrared)
            {
                auto data = (uint16_t*)dev->get_frame_data(rs::stream::infrared);
                infraredChannel = Channel16u(kDepthSize.x, kDepthSize.y, sizeof(uint16_t) * kDepthSize.x, 1, data);
                signalInfraredDirty.emit();
            }

            if (option.enableColor)
            {
                uint8_t* data = (uint8_t*)dev->get_frame_data(rs::stream::color);
                colorSurface = Surface8u(data, kDepthSize.x, kDepthSize.y, sizeof(uint8_t) * 3 * kColorSize.x, SurfaceChannelOrder::RGB);
                signalColorDirty.emit();
            }
        }
    };

    uint32_t getRealSenseCount()
    {
        return DeviceRealSense::getDeviceCount();
    }

    DeviceRef createRealSense(Option option)
    {
        return DeviceRef(new DeviceRealSense(option));
    }
}

#endif
