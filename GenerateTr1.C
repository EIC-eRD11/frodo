#include "GenerateTr1.h"
#include "frodo.h"
#include "AParticle.h"

#include "TRandom.h"

const double Xspace = 100000;
const double Yspace = 100000;

void GenerateTr1(unsigned int Npart)
{
  TRandom randy(0);

  frodo *fr = frodo::instance();
  fr->Tr1Particles.clear();

  for (unsigned int i=0; i<Npart; i++)
    {
      double x = Xspace*randy.Rndm();
      double y = Yspace*randy.Rndm();
      
      double q = -1;
      while (q<=0) q=randy.Landau(10,5);
      
      fr->Tr1Particles.push_back( AParticle(x,y,q) );
    }
  
}
