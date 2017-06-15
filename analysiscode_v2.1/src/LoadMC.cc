#define loadmc_h
#include "../include/LoadMC.h"
#include "../include/EventMC.h"

#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TRegexp.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TSystemFile.h"

#include <iostream>

LoadMC::LoadMC(){
  fChain = new TChain("h22");
}

LoadMC::~LoadMC(){

  fChain->Delete();
}

void LoadMC::Init(){
  
   fChain->SetBranchAddress("evntid", &mc_event.evntid, &b_evntid);
   fChain->SetBranchAddress("ihel", &mc_event.ihel, &b_ihel);
   fChain->SetBranchAddress("gpart", &mc_event.gpart, &b_gpart);
   fChain->SetBranchAddress("q", mc_event.q, &b_q);
   fChain->SetBranchAddress("p", mc_event.p, &b_p);
   fChain->SetBranchAddress("b", mc_event.b, &b_b);
   fChain->SetBranchAddress("cx", mc_event.cx, &b_cx);
   fChain->SetBranchAddress("cy", mc_event.cy, &b_cy);
   fChain->SetBranchAddress("vz", mc_event.vz, &b_vz);
   fChain->SetBranchAddress("dc_sect", mc_event.dc_sect, &b_dc_sect);
   fChain->SetBranchAddress("tl1_cx", mc_event.tl1_cx, &b_tl1_cx);
   fChain->SetBranchAddress("tl1_cy", mc_event.tl1_cy, &b_tl1_cy);
   fChain->SetBranchAddress("ec_sect", mc_event.ec_sect, &b_ec_sect);
   fChain->SetBranchAddress("ec_r", mc_event.ec_r, &b_ec_r);
   fChain->SetBranchAddress("ec_t", mc_event.ec_t, &b_ec_t);
   fChain->SetBranchAddress("ec_ei", mc_event.ec_ei, &b_ec_ei);
   fChain->SetBranchAddress("ec_eo", mc_event.ec_eo, &b_ec_eo);
   fChain->SetBranchAddress("etot", mc_event.etot, &b_etot);
   fChain->SetBranchAddress("cc_sect", mc_event.cc_sect, &b_cc_sect);
   fChain->SetBranchAddress("cc_r", mc_event.cc_r, &b_cc_r);
   fChain->SetBranchAddress("cc_t", mc_event.cc_t, &b_cc_t);
   fChain->SetBranchAddress("nphe", mc_event.nphe, &b_nphe);
   fChain->SetBranchAddress("cc_c2", mc_event.cc_c2, &b_cc_c2);
   fChain->SetBranchAddress("sc_sect", mc_event.sc_sect, &b_sc_sect);
   fChain->SetBranchAddress("sc_r", mc_event.sc_r, &b_sc_r);
   fChain->SetBranchAddress("sc_t", mc_event.sc_t, &b_sc_t);
   fChain->SetBranchAddress("edep", mc_event.edep, &b_edep);
   fChain->SetBranchAddress("sc_pd", mc_event.sc_pd, &b_sc_pd);
   fChain->SetBranchAddress("cc_pmt", mc_event.cc_pmt, &b_cc_pmt);
   fChain->SetBranchAddress("ech_x", mc_event.ech_x, &b_ech_x);
   fChain->SetBranchAddress("ech_y", mc_event.ech_y, &b_ech_y);
   fChain->SetBranchAddress("ech_z", mc_event.ech_z, &b_ech_z);
   fChain->SetBranchAddress("tl1_x", mc_event.tl1_x, &b_tl1_x);
   fChain->SetBranchAddress("tl1_y", mc_event.tl1_y, &b_tl1_y);
   fChain->SetBranchAddress("tl1_z", mc_event.tl1_z, &b_tl1_z);
   fChain->SetBranchAddress("tl3_x", mc_event.tl3_x, &b_tl3_x);
   fChain->SetBranchAddress("tl3_y", mc_event.tl3_y, &b_tl3_y);
   fChain->SetBranchAddress("tl3_z", mc_event.tl3_z, &b_tl3_z);
   fChain->SetBranchAddress("tl3_cx", mc_event.tl3_cx, &b_tl3_cx);
   fChain->SetBranchAddress("tl3_cy", mc_event.tl3_cy, &b_tl3_cy);
   fChain->SetBranchAddress("tl3_cz", mc_event.tl3_cz, &b_tl3_cz);
   fChain->SetBranchAddress("id", mc_event.id, &b_id);
   fChain->SetBranchAddress("vx", mc_event.vx, &b_vx);
   fChain->SetBranchAddress("vy", mc_event.vy, &b_vy);
   fChain->SetBranchAddress("svicpart", &mc_event.svicpart, &b_svicpart);
   fChain->SetBranchAddress("xc", mc_event.xc, &b_xc);
   fChain->SetBranchAddress("yc", mc_event.yc, &b_yc);
   fChain->SetBranchAddress("etc", mc_event.etc, &b_etc);
   fChain->SetBranchAddress("ecc", mc_event.ecc, &b_ecc);
   fChain->SetBranchAddress("tc", mc_event.tc, &b_tc);
   fChain->SetBranchAddress("nblk", mc_event.nblk, &b_nblk);
   fChain->SetBranchAddress("ich_x", mc_event.ich_x, &b_ich_x);
   fChain->SetBranchAddress("ich_y", mc_event.ich_y, &b_ich_y);
   fChain->SetBranchAddress("et", mc_event.et, &b_et);
   fChain->SetBranchAddress("egl", mc_event.egl, &b_egl);
   fChain->SetBranchAddress("ich_xgl", mc_event.ich_xgl, &b_ich_xgl);
   fChain->SetBranchAddress("ich_ygl", mc_event.ich_ygl, &b_ich_ygl);
   fChain->SetBranchAddress("nprt", &mc_event.nprt, &b_nprt);
   fChain->SetBranchAddress("pidpart", mc_event.pidpart, &b_pidpart);
   fChain->SetBranchAddress("xpart", mc_event.xpart, &b_xpart);
   fChain->SetBranchAddress("ypart", mc_event.ypart, &b_ypart);
   fChain->SetBranchAddress("zpart", mc_event.zpart, &b_zpart);
   fChain->SetBranchAddress("epart", mc_event.epart, &b_epart);
   fChain->SetBranchAddress("pxpart", mc_event.pxpart, &b_pxpart);
   fChain->SetBranchAddress("pypart", mc_event.pypart, &b_pypart);
   fChain->SetBranchAddress("pzpart", mc_event.pzpart, &b_pzpart);
   fChain->SetBranchAddress("qpart", mc_event.qpart, &b_qpart);
   fChain->SetBranchAddress("Ipart10", mc_event.Ipart10, &b_Ipart10);
   fChain->SetBranchAddress("Rpart11", mc_event.Rpart11, &b_Rpart11);
   fChain->SetBranchAddress("Rpart12", mc_event.Rpart12, &b_Rpart12);
   fChain->SetBranchAddress("Ipart13", mc_event.Ipart13, &b_Ipart13);
   fChain->SetBranchAddress("mcnentr", &mc_event.mcnentr, &b_mcnentr);
   fChain->SetBranchAddress("mcnpart", &mc_event.mcnpart, &b_mcnpart);
   fChain->SetBranchAddress("mcevnt", &mc_event.mcevnt, &b_mcevnt);
   fChain->SetBranchAddress("mcst", mc_event.mcst, &b_mcst);
   fChain->SetBranchAddress("mcid", mc_event.mcid, &b_mcid);
   fChain->SetBranchAddress("mcpid", mc_event.mcpid, &b_mcpid);
   fChain->SetBranchAddress("mctheta", mc_event.mctheta, &b_mctheta);
   fChain->SetBranchAddress("mcphi", mc_event.mcphi, &b_mcphi);
   fChain->SetBranchAddress("mcp", mc_event.mcp, &b_mcp);
   fChain->SetBranchAddress("mcm", mc_event.mcm, &b_mcm);
   fChain->SetBranchAddress("mcvx", mc_event.mcvx, &b_mcvx);
   fChain->SetBranchAddress("mcvy", mc_event.mcvy, &b_mcvy);
   fChain->SetBranchAddress("mcvz", mc_event.mcvz, &b_mcvz);
}


void LoadMC::MakeChain( const char *tempdirname, Int_t filestoadd ){

  //LoadMC setbranches;
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

void LoadMC::MakeChain( TChain *tempChain ){

  fChain = tempChain;
  
}

Int_t LoadMC::MCRunNum(TString tempfilename){

  const char *ext = ".root";
  //TString fname = fChain->GetFile()->GetName();
  
  if ( tempfilename.EndsWith(ext) ) {
    std::cout << tempfilename.Data() << std::endl;
    TRegexp runpattern("[0-9][0-9][0-9][0-9]");
    TString runstring = tempfilename(runpattern);
    runnumber = atoi(runstring);
  }
  return runnumber;
}

void LoadMC::AddBranch( TTree *temptree ){

  //b_runnum = temptree->Branch("runnum",&runnum,"runnum/I");
  //Make more general later
  //Pass in ttree, branchname, and value;
}

void LoadMC::FillNewBranch( Int_t tempvalue ){

  //runnum = tempvalue;
  // b_runnum->Fill();  
}

