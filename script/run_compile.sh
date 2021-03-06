#!/bin/bash
OBJ='../obj'
rm -r $OBJ
mkdir $OBJ && cd $OBJ
../configure --prefix=/users/caizht/panda --enable-flopoco --enable-eucalyptus --enable-icarus --enable-verilator --enable-opt  --enable-debug --enable-fast-install CXX=g++-5 CC=gcc-5
make -j8 && make -j8 install
make -j8 documentation
