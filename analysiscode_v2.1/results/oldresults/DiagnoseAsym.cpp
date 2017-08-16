#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"

#include <vector>
#include <iostream>
#include <cmath>

TFile *fOut;

Int_t RunNumber;
TString *TargetType;
Int_t helicity;
Float_t TarPol;
Double_t b_energy;
Float_t Q2;
Float_t W;
Float_t Xbj;
Float_t Phi;
Float_t t_Ph;
Float_t fel_E;
Float_t mm;

  

void SetBrAddress(TTree *temptree){

  temptree->SetBranchAddress("RunNumber",&RunNumber);
  temptree->SetBranchAddress("TargetType",&TargetType);
  temptree->SetBranchAddress("helicity",&helicity);
  temptree->SetBranchAddress("TarPol",&TarPol);
  temptree->SetBranchAddress("b_energy",&b_energy);
  temptree->SetBranchAddress("Q2",&Q2);
  temptree->SetBranchAddress("W",&W);
  temptree->SetBranchAddress("Xbj",&Xbj);
  temptree->SetBranchAddress("Phi",&Phi);
  temptree->SetBranchAddress("t_Ph",&t_Ph);
  temptree->SetBranchAddress("fel_E",&fel_E);
  temptree->SetBranchAddress("mm",&mm);

}



void DiagnoseAsym( const char *rootfile ){

  TFile *fIn = new TFile(rootfile);

  std::cout<< "Beginning Binning Routine" << std::endl;
  TTree *tDVCS = (TTree*)fIn->Get("tDVCS");

  SetBrAddress(tDVCS);
  
  int nentries = tDVCS->GetEntries();
  std::cout << ">> Number of Entries to process is "<< nentries << std::endl;

  const char* th[] = {"PP","PN","NP","NN"};
  TH1D* h_mm[4];

  for( int m = 0; m < 4; m++){
    h_mm[m] = new TH1D(Form("h_MM_%s",th[m]),Form("h_MM_%s",th[m]),100,-1.0,3.0);
  }

  /*  TH1D *h_mm_PP = new TH1D("h_mm_PP","",100,-1.0,3.0);
  TH1D *h_mm_PN = new TH1D("h_mm_PN","",100,-1.0,3.0);
  TH1D *h_mm_NP = new TH1D("h_mm_NP","",100,-1.0,3.0);
  TH1D *h_mm_NN = new TH1D("h_mm_NN","",100,-1.0,3.0);
  */

  //Target Types for Asym
  TString nh3t("NH3T"); 
  TString nh3b("NH3B"); 
  TString nh3s("NH3S"); 

  for(int i = 0; i < nentries; i++){
    tDVCS->GetEntry(i);
    
    if( *TargetType == nh3t || *TargetType == nh3b || *TargetType == nh3s ){
      if( TarPol > 0 && helicity == 1 ){
	h_mm[0]->Fill(mm);
      }
      if( TarPol > 0 && helicity == 0 ){
	h_mm[1]->Fill(mm);
      }
      if( TarPol < 0 && helicity == 1 ){
	h_mm[2]->Fill(mm);
      }
      if( TarPol < 0 && helicity == 0 ){
	h_mm[3]->Fill(mm);
      }
    }
  }
  std::cout << "End Entry Loop "<< std::endl;

  TCanvas *c1 = new TCanvas("c1_MM","c1_MM", 800, 800 );
  c1->Divide(2,2);
  for( int j = 0; j < 4; j++ ){
    c1->cd(j+1);
    h_mm[j]->SetTitle(Form("Missing Mass for %s (target/beam)",th[j]));
    h_mm[j]->GetXaxis()->SetTitle("Missing Mass [GeV]");
    h_mm[j]->GetXaxis()->CenterTitle();
    gStyle->SetStatY(0.9);
    gStyle->SetStatX(0.9);  
    h_mm[j]->Draw();
  }
  std::cout << " Saving PDF " << std::endl;
  c1->SaveAs("h_mmVStargetpolhelicity.pdf");

  std::cout << ">> Complete" << std::endl;
}
