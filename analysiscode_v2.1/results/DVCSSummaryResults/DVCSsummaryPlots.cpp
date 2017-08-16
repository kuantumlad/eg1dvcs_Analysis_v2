//###########################################################
//
//
// Created by: Brandon Clary
// Written: 7/14/2017
// Purpose: This macro is used for drawing most of the plots
//          needed for the DVCSrecap paper.
//          FC values are from FCRoutine.cpp           
//          
//
//
//
//###########################################################
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
#include "TMultiGraph.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TLegend.h"
#include "TPolyLine.h"
#include "TF1.h"

#include "tPID.C"

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <cmath>

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

void DVCSsummaryPlots( const char* rootfiles ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfiles);

  tPID *treevar = new tPID(fchain);
  std::cout << ">> Processing " << fchain->GetEntries() << " entries " << std::endl;
  Long64_t nnentries = fchain->GetEntries();

  //DIS Histo
  TH1D *h_dis_mm2_nh3 = new TH1D("h_dis_mm2_nh3","", 200, -1.0, 4.0);
  TH1D *h_dis_mm2_c12 = new TH1D("h_dis_mm2_c12","", 200, -1.-0, 4.0 );

  //DVCS Histo
  TH1D *h_dvcs_mm2_nh3 = new TH1D("h_dvcs_mm2_nh3","",200, -1.0, 3.0);
  TH1D *h_dvcs_mm2_c12 = new TH1D("h_dvcs_mm2_c12","",200, -1.0, 3.0);

  TH1D *h_dvcs_mmegx_nh3 = new TH1D("h_dvcs_mmegX_nh3","", 200, -0.5, 3.0);
  TH1D *h_dvcs_mmegx_c12 = new TH1D("h_dvcs_mmegX_c12","", 200, -0.5, 3.0);

  TH1D *h_dvcs_theta_nh3 = new TH1D("h_dvcs_theta_nh3","",200, 0.0, 6.0);
  TH1D *h_dvcs_theta_c12 = new TH1D("h_dvcs_theta_c12","",200, 0.0, 6.0);

  TH1D *h_dvcs_missE_nh3_ec = new TH1D("h_dvcs_missE_nh3_ec","",200,-0.50,2.0);
  TH1D *h_dvcs_missE_c12_ec = new TH1D("h_dvcs_missE_c12_ec","",200,-0.50,2.0);

  TH1D *h_dvcs_missE_nh3_ic = new TH1D("h_dvcs_missE_nh3_ic","",200,-0.50,2.0);
  TH1D *h_dvcs_missE_c12_ic = new TH1D("h_dvcs_missE_c12_ic","",200,-0.50,2.0);

  TH2D *h2_dvcs_q2x = new TH2D("h_dvcs_q2x","",200,0.075, 0.63, 200, 0.0, 5.5 ); 
  TH2D *h2_dvcs_tx = new TH2D("h_dvcs_tx","",200,0.1, 0.65, 200, 0.0, 2.0 ); 

  Double_t massthickness = 0.726;

  std::set<Double_t> runlist;

  for (Long64_t nn = 0; nn< nnentries; nn++){
    fchain->GetEntry(nn);

    std::string period = (std::string)*(treevar->periodID);    
    std::string target = (std::string)(*treevar->targetType);   

    bool groupB = period == 'B';
    bool groupA = period == 'A';
    bool target_nh3t = target == "NH3T";
    bool target_nh3b = target == "NH3B";
    bool target_nh3s = target == "NH3S";
    bool target_nh3 = target_nh3t || target_nh3b;
    bool target_c12 = target == "C12";

    if( (groupA || groupB) && (target_nh3t || target_nh3b || target_c12) ){
      runlist.insert(treevar->run);
    }

    /*    if( groupB && (treevar->FC0 > 1000 && treevar->FC1 > 1000) ){
 	
 
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
      
      TLorentzVector el_lv( treevar->el_px, treevar->el_py, treevar->el_pz, treevar->el_E);
      TLorentzVector pr_lv( treevar->pr_px, treevar->pr_py, treevar->pr_pz, treevar->pr_E);
      TLorentzVector ph_lv( treevar->ph_px, treevar->ph_py, treevar->ph_pz, treevar->ph_E);
      TLorentzVector el_b( 0.0, 0.0, treevar->beamEnergy, treevar->beamEnergy);
      TLorentzVector target_lv( 0.0, 0.0, 0.0, 0.9382720);
      
      TLorentzVector missing_lv = el_b + target_lv - (el_lv + pr_lv + ph_lv );
      Double_t missing_energy = missing_lv.E();  

      TLorentzVector missingeg_lv = el_b + target_lv - (el_lv + ph_lv );
      Double_t mm2egx = missingeg_lv.Mag2(); 

      //DIS CUTS FOR NH3
      if( q2_pass && w_pass  && phE_pass && groupB && (target == "NH3B" || target == "NH3T") ){
	h_dis_mm2_nh3->Fill(mm);      
      }
      //DIS CUTS FOR C12
      if( q2_pass && w_pass && phE_pass && groupB && (target == "C12") ){
	h_dis_mm2_c12->Fill(mm);
      }
      
      //DVCS CUTS FOR NH3
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "NH3B" || target == "NH3T") && deltatheta_pass){
     	h_dvcs_mm2_nh3->Fill(mm);

	if ( photonEC ){
	  h_dvcs_missE_nh3_ec->Fill(missing_energy);
	}
	if ( photonIC ){
	  h_dvcs_missE_nh3_ic->Fill(missing_energy);
	}
      }

      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "NH3B" || target == "NH3T") && mm2_pass ){
	h_dvcs_theta_nh3->Fill(deltheta/3.14159 * 180.0);
      }

      //DVCS CUTS FOR C12
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "C12") && deltatheta_pass ){
     	h_dvcs_mm2_c12->Fill(mm);
	
	if( photonEC ){
	  h_dvcs_missE_c12_ec->Fill(missing_energy);
	}
	if( photonIC ){
	  h_dvcs_missE_c12_ic->Fill(missing_energy);
	}
      }      
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "C12") && mm2_pass ){
	h_dvcs_theta_c12->Fill(deltheta/3.14159 * 180.0);
      }
    
      //BINNING INFORMATION
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "NH3B" || target == "NH3T") && deltatheta_pass && mm2_pass){
	h2_dvcs_q2x->Fill(x,q2);
	h2_dvcs_tx->Fill(x,-t);
      }

      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "NH3B" || target == "NH3T") && deltatheta_pass && mm2_pass){
	h_dvcs_mmegx_nh3->Fill(mm2egx);
      }
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB && (target == "C12") && deltatheta_pass && mm2_pass){
	h_dvcs_mmegx_c12->Fill(mm2egx);
      }
    
    }
  }

  Double_t fc_nh3 = 115097000000;//58200800000;
  Double_t fc_c12 = 11088600000;//4380130000;


  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1","",600,600);
  TLegend *leg1 = new TLegend(0.7, 0.7, 0.85, 0.85);
  h_dis_mm2_nh3->Scale(1.0/fc_nh3);
  h_dis_mm2_c12->Scale(massthickness/fc_c12);
  h_dis_mm2_nh3->SetLineColor(kBlack);
  h_dis_mm2_c12->SetLineColor(kRed);
  h_dis_mm2_nh3->GetXaxis()->SetTitle("MM^{2}_{epX} [GeV]");
  h_dis_mm2_nh3->GetXaxis()->CenterTitle();
  h_dis_mm2_nh3->Draw("hist");
  h_dis_mm2_c12->Draw("same+hist");
  leg1->AddEntry(h_dis_mm2_nh3,"NH_{3} target");
  leg1->AddEntry(h_dis_mm2_c12,"Carbon-12 target");
  leg1->SetLineWidth(0);
  leg1->Draw("same");

  TCanvas *c2 = new TCanvas("c2","",600,600);
  TLegend *leg2 = new TLegend(0.7, 0.7, 0.85, 0.85);
  TLine *mm2_cut_max = new TLine( 0.3, 0.0, 0.3, h_dvcs_mm2_nh3->GetMaximum()/fc_nh3 );
  TLine *mm2_cut_min = new TLine( -0.3, 0.0, -0.3, h_dvcs_mm2_nh3->GetMaximum()/fc_nh3 );
  mm2_cut_max->SetLineColor(kRed);
  mm2_cut_min->SetLineColor(kRed);
  h_dvcs_mm2_nh3->Scale(1.0/fc_nh3);
  h_dvcs_mm2_c12->Scale(massthickness/fc_c12);
  h_dvcs_mm2_c12->SetLineColor(kRed);
  h_dvcs_mm2_nh3->GetXaxis()->SetTitle("MM^{2}_{epX} [GeV^{2}]");
  h_dvcs_mm2_nh3->GetXaxis()->CenterTitle();
  h_dvcs_mm2_nh3->Draw("hist");
  h_dvcs_mm2_c12->Draw("same+hist");
  mm2_cut_max->Draw("same");
  mm2_cut_min->Draw("same");
  leg2->AddEntry(h_dvcs_mm2_nh3,"NH_{3} target");
  leg2->AddEntry(h_dvcs_mm2_c12,"Carbon-12 target");
  leg2->SetLineWidth(0);
  leg2->Draw("same");

  TCanvas *c3 = new TCanvas("c3","",600,600);
  TLegend *leg3 = new TLegend(0.7, 0.7, 0.85, 0.85);
  h_dvcs_theta_nh3->Scale(1.0/fc_nh3);
  h_dvcs_theta_c12->Scale(1.0/fc_c12);
  h_dvcs_theta_c12->SetLineColor(kRed);
  h_dvcs_theta_nh3->GetXaxis()->SetTitle("#theta_{#gamma_{det} #gamma_{calc}} [deg]");
  h_dvcs_theta_nh3->GetXaxis()->CenterTitle();
  h_dvcs_theta_nh3->Draw("hist");
  h_dvcs_theta_c12->Draw("same+hist");
  leg3->AddEntry(h_dvcs_theta_nh3,"NH_{3} target");
  leg3->AddEntry(h_dvcs_theta_c12,"Carbon-12 target");
  leg3->SetLineWidth(0);
  leg3->Draw("same");

  TCanvas *c4 = new TCanvas("c4","",1200,600);
  TLegend *leg4 = new TLegend(0.7, 0.7, 0.85, 0.85);
  TLegend *leg4a = new TLegend(0.4, 0.7, 0.55, 0.85);
  c4->Divide(2,1);
  c4->cd(1);
  //  h_dvcs_missE_nh3_ec->Scale(1.0/fc_nh3);
  //h_dvcs_missE_c12_ec->Scale(1.0/fc_c12);
  h_dvcs_missE_c12_ec->SetLineColor(kRed);
  h_dvcs_missE_nh3_ec->GetXaxis()->SetTitle("Missing Energy of ep #rightarrow epX for #gamma_{EC}");
  h_dvcs_missE_nh3_ec->GetXaxis()->CenterTitle();
  h_dvcs_missE_nh3_ec->Draw("hist");
  h_dvcs_missE_c12_ec->Draw("same+hist");
  leg4a->AddEntry(h_dvcs_missE_nh3_ec,"NH_{3} EC photon");
  leg4a->AddEntry(h_dvcs_missE_c12_ec,"Carbon-12 EC photon");
  leg4a->SetLineWidth(0);
  leg4a->Draw("same");


  c4->cd(2);
  h_dvcs_missE_nh3_ic->Scale(1.0/fc_nh3);
  h_dvcs_missE_c12_ic->Scale(1.0/fc_c12);
  h_dvcs_missE_c12_ic->SetLineColor(kRed);
  h_dvcs_missE_nh3_ic->GetXaxis()->SetTitle("Missing Energy of ep #rightarrow epX for #gamma_{IC}");
  h_dvcs_missE_nh3_ic->GetXaxis()->CenterTitle();
  h_dvcs_missE_nh3_ic->Draw("hist");
  h_dvcs_missE_c12_ic->Draw("same+hist");
  leg4->AddEntry(h_dvcs_missE_nh3_ic,"NH_{3} IC photon");
  leg4->AddEntry(h_dvcs_missE_c12_ic,"Carbon-12 IC photon");
  leg4->SetLineWidth(0);
  leg4->Draw("same");


  //BINNING INFORMATION
  std::vector<Double_t> q2_point;
  for( Int_t i = 15; i <= 48; i++ ){
    Double_t q2_value = 4*0.6*4.4*std::pow(TMath::Sin((i/2.0) * (180.0/3.14159)),2);
    //std::cout << q2_value << std::endl;
    q2_point.push_back(q2_value);
  }

  std::vector<Double_t> x_point;
  Double_t x_value = 0.1;
  while( x_value <= 0.2 ){
    //std::cout << x_value << std::endl;
    x_point.push_back(x_value);
    x_value = x_value + 0.003125;
  }


  TCanvas *c5 = new TCanvas("c5","",600,600);
  TLine *x1 = new TLine( 0.1, 0.08, 0.65, 0.08 );
  TLine *x2 = new TLine( 0.1, 0.18, 0.65, 0.18 );
  TLine *x3 = new TLine( 0.1, 0.30, 0.65, 0.30 );
  TLine *x4 = new TLine( 0.1, 0.70, 0.65, 0.70 );
  TLine *x5 = new TLine( 0.1, 2.0, 0.65, 2.0 );

  TLine *t1 = new TLine( 0.1, 0.0,  0.1, 2.0 );
  TLine *t2 = new TLine( 0.2, 0.0, 0.2, 2.0 );
  TLine *t3 = new TLine( 0.3, 0.0, 0.3, 2.0 );
  TLine *t4 = new TLine( 0.4, 0.0, 0.4, 2.0 );

  h2_dvcs_tx->GetXaxis()->SetTitle("x_{bj}");
  h2_dvcs_tx->GetYaxis()->SetTitle("-t [GeV^{2}]");
  h2_dvcs_tx->Draw("colz");
  x1->SetLineColor(kRed);
  x1->SetLineWidth(2);
  x1->Draw("same");
  x2->SetLineColor(kRed);
  x2->SetLineWidth(2);
  x2->Draw("same");
  x3->SetLineColor(kRed);
  x3->SetLineWidth(2);
  x3->Draw("same");
  x4->SetLineColor(kRed);
  x4->SetLineWidth(2);
  x4->Draw("same");
  x5->SetLineColor(kRed);
  x5->SetLineWidth(2);
  x5->Draw("same");

  t1->SetLineColor(kRed);
  t1->SetLineWidth(2);
  t1->Draw("same");
  t2->SetLineColor(kRed);
  t2->SetLineWidth(2);
  t2->Draw("same");
  t3->SetLineColor(kRed);
  t3->SetLineWidth(2);
  t3->Draw("same");
  t4->SetLineColor(kRed);
  t4->SetLineWidth(2);
  t4->Draw("same");


  TCanvas *c6 = new TCanvas("c6","",600,600);
  TF1 *qcut = new TF1("qcut","2*0.938*x*(5.887 - (2*0.938*5.954*x)/(2*0.938*x + 4*5.887*sin((47.0/2.0)*(3.14159/180.0))*sin((47.0/2.0)*(3.14159/180.0))))",0.072,0.624);
  TF1 *wcut = new TF1("wcut","(0.938*0.938 - 2*2)*( x/(x-1) )",0.18,0.625);
  TF1 *icshadowcast = new TF1("icshadowcast","2*0.938*x*(5.887 - (2*0.938*5.954*x)/(2*0.938*x + 4*5.887*sin((15.0/2.0)*(3.14159/180.0))*sin((15.0/2.0)*(3.14159/180.0))))",0.072,0.52);
  TLine *q2cut = new TLine(0.073,1.0,0.52,1.0);
  h2_dvcs_q2x->GetXaxis()->SetTitle("x_{bj}");
  h2_dvcs_q2x->GetXaxis()->CenterTitle();
  h2_dvcs_q2x->GetYaxis()->SetTitle("Q_{2} [Gev^{2}]");
  h2_dvcs_q2x->GetYaxis()->CenterTitle();
  h2_dvcs_q2x->Draw("colz");
  qcut->SetLineColor(kRed);
  qcut->Draw("same");
  wcut->SetLineColor(kBlue);
  wcut->Draw("same");
  icshadowcast->SetLineColor(kBlack);
  icshadowcast->Draw("same");
  q2cut->SetLineColor(kMagenta);
  q2cut->SetLineWidth(2);
  q2cut->Draw("same");

  TCanvas *c7 = new TCanvas("c7","",600, 600 );
  TF1 *qcut1 = new TF1("qcut1","2*0.938*x*(5.887 - (2*0.938*5.954*x)/(2*0.938*x + 4*5.887*sin((15.0/2.0)*(3.14159/180.0))*sin((15.0/2.0)*(3.14159/180.0))))",0.142,0.32);
  TF1 *qcut2 = new TF1("qcut2","2*0.938*x*(5.887 - (2*0.938*5.954*x)/(2*0.938*x + 4*5.887*sin((48.0/2.0)*(3.14159/180.0))*sin((48.0/2.0)*(3.14159/180.0))))",0.08,0.65);
  TF1 *qcut3 = new TF1("qcut3","2*0.938*x*(5.887 - (2*0.938*5.954*x)/(2*0.938*x + 4*5.887*sin((34.0/2.0)*(3.14159/180.0))*sin((34.0/2.0)*(3.14159/180.0))))",0.2,0.3);
  TF1 *wcuta = new TF1("wcuta","(0.938*0.938 - 2*2)*( x/(x-1) )",0.28,0.65);
  TF1 *icshadowcasta = new TF1("icshadowcasta","2*0.938*x*(5.887 - (2*0.938*5.954*x)/(2*0.938*x + 4*5.887*sin((15.0/2.0)*(3.14159/180.0))*sin((15.0/2.0)*(3.14159/180.0))))",0.142,0.32);
  
  TLine *x1a = new TLine(0.1, 0.95, 0.1, 1.2 );
  TLine *x2a = new TLine(0.2, .75, 0.2, 2.20 );
  TLine *x3a = new TLine(0.3, 1.3, 0.3, 3.3 );
  TLine *q2cuta = new TLine(0.1, 1.0, 0.2, 1.0);
  h2_dvcs_q2x->GetXaxis()->SetTitle("x_{bj}");
  h2_dvcs_q2x->GetXaxis()->CenterTitle();
  h2_dvcs_q2x->GetYaxis()->SetTitle("Q_{2} [Gev^{2}]");
  h2_dvcs_q2x->GetYaxis()->CenterTitle();
  h2_dvcs_q2x->Draw("colz");
  qcut1->SetLineColor(kRed);
  qcut1->Draw("same");
  qcut2->SetLineColor(kRed);
  qcut2->Draw("same");
  qcut3->SetLineColor(kRed);
  qcut3->Draw("same");
  wcuta->SetLineColor(kRed);
  icshadowcasta->SetLineColor(kRed);
  wcuta->Draw("same");
  icshadowcasta->Draw("same");
  x1a->SetLineColor(kRed);
  x2a->SetLineColor(kRed);
  x3a->SetLineColor(kRed);
  x1a->SetLineWidth(2);
  x2a->SetLineWidth(2);
  x3a->SetLineWidth(2);
  x1a->Draw("same");
  x2a->Draw("same");
  x3a->Draw("same");
  q2cuta->SetLineColor(kRed);
  q2cuta->SetLineWidth(2);
  q2cuta->Draw("same");

  //FITTING MMEGX HISTOGRAMS TO GET MEAN
  //THIS WILL TELL US HOW MUCH IT IS SHIFTED 
  //FROM THE MASS OF THE PROTON
  std::cout << " >> Fitting MM2EGX NH3" << std::endl;
  FittingMethod(h_dvcs_mmegx_nh3);
  std::cout << " >> Fitting MM2EGX C12" << std::endl;
  FittingMethod(h_dvcs_mmegx_c12);

  TCanvas *c8 = new TCanvas("c8","",600,600);
  h_dvcs_mmegx_nh3->GetXaxis()->SetTitle("MM^{2}_{e#gamma}");
  h_dvcs_mmegx_nh3->GetXaxis()->CenterTitle();
  h_dvcs_mmegx_nh3->SetLineColor(kBlue);
  h_dvcs_mmegx_c12->SetLineColor(kRed);
  h_dvcs_mmegx_nh3->Scale(1.0/fc_nh3);
  h_dvcs_mmegx_c12->Scale(1.0/fc_c12);
  h_dvcs_mmegx_nh3->Draw();
  h_dvcs_mmegx_c12->Draw("same");
    */
  }
  std::cout << "Comparison Counter " << runlist.size() << std::endl;

}
