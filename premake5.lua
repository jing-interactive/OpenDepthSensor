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
        -- sysincludedirs {

        -- }
        includedirs {
        }

    flags {
        "MultiProcessorCompile"
    }

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
            "src/librealsense/include",
            "src/v1/sdk/inc",
            "src/v2/sdk/inc",
            "src/openni2/include",
        }

        files {
            "include/*",
            "src/**",
        }

        defines {
            "RS_USE_WMF_BACKEND",
        }

        removefiles {
            "src/librealsense/src/libuvc/*",
        }

