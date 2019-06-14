#!/bin/sh
if [ "$1" == "Y" ]; then
	export PS1="\[\e]0;\u@\h: \w\a\]\[\033[01;33m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]$"
	echo "Change to Yellow"
	export PS1="\[\e]0;\u@\h: \w\a\]\[\033[01;33m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]$"
else
	echo "Change to Green"
	export PS1="\[\e]0;\u@\h: \w\a\]\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]$"
fi
