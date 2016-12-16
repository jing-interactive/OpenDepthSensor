#include "cinder/Cinder.h"
#include "cinder/Quaternion.h"
#include "cinder/Surface.h"
#include "cinder/Function.h"
#include "cinder/Signals.h"

#include <vector>

namespace ds
{
    typedef std::shared_ptr<struct Device> DeviceRef;

    enum DeviceType
    {
        Kinect1 = 0,
        Kinect2 = 1,
        RealSense = 2,
        Simulator = 3,
        OpenNI = 4,
        RgbCamera = 5,

        Count,
    };

    struct Body
    {
        uint64_t id;

        enum JointType
        {
            HIP_CENTER,
            SPINE,
            SHOULDER_CENTER,
            NECK,               // V2 only
            HEAD,
            SHOULDER_LEFT,
            ELBOW_LEFT,
            WRIST_LEFT,
            HAND_LEFT,
            SHOULDER_RIGHT,
            ELBOW_RIGHT,
            WRIST_RIGHT,
            HAND_RIGHT,
            HIP_LEFT,
            KNEE_LEFT,
            ANKLE_LEFT,
            FOOT_LEFT,
            HIP_RIGHT,
            KNEE_RIGHT,
            ANKLE_RIGHT,
            FOOT_RIGHT,
            HAND_TIP_LEFT,      // V2 only
            HAND_THUMB_LEFT,    // V2 only
            HAND_TIP_RIGHT,     // V2 only
            HAND_THUMB_RIGHT,   // V2 only

            JOINT_COUNT,
        };

        struct Joint
        {
            ci::vec3 pos3d; // view coordinate, in meters
            ci::vec2 pos2d; // depth image coordinate [0, 1] * [0, 1]
        };

        Joint joints[JOINT_COUNT];
    };

    struct Face
    {
        uint64_t id;
        ci::vec3 pos;
        ci::quat orientation;
        std::vector<ci::vec3> vertices;
        static std::vector<uint32_t> indices; // shared by each face
    };

    struct Option
    {
        int deviceId = 0;
        bool enableColor = false;
        bool enableDepth = true;
        bool enablePointCloud = false;
        bool enableBody = false;
        bool enableBodyIndex = false;
        bool enableInfrared = false;
        bool enableAudio = false;
        bool enableFace = false;
    };

    struct Device
    {
        Option option;

        static uint32_t getDeviceCount(DeviceType type);
        static DeviceRef create(DeviceType type, Option option = Option());

        virtual bool isValid() const = 0;
        virtual ci::ivec2 getDepthSize() const = 0;
        virtual ci::ivec2 getColorSize() const = 0;
        virtual float getDepthToMmScale()
        {
            return 1.0f;
        }

        ci::Channel16u depthChannel;
        std::vector<ci::vec3> pointCloudXYZ;
        std::vector<ci::vec2> pointCloudUV;
        ci::signals::Signal<void()> signalDepthDirty;

        ci::Channel16u infraredChannel;
        ci::signals::Signal<void()> signalInfraredDirty;

        ci::Surface8u colorSurface;
        ci::signals::Signal<void()> signalColorDirty;

        std::vector<Body> bodies;
        ci::signals::Signal<void()> signalBodyDirty;

        std::vector<Face> faces;
        ci::signals::Signal<void()> signalFaceDirty;

        ci::signals::Signal<void()> signaldepthToCameraTableDirty;
        ci::Surface32f depthToCameraTable;

        ci::signals::Signal<void()> signalDepthToColorTableDirty;
        ci::Surface32f depthToColorTable;
    };
}
