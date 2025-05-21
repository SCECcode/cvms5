#!/bin/bash

tmp=`uname -s`

if [ $tmp == 'Darwin' ]; then
##for macOS, make sure have automake/aclocal
  brew install automake
  brew reinstall gcc
  brew install libtool
  export PATH="/opt/homebrew/opt/libtool/libexec/gnubin:$PATH"
fi

libtoolize
aclocal -I m4
automake --add-missing --force-missing
autoconf
./configure --prefix=$UCVM_INSTALL_PATH/model/cvms5 --with-etree-libdir=${UCVM_INSTALL_PATH}/lib/euclid3/lib --with-etree-incdir=${UCVM_INSTALL_PATH}/lib/euclid3/include --with-proj-libdir=${UCVM_INSTALL_PATH}/lib/proj/lib --with-proj-incdir=${UCVM_INSTALL_PATH}/lib/proj/include --with-tiff-libdir=${UCVM_INSTALL_PATH}/lib/tiff/lib --with-tiff-incdir=${UCVM_INSTALL_PATH}/lib/tiff/include --with-sqlite-libdir=${UCVM_INSTALL_PATH}/lib/sqlite/lib --with-sqlite-incdir=${UCVM_INSTALL_PATH}/lib/sqlite/include
make
make install

