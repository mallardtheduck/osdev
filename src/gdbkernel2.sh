#!/bin/bash
gdb kernel/btos.bin -ex "source kstat.py" -ex "target remote 192.168.99.1:1234"

