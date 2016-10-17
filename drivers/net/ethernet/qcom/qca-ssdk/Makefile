# Copyright (c) 2014, The Linux Foundation. All rights reserved.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.


#
# Makefile for the QCA switch sdk
#
# TODO :
# Make it moduelable
# george.wang@ruckuswireless.com
#

#obj ?= .

obj-$(CONFIG_QCOM_SSDK) += qca-ssdk.o

qca-ssdk-objs += src/api/api_access.o \
					src/fal/fal_acl.o \
					src/fal/fal_cosmap.o \
					src/fal/fal_fdb.o \
					src/fal/fal_igmp.o \
					src/fal/fal_init.o \
					src/fal/fal_interface_ctrl.o \
					src/fal/fal_ip.o \
					src/fal/fal_leaky.o \
					src/fal/fal_led.o \
					src/fal/fal_mib.o \
					src/fal/fal_mirror.o \
					src/fal/fal_misc.o \
					src/fal/fal_nat.o \
					src/fal/fal_port_ctrl.o \
					src/fal/fal_portvlan.o \
					src/fal/fal_qos.o \
					src/fal/fal_rate.o \
					src/fal/fal_reg_access.o \
					src/fal/fal_sec.o \
					src/fal/fal_stp.o \
					src/fal/fal_trunk.o \
					src/fal/fal_vlan.o \
					src/hsl/phy/f1_phy.o \
					src/hsl/phy/f2_phy.o \
					src/hsl/phy/hsl_phy.o \
					src/hsl/phy/malibu_phy.o \
					src/hsl/hsl_acl.o \
					src/hsl/hsl_api.o \
					src/hsl/hsl_dev.o \
					src/hsl/hsl_lock.o \
					src/hsl/hsl_port_prop.o \
					src/hsl/dess/dess_acl.o \
					src/hsl/dess/dess_acl_parse.o \
					src/hsl/dess/dess_cosmap.o \
					src/hsl/dess/dess_fdb.o \
					src/hsl/dess/dess_igmp.o \
					src/hsl/dess/dess_init.o \
					src/hsl/dess/dess_interface_ctrl.o \
					src/hsl/dess/dess_ip.o \
					src/hsl/dess/dess_leaky.o \
					src/hsl/dess/dess_led.o \
					src/hsl/dess/dess_mib.o \
					src/hsl/dess/dess_mirror.o \
					src/hsl/dess/dess_misc.o \
					src/hsl/dess/dess_multicast_acl.o \
					src/hsl/dess/dess_nat.o \
					src/hsl/dess/dess_port_ctrl.o \
					src/hsl/dess/dess_portvlan.o \
					src/hsl/dess/dess_psgmii.o \
					src/hsl/dess/dess_qos.o \
					src/hsl/dess/dess_rate.o \
					src/hsl/dess/dess_reg_access.o \
					src/hsl/dess/dess_sec.o \
					src/hsl/dess/dess_stp.o \
					src/hsl/dess/dess_trunk.o \
					src/hsl/dess/dess_vlan.o \
					src/init/ssdk_init.o \
					src/init/ssdk_uci.o \
					src/ref/ref_fdb.o \
					src/ref/ref_mib.o \
					src/ref/ref_misc.o \
					src/ref/ref_port_ctrl.o \
					src/ref/ref_uci.o \
					src/ref/ref_vlan.o \
					src/sal/sd.o \
					src/sal/sw_api_ks_ioctl.o \
					src/shell_lib/shell.o \
					src/shell_lib/shell_config.o \
					src/shell_lib/shell_io.o \
					src/shell_lib/shell_sw.o \
					src/util/util.o


ccflags-y += -I$(obj)/include -I$(obj)/include/api -I$(obj)/include/common -I$(obj)/include/fal -I$(obj)/include/hsl -I$(obj)/include/hsl/phy -I$(obj)/include/hsl/dess -I$(obj)/include/init -I$(obj)/include/ref -I$(obj)/include/sal -I$(obj)/include/shell_lib

ccflags-y += -DKVER34 -DKVER32 -DLNX26_22 -D__KERNEL__ -DKERNEL_MODULE -DDESS -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Wno-format-security -fno-delete-null-pointer-checks -O2 -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -mfpu=vfp -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -DCC_HAVE_ASM_GOTO -Wreturn-type -Wparentheses -Wunused-variable -Wno-error=implicit-function-declaration -Wno-error=strict-prototypes -DIN_ACL -DIN_FDB -DIN_IGMP -DIN_LEAKY -DIN_LED -DIN_MIB -DIN_MIRROR -DIN_MISC -DIN_PORTCONTROL -DIN_PORTVLAN -DIN_QOS -DIN_RATE -DIN_STP -DIN_VLAN -DIN_COSMAP -DIN_IP -DIN_NAT -DIN_TRUNK -DIN_SEC -DIN_INTERFACECONTROL

OS=linux

OS_VER=3_14

BOARD=ipq806x

BOARD_NAME=BOARD_IPQ806X
OS_SUB=31

#MODULE_CFLAG += -D__KERNEL__ -DKERNEL_MODULE $(CPU_CFLAG)

KERNEL_MODE=TRUE
KERNEL_MODULE=TRUE

#FAL=FALSE or not define FAL, FAL will not be included in SSDK
FAL=TRUE

#CHIP_TYPE can be defined as ATHENA, GARUDA, SHIVA, HORUS, ISIS, ISISC, DESS and ALL_CHIP(ALL_CHIP means GARUDA, SHIVA, HORUS, ISIS, ISISC and DESS)
CHIP_TYPE=DESS

#UK_IF=FALSE or not define UK_IF, UK_IF will not be included in SSDK
#when UK_IF=TRUE one of UK_NETLINK,UK_IOCTL must be defined as TRUE
UK_IF=TRUE
#UK_IOCTL=TRUE define user-kernel space communication based on ioctl
UK_IOCTL=TRUE
UK_MINOR_DEV=254

#API_LOCK=FALSE or not define API_LOCK, API_LOCK will not be included in SSDK
API_LOCK=FALSE

#REG_ACCESS_SPEEDUP=FALSE or not define REG_ACCESS_SPEEDUP, REG_ACCESS_SPEEDUP will not be enabled, now only ISIS supports
REG_ACCESS_SPEEDUP=FALSE

#ALL supported features:
#ACL FDB IGMP LEAKY LED MIB MIRROR MISC PORTCONTROL PORTVLAN QOS RATE STP VLAN
#IN_X=FALSE or not define IN_X, X will not be included in SSDK
IN_ACL=TRUE
IN_FDB=TRUE
IN_IGMP=TRUE
IN_LEAKY=TRUE
IN_LED=TRUE
IN_MIB=TRUE
IN_MIRROR=TRUE
IN_MISC=TRUE
IN_PORTCONTROL=TRUE
IN_PORTVLAN=TRUE
IN_QOS=TRUE
IN_RATE=TRUE
IN_STP=TRUE
IN_VLAN=TRUE
IN_REDUCED_ACL=FALSE
IN_COSMAP=TRUE
IN_IP=TRUE
IN_NAT=TRUE
IN_TRUNK=TRUE
IN_SEC=TRUE
IN_NAT_HELPER=FALSE
IN_RFS=TRUE
IN_INTERFACECONTROL=TRUE
IN_MACBLOCK=FALSE
