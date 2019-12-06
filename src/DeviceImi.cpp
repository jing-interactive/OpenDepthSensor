#include "DepthSensor.h"

#ifdef Imi_Enabled

#include "cinder/Log.h"
#include "cinder/app/App.h"

#include "ImiCamera.h"
#include "ImiNect.h"

#pragma comment(lib, "ImiCamera.lib")
#pragma comment(lib, "ImiNect.lib")

#define MAX_DEPTH 10000
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define DEFAULT_PERPIXEL_BITS 16
#define DEFAULT_FRAMERATE 30

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceImi : public Device
    {
        ImiDeviceAttribute* pDeviceAttr = NULL;
        ImiDeviceHandle pImiDevice = NULL;
        // stream handles
        uint32_t g_streamNum = 0;
        ImiStreamHandle g_streams[10] = {NULL};
        ImiStreamHandle depthHandle, colorHandle;
        ivec2 depthSize;
        ivec2 colorSize;

        virtual bool isValid() const { return pImiDevice != NULL; }

        ivec2 getDepthSize() const { return depthSize; }

        ivec2 getColorSize() const { return colorSize; }

        virtual ~DeviceImi()
        {
            for (uint32_t num = 0; num < g_streamNum; ++num)
            {
                if (NULL != g_streams[num])
                {
                    imiCloseStream(g_streams[num]);
                }
            }

            // 7.imiCloseDevice()
            if (NULL != pImiDevice)
            {
                imiCloseDevice(pImiDevice);
            }

            // 8.imiReleaseDeviceList()
            if (NULL != pDeviceAttr)
            {
                imiReleaseDeviceList(&pDeviceAttr);
            }

            // 9.imiDestroy()
            imiDestroy();
        }

        DeviceImi(Option option)
        {
            this->option = option;

            // 1.imiInitialize()
            if (imiInitialize(NULL))
            {
                CI_LOG_E("ImiNect Init Failed!");
                return;
            }
            CI_LOG_I("ImiNect Init Success.");

            // 2.imiGetDeviceList()
            uint32_t deviceCount = 0;
            imiGetDeviceList(&pDeviceAttr, &deviceCount);
            if (deviceCount <= 0 || NULL == pDeviceAttr)
            {
                CI_LOG_E("Get No Connected Imidevice!");
                imiDestroy();
                return;
            }
            CI_ASSERT(deviceCount == 1);
            CI_LOG_I("Get %d Connected Imidevice." << deviceCount);

            // 3.imiOpenDevice()
            if (imiOpenDevice(pDeviceAttr[0].uri, &pImiDevice, 0))
            {
                CI_LOG_E("Open Imidevice Failed!");
                return;
            }
            CI_LOG_I("Imidevice Opened.");

            // 4.imiOpenStream()
            if (option.enableDepth)
            {
                if (imiOpenStream(pImiDevice, IMI_DEPTH_FRAME, NULL, NULL, &depthHandle))
                {
                    CI_LOG_E("Open Depth Stream Failed!");
                    return;
                }
                g_streams[g_streamNum++] = depthHandle;
                CI_LOG_I("Open Depth Stream Success.");

                const ImiFrameMode* frameMode = imiGetCurrentFrameMode(pImiDevice, IMI_DEPTH_FRAME);
                depthSize = {frameMode->resolutionX, frameMode->resolutionY};
            }

            if (option.enableColor)
            {
                {
                    ImiFrameMode frameMode;
                    frameMode.pixelFormat = IMI_PIXEL_FORMAT_IMAGE_RGB24;
                    frameMode.resolutionX = IMAGE_WIDTH;
                    frameMode.resolutionY = IMAGE_HEIGHT;
                    frameMode.bitsPerPixel = DEFAULT_PERPIXEL_BITS;
                    frameMode.framerate = DEFAULT_FRAMERATE;
                    imiSetFrameMode(pImiDevice, IMI_COLOR_FRAME, &frameMode);
                }

                if (imiOpenStream(pImiDevice, IMI_COLOR_FRAME, NULL, NULL, &colorHandle))
                {
                    CI_LOG_E("Open Color Stream Failed!");
                    return;
                }
                g_streams[g_streamNum++] = colorHandle;
                CI_LOG_I("Open Color Stream Success.");

                const ImiFrameMode* frameMode = imiGetCurrentFrameMode(pImiDevice, IMI_COLOR_FRAME);
                colorSize = {frameMode->resolutionX, frameMode->resolutionY};
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceImi::update, this));
        }

        void update()
        {
            int32_t avStreamIndex;

            // wait for stream, -1 means infinite;
            if (imiWaitForStreams(g_streams, g_streamNum, &avStreamIndex, 100))
            {
                return;
            }

            /*CI_LOG_E("channel index : %d", avStreamIndex);*/
            if ((avStreamIndex < 0) || ((uint32_t)avStreamIndex >= g_streamNum))
            {
                CI_LOG_E("imiWaitForStream returns 0, but channel index abnormal: " << avStreamIndex);
                return;
            }

            if (option.enableDepth && g_streams[avStreamIndex] == depthHandle)
            {
                ImiImageFrame* pFrame = NULL;
                // frame coming, read.
                if (imiReadNextFrame(g_streams[avStreamIndex], &pFrame, 0))
                {
                    CI_LOG_E("imiReadNextFrame Failed, channel index : " << avStreamIndex);
                    return;
                }
                auto data = (uint16_t*)pFrame->pData;
                depthChannel =
                    Channel16u(depthSize.x, depthSize.y, sizeof(uint16_t) * depthSize.x, 1, data);

                signalDepthDirty.emit();
                imiReleaseFrame(&pFrame);
            }

            if (option.enableColor && g_streams[avStreamIndex] == colorHandle)
            {
                ImiImageFrame* pFrame = NULL;
                // frame coming, read.
                if (imiReadNextFrame(g_streams[avStreamIndex], &pFrame, 0))
                {
                    CI_LOG_E("imiReadNextFrame Failed, channel index : ") << avStreamIndex;
                    return;
                }
                CI_ASSERT(pFrame->pixelFormat == IMI_PIXEL_FORMAT_IMAGE_RGB24);
                auto data = (uint8_t*)pFrame->pData;
                colorSurface =
                    Surface8u(data, colorSize.x, colorSize.y, sizeof(uint8_t) * 3 * colorSize.x,
                              SurfaceChannelOrder::RGB);
                signalColorDirty.emit();
                imiReleaseFrame(&pFrame);
            }
        }

    }; // namespace ds

    uint32_t getImiCount() { return 1; }

    DeviceRef createImi(Option option) { return DeviceRef(new DeviceImi(option)); }
} // namespace ds

#endif
