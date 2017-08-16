#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBrowser.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TMath.h"
#include "TStyle.h"
#include "TPolyLine.h"
#include "TF1.h"
#include "TLine.h"

#include "tPID.C"

#include <vector>
#include <iostream>
#include <string>

//
//
//  Written By: Brandon Clary
//  Date: 7-11-2017
//  The purpose of this macro is to draw plots 
//  for the DVCS Summary Report for K. Joo. Nothing
//  very special about this macro.
//
//
//



void PIDsummaryPlots(const char* rootfile){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfile);

  TFile *fIn = new TFile(rootfile);

  gStyle->SetOptStat(0);
  //gStyle->SetPalette(kRainBow );
  //CREATE PLOTS FOR RASTER CORRECTION
  TH2D *h_rastercorr = (TH2D*)fIn->Get("hPID_crrrastr12");
  h_rastercorr->GetXaxis()->SetTitle("Raster X [cm]");
  h_rastercorr->GetXaxis()->CenterTitle();
  h_rastercorr->GetYaxis()->SetTitle("Raster Y [cm]");
  h_rastercorr->GetYaxis()->CenterTitle();
  h_rastercorr->Draw("colz");

  TH2D *h_el_vzphi = (TH2D*)fIn->Get("hpid_el_vzPhi_corr");
  h_el_vzphi->GetXaxis()->SetTitle("Vertex Position of Electron [cm]");
  h_el_vzphi->GetXaxis()->CenterTitle();
  h_el_vzphi->GetYaxis()->SetTitle("Azimuthal Scattering Angle, #phi, [deg]");
  h_el_vzphi->GetYaxis()->CenterTitle();
  h_el_vzphi->Draw("colz");

  //CREATE PLOTS FOR SHADOW CAST ON THE EC BY THE IC ( ICSHADOW CUTS )
  //FOR THE ELECTRON
  TH2D *h_el_icshadhit = (TH2D*)fIn->Get("h2_el_icshadhit_cutlvl14");
  h_el_icshadhit->SetTitle("");
  h_el_icshadhit->GetXaxis()->SetTitle("IC hit position X [cm]");
  h_el_icshadhit->GetXaxis()->CenterTitle();
  h_el_icshadhit->GetYaxis()->SetTitle("IC hit position Y [cm]");
  h_el_icshadhit->GetYaxis()->CenterTitle();
  h_el_icshadhit->Draw("colz");
  Double_t x[23] = {0,       9.5,   8.5,  14.0,  18.5,  23.5, 19.5, 19.0, 13.5, 10.0,  5.3,  3.7,  0.0, -3.7, -9.7, -18.4, -18.4, -23.0, -18.0, -13.7,  -7.5,  -7.8,     0 };
  Double_t y[23] = {-25.0, -22.0, -19.0, -14.0, -18.0, -11.0, -8.5,  8.2, 14.1, 17.4, 19.3, 20.0, 20.5, 20.0, 17.8,  10.8,  -7.0, -11.5, -18.3, -14.7, -20.5, -22.5, -25.0 };
  TPolyLine *icshadow = new TPolyLine(23, x, y);
  icshadow->SetLineColor(kRed);
  icshadow->SetLineWidth(3); 
  icshadow->Draw("same");
  

  //CREATE PLOTS FOR THE ELECTRON EC HIT 
  TH2D *h_el_ecfid_before = (TH2D*)fIn->Get("h2_el_echit_cutlvl11");
  TH2D *h_el_ecfid_after = (TH2D*)fIn->Get("h2_el_echit_cutlvl14");  
  TCanvas *c2 = new TCanvas("c2","",800,600);
  c2->Divide(2,1);

  c2->cd(1);
  //h_el_ecfid_before->GetXaxis()->SetTitle("EC X hit position [cm]");
  //h_el_ecfid_before->GetXaxis()->CenterTitle();
  //h_el_ecfid_before->GetYaxis()->SetTitle("EC Y hit position [cm]");
  //h_el_ecfid_before->GetYaxis()->CenterTitle();
  h_el_ecfid_before->Draw("colz");

  c2->cd(2);
  //h_el_ecfid_after->GetXaxis()->SetTitle("EC X hit position [cm]");
  //h_el_ecfid_after->GetXaxis()->CenterTitle();
  //h_el_ecfid_after->GetYaxis()->SetTitle("EC Y hit position [cm]");
  //h_el_ecfid_after->GetYaxis()->CenterTitle();
  //h_el_ecfid_after->Draw("colz");
  c2->SaveAs("h_el_ecfid_aftbef.pdf");


  //CREATE PLOTS FOR THE PROTON EC CUTS
  TCanvas *c3 = new TCanvas("c3","",600,600);

  TH2D* h_pr_bvsp = (TH2D*)fIn->Get("h2_pr_bvsp_cutlvl4");
  TF1 *maxbetacut = new TF1("maxbetacut","(x/sqrt(x*x+0.938272*0.938272) + 0.02)*(1.2+0.92*x)/(1+x)", 0.30, 3.0);
  TF1 *minbetacut = new TF1("maxbetacut","(x/sqrt(x*x+0.938272*0.938272) - 0.05)*(0.9+1.06*x)/(1+x)", 0.30, 3.0);

  h_pr_bvsp->GetXaxis()->SetTitle("p [GeV]");
  h_pr_bvsp->GetXaxis()->CenterTitle();
  h_pr_bvsp->Draw("colz");
  maxbetacut->Draw("same");
  minbetacut->Draw("same");

  //CREATE PLOTS FOR THE EC PHOTON @ EC 
  TH2D *h_ecph_ecfid_before = (TH2D*)fIn->Get("h2_ecph_echit_cutlvl3");
  TH2D *h_ecph_ecfid_after = (TH2D*)fIn->Get("h2_ecph_echit_cutlvl6");  
  TCanvas *c4 = new TCanvas("c4","",800,600);
  c4->Divide(2,1);

  c4->cd(1);
  h_ecph_ecfid_before->GetXaxis()->SetTitle("EC X hit position [cm]");
  h_ecph_ecfid_before->GetXaxis()->CenterTitle();
  h_ecph_ecfid_before->GetYaxis()->SetTitle("EC Y hit position [cm]");
  h_ecph_ecfid_before->GetYaxis()->CenterTitle();
  h_ecph_ecfid_before->Draw("colz");

  c4->cd(2);
  h_ecph_ecfid_after->GetXaxis()->SetTitle("EC X hit position [cm]");
  h_ecph_ecfid_after->GetXaxis()->CenterTitle();
  h_ecph_ecfid_after->GetYaxis()->SetTitle("EC Y hit position [cm]");
  h_ecph_ecfid_after->GetYaxis()->CenterTitle();
  h_ecph_ecfid_after->Draw("colz");
  c4->SaveAs("h_ecph_ecfid_aftbef.pdf");

  TCanvas *c5 = new TCanvas("c5","",600,600);
  
  TH2D* h_icph_ichit = (TH2D*)fIn->Get("h2_icph_ichit_cutlvl3");
  h_icph_ichit->GetXaxis()->SetTitle("IC X hit position [cm]");
  h_icph_ichit->GetXaxis()->CenterTitle();
  h_icph_ichit->GetYaxis()->SetTitle("IC Y hit position [cm]");
  h_icph_ichit->GetYaxis()->CenterTitle();
  h_icph_ichit->Draw("colz");  
  

  TCanvas *c6 = new TCanvas("c6","",800,600);  
  TH2D* h_icph_moeller = (TH2D*)fIn->Get("h2_icph_moeller_cutlvl2");
  TF1 *mollercut = new TF1("mollercut","(-6.5/1.6)*x + 6.5",0.3,0.75);
  TLine *energycut = new TLine(0.30,5.28 , 0.30, 19.9);
  mollercut->SetLineColor(kRed);
  mollercut->SetLineWidth(3);
  energycut->SetLineColor(kRed);
  energycut->SetLineWidth(3);
  h_icph_moeller->Draw("colz");  
  mollercut->Draw("same");
  energycut->Draw("same");


}
