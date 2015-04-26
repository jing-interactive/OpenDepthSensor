#include "KinectDevice.h"
#ifdef KINECT_V2
#include "KCBv2Lib.h"
#else
#include "KinectCommonBridgeLib.h"
#endif
#include "cinder/app/app.h"
#include "cinder/Log.h"

namespace Kinect
{
    using namespace ci;
    using namespace ci::app;

#ifdef KINECT_V2

    struct DeviceV2 : public Device
    {
        ~DeviceV2()
        {
            if (depthFrame != nullptr)
            {
                KCBReleaseDepthFrame(&depthFrame);
            }
            if (coordMapper != nullptr)
            {
                coordMapper->Release();
            }
            if (sensor != KCB_INVALID_HANDLE)
            {
                KCBCloseSensor(&sensor);
            }
        }

        int getWidth() const override
        {
            return depthDesc.width;
        }

        int getHeight() const override
        {
            return depthDesc.height;
        }

        DeviceV2(Option option)
        {
            this->option = option;
            depthFrame = nullptr;

            HRESULT hr = S_OK;

            sensor = KCBOpenDefaultSensor();
            if (KCB_INVALID_HANDLE == sensor)
            {
                hr = E_UNEXPECTED;
            }

            if (SUCCEEDED(hr))
            {
                hr = KCBGetICoordinateMapper(sensor, &coordMapper);
                if (FAILED(hr))
                {
                    CI_LOG_E("Failed to call KCBGetICoordinateMapper()");
                }

                if (option.enableDepth)
                {
                    hr = KCBGetDepthFrameDescription(sensor, &depthDesc);
                    if (SUCCEEDED(hr))
                    {
                        hr = KCBCreateDepthFrame(depthDesc, &depthFrame);
                        depthChannel = Channel16u(depthDesc.width, depthDesc.height,
                            depthDesc.bytesPerPixel * depthDesc.width, 1, depthFrame->Buffer);
                    }
                }
            }

            if (FAILED(hr))
            {
                CI_LOG_E("Failed to connect to Kinect");
                App::get()->quit();
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceV2::update, this));
        }

        const vec3 toCi(const CameraSpacePoint& pos)
        {
            return vec3(pos.X, pos.Y, pos.Z);
        }

        const vec2 toCi(const ColorSpacePoint& pos)
        {
            return vec2(pos.X, pos.Y);
        }

        const vec2 toCi(const DepthSpacePoint& pos)
        {
            return vec2(pos.X, pos.Y);
        }

        void update()
        {
            if (option.enableDepth && KCBIsFrameReady(sensor, FrameSourceTypes_Depth))
            {
                if (SUCCEEDED(KCBGetDepthFrame(sensor, depthFrame)))
                {
                    signalDepthDirty();
                }
            }

            /*
            enum _JointType
            {
            JointType_SpineBase	= 0,
            JointType_SpineMid	= 1,
            JointType_Neck	= 2,
            JointType_Head	= 3,
            JointType_ShoulderLeft	= 4,
            JointType_ElbowLeft	= 5,
            JointType_WristLeft	= 6,
            JointType_HandLeft	= 7,
            JointType_ShoulderRight	= 8,
            JointType_ElbowRight	= 9,
            JointType_WristRight	= 10,
            JointType_HandRight	= 11,
            JointType_HipLeft	= 12,
            JointType_KneeLeft	= 13,
            JointType_AnkleLeft	= 14,
            JointType_FootLeft	= 15,
            JointType_HipRight	= 16,
            JointType_KneeRight	= 17,
            JointType_AnkleRight	= 18,
            JointType_FootRight	= 19,
            JointType_SpineShoulder	= 20,
            JointType_HandTipLeft	= 21,
            JointType_ThumbLeft	= 22,
            JointType_HandTipRight	= 23,
            JointType_ThumbRight	= 24,
            JointType_Count	= ( JointType_ThumbRight + 1 )
            } ;
            */
            if (option.enableBody && KCBIsFrameReady(sensor, FrameSourceTypes_Body))
            {
                int64_t timeStamp = 0L;
                IBody* srcBodies[BODY_COUNT] = { 0 };

                if (SUCCEEDED(KCBGetBodyData(sensor, BODY_COUNT, srcBodies, &timeStamp)))
                {
                    HRESULT hr = S_OK;
                    bodies.clear();
                    for (auto& srcBody : srcBodies)
                    {
                        if (srcBody == nullptr) continue;

                        BOOLEAN bTracked = false;
                        hr = srcBody->get_IsTracked(&bTracked);
                        if (FAILED(hr) || !bTracked) continue;

                        Body body;
                        srcBody->get_TrackingId(&body.id);
                            
                        Joint srcJoints[JointType_Count] = {};
                        hr = srcBody->GetJoints(JointType_Count, srcJoints);
                        if (FAILED(hr)) continue;

                        static std::pair<int, int> mappingPairs[] =
                        {
                            { Body::LEFT_HAND, JointType_HandLeft },
                            { Body::RIGHT_HAND, JointType_HandRight },
                            { Body::HEAD, JointType_Head },
                        };
                        for (auto& mapping : mappingPairs)
                        {
                            body.joints[mapping.first].pos3d = toCi(srcJoints[mapping.second].Position);
                            DepthSpacePoint depthPoint = { 0 };
                            coordMapper->MapCameraPointToDepthSpace(srcJoints[mapping.second].Position, &depthPoint);
                            body.joints[mapping.first].pos2d = toCi(depthPoint);
                        }
                    }
                    for (auto& srcBody : srcBodies)
                    {
                        if (srcBody == nullptr) continue;
                        srcBody->Release();
                    }
                    signalBodyDirty();
                }
            }
        }

        KCBDepthFrame *depthFrame;
        KCBFrameDescription depthDesc;

        ICoordinateMapper* coordMapper;
        int sensor;
    };

    DeviceRef Device::createV2(Option option)
    {
        return DeviceRef(new DeviceV2(option));
    }

#else

    struct DeviceV1 : public Device
    {
        ~DeviceV1()
        {
            if (depthBuffer != nullptr)
            {
                delete[] depthBuffer;
            }
            if (sensor != KCB_INVALID_HANDLE)
            {
                KinectCloseSensor(sensor);
            }
        }

        int getWidth() const override
        {
            return depthDesc.dwWidth;
        }

        int getHeight() const override
        {
            return depthDesc.dwHeight;
        }

        DeviceV1(Option option)
        {
            this->option = option;
            depthBuffer = nullptr;

            HRESULT hr = S_OK;

            sensor = KinectOpenDefaultSensor();
            if (KCB_INVALID_HANDLE == sensor)
            {
                hr = E_UNEXPECTED;
            }

            if (SUCCEEDED(hr))
            {
                KinectStopColorStream(sensor);
                depthDesc = { sizeof(KINECT_IMAGE_FRAME_FORMAT) };
                KinectGetDepthFrameFormat(sensor, &depthDesc);
                depthBuffer = new uint8_t[depthDesc.cbBufferSize];
                depthChannel = Channel16u(depthDesc.dwWidth, depthDesc.dwHeight,
                    depthDesc.cbBytesPerPixel * depthDesc.dwWidth, 1, (uint16_t *)depthBuffer);
            }

            if (FAILED(hr))
            {
                CI_LOG_E("Failed to connect to Kinect");
                App::get()->quit();
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceV1::update, this));
        }

        void update()
        {
            if (KinectIsDepthFrameReady(sensor))
            {
                if (SUCCEEDED(KinectGetDepthFrame(sensor, depthDesc.cbBufferSize, depthBuffer, nullptr)))
                {
                    signalDepthDirty();
                }
            }
        }

        uint8_t *depthBuffer;
        KINECT_IMAGE_FRAME_FORMAT depthDesc;
        int sensor;
    };

    DeviceRef Device::createV1(Option option/* = Option()*/)
    {
        return DeviceRef(new DeviceV1(option));
    }

#endif
}
