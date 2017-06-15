#ifndef LoadDVCS_h
#define LoadDVCS_h

#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TFile.h"

#include "EventDVCS.h"
#include "TBranch.h"

#include <iostream>

class LoadDVCS{

 public:
  TChain *gChain;

  EventDVCS dvcs;
  
  TBranch *b_RunNumber;
  TBranch *b_PeriodID;
  TBranch *b_TargetType;
  TBranch *b_pol_sign;
  TBranch *b_beampol;
  TBranch *b_helicity;
  TBranch *b_TarPol;
  TBranch *b_Q2;
  TBranch *b_Xbj;
  TBranch *b_W;
  TBranch *b_t_Pr;
  TBranch *b_t_Ph;
  TBranch *b_Phi_Pr;
  TBranch *b_Phi_Ph;
  TBranch *b_AngleXg;
  TBranch *b_Anglehg_hp;
  TBranch *b_Xbal;
  TBranch *b_Ybal;
  TBranch *b_Zbal;
  TBranch *b_Ebal;
  TBranch *b_el_p;
  TBranch *b_el_theta;
  TBranch *b_el_phi;
  TBranch *b_pr_p;
  TBranch *b_pr_theta;
  TBranch *b_pr_phi;
  TBranch *b_nphotEC;
  TBranch *b_ph_ec_p;
  TBranch *b_ph_ec_theta;
  TBranch *b_ph_ec_phi;
  TBranch *b_nphotIC;
  TBranch *b_ph_ic_p;
  TBranch *b_ph_ic_theta;
  TBranch *b_ph_ic_phi;
  TBranch *b_ph_det;
  TBranch *b_nphot;
  TBranch *b_ph_p;
  TBranch *b_ph_theta;
  TBranch *b_ph_phi;
  TBranch *b_ph_hitID;
  TBranch *b_mm2_epg;
  TBranch *b_mm2_ep;
  TBranch *b_mm2_eg;

 public:
  LoadDVCS();
  ~LoadDVCS();

 public:
   void Init();
   void MakeChain( const char*, Int_t );
   void MakeChain( TChain* );
   void AddBranch( TTree* );
   void FillNewBranch( Int_t );
   EventDVCS GetEvent(){ return dvcs; }
   Int_t NumEntries(){ return gChain->GetEntries(); }
   void GetEntry( Int_t ientry ){ gChain->GetEntry(ientry); }
   Int_t RunNum(TString);

 public:
   Int_t runnum;
   Int_t runnumber;

};
#endif
