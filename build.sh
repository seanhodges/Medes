#!/bin/bash

# Build the Medes binary

g++ -g -o medes \
	`pkg-config --cflags --libs gtk+-2.0,libxml-2.0,firefox-gtkmozembed` \
	ConfigContainer.cpp ConfigReader.cpp AppWindow.cpp GeckoEmbed.cpp AppMain.cpp
