#!/bin/bash

rm -rf sqlite-amalgamation-3200100
if [ ! -f sqlite-amalgamation-3200100.zip ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/sqlite-amalgamation-3200100.zip
fi

unzip sqlite-amalgamation-3200100.zip
mkdir -p originals
unzip -o sqlite-amalgamation-3200100.zip -d originals

cd sqlite-amalgamation-3200100
patch -p1 -R < ../sqlite3/sqlite3.c.patch
cp ../sqlite3/btos-build.sh .
cp ../sqlite3/config.h .
cp ../sqlite3/sqlitepp.hpp .
./btos-build.sh
