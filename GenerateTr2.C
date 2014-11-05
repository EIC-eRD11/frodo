#include "GenerateTr2.h"
#include "frodo.h"
#include "AParticle.h"

#include "TRandom.h"

void GenerateTr2(unsigned int Npart)
{
  TRandom randy(0);

  frodo *fr = frodo::instance();
  fr->Tr2Particles.clear();

  for (unsigned int i=0; i<Npart; i++)
    {
      double x = 100000*randy.Rndm();
      double y = 100000*randy.Rndm();
      
      double q = -1;
      while (q<=0) q=randy.Landau(10,5);
      
      fr->Tr2Particles.push_back( AParticle(x,y,q) );
    }
  
}
