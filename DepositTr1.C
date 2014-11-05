#include "DepositTr1.h"
#include "frodo.h"
#include "AParticle.h"
#include "AStrip.h"
#include "APadStrip.h"

#include "TMath.h"

#include "Riostream.h"
#include <iostream>

const double Delx  = 20; 
const double Dely  = 20;
const double Sigma = 130;

void DepositTr1()
{
  frodo *fr = frodo::instance();

  // Zero out the charge from the prior event...
  for (unsigned int i=0; i<fr->Tr1XStrips.size(); i++)
    {
      fr->Tr1XStrips[i].SetQ(0);
    }
  for (unsigned int i=0; i<fr->Tr1YStrips.size(); i++)
    {
      fr->Tr1YStrips[i].SetQ(0);
    }
  
  // Deposit charge from every particle in the current event...
  unsigned int Xmax = 255;
  unsigned int Ymax = 255;

  for (unsigned int i=0; i<fr->Tr1Particles.size(); i++)
    {
      
      double x = fr->Tr1Particles[i].X(); 
      double y = fr->Tr1Particles[i].Y();
      double q = fr->Tr1Particles[i].Q();

      //cout << "Tr1 xgen= " << x << "   ygen= " << y <<  "   q= " << q << endl;
      //cout<< "Tr1 X Strip "<< int((x+45)/390) << " illuminated!" <<endl;
      
      // First the X Strips...
      unsigned int START_XSTRIP = int((x+45)/390) - 1;
      unsigned int END_XSTRIP   = int((x+45)/390) + 1;

      if (START_XSTRIP < 0)    START_XSTRIP = 0;
      if (START_XSTRIP > Xmax) START_XSTRIP = Xmax;
      if (END_XSTRIP < 0)      END_XSTRIP   = 0;
      if (END_XSTRIP > Xmax)   END_XSTRIP   = Xmax;

      double LEFT,RIGHT,BOTTOM,TOP;
      double Qinc;
    
      for(unsigned int j=START_XSTRIP; j<=END_XSTRIP; j++)
	{
	  LEFT   = fr->Tr1XStrips[j].XCenter() - 150;
	  RIGHT  = LEFT + 300;
	  BOTTOM = y - Sigma*2;
	  TOP    = y + Sigma*2;

	  if (BOTTOM < 0)       BOTTOM = 0;
	  if (TOP > 100000) TOP = 100000;
	  
	  for(double k=LEFT; k<RIGHT; k+=Delx)
	    {  
	      for(double l=BOTTOM; l<TOP; l+=Dely)
		{
		  Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
		  fr->Tr1XStrips[j].AddQ(Qinc);
		}	
	    }
	  //cout<<"Charge on Track 1 xstrip " << j << " is " << fr->Tr1XStrips[j].Q() << endl;
	}

      //cout<< "Tr1 Y Strip "<< int((y+45)/390) << " illuminated!" <<endl;
      unsigned int START_YSTRIP = int((y+45)/390) - 1;
      unsigned int END_YSTRIP   = int((y+45)/390) + 1;

      if (START_YSTRIP < 0)    START_YSTRIP = 0;
      if (START_YSTRIP > Ymax) START_YSTRIP = Ymax;
      if (END_YSTRIP < 0)      END_YSTRIP   = 0;
      if (END_YSTRIP > Ymax)   END_YSTRIP   = Ymax;

          
      for(unsigned int j=START_YSTRIP; j<=END_YSTRIP; j++)
	{
	  LEFT   = x-Sigma*2;
	  RIGHT  = x+Sigma*2;
	  BOTTOM = fr->Tr1YStrips[j].YCenter() - 150;
	  TOP    = BOTTOM + 300;

	  if (LEFT < 0)        LEFT = 0;
	  if (RIGHT > 100000)  RIGHT = 100000;
	  
	  for(double k=LEFT; k<RIGHT; k+=Delx)
	    {  
	      for(double l=BOTTOM; l<TOP; l+=Dely)
		{
		  Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
		  fr->Tr1YStrips[j].AddQ(Qinc);
		}	
	    }
	  //cout<<"Charge on Track 1 ystrip " << j << " is " << fr->Tr1YStrips[j].Q() << endl;
	}	
      

    }
}


      


