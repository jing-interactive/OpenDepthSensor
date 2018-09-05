/**************************************************************************
  Copyright (c) 2016 Huajie IMI Technology Co.,Ltd.
  All rights reserved.

  @file   ImiSkeleton.h
  @brief  Imi Skeleton header.

  @date    2016-07-13
  @author  ChenShangwei
  @version 0.1.0

  History:
  1. 2016-07-13, Chenshangwei The initial version
**************************************************************************/

#ifndef _IMI_SKELETON_H_
#define _IMI_SKELETON_H_

#include <ImiPlatform.h>
#include <ImiDefines.h>

/*! \addtogroup imiskeleton
* @{
*/

#define MAX_TRACKED_PEOPLE_NUM		6

typedef enum tagImiSkeletonPositionIndex {  
  	IMI_SKELETON_POSITION_HIP_CENTER      = 0,
    IMI_SKELETON_POSITION_SPINE,				// = 1, //(IMI_SKELETON_POSITION_HIP_CENTER + 1),
    IMI_SKELETON_POSITION_SHOULDER_CENTER,		// = 2, //(IMI_SKELETON_POSITION_SPINE + 1),
    IMI_SKELETON_POSITION_HEAD,					// = 3, //(IMI_SKELETON_POSITION_SHOULDER_CENTER + 1),
    IMI_SKELETON_POSITION_SHOULDER_LEFT,		// = 4, //(IMI_SKELETON_POSITION_HEAD + 1),
    IMI_SKELETON_POSITION_ELBOW_LEFT,			// = 5, //(IMI_SKELETON_POSITION_SHOULDER_LEFT + 1),
    IMI_SKELETON_POSITION_WRIST_LEFT,			// = 6, //(IMI_SKELETON_POSITION_ELBOW_LEFT + 1),
    IMI_SKELETON_POSITION_HAND_LEFT,			// = 7, //(IMI_SKELETON_POSITION_WRIST_LEFT + 1),
    IMI_SKELETON_POSITION_SHOULDER_RIGHT,		// = 8, //(IMI_SKELETON_POSITION_HAND_LEFT + 1),
    IMI_SKELETON_POSITION_ELBOW_RIGHT,			// = 9, //(IMI_SKELETON_POSITION_SHOULDER_RIGHT + 1),
    IMI_SKELETON_POSITION_WRIST_RIGHT,			// = 10, //(IMI_SKELETON_POSITION_ELBOW_RIGHT + 1),
    IMI_SKELETON_POSITION_HAND_RIGHT,			// = 11, //(IMI_SKELETON_POSITION_WRIST_RIGHT + 1),
    IMI_SKELETON_POSITION_HIP_LEFT,				// = 12, //(IMI_SKELETON_POSITION_HAND_RIGHT + 1),
    IMI_SKELETON_POSITION_KNEE_LEFT,			// = 13, //(IMI_SKELETON_POSITION_HIP_LEFT + 1),
    IMI_SKELETON_POSITION_ANKLE_LEFT,			// = 14, //(IMI_SKELETON_POSITION_KNEE_LEFT + 1),
    IMI_SKELETON_POSITION_FOOT_LEFT,			// = 15, //(IMI_SKELETON_POSITION_ANKLE_LEFT + 1),
    IMI_SKELETON_POSITION_HIP_RIGHT,			// = 16, //(IMI_SKELETON_POSITION_FOOT_LEFT + 1),
    IMI_SKELETON_POSITION_KNEE_RIGHT,			// = 17, //(IMI_SKELETON_POSITION_HIP_RIGHT + 1),
    IMI_SKELETON_POSITION_ANKLE_RIGHT,			// = 18, //(IMI_SKELETON_POSITION_KNEE_RIGHT + 1),
    IMI_SKELETON_POSITION_FOOT_RIGHT,			// = 19, //(IMI_SKELETON_POSITION_ANKLE_RIGHT + 1),
    IMI_SKELETON_POSITION_COUNT					// = 20  //(IMI_SKELETON_POSITION_FOOT_RIGHT + 1)		// 20
} ImiSkeletonPositionIndex;

typedef enum tagImiSkeletonPositionTrackingState {  
  	IMI_SKELETON_POSITION_NOT_TRACKED = 0,
    IMI_SKELETON_POSITION_INFERRED,			// = (IMI_SKELETON_POSITION_NOT_TRACKED + 1) ,
    IMI_SKELETON_POSITION_TRACKED			// = (IMI_SKELETON_POSITION_INFERRED + 1)
 } ImiSkeletonPositionTrackingState;

typedef enum tagImiSkeletonTrackingState {  
	IMI_SKELETON_NOT_TRACKED     = 0,// The user is not selected and is not available for selection
    IMI_SKELETON_POSITION_ONLY,		 // The user is not selected and is available for selection,
    IMI_SKELETON_TRACKED,			 // The user is being tracked and the skeleton position is valid
    IMI_SKELETON_TRACKING,           // The user have been selected but is not tracked yet
    IMI_SKELETON_FAILED              // The user is selected but failed to be tracked. 
} ImiSkeletonTrackingState;

typedef enum tagImiUserSelectorMode {  
	IMI_USERSELECTOR_CLOSEST     = 0,// The closest users will be tracked
	IMI_USERSELECTOR_WAVE            // The hand waved users will be tracked
} ImiUserSelectorMode;

typedef struct tagImiMatrix4 
{
	float M11;
	float M12;
	float M13;
	float M14;
	float M21;
	float M22;
	float M23;
	float M24;
	float M31;
	float M32;
	float M33;
	float M34;
	float M41;
	float M42;
	float M43;
	float M44;
}ImiMatrix4; 


typedef struct tagImiSkeletonData {
    ImiSkeletonTrackingState 			trackingState;
    uint32_t 							trackingID;
    uint32_t 							enrollIndex;
    uint32_t 							usrIndex;
    ImiVector4 							position;
    ImiVector4 							skeletonPositions[IMI_SKELETON_POSITION_COUNT];
    ImiSkeletonPositionTrackingState 	skeletonPositionTrackingState[IMI_SKELETON_POSITION_COUNT];
    uint32_t 							qualityFlags;
} ImiSkeletonData;

#pragma pack(push, 16)

typedef uint16_t depthUserPixel;

typedef struct tagImiSkeletonFrame {
	ImiVector4      floorClipPlane;
    ImiSkeletonData skeletonData[MAX_TRACKED_PEOPLE_NUM];
} ImiSkeletonFrame;

typedef struct _IMI_SKELETON_BONE_ROTATION
{
    ImiMatrix4 rotationMatrix;
    ImiVector4 rotationQuaternion;
} IMI_SKELETON_BONE_ROTATION;

typedef struct tagImiSkeletonJointOrientation{
	ImiSkeletonPositionIndex endJoint;
    ImiSkeletonPositionIndex startJoint;
	IMI_SKELETON_BONE_ROTATION hierarchicalRotation;
	IMI_SKELETON_BONE_ROTATION absoluteRotation;
} ImiSkeletonJointOrientation;
#pragma pack(pop)


//IMINECT_EXP void IMINECT_API imiConvertCoordinateDepthToWorld(ImiVector4* dst, const ImiVector4I* src, int32_t height, int32_t width);
//IMINECT_EXP void IMINECT_API imiConvertCoordinateWorldToDepth(ImiVector4I* dst, const ImiVector4* src, int32_t height, int32_t width);

/**
 * @brief  Select The User To Be Track Prior
 * @param  [IN] device: Imi device handle.
 * @param  [IN] userId: The User to be tracking.

 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiSelectUser(const ImiDeviceHandle device, uint32_t userId);


/**
 * @brief  Cancel The Priority of Tracking 
 * @param  [IN] device: Imi device handle.
 * @param  [IN] userId: The User to Cancel Priorty.

 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiUnSelectUser(const ImiDeviceHandle device, uint32_t userId);

/**
 * @brief  Mirror the skeleton 
 * @param  [IN] pSkeletonData: Skeleton data.

 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiMirrorSkeleton(ImiSkeletonData* pSkeletonData);

/**
 * @brief  Dig the user color segment.
 * @param  [IN]  userId: The user id array.
 * @param  [IN]  length: The user id array length.
 * @param  [IN]  type: The ImiCoordinateConvertMode type.
 * @param  [IN]  userDepth: The User depth data index, 2 byte per.
 * @param  [IN]  userColor: The User color data index, RGB data.
		   [OUT] userColor: The User color segment data index.
		   
 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiGetUserColorSegment(const int32_t* userId, const uint8_t length, ImiCoordinateConvertMode type, uint8_t* userDepth, uint8_t* userColor);

/**
 * @brief   Get Skeleton Orientation 
 * @param  [IN] pSkeletonPositions: Skeleton Position, size 20.
 * @param  [OUT] pJointOrientation: Orientation, size 20.

 * @return 0: success, < 0 : error
 **/
IMINECT_EXP int32_t IMINECT_API imiGetSkeletonJointOrientation(const ImiSkeletonData* pSkeletonData, ImiSkeletonJointOrientation* pJointOrientation);

/*!
* @}
*/

#endif // _IMI_SKELETON_H_

