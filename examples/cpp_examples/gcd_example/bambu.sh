#!/bin/bash
script=$(readlink -e $0)
root_dir=$(dirname $script)
basename_dir=$(basename $root_dir)

export PATH=../../src:../../../src:../../../../src:/users/caizht/panda/bin:$PATH

mkdir -p $basename_dir
mkdir -p $basename_dir/hls
cd $basename_dir/hls
echo "#synthesis and simulation"
#bambu -v5 --print-dot $root_dir/gcd.cc --compiler=I386_GCC5 --generate-tb=$root_dir/test.xml --no-iob --evaluation --discrepancy --top-fname=gcd 
bambu -v5 --print-dot $root_dir/gcd.cc --compiler=I386_GCC5 --generate-tb=$root_dir/test.xml --no-iob --simulate --top-fname=gcd
return_value=$?
if test $return_value != 0; then
   exit $return_value
fi
exit 0
