
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
