//###########################################################
//
//
// Created by: Brandon Clary
// Written: 7/18/2017
// Purpose: Calculate the raw normalized target spin asymmetry
//          and the corrected asym using the dilution factor 
//          and the polarization.
//
//
//
//###########################################################
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

#include "tPID.C"

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>




void asym( const char* rootfiles ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfiles);

  tPID *treevar = new tPID(fchain);
  std::cout << ">> Processing " << fchain->GetEntries() << " entries " << std::endl;
  Long64_t nnentries = fchain->GetEntries();


  //HISTOGRAMS FOR TARGET-SPIN ASYM
  TH1D *h_asy_P = new TH1D("h_asy_P","",10,0.0,360.0);
  TH1D *h_asy_N = new TH1D("h_asy_N","",10,0.0,360.0);

  //COUNT THE RATES TO DOUBLE CHECK
  Double_t dvcs_rate_ga = 0;
  Double_t dvcs_rate_nh3_ga = 0;
  Double_t dvcs_rate_c12_ga = 0;
  Double_t dvcs_rate_gb = 0;
  Double_t dvcs_rate_nh3_gb = 0;
  Double_t dvcs_rate_c12_gb = 0;

  for (Long64_t nn = 0; nn< nnentries; nn++){
    fchain->GetEntry(nn);

    std::string period = (std::string)*(treevar->periodID);    
    bool groupB = period == 'B';
    bool groupA = period == 'A';

    //if( groupB && (treevar->FC0 > 1000 && treevar->FC1 > 1000) ){ //REMOVED BC NEED TO MATCH ANGELLA'S " NO IMPROVEMENTS " - JOO :/
      if ( nn%1000000 == 0 ) { std::cout << nn << std::endl; } 	
      std::string target = (std::string)(*treevar->targetType);   

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
      Double_t photonTop = treevar->photonTopology;
      Double_t asym_phi = (treevar->phi_)*(180.0/3.14159);

      bool q2_pass = q2 > 1;
      bool x_pass1 = x > 0;
      bool x_pass2 = x < 1.1;
      bool t_pass = -t < q2;
      bool w_pass = w > 2;
      bool phE_pass = photon_E > 1;
      bool phi_pass = fabs(phi)/3.14159 * 180.0 < 2;
      bool mm2epg_pass = fabs( mm2epg ) < 0.1;
      bool mm2_pass = fabs( mm ) < 0.3;
      bool deltatheta_pass = deltheta/3.14159 * 180.0 < (1.0);
      bool q2_t_pass = q2 > -t;
      bool photonEC = photonTop == 2;
      bool photonIC = photonTop == 1;

      bool trans_mntm_pass = TMath::Sqrt(perpX*perpX + perpY*perpY) < 0.15;
      bool target_nh3t = target == "NH3T";
      bool target_nh3b = target == "NH3B";
      bool target_nh3s = target == "NH3S";
      bool target_nh3 = target_nh3t || target_nh3b;
      bool target_c12 = target == "C12";
      
      TLorentzVector el_lv( treevar->el_px, treevar->el_py, treevar->el_pz, treevar->el_E);
      TLorentzVector pr_lv( treevar->pr_px, treevar->pr_py, treevar->pr_pz, treevar->pr_E);
      TLorentzVector ph_lv( treevar->ph_px, treevar->ph_py, treevar->ph_pz, treevar->ph_E);
      TLorentzVector el_b( 0.0, 0.0, treevar->beamEnergy, treevar->beamEnergy);
      TLorentzVector target_lv( 0.0, 0.0, 0.0, 0.9382720);
      
      TLorentzVector missing_lv = el_b + target_lv - (el_lv + pr_lv + ph_lv );
      Double_t missing_energy = missing_lv.E();  

      //DVCS CUTS FOR NH3
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && deltatheta_pass && mm2_pass){

	if( groupA ){
	  dvcs_rate_ga++;
	  if( target_c12 ){
	    dvcs_rate_c12_ga++;
	  }
	  if( target_nh3t || target_nh3b ){
	    dvcs_rate_nh3_ga++;
	  }
	}
	
	if( groupB ){
	  dvcs_rate_gb++;
	  if( target_c12 ){
	    dvcs_rate_c12_gb++;
	  }
	  if( target_nh3t || target_nh3b ){
	    dvcs_rate_nh3_gb++;
	  }
	}

	if( targetPol > 0 ){
	  h_asy_P->Fill(asym_phi);
	}
	if( targetPol < 0 ){
	  h_asy_N->Fill(asym_phi);
	}
      }
      //}
  }

  Double_t fc_p = 5.59802;
  Double_t fc_n = 5.90968;
  Double_t dilution_b = 0.74;
  Double_t tarP = 0.81;
  Double_t tarN = 0.75;

  std::vector<Double_t> asym_y, asym_x;
  std::vector<Double_t> raw_asym_y, raw_asym_x;

  for( int b = 1 ; b <= 10; b++ ){
    Int_t P = h_asy_P->GetBinContent(b);
    Int_t N = h_asy_N->GetBinContent(b);

    Double_t P_fcn = P/fc_p;
    Double_t N_fcn = N/fc_n;

    Double_t numerator = P_fcn - N_fcn;
    Double_t denominator = dilution_b*(tarN*P_fcn + tarP*N_fcn);
    
    asym_y.push_back(numerator/denominator);
    asym_x.push_back( h_asy_P->GetBinCenter(b) );

    raw_asym_y.push_back( (P_fcn-N_fcn)/(P_fcn+N_fcn) );
    raw_asym_x.push_back(h_asy_P->GetBinCenter(b));

  } 

  std::cout << " CREATING TGRAPH " << std::endl;
  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->SetGrid();
  TLegend *leg = new TLegend(0.75,0.75,0.89,0.89);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);

  TGraph *g_asym = new TGraph(asym_x.size(), &(asym_x[0]), &(asym_y[0]));
  g_asym->SetName("Asym");
  g_asym->SetTitle(" Target-Spin Asymmetry ");
  g_asym->GetXaxis()->SetTitle("#phi [deg]");
  g_asym->GetXaxis()->CenterTitle();
  g_asym->GetYaxis()->SetTitle("Target-Spin Asymmetry");
  g_asym->GetYaxis()->CenterTitle();
  g_asym->SetMarkerStyle(20);
  g_asym->SetMarkerSize(0.7);
  g_asym->SetMarkerColor(kBlue+2);
  g_asym->Draw("AP");

  TGraph *g_raw_asym = new TGraph(raw_asym_x.size(), &(raw_asym_x[0]), &(raw_asym_y[0]));
  g_raw_asym->SetName("Raw Asym");
  g_raw_asym->SetTitle("Raw Target-Spin Asymmetry");
  g_raw_asym->GetXaxis()->SetTitle("#phi [deg]");
  g_raw_asym->GetXaxis()->CenterTitle();
  g_raw_asym->GetYaxis()->SetTitle("Target-Spin Asymmetry");
  g_raw_asym->GetYaxis()->CenterTitle();
  g_raw_asym->SetMarkerStyle(20);
  g_raw_asym->SetMarkerSize(0.7);
  g_raw_asym->SetMarkerColor(kRed);
  g_raw_asym->Draw("P");

  leg->AddEntry(g_raw_asym,"Raw TSA","P");
  leg->AddEntry(g_asym,"Corrected TSA","P");
  leg->Draw("same");  


  std::cout << " >> FINAL DVCS RATE " << std::endl;
  std::cout << " >> Group A Results " << std::endl;  
  std::cout << " From all targets " << dvcs_rate_ga << std::endl;
  std::cout << " From NH3 target " << dvcs_rate_nh3_ga << std::endl;
  std::cout << " FROM C12 target " << dvcs_rate_c12_ga << std::endl;

  std::cout << " >> Group B Results " << std::endl;  
  std::cout << " From all targets " << dvcs_rate_gb << std::endl;
  std::cout << " From NH3 target " << dvcs_rate_nh3_gb << std::endl;
  std::cout << " FROM C12 target " << dvcs_rate_c12_gb << std::endl;

  std::cout << " >> Group A + B " << std::endl;
  std::cout << " From all targets " << dvcs_rate_ga + dvcs_rate_gb << std::endl;
  std::cout << " From NH3 target " << dvcs_rate_nh3_ga + dvcs_rate_nh3_gb << std::endl;
  std::cout << " FROM C12 target " << dvcs_rate_c12_ga + dvcs_rate_c12_gb << std::endl;
  

}
