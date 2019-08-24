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
#include "adsclockmanager.h"
#include "adsclockconstraint.h"
#include "outputfile.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>

ClockManager::ClockManager(){
  int i;
  for (i=0;i<MAX;i++){
    integer_timespent[i]=0;
    fraction_timespent[i]=0;
  }
  interval=0;
}


ClockManager::~ClockManager(){
}


ClockManager::ClockManager(const ClockManager &c){
  cl=c.cl;
  int clistlen=cl.count();
  int i;
  for (i=0;i<clistlen   ;i++){
    integer_timespent[i]=c.integer_timespent[i];
    fraction_timespent[i]=c.fraction_timespent[i];
  }
  interval=c.interval;
}



bool ClockManager::operator==( ClockManager comp){
  int clistlen=cl.count();
  int compclistlen=comp.cl.count();

  int i,j;
  for (i=0;i<clistlen;i++){
    bool found=False;
    for (j=0;j<compclistlen;j++){
       if ( (cl[i]==comp.cl[j]) && (integer_timespent[i]==comp.integer_timespent[j])&& (fraction_timespent[i]==comp.fraction_timespent[j]) ){
        found=True;
        break;
      }
    }
    if (!found) return False;
  }
  for (j=0;j<compclistlen;j++){
    bool found=False;
    for (i=0;i<clistlen;i++){
       if ((cl[i] == comp.cl[j] ) && (integer_timespent[i]==comp.integer_timespent[j]) && (fraction_timespent[i]==comp.fraction_timespent[j]) )  {
        found=True;
        break;
      }
    }
    if (!found) return False;
  }
  return True;
}



bool ClockManager::ExistScheduled(){
  return (cl.count()>0);
}


bool ClockManager::ExistTimeouts(){
    int clistlen=cl.count();
    for (int i=0;i<clistlen;i++){
      if ((integer_timespent[i]==0) && (fraction_timespent[i]==0)){
	return True;
      }
    }  
    return False;
}




// Get all clockconstraints that must be responded to NOW
void ClockManager::GetTimeouts(List <ClockConstraint *> *l){
  if (!ExistScheduled()) {
    error("There are no timeouts scheduled!\n");
  }
  else{
    int i;
    int clistlen=cl.count();
    for (i=0;i<clistlen;i++){
      if ((integer_timespent[i]==0) && (fraction_timespent[i]==0)){
	l->add(cl[i]);
      }
    }
  }
}




bool ClockManager::Update(List <ClockConstraint *> *zero, 
			  List <ClockConstraint *> *off){

  // reset off timers 

  // locate timers in cl
  for (off->first();!off->done();off->next()){
    int index=cl.find(off->cur());  // must exists due to assumption
    if (index==-1){ 
      error("I cannot turn off a clock constraint that is not turned on!\n"); 
      return False;  
    }
    integer_timespent[index]=-1; // used below to update array integer_timespent
  }
  int nrtimer=cl.count();

  // remove timers from cl
  for (off->first();!off->done();off->next()){
    cl.remove(off->cur());  // off->cur() must exist due to assumption
  }
 


  // remove off timers from array timespent
  int i;
  for (i=0;i<nrtimer;i++){
    if (integer_timespent[i]==-1){

      int j;
   
      // remove from timespent
      for (j=i;j<nrtimer-1;j++){
	integer_timespent[j]=integer_timespent[j+1];
	fraction_timespent[j]=fraction_timespent[j+1];
      }
      
    }
  }


  for (zero->first();!zero->done();zero->next()){
    //zero->cur()->Write();
    if (cl.find(zero->cur())>-1){
	error("Warning: hyperedge ");
	string str= cl[cl.find(zero->cur())]->GetLimit();
	error(str.getstr());
	error(" multiple times enabled!\n");
	return False;
    }
    else{
      cl.add(zero->cur());
      integer_timespent[cl.count()-1]=zero->cur()->GetLimit();
      fraction_timespent[cl.count()-1]=0;
    }    
  }  
  return True;
}






bool ClockManager::Tick(){
  int i;
  int clen=cl.count();
  for (i=0;i<clen;i++){
    if (fraction_timespent[i]==0){
      if (integer_timespent[i]>0){ 
	integer_timespent[i]--;
      }
      else{ // (integer_timespent[i]==0)
	error("A timeout is not responded to in time!\n");
	return False;
      }  
      fraction_timespent[i]=interval-1;
    }
    else{ // fraction_timespent[i]>0
      fraction_timespent[i]--;  
    }
  }
  return True;
}






void ClockManager::Write(OutputFile *ofile){
  (*ofile) << "Status of clock manager:\n";
  for (cl.first();!cl.done();cl.next()){
       cl.cur()->Write(ofile);
  }
  unsigned i;
  for (i=0;i<cl.count();i++){
     (*ofile) << "Time spent " << integer_timespent[i] <<"\t"<< 
	 	fraction_timespent[i] << "/"<< interval  << "!\n";
  }
}


void ClockManager::Write(){
  std::cout << "Status of clock manager:\n";
  for (cl.first();!cl.done();cl.next()){
       cl.cur()->Write();
  }
  unsigned i;
  for (i=0;i<cl.count();i++){
     std::cout << "Time spent " << integer_timespent[i] <<"\t"<< 
	 	fraction_timespent[i] << "/"<< interval  << "!\n";
  }
}
