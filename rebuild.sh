#!/bin/bash

source  /opt/ssd20x/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/bin/
echo "1. check cross-gcc version"
arm-linux-gnueabihf-gcc --version
echo "2. to make"
make -j4
