/////////////////////////////////////////////////
//
//
//
// Written by Brandon Clary
// 6/20/2017
// icenenergy_correction is meant to look at the IC photon
// energy in 7 different energy bins. Then a 2d histogram 
// is created to look at the distribution over the surface of the
// IC. A fit is created to correct this. 
//
//
////////////////////////////////////////////////

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TLine.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TF1.h"
#include "TLegend.h"

#include "tPID.C"

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>

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
  h_temp->Draw();
  //  c_temp->SaveAs(Form("%s",h_temp->GetName()));

  //end fitting method
  ///////////////////////////////////////////////////////
}

void icenergy_correction( const char* rootfile ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfile);

  tPID *treevar = new tPID(fchain);
  std::cout << fchain->GetEntries() << " to process " << std::endl;
 

  std::vector<TH1D*> h_ice;
  for( Int_t ice_bin = 0; ice_bin < 7; ice_bin++ ){
    h_ice.push_back(new TH1D(Form("h_ice_%d",ice_bin),Form("h_ice_%d",ice_bin), 80, -0.5, 1.5));
  }

  std::vector<Double_t> ice_min;
  std::vector<Double_t> ice_max;
  for( Int_t j = 0; j < 7; j++){
    ice_min.push_back(1.5 + j*0.5);
    //    std::cout<< 1.5 + j*0.5 << std::endl;
  }
  for( Int_t j = 0; j < 7; j++){
    //    std::cout<< 2.0 + j*0.5 << std::endl;
    ice_max.push_back(2.0 + j*0.5); 
  }


  TH2D *h_icetheta = new TH2D("h_icetheta","",100,-0.5,1.5, 100, 0.0, 25.0 );
  TH1D *h_icr = new TH1D("h_icr","",100,3.0,25.0);
  TH1D *h_ictheta = new TH1D("h_ictheta","",100,0.0,16.0);
  TVector3 zn;
  zn.SetXYZ(0,0,1.);
  Double_t ic_dist = 67.97;
  Double_t ic_thickness = 19.44;

  Long64_t nentries = fchain->GetEntries();

  for ( Long64_t nn = 0; nn < nentries; nn++ ){
    fchain->GetEntry(nn);
   
    if ( (std::string)(*treevar->periodID) == 'B' && (treevar->FC0 > 1000 && treevar->FC1 > 1000 ) ){ // 59829
      if ( nn%1000000 == 0 ) { std::cout << nn << std::endl; }
     
      //GET TREE VARIABLES
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
      Double_t elvz = treevar->el_vertex;
      Double_t prvz = treevar->pr_vertex;
      Double_t ev_vz = (elvz + prvz)/2.0;


      //SET EVENT BOOLEANS 
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
      bool target_nh3t = target == "NH3T";
      bool target_nh3b = target == "NH3B";
      bool target_nh3 = target_nh3t || target_nh3b;
      bool target_c12 = target == "C12";
      
      bool groupB = period == 'B';
      bool DVCS_pass = false;

      TLorentzVector el_lv( treevar->el_px, treevar->el_py, treevar->el_pz, treevar->el_E);
      TLorentzVector pr_lv( treevar->pr_px, treevar->pr_py, treevar->pr_pz, treevar->pr_E);
      TLorentzVector ph_lv( treevar->ph_px, treevar->ph_py, treevar->ph_pz, treevar->ph_E);
      TLorentzVector el_b( 0.0, 0.0, treevar->beamEnergy, treevar->beamEnergy);
      TLorentzVector target_lv( 0.0, 0.0, 0.0, 0.9382720);
      
      TLorentzVector missing_lv = el_b + target_lv - (el_lv + pr_lv + ph_lv );
      Double_t missing_energy = missing_lv.E();  

      TLorentzVector missingeg_lv = el_b + target_lv - (el_lv + ph_lv );
      Double_t mm2egx = missingeg_lv.Mag2(); 

      //This is to plot the MM2 for both NH3 and C12 targets. The variable mm represents the mm2 from e_i + p_i - e_f - p_f
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && deltatheta_pass && mm2epg_pass && groupB && mm2_pass ){
	if( target_nh3t || target_nh3b ){	
	  for( int j = 0; j < 7; j++ ){
	    //	std:cout << " min " << ice_min[j] << " Energy " << ph_lv.E() << " max " << ice_max[j] <<  std::endl;
	    if( ice_min[j] <= ph_lv.E() && ph_lv.E() < ice_max[j] ){
	      //std::cout << ph_lv.E() << std::endl;
	      h_ice[j]->Fill(missing_energy);
	    }
	  }
	  
	  h_icetheta->Fill(missing_energy, (std::fabs(ev_vz) - ic_thickness)*TMath::Tan(zn.Angle((ph_lv.Vect()).Unit())*(180.0/3.14159)) );
	  Double_t theta = zn.Angle((ph_lv.Vect()).Unit());
	  h_icr->Fill( (std::fabs(ev_vz) + ic_thickness )*tan(theta));
	  h_ictheta->Fill(zn.Angle((ph_lv.Vect()).Unit())*(180.0/3.14159));
	}
	
      }
    }
  }

  //DRAW HISTOGRAMS
  TCanvas *c1 = new TCanvas("c1","",2100,800);
  c1->Divide(2,2);
  gStyle->SetOptStat(0);
  c1->cd(1);
  h_ice[5]->SetLineColor(46);
  h_ice[5]->Draw("same");
  
  for(int i = 0; i < 7; i++){
    if( i == 5 ) continue;
    h_ice[i]->SetLineColor(i+1);
    h_ice[i]->Draw("same");
  }

  h_ice[5]->GetXaxis()->SetTitle("Missing Energy Photon Energy [GeV]");
  h_ice[5]->GetXaxis()->CenterTitle();

  c1->cd(2);
  h_icetheta->Draw("colz");

  c1->cd(3);
  h_icr->Draw();

  c1->cd(4);
  h_ictheta->Draw();

}
