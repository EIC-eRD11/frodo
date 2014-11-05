#include "DiffyNon.h"
#include "frodo.h"
#include "ABlob.h"
#include "ACluster.h"

#include "TMath.h"

#include "Riostream.h"
#include <iostream>

//linear fit parameters for phasorX.
const double a1 = -8.20312;     //const;
const double b1 = 0.164045;     //slope;

const double a2 = -69.7995;
const double b2 = 0.211557;
  
//linear fit parameters for phasorY.
const double a3 = -36.3917;
const double b3 = 0.242582;

//Polynomial fit parameters for qphasorX.
const double c1 = 0.350361;
const double d1 = 2.35552*pow(10,-5);    
const double e1 = -3.12516*pow(10,-7);   

const double c2 = 0.28;
const double d2 = 0.000457355;
const double e2 = -7.5811*pow(10,-7);

//Polynomial fit parameters for qphasorY.
const double c3 = 0.335536;
const double d3 = 0.000143915;
const double e3 = -4.79997*pow(10,-7);

void DiffyNon()
{

  frodo *av = frodo::instance();

  //Correcting for position phase dependence.
  for (unsigned int i=0; i<av->theXBlobs.size(); i++)
    {
      unsigned int phaseX = (int(av->theXBlobs[i].Centroid())) % int(av->Pitch);
      
      if(phaseX > 0 && phaseX<= 200)
	{
	  //cout << "the XBlobs Centroid " << i << " is " << av->theXBlobs[i].Centroid() << endl;
	  av->theXBlobs[i].SetCorrectedCentroid (av->theXBlobs[i].Centroid()+a1+b1*phaseX);
	  
	  //cout << "the corrected XBlobs Centroid " << i << " is " << av->theXBlobs[i].CorrectedCentroid() << endl;
	}
      else
	{
	  //cout << "the XBlobs Centroid " << i << " is " << av->theXBlobs[i].Centroid() << endl;
	  av->theXBlobs[i].SetCorrectedCentroid (av->theXBlobs[i].Centroid()+a2+b2*phaseX);
	  //cout << "the corrected XBlobs Centroid " << i << " is " << av->theXBlobs[i].CorrectedCentroid() << endl;
	}
    }

  for (unsigned int j=0; j<av->theYBlobs.size(); j++)
    {
      unsigned int phaseY = (int(av->theYBlobs[j].Centroid())) % int(av->Pitch);

      //cout << "the YBlobs Centroid " << j << " is " << av->theYBlobs[j].Centroid() << endl;

      av->theYBlobs[j].SetCorrectedCentroid (av->theYBlobs[j].Centroid()+a3+b3*phaseY);

      //cout << "the corrected YBlobs Centroid " << j << " is " << av->theYBlobs[j].CorrectedCentroid() << endl;
      

    }

  //------------------------------------------------------------------------------------------------------------------------------------------

  //Correcting for Q phase dependence.
  for (unsigned int i=0; i<av->theXBlobs.size(); i++)
    {
      unsigned int correctedphaseX = (int(av->theXBlobs[i].CorrectedCentroid())) % int(av->Pitch);
      
      if(correctedphaseX > 0 && correctedphaseX <= 200)
	{
	  //cout << "Before: charge on XBlob "<< i << " is " << av->theXBlobs[i].Q() <<endl;
	  av->theXBlobs[i].SetCorrectedQ (av->theXBlobs[i].Q()/(c1+d1*correctedphaseX+e1*correctedphaseX*correctedphaseX));
	  //cout << "Corrected charge on XBlob " << i << " is " << av->theXBlobs[i].CorrectedQ() << endl;
	}
      else
	{
	  //cout << "Before: charge on XBlob "<< i << " is " << av->theXBlobs[i].Q() <<endl;
	  av->theXBlobs[i].SetCorrectedQ (av->theXBlobs[i].Q()/(c2+d2*correctedphaseX+e2*correctedphaseX*correctedphaseX));
	  //cout << "After: corrected charge on XBlob " << i << " is " << av->theXBlobs[i].CorrectedQ() << endl;
	}
    }

  for (unsigned int j=0; j<av->theYBlobs.size(); j++)
    {
      unsigned int correctedphaseY = (int(av->theYBlobs[j].CorrectedCentroid())) % int(av->Pitch);

      //cout << "Before: charge on YBlob "<< j << " is " << av->theYBlobs[j].Q() <<endl;
      av->theYBlobs[j].SetCorrectedQ (av->theYBlobs[j].Q()/(c3+d3*correctedphaseY+e3*correctedphaseY*correctedphaseY));
      
      //cout << "After: corrected charge on YBlob " << j << " is " << av->theYBlobs[j].CorrectedQ() << endl;      

    }



}
