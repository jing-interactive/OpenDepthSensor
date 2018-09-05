/**************************************************************************
  Copyright (c) 2016 Huajie IMI Technology Co.,Ltd.
  All rights reserved.

  @file   ImiSkeleton.h
  @brief  Imi Skeleton header.

  @date    2016-11-08
  @author  liwei
  @version 0.1.0

  History:
  1. 2016-11-08, liwei The initial version
**************************************************************************/

#ifndef _IMI_UPGRADE_H_
#define _IMI_UPGRADE_H_

#include <ImiPlatform.h>
#include <ImiDefines.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    IMI_UPGRADE_START               = 0,
    IMI_UPLOADBLOCK_START           = 1,
    IMI_UPLOADBLOCK_UPLOADING       = 2,
    IMI_UPLOADBLOCK_PASS            = 3,
    IMI_UPLOADBLOCK_FAIL            = 4,
    IMI_REBOOT_START                = 5,
    IMI_REBOOTING                   = 6,
    IMI_REBOOT_PASS                 = 7,
    IMI_REBOOT_FAIL                 = 8,
    IMI_CHCKING_START               = 9,
    IMI_CHCKING_PASS                = 10,
    IMI_CHCKING_FAIL                = 11,
    IMI_UPGRADE_PASS                = 12,
    IMI_UPGRADE_FAIL                = 13,
    IMI_CHECK_UPGRADEINFO_SUCCESS   = 14,
    IMI_CHECK_UPGRADEINFO_FAILED    = 15,
    IMI_UPLOAD_PASS_NEED_REBOOT     = 16,
    IMI_NO_NEED_UPGRADE             = 17,
    IMI_USER_CANCEL_UPGRADE         = 18,
    IMI_DOWNLOADING                 = 19,

}IMI_UPGRADE_PROMPT;


#if defined(_WIN32)

typedef void (_stdcall * ImiDeviceUpgradeNotify) (ImiDeviceHandle device, void* pUserData);
typedef void (_stdcall * ImiDeviceUpgradeStepPrompt) (ImiDeviceHandle device, IMI_UPGRADE_PROMPT promptID, float progress, void* pUserData);

#else
typedef void (* ImiDeviceUpgradeNotify) (ImiDeviceHandle device, void* pUserData);
typedef void (* ImiDeviceUpgradeStepPrompt) (ImiDeviceHandle device, IMI_UPGRADE_PROMPT promptID, float progress, void* pUserData);

#endif

typedef struct tagImiCallbacks
{
    void* pUserData;
    ImiDeviceUpgradeNotify upgradeNotifyProc;
    ImiDeviceUpgradeStepPrompt upgradeStepPromptProc;
} ImiCallbacks;


/**
 * @brief  set the channel number for upgrade, use it to differentiate users, it's provided by hjimi,
           set it before open device. If not set it , use the default method to upgrade.

 * @param  const char* pChannelNo: the channel number
 * @return 0:success, < 0 :error
 **/
IMINECT_EXP int32_t IMINECT_API imiSetUpgradeChannelNo(const char* pChannelNo);

#ifdef __cplusplus
}
#endif

#endif // _IMI_UPGRADE_H_

