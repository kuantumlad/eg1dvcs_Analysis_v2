#define loaddvcs_cxx
#include "../include/LoadDVCS.h"
#include "../include/EventDVCS.h"

#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TRegexp.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TSystemFile.h"

#include <iostream>

LoadDVCS::LoadDVCS(){

  gChain = new TChain("tDVCS");
  
}

LoadDVCS::~LoadDVCS(){
  gChain->Delete();
}

void LoadDVCS::Init(){

   gChain->SetBranchAddress("RunNumber", &dvcs.RunNumber, &b_RunNumber);
   //gChain->SetBranchAddress("PeriodID", &dvcs.PeriodID, &b_PeriodID );
   //gChain->SetBranchAddress("TargetType", &dvcs.TargetType, &b_TargetType);
   gChain->SetBranchAddress("pol_sign", &dvcs.pol_sign, &b_pol_sign);
   gChain->SetBranchAddress("beampol", &dvcs.beampol, &b_beampol);
   gChain->SetBranchAddress("helicity", &dvcs.helicity, &b_helicity);
   gChain->SetBranchAddress("TarPol", &dvcs.TarPol, &b_TarPol);
   gChain->SetBranchAddress("Q2", &dvcs.Q2, &b_Q2);
   gChain->SetBranchAddress("Xbj", &dvcs.Xbj, &b_Xbj);
   gChain->SetBranchAddress("W", &dvcs.W, &b_W);
   gChain->SetBranchAddress("t_Pr", &dvcs.t_Pr, &b_t_Pr);
   gChain->SetBranchAddress("t_Ph", &dvcs.t_Ph, &b_t_Ph);
   gChain->SetBranchAddress("Phi_Pr", &dvcs.Phi_Pr, &b_Phi_Pr);
   gChain->SetBranchAddress("Phi_Ph", &dvcs.Phi_Ph, &b_Phi_Ph);
   gChain->SetBranchAddress("AngleXg", &dvcs.AngleXg, &b_AngleXg);
   gChain->SetBranchAddress("Anglehg_hp", &dvcs.Anglehg_hp, &b_Anglehg_hp);
   gChain->SetBranchAddress("Xbal", &dvcs.Xbal, &b_Xbal);
   gChain->SetBranchAddress("Ybal", &dvcs.Ybal, &b_Ybal);
   gChain->SetBranchAddress("Zbal", &dvcs.Zbal, &b_Zbal);
   gChain->SetBranchAddress("Ebal", &dvcs.Ebal, &b_Ebal);
   gChain->SetBranchAddress("el_p", &dvcs.el_p, &b_el_p);
   gChain->SetBranchAddress("el_theta", &dvcs.el_theta, &b_el_theta);
   gChain->SetBranchAddress("el_phi", &dvcs.el_phi, &b_el_phi);
   gChain->SetBranchAddress("pr_p", &dvcs.pr_p, &b_pr_p);
   gChain->SetBranchAddress("pr_theta", &dvcs.pr_theta, &b_pr_theta);
   gChain->SetBranchAddress("pr_phi", &dvcs.pr_phi, &b_pr_phi);
   gChain->SetBranchAddress("nphotEC", &dvcs.nphotEC, &b_nphotEC);
   gChain->SetBranchAddress("ph_ec_p", &dvcs.ph_ec_p, &b_ph_ec_p);
   gChain->SetBranchAddress("ph_theta", &dvcs.ph_ec_theta, &b_ph_ec_theta);
   gChain->SetBranchAddress("ph_ec_phi", &dvcs.ph_ec_phi, &b_ph_ec_phi);
   gChain->SetBranchAddress("nphotIC", &dvcs.nphotIC, &b_nphotIC);
   gChain->SetBranchAddress("ph_ic_p", &dvcs.ph_ic_p, &b_ph_ic_p);
   gChain->SetBranchAddress("ph_ic_theta", &dvcs.ph_ic_theta, &b_ph_ic_theta);
   gChain->SetBranchAddress("ph_ic_phi", &dvcs.ph_ic_phi, &b_ph_ic_phi);
   gChain->SetBranchAddress("nphot", &dvcs.nphot, &b_nphot);
   gChain->SetBranchAddress("ph_p", &dvcs.ph_p, &b_ph_p);
   gChain->SetBranchAddress("ph_theta", &dvcs.ph_theta, &b_ph_theta);
   gChain->SetBranchAddress("ph_phi", &dvcs.ph_phi, &b_ph_phi);
   gChain->SetBranchAddress("ph_hitID", &dvcs.ph_hitID, &b_ph_hitID);
   gChain->SetBranchAddress("mm2_epg", &dvcs.mm2_epg, &b_mm2_epg);
   gChain->SetBranchAddress("mm2_ep", &dvcs.mm2_ep, &b_mm2_ep);
   gChain->SetBranchAddress("mm2_eg", &dvcs.mm2_eg, &b_mm2_eg);
   
}


void LoadDVCS::MakeChain( const char *tempdirname, Int_t filestoadd ){

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
  	  gChain->Add(filetochain);
  	  filecounter++;
  	}
      }
  }
  std::cout << " fChain successfully created " << std::endl;
}

void LoadDVCS::MakeChain( TChain *tempChain ){

  gChain = tempChain;
  

}

Int_t LoadDVCS::RunNum(TString tempfilename){

  const char *ext = ".root";
  //TString fname = fChain->GetFile()->GetName();
  
  if ( tempfilename.EndsWith(ext) ) {
    //std::cout << tempfilename.Data() << std::endl;
    TRegexp runpattern("[0-9][0-9][0-9][0-9][0-9]");
    TString runstring = tempfilename(runpattern);
    runnumber = atoi(runstring);
  }
  return runnumber;
}
void LoadDVCS::AddBranch( TTree *temptree ){

  //b_runnum = temptree->Branch("runnum",&runnum,"runnum/I");
  //Make more general later
  //Pass in ttree, branchname, and value;
}

void LoadDVCS::FillNewBranch( Int_t tempvalue ){

  runnum = tempvalue;
  // b_runnum->Fill();  
}


