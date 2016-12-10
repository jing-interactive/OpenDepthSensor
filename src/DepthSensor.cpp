#include "DepthSensor.h"

using namespace ci;
using namespace std;

namespace ds
{
    uint32_t getKinect1Count();
    uint32_t getKinect2Count();
    uint32_t getRealSenseCount();
    uint32_t getSimulatorCount();
    uint32_t getOpenNICount();
    uint32_t getRgbCameraCount();

    uint32_t Device::getDeviceCount(DeviceType type)
    {
        if (type == Kinect1)
            return getKinect1Count();
        if (type == Kinect2)
            return getKinect2Count();
        if (type == RealSense)
            return getRealSenseCount();
        if (type == OpenNI)
            return getOpenNICount();
        if (type == RgbCamera)
            return getRgbCameraCount();
        return getSimulatorCount();
    }

    DeviceRef createKinect1(Option option);
    DeviceRef createKinect2(Option option);
    DeviceRef createRealSense(Option option);
    DeviceRef createSimulator(Option option);
    DeviceRef createOpenNI(Option option);
    DeviceRef createRgbCamera(Option option);

    DeviceRef Device::create(DeviceType type, Option option)
    {
        if (option.enablePointCloud)
            option.enableDepth = true;

        if (type == Kinect1)
            return createKinect1(option);
        if (type == Kinect2)
            return createKinect2(option);
        if (type == RealSense)
            return createRealSense(option);
        if (type == OpenNI)
            return createOpenNI(option);
        if (type == RgbCamera)
            return createRgbCamera(option);
        return createSimulator(option);
    }
}
