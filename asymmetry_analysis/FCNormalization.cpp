#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"

#include <vector>
#include <iostream>
#include <cmath>

TFile *fOut;

Int_t RunNumber;
TString *TargetType;
Int_t helicity;
Float_t TarPol;

void SetBrAddress(TTree *temptree){

  temptree->SetBranchAddress("RunNumber",&RunNumber);
  temptree->SetBranchAddress("TargetType",&TargetType);
  temptree->SetBranchAddress("helicity",&helicity);
  temptree->SetBranchAddress("TarPol",&TarPol);
 
}

void FCNormalization( const char* rootfile ){

  TFile *fIn = new TFile(rootfile);

  std::cout<< "Checking Run Parameters for EG1-DVCS" << std::endl;
  TTree *tDVCS = (TTree*)fIn->Get("tDVCS");

  SetBrAddress(tDVCS);
  
  int nentries = tDVCS->GetEntries();
  std::cout << ">> Number of Entries to process is "<< nentries << std::endl;

  std::vector<double> hel, tarpol, run;

}
