#include "DepthSensor.h"

#ifdef Simulator_Enabled

#include "cinder/app/app.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceSimulator : public Device
    {
        virtual bool isValid() const
        {
            return true;
        }

        ivec2 getDepthSize() const
        {
            return depthChannel.getSize();
        }

        ivec2 getColorSize() const
        {
            return depthChannel.getSize();
        }

        DeviceSimulator(Option option)
        {
            this->option = option;
            depthChannel = loadImage(getAssetPath("KinectSnapshot-update.png"));

            App::get()->getSignalUpdate().connect(std::bind(&DeviceSimulator::update, this));
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

    uint32_t getSimulatorCount()
    {
        return 1;
    }

    DeviceRef createSimulator(Option option)
    {
        return DeviceRef(new DeviceSimulator(option));
    }
}

#endif
