#!/bin/bash
user=$(whoami)
echo "$user"
if [ $user != "root" ]; then
	echo "not root"
fi
