#include "cinder/Cinder.h"
#include "cinder/Quaternion.h"
#include "cinder/Surface.h"
#include "cinder/Function.h"
#include "cinder/Signals.h"

#include <vector>

#define Simulator_Enabled
#define RgbCamera_Enabled

#ifdef CINDER_MSW_DESKTOP
    //#define Kinect1_Enabled
    //#define Kinect2_Enabled
    //#define RealSense_Enabled
    //#define OpenNI_Enabled
    //#define Imi_Enabled
    #define KinectAzure_Enabled
    //#define Freenect2_Enabled
#endif

#ifdef CINDER_MAC
    #define RealSense_Enabled
#endif
namespace ds
{
    typedef std::shared_ptr<struct Device> DeviceRef;

    enum DeviceType
    {
#define ITEM(name, id) name = id,
#include "Sensors.inl"
#undef ITEM

        Count,
    };

    const char* strFromType(DeviceType type);

    struct Body
    {
        uint64_t id;

        enum JointType
        {
            HIP_CENTER,
            SPINE,
            SHOULDER_CENTER,
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

            // V2+
            NECK,
            HAND_TIP_LEFT,
            HAND_THUMB_LEFT,
            HAND_TIP_RIGHT,
            HAND_THUMB_RIGHT,
            
            // azure only
            NOSE,
            EYE_LEFT,
            EAR_LEFT,
            EYE_RIGHT,
            EAR_RIGHT,

            JOINT_COUNT,
        };

        enum JointConfidence
        {
            JOINT_CONFIDENCE_NONE = 0,          /**< The joint is out of range (too far from depth camera) */
            JOINT_CONFIDENCE_LOW = 1,           /**< The joint is not observed (likely due to occlusion), predicted joint pose */
            JOINT_CONFIDENCE_MEDIUM = 2,        /**< Medium confidence in joint pose. Current SDK will only provide joints up to this confidence level */
            JOINT_CONFIDENCE_HIGH = 3,          /**< High confidence in joint pose. Placeholder for future SDK */

            JOINT_CONFIDENCE_LEVELS_COUNT = 4,  /**< The total number of confidence levels. */
        };

        struct Joint
        {
            ci::vec3 pos3d; // view coordinate, in meters
            ci::vec2 pos2d; // depth image coordinate [0, 1] * [0, 1]
            ci::quat orientation;
            JointConfidence confidence = JOINT_CONFIDENCE_NONE;
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
        ci::signals::Signal<void()> signalDepthDirty;

        ci::Channel16u infraredChannel;
        ci::signals::Signal<void()> signalInfraredDirty;

        ci::Channel8u bodyIndexChannel;
        ci::signals::Signal<void()> signalBodyIndexDirty;

        ci::Surface8u colorSurface;
        ci::signals::Signal<void()> signalColorDirty;

        std::vector<Body> bodies;
        ci::signals::Signal<void()> signalBodyDirty;

        std::vector<Face> faces;
        ci::signals::Signal<void()> signalFaceDirty;

        // pointcloud
        ci::signals::Signal<void()> signalDepthToCameraTableDirty;
        ci::Surface32f depthToCameraTable;

        ci::signals::Signal<void()> signalDepthToColorTableDirty;
        ci::Surface32f depthToColorTable;

        ci::vec2 focalLength;
    };
}
