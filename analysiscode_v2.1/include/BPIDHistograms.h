#ifndef bpidhistograms_h
#define bpidhistograms_h

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/Calculator.h"

#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TImage.h"
#include "TLine.h"
#include "TAttMarker.h"
#include "TColor.h"
#include "TStyle.h"
#include <TGeoPolygon.h>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <THnSparse.h>
#include <vector>

class BPIDHistograms{

 public:
  BPIDHistograms();
  BPIDHistograms(Int_t);
  BPIDHistograms(TFile*);
  ~BPIDHistograms();

  TFile *putoutfile;

  void CreateHistDirectories(TFile*);
  void AddCorrections(Calculator);
  void InitiateALLHistograms();
  void ElectronHist(Eventh22 &, Int_t, Int_t); // event, index, run
  void ProtonHist(Eventh22 &, Int_t, Int_t);
  void ECPhotons(Eventh22 &, Int_t, Int_t);
  void ICPhotons(Eventh22 &, Int_t, Int_t);
  void MiscHistos(Eventh22 &, Int_t, Int_t);
  void ParticleMultiplicity(Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t );
  void GoodParticles( Eventh22 , Int_t, Int_t); 
  void PIDHistWrite();
  void ElCutBasedHist(Int_t);
  void PrCutBasedHist(Int_t);
  void ECPhCutBasedHist(Int_t);
  void ICPhCutBasedHist(Int_t);

 public:
  Eventh22 event;
  Int_t index;
  Int_t cutnumber;
  ECplaneRotated planes;
  TVector3 UVWplane;
  Calculator calculator;

  std::vector<TH1D*> h_el_1d;
  std::vector<TH1D*> h1_el_vertex;
  std::vector<TH1D*> h1_el_cc2;
  std::vector<TH1D*> h1_el_timing;
  std::vector<TH1D*> h1_el_ecdepinner;
  std::vector<TH1D*> h1_el_nphe;
  std::vector<TH1D*> h1_el_ect;
  std::vector<TH1D*> h1_el_sct;
  std::vector<TH1D*> h1_el_eci;
  std::vector<TH2D*> h2_el_etotvsp;
  std::vector<TH2D*> h2_el_etotpvsp;
  std::vector<TH2D*> h2_el_etotvsei;
  std::vector<TH2D*> h2_el_ecEIEO;
  std::vector<TH2D*> h2_el_echit;
  std::vector<TH2D*> h2_el_icshadhit;
  std::vector<TH2D*> h2_el_vertexPhi;
  std::vector<TH2I*> h2_el_ecdcsect;
  std::vector<TH2I*> h2_el_ccdcsect;

  std::vector<TH1D*> h1_pr_p;
  std::vector<TH1D*> h1_pr_vertex;
  std::vector<TH1D*> h1_pr_beta;
  std::vector<TH1D*> h1_pr_sctiming;
  std::vector<TH2D*> h2_pr_deltaTvsp;
  std::vector<TH2D*> h2_pr_deltaBvsp;
  std::vector<TH2D*> h2_pr_bvsp;
  std::vector<TH2D*> h2_pr_echit;
  std::vector<TH2D*> h2_pr_icshadhit;
  std::vector<TH2D*> h2_pr_vertexPhi;

  std::vector<TH1D*> h1_ecph_b;
  std::vector<TH1D*> h1_ecph_edep;
  std::vector<TH2D*> h2_ecph_echit;
  std::vector<TH2D*> h2_ecph_icshadhit;

  std::vector<TH1D*> h1_icph_etc;
  std::vector<TH1D*> h1_icph_lvE;
  std::vector<TH1D*> h1_icph_lvTheta;
  std::vector<TH1D*> h1_icph_lvPhi;
  std::vector<TH2D*> h2_icph_ichit;
  std::vector<TH2D*> h2_icph_moeller;
  std::vector<TH2D*> h2_icph_lvThetaPhi;

  std::vector<TH2D*> h2_q2x;
  std::vector<TH2D*> h2_tx;
  std::vector<TH2D*> h2_wx;
  std::vector<TH2D*> h2_wq2;
 
  std::vector<TH2D*> h2_q2x_ic;
  std::vector<TH2D*> h2_tx_ic;
  std::vector<TH2D*> h2_wx_ic;
  std::vector<TH2D*> h2_wq2_ic;
  
 public:
  Int_t el_bin1;
  Int_t el_bin2;
  Double_t el_maxp;
  Double_t el_minp;
  Double_t el_mineci;
  Double_t el_maxeci;
  Double_t  el_maxeco;
  Double_t  el_mineco;
  Double_t  el_minnphe;
  Double_t  el_maxnphe;
  Double_t  el_maxt;
  Double_t  el_mint;
  Double_t  el_mintheta;
  Double_t  el_maxtheta;
  Double_t  el_minphi;
  Double_t  el_maxphi;
  Double_t  el_mincx;
  Double_t  el_maxcx;
  Double_t  el_mincy;
  Double_t  el_maxcy;
  Double_t  el_minvz;
  Double_t  el_maxvz;
  Double_t  el_minedep;
  Double_t  el_maxedep;
  Double_t  el_mintl1x;
  Double_t  el_maxtl1x;
  Double_t  el_mintl1y;
  Double_t  el_maxtl1y;
  Double_t  el_mincc2;
  Double_t  el_maxcc2;
  Double_t  el_minetot;
  Double_t  el_maxetot;
  Double_t el_minect;
  Double_t el_maxect;
  Double_t el_minsct;
  Double_t el_maxsct;
  Double_t el_minei;
  Double_t el_maxei;
  
  Int_t  pr_bin1;
  Int_t pr_bin2;
  Double_t pr_maxp;
  Double_t  pr_minp;
  Double_t pr_mineci;
  Double_t  pr_maxeci;
  Double_t  pr_maxeco;
  Double_t  pr_mineco;
  Double_t  pr_minnphe;
  Double_t  pr_maxnphe;
  Double_t  pr_maxt;
  Double_t  pr_mint;
  Double_t  pr_mintheta;
  Double_t  pr_maxtheta;
  Double_t  pr_minphi;
  Double_t  pr_maxphi;
  Double_t  pr_mincx;
  Double_t  pr_maxcx;
  Double_t  pr_mincy;
  Double_t  pr_maxcy;
  Double_t  pr_minvz;
  Double_t  pr_maxvz;
  Double_t  pr_minb;
  Double_t  pr_maxb;
  Double_t  pr_minedep;
  Double_t  pr_maxedep;
  Double_t  pr_mintl1x;
  Double_t  pr_maxtl1x;
  Double_t  pr_mintl1y;
  Double_t  pr_maxtl1y;
  Double_t pr_minetot;
  Double_t pr_maxetot;
  
  Int_t ecph_bin1;
  Int_t  ecph_bin2;
  Double_t  ecph_maxp;
  Double_t  ecph_minp;
  Double_t  ecph_mineci;
  Double_t  ecph_maxeci;
  Double_t  ecph_maxeco;
  Double_t  ecph_mineco;
  Double_t  ecph_minnphe;
  Double_t  ecph_maxnphe;
  Double_t  ecph_maxt;
  Double_t  ecph_mint;
  Double_t  ecph_mintheta;
  Double_t  ecph_maxtheta;
  Double_t  ecph_minphi;
  Double_t  ecph_maxphi;
  Double_t  ecph_mincx;
  Double_t  ecph_maxcx;
  Double_t  ecph_mincy;
  Double_t  ecph_maxcy;
  Double_t  ecph_minvz;
  Double_t  ecph_maxvz;
  Double_t  ecph_minb;
  Double_t  ecph_maxb;
  Double_t  ecph_minedep;
  Double_t  ecph_maxedep;
  Double_t ecph_mintl1x;
  Double_t ecph_maxtl1x;
  Double_t ecph_mintl1y;
  Double_t ecph_maxtl1y;
  
  Int_t icph_bin1;  
  Double_t  icph_minxc;
  Double_t  icph_maxxc;
  Double_t  icph_minyc;
  Double_t  icph_maxyc;
  Double_t  icph_minetc;
  Double_t  icph_maxetc;
  Double_t  icph_minecc;
  Double_t  icph_maxecc;
  Double_t  icph_maxet;
  Double_t  icph_minet;
  Double_t  icph_minichx;
  Double_t  icph_maxichx;
  Double_t  icph_minichy;
  Double_t  icph_maxichy;
  Double_t  icph_minichxgl;
  Double_t  icph_maxichxgl;
  Double_t  icph_minichygl;
  Double_t  icph_maxichygl;
  Double_t  icph_mintheta;
  Double_t  icph_maxtheta;
  Double_t  icph_minphi;
  Double_t  icph_maxphi;
  
  Double_t  minrastr1;
  Double_t  maxrastr1;
  Double_t  minrastr2;
  Double_t  maxrastr2;
  
  Double_t  ec_fidmax;
  Double_t  ec_fidmin;
  Double_t  ic_fidmax;
  Double_t  ic_fidmin;

  Double_t  ic_fidshadmax;
  Double_t  ic_fidshadmin;
  
  Double_t  ic_shadmin;
  Double_t  ic_shadmax;
  
  ///////////////////////////////
  //Variables for Corrected plots
  //
  ///////////////////////////////
  
  Double_t  cr_minrastr1;
  Double_t  cr_maxrastr1;
  Double_t  cr_minrastr2;
  Double_t  cr_maxrastr2;
  
  Double_t  cr_el_pmin;
  Double_t  cr_el_pmax;
  
  Double_t  cr_pr_pmin;
  Double_t  cr_pr_pmax;
  
  Double_t  cr_beamxmin;
  Double_t  cr_beamxmax;
  
  Double_t  cr_beamymin;
  Double_t  cr_beamymax;
  
  Double_t SpeedOfLight;
  
  
 public:
  TH1D* h_el_p;
  TH1D* h_el_ptest;
  TH1D* h_el_eci;
  TH1D* h_el_eco;
  TH1D* h_el_nphe;
  TH1D* h_el_time;
  TH1D* h_el_theta;
  TH1D* h_el_phi;
   TH1D* h_el_cx;
   TH1D* h_el_cy;
   TH1D* h_el_vz;
   TH1D* h_el_edep;
   TH1D* h_el_tl1x;
   TH1D* h_el_tl1y;
   TH1D* h_el_vz_corr;
   
   TH1D* h_pr_p;
   TH1D* h_pr_b ;
   TH1D* h_pr_eci;
   TH1D* h_pr_eco;
   TH1D* h_pr_nphe;
   TH1D* h_pr_time;
   TH1D* h_pr_theta;
   TH1D* h_pr_phi;
   TH1D* h_pr_cx;
   TH1D* h_pr_cy;
   TH1D* h_pr_vx;
   TH1D* h_pr_edep;
   TH1D* h_pr_tl1x;
   TH1D* h_pr_tl1y;
   TH1D* h_pr_vz;
   TH1D* h_pr_vz_corr;
   
   TH1D* h_ecph_p;
   TH1D* h_ecph_b;
   TH1D* h_ecph_eci;
   TH1D* h_ecph_eco; 
   TH1D* h_ecph_nphe;
   TH1D* h_ecph_time;
   TH1D* h_ecph_theta;
   TH1D* h_ecph_phi;
   TH1D* h_ecph_cx;
   TH1D* h_ecph_cy; 
   TH1D* h_ecph_vx;
   TH1D* h_ecph_edep;
   TH1D* h_ecph_tl1x;
   TH1D* h_ecph_tl1y;
   TH1D* h_ecph_vz;
   
   TH1D*  h_icph_xc;
   TH1D* h_icph_yc;
   TH1D* h_icph_etc;
   TH1D* h_icph_ecc;
   TH1D* h_icph_et;
   TH1D* h_icph_ichx;
   TH1D* h_icph_ichy;
   TH1D* h_icph_ichxgl;
   TH1D* h_icph_ichygl;
   TH1D* h_icph_theta;
   TH1D* h_icph_phi;

   TH1D* h_partMulti;
   
   ///////////////////////////
   //
   // Below are the TH2D
   // and general variables
   //
   //////////////////////////
   
   TH2D* h_el_ecieco;
   TH2D* h_el_timenphe;
   TH2D* h_el_echit;
   TH2D* h_el_icproj;
   TH2D* h_el_thetaphi;
   TH2D* h_el_vzPhi;
   TH2D* h_el_vzPhi_corr;
   
   TH2D* h_pr_ecieco;
   TH2D* h_pr_icproj;
   TH2D* h_pr_bp; 
   TH2D* h_pr_bp_calc;
   TH2D* h_pr_vzPhi;
   TH2D* h_pr_vzPhi_corr;
   TH2D* h_pr_pb_calc;
   TH2D* h_pr_pdeltaT;
   TH2D* h_pr_pdeltaB;
   TH2D* h_pr_thetaphi;
   
   TH2D* h_ecph_ecieco;
   TH2D* h_ecph_echit;
   TH2D* h_ecph_icproj;
   TH2D* h_ecph_thetaphi;
   TH2D* h_ecph_becmax;
   
   TH2D* h_icph_ichit;
   TH2D* h_icph_etctc;
   
   TH1D* h_rastr1;
   TH1D* h_rastr2;
   TH2D* h_rastr12;
   
   /////////////////////////////
   //
   // Below are corrected histos
   //
   /////////////////////////////
   
   TH1D* h_crrrastr1;
   TH1D* h_crrrastr2;
   TH2D* h_crrrastr12;
   
   TH1D* h_el_crp;
   TH1D* h_pr_crp;
   
};

#endif

