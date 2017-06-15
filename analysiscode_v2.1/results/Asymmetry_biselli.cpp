#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TPad.h"
#include "TAttMarker.h"
#include "TTree.h"
#include <iostream>
TFile *fOut;


void FaradayCupNormalizer(TFile *fIn){

  std::cout << "Getting Faraday Cup counts for normalization purposes." << std::endl;
  TTree* root_tree = (TTree*)fIn->Get("FCValues");
  std::cout << " Entries/Number of Final Runs >> " << root_tree->GetEntries() << std::endl;

  Double_t nh3fcplusplus;
  Double_t nh3fcplusminus;
  Double_t nh3fcminusplus;
  Double_t nh3fcminusminus;

  root_tree->SetBranchAddress("nh3fcplusplus",&nh3fcplusplus);
  root_tree->SetBranchAddress("nh3fcplusminus",&nh3fcplusminus);
  root_tree->SetBranchAddress("nh3fcminusplus",&nh3fcminusplus);
  root_tree->SetBranchAddress("nh3fcminusminus",&nh3fcminusminus);
  
  Double_t fc_final_PP = 0;
  Double_t fc_final_PN = 0;
  Double_t fc_final_NP = 0;
  Double_t fc_final_NN = 0;

  Int_t nentries = root_tree->GetEntries();
  for( int i = 0; i <= nentries; i++ ){
    root_tree->GetEntry(i);

    // Angela's notation: plus minus = positive helicity with negative target
    // My notation is inverted P N = positive target with negative helicity
    fc_final_PP = fc_final_PP + nh3fcplusplus;
    fc_final_PN = fc_final_PN + nh3fcminusplus;
    fc_final_NP = fc_final_NP + nh3fcplusminus;
    fc_final_NN = fc_final_NN + nh3fcminusminus;    
  }

  std::cout << " FC PP = " << fc_final_PP << std::endl;
  std::cout << " FC PN = " << fc_final_PN << std::endl;
  std::cout << " FC NP = " << fc_final_NP << std::endl;
  std::cout << " FC NN = " << fc_final_NN << std::endl;

}


void Asymmetry_biselli( const char* rootfile ){

  TFile *fIn = new TFile(rootfile);
  if( !fIn ){
    std::cout << " Could not open file " << std::endl;
  }

  if( (TString)fIn->GetName() == "dvcsBiselliAll.root" ){
    FaradayCupNormalizer(fIn);
  }

  //  if( (TString)fIn->GetName() == "h_eg1_AllBiselli.root" ){

    TH1D *PP_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_PP");
    TH1D *PN_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_PN");
    TH1D *NP_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_NP");
    TH1D *NN_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_NN");

    TH1D *PP_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_PP");
    TH1D *PN_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_PN");
    TH1D *NP_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_NP");
    TH1D *NN_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_NN");

    TH1D *PPPN_a = new TH1D("PPPN_a","",10,0,360);
    TH1D *NPNN_a = new TH1D("NPNN_a","",10,0,360);
    
    TH1D *PPPN_b = new TH1D("PPPN_b","",10,0,360);
    TH1D *NPNN_b = new TH1D("NPNN_b","",10,0,360);

    TH1D *PPPN_ab = new TH1D("PPPN_ab","",10,0,360);
    TH1D *NPNN_ab = new TH1D("NPNN_ab","",10,0,360);

    TH1D *numerator = new TH1D("numerator","",10,0,360);
    TH1D *denominator = new TH1D("denominator","",10,0,360);

    TH1D *asym = new TH1D("asym","",10,0,360);

    //Double_t dilute_a = 0.883;
    Double_t dilute_b = 0.867;
    Double_t fc_pp = 1.0/2.69372;//1.0;//(1.0/4.31883);
    Double_t fc_pn = 1.0/2.69169;//(1.0/4.32092);
    Double_t fc_np = 1.0/2.6908;//(1.0/4.52718);
    Double_t fc_nn = 1.0/2.68963;//(1.0/4.52667);  

    PPPN_a->Add(PP_a,PN_a,fc_pp,fc_pn);
    NPNN_a->Add(NP_a,NN_a,fc_np,fc_nn);

    PPPN_b->Add(PP_b,PN_b,fc_pp,fc_pn);
    NPNN_b->Add(NP_b,NN_b,fc_np,fc_nn);

    PPPN_ab->Add(PPPN_a,PPPN_b,1.0,1.0);
    NPNN_ab->Add(NPNN_a,NPNN_b,1.0,1.0);

    numerator->Add(PPPN_b,NPNN_b,1.0,-1.0);
    denominator->Add(PPPN_b,NPNN_b,dilute_b*1.0,dilute_b*1.0);

    asym->Divide(numerator,denominator);

    TCanvas *c1 = new TCanvas("c1","",800,800);
    c1->Divide(2,2);
    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.14);

    c1->cd(1);
    numerator->SetTitle("Asy_{target}: PPPN - NPNN Group A+B");
    numerator->GetXaxis()->SetTitle("#phi"); 
    numerator->GetXaxis()->CenterTitle();
    numerator->SetMarkerStyle(8);
    numerator->SetMarkerSize(0.8);
    numerator->Draw("p");

    c1->cd(2);
    denominator->SetTitle("Asy_{target}: PPPN + NPNN Group A+B");
    denominator->GetXaxis()->SetTitle("#phi"); 
    denominator->GetXaxis()->CenterTitle();
    denominator->SetMarkerStyle(8);
    denominator->SetMarkerSize(0.8);
    denominator->Draw("p");

    c1->cd(3);
    asym->SetTitle("Raw Asy_{target} Group A+B");
    asym->GetXaxis()->SetTitle("#phi"); 
    asym->GetXaxis()->CenterTitle();
    asym->GetYaxis()->SetTitle("Asym_{tar}"); 
    asym->GetYaxis()->CenterTitle();
    //   asym->GetYaxis()->SetLabelOffset(1.4);
    asym->SetMarkerStyle(8);
    asym->SetMarkerSize(0.8);
    asym->Draw("p");
  
    c1->SaveAs("asymBiselli_ab.pdf");
    //}
}

