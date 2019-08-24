include ../Config.tmpl

COLOR_FILE = colorrgb.txt
BANNER_FILE = banner.ps

CFLAGS += -DCONFIG_INSTALL=\"$(CONFIG_INSTALL)\"
CFLAGS += -DCOLOR_FILE=\"$(COLOR_FILE)\" -DBANNER_FILE=\"$(BANNER_FILE)\"

OBJECTS=application.o\
	bitmap.o\
	component.o\
	colorchooserdialog.o\
	dialog.o\
	dumpwidgettree.o\
	error.o\
	figgrafport.o\
	fileselectiondialog.o\
	fileutils.o\
	finddialog.o\
	fontchooserdialog.o\
	grafport.o\
	lineend.o\
	lineenddialog.o\
	linestyledialog.o\
	linestylesidedialog.o\
	linewidthdialog.o\
	linewidthsidedialog.o\
	liteclue.o\
        mainwindow.o\
	menu.o\
	menuitem.o\
	messagedialog.o\
	messagelogdialog.o\
	mousecursor.o\
	mstring.o\
	mwidget.o\
	nodealignmentdialog.o\
	nodeshapedialog.o\
	ntogglelistdialog.o\
	printerqueuedialog.o\
        promptdialog.o\
	psgrafport.o\
	questiondialog.o\
	replacedialog.o\
	scaledialog.o\
	selectiondialog.o\
	textalignmentdialog.o\
	texteditdialog.o\
	textfieldlistdialog.o\
	textviewdialog.o\
	togglelistdialog.o\
	xfont.o\
	xgrafport.o\
	xresources.o\
	temporalpropertydialog.o\
	modelcheckdialog.o

MAIN = main.o

libgui.a: $(OBJECTS) $(MAIN)
	$(AR) $@ $(OBJECTS) $(MAIN)
	$(CHMODPLUSX) $@
	$(MV) $@ $(LIB_DIR)

libguix.a: $(OBJECTS)
	ar cr $@ $(OBJECTS)
	$(CHMODPLUSX) $@
	$(MV) $@ $(LIB_DIR)

libgui.so: $(OBJECTS) $(MAIN)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SHAREDFLAG) $(OBJECTS) $(MAIN) -o $@
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(LIB_DIR)
 
clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
