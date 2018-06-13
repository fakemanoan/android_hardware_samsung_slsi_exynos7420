/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_EXYNOS_HWC_MODULE_H_
#define ANDROID_EXYNOS_HWC_MODULE_H_
#include <hardware/hwcomposer.h>

#define VSYNC_DEV_PREFIX "/sys/devices/"
#define VSYNC_DEV_NAME  "13930000.decon_fb/vsync"

#define FIMD_WORD_SIZE_BYTES   16
#define FIMD_BURSTLEN   16

//
// confirmed by decompiling stock-HWC
//
//     if ( v186 - v91 >= 16 )
//     {
//         v92 = *(_DWORD *)(v8 + 28);
//     }
//     else
//     {
//         v92 = *(_DWORD *)(v8 + 28);
//         if ( v91 + 16 <= v92 )
//             v90 = v91 + 16;
//         else
//             v91 = v186 - 16;
//     }
//
// REMARK: inverted ```if (HEIGHT(updateRect) < WINUPDATE_MIN_HEIGHT) { ... }```
//
#define WINUPDATE_MIN_HEIGHT 16

#define HDMI_RESERVE_MEM_DEV_NAME "/sys/class/ion_cma/ion_video_ext/isolated"
#define SMEM_PATH "/dev/s5p-smem"
#define SECMEM_IOC_SET_VIDEO_EXT_PROC   _IOWR('S', 13, int)

#define HWC_VERSION HWC_DEVICE_API_VERSION_1_5

#define DUAL_VIDEO_OVERLAY_SUPPORT

/* Max number windows available in Exynos7420 is 7. */
#define NUM_AVAILABLE_HW_WINDOWS	7

/* IDMA_G2 and IDMA_G3 cause decon register crashes on Exynos7420 */
#define DISABLE_IDMA_SECURE

const size_t GSC_DST_W_ALIGNMENT_RGB888 = 1;
const size_t GSC_DST_CROP_W_ALIGNMENT_RGB888 = 1;
const size_t GSC_W_ALIGNMENT = 16;
const size_t GSC_H_ALIGNMENT = 16;
const size_t GSC_DST_H_ALIGNMENT_RGB888 = 1;

const size_t FIMD_GSC_IDX = 0;
const size_t FIMD_EXT_MPP_IDX = 0;
/* HDMI_GSC_IDX is not used but added for build issue */
const size_t HDMI_GSC_IDX = 2;
const size_t HDMI_EXT_MPP_IDX = 2;
const size_t WFD_GSC_IDX = 1;
const size_t WFD_EXT_MPP_IDX = 1;

const int FIMD_GSC_USAGE_IDX[] = {FIMD_GSC_IDX};

//
// confirmed by decompiling stock-HWC
//
// --- _DWORD *__fastcall ExynosMPP::ExynosMPP(_DWORD *a1, int a2, int a3)
//
//     v3[3] = dword_B2B0[v5];    <--  mType = AVAILABLE_GSC_UNITS[gscIndex];
//
//         v3            <--  ExynosMPP Instance
//         dword_B2B0    <--  AVAILABLE_GSC_UNITS
//         v5            <--  gscIndex
//
// .rodata:0000B2B0 ; _DWORD dword_B2B0[6]
// .rodata:0000B2B0 dword_B2B0      DCD 0, 2, 1, 1, 5, 4    ; DATA XREF: ExynosMPP::ExynosMPP(ExynosDisplay *,int)+44↑o
//
// REMARK: Third index requested as mType is preceeded by the VMT and two pointers
//
const int AVAILABLE_GSC_UNITS[] = { 0, 2, 1, 1, 5, 4 };

#define MPP_VG          0
#define MPP_VGR         2
#define MPP_MSC         4
#define MPP_MSC_1	5

#define EXTERNAL_MPPS   2

struct exynos_mpp_t {
    int type;
    unsigned int index;
};

const exynos_mpp_t AVAILABLE_EXTERNAL_MPP_UNITS[] = {{MPP_MSC, 0}, {MPP_MSC_1, 0} };

#endif
