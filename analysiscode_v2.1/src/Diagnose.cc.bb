#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/Eventh22.h"
#include "../include/Loadh22.h"
#include "../include/HistogramTool.h"
#include "../include/SkimManager.h"

#include <iostream>
#include <map>
#include <vector>
//Max files on local disk is 364

Int_t main( void ){

  Loadh22 h22;
  Calculator correct;
  correct.SetRunParameters(60001);
  CutManager managertest(correct);

  h22.MakeChain("/Users/bclary/Documents/work/run data/run60001/",2);
  h22.Init();  
  Int_t nentries = h22.NumEntries();
  std::cout<< " Number of entries to process -> " <<nentries << std::endl;
  
  // CutManager managertest;
  managertest.InitializeCutsFor("electron");
  managertest.InitializeCutsFor("proton");
  managertest.InitializeCutsFor("ecphoton");
  managertest.InitializeCutsFor("icphoton");

  HistogramTool histtoolto;

  Int_t numgoodevents = 0;
  Int_t electronindex = -1;
  Int_t protonindex = -1;
  Int_t photonindex = -1;
  
  
  std::map<Int_t, std::vector<Int_t> > goodentries;
  std::vector<Int_t> goodevents;
  
  for( Int_t i = 0; i<nentries; i++ ){
    
    h22.GetEntry(i);
    Eventh22 eventtest = h22.GetEvent();
    Int_t gparts = h22.Gpart();
    Int_t sparts = h22.SPart();
    
    Int_t numgoodelectron = 0; Int_t totalgoodelectron = 0;
    Int_t numgoodproton = 0; Int_t totalgoodproton = 0;
    Int_t numgoodphoton = 0; Int_t totalgoodphoton = 0;
    Int_t numgoodecphoton = 0; Int_t totalgoodecphoton = 0;
    Int_t numgoodicphoton = 0; Int_t totalgoodicphoton = 0;
    Int_t numgoodphotons = 0;
    
    bool electron = managertest.PassCut("electron",eventtest, 0);
    if( electron ){
      numgoodelectron++;
      electronindex = 0;
      //histtoolto.MakeElectronPlots(eventtest, 0);
      
      bool foundproton = false;
      bool foundecphoton = false;
      for( Int_t k = 1; k < gparts; k++){
	if( !foundproton ){
	  foundproton = managertest.PassCut("proton",eventtest, k);
	  if( foundproton ){
	    //histtoolto.MakeProtonPlots(eventtest, k);
	    numgoodproton++;}
	}
	if ( !foundecphoton ){
	  foundecphoton = managertest.PassCut("ecphoton",eventtest, k);
	  if( foundecphoton ){
	    //histtoolto.MakePhotonPlots(eventtest, k);
	    numgoodecphoton++;}
	}
      }
      bool foundicphoton = false;
      for( Int_t m = 0; m < sparts; m++ ){
      	bool foundicphoton = managertest.PassCut("icphoton",eventtest, m);
	if( !foundicphoton ){
	  foundicphoton = managertest.PassCut("icphoton",eventtest, m);
	  if( foundicphoton ){
	    //histtoolto.MakeICPhotonPlots(eventtest, m );
	  numgoodicphoton++;}
      	}
      }
    }
    numgoodphotons = numgoodecphoton + numgoodicphoton;

    
    //   std::cout<< " >> numgoodelectron " << numgoodelectron << " >> numgoodproton "<<numgoodproton<<" >> numgoodecphotons " <<  numgoodecphoton << " numgoodicphotons" << numgoodicphoton << std::endl;

    if( numgoodelectron == 1 &&  numgoodproton == 1 && numgoodphotons >= 1 ){
      numgoodevents++;
    }
  }
  std::cout<< " >> good event total " << numgoodevents << std::endl;
  //histtoolto.DrawHistograms();
  
  // std::cout << " >>>>>>>>>>>>> SKIM PASS RESULTS <<<<<<<<<<< " << std::endl;
  // std::cout<< "Of the " << nentries << " entries there are..." << std::endl;
  // std::cout << " >> good electrons " << numgoodelectron << std::endl;
  // std::cout << " >> good protons "   << numgoodproton   << std::endl;
  // std::cout << " >> good ecphotons "   << numgoodecphoton << std::endl;
  // std::cout << " >> good icphotons "   << numgoodicphoton << std::endl;

  return 0;
}

  
