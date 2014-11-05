#include "Drawing.h"
#include "AParticle.h"
#include "AStrip.h"
#include "APadStrip.h"
#include "frodo.h"
#include "Coordinates.h"

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TVector3.h"

#include "TCanvas.h"
#include "TBox.h"
#include "TMarker.h"
#include "TEllipse.h"
//#include "TObject.h"
#include "TMath.h"

#include <iostream>

using namespace std;

//Define a function which computes the center of the ring from 3 points.
//X:
double FindX (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
  double D = 2*(X1*(Y2-Y3)+X2*(Y3-Y1)+X3*(Y1-Y2));
  double x = ((X1*X1+Y1*Y1)*(Y2-Y3)+(X2*X2+Y2*Y2)*(Y3-Y1)+(X3*X3+Y3*Y3)*(Y1-Y2))/D;
  return x;
}

//Y:
double FindY (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
  double D = 2*(X1*(Y2-Y3)+X2*(Y3-Y1)+X3*(Y1-Y2));
  double y = ((X1*X1+Y1*Y1)*(X3-X2)+(X2*X2+Y2*Y2)*(X1-X3)+(X3*X3+Y3*Y3)*(X2-X1))/D;
  return y;
}

//Define a function which computes the radius of the ring from 3 points.
double FindR (TVector3 P1, TVector3 P2, TVector3 P3)
{
  double r = ((P1-P2).Mag()*(P2-P3).Mag()*(P3-P1).Mag())/(2*((P1-P2).Cross(P2-P3)).Mag());
  return r;
}

TH3D *Hough;
TH2D *Houghxy, *Houghxr, *Houghyr;
TH2D *Houghxy2, *Houghxr2, *Houghyr2;


void Drawing()
{
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
  
  //----------------------------------------------------------------------------------------------------

  TCanvas *HBD = new TCanvas("HBD","HBD Event Display",0,0,700,700);
  HBD->Range(-50000,-50000,50000,50000);

    
   double Qx1,Qx2,Qx3,Qx4,Qy1,Qy2,Qy3,Qy4;

   Qx1=Qx2=Qx3=Qx4=Qy1=Qy2=Qy3=Qy4=0;
  
   for(unsigned int i=0; i<60; i++)
     {
       Qx1 += fr->J1_XStrips[i].Q();
       Qx2 += fr->J2_XStrips[i].Q();
       Qx3 += fr->J3_XStrips[i].Q();
       Qx4 += fr->J4_XStrips[i].Q();
     }

   for(unsigned int i=0; i<60; i++)
     {
       Qy1 += fr->J1_YStrips[i].Q();
       Qy2 += fr->J2_YStrips[i].Q();
       Qy3 += fr->J3_YStrips[i].Q();
       Qy4 += fr->J4_YStrips[i].Q();
     }
  
   double Qtot1 = Qx1+Qy1;
   double Qtot2 = Qx2+Qy2;
  double Qtot3 = Qx3+Qy3;
   double Qtot4 = Qx4+Qy4;
  
  
  //J1 section:-------------------------------------------------------------------
  double X1 = -49100; //left
  double Y1 = -1375; //bottom
  double X2 = -1000; //right
  double Y2 = -1075; //top
  for(unsigned int i=0; i<60; i++)
    {
      double T = fr->J1_YStrips[i].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot1*100;
      if(Qfrac>0.04 && Qfrac<1)
 	{
 	  fr->J1_YStrips[i].Draw(X1,Y1,X2,Y2,1);
 	  HBD->Update();
	  fr->Y1.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
 	}
      
       else if(Qfrac>=1 && Qfrac<50)
 	{
 	  int index = int (Qfrac);
 	  fr->J1_YStrips[i].Draw(X1,Y1,X2,Y2,index);
 	  HBD->Update();
 	  fr->Y1.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
 	  fr->AllY.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
 	}
       else if(Qfrac>=50 && Qfrac<99.98)
 	{
 	  //int index = int (Qfrac) - 49;
 	  fr->J1_YStrips[i].Draw(X1,Y1,X2,Y2,2);
 	  HBD->Update();
 	  fr->Y1.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
 	  fr->AllY.push_back(Coordinates(fr->J1_YStrips[i].YCenter()));
 	}
      	  
	  Y2 = Y1 - 500;
	  Y1 = Y2 - 300; 
    }

  double x1 = -1900;
  double y1 = -48975;
  double x2 = -1200;
  double y2 = -48675;

  for(unsigned int j=0; j<60; j++)
    {
      
      double T = fr->J1_XStrips[j].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot1*100;
      if(Qfrac>0.04 && Qfrac<1)
	{
 	  fr->J1_XStrips[j].Draw(x1,y1,x2,y2,1);   
 	  HBD->Update();
	  fr->X1.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));

 	}
	
      else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J1_XStrips[j].Draw(x1,y1,x2,y2,index);   
	  HBD->Update();
	  fr->X1.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
	}
      else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac) - 49;
	  fr->J1_XStrips[j].Draw(x1,y1,x2,y2,2);
	  HBD->Update();
	  fr->X1.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J1_XStrips[j].XCenter()));
	}
	
      
      x2 = x1 - 100;
      x1 = x2 - 700;
    }

  
  //J2 section:----------------------------------------------------------------
  //cout<<"J2: "<<endl;

  X1 = 900;
  Y1 = -1375;
  X2 = 49000;
  Y2 = -1075;
  for(unsigned int i=0; i<60; i++)
    {
      double T = fr->J2_YStrips[i].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot2*100;
      if(Qfrac>0.04 && Qfrac<1)
       	{
 	  fr->J2_YStrips[i].Draw(X1,Y1,X2,Y2,1);
 	  HBD->Update();
	  fr->Y2.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	}
      
      else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J2_YStrips[i].Draw(X1,Y1,X2,Y2,index);
	  HBD->Update();
	  fr->Y2.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	  
	}
      else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac)-49;
	  fr->J2_YStrips[i].Draw(X1,Y1,X2,Y2,2);
	  HBD->Update();
	  fr->Y2.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J2_YStrips[i].YCenter()));
	}
      

      Y2 = Y1 - 500;
      Y1 = Y2 - 300; 
    }

  x1 = 48100;
  y1 = -48975;
  x2 = 48800;
  y2 = -48675;

  for(unsigned int j=0; j<60; j++)
    {
      double T = fr->J2_XStrips[j].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot2*100;
      if(Qfrac>0.04 && Qfrac<1)
       	{
 	  fr->J2_XStrips[j].Draw(x1,y1,x2,y2,1);  
 	  HBD->Update();
	  fr->X2.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
 	}
      
      else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J2_XStrips[j].Draw(x1,y1,x2,y2,index);  
	  HBD->Update();
	  fr->X2.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
	}
      else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac)-49;
	  fr->J2_XStrips[j].Draw(x1,y1,x2,y2,2);
	  HBD->Update();
	  fr->X2.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J2_XStrips[j].XCenter()));
	}
      
      x2 = x1 - 100;
      x1 = x2 - 700;
    }
  
  //J3 section:----------------------------------------------------------------
  X1 = -49100;
  Y1 = 1125;
  X2 = -1000;
  Y2 = 1425;
  for(unsigned int i=0; i<60; i++)
    {
      double T = fr->J3_YStrips[i].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot3*100;
      if(Qfrac>0.04 && Qfrac<1)
       	{
 	  fr->J3_YStrips[i].Draw(X1,Y1,X2,Y2,1);
 	  HBD->Update();
	  fr->Y3.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
 	}
       
       else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J3_YStrips[i].Draw(X1,Y1,X2,Y2,index);
	  HBD->Update();
	  fr->Y3.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
	}
       else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac)-49;
	  fr->J3_YStrips[i].Draw(X1,Y1,X2,Y2,2);
	  HBD->Update();
	  fr->Y3.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J3_YStrips[i].YCenter()));
	}
       
      Y1 = Y2 + 500;
      Y2 = Y1 + 300; 
    }

  x1 = -49100;
  y1 = 1525;
  x2 = -48400;
  y2 = 1825;
  for(unsigned int j=0; j<60; j++)
    {
      double T = fr->J3_XStrips[j].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot3*100;
      if(Qfrac>0.04 && Qfrac<1)
       	{
 	  fr->J3_XStrips[j].Draw(x1,y1,x2,y2,1);   
 	  HBD->Update();
	  fr->X3.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	}
      
       else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J3_XStrips[j].Draw(x1,y1,x2,y2,index);   
	  HBD->Update();
	  fr->X3.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	}
       else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac)-49;
	  fr->J3_XStrips[j].Draw(x1,y1,x2,y2,2);
	  HBD->Update();
	  fr->X3.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J3_XStrips[j].XCenter()));
	}
      
      x1 = x2 + 100;
      x2 = x1 + 700;
    }

  //J4 section:-----------------------------------------------------------------
  X1 = 950;
  Y1 = 1125;
  X2 = 49050;
  Y2 = 1425;
  for(unsigned int i=0; i<60; i++)
    {
      double T = fr->J4_YStrips[i].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot4*100;
      if(Qfrac>0.04 && Qfrac<1)
       	{
 	  fr->J4_YStrips[i].Draw(X1,Y1,X2,Y2,1);
 	  HBD->Update();
	  fr->Y4.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
 	}
       
       else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J4_YStrips[i].Draw(X1,Y1,X2,Y2,index);
	  HBD->Update();
	  fr->Y4.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
	  
	}
       else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac)-49;
	  fr->J4_YStrips[i].Draw(X1,Y1,X2,Y2,2);
	  HBD->Update();
	  fr->Y4.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
	  fr->AllY.push_back(Coordinates(fr->J4_YStrips[i].YCenter()));
	}
       
      Y1 = Y2 + 500;
      Y2 = Y1 + 300; 
    }

  x1 = 950;
  y1 = 1525;
  x2 = 1650;
  y2 = 1825;
  for(unsigned int j=0; j<60; j++)
    {
      double T = fr->J4_XStrips[j].Q();
      //double Qfrac = exp(-T/20)*100;
      double Qfrac = T/Qtot4*100;
      if(Qfrac>0.04 && Qfrac<1)
       	{
 	  fr->J4_XStrips[j].Draw(x1,y1,x2,y2,1); 
 	  HBD->Update();
	  fr->X4.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
 	}
       
       else if(Qfrac>=1 && Qfrac<50)
	{
	  int index = int(Qfrac);
	  fr->J4_XStrips[j].Draw(x1,y1,x2,y2,index); 
	  HBD->Update();
	  fr->X4.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
	}
       else if(Qfrac>=50 && Qfrac<99.98)
	{
	  //int index = int(Qfrac)-49;
	  fr->J4_XStrips[j].Draw(x1,y1,x2,y2,2);
	  HBD->Update();
	  fr->X4.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
	  fr->AllX.push_back(Coordinates(fr->J4_XStrips[j].XCenter()));
	}
       
      x1 = x2 + 100;
      x2 = x1 + 700;
    }

  //Drawing the Central Cross:
  X1 = -49100;
  Y1 = -675;
  X2 = 49050;
  Y2 = 675;
  TBox Hori (X1,Y1, X2,Y2);
  Hori.SetFillColor(15);
  Hori.DrawBox(X1,Y1, X2,Y2);
  HBD->Update();

  X1 = -500;
  Y1 = -48975;
  X2 = 500;
  Y2 = 49025;
  TBox Vert (X1,Y1, X2,Y2);
  Vert.SetFillColor(15);
  Vert.DrawBox(X1,Y1, X2,Y2);
  HBD->Update();

  //Drawing the real positions of the photons:
  for(unsigned int a=0; a<fr->HBDParticles.size(); a++)
    {
      fr->HBDParticles[a].Draw();
      HBD->Update();
    }

  //Finding the ring:----------------------------------------------------------------------------------
  Hough = new TH3D ("Hough","Hough",500,-50000,50000,500,-50000,50000,500,0,50000);
  Houghxy = new TH2D ("Houghxy","Houghxy",100,-50000,50000,100,-50000,50000);
  Houghxr = new TH2D ("Houghxr","Houghxr",100,-50000,50000,100,0,50000);
  Houghyr = new TH2D ("Houghyr","Houghyr",100,-50000,50000,100,0,50000);
  
    
//Forming J1234 PseudoPoints:
  for(unsigned int s=0; s<fr->Y1.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X1.size(); ps++)
	{
	  fr->J1_PseudoPoints.push_back(TVector3(fr->X1[ps].Cor(),fr->Y1[s].Cor(),0));
	  
	}
    }
  //cout<<"J1 size:"<<fr->J1_PseudoPoints.size()<<endl;

  for(unsigned int s=0; s<fr->Y2.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X2.size(); ps++)
	{
	  fr->J2_PseudoPoints.push_back(TVector3(fr->X2[ps].Cor(),fr->Y2[s].Cor(),0));
	  
	}
    }
  //cout<<"J2 size:"<<fr->J2_PseudoPoints.size()<<endl;

  for(unsigned int s=0; s<fr->Y3.size(); s++)
    {
      for(unsigned int ps=0; ps<fr->X3.size(); ps++)
	{
	  fr->J3_PseudoPoints.push_back(TVector3(fr->X3[ps].Cor(),fr->Y3[s].Cor(),0));
	 
	}
    }
  //cout<<"J3 size:"<<fr->J3_PseudoPoints.size()<<endl;

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
		  
		  double Rad  = FindR(fr->J1_PseudoPoints[i],fr->J2_PseudoPoints[j],fr->J3_PseudoPoints[k]);
		  double Xcen = FindX(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J3_PseudoPoints[k].X(),fr->J3_PseudoPoints[k].Y());
		  double Ycen = FindY(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J3_PseudoPoints[k].X(),fr->J3_PseudoPoints[k].Y());
		  Hough->Fill(Xcen,Ycen,Rad);
		  Houghxy->Fill(Xcen,Ycen);
		  Houghyr->Fill(Ycen,Rad);
		  Houghxr->Fill(Xcen,Rad);
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
		  double Rad  = FindR(fr->J1_PseudoPoints[i],fr->J2_PseudoPoints[j],fr->J4_PseudoPoints[k]);
		  double Xcen = FindX(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  double Ycen = FindY(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J2_PseudoPoints[j].X(),fr->J2_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  Hough->Fill(Xcen,Ycen,Rad);
		  Houghxy->Fill(Xcen,Ycen);
		  Houghyr->Fill(Ycen,Rad);
		  Houghxr->Fill(Xcen,Rad);
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
		  double Rad  = FindR(fr->J1_PseudoPoints[i],fr->J3_PseudoPoints[j],fr->J4_PseudoPoints[k]);
		  double Xcen = FindX(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  double Ycen = FindY(fr->J1_PseudoPoints[i].X(),fr->J1_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  Hough->Fill(Xcen,Ycen,Rad);
		  Houghxy->Fill(Xcen,Ycen);
		  Houghyr->Fill(Ycen,Rad);
		  Houghxr->Fill(Xcen,Rad);
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
		  double Rad  = FindR(fr->J2_PseudoPoints[i],fr->J3_PseudoPoints[j],fr->J4_PseudoPoints[k]);
		  double Xcen = FindX(fr->J2_PseudoPoints[i].X(),fr->J2_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  double Ycen = FindY(fr->J2_PseudoPoints[i].X(),fr->J2_PseudoPoints[i].Y(),fr->J3_PseudoPoints[j].X(),fr->J3_PseudoPoints[j].Y(),fr->J4_PseudoPoints[k].X(),fr->J4_PseudoPoints[k].Y());
		  Hough->Fill(Xcen,Ycen,Rad);
		  Houghxy->Fill(Xcen,Ycen);
		  Houghyr->Fill(Ycen,Rad);
		  Houghxr->Fill(Xcen,Rad);
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
 	      double Rad = FindR(fr->PseudoPoints[i],fr->PseudoPoints[j],fr->PseudoPoints[k]);
 	      double Xcen = FindX(fr->PseudoPoints[i].X(),fr->PseudoPoints[i].Y(),fr->PseudoPoints[j].X(),fr->PseudoPoints[j].Y(),fr->PseudoPoints[k].X(),fr->PseudoPoints[k].Y());
 	      double Ycen = FindY(fr->PseudoPoints[i].X(),fr->PseudoPoints[i].Y(),fr->PseudoPoints[j].X(),fr->PseudoPoints[j].Y(),fr->PseudoPoints[k].X(),fr->PseudoPoints[k].Y());
 	      Hough->Fill(Xcen,Ycen,Rad);
 	      Houghxy->Fill(Xcen,Ycen);
 	      Houghyr->Fill(Ycen,Rad);
 	      Houghxr->Fill(Xcen,Rad);
	      }
 	}
     }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  */      
  int xbin, ybin, zbin;
  xbin=0; ybin=0; zbin=0;
  Hough->GetMaximumBin(xbin, ybin, zbin);
  //cout << "xbin= " << xbin << " ybin= " << ybin << " zbin= " << zbin << endl;

  TAxis *xaxis = Hough->GetXaxis();  
  double Xrec=xaxis->GetBinCenter(xbin);
  cout<<"Xrec= "<< Xrec <<endl;

  TAxis *yaxis = Hough->GetYaxis();  
  double Yrec=yaxis->GetBinCenter(ybin);
  cout<<"Yrec= "<< Yrec <<endl;

  TAxis *zaxis = Hough->GetZaxis();  
  double Rrec=zaxis->GetBinCenter(zbin);
  cout<<"Rrec= "<< Rrec <<endl;

  //Drawing the founded ring and its center:
  TEllipse ring (Xrec,Yrec,Rrec,Rrec,1,360,0);
  ring.SetLineColor(2);
  ring.SetFillStyle(0);
  ring.DrawEllipse(Xrec,Yrec,Rrec,Rrec,0,360,0);
  HBD->Update();

  TMarker circumcenter (Xrec,Yrec,8);
  circumcenter.SetMarkerColor(2);
  circumcenter.SetMarkerSize(1);
  circumcenter.DrawMarker(Xrec,Yrec);
  HBD->Update();  
  
}
