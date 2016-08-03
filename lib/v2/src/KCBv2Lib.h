/***********************************************************************************************************
Copyright ?Microsoft Open Technologies, Inc.
All Rights Reserved
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
except in compliance with the License. You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR
CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.

See the Apache 2 License for the specific language governing permissions and limitations under the License.
***********************************************************************************************************/
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
#endif

// Windows Header Files:
#include <windows.h>
#include <objbase.h>

#include <Kinect.h>                         // will need $(KINECTSDK20_DIR)inc; in the includes directory for project
#pragma comment (lib, "kinect20.lib")

#ifndef __KCB_HANDLE__
#define __KCB_HANDLE__
static const int KCB_INVALID_HANDLE = 0xffffffff;
#endif

typedef struct KCBFrameDescription
{
    int width;
    int height;
    float horizontalFieldOfView;
    float verticalFieldOfView;
    float diagonalFieldOfView;
    unsigned int lengthInPixels;
    unsigned int bytesPerPixel;
} KCBFrameDescription;

typedef struct KCBAudioFrame
{
    ULONG cAudioBufferSize;
    byte* pAudioBuffer; // ieee float 4bytes
    ULONG ulBytesRead;
    FLOAT fBeamAngle;
    FLOAT fBeamAngleConfidence;
} KCBAudioFrame;

typedef struct KCBBodyFrame
{
    UINT Count;
    IBody** Bodies;
    LONGLONG TimeStamp;
} KCBBodyFrame;

typedef struct KCBBodyIndexFrame
{
    ULONG Size;
    BYTE* Buffer;
    LONGLONG TimeStamp;
} KCBBodyIndexFrame;

typedef struct KCBColorFrame
{
    ColorImageFormat Format; 
    ULONG Size; 
    BYTE* Buffer;
    LONGLONG TimeStamp;
} KCBColorFrame;

typedef struct KCBDepthFrame
{
    ULONG Size;
    UINT16* Buffer;
    LONGLONG TimeStamp;
} KCBDepthFrame, KCBInfraredFrame, KCBLongExposureInfraredFrame;

extern "C"
{
     int APIENTRY KCBOpenDefaultSensor();
     HRESULT APIENTRY KCBCloseSensor(_Inout_ int* kcbHandle);

    // get the native IFrameDescription, caller must release the object
     HRESULT APIENTRY KCBGetAudioFormat(_In_ int kcbHandle, _Inout_ WAVEFORMATEX* pAudioFormat);
     HRESULT APIENTRY KCBGetBodyIndexFrameDescription(_In_ int kcbHandle, _Inout_ KCBFrameDescription* pFrameDescription);
     HRESULT APIENTRY KCBGetColorFrameDescription(_In_ int kcbHandle, ColorImageFormat eFormat, _Inout_ KCBFrameDescription* pFrameDescription);
     HRESULT APIENTRY KCBGetDepthFrameDescription(_In_ int kcbHandle, _Inout_ KCBFrameDescription* pFrameDescription);
     HRESULT APIENTRY KCBGetInfraredFrameDescription(_In_ int kcbHandle, _Inout_ KCBFrameDescription* pFrameDescription);
     HRESULT APIENTRY KCBGetLongExposureInfraredFrameDescription(_In_ int kcbHandle, _Inout_ KCBFrameDescription* pFrameDescription);

    // initializing frame buffers
     HRESULT APIENTRY KCBCreateBodyFrame(_Out_ KCBBodyFrame** ppBodyFrame);
     HRESULT APIENTRY KCBCreateBodyIndexFrame(KCBFrameDescription frameDescription, _Out_ KCBBodyIndexFrame** ppBodyIndexFrame);
     HRESULT APIENTRY KCBCreateColorFrame(ColorImageFormat colorFormat, KCBFrameDescription frameDescription, _Out_ KCBColorFrame** ppColorFrame);
     HRESULT APIENTRY KCBCreateDepthFrame(KCBFrameDescription frameDescription, _Out_ KCBDepthFrame** ppDepthFrame);
     HRESULT APIENTRY KCBCreateInfraredFrame(KCBFrameDescription frameDescription, _Out_ KCBInfraredFrame** ppInfraredFrame);
     HRESULT APIENTRY KCBCreateLongExposureInfraredFrame(KCBFrameDescription frameDescription, _Out_ KCBLongExposureInfraredFrame** ppLongExposureInfraredFrame);

    // clean-up frame buffer
     HRESULT APIENTRY KCBReleaseBodyFrame(_Inout_ KCBBodyFrame** pBodyFrame);
     HRESULT APIENTRY KCBReleaseBodyIndexFrame(_Inout_ KCBBodyIndexFrame** pBodyIndexFrame);
     HRESULT APIENTRY KCBReleaseColorFrame(_Inout_ KCBColorFrame** pColorFrame);
     HRESULT APIENTRY KCBReleaseDepthFrame(_Inout_ KCBDepthFrame** pDepthFrame);
     HRESULT APIENTRY KCBReleaseInfraredFrame(_Inout_ KCBInfraredFrame** pInfraredFrame);
     HRESULT APIENTRY KCBReleaseLongExposureInfraredFrame(_Inout_ KCBLongExposureInfraredFrame** pLongExposureInfraredFrame);

    // copy method by passing struct
     HRESULT APIENTRY KCBGetAudioFrame(_In_ int kcbHandle, _Inout_ KCBAudioFrame* pstAudioFrame);
     HRESULT APIENTRY KCBGetBodyFrame(_In_ int kcbHandle, _Inout_ KCBBodyFrame* pstBodyFrame);
     HRESULT APIENTRY KCBGetBodyIndexFrame(_In_ int kcbHandle, _Inout_ KCBBodyIndexFrame* pstBodyIndexFrame);
     HRESULT APIENTRY KCBGetColorFrame(_In_ int kcbHandle, _Inout_ KCBColorFrame* pstColorFrame);
     HRESULT APIENTRY KCBGetDepthFrame(_In_ int kcbHandle, _Inout_ KCBDepthFrame* pstDepthFrame);
     HRESULT APIENTRY KCBGetInfraredFrame(_In_ int kcbHandle, _Inout_ KCBInfraredFrame* pstInfraredFrame);
     HRESULT APIENTRY KCBGetLongExposureInfraredFrame(_In_ int kcbHandle, _Inout_ KCBLongExposureInfraredFrame* pstLongExposureInfraredFrame);

    // copy methods just to get the buffer data
     HRESULT APIENTRY KCBGetAudioData(_In_ int kcbHandle, ULONG cAudioBufferSize, _Inout_cap_(cAudioBufferSize) byte*, _Out_ ULONG* ulBytesRead, _Out_opt_ FLOAT* beamAngle, _Out_opt_ FLOAT* sourceConfidence);
     HRESULT APIENTRY KCBGetBodyData(_In_ int kcbHandle, UINT capacity, _Inout_updates_all_(capacity) IBody **bodies, _Out_opt_ LONGLONG* llTimeStamp);
     HRESULT APIENTRY KCBGetBodyIndexData(_In_ int kcbHandle, ULONG cbBufferSize, _Inout_cap_(cbBufferSize) BYTE* pbBuffer, _Out_opt_ LONGLONG* llTimeStamp);
     HRESULT APIENTRY KCBGetColorData(_In_ int kcbHandle, ColorImageFormat eColorFormat, ULONG cbBufferSize, _Inout_cap_(cbBufferSize) BYTE* pbBuffer, _Out_opt_ LONGLONG* llTimeStamp);
     HRESULT APIENTRY KCBGetDepthData(_In_ int kcbHandle, ULONG cuiBufferSize, _Inout_cap_(cuiBufferSize) UINT16* puiBuffer, _Out_opt_ LONGLONG* llTimeStamp);
     HRESULT APIENTRY KCBGetInfraredData(_In_ int kcbHandle, ULONG cuiBufferSize, _Inout_cap_(cuiBufferSize) UINT16* puiBuffer, _Out_opt_ LONGLONG* llTimeStamp);
     HRESULT APIENTRY KCBGetLongExposureInfraredData(_In_ int kcbHandle, ULONG cuiBufferSize, _Inout_cap_(cuiBufferSize) UINT16* puiBuffer, _Out_opt_ LONGLONG* llTimeStamp);

    // copy all frame by using the MultiSourceFrameReader
     HRESULT APIENTRY KCBGetAllFrameData(_In_ int kcbHandle, 
        _Inout_opt_ KCBBodyFrame* pstBodyFrame,
        _Inout_opt_ KCBBodyIndexFrame* pstBodyIndexFrame,
        _Inout_opt_ KCBColorFrame* pstColorFrame,
        _Inout_opt_ KCBDepthFrame* pstDepthFrame,
        _Inout_opt_ KCBInfraredFrame* pstInfraredFrame,
        _Inout_opt_ KCBLongExposureInfraredFrame* pstLongExposureInfraredFrame);

     bool APIENTRY KCBIsFrameReady(_In_ int kcbHandle, FrameSourceTypes eSourceType);
     bool APIENTRY KCBAnyFrameReady(_In_ int kcbHandle);
     bool APIENTRY KCBAllFramesReady(_In_ int kcbHandle);
     bool APIENTRY KCBMultiFrameReady(_In_ int kcbHandle);

    // straight calls to the coordinate mapper
     HRESULT APIENTRY KCBMapCameraPointToDepthSpace(_In_ int kcbHandle, 
        CameraSpacePoint cameraPoint, 
        _Out_ DepthSpacePoint* depthPoint);
     HRESULT APIENTRY KCBMapCameraPointToColorSpace(_In_ int kcbHandle, 
        CameraSpacePoint cameraPoint, 
        _Out_ ColorSpacePoint *colorPoint);
     HRESULT APIENTRY KCBMapDepthPointToCameraSpace(_In_ int kcbHandle, 
        DepthSpacePoint depthPoint, UINT16 depth, 
        _Out_ CameraSpacePoint *cameraPoint);
     HRESULT APIENTRY KCBMapDepthPointToColorSpace(_In_ int kcbHandle, 
        DepthSpacePoint depthPoint, UINT16 depth, 
        _Out_ ColorSpacePoint *colorPoint);
     HRESULT APIENTRY KCBMapCameraPointsToDepthSpace(_In_ int kcbHandle, 
        UINT cameraPointCount, _In_reads_(cameraPointCount) const CameraSpacePoint *cameraPoints, 
        UINT depthPointCount, 
        _Out_writes_all_(depthPointCount) DepthSpacePoint *depthPoints);
     HRESULT APIENTRY KCBMapCameraPointsToColorSpace(_In_ int kcbHandle,
        UINT cameraPointCount, _In_reads_(cameraPointCount) const CameraSpacePoint *cameraPoints,
        UINT colorPointCount, 
        _Out_writes_all_(colorPointCount) ColorSpacePoint *colorPoints);
     HRESULT APIENTRY KCBMapDepthPointsToCameraSpace(_In_ int kcbHandle, 
        UINT depthPointCount, _In_reads_(depthPointCount) const DepthSpacePoint *depthPoints,
        UINT depthCount, _In_reads_(depthCount) const UINT16 *depths,
        UINT cameraPointCount, 
        _Out_writes_all_(cameraPointCount) CameraSpacePoint *cameraPoints);
     HRESULT APIENTRY KCBMapDepthPointsToColorSpace(_In_ int kcbHandle,
        UINT depthPointCount, _In_reads_(depthPointCount) const DepthSpacePoint *depthPoints,
        UINT depthCount, _In_reads_(depthCount) const UINT16 *depths,
        UINT colorPointCount, 
        _Out_writes_all_(colorPointCount) ColorSpacePoint *colorPoints);
     HRESULT APIENTRY KCBMapDepthFrameToCameraSpace(_In_ int kcbHandle, 
        UINT depthPointCount, _In_reads_(depthPointCount) const UINT16 *depthFrameData, 
        UINT cameraPointCount, 
        _Out_writes_all_(cameraPointCount) CameraSpacePoint *cameraSpacePoints);
     HRESULT APIENTRY KCBMapDepthFrameToColorSpace(_In_ int kcbHandle,
        UINT depthPointCount, _In_reads_(depthPointCount) const UINT16 *depthFrameData,
        UINT colorPointCount, 
        _Out_writes_all_(colorPointCount) ColorSpacePoint *colorSpacePoints);
     HRESULT APIENTRY KCBMapColorFrameToDepthSpace(_In_ int kcbHandle,
        UINT depthDataPointCount, _In_reads_(depthDataPointCount) const UINT16 *depthFrameData,
        UINT depthPointCount, 
        _Out_writes_all_(depthPointCount) DepthSpacePoint *depthSpacePoints);
     HRESULT APIENTRY KCBMapColorFrameToCameraSpace(_In_ int kcbHandle,
        UINT depthDataPointCount, _In_reads_(depthDataPointCount)  const UINT16 *depthFrameData,
        UINT cameraPointCount, 
        _Out_writes_all_(cameraPointCount) CameraSpacePoint *cameraSpacePoints);
     HRESULT APIENTRY GetDepthFrameToCameraSpaceTable(_In_ int kcbHandle,
        _Out_  UINT32 *tableEntryCount,
        _Outptr_result_bytebuffer_(*tableEntryCount) PointF **tableEntries);

    // get the native IxxxFrame, caller must release the object
    // if you just want the data, use the other frame functions.
     HRESULT APIENTRY KCBGetIBodyFrame(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ IBodyFrame **ppBodyFrame);
     HRESULT APIENTRY KCBGetIBodyIndexFrame(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ IBodyIndexFrame **ppBodyIndexFrame);
     HRESULT APIENTRY KCBGetIColorFrame(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ IColorFrame **ppColorFrame);
     HRESULT APIENTRY KCBGetIDepthFrame(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ IDepthFrame **ppDepthFrame);
     HRESULT APIENTRY KCBGetIInfraredFrame(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ IInfraredFrame **ppInfraredFrame);
     HRESULT APIENTRY KCBGetILongExposureInfraredFrame(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ ILongExposureInfraredFrame **ppLongExposureInfraredFrame);

    // multi-source frame reader, caller must release the object
     HRESULT APIENTRY KCBGetIMultiSourceFrame(_In_ int kcbHandle, DWORD dwFrameSourceTypes, _COM_Outptr_result_maybenull_ IMultiSourceFrame **ppMultiSourceFrame);

    // Coordinate mapper, caller must release the object
     HRESULT APIENTRY KCBGetICoordinateMapper(_In_ int kcbHandle, _COM_Outptr_result_maybenull_ ICoordinateMapper** ppCoordinateMapper);
}
