#include "KinectDevice.h"
#include "KCBv2Lib.h"
#include "Kinect.Face.h"
#include "KinectCommonBridgeLib.h"
#include "cinder/app/app.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"

#include <vector>

using std::vector;

#pragma comment (lib, "Kinect20.Face.lib")

namespace Kinect
{
    using namespace ci;
    using namespace ci::app;

    struct DeviceKinect2 : public Device
    {
        KCBDepthFrame *depthFrame = nullptr;
        KCBFrameDescription depthDesc;

        ICoordinateMapper* coordMapper = nullptr;
        int sensor;
        IKinectSensor*  rawSensor = nullptr;

        struct HDFaceDetail
        {
            // https://github.com/UnaNancyOwen/Kinect2Sample/blob/master/Sample/Face/Face.cpp
            IHighDefinitionFaceFrameSource* frameSource = nullptr;
            IHighDefinitionFaceFrameReader* frameReader = nullptr;
            IFaceModelBuilder* modelBuilder = nullptr;
            bool produce = false;
            IFaceAlignment* faceAlignment = nullptr;
            IFaceModel* faceModel = nullptr;
            float deformations[FaceShapeDeformations::FaceShapeDeformations_Count] = {};
        };
        HDFaceDetail hdFaces[BODY_COUNT];
        uint32_t faceVertexCount = 0;
        uint32_t faceIndexCount = 0;

        static uint32_t getDeviceCount()
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
            if (option.enableFace)
            {
                for (int i = 0; i < BODY_COUNT; i++)
                {
                    hdFaces[i].frameSource->Release();
                    hdFaces[i].frameSource->Release();
                    hdFaces[i].modelBuilder->Release();
                }
            }
            if (sensor != KCB_INVALID_HANDLE)
            {
                KCBCloseSensor(&sensor);
            }
        }

        ivec2 getDepthSize() const
        {
            return { depthDesc.width, depthDesc.height };
        }

        bool isValid() const
        {
            return sensor != KCB_INVALID_HANDLE;
        }

        DeviceKinect2(Option option)
        {
            this->option = option;
            if (this->option.enableFace)
            {
                // face is dependent on body
                this->option.enableBody = true;
            }

            HRESULT hr = S_OK;

            sensor = KCBOpenDefaultSensor();
            if (KCB_INVALID_HANDLE == sensor)
            {
                hr = E_UNEXPECTED;
            }

            GetDefaultKinectSensor(&rawSensor);

            if (FAILED(hr))
            {
                CI_LOG_E("Failed to connect to Kinect");
                return;
            }

            hr = KCBGetICoordinateMapper(sensor, &coordMapper);
            if (FAILED(hr)) CI_LOG_E("Failed to call KCBGetICoordinateMapper()");

            hr = KCBGetDepthFrameDescription(sensor, &depthDesc);
            if (SUCCEEDED(hr))
            {
                hr = KCBCreateDepthFrame(depthDesc, &depthFrame);
                depthChannel = Channel16u(depthDesc.width, depthDesc.height,
                    depthDesc.bytesPerPixel * depthDesc.width, 1, depthFrame->Buffer);
            }
            if (FAILED(hr)) CI_LOG_E("Failed to KCBCreateDepthFrame");

            if (option.enableFace)
            {
                for (int i = 0; i < BODY_COUNT; i++)
                {
                    auto& hdFace = hdFaces[i];
                    hr = CreateHighDefinitionFaceFrameSource(rawSensor, &hdFace.frameSource);
                    if (FAILED(hr)) break;
                    
                    hr = hdFace.frameSource->OpenReader(&hdFace.frameReader);
                    if (FAILED(hr)) break;

                    hr = hdFace.frameSource->OpenModelBuilder( FaceModelBuilderAttributes::FaceModelBuilderAttributes_None,
                        &hdFace.modelBuilder);
                    if (FAILED(hr)) break;

                    hr = hdFace.modelBuilder->BeginFaceDataCollection();
                    if (FAILED(hr)) break;

                    hr = CreateFaceAlignment( &hdFace.faceAlignment);
                    if (FAILED(hr)) break;

                    hr = CreateFaceModel(1.0f, FaceShapeDeformations::FaceShapeDeformations_Count, hdFace.deformations, &hdFace.faceModel);
                    if (FAILED(hr)) break;
                }
                if (FAILED(hr)) CI_LOG_E("Failed to setup HD Face");

                hr = GetFaceModelVertexCount(&faceVertexCount); // 1347
                hr = GetFaceModelTriangleCount(&faceIndexCount);
                faceIndexCount *= 3;
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
                    for (int i = 0; i < BODY_COUNT;i++)
                    {
                        Body body;
                        if (!updateBody(srcBodies[i], body)) continue;
                        bodies.push_back(body);

                        if (!option.enableFace) continue;

                        Face face;
                        if (!updateFace(body, hdFaces[i], face)) continue;
                        faces.push_back(face);
                    }

                    // garbage collection
                    for (auto& src : srcBodies)
                    {
                        if (src == nullptr) continue;
                        src->Release();
                    }

                    signalBodyDirty.emit();
                }
            }
        }

        bool updateFace(const Body& body, HDFaceDetail& hdFace, Face& face)
        {
            HRESULT hr = S_OK;

            IHighDefinitionFaceFrameSource* source = hdFace.frameSource;
            IHighDefinitionFaceFrameReader* reader = hdFace.frameReader;

            IHighDefinitionFaceFrame* frame = nullptr;
            hr = reader->AcquireLatestFrame(&frame);
            if (FAILED(hr) || frame == nullptr) return false;

            BOOLEAN isTracked = false;
            hr = frame->get_IsTrackingIdValid(&isTracked);
            if (FAILED(hr))
            {
                frame->Release();
                return false;
            }

            face.id = body.id;

            if (!isTracked)
            {
                source->put_TrackingId(body.id);
            }
            else
            {
                hr = frame->GetAndRefreshFaceAlignmentResult(hdFace.faceAlignment);
                if (SUCCEEDED(hr) && hdFace.faceAlignment != nullptr){
                    // Face Model Building
                    if (!hdFace.produce){
                        std::system("cls");
                        FaceModelBuilderCollectionStatus collection;
                        hr = hdFace.modelBuilder->get_CollectionStatus(&collection);
                        if (collection == FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_Complete){
                            std::cout << "Status : Complete" << std::endl;
                            //cv::putText(bufferMat, "Status : Complete", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                            IFaceModelData* pFaceModelData = nullptr;
                            hr = hdFace.modelBuilder->GetFaceData(&pFaceModelData);
                            if (SUCCEEDED(hr) && pFaceModelData != nullptr){
                                hr = pFaceModelData->ProduceFaceModel(&hdFace.faceModel);
                                if (SUCCEEDED(hr) && hdFace.faceModel != nullptr){
                                    hdFace.produce = true;
                                }
                            }
                            pFaceModelData->Release();
                        }
                        else{
                            std::cout << "Status : " << collection << std::endl;
                            //cv::putText(bufferMat, "Status : " + std::to_string(collection), cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);

                            // Collection Status
                            if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_TiltedUpViewsNeeded){
                                std::cout << "Need : Tilted Up Views" << std::endl;
                                //cv::putText(bufferMat, "Need : Tilted Up Views", cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                            }
                            else if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_RightViewsNeeded){
                                std::cout << "Need : Right Views" << std::endl;
                                //cv::putText(bufferMat, "Need : Right Views", cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                            }
                            else if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_LeftViewsNeeded){
                                std::cout << "Need : Left Views" << std::endl;
                                //cv::putText(bufferMat, "Need : Left Views", cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                            }
                            else if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_FrontViewFramesNeeded){
                                std::cout << "Need : Front ViewFrames" << std::endl;
                                //cv::putText(bufferMat, "Need : Front ViewFrames", cv::Point(50, 100), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                            }

                            // Capture Status
                            FaceModelBuilderCaptureStatus capture;
                            hr = hdFace.modelBuilder->get_CaptureStatus(&capture);
                            switch (capture){
                            case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_FaceTooFar:
                                std::cout << "Error : Face Too Far from Camera" << std::endl;
                                //cv::putText(bufferMat, "Error : Face Too Far from Camera", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                                break;
                            case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_FaceTooNear:
                                std::cout << "Error : Face Too Near to Camera" << std::endl;
                                //cv::putText(bufferMat, "Error : Face Too Near to Camera", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                                break;
                            case FaceModelBuilderCaptureStatus_MovingTooFast:
                                std::cout << "Error : Moving Too Fast" << std::endl;
                                //cv::putText(bufferMat, "Error : Moving Too Fast", cv::Point(50, 150), cv::FONT_HERSHEY_SIMPLEX, 1.0f, static_cast<cv::Scalar>(color[count]), 2, CV_AA);
                                break;
                            default:
                                break;
                            }
                        }
                    }

                    // HD Face Points
                    vector<CameraSpacePoint> facePoints(faceVertexCount);
                    hr = hdFace.faceModel->CalculateVerticesForAlignment(hdFace.faceAlignment, faceVertexCount, facePoints.data());
                    if (SUCCEEDED(hr)){
                        for (int point = 0; point < faceVertexCount; point++){
                            ColorSpacePoint colorSpacePoint;
                            //hr = pCoordinateMapper->MapCameraPointToColorSpace(facePoints[point], &colorSpacePoint);
                            //if (FAILED(hr)){
                            //    int x = static_cast<int>(colorSpacePoint.X);
                            //    int y = static_cast<int>(colorSpacePoint.Y);
                            //    if ((x >= 0) && (x < width) && (y >= 0) && (y < height)){
                            //        //cv::circle(bufferMat, cv::Point(static_cast<int>(colorSpacePoint.X), static_cast<int>(colorSpacePoint.Y)), 5, static_cast<cv::Scalar>(color[count]), -1, CV_AA);
                            //    }
                            //}
                        }
                    }
                }
            }

            return true;
        }

        bool updateBody(IBody* src, Body& dst)
        {
            HRESULT hr = S_OK;

            if (src == nullptr) return false;

            BOOLEAN isTracked = false;
            hr = src->get_IsTracked(&isTracked);
            if (FAILED(hr) || !isTracked) return false;

            src->get_TrackingId(&dst.id);

            Joint srcJoints[JointType_Count] = {};
            if (FAILED(src->GetJoints(JointType_Count, srcJoints)))
            {
                return false;
            }

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
                dst.joints[mapping.first].pos3d = toCi(srcJoints[mapping.second].Position);
                DepthSpacePoint depthPoint = { 0 };
                coordMapper->MapCameraPointToDepthSpace(srcJoints[mapping.second].Position, &depthPoint);
                depthPoint.X /= depthDesc.width;
                depthPoint.Y /= depthDesc.height;
                dst.joints[mapping.first].pos2d = toCi(depthPoint);
            }
            
            return true;
        }
    };

    struct DeviceKinect1 : public Device
    {
        static uint32_t getDeviceCount()
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

        ivec2 getDepthSize() const
        {
            return{ depthDesc.dwWidth, depthDesc.dwHeight };
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
                    signalBodyDirty.emit();
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

        ivec2 getDepthSize() const
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

    uint32_t Device::getDeviceCount(DeviceType type)
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
