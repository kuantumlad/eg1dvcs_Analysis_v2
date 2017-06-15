#ifndef physicsevent_h
#define physicsevent_h

#include "TLorentzVector.h"
#include "TVector3.h"

class PhysicsEvent{
  
 public:
  PhysicsEvent();
  ~PhysicsEvent();

 public:
  Int_t run;
  Double_t polsign;
  Double_t bpol;
  Double_t helic;
  TString periodid;
  TString targettype;
  Double_t targetpos;
  Double_t beamenergy;
  Int_t waveplatepos;
  Int_t fc0;
  Int_t fc1;
  Double_t tpol;
  Double_t xbj;
  Double_t t_proton;
  Double_t t_photon;
  Double_t phi_pr;
  Double_t phi_pr_asym;
  Double_t phi_ph;
  Double_t PhiPlaneDifference;
  Double_t hadron_hadlep_Phi;
  Double_t hadron_hadVPRP_Phi;
  Double_t anglexg;
  Double_t anglehphg;
  Double_t deltaphi;
  Double_t xbal, ybal, zbal, ebal;
  Double_t pel;
  Double_t eltheta;
  Double_t elphi;
  Double_t el_vertex;
  Double_t el_dcsect;
  Double_t el_thetaDC;
  Double_t el_phiDC;
  Double_t el_eceo;
  Double_t el_ecei;
  Double_t el_ectot;
  Double_t el_ecmax;
  Double_t el_nphe;
  Double_t pr_vertex;
  Double_t pr_dcsect;
  Double_t pr_thetaDC;
  Double_t pr_phiDC;
  Double_t pr_eceo;
  Double_t pr_ecei;
  Double_t pr_ectot;
  Double_t pr_ecmax;
  Double_t pr_nphe;

  Double_t Q2;
  Double_t xB;
  Double_t T;
  Double_t Tp;
  Double_t mm2epg;
  Double_t mm;
  TLorentzVector protCM;
  Double_t epsilon;
  Double_t w;
  Double_t deltaTheta;
  Double_t deltaPhi;
  TVector3 leptonicPlane;
  TVector3 hadronicPlane;
  Double_t phi;
  TVector3 n_pro_vph;
  TVector3 n_pro_ph;
  Double_t dephi;
  Double_t perpX;
  Double_t perpY;
  Double_t pPerp;



  Double_t prp;
  Double_t prtheta;
  Double_t prphi;
  Int_t i_phec;
  TLorentzVector phecLV[10];
  Double_t phecp[10];
  Double_t phectheta[10];
  Double_t phecphi[10];
  Int_t i_phic;
  TLorentzVector phicLV[10];
  Double_t phicp[10];
  Double_t phictheta[10];
  Double_t phicphi[10];
  Double_t php;
  Double_t phE;
  Double_t phtheta;
  Double_t phphi;
  Int_t   phhitid;
  Double_t calcphtheta;
  Double_t phthetadiff;
  Double_t mm2ep;
  Double_t mm2eg;
  Double_t n_lepton_theta;
  Double_t n_lepton_phi;
  Double_t n_hadron_theta;
  Double_t n_hadron_phi;
  
 public:
  Double_t beamEnergy;
  Double_t finalEnergy;
  Double_t nu;
  Double_t qq;
  Double_t phiHadron;
  Double_t phivHadron;
  Double_t phiPhoton;
  Double_t pTransverse;
  Double_t targetMass;
  Double_t missingLVangle_ep;
  Double_t missingLVX_epg, missingLVY_epg, missingLVZ_epg, missingLVE_epg;
  Double_t gamma_photonangle;
 
  //             electronLVi   electronLVf       protonLVi       to get angles theta and phi?              
  TLorentzVector beamElectron, detectedElectron, targetParticle, virtualPhoton, finalState;
  TLorentzVector missingLV, missingLV_e, missingLV_ep, missingLV_eg, missingLV_epg, detectedPhoton, detectedProton;
  TVector3 n_lepton, n_hadron, n_vhadron, beamElectron3, detectedElectron3, targetParticle3, virtualPhoton3, realPhoton3, recoilProton3, hadronPP;
  TLorentzVector el_LV, pr_LV, ph_LV;
  void ClearKinematics();
  TVector3 n_VPRP;
 public:
  bool IChit;
  bool EChit;
  bool ICEChit;  
  
};
#endif
