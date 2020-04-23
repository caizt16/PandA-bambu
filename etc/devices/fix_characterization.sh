#!/bin/bash
abs_script=$(readlink -e $0)
root_dir=$(dirname $abs_script)/../..
$root_dir/etc/scripts/characterize.py  --eucalyptus=/users/caizht/panda/bin/eucalyptus --spider=/users/caizht/panda/bin/spider --fix $@


