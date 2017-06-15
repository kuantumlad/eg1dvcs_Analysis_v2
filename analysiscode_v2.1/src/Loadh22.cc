#define loadh22_cxx
#include "../include/Loadh22.h"
#include "../include/Eventh22.h"

#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TRegexp.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TSystemFile.h"

#include <iostream>

Loadh22::Loadh22(){

  fChain = new TChain("h22");
  runnumber = 0;

}

Loadh22::~Loadh22(){
  
   fChain->Delete();
  
}

void Loadh22::Init(Int_t mctoggle){
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   
   fChain->SetBranchAddress("evntid", &event.evntid, &b_evntid);
   fChain->SetBranchAddress("ihel", &event.ihel, &b_ihel);
   fChain->SetBranchAddress("gpart", &event.gpart, &b_gpart);
   fChain->SetBranchAddress("q", event.q, &b_q);
   fChain->SetBranchAddress("p", event.p, &b_p);
   fChain->SetBranchAddress("b", event.b, &b_b);
   fChain->SetBranchAddress("cx", event.cx, &b_cx);
   fChain->SetBranchAddress("cy", event.cy, &b_cy);
   fChain->SetBranchAddress("vz", event.vz, &b_vz);
   fChain->SetBranchAddress("dc_sect", event.dc_sect, &b_dc_sect);
   fChain->SetBranchAddress("tl1_cx", event.tl1_cx, &b_tl1_cx);
   fChain->SetBranchAddress("tl1_cy", event.tl1_cy, &b_tl1_cy);
   fChain->SetBranchAddress("ec_sect", event.ec_sect, &b_ec_sect);
   fChain->SetBranchAddress("ec_r", event.ec_r, &b_ec_r);
   fChain->SetBranchAddress("ec_t", event.ec_t, &b_ec_t);
   fChain->SetBranchAddress("ec_ei", event.ec_ei, &b_ec_ei);
   fChain->SetBranchAddress("ec_eo", event.ec_eo, &b_ec_eo);
   fChain->SetBranchAddress("etot", event.etot, &b_etot);
   fChain->SetBranchAddress("cc_sect", event.cc_sect, &b_cc_sect);
   fChain->SetBranchAddress("cc_r", event.cc_r, &b_cc_r);
   fChain->SetBranchAddress("cc_t", event.cc_t, &b_cc_t);
   fChain->SetBranchAddress("nphe", event.nphe, &b_nphe);
   fChain->SetBranchAddress("cc_c2", event.cc_c2, &b_cc_c2);
   fChain->SetBranchAddress("sc_sect", event.sc_sect, &b_sc_sect);
   fChain->SetBranchAddress("sc_r", event.sc_r, &b_sc_r);
   fChain->SetBranchAddress("sc_t", event.sc_t, &b_sc_t);
   fChain->SetBranchAddress("edep", event.edep, &b_edep);
   fChain->SetBranchAddress("sc_pd", event.sc_pd, &b_sc_pd);
   fChain->SetBranchAddress("cc_pmt", event.cc_pmt, &b_cc_pmt);
   fChain->SetBranchAddress("ech_x", event.ech_x, &b_ech_x);
   fChain->SetBranchAddress("ech_y", event.ech_y, &b_ech_y);
   fChain->SetBranchAddress("ech_z", event.ech_z, &b_ech_z);
   fChain->SetBranchAddress("tl1_x", event.tl1_x, &b_tl1_x);
   fChain->SetBranchAddress("tl1_y", event.tl1_y, &b_tl1_y);
   fChain->SetBranchAddress("tl1_z", event.tl1_z, &b_tl1_z);
   fChain->SetBranchAddress("tl3_x", event.tl3_x, &b_tl3_x);
   fChain->SetBranchAddress("tl3_y", event.tl3_y, &b_tl3_y);
   fChain->SetBranchAddress("tl3_z", event.tl3_z, &b_tl3_z);
   fChain->SetBranchAddress("tl3_cx", event.tl3_cx, &b_tl3_cx);
   fChain->SetBranchAddress("tl3_cy", event.tl3_cy, &b_tl3_cy);
   fChain->SetBranchAddress("tl3_cz", event.tl3_cz, &b_tl3_cz);
   fChain->SetBranchAddress("id", event.id, &b_id);
   fChain->SetBranchAddress("vx", event.vx, &b_vx);
   fChain->SetBranchAddress("vy", event.vy, &b_vy);
   fChain->SetBranchAddress("svicpart", &event.svicpart, &b_svicpart);
   fChain->SetBranchAddress("xc", event.xc, &b_xc);
   fChain->SetBranchAddress("yc", event.yc, &b_yc);
   fChain->SetBranchAddress("etc", event.etc, &b_etc);
   fChain->SetBranchAddress("ecc", event.ecc, &b_ecc);
   fChain->SetBranchAddress("tc", event.tc, &b_tc);
   fChain->SetBranchAddress("nblk", event.nblk, &b_nblk);
   fChain->SetBranchAddress("ich_x", event.ich_x, &b_ich_x);
   fChain->SetBranchAddress("ich_y", event.ich_y, &b_ich_y);
   fChain->SetBranchAddress("et", event.et, &b_et);
   fChain->SetBranchAddress("egl", event.egl, &b_egl);
   fChain->SetBranchAddress("ich_xgl", event.ich_xgl, &b_ich_xgl);
   fChain->SetBranchAddress("ich_ygl", event.ich_ygl, &b_ich_ygl);
   if( mctoggle != -1 ){
   fChain->SetBranchAddress("rastr1", &event.rastr1, &b_rastr1);
   fChain->SetBranchAddress("rastr2", &event.rastr2, &b_rastr2);
   }
   ///////////////////////////////////////////                                                                                                                                                            
   //                                                                                                                                                                                                     
   //  Below are the tree variables that                                                                                                                                                                 
   //  are found in the Monte Carlo ntuple                                                                                                                                                              
   //  Added on 2-21-2017                                                                                                                                                                                  
   //                                                                                                                                                                                                     
   /////////////////////////////////////////// 
   if( mctoggle == -1 ){
   fChain->SetBranchAddress("nprt", &event.nprt, &b_nprt);
   fChain->SetBranchAddress("pidpart",event.pidpart, &b_pidpart);
   fChain->SetBranchAddress("xpart",event.xpart, &b_xpart);
   fChain->SetBranchAddress("ypart",event.ypart, &b_ypart);
   fChain->SetBranchAddress("zpart",event.zpart, &b_zpart);
   fChain->SetBranchAddress("epart",event.epart, &b_epart);
   fChain->SetBranchAddress("pxpart",event.pxpart, &b_pxpart);
   fChain->SetBranchAddress("pypart",event.pypart, &b_pypart);
   fChain->SetBranchAddress("pzpart",event.pzpart, &b_pzpart);
   fChain->SetBranchAddress("qpart",event.qpart, &b_qpart);
   fChain->SetBranchAddress("Ipart10",event.Ipart10, &b_Ipart10);
   fChain->SetBranchAddress("Rpart11",event.Rpart11, &b_Rpart11);
   fChain->SetBranchAddress("Rpart12",event.Rpart12, &b_Rpart12);
   fChain->SetBranchAddress("Ipart13",event.Ipart13, &b_Ipart13);
   fChain->SetBranchAddress("mcnentr",&event.mcnentr,&b_mcnentr);
   fChain->SetBranchAddress("mcnpart",&event.mcnpart, &b_mcnpart);
   fChain->SetBranchAddress("mcevnt",&event.mcevnt, &b_mcevnt);
   fChain->SetBranchAddress("mcst",event.mcst,&b_mcst);
   fChain->SetBranchAddress("mcid",event.mcid, &b_mcid);
   fChain->SetBranchAddress("mcpid",event.mcpid,&b_mcpid);
   fChain->SetBranchAddress("mctheta",event.mctheta, &b_mctheta);
   fChain->SetBranchAddress("mcphi",event.mcphi, &b_mcphi);
   fChain->SetBranchAddress("mcp",event.mcp,&b_mcp);
   fChain->SetBranchAddress("mcm",event.mcm,&b_mcm);
   fChain->SetBranchAddress("mcvx",event.mcvx, &b_mcvx);
   fChain->SetBranchAddress("mcvy",event.mcvy, &b_mcvy);
   fChain->SetBranchAddress("mcvz",event.mcvz, &b_mcvz);
   }
   
}

void Loadh22::MakeChain( const char *tempdirname, Int_t filestoadd ){

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
  	  //std::cout << " >> Attaching file " << filename << " to fChain " << std::endl;
  	  fChain->Add(filetochain);
  	  filecounter++;
  	}
      }
  }
  // std::cout << " fChain successfully created " << std::endl;
}

void Loadh22::MakeChain( TChain *tempChain ){

  fChain = tempChain;
  

}

Int_t Loadh22::RunNum(TString tempfilename){

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

Int_t Loadh22::MCCheck( TString tempfilename){

  const char *ext = ".root";
  const char *prefix = "dvcs_";
  TRegexp runpattern("[0-9][0-9][0-9][0-9]");
  TString runstring = tempfilename(runpattern);
  runnumber = atoi(runstring);

  if( tempfilename.BeginsWith(prefix) && tempfilename.EndsWith(ext) && runnumber <=2000 ){
    isMC = 1; // true
  }
  else{
    isMC = 0; //false. i.e it is not MC run
  }
  return isMC;
}

void Loadh22::AddBranch( TTree *temptree ){

  b_runnum = temptree->Branch("runnum",&runnum,"runnum/I");
  //Make more general later
  //Pass in ttree, branchname, and value;
}

void Loadh22::FillNewBranch( Int_t tempvalue ){

  runnum = tempvalue;
  // b_runnum->Fill();  
}

