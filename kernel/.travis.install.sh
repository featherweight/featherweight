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

# This script configures the Travis CI environment prior to automated build

# Configure this script to exit on error, skipping downstream commands
set -e

# Needed to convert Red Hat to Debian package
sudo apt-get install alien

mkdir download && \
cd download && \
wget http://ftp.ni.com/support/softlib/labview/labview_runtime/2014/Linux/LabVIEW2014RTE_Linux64.tgz -O lvrte.tgz && \
tar -xzf lvrte.tgz && \
ls && \
sudo alien --install --scripts labview-2014-rte-14.0.0-1.x86_64.rpm
# sudo rpm -Uvh *.rpm

