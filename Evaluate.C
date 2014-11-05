#include "frodo.h"
#include "AParticle.h"
#include "AStrip.h"
#include "ABlob.h"
#include "ACluster.h"

#include "Riostream.h"
#include <iostream>
#include <iomanip>

#include <getClass.h>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

const double Sigma = 130;
//const double Pi = 3.1415926;

TH1D *asym;
//TH1D *x_collect_ratio, *y_collect_ratio, *u_collect_ratio;
//TH1D *corqx, *corqy, *corqu;

//TH2D *phasorx, *phasory, *phasoru;
//TH2D *qphasorx, *qphasory, *qphasoru;
//TH2D *phasorX, *phasorY, *phasorU;
//TH2D *qphasorX, *qphasorY, *qphasorU;
//TH2D *corphasorX, *corphasorY, *corphasorU;
//TH2D *corqphasorX, *corqphasorY, *corqphasorU;
//TH2D *xblob_chg_ratio, *yblob_chg_ratio, *ublob_chg_ratio;
//TH2D *qx_vs_qy, *qy_vs_qu, *qu_vs_qx;
//TH3D *xyu;

void Evaluate()
{
  static int first=1;
  if (first)
    {
      first = 0;
      
      asym = new TH1D ("asym","Asymmetry",200,-2,2);
      // corqx = new TH1D ("corqx","corqx",200,0,2);
//       corqy = new TH1D ("corqy","corqy",200,0,2);
//       corqu = new TH1D ("corqu","corqu",200,0,2);

//       phasorx = new TH2D ("phasorx", "phasorx",300,0,300,900,-500,500);
//       phasory = new TH2D ("phasory", "phasory",300,0,300,900,-500,500);
//       phasoru = new TH2D ("phasoru", "phasoru",300,0,300,900,-500,500);

//       phasorX = new TH2D ("phasorX", "phasorX",300,0,300,900,-500,500);
//       phasorY = new TH2D ("phasorY", "phasorY",300,0,300,900,-500,500);
//       phasorU = new TH2D ("phasorU", "phasorU",600,0,300,300,-500,500);
      
//       qphasorx = new TH2D ("qphasorx", "qphasorx",300,0,300,300,0.1,0.5);
//       qphasory = new TH2D ("qphasory", "qphasory",300,0,300,300,0.1,0.5);
//       qphasoru = new TH2D ("qphasoru", "qphasoru",300,0,300,300,0.1,0.5);

//       qphasorX = new TH2D ("qphasorX", "qphasorX",300,0,300,300,0.1,0.5);
//       qphasorY = new TH2D ("qphasorY", "qphasorY",300,0,300,300,0.1,0.5);
//       qphasorU = new TH2D ("qphasorU", "qphasorU",600,-300,300,300,0.1,0.5);

//       corphasorX = new TH2D ("corphasorX", "corphasorX",300,0,300,900,-500,500);
//       corphasorY = new TH2D ("corphasorY", "corphasorY",300,0,300,900,-500,500);
//       corphasorU = new TH2D ("corphasorU", "corphasorU",600,-300,300,900,-500,500);

//       corqphasorX = new TH2D ("corqphasorX", "corqphasorX",300,0,300,900,-500,500);
//       corqphasorY = new TH2D ("corqphasorY", "corqphasorY",300,0,300,900,-500,500);
//       corqphasorU = new TH2D ("corqphasorU", "corqphasorU",600,-300,300,900,-500,500);
      //qphasorx_tot = new TH2D ("qphasorx_tot", "qphasorx_tot",100,0,300,100,0,100000000);
      //qphasory_tot = new TH2D ("qphasory_tot", "qphasory_tot",100,0,300,100,0,100000000);

      // x_collect_ratio = new TH1D ("x_collect_ratio","x_collect_ratio",200,0,1);
//       y_collect_ratio = new TH1D ("y_collect_ratio","y_collect_ratio",200,0,1);
//       u_collect_ratio = new TH1D ("u_collect_ratio","u_collect_ratio",200,0,1);

//       xblob_chg_ratio = new TH2D ("xblob_chg_ratio", "xblob_chg_ratio",100,0,100000000,50,0,1);
//       yblob_chg_ratio = new TH2D ("yblob_chg_ratio", "yblob_chg_ratio",100,0,100000000,50,0,1);
//       ublob_chg_ratio = new TH2D ("ublob_chg_ratio", "ublob_chg_ratio",100,0,100000000,50,0,1);

//       qx_vs_qy = new TH2D ("qx_vs_qy","qx_vs_qy",100,0,100000000,100,0,100000000);
//       qy_vs_qu = new TH2D ("qy_vs_qu","qy_vs_qu",100,0,100000000,100,0,100000000);
//       qu_vs_qx = new TH2D ("qu_vs_qx","qu_vs_qx",100,0,100000000,100,0,100000000);

//       xyu = new TH3D ("xyu","qx_vs_qy_vs_qu",100,0,100000000,100,0,100000000,100,0,100000000);

      
    }


  frodo *fr = frodo::instance();

  double Qx=0;
  double Qy=0;
  for(unsigned int i=0; i<60; i++)
    {
      Qx += fr->J1_XStrips[i].Q() + fr->J2_XStrips[i].Q() + fr->J3_XStrips[i].Q() + fr->J4_XStrips[i].Q();          
      Qy += fr->J1_YStrips[i].Q() + fr->J2_YStrips[i].Q() + fr->J3_YStrips[i].Q() + fr->J4_YStrips[i].Q();          
    }
  
  double Qsum = Qx + Qy;
  double Qdif = Qx - Qy;
  asym->Fill(Qdif/Qsum);
  // double xgen = av->theParticles[0].X();
//   double xrec = av->theXBlobs[0].Centroid();
//   double Xrec = av->theXBlobs[0].CorrectedCentroid();

//   double ygen = av->theParticles[0].Y();
//   double yrec = av->theYBlobs[0].Centroid();
//   double Yrec = av->theYBlobs[0].CorrectedCentroid();

//   unsigned int phasex = (int(av->theParticles[0].X())) % int(av->Pitch);
//   unsigned int phasey = (int(av->theParticles[0].Y())) % int(av->Pitch);
//   int          phaseu = (int(av->theParticles[0].Y() - av->theParticles[0].X() )) % int(av->Pitch);
  //cout << "phaseu= " << phaseu << endl;

  /*
  if(av->theParticles[0].Y() > av->theParticles[0].X()) 
    {
      phaseu = (int(av->theParticles[0].Y() - av->theParticles[0].X() )) % int(av->Pitch);
      cout << "phaseu= " << phaseu <<endl;
    }
  else
    {
      phaseu = -((int(av->theParticles[0].X() - av->theParticles[0].Y() )) % int(av->Pitch));
      cout << "phaseu= " << phaseu <<endl;
    }
  */

  // unsigned int phaseX = (int(av->theXBlobs[0].Centroid())) % int(av->Pitch);
//   unsigned int phaseY = (int(av->theYBlobs[0].Centroid()))     % int(av->Pitch);
//   int          phaseU = (int(av->theUBlobs[0].Centroid()))     % int(av->Pitch);

//   unsigned int correctedphaseX = int(av->theXBlobs[0].CorrectedCentroid()) % int(av->Pitch);
//   unsigned int correctedphaseY = int(av->theYBlobs[0].CorrectedCentroid()) % int(av->Pitch);
//   //cout << "phaseU= " << phaseU <<endl;
 
//   double qx = av->theXBlobs[0].Q();
//   double qy = av->theYBlobs[0].Q();
//   double qu = av->theUBlobs[0].Q();

//   double qtot = qx + qy + qu;
//   double qgen = 2*3.1416*Sigma*Sigma*av->theParticles[0].Q();

//   double correctedqx = av->theXBlobs[0].CorrectedQ();
//   double correctedqy = av->theYBlobs[0].CorrectedQ();
//   //double correctedqu = av->theUBlobs[0].CorrectedQ();

//   xerr   ->Fill(xgen - xrec); 
//   yerr   ->Fill(ygen - yrec); 

//   phasorx->Fill(phasex,xgen-xrec);
//   phasory->Fill(phasey,ygen-yrec);
//   phasoru->Fill(phaseu,ygen-xgen-yrec+xrec);
  
//   phasorX->Fill(phaseX,xgen-xrec);
//   phasorY->Fill(phaseY,ygen-yrec);
//   phasorU->Fill(phaseU,ygen-xgen-Yrec+Xrec);

//   corphasorX->Fill(correctedphaseX,xgen-Xrec);
//   corphasorY->Fill(correctedphaseY,ygen-Yrec);
//   //corphasorU->Fill(correctedphaseU,ygen-Yrec-xgen+Xrec);

//   corqx->Fill(correctedqx/qtot);
//   corqy->Fill(correctedqy/qtot);
//   //corqu->Fill(correctedqu/qtot);

//   x_collect_ratio->Fill(qx/qgen);
//   y_collect_ratio->Fill(qy/qgen);
//   u_collect_ratio->Fill(qu/qgen);

//   xblob_chg_ratio->Fill(qtot,qx/qtot);
//   yblob_chg_ratio->Fill(qtot,qy/qtot);
//   ublob_chg_ratio->Fill(qtot,qu/qtot);
  
//   qx_vs_qy->Fill(qy,qx);
//   qy_vs_qu->Fill(qu,qy);
//   qu_vs_qx->Fill(qx,qu);

//   xyu->Fill(qx,qy,qu);

//   qphasorx->Fill(phasex,qx/qtot);
//   qphasory->Fill(phasey,qy/qtot);
//   qphasoru->Fill(phaseu,qu/qtot);

//   qphasorX->Fill(correctedphaseX,qx/qtot);
//   qphasorY->Fill(correctedphaseY,qy/qtot);
  //qphasorU->Fill(correctedphaseU,qu/qtot);

  
  //av->Report();
 
  
  
  

}
