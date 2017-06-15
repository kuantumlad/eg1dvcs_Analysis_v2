#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TF1.h"
#include "TStyle.h"
#include "TStopwatch.h"
#include "TLorentzVector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <cmath>

#include "tPID.C"


void NormalizationCheck( const char* rootfile ){

  TChain *fchain = new TChain("tPID");
  fchain->Add(rootfile);
  std::cout << "Chaining Complete" << std::endl;
  tPID *treevar = new tPID(fchain);

  Long64_t nentries = fchain->GetEntries();
  std::cout << " Number of entries to process " << nentries << std::endl;

  TH1D* h_mm2_nh3 = new TH1D("h_mm2_nh3","", 50, -1.2, -0.2);
  TH1D* h_mm2_c12 = new TH1D("h_mm2_c12","", 50, -1.2, -0.2);
  TH1D* h_mm2_ratio = new TH1D("h_mm2_ratio","", 50, -1.2, -0.2);
  TH1D* h_mm2epg_nh3 = new TH1D("h_mm2epg_nh3","",100,-4,3);
  TH1D* h_mm2epg_c12 = new TH1D("h_mm2epg_c12","",100,-4,3);

  TH1D* h_phang_nh3 = new TH1D("h_phang_nh3", "", 50, 0.0, 8.0);
  TH1D* h_phang_c12 = new TH1D("h_phang_c12", "", 50, 0.0, 8.0);
  TH1D* h_missingE_nh3 = new TH1D("h_missingE_nh3","", 50, -1.0, 1.0 ); 
  TH1D* h_missingE_c12 = new TH1D("h_missingE_c12","", 50, -1.0, 1.0 ); 

  TH1D* h_mm2_nh3_2 = new TH1D("h_mm2_nh3_2","", 50, -1.2, -0.2);
  TH1D* h_mm2_c12_2 = new TH1D("h_mm2_c12_2","", 50, -1.2, -0.2);
  TH1D* h_mm2_ratio_2 = new TH1D("h_mm2_ratio_2","", 50, -1.2, -0.2);
  TH1D* h_mm2epg_nh3_2 = new TH1D("h_mm2epg_nh3_2","",100,-4,3);
  TH1D* h_mm2epg_c12_2  = new TH1D("h_mm2epg_c12_2","",100,-4,3);

  TH1D* h_phang_nh3_2 = new TH1D("h_phang_nh3_2", "", 50, 0.0, 8.0);
  TH1D* h_phang_c12_2 = new TH1D("h_phang_c12_2", "", 50, 0.0, 8.0);
  TH1D* h_missingE_nh3_2 = new TH1D("h_missingE_nh3_2", "", 50, -1.0, 1.0 ); 
  TH1D* h_missingE_c12_2 = new TH1D("h_missingE_c12_2", "", 50, -1.0, 1.0 ); 

  TStopwatch timer;
  timer.Start();

  const char *path = "Clary_GoodFCValues.txt";
  std::ifstream myfile;
  myfile.open(path,std::ios_base::in);
  std::string line;

  std::map<Double_t, Double_t> fc_f0;
  std::map<Double_t, Double_t> fc_f1;
  std::map<Double_t, Double_t> fc_fc01;

  if( myfile.is_open() ){

    while( getline(myfile,line) ){
      if( line[0] == '#' ) continue;
      double run, fc0, fc1;
      std::stringstream first(line);
      first >> run >> fc0 >> fc1;
      //      if( fc0 != 0 || fc1 != 0){      
      //std::cout << fc0 << " " << fc1 << std::endl;
      fc_f0[run] = fc0;
      fc_f1[run] = fc1;
      fc_fc01[run] = fc0 + fc1;
      //}
    }
  }

  const char *path_nh3 = "FinalGoodRuns_GroupAB_NH3_vtest.txt";
  std::ifstream myfile_nh3;
  myfile_nh3.open(path_nh3,std::ios_base::in);
  std::string line_nh3;
  std::map<Double_t, bool > good_runs_nh3;
  std::vector<Double_t> v_good_run_nh3;  

  if( myfile_nh3.is_open() ){
    while( getline(myfile_nh3,line_nh3) ){
      if( line_nh3[0] == '#' ) continue;
      Double_t run;
      std::stringstream first_nh3(line_nh3);
      first_nh3 >> run ;
      //      std::cout << run << std::endl;
      good_runs_nh3[run] = true;

      v_good_run_nh3.push_back(run);
    }
  }
  std::cout << " Runs from NH3 good txt file " << good_runs_nh3.size() << std::endl;

  const char *path_c12 = "FinalGoodRuns_GroupAB_C12_vtest.txt";
  std::ifstream myfile_c12;
  myfile_c12.open(path_c12,std::ios_base::in);
  std::string line_c12;
  std::map<Double_t, bool > good_runs_c12;
  std::vector<Double_t> v_good_run_c12;  

  if( myfile_c12.is_open() ){
    while( getline(myfile_c12,line_c12) ){
      if( line_c12[0] == '#' ) continue;
      Double_t run;
      std::stringstream first_c12(line_c12);
      first_c12 >> run ;
      //std::cout << run << std::endl;
      good_runs_c12[run] = true;

      v_good_run_c12.push_back(run);
    }
  }

  std::cout << " Runs from C12 good txt file " << good_runs_c12.size() << std::endl;

  //Here I am testing if I can seperate the runs into two random sets
  // I will need to create three seperate groups, one for group A, B, and C
  //
  std::map<Double_t, bool> temp_AB_1_nh3;
  std::map<Double_t, bool> temp_AB_2_nh3;
  std::map<Double_t, bool> temp_AB_1_c12;
  std::map<Double_t, bool> temp_AB_2_c12;
  std::vector<Double_t> temp_good_run_nh3;
  std::vector<Double_t> temp_good_run_c12;

  int i = 0;
  srand (time(NULL));
  temp_good_run_nh3 = v_good_run_nh3;


  //changing to not do a random selection. this just entails commenting out pieces of this while loop
  while ( i < (int)v_good_run_nh3.size() ){ ///2 ){ 
    //    Double_t rand_run = rand() % temp_good_run_nh3.size();// + 1;
    temp_AB_1_nh3[(temp_good_run_nh3[i])] = true;
    std::cout << i << std::endl;
    //temp_good_run_nh3.erase(temp_good_run_nh3.begin() + i );//rand_run);
    i++;
  }

  for( std::vector<Double_t>::iterator it = temp_good_run_nh3.begin(); it != temp_good_run_nh3.end(); ++it ){
    temp_AB_2_nh3[*it] = true;
  }

  int j = 0;
  srand (time(NULL));
  temp_good_run_c12 = v_good_run_c12;

  while ( j < (int)v_good_run_c12.size() ){///2 ){ 
    //    Double_t rand_run = rand() % temp_good_run_c12.size();
    temp_AB_1_c12[(temp_good_run_c12[j])] = true;
    std::cout << " j " << j << std::endl;
    //temp_good_run_c12.erase(temp_good_run_c12.begin() + j );//rand_run);
    j++;
  }

  for( std::vector<Double_t>::iterator it = temp_good_run_c12.begin(); it != temp_good_run_c12.end(); ++it ){
    temp_AB_2_c12[*it] = true;
  }

  //Double check to make sure there are no duplicate runs in the vector for both c12 and nh3 targets
  /* for( std::map<Double_t,bool>::iterator it = temp_AB_1_nh3.begin(); it != temp_AB_1_nh3.end(); ++it ){
    for( std::vector<Double_t>::iterator it2 = temp_good_run_nh3.begin(); it2 != temp_good_run_nh3.end(); ++it2 ){
      //      if( it->first == *it2 ) { std::cout << " ERROR - Duplicate run in both vectors " << std::endl; }
    }
  }

  for( std::map<Double_t,bool>::iterator it = temp_AB_1_c12.begin(); it != temp_AB_1_c12.end(); ++it ){
    for( std::vector<Double_t>::iterator it2 = temp_good_run_c12.begin(); it2 != temp_good_run_c12.end(); ++it2 ){
      //if( it->first == *it2 ) { std::cout << " ERROR - Duplicate run in both vectors " << std::endl; }
    }
  }
  */

  std::cout << " tempAB for nh3 1 " << temp_AB_1_nh3.size() << std::endl;  
  std::cout << " tempAB for c12 1 " << temp_AB_1_c12.size() << std::endl;  
  std::cout << " tempAB for nh3 2 " << temp_AB_2_nh3.size() << std::endl;  
  std::cout << " tempAB for c12 2 " << temp_AB_2_c12.size() << std::endl;  
  std::cout << " Beginning analysis " << std::endl;

  std::map<Double_t, bool> fc_run_nh3, fc_run_c12;
  std::map<Double_t, Double_t> fc_run_nh3_2, fc_run_c12_2;

  //For Andrey's suggestion to check the DVCS rates and FC counts for the negative tail
  std::map<Double_t, Double_t> DVCS_nh3_1, DVCS_c12_1;
  std::map<Double_t, Double_t> DVCS_nh3_2, DVCS_c12_2;
  
  std::map<Double_t, Double_t> FC_nh3_1, FC_c12_1;
  std::map<Double_t, Double_t> FC_nh3_2, FC_c12_2;

  Double_t dvcs_nh3_rate = 0.0;
  Double_t dvcs_c12_rate = 0.0;

  for( Long64_t nn = 0; nn < nentries; nn++ ){
    fchain->GetEntry(nn);

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
      if( target_nh3 && temp_AB_1_nh3[Run] ){
	h_mm2_nh3->Fill(mm);
	h_missingE_nh3->Fill(missing_energy);
	fc_run_nh3[Run] = true;
	if ( mm < 0.0 ) { DVCS_nh3_1[Run]++; FC_nh3_1[Run] = fc_fc01[Run]; }
      }
      if( target_nh3 ) { //&& temp_AB_2_nh3[Run] ){
	h_mm2_nh3_2->Fill(mm);
	h_missingE_nh3_2->Fill(missing_energy);
	fc_run_nh3_2[Run] = true;
	dvcs_nh3_rate++;
	if( mm < 0.0 ) { DVCS_nh3_2[Run]++; FC_nh3_2[Run] = fc_fc01[Run];  }
      }
      if( target_c12 ) { //&& temp_AB_1_c12[Run] ){
	h_mm2_c12->Fill(mm);
	h_missingE_c12->Fill(missing_energy);
	fc_run_c12[Run] = true;
	dvcs_c12_rate++;
	if ( mm < 0.0 ) { DVCS_c12_1[Run]++; FC_c12_1[Run] = fc_fc01[Run];  }
      }
      if( target_c12 && temp_AB_2_c12[Run] ){
	h_mm2_c12_2->Fill(mm);
	h_missingE_c12_2->Fill(missing_energy);
	fc_run_c12_2[Run] = true;
	if ( mm < 0.0 ) { DVCS_c12_2[Run]++; FC_c12_2[Run] = fc_fc01[Run]; }
      }
    }

    if( q2_pass && w_pass && phE_pass && phi_pass && trans_mntm_pass && mm2epg_pass && groupB ){
      if( (target == "NH3T" || target == "NH3B") && temp_AB_1_nh3[Run] ){
	h_phang_nh3->Fill(deltheta/3.14159 * 180.0);
      }
      if( (target == "NH3T" || target == "NH3B") && temp_AB_2_nh3[Run] ){
	h_phang_nh3_2->Fill(deltheta/3.14159 * 180.0);
      }
      if( target == "C12" && temp_AB_1_c12[Run]){
	h_phang_c12->Fill(deltheta/3.14159 * 180.0);
      }
      if( target == "C12" && temp_AB_2_c12[Run]){
	h_phang_c12_2->Fill(deltheta/3.14159 * 180.0);
      }
    }
  }

  ///// Make TH1Ds for the DVCS and FC rates in the negative tail
  //TCanvas *cA = new TCanvas("cA","cA",800,600);
  //cA->Divide(2,2);
  //Fill the TH1Ds
  TH1D *h_DVCS_nh3_1 = new TH1D("h_DVCS_nh3_1","",40,0,160);
  TH1D *h_DVCS_nh3_2 = new TH1D("h_DVCS_nh3_2","",40,0,160);
  TH1D *h_DVCS_c12_1 = new TH1D("h_DVCS_c12_1","",25,0,50);
  TH1D *h_DVCS_c12_2 = new TH1D("h_DVCS_c12_2","",25,0,50);
  for( std::map< Double_t, Double_t >::iterator it = DVCS_nh3_1.begin(); it != DVCS_nh3_1.end(); ++it ){
    h_DVCS_nh3_1->Fill(it->second);
  }
  for( std::map< Double_t, Double_t >::iterator it = DVCS_nh3_2.begin(); it != DVCS_nh3_2.end(); ++it ){
    h_DVCS_nh3_2->Fill(it->second);
  }
  for( std::map< Double_t, Double_t >::iterator it = DVCS_c12_1.begin(); it != DVCS_c12_1.end(); ++it ){
    h_DVCS_c12_1->Fill(it->second);
  }
  for( std::map< Double_t, Double_t >::iterator it = DVCS_c12_2.begin(); it != DVCS_c12_2.end(); ++it ){
    h_DVCS_c12_2->Fill(it->second);
  }

  std::cout << " The size of the run map for c12 is " << fc_run_c12.size() << std::endl;
  std::cout << " The size of the run map for nh3 is " << fc_run_nh3.size() << std::endl;

  std::cout << " Counting the FC charge for the runs used " << std::endl;
  // Get the FC Normalization values for this random set
  Double_t fc_tot_nh3 = 0.0, fc_tot_c12 = 0.0;
  Double_t fc_tot_nh3_2 = 0.0, fc_tot_c12_2 = 0.0;

  std::vector<Double_t> runnh3_set1, runnh3_set2;

  for ( std::map<Double_t, bool>::iterator it = temp_AB_1_nh3.begin(); it != temp_AB_1_nh3.end(); ++it ){
    Double_t runnum = it->first;
    if( it->second){
      fc_tot_nh3 = fc_tot_nh3 + (fc_f0[runnum] + fc_f1[runnum]);
      runnh3_set1.push_back(runnum);
    }
  }
  for ( std::map<Double_t, bool>::iterator it = temp_AB_2_nh3.begin(); it != temp_AB_2_nh3.end(); ++it ){
    Double_t runnum = it->first;
    if( it->second){
      fc_tot_nh3_2 = fc_tot_nh3_2 + (fc_f0[runnum] + fc_f1[runnum]);
      runnh3_set2.push_back(runnum);
    }
  }

  std::vector<Double_t> runc12_set1, runc12_set2;

  for ( std::map<Double_t, bool>::iterator it = temp_AB_1_c12.begin(); it != temp_AB_1_c12.end(); ++it ){
    Double_t runnum = it->first;
    if( it->second){
      fc_tot_c12 = fc_tot_c12 + (fc_f0[runnum] + fc_f1[runnum]);
      runc12_set1.push_back(runnum);
    }
  }
  for ( std::map<Double_t, bool>::iterator it = temp_AB_2_c12.begin(); it != temp_AB_2_c12.end(); ++it ){
    Double_t runnum = it->first;
    if( it->second){
      fc_tot_c12_2 = fc_tot_c12_2 + (fc_f0[runnum] + fc_f1[runnum]);
      runc12_set2.push_back(runnum);
    }
  }

  
  std::cout << " Total FC for C12 for group 1 " << fc_tot_c12 << std::endl;
  std::cout << " Total FC for NH3 for group 1 " << fc_tot_nh3 << std::endl;
  std::cout << " ------------------------------------------------------- " << std::endl;
  std::cout << " Total FC for C12 for group 2 " << fc_tot_c12_2 << std::endl;
  std::cout << " Total FC for NH3 for group 2 " << fc_tot_nh3_2 << std::endl;


  std::cout << "dvcs rate for nh3 " << dvcs_nh3_rate << std::endl;
  std::cout << "dvcs rate for c12 " << dvcs_c12_rate << std::endl;

  std::cout << "dilution factor nh3 group B " <<( 1 - 0.726*( (dvcs_nh3_rate/fc_tot_nh3 )/(dvcs_c12_rate/fc_tot_c12) )) << std::endl;
  std::cout << "dilution factor c12 group B " <<( 1 - 0.726*( dvcs_c12_rate/fc_tot_c12 ) ) << std::endl;

  Double_t fcav_nh3_1 = fc_tot_nh3/runnh3_set1.size();
  Double_t fcav_nh3_2 = fc_tot_nh3_2/runnh3_set2.size();
  Double_t fcav_c12_1 = fc_tot_c12/runc12_set1.size();
  Double_t fcav_c12_2 = fc_tot_c12_2/runc12_set2.size();

  std::cout << " FC Avg NH3 set 1 " << fcav_nh3_1 << std::endl;
  std::cout << " FC Avg NH3 set 2 " << fcav_nh3_2 << std::endl;
  std::cout << " FC Avg C12 set 1 " << fcav_c12_1 << std::endl;
  std::cout << " FC Avg C12 set 2 " << fcav_c12_2 << std::endl;
  //To get the outlier subtract the FC value from the average for each set


  std::vector<Double_t> devc12_set1, devc12_set2;
  std::vector<Double_t> devnh3_set1, devnh3_set2;

  for( std::vector<Double_t>::iterator it = runnh3_set1.begin(); it != runnh3_set1.end(); ++it ){
    devnh3_set1.push_back( std::fabs(fc_f0[*it] + fc_f1[*it] - fcav_nh3_1) );
    //    std::cout << *it << std::endl;
    //std::cout <<  std::fabs(fc_f0[*it] + fc_f1[*it] - fcav_nh3_1) << std::endl;
      }
  for( std::vector<Double_t>::iterator it = runnh3_set2.begin(); it != runnh3_set2.end(); ++it ){
    devnh3_set2.push_back( std::fabs(fc_f0[*it] + fc_f1[*it] - fcav_nh3_2) );
  }
  for( std::vector<Double_t>::iterator it = runc12_set1.begin(); it != runc12_set1.end(); ++it ){
    devc12_set1.push_back( std::fabs(fc_f0[*it] + fc_f1[*it] - fcav_c12_1) );
  }
  for( std::vector<Double_t>::iterator it = runc12_set2.begin(); it != runc12_set2.end(); ++it ){
    devc12_set2.push_back( std::fabs(fc_f0[*it] + fc_f1[*it] - fcav_c12_2) );
  }

  std::cout << " devnh3_set1 " <<  devnh3_set1.size()<< ", run " << runnh3_set1.size() << " " << std::endl;
  TCanvas *c3 = new TCanvas("c3","",800,600);
  c3->Divide(2,2);
  TGraph *fc_av_nh3_1 = new TGraph(devnh3_set1.size(), &(runnh3_set1[0]), &(devnh3_set1[0]) );
  TGraph *fc_av_nh3_2 = new TGraph(devnh3_set2.size(), &(runnh3_set2[0]), &(devnh3_set2[0]) );
  TGraph *fc_av_c12_1 = new TGraph(devc12_set1.size(), &(runc12_set1[0]), &(devc12_set1[0]) );
  TGraph *fc_av_c12_2 = new TGraph(devc12_set2.size(), &(runc12_set2[0]), &(devc12_set2[0]) );
  
  gStyle->SetOptFit(1);
  
  c3->cd(1);
  fc_av_nh3_1->SetName("FC Avg NH3 Set 1");
  fc_av_nh3_1->SetTitle("FC Avg NH3 Set 1");
  fc_av_nh3_1->SetMarkerStyle(20);
  fc_av_nh3_1->SetMarkerSize(0.85);
  fc_av_nh3_1->Draw("AP");

  c3->cd(2);
  fc_av_nh3_2->SetName("FC Avg NH3 Set 2");
  fc_av_nh3_2->SetTitle("FC Avg NH3 Set 2");
  fc_av_nh3_2->SetMarkerStyle(20);
  fc_av_nh3_2->SetMarkerSize(0.85);
  fc_av_nh3_2->Draw("AP");

  c3->cd(3);
  fc_av_c12_1->SetName("FC Avg C12 Set 1");
  fc_av_c12_1->SetTitle("FC Avg C12 Set 1");
  fc_av_c12_1->SetMarkerStyle(20);
  fc_av_c12_1->SetMarkerSize(0.85);
  fc_av_c12_1->Draw("AP");

  c3->cd(4);
  fc_av_c12_2->SetName("FC Avg C12 Set 2");
  fc_av_c12_2->SetTitle("FC Avg C12 Set 2");
  fc_av_c12_2->SetMarkerStyle(20);
  fc_av_c12_2->SetMarkerSize(0.85);
  fc_av_c12_2->Draw("AP");
  /// Done with plotting histograms to find bad runs

  h_mm2_c12->Scale(1.0/fc_tot_c12);
  h_mm2_nh3->Scale(1.0/fc_tot_nh3);

  h_mm2_c12_2->Scale(1.0/fc_tot_c12_2);
  h_mm2_nh3_2->Scale(1.0/fc_tot_nh3_2);

  std::cout << " Creating Histograms and plots " << std::endl;

  Double_t ratio = 0.0;

  std::vector<Double_t> v_mm2_c12, v_ratio;
  for( Int_t bin = 1; bin <= 50; bin++ ){
    Double_t mm2_c12 = h_mm2_c12->GetBinContent(bin);
    Double_t mm2_nh3 = h_mm2_nh3->GetBinContent(bin);

    //    std::cout << mm2_c12 << " " << mm2_nh3 << std::endl;
    ratio =  mm2_nh3/mm2_c12;
     
    //std::cout << " bin center " << h_mm2_c12->GetBinCenter(bin) << " ratio " << ratio << std::endl;
    //std::cout << " bin " << mm2_c12 << " " <<  mm2_nh3 << std::endl;

    if ( ratio > 20.0 ) continue;
    v_mm2_c12.push_back(h_mm2_c12->GetBinCenter(bin));
    v_ratio.push_back(ratio);
  }

  std::cout << " Creating TGraph for Set 2 " << std::endl;
  std::vector<Double_t> v_mm2_c12_2, v_ratio_2;
  for( Int_t bin = 1; bin <= 50; bin++ ){
    Double_t mm2_c12 = h_mm2_c12_2->GetBinContent(bin);
    Double_t mm2_nh3 = h_mm2_nh3_2->GetBinContent(bin);

    //std::cout << mm2_c12 << " " << mm2_nh3 << std::endl;
    ratio =  mm2_nh3/mm2_c12;
     
    //std::cout << " bin center " << h_mm2_c12_2->GetBinCenter(bin) << " ratio " << ratio << std::endl;
    //std::cout << " bin " << mm2_c12 << " " <<  mm2_nh3 << std::endl;

    if ( ratio > 20.0 ) continue;
    v_mm2_c12_2.push_back(h_mm2_c12_2->GetBinCenter(bin));
    v_ratio_2.push_back(ratio);
  }

  TGraph *g_ratio = new TGraph(v_mm2_c12.size(), &(v_mm2_c12[0]), &(v_ratio[0]));
  TGraph *g_ratio2 = new TGraph(v_mm2_c12_2.size(), &(v_mm2_c12_2[0]), &(v_ratio_2[0]));
      
  TCanvas *c1 = new TCanvas("c1","",1600,800);
  c1->Divide(2,2);
  c1->cd(1);
  h_mm2_nh3->SetTitle("MM^{2}_{epX} for NH3 and C12 targets");
  h_mm2_nh3->SetFillColorAlpha(kRed,0.7);
  h_mm2_nh3->GetXaxis()->SetTitle("MissingMass^{2}_{epX} [GeV^{2}]");
  
  h_mm2_nh3->SetLineColor(kRed); 
  h_mm2_nh3->Draw("hist");
  
  h_mm2_c12->SetLineColor(kBlue+2); 
  h_mm2_c12->Draw("same");
  
  c1->cd(2);
  TF1 *fit = new TF1("mm2epX_fit","[0]", -1.2, -0.2);
  g_ratio->SetName("MM^{2}_{epX} ratio of NH3 to C12");
  g_ratio->SetTitle("MM^{2}_{epX} ratio of NH3 to C12");
  g_ratio->SetMarkerStyle(20);
  g_ratio->SetMarkerSize(0.85);
  g_ratio->SetMarkerColor(kBlue+2);
  g_ratio->Fit("mm2epX_fit","R");
  gStyle->SetOptFit(1);
  g_ratio->Draw("AP");
  
  h_phang_c12->Scale(1.0/fc_tot_c12);//16138300000.0);
  h_phang_nh3->Scale(1.0/fc_tot_nh3);//107756000000.0);

  c1->cd(3);
  h_DVCS_nh3_1->SetTitle("Number of DVCS events for MM2 < 0 " );
  h_DVCS_nh3_1->GetXaxis()->SetTitle("Number of DVCS events for NH3 Set 1 for MM2_{epX} < 0" );
  h_DVCS_nh3_1->Scale(1.0/fc_tot_nh3);
  h_DVCS_nh3_1->SetFillColorAlpha(kRed,0.7);
  h_DVCS_nh3_1->SetLineColor(kRed); 
  h_DVCS_nh3_1->Draw("hist");
  
  c1->cd(4);
  h_DVCS_c12_1->SetTitle("Number of DVCS events for MM2 < 0 " );
  h_DVCS_c12_1->GetXaxis()->SetTitle("Number of DVCS events for C12 Set 1 for MM2_{epX} < 0" );
  h_DVCS_c12_1->Scale(1.0/fc_tot_c12);
  h_DVCS_c12_1->SetFillColorAlpha(kBlue+2,0.7);
  h_DVCS_c12_1->SetLineColor(kBlue+2);
  h_DVCS_c12_1->Draw("hist");

  /*  c1->cd(4);
  h_phang_nh3->SetTitle("Angle between Measured and Calculated Photon for NH3 ");
  h_phang_nh3->GetXaxis()->SetTitle("#theta [deg]");
  h_phang_nh3->SetFillColorAlpha(kRed,0.7);
  h_phang_c12->SetLineColor(kBlue+2);
  
  h_phang_nh3->Draw("hist");
  h_phang_c12->Draw("same");
  */
  /* c1->cd(4);
  h_missingE_c12->Scale(1.0/16138300000.0);
  h_missingE_nh3->Scale(1.0/107756000000.0);
  h_missingE_nh3->SetTitle("Missing Energy NH3");
  h_missingE_nh3->GetXaxis()->SetTitle("Missing Energy [GeV]");
  h_missingE_nh3->SetFillColorAlpha(kRed,0.7);
  h_missingE_c12->SetLineColor(kBlue+2);
  h_missingE_nh3->Draw("hist");
  h_missingE_c12->Draw("same");
  */
  TCanvas *c2 = new TCanvas("c2","",1600,800);
  c2->Divide(2,2);
  c2->cd(1);
  h_mm2_nh3_2->SetTitle("MM^{2}_{epX} for NH3 and C12 targets Set 2");
  h_mm2_nh3_2->SetFillColorAlpha(kRed,0.7);
  h_mm2_nh3_2->GetXaxis()->SetTitle("MissingMass^{2}_{epX} [GeV^{2}]");
 
  h_mm2_nh3_2->SetLineColor(kRed); 
  h_mm2_nh3_2->Draw("hist");
  
  h_mm2_c12_2->SetLineColor(kBlue+2); 
  h_mm2_c12_2->Draw("same");
  
  c2->cd(2);
  TF1 *fit2 = new TF1("mm2epX_fit2","[0]", -1.2, -0.2);
  g_ratio2->SetName("MM^{2}_{epX} ratio of NH3 to C12 Set 2");
  g_ratio2->SetTitle("MM^{2}_{epX} ratio of NH3 to C12 Set 2");
  g_ratio2->SetMarkerStyle(20);
  g_ratio2->SetMarkerSize(0.85);
  g_ratio2->SetMarkerColor(kBlue+2);
  g_ratio2->Fit("mm2epX_fit2","R");
  gStyle->SetOptFit(1);
  g_ratio2->Draw("AP");
  
  h_phang_c12_2->Scale(1.0/fc_tot_c12_2);//16138300000.0);
  h_phang_nh3_2->Scale(1.0/fc_tot_nh3_2);//107756000000.0);

  c2->cd(3);
  h_DVCS_nh3_2->SetTitle("Number of DVCS events for MM2 < 0 Set 2 " );
  h_DVCS_nh3_2->GetXaxis()->SetTitle("Number of DVCS events for NH3 Set 2 for MM2_{epX} < 0" );
  h_DVCS_nh3_2->SetFillColorAlpha(kRed,0.7);
  h_DVCS_nh3_2->SetLineColor(kRed);
  h_DVCS_nh3_2->Draw();

  c2->cd(4);
  h_DVCS_c12_2->SetTitle("Number of DVCS events for MM2 < 0 Set 2 " );
  h_DVCS_c12_2->GetXaxis()->SetTitle("Number of DVCS events for C12 Set 2 for MM2_{epX} < 0" );
  h_DVCS_c12_2->SetFillColorAlpha(kBlue+2,0.7);
  h_DVCS_c12_2->SetLineColor(kBlue+2);
  h_DVCS_c12_2->Draw();

  /*  c2->cd(4);
  h_phang_nh3_2->SetTitle("Angle between Measured and Calculated Photon for NH3 Set 2");
  h_phang_nh3_2->GetXaxis()->SetTitle("#theta [deg]");
  h_phang_nh3_2->SetFillColorAlpha(kRed,0.7);
  h_phang_c12_2->SetLineColor(kBlue+2);
  
  h_phang_nh3_2->Draw("hist");
  h_phang_c12_2->Draw("same");
  */
  /* c2->cd(4);
  h_missingE_c12_2->Scale(1.0/fc_tot_c12_2);
  h_missingE_nh3_2->Scale(1.0/fc_tot_nh3_2);
  h_missingE_nh3_2->SetTitle("Missing Energy NH3 Set 2");
  h_missingE_nh3_2->GetXaxis()->SetTitle("Missing Energy [GeV]");
  h_missingE_nh3_2->SetFillColorAlpha(kRed,0.7);
  h_missingE_c12_2->SetLineColor(kBlue+2);
  h_missingE_nh3_2->Draw("hist");
  h_missingE_c12_2->Draw("same");
  */
  /*h_mm2_ratio->Divide(h_mm2_c12,h_mm2_nh3,1.0,1.0);
  TF1 *fit = new TF1("fit","[0]", -0.99, -0.2);
  h_mm2_ratio->Fit("fit","R");
  h_mm2_ratio->Draw();
  */
  //  h_mm2_ratio->SetTitle("Ratio of MM^{2}_{epX} of C12 to NH3");
  //h_mm2_ratio->GetXaxis()->SetTitle("Ratio");
  //h_mm2_ratio->Draw();
  /*    h_mm2epg_nh3->SetTitle("MM^{2}_{epX} for NH3 and C12 targets");
	h_mm2epg_nh3->SetFillColorAlpha(kRed,0.7);
	h_mm2epg_nh3->GetXaxis()->SetTitle("MissingMass^{2}_{epX} [GeV^{2}]");
	
	h_mm2epg_c12->Scale(1.0/16138300000.0);
	h_mm2epg_nh3->Scale(1.0/107756000000.0);
	
    h_mm2epg_nh3->SetLineColor(kRed); 
    h_mm2epg_nh3->Draw("hist");

    h_mm2epg_c12->SetLineColor(kBlue+2); 
    h_mm2epg_c12->Draw("same");
    */
    
  timer.Stop();
  
  std::cout << " ---- RESULTS ---- " << std::endl;
  std::cout << " NH3 Entries: " << h_mm2_nh3->GetEntries() << std::endl;
  std::cout << " C12 Entries: " << h_mm2_c12->GetEntries() << std::endl;
  
  std::cout << timer.CpuTime() << std::endl;
  std::cout << timer.RealTime() << std::endl;
  
  std::cout << " Complete " << std::endl;
}
