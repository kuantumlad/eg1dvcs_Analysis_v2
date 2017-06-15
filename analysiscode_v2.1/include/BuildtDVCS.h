#ifndef buildtdvcs_h
#define buildtdvcs_h

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "PhysicsEventBuilder.h"
#include "PhysicsEvent.h"
#include "TLorentzVector.h"
#include "EventPID.h"

class BuildtDVCS {

 public:
  BuildtDVCS();
  ~BuildtDVCS();

 public:
    TTree *tDVCS;

    Int_t RunNumber;
    TString *PeriodID;
    TString *TargetType;
    Int_t pol_sign;
    Int_t beampol;
    Int_t helicity;
    Double_t b_energy;
    Int_t wp_status;
    Int_t fc0;
    Int_t fc1;
    Float_t TarPol;
    Float_t Q2;
    Float_t Xbj;
    Float_t W;
    Float_t Nu;
    Float_t t_Pr;
    Float_t t_Ph;
    Float_t Delta_phi;
    Float_t Phi_Pr_Asym;
    Float_t Phi;
    Float_t AngleXg;
    //    Float_t Anglehg_hp;
    Float_t Delta_Phi;
    Float_t Xbal;
    Float_t Ybal;
    Float_t Zbal;
    Float_t Ebal;
    Float_t mm2_epg;
    Float_t mm;
  
    Float_t fel_px;
    Float_t fel_py;
    Float_t fel_pz;
    Float_t fel_E;
    Float_t fel_vz;
    Float_t fel_dcsect;
    Float_t fel_thetadc;
    Float_t fel_ecmax;

    Float_t fpr_px;
    Float_t fpr_py;
    Float_t fpr_pz;
    Float_t fpr_E;
    Float_t fpr_vz;
    Float_t fpr_dcsect;
    Float_t fpr_thetadc;
    Float_t fpr_ecmax;

    Float_t fph_px;
    Float_t fph_py;
    Float_t fph_pz;
    Float_t fph_E;
    Int_t fph_ID;
    /*

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
    Float_t ph_E;
    Float_t ph_theta;
    Float_t ph_phi;
    Int_t ph_hitID;
    Float_t calcph_theta;
    Float_t ph_thetadiff;
    */
 public:
    PhysicsEvent pevent;
    void Fill( EventPID );
    void dvcsWrite();
    void InitTree();
    void WriteToTree();
    void PrintTree();
    void GetEntry( Int_t entry ){ tDVCS->GetEntry(entry); }
    Int_t dvcsEntries( ) { return tDVCS->GetEntries();};
    
};


#endif
  
