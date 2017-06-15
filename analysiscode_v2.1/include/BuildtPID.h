#ifndef buildtpid_h
#define buildtpid_h

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "PhysicsEventBuilder.h"
#include "PhysicsEvent.h"
#include "TLorentzVector.h"

class BuildtPID {

 public:
  BuildtPID();
  ~BuildtPID();

 public:
  TTree *tPID;
  
  Int_t run;
  TString periodID;
  Double_t beamEnergy;
  Int_t beamHelicity;
  Int_t pol_sign;
  TString targetType;
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
  Int_t el_dcsect;
  Double_t el_thetadc;
  Double_t el_phidc;
  Double_t el_ecei;
  Double_t el_eceo;
  Double_t el_ectot;
  Double_t el_ecmax;
  Int_t el_nphe;

  Double_t pr_px;
  Double_t pr_py;
  Double_t pr_pz;
  Double_t pr_E;
  Double_t pr_vertex;
  Int_t pr_dcsect;
  Double_t pr_thetadc;
  Double_t pr_phidc;
  Double_t pr_ecei;
  Double_t pr_eceo;
  Double_t pr_ectot;
  Double_t pr_ecmax;
  Int_t pr_nphe;


  Int_t photonTopology; //
  //Int_t ipart;
  Double_t ph_px;
  Double_t ph_py;
  Double_t ph_pz;
  Double_t ph_E;
  //Int_t epart;
  /* Double_t ecph_px; */
  /* Double_t ecph_py; */
  /* Double_t ecph_pz; */
  /* Double_t ecph_E; */

  Double_t qq;// = 0;
  Double_t xb; // = 0;// tempphysics.xB;
  Double_t t_ ;// =  0;//tempphysics.T;
  Double_t w_; // =  0;//tempphysics.w;
  Double_t tp_; 
  Double_t MM ;  // =  0;//tempphysics.mm;
  Double_t MM2epg;     //=  0;//tempphysics.mm2epg;
  Double_t eps;// = 0;// tempphysics.epislon;
  Double_t deltatheta;// =  0;//tempphysics.deltaTheta;
  Double_t delta_phi;// =  0;//tempphysics.deltaPhi;
  Double_t phi_ ;//=  0;//tempphysics.phi;
  Double_t Dephi;// =  0;//tempphysics.dephi;
  Double_t perpx_;// =  0;//tempphysics.perpX;
  Double_t perpy_ ;//=  0;//tempphysics.perpY;
  Double_t pperp_ ;//= 0;// tempphysics.pPerp;
  
 public:
  void Fill( PhysicsEvent );
  void InitPIDTree();
  void WriteToTree();
  void PrintTree();
  void GetEntry( Int_t entry ){ tPID->GetEntry(entry); }
  Int_t skimEntries( ) { return tPID->GetEntries();};


};

#endif
