#include "frodo.h"

#include "AParticle.h"
#include "AStrip.h"
#include "APadStrip.h"
//#include "ABlob.h"
//#include "ACluster.h"

#include "TVector3.h"
#include <iostream>
//#include <algorithm>

using namespace std;

frodo *frodo::__instance=0;

//bool StripSort(const AStrip& s1, const AStrip& s2);

//frodo::frodo(double Xsp, double Ysp, double Pch)
frodo::frodo()
{
  cout << "Creating a new frodo";
  cout << endl;


  //  Here is the HBD in four sections (J1...J4):

  //  J1 section:
  
  J1_XStrips.clear();
  J1_YStrips.clear();
  
  double XLeft = -49100;
  double XRight= -1000;
  double YTop = -875;
  double YBottom = -1425;

  J1_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); // special case...
  for (int i=0; i<59; i++)
    {
      YTop = YBottom-400;
      YBottom = YTop - 400;
      J1_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
    }
  
  double XL = -1900;
  double XR = -1200;
  double YB = -48975;
  double YT = -1475;
  
  J1_XStrips.push_back(APadStrip(XL,YB,XR,YT));  
  for (int j=0; j<59; j++)
    {
      XR = XL - 100;
      XL = XR - 700;
      J1_XStrips.push_back(APadStrip(XL,YB,XR,YT));
    }
  
  //  J2 section:
  J2_XStrips.clear();
  J2_YStrips.clear();

  XLeft = 900;
  XRight= XLeft+48100;
  YTop = -875;
  YBottom = -1425;
  J2_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); // special case...
  for (int i=0; i<59; i++)
    {
      YTop = YBottom-400;
      YBottom = YTop - 400;
      J2_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
    }

  XL = 48100;
  XR = XL + 700;
  YB = -48975;
  YT = -1475;
  J2_XStrips.push_back(APadStrip(XL,YB,XR,YT));
  for (int j=0; j<59; j++)
    {
      XR = XL - 100;
      XL = XR - 700;
      J2_XStrips.push_back(APadStrip(XL,YB,XR,YT));
    }

  //  J3 section:
  J3_XStrips.clear();
  J3_YStrips.clear();

  XLeft = -49100;
  XRight= XLeft+48100;
  YTop = 1475;
  YBottom = 900;
  J3_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); // special case...
  for (int i=0; i<59; i++)
    {
      YBottom = YTop + 400;
      YTop = YBottom + 400;
      J3_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
    }

  XL = -49100;
  XR = -48400;
  YB = 1525;
  YT = 49025;

  J3_XStrips.push_back(APadStrip(XL,YB,XR,YT));
  for (int j=0; j<59; j++)
    {
      XL = XR + 100;
      XR = XL + 700;
      J3_XStrips.push_back(APadStrip(XL,YB,XR,YT));
    }
  
  //  J4 section:
  XLeft = 950;
  XRight= XLeft+48100;
  YTop = 1475;
  YBottom = 900;
  J4_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); // special case...
  for (int i=0; i<59; i++)
    {
      YBottom = YTop + 400;
      YTop = YBottom + 400;
      J4_YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
    }

  XL = 950;
  XR = 1650;
  YB = 1525;
  YT = 49025;
  J4_XStrips.push_back(APadStrip(XL,YB,XR,YT));
  for (int j=0; j<59; j++)
    {
      XL = XR + 100;
      XR = XL + 700;
      J4_XStrips.push_back(APadStrip(XL,YB,XR,YT));
    }


  //Setting up the Tracker1 strips.
  XL = 0;
  XR = XL+300;
  YT = 100000;
  YB = 0;
  Tr1XStrips.push_back(AStrip(XL,YB,XR,YT)); 
  for (int i=0; i<255; i++)
    {
      XL = XR + 90;
      XR = XL + 300;
      Tr1XStrips.push_back(AStrip(XL,YB,XR,YT)); 
    }

  XLeft   = 0;
  XRight  = 100000;
  YBottom = 0;
  YTop = YBottom + 300;
  Tr1YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
  for (int i=0; i<255; i++)
    {
      YBottom  = YTop + 90;
      YTop = YBottom + 300;
      Tr1YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
    }

  //Setting up the Tracker2 strips.
  XL = 0;
  XR = XL+300;
  YT = 100000;
  YB = 0;
  Tr2XStrips.push_back(AStrip(XL,YB,XR,YT)); 
  for (int i=0; i<255; i++)
    {
      XL = XR + 90;
      XR = XL + 300;
      Tr2XStrips.push_back(AStrip(XL,YB,XR,YT)); 
    }

 
  XLeft   = 0;
  XRight  = 100000;
  YBottom = 0;
  YTop = YBottom + 300;
  Tr2YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
  for (int i=0; i<255; i++)
    {
      YBottom  = YTop + 90;
      YTop = YBottom + 300;
      Tr2YStrips.push_back(AStrip(XLeft,YBottom,XRight,YTop)); 
    }




}








  
/*
  //  Set up the strips...
  theXStrips.clear();
  for (double x=0; x<Xspace; x+=Pitch)
    {
      theXStrips.push_back(AStrip(x+Pitch/6.0));
    }
  
  theYStrips.clear();
  for (double y=0; y<Yspace; y+=Pitch)
    {
      theYStrips.push_back(AStrip(y+Pitch/2.0));
    }
  
  theUStrips.clear();
  for (double y=0; y<Yspace; y+=Pitch)
    {
      theUStrips.push_back(AStrip( (y+Pitch/2.0) - (Pitch*5/6.0) ));
    }
  for (double x=Pitch; x<Xspace; x+=Pitch)
    {
      theUStrips.push_back(AStrip( (Pitch/2.0) - (x + Pitch*5/6.0) ));
    }
  sort(theUStrips.begin(), theUStrips.end(), StripSort);

  //theParticles.clear();
  theXBlobs.clear();
  theYBlobs.clear();
  theUBlobs.clear();
  theClusters.clear();
}
*/
/*
void frodo::Report()
{
  cout << "Frodo Object reporting for Duty!" << endl;

  cout << "SPACE -----------------------------------------------------------" << endl;
  cout << " Xspace = " << Xspace;
  cout << " Yspace = " << Yspace;
  cout << " Pitch = "  << Pitch;
  cout << endl;

  cout << "PARTICLES -------------------------------------------------------" << endl;
  cout << "We presently have " << theParticles.size() << " particles." << endl;
  for (unsigned int i=0; i< theParticles.size(); i++)
    {
      cout << i ;
      cout << " X: " << theParticles[i].X();
      cout << " Y: " << theParticles[i].Y();
      cout << " Q: " << theParticles[i].Q();
      cout << endl;
    }

 
  cout << "STRIPS -------------------------------------------------------" << endl;
  cout << "Let's look at the X strips: " << endl;
  cout << "Their size is " << theXStrips.size() << endl;
  cout << "Their Non-zero charges are:" << endl;
  for (unsigned int i=0; i< theXStrips.size(); i++)
    {
      if (theXStrips[i].Q() > 0)
	{
	  cout << i << " ";
	  cout << "Center: " << theXStrips[i].Center() << " ";
	  cout << "Charge: " << theXStrips[i].Q()      << " ";
	  cout << endl;
	}
    }


  cout << "Let's look at the Y strips: " << endl;
  cout << "Their size is " << theYStrips.size() << endl;
  cout << "Their Non-zero charges are:" << endl;
  for (unsigned int i=0; i< theYStrips.size(); i++)
    {
      if (theYStrips[i].Q() > 0)
	{
	  cout << i << " ";
	  cout << "Center: " << theYStrips[i].Center() << " ";
	  cout << "Charge: " << theYStrips[i].Q()      << " ";
	  cout << endl;
	}
    }
  cout << endl;

  cout << "Let's look at the U strips: " << endl;
  cout << "Their size is " << theUStrips.size() << endl;
  cout << "Their Non-zero charges are:" << endl;
  for (unsigned int i=0; i< theUStrips.size(); i++)
    {
      if (theUStrips[i].Q() > 0)
	{
	  cout << i << " ";
	  cout << "Center: " << theUStrips[i].Center() << " ";
	  cout << "Charge: " << theUStrips[i].Q()      << " ";
	  cout << endl;
	}
    }

  cout << "BLOBS -------------------------------------------------------" << endl;
  cout << "We presently have " << theXBlobs.size() << " X blobs." << endl;
  for (unsigned int i=0; i< theXBlobs.size(); i++)
    {
      cout << i ;
      cout << " Centroid: "      << theXBlobs[i].Centroid();
      cout << " Q: "             << theXBlobs[i].Q();
      cout << " Corr-Centroid: " << theXBlobs[i].CorrectedCentroid();
      cout << " Corr-Q: "        << theXBlobs[i].CorrectedQ();
      cout << endl;
    }

  cout << "We presently have " << theYBlobs.size() << " Y blobs." << endl;
  for (unsigned int i=0; i< theYBlobs.size(); i++)
    {
      cout << i ;
      cout << " Centroid: "      << theYBlobs[i].Centroid();
      cout << " Q: "             << theYBlobs[i].Q();
      cout << " Corr-Centroid: " << theYBlobs[i].CorrectedCentroid();
      cout << " Corr-Q: "        << theYBlobs[i].CorrectedQ();
      cout << endl;
    }

  cout << "We presently have " << theUBlobs.size() << " U blobs." << endl;
  for (unsigned int i=0; i< theUBlobs.size(); i++)
    {
      cout << i ;
      cout << " Centroid: "      << theUBlobs[i].Centroid();
      cout << " Q: "             << theUBlobs[i].Q();
      cout << " Corr-Centroid: " << theUBlobs[i].CorrectedCentroid();
      cout << " Corr-Q: "        << theUBlobs[i].CorrectedQ();
      cout << endl;
    }

  cout << "CLUSTERS -------------------------------------------------------" << endl;
  cout << "We presently have " << theClusters.size() << " clusters." << endl;
  for (unsigned int i=0; i< theClusters.size(); i++)
    {
      cout << i ;
      cout << " Best X: " << theClusters[i].BestX();
      cout << " Best Y: " << theClusters[i].BestY();
      cout << " Best Q: " << theClusters[i].BestQ();
      cout << endl;
    }
}
*/



 /*  
bool StripSort(const AStrip& s1, const AStrip& s2)
{
  AStrip S1 = s1;
  AStrip S2 = s2;

  double a = S1.Center();
  double b = S2.Center();

  return (a < b);
}
*/

