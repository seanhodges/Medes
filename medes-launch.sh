#!/bin/bash

export LD_LIBRARY_PATH=/usr/lib/firefox
export MOZILLA_FIVE_HOME=/usr/lib/firefox

./medes webapps/$1.xml

