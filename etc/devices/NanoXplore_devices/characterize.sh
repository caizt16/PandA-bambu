#! /bin/bash

for devices in nx1h35S nx1h140tsp; do
   mkdir -p "$devices-DIR"
   cd "$devices-DIR"
   /users/caizht/panda/bin/eucalyptus --estimate-library="../$devices.xml" --target-scriptfile=../NG-medium.xml --target-datafile="../$devices-seed.xml" -v2 >& "$devices.log" &
   cd ..
done


