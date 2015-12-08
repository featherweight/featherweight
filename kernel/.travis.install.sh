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

LV_DOWNLOAD=http://ftp.ni.com/support/softlib/labview/labview_runtime/2014/Linux/LabVIEW2014RTE_Linux64.tgz
LV_PKG_ORIG=labview-2014-rte-14.0.0-1.x86_64.rpm
LV_PKG_DEST=labview-2014-rte_14.0.0-2_amd64.deb
DPKG_FAKEROOT=$TRAVIS_BUILD_DIR/dpkg

mkdir -p $1
cd $1
ls -al

# Test for presence of cached packages in download cache
if test -e $LV_PKG_ORIG; then
  echo "Found cached LVRTE package: $LV_PKG_ORIG"
else
  echo "Did not find cached package: $LV_PKG_ORIG"
  wget $LV_DOWNLOAD -O lvrte.tgz && \
  tar -xzf lvrte.tgz
fi

if test -e $LV_PKG_DEST; then
  echo "Found cached LVRTE package: $LV_PKG_DEST"
else
  echo "Did not find cached package: $LV_PKG_DEST"
  fakeroot alien --to-deb --scripts --veryverbose $LV_PKG_ORIG
  ls -al
fi

set +e
#sudo alien --install --veryverbose --scripts $LVPKG

mkdir -m 777 $DPKG_FAKEROOT
mkdir -m 777 $DPKG_FAKEROOT/var
mkdir -m 777 $DPKG_FAKEROOT/var/lib
mkdir -m 777 $DPKG_FAKEROOT/var/lib/dpkg

ls -al /var/lib
ls -al /var/lib/dpkg

#dpkg --unpack --force-not-root --debug=2000 $LV_PKG_DEST

dpkg --install --force-all --log=../dpkg.log --debug=2000 $LV_PKG_DEST
#cat ../dpkg.log
