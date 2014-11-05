#include <iostream>

#include "AStrip.h"

#include "TObject.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TBox.h"

using namespace std;

AStrip::AStrip(double X1, double Y1, double X2, double Y2)
{
  // Set the patameters define the pad plane space.
  x1 = X1;
  y1 = Y1;
  x2 = X2;
  y2 = Y2;
  q  = 0;
}

void AStrip::Draw(double X1,double Y1, double X2, double Y2, int Qfrac)
{
  TBox astripa(X1,Y1,X2,Y2);
  astripa.SetFillColor(Qfrac); 
  astripa.DrawBox(X1,Y1,X2,Y2);
}
