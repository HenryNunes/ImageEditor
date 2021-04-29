#!/bin/bash

gcc `pkg-config --cflags gtk+-3.0` -o programa programa.c -lm `pkg-config --libs gtk+-3.0`
