// SPDX-License-Identifier: GPL-2.0
//
// cs40l26-tables.c -- CS40L26 Boosted Haptic Driver with Integrated DSP and
// Waveform Memory with Advanced Closed Loop Algorithms and LRA protection
//
// Copyright 2021 Cirrus Logic, Inc.
//
// Author: Fred Treven <fred.treven@cirrus.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#include "cs40l26.h"

const struct of_device_id cs40l26_of_match[CS40L26_NUM_DEVS + 1] = {
	{ .compatible = "cirrus,cs40l26a" },
	{ .compatible = "cirrus,cs40l26b" },
	{ }
};
MODULE_DEVICE_TABLE(of, cs40l26_of_match);

const struct regmap_config cs40l26_regmap = {
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.reg_format_endian = REGMAP_ENDIAN_BIG,
	.val_format_endian = REGMAP_ENDIAN_BIG,
	.max_register = CS40L26_LASTREG,
	.num_reg_defaults = 0,
	.precious_reg = cs40l26_precious_reg,
	.readable_reg = cs40l26_readable_reg,
	.volatile_reg = cs40l26_volatile_reg,
	.cache_type = REGCACHE_NONE,
};

const struct dev_pm_ops cs40l26_pm_ops = {
	SET_RUNTIME_PM_OPS(cs40l26_suspend, cs40l26_resume, NULL)
	SET_SYSTEM_SLEEP_PM_OPS(cs40l26_sys_suspend, cs40l26_sys_resume)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(cs40l26_sys_suspend_noirq,
			cs40l26_sys_resume_noirq)
};

const u8 cs40l26_pseq_op_sizes[CS40L26_PSEQ_NUM_OPS][2] = {
	{	CS40L26_PSEQ_OP_WRITE_REG_FULL,
		CS40L26_PSEQ_OP_WRITE_REG_FULL_WORDS},
	{	CS40L26_PSEQ_OP_WRITE_FIELD,
		CS40L26_PSEQ_OP_WRITE_FIELD_WORDS},
	{	CS40L26_PSEQ_OP_WRITE_REG_ADDR8,
		CS40L26_PSEQ_OP_WRITE_REG_ADDR8_WORDS},
	{	CS40L26_PSEQ_OP_WRITE_REG_INCR,
		CS40L26_PSEQ_OP_WRITE_REG_INCR_WORDS},
	{	CS40L26_PSEQ_OP_WRITE_REG_L16,
		CS40L26_PSEQ_OP_WRITE_REG_L16_WORDS},
	{	CS40L26_PSEQ_OP_WRITE_REG_H16,
		CS40L26_PSEQ_OP_WRITE_REG_H16_WORDS},
	{	CS40L26_PSEQ_OP_DELAY,
		CS40L26_PSEQ_OP_DELAY_WORDS},
	{	CS40L26_PSEQ_OP_END,
		CS40L26_PSEQ_OP_END_WORDS},
};

struct regulator_bulk_data cs40l26_supplies[CS40L26_NUM_SUPPLIES] = {
	{ .supply = CS40L26_VP_SUPPLY_NAME },
	{ .supply = CS40L26_VA_SUPPLY_NAME },
};

const struct mfd_cell cs40l26_devs[CS40L26_NUM_MFD_DEVS] = {
	{
		.name = "cs40l26-codec",
		.of_compatible = "cs40l26-codec",
	},
};

const u32 cs40l26_attn_q21_2_vals[CS40L26_NUM_PCT_MAP_VALUES] = {
	400, /* MUTE */
	160, /* 1% */
	136,
	122,
	112,
	104,
	98,
	92,
	88,
	84,
	80,
	77,
	74,
	71,
	68,
	66,
	64,
	62,
	60,
	58,
	56,
	54,
	53,
	51,
	50,
	48, /* 25% */
	47,
	45,
	44,
	43,
	42,
	41,
	40,
	39,
	37,
	36,
	35,
	35,
	34,
	33,
	32,
	31,
	30,
	29,
	29,
	28,
	27,
	26,
	26,
	25,
	24, /* 50 % */
	23,
	23,
	22,
	21,
	21,
	20,
	20,
	19,
	18,
	18,
	17,
	17,
	16,
	16,
	15,
	14,
	14,
	13,
	13,
	12,
	12,
	11,
	11,
	10,
	10, /* 75% */
	10,
	9,
	9,
	8,
	8,
	7,
	7,
	6,
	6,
	6,
	5,
	5,
	4,
	4,
	4,
	3,
	3,
	3,
	2,
	2,
	1,
	1,
	1,
	0,
	0, /* 100% */
};

bool cs40l26_precious_reg(struct device *dev, unsigned int reg)
{
	return false;
}
EXPORT_SYMBOL(cs40l26_precious_reg);

bool cs40l26_volatile_reg(struct device *dev, unsigned int reg)
{
	return false;
}
EXPORT_SYMBOL(cs40l26_volatile_reg);

bool cs40l26_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS40L26_DEVID:
	case CS40L26_REVID:
	case CS40L26_FABID:
	case CS40L26_RELID:
	case CS40L26_OTPID:
	case CS40L26_SFT_RESET:
	case CS40L26_TEST_KEY_CTRL:
	case CS40L26_USER_KEY_CTRL:
	case CS40L26_CTRL_ASYNC0:
	case CS40L26_CTRL_ASYNC1:
	case CS40L26_CTRL_ASYNC2:
	case CS40L26_CTRL_ASYNC3:
	case CS40L26_CIF_MON1:
	case CS40L26_CIF_MON2:
	case CS40L26_CIF_MON_PADDR:
	case CS40L26_CTRL_IF_SPARE1:
	case CS40L26_CTRL_IF_I2C:
	case CS40L26_CTRL_IF_I2C_1_CONTROL:
	case CS40L26_CTRL_IF_I2C_1_BROADCAST:
	case CS40L26_APB_MSTR_DSP_BRIDGE_ERR:
	case CS40L26_CIF1_BRIDGE_ERR:
	case CS40L26_CIF2_BRIDGE_ERR:
	case CS40L26_OTP_CTRL0:
	case CS40L26_OTP_CTRL1:
	case CS40L26_OTP_CTRL3:
	case CS40L26_OTP_CTRL4:
	case CS40L26_OTP_CTRL5:
	case CS40L26_OTP_CTRL6:
	case CS40L26_OTP_CTRL7:
	case CS40L26_OTP_CTRL8:
	case CS40L26_GLOBAL_ENABLES:
	case CS40L26_BLOCK_ENABLES:
	case CS40L26_BLOCK_ENABLES2:
	case CS40L26_GLOBAL_OVERRIDES:
	case CS40L26_GLOBAL_SYNC:
	case CS40L26_GLOBAL_STATUS:
	case CS40L26_DISCH_FILT:
	case CS40L26_OSC_TRIM:
	case CS40L26_ERROR_RELEASE:
	case CS40L26_PLL_OVERRIDE:
	case CS40L26_CHIP_STATUS_1:
	case CS40L26_CHIP_STATUS_2:
	case CS40L26_BIAS_PTE_MODE_CONTROL:
	case CS40L26_SCL_PAD_CONTROL:
	case CS40L26_SDA_PAD_CONTROL:
	case CS40L26_LRCK_PAD_CONTROL:
	case CS40L26_SCLK_PAD_CONTROL:
	case CS40L26_SDIN_PAD_CONTROL:
	case CS40L26_SDOUT_PAD_CONTROL:
	case CS40L26_GPIO_PAD_CONTROL:
	case CS40L26_MDSYNC_PAD_CONTROL:
	case CS40L26_JTAG_CONTROL:
	case CS40L26_GPIO1_PAD_CONTROL:
	case CS40L26_GPIO_GLOBAL_ENABLE_CONTROL:
	case CS40L26_GPIO_LEVELSHIFT_BYPASS:
	case CS40L26_I2C_ADDR_DETECT_CNTL0:
	case CS40L26_I2C_ADDR_DET_STATUS0:
	case CS40L26_DEVID_METAL:
	case CS40L26_PWRMGT_CTL:
	case CS40L26_WAKESRC_CTL:
	case CS40L26_WAKEI2C_CTL:
	case CS40L26_PWRMGT_STS:
	case CS40L26_PWRMGT_RST:
	case CS40L26_REFCLK_INPUT:
	case CS40L26_DSP_CLOCK_GEARING:
	case CS40L26_GLOBAL_SAMPLE_RATE:
	case CS40L26_DATA_FS_SEL:
	case CS40L26_FREE_RUN_FORCE:
	case CS40L26_ASP_RATE_DOUBLE_CONTROL0:
	case CS40L26_NZ_AUDIO_DETECT0:
	case CS40L26_NZ_AUDIO_DETECT1:
	case CS40L26_NZ_AUDIO_DETECT2:
	case CS40L26_PLL_REFCLK_DETECT_0:
	case CS40L26_SP_SCLK_CLOCKING:
	case CS40L26_CONFIG0:
	case CS40L26_CONFIG1:
	case CS40L26_CONFIG2:
	case CS40L26_FS_MON_0:
	case CS40L26_FS_MON_1:
	case CS40L26_FS_MON_2:
	case CS40L26_FS_MON_OVERRIDE:
	case CS40L26_DFT:
	case CS40L26_ANALOG_ADC_CONTROLS:
	case CS40L26_SPK_CHOP_CLK_CONTROLS:
	case CS40L26_DSP1_SAMPLE_RATE_RX1:
	case CS40L26_DSP1_SAMPLE_RATE_RX2:
	case CS40L26_DSP1_SAMPLE_RATE_TX1:
	case CS40L26_DSP1_SAMPLE_RATE_TX2:
	case CS40L26_CLOCK_PHASE:
	case CS40L26_USER_CONTROL:
	case CS40L26_CONFIG_RATES:
	case CS40L26_LOOP_PARAMETERS:
	case CS40L26_LDOA_CONTROL:
	case CS40L26_DCO_CONTROL:
	case CS40L26_MISC_CONTROL:
	case CS40L26_LOOP_OVERRIDES:
	case CS40L26_DCO_CTRL_OVERRIDES:
	case CS40L26_CONTROL_READ:
	case CS40L26_CONTROL_READ_2:
	case CS40L26_DCO_CAL_CONTROL_1:
	case CS40L26_DCO_CAL_CONTROL_2:
	case CS40L26_DCO_CAL_STATUS:
	case CS40L26_SYNC_TX_RX_ENABLES:
	case CS40L26_SYNC_POWER_CTL:
	case CS40L26_SYNC_SW_TX_ID:
	case CS40L26_SYNC_SW_RX:
	case CS40L26_SYNC_SW_TX:
	case CS40L26_SYNC_LSW_RX:
	case CS40L26_SYNC_LSW_TX:
	case CS40L26_SYNC_SW_DATA_TX_STATUS:
	case CS40L26_SYNC_SW_DATA_RX_STATUS:
	case CS40L26_SYNC_ERROR_STATUS:
	case CS40L26_MDSYNC_SYNC_RX_DECODE_CTL_1:
	case CS40L26_MDSYNC_SYNC_RX_DECODE_CTL_2:
	case CS40L26_MDSYNC_SYNC_TX_ENCODE_CTL:
	case CS40L26_MDSYNC_SYNC_IDLE_STATE_CTL:
	case CS40L26_MDSYNC_SYNC_SLEEP_STATE_CTL:
	case CS40L26_MDSYNC_SYNC_TYPE:
	case CS40L26_MDSYNC_SYNC_TRIGGER:
	case CS40L26_MDSYNC_SYNC_PTE0:
	case CS40L26_MDSYNC_SYNC_PTE1:
	case CS40L26_SYNC_PTE2:
	case CS40L26_SYNC_PTE3:
	case CS40L26_VBST_CTL_1:
	case CS40L26_VBST_CTL_2:
	case CS40L26_BST_IPK_CTL:
	case CS40L26_SOFT_RAMP:
	case CS40L26_BST_LOOP_COEFF:
	case CS40L26_LBST_SLOPE:
	case CS40L26_BST_SW_FREQ:
	case CS40L26_BST_DCM_CTL:
	case CS40L26_DCM_FORCE:
	case CS40L26_VBST_OVP:
	case CS40L26_BST_DCR:
	case CS40L26_VPI_LIMIT_MODE:
	case CS40L26_VPI_LIMITING:
	case CS40L26_VPI_VP_THLDS:
	case CS40L26_VPI_TRACKING:
	case CS40L26_VPI_TRIG_TIME:
	case CS40L26_VPI_TRIG_STEPS:
	case CS40L26_VPI_STATES:
	case CS40L26_VPI_OUTPUT_RATE:
	case CS40L26_VMON_IMON_VOL_POL:
	case CS40L26_SPKMON_RATE_SEL:
	case CS40L26_MONITOR_FILT:
	case CS40L26_IMON_COMP:
	case CS40L26_WARN_LIMIT_THRESHOLD:
	case CS40L26_CONFIGURATION:
	case CS40L26_STATUS:
	case CS40L26_ENABLES_AND_CODES_ANA:
	case CS40L26_ENABLES_AND_CODES_DIG:
	case CS40L26_CALIBR_STATUS:
	case CS40L26_TEMP_RESYNC:
	case CS40L26_ERROR_LIMIT_THLD_OVERRIDE:
	case CS40L26_WARN_LIMIT_THLD_OVERRIDE:
	case CS40L26_CALIBR_ROUTINE_CONFIGURATIONS:
	case CS40L26_STATUS_FS:
	case CS40L26_ASP_ENABLES1:
	case CS40L26_ASP_CONTROL1:
	case CS40L26_ASP_CONTROL2:
	case CS40L26_ASP_CONTROL3:
	case CS40L26_ASP_FRAME_CONTROL1:
	case CS40L26_ASP_FRAME_CONTROL5:
	case CS40L26_ASP_DATA_CONTROL1:
	case CS40L26_ASP_DATA_CONTROL5:
	case CS40L26_ASP_LATENCY1:
	case CS40L26_ASP_CONTROL4:
	case CS40L26_ASP_FSYNC_CONTROL1:
	case CS40L26_ASP_FSYNC_CONTROL2:
	case CS40L26_ASP_FSYNC_STATUS1:
	case CS40L26_DACPCM1_INPUT:
	case CS40L26_DACMETA1_INPUT:
	case CS40L26_DACPCM2_INPUT:
	case CS40L26_ASPTX1_INPUT:
	case CS40L26_ASPTX2_INPUT:
	case CS40L26_ASPTX3_INPUT:
	case CS40L26_ASPTX4_INPUT:
	case CS40L26_DSP1RX1_INPUT:
	case CS40L26_DSP1RX2_INPUT:
	case CS40L26_DSP1RX3_INPUT:
	case CS40L26_DSP1RX4_INPUT:
	case CS40L26_DSP1RX5_INPUT:
	case CS40L26_DSP1RX6_INPUT:
	case CS40L26_NGATE1_INPUT:
	case CS40L26_NGATE2_INPUT:
	case CS40L26_SPARE_CP_BITS_0:
	case CS40L26_VIS_ADDR_CNTL1_4:
	case CS40L26_VIS_ADDR_CNTL5_8:
	case CS40L26_VIS_ADDR_CNTL9_12:
	case CS40L26_VIS_ADDR_CNTL13_16:
	case CS40L26_VIS_ADDR_CNTL_17_20:
	case CS40L26_BLOCK_SEL_CNTL0_3:
	case CS40L26_BIT_SEL_CNTL:
	case CS40L26_ANALOG_VIS_CNTL:
	case CS40L26_AMP_CTRL:
	case CS40L26_VPBR_CONFIG:
	case CS40L26_VBBR_CONFIG:
	case CS40L26_VPBR_STATUS:
	case CS40L26_VBBR_STATUS:
	case CS40L26_OTW_CONFIG:
	case CS40L26_AMP_ERROR_VOL_SEL:
	case CS40L26_VPBR_FILTER_CONFIG:
	case CS40L26_VBBR_FILTER_CONFIG:
	case CS40L26_VOL_STATUS_TO_DSP:
	case CS40L26_AMP_GAIN:
	case CS40L26_SVC_CTRL:
	case CS40L26_SVC_SER_R:
	case CS40L26_SVC_R_LPF:
	case CS40L26_SVC_FILT_CFG:
	case CS40L26_SVC_SER_L_CTRL:
	case CS40L26_SVC_SER_C_CTRL:
	case CS40L26_SVC_PAR_RLC_SF:
	case CS40L26_SVC_PAR_RLC_C1:
	case CS40L26_SVC_PAR_RLC_C2:
	case CS40L26_SVC_PAR_RLC_B1:
	case CS40L26_SVC_GAIN:
	case CS40L26_SVC_STATUS:
	case CS40L26_SVC_IMON_SF:
	case CS40L26_DAC_MSM_CONFIG:
	case CS40L26_TST_DAC_MSM_CONFIG:
	case CS40L26_ALIVE_DCIN_WD:
	case CS40L26_IRQ1_CFG:
	case CS40L26_IRQ1_STATUS:
	case CS40L26_IRQ1_EINT_1:
	case CS40L26_IRQ1_EINT_2:
	case CS40L26_IRQ1_EINT_3:
	case CS40L26_IRQ1_EINT_4:
	case CS40L26_IRQ1_EINT_5:
	case CS40L26_IRQ1_STS_1:
	case CS40L26_IRQ1_STS_2:
	case CS40L26_IRQ1_STS_3:
	case CS40L26_IRQ1_STS_4:
	case CS40L26_IRQ1_STS_5:
	case CS40L26_IRQ1_MASK_1:
	case CS40L26_IRQ1_MASK_2:
	case CS40L26_IRQ1_MASK_3:
	case CS40L26_IRQ1_MASK_4:
	case CS40L26_IRQ1_MASK_5:
	case CS40L26_IRQ1_FRC_1:
	case CS40L26_IRQ1_FRC_2:
	case CS40L26_IRQ1_FRC_3:
	case CS40L26_IRQ1_FRC_4:
	case CS40L26_IRQ1_FRC_5:
	case CS40L26_IRQ1_EDGE_1:
	case CS40L26_IRQ1_POL_1:
	case CS40L26_IRQ1_POL_2:
	case CS40L26_IRQ1_POL_3:
	case CS40L26_IRQ1_POL_5:
	case CS40L26_IRQ1_DB_2:
	case CS40L26_GPIO_STATUS1:
	case CS40L26_GPIO_FORCE:
	case CS40L26_GPIO1_CTRL1:
	case CS40L26_GPIO2_CTRL1:
	case CS40L26_GPIO3_CTRL1:
	case CS40L26_GPIO4_CTRL1:
	case CS40L26_MIXER_NGATE_CFG:
	case CS40L26_MIXER_NGATE_CH1_CFG:
	case CS40L26_MIXER_NGATE_CH2_CFG:
	case CS40L26_DSP_MBOX_1:
	case CS40L26_DSP_MBOX_2:
	case CS40L26_DSP_MBOX_3:
	case CS40L26_DSP_MBOX_4:
	case CS40L26_DSP_MBOX_5:
	case CS40L26_DSP_MBOX_6:
	case CS40L26_DSP_MBOX_7:
	case CS40L26_DSP_MBOX_8:
	case CS40L26_DSP_VIRTUAL1_MBOX_1:
	case CS40L26_DSP_VIRTUAL1_MBOX_2:
	case CS40L26_DSP_VIRTUAL1_MBOX_3:
	case CS40L26_DSP_VIRTUAL1_MBOX_4:
	case CS40L26_DSP_VIRTUAL1_MBOX_5:
	case CS40L26_DSP_VIRTUAL1_MBOX_6:
	case CS40L26_DSP_VIRTUAL1_MBOX_7:
	case CS40L26_DSP_VIRTUAL1_MBOX_8:
	case CS40L26_DSP_VIRTUAL2_MBOX_1:
	case CS40L26_DSP_VIRTUAL2_MBOX_2:
	case CS40L26_DSP_VIRTUAL2_MBOX_3:
	case CS40L26_DSP_VIRTUAL2_MBOX_4:
	case CS40L26_DSP_VIRTUAL2_MBOX_5:
	case CS40L26_DSP_VIRTUAL2_MBOX_6:
	case CS40L26_DSP_VIRTUAL2_MBOX_7:
	case CS40L26_DSP_VIRTUAL2_MBOX_8:
	case CS40L26_TIMER1_CONTROL:
	case CS40L26_TIMER1_COUNT_PRESET:
	case CS40L26_TIMER1_START_AND_STOP:
	case CS40L26_TIMER1_STATUS:
	case CS40L26_TIMER1_COUNT_READBACK:
	case CS40L26_TIMER1_DSP_CLOCK_CONFIG:
	case CS40L26_TIMER1_DSP_CLOCK_STATUS:
	case CS40L26_TIMER2_CONTROL:
	case CS40L26_TIMER2_COUNT_PRESET:
	case CS40L26_TIMER2_START_AND_STOP:
	case CS40L26_TIMER2_STATUS:
	case CS40L26_TIMER2_COUNT_READBACK:
	case CS40L26_TIMER2_DSP_CLOCK_CONFIG:
	case CS40L26_TIMER2_DSP_CLOCK_STATUS:
	case CS40L26_DFT_JTAG_CTRL:
	case CS40L26_TEMP_CAL2:
	case CS40L26_OTP_MEM0 ...
CS40L26_OTP_MEM31:
	case CS40L26_DSP1_XMEM_PACKED_0 ...
CS40L26_DSP1_XMEM_PACKED_6143:
	case CS40L26_DSP1_XROM_PACKED_0 ...
CS40L26_DSP1_XROM_PACKED_4604:
	case CS40L26_DSP1_XMEM_UNPACKED32_0 ...
CS40L26_DSP1_XROM_UNPACKED32_3070:
	case CS40L26_DSP1_TIMESTAMP_COUNT:
	case CS40L26_DSP1_SYS_INFO_ID:
	case CS40L26_DSP1_SYS_INFO_VERSION:
	case CS40L26_DSP1_SYS_INFO_CORE_ID:
	case CS40L26_DSP1_SYS_INFO_AHB_ADDR:
	case CS40L26_DSP1_SYS_INFO_XM_SRAM_SIZE:
	case CS40L26_DSP1_SYS_INFO_XM_ROM_SIZE:
	case CS40L26_DSP1_SYS_INFO_YM_SRAM_SIZE:
	case CS40L26_DSP1_SYS_INFO_YM_ROM_SIZE:
	case CS40L26_DSP1_SYS_INFO_PM_SRAM_SIZE:
	case CS40L26_DSP1_SYS_INFO_PM_BOOT_SIZE:
	case CS40L26_DSP1_SYS_INFO_FEATURES:
	case CS40L26_DSP1_SYS_INFO_FIR_FILTERS:
	case CS40L26_DSP1_SYS_INFO_LMS_FILTERS:
	case CS40L26_DSP1_SYS_INFO_XM_BANK_SIZE:
	case CS40L26_DSP1_SYS_INFO_YM_BANK_SIZE:
	case CS40L26_DSP1_SYS_INFO_PM_BANK_SIZE:
	case CS40L26_DSP1_SYS_INFO_STREAM_ARB:
	case CS40L26_DSP1_SYS_INFO_XM_EMEM_SIZE:
	case CS40L26_DSP1_SYS_INFO_YM_EMEM_SIZE:
	case CS40L26_DSP1_AHBM_WINDOW0_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW0_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW1_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW1_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW2_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW2_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW3_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW3_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW4_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW4_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW5_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW5_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW6_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW6_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW7_CONTROL_0:
	case CS40L26_DSP1_AHBM_WINDOW7_CONTROL_1:
	case CS40L26_DSP1_AHBM_WINDOW_DEBUG_0:
	case CS40L26_DSP1_AHBM_WINDOW_DEBUG_1:
	case CS40L26_DSP1_XMEM_UNPACKED24_0 ...
CS40L26_DSP1_XMEM_UNPACKED24_8191:
	case CS40L26_DSP1_XROM_UNPACKED24_0 ...
CS40L26_DSP1_XROM_UNPACKED24_6141:
	case CS40L26_DSP1_CLOCK_FREQ:
	case CS40L26_DSP1_CLOCK_STATUS:
	case CS40L26_DSP1_CORE_SOFT_RESET:
	case CS40L26_DSP1_CORE_WRAP_STATUS:
	case CS40L26_DSP1_TIMER_CONTROL:
	case CS40L26_DSP1_STREAM_ARB_CONTROL:
	case CS40L26_DSP1_NMI_CONTROL1:
	case CS40L26_DSP1_NMI_CONTROL2:
	case CS40L26_DSP1_NMI_CONTROL3:
	case CS40L26_DSP1_NMI_CONTROL4:
	case CS40L26_DSP1_NMI_CONTROL5:
	case CS40L26_DSP1_NMI_CONTROL6:
	case CS40L26_DSP1_NMI_CONTROL7:
	case CS40L26_DSP1_NMI_CONTROL8:
	case CS40L26_DSP1_RESUME_CONTROL:
	case CS40L26_DSP1_IRQ1_CONTROL:
	case CS40L26_DSP1_IRQ2_CONTROL:
	case CS40L26_DSP1_IRQ3_CONTROL:
	case CS40L26_DSP1_IRQ4_CONTROL:
	case CS40L26_DSP1_IRQ5_CONTROL:
	case CS40L26_DSP1_IRQ6_CONTROL:
	case CS40L26_DSP1_IRQ7_CONTROL:
	case CS40L26_DSP1_IRQ8_CONTROL:
	case CS40L26_DSP1_IRQ9_CONTROL:
	case CS40L26_DSP1_IRQ10_CONTROL:
	case CS40L26_DSP1_IRQ11_CONTROL:
	case CS40L26_DSP1_IRQ12_CONTROL:
	case CS40L26_DSP1_IRQ13_CONTROL:
	case CS40L26_DSP1_IRQ14_CONTROL:
	case CS40L26_DSP1_IRQ15_CONTROL:
	case CS40L26_DSP1_IRQ16_CONTROL:
	case CS40L26_DSP1_IRQ17_CONTROL:
	case CS40L26_DSP1_IRQ18_CONTROL:
	case CS40L26_DSP1_IRQ19_CONTROL:
	case CS40L26_DSP1_IRQ20_CONTROL:
	case CS40L26_DSP1_IRQ21_CONTROL:
	case CS40L26_DSP1_IRQ22_CONTROL:
	case CS40L26_DSP1_IRQ23_CONTROL:
	case CS40L26_DSP1_SCRATCH1:
	case CS40L26_DSP1_SCRATCH2:
	case CS40L26_DSP1_SCRATCH3:
	case CS40L26_DSP1_SCRATCH4:
	case CS40L26_DSP1_CCM_CORE_CONTROL:
	case CS40L26_DSP1_CCM_CLK_OVERRIDE:
	case CS40L26_DSP1_MEM_CTRL_XM_MSTR_EN:
	case CS40L26_DSP1_MEM_CTRL_XM_CORE_PRIO:
	case CS40L26_DSP1_MEM_CTRL_XM_PL0_PRIO:
	case CS40L26_DSP1_MEM_CTRL_XM_PL1_PRIO:
	case CS40L26_DSP1_MEM_CTRL_XM_PL2_PRIO:
	case CS40L26_DSP1_MEM_CTRL_XM_NPL0_PRIO:
	case CS40L26_DSP1_MEM_CTRL_YM_MSTR_EN:
	case CS40L26_DSP1_MEM_CTRL_YM_CORE_PRIO:
	case CS40L26_DSP1_MEM_CTRL_YM_PL0_PRIO:
	case CS40L26_DSP1_MEM_CTRL_YM_PL1_PRIO:
	case CS40L26_DSP1_MEM_CTRL_YM_PL2_PRIO:
	case CS40L26_DSP1_MEM_CTRL_YM_NPL0_PRIO:
	case CS40L26_DSP1_MEM_CTRL_PM_MSTR_EN:
	case CS40L26_DSP1_MEM_CTRL_FIXED_PRIO:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH0_ADDR:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH0_EN:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH0_DATA_LO:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH0_DATA_HI:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH1_ADDR:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH1_EN:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH1_DATA_LO:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH1_DATA_HI:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH2_ADDR:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH2_EN:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH2_DATA_LO:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH2_DATA_HI:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH3_ADDR:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH3_EN:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH3_DATA_LO:
	case CS40L26_DSP1_MEM_CTRL_PM_PATCH3_DATA_HI:
	case CS40L26_DSP1_MPU_XMEM_ACCESS_0:
	case CS40L26_DSP1_MPU_YMEM_ACCESS_0:
	case CS40L26_DSP1_MPU_WINDOW_ACCESS_0:
	case CS40L26_DSP1_MPU_XREG_ACCESS_0:
	case CS40L26_DSP1_MPU_YREG_ACCESS_0:
	case CS40L26_DSP1_MPU_XMEM_ACCESS_1:
	case CS40L26_DSP1_MPU_YMEM_ACCESS_1:
	case CS40L26_DSP1_MPU_WINDOW_ACCESS_1:
	case CS40L26_DSP1_MPU_XREG_ACCESS_1:
	case CS40L26_DSP1_MPU_YREG_ACCESS_1:
	case CS40L26_DSP1_MPU_XMEM_ACCESS_2:
	case CS40L26_DSP1_MPU_YMEM_ACCESS_2:
	case CS40L26_DSP1_MPU_WINDOW_ACCESS_2:
	case CS40L26_DSP1_MPU_XREG_ACCESS_2:
	case CS40L26_DSP1_MPU_YREG_ACCESS_2:
	case CS40L26_DSP1_MPU_XMEM_ACCESS_3:
	case CS40L26_DSP1_MPU_YMEM_ACCESS_3:
	case CS40L26_DSP1_MPU_WINDOW_ACCESS_3:
	case CS40L26_DSP1_MPU_XREG_ACCESS_3:
	case CS40L26_DSP1_MPU_YREG_ACCESS_3:
	case CS40L26_DSP1_MPU_X_EXT_MEM_ACCESS_0:
	case CS40L26_DSP1_MPU_Y_EXT_MEM_ACCESS_0:
	case CS40L26_DSP1_MPU_XM_VIO_ADDR:
	case CS40L26_DSP1_MPU_XM_VIO_STATUS:
	case CS40L26_DSP1_MPU_YM_VIO_ADDR:
	case CS40L26_DSP1_MPU_YM_VIO_STATUS:
	case CS40L26_DSP1_MPU_PM_VIO_ADDR:
	case CS40L26_DSP1_MPU_PM_VIO_STATUS:
	case CS40L26_DSP1_MPU_LOCK_CONFIG:
	case CS40L26_DSP1_MPU_WDT_RESET_CONTROL:
	case CS40L26_DSP1_STREAM_ARB_MSTR1_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_MSTR1_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_MSTR1_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_MSTR2_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_MSTR2_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_MSTR2_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_MSTR3_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_MSTR3_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_MSTR3_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_MSTR4_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_MSTR4_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_MSTR4_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_TX1_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_TX1_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_TX2_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_TX2_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_TX3_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_TX3_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_TX4_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_TX4_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_TX5_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_TX5_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_TX6_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_TX6_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_RX1_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_RX1_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_RX2_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_RX2_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_RX3_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_RX3_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_RX4_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_RX4_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_RX5_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_RX5_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_RX6_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_RX6_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_IRQ1_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_IRQ1_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_IRQ1_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_IRQ2_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_IRQ2_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_IRQ2_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_IRQ3_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_IRQ3_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_IRQ3_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_IRQ4_CONFIG_0:
	case CS40L26_DSP1_STREAM_ARB_IRQ4_CONFIG_1:
	case CS40L26_DSP1_STREAM_ARB_IRQ4_CONFIG_2:
	case CS40L26_DSP1_STREAM_ARB_RESYNC_MSK1:
	case CS40L26_DSP1_STREAM_ARB_ERR_STATUS:
	case CS40L26_DSP1_WDT_CONTROL:
	case CS40L26_DSP1_WDT_STATUS:
	case CS40L26_DSP1_ACCEL_DB_IN:
	case CS40L26_DSP1_ACCEL_LINEAR_OUT:
	case CS40L26_DSP1_ACCEL_LINEAR_IN:
	case CS40L26_DSP1_ACCEL_DB_OUT:
	case CS40L26_DSP1_ACCEL_RAND_NUM:
	case CS40L26_DSP1_YMEM_PACKED_0:
	case CS40L26_DSP1_YMEM_PACKED_1 ...
CS40L26_DSP1_YMEM_PACKED_1532:
	case CS40L26_DSP1_YMEM_UNPACKED32_0 ...
CS40L26_DSP1_YMEM_UNPACKED32_1022:
	case CS40L26_DSP1_YMEM_UNPACKED24_0 ...
CS40L26_DSP1_YMEM_UNPACKED24_2045:
	case CS40L26_DSP1_PMEM_0 ...
CS40L26_DSP1_PMEM_5114:
	case CS40L26_DSP1_PROM_0 ...
CS40L26_DSP1_PROM_30714:
		return true;
	default:
		return false;
	}
}
EXPORT_SYMBOL(cs40l26_readable_reg);
