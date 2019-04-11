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
sounds = ["/mnt/sda1/arduino/www/animal_rights/female_french_idiocy.mp3", "/mnt/sda1/arduino/www/animal_rights/female_indian_tshirt2.mp3", "/mnt/sda1/arduino/www/animal_rights/female_us_gay.mp3", "/mnt/sda1/arduino/www/animal_rights/male_german_pandas.mp3", "/mnt/sda1/arduino/www/animal_rights/male_us_sexy3.mp3"]
#sounds = ["/root/animal_rights/female_french_idiocy.mp3", "/root/animal_rights/female_indian_tshirt2.mp3", "/root/animal_rights/female_us_gay.mp3", "/root/animal_rights/male_german_pandas.mp3", "/root/animal_rights/male_us_sexy3.mp3"]



mp3opt = "-a 5"

#soundPath = sys.argv[2]

if len(sys.argv) > 1:
	if sys.argv[1] == "-play":
		os.system("madplay " + mp3opt + " \"" + random.choice(sounds) + "\" &>/dev/null")
	elif sys.argv[1] == "-stop":
		pid = os.popen("pgrep madplay").read()
		os.kill(int(pid), signal.SIGKILL)
