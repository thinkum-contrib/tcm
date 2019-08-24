include ../Config.tmpl

tcmd$(EXEEXTENSION):
	( cd ./gd ; $(MAKE) libtcmgd.a)
	( cd ./tr ; $(MAKE) libtcmtr.a)
	( cd ./dv ; $(MAKE) libtcmdv.a)
	( cd ./bv ; $(MAKE) libtcmbv.a)
	( cd ./fv ; $(MAKE) libtcmfv.a)
	( cd ./pv ; $(MAKE) libtcmpv.a)
	( cd ./gd ; $(MAKE) $@)

tcmgd$(EXEEXTENSION) tgd$(EXEEXTENSION):   
	( cd ./gd ; $(MAKE) $@)

tcmtr$(EXEEXTENSION) tgtt$(EXEEXTENSION) tfrt$(EXEEXTENSION):   
	( cd ./tr ; $(MAKE) $@)

tcmdv$(EXEEXTENSION) terd$(EXEEXTENSION) tesd$(EXEEXTENSION) tcrd$(EXEEXTENSION) tssd$(EXEEXTENSION) tucd$(EXEEXTENSION) tcbd$(EXEEXTENSION) tsqd$(EXEEXTENSION):
	( cd ./dv ; $(MAKE) $@)

tcmbv$(EXEEXTENSION) tscd$(EXEEXTENSION) tstd$(EXEEXTENSION) trpg$(EXEEXTENSION) tpsd$(EXEEXTENSION) tatd$(EXEEXTENSION):   
	( cd ./bv ; $(MAKE) $@)

tcmfv$(EXEEXTENSION) tdfd$(EXEEXTENSION) tefd$(EXEEXTENSION) tsnd$(EXEEXTENSION):   
	( cd ./fv ; $(MAKE) $@)

tcmpv$(EXEEXTENSION) tdpd$(EXEEXTENSION) tcpd$(EXEEXTENSION):   
	( cd ./pv ; $(MAKE) $@)

tsqd$(EXEEXTENSION):
	@echo $@ not available yet

SUBDIRS = bv dv fv gd pv tr

clean depend undepend:
	for dir in $(SUBDIRS); do \
                (cd $${dir}; ${MAKE} $@); done

# DO NOT DELETE THIS LINE -- make depend depends on it.
