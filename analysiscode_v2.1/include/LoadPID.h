#ifndef LoadPID_h
#define LoadPID_h

#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "TBranch.h"

#include "EventPID.h"

#include <iostream>

class LoadPID{

 public:
  TChain *fChain;

  EventPID pid;
  Int_t runnumber;
  //List of Branches
  
  TBranch *b_run;
  TBranch *b_periodID;
  TBranch *b_beamEnergy;
  TBranch *b_beamHelicity;
  TBranch *b_polsign;
  TBranch *b_targetType;
  TBranch *b_targetPolarization;
  //Double_t targetPos;
  TBranch *b_wpstatus;
  TBranch *b_FC0;
  TBranch *b_FC1;
   
  TBranch *b_el_px;
  TBranch *b_el_py;
  TBranch *b_el_pz;
  TBranch *b_el_E;
  TBranch *b_el_vertex;
  TBranch *b_el_DCsect;
  TBranch *b_el_thetadc;
  TBranch *b_el_phidc;
  TBranch *b_el_nphe;
   
  TBranch *b_pr_px;
  TBranch *b_pr_py;
  TBranch *b_pr_pz;
  TBranch *b_pr_E;
  TBranch *b_pr_vertex;
  TBranch *b_pr_DCsect;
  TBranch *b_pr_thetadc;
  TBranch *b_pr_phidc;
  TBranch *b_pr_nphe;

  TBranch *b_photonTopology; 
  TBranch *b_ph_px;
  TBranch *b_ph_py;
  TBranch *b_ph_pz;
  TBranch *b_ph_E;

  TBranch *b_qq;
  TBranch *b_xb;
  TBranch *b_t_;
  TBranch *b_w_;
  TBranch *b_tp_;
  TBranch *b_MM;
  TBranch *b_MM2epg;
  TBranch *b_eps;
  TBranch *b_deltatheta;
  TBranch *b_delta_phi;
  TBranch *b_phi_;
  TBranch *b_Dephi;
  TBranch *b_perpx;
  TBranch *b_perpy;
  TBranch *b_pPerp;   
   
 public:
   LoadPID();
   ~LoadPID();

 public:
   void Init();
   void MakeChain( const char*, Int_t );
   void MakeChain( TChain* );
   void AddBranch( TTree* );
   void FillNewBranch( Int_t );
   EventPID GetEvent(){ return pid; }
   //Int_t Gpart(){ return event.gpart; }
   //Int_t SPart(){ return event.svicpart; }
   Int_t NumEntries(){ return fChain->GetEntries(); }
   void GetEntry( Int_t ientry ){ fChain->GetEntry(ientry); }
   Int_t RunNum(TString);

 public:
   TBranch *b_runnum;
   Int_t runnum;
   
   
};
#endif
   
   
