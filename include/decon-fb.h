/*
 * Copyright@ Samsung Electronics Co. LTD
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 * Alternatively, this program is free software in case of open source projec;
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef ___SAMSUNG_DECON_H__
#define ___SAMSUNG_DECON_H__

#define MAX_DECON_WIN		(7)
#define MAX_DECON_EXT_WIN	(5)
#define DECON_WIN_UPDATE_IDX MAX_DECON_WIN
#define IDMA_MAX IDMA_G3
#define MAX_BUF_PLANE_CNT (3)
typedef unsigned int u32;
#if defined(USES_ARCH_ARM64)
typedef uint64_t dma_addr_t;
#else
typedef uint32_t dma_addr_t;
#endif
struct decon_win_rect {
	int x;
	int y;
	u32 w;
	u32 h;
};

struct decon_rect {
	int	left;
	int	top;
	int	right;
	int	bottom;
};
struct decon_user_window {
	int x;
	int y;
};
struct s3c_fb_user_plane_alpha {
	int		channel;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
};
struct s3c_fb_user_chroma {
	int		enabled;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
};
struct s3c_fb_user_ion_client {
	int	fd[MAX_BUF_PLANE_CNT];
	int	offset;
};
enum decon_pixel_format {
	/* RGB 32bit */
	DECON_PIXEL_FORMAT_ARGB_8888 = 0,
	DECON_PIXEL_FORMAT_ABGR_8888,
	DECON_PIXEL_FORMAT_RGBA_8888,
	DECON_PIXEL_FORMAT_BGRA_8888,
	DECON_PIXEL_FORMAT_XRGB_8888,
	DECON_PIXEL_FORMAT_XBGR_8888,
	DECON_PIXEL_FORMAT_RGBX_8888,
	DECON_PIXEL_FORMAT_BGRX_8888,
	/* RGB 16 bit */
	DECON_PIXEL_FORMAT_RGBA_5551,
	DECON_PIXEL_FORMAT_RGB_565,
	/* YUV422 2P */
	DECON_PIXEL_FORMAT_NV16,
	DECON_PIXEL_FORMAT_NV61,
	/* YUV422 3P */
	DECON_PIXEL_FORMAT_YVU422_3P,
	/* YUV420 2P */
	DECON_PIXEL_FORMAT_NV12,
	DECON_PIXEL_FORMAT_NV21,
	DECON_PIXEL_FORMAT_NV12M,
	DECON_PIXEL_FORMAT_NV21M,
	/* YUV420 3P */
	DECON_PIXEL_FORMAT_YUV420,
	DECON_PIXEL_FORMAT_YVU420,
	DECON_PIXEL_FORMAT_YUV420M,
	DECON_PIXEL_FORMAT_YVU420M,

	DECON_PIXEL_FORMAT_MAX,
};
enum decon_blending {
	DECON_BLENDING_NONE = 0,
	DECON_BLENDING_PREMULT = 1,
	DECON_BLENDING_COVERAGE = 2,
	DECON_BLENDING_MAX = 3,
};
struct exynos_hdmi_data {
	enum {
		EXYNOS_HDMI_STATE_PRESET = 0,
		EXYNOS_HDMI_STATE_ENUM_PRESET,
		EXYNOS_HDMI_STATE_CEC_ADDR,
		EXYNOS_HDMI_STATE_HDCP,
		EXYNOS_HDMI_STATE_AUDIO,
	} state;
	struct	v4l2_dv_timings timings;
	struct	v4l2_enum_dv_timings etimings;
	__u32	cec_addr;
	__u32	audio_info;
	int	hdcp;
};

enum vpp_rotate {
	VPP_ROT_NORMAL = 0x0,
	VPP_ROT_XFLIP,
	VPP_ROT_YFLIP,
	VPP_ROT_180,
	VPP_ROT_90,
	VPP_ROT_90_XFLIP,
	VPP_ROT_90_YFLIP,
	VPP_ROT_270,
};

enum vpp_csc_eq {
	BT_601_NARROW = 0x0,
	BT_601_WIDE,
	BT_709_NARROW,
	BT_709_WIDE,
};
enum decon_idma_type {
	IDMA_G0 = 0x0,
	IDMA_G1,
	IDMA_VG0,
	IDMA_VG1,
	IDMA_VGR0,
	IDMA_VGR1,
	IDMA_G2,
	IDMA_G3,
};
struct vpp_params {
	dma_addr_t addr[MAX_BUF_PLANE_CNT];
	enum vpp_rotate rot;
	enum vpp_csc_eq eq_mode;
};
struct decon_frame {
	int x;
	int y;
	u32 w;
	u32 h;
	u32 f_w;
	u32 f_h;
};
struct decon_win_config {
	enum {
		DECON_WIN_STATE_DISABLED = 0,
		DECON_WIN_STATE_COLOR,
		DECON_WIN_STATE_BUFFER,
		DECON_WIN_STATE_UPDATE,
	} state;

	union {
		__u32 color;
		struct {
			int				fd_idma[3];
			int				fence_fd;
			int				plane_alpha;
			enum decon_blending		blending;
			enum decon_idma_type		idma_type;
			enum decon_pixel_format		format;
			struct vpp_params		vpp_parm;
			/* no read area of IDMA */
			struct decon_win_rect		block_area;
			struct decon_win_rect           transparent_area;
			struct decon_win_rect           opaque_area;
			/* source framebuffer coordinates */
			struct decon_frame		src;
		};
	};

	/* destination OSD coordinates */
	struct decon_frame dst;
	bool protection;
};
struct decon_win_config_data {
	int	fence;
	int	fd_odma;
	struct decon_win_config config[MAX_DECON_WIN + 1];
};

enum disp_pwr_mode {
	DECON_POWER_MODE_OFF = 0,
	DECON_POWER_MODE_DOZE,
	DECON_POWER_MODE_NORMAL,
	DECON_POWER_MODE_DOZE_SUSPEND,
};

#define S3CFB_WIN_POSITION		_IOW('F', 203, \
						struct decon_user_window)
#define S3CFB_WIN_SET_PLANE_ALPHA	_IOW('F', 204, \
						struct s3c_fb_user_plane_alpha)
#define S3CFB_WIN_SET_CHROMA		_IOW('F', 205, \
						struct s3c_fb_user_chroma)
#define S3CFB_SET_VSYNC_INT		_IOW('F', 206, __u32)

#define S3CFB_GET_ION_USER_HANDLE	_IOWR('F', 208, \
						struct s3c_fb_user_ion_client)
#define S3CFB_WIN_CONFIG		_IOW('F', 209, \
						struct decon_win_config_data)
#define S3CFB_WIN_PSR_EXIT		_IOW('F', 210, int)
#define S3CFB_POWER_MODE		_IOW('F', 223, __u32)
#endif
