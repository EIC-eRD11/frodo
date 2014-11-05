#include "Ringfinder.h"
#include "frodo.h"
#include "AParticle.h"
#include "ARing.h"
#include "Coordinates.h"

#include "TFile.h"
#include "TObject.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TVector3.h"
#include "TMath.h"

#include <iostream>

using namespace std;

//Define a function which computes the center of the ring from 3 points.
//X:
double RFindX (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
  double D = 2*(X1*(Y2-Y3)+X2*(Y3-Y1)+X3*(Y1-Y2));
  double x = ((X1*X1+Y1*Y1)*(Y2-Y3)+(X2*X2+Y2*Y2)*(Y3-Y1)+(X3*X3+Y3*Y3)*(Y1-Y2))/D;
  return x;
}

//Y:
double RFindY (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
  double D = 2*(X1*(Y2-Y3)+X2*(Y3-Y1)+X3*(Y1-Y2));
  double y = ((X1*X1+Y1*Y1)*(X3-X2)+(X2*X2+Y2*Y2)*(X1-X3)+(X3*X3+Y3*Y3)*(X2-X1))/D;
  return y;
}

//Define a function which computes the radius of the ring from 3 points.
double RFindR (TVector3 P1, TVector3 P2, TVector3 P3)
{
  double r = ((P1-P2).Mag()*(P2-P3).Mag()*(P3-P1).Mag())/(2*((P1-P2).Cross(P2-P3)).Mag());
  return r;
}

TH3D *HoughF = new TH3D ("HoughF","HoughF",500,-50000,50000,500,-50000,50000,500,0,50000);;
TH1D *xerr, *yerr, *rerr;

void Ringfinder()
{
     static int first=1;
     if (first)
       {
         first = 0;      
	 xerr = new TH1D ("xerr","xerr",200,-5000,5000);
         yerr = new TH1D ("yerr","yerr",200,-5000,5000);
         rerr = new TH1D ("rerr","rerr",200,-3000,3000);
       }
  
  HoughF->Reset();
  
  frodo *fr = frodo::instance();
  fr->Y1.clear();
  fr->X1.clear();
  fr->Y2.clear();
  fr->X2.clear();
  fr->Y3.clear();
  fr->X3.clear();
  fr->Y4.clear();
  fr->X4.clear();
  fr->AllX.clear();
  fr->AllY.clear();
  fr->PseudoPoints.clear();
  fr->J1_PseudoPoints.clear();
  fr->J2_PseudoPoints.clear();
  fr->J3_PseudoPoints.clear();
  fr->J4_PseudoPoints.clear();
  fr->CX.clear();
  fr->CY.clear();
  
//   double Qx1,Qx2,Qx3,Qx4,Qy1,Qy2,Qy3,Qy4;
  
//   Qx1=Qx2=Qx3=Qx4=Qy1=Qy2=Qy3=Qy4=0;
  
//   for(unsigned int i=0; i<60; i++)
//     {
//       Qx1 += fr->J1_XStrips[i].Q();
//       Qx2 += fr->J2_XStrips[i].Q();
//       Qx3 += fr->J3_XStrips[i].Q();
//       Qx4 += fr->J4_XStrips[i].Q();
//     }
//   for(unsigned int i=0; i<60; i++)
//     {
//       Qy1 += fr->J1_YStrips[i].Q();
//       Qy2 += fr->J2_YStrips[i].Q();
//       Qy3 += fr->J3_YStrips[i].Q();
//       Qy4 += fr->J4_YStrips[i].Q();
//     }
  
//   double Qtot1 = Qx1+Qy1;
//   double Qtot2 = Qx2+Qy2;
//   double Qtot3 = Qx3+Qy3;
//   double Qtot4 = Qx4+Qy4;

  //J1 section:-------------------------------------------------------------------
  for(unsigned int i=0; i<60; i++)
    {
      double T = fr->J1_YStrips[i].Q();
      //double Qfrac = T/Qtot1*100;
            
      if(T>=4000)
 	{
	  fr->Y1.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
	  //fr->AllY.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
 	}
    }

  for(unsigned int j=0; j<60; j++)
    {
      double T = fr->J1_XStrips[j].Q();
      //double Qfrac = T/Qtot1*100;
      //double Qfrac = exp(-T/20)*100;
      
      if(T>=4000)
 	{
	  fr->X1.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
	  //fr->AllX.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
 	}
      
    }

  
  //J2 section:----------------------------------------------------------------
  //cout<<"J2: "<<endl;

  for(unsigned int i=0; i<60; i++)
    {
      double T = fr->J2_YStrips[i].Q();
      //double Qfrac = T/Qtot2*100;
      //double Qfrac = exp(-T/20)*100;

      if(T>=4000)
 	{
	  fr->Y2.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	  //fr->AllY.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	}
    }

  for(unsigned int j=0; j<60; j++)
    {
      double T = fr->J2_XStrips[j].Q();
      //double Qfrac = T/Qtot2*100;
      //double Qfrac = exp(-T/20)*100;
      
      if(T>=4000)
 	{
	  fr->X2.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
	  //fr->AllX.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
 	}
    }
  
  //J3 section:----------------------------------------------------------------

  for(unsigned int i=0; i<60; i++)
    {  
      double T = fr->J3_YStrips[i].Q();
      //double Qfrac = T/Qtot3*100;
      //double Qfrac = exp(-T/20)*100;
      
      if(T>=4000)
 	{
	  fr->Y3.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
	  //fr->AllY.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
 	}
    }

  for(unsigned int j=0; j<60; j++)
    {      
      double T = fr->J3_XStrips[j].Q();
      //double Qfrac = T/Qtot3*100;
      //double Qfrac = exp(-T/20)*100;
      
      if(T>=4000)
 	{
	  fr->X3.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	  //fr->AllX.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	}
    }

  //J4 section:-----------------------------------------------------------------
  for(unsigned int i=0; i<60; i++)
    {      
      double T = fr->J4_YStrips[i].Q();
      //double Qfrac = T/Qtot4*100;
      //double Qfrac = exp(-T/20)*100;
      
      if(T>=4000)
 	{
	  fr->Y4.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
	  //fr->AllY.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
 	}
    }

  for(unsigned int j=0; j<60; j++)
    {    
      double T = fr->J4_XStrips[j].Q();
      //double Qfrac = T/Qtot4*100;
      //double Qfrac = exp(-T/20)*100;
      
      if(T>=4000)
 	{
	  fr->X4.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
	}
    }

  //Finding the ring:----------------------------------------------------------------------------------
  
    
//Forming J1234 PseudoPoints:
  for(unsigned int s=0; s<fr->Y1.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X1.size(); ps++)
	{
	  fr->J1_PseudoPoints.push_back(TVector3(fr->X1[ps].Cor(),fr->Y1[s].Cor(),0));
	}
    }
 
  for(unsigned int s=0; s<fr->Y2.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X2.size(); ps++)
	{
	  fr->J2_PseudoPoints.push_back(TVector3(fr->X2[ps].Cor(),fr->Y2[s].Cor(),0));
	}
    }

  for(unsigned int s=0; s<fr->Y3.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X3.size(); ps++)
	{
	  fr->J3_PseudoPoints.push_back(TVector3(fr->X3[ps].Cor(),fr->Y3[s].Cor(),0));
	}
    }

  for(unsigned int s=0; s<fr->Y4.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X4.size(); ps++)
	{
	  fr->J4_PseudoPoints.push_back(TVector3(fr->X4[ps].Cor(),fr->Y4[s].Cor(),0));
	}
    }
 
  //Selecting 3 PseudoPoints in three different quadrants:
  //J1,J2,J3:
  if(fr->J1_PseudoPoints.size() >= 1 && fr->J2_PseudoPoints.size() >= 1 && fr->J3_PseudoPoints.size() >= 1)
    {
      for(unsigned int i=0; i<fr->J1_PseudoPoints.size(); i++)
	{
	  for(unsigned int j=0; j<fr->J2_PseudoPoints.size(); j++)
	    {
	      for(unsigned int k=0; k<fr->J3_PseudoPoints.size(); k++)
		{
		  
		  double Rad  = RFindR(fr->J1_PseudoPoints[i],fr->J2_PseudoPoints[j],fr->J3_PseudoPoints[k]);
		  double Xcen = RFindX(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J3_PseudoPoints[k].X(),fr->J3_PseudoPoints[k].Y());
		  double Ycen = RFindY(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J3_PseudoPoints[k].X(),fr->J3_PseudoPoints[k].Y());
		  HoughF->Fill(Xcen,Ycen,Rad);
		}
	    }
	}
    }
      
  //J1,J2,J4:
  if(fr->J1_PseudoPoints.size() >= 1 && fr->J2_PseudoPoints.size() >= 1 && fr->J4_PseudoPoints.size() >= 1)
    {
      for(unsigned int i=0; i<fr->J1_PseudoPoints.size(); i++)
	{
	  for(unsigned int j=0; j<fr->J2_PseudoPoints.size(); j++)
	    {
	      for(unsigned int k=0; k<fr->J4_PseudoPoints.size(); k++)
		{
		  double Rad  = RFindR(fr->J1_PseudoPoints[i],fr->J2_PseudoPoints[j],fr->J4_PseudoPoints[k]);
		  double Xcen = RFindX(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  double Ycen = RFindY(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  HoughF->Fill(Xcen,Ycen,Rad);
		}
	    }
	}
    }
  
  //J1,J3,J4:
  if(fr->J1_PseudoPoints.size() >= 1 && fr->J3_PseudoPoints.size() >= 1 && fr->J4_PseudoPoints.size() >= 1)
    {
      for(unsigned int i=0; i<fr->J1_PseudoPoints.size(); i++)
	{
	  for(unsigned int j=0; j<fr->J3_PseudoPoints.size(); j++)
	    {
	      for(unsigned int k=0; k<fr->J4_PseudoPoints.size(); k++)
		{
		  double Rad  = RFindR(fr->J1_PseudoPoints[i],fr->J3_PseudoPoints[j],fr->J4_PseudoPoints[k]);
		  double Xcen = RFindX(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  double Ycen = RFindY(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  HoughF->Fill(Xcen,Ycen,Rad);
		}
	    }
	}
    }
  
  //J2,J3,J4;
  if(fr->J2_PseudoPoints.size() >= 1 && fr->J3_PseudoPoints.size() >= 1 && fr->J4_PseudoPoints.size() >= 1)
    {
      for(unsigned int i=0; i<fr->J2_PseudoPoints.size(); i++)
	{
	  for(unsigned int j=0; j<fr->J3_PseudoPoints.size(); j++)
	    {
	      for(unsigned int k=0; k<fr->J4_PseudoPoints.size(); k++)
		{
		  double Rad  = RFindR(fr->J2_PseudoPoints[i],fr->J3_PseudoPoints[j],fr->J4_PseudoPoints[k]);
		  double Xcen = RFindX(fr->J2_PseudoPoints[i].X(),fr->J2_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  double Ycen = RFindY(fr->J2_PseudoPoints[i].X(),fr->J2_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  HoughF->Fill(Xcen,Ycen,Rad);
		}
	    }
	}
    }

  /*
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!DO NOT ERASE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //Forming PseudoPoints:
  for(unsigned int ps=0; ps<fr->AllX.size(); ps++)
    {
      for(unsigned int s=0; s<fr->AllY.size(); s++)
	{
	   fr->PseudoPoints.push_back(TVector3(fr->AllX[ps].Cor(),fr->AllY[s].Cor(),0));
	}
    }
    
  //Full Combinatorial:
   for(unsigned int i=0; i<fr->PseudoPoints.size()-2; i++)
     {
       for(unsigned int j=i+1; j<fr->PseudoPoints.size()-1; j++)
 	{
 	  for(unsigned int k=j+1; k<fr->PseudoPoints.size(); k++)
 	    {
 	      double Rad = RFindR(fr->PseudoPoints[i],fr->PseudoPoints[j],fr->PseudoPoints[k]);
 	      double Xcen = RFindX(fr->PseudoPoints[i].X(),fr->PseudoPoints[i].Y(),fr->PseudoPoints[j].X(),fr->PseudoPoints[j].Y(),fr->PseudoPoints[k].X(),fr->PseudoPoints[k].Y());
 	      double Ycen = RFindY(fr->PseudoPoints[i].X(),fr->PseudoPoints[i].Y(),fr->PseudoPoints[j].X(),fr->PseudoPoints[j].Y(),fr->PseudoPoints[k].X(),fr->PseudoPoints[k].Y());
 	      HoughF->Fill(Xcen,Ycen,Rad);
 	      HoughFxy->Fill(Xcen,Ycen);
 	      HoughFyr->Fill(Ycen,Rad);
 	      HoughFxr->Fill(Xcen,Rad);
	      }
 	}
     }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  */      
  int xbin, ybin, zbin;
  xbin=0; ybin=0; zbin=0;
  HoughF->GetMaximumBin(xbin, ybin, zbin);
  // cout << "xbin= " << xbin << " ybin= " << ybin << " zbin= " << zbin << endl;

  TAxis *xaxis = HoughF->GetXaxis();  
  double Xrec=xaxis->GetBinCenter(xbin);
  //cout<<"Xrec= "<< Xrec <<endl;

  TAxis *yaxis = HoughF->GetYaxis();  
  double Yrec=yaxis->GetBinCenter(ybin);
  //cout<<"Yrec= "<< Yrec <<endl;

  TAxis *zaxis = HoughF->GetZaxis();  
  double Rrec=zaxis->GetBinCenter(zbin);
  //cout<<"Rrec= "<< Rrec <<endl;

   double Xerr = fr->CX[0].Cor()-Xrec;  
   double Yerr = fr->CY[0].Cor()-Yrec;  
   double Rerr = fr->Ring[0].R()-Rrec;  

//  if(fabs(Xerr) < 3*fr->Ring[0].SigmaX() && fabs(Yerr) < 3*fr->Ring[0].SigmaY() && fabs(Rerr) < 3*fr->Ring[0].SigmaR()) fr->Nsuc.push_back(1);
       
//    double Xdif = fabs(fr->Ring[0].Xmean())-fabs(Xerr); //cout<<"Xdif= " <<Xdif<<endl;
//    double Ydif = fabs(fr->Ring[0].Ymean())-fabs(Yerr); //cout<<"Ydif= " <<Ydif<<endl;
//    double Rdif = fabs(fr->Ring[0].Rmean())-fabs(Rerr); //cout<<"Rdif= " <<Rdif<<endl;

//    if(fabs(Xdif) < 3*fr->Ring[0].SigmaX() && fabs(Ydif) < 3*fr->Ring[0].SigmaY() && fabs(Rdif) < 3*fr->Ring[0].SigmaR()) fr->Nsuc_off.push_back(1);

   xerr->Fill(Xerr);
   yerr->Fill(Yerr);
   rerr->Fill(Rerr);
   
}

