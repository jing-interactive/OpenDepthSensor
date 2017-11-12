#include "DepthSensor.h"

#ifdef Rplidar_Enabled

#include "cinder/app/App.h"
#include "cinder/Log.h"
#include "rplidar.h"

using namespace ci;
using namespace ci::app;
using namespace std;

using namespace rp::standalone::rplidar;

void info_(const string& err)
{
    CI_LOG_I(err);
}

struct RPlidarHelper
{
    bool setup(const string& serialPort)
    {
        // create the driver instance
        if (drv == nullptr) {
            drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);
            if (!drv) {
                info_("insufficent memory, exit");
                return false;
            }
        }

        drv->disconnect();

        // make connection...
        if (IS_FAIL(drv->connect(serialPort.c_str(), 115200))) {
            info_("Fail to connect LIDAR");
            return false;
        }

        info_("Connected to RPLidar");

        rplidar_response_device_info_t devinfo;

        // retrieving the device info
        ////////////////////////////////////////
        if (IS_FAIL(drv->getDeviceInfo(devinfo))) {
            info_("getDeviceInfo() fails");
            return false;
        }

        CI_LOG_I("Firmware Ver: " << (devinfo.firmware_version >> 8) << '.' << (devinfo.firmware_version & 0xFF));
        CI_LOG_I("Hardware Rev: " << (int)devinfo.hardware_version);

        // check health...
        if (!checkRPLIDARHealth()) {
            info_("checkRPLIDARHealth() fails");
            return false;
        }

        if (IS_FAIL(drv->startMotor())) {
            info_("startMotor() fails");
        }

        if (IS_FAIL(drv->startScan())) {
            info_("startScan() fails");
        }

        return true;
    }

    ~RPlidarHelper()
    {
        if (drv) {
            drv->stop();
            drv->stopMotor();
            RPlidarDriver::DisposeDriver(drv);
        }
    }

    bool checkRPLIDARHealth() const
    {
        u_result     op_result;
        rplidar_response_device_health_t healthinfo;

        op_result = drv->getHealth(healthinfo);
        if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
            printf("RPLidar health status : %d\n", healthinfo.status);
            if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
                fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
                // enable the following code if you want rplidar to be reboot by software
                // drv->reset();
                return false;
            }
            else {
                return true;
            }
        }
        else {
            fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
            return false;
        }
    }

    void update()
    {
        if (!drv->isConnected()) return;

        if (IS_FAIL(drv->grabScanData(nodes, scanCount))) {
            info_("grabScanData() fails");
            return;
        }

        if (IS_FAIL(drv->ascendScanData(nodes, scanCount))) {
            info_("ascendScanData() fails");
            return;
        }

        for (int pos = 0; pos < scanCount; ++pos) {
            scanData[pos].x = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f;
            scanData[pos].y = nodes[pos].distance_q2 / 4.0f;
        }
    }

    RPlidarDriver* drv = nullptr;
    rplidar_response_measurement_node_t nodes[360 * 2];
    vec2 scanData[360 * 2];
    size_t scanCount = _countof(nodes);
};

namespace ds
{
    struct DeviceRplidar : public Device
    {
        RPlidarHelper lidar;

        virtual bool isValid() const
        {
            return lidar.checkRPLIDARHealth();
        }

        const int32_t kWidth = 640;
        const int32_t kHeight = 480;

        ivec2 getDepthSize() const
        {
            return{ kWidth, kHeight };
        }

        ivec2 getColorSize() const
        {
            return{ kWidth, kHeight };
        }

        DeviceRplidar(Option option)
        {
            this->option = option;

            try {
                lidar.setup(string("\\\\.\\com" + option.deviceId));
            }
            catch (ci::Exception &exc) {
                CI_LOG_EXCEPTION("Failed to init lidar ", exc);
            }

            option.enableDepth = true;
            option.enableColor = false;

            depthChannel = Channel16u(kWidth, kHeight);

            App::get()->getSignalUpdate().connect(std::bind(&DeviceRplidar::update, this));
        }

        void update()
        {
            if (!isValid()) return;

            lidar.update();

#if 0
            current = cv::Scalar(0);
            vector<cv::Point> points(mLidar.scanCount);
            for (int pos = 0; pos < mLidar.scanCount; pos++) {
                float distPixel = mLidar.scanData[pos].y*MM_TO_PIXEL;
                float rad = (float)(mLidar.scanData[pos].x*3.1415 / 180.0);
                points[pos].x = sin(rad)*(distPixel)+centerPt.x;
                points[pos].y = centerPt.y - cos(rad)*(distPixel);

                //int brightness = (_scan_data[pos].quality << 1) + 128;
                //if (brightness>255) brightness = 255;

                gl::drawSolidCircle({ points[pos].x, points[pos].y }, 1);
            }

            const Point* pts = &points[0];
            const int npts = points.size();
            cv::fillPoly(current, &pts, &npts, 1, cv::Scalar(255));
#endif
            signalDepthDirty.emit();

//            if (mCapture->checkNewFrame())
//            {
//                if (option.enableDepth)
//                {
//#if 1
//                    cv::Mat im = toOcv(colorSurface);
//                    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);  // 3 to 1 chan
//                    im.convertTo(im, CV_16U, 255); // 8bit to 16
//                    depthChannel = fromOcv(im);
//#else
//                    for (int x = 0; x < kWidth; x++)
//                        for (int y = 0; y < kHeight; y++)
//                        {
//                            uint16_t* dest = depthChannel.getData({ x, y });
//                            uint8_t* src = colorSurface.getData({ x, y });
//                            *dest = (src[0] + src[1] + src[2]) * 4; // 4 is magic number
//                        }
//#endif
//
//                    signalDepthDirty.emit();
//                }
//            }
        }

        int width, height;
    };

    uint32_t getRplidarCount()
    {
        return 1;
    }

    DeviceRef createRplidar(Option option)
    {
        return DeviceRef(new DeviceRplidar(option));
    }
}

#endif
