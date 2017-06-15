#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TMath.h"
#include "TString.h"
#include "tDVCS.C"


#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


void dilfactor( const char* rootfile ){

  TChain *fchain = new TChain("tDVCS");
  fchain->Add(rootfile);

  tDVCS *treevar = new tDVCS(fchain);

  const char *path = "/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/fcup_analysis/Clary_GoodFCValues.txt"; //"FinalGoodRunsGroupAB.txt";
  std::ifstream myfile;
  myfile.open(path,std::ios_base::in);
  std::string line;
  std::map<Double_t,bool> goodruns;
  if( myfile.is_open() ){
    
    while( getline(myfile,line) ){
      if( line[0] == '#' ) continue;
      double run, fc0, fc1;
      std::stringstream first(line);
      first >> run >> fc0 >> fc1 ;
      //std::cout << run << std::endl;
      if( fc0 != 0 || fc1 != 0 ){
	goodruns[run] = true;
      }
      else{
	//std::cout << " no fc charge found " << std::endl;
	goodruns[run] = false;
      }
    }
  }
    
  //Count the number of events coming from a NH3 or C12 target
  std::map<TString,Double_t> target_event;
  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++ ){
    fchain->GetEntry(nn);
    if( goodruns[treevar->RunNumber] ){
      std::string target = (std::string)(*treevar->TargetType);
      if( *treevar->PeriodID == 'B' ){//||  *treevar->PeriodID == 'A' ){
	if( target == "NH3T" || target == "NH3B" || target == "NH3S" ){
	  target="NH3";
	  target_event[target]+=1;
	}
	if( target == "C12" ){
	  target_event[target]+=1;
	} 
      }
    }
  }

  Double_t Nc12 = target_event["C12"]/0.110663;
  Double_t Nnh3 = target_event["NH3"]/1.1425;

  Double_t dilution = 1 - (0.7)*(Nc12/Nnh3);
  std::cout << "Number of events coming from a C12 target " << target_event["C12"] << std::endl;
  std::cout << "Number of events coming from a NH3 target " << target_event["NH3"] << std::endl;
  std::cout << "Dilution factor " << dilution << std::endl;
  

}
