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
application.o: application.c application.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h mainwindow.h \
  mousecursor.h messagelogdialog.h textviewdialog.h dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/printeroptions.h \
  xresources.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h color.h
bitmap.o: bitmap.c bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Default.xbm
colorchooserdialog.o: colorchooserdialog.c colorchooserdialog.h \
  selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h application.h \
  mstring.h
component.o: component.c component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
dialog.o: dialog.c dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
dumpwidgettree.o: dumpwidgettree.c dumpwidgettree.h
error.o: error.c /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  application.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  messagelogdialog.h textviewdialog.h dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h
figgrafport.o: figgrafport.c figgrafport.h grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h application.h \
  mwidget.h component.h
fileselectiondialog.o: fileselectiondialog.c fileselectiondialog.h \
  selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h application.h \
  mstring.h menu.h menuitem.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h
fileutils.o: fileutils.c fileutils.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h questiondialog.h \
  messagedialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/printeroptions.h \
  application.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
finddialog.o: finddialog.c finddialog.h selectiondialog.h dialog.h \
  mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
fontchooserdialog.o: fontchooserdialog.c fontchooserdialog.h \
  ntogglelistdialog.h promptdialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h mstring.h \
  xfont.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h
grafport.o: grafport.c grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h application.h \
  mwidget.h component.h
lineend.o: lineend.c lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h color.h
lineenddialog.o: lineenddialog.c lineenddialog.h ntogglelistdialog.h \
  promptdialog.h selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndEmpty.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginFilledArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginDoubleOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginDoubleFilledArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginWhiteCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginBlackCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginWhiteDiamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginBlackDiamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginWhiteTriangle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineBeginBlackTriangle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndFilledArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndDoubleOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndDoubleFilledArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndWhiteCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndBlackCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndWhiteDiamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndBlackDiamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndWhiteTriangle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineEndBlackTriangle.xbm
linestyledialog.o: linestyledialog.c linestyledialog.h \
  ntogglelistdialog.h promptdialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleSolid.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleDashed.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleDotted.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleWideDotted.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleDual.xbm
linestylesidedialog.o: linestylesidedialog.c linestylesidedialog.h \
  linestyledialog.h ntogglelistdialog.h promptdialog.h selectiondialog.h \
  dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideTop.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideBottom.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideLeft.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideRight.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideAll.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideSurrounding.xbm
linewidthdialog.o: linewidthdialog.c linewidthdialog.h \
  ntogglelistdialog.h promptdialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth1.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth2.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth3.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth4.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth5.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth6.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth7.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth8.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineWidth9.xbm
linewidthsidedialog.o: linewidthsidedialog.c linewidthsidedialog.h \
  linewidthdialog.h ntogglelistdialog.h promptdialog.h selectiondialog.h \
  dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideTop.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideBottom.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideLeft.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideRight.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideAll.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SideSurrounding.xbm
liteclue.o: liteclue.c litecluep.h
main.o: main.c application.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
mainwindow.o: mainwindow.c application.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h mainwindow.h \
  mousecursor.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h \
  dumpwidgettree.h
menu.o: menu.c menu.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h menuitem.h \
  bitmap.h mstring.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
menuitem.o: menuitem.c menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h bitmap.h
messagedialog.o: messagedialog.c messagedialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
messagelogdialog.o: messagelogdialog.c messagelogdialog.h \
  textviewdialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h
modelcheckdialog.o: modelcheckdialog.c modelcheckdialog.h \
  selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
mousecursor.o: mousecursor.c mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
mstring.o: mstring.c mstring.h
mwidget.o: mwidget.c component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h mwidget.h \
  liteclue.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
nodealignmentdialog.o: nodealignmentdialog.c nodealignmentdialog.h \
  ntogglelistdialog.h promptdialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AlignTop.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AlignBottom.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AlignLeft.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AlignRight.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AlignHorizontal.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AlignVertical.xbm
nodeshapedialog.o: nodeshapedialog.c nodeshapedialog.h \
  ntogglelistdialog.h promptdialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Square.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Circle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StickMan.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Ellipse.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Triangle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Diamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Hexagon.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/HorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/VerticalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SolidHorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SolidVerticalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BlackDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BullsEye.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/RoundedBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EllipsedBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Cube.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Folder.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Disk.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SubFolder.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BuildingBlock.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/GDBoundaryShape.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/GDControllerShape.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/GDEntityShape.xbm
ntogglelistdialog.o: ntogglelistdialog.c ntogglelistdialog.h \
  promptdialog.h selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h mstring.h \
  bitmap.h
printerqueuedialog.o: printerqueuedialog.c printerqueuedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/printeroptions.h \
  mainwindow.h mousecursor.h promptdialog.h messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/link.h mstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h
promptdialog.o: promptdialog.c promptdialog.h selectiondialog.h dialog.h \
  mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
psgrafport.o: psgrafport.c psgrafport.h grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h application.h \
  mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h
questiondialog.o: questiondialog.c questiondialog.h messagedialog.h \
  dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
replacedialog.o: replacedialog.c replacedialog.h finddialog.h \
  selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
scaledialog.o: scaledialog.c scaledialog.h messagedialog.h dialog.h \
  mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
selectiondialog.o: selectiondialog.c selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
temporalpropertydialog.o: temporalpropertydialog.c \
  temporalpropertydialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
textalignmentdialog.o: textalignmentdialog.c textalignmentdialog.h \
  ntogglelistdialog.h promptdialog.h selectiondialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TextAlignmentCenter.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TextAlignmentLeft.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TextAlignmentRight.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TextAlignmentVCenter.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TextAlignmentVTop.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TextAlignmentVBottom.xbm
texteditdialog.o: texteditdialog.c texteditdialog.h textviewdialog.h \
  dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  fileselectiondialog.h selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h replacedialog.h \
  finddialog.h menu.h menuitem.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h
textfieldlistdialog.o: textfieldlistdialog.c textfieldlistdialog.h \
  dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h mstring.h
textviewdialog.o: textviewdialog.c textviewdialog.h dialog.h mwidget.h \
  component.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h fileutils.h \
  fileselectiondialog.h selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h finddialog.h \
  replacedialog.h messagedialog.h mstring.h menu.h menuitem.h bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/printeroptions.h \
  application.h
togglelistdialog.o: togglelistdialog.c togglelistdialog.h promptdialog.h \
  selectiondialog.h dialog.h mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h mstring.h \
  bitmap.h
xfont.o: xfont.c xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h application.h \
  mwidget.h component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h
xgrafport.o: xgrafport.c xgrafport.h grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
xresources.o: xresources.c xresources.h
