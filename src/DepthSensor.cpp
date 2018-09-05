#include "DepthSensor.h"

using namespace ci;
using namespace std;

namespace ds
{
    const char* strFromType(DeviceType type)
    {
        switch (type)
        {
#define ITEM(name, id)                                                                             \
    case name:                                                                                     \
        return #name;
#include "Sensors.inl"
#undef ITEM
        }

        return "Unknown sensor";
    }

#define ITEM(name, id) uint32_t get##name##Count();
#include "Sensors.inl"
#undef ITEM

    uint32_t Device::getDeviceCount(DeviceType type)
    {
        switch (type)
        {
#define ITEM(name, id)                                                                             \
    case name:                                                                                     \
        return get##name##Count();
#include "Sensors.inl"
#undef ITEM
        }

        return 0;
    }

#define ITEM(name, id) DeviceRef create##name(Option option);
#include "Sensors.inl"
#undef ITEM

    DeviceRef Device::create(DeviceType type, Option option)
    {
        if (option.enablePointCloud)
            option.enableDepth = true;

        switch (type)
        {
#define ITEM(name, id)                                                                             \
    case name:                                                                                     \
        return create##name(option);
#include "Sensors.inl"
#undef ITEM
        }

        return DeviceRef(nullptr);
    }
} // namespace ds
