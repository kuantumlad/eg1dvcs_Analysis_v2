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

void RunParameter( const char* rootfile ){

  TFile *fIn = new TFile(rootfile);

  std::cout<< "Checking Run Parameters for EG1-DVCS" << std::endl;
  TTree *tDVCS = (TTree*)fIn->Get("tDVCS");

  SetBrAddress(tDVCS);
  
  int nentries = tDVCS->GetEntries();
  std::cout << ">> Number of Entries to process is "<< nentries << std::endl;

  std::vector<double> hel, tarpol, run;

  //Target Types
  TString nh3t("NH3T"); 
  TString nh3b("NH3B"); 
  TString nh3s("NH3S"); 

  TH1D *h_el_theta = new TH1D("h_el_theta","", 100, -0.5, 60.5);

  for( int i = 0; i < nentries; i++){
    tDVCS->GetEntry(i);
       
    if( *TargetType == nh3t || *TargetType == nh3b || *TargetType == nh3s ){
      double theta = (acos(1 - Q2/(2*fel_E*b_energy)))*(180.0/TMath::Pi());
      h_el_theta->Fill(theta);
      hel.push_back(helicity);
      tarpol.push_back(TarPol);
      run.push_back(RunNumber);
    }
  }


  TCanvas *c1 = new TCanvas("Eg1-dvcs Run Parameters","",1600,800);
  c1->Divide(2,2);
  std::cout << ">> Drawing Graph of Target Polarization Vs Run Number" << std::endl;  
  c1->cd(1);
  TGraph *gtemp = new TGraph(run.size(), &(run[0]), &(hel[0]) );
  gtemp->SetName("Beam Helicity vs eg1-dvcs Run Number");
  gtemp->SetTitle("Beam Helicity vs eg1-dvcs Run Number");
  gtemp->GetXaxis()->SetTitle("Run Number");
  gtemp->GetXaxis()->CenterTitle();
  gtemp->GetYaxis()->SetTitle("Beam Helicity");
  gtemp->SetMarkerStyle(20);
  gtemp->SetMarkerSize(0.6);
  gtemp->SetMarkerColor(kBlue+2);
  gtemp->Draw("AP");

  c1->cd(2);
  TGraph *gtemp2 = new TGraph(run.size(), &(run[0]), &(tarpol[0]) );
  gtemp2->SetName("Target Polarization vs eg1-dvcs Run Number");
  gtemp2->SetTitle("Target Polarization vs eg1-dvcs Run Number");
  gtemp2->GetXaxis()->SetTitle("Run Number");
  gtemp2->GetXaxis()->CenterTitle();
  gtemp2->GetYaxis()->SetTitle("Target Polarization");
  gtemp2->SetMarkerStyle(20);
  gtemp2->SetMarkerSize(0.6);
  gtemp2->SetMarkerColor(kBlue+2);
  gtemp2->Draw("AP");
  
  c1->cd(3);
  h_el_theta->GetXaxis()->SetTitle("Electron Theta");
  h_el_theta->Draw();
  
  std::cout << ">> Complete." << std::endl;

}
