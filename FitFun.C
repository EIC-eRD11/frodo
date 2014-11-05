#include "FitFun.h"
#include "frodo.h"
#include "AStrip.h"
#include "ABlob.h"
#include "ACluster.h"

#include "Riostream.h"
#include <iostream>

//linear fit parameters for phasorX.
const double a1 = -8.20312;
const double b1 = 0.164045;
const double a2 = -69.7995;
const double b2 = 0.211557;
  
//phasorY.
const double a3 = -36.3917;
const double b3 = 0.242582;

TF2 *xphifit = h->GetFunction("xphifit");


void FitFun()
{
  frodo *av = frodo::instance();

f
  Double_t chi2 = xphifit->GetChisquare();
  Double_t a1   = xphifit->GetParameter(0);
  Double_t b1   = xphifit->GetParameter(1);

  /*
  for (unsigned int i=0; i<av->theXBlobs.size(); i++)
    {
      unsigned int phaseX = (int(av->theXBlobs[i].Centroid())) % int(av->Pitch);

      if(av->theXBlobs[i].Centroid() > 0 && av->theXBlobs[i].Centroid() <= 200)
	{
	  cout << "the XBlobs Centroid " << i << " is " << av->theXBlobs[i].Centroid() << endl;
	  av->theXBlobs[i].Centroid() += a1+b1*phaseX;
	  cout << "the corrected XBlobs Centroid " << i << " is " << av->theXBlobs[i].Centroid() << endl;
	}
      else
	{
	  av->theXBlobs[i].Centroid() = av->theXBlobs[i].Centroid()+a2+b2*phaseX;
	  cout << "the corrected XBlobs Centroid " << i << " is " << av->theXBlobs[i].Centroid() << endl;
	}
    }

  for (unsigned int j=0; j<av->theYBlobs.size(); j++)
    {
      unsigned int phaseY = (int(av->theYBlobs[j].Centroid())) % int(av->Pitch);

      cout << "the YBlobs Centroid " << j << " is " << av->theYBlobs[j].Centroid() << endl;
      av->theYBlobs[j].Centroid() += a3+b3*phaseY;
      cout << "the corrected YBlobs Centroid " << j << " is " << av->theYBlobs[j].Centroid() << endl;
      //av->theXBlobs[i].Q() = av->theXBlobs[i].Q()/exp(a1+b1*)

    }
  */




}


Double_t delxphifit(Double_t *x, Double_t *par)
{
  Double_t fitval = par[0]+par[1]*x[0];
}

