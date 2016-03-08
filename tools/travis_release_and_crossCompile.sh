#!/bin/bash

# pack the linux release
echo "packing the 32bit Linux release"
cd ./build
tar -pczf acpltRTE-linux32.tar.gz acplt
mv acpltRTE-linux32.tar.gz ../acpltRTE-linux32.tar.gz
cd ..
echo "Done."

# windows build
# copy local binaries
echo "Building Windows release"
mkdir ~/localBins
cp ./build/acplt/system/sysbin/* ~/localBins/.
export CPATH=/usr/i686-w64-mingw32/include/
export PATH=/home/travis/localBins:$PATH
cd ./build
rm -R acplt acplt.build
tclsh acplt_build.tcl cross windows32.cross
echo "Packing Windows release"
zip -qr acpltRTE-win32.zip acplt
mv acpltRTE-win32.zip ../acpltRTE-win32.zip
cd ..
echo "Done"

# raspberry pi build
# get toolchain
echo "Building release for Raspberry Pi"
mkdir ~/RaspberryTools
cd ~/RaspberryTools
git clone https://github.com/raspberrypi/tools
cd ~/build/acplt/rte/build
rm -R acplt acplt.build
export CPATH=/home/travis/RaspberryTools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/lib/gcc/arm-linux-gnueabihf/4.8.3/include/
export PATH=/home/travis/RaspberryTools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/:$PATH
tclsh acplt_build.tcl cross raspberryPi.cross
echo "Packing Release for Raspberry Pi"
tar -pczf acpltRTE-RPi.tar.gz acplt
mv acpltRTE-RPi.tar.gz ../acpltRTE-RPi.tar.gz
cd ..
echo "Done."


