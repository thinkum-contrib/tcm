#!/bin/sh
##
## Daniel Boesswetter <boesswetter@peppermind.de>
##
## Fri Oct 25 11:03:05  2002
##
## wrapper for "ln -s" that also copies the acl (non-default on cygwin)
##


c="ln -s $1 $2"
echo $c
$c
getfacl $1 | setfacl -f - $2

