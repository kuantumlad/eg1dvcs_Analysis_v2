#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <sstream>

#include "tPID.C"

void runparameters( const char* rootfile ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfile);

  tPID *treevar = new tPID(fchain);

  std::cout << "Proceeding to Create Plots for Run Parameters " << std::endl;


  std::vector< Double_t > Abeam, Bbeam, Cbeam;
  std::vector< Double_t > vArun, vBrun, vCrun;
 
  std::map< Double_t, std::set<Double_t> > mA_beam, mB_beam, mC_beam;
  std::set<Double_t> Arun, Brun, Crun;
  std::set<Double_t> sAbeam, sBbeam, sCbeam;

  Long64_t nentries = fchain->GetEntries();

  for( Long64_t nn = 0; nn < nentries; nn++ ){
    fchain->GetEntry(nn);

    std::string group = std::string(*treevar->periodID);

    if( group == 'A' ){
      Arun.insert(treevar->run);
      sAbeam.insert(treevar->beamEnergy);
    }
    if( group == 'B' ){
      Brun.insert(treevar->run);
      sBbeam.insert(treevar->beamEnergy);
    }
    if( group == 'C' ){
      Brun.insert(treevar->run);
      sBbeam.insert(treevar->beamEnergy);
    }
  

  }

  for( std::set<Double_t>::iterator it = Arun.begin(); it != Arun.end(); ++it ){
    for( std::set<Double_t>::iterator it2 = sAbeam.begin(); it2 != sAbeam.end(); ++it2 ){
      Abeam.push_back(*it);
    }
  }
  for( std::set<Double_t>::iterator it = Arun.begin(); it != Arun.end(); ++it ){
    vArun.push_back(*it);
  }

  for( std::set<Double_t>::iterator it = Brun.begin(); it != Brun.end(); ++it ){
    for( std::set<Double_t>::iterator it2 = sBbeam.begin(); it2 != sBbeam.end(); ++it2 ){
      Bbeam.push_back(*it2);
    }
  }
  for( std::set<Double_t>::iterator it = Brun.begin(); it != Brun.end(); ++it ){
    vBrun.push_back(*it);
  }

  for( std::set<Double_t>::iterator it = Crun.begin(); it != Crun.end(); ++it ){
    for( std::set<Double_t>::iterator it2 = sCbeam.begin(); it2 != sCbeam.end(); ++it2 ){
      Cbeam.push_back(*it2);
    }
  }
  for( std::set<Double_t>::iterator it = Crun.begin(); it != Crun.end(); ++it ){
    vCrun.push_back(*it);
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  TGraph *g_abeam = new TGraph(Arun.size(), &(vArun[0]), &(Abeam[0]) );
  //  TGraph *g_bbeam = new TGraph(Brun.size(), &(vBrun[0]), &(Bbeam[0]) );
  //TGraph *g_cbeam = new TGraph(Crun.size(), &(vCrun[0]), &(Cbeam[0]) );

  g_abeam->SetName("Beam Energy for Group A");
  g_abeam->SetTitle("Beam Energy for Group A");
  g_abeam->GetXaxis()->SetTitle("Run Number");
  g_abeam->GetXaxis()->CenterTitle();
  g_abeam->GetYaxis()->SetTitle("Beam Energy [GeV]");
  g_abeam->SetMarkerColor(kBlue+2);
  g_abeam->SetMarkerStyle(20);
  g_abeam->SetMarkerSize(0.85);
  g_abeam->Draw("AP");

  g_bbeam->SetMarkerColor(kRed);
  g_bbeam->SetMarkerStyle(20);
  g_bbeam->SetMarkerSize(0.85);
  g_bbeam->Draw("AP+same");

 
  g_cbeam->SetMarkerColor(kGreen);
  g_cbeam->SetMarkerStyle(20);
  g_cbeam->SetMarkerSize(0.85);
  g_cbeam->Draw("AP_same");

}

