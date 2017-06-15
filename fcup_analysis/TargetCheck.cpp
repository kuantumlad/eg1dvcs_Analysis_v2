#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TChain.h"
#include "TColor.h"
#include "TFunction.h"
#include "TF1.h"
#include "TLegend.h"
#include "TLine.h"
#include "TArrow.h"
#include "TLatex.h"

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iterator>
#include <algorithm>
#include "tDVCS.C"

/////////////////////////////////////////////
//
//
// Brandon Clary
// 6/5/2017
// Purpose: Determine the position of the carbon 
//          and nh3 target. It was simply to determine
//          the position and make sure the dvcs event
//          was good
//
//
//
//
//
////////////////////////////////////////////


void TargetCheck( const char* rootfile ){

  TChain *fchain = new TChain("tDVCS");
  fchain->Add(rootfile);

  tDVCS *treevar = new tDVCS(fchain);

  TH1D *t_hit_c12 = new TH1D("t_hit_c12","",100,-72.0,-64.0);
  TH1D *t_hit_nh3 = new TH1D("t_hit_nh3","",100,-72.0,-64.0);

  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++){
    fchain->GetEntry(nn);
    std::string target = (std::string)(*treevar->TargetType);
    if( *treevar->PeriodID == 'B' ){
      if( target == "C12" ){
	t_hit_c12->Fill(treevar->fel_vz);
      }
      else if( target == "NH3T" || target == "NH3B" || target == "NH3S" ){
	t_hit_nh3->Fill(treevar->fel_vz);
      }
    }
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",1600,800);
  c1->Divide(2,1);
  gStyle->SetOptStat(10);
  c1->cd(1);
  t_hit_c12->SetTitle("DVCS vertex location in C12 Target");
  t_hit_c12->GetXaxis()->SetTitle("Vertex position of event [cm]");
  t_hit_c12->SetFillColorAlpha(kBlue-2,0.7);
  t_hit_c12->Draw();
  c1->cd(2);
  t_hit_nh3->SetTitle("DVCS vertex location in NH3 Target");
  t_hit_nh3->GetXaxis()->SetTitle("Vertex position of event [cm]");
  t_hit_nh3->SetFillColorAlpha(kRed-4,0.7);
  t_hit_nh3->Draw();

}
