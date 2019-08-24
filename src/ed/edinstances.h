//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
//-----------------------------------------------------------------------------
#ifndef __EDINSTANCES_H
#define __EDINSTANCES_H

#ifdef __GNUC__

//GNU g++ does not implement a separate pass to instantiate template
//functions and classes at this point; for this reason, it will not work,
//for the most part, to declare your template functions in one file and
//define them in another. The compiler will need to see the entire
//definition of the function, and will generate a static copy of the
//function in each file in which it is used.
// 
//g++ does not automatically instantiate templates defined in other
//files. Because of this, code written for cfront will often produce
//undefined symbol errors when compiled with g++. You need to tell g++
//the file where they are defined.

#include "assoclist.h"
#include "lstring.h"
#include "point.h"
#include "dpoint.h"
#include "textalign.h"
#include "linestyle.h"
#include "fillstyle.h"
#include "xfont.h"
#include "color.h"
#include "readdirection.h"
#include "mainwindow.h"
#include <Xm/Xm.h>

template <> void List<int>::clear() { empty(); }
template <> void List<unsigned>::clear() { empty(); }
template <> void List<long>::clear() { empty(); }
template <> void List<unsigned long>::clear() { empty(); }
template <> void List<char>::clear() { empty(); }
template <> void List<float>::clear() { empty(); }
template <> void List<double>::clear() { empty(); }
template <> void List<bool>::clear() { empty(); }
template <> void List<string>::clear() { empty(); }
template <> void List<Point>::clear() { empty(); }
template <> void List<Widget>::clear() { empty(); }
template <> void List<TextAlign::Type>::clear() { empty(); }
template <> void List<LineStyle::Type>::clear() { empty(); }
template <> void List<FillStyle::Type>::clear() { empty(); }
template <> void List<ReadDirection::Type>::clear() { empty(); }
template <> void List<XFont *>::clear() { empty(); }

template class List<int>;
template class List<int *>;
template class List<unsigned>;
template class List<long>;
template class List<unsigned long>;
template class List<char>;
template class List<float>;
template class List<double>;
template class List<bool>;
template class List<Assoc *>;
template class List<Point>;
template class List<Point *>;
template class List<DPoint *>;
template class List<string *>;
template class List<string>;
template class List<Widget>;
template class List<XFont *>;
template class List<Color *>;
template class List<MainWindow *>;
template class List<List<string *> *>;
template class List<List<Widget> *>;
template class List<TextAlign::Type>;
template class List<LineStyle::Type>;
template class List<FillStyle::Type>;
template class List<ReadDirection::Type>;
#endif
#endif
