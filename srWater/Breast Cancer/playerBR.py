#!/usr/bin/python

# Arduino Meets Linux:
# The User's Guide to Arduino Yun Development
# Copyright (c) 2015, Bob Hammell.
#
# Disclaimer:
# This code is provided by ArduinoMeetsLinux.com on an "AS IS"
# basis. ArduinoMeetsLinux.com makes no warranties, express or
# implied, regarding use of the code alone or in combination with
# your projects.
#
# In no event shall ArduinoMeetsLinux.com be liable for any special,
# indirect, incidental, or consequential damages (including, but not
# limited to, loss of data and damage to systems) arising in any way
# out of the use, reproduction, modification and/or distribution of
# this code.
import os, signal, sys
import random
#sounds = ["/root/breast_cancer/female_brit_kickbutt1.mp3", "/root/breast_cancer/female_uk_survivor1.mp3", "/root/breast_cancer/female_us_cancer1.mp3", "/root/breast_cancer/male_brit_twitter.mp3", "/root/breast_cancer/male_us_feminine_side.mp3"]
sounds = ["/mnt/sda1/arduino/www/breast_cancer/female_brit_kickbutt1.mp3", "/mnt/sda1/arduino/www/breast_cancer/female_uk_survivor1.mp3", "/mnt/sda1/arduino/www/breast_cancer/female_us_cancer1.mp3", "/mnt/sda1/arduino/www/breast_cancer/male_brit_twitter.mp3", "/mnt/sda1/arduino/www/breast_cancer/male_us_feminine_side.mp3"]



mp3opt = "-a 5"

#soundPath = sys.argv[2]

if len(sys.argv) > 1:
	if sys.argv[1] == "-play":
		os.system("madplay " + mp3opt + " \"" + random.choice(sounds) + "\" &>/dev/null")
	elif sys.argv[1] == "-stop":
		pid = os.popen("pgrep madplay").read()
		os.kill(int(pid), signal.SIGKILL)
