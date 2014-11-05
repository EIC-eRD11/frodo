#include "APadStrip.h"
#include "AStrip.h"

#include "TObject.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TBox.h"

#include <iostream>

using namespace std;

APadStrip::APadStrip(double X1, double Y1, double X2, double Y2)
{
  // Set the patameters define the pad plane space.
  x1 = X1;
  y1 = Y1;
  x2 = X2;
  y2 = Y2;
  q  = 0;
}

void APadStrip::Draw(double X1, double Y1, double X2, double Y2, int Qfrac)
{
  for(unsigned int n=0; n<60; n++)
    {
      TBox apadstrip (X1,Y1,X2,Y2);
      apadstrip.SetFillColor(Qfrac); 
      apadstrip.DrawBox(X1,Y1,X2,Y2);

      Y1 = Y2 + 500;
      Y2 = Y1 + 300;
      
      //cout<<"A set of pads i.e. one xstrip is drawn!"<<endl;
    }    
}
