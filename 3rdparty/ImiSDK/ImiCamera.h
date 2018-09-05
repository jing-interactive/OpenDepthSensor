/********************************************************************************
Copyright (c) 2015-2017 Huajie IMI Technology Co., Ltd.
All rights reserved.

@File Name    : ImiCamera.h
@Author        : Yang Feiyi
@Date           : 2017-03-24
@Description  : ImiCamera Application Develop API
@Version       : 0.1.0

@History       :
1.2017-03-24 Yang Feiyi Created file
********************************************************************************/
#ifndef _IMI_CAMERA_H_
#define _IMI_CAMERA_H_

#include "ImiCameraDefines.h"

/** 
 * @brief Open the specified camera.
 *
 * @param[in, out] ImiCameraHandle* pCameraDevice: Camera Device handle
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamOpen(ImiCameraHandle* pCameraDevice);

/** 
 * @brief Open the specified camera with pid, vid.
 *
 * @param[in] int32_t vid: Camera Device vid
 * @param[in] int32_t pid: Camera Device Pid
 * @param[in] int32_t fd: Camera Device fd
 * @param[in] int32_t busnum: Camera Device busnum
 * @param[in] int32_t devaddr: Camera Device addr
 * @param[in] const char * usbfs: Camera Device usbfs
 * @param[in, out] ImiCameraHandle* pCameraDevice: Camera Device handle
 *
 * return 0: success, < 0 : error
 */
IMICAMERA_EXP int32_t imiCamOpen2(int32_t vid, int32_t pid, int32_t fd, int32_t busnum, int32_t devaddr, const char *usbfs, ImiCameraHandle* pCameraDevice);

/** 
 * @brief Close Camera by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamClose(ImiCameraHandle cameraDevice);

/** 
 * @brief Get SupportFrameModes by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 * @param[in, out] const ImiCameraFrameMode** pMode: where frame mode list to assign
 * @param[in, out] uint32_t* pNumber: where the supported frame mode count to assign
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamGetSupportFrameModes(ImiCameraHandle cameraDevice, const ImiCameraFrameMode** pMode, uint32_t* pNumber);

/** 
 * @brief Start Camera Stream by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 * @param[in] const ImiCameraFrameMode* pMode: the pointer of frame mode
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamStartStream(ImiCameraHandle cameraDevice, const ImiCameraFrameMode* pMode);

/** 
 * @brief Stop Camera Stream by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamStopStream(ImiCameraHandle cameraDevice);

/** 
 * @brief Get the latest frame of stream by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 * @param[in, out] ImiCameraFrame** pFrame: Pointer of frame pointer to assign the new frame pointer
 * @param[in] uint32_t timeout: Max time to wait utill get the frame, if -1 default wait 1000 ms
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamReadNextFrame(ImiCameraHandle cameraDevice, ImiCameraFrame** pFrame, int32_t timeout);

/** 
 * @brief Release a frame ref.
 *
 * @param[in] ppFrame : Pointer of frame pointer to release ref
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamReleaseFrame(ImiCameraFrame** pFrame);

/** 
 * @brief Set frame Mirror by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 * @param[in] ImiCAMBOOL mirror: whether or not do Mirror
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamSetMirror(ImiCameraHandle cameraDevice, ImiCAMBOOL bMirror);

/** 
 * @brief Set frame Mirror by Camera Device handle.
 *
 * @param[in] ImiCameraHandle cameraDevice: Camera Device handle
 * @param const char* pBmpImagePath: the path bmp image to save.if pBmpImagePath is NULL, save bmp image to workdirectory and set name like 20161212090807.bmp
 *
 * return 0: success, < 0 : error
 **/
IMICAMERA_EXP int32_t imiCamTakePhoto(ImiCameraHandle cameraDevice, const char* pBmpImagePath);

IMICAMERA_EXP int32_t imiCamSetProperty(ImiCameraHandle cameraDevice, uint32_t propertyId, const void* pData, uint32_t dataSize);

IMICAMERA_EXP int32_t imiCamGetProperty(ImiCameraHandle cameraDevice, uint32_t propertyId, void* pData, uint32_t* pDataSize);

#endif
