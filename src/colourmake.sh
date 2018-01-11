#!/bin/bash -e

make ${@} 2>&1 | perl -wln -M'Term::ANSIColor' -e '
m/Building|gcc|g\+\+|\bCC\b|\bcc\b/ and print "\e[1;32m", "$_", "\e[0m"
or
m/error|No rule/i and print "\e[1;91m", "$_", "\e[0m"
or
m/warning/i and print "\e[1;93m", "$_", "\e[0m"
or
m/linking|cp|\.ld|\.elx|\.ell|\.a\b/ and print "\e[1;36m", "$_", "\e[0m"
or
print; '

