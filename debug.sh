#!/bin/bash

export LD_LIBRARY_PATH=/usr/lib/firefox
export MOZILLA_FIVE_HOME=/usr/lib/firefox

gdb --args ./medes webapps/googlemaps.xml 
