//////////////////////////////////////////////////////
//
//
// Written by : Brandon Clary
// Date: 6-17-2017
// Purpose: This macro is meant to look at how the dilution
//          factor changes when one specific cut, a cut on the 
//          the angle between the calculated and measured photon,
//          is varied over 5 ranges. The output is five different th1ds
//          showing the distribution of C12 and NH3 with this cut
//          and a tgraph to illustrate the change in the dilution factor.
//          The FC values are from the output of the FCRoutine.cpp file.
//          Specifically worked with part B but can also incorporate A.
//
//
////////////////////////////////////////////////////////

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLine.h"
#include "TColor.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "tPID.C"

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <cmath>

void PhAngleCheck( const char* rootfiles ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfiles);

  tPID *treevar = new tPID(fchain);

  std::cout << " Processing " << fchain->GetEntries() << " entries " << std::endl;

  Long64_t nnentries = fchain->GetEntries();

  std::vector<bool> phangtest;
  std::vector<TH1D*> h_phanglvl_nh3, h_phanglvl_c12;
  Int_t max_cutlvl = 200;
  Double_t min_cut = 0.4;

  for(Int_t lvl = 0; lvl <= max_cutlvl; lvl++){
    h_phanglvl_nh3.push_back( new TH1D(Form("h_phang_lvl%d_nh3",lvl),Form("h_phang_lvl%d_nh3",lvl), 100, 0.0, 10.0) );
  }

  for(Int_t lvl = 0; lvl <= max_cutlvl; lvl++){
    h_phanglvl_c12.push_back( new TH1D(Form("h_phang_lvl%d_c12",lvl),Form("h_phang_lvl%d_c12",lvl), 100, 0.0, 10.0) );
  }

  for( Long64_t nn = 0; nn < nnentries; nn++ ){
    fchain->GetEntry(nn);
    
    std::string period = (std::string)(*treevar->periodID);
    
    bool groupB = period == 'B';
    
    if ( groupB && (treevar->FC0 > 1000 && treevar->FC1 > 1000 ) ){
      if ( nn%1000000 == 0 ) { std::cout << nn << std::endl; }
      //      if( nn == 5000000 ) break;
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
      
      bool q2_pass = q2 > 1;
      bool x_pass1 = x > 0;
      bool x_pass2 = x < 1.1;
      bool t_pass = -t < q2;
      bool w_pass = w > 2;
      bool phE_pass = photon_E > 1;
      bool phi_pass = fabs(phi)/3.14159 * 180.0 < 2;
      bool mm2epg_pass = fabs( mm2epg ) < 0.1;
      bool mm2_pass = fabs( mm ) < 0.3;
      bool trans_mntm_pass = TMath::Sqrt(perpX*perpX + perpY*perpY) < 0.15;
      bool target_nh3t = target == "NH3T";
      bool target_nh3b = target == "NH3B";
      bool target_nh3 = target_nh3t || target_nh3b;
      bool target_c12 = target == "C12";
      
      TLorentzVector el_lv( treevar->el_px, treevar->el_py, treevar->el_pz, treevar->el_E);
      TLorentzVector pr_lv( treevar->pr_px, treevar->pr_py, treevar->pr_pz, treevar->pr_E);
      TLorentzVector ph_lv( treevar->ph_px, treevar->ph_py, treevar->ph_pz, treevar->ph_E);
      TLorentzVector el_b( 0.0, 0.0, treevar->beamEnergy, treevar->beamEnergy);
      TLorentzVector target_lv( 0.0, 0.0, 0.0, 0.9382720);
      
      TLorentzVector missing_lv = el_b + target_lv - (el_lv + pr_lv + ph_lv );
      Double_t missing_energy = missing_lv.E();  
      
      for( Int_t pass_counter = 0; pass_counter <= max_cutlvl; pass_counter++ ){
	Double_t cut_value = min_cut + pass_counter/100.0;
	bool deltatheta_pass1 = deltheta/3.14159 * 180.0 < (cut_value);
	phangtest.push_back(deltatheta_pass1);
      }

      /*      bool deltatheta_pass2 = deltheta/3.14159 * 180.0 < (0.9)*1.5;
      bool deltatheta_pass3 = deltheta/3.14159 * 180.0 < 1.5;
      bool deltatheta_pass4 = deltheta/3.14159 * 180.0 < (1.1)*1.5;
      bool deltatheta_pass5 = deltheta/3.14159 * 180.0 < (1.2)*1.5;
      
      phangtest.push_back(deltatheta_pass1);  
      phangtest.push_back(deltatheta_pass2);  
      phangtest.push_back(deltatheta_pass3);  
      phangtest.push_back(deltatheta_pass4);  
      phangtest.push_back(deltatheta_pass5);  
      */

      //Boolean tests for MM2, PhotonAngle, and ??
      //bool mm2_test = q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && deltatheta_pass && mm2epg_pass && groupB;
      //bool photonangle_test = q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB;
             
      //This is to plot the MM2 for both NH3 and C12 targets. The variable mm represents the mm2 from e_i + p_i - e_f - p_f      
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && mm2_pass ){
	int i = 0;
       	for( std::vector<bool>::iterator it = phangtest.begin(); it != phangtest.end(); ++it ){
	  //std::cout << " i " << i << std::endl;	  
	  if( target_nh3 ){
	    if( (*it) ){
	      h_phanglvl_nh3[i]->Fill( deltheta/3.14159 * 180.0);
	    }
	  }
	  
	  if( target_c12 ){
	    if( (*it) ){
	      h_phanglvl_c12[i]->Fill( deltheta/3.14159 * 180.0);
	    }
	  }	  
	  i++; 
	}
      }
      phangtest.clear();
    }
  }

  std::vector<Double_t> dilution, cutlvl;
  std::vector< Double_t > error_y, error_x;
  std::vector< Double_t > SNR, error_snr_y;
  Double_t fc_nh3 = 115097000000;//58200800000;
  Double_t fc_c12 = 11088600000;//4380130000;
  Double_t del_fc_nh3 = TMath::Sqrt(fc_nh3);
  Double_t del_fc_c12 = TMath::Sqrt(fc_c12);
  Double_t del_c = 0.02;

  for( int i = 0; i <= max_cutlvl; i++ ){
    /*    TCanvas *c1 = new TCanvas( Form("c_%d",i), Form("c_%d",i), 800, 600 );
    gStyle->SetOptStat(10);
    h_phanglvl_nh3[i]->SetFillColorAlpha(kRed,0.7);
    h_phanglvl_c12[i]->SetFillColorAlpha(kBlue+2,0.7);
    h_phanglvl_nh3[i]->GetXaxis()->SetTitle("Angle between Calculated and Measured Photon [deg]");
    h_phanglvl_nh3[i]->Draw("hist");
    h_phanglvl_c12[i]->Draw("same");
    */

    Double_t rate_nh3 = (h_phanglvl_nh3[i]->GetEntries())/(fc_nh3);
    Double_t rate_c12 = (h_phanglvl_c12[i]->GetEntries())/(fc_c12);

    Double_t n_nh3 = h_phanglvl_nh3[i]->GetEntries();
    Double_t n_c12 = h_phanglvl_c12[i]->GetEntries();
    Double_t del_nh3 = TMath::Sqrt(n_nh3);
    Double_t del_c12 = TMath::Sqrt(n_c12);

    Double_t D =  1 - 0.726*(rate_c12/rate_nh3);

    Double_t del_D = D*(TMath::Sqrt( pow( ((n_c12/n_nh3)*(fc_nh3/fc_c12)*del_c), 2 ) +
				     pow( (0.726/n_nh3)*(fc_nh3/fc_c12)*del_c12, 2) +
				     pow( (0.726*n_c12)/(n_nh3*n_nh3) * (fc_nh3/fc_c12) * del_nh3, 2 ) +
				     pow( ((0.726*n_c12)/n_nh3) * (1.0/fc_c12) * del_fc_nh3, 2 ) +
				     pow( ((0.726*n_c12)/n_nh3) * (fc_nh3/(fc_c12*fc_c12)) * del_fc_c12, 2 ) ) );
    
    std::cout << "Dilution error " <<  del_D << std::endl;

    //CALCULATE SIGNAL TO NOISE RATIO AND ERROR
    Double_t snr = rate_nh3/rate_c12;
    Double_t del_snr = snr*(TMath::Sqrt( pow( (1/rate_c12)*(del_nh3), 2 ) +
					 pow( (rate_nh3/(rate_c12*rate_c12))*(del_c12), 2 )) );					 


    std::cout << " SNR error " << del_snr << std::endl;
    std::cout << " SNR " << snr << std::endl;

    std::cout << " Rates for NH3 at cut lvl " << i << " " << h_phanglvl_nh3[i]->GetEntries() << std::endl;
    std::cout << " Rates for C12 at cut lvl " << i << " " << h_phanglvl_c12[i]->GetEntries() << std::endl;

    error_x.push_back(0.0);
    cutlvl.push_back( min_cut + i/100.0 );

    dilution.push_back( 1 - 0.726*(rate_c12/rate_nh3));
    error_y.push_back( del_D );

    SNR.push_back(rate_nh3/rate_c12);
    error_snr_y.push_back( 0 );
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->Divide(2,1);

  c1->cd(1);
  TGraphErrors *g_dil = new TGraphErrors(dilution.size(), &(cutlvl[0]), &(dilution[0]), &(error_x[0]), &(error_y[0]) );
  g_dil->SetName("Dilution Factor vs Photon Angle Cut ");
  g_dil->SetTitle("Dilution Factor vs Photon Angle Cut ");
  g_dil->GetXaxis()->SetTitle("Photon Angle Cut [deg]");
  g_dil->GetYaxis()->SetTitle("Dilution Factor");
  g_dil->GetXaxis()->CenterTitle();
  g_dil->GetYaxis()->CenterTitle();
  g_dil->SetMarkerColor(kBlue+2);
  g_dil->SetMarkerStyle(20);
  g_dil->SetMarkerSize(0.85);
  g_dil->Draw("AP");

  c1->cd(2);
  TGraphErrors *g_snr = new TGraphErrors(SNR.size(), &(cutlvl[0]), &(SNR[0]), &(error_x[0]), &(error_snr_y[0]) );
  g_snr->SetName("Signal to Noise for Photon Angle Cut ");
  g_snr->SetTitle("Signal to Noise vs Photon Angle Cut ");
  g_snr->GetXaxis()->SetTitle("Photon Angle Cut [deg]");
  g_snr->GetYaxis()->SetTitle("Signal to Noise");
  g_snr->GetXaxis()->CenterTitle();
  g_snr->GetYaxis()->CenterTitle();
  g_snr->SetMarkerColor(kBlue+2);
  g_snr->SetMarkerStyle(20);
  g_snr->SetMarkerSize(0.85);
  g_snr->Draw("AP");

}
  
