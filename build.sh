#!/bin/bash

g++ geckotest.c -o geckotest `pkg-config --cflags --libs gtk+-2.0,firefox-gtkmozembed,firefox-xpcom,firefox-js,firefox-nspr,firefox-nss,firefox-plugin` -lgtkembedmoz -lmozjs -lxpcom
