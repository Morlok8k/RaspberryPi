#!/bin/bash

echo pcd8544_rpi.c
gcc -o cpushow pcd8544_rpi.c PCD8544.c  -L/usr/local/lib -lwiringPi

echo pcd8544_rpi2.c
gcc -o cpushow2 pcd8544_rpi2.c PCD8544.c  -L/usr/local/lib -lwiringPi

echo pcd8544_test.c
gcc -o test pcd8544_test.c PCD8544.c  -L/usr/local/lib -lwiringPi

echo pcd8544_test2.c
gcc -o test2 pcd8544_test2.c PCD8544.c  -L/usr/local/lib -lwiringPi

