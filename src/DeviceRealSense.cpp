#include "DepthSensor.h"
#include "librealsense/rs.hpp"

#include "cinder/app/app.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace Kinect;

struct DeviceRealSense : public Device
{
    rs::context ctx;
    rs::device* dev = nullptr;
    float depthScale;

    const int32_t kWidth = 640;
    const int32_t kHeight = 480;

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
        return{ kWidth, kHeight };
    }

    bool isValid() const
    {
        return dev != nullptr;;
    }

    DeviceRealSense(Option option)
    {
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
            dev->enable_stream(rs::stream::depth, kWidth, kHeight, rs::format::z16, 60);
            depthScale = dev->get_depth_scale() * 1000;
        }

        if (option.enableColor)
        {
            dev->enable_stream(rs::stream::color, kWidth, kHeight, rs::format::rgb8, 60);
        }

        if (option.enableInfrared)
        {
            dev->enable_stream(rs::stream::infrared, kWidth, kHeight, rs::format::y8, 60);
        }

        dev->start();

        App::get()->getSignalUpdate().connect(std::bind(&DeviceRealSense::update, this));
    }

    void update()
    {
        if (option.enableDepth)
        {
            dev->wait_for_frames();

            if (option.enableDepth)
            {
                uint16_t* data = (uint16_t*)dev->get_frame_data(rs::stream::depth);
                depthChannel = Channel16u(kWidth, kHeight, sizeof(uint16_t) * kWidth, 1, data);
                signalDepthDirty.emit();
            }

            if (option.enableInfrared)
            {
                uint8_t* data = (uint8_t*)dev->get_frame_data(rs::stream::infrared);
                infraredChannel.is16bit = false;
                infraredChannel.u8 = Channel8u(kWidth, kHeight, sizeof(uint16_t) * kWidth, 1, data);
            }

            if (option.enableColor)
            {
                uint8_t* data = (uint8_t*)dev->get_frame_data(rs::stream::color);
                colorSurface = Surface8u(data, kWidth, kHeight, sizeof(uint8_t) * 3 * kWidth, SurfaceChannelOrder::RGB);
            }
        }
    }
};

uint32_t getRealSenseCount()
{
    return DeviceRealSense::getDeviceCount();
}

DeviceRef createRealSense(Device::Option option)
{
    return DeviceRef(new DeviceRealSense(option));
}
