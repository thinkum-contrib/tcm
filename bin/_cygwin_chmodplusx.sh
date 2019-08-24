#!/bin/sh
##
## Daniel Boesswetter <boesswetter@peppermind.de>
##
## Fri Oct 25 13:11:40  2002
##

if [ -e "$1.exe" ]; then
	n=$1.exe
else
	n=$1
fi

setfacl.exe -m user::rwx $n

