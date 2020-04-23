#!/bin/bash
abs_script=$(readlink -e $0)
root_dir=$(dirname $abs_script)/../..
#$root_dir/etc/scripts/characterize.py --eucalyptus=/users/caizht/panda/bin/eucalyptus --spider=/users/caizht/panda/bin/spider -s=-d=4 --technology-files=$root_dir/etc/lib/technology/C_COMPLEX_IPs.xml,$root_dir/etc/lib/technology/C_HLS_IPs.xml,$root_dir/etc/lib/technology/C_MEM_IPs.xml,$root_dir/etc/lib/technology/C_PC_IPs.xml,$root_dir/etc/lib/technology/C_PROFILING_IPs.xml,$root_dir/etc/lib/technology/C_VEC_IPs.xml,$root_dir/etc/lib/technology/C_FP_IPs.xml,$root_dir/etc/lib/technology/C_IO_IPs.xml,,$root_dir/etc/lib/technology/C_STD_IPs.xml $@

#$root_dir/etc/scripts/characterize.py --eucalyptus=/users/caizht/panda/bin/eucalyptus --spider=/users/caizht/panda/bin/spider -s="-d4 -v4" --technology-files=$root_dir/etc/lib/technology/C_MEM_IPs.xml,$root_dir/etc/lib/technology/C_HLS_IPs.xml $@ > log.txt 2>&1
$root_dir/etc/scripts/characterize.py --eucalyptus=/users/caizht/panda/bin/eucalyptus --spider=/users/caizht/panda/bin/spider -c="-d4 -v4 import-ip-core=test.xml" -s="-d4 -v4" --technology-files=$root_dir/etc/lib/technology/C_HLS_IPs.xml $@ > log.txt 2>&1


