#include "DepthSensor.h"

#include "cinder/app/app.h"
#include "cinder/Log.h"
#include "cinder/Capture.h"
#include "../../Cinder-OpenCV3/include/CinderOpenCV.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceRgbCamera : public Device
    {
        CaptureRef mCapture;

        virtual bool isValid() const
        {
            return mCapture != nullptr;
        }

        const int32_t kWidth = 640;
        const int32_t kHeight = 480;

        ivec2 getDepthSize() const
        {
            return depthChannel.getSize();
        }

        DeviceRgbCamera(Option option)
        {
            this->option = option;

            try {
                mCapture = Capture::create(kWidth, kHeight, Capture::getDevices()[option.deviceId]);
                mCapture->start();
            }
            catch (ci::Exception &exc) {
                CI_LOG_EXCEPTION("Failed to init capture ", exc);
            }

            //if (option.enableDepth)
            //{
            //    depthChannel = Channel16u(kWidth, kHeight);
            //}

            App::get()->getSignalUpdate().connect(std::bind(&DeviceRgbCamera::update, this));
        }

        void update()
        {
            if (!isValid()) return;

            if (mCapture->checkNewFrame())
            {
                colorSurface = *mCapture->getSurface();
                if (option.enableColor)
                {
                    signalColorDirty.emit();
                }
                if (option.enableDepth)
                {
                    cv::Mat im = toOcv(colorSurface);
                    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);  // 3 to 1 chan
                    im.convertTo(im, CV_16U, 255); // 8bit to 16
                    depthChannel = fromOcv(im);

                    signalDepthDirty.emit();
                }
            }
        }

        int width, height;
    };

    uint32_t getRgbCameraCount()
    {
        return Capture::getDevices().size();
    }

    DeviceRef createRgbCamera(Option option)
    {
        return DeviceRef(new DeviceRgbCamera(option));
    }
}
