#!/bin/sh
#
# makeundepend.sh
# copyright (c) 2001 Henk R. van de Zandschulp, David N. Jansen
# $Id: makeundepend.sh,v 1.2 2002/05/29 08:27:34 henkz Exp $
#

makefile=

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
     /bin/rm -f ${makefile}.bak
     mv ${makefile} ${makefile}.bak
     sed -e "/${marker}/q" < ${makefile}.bak > ${makefile} || {
       echo sed command failed ... bailing out
       exit 1
     }
 fi # [ ${foundit} ]

# EOF
