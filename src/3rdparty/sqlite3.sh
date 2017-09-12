#!/bin/bash

rm -rf sqlite-amalgamation-3200100
if [ ! -f sqlite-amalgamation-3200100.zip ];
then
	wget https://sqlite.org/2017/sqlite-amalgamation-3200100.zip
fi

unzip sqlite-amalgamation-3200100.zip
mkdir -p originals
unzip -o sqlite-amalgamation-3200100.zip -d originals

cd sqlite-amalgamation-3200100
cp ../sqlite3/btos-build.sh .
cp ../sqlite3/config.h .
./btos-build.sh
