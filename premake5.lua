-- https://github.com/premake/premake-core/wiki

local action = _ACTION or ""

solution "Cinder-DepthSensor"
    location (action)
    configurations { "Debug", "Release" }
    platforms {"x64", "x86"}
    language "C++"

    configuration "vs*"
        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_DEPRECATE",
        }

        disablewarnings {
            "4244",
            "4305",
            "4996",
        }

        flags {
            "StaticRuntime",   
        }

        configuration "x86"
            libdirs {
                "lib/msw/x86",
            }
            targetdir ("lib/msw/x86")

        configuration "x64"
            libdirs {
                "lib/msw/x64",
            }
            targetdir ("lib/msw/x64")

    configuration "macosx"
        sysincludedirs {
            "include",
            "../../include",
            "3rdparty",
            "3rdparty/librealsense/include",
            "3rdparty/v1/sdk/inc",
            "3rdparty/v2/sdk/inc",
            "3rdparty/openni2/include",
        }

        includedirs {
        }

    flags {
        "MultiProcessorCompile"
    }

    cppdialect "C++11"

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols"}
        targetsuffix "-d"

    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize"}

    project "Cinder-DepthSensor"
        kind "StaticLib"

        includedirs {
            "include",
            "../../include",
            "3rdparty",
            "3rdparty/librealsense/include",
            "3rdparty/v1/sdk/inc",
            "3rdparty/v2/sdk/inc",
            "3rdparty/openni2/include",
        }

        files {
            "include/*",
            "src/*",
            "3rdparty/v1/**",
            "3rdparty/v2/**",
            "3rdparty/openni2/**",
            "3rdparty/librealsense/include/**",
            "3rdparty/librealsense/src/*",
        }

        configuration "vs*"
            defines {
                "RS_USE_WMF_BACKEND",
            }

        configuration "macosx"
            defines {
                "RS_USE_LIBUVC_BACKEND",
            }

