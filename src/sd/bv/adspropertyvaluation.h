//////////////////////////////////////////////////////////////////////////////////
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Rik Eshuis (eshuis@cs.utwente.nl).
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
#ifndef _ADSPROPVAL_H
#define _ADSPROPVAL_H



#include "bool.h"
#include "adsproperty.h"


class OutputFile;

/// variable class.
class PropVal  {
/*@Doc: {\large {\bf scope:} } */
public:
  PropVal( Prop *prop, bool b);
  ///
  PropVal(const PropVal &copy);
  ///
  ~PropVal();
  ///
  bool operator==(const PropVal &copy);
  ///
  Prop *GetProp(void);
  ///
  bool GetBool(void);
  ///
  void SetBool(bool b);
  ///
  void Write(OutputFile *ofile);
  ///
  void Write();

 private:
  ///
  Prop *p;
  ///
  bool v;
};

#endif
