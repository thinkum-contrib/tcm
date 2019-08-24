////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
//
// TCM is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// TCM is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "drawingarea.h"
#include "viewer.h"
#include "xgrafport.h"
#include "messagedialog.h"
#include "command.h"
#include "menu.h"
#include "mstring.h"
#include "key.h"
#include "config.h"
#include <stdlib.h>
#include <Xm/XmAll.h>
#include <X11/keysym.h>

// the standard translations don't work, actually.
// These are borrowed from an example program in the Motif distribution.
char DrawingArea::drawTranslations[] = "#replace\n\
~s ~m ~a <Key>Return:DrawingAreaInput() ManagerParentActivate()\n\
<Key>Return:DrawingAreaInput() ManagerGadgetSelect()\n\
<Key>osfActivate:DrawingAreaInput() ManagerParentActivate()\n\
<Key>osfCancel:DrawingAreaInput() ManagerParentCancel()\n\
<Key>osfHelp:DrawingAreaInput() ManagerGadgetHelp()\n\
<Key>space:DrawingAreaInput() ManagerGadgetSelect()\n\
<Key>osfSelect:DrawingAreaInput() ManagerGadgetSelect()\n\
<Key>osfBeginLine:DrawingAreaInput()\n\
<Key>osfEndLine:DrawingAreaInput()\n\
<KeyDown>:DrawingAreaInput() ManagerGadgetKeyInput()\n\
<KeyUp>:DrawingAreaInput()\n\
<Enter>:DrawingAreaInput()\n\
<Leave>:DrawingAreaInput()\n\
<BtnMotion>:DrawingAreaInput() ManagerGadgetButtonMotion()\n\
<Motion>:DrawingAreaInput() ManagerGadgetButtonMotion()\n\
<Btn1Down>:DrawingAreaInput() ManagerGadgetArm()\n\
<Btn1Up>:DrawingAreaInput() ManagerGadgetActivate()\n\
<Btn2Down>:DrawingAreaInput() ManagerGadgetDrag()\n\
<BtnDown>:DrawingAreaInput()\n\
<BtnUp>:DrawingAreaInput()";

DrawingArea::DrawingArea(Config *config, Widget parent, const char *n, 
		DrawWindow *w): MWidget(n) {
	drawwindow = w;
	beenDragging = False;
	x = 0; y = 0;
	viewer = 0;
	grafport = 0;
	width = min(drawwindow->initDrawingWidth, drawwindow->maxDrawingWidth);
	height = min(drawwindow->initDrawingHeight, 
			drawwindow->maxDrawingHeight);
	maxWidth = drawwindow->maxDrawingWidth;
	maxHeight = drawwindow->maxDrawingHeight;
	// create a drawing area widget
	SetWidget(XtVaCreateWidget(
		GetName()->getstr(), xmDrawingAreaWidgetClass, parent,
		XmNtranslations, XtParseTranslationTable(drawTranslations),
		XmNheight, height,
		XmNwidth, width,
		XmNresizePolicy, XmNONE, // remain this a fixed size
		0));
	// set up destruction handler.
	InstallDestroyHandler();
	// convert drawing area back to pixels to get its width and height
	XtVaSetValues(GetWidget(), XmNunitType, XmPIXELS, 0);
	XtAddCallback(GetWidget(), XmNexposeCallback, DrawCB, this);
	XtAddCallback(GetWidget(), XmNresizeCallback, DrawCB, this);
	XtAddCallback(GetWidget(), XmNinputCallback, DrawCB, this);
	// create popup menu.
	CreatePopupMenu(drawwindow->GetTool());
	XtManageChild(GetWidget());
	Display *display = GetDisplay();
	Window window = GetWindow();
	if (!check(display) || !check(window))
		return;
	// create new x grafport object.
	if (check(config)) {
		grafport = new XGrafport(display, window, width, height);
		grafport->SetBackgroundColor(config->GetDrawingBackground());
		grafport->SetForegroundColor(config->GetDrawingForeground());
		grafport->ClearArea(0,0,width,height);
	}
}

void DrawingArea::SetViewer(Viewer *v) {
	viewer = v;
	if (grafport)
		grafport->SetFont(viewer->GetDefaultFont());
}

Pixel DrawingArea::GetBackgroundColor() {
	Pixel p;
	XtVaGetValues(GetWidget(), XmNbackground, &p, 0);
	return p;
}

Pixel DrawingArea::GetForegroundColor() {
	Pixel p;
	XtVaGetValues(GetWidget(), XmNforeground, &p, 0);
	return p;
}

void DrawingArea::UpdateSize(int w, int h) {
	w = min(w, maxWidth);
	h = min(h, maxHeight);
	XtVaSetValues(GetWidget(), XmNheight, h, XmNwidth, w, 0);
	height = h;
	width = w;
}

void DrawingArea::FitDocument(int wd, int ht) {
	if (wd > maxWidth || ht > maxHeight) { 
		(new MessageDialog(GetWidget(), MessageDialog::WARNING))->
		 Show("Warning", 
			"The drawing area has reached its maximum size\n"
			"Can not display the entire document");
	}
	wd = min(wd, maxWidth);
	ht = min(ht, maxHeight);
	if (ht > height || wd > width) {
		wd = max(wd, width);
		ht = max(ht, height);
		if (check(grafport))
			grafport->UpdateSize(wd, ht);
		UpdateSize(wd, ht);
		if (viewer)
			viewer->Redraw();
	}
}

void DrawingArea::FitDocument() {
	if (!check(viewer))
		return;
	Point p1, p2;
	viewer->CalcSizeElements(p1, p2);
	int wd = int(0.5 + 10.0 + grafport->Zoom(p2.x));
	int ht = int(0.5 + 10.0 + grafport->Zoom(p2.y));
	FitDocument(wd, ht);
}
 
void DrawingArea::CreatePopupMenu(int tool) {
	popupMenu = new Menu(GetWidget(), Menu::POPUP, "Edit", 0, 
				drawwindow->GetPopupEditItems());
//	if (Toolkit::EditorWithoutDuplicates(tool)) {
//		// make "Duplicate" command insensitive.
//		Widget w1 = popupMenu->GetMenuItem("Duplicate");
//		if (w1)
//			XtVaSetValues(w1, XmNsensitive, False, 0);
//	}
}

void DrawingArea::DrawCB(Widget, XtPointer clientData, XtPointer callData) {
	DrawingArea *da = (DrawingArea *)clientData;
	da->Dispatch(callData);
}

void DrawingArea::Dispatch (XtPointer callData) {
	XmDrawingAreaCallbackStruct *dacs = 
			(XmDrawingAreaCallbackStruct *)callData;
	static int dragButton = 0;
	switch (dacs->reason) {
	case XmCR_EXPOSE:
	case XmCR_RESIZE:
		Redraw(dacs->event);
		break;
	case XmCR_INPUT: {
		if (!check(viewer))
			return;
		bool pasting = viewer->IsPasting();
		bool zigZag = viewer->IsZigZag();
		switch (dacs->event->type) {
		case ButtonPress: {
			XButtonEvent *event = (XButtonEvent *)dacs->event;
			x = event->x;
			y = event->y;
			if (event->button == Button3 && 
			    !(zigZag || pasting || beenDragging))
				PopupMenu(dacs->event); 
			beenDragging = False;
			break;
		}
		case ButtonRelease: {
			XButtonEvent *event = (XButtonEvent *)dacs->event;
			Command *lastcmd = viewer->GetLastCmd();
			x = event->x;
			y = event->y;
			if (zigZag || pasting) {
				if (!lastcmd) 
					return;
				if ((zigZag && (event->button != Button2) &&
						!(event->state & ShiftMask)) || 
				     pasting && (event->button != Button1)) {
					lastcmd->SayAborted();
					lastcmd->Abort();
				}
				else {
					lastcmd->TrackMouse(Command::TRACK_UP, 
					     &anchorPoint, &previousPoint, 
					     &nextPoint);
					anchorPoint = nextPoint;
				}
			}
			else if (beenDragging) {
				if (!lastcmd) {
					beenDragging = False;
					dragButton = 0;
					return;
				}
				lastcmd->TrackMouse(Command::TRACK_RELEASE,
					  &anchorPoint, &previousPoint, 
					  &nextPoint);
				if ((int)event->button == dragButton)
					viewer->ExecuteCommand();
			}
			else if (dragButton == 0) {
				if (event->button == Button1) {
					if (event->state & ShiftMask)
						viewer->Adjust(x, y);
					else
						viewer->Select(x, y);
				}
				else if (event->button == Button2)
					viewer->Adjust(x, y);
			}
			else if (dragButton > 0) {
				if (!lastcmd) {
					beenDragging = False;
					dragButton = 0;
					return;
				}
				dragButton = -1;
				lastcmd->TrackMouse(Command::TRACK_RELEASE,
					&anchorPoint, &previousPoint, 
					&nextPoint);
				lastcmd->SayAborted();
				lastcmd->Abort();
				return;
			}
			beenDragging = False;
			dragButton = 0;
			break;
		}
		case MotionNotify: {
			XMotionEvent *event = (XMotionEvent *)dacs->event;
			if (event->state & 
			    (Button1MotionMask | Button2MotionMask)) {
				int xx = event->x;
				int yy = event->y;
				if (!beenDragging && abs(xx-x) < 5 && 
				    abs(yy-y) < 5 && !zigZag) 
					return;
				if (!beenDragging && !zigZag) {
					if (pasting)
						return;
					beenDragging = True;
					anchorPoint.Set(x,y);
					previousPoint = anchorPoint;
					nextPoint = anchorPoint;
					Command *newCmd;
					if (event->state & Button1MotionMask) {
						if (event->state & ShiftMask)
							newCmd = viewer->Connect(x,y);
						else
							newCmd = viewer->Drag(x,y);
						dragButton = Button1;
					}
					else {  // button2
						newCmd = viewer->Connect(x,y);
						dragButton = Button2;
					}
					viewer->NewCommand(newCmd);
					if (!newCmd) 
						return;
					newCmd->TrackMouse(
						Command::TRACK_PRESS, 
						&anchorPoint, &previousPoint, 
						&nextPoint);
				}
				if (beenDragging) {
					nextPoint.Set(event->x, event->y);
					Command *lastcmd = viewer->GetLastCmd();
					if (!lastcmd) 
						return;
					lastcmd->TrackMouse(
						Command::TRACK_DRAG, 
						&anchorPoint, &previousPoint, 
						&nextPoint);
					previousPoint = nextPoint;
				}
				return;
			}
			else if (zigZag || pasting) {
				nextPoint.Set(event->x, event->y);
				Command *lastcmd = viewer->GetLastCmd();
				if (lastcmd)
					lastcmd->TrackMouse(Command::TRACK_DRAG,
						&anchorPoint, &previousPoint, 
						&nextPoint);
				previousPoint = nextPoint;
				return;
			}
			else
				viewer->MovingPointer(event->x, event->y);
			break;
		}
		case KeyPress: {
			XKeyEvent *event = (XKeyEvent *)dacs->event;
			XComposeStatus status;
			KeySym keysym;
			int n = XLookupString(event, buf, 5, &keysym, &status);
                        if (n == 1) {
                                // normal ascii character.
                                viewer->KeyTyped(event->x, event->y, buf[0]);
                        }
                        else {
                                // special character.
                                int code = MapKeySym(keysym);
                                if (code != 0)
                                        viewer->KeyTyped(event->x, event->y,
                                                        code);
                        }
			break;
		}
		// next two don't work ??
		case EnterNotify: {
			error("ENTERING !!!\n");
			viewer->Activate();
			break;
		}
		case LeaveNotify: {
			error("LEAVING !!!\n");
			viewer->Deactivate();
			break;
		}
		default:
			// do nothing.
			break;
		}}
	}
}

void DrawingArea::Redraw(XEvent *e) {
	if (!e)
		return;
	XExposeEvent *event = (XExposeEvent *)e;
	if (check(grafport))
		grafport->Redraw(event->x, event->y, 
			event->width, event->height, event->x, event->y);
}

void DrawingArea::PopupMenu(XEvent *e) {
	Widget w = popupMenu->GetWidget();
	XmMenuPosition(w, (XButtonEvent *)e);
	XtManageChild(w);
}

void DrawingArea::EnableUndo(bool flag) {
	Widget undoMenuItem = popupMenu->GetMenuItem("Undo");
	if (undoMenuItem)
		XtVaSetValues(undoMenuItem, XmNsensitive, flag, 0);
}

void DrawingArea::EnableRedo(bool flag) {
	Widget redoMenuItem = popupMenu->GetMenuItem("Redo");
	if (redoMenuItem)
		XtVaSetValues(redoMenuItem, XmNsensitive, flag, 0);
}

void DrawingArea::Enable(const char *label, bool flag) {
	Widget menuItem = popupMenu->GetMenuItem(label);
	if (menuItem)
		XtVaSetValues(menuItem, XmNsensitive, flag, 0);
}

void DrawingArea::SetUndoName(const char *undoname) {
	XmString s = CreateXmString(undoname);
	Widget undoMenuItem = popupMenu->GetMenuItem("Undo");
	if (undoMenuItem)
		XtVaSetValues(undoMenuItem, XmNlabelString, s, 0);
	XmStringFree(s);
}

void DrawingArea::SetRedoName(const char *redoname) {
	XmString s = CreateXmString(redoname);
	Widget redoMenuItem = popupMenu->GetMenuItem("Redo");
	if (redoMenuItem)
		XtVaSetValues(redoMenuItem, XmNlabelString, s, 0);
	XmStringFree(s);
}

int DrawingArea::MapKeySym(KeySym keysym) {
	switch(keysym) {
#ifdef XK_Home
	case XK_Home: return Key::HOME;
#endif
#ifdef XK_Left
	case XK_Left: return Key::LEFT;
#endif
#ifdef XK_Up
	case XK_Up: return Key::UP;
#endif
#ifdef XK_Right
	case XK_Right: return Key::RIGHT;
#endif
#ifdef XK_Down
	case XK_Down: return Key::DOWN;
#endif
#ifdef XK_Page_Up
	case XK_Page_Up: return Key::PAGE_UP;
#endif
#ifdef XK_Page_Down
	case XK_Page_Down: return Key::PAGE_DOWN;
#endif
#ifdef XK_End
	case XK_End: return Key::END;
#endif
#ifdef XK_Insert
	case XK_Insert: return Key::INSERT;
#endif
	default: return 0;
	}
}
