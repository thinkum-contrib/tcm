include ../Config.tmpl

TDOBJECTS =     tdtable.o tdwindow.o tdviewer.o
 
TUOBJECTS =     tutable.o tuwindow.o tuviewer.o
 
FEOBJECTS =     fetable.o fewindow.o feviewer.o
 
TBOBJECTS = $(TDOBJECTS) $(TUOBJECTS) $(FEOBJECTS)

tcmt$(EXEEXTENSION):   $(TBOBJECTS) tcmt.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TBOBJECTS) tcmt.o \
	$(LIB_DIR)/libtable.a $(LIB_DIR)/libeditor.a $(LIB_DIR)/libgui.a \
         -o $@ $(LDFLAGS) $(LIB_DIR)/libglobal.a $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tgt$(EXEEXTENSION):    $(OBJECTS) tableeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) tableeditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

ttdt$(EXEEXTENSION):   $(TDOBJECTS) tdeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TDOBJECTS) tdeditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

ttut$(EXEEXTENSION):   $(TUOBJECTS) tueditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TUOBJECTS) tueditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tfet$(EXEEXTENSION):   $(FEOBJECTS) feeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(FEOBJECTS) feeditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
feeditor.o: feeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h fewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h
fetable.o: fetable.c fewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h feviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h fetable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrix.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellvector.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellcolumn.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cell.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/celltext.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/simplelabel.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h
feviewer.o: feviewer.c feviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellcolumn.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellvector.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
fewindow.o: fewindow.c fewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h feviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h fetable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrix.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h
tableeditor.o: tableeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h
tcmt.o: tcmt.c /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h fewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h tuwindow.h \
  tdwindow.h
tdeditor.o: tdeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h tdwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h
tdtable.o: tdtable.c tdwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h tdviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h tdtable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrix.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellvector.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellcolumn.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cell.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/celltext.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/simplelabel.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h
tdviewer.o: tdviewer.c tdviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h
tdwindow.o: tdwindow.c tdwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h tdviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h tdtable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrix.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h
tueditor.o: tueditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h tuwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h
tutable.o: tutable.c tuwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h tuviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h tutable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrix.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellvector.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellcolumn.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cell.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/celltext.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/simplelabel.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h
tuviewer.o: tuviewer.c tuviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cell.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/celltext.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/simplelabel.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellcolumn.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellvector.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
tuwindow.o: tuwindow.c tuwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tablewindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h tuviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrixviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/tableviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/side.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/linepiece.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/cellselection.h tutable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/matrix.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/tb/table.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h
