#
# A specfile for TCM (Toolkit for Conceptual Modeling).
# This is the dynamic motif specfile.
#
Summary: A suite of graphical editors for diagrams and tables.
Name: tcm-dynmotif
Version: 2.20
Release: 1
Copyright: GPL
Group: Development/Tools
Source: ftp://ftp.cs.utwente.nl/pub/tcm/tcm-%{version}.src.tar.gz
URL: http://www.cs.utwente.nl/~tcm
Packager: Frank Dehne <frank@cs.vu.nl> and Rick van Rein <hackers@home.nl>
Prefix: /opt/tcm
Provides: tcm
Patch0: tcm-2.20-dynamic.patch
%description
The Toolkit for Conceptual Modeling is a collection of software tools to 
present conceptual models of software systems in the form of diagrams, 
tables, trees, and the like. A conceptual model of a system is a structure 
used to represent the requirements or architecture of the system. TCM is 
meant to be used for specifying and maintaining requirements for desired 
systems, in which a number of techniques and heuristics for problem analysis, 
function refinement, behavior specification, and architecture specification 
are used. TCM takes the form of a suite of graphical editors that can be 
used in these design tasks. These editors can be categorized into:

* Generic editors, for generic diagrams, generic tables and generic trees.
* Structured Analysis (SA) editors, for entity-relationship diagrams, data 
  and event flow diagrams, state transition diagrams, function refinement 
  trees, transaction-use tables and function-entity type tables.
* Unified Modeling Language (UML) editors, for static structure diagrams, 
  use-case diagrams, activity diagrams, state charts, message sequence 
  diagrams, collaboration diagrams, component diagrams and deployment 
  diagrams.
%prep
%setup -n tcm-%{version}
for f in $(find . -name Makefile) ; do mv $f $f.or ; \
  sed -e '/DO NOT DELETE/q' < $f.or > $f ; rm $f.or ; done
%patch0 -p0
%build
make config 
make depend 
make execs
%install
make TCM_INSTALL_DIR="${RPM_BUILD_ROOT}/opt/tcm" install
[ ! -d ${RPM_BUILD_ROOT}/etc/profile.d ] \
       && mkdir -p ${RPM_BUILD_ROOT}/etc/profile.d
cat > ${RPM_BUILD_ROOT}/etc/profile.d/tcm.sh <<EOF
[ \${TCM_HOME} ] || {
  TCM_HOME=\`rpm  -q %{name} --queryformat %{INSTALLPREFIX}\`
  PATH="\${PATH}:\${TCM_HOME}/bin"
  LD_LIBRARY_PATH=\${LD_LIBRARY_PATH:+\${LD_LIBRARY_PATH}:}\${TCM_HOME}/lib
  MANPATH=\${MANPATH:-\`man -w\`}:\${TCM_HOME}/man
  export TCM_HOME LD_LIBRARY_PATH MANPATH PATH
}
EOF
cat > ${RPM_BUILD_ROOT}/etc/profile.d/tcm.csh <<EOF
setenv TCM_HOME \`rpm  -q %{name} --queryformat "%{INSTALLPREFIX}"\`
if ( \`echo \${PATH} | grep \${TCM_HOME}/bin\` ) then
      true
else
if ( ! \$?LD_LIBRARY_PATH ) then
       setenv LD_LIBRARY_PATH "\${TCM_HOME}/lib"
else
       setenv LD_LIBRARY_PATH "\${LD_LIBRARY_PATH}:\${TCM_HOME}/lib"
endif
if ( ! \$?MANPATH ) then
       setenv MANPATH "\`man -w\`"
endif
setenv MANPATH "\${MANPATH}:\${TCM_HOME}/man"
setenv PATH "\${PATH}:\${TCM_HOME}/bin"
EOF
chmod ugo+x ${RPM_BUILD_ROOT}/etc/profile.d/tcm.sh
chmod ugo+x ${RPM_BUILD_ROOT}/etc/profile.d/tcm.csh
%post
makewhatis $RPM_INSTALL_PREFIX/man
%preun
rm $RPM_INSTALL_PREFIX/man/whatis
%postun
if [ -x "$RPM_INSTALL_PREFIX/man" ]
then makewhatis $RPM_INSTALL_PREFIX/man
fi
%files
%doc CHANGELOG
%doc COPYING
%doc FILEMAP
%doc INSTALL_
%doc INSTALL.cygwin
%doc README
%doc README.cygwin
%dir /opt/tcm
%dir /opt/tcm/bin
/opt/tcm/bin/psf
/opt/tcm/bin/tatd
/opt/tcm/bin/tcbd
/opt/tcm/bin/tcm
/opt/tcm/bin/tcmd
/opt/tcm/bin/tcmt
/opt/tcm/bin/tcpd
/opt/tcm/bin/tcrd
/opt/tcm/bin/tdfd
/opt/tcm/bin/tdpd
/opt/tcm/bin/tefd
/opt/tcm/bin/terd
/opt/tcm/bin/tesd
/opt/tcm/bin/text2ps
/opt/tcm/bin/tfet
/opt/tcm/bin/tfrt
/opt/tcm/bin/tgd
/opt/tcm/bin/tgt
/opt/tcm/bin/tgtt
/opt/tcm/bin/tpsd
/opt/tcm/bin/trpg
/opt/tcm/bin/tscd
/opt/tcm/bin/tsnd
/opt/tcm/bin/tssd
/opt/tcm/bin/tsqd
/opt/tcm/bin/tstd
/opt/tcm/bin/ttdt
/opt/tcm/bin/ttut
/opt/tcm/bin/tucd
%dir /opt/tcm/doc
%doc /opt/tcm/doc/usersguide.html
%doc /opt/tcm/doc/usersguide-%{version}.ps.gz
%doc /opt/tcm/doc/usersguide
%dir /opt/tcm/doc/wishlist
%doc /opt/tcm/doc/wishlist/WishList.html
%doc /opt/tcm/doc/wishlist/FutureDevelopments.html
%dir /opt/tcm/lib
/opt/tcm/lib/TCM
/opt/tcm/lib/banner.ps
%dir /opt/tcm/lib/help
/opt/tcm/lib/help/DiagramEditCommands
/opt/tcm/lib/help/DiagramMainWindow
/opt/tcm/lib/help/DiagramMiscCommands
/opt/tcm/lib/help/DiagramMouseCommands
/opt/tcm/lib/help/FileMenuCommands
/opt/tcm/lib/help/GettingStarted
/opt/tcm/lib/help/PrintPageCommands
/opt/tcm/lib/help/StartingEditors
/opt/tcm/lib/help/TATDIntro
/opt/tcm/lib/help/TCBDIntro
/opt/tcm/lib/help/TCPDIntro
/opt/tcm/lib/help/TCRDIntro
/opt/tcm/lib/help/TDFDIntro
/opt/tcm/lib/help/TDPDIntro
/opt/tcm/lib/help/TEFDIntro
/opt/tcm/lib/help/TERDIntro
/opt/tcm/lib/help/TESDIntro
/opt/tcm/lib/help/TFETIntro
/opt/tcm/lib/help/TFRTIntro
/opt/tcm/lib/help/TGDIntro
/opt/tcm/lib/help/TGTIntro
/opt/tcm/lib/help/TGTTIntro
/opt/tcm/lib/help/TPSDIntro
/opt/tcm/lib/help/TRPGIntro
/opt/tcm/lib/help/TSCDIntro
/opt/tcm/lib/help/TSNDIntro
/opt/tcm/lib/help/TSSDIntro
/opt/tcm/lib/help/TSTDIntro
/opt/tcm/lib/help/TTDTIntro
/opt/tcm/lib/help/TTUTIntro
/opt/tcm/lib/help/TUCDIntro
/opt/tcm/lib/help/TableEditCommands
/opt/tcm/lib/help/TableMainWindow
/opt/tcm/lib/help/TableMiscCommands
/opt/tcm/lib/help/TableMouseCommands
/opt/tcm/lib/help/Version
/opt/tcm/lib/help/Welcome
/opt/tcm/lib/colorrgb.txt
%config /opt/tcm/lib/tcm.conf
/etc/profile.d/tcm.sh
/etc/profile.d/tcm.csh
%docdir /opt/tcm/man
%dir /opt/tcm/man
%dir /opt/tcm/man/man1
%doc /opt/tcm/man/man1/psf.1
%doc /opt/tcm/man/man1/tatd.1
%doc /opt/tcm/man/man1/tcbd.1
%doc /opt/tcm/man/man1/tcm.1
%doc /opt/tcm/man/man1/tcmd.1
%doc /opt/tcm/man/man1/tcmdv.1
%doc /opt/tcm/man/man1/tcmt.1
%doc /opt/tcm/man/man1/tcpd.1
%doc /opt/tcm/man/man1/tcrd.1
%doc /opt/tcm/man/man1/tdfd.1
%doc /opt/tcm/man/man1/tdpd.1
%doc /opt/tcm/man/man1/tefd.1
%doc /opt/tcm/man/man1/terd.1
%doc /opt/tcm/man/man1/tesd.1
%doc /opt/tcm/man/man1/text2ps.1
%doc /opt/tcm/man/man1/tfet.1
%doc /opt/tcm/man/man1/tfrt.1
%doc /opt/tcm/man/man1/tgd.1
%doc /opt/tcm/man/man1/tgt.1
%doc /opt/tcm/man/man1/tgtt.1
%doc /opt/tcm/man/man1/tpsd.1
%doc /opt/tcm/man/man1/trpg.1
%doc /opt/tcm/man/man1/tscd.1
%doc /opt/tcm/man/man1/tsnd.1
%doc /opt/tcm/man/man1/tssd.1
%doc /opt/tcm/man/man1/tstd.1
%doc /opt/tcm/man/man1/ttdt.1
%doc /opt/tcm/man/man1/ttut.1
%doc /opt/tcm/man/man1/tucd.1
