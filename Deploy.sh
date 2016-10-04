#!/bin/bash

if [ ! -f ./pam_ela.so ]; then
    echo "pam_ela.so not found!"
elif [ "$EUID" -ne 0 ]; then
    echo "Please run as root"
else
    if [ $# -eq 1 ] && [ $1 == "update" ]; then
	echo "# Pamela\n" >> /etc/pam.d/login
	echo "session    optionnal   pam_ela.so\n" >> /etc/pam.d/login
	echo "Updated conf /etc/pam.d/login"
    fi
    cp pam_ela.so /lib/*/security
    echo "pam_ela.so successfully copied to /lib/*/security"
fi
