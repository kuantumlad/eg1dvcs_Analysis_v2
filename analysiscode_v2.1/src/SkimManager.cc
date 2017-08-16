#define skimmanager_cxx
#include "../include/Eventh22.h"
#include "../include/Loadh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/SkimManager.h"
#include "../include/Calculator.h"
#include "../include/PhysicsEvent.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/PhysicsCutManager.h"
#include "../include/PhysicsCuts.h"
#include "../include/HistogramTool.h"
#include "../include/DVCSHistogramTool.h"
#include "../include/BuildtDVCS.h"
#include "../include/BuildtPID.h"
#include "../include/LoadDVCS.h"
#include "../include/RunDB.h"
#include "../include/PIDHistograms.h"
#include "../include/BPIDHistograms.h"
#include "../include/PIDHistoMonitor.h"

#include <TFile.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TMath.h>
#include <TString.h>
#include "TROOT.h"
#include "TBrowser.h"
#include <iostream>
#include <string>
#include "TChain.h"
#include "TRegexp.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"

#include <map>
#include <sstream>   // std::string
#include <iomanip>   
#include <cmath>
#include <string>
SkimManager::SkimManager(){

  // TFile *newskimfile;
  // TTree *treeclone;
  originalChain = new TChain("h22");
  ext = ".root";

}

SkimManager::~SkimManager(){

}

TString SkimManager::SkimPrefix(Int_t templevel){

  if( templevel == 1 ){
    skimprefix = "SkimLevel1";
  }
  else if ( templevel == 2 ){
    skimprefix = "SkimLevel2";
  }
  return skimprefix; 
}
  

//Memory Management
void SkimManager::Close(){

  //clonedtree->Write();
  //newskimfile->Close();

}

//Int_t SkimManager::SkimByFile(const char *tempdirname, Int_t maxfiles){ 
void SkimManager::SkimByFile(const char *tempdirname, Int_t startfile, Int_t endfile){ //changed to span over a set of runs 
  RunDB eg1runcheck;
  SkimManager tempskim;
  skimprefix = tempskim.SkimPrefix(1);
  DVCSHistogramTool tempdvcshisttool;
  HistogramTool temphisttool;

  filecounter = 0;
  nthfile = startfile; //added
  TString pidprefix("PID");
  
  TSystemDirectory dir(tempdirname, tempdirname);
  files = dir.GetListOfFiles();
  // TSystemFile *testfind = (TSystemFile*)files->FindObject("root22_59519_a00.root");
  // std::cout <<  testfind->GetName() << std::endl;
  if (files){
    TIter next(files);
    
    while((file=(TSystemFile*)next()) && (startfile <= nthfile) && (nthfile <= endfile) ){
      filename = file->GetName();
      filetoskim = (std::string)tempdirname + filename;
      if( !file->IsDirectory() && filename.EndsWith(ext) ){
	originalfile = new TFile(filetoskim);

	if(originalfile == 0){
	  //std::cout << "NULL pointer for originalfile" << std::endl;
	  continue;
	}
	
	originaltree = (TTree*) originalfile->Get("h22");
	originalChain = (TChain*)originalfile->Get("h22");
	if( originaltree == 0 || originalChain == 0 ){
	  //std::cout << "NULL pointer for originaltree or originalChain " << std::endl;
	  continue;
	}
	       
	sfiletoskim = (std::string)filetoskim;
	found = sfiletoskim.find_last_of("/");
	filebasename = sfiletoskim.substr(found + 1);

	TString inputfile(filebasename);
	TString pidoutfile = pidprefix + inputfile;
	//TFile outfile(pidoutfile,"recreate"); //outputfile creates PIDroot22*.root files 
	//tempfiletoskim = inputfile.Insert(0,"skim");
	//skimfile = new TFile(tempfiletoskim,"RECREATE");
	
	Int_t runnumber = loadh22.RunNum(inputfile);
	nthfile = runnumber; // added this line to skim sets of files
	//See if the run is even good!
	eg1runcheck.OpenDB();
	TString s_runid = eg1runcheck.Query("TargetConfiguration","RunID",runnumber );
	eg1runcheck.CloseDB();

	if( atoi(s_runid) == runnumber ){
	  TFile outfile(pidoutfile,"recreate"); // changed from dvcsoutfile to pidoutfile 

	  clonedtree = originalChain->CloneTree(0);

	  //Change the SkimProcessEntries parameter list to include runnumber or not.
	  //tempskim.SkimProcessEntries(originalChain, clonedtree, runnumber, tempdvcshisttool, temphisttool);
	
	  //std::cout << ">> original file size: " << originalfile->GetSize() << " MB " << std::endl;
	  //std::cout << ">> new file size: "      << skimfile->GetSize()      << " MB " << "\n " << std::endl;
	  delete clonedtree;
	  outfile.Write();
	  outfile.Close();
	  //skimfile->Close();
	  originalfile->Close();
	}
	else{
	  //std::cout << ">> Run " << runnumber << " is not in the Target Configuration List that was provided " << std::endl;
	  originalfile->Close();
	}
	filecounter++;
      }
    }
  }
  //temphisttool.DrawHistograms();
  
  // tempdvcshisttool.DrawDVCSHistograms();
  // tempdvcshisttool.AverageBinTool();
  
  
}


void SkimManager::SkimByFile(const char *tempdirname, const char *temppath ){ //changed to run on JLab's farm // changed tempdirname to filename
  RunDB eg1runcheck;
  //SkimManager tempskim;
  skimprefix = SkimPrefix(1);
  DVCSHistogramTool tempdvcshisttool;
  HistogramTool temphisttool;

  TString pidprefix("PID");
  TString mcpidprefix("mcPID");
  filetoskim = (std::string)temppath + (std::string)tempdirname;
  file = new TSystemFile(tempdirname, temppath);
  filename = file->GetName();
  
    if( !file->IsDirectory() && filename.EndsWith(ext) ){
      originalfile = new TFile(filetoskim);
      
      if(originalfile == 0){
      //std::cout << "NULL pointer for originalfile" << std::endl;
      //continue;
	exit(0);
      }
      originaltree = (TTree*)originalfile->Get("h22");
      originalChain = (TChain*)originalfile->Get("h22");
      if( originaltree == 0 || originalChain == 0 ){
	//std::cout << "NULL pointer for originaltree or originalChain " << std::endl;
	//continue;
	exit(0);
      }
    
    sfiletoskim = (std::string)filetoskim;   
    found = sfiletoskim.find_last_of("/");
    filebasename = sfiletoskim.substr(found + 1);
    
    TString inputfile(filebasename);
    //tempfiletoskim = inputfile.Insert(0,"skim");
    //skimfile = new TFile(tempfiletoskim,"RECREATE");
    //See if the file is in the Good File database (list is taken from Andrey) !
    std::string checkfile  = "\""+filebasename+"\"";
    eg1runcheck.OpenDB();
    TString s_runid = eg1runcheck.Query("BiselliFileWithFC", "BiselliFileID", checkfile, "BiselliFileID"); // word of warning, compiler preferes type std::string over TString as input
    eg1runcheck.CloseDB();

    //This checks if input file is a MC file
    Int_t isMC = loadh22.MCCheck(inputfile);

    // COMMENTING THIS OUT TO ANALYZE EVERY UNCORRUPTED FILE    
    if( s_runid == inputfile ){
      TString pidoutfile = pidprefix + inputfile;
      TFile outfile(pidoutfile,"recreate"); //outfile creates PIDroot22_*.root files with personalized trees
      Int_t runnumber = loadh22.RunNum(inputfile);
      
      BPIDHistograms pidhisttool;
      pidhisttool.InitiateALLHistograms();
      pidhisttool.CreateHistDirectories(&outfile);

      clonedtree = originalChain->CloneTree(0);
      TStopwatch timer;
      timer.Start();
      //SkimProcessEntries is where all the magic happens
      SkimProcessEntries(originalChain, clonedtree, runnumber, tempdvcshisttool, temphisttool, pidhisttool, &outfile); //added outfile to function arguments week of 2/14/2017
      //std::cout << "here" <<std::endl;	
      delete clonedtree;
      timer.Stop();
      outfile.Write();
      outfile.Close();
      std::cout<< " real time SkimProcessEntries - "<< timer.RealTime() << std::endl;
      std::cout<< " cpu time SkimProcessEntries - "<< timer.CpuTime() << std::endl;

      //std::cout << " breaking1 " << std::endl;
      //skimfile->Close();
      originalfile->Close();
      // COMMENTED OUT TO ANALYZE EVERY FILE
    }

    if( isMC ){
      //Double check it is in the MC file list 
      eg1runcheck.OpenDB();
      TString s_mcid = eg1runcheck.Query("MCGoodFiles", "MCGoodFileID", checkfile); 
      eg1runcheck.CloseDB();
      if( s_mcid == inputfile ){
	std::cout<<" Analyzing MC File " << std::endl;
	Int_t mcON = -1;
	TString mcpidoutfile = mcpidprefix + inputfile;
	TFile mcoutfile(mcpidoutfile,"recreate"); //outfile creates PIDroot22_*.root files with personalized trees
	Int_t runnumber = mcON;

	BPIDHistograms pidhisttool;
	pidhisttool.InitiateALLHistograms();
	pidhisttool.CreateHistDirectories(&mcoutfile);
	
	clonedtree = originalChain->CloneTree(0);
	
	//Change the SkimProcessEntries parameter list to include runnumber or not.
	SkimProcessEntries(originalChain, clonedtree, runnumber, tempdvcshisttool, temphisttool, pidhisttool, &mcoutfile); //added outfile to function arguments week of 2/14/2017
	
	delete clonedtree;
	mcoutfile.Write();
	mcoutfile.Close();
	//skimfile->Close();
	originalfile->Close();
      }
    }
    else {

      //      std::cout << " breaking 2" << std::endl;
      //std::cout << ">> Run " << runnumber << " is not in the Target Configuration List that was provided nor is it an MC file " << std::endl;
            originalfile->Close();
    }
    filecounter++;
    }

    //std::cout << " breaking " << std::endl;
      /// originalfile->Close();

      //std::cout << " breaking " << std::endl;
    temphisttool.DrawHistograms();

    //std::cout << " breaking " << std::endl;
    //    temphisttool.SavePlots("mc");
}

/*Routine to skim a given root file. User defines the skim level to apply to root file. 
For level 1 cuts pass "1" as the argument to SkimLevel method
For level 2 cuts pass "2" as the argument to SkimLevel method.
 */
void SkimManager::SkimLevel( Int_t tempSkimLevel, TChain *tempchain  ){
  Loadh22 h22;
  h22.MakeChain(tempchain);
  std::cout << " >> " << h22.NumEntries() << std::endl;
  if( tempSkimLevel == 1 ){

    std::cout << " >>skimlevel 1  with " << std::endl;
  }
  else if ( tempSkimLevel == 2 ){
    std::cout<< " >>skimlevel 2 with  "<< std::endl;
  }
  else{
    std::cout << " Please specify either skim level 1 or 2. " << std::endl;
    std::cout << " Or define a new skim level and add to existing code base " << std::endl;
  }
}


void SkimManager::SkimCuts(TString tempreaction){

  CutManager cutmanager1;

  if( tempreaction == "electron + proton + photon" ){
  cutmanager1.InitializeCutsFor("electron");
  cutmanager1.InitializeCutsFor("proton");
  cutmanager1.InitializeCutsFor("photon");  
  }

  else if ( tempreaction == "electron + proton" ){
    cutmanager1.InitializeCutsFor("electron");
    cutmanager1.InitializeCutsFor("proton");
  }
}

/*
FIRST SKIM PROCESS ENTRIES function without run number
 */
void SkimManager::SkimProcessEntries( TChain *tempchain, TTree *tempclone){

  Loadh22 h22;
  CutManager managertest;
  h22.MakeChain(tempchain);
  Int_t tempnumber = 0;
  h22.Init(tempnumber); // put as placeholder 2-20- 2017 bc new definition of init function
  
  managertest.InitializeCutsFor("electron");
  managertest.InitializeCutsFor("proton");
  managertest.InitializeCutsFor("ecphoton");
  managertest.InitializeCutsFor("icphoton");
  
  Int_t nentries = h22.NumEntries();
  
  Int_t numgoodelectron = 0;
  Int_t numgoodproton = 0;
  Int_t numgoodphoton = 0;
  Int_t fillcounter = 0;
  
  for( Int_t i = 0; i<nentries; i++ ){
    
    h22.GetEntry(i);
    Eventh22 eventtest = h22.GetEvent();
    Int_t gparts = h22.Gpart();

    bool electron = managertest.PassCut("electron",eventtest, 0);
    if( electron ){
      numgoodelectron++;
      bool foundproton = false;
      bool foundphoton = false;
      for( Int_t k = 1; k < gparts; k++){
	if( !foundproton ){
	  foundproton = managertest.PassCut("proton",eventtest, k);
	}
	if( !foundphoton ){
	  foundphoton = managertest.PassCut("photon",eventtest, k);
	}
      }

      if( foundproton ){
	numgoodproton++;
      }
      if( foundphoton ){
	numgoodphoton++;
      }
      if( foundphoton && foundproton ){
	tempclone->Fill();
	fillcounter++;
      }
    }
  }
  //tempclone->Write(); 
  //tempclone->Scan();
}

// Overloaded function for user to incorporate run dependent calculations in the analysis.
// This method is used in the SkimByFile method which goes through each cuts each file one at a time
// 1-13-2017 should probably remove the dvcshist from this function as it is not needed for the PID.
void SkimManager::SkimProcessEntries( TChain *tempchain, TTree *tempclone, Int_t temprun, DVCSHistogramTool dvcshisttool, HistogramTool histtool, BPIDHistograms pidhisttool, TFile *tempoutfile){
  Loadh22 h22;
  Calculator rundep;
  rundep.SetRunParameters(temprun);
  std::string tempfname = (std::string)tempoutfile->GetName();
  std::string temprootname = tempfname.erase(0,3);
  rundep.SetFCRunValues(temprun, temprootname);
  CutManager managertest(rundep);
  PhysicsEvent physevents;
  PhysicsCutManager physmanager(rundep);
  PIDHistoMonitor pidmonitor(rundep);
  BuildtPID buildtPID;
  buildtPID.InitPIDTree();
 
  pidhisttool.AddCorrections(rundep);  

  h22.MakeChain(tempchain);
  h22.Init(temprun);
  
  managertest.InitializeCutsFor("electron");
  managertest.InitializeCutsFor("proton");
  managertest.InitializeCutsFor("ecphoton"); 	  
  managertest.InitializeCutsFor("icphoton");
  physmanager.InitializeCutsFor("DIS");
  physmanager.InitializeCutsFor("DVCS");
    
  pidmonitor.CreatePIDHist(managertest, pidhisttool );

  Int_t totalgoodelectron = 0;
  Int_t totalgoodproton = 0;
  Int_t fillcounter = 0;
  Int_t totalgoodphoton = 0;
  Int_t totalgoodecphoton = 0;
  Int_t totalgoodicphoton = 0;
  Int_t IChitcounter = 0;
  Int_t EChitcounter = 0;
  Int_t ICEChitcounter = 0;
  
  TLorentzVector target( 0, 0, 0, 0.938272 );
  PhysicsEventBuilder buildPhys(rundep.BeamEnergyCorrection(temprun), target, rundep );
  
  Int_t nentries = h22.NumEntries();
  Int_t atleast1proton = 0;
  Int_t oneelectronevent = 0;


  Int_t singleElectron = 0;
  Int_t multiElectron = 0;
  Int_t singleEP = 0;
  Int_t multiProton  = 0;
  Int_t totalEPG = 0;
  Int_t totalEPGG = 0;
  Int_t  notzeroel = 0;
  Int_t zerothel = 0;
  Int_t discounter = 0;
  Int_t dvcsIC = 0; Int_t dvcsEC = 0;
  Int_t heliZero = 0;
  Int_t heliOne = 0;

  std::map<Int_t, TLorentzVector > energeticPhoton;
  Int_t  nechittotal, nichittotal;
  nechittotal =  nichittotal = 0;

  rundep.PrintRunInformation();

  for( Int_t i = 0; i<nentries; i++ ){
    h22.GetEntry(i);
    //    std::cout << " starting entry " << i << std::endl;
    Eventh22 eventtest = h22.GetEvent();

    //h22.CallByRef(eventtest);

    Int_t gparts = h22.Gpart();
    Int_t sparts = h22.SPart();

    //std::cout << " gparts - " << gparts << std::endl;
    //std::cout << " sparts - " << sparts << std::endl;
    Int_t numgoodelectron = 0;
    Int_t numgoodproton = 0;
    Int_t numgoodphoton = 0;
    Int_t numgoodecphoton = 0; 
    Int_t numgoodicphoton = 0; 
    Int_t numgoodphotons = 0;
    Int_t protonindex = 0, ecphotonindex = 0, icphotonindex = 0, electronindex = 0;
    TLorentzVector el_LV( 0, 0, 0, 0);
    TLorentzVector pr_LV( 0, 0, 0, 0);
    TLorentzVector ecph_LV( 0, 0, 0, 0);
    TLorentzVector icph_LV( 0, 0, 0, 0);
    ////////////////////////////////////////////////////////////////////////
    // Commented out code below is from a bygone era when I was writing this 
    // without reference to Angela's code.
    //std::cout << " Electron Test here " << std::endl;
    // bool foundelectron = managertest.PassCut("electron",eventtest, 0);
    // if( foundelectron ){
    //   //std::cout << " Found a good electron " << std::endl;
    //   el_LV = buildPhys.setParticleLV("electron",eventtest, 0);
    //   numgoodelectron++;
    //   totalgoodelectron++;
    //   electronindex = 0;
    //   histtool.MakeElectronPlots( eventtest, 0, rundep );
    //  bool foundelectron = false;
    //    bool foundproton = false;
    //  bool foundecphoton = false;
    Int_t nelec = 0;// added to match Angela
    Int_t nprot = 0;
    Int_t necph = 0;
    Int_t nicph = 0;
    Int_t nph = 0;
     
    for( Int_t k = 0; k < gparts; k++){
      bool foundelectron = false;
      // bool foundproton = false;
      bool foundecphoton = false;
      //std::cout << " Electron test " << std::endl;
      if( !foundelectron ){
	foundelectron = managertest.PassCut("electron",eventtest, k); //Calculations in PassCut include corrections to direction cosines, and raster vertex correction. 
	std::vector<bool> el_passrate = managertest.PassCutVector("electron", eventtest, k);
	pidmonitor.FillElectronHisto( el_passrate, eventtest, k, temprun );
	if( foundelectron ){
	  //	  std::cout << " FOund Electron " << std::endl;
	  el_LV = buildPhys.setParticleLV("electron",eventtest,k); //applied momentum correction
	  numgoodelectron++;
	  totalgoodelectron++;
	  nelec++;
	  electronindex = k;
	  if( electronindex == 0 ){ zerothel++; }
	  if( electronindex != 0 ){ notzeroel++; }//histtool.MakeElectronPlots( eventtest, k, rundep );
	  //pidhisttool.FillGoodCandidateParticleTHn( 11, el_passrate, eventtest, k );
	  pidhisttool.ElectronHist(eventtest, electronindex, temprun );
	  pidhisttool.MiscHistos(eventtest,electronindex, temprun );
	}
      }
    }
     if( nelec == 1 ){
      eventtest.SetGoldenElectronIndex(electronindex);
      eventtest.SetNumGoodElectron(nelec);
    }
    if(nelec == 1 ){
      for( Int_t j = 0; j < gparts; j++ ){
	bool foundproton = false;
	if( !foundproton ){
	  foundproton = managertest.PassCut("proton", eventtest, j); // Similiar corrections to thse in the electron test are applied here
	  std::vector<bool> pr_passrate = managertest.PassCutVector("proton", eventtest, j);                                                                                                       
	  pidmonitor.FillProtonHisto( pr_passrate, eventtest, j, temprun );
	  //pidhisttool.FillProtonTHn( pr_passrate, eventtest, j );
	  if( foundproton && j != electronindex ){
	    pr_LV = buildPhys.setParticleLV("proton", eventtest, j); //applied momentum correction
	    numgoodproton++;
	    totalgoodproton++;
	    protonindex = j;
	    nprot++;
	    // histtool.MakeProtonPlots( eventtest, protonindex, rundep, temprun  );
	    //pidhisttool.FillGoodCandidateParticleTHn( 2212, pr_passrate, eventtest, j );
	    eventtest.SetGoldenProtonIndex(protonindex);
	    eventtest.SetNumGoodProton(nprot); 
	    pidhisttool.ProtonHist(eventtest, protonindex, temprun );
	  }
	}
      }

      //// testing if vertex is correct for photons /////
      //if( nelec == 1 ){ 
	TLorentzVector tempLV(0,0,0,0);
	TVector3 tempv3(0,0,0);
	//Take the starting positin as the average position of the electron and proton
	Double_t z_pos = 0.;
	zpos = 0.;
	Double_t vz_corr_e = 0.;
	Double_t vz_corr_pro = 0.; 
	//	std::cout << " Calling Electron Correction " << std::endl;
	Double_t el_pcorr = rundep.ElectronCorrectedMntm(eventtest.p[eventtest.goldenelectronindex]);
	//std::cout << ">> corrected - " << el_pcorr << "\n" << ">> original - " << eventtest.p[eventtest.goldenelectronindex] << std::endl;
	//std::cout << " Calling CorrectedCosineCorrection for Electron" << std::endl;
	Double_t *vz_corr_el = rundep.CorrectedCosineCorrection( temprun, eventtest, eventtest.goldenelectronindex, el_pcorr );
 	Double_t vz_elc = vz_corr_el[3];


	z_pos = fabs(vz_corr_el[3]);// fabs(tempevent.vz[tempevent.goldenelectronindex]); //this is the vertex of the event.
	zpos = fabs( eventtest.vz[eventtest.goldenelectronindex]);

	//std::cout << " z_pos 1 " << z_pos << std::endl;
	Double_t z_pose = fabs(vz_corr_el[3]);
	vz_corr_e = vz_corr_el[3];


	if( nprot == 1 ){
	  //std::cout << " Calling Proton Correction " << std::endl;
	  Double_t pr_pcorr = rundep.ProtonCorrectedMntm( eventtest.p[eventtest.goldenprotonindex] );
	  Double_t pr_p = eventtest.p[eventtest.goldenprotonindex];
	  //std::cout << " corrected - " << pr_pcorr << " \n " << " original - " << pr_p << std::endl;
	  //std::cout << " Calling CorrectedCosineCorrection for Protoon " << std::endl;
	  Double_t *vz_corr_pr = rundep.CorrectedCosineCorrection( temprun, eventtest, eventtest.goldenprotonindex, pr_pcorr );
	  z_posp = fabs(vz_corr_pr[3]);
	  //std::cout << " corrected proton vertex " << vz_corr_pr[3] << std::endl;
	  //std::cout << " corrected electron vertex " << vz_corr_e << std::endl;
	  
	  z_pos = fabs((vz_corr_e + vz_corr_pr[3])/2.);
	  //std::cout << " z_pos 2 " << z_pos << std::endl;
	  zpos = fabs((eventtest.vz[eventtest.goldenelectronindex] + eventtest.vz[eventtest.goldenprotonindex])/2.);
	  //	  std::cout << fabs(eventtest.vz[eventtest.goldenelectronindex]) << " " << fabs(eventtest.vz[eventtest.goldenprotonindex]) << " " << fabs(eventtest.vz[eventtest.goldenelectronindex] + eventtest.vz[eventtest.goldenprotonindex]) << std::endl;
	  //histtool.h_pz->Fill(fabs(eventtest.vz[eventtest.goldenprotonindex]) );
	  //histtool.h_pzc->Fill(z_posp);
	  //histtool.h_vzsum->Fill( fabs(eventtest.vz[event.goldenelectronindex] + eventtest.vz[eventtest.goldenprotonindex]) );
	  histtool.FillPZ( fabs(eventtest.vz[eventtest.goldenprotonindex]), z_posp, fabs(eventtest.vz[eventtest.goldenelectronindex] + eventtest.vz[eventtest.goldenprotonindex]), pr_pcorr );
	}

	//	Double_t zpos = fabs((eventtest.vz[eventtest.goldenprotonindex] + eventtest.vz[eventtest.goldenelectronindex] )/2. );
	//std::cout << " Filling histogram with z_pos - " << z_pos << std::endl;
	histtool.TestPlot1D(z_pose, z_posp, z_pos, fabs(eventtest.vz[eventtest.goldenelectronindex]), fabs(eventtest.vz[eventtest.goldenprotonindex]), zpos );	  
	//}
      ////////
      for( Int_t m = 0; m < gparts; m++ ){
	bool foundecphoton = false;
	if ( !foundecphoton ){
 	  foundecphoton = managertest.PassCut("ecphoton",eventtest, m);
	  std::vector<bool> ecph_passrate = managertest.PassCutVector("ecphoton", eventtest, m);                                                                                                     
	  pidmonitor.FillECPhotonHisto( ecph_passrate, eventtest, m, temprun );
	  //pidhisttool.FillECPhotonTHn( ecph_passrate, eventtest, m);
	  if( foundecphoton ){
	    numgoodecphoton++; // pass the numgoodecphoton into photon kin, this will be array index.
	    //ecph_LV = buildPhys.setParticleLV("photon",eventtest, m); //applied mntm correction
	    //buildPhys.setECPhotonKinematics( ecph_LV, numgoodecphoton );
	    totalgoodecphoton++;
	    ecphotonindex = m;
	    necph++;
	    
	    rundep.StorePhotons( eventtest, ecphotonindex, 2, temprun );
	    //histtool.MakePhotonPlots( eventtest, ecphotonindex, rundep  ); 
	    //pidhisttool.FillGoodCandidateParticleTHn( 11000, ecph_passrate, eventtest, m );
	    pidhisttool.ECPhotons(eventtest, ecphotonindex, temprun );
	  }
	}
      }  
    }
    
    Int_t ec_detector = 2;
    eventtest.SetNumGoodPhotons(necph, ec_detector );
    
    // Find IC photon candidates given that there is exactly one electron candidate  
    if( nelec  ==  1 ){// && nprot == 1){
      for( Int_t m = 0; m < sparts; m++ ){
	bool foundicphoton = false;
	if( !foundicphoton ){
	  foundicphoton = managertest.PassCut("icphoton",eventtest, m);
	  std::vector<bool> icph_passrate = managertest.PassCutVector("icphoton", eventtest, m);                                                                                                     
	  pidmonitor.FillICPhotonHisto( icph_passrate, eventtest, m, temprun );
	  //pidhisttool.FillICPhotonTHn( icph_passrate, eventtest, m);
	  //bool timingcut = fabs(eventtest.tc[m] - eventtest.sc_t[electronindex] + eventtest.sc_r[electronindex]/30.0) < 2.0; // NOT IN AN
	  if( foundicphoton ){// && timingcut ){
	    //	    icph_LV = buildPhys.setParticleLV("icphoton", eventtest, m); //corrected this....
	    numgoodicphoton++;
	    //buildPhys.setICPhotonKinematics( icph_LV, numgoodicphoton );
	    totalgoodicphoton++;
	    icphotonindex = m;
	    nicph++;
	    rundep.StorePhotons( eventtest, icphotonindex, 1, temprun );
	    pidhisttool.ICPhotons(eventtest, icphotonindex, temprun );
	    //histtool.MakeICPhotonPlots( eventtest, icphotonindex, temprun );
	    //pidhisttool.FillGoodCandidateParticleTHn( 110000, icph_passrate, eventtest, m );
	  }
	}
      }
      Int_t ic_detector = 1;
      eventtest.SetNumGoodPhotons(nicph, ic_detector );
    }
   
    Int_t ecic_detector = 3;
    Int_t add_photons = -1;
    eventtest.SetNumGoodPhotons( add_photons, ecic_detector );
    bool ElectronProtonGammaEvent = false;
    //Rates for different processes
    if( nelec == 1 ){ singleElectron++;}
    if ( nelec > 1 ){ multiElectron++; }
    nph = nicph + necph;
    histtool.TestPlots(nph);
    if( nprot == 1  && nelec == 1 ){ singleEP++; }
    if ( nprot > 1 ){ multiProton++;}
    if( nelec == 1 && nprot == 1 && nph == 1 ){ totalEPG++;  }
    if( nelec == 1 && nprot == 1 && nph > 1 ){ totalEPGG++;  }
    
    //Individually count those stored in the map to verify results
    if( nelec == 1 && nprot == 1 && nph >= 1 ){ // change back to == for expected sum of ic and ec hits
      rundep.mostEnergeticPhoton(energeticPhoton);
      TLorentzVector photonLV(0,0,0,0);
      Int_t photondetectorID = -1;
      std::map<Int_t, TLorentzVector>::iterator itert;
      for( itert =  energeticPhoton.begin(); itert!=energeticPhoton.end(); ++itert ){
	//      std::cout << itert->first << " " << itert->second.E() << std::endl;
	if( itert->first == 1 ){ nichittotal++; photondetectorID = itert->first; photonLV = itert->second; }
	else if ( itert->first == 2 ){ nechittotal++; photondetectorID = itert->first; photonLV = itert->second; }
	//	std::cout<< " sending the hit location of " << photondetectorID << " to eventh22 " << std::endl;
	eventtest.ChosenPhoton(photondetectorID, photonLV);
	}
      //}
    
    //Set chosen photon here so it is available to physicseventbuilder 
    // Photon has energy corrected here
    
    //      std::cout << " >>>>> Setting physics Event " << std::endl;
      PhysicsEvent physicsevent = buildPhys.setPhysicsEvent(eventtest);
      Double_t mtranmntm = TMath::Sqrt(physicsevent.perpX*physicsevent.perpX + physicsevent.perpY*physicsevent.perpY);
      Double_t deltaplane = fabs(physicsevent.dephi)/(3.14159) * 180.0;
      Double_t deltaTheta = physicsevent.deltaTheta/(3.14159) * 180;

      //      if( physicsevent.Q2 > 1 && physicsevent.w > 2 && physicsevent.ph_LV.E() >= 1 && physicsevent.mm < 0.3 &&  
      //  mtranmntm < 0.15 && deltaplane < 2 && fabs(physicsevent.mm2epg) < 0.1 && deltaTheta < 1.5 ){
	discounter++;
	Int_t eventheli = eventtest.ihel;
	//std::cout << " Entry: " << i << " Event Helicity: " << eventheli << " --  PhysicsEvent Helicity: " << physicsevent.helic<<  std::endl;

	if( physicsevent.helic == 0 ){
	  heliZero++;
	}
	else if( physicsevent.helic == 1 ){
	  heliOne++;
	}
	buildtPID.Fill(physicsevent);
	histtool.MakeExclusivityPlots( physicsevent );
	
	if( physicsevent.phhitid == 1 ) dvcsIC++;
	else if ( physicsevent.phhitid == 2 ) dvcsEC++;
	
	//}
    }
    
    eventtest.ClearCountersNIndices();
    rundep.ClearPhotonVector();
    energeticPhoton.clear();
  }
  
  //uncomment tempclone items to clone the root22 tree, and comment out the buildtDVCS fill command.
  //tempclone->Write();//"", TObject::kOverwrite); 
  //tempclone->Scan();
  //std::cout<< "Writing to Tree " << std::endl;
  buildtPID.WriteToTree();
  //pidhisttool.WriteSparses( tempoutfile );
  //  pidhisttool.WriteSparses( );
  //  pidhisttool.PIDHistWrite();////////////
  //DVCSoutfile.Write();
  //DVCSoutfile.Close();
  //dvcshisttool.CarveQ2XbjBins();

  //Comment out the pass details when running on the farm
  //managertest.SummerizeOut("electron"); 
  //managertest.SummerizeOut("proton"); 
  //managertest.SummerizeOut("ECphoton"); 
  //managertest.SummerizeOut("ICphoton"); 
  pidhisttool.ParticleMultiplicity( singleElectron,multiElectron, singleEP, multiProton, totalEPG, totalEPGG, nichittotal, nechittotal, notzeroel, zerothel, totalgoodelectron,totalgoodproton, totalgoodecphoton, totalgoodicphoton, discounter, dvcsIC, dvcsEC);


  std::cout << " >>>>>>>>>>>>> PASS RESULTS <<<<<<<<<<<< " << std::endl;
  std::cout << "  Of the " << nentries<< " entries there are..." << std::endl;
  std::cout << " >> total number of 1 electron events " << singleElectron << std::endl;
  std::cout << " >> total number of n electron events " << multiElectron << std::endl;
  std::cout << " >> total number of 1 electron and 1 proton events " << singleEP << std::endl;
  std::cout << " >> total number of n proton events " << multiProton << std::endl;
  std::cout << " >> total number of 1 electron and 1 proton and 1 photon events " << totalEPG << std::endl;
  std::cout << " >> total number of 1 electron and 1 proton and n photon events " << totalEPGG << std::endl;
  std::cout << " >> total number of photons in IC " << nichittotal << std::endl;
  std::cout << " >> total number of photons in EC " << nechittotal << std::endl;
  std::cout << " >> total number of electrons not with zero index " << notzeroel << std::endl;
  std::cout << " >> total number of electrons with zero index " << zerothel << std::endl; 
  std::cout << " >> detected electrons " << totalgoodelectron << std::endl;
  std::cout << " >> detected protons "   << totalgoodproton   << std::endl;
  std::cout << " >> detected EC photons "<< totalgoodecphoton   << std::endl;
  std::cout << " >> detected IC photons "<< totalgoodicphoton   << std::endl;
  std::cout << " >> Number of 0 helicity states " << heliZero << std::endl;
  std::cout << " >> Number of 1 helicity states " << heliOne << std::endl;
  std::cout << " >> DVCS candidate counter " << discounter << std::endl;
  std::cout << " >> DVCS IC candidate counter " << dvcsIC << std::endl;
  std::cout << " >> DVCS EC candidate counter " << dvcsEC << std::endl;
  std::cout << " >>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<< "<< std::endl;
  
}
