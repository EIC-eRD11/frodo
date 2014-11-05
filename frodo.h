#ifndef __FRODO_H__
#define __FRODO_H__

#include <vector>

//
//  Hello EIC Fans:
//
//    Welcome to Frodo.  Frodo is the Lord of the Rings.
//
//  The code package Frodo is used to perform pattern recognition
//  on the cherenkov test beam experiment from Spring 2012.  It supports THREE
//  detectors:  Tracker1, Tracker2, and HBD.
//
//    If this code were written for PHENIX, data objects (Blobs, Clusters, etc) would be
//  located in a PHENIX "Node Tree" (linked list).  Since EIC is not PHENIX, we have
//  TEMPORARILY(!!!) located these objects inside frodo awaiting an EIC
//  standard for handling such details.
//
//    This file principally declares vectors of object types that are essential to the 
//  pattern recognition itself.
//
//                                                HG & TKH
//                                                11-16-2011
//

#include "AParticle.h"
#include "AStrip.h"
#include "APadStrip.h"
#include "Coordinates.h"
#include "ARing.h"
//#include "ABlob.h"
//#include "ACluster.h"
#include "TObject.h"
#include "TVector3.h"
#include <iostream>

class frodo
{
 public:
  static frodo *instance()
  {
    if (__instance) return __instance;
    __instance = new frodo();
    return __instance;
  }
  virtual ~frodo() {}

  std::vector<AParticle> Tr1Particles;
  std::vector<AParticle> Tr2Particles;
  std::vector<AParticle> HBDParticles;

  std::vector<TVector3> PseudoPoints;
  std::vector<TVector3> J1_PseudoPoints;
  std::vector<TVector3> J2_PseudoPoints;
  std::vector<TVector3> J3_PseudoPoints;
  std::vector<TVector3> J4_PseudoPoints;
  std::vector<Coordinates> Y1;
  std::vector<Coordinates> X1;
  std::vector<Coordinates> Y2;
  std::vector<Coordinates> X2;
  std::vector<Coordinates> Y3;
  std::vector<Coordinates> X3;
  std::vector<Coordinates> Y4;
  std::vector<Coordinates> X4;
  std::vector<Coordinates> AllX;
  std::vector<Coordinates> AllY;
  std::vector<Coordinates> CX;
  std::vector<Coordinates> CY;
  
  std::vector<Coordinates> Nsuc;
  std::vector<Coordinates> Nsuc_off;

  // Tracker 1 Characteristics:
  std::vector<AStrip>    Tr1XStrips  ;
  std::vector<AStrip>    Tr1YStrips  ;
  //std::vector<ABlob>     Tr1XBlobs   ;
  //std::vector<ABlob>     Tr1YBlobs   ;
  //std::vector<ACluster>  Tr1Clusters ;

  // Tracker 2 Characteristics:
  std::vector<AStrip>    Tr2XStrips  ;
  std::vector<AStrip>    Tr2YStrips  ;
  //std::vector<ABlob>     Tr2XBlobs   ;
  //std::vector<ABlob>     Tr2YBlobs   ;
  //std::vector<ACluster>  Tr1Clusters ;

  // HBD Characteristics:
  std::vector<APadStrip> J1_XStrips  ;
  std::vector<AStrip>    J1_YStrips  ;
  std::vector<APadStrip> J2_XStrips  ;
  std::vector<AStrip>    J2_YStrips  ;
  std::vector<APadStrip> J3_XStrips  ;
  std::vector<AStrip>    J3_YStrips  ;
  std::vector<APadStrip> J4_XStrips  ;
  std::vector<AStrip>    J4_YStrips  ;
  //std::vector<ABlob>     J1_XBlobs   ;
  //std::vector<ABlob>     J1_YBlobs   ;
  //std::vector<ABlob>     J2_XBlobs   ;
  //std::vector<ABlob>     J2_YBlobs   ;
  //std::vector<ABlob>     J3_XBlobs   ;
  //std::vector<ABlob>     J3_YBlobs   ;
  //std::vector<ABlob>     J4_XBlobs   ;
  //std::vector<ABlob>     J4_YBlobs   ;
  //std::vector<ACluster>  HBDClusters ;

  std::vector<ARing> Ring;

  void Report();

protected:
  frodo();
  static frodo *__instance;

};

#endif /* __FRODO_H__ */
