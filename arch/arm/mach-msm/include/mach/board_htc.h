/* arch/arm/mach-msm/include/mach/BOARD_HTC.h
 * Copyright (C) 2007-2009 HTC Corporation.
 * Author: Thomas Tsai <thomas_tsai@htc.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __ASM_ARCH_MSM_BOARD_HTC_H
#define __ASM_ARCH_MSM_BOARD_HTC_H

#include <linux/types.h>
#include <linux/list.h>
#include <asm/setup.h>
#include <mach/msm_hsusb.h>

struct msm_pmem_setting{
	resource_size_t pmem_start;
	resource_size_t pmem_size;
	resource_size_t pmem_adsp_start;
	resource_size_t pmem_adsp_size;
	resource_size_t pmem_gpu0_start;
	resource_size_t pmem_gpu0_size;
	resource_size_t pmem_gpu1_start;
	resource_size_t pmem_gpu1_size;
	resource_size_t pmem_camera_start;
	resource_size_t pmem_camera_size;
	resource_size_t ram_console_start;
	resource_size_t ram_console_size;
	resource_size_t kgsl_start;
	resource_size_t kgsl_size;
#ifdef CONFIG_BUILD_CIQ
	resource_size_t pmem_ciq_start;
	resource_size_t pmem_ciq_size;
	resource_size_t pmem_ciq1_start;
	resource_size_t pmem_ciq1_size;
	resource_size_t pmem_ciq2_start;
	resource_size_t pmem_ciq2_size;
	resource_size_t pmem_ciq3_start;
	resource_size_t pmem_ciq3_size;
#endif
};

enum {
	MSM_SERIAL_UART1	= 0,
	MSM_SERIAL_UART2,
	MSM_SERIAL_UART3,
#ifdef CONFIG_SERIAL_MSM_HS
	MSM_SERIAL_UART1DM,
	MSM_SERIAL_UART2DM,
#endif
	MSM_SERIAL_NUM,
};

enum {
	KERNEL_FLAG_RESERVED_0 = BIT(0),
	KERNEL_FLAG_SERIAL_HSL_ENABLE = BIT(1),
	KERNEL_FLAG_RESERVED_2 = BIT(2),
	KERNEL_FLAG_RESERVED_3 = BIT(3),
	KERNEL_FLAG_KMEMLEAK = BIT(4),
	KERNEL_FLAG_RESERVED_5 = BIT(5),
	KERNEL_FLAG_MDM_CHARM_DEBUG = BIT(6),
	KERNEL_FLAG_MSM_SMD_DEBUG = BIT(7),
	KERNEL_FLAG_RESERVED_8 = BIT(8),
	KERNEL_FLAG_RESERVED_9 = BIT(9),
	KERNEL_FLAG_RESERVED_10 = BIT(10),
	KERNEL_FLAG_RESERVED_11 = BIT(11),
	KERNEL_FLAG_RESERVED_12 = BIT(12),
	KERNEL_FLAG_RESERVED_13 = BIT(13),
	KERNEL_FLAG_RESERVED_14 = BIT(14),
	KERNEL_FLAG_RESERVED_15 = BIT(15),
	KERNEL_FLAG_RIL_DBG_DMUX = BIT(16),
	KERNEL_FLAG_RIL_DBG_RMNET = BIT(17),
	KERNEL_FLAG_RIL_DBG_CMUX = BIT(18),
	KERNEL_FLAG_RIL_DBG_DATA_LPM = BIT(19),
	KERNEL_FLAG_RIL_DBG_CTL = BIT(20),
	KERNEL_FLAG_RIL_DBG_ALDEBUG_LAWDATA = BIT(21),
	KERNEL_FLAG_RIL_DBG_MEMCPY = BIT(22),
	KERNEL_FLAG_RIL_DBG_RPC = BIT(23),
	KERNEL_FLAG_RESERVED_24 = BIT(24),
	KERNEL_FLAG_PM_MONITOR = BIT(25),
	KERNEL_FLAG_ENABLE_FAST_CHARGE = BIT(26),
	KERNEL_FLAG_RESERVED_27 = BIT(27),
	KERNEL_FLAG_RESERVED_28 = BIT(28),
	KERNEL_FLAG_RESERVED_29 = BIT(29),
	KERNEL_FLAG_RESERVED_30 = BIT(30),
	KERNEL_FLAG_GPIO_DUMP = BIT(31),
};

/* common init routines for use by arch/arm/mach-msm/board-*.c */

void __init msm_add_usb_devices(void (*phy_reset) (void), void (*phy_shutdown) (void));
void __init msm_add_usb_id_pin_function(void (*config_usb_id_gpios)(bool enable));
void __init msm_add_usb_id_pin_gpio(int usb_id_pin_io);
void __init msm_enable_car_kit_detect(bool enable);
void __init msm_change_usb_id(__u16 vendor_id, __u16 product_id);
void __init msm_add_mem_devices(struct msm_pmem_setting *setting);
void __init msm_init_pmic_vibrator(int);
#ifdef CONFIG_USB_FUNCTION
void __init msm_register_uart_usb_switch(void (*usb_uart_switch) (int));
void __init msm_register_usb_phy_init_seq(int *int_seq);
void __init msm_init_ums_lun(int lun_num);
void __init msm_set_ums_device_id(int id);
void __init msm_hsusb_set_product(struct msm_hsusb_product *product, int num_products);
#endif

struct mmc_platform_data;
int __init msm_add_sdcc_devices(unsigned int controller, struct mmc_platform_data *plat);
int __init msm_add_serial_devices(unsigned uart);

int board_mfg_mode(void);
int __init board_mcp_monodie(void);
int __init parse_tag_smi(const struct tag *tags);
int __init parse_tag_hwid(const struct tag *tags);
int __init parse_tag_monodie(const struct tag *tags);

void board_get_keycaps_tag(char **);
void board_get_cid_tag(char **);
void board_get_carrier_tag(char **);
void board_get_mid_tag(char **);
int board_emmc_boot(void);

void notify_usb_connected(int online);

char *board_serialno(void);

/*
 * Obviously, we need these in all project.
 * To export a function to get these is too lousy.
 * Each BSP can include board.h to get these.
 *
 * Jay, 15/May/09'
 * */
extern int panel_type;
extern unsigned engineer_id;
unsigned long get_kernel_flag(void);
extern int usb_phy_error;

#if defined(CONFIG_ARCH_MSM8X60)
unsigned int get_radio_flag(void);
#endif

#endif
