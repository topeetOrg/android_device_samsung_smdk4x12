#
# Copyright (C) 2011 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# This file is executed by build/envsetup.sh, and can use anything
# defined in envsetup.sh.
#
# In particular, you can add lunch options with the add_lunch_combo
# function: add_lunch_combo generic-eng

add_lunch_combo smdk4x12-userdebug
add_lunch_combo smdk4x12-eng

function make_uboot_ramdisk_img()
{
	local OUT_ROOT=$(get_abs_build_var PRODUCT_OUT)
	cd $OUT_ROOT

	echo
	echo '[[[[[[[ Make ramdisk image for u-boot ]]]]]]]'
	echo

	$ROOT_DIR/device/samsung/smdk4x12/tools/recovery/mkimage -A arm -O linux -T ramdisk -C none -a 0x40800000 -n "ramdisk" -d ramdisk.img ramdisk-uboot.img
	if [ $? != 0 ]; then
		echo 'FAIL!'
	fi

	echo "$OUT_ROOT/ramdisk-uboot.img"
	echo 'OK!'

	croot
}
