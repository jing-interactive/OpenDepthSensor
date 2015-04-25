#include "cinder/Cinder.h"
#include "cinder/Channel.h"
#include "cinder/Function.h"

namespace Kinect
{
typedef std::shared_ptr<struct Device> DeviceRef;

struct Device
{
#ifdef KINECT_V2
    static DeviceRef createV2();
#else
    static DeviceRef createV1();
#endif

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    ci::Channel16u depthChannel;

    ci::signals::signal<void()> signalDepthDirty;
};
}
