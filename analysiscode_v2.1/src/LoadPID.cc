#define loadpid_cxx
#include "../include/LoadPID.h"
#include "../include/EventPID.h"

#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TRegexp.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TSystemFile.h"

#include <iostream>

LoadPID::LoadPID(){

  fChain = new TChain("tPID");
  runnumber = 0;

}

LoadPID::~LoadPID(){
  
   fChain->Delete();
  
}

void LoadPID::Init(){
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   
   fChain->SetBranchAddress("run", &pid.run, &b_run);
   fChain->SetBranchAddress("periodID", &pid.periodID, &b_periodID);
   fChain->SetBranchAddress("beamEnergy", &pid.beamEnergy, &b_beamEnergy);
   fChain->SetBranchAddress("beamHelicity", &pid.beamHelicity, &b_beamHelicity);
   //   fChain->SetBranchAddress("polsign", &pid.polsign, &b_polsign);
   fChain->SetBranchAddress("targetType", &pid.targetType, &b_targetType);
   fChain->SetBranchAddress("targetPolarization", &pid.targetPolarization, &b_targetPolarization);
   fChain->SetBranchAddress("wpstatus", &pid.wpstatus, &b_wpstatus);
   fChain->SetBranchAddress("FC0", &pid.FC0, &b_FC0);
   fChain->SetBranchAddress("FC1", &pid.FC1, &b_FC1);
   fChain->SetBranchAddress("el_px", &pid.el_px, &b_el_px);
   fChain->SetBranchAddress("el_py", &pid.el_py, &b_el_py);
   fChain->SetBranchAddress("el_pz", &pid.el_pz, &b_el_pz);
   fChain->SetBranchAddress("el_E", &pid.el_E, &b_el_E);
   fChain->SetBranchAddress("el_vertex", &pid.el_vertex, &b_el_vertex);
   fChain->SetBranchAddress("el_DCsect", &pid.el_DCsect, &b_el_DCsect);
   fChain->SetBranchAddress("el_thetadc", &pid.el_thetadc, &b_el_thetadc);
   fChain->SetBranchAddress("el_phidc", &pid.el_phidc, &b_el_phidc);
   fChain->SetBranchAddress("el_nphe", &pid.el_nphe, &b_el_nphe);
   

   fChain->SetBranchAddress("pr_px", &pid.pr_px, &b_pr_px);
   fChain->SetBranchAddress("pr_py", &pid.pr_py, &b_pr_py);
   fChain->SetBranchAddress("pr_pz", &pid.pr_pz, &b_pr_pz);
   fChain->SetBranchAddress("pr_E", &pid.pr_E, &b_pr_E);
   fChain->SetBranchAddress("pr_vertex", &pid.pr_vertex, &b_pr_vertex);
   fChain->SetBranchAddress("pr_DCsect", &pid.pr_DCsect, &b_pr_DCsect);
   fChain->SetBranchAddress("pr_thetadc", &pid.pr_thetadc, &b_pr_thetadc);
   fChain->SetBranchAddress("pr_phidc", &pid.pr_phidc, &b_pr_phidc);
   fChain->SetBranchAddress("pr_nphe", &pid.pr_nphe, &b_pr_nphe);


   fChain->SetBranchAddress("photonTopology", &pid.photonTopology, &b_photonTopology);
   fChain->SetBranchAddress("ph_px", &pid.ph_px, &b_ph_px);
   fChain->SetBranchAddress("ph_py", &pid.ph_py, &b_ph_py);
   fChain->SetBranchAddress("ph_pz", &pid.ph_pz, &b_ph_pz);
   fChain->SetBranchAddress("ph_E", &pid.ph_E, &b_ph_E);

   fChain->SetBranchAddress("qq", &pid.qq, &b_qq);
   fChain->SetBranchAddress("xb", &pid.xb, &b_xb);
   fChain->SetBranchAddress("t_", &pid.t_, &b_t_);
   fChain->SetBranchAddress("w_", &pid.w_, &b_w_);
   fChain->SetBranchAddress("tp_", &pid.tp_, &b_tp_);
   fChain->SetBranchAddress("MM", &pid.MM, &b_MM);
   fChain->SetBranchAddress("MM2epg", &pid.MM2epg, &b_MM2epg);
   fChain->SetBranchAddress("eps", &pid.eps, &b_eps);
   fChain->SetBranchAddress("deltatheta", &pid.deltatheta, &b_deltatheta);
   fChain->SetBranchAddress("delta_phi", &pid.delta_phi, &b_delta_phi);
   fChain->SetBranchAddress("phi_", &pid.phi_, &b_phi_);
   fChain->SetBranchAddress("Dephi", &pid.Dephi, &b_Dephi);
   fChain->SetBranchAddress("perpx", &pid.perpx, &b_perpx);
   fChain->SetBranchAddress("perpy", &pid.perpy, &b_perpy);
   fChain->SetBranchAddress("pPerp", &pid.pPerp, &b_pPerp);


}

void LoadPID::MakeChain( const char *tempdirname, Int_t filestoadd ){

  //Loadh22 setbranches;
  //setbranches.Init();

  Int_t filecounter = 0;
  const char *ext = ".root";
  TSystemDirectory dir(tempdirname, tempdirname);
  TList *files = dir.GetListOfFiles();
  if (files){
    TSystemFile *file;
    TString filename;
    TIter next(files);
      while((file=(TSystemFile*)next()) && (filecounter < filestoadd)){
  	filename = file->GetName();
	TString filetochain = (std::string)tempdirname + filename;
  	if( !file->IsDirectory() && filename.EndsWith(ext) ){
  	  std::cout << " >> Attaching file " << filename << " to fChain " << std::endl;
  	  fChain->Add(filetochain);
  	  filecounter++;
  	}
      }
  }
  std::cout << " fChain successfully created " << std::endl;
}

void LoadPID::MakeChain( TChain *tempChain ){

  fChain = tempChain;
  

}

Int_t LoadPID::RunNum(TString tempfilename){

  const char *ext = ".root";
  //TString fname = fChain->GetFile()->GetName();
  
  if ( tempfilename.EndsWith(ext) ) {
    std::cout << tempfilename.Data() << std::endl;
    TRegexp runpattern("[0-9][0-9][0-9][0-9][0-9]");
    TString runstring = tempfilename(runpattern);
    runnumber = atoi(runstring);
  }
  return runnumber;
}

void LoadPID::AddBranch( TTree *temptree ){

  b_runnum = temptree->Branch("runnum",&runnum,"runnum/I");
  //Make more general later
  //Pass in ttree, branchname, and value;
}

void LoadPID::FillNewBranch( Int_t tempvalue ){

  runnum = tempvalue;
  // b_runnum->Fill();  
}

