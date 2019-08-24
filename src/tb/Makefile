include ../Config.tmpl

OBJECTS=addcolumnscmd.o\
	addrowscmd.o\
	appendtablecmd.o\
        cell.o\
	cellcolumn.o\
	cellrow.o\
        cellselection.o\
	celltext.o\
	celltextbuffer.o\
	celltexteditor.o\
	cellvector.o\
	copycelltextscmd.o\
	cutcelltextscmd.o\
	deleteallcellscmd.o\
	deletecellscmd.o\
	deletecolumnscmd.o\
	deleterowscmd.o\
	dragcelltextcmd.o\
	dragcmd.o\
	dragcolumncmd.o\
	dragcolumnlabelcmd.o\
	dragrowcmd.o\
	dragrowlabelcmd.o\
	findallcellscmd.o\
	findnextcellcmd.o\
	linepiece.o\
	matrix.o\
	matrixviewer.o\
	movetablecmd.o\
	pastecelltextscmd.o\
	purgecellscmd.o\
	replaceallcelltextscmd.o\
	replacecelltextcmd.o\
	replacenextcelltextcmd.o\
	rowcolumnlabel.o\
	selectallcellscmd.o\
	selectcellareacmd.o\
	simplelabel.o\
	sortcolumnscmd.o\
	sortrowscmd.o\
	table.o\
	tablestubs.o\
	tableviewer.o\
	tablewindow.o\
	updatelinestyletablecmd.o\
	updatelinetablecmd.o\
	updatelinewidthtablecmd.o\
	updatecolumnalignmentcmd.o\
	updaterowalignmentcmd.o\
	updatevectoralignmentcmd.o\
	updatecelltextcmd.o\
	updatecelltextunderlinecmd.o\
	updatecelltextfontcmd.o

libtable.a: $(OBJECTS)
	$(AR) $@ $(OBJECTS)
	$(CHMODPLUSX) $@
	$(MV) $@ $(LIB_DIR)

libtable.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SHAREDFLAG) $(OBJECTS) -o $@
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(LIB_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
