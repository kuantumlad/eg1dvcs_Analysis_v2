////////////////////////////////////////
//
//
//
//    Writte: by Brandon Clary
//    Date: 6-20-2017
//    Purpose: This macro is meant to look at the variables that 
//             are cut on to select the dvcs events. This amounts to
//             fitting the distributions and getting the mean and sigma.
//             These will then be used for seeing how the dilution factor changes
//             based on the cut's size.
//
//
//
////////////////////////////////////////

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFunction.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLine.h"
#include "TLatex.h"

#include "tPID.C"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>


void FittingMethod( TH1D *h_temp ){

  ///////////////////////////////////////////////////////
  //fitting method 
  TCanvas *c_temp = new TCanvas(Form("%s",h_temp->GetName()),Form("%s",h_temp->GetName()),800,800);

  Double_t xlow, xhigh, histmax;
  Int_t binlow, binhigh, binmax;

  binmax= h_temp->GetMaximumBin();
  histmax = h_temp->GetMaximum();
  binlow = binmax;
  binhigh = binmax;

  Double_t percentofmax = 0.65;

  while( h_temp->GetBinContent(binhigh++) >= percentofmax*histmax && binhigh <= h_temp->GetNbinsX() ){};
  while( h_temp->GetBinContent(binlow--) >= percentofmax*histmax && binlow>=1 ) {};

  xlow=h_temp->GetBinLowEdge(binlow);
  xhigh=h_temp->GetBinLowEdge(binhigh+1);

  h_temp->Fit("gaus","","",xlow,xhigh);

  TF1 *ftemp = (TF1*)h_temp->GetListOfFunctions()->FindObject("gaus");

  Double_t ftemp_mean = ftemp->GetParameter(1);
  Double_t ftemp_stdev = ftemp->GetParameter(2);

  c_temp->cd(1);
  ftemp->SetLineColor(kBlue+2);
  h_temp->GetXaxis()->SetTitle(h_temp->GetName());
  h_temp->SetFillColorAlpha(kRed,0.7);
  h_temp->SetLineColor(kRed);
  h_temp->Draw();
  //  c_temp->SaveAs(Form("%s",h_temp->GetName()));

  //end fitting method
  ///////////////////////////////////////////////////////
}


void DilutionVsCuts( const char* rootfiles ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfiles);

  tPID *treevar = new tPID(fchain);

  std::cout << " Proceeding to analyze " << fchain->GetEntries() << " entries " << std::endl;

  TH1D* h_x = new TH1D("h_x","Xbj", 100, 0.0, 1.1);
  TH1D* h_q2 = new TH1D("h_q2","Q^{2} [GeV^{2}]", 100, 0.0, 5.5);
  TH1D* h_w = new TH1D("h_w"," W [GeV]", 100, -1.0, 3.0);
  TH1D* h_t = new TH1D("h_t"," t [GeV]", 100, 0.0, 1.5);
  TH1D* h_mm2epX = new TH1D("h_mm2epX"," MM^{2} ep->epX [GeV^{2}] ", 200, -0.5, 2.0);
  TH1D* h_mm2epg = new TH1D("h_mm2epg"," MM^{2} ep->epg [GeV^{2}]", 200, -0.5, 2.0);
  TH1D* h_photonE = new TH1D("h_photonE"," Photon Energy [GeV]", 100, 0.0, 3.0);
  TH1D* h_phi = new TH1D("h_phi"," #phi [deg]", 40, -10, 10.0);
  TH1D* h_perpX = new TH1D("h_perpX","p_perpX [GeV]", 100, -1.1, 1.1);
  TH1D* h_perpY = new TH1D("h_perpY","p_perpY [GeV]", 100, -1.1, 1.1);
  TH1D* h_deltatheta = new TH1D("h_deltatheta"," Angle between calculated and measured photon [deg]", 100, 0.0, 3.0);
  TH2D* h_TarPolRun = new TH2D("h_TarPolRun","",1000, 52000, 62000, 100, 0.0, 100.0 );

  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++ ){
    fchain->GetEntry(nn);
   
    if ( (std::string)(*treevar->periodID) == 'B' && (treevar->FC0 > 1000 && treevar->FC1 > 1000 ) ){ // 59829
      if ( nn%1000000 == 0 ) { std::cout << nn << std::endl; }

      std::string target = (std::string)(*treevar->targetType);   
      std::string period = (std::string)(*treevar->periodID);
      Double_t Run = treevar->run;
      Double_t q2 = treevar->qq;
      Double_t x = treevar->xb;
      Double_t t = treevar->t_;
      Double_t w = treevar->w_;
      Double_t mm = treevar->MM;
      Double_t mm2epg = treevar->MM2epg;
      Double_t photon_E = treevar->ph_E;
      Double_t phi = treevar->Dephi;
      Double_t perpX = treevar->perpx;
      Double_t perpY = treevar->perpy;
      Double_t deltheta = treevar->deltatheta;
      Double_t targetPol = treevar->targetPolarization;
      
      h_x->Fill(x);
      h_q2->Fill(q2);
      h_w->Fill(w);
      h_t->Fill(-t);
      h_mm2epX->Fill(mm);
      h_mm2epg->Fill(mm2epg);
      h_photonE->Fill(photon_E);
      h_phi->Fill(phi);
      h_perpX->Fill(perpX);
      h_perpY->Fill(perpY);
      h_deltatheta->Fill(deltheta);
      h_TarPolRun->Fill(Run,targetPol);
            
    }
  }
  std::vector< TH1D* > h_precut;
  h_precut.push_back(h_x);    
  h_precut.push_back(h_q2);    
  h_precut.push_back(h_w);    
  h_precut.push_back(h_t);    
  h_precut.push_back(h_mm2epX);    
  h_precut.push_back(h_mm2epg);    
  h_precut.push_back(h_photonE);    
  h_precut.push_back(h_phi);    
  h_precut.push_back(h_perpX);
  h_precut.push_back(h_perpY);    
  h_precut.push_back(h_deltatheta);    
  
  
  std::cout << " Creating histograms and fitting " << std::endl;

  //Dont fit any of these bc nothing is a gaussian - change this
  int i = 0;
  for( std::vector<TH1D*>::iterator it = h_precut.begin(); it != h_precut.end(); ++it ){
    i++;
    std::cout << i << std::endl;
    FittingMethod(*it);
  }
  
}




