#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "Please run as root"
elif [ $# -eq 1 ]; then
  dd if=/dev/zero of=$1.img bs=4k count=60000
  mkfs.ext4 $1.img
  echo "Image $1.img created"
  mv $1.img /root/cntr
  echo "Image $1.img moved to /root/cntr"
  rm /root/cntr/.aesIV$1
  rm /root/cntr/.aeskey$1
  rm /root/cntr/.containerSize$1
fi
