#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/PhysicsCutManager.h"
#include "../include/PhysicsEvent.h"
#include "../include/Eventh22.h"
#include "../include/Loadh22.h"
#include "../include/EventDVCS.h"
#include "../include/LoadDVCS.h"
#include "../include/HistogramTool.h"
#include "../include/SkimManager.h"
#include "../include/AnalysisManager.h"

#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <sstream>
#include <TStopwatch.h>



Int_t main( int argv1, char* argc[] ){
  // Inputs are provided by script
  // argc[2] is the path way to desired files
  // argc[1] is the file you want to perform analysis on
  // argc[3] is the type of analysis you want - either PID, DVCS, or MC.

  //Timer to measure speed of analysis
  TStopwatch timer;
  timer.Start();
  
  TString processPID("PID");
  TString processDVCS("DVCS");
  TString processMC("MC");
  string mycommand = (std::string)argc[3];

  if( mycommand == processPID ){
   SkimManager skim;
   skim.SkimByFile(argc[2], argc[1]);                                                                                                                                                                                                                                                               
   }
  if( mycommand == processDVCS ){
    AnalysisManager analyze;
    analyze.AnalyzeByFile(argc[2],argc[1]);
    }

  timer.Stop();                                                                                                                                                                                     
  std::cout<<"real time - "<<timer.RealTime()<<std::endl;                                                                                                                                                        
  std::cout<<"cpu time - "<<timer.CpuTime()<<std::endl;    
  return 0;
}


// Below are ghost versions of the main







   //Max files on local disk is 362

    // AnalysisManager analyzetest;
    // std::cout << "Input argument argv " << argv << std::endl;
    // switch ( argv-1 ){
    //case 1:
    //std::cout << "Skimming Files " << std::endl;
    // int start = std::atoi(argc[1]);
    //int end = start+200;
        
    // ON the farm use the following path /lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/root
    //case 2 :
    //std::cout << "Analyzing DVCSroot22 files" << std::endl;
    //analyzetest.AnalyzeByFile("/Users/bclary/Documents/work/run data/DVCSresults/",92);
    // }
  //skimtest.SkimByFile("/Volumes/MYTHESISDAT/rootfiles/",759);
  //skimtest.SkimByFile("/Users/bclary/Documents/work/run data/mixedgoodbadfiles/",7);

  //AnalysisManager analyzetest;
  //analyzetest.AnalyzeByFile("/projet/nucleon/silvia/eg1-dvcs/root22/",10370);

 
  //return 0;
  
  // Loadh22 h22;
  // h22.MakeChain("/Users/bclary/Documents/work/run data/run60001/",1);
  // h22.Init();  
  // Int_t nentries = h22.NumEntries();
  // std::cout<< nentries << std::endl;
  
  // PhysicsCutManager pmanagertest;
  // CutManager managertest;
  // PhysicsEvent peventtest;

  // pmanagertest.InitializeCutsFor("electron + proton");
  // managertest.InitializeCutsFor("electron");
  // managertest.InitializeCutsFor("proton");
  // managertest.InitializeCutsFor("photon");

  // HistogramTool histtoolto;

  // //PhysicsEventBuilder eventbuild;
  // TLorentzVector electronLVi( 0, 0, 5.95, 5.95 );
  // TLorentzVector protonLVi( 0, 0, 0, 0.938 );
  // PhysicsEventBuilder eventbuild( electronLVi, protonLVi );
  // TLorentzVector protoncandLVf, photoncandLVf;
  
  // Int_t numgoodelectron = 0;
  // Int_t numgoodproton = 0;
  // Int_t numgoodphoton = 0;
  // Int_t counter = 0;
  
  // for( Int_t i = 0; i<nentries; i++ ){
    
  //   h22.GetEntry(i);
  //   Eventh22 eventtest = h22.GetEvent();
  //   Int_t gparts = h22.Gpart();
  
  //   bool electron = managertest.PassCut("electron",eventtest, 0);
  //   if( electron ){
  //          numgoodelectron++;
  //     TLorentzVector electronLVf = eventbuild.setParticleLV("electron",eventtest, 0);
      
  //     //histtoolto.MakeElectronPlots(eventtest, 0);
  //     //bool foundproton = false;
  //     //bool foundphoton = false;
  //     // for( Int_t k = 1; k < gparts; k++){
  //     // 	if( !foundproton ){
  //     // 	  foundproton = managertest.PassCut("proton",eventtest, k);	  
  //     // 	  //histtoolto.MakeProtonPlots(eventtest, k);
  //     // 	  protoncandLVf = eventbuild.setParticleLV("proton",eventtest,k);
  //     // 	}
  //     // 	if ( !foundphoton ){
  //     // 	  foundphoton = managertest.PassCut("photon",eventtest, k);
  //     // 	  //histtoolto.MakePhotonPlots(eventtest, k);
  //     // 	  photoncandLVf = eventbuild.setParticleLV("photon",eventtest, k);
  //     // 	}
  //     // }
  //     // PhysicsEvent electronpevent = eventbuild.getPhysicsEvent(electronLVf);
  //     //histtoolto.MakeExclusivityPlots(electronpevent);
  //     // if( foundproton ){

  //     // 	PhysicsEvent allpevent = eventbuild.getPhysicsEvent(electronLVf, protoncandLVf, photoncandLVf );
  //     // 	PhysicsEvent testpevent = eventbuild.getPhysicsEvent(electronLVf, protoncandLVf);
	
  //     // 	bool physicspass = pmanagertest.PassCut(allpevent);
  //     // 	if ( physicspass ){
  //     // 	  counter++;
  //     // 	  histtoolto.MakeExclusivityPlots(testpevent);	  
  //     // 	}
  //     // }

  //   }
  // }
    

  // histtoolto.DrawHistograms();
  
  // std::cout << " >>>>>>>>>>>>> STAGE 1 & 2 PASS RESULTS <<<<<<<<<<< " << std::endl;
  // std::cout<< "Of the " << nentries << " entries there are..." << std::endl;
  // std::cout << " >> good electrons " << numgoodelectron << std::endl;
  // std::cout << " >> good protons "   << numgoodproton   << std::endl;
  // std::cout << " >> good photons "   << numgoodphoton   << std::endl;
  // std::cout << " >> good elastic "   << counter   << std::endl;
//   return 0;
  
// }

  
