#include "cinder/Cinder.h"
#include "cinder/Channel.h"
#include "cinder/Function.h"

namespace Kinect
{
    typedef std::shared_ptr<struct Device> DeviceRef;

    struct Body
    {
        ci::uint64_t id;

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

    struct Device
    {
        struct Option
        {
            Option()
            {
                enableColor = false;
                enableDepth = true;
                enableBody = false;
                enableBodyIndex = false;
                enableInfra = false;
                enableAudio = false;
            }
            bool enableColor;
            bool enableDepth;
            bool enableBody;
            bool enableBodyIndex;
            bool enableInfra;
            bool enableAudio;
        };
        Option option;

#ifdef KINECT_V2
        static DeviceRef createV2(Option option = Option());
#else
        static DeviceRef createV1(Option option = Option());
#endif

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        ci::Channel16u depthChannel;
        ci::signals::signal<void()> signalDepthDirty;

        std::vector<Body> bodies;
        ci::signals::signal<void()> signalBodyDirty;
    };
}
