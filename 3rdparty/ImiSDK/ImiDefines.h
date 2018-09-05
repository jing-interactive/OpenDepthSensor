/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : ImiDefines.h
  @Author        : Chen Shangwei
  @Date          : 2015-05-27
  @Description   : Defines data structs used in IMI API
  @Version       : 0.1.0

  @History       :
  1.2015-05-27 Chen Shangwei Created file

********************************************************************************/

#ifndef _IMI_DEFINES_H_
#define _IMI_DEFINES_H_

#include <stdint.h>
#include <ImiProperties.h>

#ifdef __cplusplus
extern "C" {
#endif


//types
struct ImiDevice;
struct ImiStream;
struct ImiRecord;
typedef struct ImiDevice* ImiDeviceHandle;
typedef struct ImiStream* ImiStreamHandle;
typedef struct ImiRecord* ImiRecordHandle;

//basic enums
#define	IMI_DEVICE_CAMERA  (1 << 0)
#define	IMI_DEVICE_AUDIO   (1 << 1)

typedef uint32_t ImiBOOL;
#define IMI_TRUE    1
#define IMI_FALSE   0

typedef enum {
	IMI_DRIVER_NONE             = 0x00,
	IMI_DRIVER_USB               = 0x01,
	IMI_DRIVER_FILE               = 0x02,
	IMI_DRIVER_NET               = 0x03,
} ImiDriverType;

typedef uint32_t ImiFrameType;
enum {
	IMI_DEPTH_FRAME               = 0x00,
	IMI_DEPTH_SKELETON_FRAME      = 0x01,
	IMI_USER_INDEX_SKELETON_FRAME = 0x02,
	IMI_SKELETON_FRAME            = 0x03,
	IMI_COLOR_FRAME               = 0x04,
	IMI_IR_FRAME                   = 0x06,
};

typedef enum {
	IMI_COLOR_DATA               = 0x00,
	IMI_DEPTH_DATA               = 0x04,
	IMI_DEPTH_ORG_DATA               = 0x05,
	IMI_DEPTH_SKELETON_DATA               = 0x08,
	IMI_USER_INDEX_SKELETON_DATA               = 0x0c,
	IMI_SKELETON_DATA               = 0x10
} ImiDataType;

typedef enum {
    IMI_DEVICE_STATE_CONNECT 	= 0,
    IMI_DEVICE_STATE_DISCONNECT = 1
} ImiDeviceState;

typedef uint32_t ImiCoordinateConvertMode;
enum {
    IMI_COORDINATE_VGATOVGA           = 0,
    IMI_COORDINATE_VGATO720P          = 1,
    IMI_COORDINATE_VGATO1080P         = 2,
	
	IMI_COORDINATE_QVGATOVGA          = 3,
	IMI_COORDINATE_QVGATO720P         = 4,
   	IMI_COORDINATE_QVGATO1080P        = 5
};

//basic struct
typedef struct tagImiDriverInfo {
	ImiDriverType		driverType;
	int32_t		 netListenPort;        // required when driverType is IMI_DRIVER_NET
	char			recordFilePath[255];  // required when driverType is IMI_DRIVER_FILE
} ImiDriverInfo;

#define MAX_SN_SIZE 64
typedef struct tagImiDeviceAttribute {
	uint16_t vendorId;
	uint16_t productId;
	uint32_t deviceAddress;
	char     serialNumber[MAX_SN_SIZE];
	char     uri[255];
} ImiDeviceAttribute;

typedef struct tagVector4I {
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t w;
} ImiVector4I;

typedef struct tagVector4 {
	float x;
	float y;
	float z;
	float w;
} ImiVector4;

typedef struct tagPoint3D {
    float x;
    float y;
    float z;
}ImiPoint3D;

typedef int16_t ImiDepthPixel;
typedef struct tagImiFrame {
	ImiPixelFormat pixelFormat;
    ImiFrameType   type;
    uint32_t       frameNum;
    uint64_t       timeStamp;

    uint32_t       fps;
    int32_t        width;
    int32_t        height;

    void*		   pData;//depth color pixel data, if not null
	void*          pSkeletonData;//skeleton frame if not null
    uint32_t	   size;
} ImiImageFrame;

typedef struct tagImiFrameMode {
    ImiPixelFormat pixelFormat;
    int16_t resolutionX;
    int16_t resolutionY;
    int8_t  bitsPerPixel;
    int8_t  framerate;
} ImiFrameMode;

#if defined(_WIN32)
typedef void (_stdcall * ImiNewFrameCallback) (ImiStreamHandle stream, void* pUserData);
typedef void (_stdcall * ImiDeviceStateCallback) (const char* deviceUri, ImiDeviceState deviceState, void* pUserData);
#else
typedef void (* ImiNewFrameCallback) (ImiStreamHandle stream, void* pUserData);
typedef void (* ImiDeviceStateCallback) (const char* deviceUri, ImiDeviceState deviceState, void* pUserData);
#endif

#ifdef __cplusplus
}
#endif
#endif // _IMI_DEFINES_H_
