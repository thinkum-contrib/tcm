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
#ifndef __BAG_C
#define __BAG_C


#include "bag.h"



//template class Bag<Subject *>;

//template class List<Subject *>;




template <class T> Bag<T>::Bag(){
}

template <class T> Bag<T>::Bag(const List<T> &l, int n){
  int i=l.count();
  int j;
  for (j=0;j<i;j++)
    add(l[j],n);     
}

template <class T> Bag<T>::Bag(const Bag<T> &b){
  list=b.list;
  int i=list.count();
  int j;
  for (j=0;j<i;j++)
    countl[j]=b.countl[j];      
}



template <class T> void Bag<T>::add(const T &e){
  add(e,1);
}

template <class T> void Bag<T>::add(const T &e,int n){
   int i=0;
   i = list.find(e);
   if (i>=0) 
      countl[i]=countl[i]+n;
   else //i==-1 
     { 
        list.add(e);
      	countl[list.count()-1]=n;
     }
}


template <class T> bool Bag<T>::remove(const T &e){
  if (count(e)>0){
      add(e,-1);
      return True;
   }
   else
      return False;
}

	/// return list is set			                        
template <class T> bool Bag<T>::isSet() const{
  int i=list.count();
  int j;
  for (j=0;j<i;j++){
     if (countl[i]>1) return False;
  }
  return True;
}                                          


        /// count the number of times e occurs in the list
template <class T> int Bag<T>::count(const T &e) const{
  int i= list.find(e);
  i = list.find(e);
  if (i<0) 
      return 0;
   else
     return countl[i];
}                                

	/// return if bag contains bag b                          
template <class T> bool Bag<T>::contains(Bag<T> &b) const{
  List<T> lt;
  b.GetList(lt);
  int i=lt.count();
  int j; 
  for (j=0;j<i;j++){
    //  T current=lt[j]; //no copy?
      if (count(lt[j]) < (b.countl[j])) 
        return False;
  }
  return True;
}

template <class T> void Bag<T>::join(const Bag <T> &l) {
  List<T> lt;
  l.GetList(lt);
  int i=lt.count();
  int j;
  for (j=0;j<i;j++){
    add(lt[j],l.countl[j]); //assuming lt is set
  }  
}

                           

template <class T> bool Bag<T>::diff( Bag <T> &l) {
  List<T> lt;
  l.GetList(lt);
  int i=lt.count();
  int j;
  for (j=0;j<i;j++){
    T current=lt[j]; //no copy?
    if (count(current) < l.countl[j]) 
      return False;
    else
      add(current,-(l.countl[j]));  
  }
  return True;
}



template <class T> int Bag<T>::length(void){
  int i=list.count();
  int length=0;
  int j=0;
  for (j=0;j<i;j++){
        length=length+countl[j];
  }
  return length;
}

template <class T> void Bag<T>::GetSet(List <T> *li){
  int i=list.count();
  int j;
  for (j=0;j<i;j++){
     if (countl[j]>0) 
        li->add(list[j]);
  }
}


template <class T> void Bag<T>::empty(){
  list.empty();
}




#include "../../dg/subject.h"
#include "adshyperedge.h"
#include "atdactionstatenode.h"

template class Bag <Subject *>;
template class Bag <ADSHyperEdge *>;
template class Bag <ATDActionStateNode *>;

#endif
