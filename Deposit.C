#include "Deposit.h"
#include "frodo.h"
#include "AParticle.h"
#include "APadStrip.h"
#include "AStrip.h"

#include "TMath.h"
#include <iostream>

using namespace std;

const double Delx  = 10; 
const double Dely  = 10;
const double Sigma = 130;

void Deposit()
{
  frodo *fr = frodo::instance();

  //-------------------------------------------------------------------------------------
  // Zero out the charge from the prior event...
  //J1 section:
  for (unsigned int i=0; i<fr->J1_XStrips.size(); i++)
    {
      fr->J1_XStrips[i].SetQ(0);
    }
  for (unsigned int i=0; i<fr->J1_YStrips.size(); i++)
    {
      fr->J1_YStrips[i].SetQ(0);
    }

  //J2 section:
  for (unsigned int i=0; i<fr->J2_XStrips.size(); i++)
    {
      fr->J2_XStrips[i].SetQ(0);
    }
  for (unsigned int i=0; i<fr->J2_YStrips.size(); i++)
    {
      fr->J2_YStrips[i].SetQ(0);
    }

   //J3 section:
  for (unsigned int i=0; i<fr->J3_XStrips.size(); i++)
    {
      fr->J3_XStrips[i].SetQ(0);
    }
  for (unsigned int i=0; i<fr->J3_YStrips.size(); i++)
    {
      fr->J3_YStrips[i].SetQ(0);
    }

   //J4 section:
  for (unsigned int i=0; i<fr->J4_XStrips.size(); i++)
    {
      fr->J4_XStrips[i].SetQ(0);
    }
  for (unsigned int i=0; i<fr->J4_YStrips.size(); i++)
    {
      fr->J4_YStrips[i].SetQ(0);
    }

  //-------------------------------------------------------------------------------------------
  
  // Deposit charge from every particle in the current event...
  //unsigned int Xmax = 119;
  //unsigned int Ymax = 119;

  for (unsigned int i=0; i<fr->HBDParticles.size(); i++)
    {
      
      double x = fr->HBDParticles[i].X(); 
      double y = fr->HBDParticles[i].Y();
      double q = fr->HBDParticles[i].Q();

      //cout << "HBD xgen= " << x << "   ygen= " << y <<  "   q= " << q << endl;
      
      // J4 section:-----------------------------------------------------------------------------------
      // First Y Strips;
      
      if(x>500 && y>675)
	{
	  //cout <<"Detected position in J4!"<<endl;
	  //cout<< "Y Strip " << int((y-1125+250)/800) << " illuminated!"<<endl;
	  unsigned int START_YSTRIP = int((y-675-450/2+200)/800) - 2;
	  unsigned int END_YSTRIP   = int((y-675-450/2+200)/800) + 2;
	  
	  if (START_YSTRIP < 0)  START_YSTRIP = 0;
	  if (START_YSTRIP > 59) START_YSTRIP = 59;
	  if (END_YSTRIP < 0)    END_YSTRIP   = 0;
	  if (END_YSTRIP > 59)   END_YSTRIP   = 59;
	  
	  double LEFT,RIGHT,BOTTOM,TOP;
	  double Qinc;
	  
	  for(unsigned int j=START_YSTRIP; j<=END_YSTRIP; j++)
	    {
	      LEFT   = x - Sigma*5;
	      RIGHT  = x + Sigma*5;
	      BOTTOM = fr->J4_YStrips[j].YCenter() - 200;
	      TOP    = BOTTOM + 400;
	      
	      if (LEFT < 950)     LEFT = 950;
	      if (RIGHT > 49050)  RIGHT = 49050;
	      
	      for(double k=LEFT; k<RIGHT; k+=Delx)
		{  
		  for(double l=BOTTOM; l<TOP; l+=Dely)
		    {
		      Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
		      fr->J4_YStrips[j].AddQ(Qinc);
		    }	
		}
	      //cout<<"Charge on J4 ystrip " << j << " is " << fr->J4_YStrips[j].Q()<<endl;
	    }

	  
	  // Then the X Strips...
	  //cout << "X Strip "<< int ((x-950+50)/800) << " illuminated!"<< endl;
	  unsigned int START_XSTRIP = int ((x-950+50)/800) - 3;
	  unsigned int END_XSTRIP   = int ((x-950+50)/800) + 3;
	  
	  if (START_XSTRIP < 0)  START_XSTRIP = 0;
	  if (START_XSTRIP > 59) START_XSTRIP = 59;
	  if (END_XSTRIP < 0)    END_XSTRIP   = 0;
	  if (END_XSTRIP > 59)   END_XSTRIP   = 59; 

	  if (START_YSTRIP < 1)  START_YSTRIP = 1;
	  if (START_YSTRIP > 58) START_YSTRIP = 58;
	  if (END_YSTRIP < 1)    END_YSTRIP   = 1;
	  if (END_YSTRIP > 58)   END_YSTRIP   = 58;
	  
	  for(unsigned int m=START_XSTRIP; m<=END_XSTRIP; m++)
	    {
	      for(unsigned int j=START_YSTRIP-1; j<=END_YSTRIP+1; j++)
		{
		  LEFT   = fr->J4_XStrips[m].XCenter()-350;
		  RIGHT  = LEFT + 700;
		  BOTTOM = fr->J4_YStrips[j].YCenter() + 250;
		  TOP    = BOTTOM + 300;
		  
		  for(double k=LEFT; k<RIGHT; k+=Delx)
		    {
		      for(double l=BOTTOM; l<TOP; l+=Dely)
			{
			  Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
			  fr->J4_XStrips[m].AddQ(Qinc);
			}
		    }
		}
	      //cout<<"Charge on J4 xstrip " << m << " is " << fr->J4_XStrips[m].Q() << endl;
	    }
	  
	}

      //J2 section:-------------------------------------------------------------------------------------
      else if(x>500 && y<-675)
	{
	  //cout <<"Detected position in J2!"<<endl;
	  //cout << "Y Strip "<< int(fabs(y+1075-250)/800) << " illuminated!"<< endl;
	  unsigned int START_YSTRIP = int(fabs(y+675+200-200)/800) - 2;
	  unsigned int END_YSTRIP   = int(fabs(y+675+200-200)/800) + 2;
	  
	  if (START_YSTRIP < 0)  START_YSTRIP = 0;
	  if (START_YSTRIP > 59) START_YSTRIP = 59;
	  if (END_YSTRIP < 0)    END_YSTRIP   = 0;
	  if (END_YSTRIP > 59)   END_YSTRIP   = 59;
	  
	  double LEFT,RIGHT,BOTTOM,TOP;
	  double Qinc;
	  
	  for(unsigned int j=START_YSTRIP; j<=END_YSTRIP; j++)
	    {
	      LEFT   = x - Sigma*5;
	      RIGHT  = x + Sigma*5;
	      BOTTOM = fr->J2_YStrips[j].YCenter() - 200;
	      TOP    = BOTTOM + 400;
	      
	      if (LEFT < 900)     LEFT = 900;
	      if (RIGHT > 49000)  RIGHT = 49000;
	      
	      for(double k=LEFT; k<RIGHT; k+=Delx)
		{  
		  for(double l=BOTTOM; l<TOP; l+=Dely)
		    {
		      Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
		      fr->J2_YStrips[j].AddQ(Qinc);
		    }	
		}
	      //cout<<"Charge on J2 ystrip " << j << " is " << fr->J2_YStrips[j].Q() << endl;	
	    }
	  
	  // Then the X Strips...
	  //cout << "X Strip "<< int (fabs(x-48100-900+200-50)/800) <<" illuminated!" <<endl;
	  unsigned int START_XSTRIP = int (fabs(x-48100-900+200-50)/800) - 3;
	  unsigned int END_XSTRIP   = int (fabs(x-48100-900+200-50)/800) + 3;
	  
	  if (START_XSTRIP < 0)  START_XSTRIP = 0;
	  if (START_XSTRIP > 59) START_XSTRIP = 59;
	  if (END_XSTRIP < 0)    END_XSTRIP   = 0;
	  if (END_XSTRIP > 59)   END_XSTRIP   = 59; 
	  
	  if (START_YSTRIP < 1)  START_YSTRIP = 1;
	  if (START_YSTRIP > 58) START_YSTRIP = 58;
	  if (END_YSTRIP < 1)    END_YSTRIP   = 1;
	  if (END_YSTRIP > 58)   END_YSTRIP   = 58;
	  
	  for(unsigned int m=START_XSTRIP; m<=END_XSTRIP; m++)
	    {
	      for(unsigned int j=START_YSTRIP-1; j<=END_YSTRIP+1; j++)
		{
		  LEFT   = fr->J2_XStrips[m].XCenter()-350;
		  RIGHT  = LEFT + 700;
		  BOTTOM = fr->J2_YStrips[j].YCenter() - 550;
		  TOP    = BOTTOM + 300;
		  
		  for(double k=LEFT; k<RIGHT; k+=Delx)
		    {
		      for(double l=BOTTOM; l<TOP; l+=Dely)
			{
			  Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
			  fr->J2_XStrips[m].AddQ(Qinc);
			}
		    }
		}
	      //cout<<"Charge on J2 xstrip " << m << " is " << fr->J2_XStrips[m].Q() << endl;
	    }
	}
      

      //J3 section:-------------------------------------------------------------------------------------
      else if(x<-500 && y>675)
	{
	  //cout <<"Detected position in J3!"<<endl;
	  //cout << "Y Strip "<< int((y-675-450/2+50)/800) <<" illuminated!" <<endl;
	  unsigned int START_YSTRIP = int((y-675-450/2+200)/800) - 2;
	  unsigned int END_YSTRIP   = int((y-675-450/2+200)/800) + 2;
	  
	  if (START_YSTRIP < 0)  START_YSTRIP = 0;
	  if (START_YSTRIP > 59) START_YSTRIP = 59;
	  if (END_YSTRIP < 0)    END_YSTRIP   = 0;
	  if (END_YSTRIP > 59)   END_YSTRIP   = 59;
	  
	  double LEFT,RIGHT,BOTTOM,TOP;
	  double Qinc;
	  
	  for(unsigned int j=START_YSTRIP; j<=END_YSTRIP; j++)
	    {
	      LEFT   = x - Sigma*5;
	      RIGHT  = x + Sigma*5;
	      BOTTOM = fr->J3_YStrips[j].YCenter() - 200;
	      TOP    = BOTTOM + 400;
	      
	      if (LEFT < -49100)  LEFT = -49100;
	      if (RIGHT > -1000)  RIGHT = -1000;
	      
	      for(double k=LEFT; k<RIGHT; k+=Delx)
		{  
		  for(double l=BOTTOM; l<TOP; l+=Dely)
		    {
		      Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
		      fr->J3_YStrips[j].AddQ(Qinc);
		    }	
		}
	      //cout<<"Charge on J3 ystrip " << j << " is " << fr->J3_YStrips[j].Q() << endl;
	    }
	  
	  // Then the X Strips...
	  //cout << "X Strip "<< int (fabs(x+49100+50)/800) <<" illuminated!" <<endl;
	  unsigned int START_XSTRIP = int (fabs(x+49100+50)/800) - 3;
	  unsigned int END_XSTRIP   = int (fabs(x+49100+50)/800) + 3;
	  
	  if (START_XSTRIP < 0)  START_XSTRIP = 0;
	  if (START_XSTRIP > 59) START_XSTRIP = 59;
	  if (END_XSTRIP < 0)    END_XSTRIP   = 0;
	  if (END_XSTRIP > 59)   END_XSTRIP   = 59; 

	  if (START_YSTRIP < 1)  START_YSTRIP = 1;
	  if (START_YSTRIP > 58) START_YSTRIP = 58;
	  if (END_YSTRIP < 1)    END_YSTRIP   = 1;
	  if (END_YSTRIP > 58)   END_YSTRIP   = 58;
	  
	  for(unsigned int m=START_XSTRIP; m<=END_XSTRIP; m++)
	    {
	      for(unsigned int j=START_YSTRIP-1; j<=END_YSTRIP+1; j++)
		{
		  LEFT   = fr->J3_XStrips[m].XCenter() - 350;
		  RIGHT  = LEFT + 700;
		  BOTTOM = fr->J3_YStrips[j].YCenter() + 250;
		  TOP    = BOTTOM + 300;
		  
		  for(double k=LEFT; k<RIGHT; k+=Delx)
		    {
		      for(double l=BOTTOM; l<TOP; l+=Dely)
			{
			  Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
			  fr->J3_XStrips[m].AddQ(Qinc);
			}
		    }
		}
	      //cout<<"Charge on J3 xstrip " << m << " is " << fr->J3_XStrips[m].Q() << endl;
	    }	  
	}
      
      //J1 section:------------------------------------------------------------------------------------
      else if(x<-500 && y<-675)
	{
	  //cout <<"Detected position in J1!"<<endl;
	  //cout << "Y Strip "<< int(fabs((y+1075)-250)/800) <<" illuminated"<<endl;
	  unsigned int START_YSTRIP = int(fabs(y+675+200-200)/800) - 2;
	  unsigned int END_YSTRIP   = int(fabs(y+675+200-200)/800) + 2;
	  
	  if (START_YSTRIP < 0)  START_YSTRIP = 0;
	  if (START_YSTRIP > 59) START_YSTRIP = 59;
	  if (END_YSTRIP < 0)    END_YSTRIP   = 0;
	  if (END_YSTRIP > 59)   END_YSTRIP   = 59;
	  
	  double LEFT,RIGHT,BOTTOM,TOP;
	  double Qinc;
	  
	  for(unsigned int j=START_YSTRIP; j<=END_YSTRIP; j++)
	    {
	      LEFT   = x - Sigma*5;
	      RIGHT  = x + Sigma*5;
	      BOTTOM = fr->J1_YStrips[j].YCenter() - 200;
	      TOP    = BOTTOM + 400;
	      
	      if (LEFT < -49100)  LEFT = -49100;
	      if (RIGHT > -1000)  RIGHT = -1000;
	      
	      for(double k=LEFT; k<RIGHT; k+=Delx)
		{  
		  for(double l=BOTTOM; l<TOP; l+=Dely)
		    {
		      Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
		      fr->J1_YStrips[j].AddQ(Qinc);
		    }	
		}
	      //cout<<"Charge on J1 Ystrip " << j << " is " << fr->J1_YStrips[j].Q() << endl;
	    }
	  
	  // Then the X Strips...
	  //cout << "X Strip "<< int (fabs(x+1000-50)/800) <<" illuminated"<<endl;
	  unsigned int START_XSTRIP = int (fabs(x+1200-50)/800) - 3;
	  unsigned int END_XSTRIP   = int (fabs(x+1200-50)/800) + 3;
  
	  if (START_XSTRIP < 0)  START_XSTRIP = 0;
	  if (START_XSTRIP > 59) START_XSTRIP = 59;
	  if (END_XSTRIP < 0)    END_XSTRIP   = 0;
	  if (END_XSTRIP > 59)   END_XSTRIP   = 59; 

	  if (START_YSTRIP < 1)  START_YSTRIP = 1;
	  if (START_YSTRIP > 58) START_YSTRIP = 58;
	  if (END_YSTRIP < 1)    END_YSTRIP   = 1;
	  if (END_YSTRIP > 58)   END_YSTRIP   = 58;
	  
	  for(unsigned int m=START_XSTRIP; m<=END_XSTRIP; m++)
	    {
	      for(unsigned int j=START_YSTRIP-1; j<=END_YSTRIP+1; j++)
		{
		  LEFT   = fr->J1_XStrips[m].XCenter() - 350;
		  RIGHT  = LEFT + 700;
		  BOTTOM = fr->J1_YStrips[j].YCenter() - 550;
		  TOP    = BOTTOM + 300;
		  
		  for(double k=LEFT; k<RIGHT; k+=Delx)
		    {
		      for(double l=BOTTOM; l<TOP; l+=Dely)
			{
			  Qinc = Delx*Dely*q*exp(-((k+Delx/2.0-x)*(k+Delx/2.0-x)+(l+Dely/2.0-y)*(l+Dely/2.0-y))/(2.0*Sigma*Sigma));
			  fr->J1_XStrips[m].AddQ(Qinc);
			}
		    }
		}
	      //cout<<"Charge on J1 xstrip " << m << " is " << fr->J1_XStrips[m].Q() << endl;
	    }
	  
	}

    }
}
