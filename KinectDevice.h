#include "cinder/Cinder.h"
#include "cinder/Channel.h"
#include "cinder/Function.h"

namespace Kinect
{
    typedef std::shared_ptr<struct Device> DeviceRef;

    struct Device
    {
#ifdef KINECT_V2
        static DeviceRef createV2();
#else
        static DeviceRef createV1();
#endif

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        ci::Channel16u depthChannel;
        ci::signals::signal<void()> signalDepthDirty;

        struct Skeleton
        {
            int id;
            ci::vec2 pos;

            struct Joint
            {
                enum
                {
                    LEFT_HAND,
                    RIGHT_HAND,
                    HEAD,
                    JOINT_COUNT,
                };
                ci::vec2 pos;
                float confidence;
            };

            Joint joints[Joint::JOINT_COUNT];
        };
        std::vector<Skeleton> skeletons;
        ci::signals::signal<void()> signalSkeletonDirty;
    };
}
