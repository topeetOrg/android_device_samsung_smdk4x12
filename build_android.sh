#!/bin/bash

CPU_JOB_NUM=$(grep processor /proc/cpuinfo | awk '{field=$NF};END{print field+1}')
CLIENT=$(whoami)

ROOT_DIR=$(pwd)
KERNEL_DIR="$ROOT_DIR/../kernel/iTop4412_Kernel_3.0"
export KERNEL_DIR

#SEC_PRODUCT='generic' #Enable for generic build


#SEC_PRODUCT=$1
SEC_PRODUCT=smdk4x12

OUT_DIR="$ROOT_DIR/out/target/product/$SEC_PRODUCT"
OUT_HOSTBIN_DIR="$ROOT_DIR/out/host/linux-x86/bin"
 
cp $KERNEL_DIR/arch/arm/boot/zImage device/samsung/smdk4x12/kernel
if [  -f $OUT_DIR/ramdisk.img ]
then
    rm -f $OUT_DIR/ramdisk.img
fi

option="recovery"
function check_exit()
{
	if [ $? != 0 ]
	then
		exit $?
	fi
}

function build_android()
{
	echo
	echo '[[[[[[[ Build android platform ]]]]]]]'
	echo

	START_TIME=`date +%s`
	if [ $SEC_PRODUCT = "generic" ]
	then
		echo make -j$CPU_JOB_NUM
		echo
		make -j$CPU_JOB_NUM
	else
		echo make -j$CPU_JOB_NUM PRODUCT-$SEC_PRODUCT-eng
		echo
		make -j$CPU_JOB_NUM PRODUCT-$SEC_PRODUCT-eng
	fi
	check_exit

	END_TIME=`date +%s`
	let "ELAPSED_TIME=$END_TIME-$START_TIME"
	echo "Total compile time is $ELAPSED_TIME seconds"
}

function make_uboot_img()
{
	cd $OUT_DIR

	echo
	echo '[[[[[[[ Make ramdisk image for u-boot ]]]]]]]'
	echo

	mkimage -A arm -O linux -T ramdisk -C none -a 0x40800000 -n "ramdisk" -d ramdisk.img ramdisk-uboot.img
	check_exit

	rm -f ramdisk.img

	echo
	cd ../../../..
}
#----------NOTICE--------------------------------------------------------
#before compile the recovery image, please setting the option likes below
#	TARGET_NO_KERNEL := false
#in file BoardConfig.mk
#------------------------------------------------------------------------
function make_recovery_img()
{
	echo "MAKE RECOVERY IMAGE----"
	chmod 777 build/tools/releasetools/ota_from_target_files
	$ROOT_DIR/device/samsung/smdk4x12/tools/recovery/mkimage -A arm -O linux -T ramdisk -C none -a 0x40800000 -n "ramdisk" -d $OUT_DIR/ramdisk-recovery.img $OUT_DIR/ramdisk-recovery-uboot.img
	rm -f device/samsung/smdk4x12/kernel
	#make otapackage TARGET_PRODUCT=sc1_dvt1 #mj
}
function make_fastboot_img()
{
	echo
	echo '[[[[[[[ Make additional images for fastboot ]]]]]]]'
	echo

	if [ ! -f $KERNEL_DIR/arch/arm/boot/zImage ]
	then
		echo "No zImage is found at $KERNEL_DIR/arch/arm/boot"
		echo '  Please set KERNEL_DIR if you want to make additional images'
		echo "  Ex.) export KERNEL_DIR=~ID/android_kernel_$SEC_PRODUCT"
		echo
		return
	fi

	echo 'boot.img ->' $OUT_DIR
	cp $KERNEL_DIR/arch/arm/boot/zImage $OUT_DIR/zImage
	$OUT_HOSTBIN_DIR/mkbootimg --kernel $OUT_DIR/zImage --ramdisk $OUT_DIR/ramdisk-uboot.img -o $OUT_DIR/boot.img
	check_exit

	echo 'update.zip ->' $OUT_DIR
	zip -j $OUT_DIR/update.zip $OUT_DIR/android-info.txt $OUT_DIR/boot.img $OUT_DIR/system.img
	check_exit

	echo
}
function make_engmode_img()
{
        cd $OUT_DIR

        echo
        echo '[[[[[[[ Make ramdisk image for engineering mode ]]]]]]]'
        echo

        mkdir temp
        cp ramdisk.img temp/ramdisk.img.gz
        cd temp
        gunzip ramdisk.img.gz
        mkdir ramdisk
        cd ramdisk
        cpio -i -F ../ramdisk.img
	cp $ROOT_DIR/device/samsung/smdk4x12/conf/init.engmode $OUT_DIR/temp/ramdisk/init.rc
        cpio -i -t -F ../ramdisk.img > list
        cpio -o -H newc -O temp.img < list
        gzip temp.img
        cp temp.img.gz $OUT_DIR/temp.img
        cd ../..
	$ROOT_DIR/device/samsung/smdk4x12/tools/engmode/mkimage -A arm -O linux -T ramdisk -C none -a 0x41000000 -n "ramdisk" -d temp.img ramdisk-engmode.img
        rm -f temp.img
        check_exit

        cd ../../../..
        rm -rf $OUT_DIR/temp
}

echo
echo '                Build android for '$SEC_PRODUCT''
echo

case "$SEC_PRODUCT" in
	smdk4x12)
		. build/envsetup.sh
		lunch smdk4x12-eng
		build_android
		make_uboot_ramdisk_img
		#make_recovery_img
		#make_engmode_img
		;;
	*)	
		echo "Please, add SEC_PRODUCT"
		echo "  ./build_android.sh smdk4x12"
		
		exit 1
		;;
esac

echo ok success !!!

exit 0
