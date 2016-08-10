/************************************************************************
*                                                                       *
*   NuiSkeleton.h -- This module defines the APIs for the Natural       *
*                    User Interface(NUI) skeleton services.             *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once

#ifndef NUIAPI
#error "You must include nuiapi.h rather than including nuiskeleton.h directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FLT_EPSILON
  #define FLT_EPSILON     1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */
#endif

#ifndef _Matrix4_
#define _Matrix4_
typedef struct _Matrix4 
{
    FLOAT M11;
    FLOAT M12;
    FLOAT M13;
    FLOAT M14;
    FLOAT M21;
    FLOAT M22;
    FLOAT M23;
    FLOAT M24;
    FLOAT M31;
    FLOAT M32;
    FLOAT M33;
    FLOAT M34;
    FLOAT M41;
    FLOAT M42;
    FLOAT M43;
    FLOAT M44;
} Matrix4;
#endif

#ifndef __NuiSensor_h__

#ifndef _Vector4_
#define _Vector4_
typedef struct _Vector4
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT w;
} Vector4;
#endif

#ifdef __XNAMATH_H__

#ifndef _Vector4_Functions_
#define _Vector4_Functions_

inline XMVECTOR XMVectorFromVector4(const Vector4& vec4)
{
    return XMVectorSet(vec4.x, vec4.y, vec4.z, vec4.w);
}

inline Vector4 XMVectorToVector4(FXMVECTOR V)
{
    Vector4 vec4 = { XMVectorGetX(V), XMVectorGetY(V), XMVectorGetZ(V), XMVectorGetW(V) };
    return vec4;
}

#endif

#endif

typedef enum _NUI_SKELETON_POSITION_INDEX
{
    NUI_SKELETON_POSITION_HIP_CENTER = 0,
    NUI_SKELETON_POSITION_SPINE,
    NUI_SKELETON_POSITION_SHOULDER_CENTER,
    NUI_SKELETON_POSITION_HEAD,
    NUI_SKELETON_POSITION_SHOULDER_LEFT,
    NUI_SKELETON_POSITION_ELBOW_LEFT,
    NUI_SKELETON_POSITION_WRIST_LEFT,
    NUI_SKELETON_POSITION_HAND_LEFT,
    NUI_SKELETON_POSITION_SHOULDER_RIGHT,
    NUI_SKELETON_POSITION_ELBOW_RIGHT,
    NUI_SKELETON_POSITION_WRIST_RIGHT,
    NUI_SKELETON_POSITION_HAND_RIGHT,
    NUI_SKELETON_POSITION_HIP_LEFT,
    NUI_SKELETON_POSITION_KNEE_LEFT,
    NUI_SKELETON_POSITION_ANKLE_LEFT,
    NUI_SKELETON_POSITION_FOOT_LEFT,
    NUI_SKELETON_POSITION_HIP_RIGHT,
    NUI_SKELETON_POSITION_KNEE_RIGHT,
    NUI_SKELETON_POSITION_ANKLE_RIGHT,
    NUI_SKELETON_POSITION_FOOT_RIGHT,
    NUI_SKELETON_POSITION_COUNT
} NUI_SKELETON_POSITION_INDEX;

//
//  Number of NUI_SKELETON_DATA elements in NUI_SKELETON_FRAME
//

#define NUI_SKELETON_COUNT 6

#endif // __NuiSensor_h__

//
//  Number of NUI_SKELETON_DATA elements that can be in the NUI_SKELETON_TRACKED state
//

#define NUI_SKELETON_MAX_TRACKED_COUNT 2

//
//  Tracking IDs start at 1
//

#define NUI_SKELETON_INVALID_TRACKING_ID 0

#ifndef __NuiSensor_h__
typedef enum _NUI_SKELETON_POSITION_TRACKING_STATE
{
    NUI_SKELETON_POSITION_NOT_TRACKED = 0,
    NUI_SKELETON_POSITION_INFERRED,
    NUI_SKELETON_POSITION_TRACKED
} NUI_SKELETON_POSITION_TRACKING_STATE;

typedef enum _NUI_SKELETON_TRACKING_STATE
{
    NUI_SKELETON_NOT_TRACKED = 0,
    NUI_SKELETON_POSITION_ONLY,
    NUI_SKELETON_TRACKED
} NUI_SKELETON_TRACKING_STATE;

typedef struct _NUI_SKELETON_DATA
{
  NUI_SKELETON_TRACKING_STATE eTrackingState;
  DWORD dwTrackingID;
  DWORD dwEnrollmentIndex;
  DWORD dwUserIndex;
  Vector4 Position;
  Vector4 SkeletonPositions[NUI_SKELETON_POSITION_COUNT];
  NUI_SKELETON_POSITION_TRACKING_STATE eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_COUNT];
  DWORD dwQualityFlags;
} NUI_SKELETON_DATA;
#endif // __NuiSensor_h__


//
// Force a link error if the size of NUI_SKELETON_DATA is different
// between the static library and the header included by the title.
//

__declspec(selectany) DWORD NuiSkeletonDataSize = sizeof(NUI_SKELETON_DATA);


#define NUI_SKELETON_QUALITY_CLIPPED_RIGHT  0x00000001
#define NUI_SKELETON_QUALITY_CLIPPED_LEFT   0x00000002
#define NUI_SKELETON_QUALITY_CLIPPED_TOP    0x00000004
#define NUI_SKELETON_QUALITY_CLIPPED_BOTTOM 0x00000008

#ifndef __NuiSensor_h__
#pragma pack(push, 16)
typedef struct _NUI_SKELETON_FRAME
{
  LARGE_INTEGER         liTimeStamp;
  DWORD                 dwFrameNumber;
  DWORD                 dwFlags;
  Vector4              vFloorClipPlane;
  Vector4              vNormalToGravity;
  NUI_SKELETON_DATA     SkeletonData[NUI_SKELETON_COUNT];
} NUI_SKELETON_FRAME;
#pragma pack(pop)

typedef struct _NUI_TRANSFORM_SMOOTH_PARAMETERS
{
    FLOAT   fSmoothing;             // [0..1], lower values closer to raw data
    FLOAT   fCorrection;            // [0..1], lower values slower to correct towards the raw data
    FLOAT   fPrediction;            // [0..n], the number of frames to predict into the future
    FLOAT   fJitterRadius;          // The radius in meters for jitter reduction
    FLOAT   fMaxDeviationRadius;    // The maximum radius in meters that filtered positions are allowed to deviate from raw data
} NUI_TRANSFORM_SMOOTH_PARAMETERS;
#endif // __NuiSensor_h__

// Flags returned by NuiSkeletonGetNextFrame in the dwFlags field of the NUI_SKELETON_FRAME structure
#define NUI_SKELETON_FRAME_FLAG_SEATED_SUPPORT_ENABLED  0x00000008

// Flags for use with the NuiSkeletonTrackingEnable function
#define NUI_SKELETON_TRACKING_FLAG_SUPPRESS_NO_FRAME_DATA       0x00000001
#define NUI_SKELETON_TRACKING_FLAG_TITLE_SETS_TRACKED_SKELETONS 0x00000002
#define NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT        0x00000004
#define NUI_SKELETON_TRACKING_FLAG_ENABLE_IN_NEAR_RANGE         0x00000008

#ifndef __NuiSensor_h__
typedef struct _NUI_SKELETON_BONE_ROTATION
{
    Matrix4 rotationMatrix;
    Vector4 rotationQuaternion;
} NUI_SKELETON_BONE_ROTATION;

typedef struct _NUI_SKELETON_BONE_ORIENTATION
{
    NUI_SKELETON_POSITION_INDEX endJoint;
    NUI_SKELETON_POSITION_INDEX startJoint;
    NUI_SKELETON_BONE_ROTATION hierarchicalRotation;
    NUI_SKELETON_BONE_ROTATION absoluteRotation;
} NUI_SKELETON_BONE_ORIENTATION;
#endif // __NuiSensor_h__

/// <summary>
/// Enables skeleton tracking.
/// </summary>
/// <param name="hNextFrameEvent">
/// A handle to an application-allocated, manual reset event that will be set whenever a new frame
/// of skeleton data is available, and will be reset whenever the latest frame data is returned.
/// This can be NULL.
/// </param>
/// <param name="dwFlags">
/// Flags that control skeleton tracking, as a bitwise-OR combination NUI_SKELETON_TRACKING values.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>__HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION)</term>
///       <description>The device is uninitialized or the sensor is not initialized with the NUI_INITIALIZE_FLAG_USES_SKELETON flag. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="dwFlags"/> parameter includes invalid flags.</description>
///    </item>
///    <item>
///       <term>E_OUTOFMEMORY</term>
///       <description>Allocation failed.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// The following flags are supported:
/// <list type="table">
///    <item>
///       <term>NUI_SKELETON_TRACKING_FLAG_SUPPRESS_NO_FRAME_DATA</term>
///       <description>Prevents NuiSkeletonGetNextFrame from returning E_NUI_FRAME_NO_DATA errors. Instead, calls to NuiSkeletonGetNextFrame block until data is available or the timeout period passes.</description>
///    </item>
///    <item>
///       <term>NUI_SKELETON_TRACKING_FLAG_TITLE_SETS_TRACKED_SKELETONS</term>
///       <description>Disables the default player selection mode and enables the title to manage which players have tracked skeletons.</description>
///    </item>
///    <item>
///       <term>NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT</term>
///       <description>Uses seated skeleton tracking mode. The 10 lower-body joints of each skeleton will not be tracked.</description>
///    </item>
/// </list>
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiSkeletonTrackingEnable(
    _In_opt_ HANDLE hNextFrameEvent,
    _In_     DWORD  dwFlags
    );

/// <summary>
/// Disables skeleton tracking.
/// </summary>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>__HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION)</term>
///       <description>The device is uninitialized or the sensor is not initialized with the NUI_INITIALIZE_FLAG_USES_SKELETON flag. <see cref="NuiInitialize"/>.</description>
///    </item>
/// </list>
/// </returns>
_Check_return_ HRESULT NUIAPI NuiSkeletonTrackingDisable(
    );

/// <summary>
/// Gets the next frame of data from the skeleton stream.
/// </summary>
/// <param name="dwMillisecondsToWait">The timeout (in milliseconds) before returning without a new frame.</param>
/// <param name="pSkeletonFrame">
/// A pointer to a NUI_SKELETON_FRAME structure that receives the next image frame in the skeleton
/// stream. This must not be NULL.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>S_FALSE</term>
///       <description>The wait timeout expired before a new frame was available and NuiSkeletonTrackingEnable was passed the NUI_SKELETON_TRACKING_FLAG_TITLE_SETS_TRACKED_SKELETONS flag.</description>
///    </item>
///    <item>
///       <term>E_NUI_FRAME_NO_DATA</term>
///       <description>The wait timeout expired before a new frame was available.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="pSkeletonFrame"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <seealso cref="NuiSkeletonTrackingEnable"/>
_Check_return_ HRESULT NUIAPI NuiSkeletonGetNextFrame(
    _In_  DWORD dwMillisecondsToWait,
    _Inout_ NUI_SKELETON_FRAME *pSkeletonFrame
    );

/// <summary>
/// Sets an array of IDs for skeletal tracking.
/// </summary>
/// <param name="TrackingIDs">A pointer to the first DWORD in an array of tracking IDs, one for each skeleton.</param>
/// <returns>
/// <para>Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="TrackingIDs"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_NUI_STREAM_NOT_ENABLED</term>
///       <description>The device is uninitialized or the sensor is not initialized with the NUI_INITIALIZE_FLAG_USES_SKELETON flag. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_NUI_FEATURE_NOT_INITIALIZED</term>
///       <description>Skeletal tracking is not enabled with the NUI_SKELETON_TRACKING_FLAG_TITLE_SETS_TRACKED_SKELETONS flag.</description>
///    </item>
/// </list>
/// </returns>
_Check_return_ HRESULT NUIAPI NuiSkeletonSetTrackedSkeletons(
    _In_count_c_(NUI_SKELETON_MAX_TRACKED_COUNT) DWORD TrackingIDs[NUI_SKELETON_MAX_TRACKED_COUNT]
    );

#ifdef __cplusplus
} //close extern "C"

// Assuming a pixel resolution of 320x240
// x_meters = (x_pixelcoord - 160) * NUI_CAMERA_DEPTH_IMAGE_TO_SKELETON_MULTIPLIER_320x240 * z_meters;
// y_meters = (y_pixelcoord - 120) * NUI_CAMERA_DEPTH_IMAGE_TO_SKELETON_MULTIPLIER_320x240 * z_meters;
#define NUI_CAMERA_DEPTH_IMAGE_TO_SKELETON_MULTIPLIER_320x240 (NUI_CAMERA_DEPTH_NOMINAL_INVERSE_FOCAL_LENGTH_IN_PIXELS)
 
// Assuming a pixel resolution of 320x240
// x_pixelcoord = (x_meters) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / z_meters + 160;
// y_pixelcoord = (y_meters) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / z_meters + 120;
#define NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 (NUI_CAMERA_DEPTH_NOMINAL_FOCAL_LENGTH_IN_PIXELS)

/// <summary>
/// Returns the depth space coordinates of the specified point in skeleton space.
/// </summary>
/// <param name="vPoint">
/// The point to transform, in skeleton space coordinates. This point must have a valid depth value.
/// </param>
/// <param name="pfDepthX">
/// A pointer to a FLOAT that receives the X coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="pfDepthY">
/// A pointer to a FLOAT that receives the Y coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="pusDepthValue">
/// <para>A pointer to a USHORT that receives the depth value of the point in depth space. This
/// pointer must be non-NULL when you call the function. If this is a NULL pointer, this function
/// returns without doing anything.</para>
///
/// <para>The format of this value is the same as that for points in other depth images: the least
/// significant three bits contain a player index that is always zero, and the remaining bits are
/// the depth value, in millimeters. This value is suitable for comparison with values from an
/// image from any of the depth streams, provided that the player index information is masked
/// appropriately from the other image.</para>
/// </param>
/// <param name="eResolution">
/// A NUI_IMAGE_RESOLUTION value that specifies the resolution of the depth image.
/// </param>
/// <remarks>
/// You can use this function to place virtual objects into the color image with depth-based
/// occlusion. Call this function to determine which skeleton-space vertices of a virtual object
/// are in front of, or behind, real objects that are visible in the depth map image. After
/// occluded parts of the virtual objects have been culled, use the
/// NuiImageGetColorPixelCoordinatesFromDepthPixel function to overlay the virtual object's
/// vertices into color image pixel coordinates for rendering.
/// </remarks>
inline
VOID
NuiTransformSkeletonToDepthImage(
    _In_ Vector4 vPoint,
    _Out_ LONG *plDepthX,
    _Out_ LONG *plDepthY,
    _Out_ USHORT *pusDepthValue,
    _In_ NUI_IMAGE_RESOLUTION eResolution
    )
{
    if((plDepthX == NULL) || (plDepthY == NULL) || (pusDepthValue == NULL))
    {
        return;
    }
    
    //
    // Requires a valid depth value.
    //
    
    if(vPoint.z > FLT_EPSILON)
    {
        DWORD width;
        DWORD height;
        NuiImageResolutionToSize( eResolution, width, height );

        //
        // Center of depth sensor is at (0,0,0) in skeleton space, and
        // and (width/2,height/2) in depth image coordinates.  Note that positive Y
        // is up in skeleton space and down in image coordinates.
        //
        // The 0.5f is to correct for casting to int truncating, not rounding

        *plDepthX = static_cast<INT>( width / 2 + vPoint.x * (width/320.f) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / vPoint.z + 0.5f);
        *plDepthY = static_cast<INT>( height / 2 - vPoint.y * (height/240.f) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / vPoint.z + 0.5f);
        
        //
        //  Depth is in meters in skeleton space.
        //  The depth image pixel format has depth in millimeters shifted left by 3.
        //
        
        *pusDepthValue = static_cast<USHORT>(vPoint.z *1000) << 3;
    } else
    {
        *plDepthX = 0;
        *plDepthY = 0;
        *pusDepthValue = 0;
    }
}

/// <summary>
/// Returns the depth space coordinates of the specified point in skeleton space.
/// </summary>
/// <param name="vPoint">
/// The point to transform, in skeleton space coordinates. This point must have a valid depth value.
/// </param>
/// <param name="pfDepthX">
/// A pointer to a FLOAT that receives the X coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="pfDepthY">
/// A pointer to a FLOAT that receives the Y coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="pusDepthValue">
/// <para>A pointer to a USHORT that receives the depth value of the point in depth space. This
/// pointer must be non-NULL when you call the function. If this is a NULL pointer, this function
/// returns without doing anything.</para>
///
/// <para>The format of this value is the same as that for points in other depth images: the least
/// significant three bits contain a player index that is always zero, and the remaining bits are
/// the depth value, in millimeters. This value is suitable for comparison with values from an
/// image from any of the depth streams, provided that the player index information is masked
/// appropriately from the other image.</para>
/// </param>
/// <remarks>
/// You can use this function to place virtual objects into the color image with depth-based
/// occlusion. Call this function to determine which skeleton-space vertices of a virtual object
/// are in front of, or behind, real objects that are visible in the depth map image. After
/// occluded parts of the virtual objects have been culled, use the
/// NuiImageGetColorPixelCoordinatesFromDepthPixel function to overlay the virtual object's
/// vertices into color image pixel coordinates for rendering.
/// </remarks>
inline
VOID
NuiTransformSkeletonToDepthImage(
    _In_ Vector4 vPoint,
    _Out_ LONG *plDepthX,
    _Out_ LONG *plDepthY,
    _Out_ USHORT *pusDepthValue
    )
{
    NuiTransformSkeletonToDepthImage( vPoint, plDepthX, plDepthY, pusDepthValue, NUI_IMAGE_RESOLUTION_320x240);
}

/// <summary>
/// Returns the depth space coordinates of the specified point in skeleton space.
/// </summary>
/// <param name="vPoint">
/// The point to transform, in skeleton space coordinates. This point must have a valid depth value.
/// </param>
/// <param name="pfDepthX">
/// A pointer to a FLOAT that receives the X coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="pfDepthY">
/// A pointer to a FLOAT that receives the Y coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="eResolution">
/// A NUI_IMAGE_RESOLUTION value that specifies the resolution of the depth image.
/// </param>
/// <remarks>
/// You can use this function to place virtual objects into the color image with depth-based
/// occlusion. Call this function to determine which skeleton-space vertices of a virtual object
/// are in front of, or behind, real objects that are visible in the depth map image. After
/// occluded parts of the virtual objects have been culled, use the
/// NuiImageGetColorPixelCoordinatesFromDepthPixel function to overlay the virtual object's
/// vertices into color image pixel coordinates for rendering.
/// </remarks>
inline
VOID
NuiTransformSkeletonToDepthImage(
    _In_ Vector4 vPoint,
    _Out_ FLOAT *pfDepthX,
    _Out_ FLOAT *pfDepthY,
    _In_ NUI_IMAGE_RESOLUTION eResolution
    )
{
    if((pfDepthX == NULL) || (pfDepthY == NULL))
    {
        return;
    }
    
    //
    // Requires a valid depth value.
    //
    
    if(vPoint.z > FLT_EPSILON)
    {
        DWORD width;
        DWORD height;
        NuiImageResolutionToSize( eResolution, width, height );

        //
        // Center of depth sensor is at (0,0,0) in skeleton space, and
        // and (width/2,height/2) in depth image coordinates.  Note that positive Y
        // is up in skeleton space and down in image coordinates.
        //
        
        *pfDepthX = width / 2 + vPoint.x * (width/320.f) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / vPoint.z;
        *pfDepthY = height / 2 - vPoint.y * (height/240.f) * NUI_CAMERA_SKELETON_TO_DEPTH_IMAGE_MULTIPLIER_320x240 / vPoint.z;
        
    } else
    {
        *pfDepthX = 0.0f;
        *pfDepthY = 0.0f;
    }
}

/// <summary>
/// Returns the depth space coordinates of the specified point in skeleton space.
/// </summary>
/// <param name="vPoint">
/// The point to transform, in skeleton space coordinates. This point must have a valid depth value.
/// </param>
/// <param name="pfDepthX">
/// A pointer to a FLOAT that receives the X coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <param name="pfDepthY">
/// A pointer to a FLOAT that receives the Y coordinate of the point in depth space. This pointer
/// must be non-NULL when you call the function. If this is a NULL pointer, this function returns
/// without doing anything.
/// </param>
/// <remarks>
/// You can use this function to place virtual objects into the color image with depth-based
/// occlusion. Call this function to determine which skeleton-space vertices of a virtual object
/// are in front of, or behind, real objects that are visible in the depth map image. After
/// occluded parts of the virtual objects have been culled, use the
/// NuiImageGetColorPixelCoordinatesFromDepthPixel function to overlay the virtual object's
/// vertices into color image pixel coordinates for rendering.
/// </remarks>
inline
VOID
NuiTransformSkeletonToDepthImage(
    _In_ Vector4 vPoint,
    _Out_ FLOAT *pfDepthX,
    _Out_ FLOAT *pfDepthY
    )
{
    NuiTransformSkeletonToDepthImage(vPoint, pfDepthX, pfDepthY, NUI_IMAGE_RESOLUTION_320x240);
}

/// <summary>
/// Returns the depth space coordinates of the specified point in skeleton space.
/// </summary>
/// <param name="lDepthX">The X coordinate of the depth pixel.</param>
/// <param name="lDepthY">The Y coordinate of the depth pixel.</param>
/// <param name="usDepthValue">
/// The depth value (in millimeters) of the depth image pixel, shifted left by three bits. The left
/// shift enables you to pass the value from the depth image directly into this function.
/// </param>
/// <param name="eResolution">
/// A NUI_IMAGE_RESOLUTION value that specifies the resolution of the depth image.
/// </param>
/// <returns>
/// Returns the skeleton space coordinates of the given depth image pixel (in meters).
/// </returns>
inline
Vector4
NuiTransformDepthImageToSkeleton(
    _In_ LONG lDepthX,
    _In_ LONG lDepthY,
    _In_ USHORT usDepthValue,
    _In_ NUI_IMAGE_RESOLUTION eResolution
    )
{
    DWORD width;
    DWORD height;
    NuiImageResolutionToSize( eResolution, width, height );

    //
    //  Depth is in meters in skeleton space.
    //  The depth image pixel format has depth in millimeters shifted left by 3.
    //
    
    FLOAT fSkeletonZ = static_cast<FLOAT>(usDepthValue >> 3) / 1000.0f;

    //
    // Center of depth sensor is at (0,0,0) in skeleton space, and
    // and (width/2,height/2) in depth image coordinates.  Note that positive Y
    // is up in skeleton space and down in image coordinates.
    //
    
    FLOAT fSkeletonX = (lDepthX - width/2.0f) * (320.0f/width) * NUI_CAMERA_DEPTH_IMAGE_TO_SKELETON_MULTIPLIER_320x240 * fSkeletonZ;
    FLOAT fSkeletonY = -(lDepthY - height/2.0f) * (240.0f/height) * NUI_CAMERA_DEPTH_IMAGE_TO_SKELETON_MULTIPLIER_320x240 * fSkeletonZ;

    //
    // Return the result as a vector.
    //
        
    Vector4 v4;
    v4.x = fSkeletonX;
    v4.y = fSkeletonY;
    v4.z = fSkeletonZ;
    v4.w = 1.0f;
    return v4;
}

/// <summary>
/// Returns the depth space coordinates of the specified point in skeleton space.
/// </summary>
/// <param name="lDepthX">The X coordinate of the depth pixel.</param>
/// <param name="lDepthY">The Y coordinate of the depth pixel.</param>
/// <param name="usDepthValue">
/// The depth value (in millimeters) of the depth image pixel, shifted left by three bits. The left
/// shift enables you to pass the value from the depth image directly into this function.
/// </param>
/// <returns>
/// Returns the skeleton space coordinates of the given depth image pixel (in meters).
/// </returns>
inline
Vector4
NuiTransformDepthImageToSkeleton(
    _In_ LONG lDepthX,
    _In_ LONG lDepthY,
    _In_ USHORT usDepthValue
    )
{
    return NuiTransformDepthImageToSkeleton(lDepthX, lDepthY, usDepthValue, NUI_IMAGE_RESOLUTION_320x240);
}

#endif

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Filters skeleton positions to reduce jitter between frames.
/// </summary>
/// <param name="pSkeletonFrame">
/// On entry, points to a NUI_SKELETON_FRAME structure that contains the skeleton data to be
/// smoothed. On exit, the skeleton data in the structure has been replaced by smoothed data. If
/// this function does not return S_OK, this data is unchanged.
/// </param>
/// <param name="pSmoothingParams">
/// The parameters for the smoothing function.  See the NUI_TRANSFORM_SMOOTH_PARAMETERS structure
/// for a description of the parameters.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_OUTOFMEMORY</term>
///       <description>Failed allocation.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="pSkeletonFrame"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// The filter used is based on the Holt Double Exponential Smoothing method used for statistical
/// analysis of economic data, which provides smoothing with less latency than other smoothing
/// filter algorithms. A single call of this function updates all currently-tracked skeletons.
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiTransformSmooth(
         _Inout_ NUI_SKELETON_FRAME *pSkeletonFrame,
         _In_opt_ CONST NUI_TRANSFORM_SMOOTH_PARAMETERS *pSmoothingParams
    );

/// <summary>
/// Calculate bone orientations for a skeleton.
/// </summary>
/// <param name="pSkeletonData">
/// Pointer to the skeleton data to calculate joint angles for.
/// </param>
/// <param name="pBoneOrientations">
/// Pointer to an array of NUI_SKELETON_BONE_ORIENTATION of dimension NUI_SKELETON_POSITION_COUNT (20).
/// This array must be allocated by the user before calling this function.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="pSkeletonData"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="pBoneOrientations"/> parameter is NULL.</description>
///    </item>
/// </list>
///    <item>
///       <term>S_FALSE</term>
///       <description>The joints required to calculate the skeleton root are not visible. Hierarchical bone rotations are set to Identity.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// The function calculates hierarchical and absolute joint angles for the skeleton, which can
/// be used in animating an avatar (Avateering). The HipCenter joint is the root of the hierarchy,
/// and describes an absolute rotation in the right-hand camera coordinate system. All other
/// joints describe rotations relative to their parent joint orientation. The angles are returned
/// in the same order as the joints are defined.
/// </remarks>
_Check_return_ STDMETHODIMP
NuiSkeletonCalculateBoneOrientations(
    _In_ const NUI_SKELETON_DATA *pSkeletonData,
    _Out_cap_c_(NUI_SKELETON_POSITION_COUNT) NUI_SKELETON_BONE_ORIENTATION *pBoneOrientations);

#ifdef __cplusplus
} //close extern "C"
#endif


