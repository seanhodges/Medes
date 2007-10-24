#!/bin/bash

export MOZILLA_FIVE_HOME=/usr/lib/firefox

if [ -e build/Makefile ]; then
	rm -r build/*
fi

cd build
cmake ../
make
cd ../
mv build/medes .

