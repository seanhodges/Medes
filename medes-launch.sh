#!/bin/bash

export LD_LIBRARY_PATH=/usr/lib/firefox
export MOZILLA_FIVE_HOME=/usr/lib/firefox

cd /home/sean/Development/medes

./medes webapps/$1.xml

