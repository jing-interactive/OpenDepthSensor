#include "DepthSensor.h"

#include "libfreenect2/libfreenect2.hpp"
#include "libfreenect2/logger.h"
#include "libfreenect2/frame_listener_impl.h"
#include "libfreenect2/registration.h"

#include "cinder/app/app.h"
#include "cinder/Log.h"

#ifdef _DEBUG
#pragma comment (lib, "freenect2d.lib")
#else
#pragma comment (lib, "freenect2.lib")
#endif

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct MyFileLogger : public libfreenect2::Logger
    {
    public:
        MyFileLogger()
        {
            level_ = Debug;
        }

        bool good()
        {
            return true;
        }

        virtual void log(Level level, const std::string &message)
        {
            ci::log::Level ciLevel = ci::log::LEVEL_INFO;
            switch (level)
            {
            case Error:     ciLevel = ci::log::LEVEL_ERROR;
            case Warning:   ciLevel = ci::log::LEVEL_WARNING;
            case Debug:     ciLevel = ci::log::LEVEL_DEBUG;
            default:        break;
            }

            CINDER_LOG_STREAM(ciLevel, message);
        }
    };

    struct DeviceFreenect2 : public Device
    {
        static libfreenect2::Freenect2 freenect2;
        libfreenect2::Freenect2Device *dev = nullptr;
        libfreenect2::PacketPipeline *pipeline = nullptr;

        unique_ptr<libfreenect2::Registration> registration;
        unique_ptr<libfreenect2::SyncMultiFrameListener> listener;

        unique_ptr<uint16_t[]> depthBuffer;
        ivec2 kDepthSize = { 512, 424 };
        ivec2 kColorSize = { 1920, 1080 };

        virtual bool isValid() const
        {
            return dev != nullptr;
        }
 
        static uint32_t getDeviceCount()
        {
            static bool isLoggerCreated = false;
            if (!isLoggerCreated)
            {
                isLoggerCreated = true;
                libfreenect2::setGlobalLogger(new MyFileLogger());
            }

            return freenect2.enumerateDevices();
        }

        ivec2 getDepthSize() const
        {
            return kDepthSize;
        }

        ivec2 getColorSize() const
        {
            return kColorSize;
        }

        DeviceFreenect2(Option option)
        {
            this->option = option;

            if (getDeviceCount() == 0)
            {
                CI_LOG_E("There is no Freenect2 devices.");
                return;
            }

            const int gpuId = -1;
#ifdef LIBFREENECT2_WITH_OPENCL_SUPPORT
            if (!pipeline)
                pipeline = new libfreenect2::OpenCLPacketPipeline(gpuId);
#elif LIBFREENECT2_WITH_CUDA_SUPPORT
            if (!pipeline)
                pipeline = new libfreenect2::CudaPacketPipeline(gpuId);
#endif
            if (!pipeline)
                pipeline = new libfreenect2::CpuPacketPipeline();

            dev = freenect2.openDevice(option.deviceId, pipeline);
            //CI_LOG_I("device serial : " << dev->getSerialNumber());
            //CI_LOG_I("device firmware : " << dev->getFirmwareVersion());

            /// listeners
            int types = 0;
            if (option.enableColor)
            {
                types |= libfreenect2::Frame::Color;
            }
            if (option.enableDepth)
            {
                types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
                depthBuffer.reset(new uint16_t[kDepthSize.x * kDepthSize.y]);
                depthChannel = Channel16u(kDepthSize.x, kDepthSize.y, sizeof(uint16_t) * kDepthSize.x, 1, depthBuffer.get());
            }
            listener = make_unique<libfreenect2::SyncMultiFrameListener>(types);

            dev->setColorFrameListener(listener.get());
            dev->setIrAndDepthFrameListener(listener.get());

            /// start
            if (!dev->startStreams(option.enableColor, option.enableDepth))
            {
                CI_LOG_E("device #" << option.deviceId << " fails at startStreams()");
                return;
            }

            if (option.enablePointCloud)
            {
                registration = make_unique<libfreenect2::Registration>(dev->getIrCameraParams(), dev->getColorCameraParams());
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceFreenect2::update, this));
        }

        virtual ~DeviceFreenect2()
        {
            if (dev)
            {
                dev->stop();
                dev->close();
            }
        }

        void update()
        {
            if (!listener->hasNewFrame()) return;

            libfreenect2::FrameMap frames;

            if (!listener->waitForNewFrame(frames, 0.01)) // seconds
            {
                CI_LOG_V("timeout!");
                return;
            }

            libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
            libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
            libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];

            if (depth && option.enableDepth)
            {
                assert(kDepthSize.x == depth->width);
                assert(sizeof(float) == depth->bytes_per_pixel);
                const float* src = (const float*)depth->data;
                for (int i = 0; i < kDepthSize.x*kDepthSize.y; i++)
                {
                    depthBuffer[i] = src[i];
                }
                signalDepthDirty.emit();
            }

            if (rgb && option.enableColor)
            {
                signalColorDirty.emit();
            }

            if (option.enablePointCloud)
            {
                libfreenect2::Frame undistorted(kDepthSize.x, kDepthSize.y, 4);
                libfreenect2::Frame registered(kDepthSize.x, kDepthSize.y, 4);
                registration->apply(rgb, depth, &undistorted, &registered);
            }

            listener->release(frames);
        }

        int width, height;
    };

    libfreenect2::Freenect2 DeviceFreenect2::freenect2;

    uint32_t getFreenect2Count()
    {
        return DeviceFreenect2::getDeviceCount();
    }

    DeviceRef createFreenect2(Option option)
    {
        return DeviceRef(new DeviceFreenect2(option));
    }
}
