#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=kthread-test
PKG_RELEASE:=2
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define KernelPackage/kthread-test
  SUBMENU:=Other modules
  TITLE:=kthread test modules
  FILES:=$(PKG_BUILD_DIR)/kthread-test.ko
  KCONFIG:=
endef
#  AUTOLOAD:=$(call AutoLoad,30,kthread-test,1)

define KernelPackage/kthread-test/description
 test kthread func
endef

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	SUBDIRS="$(PKG_BUILD_DIR)"

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,kthread-test))
