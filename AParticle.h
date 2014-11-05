#ifndef __APARTICLE_H__
#define __APARTICLE_H__

#include "TObject.h"

//
//  Hello Aparticle Fans:
//
//    Welcome to Particle.  This is a trivial class that says every
//  "particle" to be detected by our system is associated with a position
//  and a charge deposit.  This class is TEMPORARY!  A good monte Carlo
//  will put fluctuations in the particles.  To learn how to do
//  correct pattern recognition, we will use these simple "perfect"
//  particles as a means to guide and perfect our code.
//
//    Later on, a true MC calculation that understands details of the
//  energy deposit in the gas and the drift and avalanche processes will
//  eliminate this class from our codes...
//
//                                                HG & TKH
//                                                11-16-2011
//

class AParticle
{
public:
  AParticle() {}
  AParticle(double X, double Y, double Q );
  virtual ~AParticle() {}

  double X() {return x;}
  double Y() {return y;}
  double Q() {return q;}
  void Draw();

protected:
  double x;
  double y;
  double q;
  
};

#endif /* __APARTICLE_H__ */
