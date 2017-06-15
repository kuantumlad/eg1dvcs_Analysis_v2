#ifndef Loadh22_h
#define Loadh22_h

#include "TROOT.h"
#include "TChain.h"
#include "TString.h"
#include "TFile.h"

#include "Eventh22.h"

#include <iostream>

class Loadh22{

 public:
  TChain *fChain;

  Eventh22 event;
  Int_t runnumber;

   // List of branches
   TBranch        *b_evntid;   //!
   TBranch        *b_ihel;   //!
   TBranch        *b_gpart;   //!
   TBranch        *b_q;   //!
   TBranch        *b_p;   //!
   TBranch        *b_b;   //!
   TBranch        *b_cx;   //!
   TBranch        *b_cy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_dc_sect;   //!
   TBranch        *b_tl1_cx;   //!
   TBranch        *b_tl1_cy;   //!
   TBranch        *b_ec_sect;   //!
   TBranch        *b_ec_r;   //!
   TBranch        *b_ec_t;   //!
   TBranch        *b_ec_ei;   //!
   TBranch        *b_ec_eo;   //!
   TBranch        *b_etot;   //!
   TBranch        *b_cc_sect;   //!
   TBranch        *b_cc_r;   //!
   TBranch        *b_cc_t;   //!
   TBranch        *b_nphe;   //!
   TBranch        *b_cc_c2;   //!
   TBranch        *b_sc_sect;   //!
   TBranch        *b_sc_r;   //!
   TBranch        *b_sc_t;   //!
   TBranch        *b_edep;   //!
   TBranch        *b_sc_pd;   //!
   TBranch        *b_cc_pmt;   //!
   TBranch        *b_ech_x;   //!
   TBranch        *b_ech_y;   //!
   TBranch        *b_ech_z;   //!
   TBranch        *b_tl1_x;   //!
   TBranch        *b_tl1_y;   //!
   TBranch        *b_tl1_z;   //!
   TBranch        *b_tl3_x;   //!
   TBranch        *b_tl3_y;   //!
   TBranch        *b_tl3_z;   //!
   TBranch        *b_tl3_cx;   //!
   TBranch        *b_tl3_cy;   //!
   TBranch        *b_tl3_cz;   //!
   TBranch        *b_id;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_svicpart;   //!
   TBranch        *b_xc;   //!
   TBranch        *b_yc;   //!
   TBranch        *b_etc;   //!
   TBranch        *b_ecc;   //!
   TBranch        *b_tc;   //!
   TBranch        *b_nblk;   //!
   TBranch        *b_ich_x;   //!
   TBranch        *b_ich_y;   //!
   TBranch        *b_et;   //!
   TBranch        *b_egl;   //!
   TBranch        *b_ich_xgl;   //!
   TBranch        *b_ich_ygl;   //!
   TBranch        *b_rastr1;   //!
   TBranch        *b_rastr2;   //!

   TBranch        *b_nprt;   //!
   TBranch        *b_pidpart;   //!
   TBranch        *b_xpart;   //!
   TBranch        *b_ypart;   //!
   TBranch        *b_zpart;   //!
   TBranch        *b_epart;   //!
   TBranch        *b_pxpart;   //!
   TBranch        *b_pypart;   //!
   TBranch        *b_pzpart;   //!
   TBranch        *b_qpart;   //!
   TBranch        *b_Ipart10;   //!
   TBranch        *b_Rpart11;   //!
   TBranch        *b_Rpart12;   //!
   TBranch        *b_Ipart13;   //!
   TBranch        *b_mcnentr;   //!
   TBranch        *b_mcnpart;   //!
   TBranch        *b_mcevnt;   //!
   TBranch        *b_mcst;   //!
   TBranch        *b_mcid;   //!
   TBranch        *b_mcpid;   //!
   TBranch        *b_mctheta;   //!
   TBranch        *b_mcphi;   //!
   TBranch        *b_mcp;   //!
   TBranch        *b_mcm;   //!
   TBranch        *b_mcvx;   //!
   TBranch        *b_mcvy;   //!
   TBranch        *b_mcvz; 

 public:
   Loadh22();
   ~Loadh22();

 public:
   void Init(Int_t);
   void MakeChain( const char*, Int_t );
   void MakeChain( TChain* );
   void AddBranch( TTree* );
   void FillNewBranch( Int_t );
   Eventh22 GetEvent(){ return event; }
   Int_t Gpart(){ return event.gpart; }
   Int_t SPart(){ return event.svicpart; }
   Int_t NumEntries(){ return fChain->GetEntries(); }
   void GetEntry( Int_t ientry ){ fChain->GetEntry(ientry); }
   Int_t RunNum(TString);
   Int_t MCCheck(TString); // same idea as RunNum but will return -1 for any mc file
 public:
   TBranch *b_runnum;
   Int_t runnum;
   Int_t isMC;   
  
   //Call by reference
   Eventh22 refevent;
   Int_t CallByRef( Eventh22 &refevent ){ std::cout << refevent.gpart << std::endl;} 
 
};
#endif
   
   
