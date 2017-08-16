#define analysismanager_cxx
#include "../include/Eventh22.h"
#include "../include/Loadh22.h"
#include "../include/CutManager.h"
#include "../include/AnalysisManager.h"
#include "../include/Calculator.h"
#include "../include/PhysicsEvent.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/PhysicsCutManager.h"
#include "../include/PhysicsCuts.h"
#include "../include/HistogramTool.h"
#include "../include/DVCSHistogramTool.h"
#include "../include/BuildtDVCS.h"
#include "../include/LoadDVCS.h"
#include "../include/LoadPID.h"
#include "../include/RunDB.h"
#include "../include/DVCSHistoMonitor.h"

#include "sqlite3.h"
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

AnalysisManager::AnalysisManager(){

  // TFile *newskimfile;
  // TTree *treeclone;
  originalChain = new TChain("tDVCS");
  ext = ".root";

}

AnalysisManager::~AnalysisManager(){

}

TString AnalysisManager::SkimPrefix(Int_t templevel){

  if( templevel == 1 ){
    skimprefix = "SkimLevel1";
  }
  else if ( templevel == 2 ){
    skimprefix = "SkimLevel2";
  }
  return skimprefix; 
}
  

//Memory Management
void AnalysisManager::Close(){

  //clonedtree->Write();
  //newskimfile->Close();

}

Int_t AnalysisManager::RunNumb( TString tempfname ){
  TString tempfilename(tempfname);
  const char *ext = ".root";
  if ( tempfilename.EndsWith(ext) ) {
    TRegexp runpattern("[0-9][0-9][0-9][0-9][0-9]");
    TString runstring = tempfilename(runpattern);
    runnum = atoi(runstring);
  }
  return runnum;
}


void AnalysisManager::AnalyzeByFile(const char *tempfilename, const char *temppath){
  RunDB eg1runcheck;
  AnalysisManager tempskim;
  //skimprefix = tempskim.SkimPrefix(1);
  Int_t runnumber = tempskim.RunNumb(tempfilename);
  //  DVCSHistogramTool tempdvcshisttool(runnumber);
  filecounter = 0;
  //fileprogress = 0.0;
  TString dvcsprefix("h_dvcs_");
  
  // TSystemDirectory dir(tempdirname, tempdirname);
  //files = dir.GetListOfFiles();
  //  const char *tempfilename, const char *temppath
  //if (files){
    //  TIter next(files);
  // while((file=(TSystemFile*)next()) && (filecounter <= maxfiles) ){

      //Progress Bar 
  /*progressbar = 100;
  std::cout << "\r[";
  fileprogress = double(filecounter)/double(maxfiles);
  Int_t pos = progressbar*fileprogress;
  for( Int_t p = 0; p <= progressbar; ++p){
    if (p < pos){ std::cout << "="; }
    else if (p == pos){ std::cout << ">"; }
      }
  std::cout << "] " << int(fileprogress*100.0) << " %" ;
  std::cout.flush();
  fileprogress = double(filecounter)/double(maxfiles);
  if( fileprogress == 1.0 ){ std::cout << "\nAnalysis complete" << std::endl; }
  *///end of Progress Bar
  
  filetoskim = (std::string)temppath + (std::string)tempfilename;
  file = new TSystemFile(tempfilename, temppath);
  filename = file->GetName();
  std::cout << filename << std::endl;
  if( !file->IsDirectory() && filename.EndsWith(ext) ){
    originalfile = new TFile(filetoskim);
    if(originalfile == 0){
      std::cout << "NULL pointer for originalfile" << std::endl;
      exit(0);
    }
    
    originaltree = (TTree*) originalfile->Get("tPID");//Get("tDVCS");
    originalChain = (TChain*)originalfile->Get("tPID");//Get("tDVCS");
    if( originaltree == 0 || originalChain == 0 ){
      std::cout << "Failed " << std::endl;
      exit(0);
    }
    
    sfiletoskim = (std::string)filetoskim;
    found = sfiletoskim.find_last_of("/");
    filebasename = sfiletoskim.substr(found + 1);
    
    TString inputfile(filebasename);
    Int_t runnumber = loadDVCS.RunNum(inputfile);
    TString inputrun(std::to_string(runnumber));

    TString dvcsoutfile = dvcsprefix + inputrun + ext;
    std::cout << " Creating final Histogram file -> " << dvcsoutfile << std::endl;
    TFile outfile(dvcsoutfile,"recreate");
    //tempfiletoskim = inputfile.Insert(0,"skim");
    //skimfile = new TFile(tempfiletoskim,"RECREATE");
    
    std::cout << " Run Number: " << runnumber << std::endl;
    //See if the run is even good!
    //eg1runcheck.OpenDB();
    //TString s_runid = eg1runcheck.Query("TargetConfiguration","RunID", runnumber);
    //TString s_fc0 = eg1runcheck.Query("FCRunParameters","FC0",runnumber );
    //TString s_fc1 = eg1runcheck.Query("FCRunParameters","FC1",runnumber );
    //eg1runcheck.CloseDB();
    //std::cout << s_runid << " " << s_fc0 << " " << s_fc1 << std::endl;
    //std::cout << "At BDVCSHistograms init" << std::endl;
    BDVCSHistograms bdvcshist;
    bdvcshist.CreateDVCSHistograms(&outfile);

    //COMMENT OUT TO USE EVERYFILE
    //if( atoi(s_runid) == runnumber ){
    //if ( true ){ 
    //TFile outfile(dvcsoutfile,"recreate");
      //      std::cout << " File exists...proceeding to analyze " << std::endl;
      clonedtree = originalChain->CloneTree(0);
      //Change the SkimProcessEntries parameter list to include runnumber or not.
      tempskim.AnalyzeEntries(originalChain, clonedtree, runnumber, bdvcshist);
      
      //std::cout << ">> original file size: " << originalfile->GetSize() << " MB " << std::endl;
      //std::cout << ">> new file size: "      << skimfile->GetSize()      << " MB " << "\n " << std::endl;
      
      originalfile->Close();
      outfile.Write();
      outfile.Close();
      //skimfile->Close();
      //}
      //else{
      //std::cout << ">> Run " << runnumber << " is not in the Target Configuration List that was provided " << std::endl;
      //originalfile->Close();
      //}
    filecounter++;
  }
  std::cout << "Saving histogram file " << std::endl;
  //temphisttool.DrawHistograms();
    //  tempdvcshisttool.AverageBinTool();
    //tempdvcshisttool.DrawDVCSHistograms();
}


void AnalysisManager::AnalyzeEntries( TChain *tempchain, TTree *tempclone, Int_t temprun, BDVCSHistograms bdvcshisttool ){
  //LoadDVCS tDVCS;
  LoadPID tPID;
  RunDB eg1rundata;
  Calculator rundep;
  rundep.SetRunParameters(temprun);
  PhysicsEvent physevents;
  PhysicsCutManager physmanager(rundep);
  tPID.MakeChain(tempchain);
  tPID.Init();

  BuildtDVCS buildtDVCS;
  buildtDVCS.InitTree();

  DVCSHistoMonitor dvcsmonitor(rundep);

  physmanager.InitializeCutsFor("DIS");
  dvcsmonitor.CreateDVCSHist(physmanager, bdvcshisttool );
  // physmanager.InitializeCutsFor("DVCS");

  TLorentzVector target( 0, 0, 0, 0.938272 );
  //PhysicsEventBuilder buildPhys(rundep.BeamEnergyCorrection(temprun), target, rundep );
  eg1rundata.OpenDB();
  TString TargetType = eg1rundata.Query("TargetConfiguration","Target", temprun );
  //TString PeriodID = eg1rundata.Query("RunConfiguration","PeriodID", temprun );
  TString TargPol  = eg1rundata.Query("TargetConfiguration", "Polarization", temprun );
  eg1rundata.CloseDB();
 
  std::cout << ">>>>>>>>>> Run Properties <<<<<<<<<< " << std::endl;
  std::cout << " Target Type : " << TargetType << std::endl;
  std::cout << " Target Polarization : " << TargPol << std::endl;

  Int_t nentries = tPID.NumEntries();
  std::cout << " number of DVCS type events to process " << nentries << std::endl;
  for( Int_t i = 0; i<nentries; i++ ){
    tPID.GetEntry(i);   
    EventPID pid = tPID.GetEvent();
    TString *target = pid.targetType;   
    TString *period = pid.periodID;

    bool foundDIS = false;
    if( !foundDIS ){
      //std::cout << " Finding DIS " << std::endl;
      foundDIS = physmanager.PassCut("DIS", pid );
      //std::cout << " Foudn DIS boolean " << foundDIS << std::endl;
      std::vector<bool> dis_passrate = physmanager.PassCutVector("DIS", pid);
      dvcsmonitor.FillDVCSElHist( dis_passrate, pid, temprun );
      dvcsmonitor.FillDVCSPrHist( dis_passrate, pid, temprun );
      dvcsmonitor.FillDVCSPhHist( dis_passrate, pid, temprun );

      //std::cout << "bh " << pid.beamHelicity << std::endl;
      //std::cout << "ps " << pid.polsign << std::endl;      
      //std::cout << "tp " << pid.targetPolarization << std::endl;

      //std::cout << "tt" <<  *target << std::endl;
 
      if( pid.photonTopology == 2 ){
	//	std::cout<< " Fill DVCS Kin EC " << std::endl;
	dvcsmonitor.FillDVCSKinECHist( dis_passrate, pid, temprun );
      }
      else if( pid.photonTopology == 1 ){
	//std::cout<< " Fill DVCS Kin IC " << std::endl;
	dvcsmonitor.FillDVCSKinICHist( dis_passrate, pid, temprun );
      }

      //std::cout << " PERIOD IS " << *period << std::endl;
      if( *period == "A" && (*target == "NH3B" || *target == "NH3T" || *target == "NH3S")){
	//std::cout<< " Fill Asym A " << std::endl;
	dvcsmonitor.FillAsymHistA( dis_passrate, pid, temprun );      
      }
      if( *period == "B" && (*target == "NH3B" || *target == "NH3T" || *target == "NH3S")){
	//std::cout<< " Fill Asym B " << std::endl;
	dvcsmonitor.FillAsymHistB( dis_passrate, pid, temprun );
      }
    }
  
    if( foundDIS ){

      //      std::cout << " Filling tDVCS " << std::endl;
      buildtDVCS.Fill(pid);
      //This TTree is used by macros for the final analysis...
      
    }    
  }
  buildtDVCS.WriteToTree();
}

