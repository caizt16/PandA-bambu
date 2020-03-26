#!/bin/bash
export PATH=$PATH:../../src:../../../src:/users/caizht/panda/bin
script=`readlink -e $0`
root_dir=`dirname $script`
policies='ALL_BRAM LSS GSS NO_BRAM EXT_PIPELINED_BRAM'
mkdir mem_example
cd mem_example
for policy in $policies; do
	mkdir $policy
	cd $policy
	#bambu -v4 --clock-period=5 --memory-allocation-policy=$policy --channels-type=MEM_ACC_11 --do-not-use-asynchronous-memories --top-fname=bellmanford $root_dir/constraints.xml $root_dir/bellmanford.c $@
	bambu -v4 --clock-period=5 --memory-allocation-policy=$policy --channels-type=MEM_ACC_11 --do-not-use-asynchronous-memories $root_dir/mips.c $@
	cd ..
done
cd ..
