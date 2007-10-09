#!/bin/bash

g++ -g -o application.bin \
	`pkg-config --cflags --libs gtk+-2.0,libxml-2.0,firefox-gtkmozembed` \
	StringEnum.cpp ConfigContainer.cpp ConfigReader.cpp AppWindow.cpp GeckoEmbed.cpp AppMain.cpp
