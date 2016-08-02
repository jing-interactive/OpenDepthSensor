#include "DepthSensor.h"

using namespace ci;
using namespace std;
using namespace Kinect;

uint32_t getKinect1Count();
uint32_t getKinect2Count();
uint32_t getRealSenseCount();
uint32_t getSimulatorCount();

uint32_t Device::getDeviceCount(DeviceType type)
{
    if (type == Kinect1)
        return getKinect1Count();
    if (type == Kinect2)
        return getKinect2Count();
    if (type == RealSense)
        return getRealSenseCount();
    return getSimulatorCount();
}

DeviceRef createKinect1(Device::Option option);
DeviceRef createKinect2(Device::Option option);
DeviceRef createRealSense(Device::Option option);
DeviceRef createSimulator(Device::Option option);

DeviceRef Device::create(DeviceType type, Option option)
{
    if (type == Kinect1)
        return createKinect1(option);
    if (type == Kinect2)
        return createKinect2(option);
    if (type == RealSense)
        return createRealSense(option);
    return createSimulator(option);
}
