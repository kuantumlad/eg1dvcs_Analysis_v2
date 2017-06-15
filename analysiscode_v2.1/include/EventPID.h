#ifndef eventpid_h
#define eventpid_h

/* #include "TTree.h" */
/* #include "TFile.h" */
/* #include "TMath.h" */
/* #include "PhysicsEventBuilder.h" */
/* #include "PhysicsEvent.h" */
/* #include "TLorentzVector.h" */

#include "TROOT.h"
#include "TMath.h"

class EventPID {

 public:
  EventPID();
  ~EventPID();

 public:
  Int_t run;
  TString *periodID;
  Double_t beamEnergy;
  Int_t beamHelicity;
  Int_t polsign;
  TString *targetType;
  Double_t targetPolarization;
  //Double_t targetPos;
  Double_t wpstatus;
  Double_t FC0;
  Double_t FC1;

  Double_t el_px;
  Double_t el_py;
  Double_t el_pz;
  Double_t el_E;
  Double_t el_vertex;
  Int_t el_DCsect;
  Double_t el_thetadc;
  Double_t el_phidc;
  Int_t el_nphe;

  Double_t pr_px;
  Double_t pr_py;
  Double_t pr_pz;
  Double_t pr_E;
  Double_t pr_vertex;
  Int_t pr_DCsect;
  Double_t pr_thetadc;
  Double_t pr_phidc;
  Int_t pr_nphe;

  Int_t photonTopology; //
  Double_t ph_px;
  Double_t ph_py;
  Double_t ph_pz;
  Double_t ph_E;
  
  Double_t qq;
  Double_t xb;
  Double_t w;
  Double_t t_;
  Double_t w_;
  Double_t tp_;
  Double_t MM;
  Double_t MM2epg;
  Double_t eps;
  Double_t deltatheta;
  Double_t delta_phi;
  Double_t phi_;
  Double_t Dephi;
  Double_t perpx;
  Double_t perpy;
  Double_t pPerp;

  /* public: */
  /*  void Init(); */
  /*  void MakeChain( const char*, Int_t ); */
  /*  void MakeChain( TChain* ); */
  /*  void AddBranch( TTree* ); */
  /*  void FillNewBranch( Int_t ); */
  /*  // Eventh22 GetEvent(){ return event; } */
  /*  Int_t Gpart(){ return event.gpart; } */
  /*  Int_t SPart(){ return event.svicpart; } */
  /*  Int_t NumEntries(){ return fChain->GetEntries(); } */
  

 /* public: */
 /*   TBranch *b_runnum; */
 /*   Int_t runnum; */


};

#endif
