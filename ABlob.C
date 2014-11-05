#include "ABlob.h"
#include "AStrip.h"
#include <iostream>

using namespace std;

ABlob::ABlob(AStrip *ONE, AStrip *TWO, AStrip *THREE)
{
  one = ONE;
  two = TWO;
  three = THREE;

  correctedq = 0;
  correctedcentroid = 0;
}


double ABlob::Centroid()
{
  if (Q() == 0)
    {
      cout << "ABlob:: Error: Blob has zero total charge...no centroid" << endl;
      return -9999;
    }

  double num = one->Q()*one->Center() +
    two->Q()*two->Center() +
    three->Q()*three->Center();

  return num/Q();

}

double ABlob::Q()
{
 double den = one->Q() + two->Q() + three->Q();
 return den;
}
