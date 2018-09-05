#include "DepthSensor.h"

#ifdef RgbCamera_Enabled

#include "cinder/Capture.h"
#include "cinder/Log.h"
#include "cinder/app/App.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
    struct DeviceRgbCamera : public Device
    {
        CaptureRef mCapture;

        virtual bool isValid() const { return mCapture != nullptr; }

        const int32_t kWidth = 640;
        const int32_t kHeight = 480;

        ivec2 getDepthSize() const { return {kWidth, kHeight}; }

        ivec2 getColorSize() const { return {kWidth, kHeight}; }

        DeviceRgbCamera(Option option)
        {
            this->option = option;

            try
            {
                mCapture = Capture::create(kWidth, kHeight, Capture::getDevices()[option.deviceId]);
                mCapture->start();
            }
            catch (ci::Exception& exc)
            {
                CI_LOG_EXCEPTION("Failed to init capture ", exc);
            }

            if (option.enableDepth)
            {
                depthChannel = Channel16u(kWidth, kHeight);
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceRgbCamera::update, this));
        }

        void update()
        {
            if (!isValid())
                return;

            if (mCapture->checkNewFrame())
            {
                if (option.enablePointCloud && option.enableColor &&
                    depthToColorTable.getWidth() == 0)
                {
                    depthToColorTable =
                        Surface32f(kWidth, kHeight, false, SurfaceChannelOrder::RGB);

                    for (int y = 0; y < kHeight; y++)
                    {
                        for (int x = 0; x < kWidth; x++)
                        {
                            float* data = depthToColorTable.getData({x, y});
                            data[0] = x / (float)kWidth;
                            data[1] = y / (float)kHeight;
                        }
                    }
                    signalDepthToColorTableDirty.emit();
                }

                colorSurface = *mCapture->getSurface();
                if (option.enableColor)
                {
                    signalColorDirty.emit();
                }
                if (option.enableDepth)
                {
#if 0
                    cv::Mat im = toOcv(colorSurface);
                    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);  // 3 to 1 chan
                    im.convertTo(im, CV_16U, 255); // 8bit to 16
                    depthChannel = fromOcv(im);
#else
                    for (int x = 0; x < kWidth; x++)
                        for (int y = 0; y < kHeight; y++)
                        {
                            uint16_t* dest = depthChannel.getData({x, y});
                            uint8_t* src = colorSurface.getData({x, y});
                            *dest = (src[0] + src[1] + src[2]) * 4; // 4 is magic number
                        }
#endif

                    signalDepthDirty.emit();
                }
            }
        }

        int width, height;
    };

    uint32_t getRgbCameraCount() { return Capture::getDevices().size(); }

    DeviceRef createRgbCamera(Option option) { return DeviceRef(new DeviceRgbCamera(option)); }
} // namespace ds

#endif
