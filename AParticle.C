#include <iostream>
#include "TMarker.h"
#include "TAttMarker.h"

#include "AParticle.h"
#include "frodo.h"

using namespace std;

AParticle::AParticle(double X, double Y, double Q)
{
  // Set the patameters define the pad plane space.
  x = X;
  y = Y;
  q = Q;
}

void AParticle::Draw()
{
  TMarker dot (x,y,4);
  dot.SetMarkerColor(2);
  dot.SetMarkerSize(1.5);
  dot.DrawMarker(x,y);
}
