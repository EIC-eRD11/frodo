#include "Generate.h"
#include "frodo.h"
#include "AParticle.h"

#include "TRandom.h"

void Generate(unsigned int Npart)
{
  TRandom randy;

  frodo *av = frodo::instance();
  av->theParticles.clear();

  for (unsigned int i=0; i<Npart; i++)
    {
      double x = Xspace*randy.Rndm();
      double y = Yspace*randy.Rndm();
      double q = -1;
      while (q<0) q=randy.Gaus(100,20);
      
      av->theParticles.push_back( AParticle(x,y,q) );
    }
  

}
