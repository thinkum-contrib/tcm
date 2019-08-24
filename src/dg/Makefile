
include ../Config.tmpl

OBJECTS=addhandlecmd.o\
	alignnodeshapescmd.o\
	anchorpoint.o\
	anchorpointnode.o\
	arrowtextbox.o\
	blackdot.o\
	box.o\
	buffer.o\
	buildingblock.o\
	bullseye.o\
	c1edge.o\
	circle.o\
	comment.o\
	commentlink.o\
	copyshapescmd.o\
	createedgecmd.o\
	createnodecmd.o\
	cube.o\
	cutshapescmd.o\
	deleteallsubjectscmd.o\
	deletehandlecmd.o\
	deleteselectedsubjectscmd.o\
	deleteshapescmd.o\
	deletesubjectscmd.o\
	diagram.o\
	diagramchecks.o\
	diagramstubs.o\
	diagramviewer.o\
	diagramwindow.o\
	diamond.o\
	disk.o\
	doublebox.o\
        draghandlecmd.o\
        dragshapecmd.o\
        dragshapescmd.o\
        dragtextshapecmd.o\
	duplicateshapescmd.o\
	edge.o\
	ellipse.o\
	ellipsedbox.o\
	emptyedge.o\
	emptynode.o\
	findalltextscmd.o\
	findnexttextcmd.o\
	flasharrow.o\
	folder.o\
	genericedge.o\
	genericnode.o\
	graph.o\
	gshape.o\
	hexagon.o\
	horizontalbar.o\
	leftlinecircle.o\
	line.o\
	miniarrowellipse.o\
	minidiamond.o\
	miniellipse.o\
	minitriangle.o\
	moveallshapescmd.o\
	moveshapescmd.o\
	node.o\
	nodealign.o\
	nodeshape.o\
	note.o\
	notebox.o\
	pasteshapescmd.o\
	reindexcmd.o\
	replacealltextscmd.o\
	replacenexttextcmd.o\
	replacetextcmd.o\
	roundedbox.o\
	samesizecmd.o\
	selectallcmd.o\
	selectareacmd.o\
	shape.o\
	shapeview.o\
	shapes.o\
	sizeshapecmd.o\
	sizeshapecentercmd.o\
	sizeshapebordercmd.o\
	solidhorizontalbar.o\
	solidverticalbar.o\
	square.o\
	stickman.o\
	stringlistnode.o\
	stringlistnode2.o\
	stringlistedge.o\
	subfolder.o\
	subject.o\
	subjects.o\
	t1line.o\
	t2line.o\
	t4line.o\
	t4tlistline.o\
	textbox.o\
	textshape.o\
	textshapeeditor.o\
	thing.o\
	triangle.o\
	triplebox.o\
	updatecolorcmd.o\
	updatecurvecmd.o\
	updatefillcolorcmd.o\
	updatetextalignmentcmd.o\
	updatetextunderlinecmd.o\
	updatefontcmd.o\
	updatelinecolorcmd.o\
	updatelineendcmd.o\
	updatelinestylecmd.o\
	updatelinewidthcmd.o\
	updatetextcmd.o\
	updatetextcolorcmd.o\
	updatetypecmd.o\
	updatenodeshapetypecmd.o\
	verticalbar.o\
	whitedot.o\
	hyperedge.o\
	hypergraph.o\
	polygon.o\
	polypoint.o\
	shapetype.o

libdiagram.a: $(OBJECTS)
	$(AR) $@ $(OBJECTS)
	$(CHMODPLUSX) $@
	$(MV) $@ $(LIB_DIR)

libdiagram.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SHAREDFLAG) $(OBJECTS) -o $@
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(LIB_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
addhandlecmd.o: addhandlecmd.c line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h addhandlecmd.h \
  draghandlecmd.h dragshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h
alignnodeshapescmd.o: alignnodeshapescmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  alignnodeshapescmd.h moveshapescmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h
anchorpoint.o: anchorpoint.c anchorpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h
anchorpointnode.o: anchorpointnode.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h node.h subject.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hypergraph.h \
  anchorpointnode.h anchorpoint.h
arrowtextbox.o: arrowtextbox.c arrowtextbox.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  ../sd/tr/trviewer.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h
blackdot.o: blackdot.c blackdot.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
box.o: box.c box.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
buffer.o: buffer.c shapes.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h subjects.h \
  subject.h buffer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h
buildingblock.o: buildingblock.c buildingblock.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
bullseye.o: bullseye.c bullseye.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
c1edge.o: c1edge.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h c1edge.h edge.h \
  subject.h thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
circle.o: circle.c circle.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
comment.o: comment.c comment.h node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
commentlink.o: commentlink.c commentlink.h emptyedge.h edge.h subject.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
copyshapescmd.o: copyshapescmd.c subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h shapes.h subjects.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h buffer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h copyshapescmd.h
createedgecmd.o: createedgecmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h edge.h \
  subject.h line.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h createedgecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h nodeshape.h \
  shapetype.h polygon.h polypoint.h
createnodecmd.o: createnodecmd.c node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h nodeshape.h \
  gshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h createnodecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
cube.o: cube.c cube.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
cutshapescmd.o: cutshapescmd.c subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h cutshapescmd.h \
  copyshapescmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
deleteallsubjectscmd.o: deleteallsubjectscmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h subject.h \
  deleteallsubjectscmd.h deletesubjectscmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
deletehandlecmd.o: deletehandlecmd.c line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  deletehandlecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
deleteselectedsubjectscmd.o: deleteselectedsubjectscmd.c shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h subject.h \
  gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  deleteselectedsubjectscmd.h deletesubjectscmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
deleteshapescmd.o: deleteshapescmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h subject.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  deleteshapescmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
deletesubjectscmd.o: deletesubjectscmd.c shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h subject.h \
  gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  deletesubjectscmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
diagram.o: diagram.c graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/texteditdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/textviewdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/questiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/finddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/replacedialog.h node.h \
  subject.h thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hypergraph.h \
  edge.h line.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h buffer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h subjects.h \
  shapes.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h
diagramchecks.o: diagramchecks.c graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h node.h \
  subject.h hypergraph.h edge.h diagramchecks.h
diagramstubs.o: diagramstubs.c diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h nodeshape.h \
  gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/texteditdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/textviewdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineenddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/ntogglelistdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/promptdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/nodealignmentdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/nodeshapedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/scaledialog.h \
  diagramstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h
diagramviewer.o: diagramviewer.c alignnodeshapescmd.h moveshapescmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  createnodecmd.h createedgecmd.h cutshapescmd.h copyshapescmd.h \
  deleteshapescmd.h deleteallsubjectscmd.h deletesubjectscmd.h \
  deleteselectedsubjectscmd.h duplicateshapescmd.h pasteshapescmd.h \
  addhandlecmd.h draghandlecmd.h dragshapecmd.h deletehandlecmd.h \
  dragtextshapecmd.h dragshapescmd.h findnexttextcmd.h findalltextscmd.h \
  selectallcmd.h moveallshapescmd.h replacealltextscmd.h replacetextcmd.h \
  replacenexttextcmd.h samesizecmd.h selectareacmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  sizeshapecentercmd.h sizeshapecmd.h polypoint.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  sizeshapebordercmd.h updatetextcmd.h updatefontcmd.h \
  updatetextalignmentcmd.h updatelinewidthcmd.h updatelinestylecmd.h \
  updatelinecolorcmd.h updatecolorcmd.h updatefillcolorcmd.h \
  updatetextcolorcmd.h updatelineendcmd.h updatecurvecmd.h \
  updatetextunderlinecmd.h reindexcmd.h buffer.h textshapeeditor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/inlineeditor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/questiondialog.h line.h \
  gshape.h nodeshape.h shapetype.h polygon.h node.h subject.h \
  hypergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/key.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  diagramstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineenddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/ntogglelistdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/promptdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/nodealignmentdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/nodeshapedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h
diagramwindow.o: diagramwindow.c diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/printer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xgrafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/liteclue.h graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Curve.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleSolid.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleDashed.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LineStyleDotted.xbm
diamond.o: diamond.c diamond.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
disk.o: disk.c disk.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
doublebox.o: doublebox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  doublebox.h box.h nodeshape.h gshape.h textshape.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h
draghandlecmd.o: draghandlecmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h line.h gshape.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  shape.h thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h shapeview.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  draghandlecmd.h dragshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
dragshapecmd.o: dragshapecmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  dragshapecmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
dragshapescmd.o: dragshapescmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  dragshapescmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
dragtextshapecmd.o: dragtextshapecmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  dragtextshapecmd.h dragshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h
duplicateshapescmd.o: duplicateshapescmd.c subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  duplicateshapescmd.h pasteshapescmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
edge.o: edge.c /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h graph.h edge.h \
  subject.h thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
ellipse.o: ellipse.c ellipse.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
ellipsedbox.o: ellipsedbox.c ellipsedbox.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
ellipsis.o: ellipsis.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h ellipsis.h box.h \
  nodeshape.h gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h
emptyedge.o: emptyedge.c emptyedge.h edge.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h
emptynode.o: emptynode.c emptynode.h node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
findalltextscmd.o: findalltextscmd.c shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  findalltextscmd.h selectallcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h
findnexttextcmd.o: findnexttextcmd.c shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  findnexttextcmd.h findalltextscmd.h selectallcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h
flasharrow.o: flasharrow.c flasharrow.h line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h
folder.o: folder.c folder.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
genericedge.o: genericedge.c genericedge.h edge.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h
genericnode.o: genericnode.c genericnode.h node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
graph.o: graph.c graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h node.h subject.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hypergraph.h \
  edge.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h
gshape.o: gshape.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h node.h subject.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hypergraph.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  gshape.h textshape.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h
hexagon.o: hexagon.c hexagon.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
horizontalbar.o: horizontalbar.c horizontalbar.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
hyperedge.o: hyperedge.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h hypergraph.h \
  hyperedge.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h edge.h
hypergraph.o: hypergraph.c hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h node.h subject.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hyperedge.h \
  edge.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h
leftlinecircle.o: leftlinecircle.c leftlinecircle.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
line.o: line.c /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h line.h \
  gshape.h textshape.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h edge.h \
  subject.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
miniarrowellipse.o: miniarrowellipse.c miniarrowellipse.h nodeshape.h \
  gshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
minibox.o: minibox.c minibox.h box.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
minidiamond.o: minidiamond.c minidiamond.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
miniellipse.o: miniellipse.c miniellipse.h ellipse.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
minitriangle.o: minitriangle.c minitriangle.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
moveallshapescmd.o: moveallshapescmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  line.h gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  moveallshapescmd.h moveshapescmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
moveshapescmd.o: moveshapescmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  moveshapescmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
nodealign.o: nodealign.c nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h
node.o: node.c node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
nodeshape.o: nodeshape.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodeshape.h \
  gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h node.h \
  subject.h hypergraph.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
notebox.o: notebox.c notebox.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
note.o: note.c note.h comment.h node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h graph.h
pasteshapescmd.o: pasteshapescmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h gshape.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  shape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h subjects.h shapes.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h buffer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h pasteshapescmd.h
polygon.o: polygon.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h polygon.h \
  polypoint.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
polypoint.o: polypoint.c polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h
pullshapecmd.o: pullshapecmd.c nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h pullshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
reindexcmd.o: reindexcmd.c reindexcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramviewer.h \
  diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h node.h \
  subject.h hypergraph.h nodeshape.h gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h
replacealltextscmd.o: replacealltextscmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  replacealltextscmd.h replacetextcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
replacenexttextcmd.o: replacenexttextcmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  replacenexttextcmd.h replacetextcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
replacetextcmd.o: replacetextcmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  replacetextcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
roundedbox.o: roundedbox.c roundedbox.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
samesizecmd.o: samesizecmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h samesizecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
selectallcmd.o: selectallcmd.c diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  selectallcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
selectareacmd.o: selectareacmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h gshape.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  shape.h thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  selectareacmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
shape.o: shape.c /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h shapeview.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h shape.h
shapes.o: shapes.c shapes.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h
shapetype.o: shapetype.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
shapeview.o: shapeview.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h nodeshape.h \
  gshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h node.h subject.h \
  hypergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
sizeshapebordercmd.o: sizeshapebordercmd.c sizeshapebordercmd.h \
  sizeshapecmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  nodeshape.h gshape.h shapetype.h polygon.h
sizeshapecentercmd.o: sizeshapecentercmd.c sizeshapecentercmd.h \
  sizeshapecmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  nodeshape.h gshape.h shapetype.h polygon.h
sizeshapecmd.o: sizeshapecmd.c nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h sizeshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
solidhorizontalbar.o: solidhorizontalbar.c solidhorizontalbar.h \
  nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
solidverticalbar.o: solidverticalbar.c solidverticalbar.h nodeshape.h \
  gshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  textshape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
square.o: square.c square.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
stickman.o: stickman.c stickman.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
stringlistedge.o: stringlistedge.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/stringlist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h stringlistedge.h \
  edge.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
stringlistnode2.o: stringlistnode2.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/stringlist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  stringlistnode2.h stringlistnode.h node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hypergraph.h
stringlistnode.o: stringlistnode.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/stringlist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h stringlistnode.h \
  node.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h hypergraph.h
subfolder.o: subfolder.c subfolder.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
subject.o: subject.c subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h node.h \
  hypergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
subjects.o: subjects.c subjects.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
t1line.o: t1line.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h t1line.h line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
t2line.o: t2line.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h t2line.h t1line.h \
  line.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
t4line.o: t4line.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h t4line.h t2line.h \
  t1line.h line.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
t4tlistline.o: t4tlistline.c subject.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h t4tlistline.h \
  t4line.h t2line.h t1line.h line.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h
textbox.o: textbox.c textbox.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
textshape.o: textshape.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h textshape.h \
  shape.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  nodeshape.h gshape.h shapetype.h polygon.h polypoint.h subject.h
textshapeeditor.o: textshapeeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h textshapeeditor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/inlineeditor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h nodeshape.h \
  gshape.h textshape.h shape.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/texteditdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/textviewdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  updatetextcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
thing.o: thing.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
triangle.o: triangle.c triangle.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
triplebox.o: triplebox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  triplebox.h doublebox.h box.h nodeshape.h gshape.h textshape.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h
updatecolorcmd.o: updatecolorcmd.c nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatecolorcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatecurvecmd.o: updatecurvecmd.c line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatecurvecmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatefillcolorcmd.o: updatefillcolorcmd.c updatefillcolorcmd.h \
  updatecolorcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h nodeshape.h \
  gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapetype.h polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h
updatefontcmd.o: updatefontcmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  shapeview.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatefontcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatelinecolorcmd.o: updatelinecolorcmd.c updatelinecolorcmd.h \
  updatecolorcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
updatelineendcmd.o: updatelineendcmd.c line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatelineendcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatelinestylecmd.o: updatelinestylecmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatelinestylecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatelinewidthcmd.o: updatelinewidthcmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatelinewidthcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatenodeshapetypecmd.o: updatenodeshapetypecmd.c \
  updatenodeshapetypecmd.h updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  line.h gshape.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  nodeshape.h shapetype.h polygon.h polypoint.h
updatetextalignmentcmd.o: updatetextalignmentcmd.c gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatetextalignmentcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatetextcmd.o: updatetextcmd.c line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h shapeview.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h updatetextcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatetextcolorcmd.o: updatetextcolorcmd.c updatetextcolorcmd.h \
  updatecolorcmd.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
updatetextunderlinecmd.o: updatetextunderlinecmd.c textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  diagramviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  diagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatetextunderlinecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
updatetypecmd.o: updatetypecmd.c updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h shapeview.h \
  thing.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h diagramviewer.h \
  diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
verticalbar.o: verticalbar.c verticalbar.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
whitedot.o: whitedot.c whitedot.h nodeshape.h gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h shapetype.h \
  polygon.h polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
