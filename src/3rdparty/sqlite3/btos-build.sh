#!/bin/bash

source ../../env-os.sh

i686-pc-btos-gcc -shared -o sqlite3.ell sqlite3.c -D_HAVE_SQLITE_CONFIG_H
i686-pc-btos-gcc -o sqlite.elx -L. -lsqlite3 shell.c -include config.h