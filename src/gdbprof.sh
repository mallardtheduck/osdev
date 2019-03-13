#!/bin/bash
nsamples=100
sleeptime=0
pid=$(pidof mysqld)

for x in $(seq 1 $nsamples)
  do
    gdb -ex "set pagination 0" -ex "target remote localhost:1234" -ex "thread apply all bt" -batch 2>/dev/null
    sleep $sleeptime
  done | \
awk '
  BEGIN { s = ""; } 
  /^Thread/ { print s; s = ""; } 
  /^\#/ { if (s != "" ) { s = s "," $2} else { s = $2 } } 
  END { print s }' | \
sort | uniq -c | sort -r -n -k 1,1
