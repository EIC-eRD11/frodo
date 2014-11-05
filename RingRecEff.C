#include "RingRecEff.h"
#include "frodo.h"
#include "ARing.h"

#include <iostream>

using namespace std;

void RingRecEff()
{
  frodo *fr = frodo::instance();
  cout<<"# of success: "<< fr->Nsuc.size() << ";                        # of off success: "<< fr->Nsuc_off.size() << endl;

  cout<<"Ring Reconstruction efficiency is: " <<fr->Nsuc.size()/2000.0 <<";   Ring Reconstruction efficiency (off) is: " << fr->Nsuc_off.size()/2000.0<<endl;
}

