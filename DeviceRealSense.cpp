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
    static uint32_t getDeviceCount()
    {
        // TODO:
        return 1;
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
        return true;
    }

    DeviceRealSense(Option option)
    {
        this->option = option;

        if (ctx.get_device_count() == 0)
        {
            CI_LOG_E("Failed to connect to RealSense devices.");
        }

        dev = ctx.get_device(0);
        printf("\nUsing device 0, an %s\n", dev->get_name());
        printf("    Serial number: %s\n", dev->get_serial());
        printf("    Firmware version: %s\n", dev->get_firmware_version());

        if (option.enableDepth)
        {
            // Configure depth to run at VGA resolution at 30 frames per second
            dev->enable_stream(rs::stream::depth, kWidth, kHeight, rs::format::z16, 30);
            dev->start();

            // Determine depth value corresponding to one meter
            one_meter = static_cast<uint16_t>(1.0f / dev->get_depth_scale());
        }

        App::get()->getSignalUpdate().connect(std::bind(&DeviceRealSense::update, this));
    }

    //const vec3 toCi(const Vector4& pos)
    //{
    //    return vec3(pos.x, pos.y, pos.z);
    //}

    void update()
    {
        if (option.enableDepth)
        {
            dev->wait_for_frames();

            // Retrieve depth data, which was previously configured as a 640 x 480 image of 16-bit depth values
            uint16_t* data = (uint16_t*)dev->get_frame_data(rs::stream::depth);
            depthChannel = Channel16u(kWidth, kHeight, sizeof(uint16_t) * kWidth, 1, data);

            signalDepthDirty.emit();
        }
    }

    rs::context ctx;
    rs::device* dev = nullptr;
    uint16_t one_meter = 0;

    const int32_t kWidth = 640;
    const int32_t kHeight = 480;
};

uint32_t getRealSenseCount()
{
    return DeviceRealSense::getDeviceCount();
}

DeviceRef createRealSense(Device::Option option)
{
    return DeviceRef(new DeviceRealSense(option));
}
