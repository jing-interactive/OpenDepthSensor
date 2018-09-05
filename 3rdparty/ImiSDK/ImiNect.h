/********************************************************************************
  Copyright (c) 2015-2016 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : ImiNect.h
  @Author        : Chen Shangwei
  @Date          : 2015-05-12
  @Description   : ImiNect Application Develop API
  @Version       : 0.1.0

  @History       :
  1.2015-05-12 Chen Shangwei Created file
********************************************************************************/
#ifndef _IMI_NECT_H_
#define _IMI_NECT_H_

#include <ImiDefines.h>
#include <ImiPlatform.h>
#include <ImiUpgrade.h>

/*! \addtogroup iminect
* @{
*/
//System APIs

/**
 * @brief Initialize ImiSDK, Should Called at first

 * @param  const ImiCallbacks* pCallbacks: the pointer to ImiCallbacks
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiInitialize(const ImiCallbacks* pCallbacks);

/**
 * @brief Initialize ImiSDK, if change Driver Should Called at first

 * @param  ImiDriverInfo mDriverInfo:  DriverInfo
 * @param  const ImiCallbacks* pCallbacks: the pointer to ImiCallbacks
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiInitialize2(ImiDriverInfo* mDriverInfo, const ImiCallbacks* pCallbacks);

/**
 * @brief Destroy ImiSDK, Close the device if opened

 * @param  None
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiDestroy();

//Deivce APIs
/**
 * @brief  Get the connected ImiNect list

 * @param  ImiDeviceAttribute **pDeviceList: the pointer to ImiNect device list
 * @param  int32_t* pDeviceCount: the pointer to ImiNect device count
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiGetDeviceList(ImiDeviceAttribute** pDeviceList, uint32_t* pDeviceCount);

//Deivce APIs
/**
 * @brief  release the memory of ImiNect device list

 * @param  ImiDeviceAttribute **pDeviceList: the pointer to ImiNect device list
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiReleaseDeviceList(ImiDeviceAttribute** pDeviceList);

/**
 * @brief Open an ImiNect by specified device uri

 * @param  const char* pDeviceUri: device uri in system, open the frist device if uri is null.
 * @param  ImiDeviceHandle* pDevice: Device hanlde  to assign opened device to
 * @param  int32_t  reserve: Reserve Parameter, not used yet, any value is ok
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiOpenDevice(const char* pDeviceUri, ImiDeviceHandle* pDevice, int32_t reserve);

/**
 * @brief Open an ImiNect by specified file descriptor and usb fs path, Only available in Android

 * @param  uint32_t fd: device file descriptor
 * @param  const char* pUsbFsPath: the pointer of usb file path. ex: /dev/bus/usb/02
 * @param  ImiDeviceHandle* pDevice: Device hanlde  to assign opened device to
 * @param  int32_t  reserve: Reserve Parameter, not used yet, any value is ok
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiOpenDevice2(uint32_t fd, const char* pUsbFsPath, ImiDeviceHandle* pDevice, int32_t reserve);

/**
 * @brief Close an opened iminect device

 * @param  ImiDeviceHandle pDevice: Device to close
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiCloseDevice(ImiDeviceHandle device);

/**
 * @brief Upgrade Imi devices, 
    When Application call this function, will start upgrade and notify user the progress by the
    callback function ImiDeviceUpgradeStepPrompt

 * @param  ImiDeviceHandle pDevice: Device to upgrade
 * @param  ImiBOOL bUpgrade:  IMI_TRUE: upgrade,  IMI_FALSE: not upgrade
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetDeviceUpgrade(ImiDeviceHandle device, ImiBOOL bUpgrade);

/**
 * @brief  Modify property of a opened iminect

 * @param  ImiDeviceHandle device: Device to modify
 * @param  uint32_t propertyId: property to  modify
 * @param  void* pData: the pointer of property value
 * @param  uint32 dataSize: property value size in Byte
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetDeviceProperty(ImiDeviceHandle device, uint32_t propertyId, const void* pData, uint32_t dataSize);

/**
 * @brief  Get property of a opened iminect

 * @param  ImiDeviceHandle device: Device to  view property
 * @param  uint32_t propertyId: property to  get
 * @param  void* pData: where property value to assign
 * @param  uint32* pDataSize: property value size in Byte
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiGetDeviceProperty(ImiDeviceHandle device, uint32_t propertyId, void* pData, uint32_t* pDataSize);

/**
 * @brief  set the registration status of a opened iminect

 * @param  ImiDeviceHandle device: the device handle
 * @param  ImiBOOL bEnable: IMI_TRUE: enable registration; IMI_FALSE: disable registration; registration status of skeleton is enable by default 
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetImageRegistration(ImiDeviceHandle device, ImiBOOL bEnable);


 /**
 * @brief  get the registration status of a opened iminect

 * @param  ImiDeviceHandle device: the device handle
 * @return IMI_TRUE: registration is enable, IMI_FALSE : registration is disable.
 **/
IMINECT_EXP ImiBOOL IMINECT_API imiIsImageRegistrationEnable(ImiDeviceHandle device);

/**
 * @brief  Set Device State Callback Function, 
           callback will be called when any imi device state changed

 * @param  ImiDeviceStateCallback callback: callback will be called when any imi device state changed
 * @param  void* pData: the pointer of User data
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetDeviceStateCallback(ImiDeviceStateCallback callback, void* pData);


//Stream APIs
/**
 * @brief  get the supported frame modes

 * @param  ImiDeviceHandle device: the device handle
 * @param  ImiFrameType frameType: the frame type
 * @param  const ImiFrameMode** pMode: where frame mode list to assign
 * @param  uint32_t* pNumber: where the supported frame mode count to assign
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiGetSupportFrameMode(ImiDeviceHandle device, ImiFrameType frameType, const ImiFrameMode** pMode, uint32_t* pNumber);

/**
 * @brief  set the frame mode by frame type

 * @param  ImiDeviceHandle device: the device handle
 * @param  ImiFrameType frameType: the frame type
 * @param  const ImiFrameMode* pMode: the pointer of frame mode
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetFrameMode(ImiDeviceHandle device, ImiFrameType frameType, ImiFrameMode* pMode);
    
/**
 * @brief  get the current frame mode by frame type 

 * @param  ImiDeviceHandle device: the device handle
 * @param  ImiFrameType frameType: the frame type
 * @return const ImiFrameMode*: the pointer of frame mode
 **/
IMINECT_EXP const ImiFrameMode* IMINECT_API imiGetCurrentFrameMode(ImiDeviceHandle device, ImiFrameType frameType);

/**
 * @brief  Open a stream of type 'frameType'
 * @param  ImiDeviceHandle device: Device to open stream
 * @param  ImiFrameType frameType: Frame type to create, image frame or depth frame
 * @param  ImiNewFrameCallback callback:Function pointer to process new frame event, if NULL, callback will not be set
 * @param  void* pData: User data
 * @param  ImiStreamHandle* pStream: Stream handle to assign new created stream
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiOpenStream(ImiDeviceHandle device, ImiFrameType frameType,
    ImiNewFrameCallback callback, void* pData, ImiStreamHandle* pStream);

/**
 * @brief  Close stream

 * @param  ImiStreamHandle stream: stream to be close
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiCloseStream(ImiStreamHandle stream);

/**
 * @brief   Get the latest frame of stream

 * @param  ImiStreamHandle stream: stream to get frame
 * @param  ImiImageFrame** ppFrame : Pointer of frame pointer to assign the new frame pointer
 * @param  int32_t timeout: Max time to wait utill get the frame
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiReadNextFrame(ImiStreamHandle stream, ImiImageFrame** ppFrame, int32_t timeout);

/**
 * @brief   Release a frame ref

 * @param  ImiImageFrame** ppFrame : Pointer of frame pointer to release ref
 * @return None
 **/
IMINECT_EXP int32_t IMINECT_API imiReleaseFrame(ImiImageFrame** pFrame);

/**
 * @brief  Convert coordinate depth to color

 * @param  ImiCoordinateConvertMode convertMode: convert mode
 * @param  uint32_t depthX：depth x coordinate
 * @param  uint32_t depthY: depth y coordinate
 * @param  uint16_t depthZ: depth z coordinate
 * @param  uint32_t* pImageX:Pointer to Color x coordinate
 * @param  uint32_t* pImageY:Porinter to Color y coordinate
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiConvertCoordinateDepthToColor(ImiCoordinateConvertMode convertMode, uint32_t depthX, uint32_t depthY, uint16_t depthZ, uint32_t* pImageX, uint32_t* pImageY);

/**
 * @brief  Convert coordinate depth to world

 * @param  ImiVector4* pDst: the world coordinate
 * @param  const ImiVector4I* pSrc：the depth coordinate
 * @param  int32_t height: the height
 * @param  int32_t width: the width
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiConvertCoordinateDepthToWorld(ImiVector4* pDst, const ImiVector4I* pSrc, int32_t height, int32_t width);

/**
 * @brief  Convert coordinate world to depth

 * @param  ImiVector4* pDst: the depth coordinate
 * @param  const ImiVector4I* pSrc：the world coordinate
 * @param  int32_t height: the height
 * @param  int32_t width: the width
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiConvertCoordinateWorldToDepth(ImiVector4I* pDst, const ImiVector4* pSrc, int32_t height, int32_t width);


/**
 * @brief  Convert depth to point cloud

 * @param  const ImiImageFrame* pDepth : Pointer of frame
 * @param  float factor : camera factor, if the output point in meters , use 1000.0
 * @param  float fx : camera internal reference, the x-axis focal length expressed in pixel units
 * @param  float fy : camera internal reference, the y-axis focal length expressed in pixel units
 * @param  float cx : camera internal reference, the x-axis coordinate value of principal point that is usually at the image center
 * @param  float cy : camera internal reference, the y-axis coordinate value of principal point that is usually at the image center
 * @param  float* pPointClouds: the pointer of the point cloud buffer, the point size is pDepth->width * pDepth->height
 * @return 0:success, < 0:error
 * @ps: if any one of (factor, fx, fy, cx, cy) <= 0, these use default parameters
 **/
IMINECT_EXP int32_t IMINECT_API imiConvertDepthToPointCloud(const ImiImageFrame* pDepth, float factor, float fx, float fy, float cx, float cy, ImiPoint3D* pPointClouds);


/**
 * @brief   Wait for multiple streams

 * @param  ImiStreamHandle* pStream: Pointer of streams
 * @param  int32_t numStreams: number of streams
 * @param  int32_t* pStreamIndex: the index of the stream that receives a frame
 * @param  int32_t timeout: Max time to wait for
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiWaitForStreams(ImiStreamHandle* pStream, int32_t numStreams, int32_t* pStreamIndex, int32_t timeout);

/**
 * @brief  Create Recorder

 * @param  const char* pFileToSave: the file to save data to
 * @param  ImiRecordHandle* pRecordHandle: recordHandle to assign new recordHandle
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiCreateRecorder(const char* pFileToSave, ImiRecordHandle* pRecorder);

/**
 * @brief  Attach Stream to Recorder

 * @param  ImiRecordHandle recorder: the recorder handle
 * @param  ImiStreamHandle stream: the stream handle
 * @param  ImiDataType dataType: the data type
 * @param  ImiBOOL bCompress: whether the compression
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiRecorderAttachStream(ImiRecordHandle recorder, ImiStreamHandle stream, ImiDataType dataType, ImiBOOL bCompress);

/**
 * @brief  Start Recorder

 * @param  ImiRecordHandle recorder: the recorder handle
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiRecorderStart(ImiRecordHandle recorder);

/**
 * @brief  Stop Recorder

 * @param  ImiRecordHandle recorder: the recorder handle
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiRecorderStop(ImiRecordHandle recorder);

/**
 * @brief  Destroy Recorder

 * @param  ImiRecordHandle recorder: the recorder handle
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiDestroyRecorder(ImiRecordHandle recorder);

//Maintaince APIs
/**
 * @brief   Get current SDK version

 * @param  ImiDeviceHandle device: the device handle 
 * @param  ImiVersions* pImiVersion: where the version to assign.
 * @return  0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiGetVersion(ImiDeviceHandle device, ImiVersions* pImiVersion);

/**
 * @brief  Get the errno of last failure operation

 * @param  None
 * @return An error no
 **/
IMINECT_EXP int32_t IMINECT_API imiGetLastError();

/**
 * @brief  Get the error information of the error code :nErrorCode

 * @param  nErrorCode:error code
 * @return Error information
 **/
IMINECT_EXP const char* IMINECT_API imiGetErrorString(int32_t nErrorCode);

/**
 * @brief   Set the log output dir

 * @param  pOutputDir: path to Save Log, end with '/0'.
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetLogOutputDir(const char* pOutputDir);

/**
 * @brief Set imisdk log level
 *
 * @param level log level to enable,
 * 0:Verbose, 1:Information, 2:Warning, 3:Error
 * @return 0:success, < 0 :error
 */
IMINECT_EXP int32_t IMINECT_API imiSetLogLevel(uint32_t level);

/**
 * @brief Take Photo
 * @param const char* pBmpImagePath: the path bmp image to save.if pBmpImagePath is NULL, save bmp image to workdirectory and set name like 20161212090807.bmp
 * @return 0:success, < 0 :error
 */
IMINECT_EXP int32_t IMINECT_API imiTakePhoto(const char* pBmpImagePath);

/*! @} */
#endif // _IMI_NECT_H_
