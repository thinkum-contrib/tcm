#!/bin/sh
#
# makedepend_sh
# copyright (c) 2000 J. Alan Eldridge
# $Id: makedepend.sh,v 1.2 2002/05/29 08:27:34 henkz Exp $
#

makefile=
makedepend="gcc -MM"

[ -f makefile ] && makefile=makefile
[ -f Makefile ] && makefile=Makefile
[ -f GNUMakefile ] && makefile=GNUMakefile
[ ${makefile} ] || {
     echo cannot find a makefile ... bailing out
     exit 1
}

marker='# DO NOT DELETE THIS LINE -- make depend depends on it.'


grep "${marker}" ${makefile} >/dev/null 2>&1
[ $? -eq 0 ] && foundit=y || foundit=
if [ ${foundit} ] ; then
     rm -f ${makefile}.or
     mv ${makefile} ${makefile}.or
     sed -e "/${marker}/q" < ${makefile}.or > ${makefile} || {
       echo sed command failed ... bailing out
       exit 1
     }
     rm -f ${makefile}.or
 else
     echo "${marker}" >> ${makefile}; echo >> ${makefile}
 fi # [ ${foundit} ]

 ${makedepend} ${1:+"$@"} >> ${makefile}

 #
 # EOF
 ##





