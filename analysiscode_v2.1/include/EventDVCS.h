#ifndef eventdvcs_h
#define eventdvcs_h

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"

class EventDVCS {

 public:
  EventDVCS();
  ~EventDVCS();

 public:
    Int_t RunNumber;
    TString PeriodID;
    TString TargetType;
    Int_t pol_sign;
    Int_t beampol;
    Int_t helicity;
    Float_t TarPol;
    Float_t Q2;
    Float_t Xbj;
    Float_t W;
    Float_t t_Pr;
    Float_t t_Ph;
    Float_t Phi_Pr;
    Float_t Phi_Ph;
    Float_t AngleXg;
    Float_t Anglehg_hp;
    Float_t Xbal;
    Float_t Ybal;
    Float_t Zbal;
    Float_t Ebal;
    Float_t el_p;
    Double_t el_theta;
    Double_t el_phi;
    Float_t pr_p;
    Float_t pr_theta;
    Float_t pr_phi;
    Int_t nphotEC;
    Float_t ph_ec_p;
    Float_t ph_ec_theta;
    Float_t ph_ec_phi;
    Int_t nphotIC;
    Float_t ph_ic_p;
    Float_t ph_ic_theta;
    Float_t ph_ic_phi;
    Int_t ph_det;
    Float_t nphot;
    Float_t ph_p;
    Float_t ph_theta;
    Float_t ph_phi;
    Int_t ph_hitID;
    Float_t mm2_epg;
    Float_t mm2_ep;
    Float_t mm2_eg;
};
#endif
  
