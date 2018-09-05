/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : ImiPlatform.h
  @Author        : Chen Shangwei
  @Date          : 2015-05-12
  @Description   : Platform Defines
  @Version       : 0.1.0

  @History       :
  1.2015-05-12 Chen Shangwei Created file

********************************************************************************/
#ifndef _IMI_PLATFORM_H_
#define _IMI_PLATFORM_H_

// Supported platforms
#define IMI_PLATFORM_ARM 1
#define IMI_PLATFORM_X86 2
#define IMI_PLATFORM_WINDOWS 3

#if defined (__arm__)
#define IMI_PLATFORM IMI_PLATFORM_ARM
#elif (i386 || __x86_64__)
#define IMI_PLATFORM IMI_PLATFORM_X86
#elif defined (_WIN32)
#define IMI_PLATFORM IMI_PLATFORM_WINDOWS
#include <windows.h>
#else
//   Unsupported Platform!
#endif

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning (pop)
#else
#include <stdint.h>		/* C99 */
#endif

//Api Export
#if !defined(IMI_API_EXPORT)
#if defined(_WIN32)
#define IMI_API_EXPORT __declspec(dllexport)
#elif defined (ANDROID) || defined (__linux__)
#define IMI_API_EXPORT __attribute__ ((visibility("default")))
#else
#	Unsupported Platform!
#endif
#endif

#ifdef __cplusplus
#	define IMINECT_API_EXPORT extern "C" IMI_API_EXPORT
#else // __cplusplus
#	define IMINECT_API_EXPORT IMI_API_EXPORT
#endif  // __cplusplus

#define IMINECT_EXP IMINECT_API_EXPORT

#if !defined(IMINECT_API)
#if defined(_WIN32)
#define IMINECT_API WINAPI
#elif defined (ANDROID) || defined (__linux__)
#define IMINECT_API
#else
#	Unsupported Platform!
#endif
#endif

#endif // _IMI_PLATFORM_H_
