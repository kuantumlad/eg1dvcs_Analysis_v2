#ifndef bdvcshistograms_hh
#define bdvcshistograms_hh

#include "Calculator.h"
#include "EventPID.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include <vector>

class BDVCSHistograms{

 public:
  BDVCSHistograms();
  BDVCSHistograms(Int_t);
  BDVCSHistograms(TFile*);
  ~BDVCSHistograms();

  TFile *poutfile;
  Calculator calc;

  void CreateDVCSHistograms( TFile* );
  void AddCorrection( Calculator);
  void ElDVCSHist(Int_t);
  void PrDVCSHist(Int_t);
  void PhDVCSHist(Int_t);
  void DVCSKinHistEC(Int_t );
  void DVCSKinHistIC(Int_t );
  void AsymHistA(Int_t);
  void AsymHistB(Int_t);


 public:
  std::vector<TH1D*> h1_el_px;
  std::vector<TH1D*> h1_el_py;
  std::vector<TH1D*> h1_el_pz;
  std::vector<TH1D*> h1_el_E;
  std::vector<TH1D*> h1_el_p;
  std::vector<TH1D*> h1_el_vertex;
  std::vector<TH1D*> h1_el_dcsect;
  std::vector<TH1D*> h1_el_thetadc;
  std::vector<TH1D*> h1_el_nphe;

  std::vector<TH1D*> h1_pr_px;
  std::vector<TH1D*> h1_pr_py;
  std::vector<TH1D*> h1_pr_pz;
  std::vector<TH1D*> h1_pr_E;
  std::vector<TH1D*> h1_pr_p;
  std::vector<TH1D*> h1_pr_vertex;
  std::vector<TH1D*> h1_pr_dcsect;
  std::vector<TH1D*> h1_pr_thetadc;
  std::vector<TH1D*> h1_pr_nphe;

  std::vector<TH1D*> h1_ph_px;
  std::vector<TH1D*> h1_ph_py;
  std::vector<TH1D*> h1_ph_pz;
  std::vector<TH1D*> h1_ph_E;
  std::vector<TH1D*> h1_ph_p;

  std::vector<TH1D*> h1_qq;
  std::vector<TH1D*> h1_w;
  std::vector<TH1D*> h1_xb;
  std::vector<TH1D*> h1_t;
  std::vector<TH1D*> h1_tp;
  std::vector<TH1D*> h1_MM;
  std::vector<TH1D*> h1_MM2epg;
  std::vector<TH1D*> h1_eps;
  std::vector<TH1D*> h1_deltatheta;
  std::vector<TH1D*> h1_deltaphi;
  std::vector<TH1D*> h1_phi;
  std::vector<TH1D*> h1_Dephi;
  std::vector<TH1D*> h1_perpx;
  std::vector<TH1D*> h1_perpy;
  std::vector<TH1D*> h1_pPerp;

  std::vector<TH1D*> h1_qq_ic;
  std::vector<TH1D*> h1_w_ic;
  std::vector<TH1D*> h1_xb_ic;
  std::vector<TH1D*> h1_t_ic;
  std::vector<TH1D*> h1_tp_ic;
  std::vector<TH1D*> h1_MM_ic;
  std::vector<TH1D*> h1_MM2epg_ic;
  std::vector<TH1D*> h1_eps_ic;
  std::vector<TH1D*> h1_deltatheta_ic;
  std::vector<TH1D*> h1_deltaphi_ic;
  std::vector<TH1D*> h1_phi_ic;
  std::vector<TH1D*> h1_Dephi_ic;
  std::vector<TH1D*> h1_perpx_ic;
  std::vector<TH1D*> h1_perpy_ic;
  std::vector<TH1D*> h1_pPerp_ic;

  std::vector<TH2D*> h2_q2x;
  std::vector<TH2D*> h2_tx;
  std::vector<TH2D*> h2_wx;
  std::vector<TH2D*> h2_wq2;

  std::vector<TH2D*> h2_q2x_ic;
  std::vector<TH2D*> h2_tx_ic;
  std::vector<TH2D*> h2_wx_ic;
  std::vector<TH2D*> h2_wq2_ic;

  std::vector<TH1D*> h1_Aepgyield_pp;
  std::vector<TH1D*> h1_Aepgyield_pn;
  std::vector<TH1D*> h1_Aepgyield_np;
  std::vector<TH1D*> h1_Aepgyield_nn;
  std::vector<TH1D*> h1_Aepgyield_PPPN;
  std::vector<TH1D*> h1_Aepgyield_PPPN_pol;
  std::vector<TH1D*> h1_Aepgyield_NPNN;
  std::vector<TH1D*> h1_Aepgyield_NPNN_pol;
  std::vector<TH1D*> h1_Aasymmetry_Top;
  std::vector<TH1D*> h1_Aasymmetry_Bot;
  std::vector<TH1D*> h1_Atargetasymmetry;

  std::vector<TH1D*> h1_Bepgyield_pp;
  std::vector<TH1D*> h1_Bepgyield_pn;
  std::vector<TH1D*> h1_Bepgyield_np;
  std::vector<TH1D*> h1_Bepgyield_nn;
  std::vector<TH1D*> h1_Bepgyield_PPPN;
  std::vector<TH1D*> h1_Bepgyield_PPPN_pol;
  std::vector<TH1D*> h1_Bepgyield_NPNN;
  std::vector<TH1D*> h1_Bepgyield_NPNN_pol;
  std::vector<TH1D*> h1_Basymmetry_Top;
  std::vector<TH1D*> h1_Basymmetry_Bot;
  std::vector<TH1D*> h1_Btargetasymmetry;

 public:
  Int_t el_bin1;
  Double_t el_minpx;
  Double_t el_maxpx;
  Double_t el_minpy;
  Double_t el_maxpy;
  Double_t el_minpz;
  Double_t el_maxpz;
  Double_t el_minE;
  Double_t el_maxE;
  Double_t el_minp;
  Double_t el_maxp;
  Double_t el_minvz;
  Double_t el_maxvz;
  Double_t el_minthetadc;
  Double_t el_maxthetadc;
  Double_t el_minnphe;
  Double_t el_maxnphe;

  Int_t pr_bin1;
  Double_t pr_minpx;
  Double_t pr_maxpx;
  Double_t pr_minpy;
  Double_t pr_maxpy;
  Double_t pr_minpz;
  Double_t pr_maxpz;
  Double_t pr_minE;
  Double_t pr_maxE;
  Double_t pr_minp;
  Double_t pr_maxp;
  Double_t pr_minvz;
  Double_t pr_maxvz;
  Double_t pr_minthetadc;
  Double_t pr_maxthetadc;
  Double_t pr_minnphe;
  Double_t pr_maxnphe;

  Int_t ph_bin1;
  Double_t ph_minpx;
  Double_t ph_maxpx;
  Double_t ph_minpy;
  Double_t ph_maxpy;
  Double_t ph_minpz;
  Double_t ph_maxpz;
  Double_t ph_minE;
  Double_t ph_maxE;
  Double_t ph_minp;
  Double_t ph_maxp;

  Int_t dvcs_bin1;
  Double_t qq_min;
  Double_t qq_max;
  Double_t xb_min;
  Double_t xb_max;
  Double_t w_min;
  Double_t w_max;
  Double_t t_min;
  Double_t t_max;
  Double_t tp_min;
  Double_t tp_max;
  Double_t MM_min;
  Double_t MM_max;
  Double_t MM2epg_min;
  Double_t MM2epg_max;
  Double_t eps_min;
  Double_t eps_max;
  Double_t deltatheta_min;
  Double_t deltatheta_max;
  Double_t deltaphi_min;
  Double_t deltaphi_max;
  Double_t phi_min;
  Double_t phi_max;
  Double_t Dephi_min;
  Double_t Dephi_max;
  Double_t perpx_min;
  Double_t perpx_max;
  Double_t perpy_min;
  Double_t perpy_max;
  Double_t pPerp_min;
  Double_t pPerp_max;

 Int_t Aasymbin1;
 Double_t Aasy_min;
 Double_t Aasy_max;

 Int_t Basymbin1;
 Double_t Basy_min;
 Double_t Basy_max;

};

#endif






