#include "DepthSensor.h"

#ifdef KinectAzure_Enabled

#include "cinder/ImageIo.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"

#include "k4a/k4a.h"

#pragma comment(lib, "k4a")

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceKinectAzure : public Device
    {
        virtual bool isValid() const { return true; }

        ivec2 getDepthSize() const { return depthChannel.getSize(); }

        ivec2 getColorSize() const { return depthChannel.getSize(); }

        DeviceKinectAzure(Option option)
        {
            this->option = option;
            depthChannel = loadImage(getAssetPath("KinectSnapshot-update.png"));

            App::get()->getSignalUpdate().connect(std::bind(&DeviceKinectAzure::update, this));
        }

        void update()
        {
            if (option.enableDepth)
            {
                // TODO: update depthChannel
                signalDepthDirty.emit();
            }
        }

        int width, height;
    };

    uint32_t getKinectAzureCount() { return k4a_device_get_installed_count(); }

    DeviceRef createKinectAzure(Option option) { return DeviceRef(new DeviceKinectAzure(option)); }
} // namespace ds

#endif
