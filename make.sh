#!/bin/bash
make \
ARCH=arm \
CROSS_COMPILE=gcc-linaro-7.1.1/bin/arm-linux-gnueabihf- \
EXTRA_CFLAGS=-w
cp arch/arm/boot/zImage AnyKernel2/
cd AnyKernel2/ && zip ../lsm-anykernel.zip $(ls) -r &>/dev/null
echo "Installer zip created @ 'lsm-anykernel.zip'!"

