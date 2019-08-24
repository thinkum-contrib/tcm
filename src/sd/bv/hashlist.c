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


#define HASHSIZE 100003

#include "hashlist.h"
#include "adsvaluation.h"
#include "adstransition.h"
#include <stdlib.h>

ValuationHashList::ValuationHashList() {
  int i;
  for (i = 0; i < HASHSIZE; i++) {
    hash_list.add(NULL);
  }
}

void ValuationHashList::add(ADSValuation *adk,int key) {
  key=key % HASHSIZE;
  if (!hash_list[key]) hash_list[key]=new List<ADSValuation *> ;
  hash_list[key]->add(adk);
}

ADSValuation *ValuationHashList::isin(ADSValuation *adk,int key) {
  key=key % HASHSIZE;
  List <ADSValuation *> *l=hash_list[key];
  if (!l)  return NULL;   
  for (l->first();!l->done();l->next()){
    if (*(l->cur())==*adk) return l->cur();
  }
  return NULL;
}

/*
void ValuationHashList::Write(OutputFile *f){
  int i,j;
  j=0;
  for (i = 0; i < HASHSIZE; i++) {
    (*f) << "entry:\t"<< i << "\t\tused:\t"<<  (hash_list[i]==NULL?0:hash_list[i]->count() ) << "\n" ;
    if (hash_list[i]!=NULL) j=j+hash_list[i]->count();
  }
  (*f) << "\nTotal:\t"<< j <<"\n\n\n\n";
}
*/

TransitionHashList::TransitionHashList() {
  int i;
  for (i = 0; i < HASHSIZE; i++) {
    hash_list.add(NULL);
  }
}

void TransitionHashList::add(ADSTransition *t,int key) {
  key=key % HASHSIZE;
  if (!hash_list[key]) hash_list[key]=new List<ADSTransition *> ;
  hash_list[key]->add(t);
}

ADSTransition *TransitionHashList::isin(ADSTransition *t,int key) {
  key=key % HASHSIZE;
  List <ADSTransition *> *l=hash_list[key];
  if (!l)  return NULL;   
  for (l->first();!l->done();l->next()){
    if (*(l->cur())==*t) return l->cur();
  }
  return NULL;
}

/*
void TransitionHashList::Write(OutputFile *f){
  int i;
  for (i = 0; i < HASHSIZE; i++) {
    (*f) << "entry:\t"<< i << "\t\tused:\t"<<  (hash_list[i]==NULL?0:hash_list[i]->count() ) << "\n" ;
  }
}
*/

