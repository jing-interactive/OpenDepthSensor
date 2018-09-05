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
        virtual bool isValid() const { return pImiDevice != NULL; }

        ivec2 getDepthSize() const { return depthChannel.getSize(); }

        ivec2 getColorSize() const { return depthChannel.getSize(); }

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
            if (0 != imiInitialize(NULL))
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
            CI_LOG_I("Get %d Connected Imidevice.", deviceCount);

            // 3.imiOpenDevice()
            if (0 != imiOpenDevice(pDeviceAttr[0].uri, &pImiDevice, 0))
            {
                CI_LOG_E("Open Imidevice Failed!");
                return;
            }
            CI_LOG_I("Imidevice Opened.");

            // 4.imiOpenStream()
            if (option.enableDepth)
            {
                if (0 != imiOpenStream(pImiDevice, IMI_DEPTH_FRAME, NULL, NULL,
                                       &g_streams[g_streamNum++]))
                {
                    CI_LOG_E("Open Depth Stream Failed!");
                    return;
                }
                CI_LOG_I("Open Depth Stream Success.");
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceImi::update, this));
        }

        void update()
        {
            if (option.enableDepth)
            {
                // TODO: update depthChannel
                signalDepthDirty.emit();
            }
        }
        ImiDeviceAttribute* pDeviceAttr = NULL;
        ImiDeviceHandle pImiDevice = NULL;
        // stream handles
        uint32_t g_streamNum = 0;
        ImiStreamHandle g_streams[10] = {NULL};

        int width, height;
    };

    uint32_t getImiCount() { return 1; }

    DeviceRef createImi(Option option) { return DeviceRef(new DeviceImi(option)); }
} // namespace ds

#endif
