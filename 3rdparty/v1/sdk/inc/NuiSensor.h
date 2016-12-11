

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Aug 20 15:14:52 2013
 */
/* Compiler settings for ..\inc_public\Kinect.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __NuiSensor_h__
#define __NuiSensor_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __INuiAudioBeam_FWD_DEFINED__
#define __INuiAudioBeam_FWD_DEFINED__
typedef interface INuiAudioBeam INuiAudioBeam;
#endif 	/* __INuiAudioBeam_FWD_DEFINED__ */


#ifndef __INuiFrameTexture_FWD_DEFINED__
#define __INuiFrameTexture_FWD_DEFINED__
typedef interface INuiFrameTexture INuiFrameTexture;
#endif 	/* __INuiFrameTexture_FWD_DEFINED__ */


#ifndef __INuiCoordinateMapperParametersChangedEvent_FWD_DEFINED__
#define __INuiCoordinateMapperParametersChangedEvent_FWD_DEFINED__
typedef interface INuiCoordinateMapperParametersChangedEvent INuiCoordinateMapperParametersChangedEvent;
#endif 	/* __INuiCoordinateMapperParametersChangedEvent_FWD_DEFINED__ */


#ifndef __INuiCoordinateMapper_FWD_DEFINED__
#define __INuiCoordinateMapper_FWD_DEFINED__
typedef interface INuiCoordinateMapper INuiCoordinateMapper;
#endif 	/* __INuiCoordinateMapper_FWD_DEFINED__ */


#ifndef __INuiColorCameraSettings_FWD_DEFINED__
#define __INuiColorCameraSettings_FWD_DEFINED__
typedef interface INuiColorCameraSettings INuiColorCameraSettings;
#endif 	/* __INuiColorCameraSettings_FWD_DEFINED__ */


#ifndef __INuiDepthFilter_FWD_DEFINED__
#define __INuiDepthFilter_FWD_DEFINED__
typedef interface INuiDepthFilter INuiDepthFilter;
#endif 	/* __INuiDepthFilter_FWD_DEFINED__ */


#ifndef __INuiSensor_FWD_DEFINED__
#define __INuiSensor_FWD_DEFINED__
typedef interface INuiSensor INuiSensor;
#endif 	/* __INuiSensor_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Kinect_0000_0000 */
/* [local] */ 

//----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#ifndef NUIAPI
#error "You must include nuiapi.h rather than including nuisensor.h directly"
#endif

#ifndef DEFINE_UUID
#define DEFINE_UUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) extern "C"  const GUID __declspec(selectany) name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#endif




// d3d9ab7b-31ba-44ca-8cc0-d42525bbea43
DEFINE_UUID(IID_INuiSensor,0xd3d9ab7b,0x31ba,0x44ca,0x8c,0xc0,0xd4,0x25,0x25,0xbb,0xea,0x43);

// 13ea17f5-ff2e-4670-9ee5-1297a6e880d1
DEFINE_UUID(IID_INuiFrameTexture,0x13ea17f5,0xff2e,0x4670,0x9e,0xe5,0x12,0x97,0xa6,0xe8,0x80,0xd1);

// {8c3cebfa-a35d-497e-bc9a-e9752a8155e0}
DEFINE_UUID(IID_INuiAudioBeam, 0x8c3cebfa, 0xa35d, 0x497e, 0xbc, 0x9a, 0xe9, 0x75, 0x2a, 0x81, 0x55, 0xe0);

// {1d7c07dd-2304-49bb-9b7f-2fdc6e00c1b2}
DEFINE_UUID(IID_INuiDepthFilter,0x1d7c07dd,0x2304,0x49bb,0x9b,0x7f,0x2f,0xdc,0x6e,0x00,0xc1,0xb2);

#define	NUI_SKELETON_COUNT	( 6 )

#ifndef _Vector4_
#define _Vector4_
typedef struct _Vector4
    {
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT w;
    } 	Vector4;

#endif _Vector4_
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
    } 	Matrix4;

#endif _Matrix4_

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

#endif _Vector4_Functions_

#endif // __XNAMATH_H__

#ifndef _NUI_SKELETON_POSITION_INDEX_
#define _NUI_SKELETON_POSITION_INDEX_
typedef 
enum _NUI_SKELETON_POSITION_INDEX
    {	NUI_SKELETON_POSITION_HIP_CENTER	= 0,
	NUI_SKELETON_POSITION_SPINE	= ( NUI_SKELETON_POSITION_HIP_CENTER + 1 ) ,
	NUI_SKELETON_POSITION_SHOULDER_CENTER	= ( NUI_SKELETON_POSITION_SPINE + 1 ) ,
	NUI_SKELETON_POSITION_HEAD	= ( NUI_SKELETON_POSITION_SHOULDER_CENTER + 1 ) ,
	NUI_SKELETON_POSITION_SHOULDER_LEFT	= ( NUI_SKELETON_POSITION_HEAD + 1 ) ,
	NUI_SKELETON_POSITION_ELBOW_LEFT	= ( NUI_SKELETON_POSITION_SHOULDER_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_WRIST_LEFT	= ( NUI_SKELETON_POSITION_ELBOW_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_HAND_LEFT	= ( NUI_SKELETON_POSITION_WRIST_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_SHOULDER_RIGHT	= ( NUI_SKELETON_POSITION_HAND_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_ELBOW_RIGHT	= ( NUI_SKELETON_POSITION_SHOULDER_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_WRIST_RIGHT	= ( NUI_SKELETON_POSITION_ELBOW_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_HAND_RIGHT	= ( NUI_SKELETON_POSITION_WRIST_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_HIP_LEFT	= ( NUI_SKELETON_POSITION_HAND_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_KNEE_LEFT	= ( NUI_SKELETON_POSITION_HIP_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_ANKLE_LEFT	= ( NUI_SKELETON_POSITION_KNEE_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_FOOT_LEFT	= ( NUI_SKELETON_POSITION_ANKLE_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_HIP_RIGHT	= ( NUI_SKELETON_POSITION_FOOT_LEFT + 1 ) ,
	NUI_SKELETON_POSITION_KNEE_RIGHT	= ( NUI_SKELETON_POSITION_HIP_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_ANKLE_RIGHT	= ( NUI_SKELETON_POSITION_KNEE_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_FOOT_RIGHT	= ( NUI_SKELETON_POSITION_ANKLE_RIGHT + 1 ) ,
	NUI_SKELETON_POSITION_COUNT	= ( NUI_SKELETON_POSITION_FOOT_RIGHT + 1 ) 
    } 	NUI_SKELETON_POSITION_INDEX;

#endif _NUI_SKELETON_POSITION_INDEX_
#ifndef _NUI_IMAGE_TYPE_
#define _NUI_IMAGE_TYPE_
typedef 
enum _NUI_IMAGE_TYPE
    {	NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX	= 0,
	NUI_IMAGE_TYPE_COLOR	= ( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX + 1 ) ,
	NUI_IMAGE_TYPE_COLOR_YUV	= ( NUI_IMAGE_TYPE_COLOR + 1 ) ,
	NUI_IMAGE_TYPE_COLOR_RAW_YUV	= ( NUI_IMAGE_TYPE_COLOR_YUV + 1 ) ,
	NUI_IMAGE_TYPE_DEPTH	= ( NUI_IMAGE_TYPE_COLOR_RAW_YUV + 1 ) ,
	NUI_IMAGE_TYPE_COLOR_INFRARED	= ( NUI_IMAGE_TYPE_DEPTH + 1 ) ,
	NUI_IMAGE_TYPE_COLOR_RAW_BAYER	= ( NUI_IMAGE_TYPE_COLOR_INFRARED + 1 ) 
    } 	NUI_IMAGE_TYPE;

#endif _NUI_IMAGE_TYPE_
#ifndef _NUI_IMAGE_RESOLUTION_
#define _NUI_IMAGE_RESOLUTION_
typedef 
enum _NUI_IMAGE_RESOLUTION
    {	NUI_IMAGE_RESOLUTION_INVALID	= -1,
	NUI_IMAGE_RESOLUTION_80x60	= 0,
	NUI_IMAGE_RESOLUTION_320x240	= ( NUI_IMAGE_RESOLUTION_80x60 + 1 ) ,
	NUI_IMAGE_RESOLUTION_640x480	= ( NUI_IMAGE_RESOLUTION_320x240 + 1 ) ,
	NUI_IMAGE_RESOLUTION_1280x960	= ( NUI_IMAGE_RESOLUTION_640x480 + 1 ) 
    } 	NUI_IMAGE_RESOLUTION;

#endif _NUI_IMAGE_RESOLUTION_
#ifndef _NUI_BACKLIGHT_COMPENSATION_MODE_
#define _NUI_BACKLIGHT_COMPENSATION_MODE_
typedef 
enum _NUI_BACKLIGHT_COMPENSATION_MODE
    {	NUI_BACKLIGHT_COMPENSATION_MODE_AVERAGE_BRIGHTNESS	= 0,
	NUI_BACKLIGHT_COMPENSATION_MODE_CENTER_PRIORITY	= 1,
	NUI_BACKLIGHT_COMPENSATION_MODE_LOWLIGHTS_PRIORITY	= 2,
	NUI_BACKLIGHT_COMPENSATION_MODE_CENTER_ONLY	= 4
    } 	NUI_BACKLIGHT_COMPENSATION_MODE;

#endif _NUI_BACKLIGHT_COMPENSATION_MODE_
#ifndef _NUI_POWER_LINE_FREQUENCY_
#define _NUI_POWER_LINE_FREQUENCY_
typedef 
enum _NUI_POWER_LINE_FREQUENCY
    {	NUI_POWER_LINE_FREQUENCY_DISABLED	= 0,
	NUI_POWER_LINE_FREQUENCY_50HZ	= 1,
	NUI_POWER_LINE_FREQUENCY_60HZ	= 2
    } 	NUI_POWER_LINE_FREQUENCY;

#endif _NUI_POWER_LINE_FREQUENCY_
#ifndef _NUI_IMAGE_VIEW_AREA_
#define _NUI_IMAGE_VIEW_AREA_
typedef struct _NUI_IMAGE_VIEW_AREA
    {
    int eDigitalZoom;
    LONG lCenterX;
    LONG lCenterY;
    } 	NUI_IMAGE_VIEW_AREA;

#endif _NUI_IMAGE_VIEW_AREA_
#ifndef _NUI_TRANSFORM_SMOOTH_PARAMETERS_
#define _NUI_TRANSFORM_SMOOTH_PARAMETERS_
typedef struct _NUI_TRANSFORM_SMOOTH_PARAMETERS
    {
    FLOAT fSmoothing;
    FLOAT fCorrection;
    FLOAT fPrediction;
    FLOAT fJitterRadius;
    FLOAT fMaxDeviationRadius;
    } 	NUI_TRANSFORM_SMOOTH_PARAMETERS;

#endif _NUI_TRANSFORM_SMOOTH_PARAMETERS_
#ifndef _NUI_SURFACE_DESC_
#define _NUI_SURFACE_DESC_
typedef struct _NUI_SURFACE_DESC
    {
    UINT Width;
    UINT Height;
    } 	NUI_SURFACE_DESC;

#endif _NUI_SURFACE_DESC_
#ifndef _NUI_SKELETON_POSITION_TRACKING_STATE_
#define _NUI_SKELETON_POSITION_TRACKING_STATE_
typedef 
enum _NUI_SKELETON_POSITION_TRACKING_STATE
    {	NUI_SKELETON_POSITION_NOT_TRACKED	= 0,
	NUI_SKELETON_POSITION_INFERRED	= ( NUI_SKELETON_POSITION_NOT_TRACKED + 1 ) ,
	NUI_SKELETON_POSITION_TRACKED	= ( NUI_SKELETON_POSITION_INFERRED + 1 ) 
    } 	NUI_SKELETON_POSITION_TRACKING_STATE;

#endif _NUI_SKELETON_POSITION_TRACKING_STATE_
#ifndef _NUI_SKELETON_TRACKING_STATE_
#define _NUI_SKELETON_TRACKING_STATE_
typedef 
enum _NUI_SKELETON_TRACKING_STATE
    {	NUI_SKELETON_NOT_TRACKED	= 0,
	NUI_SKELETON_POSITION_ONLY	= ( NUI_SKELETON_NOT_TRACKED + 1 ) ,
	NUI_SKELETON_TRACKED	= ( NUI_SKELETON_POSITION_ONLY + 1 ) 
    } 	NUI_SKELETON_TRACKING_STATE;

#endif _NUI_SKELETON_TRACKING_STATE_
#ifndef _NUI_SKELETON_DATA_
#define _NUI_SKELETON_DATA_
typedef struct _NUI_SKELETON_DATA
    {
    NUI_SKELETON_TRACKING_STATE eTrackingState;
    DWORD dwTrackingID;
    DWORD dwEnrollmentIndex;
    DWORD dwUserIndex;
    Vector4 Position;
    Vector4 SkeletonPositions[ 20 ];
    NUI_SKELETON_POSITION_TRACKING_STATE eSkeletonPositionTrackingState[ 20 ];
    DWORD dwQualityFlags;
    } 	NUI_SKELETON_DATA;

#endif _NUI_SKELETON_TRACKING_STATE_
#ifndef _NUI_SKELETON_FRAME_
#define _NUI_SKELETON_FRAME_

#pragma pack(push, 16)
typedef struct _NUI_SKELETON_FRAME
    {
    LARGE_INTEGER liTimeStamp;
    DWORD dwFrameNumber;
    DWORD dwFlags;
    Vector4 vFloorClipPlane;
    Vector4 vNormalToGravity;
    NUI_SKELETON_DATA SkeletonData[ 6 ];
    } 	NUI_SKELETON_FRAME;


#pragma pack(pop)
#endif _NUI_SKELETON_FRAME_
#ifndef _NUI_SKELETON_BONE_ROTATION_
#define _NUI_SKELETON_BONE_ROTATION_
typedef struct _NUI_SKELETON_BONE_ROTATION
    {
    Matrix4 rotationMatrix;
    Vector4 rotationQuaternion;
    } 	NUI_SKELETON_BONE_ROTATION;

#endif _NUI_SKELETON_BONE_ROTATION_
#ifndef _NUI_SKELETON_BONE_ORIENTATION_
#define _NUI_SKELETON_BONE_ORIENTATION_
typedef struct _NUI_SKELETON_BONE_ORIENTATION
    {
    NUI_SKELETON_POSITION_INDEX endJoint;
    NUI_SKELETON_POSITION_INDEX startJoint;
    NUI_SKELETON_BONE_ROTATION hierarchicalRotation;
    NUI_SKELETON_BONE_ROTATION absoluteRotation;
    } 	NUI_SKELETON_BONE_ORIENTATION;

#endif _NUI_SKELETON_BONE_ORIENTATION_
#ifndef _NUI_LOCKED_RECT_
#define _NUI_LOCKED_RECT_
#ifdef _MIDL_OUTPUT_
typedef struct _NUI_LOCKED_RECT
    {
    INT Pitch;
    INT size;
    void *pBits;
    } 	NUI_LOCKED_RECT;

#else
typedef struct _NUI_LOCKED_RECT
{
    INT                         Pitch;
    INT                         size;
    byte                        *pBits;
} NUI_LOCKED_RECT;
#endif _MIDL_OUTPUT_
#endif _NUI_LOCKED_RECT_
#ifndef _NUI_DEPTH_IMAGE_POINT_
#define _NUI_DEPTH_IMAGE_POINT_
typedef struct _NUI_DEPTH_IMAGE_POINT
    {
    LONG x;
    LONG y;
    LONG depth;
    LONG reserved;
    } 	NUI_DEPTH_IMAGE_POINT;

#endif _NUI_DEPTH_IMAGE_POINT_
#ifndef _NUI_COLOR_IMAGE_POINT_
#define _NUI_COLOR_IMAGE_POINT_
typedef struct _NUI_COLOR_IMAGE_POINT
    {
    LONG x;
    LONG y;
    } 	NUI_COLOR_IMAGE_POINT;

#endif _NUI_COLOR_IMAGE_POINT_
#define MICARRAY_ADAPTIVE_BEAM 0x1100


extern RPC_IF_HANDLE __MIDL_itf_Kinect_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Kinect_0000_0000_v0_0_s_ifspec;






/* [helpstring][version][uuid] */ 

#ifndef _NUI_IMAGE_FRAME_
#define _NUI_IMAGE_FRAME_
typedef struct _NUI_IMAGE_FRAME
    {
    LARGE_INTEGER liTimeStamp;
    DWORD dwFrameNumber;
    NUI_IMAGE_TYPE eImageType;
    NUI_IMAGE_RESOLUTION eResolution;
    INuiFrameTexture *pFrameTexture;
    DWORD dwFrameFlags;
    NUI_IMAGE_VIEW_AREA ViewArea;
    } 	NUI_IMAGE_FRAME;

#endif _NUI_IMAGE_FRAME_
#ifndef _NUI_DEPTH_IMAGE_PIXEL_
#define _NUI_DEPTH_IMAGE_PIXEL_
typedef struct _NUI_DEPTH_IMAGE_PIXEL
    {
    USHORT playerIndex;
    USHORT depth;
    } 	NUI_DEPTH_IMAGE_PIXEL;

#endif _NUI_DEPTH_IMAGE_PIXEL_




#ifndef __INuiAudioBeam_INTERFACE_DEFINED__
#define __INuiAudioBeam_INTERFACE_DEFINED__

/* interface INuiAudioBeam */
/* [object][uuid] */ 


EXTERN_C const IID IID_INuiAudioBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8C3CEBFA-A35D-497E-BC9A-E9752A8155E0")
    INuiAudioBeam : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetBeam( 
            /* [retval][out] */ double *angle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBeam( 
            /* [in] */ double angle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ double *angle,
            /* [out] */ double *confidence) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiAudioBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiAudioBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiAudioBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiAudioBeam * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBeam )( 
            INuiAudioBeam * This,
            /* [retval][out] */ double *angle);
        
        HRESULT ( STDMETHODCALLTYPE *SetBeam )( 
            INuiAudioBeam * This,
            /* [in] */ double angle);
        
        HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            INuiAudioBeam * This,
            /* [out] */ double *angle,
            /* [out] */ double *confidence);
        
        END_INTERFACE
    } INuiAudioBeamVtbl;

    interface INuiAudioBeam
    {
        CONST_VTBL struct INuiAudioBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiAudioBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiAudioBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiAudioBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiAudioBeam_GetBeam(This,angle)	\
    ( (This)->lpVtbl -> GetBeam(This,angle) ) 

#define INuiAudioBeam_SetBeam(This,angle)	\
    ( (This)->lpVtbl -> SetBeam(This,angle) ) 

#define INuiAudioBeam_GetPosition(This,angle,confidence)	\
    ( (This)->lpVtbl -> GetPosition(This,angle,confidence) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiAudioBeam_INTERFACE_DEFINED__ */


#ifndef __INuiFrameTexture_INTERFACE_DEFINED__
#define __INuiFrameTexture_INTERFACE_DEFINED__

/* interface INuiFrameTexture */
/* [object][uuid][local] */ 


EXTERN_C const IID IID_INuiFrameTexture;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13ea17f5-ff2e-4670-9ee5-1297a6e880d1")
    INuiFrameTexture : public IUnknown
    {
    public:
        virtual int STDMETHODCALLTYPE BufferLen( void) = 0;
        
        virtual int STDMETHODCALLTYPE Pitch( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LockRect( 
            UINT Level,
            /* [ref] */ NUI_LOCKED_RECT *pLockedRect,
            /* [unique] */ RECT *pRect,
            DWORD Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLevelDesc( 
            UINT Level,
            NUI_SURFACE_DESC *pDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnlockRect( 
            /* [in] */ UINT Level) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiFrameTextureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiFrameTexture * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiFrameTexture * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiFrameTexture * This);
        
        int ( STDMETHODCALLTYPE *BufferLen )( 
            INuiFrameTexture * This);
        
        int ( STDMETHODCALLTYPE *Pitch )( 
            INuiFrameTexture * This);
        
        HRESULT ( STDMETHODCALLTYPE *LockRect )( 
            INuiFrameTexture * This,
            UINT Level,
            /* [ref] */ NUI_LOCKED_RECT *pLockedRect,
            /* [unique] */ RECT *pRect,
            DWORD Flags);
        
        HRESULT ( STDMETHODCALLTYPE *GetLevelDesc )( 
            INuiFrameTexture * This,
            UINT Level,
            NUI_SURFACE_DESC *pDesc);
        
        HRESULT ( STDMETHODCALLTYPE *UnlockRect )( 
            INuiFrameTexture * This,
            /* [in] */ UINT Level);
        
        END_INTERFACE
    } INuiFrameTextureVtbl;

    interface INuiFrameTexture
    {
        CONST_VTBL struct INuiFrameTextureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiFrameTexture_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiFrameTexture_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiFrameTexture_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiFrameTexture_BufferLen(This)	\
    ( (This)->lpVtbl -> BufferLen(This) ) 

#define INuiFrameTexture_Pitch(This)	\
    ( (This)->lpVtbl -> Pitch(This) ) 

#define INuiFrameTexture_LockRect(This,Level,pLockedRect,pRect,Flags)	\
    ( (This)->lpVtbl -> LockRect(This,Level,pLockedRect,pRect,Flags) ) 

#define INuiFrameTexture_GetLevelDesc(This,Level,pDesc)	\
    ( (This)->lpVtbl -> GetLevelDesc(This,Level,pDesc) ) 

#define INuiFrameTexture_UnlockRect(This,Level)	\
    ( (This)->lpVtbl -> UnlockRect(This,Level) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiFrameTexture_INTERFACE_DEFINED__ */


#ifndef __INuiCoordinateMapperParametersChangedEvent_INTERFACE_DEFINED__
#define __INuiCoordinateMapperParametersChangedEvent_INTERFACE_DEFINED__

/* interface INuiCoordinateMapperParametersChangedEvent */
/* [object][local][uuid] */ 


EXTERN_C const IID IID_INuiCoordinateMapperParametersChangedEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BABEBBEC-C71B-4EE8-9F15-FC5C6C948622")
    INuiCoordinateMapperParametersChangedEvent : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Invoke( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiCoordinateMapperParametersChangedEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiCoordinateMapperParametersChangedEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiCoordinateMapperParametersChangedEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiCoordinateMapperParametersChangedEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            INuiCoordinateMapperParametersChangedEvent * This);
        
        END_INTERFACE
    } INuiCoordinateMapperParametersChangedEventVtbl;

    interface INuiCoordinateMapperParametersChangedEvent
    {
        CONST_VTBL struct INuiCoordinateMapperParametersChangedEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiCoordinateMapperParametersChangedEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiCoordinateMapperParametersChangedEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiCoordinateMapperParametersChangedEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiCoordinateMapperParametersChangedEvent_Invoke(This)	\
    ( (This)->lpVtbl -> Invoke(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiCoordinateMapperParametersChangedEvent_INTERFACE_DEFINED__ */


#ifndef __INuiCoordinateMapper_INTERFACE_DEFINED__
#define __INuiCoordinateMapper_INTERFACE_DEFINED__

/* interface INuiCoordinateMapper */
/* [object][local][uuid] */ 


EXTERN_C const IID IID_INuiCoordinateMapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("618E3670-BA84-4405-898A-3FF64446157C")
    INuiCoordinateMapper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetColorToDepthRelationalParameters( 
            /* [out] */ ULONG *pDataByteCount,
            /* [size_is][size_is][out] */ void **ppData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyParametersChanged( 
            /* [in] */ INuiCoordinateMapperParametersChangedEvent *pCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapColorFrameToDepthFrame( 
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ DWORD cDepthPoints,
            /* [size_is][out][in] */ NUI_DEPTH_IMAGE_POINT *pDepthPoints) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapColorFrameToSkeletonFrame( 
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ DWORD cSkeletonPoints,
            /* [size_is][out][in] */ Vector4 *pSkeletonPoints) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapDepthFrameToColorFrame( 
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ DWORD cColorPoints,
            /* [size_is][out][in] */ NUI_COLOR_IMAGE_POINT *pColorPoints) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapDepthFrameToSkeletonFrame( 
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ DWORD cSkeletonPoints,
            /* [size_is][out][in] */ Vector4 *pSkeletonPoints) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapDepthPointToColorPoint( 
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ NUI_DEPTH_IMAGE_POINT *pDepthPoint,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [out] */ NUI_COLOR_IMAGE_POINT *pColorPoint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapDepthPointToSkeletonPoint( 
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ NUI_DEPTH_IMAGE_POINT *pDepthPoint,
            /* [out] */ Vector4 *pSkeletonPoint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapSkeletonPointToColorPoint( 
            /* [in] */ Vector4 *pSkeletonPoint,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [out] */ NUI_COLOR_IMAGE_POINT *pColorPoint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapSkeletonPointToDepthPoint( 
            /* [in] */ Vector4 *pSkeletonPoint,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [out] */ NUI_DEPTH_IMAGE_POINT *pDepthPoint) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiCoordinateMapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiCoordinateMapper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiCoordinateMapper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiCoordinateMapper * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetColorToDepthRelationalParameters )( 
            INuiCoordinateMapper * This,
            /* [out] */ ULONG *pDataByteCount,
            /* [size_is][size_is][out] */ void **ppData);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyParametersChanged )( 
            INuiCoordinateMapper * This,
            /* [in] */ INuiCoordinateMapperParametersChangedEvent *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE *MapColorFrameToDepthFrame )( 
            INuiCoordinateMapper * This,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ DWORD cDepthPoints,
            /* [size_is][out][in] */ NUI_DEPTH_IMAGE_POINT *pDepthPoints);
        
        HRESULT ( STDMETHODCALLTYPE *MapColorFrameToSkeletonFrame )( 
            INuiCoordinateMapper * This,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ DWORD cSkeletonPoints,
            /* [size_is][out][in] */ Vector4 *pSkeletonPoints);
        
        HRESULT ( STDMETHODCALLTYPE *MapDepthFrameToColorFrame )( 
            INuiCoordinateMapper * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ DWORD cColorPoints,
            /* [size_is][out][in] */ NUI_COLOR_IMAGE_POINT *pColorPoints);
        
        HRESULT ( STDMETHODCALLTYPE *MapDepthFrameToSkeletonFrame )( 
            INuiCoordinateMapper * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthPixels,
            /* [size_is][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthPixels,
            /* [in] */ DWORD cSkeletonPoints,
            /* [size_is][out][in] */ Vector4 *pSkeletonPoints);
        
        HRESULT ( STDMETHODCALLTYPE *MapDepthPointToColorPoint )( 
            INuiCoordinateMapper * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ NUI_DEPTH_IMAGE_POINT *pDepthPoint,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [out] */ NUI_COLOR_IMAGE_POINT *pColorPoint);
        
        HRESULT ( STDMETHODCALLTYPE *MapDepthPointToSkeletonPoint )( 
            INuiCoordinateMapper * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ NUI_DEPTH_IMAGE_POINT *pDepthPoint,
            /* [out] */ Vector4 *pSkeletonPoint);
        
        HRESULT ( STDMETHODCALLTYPE *MapSkeletonPointToColorPoint )( 
            INuiCoordinateMapper * This,
            /* [in] */ Vector4 *pSkeletonPoint,
            /* [in] */ NUI_IMAGE_TYPE eColorType,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [out] */ NUI_COLOR_IMAGE_POINT *pColorPoint);
        
        HRESULT ( STDMETHODCALLTYPE *MapSkeletonPointToDepthPoint )( 
            INuiCoordinateMapper * This,
            /* [in] */ Vector4 *pSkeletonPoint,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [out] */ NUI_DEPTH_IMAGE_POINT *pDepthPoint);
        
        END_INTERFACE
    } INuiCoordinateMapperVtbl;

    interface INuiCoordinateMapper
    {
        CONST_VTBL struct INuiCoordinateMapperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiCoordinateMapper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiCoordinateMapper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiCoordinateMapper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiCoordinateMapper_GetColorToDepthRelationalParameters(This,pDataByteCount,ppData)	\
    ( (This)->lpVtbl -> GetColorToDepthRelationalParameters(This,pDataByteCount,ppData) ) 

#define INuiCoordinateMapper_NotifyParametersChanged(This,pCallback)	\
    ( (This)->lpVtbl -> NotifyParametersChanged(This,pCallback) ) 

#define INuiCoordinateMapper_MapColorFrameToDepthFrame(This,eColorType,eColorResolution,eDepthResolution,cDepthPixels,pDepthPixels,cDepthPoints,pDepthPoints)	\
    ( (This)->lpVtbl -> MapColorFrameToDepthFrame(This,eColorType,eColorResolution,eDepthResolution,cDepthPixels,pDepthPixels,cDepthPoints,pDepthPoints) ) 

#define INuiCoordinateMapper_MapColorFrameToSkeletonFrame(This,eColorType,eColorResolution,eDepthResolution,cDepthPixels,pDepthPixels,cSkeletonPoints,pSkeletonPoints)	\
    ( (This)->lpVtbl -> MapColorFrameToSkeletonFrame(This,eColorType,eColorResolution,eDepthResolution,cDepthPixels,pDepthPixels,cSkeletonPoints,pSkeletonPoints) ) 

#define INuiCoordinateMapper_MapDepthFrameToColorFrame(This,eDepthResolution,cDepthPixels,pDepthPixels,eColorType,eColorResolution,cColorPoints,pColorPoints)	\
    ( (This)->lpVtbl -> MapDepthFrameToColorFrame(This,eDepthResolution,cDepthPixels,pDepthPixels,eColorType,eColorResolution,cColorPoints,pColorPoints) ) 

#define INuiCoordinateMapper_MapDepthFrameToSkeletonFrame(This,eDepthResolution,cDepthPixels,pDepthPixels,cSkeletonPoints,pSkeletonPoints)	\
    ( (This)->lpVtbl -> MapDepthFrameToSkeletonFrame(This,eDepthResolution,cDepthPixels,pDepthPixels,cSkeletonPoints,pSkeletonPoints) ) 

#define INuiCoordinateMapper_MapDepthPointToColorPoint(This,eDepthResolution,pDepthPoint,eColorType,eColorResolution,pColorPoint)	\
    ( (This)->lpVtbl -> MapDepthPointToColorPoint(This,eDepthResolution,pDepthPoint,eColorType,eColorResolution,pColorPoint) ) 

#define INuiCoordinateMapper_MapDepthPointToSkeletonPoint(This,eDepthResolution,pDepthPoint,pSkeletonPoint)	\
    ( (This)->lpVtbl -> MapDepthPointToSkeletonPoint(This,eDepthResolution,pDepthPoint,pSkeletonPoint) ) 

#define INuiCoordinateMapper_MapSkeletonPointToColorPoint(This,pSkeletonPoint,eColorType,eColorResolution,pColorPoint)	\
    ( (This)->lpVtbl -> MapSkeletonPointToColorPoint(This,pSkeletonPoint,eColorType,eColorResolution,pColorPoint) ) 

#define INuiCoordinateMapper_MapSkeletonPointToDepthPoint(This,pSkeletonPoint,eDepthResolution,pDepthPoint)	\
    ( (This)->lpVtbl -> MapSkeletonPointToDepthPoint(This,pSkeletonPoint,eDepthResolution,pDepthPoint) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiCoordinateMapper_INTERFACE_DEFINED__ */


#ifndef __INuiColorCameraSettings_INTERFACE_DEFINED__
#define __INuiColorCameraSettings_INTERFACE_DEFINED__

/* interface INuiColorCameraSettings */
/* [object][local][uuid] */ 


EXTERN_C const IID IID_INuiColorCameraSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00a4b392-e315-470c-90b7-f7b4c3ce00c4")
    INuiColorCameraSettings : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAutoWhiteBalance( 
            /* [in] */ BOOL AutoWhiteBalanceEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAutoWhiteBalance( 
            /* [retval][out] */ BOOL *pAutoWhiteBalanceEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWhiteBalance( 
            /* [in] */ LONG WhiteBalance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWhiteBalance( 
            /* [retval][out] */ LONG *pWhiteBalance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinWhiteBalance( 
            /* [retval][out] */ LONG *pWhiteBalance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxWhiteBalance( 
            /* [retval][out] */ LONG *pWhiteBalance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetContrast( 
            /* [in] */ double Contrast) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContrast( 
            /* [retval][out] */ double *pContrast) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinContrast( 
            /* [retval][out] */ double *pContrast) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxContrast( 
            /* [retval][out] */ double *pContrast) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHue( 
            /* [in] */ double Hue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHue( 
            /* [retval][out] */ double *pHue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinHue( 
            /* [retval][out] */ double *pHue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxHue( 
            /* [retval][out] */ double *pHue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSaturation( 
            /* [in] */ double Saturation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSaturation( 
            /* [retval][out] */ double *pSaturation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinSaturation( 
            /* [retval][out] */ double *pSaturation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSaturation( 
            /* [retval][out] */ double *pSaturation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGamma( 
            /* [in] */ double Gamma) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGamma( 
            /* [retval][out] */ double *pGamma) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinGamma( 
            /* [retval][out] */ double *pGamma) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxGamma( 
            /* [retval][out] */ double *pGamma) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSharpness( 
            /* [in] */ double Sharpness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSharpness( 
            /* [retval][out] */ double *pSharpness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinSharpness( 
            /* [retval][out] */ double *pSharpness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSharpness( 
            /* [retval][out] */ double *pSharpness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAutoExposure( 
            /* [in] */ BOOL AutoExposureEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAutoExposure( 
            /* [retval][out] */ BOOL *pAutoExposureEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetExposureTime( 
            /* [in] */ double ExposureTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExposureTime( 
            /* [retval][out] */ double *pExposureTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinExposureTime( 
            /* [retval][out] */ double *pExposureTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxExposureTime( 
            /* [retval][out] */ double *pExposureTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFrameInterval( 
            /* [in] */ double FrameInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameInterval( 
            /* [retval][out] */ double *pFrameInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinFrameInterval( 
            /* [retval][out] */ double *pFrameInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxFrameInterval( 
            /* [retval][out] */ double *pFrameInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBrightness( 
            /* [in] */ double Brightness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBrightness( 
            /* [retval][out] */ double *pBrightness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinBrightness( 
            /* [retval][out] */ double *pBrightness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxBrightness( 
            /* [retval][out] */ double *pBrightness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPowerLineFrequency( 
            /* [in] */ NUI_POWER_LINE_FREQUENCY PowerLineFrequency) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPowerLineFrequency( 
            /* [retval][out] */ NUI_POWER_LINE_FREQUENCY *pPowerLineFrequency) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompensationMode( 
            /* [in] */ NUI_BACKLIGHT_COMPENSATION_MODE BacklightCompensationMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompensationMode( 
            /* [retval][out] */ NUI_BACKLIGHT_COMPENSATION_MODE *pBacklightCompensationMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGain( 
            /* [in] */ double Gain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGain( 
            /* [retval][out] */ double *pGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinGain( 
            /* [retval][out] */ double *pGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxGain( 
            /* [retval][out] */ double *pGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetCameraSettingsToDefault( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiColorCameraSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiColorCameraSettings * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiColorCameraSettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiColorCameraSettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAutoWhiteBalance )( 
            INuiColorCameraSettings * This,
            /* [in] */ BOOL AutoWhiteBalanceEnabled);
        
        HRESULT ( STDMETHODCALLTYPE *GetAutoWhiteBalance )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ BOOL *pAutoWhiteBalanceEnabled);
        
        HRESULT ( STDMETHODCALLTYPE *SetWhiteBalance )( 
            INuiColorCameraSettings * This,
            /* [in] */ LONG WhiteBalance);
        
        HRESULT ( STDMETHODCALLTYPE *GetWhiteBalance )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ LONG *pWhiteBalance);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinWhiteBalance )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ LONG *pWhiteBalance);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxWhiteBalance )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ LONG *pWhiteBalance);
        
        HRESULT ( STDMETHODCALLTYPE *SetContrast )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Contrast);
        
        HRESULT ( STDMETHODCALLTYPE *GetContrast )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pContrast);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinContrast )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pContrast);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxContrast )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pContrast);
        
        HRESULT ( STDMETHODCALLTYPE *SetHue )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Hue);
        
        HRESULT ( STDMETHODCALLTYPE *GetHue )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pHue);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinHue )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pHue);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxHue )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pHue);
        
        HRESULT ( STDMETHODCALLTYPE *SetSaturation )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Saturation);
        
        HRESULT ( STDMETHODCALLTYPE *GetSaturation )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pSaturation);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinSaturation )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pSaturation);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxSaturation )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pSaturation);
        
        HRESULT ( STDMETHODCALLTYPE *SetGamma )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Gamma);
        
        HRESULT ( STDMETHODCALLTYPE *GetGamma )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pGamma);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinGamma )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pGamma);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxGamma )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pGamma);
        
        HRESULT ( STDMETHODCALLTYPE *SetSharpness )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Sharpness);
        
        HRESULT ( STDMETHODCALLTYPE *GetSharpness )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pSharpness);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinSharpness )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pSharpness);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxSharpness )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pSharpness);
        
        HRESULT ( STDMETHODCALLTYPE *SetAutoExposure )( 
            INuiColorCameraSettings * This,
            /* [in] */ BOOL AutoExposureEnabled);
        
        HRESULT ( STDMETHODCALLTYPE *GetAutoExposure )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ BOOL *pAutoExposureEnabled);
        
        HRESULT ( STDMETHODCALLTYPE *SetExposureTime )( 
            INuiColorCameraSettings * This,
            /* [in] */ double ExposureTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetExposureTime )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pExposureTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinExposureTime )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pExposureTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxExposureTime )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pExposureTime);
        
        HRESULT ( STDMETHODCALLTYPE *SetFrameInterval )( 
            INuiColorCameraSettings * This,
            /* [in] */ double FrameInterval);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameInterval )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pFrameInterval);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinFrameInterval )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pFrameInterval);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxFrameInterval )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pFrameInterval);
        
        HRESULT ( STDMETHODCALLTYPE *SetBrightness )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Brightness);
        
        HRESULT ( STDMETHODCALLTYPE *GetBrightness )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pBrightness);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinBrightness )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pBrightness);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxBrightness )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pBrightness);
        
        HRESULT ( STDMETHODCALLTYPE *SetPowerLineFrequency )( 
            INuiColorCameraSettings * This,
            /* [in] */ NUI_POWER_LINE_FREQUENCY PowerLineFrequency);
        
        HRESULT ( STDMETHODCALLTYPE *GetPowerLineFrequency )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ NUI_POWER_LINE_FREQUENCY *pPowerLineFrequency);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompensationMode )( 
            INuiColorCameraSettings * This,
            /* [in] */ NUI_BACKLIGHT_COMPENSATION_MODE BacklightCompensationMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompensationMode )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ NUI_BACKLIGHT_COMPENSATION_MODE *pBacklightCompensationMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetGain )( 
            INuiColorCameraSettings * This,
            /* [in] */ double Gain);
        
        HRESULT ( STDMETHODCALLTYPE *GetGain )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetMinGain )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxGain )( 
            INuiColorCameraSettings * This,
            /* [retval][out] */ double *pGain);
        
        HRESULT ( STDMETHODCALLTYPE *ResetCameraSettingsToDefault )( 
            INuiColorCameraSettings * This);
        
        END_INTERFACE
    } INuiColorCameraSettingsVtbl;

    interface INuiColorCameraSettings
    {
        CONST_VTBL struct INuiColorCameraSettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiColorCameraSettings_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiColorCameraSettings_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiColorCameraSettings_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiColorCameraSettings_SetAutoWhiteBalance(This,AutoWhiteBalanceEnabled)	\
    ( (This)->lpVtbl -> SetAutoWhiteBalance(This,AutoWhiteBalanceEnabled) ) 

#define INuiColorCameraSettings_GetAutoWhiteBalance(This,pAutoWhiteBalanceEnabled)	\
    ( (This)->lpVtbl -> GetAutoWhiteBalance(This,pAutoWhiteBalanceEnabled) ) 

#define INuiColorCameraSettings_SetWhiteBalance(This,WhiteBalance)	\
    ( (This)->lpVtbl -> SetWhiteBalance(This,WhiteBalance) ) 

#define INuiColorCameraSettings_GetWhiteBalance(This,pWhiteBalance)	\
    ( (This)->lpVtbl -> GetWhiteBalance(This,pWhiteBalance) ) 

#define INuiColorCameraSettings_GetMinWhiteBalance(This,pWhiteBalance)	\
    ( (This)->lpVtbl -> GetMinWhiteBalance(This,pWhiteBalance) ) 

#define INuiColorCameraSettings_GetMaxWhiteBalance(This,pWhiteBalance)	\
    ( (This)->lpVtbl -> GetMaxWhiteBalance(This,pWhiteBalance) ) 

#define INuiColorCameraSettings_SetContrast(This,Contrast)	\
    ( (This)->lpVtbl -> SetContrast(This,Contrast) ) 

#define INuiColorCameraSettings_GetContrast(This,pContrast)	\
    ( (This)->lpVtbl -> GetContrast(This,pContrast) ) 

#define INuiColorCameraSettings_GetMinContrast(This,pContrast)	\
    ( (This)->lpVtbl -> GetMinContrast(This,pContrast) ) 

#define INuiColorCameraSettings_GetMaxContrast(This,pContrast)	\
    ( (This)->lpVtbl -> GetMaxContrast(This,pContrast) ) 

#define INuiColorCameraSettings_SetHue(This,Hue)	\
    ( (This)->lpVtbl -> SetHue(This,Hue) ) 

#define INuiColorCameraSettings_GetHue(This,pHue)	\
    ( (This)->lpVtbl -> GetHue(This,pHue) ) 

#define INuiColorCameraSettings_GetMinHue(This,pHue)	\
    ( (This)->lpVtbl -> GetMinHue(This,pHue) ) 

#define INuiColorCameraSettings_GetMaxHue(This,pHue)	\
    ( (This)->lpVtbl -> GetMaxHue(This,pHue) ) 

#define INuiColorCameraSettings_SetSaturation(This,Saturation)	\
    ( (This)->lpVtbl -> SetSaturation(This,Saturation) ) 

#define INuiColorCameraSettings_GetSaturation(This,pSaturation)	\
    ( (This)->lpVtbl -> GetSaturation(This,pSaturation) ) 

#define INuiColorCameraSettings_GetMinSaturation(This,pSaturation)	\
    ( (This)->lpVtbl -> GetMinSaturation(This,pSaturation) ) 

#define INuiColorCameraSettings_GetMaxSaturation(This,pSaturation)	\
    ( (This)->lpVtbl -> GetMaxSaturation(This,pSaturation) ) 

#define INuiColorCameraSettings_SetGamma(This,Gamma)	\
    ( (This)->lpVtbl -> SetGamma(This,Gamma) ) 

#define INuiColorCameraSettings_GetGamma(This,pGamma)	\
    ( (This)->lpVtbl -> GetGamma(This,pGamma) ) 

#define INuiColorCameraSettings_GetMinGamma(This,pGamma)	\
    ( (This)->lpVtbl -> GetMinGamma(This,pGamma) ) 

#define INuiColorCameraSettings_GetMaxGamma(This,pGamma)	\
    ( (This)->lpVtbl -> GetMaxGamma(This,pGamma) ) 

#define INuiColorCameraSettings_SetSharpness(This,Sharpness)	\
    ( (This)->lpVtbl -> SetSharpness(This,Sharpness) ) 

#define INuiColorCameraSettings_GetSharpness(This,pSharpness)	\
    ( (This)->lpVtbl -> GetSharpness(This,pSharpness) ) 

#define INuiColorCameraSettings_GetMinSharpness(This,pSharpness)	\
    ( (This)->lpVtbl -> GetMinSharpness(This,pSharpness) ) 

#define INuiColorCameraSettings_GetMaxSharpness(This,pSharpness)	\
    ( (This)->lpVtbl -> GetMaxSharpness(This,pSharpness) ) 

#define INuiColorCameraSettings_SetAutoExposure(This,AutoExposureEnabled)	\
    ( (This)->lpVtbl -> SetAutoExposure(This,AutoExposureEnabled) ) 

#define INuiColorCameraSettings_GetAutoExposure(This,pAutoExposureEnabled)	\
    ( (This)->lpVtbl -> GetAutoExposure(This,pAutoExposureEnabled) ) 

#define INuiColorCameraSettings_SetExposureTime(This,ExposureTime)	\
    ( (This)->lpVtbl -> SetExposureTime(This,ExposureTime) ) 

#define INuiColorCameraSettings_GetExposureTime(This,pExposureTime)	\
    ( (This)->lpVtbl -> GetExposureTime(This,pExposureTime) ) 

#define INuiColorCameraSettings_GetMinExposureTime(This,pExposureTime)	\
    ( (This)->lpVtbl -> GetMinExposureTime(This,pExposureTime) ) 

#define INuiColorCameraSettings_GetMaxExposureTime(This,pExposureTime)	\
    ( (This)->lpVtbl -> GetMaxExposureTime(This,pExposureTime) ) 

#define INuiColorCameraSettings_SetFrameInterval(This,FrameInterval)	\
    ( (This)->lpVtbl -> SetFrameInterval(This,FrameInterval) ) 

#define INuiColorCameraSettings_GetFrameInterval(This,pFrameInterval)	\
    ( (This)->lpVtbl -> GetFrameInterval(This,pFrameInterval) ) 

#define INuiColorCameraSettings_GetMinFrameInterval(This,pFrameInterval)	\
    ( (This)->lpVtbl -> GetMinFrameInterval(This,pFrameInterval) ) 

#define INuiColorCameraSettings_GetMaxFrameInterval(This,pFrameInterval)	\
    ( (This)->lpVtbl -> GetMaxFrameInterval(This,pFrameInterval) ) 

#define INuiColorCameraSettings_SetBrightness(This,Brightness)	\
    ( (This)->lpVtbl -> SetBrightness(This,Brightness) ) 

#define INuiColorCameraSettings_GetBrightness(This,pBrightness)	\
    ( (This)->lpVtbl -> GetBrightness(This,pBrightness) ) 

#define INuiColorCameraSettings_GetMinBrightness(This,pBrightness)	\
    ( (This)->lpVtbl -> GetMinBrightness(This,pBrightness) ) 

#define INuiColorCameraSettings_GetMaxBrightness(This,pBrightness)	\
    ( (This)->lpVtbl -> GetMaxBrightness(This,pBrightness) ) 

#define INuiColorCameraSettings_SetPowerLineFrequency(This,PowerLineFrequency)	\
    ( (This)->lpVtbl -> SetPowerLineFrequency(This,PowerLineFrequency) ) 

#define INuiColorCameraSettings_GetPowerLineFrequency(This,pPowerLineFrequency)	\
    ( (This)->lpVtbl -> GetPowerLineFrequency(This,pPowerLineFrequency) ) 

#define INuiColorCameraSettings_SetBacklightCompensationMode(This,BacklightCompensationMode)	\
    ( (This)->lpVtbl -> SetBacklightCompensationMode(This,BacklightCompensationMode) ) 

#define INuiColorCameraSettings_GetBacklightCompensationMode(This,pBacklightCompensationMode)	\
    ( (This)->lpVtbl -> GetBacklightCompensationMode(This,pBacklightCompensationMode) ) 

#define INuiColorCameraSettings_SetGain(This,Gain)	\
    ( (This)->lpVtbl -> SetGain(This,Gain) ) 

#define INuiColorCameraSettings_GetGain(This,pGain)	\
    ( (This)->lpVtbl -> GetGain(This,pGain) ) 

#define INuiColorCameraSettings_GetMinGain(This,pGain)	\
    ( (This)->lpVtbl -> GetMinGain(This,pGain) ) 

#define INuiColorCameraSettings_GetMaxGain(This,pGain)	\
    ( (This)->lpVtbl -> GetMaxGain(This,pGain) ) 

#define INuiColorCameraSettings_ResetCameraSettingsToDefault(This)	\
    ( (This)->lpVtbl -> ResetCameraSettingsToDefault(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiColorCameraSettings_INTERFACE_DEFINED__ */


#ifndef __INuiDepthFilter_INTERFACE_DEFINED__
#define __INuiDepthFilter_INTERFACE_DEFINED__

/* interface INuiDepthFilter */
/* [object][local][uuid] */ 


EXTERN_C const IID IID_INuiDepthFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D7C07DD-2304-49BB-9B7F-2FDC6E00C1B2")
    INuiDepthFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ProcessFrame( 
            /* [in] */ LARGE_INTEGER liTimeStamp,
            /* [in] */ UINT width,
            /* [in] */ UINT height,
            /* [size_is][out][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthImagePixels,
            /* [out] */ BOOL *pFrameModified) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiDepthFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiDepthFilter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiDepthFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiDepthFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessFrame )( 
            INuiDepthFilter * This,
            /* [in] */ LARGE_INTEGER liTimeStamp,
            /* [in] */ UINT width,
            /* [in] */ UINT height,
            /* [size_is][out][in] */ NUI_DEPTH_IMAGE_PIXEL *pDepthImagePixels,
            /* [out] */ BOOL *pFrameModified);
        
        END_INTERFACE
    } INuiDepthFilterVtbl;

    interface INuiDepthFilter
    {
        CONST_VTBL struct INuiDepthFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiDepthFilter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiDepthFilter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiDepthFilter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiDepthFilter_ProcessFrame(This,liTimeStamp,width,height,pDepthImagePixels,pFrameModified)	\
    ( (This)->lpVtbl -> ProcessFrame(This,liTimeStamp,width,height,pDepthImagePixels,pFrameModified) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiDepthFilter_INTERFACE_DEFINED__ */


#ifndef __INuiSensor_INTERFACE_DEFINED__
#define __INuiSensor_INTERFACE_DEFINED__

/* interface INuiSensor */
/* [object][local][uuid] */ 


EXTERN_C const IID IID_INuiSensor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d3d9ab7b-31ba-44ca-8cc0-d42525bbea43")
    INuiSensor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NuiInitialize( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual void STDMETHODCALLTYPE NuiShutdown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSetFrameEndEvent( 
            /* [in] */ HANDLE hEvent,
            /* [in] */ DWORD dwFrameEventFlag) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageStreamOpen( 
            /* [in] */ NUI_IMAGE_TYPE eImageType,
            /* [in] */ NUI_IMAGE_RESOLUTION eResolution,
            /* [in] */ DWORD dwImageFrameFlags,
            /* [in] */ DWORD dwFrameLimit,
            /* [in] */ HANDLE hNextFrameEvent,
            /* [out] */ HANDLE *phStreamHandle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageStreamSetImageFrameFlags( 
            /* [in] */ HANDLE hStream,
            /* [in] */ DWORD dwImageFrameFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageStreamGetImageFrameFlags( 
            /* [in] */ HANDLE hStream,
            /* [retval][out] */ DWORD *pdwImageFrameFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageStreamGetNextFrame( 
            /* [in] */ HANDLE hStream,
            /* [in] */ DWORD dwMillisecondsToWait,
            /* [retval][out] */ NUI_IMAGE_FRAME *pImageFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageStreamReleaseFrame( 
            /* [in] */ HANDLE hStream,
            /* [in] */ NUI_IMAGE_FRAME *pImageFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageGetColorPixelCoordinatesFromDepthPixel( 
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ const NUI_IMAGE_VIEW_AREA *pcViewArea,
            /* [in] */ LONG lDepthX,
            /* [in] */ LONG lDepthY,
            /* [in] */ USHORT usDepthValue,
            /* [out] */ LONG *plColorX,
            /* [out] */ LONG *plColorY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution( 
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ const NUI_IMAGE_VIEW_AREA *pcViewArea,
            /* [in] */ LONG lDepthX,
            /* [in] */ LONG lDepthY,
            /* [in] */ USHORT usDepthValue,
            /* [out] */ LONG *plColorX,
            /* [out] */ LONG *plColorY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageGetColorPixelCoordinateFrameFromDepthPixelFrameAtResolution( 
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthValues,
            /* [size_is][in] */ USHORT *pDepthValues,
            /* [in] */ DWORD cColorCoordinates,
            /* [size_is][out][in] */ LONG *pColorCoordinates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiCameraElevationSetAngle( 
            /* [in] */ LONG lAngleDegrees) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiCameraElevationGetAngle( 
            /* [retval][out] */ LONG *plAngleDegrees) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSkeletonTrackingEnable( 
            /* [in] */ HANDLE hNextFrameEvent,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSkeletonTrackingDisable( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSkeletonSetTrackedSkeletons( 
            /* [size_is][in] */ DWORD *TrackingIDs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSkeletonGetNextFrame( 
            /* [in] */ DWORD dwMillisecondsToWait,
            /* [out][in] */ NUI_SKELETON_FRAME *pSkeletonFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiTransformSmooth( 
            NUI_SKELETON_FRAME *pSkeletonFrame,
            const NUI_TRANSFORM_SMOOTH_PARAMETERS *pSmoothingParams) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NuiGetAudioSource( 
            /* [out] */ INuiAudioBeam **ppDmo) = 0;
        
        virtual int STDMETHODCALLTYPE NuiInstanceIndex( void) = 0;
        
        virtual BSTR STDMETHODCALLTYPE NuiDeviceConnectionId( void) = 0;
        
        virtual BSTR STDMETHODCALLTYPE NuiUniqueId( void) = 0;
        
        virtual BSTR STDMETHODCALLTYPE NuiAudioArrayId( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiStatus( void) = 0;
        
        virtual DWORD STDMETHODCALLTYPE NuiInitializationFlags( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiGetCoordinateMapper( 
            /* [retval][out] */ INuiCoordinateMapper **pMapping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiImageFrameGetDepthImagePixelFrameTexture( 
            /* [in] */ HANDLE hStream,
            /* [in] */ NUI_IMAGE_FRAME *pImageFrame,
            /* [out] */ BOOL *pNearMode,
            /* [out] */ INuiFrameTexture **ppFrameTexture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiGetColorCameraSettings( 
            /* [retval][out] */ INuiColorCameraSettings **pCameraSettings) = 0;
        
        virtual BOOL STDMETHODCALLTYPE NuiGetForceInfraredEmitterOff( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSetForceInfraredEmitterOff( 
            /* [in] */ BOOL fForceInfraredEmitterOff) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiAccelerometerGetCurrentReading( 
            /* [retval][out] */ Vector4 *pReading) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiSetDepthFilter( 
            /* [in] */ INuiDepthFilter *pDepthFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiGetDepthFilter( 
            /* [retval][out] */ INuiDepthFilter **ppDepthFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NuiGetDepthFilterForTimeStamp( 
            /* [in] */ LARGE_INTEGER liTimeStamp,
            /* [retval][out] */ INuiDepthFilter **ppDepthFilter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INuiSensorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INuiSensor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INuiSensor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INuiSensor * This);
        
        HRESULT ( STDMETHODCALLTYPE *NuiInitialize )( 
            INuiSensor * This,
            /* [in] */ DWORD dwFlags);
        
        void ( STDMETHODCALLTYPE *NuiShutdown )( 
            INuiSensor * This);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSetFrameEndEvent )( 
            INuiSensor * This,
            /* [in] */ HANDLE hEvent,
            /* [in] */ DWORD dwFrameEventFlag);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageStreamOpen )( 
            INuiSensor * This,
            /* [in] */ NUI_IMAGE_TYPE eImageType,
            /* [in] */ NUI_IMAGE_RESOLUTION eResolution,
            /* [in] */ DWORD dwImageFrameFlags,
            /* [in] */ DWORD dwFrameLimit,
            /* [in] */ HANDLE hNextFrameEvent,
            /* [out] */ HANDLE *phStreamHandle);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageStreamSetImageFrameFlags )( 
            INuiSensor * This,
            /* [in] */ HANDLE hStream,
            /* [in] */ DWORD dwImageFrameFlags);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageStreamGetImageFrameFlags )( 
            INuiSensor * This,
            /* [in] */ HANDLE hStream,
            /* [retval][out] */ DWORD *pdwImageFrameFlags);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageStreamGetNextFrame )( 
            INuiSensor * This,
            /* [in] */ HANDLE hStream,
            /* [in] */ DWORD dwMillisecondsToWait,
            /* [retval][out] */ NUI_IMAGE_FRAME *pImageFrame);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageStreamReleaseFrame )( 
            INuiSensor * This,
            /* [in] */ HANDLE hStream,
            /* [in] */ NUI_IMAGE_FRAME *pImageFrame);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageGetColorPixelCoordinatesFromDepthPixel )( 
            INuiSensor * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ const NUI_IMAGE_VIEW_AREA *pcViewArea,
            /* [in] */ LONG lDepthX,
            /* [in] */ LONG lDepthY,
            /* [in] */ USHORT usDepthValue,
            /* [out] */ LONG *plColorX,
            /* [out] */ LONG *plColorY);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution )( 
            INuiSensor * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ const NUI_IMAGE_VIEW_AREA *pcViewArea,
            /* [in] */ LONG lDepthX,
            /* [in] */ LONG lDepthY,
            /* [in] */ USHORT usDepthValue,
            /* [out] */ LONG *plColorX,
            /* [out] */ LONG *plColorY);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageGetColorPixelCoordinateFrameFromDepthPixelFrameAtResolution )( 
            INuiSensor * This,
            /* [in] */ NUI_IMAGE_RESOLUTION eColorResolution,
            /* [in] */ NUI_IMAGE_RESOLUTION eDepthResolution,
            /* [in] */ DWORD cDepthValues,
            /* [size_is][in] */ USHORT *pDepthValues,
            /* [in] */ DWORD cColorCoordinates,
            /* [size_is][out][in] */ LONG *pColorCoordinates);
        
        HRESULT ( STDMETHODCALLTYPE *NuiCameraElevationSetAngle )( 
            INuiSensor * This,
            /* [in] */ LONG lAngleDegrees);
        
        HRESULT ( STDMETHODCALLTYPE *NuiCameraElevationGetAngle )( 
            INuiSensor * This,
            /* [retval][out] */ LONG *plAngleDegrees);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSkeletonTrackingEnable )( 
            INuiSensor * This,
            /* [in] */ HANDLE hNextFrameEvent,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSkeletonTrackingDisable )( 
            INuiSensor * This);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSkeletonSetTrackedSkeletons )( 
            INuiSensor * This,
            /* [size_is][in] */ DWORD *TrackingIDs);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSkeletonGetNextFrame )( 
            INuiSensor * This,
            /* [in] */ DWORD dwMillisecondsToWait,
            /* [out][in] */ NUI_SKELETON_FRAME *pSkeletonFrame);
        
        HRESULT ( STDMETHODCALLTYPE *NuiTransformSmooth )( 
            INuiSensor * This,
            NUI_SKELETON_FRAME *pSkeletonFrame,
            const NUI_TRANSFORM_SMOOTH_PARAMETERS *pSmoothingParams);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NuiGetAudioSource )( 
            INuiSensor * This,
            /* [out] */ INuiAudioBeam **ppDmo);
        
        int ( STDMETHODCALLTYPE *NuiInstanceIndex )( 
            INuiSensor * This);
        
        BSTR ( STDMETHODCALLTYPE *NuiDeviceConnectionId )( 
            INuiSensor * This);
        
        BSTR ( STDMETHODCALLTYPE *NuiUniqueId )( 
            INuiSensor * This);
        
        BSTR ( STDMETHODCALLTYPE *NuiAudioArrayId )( 
            INuiSensor * This);
        
        HRESULT ( STDMETHODCALLTYPE *NuiStatus )( 
            INuiSensor * This);
        
        DWORD ( STDMETHODCALLTYPE *NuiInitializationFlags )( 
            INuiSensor * This);
        
        HRESULT ( STDMETHODCALLTYPE *NuiGetCoordinateMapper )( 
            INuiSensor * This,
            /* [retval][out] */ INuiCoordinateMapper **pMapping);
        
        HRESULT ( STDMETHODCALLTYPE *NuiImageFrameGetDepthImagePixelFrameTexture )( 
            INuiSensor * This,
            /* [in] */ HANDLE hStream,
            /* [in] */ NUI_IMAGE_FRAME *pImageFrame,
            /* [out] */ BOOL *pNearMode,
            /* [out] */ INuiFrameTexture **ppFrameTexture);
        
        HRESULT ( STDMETHODCALLTYPE *NuiGetColorCameraSettings )( 
            INuiSensor * This,
            /* [retval][out] */ INuiColorCameraSettings **pCameraSettings);
        
        BOOL ( STDMETHODCALLTYPE *NuiGetForceInfraredEmitterOff )( 
            INuiSensor * This);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSetForceInfraredEmitterOff )( 
            INuiSensor * This,
            /* [in] */ BOOL fForceInfraredEmitterOff);
        
        HRESULT ( STDMETHODCALLTYPE *NuiAccelerometerGetCurrentReading )( 
            INuiSensor * This,
            /* [retval][out] */ Vector4 *pReading);
        
        HRESULT ( STDMETHODCALLTYPE *NuiSetDepthFilter )( 
            INuiSensor * This,
            /* [in] */ INuiDepthFilter *pDepthFilter);
        
        HRESULT ( STDMETHODCALLTYPE *NuiGetDepthFilter )( 
            INuiSensor * This,
            /* [retval][out] */ INuiDepthFilter **ppDepthFilter);
        
        HRESULT ( STDMETHODCALLTYPE *NuiGetDepthFilterForTimeStamp )( 
            INuiSensor * This,
            /* [in] */ LARGE_INTEGER liTimeStamp,
            /* [retval][out] */ INuiDepthFilter **ppDepthFilter);
        
        END_INTERFACE
    } INuiSensorVtbl;

    interface INuiSensor
    {
        CONST_VTBL struct INuiSensorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INuiSensor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INuiSensor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INuiSensor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INuiSensor_NuiInitialize(This,dwFlags)	\
    ( (This)->lpVtbl -> NuiInitialize(This,dwFlags) ) 

#define INuiSensor_NuiShutdown(This)	\
    ( (This)->lpVtbl -> NuiShutdown(This) ) 

#define INuiSensor_NuiSetFrameEndEvent(This,hEvent,dwFrameEventFlag)	\
    ( (This)->lpVtbl -> NuiSetFrameEndEvent(This,hEvent,dwFrameEventFlag) ) 

#define INuiSensor_NuiImageStreamOpen(This,eImageType,eResolution,dwImageFrameFlags,dwFrameLimit,hNextFrameEvent,phStreamHandle)	\
    ( (This)->lpVtbl -> NuiImageStreamOpen(This,eImageType,eResolution,dwImageFrameFlags,dwFrameLimit,hNextFrameEvent,phStreamHandle) ) 

#define INuiSensor_NuiImageStreamSetImageFrameFlags(This,hStream,dwImageFrameFlags)	\
    ( (This)->lpVtbl -> NuiImageStreamSetImageFrameFlags(This,hStream,dwImageFrameFlags) ) 

#define INuiSensor_NuiImageStreamGetImageFrameFlags(This,hStream,pdwImageFrameFlags)	\
    ( (This)->lpVtbl -> NuiImageStreamGetImageFrameFlags(This,hStream,pdwImageFrameFlags) ) 

#define INuiSensor_NuiImageStreamGetNextFrame(This,hStream,dwMillisecondsToWait,pImageFrame)	\
    ( (This)->lpVtbl -> NuiImageStreamGetNextFrame(This,hStream,dwMillisecondsToWait,pImageFrame) ) 

#define INuiSensor_NuiImageStreamReleaseFrame(This,hStream,pImageFrame)	\
    ( (This)->lpVtbl -> NuiImageStreamReleaseFrame(This,hStream,pImageFrame) ) 

#define INuiSensor_NuiImageGetColorPixelCoordinatesFromDepthPixel(This,eColorResolution,pcViewArea,lDepthX,lDepthY,usDepthValue,plColorX,plColorY)	\
    ( (This)->lpVtbl -> NuiImageGetColorPixelCoordinatesFromDepthPixel(This,eColorResolution,pcViewArea,lDepthX,lDepthY,usDepthValue,plColorX,plColorY) ) 

#define INuiSensor_NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(This,eColorResolution,eDepthResolution,pcViewArea,lDepthX,lDepthY,usDepthValue,plColorX,plColorY)	\
    ( (This)->lpVtbl -> NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(This,eColorResolution,eDepthResolution,pcViewArea,lDepthX,lDepthY,usDepthValue,plColorX,plColorY) ) 

#define INuiSensor_NuiImageGetColorPixelCoordinateFrameFromDepthPixelFrameAtResolution(This,eColorResolution,eDepthResolution,cDepthValues,pDepthValues,cColorCoordinates,pColorCoordinates)	\
    ( (This)->lpVtbl -> NuiImageGetColorPixelCoordinateFrameFromDepthPixelFrameAtResolution(This,eColorResolution,eDepthResolution,cDepthValues,pDepthValues,cColorCoordinates,pColorCoordinates) ) 

#define INuiSensor_NuiCameraElevationSetAngle(This,lAngleDegrees)	\
    ( (This)->lpVtbl -> NuiCameraElevationSetAngle(This,lAngleDegrees) ) 

#define INuiSensor_NuiCameraElevationGetAngle(This,plAngleDegrees)	\
    ( (This)->lpVtbl -> NuiCameraElevationGetAngle(This,plAngleDegrees) ) 

#define INuiSensor_NuiSkeletonTrackingEnable(This,hNextFrameEvent,dwFlags)	\
    ( (This)->lpVtbl -> NuiSkeletonTrackingEnable(This,hNextFrameEvent,dwFlags) ) 

#define INuiSensor_NuiSkeletonTrackingDisable(This)	\
    ( (This)->lpVtbl -> NuiSkeletonTrackingDisable(This) ) 

#define INuiSensor_NuiSkeletonSetTrackedSkeletons(This,TrackingIDs)	\
    ( (This)->lpVtbl -> NuiSkeletonSetTrackedSkeletons(This,TrackingIDs) ) 

#define INuiSensor_NuiSkeletonGetNextFrame(This,dwMillisecondsToWait,pSkeletonFrame)	\
    ( (This)->lpVtbl -> NuiSkeletonGetNextFrame(This,dwMillisecondsToWait,pSkeletonFrame) ) 

#define INuiSensor_NuiTransformSmooth(This,pSkeletonFrame,pSmoothingParams)	\
    ( (This)->lpVtbl -> NuiTransformSmooth(This,pSkeletonFrame,pSmoothingParams) ) 

#define INuiSensor_NuiGetAudioSource(This,ppDmo)	\
    ( (This)->lpVtbl -> NuiGetAudioSource(This,ppDmo) ) 

#define INuiSensor_NuiInstanceIndex(This)	\
    ( (This)->lpVtbl -> NuiInstanceIndex(This) ) 

#define INuiSensor_NuiDeviceConnectionId(This)	\
    ( (This)->lpVtbl -> NuiDeviceConnectionId(This) ) 

#define INuiSensor_NuiUniqueId(This)	\
    ( (This)->lpVtbl -> NuiUniqueId(This) ) 

#define INuiSensor_NuiAudioArrayId(This)	\
    ( (This)->lpVtbl -> NuiAudioArrayId(This) ) 

#define INuiSensor_NuiStatus(This)	\
    ( (This)->lpVtbl -> NuiStatus(This) ) 

#define INuiSensor_NuiInitializationFlags(This)	\
    ( (This)->lpVtbl -> NuiInitializationFlags(This) ) 

#define INuiSensor_NuiGetCoordinateMapper(This,pMapping)	\
    ( (This)->lpVtbl -> NuiGetCoordinateMapper(This,pMapping) ) 

#define INuiSensor_NuiImageFrameGetDepthImagePixelFrameTexture(This,hStream,pImageFrame,pNearMode,ppFrameTexture)	\
    ( (This)->lpVtbl -> NuiImageFrameGetDepthImagePixelFrameTexture(This,hStream,pImageFrame,pNearMode,ppFrameTexture) ) 

#define INuiSensor_NuiGetColorCameraSettings(This,pCameraSettings)	\
    ( (This)->lpVtbl -> NuiGetColorCameraSettings(This,pCameraSettings) ) 

#define INuiSensor_NuiGetForceInfraredEmitterOff(This)	\
    ( (This)->lpVtbl -> NuiGetForceInfraredEmitterOff(This) ) 

#define INuiSensor_NuiSetForceInfraredEmitterOff(This,fForceInfraredEmitterOff)	\
    ( (This)->lpVtbl -> NuiSetForceInfraredEmitterOff(This,fForceInfraredEmitterOff) ) 

#define INuiSensor_NuiAccelerometerGetCurrentReading(This,pReading)	\
    ( (This)->lpVtbl -> NuiAccelerometerGetCurrentReading(This,pReading) ) 

#define INuiSensor_NuiSetDepthFilter(This,pDepthFilter)	\
    ( (This)->lpVtbl -> NuiSetDepthFilter(This,pDepthFilter) ) 

#define INuiSensor_NuiGetDepthFilter(This,ppDepthFilter)	\
    ( (This)->lpVtbl -> NuiGetDepthFilter(This,ppDepthFilter) ) 

#define INuiSensor_NuiGetDepthFilterForTimeStamp(This,liTimeStamp,ppDepthFilter)	\
    ( (This)->lpVtbl -> NuiGetDepthFilterForTimeStamp(This,liTimeStamp,ppDepthFilter) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INuiSensor_INTERFACE_DEFINED__ */



/* interface __MIDL_itf_Kinect_0001_0070 */
/* [local] */ 

/// <summary>
/// Returns the number of Kinect sensors that are connected to the computer.
/// </summary>
/// <param name="pCount">Pointer to an integer which receives the number of Kinect sensors.</param>
/// <returns>
/// <para>Returns S_OK if successful; otherwise, returns one of the following failure codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="pCount"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
_Check_return_ HRESULT NUIAPI NuiGetSensorCount( _In_ int * pCount );

/// <summary>
/// Creates an instance of the sensor with the specified index so that an application can open and use it.
/// </summary>
/// <param name="index">
/// The zero-based index of the sensor to open. Valid values range from zero to one less than the
/// value returned by the NuiGetSensorCount function.
/// </param>
/// <param name="ppNuiSensor">A pointer that receives a reference to the created INuiSensor interface. This must not be NULL.</param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="index"/> parameter is negative.</description>
///    </item>
///    <item>
///       <term>E_NUI_BADINDEX</term>
///       <description>The <paramref name="index"/> parameter is out of range.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="ppNuiSensor"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>Applications that support more than one Kinect sensor call this function to access the
/// second and subsequent devices. This function returns a pointer to an INuiSensor interface,
/// which provides functions that are identical to those in NuiApi.h</para>
///
/// <para>Repeated calls to this method with the same ID may return the same interface pointer.</para>
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiCreateSensorByIndex( _In_ int index, _Out_ INuiSensor ** ppNuiSensor );

/// <summary>
/// Creates an instance of the sensor with the specified ID so that an application can open and use it.
/// </summary>
/// <param name="strInstanceId">A pointer to the ID of the Kinect sensor to open. This must not be NULL.</param>
/// <param name="ppNuiSensor">A pointer that receives a reference to the created INuiSensor interface. This must not be NULL.</param>
/// <returns>
/// Returns S_OK if successful; otherwise, returns one of the following error codes:
/// <list type="table">
///    <listheader>
///       <term>Error code</term>
///       <description>Description</description>
///    </listheader>
///    <item>
///       <term>E_INVALIDARG</term>
///       <description>The <paramref name="strInstanceId"/> parameter is NULL.</description>
///    </item>
///    <item>
///       <term>E_NUI_BADINDEX</term>
///       <description>The <paramref name="strInstanceId"/> parameter does not match any attached device.</description>
///    </item>
///    <item>
///       <term>E_POINTER</term>
///       <description>The <paramref name="ppNuiSensor"/> parameter is NULL.</description>
///    </item>
/// </list>
/// </returns>
/// <remarks>
/// <para>Applications that support more than one Kinect sensor call this function to access the
/// second and subsequent devices. This function returns a pointer to an INuiSensor interface,
/// which provides functions that are identical to those in NuiApi.h</para>
///
/// <para>Repeated calls to this method with the same ID may return the same interface pointer.</para>
/// </remarks>
_Check_return_ HRESULT NUIAPI NuiCreateSensorById( _In_ const OLECHAR *strInstanceId, _Out_ INuiSensor ** ppNuiSensor );

_Check_return_ HRESULT NUIAPI NuiGetAudioSource( _Out_ INuiAudioBeam ** ppDmo );

typedef void (CALLBACK* NuiStatusProc)( HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName, void* pUserData );

/// <summary>
/// Sets a callback function that gets notified when the sensor connection status changes.
/// </summary>
/// <param name="callback">Function pointer to the callback.</param>
/// <param name="pUserData">Pointer to optional context data that will be passed to the callback.</param>
/// <remarks>
/// Use this method to handle the case of a user connecting or disconnecting a sensor.
/// </remarks>
void NUIAPI NuiSetDeviceStatusCallback( NuiStatusProc callback, void* pUserData );

/// <summary>
/// Determines whether the sensor instance has a skeletal engine.
/// </summary>
/// <param name="pNuiSensor">Pointer to an instance of the sensor.</param>
/// <returns>
/// Returns true if the sensor instance has a skeletal engine; otherwise, returns false.
/// </returns>
_Check_return_ inline bool HasSkeletalEngine(_In_ INuiSensor *pNuiSensor)
{
    if (!pNuiSensor) return false;
    return (pNuiSensor->NuiInitializationFlags() & NUI_INITIALIZE_FLAG_USES_SKELETON) || (pNuiSensor->NuiInitializationFlags() & NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX);
};

#define MAX_DEV_STR_LEN 512
typedef struct
{
    wchar_t szDeviceName[MAX_DEV_STR_LEN];
    wchar_t szDeviceID[MAX_DEV_STR_LEN];
    int iDeviceIndex;
} NUI_MICROPHONE_ARRAY_DEVICE, *PNUI_MICROPHONE_ARRAY_DEVICE;

/// <summary>
/// Gets device information for the connected Kinect sensors.
/// </summary>
/// <param name="pDeviceInfo">
/// Pointer to an array of NUI_MICROPHONE_ARRAY_DEVICE structures, allocated by the caller, each of
/// which receives the device information for a single connected Kinect sensor. If you set this
/// parameter to NULL, the <paramref name="piDeviceCount"/> parameter will still receive the number
/// of connected Kinect sensors.
/// </param>
/// <param name="size">
/// Size of the array pointed to by the <paramref name="pDeviceInfo"/> parameter.
/// </param>
/// <param name="piDeviceCount">
/// Receives the number of connected Kinect sensors. When this function returns, this parameter is
/// set to the number of structures in the array pointed to by the <paramref name="pDeviceInfo"/>
/// parameter that contain valid information.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise returns a failure code.
/// </returns>
_Check_return_ HRESULT NuiGetMicrophoneArrayDevices( _Out_opt_cap_post_count_(size, *piDeviceCount) PNUI_MICROPHONE_ARRAY_DEVICE pDeviceInfo, _In_ int size,  _Out_ int *piDeviceCount);

typedef struct
{
    wchar_t szDeviceName[MAX_DEV_STR_LEN];
    int iDeviceIndex;
    bool fDefault;
} NUI_SPEAKER_DEVICE, *PNUI_SPEAKER_DEVICE;

/// <summary>
/// Gets the active speaker devices found on the system.
/// </summary>
/// <param name="pDeviceInfo">
/// Pointer to an array of NUI_SPEAKER_DEVICE structures, allocated by the caller, each of which
/// receives the device information for a single connected speaker device. If you set this
/// parameter to NULL, the <paramref name="piDeviceCount"/> parameter will still receive the number
/// of connected speaker devices.
/// </param>
/// <param name="size">
/// Size of the array pointed to by the <paramref name="pDeviceInfo"/> parameter.
/// </param>
/// <param name="piDeviceCount">
/// Receives the number of connected speaker devices. When this function returns, this parameter is
/// set to the number of structures in the array pointed to by the <paramref name="pDeviceInfo"/>
/// parameter that contain valid information.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise returns a failure code.
/// </returns>
_Check_return_ HRESULT NuiGetSpeakerDevices( _Out_opt_cap_post_count_(size, *piDeviceCount) PNUI_SPEAKER_DEVICE pDeviceInfo, _In_ int size,  _Out_ int *piDeviceCount);
_Check_return_ HRESULT NUIAPI NuiCreateCoordinateMapperFromParameters(
                _In_ ULONG dataByteCount, 
                _In_ void* pData,
                _Out_ INuiCoordinateMapper **ppCoordinateMapper);
/// <summary>
/// Creates a filter that can be applied to depth frames.
/// </summary>
/// <param name="filename">
/// The name of the DLL that implements the depth filter. Must be an absolute path or
/// a simple filename. Other forms of relative paths are not permitted. If a simple
/// filename, the file must be found in the same directory as the process executable.
/// </param>
/// <param name="factoryEntryPoint">
/// The name of the DLL entry point to instantiate the depth filter.
/// </param>
/// <param name="ppDepthFilter">
/// Receives a reference-counted pointer to the newly created filter.
/// </param>
/// <returns>
/// Returns S_OK if successful; otherwise returns a failure code.
/// </returns>
_Check_return_ HRESULT NUIAPI NuiCreateDepthFilter(
                _In_ LPCWSTR filename,
                _In_ LPCSTR factoryEntryPoint,
                _Out_ INuiDepthFilter** ppDepthFilter);


extern RPC_IF_HANDLE __MIDL_itf_Kinect_0001_0070_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Kinect_0001_0070_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


