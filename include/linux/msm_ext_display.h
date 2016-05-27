/* include/linux/msm_ext_display.h
 *
 * Copyright (c) 2014-2016 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef _MSM_EXT_DISPLAY_H_
#define _MSM_EXT_DISPLAY_H_

#include <linux/device.h>
#include <linux/platform_device.h>

/*
 * External display cable notify handler structure.
 * link A link for the linked list
 * status Current status of HDMI/DP cable connection
 * hpd_notify Callback function to provide cable status
 */
struct ext_disp_cable_notify {
	struct list_head link;
	int status;
	void (*hpd_notify)(struct ext_disp_cable_notify *h);
};

struct msm_ext_disp_audio_edid_blk {
	u8 *audio_data_blk;
	unsigned int audio_data_blk_size; /* in bytes */
	u8 *spk_alloc_data_blk;
	unsigned int spk_alloc_data_blk_size; /* in bytes */
};

struct msm_ext_disp_audio_setup_params {
	u32 sample_rate_hz;
	u32 num_of_channels;
	u32 channel_allocation;
	u32 level_shift;
	bool down_mix;
	u32 sample_present;
};

struct msm_ext_disp_audio_codec_ops {
	int (*audio_info_setup)(struct platform_device *pdev,
		struct msm_ext_disp_audio_setup_params *params);
	int (*get_audio_edid_blk)(struct platform_device *pdev,
		struct msm_ext_disp_audio_edid_blk *blk);
	int (*cable_status)(struct platform_device *pdev, u32 vote);
};

#ifdef CONFIG_FB_MSM_MDSS_DP_PANEL
int msm_dp_register_audio_codec(struct platform_device *pdev,
	struct msm_ext_disp_audio_codec_ops *ops);

#else
static inline int msm_dp_register_audio_codec(struct platform_device *pdev,
		struct msm_ext_disp_audio_codec_ops *ops) {
	return 0;
}
#endif /* CONFIG_FB_MSM_MDSS_DP_PANEL */
#ifdef CONFIG_FB_MSM_MDSS_HDMI_PANEL
/*
 * Register for HDMI cable connect or disconnect notification.
 * @param handler callback handler for notification
 * @return negative value as error otherwise current status of cable
 */
int register_hdmi_cable_notification(
		struct ext_disp_cable_notify *handler);

/*
 * Un-register for HDMI cable connect or disconnect notification.
 * @param handler callback handler for notification
 * @return negative value as error
 */
int unregister_hdmi_cable_notification(
		struct ext_disp_cable_notify *handler);

int msm_hdmi_register_audio_codec(struct platform_device *pdev,
	struct msm_ext_disp_audio_codec_ops *ops);

#else
static inline int register_hdmi_cable_notification(
		struct ext_disp_cable_notify *handler) {
	return 0;
}

static inline int unregister_hdmi_cable_notification(
		struct ext_disp_cable_notify *handler) {
	return 0;
}

static inline int msm_hdmi_register_audio_codec(struct platform_device *pdev,
		struct msm_ext_disp_audio_codec_ops *ops) {
	return 0;
}
#endif /* CONFIG_FB_MSM_MDSS_HDMI_PANEL */

#endif /*_MSM_EXT_DISPLAY_H_*/
