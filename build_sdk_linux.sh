#!/bin/bash
JAVA_HOME=/usr/lib/jvm/jdk1.6.0_43
export JAVA_HOME
. ./build/envsetup.sh
lunch sdk-eng
make -j4 sdk  2>&1 | tee log.txt
