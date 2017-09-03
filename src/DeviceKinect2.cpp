#include "DepthSensor.h"

#ifdef Kinect2_Enabled

#include "v2/src/KCBv2Lib.h"
#include "Kinect.Face.h"
#include "NuiKinectFusionApi.h"

#include "cinder/app/app.h"
#include "cinder/Log.h"
#include "cinder/msw/CinderMsw.h"

#pragma comment (lib, "Kinect20.Face.lib")

using namespace ci;
using namespace ci::app;
using namespace std;

namespace ds
{
#define SCOPED_COM_OBJECT(objName) auto scoped##__LINE__## = msw::makeComUnique(objName);

    vector<uint32_t> Face::indices;

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

    struct DeviceKinect2 : public Device
    {
        KCBDepthFrame* depthFrame = nullptr;
        KCBFrameDescription depthDesc = {};

        KCBInfraredFrame* infraredFrame = nullptr;
        KCBFrameDescription infraredDesc = {};

        KCBColorFrame* colorFrame = nullptr;
        KCBFrameDescription colorDesc = {};

        ICoordinateMapper* coordMapper = nullptr;
        int sensor = KCB_INVALID_HANDLE;
        IKinectSensor*  rawSensor = nullptr;

        CameraIntrinsics cameraIntrinsics;

        struct HDFaceInternal
        {
            // https://github.com/UnaNancyOwen/Kinect2Sample/blob/master/Sample/Face/Face.cpp
            IHighDefinitionFaceFrameSource* frameSource = nullptr;
            IHighDefinitionFaceFrameReader* frameReader = nullptr;
            IFaceModelBuilder* modelBuilder = nullptr;
            bool isModelBuilt = false;
            IFaceAlignment* faceAlignment = nullptr;
            IFaceModel* faceModel = nullptr;
            float deformations[FaceShapeDeformations::FaceShapeDeformations_Count];
        };
        HDFaceInternal hdFaces[BODY_COUNT] = {};

        vector<ColorSpacePoint> depthToColorArray;

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

            if (infraredFrame != nullptr)
            {
                KCBReleaseDepthFrame(&infraredFrame);
            }

            if (colorFrame != nullptr)
            {
                KCBReleaseColorFrame(&colorFrame);
            }

            msw::ComDelete(coordMapper);
            if (option.enableFace)
            {
                // TODO: apply SCOPED_COM_OBJECT
                for (int i = 0; i < BODY_COUNT; i++)
                {
                    msw::ComDelete(hdFaces[i].frameSource);
                    msw::ComDelete(hdFaces[i].frameReader);
                    msw::ComDelete(hdFaces[i].modelBuilder);
                    msw::ComDelete(hdFaces[i].faceAlignment);
                    msw::ComDelete(hdFaces[i].faceModel);
                }
            }
            if (sensor != KCB_INVALID_HANDLE)
            {
                KCBCloseSensor(&sensor);
            }
        }

        ivec2 getDepthSize() const
        {
            return{ depthDesc.width, depthDesc.height };
        }

        ivec2 getColorSize() const
        {
            return{ colorDesc.width, colorDesc.height };
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

            ::GetDefaultKinectSensor(&rawSensor);

            if (FAILED(hr))
            {
                CI_LOG_E("Failed to connect to Kinect V2");
                return;
            }

            hr = KCBGetICoordinateMapper(sensor, &coordMapper);
            if (FAILED(hr)) CI_LOG_E("KCBGetICoordinateMapper() fails.");
            coordMapper->GetDepthCameraIntrinsics(&cameraIntrinsics);
            if (FAILED(hr)) CI_LOG_E("GetDepthCameraIntrinsics() fails.");
            focalLength.x = NUI_DEPTH_RAW_WIDTH * NUI_KINECT_DEPTH_NORM_FOCAL_LENGTH_X;
            focalLength.y = NUI_DEPTH_RAW_HEIGHT * NUI_KINECT_DEPTH_NORM_FOCAL_LENGTH_Y;

            if (option.enableDepth)
            {
                hr = KCBGetDepthFrameDescription(sensor, &depthDesc);
                if (SUCCEEDED(hr))
                {
                    hr = KCBCreateDepthFrame(depthDesc, &depthFrame);
                    depthChannel = Channel16u(depthDesc.width, depthDesc.height,
                        depthDesc.bytesPerPixel * depthDesc.width, 1, depthFrame->Buffer);
                }
                if (FAILED(hr)) CI_LOG_E("KCBCreateDepthFrame() fails.");
            }    

            if (option.enableInfrared)
            {
                hr = KCBGetInfraredFrameDescription(sensor, &infraredDesc);
                if (SUCCEEDED(hr))
                {
                    hr = KCBCreateInfraredFrame(infraredDesc, &infraredFrame);
                    if (!option.enableDepth)
                    {
                        // WAR infrared only mode
                        depthDesc = infraredDesc;
                    }
                    infraredChannel = Channel16u(infraredDesc.width, infraredDesc.height,
                        infraredDesc.bytesPerPixel * infraredDesc.width, 1, infraredFrame->Buffer);
                }
                if (FAILED(hr)) CI_LOG_E("KCBCreateInfraredFrame() fails.");
            }

            if (option.enableColor)
            {
                hr = KCBGetColorFrameDescription(sensor, ColorImageFormat_Bgra, &colorDesc);
                if (SUCCEEDED(hr))
                {
                    hr = KCBCreateColorFrame(ColorImageFormat_Bgra, colorDesc, &colorFrame);
                    colorSurface = Surface8u(colorFrame->Buffer, colorDesc.width, colorDesc.height,
                        colorDesc.bytesPerPixel * colorDesc.width, SurfaceChannelOrder::BGRX);
                }
                if (FAILED(hr)) CI_LOG_E("KCBCreateColorFrame() fails.");
            }

            if (option.enablePointCloud && option.enableColor)
            {
                depthToColorArray.resize(depthDesc.width * depthDesc.height);
                depthToColorTable = Surface32f(depthDesc.width, depthDesc.height, false, SurfaceChannelOrder::RGB);
            }

            if (option.enableFace)
            {
                for (int i = 0; i < BODY_COUNT; i++)
                {
                    auto& hdFace = hdFaces[i];
                    hr = CreateHighDefinitionFaceFrameSource(rawSensor, &hdFace.frameSource);
                    if (FAILED(hr)) break;

                    hr = hdFace.frameSource->OpenReader(&hdFace.frameReader);
                    if (FAILED(hr)) break;

                    hr = hdFace.frameSource->OpenModelBuilder(FaceModelBuilderAttributes::FaceModelBuilderAttributes_None,
                        &hdFace.modelBuilder);
                    if (FAILED(hr)) break;

                    hr = hdFace.modelBuilder->BeginFaceDataCollection();
                    if (FAILED(hr)) break;

                    hr = ::CreateFaceAlignment(&hdFace.faceAlignment);
                    if (FAILED(hr) || hdFace.faceAlignment == nullptr) break;

                    hr = ::CreateFaceModel(1.0f, FaceShapeDeformations::FaceShapeDeformations_Count, hdFace.deformations, &hdFace.faceModel);
                    if (FAILED(hr) || hdFace.faceModel == nullptr) break;
                }
                if (FAILED(hr)) CI_LOG_E("Failed to setup HD Face.");

                // mesh related
                {
                    uint32_t vertexCount;
                    hr = ::GetFaceModelVertexCount(&vertexCount); // 1347
                    for (int i = 0; i < BODY_COUNT; i++)
                    {
                        faces[i].vertices.resize(vertexCount);
                    }

                    uint32_t indexCount;
                    hr = ::GetFaceModelTriangleCount(&indexCount);
                    indexCount *= 3;
                    // index data is static & constant
                    Face::indices.resize(indexCount);
                    ::GetFaceModelTriangles(indexCount, Face::indices.data());
                }
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
                // signalDepthDirty
                if (SUCCEEDED(KCBGetDepthFrame(sensor, depthFrame)))
                {
                    signalDepthDirty.emit();

                    // signalDepthToColorTable
                    if (option.enablePointCloud && option.enableColor)
                    {
                        auto depthPointCount = depthDesc.width * depthDesc.height;
                        HRESULT hr = KCBMapDepthFrameToColorSpace(sensor, depthPointCount, depthChannel.getData(), depthPointCount, depthToColorArray.data());
                        if (SUCCEEDED(hr))
                        {
                            ColorSpacePoint* src = depthToColorArray.data();
                            vec3* dst = (vec3*)depthToColorTable.getData();
                            for (int i = 0; i < depthPointCount; i++)
                            {
                                dst[i].x = src[i].X / colorDesc.width;
                                dst[i].y = src[i].Y / colorDesc.height;
                            }
                            signalDepthToColorTableDirty.emit();
                        }
                    }
                }

                // signalDepthToCameraTableDirty
                if (depthToCameraTable.getWidth() == 0)
                {
                    PointF* table = nullptr;
                    uint32_t count = 0;
                    HRESULT hr = GetDepthFrameToCameraSpaceTable(sensor, &count, &table);
                    if (SUCCEEDED(hr))
                    {
                        depthToCameraTable = Surface32f(depthDesc.width, depthDesc.height, false, SurfaceChannelOrder::RGB);

                        // optimize
                        Surface32f::Iter iter = depthToCameraTable.getIter();

                        size_t i = 0;
                        while (iter.line())
                        {
                            while (iter.pixel())
                            {
                                iter.r() = table[i].X;
                                iter.g() = table[i].Y;
                                iter.b() = 0.0f;
                                ++i;
                            }
                        }
                        signalDepthToCameraTableDirty.emit();
                    }
                }
            }

            // signalInfraredDirty
            if (option.enableInfrared && KCBIsFrameReady(sensor, FrameSourceTypes_Infrared))
            {
                if (SUCCEEDED(KCBGetInfraredFrame(sensor, infraredFrame)))
                {
                    signalInfraredDirty.emit();
                }
            }

            // signalColorDirty
            if (option.enableColor && KCBIsFrameReady(sensor, FrameSourceTypes_Color))
            {
                if (SUCCEEDED(KCBGetColorFrame(sensor, colorFrame)))
                {
                    signalColorDirty.emit();
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
                    for (int i = 0; i < BODY_COUNT; i++)
                    {
                        SCOPED_COM_OBJECT(srcBodies[i]);
                        Body body;
                        if (!updateBody(srcBodies[i], body)) continue;
                        bodies.push_back(body);

                        if (!option.enableFace) continue;

                        Face face;
                        if (!updateFace(body, hdFaces[i], face)) continue;
                        faces.push_back(face);
                    }

                    signalBodyDirty.emit();
                }
            }
        }

        bool updateFace(const Body& body, HDFaceInternal& hdFace, Face& face)
        {
            HRESULT hr = S_OK;

            IHighDefinitionFaceFrameSource* source = hdFace.frameSource;
            IHighDefinitionFaceFrameReader* reader = hdFace.frameReader;

            IHighDefinitionFaceFrame* frame = nullptr;
            hr = reader->AcquireLatestFrame(&frame);
            SCOPED_COM_OBJECT(frame);

            if (FAILED(hr) || frame == nullptr) return false;

            BOOLEAN isTracked = false;
            hr = frame->get_IsTrackingIdValid(&isTracked);
            if (FAILED(hr)) return false;

            face.id = body.id;

            if (!isTracked)
            {
                source->put_TrackingId(body.id);
                return false;
            }

            hr = frame->GetAndRefreshFaceAlignmentResult(hdFace.faceAlignment);
            if (FAILED(hr)) return false;

            if (!hdFace.isModelBuilt)
                buildFaceModel(hdFace);

            // Calculate face points
            hr = hdFace.faceModel->CalculateVerticesForAlignment(hdFace.faceAlignment,
                face.vertices.size(), (CameraSpacePoint*)face.vertices.data());
            if (FAILED(hr)) return false;

            return true;
        }

        void buildFaceModel(HDFaceInternal& hdFace)
        {
            HRESULT hr = S_OK;

            FaceModelBuilderCollectionStatus collection;
            hr = hdFace.modelBuilder->get_CollectionStatus(&collection);
            if (collection == FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_Complete) {
                std::cout << "Status : Complete" << std::endl;
                IFaceModelData* pFaceModelData = nullptr;
                hr = hdFace.modelBuilder->GetFaceData(&pFaceModelData);
                SCOPED_COM_OBJECT(pFaceModelData);

                if (SUCCEEDED(hr) && pFaceModelData != nullptr) {
                    hr = pFaceModelData->ProduceFaceModel(&hdFace.faceModel);
                    if (SUCCEEDED(hr) && hdFace.faceModel != nullptr) {
                        hdFace.isModelBuilt = true;
                    }
                }
            }
            else {
                std::cout << "Status : " << collection << std::endl;

                // Collection Status
                if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_TiltedUpViewsNeeded) {
                    std::cout << "Need : Tilted Up Views" << std::endl;
                }
                else if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_RightViewsNeeded) {
                    std::cout << "Need : Right Views" << std::endl;
                }
                else if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_LeftViewsNeeded) {
                    std::cout << "Need : Left Views" << std::endl;
                }
                else if (collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_FrontViewFramesNeeded) {
                    std::cout << "Need : Front ViewFrames" << std::endl;
                }

                // Capture Status
                FaceModelBuilderCaptureStatus capture;
                hr = hdFace.modelBuilder->get_CaptureStatus(&capture);
                switch (capture) {
                case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_FaceTooFar:
                    std::cout << "Error : Face Too Far from Camera" << std::endl;
                    break;
                case FaceModelBuilderCaptureStatus::FaceModelBuilderCaptureStatus_FaceTooNear:
                    std::cout << "Error : Face Too Near to Camera" << std::endl;
                    break;
                case FaceModelBuilderCaptureStatus_MovingTooFast:
                    std::cout << "Error : Moving Too Fast" << std::endl;
                    break;
                default:
                    break;
                }
            }
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

    uint32_t getKinect2Count()
    {
        return DeviceKinect2::getDeviceCount();
    }

    DeviceRef createKinect2(Option option)
    {
        return DeviceRef(new DeviceKinect2(option));
    }
}

#endif
