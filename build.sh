#!/bin/bash

#g++ geckotest.c -o geckotest `pkg-config --cflags --libs gtk+-2.0,firefox-gtkmozembed,firefox-xpcom,firefox-js,firefox-nspr,firefox-nss,firefox-plugin` -lgtkembedmoz -lmozjs -lxpcom
#g++ AppMain.cpp -o application.bin `pkg-config --cflags --libs gtk+-2.0,firefox-gtkmozembed,firefox-xpcom,firefox-js,firefox-nspr,firefox-nss,firefox-plugin` -lgtkembedmoz -lmozjs -lxpcom

#g++ -g -o application.bin \
#	`pkg-config --cflags --libs gtk+-2.0,libxml-2.0,firefox-gtkmozembed,firefox-xpcom,firefox-js,firefox-nspr,firefox-nss,firefox-plugin` \
#	-lgtkembedmoz -lmozjs -lxpcom \
#	ConfigReader.cpp AppWindow.cpp GeckoEmbed.cpp AppMain.cpp

g++ -g -o application.bin \
	`pkg-config --cflags --libs gtk+-2.0,libxml-2.0,firefox-gtkmozembed` \
	ConfigReader.cpp AppWindow.cpp GeckoEmbed.cpp AppMain.cpp
