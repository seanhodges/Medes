#!/bin/bash
 
export LD_LIBRARY_PATH=/usr/lib/firefox
export MOZILLA_FIVE_HOME=/usr/lib/firefox

# Build the Medes binary

g++ -g -o medes \
	`pkg-config --cflags --libs gtk+-2.0,libxml-2.0,firefox-gtkmozembed` \
	-Iinclude \
	src/ConfigContainer.cpp src/ConfigReader.cpp src/AppWindow.cpp src/GeckoEmbed.cpp src/AppMain.cpp
