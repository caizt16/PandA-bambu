#!/bin/bash
export PATH=$PATH:../../src:../../../src:/users/caizht/panda/bin
script=`readlink -e $0`
root_dir=`dirname $script`
mkdir temp
cd temp
#bambu  -fopenmp -v3 --pragma-parse --experimental-setup=BAMBU --channels-type=MEM_ACC_11 --num-accelerators=4 --memory-allocation-policy=NO_BRAM $root_dir/bfs.c --memory-banks-number=4 --simulate $@
bambu  -fopenmp -v6 --experimental-setup=BAMBU --channels-type=MEM_ACC_11 --num-accelerators=4 --memory-allocation-policy=NO_BRAM $root_dir/bfs.c --memory-banks-number=4 --simulate $@
if test $return_value != 0; then
   exit $return_value
fi
cd ..
