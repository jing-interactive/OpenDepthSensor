#include "KinectDevice.h"
#include "KCBv2Lib.h"
#include "KinectCommonBridgeLib.h"
#include "cinder/app/app.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"

namespace Kinect
{
    using namespace ci;
    using namespace ci::app;

    struct DeviceKinect2 : public Device
    {
        static int getDeviceCount()
        {
            return 1;
        }

        ~DeviceKinect2()
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

        bool isValid() const
        {
            return sensor != KCB_INVALID_HANDLE;
        }

        DeviceKinect2(Option option)
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

                hr = KCBGetDepthFrameDescription(sensor, &depthDesc);
                if (SUCCEEDED(hr))
                {
                    hr = KCBCreateDepthFrame(depthDesc, &depthFrame);
                    depthChannel = Channel16u(depthDesc.width, depthDesc.height,
                        depthDesc.bytesPerPixel * depthDesc.width, 1, depthFrame->Buffer);
                }
            }

            if (FAILED(hr))
            {
                CI_LOG_E("Failed to connect to Kinect");
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceKinect2::update, this));
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
                    signalDepthDirty.emit();
                }
            }

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
                            { Body::HIP_CENTER, JointType_SpineBase },
                            { Body::SPINE, JointType_SpineMid },
                            { Body::SHOULDER_CENTER, JointType_SpineShoulder },
                            { Body::NECK, JointType_Neck },
                            { Body::HEAD, JointType_Head },
                            { Body::SHOULDER_LEFT, JointType_ShoulderLeft },
                            { Body::ELBOW_LEFT, JointType_ElbowLeft },
                            { Body::WRIST_LEFT, JointType_WristLeft },
                            { Body::HAND_LEFT, JointType_HandLeft },
                            { Body::SHOULDER_RIGHT, JointType_ShoulderRight },
                            { Body::ELBOW_RIGHT, JointType_ElbowRight },
                            { Body::WRIST_RIGHT, JointType_WristRight },
                            { Body::HAND_RIGHT, JointType_HandRight },
                            { Body::HIP_LEFT, JointType_HipLeft },
                            { Body::KNEE_LEFT, JointType_KneeLeft },
                            { Body::ANKLE_LEFT, JointType_AnkleLeft },
                            { Body::FOOT_LEFT, JointType_FootLeft },
                            { Body::HIP_RIGHT, JointType_HipRight },
                            { Body::KNEE_RIGHT, JointType_KneeRight },
                            { Body::ANKLE_RIGHT, JointType_AnkleRight },
                            { Body::FOOT_RIGHT, JointType_FootRight },
                            { Body::HAND_TIP_LEFT, JointType_HandTipLeft },
                            { Body::HAND_THUMB_LEFT, JointType_ThumbLeft },
                            { Body::HAND_TIP_RIGHT, JointType_HandTipRight },
                            { Body::HAND_THUMB_RIGHT, JointType_ThumbRight },
                        };
                        for (auto& mapping : mappingPairs)
                        {
                            body.joints[mapping.first].pos3d = toCi(srcJoints[mapping.second].Position);
                            DepthSpacePoint depthPoint = { 0 };
                            coordMapper->MapCameraPointToDepthSpace(srcJoints[mapping.second].Position, &depthPoint);
                            depthPoint.X /= getWidth();
                            depthPoint.Y /= getHeight();
                            body.joints[mapping.first].pos2d = toCi(depthPoint);
                        }
                        bodies.push_back(body);
                    }
                    for (auto& srcBody : srcBodies)
                    {
                        if (srcBody == nullptr) continue;
                        srcBody->Release();
                    }
                    signalBodyDirty.emit();
                }
            }
        }

        KCBDepthFrame *depthFrame;
        KCBFrameDescription depthDesc;

        ICoordinateMapper* coordMapper;
        int sensor;
    };

    struct DeviceKinect1 : public Device
    {
        static int getDeviceCount()
        {
            return KinectGetPortIDCount();
        }

        ~DeviceKinect1()
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

        bool isValid() const
        {
            return sensor != KCB_INVALID_HANDLE;
        }

        DeviceKinect1(Option option)
        {
            this->option = option;
            depthBuffer = nullptr;

            HRESULT hr = S_OK;

            WCHAR portName[100];
            if (KinectGetPortIDByIndex(option.deviceId, 100, portName))
            {
                sensor = KinectOpenSensor(portName);
            }
            else
            {
                sensor = KinectOpenDefaultSensor();
            }

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
            }

            App::get()->getSignalUpdate().connect(std::bind(&DeviceKinect1::update, this));
        }

        const vec3 toCi(const Vector4& pos)
        {
            return vec3(pos.x, pos.y, pos.z);
        }

        void update()
        {
            if (option.enableDepth && KinectIsDepthFrameReady(sensor))
            {
                if (SUCCEEDED(KinectGetDepthFrame(sensor, depthDesc.cbBufferSize, depthBuffer, nullptr)))
                {
                    signalDepthDirty.emit();
                }
            }

            if (option.enableBody && KinectIsSkeletonFrameReady(sensor))
            {
                if (SUCCEEDED(KinectGetSkeletonFrame(sensor, &skeletonFrame)))
                {
                    for (auto& data : skeletonFrame.SkeletonData)
                    {
                        if (data.eTrackingState != NUI_SKELETON_TRACKED) continue;
                        Body body;
                        body.id = data.dwTrackingID;

                        static std::pair<int, int> mappingPairs[] =
                        {
                            { Body::HIP_CENTER, NUI_SKELETON_POSITION_HIP_CENTER },
                            { Body::SPINE, NUI_SKELETON_POSITION_SPINE },
                            { Body::SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_CENTER },
                            { Body::HEAD, NUI_SKELETON_POSITION_HEAD },
                            { Body::SHOULDER_LEFT, NUI_SKELETON_POSITION_SHOULDER_LEFT },
                            { Body::ELBOW_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT },
                            { Body::WRIST_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT },
                            { Body::HAND_LEFT, NUI_SKELETON_POSITION_HAND_LEFT },
                            { Body::SHOULDER_RIGHT, NUI_SKELETON_POSITION_SHOULDER_RIGHT },
                            { Body::ELBOW_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT },
                            { Body::WRIST_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT },
                            { Body::HAND_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT },
                            { Body::HIP_LEFT, NUI_SKELETON_POSITION_HIP_LEFT },
                            { Body::KNEE_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT },
                            { Body::ANKLE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT },
                            { Body::FOOT_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT },
                            { Body::HIP_RIGHT, NUI_SKELETON_POSITION_HIP_RIGHT },
                            { Body::KNEE_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT },
                            { Body::ANKLE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT },
                            { Body::FOOT_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT },
                        };
                        for (auto& mapping : mappingPairs)
                        {
                            vec3 pos3d = toCi(data.SkeletonPositions[mapping.second]);
                            vec2 pos2d;

                            if (pos3d.z > FLT_EPSILON)
                            {
                                //
                                // Center of depth sensor is at (0,0,0) in skeleton space, and
                                // and (width/2,height/2) in depth image coordinates.  Note that positive Y
                                // is up in skeleton space and down in image coordinates.
                                //

                                pos2d.x = 0.5f + pos3d.x * (depthDesc.dwWidth / 320.f) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / pos3d.z;
                                pos2d.y = 0.5f - pos3d.y * (depthDesc.dwHeight / 240.f) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / pos3d.z;

                            }
                            body.joints[mapping.first].pos3d = pos3d;
                            body.joints[mapping.first].pos2d = pos2d;
                        }
                        bodies.push_back(body);
                    }
                }
            }
        }

        uint8_t *depthBuffer;
        KINECT_IMAGE_FRAME_FORMAT depthDesc;
        NUI_SKELETON_FRAME skeletonFrame;
        int sensor;
    };

    struct DeviceSimulator : public Device
    {
        virtual bool isValid() const
        {
            return true;
        }
        virtual int getWidth() const
        {
            return depthChannel.getWidth();
        }
        virtual int getHeight() const
        {
            return depthChannel.getHeight();
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

    int Device::getDeviceCount(DeviceType type)
    {
        if (type == Kinect1)
            return DeviceKinect1::getDeviceCount();
        else if (type == Kinect2)
            return DeviceKinect2::getDeviceCount();
        else
            return 1;
    }

    DeviceRef Device::create(DeviceType type, Option option/* = Option()*/)
    {
        if (type == Kinect1)
            return DeviceRef(new DeviceKinect1(option));
        else if (type == Kinect2)
            return DeviceRef(new DeviceKinect2(option));
        else
            return DeviceRef(new DeviceSimulator(option));
    }
}
