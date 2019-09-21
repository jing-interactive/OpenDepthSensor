#include "DepthSensor.h"

#ifdef KinectAzure_Enabled

#include "cinder/ImageIo.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"

#include "k4a/k4a.h"

#pragma comment(lib, "k4a")

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceKinectAzure : public Device
    {
        virtual bool isValid() const { return true; }

        ivec2 getDepthSize() const { return depthSize; }

        ivec2 getColorSize() const { return colorSize; }

        DeviceKinectAzure(Option option)
        {
            this->option = option;
            k4a_result_t openResult = k4a_device_open(option.deviceId, &device_handle);
            if (openResult != K4A_RESULT_SUCCEEDED)
                return;

            k4a_device_configuration_t conf = {};
            //if (option.enableColor)
            {
                conf.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
                conf.color_resolution = K4A_COLOR_RESOLUTION_1080P;
            }
            if (option.enableInfrared)
            {
                conf.depth_mode = K4A_DEPTH_MODE_PASSIVE_IR;
            }

            if (option.enableDepth)
            {
                conf.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
            }
            conf.camera_fps = K4A_FRAMES_PER_SECOND_30;
            conf.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;

            k4a_result_t startResult = k4a_device_start_cameras(device_handle, &conf);
            if (startResult != K4A_RESULT_SUCCEEDED)
                return;

            App::get()->getSignalUpdate().connect(std::bind(&DeviceKinectAzure::update, this));
        }

        ~DeviceKinectAzure()
        {
            if (device_handle)
            {
                k4a_device_stop_cameras(device_handle);
                k4a_device_close(device_handle);
            }
        }

        void update()
        {
            const int32_t TIMEOUT_IN_MS = 1000;

            k4a_capture_t capture_handle;
            k4a_wait_result_t waiResult = k4a_device_get_capture(device_handle, &capture_handle, TIMEOUT_IN_MS);

            if (waiResult != K4A_WAIT_RESULT_SUCCEEDED) return;

            if (option.enableColor)
            {
                auto image = k4a_capture_get_color_image(capture_handle);
                if (colorSize.x == 0 || colorSize .y == 0)
                {
                    colorSize.x = k4a_image_get_width_pixels(image);
                    colorSize.y = k4a_image_get_height_pixels(image);
                    colorSize.z = k4a_image_get_stride_bytes(image);
                }
                uint8_t* ptr = k4a_image_get_buffer(image);
                colorSurface = Surface8u(ptr, colorSize.x, colorSize.y, colorSize.z, SurfaceChannelOrder::BGRX);
                signalColorDirty.emit();
            }

            if (option.enableDepth)
            {
                auto image = k4a_capture_get_depth_image(capture_handle);
                if (depthSize.x == 0 || depthSize.y == 0)
                {
                    depthSize.x = k4a_image_get_width_pixels(image);
                    depthSize.y = k4a_image_get_height_pixels(image);
                    depthSize.z = k4a_image_get_stride_bytes(image);
                }
                uint16_t* ptr = (uint16_t*)k4a_image_get_buffer(image);
                depthChannel = Channel16u(depthSize.x, depthSize.y, depthSize.z, 1, ptr);

                signalDepthDirty.emit();
            }

            if (option.enableInfrared)
            {
                auto image = k4a_capture_get_ir_image(capture_handle);
                if (depthSize.x == 0 || depthSize.y == 0)
                {
                    depthSize.x = k4a_image_get_width_pixels(image);
                    depthSize.y = k4a_image_get_height_pixels(image);
                    depthSize.z = k4a_image_get_stride_bytes(image);
                }
                uint16_t* ptr = (uint16_t*)k4a_image_get_buffer(image);
                infraredChannel = Channel16u(depthSize.x, depthSize.y, depthSize.z, 1, ptr);

                signalInfraredDirty.emit();
            }
            k4a_capture_release(capture_handle);
        }

        k4a_device_t device_handle = 0;
        ivec3 colorSize, depthSize;
    };

    uint32_t getKinectAzureCount() { return k4a_device_get_installed_count(); }

    DeviceRef createKinectAzure(Option option) { return DeviceRef(new DeviceKinectAzure(option)); }
} // namespace ds

#endif
