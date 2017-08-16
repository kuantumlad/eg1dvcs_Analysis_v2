/////////////////////////////////////////////////
//
//
//
// Written by Brandon Clary
// 6/16/2017
// This is the code that is to be used to calculate the 
// FC counter rates. It also takes into account the status 
// of the waveplate ( that was done in the PID code )
//
//
//
////////////////////////////////////////////////

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


// Routine to get unique elements in vector. Accomplised this same task by using cpp's set container.
void FCCounter( std::map<Double_t, std::vector< Double_t >> tempmap ){
  Double_t fc_total = 0.0;
  for( std::map< Double_t,std::vector<Double_t> >::iterator it = tempmap.begin(); it != tempmap.end(); ++it ){
    //std::cout << " run " << it->first  << std::endl;
    std::vector< Double_t > temp;
    temp.push_back( (it->second)[0] );
    bool check = false;
    for( std::vector<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      
      //std::cout << ">>>it2 " << *it2 << std::endl;
      for( std::vector<Double_t>::iterator tempit = temp.begin(); tempit != temp.end(); ++tempit ){
	if( *it2 == *tempit ){
	  check = false;
	}
	else if( *it2 != *tempit ){
	  check = true;
	}
	if( check == false ){ break; }
      }
      
      if( check ){
	//std::cout << " pushing back " << *it2 << std::endl;
	temp.push_back(*it2);
      }	
    }

    for( std::vector<Double_t>::iterator finalit = temp.begin(); finalit != temp.end(); ++finalit ){
      //std::cout << "final it " << *finalit << std::endl;
      fc_total = *finalit + fc_total;
    }
    temp.clear();
  }
  std::cout << " Total is " << fc_total << std::endl;
} 


void FCRoutine( const char* rootfile ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfile);

  tPID *treevar = new tPID(fchain);
  std::cout << fchain->GetEntries() << " to process " << std::endl;


  //HISTOGRAMS TO FIND OVERALL RUN PROPERTIES
  TH1D *h_runratio_nh3 = new TH1D("h_runratio_nh3","",50,0.0000000001,0.0000015);
  TH1D *h_runratio_c12 = new TH1D("h_runratio_c12","",50,0.0000000001,0.0000015);

  std::map<Double_t, std::vector<Double_t>> m_fctot_nh3, m_fc0_nh3, m_fc1_nh3;
  std::map<Double_t, std::set<Double_t>> s_fctot_nh3, s_fc0_nh3, s_fc1_nh3, s_fctot_nh3_P, s_fctot_nh3_N;
  std::vector<Double_t> fcsum_nh3;

  std::map<Double_t, std::vector<Double_t>> m_fctot_c12, m_fc0_c12, m_fc1_c12;
  std::map<Double_t, std::set<Double_t>> s_fctot_c12, s_fc0_c12, s_fc1_c12, s_fctot_c12_P,s_fctot_c12_N;
  std::vector<Double_t> fcsum_c12;

  Double_t dvcs_nh3 = 0.0;
  Double_t dvcs_c12 = 0.0;
  std::map<Double_t, Double_t> m_ratedvcs_nh3, m_ratedvcs_c12;

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

      //This is to plot the MM2 for both NH3 and C12 targets. The variable mm represents the mm2 from e_i + p_i - e_f - p_f
      if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && deltatheta_pass && mm2epg_pass && groupB && mm2_pass ){
	DVCS_pass = true;
      }
      Double_t fc0 = treevar->FC0;
      Double_t fc1 = treevar->FC1;
      
      if( target_nh3 ){
	//std::cout << " run " << treevar->run << std::endl;
	//std::cout << " target " << target << std::endl;
	//std::cout << " FC0 " << treevar->FC0 << std::endl;
	//std::cout << " FC1 " << treevar->FC1 << std::endl;
	s_fc0_nh3[treevar->run].insert(fc0);
	s_fc1_nh3[treevar->run].insert(fc1);
	s_fctot_nh3[treevar->run].insert(fc0 + fc1);

	//ADDED THIS ON 7-19 for FC values for two target polarizations. REMOVE WHEN DONE
	if( targetPol > 0 ){
	s_fctot_nh3_P[treevar->run].insert(fc0 + fc1);
	}
	else if( targetPol < 0 ){
	s_fctot_nh3_N[treevar->run].insert(fc0 + fc1);
	}
	if( DVCS_pass ){
	  m_ratedvcs_nh3[treevar->run]+=1;
	  dvcs_nh3++;
	}
      }
      if( target_c12 ) {   
	//std::cout << " run " << treevar->run << std::endl;
	//std::cout << " target " << target << std::endl;
	//std::cout << " FC0 " << treevar->FC0 << std::endl;
	//std::cout << " FC1 " << treevar->FC1 << std::endl;
	s_fc0_c12[treevar->run].insert(fc0);
	s_fc1_c12[treevar->run].insert(fc1);

	s_fctot_c12[treevar->run].insert(fc0 + fc1);
	
	if( DVCS_pass ){
	  m_ratedvcs_c12[treevar->run]+=1;
	  dvcs_c12++;
	  }
      }
    }
  }
  std::cout << " ------------- Totaling FC counts -------------- " << std::endl;
   
  Double_t fc0_tot_nh3 = 0.0;
  Double_t fc1_tot_nh3 = 0.0;
  Double_t fc0_tot_c12 = 0.0;
  Double_t fc1_tot_c12 = 0.0;

  for(std::map<Double_t, std::set<Double_t>>::iterator it = s_fc0_nh3.begin(); it != s_fc0_nh3.end(); ++it ){
    //std::cout << " Run " << it->first << std::endl;
    //std::cout << " set size " << (it->second).size() << std::endl;
    for(std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << *it2 << std::endl;
      fc0_tot_nh3+=(*it2);
    }
  }

  for(std::map<Double_t, std::set<Double_t>>::iterator it = s_fc1_nh3.begin(); it != s_fc1_nh3.end(); ++it ){
    //std::cout << " Run " << it->first << std::endl;
    //std::cout << " set size " << (it->second).size() << std::endl;
    for(std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << *it2 << std::endl;
      fc1_tot_nh3+=(*it2);
    }
  }

  for(std::map<Double_t, std::set<Double_t>>::iterator it = s_fc0_c12.begin(); it != s_fc0_c12.end(); ++it ){
    //std::cout << " Run " << it->first << std::endl;
    for(std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << *it2 << std::endl;
      fc0_tot_c12+=(*it2);
    }
  }

  for(std::map<Double_t, std::set<Double_t>>::iterator it = s_fc0_c12.begin(); it != s_fc0_c12.end(); ++it ){
    //std::cout << " Run " << it->first << std::endl;
    for(std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << *it2 << std::endl;
      fc1_tot_c12+=(*it2);
    }
  }


  ////////////////////////////////////////////////////////////////////////////
  //ADDING FC VALUES FOR DIFFERENT TARGET POLARIZATIONS
  
  Double_t fctot_nh3_P = 0, fctot_nh3_N = 0 , fctot_c12_P = 0, fctot_c12_N = 0;
  for(std::map<Double_t, std::set<Double_t>>::iterator it = s_fctot_nh3_P.begin(); it != s_fctot_nh3_P.end(); ++it ){
    //std::cout << " Run " << it->first << std::endl;
    for(std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << *it2 << std::endl;
      fctot_nh3_P+=(*it2);
    }
  }
  
  for(std::map<Double_t, std::set<Double_t>>::iterator it = s_fctot_nh3_N.begin(); it != s_fctot_nh3_N.end(); ++it ){
    //std::cout << " Run " << it->first << std::endl;
    for(std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << *it2 << std::endl;
      fctot_nh3_N+=(*it2);
    }
  }
  
  std::cout << " >>>>>>>>>>>>>> FC for Target Polarizations " << std::endl;
  std::cout << " FC NH3 Positive target " << fctot_nh3_P << std::endl;
  std::cout << " FC NH3 Negative target " << fctot_nh3_N << std::endl;
  ///////////////////////////////////////////////////////////////////////////

  std::vector<Double_t> fc_run_nh3, fc_run_c12;
  std::vector<Double_t> fctot_nh3, fctot_c12;
 
  //FIT VALUES FROM FITTING METHOD. CAN ONLY GET AFTER RUNNING CODE AT LEAST ONCE
  std::cout << " >> Checking Run Quality " << std::endl;
  Double_t sigma_nh3 = 0.0000000617977;
  Double_t avg_nh3 = 0.000000745641;
  Double_t max_ratio_nh3 = avg_nh3 + 3.0*sigma_nh3;
  Double_t min_ratio_nh3 = avg_nh3 - 3.0*sigma_nh3;

  Double_t sigma_c12 = 0.0000000395964;
  Double_t avg_c12 = 0.000000196995;
  Double_t max_ratio_c12 = avg_c12 + 3.0*sigma_c12;
  Double_t min_ratio_c12 = avg_c12 - 3.0*sigma_c12;
  std::vector< Double_t > fc_ratio_good_nh3, fc_ratio_bad_nh3, fc_run_good_nh3, fc_run_bad_nh3;
  std::vector< Double_t > fc_ratio_good_c12, fc_ratio_bad_c12, fc_run_good_c12, fc_run_bad_c12;

  //OUTPUTFILE CONTAINING GOOD RUNS  
  const char *pathout = "FinalGoodRuns_GroupB.txt";
  std::ofstream outfile;
  outfile.open(pathout,std::ios_base::in);

  //CREATE VECTORS FOR GRAPH --- NH3 
  for(std::map<Double_t,std::set<Double_t>>::iterator it = s_fctot_nh3.begin(); it != s_fctot_nh3.end(); ++it){
    fc_run_nh3.push_back(it->first);
    Double_t fctotnh3 = 0;
    for( std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      fctotnh3+=(*it2);
    }
    Double_t dvcsrate = m_ratedvcs_nh3[it->first];
    h_runratio_nh3->Fill(dvcsrate/fctotnh3);

    Double_t ratio = dvcsrate/fctotnh3;
    if(  ratio <= max_ratio_nh3 && min_ratio_nh3 <= ratio ){
      //outfile<< it->first << std::endl;
      fc_run_good_nh3.push_back(it->first);
      fc_ratio_good_nh3.push_back(ratio);
    } 
    else{
      fc_run_bad_nh3.push_back(it->first);
      fc_ratio_bad_nh3.push_back(ratio);
    }
    //fctot_nh3.push_back(dvcsrate/fctotnh3);
    //std::cout << ">> " << dvcsrate << " " << fctotnh3 <<  std::endl;
  }


  //CREATE VECTORS FOR GRAPH --- CARBON 12 
  for(std::map<Double_t,std::set<Double_t>>::iterator it = s_fctot_c12.begin(); it != s_fctot_c12.end(); ++it){
    //std::cout << " run " << it->first << std::endl;
    fc_run_c12.push_back(it->first);
    Double_t fctotc12 = 0;
    for( std::set<Double_t>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 ){
      //std::cout << " check " << std::endl;
      fctotc12+=(*it2);
    }
    Double_t dvcsrate = m_ratedvcs_c12[it->first];
    h_runratio_c12->Fill(dvcsrate/fctotc12);

    Double_t ratioc12 = dvcsrate/fctotc12;
    if(  ratioc12 <= max_ratio_c12 && min_ratio_c12 <= ratioc12 ){
      //outfile << it->first << std::endl;
      fc_run_good_c12.push_back(it->first);
      fc_ratio_good_c12.push_back(ratioc12);
    } 
    else{
      fc_run_bad_c12.push_back(it->first);
      fc_ratio_bad_c12.push_back(ratioc12);
    }
    //fctot_c12.push_back(dvcsrate/fctotc12);
    //std::cout << ">> " << dvcsrate << " " << fctotc12 <<  std::endl;
  }

  std::cout << ">> Fitting nh3 data" << std::endl;
  FittingMethod(h_runratio_nh3);
  std::cout << " Fitting c12 data " << std::endl;
  FittingMethod(h_runratio_c12);

 
  std::cout << " " << std::endl;
  std::cout << " >>>>>>>>>>>>>>>>> RESULTS <<<<<<<<<<<<<<<<< " << std::endl;
  std::cout << " dvcs rates for nh3 " << dvcs_nh3 << std::endl;
  std::cout << " dvcs rates for c12 " << dvcs_c12 << std::endl;
  std::cout << " fctotal rates for nh3 " << fc0_tot_nh3 + fc1_tot_nh3 << std::endl;  
  std::cout << " fctotal rates for c12 " << fc0_tot_c12 + fc1_tot_c12 << std::endl;  
  
  std::cout << " Creating FC vs Run Plot " << std::endl;
  std::cout << " >> Number of good NH3 Runs: " << fc_run_good_nh3.size() << std::endl; 
  std::cout << " >> Number of good C12 Runs: " << fc_run_good_c12.size() << std::endl;
  std::cout << " >> Number of bad NH3 Runs:" << fc_run_bad_nh3.size() << std::endl;
  std::cout << " >> Number of bad C12 Runs: " << fc_run_bad_c12.size() << std::endl;


  std:::cout << " >> Creating Graphs and Plots now " << std::endl;  
  TGraph *g_fctot_good_nh3 = new TGraph(fc_run_good_nh3.size(), &(fc_run_good_nh3[0]), &(fc_ratio_good_nh3[0]));
  TGraph *g_fctot_bad_nh3 = new TGraph(fc_run_bad_nh3.size(), &(fc_run_bad_nh3[0]), &(fc_ratio_bad_nh3[0]));
  TGraph *g_fctot_good_c12 = new TGraph(fc_run_good_c12.size(), &(fc_run_good_c12[0]), &(fc_ratio_good_c12[0]));
  TGraph *g_fctot_bad_c12 = new TGraph(fc_run_bad_c12.size(), &(fc_run_bad_c12[0]), &(fc_ratio_bad_c12[0]));

  TMultiGraph *mg = new TMultiGraph();

  TCanvas *c1 = new TCanvas("c1","",1600,800);
  gPad->SetGrid();
  gStyle->SetOptStat(0);
  //GRAPHS FOR NH3

  c1->Divide(1,1);
  c1->cd(1);
  g_fctot_good_nh3->SetName("g_fctot_good_nh3");
  g_fctot_good_nh3->SetTitle("DVCS rate to FC total ratio Pass");
  g_fctot_good_nh3->SetMarkerStyle(8);
  g_fctot_good_nh3->SetMarkerSize(0.8);
  g_fctot_good_nh3->SetMarkerColor(kBlue);
  g_fctot_good_nh3->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  g_fctot_good_nh3->GetXaxis()->CenterTitle();

  g_fctot_bad_nh3->SetName("g_fctot_bad_nh3");
  g_fctot_bad_nh3->SetTitle("DVCS rate to FC total ratio Fail");
  g_fctot_bad_nh3->SetMarkerStyle(8);
  g_fctot_bad_nh3->SetMarkerSize(0.8);
  g_fctot_bad_nh3->SetMarkerColor(kRed);
  g_fctot_bad_nh3->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  g_fctot_bad_nh3->GetXaxis()->CenterTitle();


  //GRAPHS FOR C12
  g_fctot_good_c12->SetName("g_fctot_bad_c12");
  g_fctot_good_c12->SetTitle("DVCS rate to FC total ratio Pass C12");
  g_fctot_good_c12->SetMarkerStyle(22);
  g_fctot_good_c12->SetMarkerSize(0.8);
  g_fctot_good_c12->SetMarkerColor(kBlue);
  g_fctot_good_c12->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  g_fctot_good_c12->GetXaxis()->CenterTitle();

  g_fctot_bad_c12->SetName("g_fctot_bad_c12");
  g_fctot_bad_c12->SetTitle("DVCS rate to FC total ratio Fail C12");
  g_fctot_bad_c12->SetMarkerStyle(22);
  g_fctot_bad_c12->SetMarkerSize(0.8);
  g_fctot_bad_c12->SetMarkerColor(kRed);
  g_fctot_bad_c12->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  g_fctot_bad_c12->GetXaxis()->CenterTitle();

  TLegend *leg = new TLegend( 0.75, 0.375, 0.9, 0.525 );
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->AddEntry(g_fctot_good_nh3,"Accepted for NH3","P");
  leg->AddEntry(g_fctot_bad_nh3,"Rejected for NH3","P");
  leg->AddEntry(g_fctot_good_c12,"Accepted for C12","P");
  leg->AddEntry(g_fctot_bad_c12,"Rejected for C12","P");
 
  TLine *topcut_nh3 = new TLine(59450,max_ratio_nh3, 60200,max_ratio_nh3);
  TLine *lowercut_nh3 = new TLine(59450,min_ratio_nh3, 60200,min_ratio_nh3);
  TLine *topcut_c12 = new TLine(59450,max_ratio_c12, 60200,max_ratio_c12);
  TLine *lowercut_c12 = new TLine(59450,min_ratio_c12, 60200,min_ratio_c12);

  mg->Add(g_fctot_good_nh3);
  mg->Add(g_fctot_good_c12);
  mg->Add(g_fctot_bad_nh3);
  mg->Add(g_fctot_bad_c12);

  mg->Draw("AP");
  mg->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  mg->GetYaxis()->SetTitle("DVCS event to FC Charge Ratio");  
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();
 
  topcut_nh3->SetLineColor(kRed);
  topcut_nh3->Draw("same");
  lowercut_nh3->SetLineColor(kRed);
  lowercut_nh3->Draw("same");

  topcut_c12->SetLineColor(kRed);
  topcut_c12->Draw("same");
  lowercut_c12->SetLineColor(kRed);
  lowercut_c12->Draw("same");

  leg->Draw("same");

}

