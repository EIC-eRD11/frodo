#include "ACluster.h"
#include "ABlob.h"

ACluster::ACluster(ABlob *X, ABlob *Y, ABlob *U)
{
  xblob = X;
  yblob = Y;
  ublob = U;
}


double ACluster::BestX()
{
  //Average of the "3" crossing points:

  double x12 = xblob->CorrectedCentroid();
  double x3  = yblob->CorrectedCentroid() - ublob->CorrectedCentroid();

  return (2.0*x12 + x3)/3.0;
}

double ACluster::BestY()
{
  //Average of the "3" crossing points:

  double y12 = yblob->CorrectedCentroid();
  double y3  = xblob->CorrectedCentroid() + ublob->CorrectedCentroid();

  return (2.0*y12 + y3)/3.0;
}

