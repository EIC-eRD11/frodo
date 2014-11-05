#include "DrawingTr1.h"
#include "AParticle.h"
#include "AStrip.h"
#include "APadStrip.h"
#include "frodo.h"

#include "TCanvas.h"
#include "TObject.h"
#include "TMath.h"

#include "Riostream.h"
#include <iostream>

void DrawingTr1()
{
  frodo *fr = frodo::instance();

  TCanvas *Tracker1 = new TCanvas("Tracker1","Tracker 1 Event Display",0,0,1500,1500);
  Tracker1->Range(0,0,100000,100000);

  double Qx = 0;
  double Qy = 0;
  double Qtot = 0;
  for(unsigned int i=0; i<255; i++)
    {
      Qx += fr->Tr1XStrips[i].Q();
      Qy += fr->Tr1YStrips[i].Q();
    }
  Qtot = Qx + Qy;

  
  //Draw X strips:
  double X1 = 0;
  double Y1 = 0;
  double X2 = 300;
  double Y2 = 100000;
  for(unsigned int i=0; i<256; i++)
    {
      int Qfrac = int(fr->Tr1XStrips[i].Q()/Qtot*100);
      // int Qfrac = 3;
      fr->Tr1XStrips[i].Draw(X1,Y1,X2,Y2,Qfrac);
      Tracker1->Update();
      X1 = X2 + 90;
      X2 = X1 + 300;
    }

  //Draw Y strips:
  X1 = 0;
  Y1 = 0;
  X2 = 100000;
  Y2 = 300;
  for(unsigned int i=0; i<256; i++)
    {
      int Qfrac = int(fr->Tr1YStrips[i].Q()/Qtot*100);
      //int Qfrac = 2;
      fr->Tr1YStrips[i].Draw(X1,Y1,X2,Y2,Qfrac);
      Tracker1->Update();
      Y1 = Y2 + 90;
      Y2 = Y1 + 300; 
    }

}


  

