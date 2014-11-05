#ifndef __ABLOB_H__
#define __ABLOB_H__

//
//  Hello ABlob Fans:
//
//  The pattern recognition will create a vector of Blob objects.
//  in the current implementation, each Blob object will be made
//  as a collection of three strips where the charge on the "center"
//  strip is greater than the left strip and greater than or equal
//  to the right strip.
//
//  The blob class contains POINTERS (not owned locally so they should
//  not be deleted upon destruction) to the three strips in question.
//  It then implements methods to return the total blob charge, and the
//  coordinate of the centroid.
//
//  Since we know that there is always some level of differential non-linearity
//  in  segmented pad plane response, we expect that the simple centroid
//  calculation will need some kind of correction.  We opt to NOT put
//  the correction function as a part of the Blob object, but expect the user
//  to write external codes to manipulate and set the corrected charges and
//  positions.
//
//  Also worth noting is the intended use of the CorrectedQ (corrected charge).
//  Charge is divided among X,Y, and U coordinates roughly equally (1/3 each).
//  The corrected charge is intended to take away this factor so that each of
//  of the blobs makes its own estimate of the TOTAL charge deposit of the
//  ORIGINAL particle.  This is the proper value for matching at the pattern 
//  recognition stage.
//
//                                                HG & TKH
//                                                11-16-2011
//

class AStrip;

class ABlob
{
public:
  ABlob() {}
  ABlob(AStrip *ONE, AStrip *TWO, AStrip *THREE);
  virtual ~ABlob() {}

  // sets...
  void SetCorrectedCentroid(double CC) {correctedcentroid = CC;}
  void SetCorrectedQ       (double CQ) {correctedq = CQ;}

  // gets...
  double Centroid();
  double Q       ();

  double CorrectedCentroid() {return correctedcentroid;}
  double CorrectedQ       () {return correctedq; }

protected:
  AStrip *one;
  AStrip *two;
  AStrip *three;
  
  double correctedcentroid;
  double correctedq       ;

};

#endif /* __ABLOB_H__ */
