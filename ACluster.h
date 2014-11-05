#ifndef __ACLUSTER_H__
#define __ACLUSTER_H__

//
//  Hello ACluster Fans:
//
//  A Cluster is a decision on the solution to the pattern
//  recognition process.  Is consists of three Blobs...
//  One each in the X, Y, and U directions.  This object
//  holds pointers to the three Blobs, and will return the 
//  pointers to them, as well as some simple functions like the
//  average of the corrected charge measurements and the best
//  estimates for the X() and Y() of the whole cluster.
//
//                                                HG & TKH
//                                                11-16-2011
//

#include "ABlob.h"

class ACluster
{
public:
  ACluster() {}
  ACluster(ABlob *XBLOB, ABlob *YBLOB, ABlob *UBLOB);
  virtual ~ACluster() {}

  // gets...
  double BestX();
  double BestY();
  double BestQ() {return (xblob->Q()+yblob->Q()+ublob->Q())/3.0;}

  ABlob *XBlob() {return xblob;}
  ABlob *YBlob() {return yblob;}
  ABlob *UBlob() {return ublob;}


protected:
  ABlob *xblob;
  ABlob *yblob;
  ABlob *ublob;
  
};

#endif /* __ACLUSTER_H__ */
