#include "DepthSensor.h"

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
    }

    ~DeviceRealSense()
    {
    }

    ivec2 getDepthSize() const
    {
        return { };
    }

    bool isValid() const
    {
        return true;
    }

    DeviceRealSense(Option option)
    {
        this->option = option;

        App::get()->getSignalUpdate().connect(std::bind(&DeviceRealSense::update, this));
    }

    //const vec3 toCi(const Vector4& pos)
    //{
    //    return vec3(pos.x, pos.y, pos.z);
    //}

    void update()
    {
        //if (option.enableDepth && KinectIsDepthFrameReady(sensor))
        //{
        //    if (SUCCEEDED(KinectGetDepthFrame(sensor, depthDesc.cbBufferSize, depthBuffer.get(), nullptr)))
        //    {
        //        signalDepthDirty.emit();
        //    }
        //}
    }

    unique_ptr<uint8_t[]> depthBuffer;
};

uint32_t getRealSenseCount()
{
    return DeviceRealSense::getDeviceCount();
}

DeviceRef createRealSense(Device::Option option)
{
    return DeviceRef(new DeviceRealSense(option));
}
