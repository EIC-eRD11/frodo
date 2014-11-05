#include "Generate.h"
#include "frodo.h"
#include "AParticle.h"

#include "TRandom.h"
#include "TMath.h"
#include <iostream>
#include "Riostream.h"

const double R = 35000;

void Generate(unsigned int Npart)
{
  static TRandom randy(0);

  frodo *fr = frodo::instance();
  fr->HBDParticles.clear();

  for (unsigned int i=0; i<Npart; i++)
    {
      double s = randy.Rndm();
      double s1 = 0;
      if(s < 0.5) s1 = 1;
      else s1 = -1;

      double x = 2*R*randy.Rndm() - R;      
      double y = s1*sqrt(R*R - x*x);
      
      if(fabs(x) <= 1000 || fabs(y) <= 1125)
	{
	  //cout<<"reject!"<<endl;
	  continue;
	}
      double q = -1;
      while (q<=0) q=randy.Exp(20);
      //cout<<"q= " <<q<<endl;
      
      fr->HBDParticles.push_back( AParticle(x,y,q) );
    }
  
}
