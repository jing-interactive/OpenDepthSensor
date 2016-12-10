#include "DepthSensor.h"
#include "OpenNI.h"

#include "cinder/app/app.h"
#include "cinder/Log.h"

#pragma comment (lib, "OpenNI2.lib")

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceOpenNI : public Device
    {
        static const int OpenNiSensorTypeCount = openni::SENSOR_DEPTH;
        openni::Device device;
        openni::VideoStream infraredStream, depthStream, colorStream;

        float depthScale;
        ivec2 depthSize;

        static uint32_t getDeviceCount()
        {
            // TODO:
            return 1;
        }

        virtual float getDepthToMmScale()
        {
            return depthScale;
        }

        ~DeviceOpenNI()
        {
            // TODO: ref-count
            openni::OpenNI::shutdown();
        }

        // TODO:
        ivec2 getDepthSize() const
        {
            return depthSize;
        }

        bool isValid() const
        {
            return device.isValid();
        }

        DeviceOpenNI(Option option)
        {
            this->option = option;

            openni::Status rc = openni::OpenNI::initialize();
            if (rc != openni::STATUS_OK)
            {
                CI_LOG_E("Initialize failed\n%s\n", openni::OpenNI::getExtendedError());
                return;
            }

            rc = device.open(openni::ANY_DEVICE);
            if (rc != openni::STATUS_OK)
            {
                CI_LOG_E("Couldn't open device\n%s\n", openni::OpenNI::getExtendedError());
                return;
            }

            bool streamEnabled[] =
            {
                option.enableInfrared,
                option.enableColor,
                option.enableDepth
            };

            openni::VideoStream* streams[] =
            {
                &infraredStream,
                &colorStream,
                &depthStream,
            };

            for (int i = 0; i < OpenNiSensorTypeCount; i++)
            {
                if (!streamEnabled[i]) continue;

                auto type = openni::SensorType(i + 1);
                if (device.getSensorInfo(type) != NULL)
                {
                    rc = streams[i]->create(device, type);
                    if (rc != openni::STATUS_OK)
                    {
                        CI_LOG_E("Couldn't create stream %d\n%s\n", i, openni::OpenNI::getExtendedError());
                        return;
                    }
                }

                rc = streams[i]->start();
                if (rc != openni::STATUS_OK)
                {
                    CI_LOG_E("Couldn't start stream %d\n%s\n", i, openni::OpenNI::getExtendedError());
                    return;
                }
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceOpenNI::update, this));
        }

        static const int SAMPLE_READ_WAIT_TIMEOUT = 100; // ms
        openni::VideoFrameRef grabVideoFrame(openni::VideoStream* pStream)
        {
            openni::VideoFrameRef frame;

            int changedStreamDummy;
            openni::Status rc = openni::OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
            if (rc != openni::STATUS_OK)
            {
                CI_LOG_E("Wait failed! (timeout is %d ms)\n%s\n", openni::SAMPLE_READ_WAIT_TIMEOUT, openni::OpenNI::getExtendedError());
            }

            rc = pStream->readFrame(&frame);
            if (rc != openni::STATUS_OK)
            {
                CI_LOG_E("Read failed!\n%s\n", OpenNI::getExtendedError());
            }

            return frame;
        }

        void update()
        {
            if (option.enableDepth)
            {
                auto frame = grabVideoFrame(&depthStream);
                depthSize.x = frame.getWidth();
                depthSize.y = frame.getHeight();
                auto data = (uint16_t*)frame.getData();
                depthChannel = Channel16u(depthSize.x, depthSize.y, sizeof(uint16_t) * depthSize.x, 1, data);
                signalDepthDirty.emit();
            }

            if (option.enableInfrared)
            {
                auto frame = grabVideoFrame(&infraredStream);
                auto data = (uint16_t*)frame.getData();
                int w = frame.getWidth();
                int h = frame.getHeight();
                infraredChannel = Channel16u(w, h, sizeof(uint16_t) * w, 1, data);
                signalInfraredDirty.emit();
            }

            if (option.enableColor)
            {
                auto frame = grabVideoFrame(&colorStream);
                auto data = (uint8_t*)frame.getData();
                int w = frame.getWidth();
                int h = frame.getHeight();
                colorSurface = Surface8u(data, w, h, sizeof(uint8_t) * 3 * w, SurfaceChannelOrder::RGB);
                signalColorDirty.emit();
            }
        }
    };

    uint32_t getOpenNICount()
    {
        return DeviceOpenNI::getDeviceCount();
    }

    DeviceRef createOpenNI(Option option)
    {
        return DeviceRef(new DeviceOpenNI(option));
    }
}
