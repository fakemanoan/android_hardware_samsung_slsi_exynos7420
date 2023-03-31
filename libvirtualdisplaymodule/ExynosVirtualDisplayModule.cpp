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
}

ExynosVirtualDisplayModule::~ExynosVirtualDisplayModule()
{
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
