#!/bin/sh
##
## Daniel Boesswetter <boesswetter@peppermind.de>
##
## Fri Oct 25 11:03:05  2002
##

X=`mktemp`
getfacl $1 > $X
/usr/bin/strip --strip-all $1
setfacl -f - $1 < $X
rm -f $X

