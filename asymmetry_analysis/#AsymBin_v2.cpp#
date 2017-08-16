/////////////////////////////////////////////////
//
//
//
// Written by Brandon Clary
// 7/26/2017
// Purpose : read the h_dvcs_ root files to create the same
//           raw asymmetry as Biselli's using the wrong 
//           total accumulated beam charge (FC values).
//
//
////////////////////////////////////////////////

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TLine.h"
#include "TLorentzVector.h"
#include "TF1.h"
#include "TLegend.h"

#include "tDVCS.C"

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>



void AsymBin_v2( const char* rootfile ){

  TChain *fchain = new TChain("tDVCS");
  fchain->Add(rootfile);

  tDVCS *treevar = new tDVCS(fchain);
  std::cout << fchain->GetEntries() << " to process " << std::endl;


  //HISTOGRAMS FOR TARGET SPIN ASYMMETRY
  TH1D *h_tbsA_PP = new TH1D("h_tbsA_PP","",10,0.0,360.0);
  TH1D *h_tbsA_PN = new TH1D("h_tbsA_PN","",10,0.0,360.0);
  TH1D *h_tbsA_NP = new TH1D("h_tbsA_NP","",10,0.0,360.0);
  TH1D *h_tbsA_NN = new TH1D("h_tbsA_NN","",10,0.0,360.0);

  TH1D *h_tbsB_PP = new TH1D("h_tbsB_PP","",10,0.0,360.0);
  TH1D *h_tbsB_PN = new TH1D("h_tbsB_PN","",10,0.0,360.0);
  TH1D *h_tbsB_NP = new TH1D("h_tbsB_NP","",10,0.0,360.0);
  TH1D *h_tbsB_NN = new TH1D("h_tbsB_NN","",10,0.0,360.0);

  TH1D *h_tsA_P = new TH1D("h_tsA_P","",10,0.0,360.0);
  TH1D *h_tsA_N = new TH1D("h_tsA_N","",10,0.0,360.0);

  TH1D *h_tsB_P = new TH1D("h_tsB_P","",10,0.0,360.0);
  TH1D *h_tsB_N = new TH1D("h_tsB_N","",10,0.0,360.0);

  Long64_t nentries = fchain->GetEntries();

  for ( Long64_t nn = 0; nn < nentries; nn++ ){
    fchain->GetEntry(nn);
    
    std::string target = (std::string)(*treevar->TargetType);
    std::string group = (std::string)(*treevar->PeriodID);
    Int_t run = (treevar->RunNumber);
    Double_t asy_phi = (treevar->Phi)*(180.0/3.1415926);//5358979);
    Double_t tarpol = treevar->TarPol;
    //std::cout << group << " " << target << " " << tarpol << std::endl;


    if( run >= 58670 && run <= 59220 ){ 
      //if( group == 'A' ){// && (target == "NH3T" || target == "NH3B") ){
      if( tarpol > 0 ){
	h_tsA_P->Fill(asy_phi);
	//std::cout << ">> " << asy_phi << std::endl;
      }
      else if( tarpol < 0 ){
	h_tsA_N->Fill(asy_phi);
      }
    }
    
    if( run > 59220 && run <= 60184 ){
      //if( group == 'B' ){// && (target == "NH3T" || target == "NH3B") ){
      if( tarpol > 0 ){
	h_tsB_P->Fill(asy_phi);
      }
      else if( tarpol < 0 ){
	h_tsB_N->Fill(asy_phi);
      }
    }
  }

  std::cout << " Group A " << std::endl;
  std::cout << ">> P " << h_tsA_P->GetEntries() << std::endl;
  std::cout << ">> N " << h_tsA_N->GetEntries() << std::endl;

  std::cout << " Group B " << std::endl;
  std::cout << ">> P " << h_tsB_P->GetEntries() << std::endl;
  std::cout << ">> N " << h_tsB_N->GetEntries() << std::endl;

 
   
  //MAKE THE ASYMMETRY PLOTS
  TH1D *top_A = new TH1D("top_A","",10,0.0,360.0);
  TH1D *bot_A = new TH1D("bot_A","",10,0.0,360.0);
  TH1D *top_B = new TH1D("top_B","",10,0.0,360.0);
  TH1D *bot_B = new TH1D("bot_B","",10,0.0,360.0);

  TH1D *asy_A = new TH1D("asy_A","",10,0.0,360.0);
  TH1D *asy_B = new TH1D("asy_B","",10,0.0,360.0);


  Double_t dilute_a = 0.912; //0.867
  Double_t tarpol_p_a = 0.75;
  Double_t tarpol_n_a = 0.72;
  Double_t fc_A_pp = 1.65813; //(4.31883);//1.0/2.69372;//1.0;//;
  Double_t fc_A_pn = 1.65679; //(4.32092);//1.0/2.69169; //
  Double_t fc_A_np = 1.7595; //1.0/2.6908;//
  Double_t fc_A_nn = 1.76078; //1.0/2.68963;//  
  
  Double_t fc_A_p = fc_A_pp + fc_A_pn;
  Double_t fc_A_n = fc_A_np + fc_A_nn;
 
  Double_t dilute_b = 0.928;
  Double_t tarpol_p_b = 0.81;
  Double_t tarpol_n_b = 0.75;
  Double_t fc_B_pp = 2.6607; // (4.31883);//1.0/2.69372;//1.0;//;
  Double_t fc_B_pn = 2.66413; // (4.32092);//1.0/2.69169; //
  Double_t fc_B_np = 2.76767; //(4.52718);//1.0/2.6908;//
  Double_t fc_B_nn = 2.76589; //(4.52667);//1.0/2.68963;//  
 
  Double_t fc_B_p = fc_B_pp + fc_B_pn;
  Double_t fc_B_n = fc_B_np + fc_B_nn;
  
  top_A->Add(h_tsA_P, h_tsA_N, 1.0/fc_A_p, -1.0/fc_A_n);
  bot_A->Add(h_tsA_P, h_tsA_N, tarpol_n_a * dilute_a * 1.0/fc_A_p, tarpol_p_a * dilute_a * 1.0/fc_A_n);

  top_B->Add(h_tsB_P, h_tsB_N, 1.0/fc_B_p, -1.0/fc_B_n);
  bot_B->Add(h_tsB_P, h_tsB_N, tarpol_n_b * dilute_b * 1.0/fc_B_p, tarpol_p_b * dilute_b * 1.0/fc_B_n);

  asy_A->Divide(top_A,bot_A,1.0,1.0);
  asy_B->Divide(top_B,bot_B,1.0,1.0);

  TCanvas *c1 = new TCanvas("c1","",1600,600);
  gStyle->SetOptStat(0);
  c1->Divide(2,1);
  c1->cd(1);
  asy_A->SetMarkerStyle(8);
  asy_A->SetMarkerSize(0.8);
  asy_A->Draw("p");
  c1->cd(2);
  asy_B->SetMarkerStyle(8);
  asy_B->SetMarkerSize(0.8);
  asy_B->Draw("p");
 

}






