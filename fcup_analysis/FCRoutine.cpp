#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TColor.h"
#include "TLine.h"

#include "tDVCS.C"

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


void FCRoutine( const char* rootfile ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfile);

  tPID *treevar = new tPID(fchain);
  std::cout << fchain->GetEntries() << " to process " << std::endl;

  std::map<Double_t, std::vector<Double_t>> m_fctot_nh3;
  std::vector<Double_t> fcsum_nh3;

  std::map<Double_t, std::vector<Double_t>> m_fctot_c12;
  std::vector<Double_t> fcsum_c12;


  for ( Long64_t nn = 0; nn < fchain->GetEntries(); nn++ ){
    fchain->GetEntry(nn);
    if ( treevar->RunNumber < 59829 && (treevar->FC0 != 0 || treevar->FC1 != 0 ) ){
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
      bool deltatheta_pass = deltheta/3.14159 * 180.0 < 1.5;
      bool groupB = period == 'B';
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
      
      // Boolean tests for MM2, PhotonAngle, and ??
      bool mm2_test = q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && deltatheta_pass && mm2epg_pass && groupB;
      bool photonangle_test = q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB;
      
      //This is to plot the MM2 for both NH3 and C12 targets. The variable mm represents the mm2 from e_i + p_i - e_f - p_f
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && deltatheta_pass && mm2epg_pass && groupB && mm2_pass ){
	
	if( target_nh3 ){
	  std::cout << " run " << treevar->RunNumber std::endl;
	  std::cout << " target " << target << std::endl;
	  std::cout << " FC0 " << treevar->FC0 << std::endl;
	  std::cout << " FC1 " << treevar->FC1 << std::endl;
	  Double_t fctot = treevar->FC0 + treevar->FC1;
	  std::cout << " FC total " << fctot << std::endl;
	  fcsum_nh3.push_back(fctot);
	  m_fctot_nh3[treevar->RunNumber] = fcsum_nh3;
	  
	}
	if( target_c12 ) { 
	  
	  std::cout << " run " << treevar->RunNumber std::endl;
	  std::cout << " target " << target << std::endl;
	  std::cout << " FC0 " << treevar->FC0 << std::endl;
	  std::cout << " FC1 " << treevar->FC1 << std::endl;
	  Double_t fctot_c12 = treevar->FC0 + treevar->FC1;
	  std::cout << " FC total " << fctot_c12 << std::endl;
	   
	  fcsum_c12.push_back(fctot_c12);
	  m_fctot_c12[treevar->RunNumber] = fcsum_c12;
	}
      }
    }
  }

  for(std::map<Double_t, std::vector<Double_t> >

}

