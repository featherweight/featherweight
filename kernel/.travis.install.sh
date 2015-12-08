#
#    Copyright (c) 2014-2015 Wirebird Labs LLC. All rights reserved.
#
#    Permission is hereby granted, free of charge, to any person obtaining a copy
#    of this software and associated documentation files (the "Software"),
#    to deal in the Software without restriction, including without limitation
#    the rights to use, copy, modify, merge, publish, distribute, sublicense,
#    and/or sell copies of the Software, and to permit persons to whom
#    the Software is furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included
#    in all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
#    IN THE SOFTWARE.
#

# This script downloads and installs the LabVIEW Runtime Engine for Linux

# Configure this script to exit on error, skipping downstream commands, and also echo commands
set -ve

printenv

LV_DOWNLOAD_URL=http://ftp.ni.com/support/softlib/labview/labview_runtime/2014/Linux/LabVIEW2014RTE_Linux64.tgz
LV_PKG_ORIG=labview-2014-rte-14.0.0-1.x86_64.rpm
#DPKG_FAKEROOT=$TRAVIS_BUILD_DIR/dpkg
#LV_PKG_DEST=labview-2014-rte-14.0.0.tgz
#DPKG_FAKEROOT=$TRAVIS_BUILD_DIR/dpkg

mkdir -p $1
cd $1

# Test for presence of cached packages in download cache
if test -e $LV_PKG_ORIG; then
  echo "Found cached LVRTE package: $LV_PKG_ORIG"
else
  echo "Did not find cached package: $LV_PKG_ORIG"
  wget $LV_DOWNLOAD_URL -O lvrte.tgz && \
  tar -xzf lvrte.tgz
fi
ls -al

rpm2cpio $LV_PKG_ORIG | cpio -idmv
ls -al


ln -sf ./usr/local/lib64/LabVIEW-2014-64/liblvrt.so.14.0.0 liblvrt.so
ln -sf ./usr/local/lib64/LabVIEW-2014-64/liblvrtdark.so.14.0.0 liblvrtdark.so

#if test

#if test -e $LV_PKG_DEST; then
#  echo "Found cached LVRTE package: $LV_PKG_DEST"
#else
#  echo "Did not find cached package: $LV_PKG_DEST"
#  fakeroot alien --to-tgz --veryverbose $LV_PKG_ORIG
#  ls -al
#fi

set +e
#sudo alien --install --veryverbose --scripts $LVPKG

#mkdir -m 777 $DPKG_FAKEROOT
#mkdir -m 777 $DPKG_FAKEROOT/var
#mkdir -m 777 $DPKG_FAKEROOT/var/lib
#mkdir -m 777 $DPKG_FAKEROOT/var/lib/dpkg

#ls -al /var/lib
#ls -al /var/lib/dpkg


#ls -al /usr/local
#ls -al /usr/local/lib

#dpkg --unpack --force-not-root --debug=2000 $LV_PKG_DEST

#tar -xzf $LV_PKG_DEST -C /usr/local/lib
#ls -al /usr/local
#dpkg --force-all --log=../dpkg.log --debug=3773 --install $LV_PKG_DEST
#cat ../dpkg.log
