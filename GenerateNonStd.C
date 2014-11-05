#include "GenerateNonStd.h"
#include "frodo.h"
#include "AParticle.h"
#include "ARing.h"

#include "TRandom.h"
#include "TMath.h"
#include <iostream>

using namespace std;

//const double R = 25000;
//const double C = 0.0;

void GenerateNonStd(unsigned int Npart)
{
  frodo *fr = frodo::instance();

  static TRandom randy(0);

  fr->HBDParticles.clear();
  
  double s = randy.Rndm();
  //cout<<"s= "<<s<<endl;
  double s1 = 0;
  if(s < 0.5) s1 = 1;
  else s1 = -1;
  
  double a = randy.Rndm();
  //cout<<"a= "<<a <<endl;
  double Cx = 2*fr->Ring[0].C()*a - fr->Ring[0].C();
  double Cy = s1*sqrt(fr->Ring[0].C()*fr->Ring[0].C()-Cx*Cx);
  fr->CX.push_back(Coordinates(Cx));
  fr->CY.push_back(Coordinates(Cy));
  //cout<<"ring center is: ( "<< Cx <<" , " << Cy << " ) " <<endl;

  for (unsigned int i=0; i<Npart; i++)
    {
      //cout<<"Npart= " <<i<<endl;
      double S = randy.Rndm();
      //cout<<"S= "<<S<<endl;
      double s2 = 0;
      if(S < 0.5) s2 = 1;
      else s2 = -1;

      double b = randy.Rndm();
      //cout<<"b= "<<b<<endl;
      
      double x = Cx + 2*fr->Ring[0].R()*b - fr->Ring[0].R();      
      double y = Cy + s2*sqrt(fr->Ring[0].R()*fr->Ring[0].R() - (x-Cx)*(x-Cx));
      
      if(fabs(x) <= 1000 || fabs(y) <= 1125)
	{
	  i--;
	  //cout<<"reject!"<<endl;
	  continue;
	}
      double q = -1;
      while (q<=0) q=randy.Exp(80000);
      //cout<<"q= " <<q<<endl;
      
      fr->HBDParticles.push_back( AParticle(x,y,q) );
    }
  //cout<<"# of particles: " <<fr->HBDParticles.size()<<endl;
  
  
}
