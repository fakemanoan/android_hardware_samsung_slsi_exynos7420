#include "ExynosVirtualDisplayModule.h"
#include "ExynosHWCUtils.h"
#include "ExynosMPPModule.h"

#ifdef EVD_DBUG
#define DISPLAY_LOGD(msg, ...) ALOGD("[%s] " msg, mDisplayName.string(), ##__VA_ARGS__)
#define DISPLAY_LOGV(msg, ...) ALOGV("[%s] " msg, mDisplayName.string(), ##__VA_ARGS__)
#define DISPLAY_LOGI(msg, ...) ALOGI("[%s] " msg, mDisplayName.string(), ##__VA_ARGS__)
#define DISPLAY_LOGW(msg, ...) ALOGW("[%s] " msg, mDisplayName.string(), ##__VA_ARGS__)
#define DISPLAY_LOGE(msg, ...) ALOGE("[%s] " msg, mDisplayName.string(), ##__VA_ARGS__)
#else
#define DISPLAY_LOGD(msg, ...)
#define DISPLAY_LOGV(msg, ...)
#define DISPLAY_LOGI(msg, ...)
#define DISPLAY_LOGW(msg, ...)
#define DISPLAY_LOGE(msg, ...)
#endif

ExynosVirtualDisplayModule::ExynosVirtualDisplayModule(struct exynos5_hwc_composer_device_1_t *pdev)
    : ExynosVirtualDisplay(pdev)
{
    mGLESFormat = HAL_PIXEL_FORMAT_RGBA_8888;
    mDisplayFd  = 0;
}

ExynosVirtualDisplayModule::~ExynosVirtualDisplayModule()
{
}

void ExynosVirtualDisplayModule::configureWriteBack(hwc_display_contents_1_t *contents,
        decon_win_config_data &win_data)
{
	private_handle_t *outBufHandle = private_handle_t::dynamicCast(contents->outbuf);
	if(outBufHandle != NULL){
		// TODO
	}
}

bool ExynosVirtualDisplayModule::isSupportGLESformat()
{
	// Reverse engineered from blobs
	return mGLESFormat == HAL_PIXEL_FORMAT_RGBA_8888;
	
}

void ExynosVirtualDisplayModule::determineBandwidthSupport(hwc_display_contents_1_t *contents)
{
    ALOGV("ExynosVirtualDisplay::determineBandwidthSupport");

/*
* Determined from reverse engineering
*/
   if (mAllowedOverlays > 4){
   	mAllowedOverlays = 5;
   }
	
    if (mDisplayFd < 0) {
        ALOGE("determineBandwidthSupport, mDisplayFd is invalid , no overlay");
        return;
    }

#ifdef USES_VDS_OTHERFORMAT
    if (!isSupportGLESformat()) {
        ALOGE("determineBandwidthSupport, GLES format is not suppoted, no overlay");
        return;
    }
#endif

    if (mIsRotationState)
        return;

    private_handle_t *outBufHandle = private_handle_t::dynamicCast(contents->outbuf);
    if (outBufHandle == NULL) {
        ALOGE("determineBandwidthSupport, outbuf is invalid, no overlay");
        return;
    }

    ExynosDisplay::determineBandwidthSupport(contents);
}

int32_t ExynosVirtualDisplayModule::getDisplayAttributes(const uint32_t attribute)
{
    switch(attribute) {
        case HWC_DISPLAY_COMPOSITION_TYPE:
            return mCompositionType;
        case HWC_DISPLAY_GLES_FORMAT:
            return mGLESFormat;
        case HWC_DISPLAY_SINK_BQ_FORMAT:
            if (mIsRotationState)
                return -1;
            else
                return mGLESFormat;
        case HWC_DISPLAY_SINK_BQ_USAGE:
            return mSinkUsage;
        case HWC_DISPLAY_SINK_BQ_WIDTH:
            if (mDisplayWidth == 0)
                return mWidth;
            return mDisplayWidth;
        case HWC_DISPLAY_SINK_BQ_HEIGHT:
            if (mDisplayHeight == 0)
                return mHeight;
            return mDisplayHeight;
        default:
            ALOGE("unknown display attribute %u", attribute);
            return -EINVAL;
    }
    return 0;
}
