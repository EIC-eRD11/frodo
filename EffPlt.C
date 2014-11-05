#include "TGraph.h"

#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <iostream>

using namespace std;

void EffPlt()
{
  double x[6]  = {25000,30000,35000,40000,45000,50000};
  double y0[6] = {0.9205,0.9245,0.9725,0.966,0.9755,0.925};
  double y1[6] = {0.914,0.9445,0.9545,0.962,0.9355,0.813};
  double y2[6] = {0.8675,0.922,0.93,0.921,0.8615,0.655};
  double y3[6] = {0.748,0.8645,0.8715,0.8285,0.7185};
  double y4[6] = {0.2575,0.699,0.763,0.684,0.5095};

  double Y0[6] = {0.9475,0.964,0.9645,0.9715,0.9835,0.925};
  double Y1[6] = {0.9325,0.952,0.9685,0.97,0.943,0.8465};
  double Y2[6] = {0.883,0.9365,0.952,0.9365,0.871,0};
  double Y3[6] = {0.7355,0.8805,0.8965,0.8405,0.7335,0};
  double Y4[6] = {0.288,0.7095,0.7955,0.6885,0.4995,0};

//   TGraph *gr0 = new TGraph (6,x,y0);
//   TGraph *gr1 = new TGraph (6,x,y1);
//   TGraph *gr2 = new TGraph (6,x,y2);
//   TGraph *gr3 = new TGraph (6,x,y3);
//   TGraph *gr4 = new TGraph (6,x,y4);

//   TCanvas *c1 = new TCanvas ("c1","Reco Eff",200,10,600,400);
//   c1->Range(0,0.0,60000,1.0);
//   //c1->BuildLegend();

//   TLegend *l1 = new TLegend (300,200,400,250,"Eff");
//   l1->Draw();

//   //gr0->SetLimits(lower,upper);
//   gr0->SetMaximum(1.5);
//   gr0->SetMinimum(0);
//   gr0->SetTitle("Ring Reconstruction Efficiency");
//   gr0->GetXaxis()->SetTitle("R");
//   gr0->GetYaxis()->SetTitle("Efficiency");
  
//   gr0->SetMarkerStyle(21);
//   gr0->SetMarkerColor(1);
//   gr0->Draw("AP");

//   //  c1->Update();

//   gr1->SetMarkerStyle(21);
//   gr1->SetMarkerColor(2);
//   gr1->Draw("P");

//   //  c1->Update();

//   gr2->SetMarkerStyle(21);
//   gr2->SetMarkerColor(3);
//   gr2->Draw("P");
 
//   //  c1->Update();

//   gr3->SetMarkerStyle(21);
//   gr3->SetMarkerColor(4);
//   gr3->Draw("P");

//   //  c1->Update();

//   gr4->SetMarkerStyle(21);
//   gr4->SetMarkerColor(5);
//   gr4->Draw("P");
//   c1->Update();

  TGraph *GR0 = new TGraph (6,x,Y0);
  TGraph *GR1 = new TGraph (6,x,Y1);
  TGraph *GR2 = new TGraph (6,x,Y2);
  TGraph *GR3 = new TGraph (6,x,Y3);
  TGraph *GR4 = new TGraph (6,x,Y4);

  TCanvas *c1 = new TCanvas ("c1","Reco Eff",200,10,600,400);
  c1->Range(0,0.0,60000,1.0);
  //c1->BuildLegend();

  TLegend *l1 = new TLegend (300,200,400,250,"Eff");
  l1->Draw();

  //gr0->SetLimits(lower,upper);
  GR0->SetMaximum(1.5);
  GR0->SetMinimum(0);
  GR0->SetTitle("Ring Reconstruction Efficiency");
  GR0->GetXaxis()->SetTitle("R");
  GR0->GetYaxis()->SetTitle("Efficiency");
  
  GR0->SetMarkerStyle(21);
  GR0->SetMarkerColor(1);
  GR0->Draw("AP");

  //  c1->Update();

  GR1->SetMarkerStyle(21);
  GR1->SetMarkerColor(2);
  GR1->Draw("P");

  //  c1->Update();

  GR2->SetMarkerStyle(21);
  GR2->SetMarkerColor(3);
  GR2->Draw("P");
 
  //  c1->Update();

  GR3->SetMarkerStyle(21);
  GR3->SetMarkerColor(4);
  GR3->Draw("P");

  //  c1->Update();

  GR4->SetMarkerStyle(21);
  GR4->SetMarkerColor(5);
  GR4->Draw("P");
  c1->Update();
}
