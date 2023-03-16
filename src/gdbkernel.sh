#!/bin/bash
gdb -q kernel/btos.bin -ex "source kstat.py" -ex "target remote localhost:1234"

