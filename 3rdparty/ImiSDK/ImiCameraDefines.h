#ifndef _IMI_CAMERA_DEFINES_H_
#define _IMI_CAMERA_DEFINES_H_

#include <stdint.h>

//Api Export
#if !defined(IMICAMERA_API_EXPORT)
#if defined(_WIN32)
#define IMICAMERA_API_EXPORT __declspec(dllexport)
#elif defined (ANDROID) || defined (__linux__)
#define IMICAMERA_API_EXPORT __attribute__ ((visibility("default")))
#else
#	Unsupported Platform!
#endif
#endif

#ifdef __cplusplus
#	define IMICAMERA_EXP extern "C" IMICAMERA_API_EXPORT
#else // __cplusplus
#	define IMICAMERA_EXP IMICAMERA_API_EXPORT
#endif  // __cplusplus


typedef uint32_t ImiCAMBOOL;
#define IMI_CAM_TRUE    1
#define IMI_CAM_FALSE   0

struct ImiCamera;
typedef struct ImiCamera* ImiCameraHandle;


typedef enum
{
	CAMERA_PIXEL_FORMAT_RGB888        = 0x00,
	CAMERA_PIXEL_FORMAT_MJPEG         = 0x01,
	CAMERA_PIXEL_FORMAT_YUYV          = 0x02,
	CAMERA_PIXEL_FORMAT_YUV420SP      = 0x03

}ImiCameraPixelFormat;


typedef struct tagImiCameraFrame
{
	ImiCameraPixelFormat      pixelFormat;
	uint32_t                  frameNum;
	uint64_t                  timeStamp;

	uint32_t                  fps;
	int32_t                   width;
	int32_t                   height;

	void*					  pData;
	uint32_t	              size;
}ImiCameraFrame;

typedef struct tagCameraFrameMode
{
	ImiCameraPixelFormat pixelFormat;
	int32_t resolutionX;
	int32_t resolutionY;
	int32_t fps;
}ImiCameraFrameMode;


typedef enum
{
	IMI_CAM_PROPERTY_COLOR_AE_MODE = 0x00,                   // value type: uint8_t, 1:manual exposure time£¬8:auto exposure time
	IMI_CAM_PROPERTY_COLOR_EXPOSURE_ABSOLUTE_TIME = 0x01,    // value type: uint32_t, >= 1
	
}ImiCamPropertyEnum;

#endif
