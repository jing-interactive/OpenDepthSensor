/************************************************************************
*                                                                       *
*   NuiImageCamera.h -- This module defines the APIs for the Natural    *
*                       User Interface(NUI) image and camera services.  *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once

#ifndef NUIAPI
#error "You must include nuiapi.h rather than including nuiimagecamera.h directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NuiSensor_h__

#ifndef _NUI_IMAGE_TYPE_
#define _NUI_IMAGE_TYPE_
typedef enum _NUI_IMAGE_TYPE
{
  NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX = 0,            // USHORT
  NUI_IMAGE_TYPE_COLOR,                                 // RGB32 data
  NUI_IMAGE_TYPE_COLOR_YUV,                             // YUY2 stream from camera h/w, but converted to RGB32 before user getting it.
  NUI_IMAGE_TYPE_COLOR_RAW_YUV,                         // YUY2 stream from camera h/w.
  NUI_IMAGE_TYPE_DEPTH,                                 // USHORT
  NUI_IMAGE_TYPE_COLOR_INFRARED,                        // USHORT
  NUI_IMAGE_TYPE_COLOR_RAW_BAYER,                       // 8-bit Bayer
} NUI_IMAGE_TYPE;
#endif // _NUI_IMAGE_TYPE_

#ifndef _NUI_IMAGE_RESOLUTION_
#define _NUI_IMAGE_RESOLUTION_
typedef enum _NUI_IMAGE_RESOLUTION
{
  NUI_IMAGE_RESOLUTION_INVALID = -1,
  NUI_IMAGE_RESOLUTION_80x60 = 0,
  NUI_IMAGE_RESOLUTION_320x240,
  NUI_IMAGE_RESOLUTION_640x480,
  NUI_IMAGE_RESOLUTION_1280x960,                         // for hires color only
} NUI_IMAGE_RESOLUTION;
#endif _NUI_IMAGE_RESOLUTION_

#ifndef _NUI_BACKLIGHT_COMPENSATION_MODE_
#define _NUI_BACKLIGHT_COMPENSATION_MODE_
typedef
enum _NUI_BACKLIGHT_COMPENSATION_MODE
    {
    NUI_BACKLIGHT_COMPENSATION_MODE_AVERAGE_BRIGHTNESS = 0,
    NUI_BACKLIGHT_COMPENSATION_MODE_CENTER_PRIORITY = 1,
    NUI_BACKLIGHT_COMPENSATION_MODE_LOWLIGHTS_PRIORITY = 2,
    NUI_BACKLIGHT_COMPENSATION_MODE_CENTER_ONLY = 4
    }   NUI_BACKLIGHT_COMPENSATION_MODE;
#endif _NUI_BACKLIGHT_COMPENSATION_MODE_

#ifndef _NUI_POWER_LINE_FREQUENCY_
#define _NUI_POWER_LINE_FREQUENCY_
typedef
enum _NUI_POWER_LINE_FREQUENCY
    {
    NUI_POWER_LINE_FREQUENCY_DISABLED = 0,
    NUI_POWER_LINE_FREQUENCY_50HZ = 1,
    NUI_POWER_LINE_FREQUENCY_60HZ = 2
    }   NUI_POWER_LINE_FREQUENCY;
#endif _NUI_POWER_LINE_FREQUENCY_

#endif // __NuiSensor_h__

/// <summary>
/// Converts the resolution to a size.
/// </summary>
/// <param name="res">The image resolution.</param>
/// <param name="refWidth">The width of the image.</param>
/// <param name="refHeight">The height of the image.</param>
inline void NuiImageResolutionToSize( _In_ NUI_IMAGE_RESOLUTION res, _Out_ DWORD & refWidth, _Out_ DWORD & refHeight )
{
    switch( res )
    {
    case NUI_IMAGE_RESOLUTION_80x60:
        refWidth = 80;
        refHeight = 60;
        break;
    case NUI_IMAGE_RESOLUTION_320x240:
        refWidth = 320;
        refHeight = 240;
        break;
    case NUI_IMAGE_RESOLUTION_640x480:
        refWidth = 640;
        refHeight = 480;
        break;
    case NUI_IMAGE_RESOLUTION_1280x960 :
        refWidth = 1280;
        refHeight = 960;
        break;
    default:
        refWidth = 0;
        refHeight = 0;
        break;
    }
}

#define NUI_IMAGE_PLAYER_INDEX_SHIFT          3
#define NUI_IMAGE_PLAYER_INDEX_MASK           ((1 << NUI_IMAGE_PLAYER_INDEX_SHIFT)-1)
#define NUI_IMAGE_DEPTH_MAXIMUM               ((4000 << NUI_IMAGE_PLAYER_INDEX_SHIFT) | NUI_IMAGE_PLAYER_INDEX_MASK)
#define NUI_IMAGE_DEPTH_MINIMUM               (800 << NUI_IMAGE_PLAYER_INDEX_SHIFT)
#define NUI_IMAGE_DEPTH_MAXIMUM_NEAR_MODE     ((3000 << NUI_IMAGE_PLAYER_INDEX_SHIFT) | NUI_IMAGE_PLAYER_INDEX_MASK)
#define NUI_IMAGE_DEPTH_MINIMUM_NEAR_MODE     (400 << NUI_IMAGE_PLAYER_INDEX_SHIFT)
#define NUI_IMAGE_DEPTH_NO_VALUE              0
#define NUI_IMAGE_DEPTH_TOO_FAR_VALUE         (0x0fff << NUI_IMAGE_PLAYER_INDEX_SHIFT)
#define NUI_IMAGE_DEPTH_UNKNOWN_VALUE         (0x1fff << NUI_IMAGE_PLAYER_INDEX_SHIFT)
#define NUI_DEPTH_DEPTH_UNKNOWN_VALUE         NUI_IMAGE_DEPTH_UNKNOWN_VALUE

// These must exactly match the constants defined in CDRPProcessor.h
#define NUI_DEPTH_UNKNOWN                     0
#define NUI_PIXEL_COORDINATE_UNKNOWN          INT_MIN

#define NUI_CAMERA_DEPTH_NOMINAL_FOCAL_LENGTH_IN_PIXELS         (285.63f)   // Based on 320x240 pixel size.
#define NUI_CAMERA_DEPTH_NOMINAL_INVERSE_FOCAL_LENGTH_IN_PIXELS (3.501e-3f) // (1/NUI_CAMERA_DEPTH_NOMINAL_FOCAL_LENGTH_IN_PIXELS)
#define NUI_CAMERA_DEPTH_NOMINAL_DIAGONAL_FOV                   (70.0f)
#define NUI_CAMERA_DEPTH_NOMINAL_HORIZONTAL_FOV                 (58.5f)
#define NUI_CAMERA_DEPTH_NOMINAL_VERTICAL_FOV                   (45.6f)

#define NUI_CAMERA_COLOR_NOMINAL_FOCAL_LENGTH_IN_PIXELS         (531.15f)   // Based on 640x480 pixel size.
#define NUI_CAMERA_COLOR_NOMINAL_INVERSE_FOCAL_LENGTH_IN_PIXELS (1.83e-3f)  // (1/NUI_CAMERA_COLOR_NOMINAL_FOCAL_LENGTH_IN_PIXELS)
#define NUI_CAMERA_COLOR_NOMINAL_DIAGONAL_FOV                   ( 73.9f)
#define NUI_CAMERA_COLOR_NOMINAL_HORIZONTAL_FOV                 ( 62.0f)
#define NUI_CAMERA_COLOR_NOMINAL_VERTICAL_FOV                   ( 48.6f)


//
// Unpacks the depth value from the packed pixel format
//
inline USHORT NuiDepthPixelToDepth(USHORT packedPixel)
{
    return packedPixel >> NUI_IMAGE_PLAYER_INDEX_SHIFT;
}

//
// Unpacks the player index value from the packed pixel format
//
inline USHORT NuiDepthPixelToPlayerIndex(USHORT packedPixel)
{
    return packedPixel & NUI_IMAGE_PLAYER_INDEX_MASK;
}

typedef enum _NUI_IMAGE_DIGITALZOOM
{
    NUI_IMAGE_DIGITAL_ZOOM_1X = 0,
} NUI_IMAGE_DIGITALZOOM;


#ifndef __NuiSensor_h__

#ifndef _NUI_IMAGE_VIEW_AREA_
#define _NUI_IMAGE_VIEW_AREA_
typedef struct _NUI_IMAGE_VIEW_AREA
{
    NUI_IMAGE_DIGITALZOOM  eDigitalZoom;
    LONG                   lCenterX;
    LONG                   lCenterY;
} NUI_IMAGE_VIEW_AREA;
#endif _NUI_IMAGE_VIEW_AREA_


#endif __NuiSensor_h__

#define NUI_IMAGE_FRAME_FLAG_NONE              0x00000000
#define NUI_IMAGE_FRAME_FLAG_VIEW_AREA_UNKNOWN 0x00000001
#define NUI_IMAGE_FRAME_FLAG_NEAR_MODE_ENABLED 0x00020000

#ifndef __NuiSensor_h__

#ifndef _NUI_LOCKED_RECT_
#define _NUI_LOCKED_RECT_
// Note:  NOT identical to D3DLOCKED_RECT
typedef struct _NUI_LOCKED_RECT
{
    INT                 Pitch;
    int                 size;   // Size of pBits, in bytes.
    BYTE*               pBits;
} NUI_LOCKED_RECT;
#endif _NUI_LOCKED_RECT_

#ifndef _NUI_SURFACE_DESC_
#define _NUI_SURFACE_DESC_
// Note:  NOT identical to D3DSURFACE_DESC
typedef struct _NUI_SURFACE_DESC
{
    UINT                Width;
    UINT                Height;
} NUI_SURFACE_DESC;
#endif _NUI_SURFACE_DESC_

struct INuiFrameTexture;

#ifndef _NUI_IMAGE_FRAME_
#define _NUI_IMAGE_FRAME_
typedef struct _NUI_IMAGE_FRAME
{
  LARGE_INTEGER             liTimeStamp;
  DWORD                     dwFrameNumber;
  NUI_IMAGE_TYPE            eImageType;
  NUI_IMAGE_RESOLUTION      eResolution;
  INuiFrameTexture          *pFrameTexture;
  DWORD                     dwFrameFlags;  
  NUI_IMAGE_VIEW_AREA       ViewArea;
} NUI_IMAGE_FRAME;
#endif _NUI_IMAGE_FRAME_

#ifndef _NUI_DEPTH_IMAGE_PIXEL_
#define _NUI_DEPTH_IMAGE_PIXEL_

// This struct layout must exactly match that of NUI_DEPTH_IMAGE_PIXEL in
// Kinect.idl and NUI_IMAGE_PIXEL in CDRPProcessor.h.
typedef struct _NUI_DEPTH_IMAGE_PIXEL
{
    USHORT              playerIndex;
    USHORT              depth;
} NUI_DEPTH_IMAGE_PIXEL;

#endif _NUI_DEPTH_IMAGE_PIXEL_

#ifndef _NUI_DEPTH_IMAGE_POINT_
#define _NUI_DEPTH_IMAGE_POINT_

// This struct layout must exactly match that of NUI_DEPTH_IMAGE_POINT in
// Kinect.idl and NUI_DEPTH_IMAGE_POINT in CDRPProcessor.h.
typedef struct _NUI_DEPTH_IMAGE_POINT
{
    LONG                x;
    LONG                y;
    LONG                depth;
    LONG                reserved;
} NUI_DEPTH_IMAGE_POINT;

#endif _NUI_DEPTH_IMAGE_POINT_

#ifndef _NUI_COLOR_IMAGE_POINT_
#define _NUI_COLOR_IMAGE_POINT_

// This struct layout must exactly match that of NUI_DEPTH_IMAGE_POINT in
// Kinect.idl and NUI_DEPTH_IMAGE_POINT in CDRPProcessor.h.
typedef struct _NUI_COLOR_IMAGE_POINT
{
    LONG                x;
    LONG                y;
} NUI_COLOR_IMAGE_POINT;

#endif _NUI_COLOR_IMAGE_POINT_


#endif __NuiSensor_h__

// return S_FALSE instead of E_NUI_FRAME_NO_DATA if NuiImageStreamGetNextFrame( ) doesn't have a frame ready and a timeout != INFINITE is used
#define NUI_IMAGE_STREAM_FLAG_SUPPRESS_NO_FRAME_DATA              0x00010000
// Set the depth stream to near mode
#define NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE                    0x00020000
// Use distinct values for depth values that are either too close, too far or unknown
#define NUI_IMAGE_STREAM_FLAG_DISTINCT_OVERFLOW_DEPTH_VALUES      0x00040000

// the max # of NUI output frames you can hold w/o releasing
#define NUI_IMAGE_STREAM_FRAME_LIMIT_MAXIMUM 4

/// <summary>
/// Sets the image frame flags for the specified stream.
/// </summary>
/// <param name="hStream">A handle to the stream.</param>
/// <param name="dwImageFrameFlags">The image frame flags, as a bitwise-OR combination of the NUI_IMAGE_STREAM_FLAG constants.</param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="hStream"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// The maximum number of output frames you can set is defined by NUI_IMAGE_STREAM_FRAME_LIMIT_MAXIMUM.
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiImageStreamSetImageFrameFlags(
    _In_  HANDLE hStream,
    _In_  DWORD dwImageFrameFlags
    );

/// <summary>
/// Gets the image frame flags for the specified stream.
/// </summary>
/// <param name="hStream">A handle to the stream.</param>
/// <param name="pdwImageFrameFlags">A pointer to a DWORD that receives the image frame flags.</param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="hStream"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="pdwImageFrameFlags"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
_Check_return_ HRESULT NUIAPI NuiImageStreamGetImageFrameFlags(
    _In_  HANDLE hStream,
    _Out_  DWORD *pdwImageFrameFlags
    );

/// <summary>
/// Sets the event that signals the last frame.
/// </summary>
/// <param name="hEvent">A handle to the event.</param>
/// <param name="dwFrameEventFlag">
/// The frame event options, as a bitwise-OR combination of the NUI_IMAGE_STREAM_FLAG constants.
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
///       <description>The <paramref name="hEvent"/> parameter is an invalid handle.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>If the frame does not process any data, the event is still signaled unless you specify
/// NUI_FRAME_EVENT_FLAG_SUPPRESS_NO_FRAME_DATA.</para>
///
/// <para>The event provided is signaled after the NUI runtime is finished processing all data
/// associated with a frame. When you use NuiImageStreamGetNextFrame and NuiSkeletonGetNextFrame,
/// all stream data generated in that frame is available before the event is signaled.</para>
///
/// <para>This event is never reset by the NUI runtime because there is not a well-defined time to
/// do so. This is unlike the events provided to NuiImageStreamOpen and NuiSkeletonTrackingEnable.
/// Similarly, proper operation requires an auto-reset event, instead of a manual reset event.</para>
///
/// <para>When pumping multiple streams with a single thread, you should use a NuiSetFrameEndEvent
/// event over separate per-stream events.</para>
///
/// <para>The flag NUI_IMAGE_STREAM_FLAG_SUPPRESS_NO_FRAME_DATA still applies on a per-stream basis
/// when you call NuiImageStreamGetNextFrame provided you specify that flag for the stream in
/// NuiImageStreamOpen.</para>
///
/// <para>The flag NUI_SKELETON_TRACKING_FLAG_SUPPRESS_NO_FRAME_DATA still applies on a per-stream
/// basis when you call NuiSkeletonGetNextFrame provided you specify that flag for the stream in
/// NuiSkeletonTrackingEnable.</para>
///
/// <para>When processing multiple streams on multiple threads, it's more efficient to create a
/// separate event for each stream instead of using NuiSetFrameEndEvent. Using separate events
/// ensures that the app doesn't have to wait until processing for skeleton tracking is done before
/// it can get color and depth data.</para>
///
/// <para>For signaling when skeleton data is available, use an event in NuiSkeletonTrackingEnable.
/// For signaling when an image stream is available, use an event in NuiImageStreamOpen.</para>
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiSetFrameEndEvent(
    _In_ HANDLE hEvent,
    _In_ DWORD dwFrameEventFlag
    );

/// <summary>
/// Opens an image stream.
/// </summary>
/// <param name="eImageType">
/// A NUI_IMAGE_TYPE value that specifies which image stream to open. The valid values for this
/// parameter depend on the flags passed to the NuiInitialize method; for more information see
/// remarks.
/// </param>
/// <param name="eResolution">
/// A NUI_IMAGE_RESOLUTION value that specifies which resolution to use for the image stream. The
/// valid values for this parameter depend on the flags passed to the NuiInitialize method; for
/// more information, see remarks.
/// </param>
/// <param name="dwImageFrameFlags">
/// The stream options, as a bitwise-OR combination of the NUI_IMAGE_STREAM_FLAG constants.
/// </param>
/// <param name="dwFrameLimit">
/// The number of frames that the NUI runtime should buffer. The maximum value is
/// NUI_IMAGE_STREAM_FRAME_LIMIT_MAXIMUM. Most applications should use a frame limit of two.
/// </param>
/// <param name="hNextFrameEvent">
/// A handle to a manual reset event that will be fired when the next frame in the stream is
/// available.
/// </param>
/// <param name="phStreamHandle">
/// A pointer that receives a handle to the opened stream. This must not be NULL.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="dwFrameLimit"/> parameter is out of range.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device has not been initialized. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_OUTOFMEMORY</term>
///       <description>The <paramref name="hEvent"/> parameter is an invalid handle.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="hEvent"/> parameter is an invalid handle.</description>
///    </item>
///    <item>
///       <term>E_FAIL</term>
///       <description>An unspecified error occurred.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>The NUI runtime buffers the number of frames specified by the dwFrameLimit parameter. If
/// the application does not retrieve and release a frame before the buffer is full, the runtime
/// replaces the oldest frame in the buffer with an incoming frame. As a result, frames can
/// occasionally be dropped.</para>
///
/// <para>The valid values for the eImageType and eResolution parameters depend on the NUI
/// initialization flags passed to the NuiInitialize method in the dwFlags parameter. The following
/// tables summarize the combinations that are currently valid.</para>
///
/// <para>If <paramref name="dwFlags"/> includes NUI_INITIALIZE_FLAG_USES_DEPTH:
/// <list>
///    <listheader>
///       <term>NUI_IMAGE_TYPE value</term>
///       <description>NUI_IMAGE_RESOLUTION value</description>
///    </listheader>
///    <item>
///       <term>NUI_IMAGE_TYPE_DEPTH</term>
///       <description>NUI_IMAGE_RESOLUTION_640x480</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_DEPTH</term>
///       <description>NUI_IMAGE_RESOLUTION_320x240</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_DEPTH</term>
///       <description>NUI_IMAGE_RESOLUTION_80x60</description>
///    </item>
/// </list></para>
///
/// <para>If <paramref name="dwFlags"/> includes NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX:
/// <list>
///    <listheader>
///       <term>NUI_IMAGE_TYPE value</term>
///       <description>NUI_IMAGE_RESOLUTION value</description>
///    </listheader>
///    <item>
///       <term>NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX</term>
///       <description>NUI_IMAGE_RESOLUTION_320x240</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX</term>
///       <description>NUI_IMAGE_RESOLUTION_80x60</description>
///    </item>
/// </list></para>
///
/// <para>If <paramref name="dwFlags"/> includes NUI_INITIALIZE_FLAG_USES_COLOR:
/// <list>
///    <listheader>
///       <term>NUI_IMAGE_TYPE value</term>
///       <description>NUI_IMAGE_RESOLUTION value</description>
///    </listheader>
///    <item>
///       <term>NUI_IMAGE_TYPE_COLOR</term>
///       <description>NUI_IMAGE_RESOLUTION_1280x960</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_COLOR</term>
///       <description>NUI_IMAGE_RESOLUTION_640x480</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_COLOR_YUV</term>
///       <description>NUI_IMAGE_RESOLUTION_640x480</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_COLOR_RAW_YUV</term>
///       <description>NUI_IMAGE_RESOLUTION_640x480</description>
///    </item>
///    <item>
///       <term>NUI_IMAGE_TYPE_COLOR_INFRARED</term>
///       <description>NUI_IMAGE_RESOLUTION_640x480</description>
///    </item>
/// </list></para>
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiImageStreamOpen(
    _In_ NUI_IMAGE_TYPE eImageType,
    _In_ NUI_IMAGE_RESOLUTION eResolution,
    _In_ DWORD dwImageFrameFlags,
    _In_ DWORD dwFrameLimit,
    _In_opt_ HANDLE hNextFrameEvent,
    _Out_ HANDLE *phStreamHandle
    );

/// <summary>
/// Gets the next frame of data from the specified image stream.
/// </summary>
/// <param name="hStream">
/// A handle to the image stream. This stream must have been opened by a call to the
/// NuiImageStreamOpen method.
/// </param>
/// <param name="dwMillisecondsToWait">
/// The timeout (in milliseconds) before returning without a new frame.
/// </param>
/// <param name="pImageFrame">
/// A pointer to a NUI_IMAGE_FRAME structure that receives the next image frame in the specified
/// stream. The pFrameTexture member of the structure points to an INuiFrameTexture instance that
/// contains the frame data.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes: , .</para>
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>S_FALSE</term>
///       <description>The wait timeout expired before a new frame was available and <paramref name="hStream"/> was opened with the NUI_IMAGE_STREAM_FLAG_SUPPRESS_NO_FRAME_DATA flag.</description>
///    </item>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="hStream"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_NUI_FRAME_NO_DATA</term>
///       <description>The wait timeout expired before a new frame was available.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="pImageFrame"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
_Check_return_ HRESULT NUIAPI NuiImageStreamGetNextFrame(
    _In_  HANDLE hStream,
    _In_  DWORD dwMillisecondsToWait,
    _Deref_out_ CONST NUI_IMAGE_FRAME **ppcImageFrame
    );

/// <summary>
/// Releases the specified frame of data from the specified stream.
/// </summary>
/// <param name="hStream">
/// A handle to the image stream. This stream must have been opened by a call to the
/// NuiImageStreamOpen method.
/// </param>
/// <param name="pImageFrame">A pointer to the frame to release.</param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="hStream"/> or <paramref name="pImageFrame"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_NOINTERFACE</term>
///       <description>The <paramref name="pImageFrame"/> parameter's <c>pFrameTexture</c> member is NULL.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// Before you call this function, reset the notification event for the stream.
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiImageStreamReleaseFrame(
    _In_ HANDLE hStream,
    _In_ CONST NUI_IMAGE_FRAME *pImageFrame
    );

/// <summary>
/// Gets the pixel coordinates in color space that correspond to the specified pixel coordinates in
/// depth space.
/// </summary>
/// <param name="eColorResolution">
/// The resolution of the color image, as a NUI_IMAGE_RESOLUTION enumeration constant.
/// </param>
/// <param name="pcViewArea">
/// The optional zoom and pan settings of the color image, as a pointer to a NUI_IMAGE_VIEW_AREA
/// structure. To ensure that the settings are valid, use the ViewArea member of the NUI_IMAGE_FRAME
/// that you are registering pixels against. Do not instantiate and populate this structure manually.
/// </param>
/// <param name="lDepthX">The X coordinate in depth image space.</param>
/// <param name="lDepthY">The Y coordinate in depth image space.</param>
/// <param name="usDepthValue">
/// The depth value in depth image space. This value is constrained between NUI_IMAGE_DEPTH_MINIMUM
/// and NUI_IMAGE_DEPTH_MAXIMUM.
/// </param>
/// <param name="plColorX">
/// Pointer to a LONG value that receives the X coordinate of the pixel in color image space. This
/// pointer must be non-NULL when you call this function. If this method does not return S_OK, this
/// data is invalid. This value can be outside of the bounds of the color image.
/// </param>
/// <param name="plColorY">
/// Pointer to a LONG value that receives the Y coordinate of the pixel in color image space. This
/// pointer must be non-NULL when you call this function. If this method does not return S_OK, this
/// data is invalid. This value can be outside of the bounds of the color image.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="eColorResolution"/> parameter does not specify a valid resolution, or pcViewArea is provided but does not describe the full frame.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="plColorX"/> or <paramref name="plColorY"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>Because depth image data and color image data come from separate sensors, pixels in the
/// two images may not always line up exactly. The two sensors may have different fields of view,
/// or may not be aimed precisely in the same direction. This means that a point near the edge of
/// the depth image may correspond to a pixel just beyond the edge of the color image, or vice
/// versa.</para>
///
/// <para>This function accepts coordinates outside the bounds of the depth image. It may return
/// pixels outside the color image. This means that you can use data from the two images in
/// combination, even when the two images do not line up completely. You must verify that the
/// coordinates that are returned lie within the color image before using the coordinates to
/// reference pixels in that color image.</para>
///
/// <para>The depth image coordinates you specify are not required to be within the bounds of the
/// depth frame image, but they should not be too far outside the depth frame image bounds. If the
/// coordinates are far outside the depth frame image, they are unlikely to map to coordinates
/// inside the bounds of the color image. This function will then return color image coordinates
/// that are unlikely to be useful.</para>
/// </remarks>
/// <seealso cref="NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution"/>
_Check_return_ HRESULT NUIAPI NuiImageGetColorPixelCoordinatesFromDepthPixel(
    _In_ NUI_IMAGE_RESOLUTION eColorResolution,
    _In_opt_ CONST NUI_IMAGE_VIEW_AREA *pcViewArea,
    _In_ LONG   lDepthX,
    _In_ LONG   lDepthY,
    _In_ USHORT usDepthValue,
    _Out_ LONG *plColorX,
    _Out_ LONG *plColorY
    );

/// <summary>
/// Gets the pixel coordinates in color space that correspond to the specified pixel coordinates in
/// depth space, using the specified depth resolution.
/// </summary>
/// <param name="eColorResolution">
/// The resolution of the color image, as a NUI_IMAGE_RESOLUTION enumeration constant.
/// </param>
/// <param name="eDepthResolution">
/// The resolution of the depth image, as a NUI_IMAGE_RESOLUTION enumeration constant.
/// </param>
/// <param name="pcViewArea">
/// The optional zoom and pan settings of the color image, as a pointer to a NUI_IMAGE_VIEW_AREA
/// structure. To ensure that the settings are valid, use the ViewArea member of the NUI_IMAGE_FRAME
/// that you are registering pixels against. Do not instantiate and populate this structure manually.
/// </param>
/// <param name="lDepthX">The X coordinate in depth image space.</param>
/// <param name="lDepthY">The Y coordinate in depth image space.</param>
/// <param name="usDepthValue">
/// The depth value in depth image space. This value is constrained between NUI_IMAGE_DEPTH_MINIMUM
/// and NUI_IMAGE_DEPTH_MAXIMUM.
/// </param>
/// <param name="plColorX">
/// Pointer to a LONG value that receives the X coordinate of the pixel in color image space. This
/// pointer must be non-NULL when you call this function. If this method does not return S_OK, this
/// data is invalid. This value can be outside of the bounds of the color image.
/// </param>
/// <param name="plColorY">
/// Pointer to a LONG value that receives the Y coordinate of the pixel in color image space. This
/// pointer must be non-NULL when you call this function. If this method does not return S_OK, this
/// data is invalid. This value can be outside of the bounds of the color image.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="eColorResolution"/> or <paramref name="eDepthResolution"/> parameter does not specify a valid resolution, or pcViewArea is provided but does not describe the full frame.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="plColorX"/> or <paramref name="plColorY"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>Because depth image data and color image data come from separate sensors, pixels in the
/// two images may not always line up exactly. The two sensors may have different fields of view,
/// or may not be aimed precisely in the same direction. This means that a point near the edge of
/// the depth image may correspond to a pixel just beyond the edge of the color image, or vice
/// versa.</para>
///
/// <para>This function accepts coordinates outside the bounds of the depth image. It may return
/// pixels outside the color image. This means that you can use data from the two images in
/// combination, even when the two images do not line up completely. You must verify that the
/// coordinates that are returned lie within the color image before using the coordinates to
/// reference pixels in that color image.</para>
///
/// <para>The depth image coordinates you specify are not required to be within the bounds of the
/// depth frame image, but they should not be too far outside the depth frame image bounds. If the
/// coordinates are far outside the depth frame image, they are unlikely to map to coordinates
/// inside the bounds of the color image. This function will then return color image coordinates
/// that are unlikely to be useful.</para>
/// </remarks>
/// <seealso cref="NuiImageGetColorPixelCoordinatesFromDepthPixel"/>
_Check_return_ HRESULT NUIAPI NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
    _In_ NUI_IMAGE_RESOLUTION eColorResolution,
    _In_ NUI_IMAGE_RESOLUTION eDepthResolution,
    _In_opt_ CONST NUI_IMAGE_VIEW_AREA *pcViewArea,
    _In_ LONG   lDepthX,
    _In_ LONG   lDepthY,
    _In_ USHORT usDepthValue,
    _Out_ LONG *plColorX,
    _Out_ LONG *plColorY
    );    

#define NUI_CAMERA_ELEVATION_MAXIMUM  27
#define NUI_CAMERA_ELEVATION_MINIMUM (-27)

/// <summary>
/// Gets the elevation angle of the Kinect sensor.
/// </summary>
/// <param name="plAngleDegrees">Pointer to a LONG which receives the angle of the sensor in degrees.</param>
/// <returns>
/// Returs S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="plAngleDegrees"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>An elevation angle of zero indicates that the Kinect sensor is pointing perpendicular to
/// gravity. The tilt is relative to gravity rather than relative to the sensor base. The angle is
/// subject to the physical limitations of the sensor. If the sensor base is resting on a tilted
/// surface, the middle of the sensor's tilt range will not correspond to a tilt angle of zero, and
/// the sensor may not be physically capable of reaching the outer limits of the range allowed by
/// the API. If the sensor is moved so that the base is at a different angle relative to gravity,
/// or if the sensor is tilted manually, the angle reported by the API will change, even if the
/// tilt angle has not been changed programmatically.</para>
/// </remarks>
/// <seealso cref="NuiCameraElevationSetAngle"/>
_Check_return_ HRESULT NUIAPI NuiCameraElevationGetAngle(
    _Out_ LONG * plAngleDegrees
    );

/// <summary>
/// Sets the elevation angle of the Kinect sensor.
/// </summary>
/// <param name="lAngleDegrees">
/// The elevation angle relative to gravity, in degrees. A value of zero indicates that the sensor
/// array should point exactly horizontally. Positive values indicate that the sensor array should
/// point above the horizon, and negative values indicate that the sensor array should point below
/// the horizon. This value is constrained between NUI_CAMERA_ELEVATION_MINIMUM and
/// NUI_CAMERA_ELEVATION_MAXIMUM.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>__HRESULT_FROM_WIN32(ERROR_TOO_MANY_CMDS)</term>
///       <description>There were too many calls to <c>NuiCameraElevationSetAngle</c> within a given timespan.</description>
///    </item>
///    <item>
///       <term>__HRESULT_FROM_WIN32(ERROR_RETRY)</term>
///       <description>There was too little time between subsequent <c>NuiCameraElevationSetAngle</c> calls.</description>
///    </item>
///    <item>
///       <term>E_NUI_DEVICE_NOT_READY</term>
///       <description>The device is uninitialized. <see cref="NuiInitialize"/>.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>You should tilt the Kinect sensor as few times as possible, to minimize wear on the
/// sensor and to minimize tilting time. The tilt motor is not designed for constant or repetitive
/// movement, and attempts to use it that way can cause degradation of motor function. To reduce
/// wear on the Kinect sensor's tilt motor, your application can change the elevation angle no more
/// than once per second. In addition, you must allow at least 20 seconds of rest after 15
/// consecutive changes. If your application exceeds these limits, additional attempts to set the
/// elevation angle during the lockout period will result in an error code.</para>
/// 
/// <para>An elevation angle of zero indicates that the Kinect sensor is pointing perpendicular to
/// gravity. The tilt is relative to gravity rather than relative to the sensor base. The angle is
/// subject to the physical limitations of the sensor. If the sensor base is resting on a tilted
/// surface, the middle of the sensor's tilt range will not correspond to a tilt angle of zero, and
/// the sensor may not be physically capable of reaching the outer limits of the range allowed by
/// the API. If the sensor is moved so that the base is at a different angle relative to gravity,
/// or if the sensor is tilted manually, the angle reported by the API will change, even if the
/// tilt angle has not been changed programmatically.</para>
/// </remarks>
/// <seealso cref="NuiCameraElevationGetAngle"/>
_Check_return_ HRESULT NUIAPI NuiCameraElevationSetAngle(
    _In_ LONG lAngleDegrees
    );

#ifdef __cplusplus
} //close extern "C"
#endif

