#include "DepthSensor.h"

#ifdef KinectAzure_Enabled

#include "cinder/ImageIo.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"

#include "k4a/k4a.h"
#include "k4a/k4abt.h"

#pragma comment(lib, "k4a")
#pragma comment(lib, "k4abt")

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
            k4a_result_t result = k4a_device_open(option.deviceId, &device_handle);
            if (result != K4A_RESULT_SUCCEEDED)
                return;

            k4a_device_configuration_t conf = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
            if (option.enableColor)
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
                conf.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
            }
            conf.camera_fps = K4A_FRAMES_PER_SECOND_30;
            conf.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;

            k4a_result_t startResult = k4a_device_start_cameras(device_handle, &conf);
            if (startResult != K4A_RESULT_SUCCEEDED)
                return;

            if (option.enableBody || option.enableBodyIndex)
            {
                result = k4a_device_get_calibration(device_handle,
                    conf.depth_mode,
                    conf.color_resolution,
                    &calibration);
                k4abt_tracker_configuration_t cfg = K4ABT_TRACKER_CONFIG_DEFAULT;
                result = k4abt_tracker_create(&calibration,
                    cfg,
                    &tracker);
            }
            App::get()->getSignalUpdate().connect(std::bind(&DeviceKinectAzure::update, this));
        }

        ~DeviceKinectAzure()
        {
            if (device_handle)
            {
                k4a_device_stop_cameras(device_handle);
                k4a_device_close(device_handle);
            }
            if (tracker)
            {
                k4abt_tracker_destroy(tracker);
            }
        }

        void update()
        {
            if (device_handle == 0)
                return;

            const int32_t TIMEOUT_IN_MS = 1000;

            k4a_capture_t capture_handle;
            k4a_wait_result_t waiResult = k4a_device_get_capture(device_handle, &capture_handle, TIMEOUT_IN_MS);

            if (waiResult != K4A_WAIT_RESULT_SUCCEEDED) return;

            if (option.enableColor)
            {
                auto image = k4a_capture_get_color_image(capture_handle);
                if (image != 0)
                {
                    if (colorSize.x == 0 || colorSize.y == 0)
                    {
                        colorSize.x = k4a_image_get_width_pixels(image);
                        colorSize.y = k4a_image_get_height_pixels(image);
                        colorSize.z = k4a_image_get_stride_bytes(image);
                    }
                    uint8_t* ptr = k4a_image_get_buffer(image);
                    colorSurface = Surface8u(ptr, colorSize.x, colorSize.y, colorSize.z, SurfaceChannelOrder::BGRX);
                    signalColorDirty.emit();
                    k4a_image_release(image);
                }
            }

            if (option.enableDepth)
            {
                auto image = k4a_capture_get_depth_image(capture_handle);
                if (image != 0)
                {
                    if (depthSize.x == 0 || depthSize.y == 0)
                    {
                        depthSize.x = k4a_image_get_width_pixels(image);
                        depthSize.y = k4a_image_get_height_pixels(image);
                        depthSize.z = k4a_image_get_stride_bytes(image);
                    }
                    uint16_t* ptr = (uint16_t*)k4a_image_get_buffer(image);
                    if (ptr != nullptr)
                    {
                        depthChannel = Channel16u(depthSize.x, depthSize.y, depthSize.z, 1, ptr);
                        signalDepthDirty.emit();
                    }
                    k4a_image_release(image);
                }
            }

            if (option.enableBody || option.enableBodyIndex)
            {
                k4a_wait_result_t result = k4abt_tracker_enqueue_capture(tracker,
                    capture_handle,
                    TIMEOUT_IN_MS);

                if (result == K4A_WAIT_RESULT_SUCCEEDED)
                {
                    k4abt_frame_t body_frame_handle;
                    result = k4abt_tracker_pop_result(tracker,
                        &body_frame_handle,
                        TIMEOUT_IN_MS);
                    if (body_frame_handle != nullptr)
                    {
                        if (option.enableBody)
                        {
                            uint32_t num_bodies = k4abt_frame_get_num_bodies(body_frame_handle);
                            CI_LOG_I(num_bodies << " bodies are detected");
                            vector<k4abt_skeleton_t> skeletons;
                            for (int i = 0; i < num_bodies; i++)
                            {
                                k4abt_skeleton_t skeleton;
                                auto result = k4abt_frame_get_body_skeleton(body_frame_handle, i, &skeleton);
                                skeletons.emplace_back(skeleton);
                            }
                        }
                        if (option.enableBodyIndex)
                        {
                            k4a_image_t body_index = k4abt_frame_get_body_index_map(body_frame_handle);
                        }
                        k4abt_frame_release(body_frame_handle);
                    }
                }
            }

            if (option.enableInfrared)
            {
                auto image = k4a_capture_get_ir_image(capture_handle);
                if (image != 0)
                {
                    if (depthSize.x == 0 || depthSize.y == 0)
                    {
                        depthSize.x = k4a_image_get_width_pixels(image);
                        depthSize.y = k4a_image_get_height_pixels(image);
                        depthSize.z = k4a_image_get_stride_bytes(image);
                    }
                    uint16_t* ptr = (uint16_t*)k4a_image_get_buffer(image);
                    infraredChannel = Channel16u(depthSize.x, depthSize.y, depthSize.z, 1, ptr);

                    signalInfraredDirty.emit();
                    k4a_image_release(image);
                }
            }
            k4a_capture_release(capture_handle);
        }

        k4a_device_t device_handle = 0;
        ivec3 colorSize, depthSize;
        k4a_calibration_t calibration;
        k4abt_tracker_t tracker;
    };

    uint32_t getKinectAzureCount() { return k4a_device_get_installed_count(); }

    DeviceRef createKinectAzure(Option option) { return DeviceRef(new DeviceKinectAzure(option)); }
} // namespace ds

#endif
