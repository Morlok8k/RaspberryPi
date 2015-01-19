/*
=================================================================================
 Name        : pcd8544_rpi2.c
 Version     : 0.1

 Copyright (C) 2015 by Morlok8k

 Description :
     An updated example program that correctly shows uptime, Load averages, RAM, and the current time.

The original "pcd8544_rpi2.c" was lacking in the displayed information:
* uptime was shown in just minutes.  how long is 3452 minutes? sure, i could calculate it, but showing days, hours, minutes, seconds is better.
* The CPU% was incorrect (It took the load averages and attempted to make it a %.  I myself got 600% CPU usage to show up.)
* It just showed the free ram.  This has been changed to used/total.
* added the current time to the empty line at the bottom.

	 Makes use of WiringPI-library of Gordon Henderson (https://projects.drogon.net/raspberry-pi/wiringpi/)

================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
 */
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "PCD8544.h"
#include <time.h>

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;
  
// lcd contrast 
//may be need modify to fit your screen!  normal: 30- 90 ,default is:45 !!!maybe modify this value!
int contrast = 60;  
  
int main (void)
{
  // print infos
  printf("Raspberry Pi PCD8544 sysinfo display\n");
  printf("========================================\n");
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }
  
  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();
  
  // show logo
  LCDshowLogo();
  
  delay(2000);
  
  for (;;)
  {
	  // clear lcd
	  LCDclear();
	  
	  // get system usage / info
	  struct sysinfo sys_info;
	  if(sysinfo(&sys_info) != 0)
	  {
		printf("sysinfo-Error\n");
	  }
	  

	  // uptime
	  //provides an output that looks like: 5d 23h35m21s (or 23d 2h04m02s)
	  unsigned long uptime = sys_info.uptime;
	  char uptimeInfo[15];
	
	  /* Conversion constants.  */
	  const long minute = 60;
	  const long hour = minute * 60;
	  const long day = hour * 24;
	  /* Produce output.  */
	  sprintf (uptimeInfo, "%ldd %ld:%02ld:%02ld\n", uptime / day, 
	  (uptime % day) / hour, (uptime % hour) / minute, uptime % minute);


	  // cpu info
	  // Provides a standard 1, 5, 15 minute load average output. (0.16 0.88 1.16)
	  char cpuInfo[15]; 
	  float avgCpuLoad1 = sys_info.loads[0] / (float)(1 << SI_LOAD_SHIFT);
	  float avgCpuLoad5 = sys_info.loads[1] / (float)(1 << SI_LOAD_SHIFT);
	  float avgCpuLoad15 = sys_info.loads[2] / (float)(1 << SI_LOAD_SHIFT);
	  sprintf(cpuInfo, "%.2f %.2f %.2f\n", avgCpuLoad1, avgCpuLoad5, avgCpuLoad15);

	  
	  // ram info
	  // used ram / total ram available - (289 / 450MB)
	  char ramInfo[15]; 
	  unsigned long freeRam = sys_info.freeram / 1024 / 1024;
	  unsigned long totalRam = sys_info.totalram / 1024 / 1024;
	  sprintf(ramInfo, "%ld / %ldMB", totalRam - freeRam, totalRam);
	  
	  
	  //time info
	  // Jan 18 08:39PM
	  time_t rawtime;
	  struct tm * timeinfo;
	  char timeCurrent[15];
	  time (&rawtime);
	  timeinfo = localtime (&rawtime);
	  strftime (timeCurrent,15,"%b %e %I:%M%p",timeinfo);
	  
	  
	  // build screen
	  LCDdrawstring(0, 0, "Raspberry Pi:");
	  LCDdrawline(0, 10, 83, 10, BLACK);
	  LCDdrawstring(0, 12, uptimeInfo);
	  LCDdrawstring(0, 20, cpuInfo);
	  LCDdrawstring(0, 28, ramInfo);
	  LCDdrawline(0, 36, 83, 36, BLACK);
	  LCDdrawstring(0, 38, timeCurrent);
	  LCDdisplay();
	  
	  delay(1000);
  }
  
    //for (;;){
  //  printf("LED On\n");
  //  digitalWrite(pin, 1);
  //  delay(250);
  //  printf("LED Off\n");
  //  digitalWrite(pin, 0);
  //  delay(250);
  //}

  return 0;
}
