#include "../include/LoadDVCS.h"
#include "../include/EventDVCS.h"

#include "TChain.h"
#include "TFile.h"
#include "TH2D.h"
#include "TLine.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TBranch.h"
#include "TF1.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBrowser.h"

Int_t main( void ){
  


  LoadDVCS dvcs;
  dvcs.MakeChain("/Users/bclary/Documents/work/run data/DVCSresults/",362);
  dvcs.Init();  
  Int_t nentries = dvcs.NumEntries();
  std::cout<< " Number of entries to process -> " <<nentries << std::endl;
   
  TCanvas *c1 = new TCanvas("c1", "DVCS", 1400, 1000 );
  c1->Divide(1,1);
  TH2D *Q2vsXbj = new TH2D("Q2vsXbj","",100, 0.1, 0.6, 100, 0.95, 5.0 );

  for( Int_t i = 0; i < nentries ; i++ ){
    dvcs.GetEntry( i );

    EventDVCS dvcsevent = dvcs.GetEvent();

    //Free to create histograms here and calculations....
    //Most of the grunt work has already been done, so draw away!
    
    
  }
  c1->cd(1);
  Q2vsXbj->Draw("colz");
  c1->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/dvcstest_v1.pdf");

  return 0;
}

