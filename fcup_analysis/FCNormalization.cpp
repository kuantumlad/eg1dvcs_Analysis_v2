//#################################################
//
//    Written By Brandon Clary
//    Date: unknown ~ May?
//    Purpose: To use the FinalGoodRuns_GroupAB_NH3_vtest.txt file
//             for creating a list of runs to use in adding up the 
//             FC values. 
//
//
//
//#################################################
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLine.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>

#include "tDVCS.C"

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void RunFileToMap( std::map<Double_t,bool>& tempmap,  const char* filename ){

  std::ifstream fIn;
  fIn.open(filename, std::ios_base::in );

  std::string line;
  if( fIn.is_open() ){

    while( getline( fIn, line ) ){
      if( line[0] == '#' ) continue;
      Double_t col1;
      std::stringstream first(line);
      first >> col1;
      tempmap[col1] = true;
    }
  }
  fIn.close();
}


void FCFileToMap( Int_t fcsign, std::map<Double_t, Double_t>& fctempmap, const char* filename ){

  std::ifstream fIn;
  fIn.open(filename, std::ios_base::in );

  std::string line;
  if( fIn.is_open() ){

    while( getline( fIn, line ) ){
      if( line[0] == '#' ) continue;
      Double_t col1, col2, col3;
      std::stringstream first(line);
      first >> col1 >> col2 >> col3;
      if( fcsign == 0 ){
	fctempmap[col1] = col2;
	//std::cout << " " << col1 << " " << col2 << std::endl;
      }
      if( fcsign == 1 ){
	fctempmap[col1] = col3;
	//std::cout << " " << col1 <<  " " << col3 << std::endl;
      }
    }	
  }
  fIn.close();
}


void TreeToMap(std::map< Double_t, Double_t >& tempmap, const char* tempfile ){

  //Create map for each run and its number of dvcs events
  TChain *fchain = new TChain("tDVCS");
  fchain->Add(tempfile);
 
  tDVCS *treevar = new tDVCS(fchain);
  std::cout << " There are " << fchain->GetEntries() << " Number of final DVCS events to process " << std::endl;
  
  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++ ){
    fchain->GetEntry(nn);
    std::string target = (std::string)(*treevar->TargetType);
    tempmap[treevar->RunNumber]++;


  }

}

void TreeToTargetMap( std::string period, std::map< Double_t, Double_t >& tempmap, const char* tempfile ){

  //Create map for each run and its number of dvcs events
  TChain *fchain = new TChain("tDVCS");
  fchain->Add(tempfile);
 
  tDVCS *treevar = new tDVCS(fchain);
  std::cout << " There are " << fchain->GetEntries() << " Number of final DVCS events to process " << std::endl;
  
  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++ ){
    fchain->GetEntry(nn);
    std::string target = (std::string)(*treevar->TargetType);

    if( (std::string)(*treevar->PeriodID) == period ) {
      if( target == "NH3T" || target == "NH3B" ) tempmap[treevar->RunNumber] = 3;
      if( target == "C12" ) tempmap[treevar->RunNumber] = 12;
    }
  }

}

void FCNormalization( const char* rootfile ){

  //Load in the txt files that have the runs which passed the 
  //'quality' assessment test. These are marked by the Final*.txt files

  std::map< Double_t, bool > final_nh3_runs;
  std::map< Double_t, bool > final_c12_runs;

  std::cout << " final_nh3_runs size BEFORE " << final_nh3_runs.size() << std::endl;
  std::cout << " final_c12_runs size BEFORE " << final_c12_runs.size() << std::endl;
  std::cout << " Sending in each map to RunFileToMap " << std::endl;

  std::cout << " Create NH3 Map " << std::endl;
  RunFileToMap( final_nh3_runs, "FinalGoodRuns_GroupAB_NH3_vtest.txt" );
  std::cout << " Create C12 Map " << std::endl;
  RunFileToMap( final_c12_runs, "FinalGoodRuns_GroupAB_C12_vtest.txt" );

  std::cout << " final_nh3_runs size AFTER " << final_nh3_runs.size() << std::endl;
  std::cout << " final_c12_runs size AFTER " << final_c12_runs.size() << std::endl;


  std::map< Double_t, Double_t > fc0;
  std::map< Double_t, Double_t > fc1;
  std::cout << " reading in fc counts BEFORE " << fc0.size() << std::endl; 
  std::cout << " reading in fc counts BEFORE " << fc1.size() << std::endl; 
  std::cout << " Create fc0 Map " << std::endl;
  FCFileToMap(0, fc0, "Clary_GoodFCValues.txt");
  std::cout << " Create fc1 Map " << std::endl;
  FCFileToMap(1, fc1, "Clary_GoodFCValues.txt");
  std::cout << " reading in fc counts AFTER " << fc0.size() << std::endl; 
  std::cout << " reading in fc counts AFTER " << fc1.size() << std::endl; 

  std::map< Double_t, Double_t > dvcs;
  std::map< Double_t, Double_t > target;
  std::cout << " reading in dvcs counts BEFORE " << dvcs.size() << std::endl;
  std::cout << " Create dvcs Map " << std::endl;
  TreeToMap(dvcs, rootfile);
  std::cout << " dvcs size AFTER " << dvcs.size() << std::endl;

  std::cout << " reading in target counts BEFORE " << target.size() << std::endl;
  std::cout << " Create target Map " << std::endl;
  TreeToTargetMap("B",target, rootfile);
  std::cout << " target size AFTER " << target.size() << std::endl;

  std::cout << " Looping over the target map which is from a chosen period (A or B)" << std::endl;
  Double_t fc0_total_nh3 = 0;
  Double_t fc1_total_nh3 = 0;
  Double_t fc0_total_c12 = 0;
  Double_t fc1_total_c12 = 0;
  Double_t dvcs_total = 0;

  for( std::map< Double_t, Double_t >::iterator it = target.begin(); it != target.end(); ++it ){
    Double_t target = it->second;
    Double_t run = it->first;
    if( target == 12 && final_c12_runs[run] ){
      std::cout << it->first << " " << it->second << std::endl;
      //      std::cout << fc0[run] << " + " << fc1[run] << " = " << fc0[run] + fc1[run] << std::endl;
      fc0_total_c12 = fc0_total_c12 + fc0[run];
      fc1_total_c12 = fc1_total_c12 + fc1[run];

      dvcs_total = dvcs_total + dvcs[run];
      //std::cout << " dvcs " << dvcs[run] << std::endl;
      //std::cout << " dvcs total " << dvcs_total << std::endl;
    }
  }


  std::cout << " --------------------------------------------------- " << std::endl; 
  std::cout << "fc0 C12 total " << fc0_total_c12 << std::endl;
  std::cout << "fc1 C12 total " << fc1_total_c12 << std::endl;
  Double_t fc_total_c12 = fc0_total_c12 + fc1_total_c12;
  std::cout << " DVCS total for C12 " << dvcs_total << std::endl;
  std::cout << " FC total for C12 " << fc_total_c12 << std::endl;
  std::cout << " DVCS to FC ratio " << dvcs_total/fc_total_c12 << std::endl;
  //std::cout << "fc0 C12 total " << fc0_total_c12 << std::endl;
  //std::cout << "fc0 C12 total " << fc0_total_c12 << std::endl;
}
