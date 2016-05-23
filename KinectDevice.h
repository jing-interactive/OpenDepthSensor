#include "cinder/Cinder.h"
#include "cinder/Channel.h"
#include "cinder/Function.h"
#include "cinder/Signals.h"

namespace Kinect
{
    typedef std::shared_ptr<struct Device> DeviceRef;

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

    enum DeviceType
    {
        Kinect1,
        Kinect2,
        Simulator,
        OpenNI,
        OpenNI2,
        Count,
    };

    struct Device
    {
        struct Option
        {
            Option()
            {
                deviceId = 0;
                enableColor = false;
                enableDepth = true;
                enableBody = false;
                enableBodyIndex = false;
                enableInfra = false;
                enableAudio = false;
            }
            int deviceId;
            bool enableColor;
            bool enableDepth;
            bool enableBody;
            bool enableBodyIndex;
            bool enableInfra;
            bool enableAudio;
        };
        Option option;

        static int getDeviceCount(DeviceType type);
        static DeviceRef create(DeviceType type, Option option = Option());

        virtual bool isValid() const = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        ci::Channel16u depthChannel;
        ci::signals::Signal<void()> signalDepthDirty;

        std::vector<Body> bodies;
        ci::signals::Signal<void()> signalBodyDirty;
    };
}
