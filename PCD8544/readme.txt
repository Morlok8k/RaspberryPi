1: Install wiringPi
	cd  /home
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	sudo  ./build

2: Compile files
	cd  /path/to/files/PCD8544
	sudo  ./compile

3: Run the program
	sudo  ./cpushow

NOTE：
Due to the contrast of different LCD's may vary, if you find the content displayed too dark  or too light, you should to modify the contrast variables of pcd8544_rpi.c, and then recompile and run to see the effect of changes !
	nano  pcd8544_rpi.c
Modify the line 52, int contrast = 45;  
45 is the default contrast, if the character LCD display is too light, increase this value; decrease if the LCD display is too dark. Recommended stepping value is 5. After the changes are complete, re-compile the code, and then run.

