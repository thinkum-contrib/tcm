include ../../Config.tmpl
 
GDOBJECTS = gdboundaryshape.o\
	gdcontrollershape.o\
	gddiagram.o\
	gdentityshape.o\
	gdgraph.o\
	gdviewer.o\
	gdupdatenodeshapetypecmd.o\
	gdwindow.o

tcmgd$(EXEEXTENSION):  $(GDOBJECTS) tcmgd.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(GDOBJECTS) \
	-ldiagram -leditor -lguix $(LIB_DIR)/libglobal.a \
	tcmgd.o -o $@ $(LDFLAGS) $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

libtcmgd.a: $(GDOBJECTS)
	$(AR) $@ $(GDOBJECTS)
	$(CHMODPLUSX) $@
	$(RANLIB) $@
	$(MV) $@ $(LIB_DIR)

tgd$(EXEEXTENSION):    $(GDOBJECTS) gdeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(GDOBJECTS) gdeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tcmd$(EXEEXTENSION):   tcmd.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) tcmd.o -o $@ \
	-I../dv -I../bv -I../tr -I../fv \
	$(LDFLAGS) $(LIB_DIR)/libtcmgd.a $(LIB_DIR)/libtcmtr.a \
        $(LIB_DIR)/libtcmdv.a $(LIB_DIR)/libtcmbv.a $(LIB_DIR)/libtcmfv.a \
	$(LIB_DIR)/libtcmpv.a \
	$(LIB_DIR)/libdiagram.a $(LIB_DIR)/libeditor.a \
        $(LIB_DIR)/libgui.a $(LIB_DIR)/libglobal.a $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)


clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
