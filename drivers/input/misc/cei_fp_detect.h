// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019, 2021 The Linux Foundation. All rights reserved.
 */
 
#ifndef _CEI_FP_DETECT_H
#define _CEI_FP_DETECT_H

#include <linux/delay.h>
#include <linux/io.h>
#include <linux/kernel.h>

#define FP_HW_TYPE_EGISTEC 0
#define FP_HW_TYPE_FPC 1

#define MSM_TLMM_GPIO14_BASE 0x0390E000
#define MSM_TLMM_SIZE 0x72000

static inline int cei_fp_module_detect(void)
{
	int value;
	void __iomem *cfg_reg = NULL;
	uint32_t cei_current_dir;

	pr_info("Detecting fingerprint module...\n");

	cfg_reg = ioremap(MSM_TLMM_GPIO14_BASE, MSM_TLMM_SIZE);
	writel_relaxed(0, cfg_reg);
	msleep(100);
	cei_current_dir = readl_relaxed(cfg_reg + 0x4);

	iounmap(cfg_reg);

	value = cei_current_dir & 0x1;

	if (value) {
		pr_info("fp module is fpc");
		return FP_HW_TYPE_FPC;
	}

	pr_info("fp module is egistec or null");
	return FP_HW_TYPE_EGISTEC;
}

#endif /* _CEI_FP_DETECT_H */
