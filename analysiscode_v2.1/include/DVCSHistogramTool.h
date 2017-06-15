#ifndef dvcshistogramtool_hh
#define dvcshistogramtool_hh

#include "Loadh22.h"
#include "Eventh22.h"
#include "EventDVCS.h"
#include "Cuts.h"
#include "PhysicsEvent.h"
#include "PhysicsEventBuilder.h"
#include "Calculator.h"

#include "TH1D.h"
#include "TH2F.h"
#include "TH3D.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TVector3.h"

class DVCSHistogramTool{

 public:
  DVCSHistogramTool();
  DVCSHistogramTool( Int_t );
  ~DVCSHistogramTool();
  TFile *top;
  TDirectory *cdtof;
  TDirectory *cdparticle[6];
    
 public:
  PhysicsEvent temppevent;
  PhysicsEventBuilder tempbuild;
  void MakeDVCSElectronPlots( PhysicsEvent, Int_t );
  void MakeDVCSProtonPlots( PhysicsEvent, Int_t );
  //void MakeDVCSPhotonPlots( PhysicsEventBuilder, Int_t );
  void MakeICDVCSPhotonPlots( PhysicsEvent );
  void MakeECDVCSPhotonPlots( PhysicsEvent );
  void MakeDVCSKinematicsPlots( PhysicsEvent, Int_t );
  void TestPlots(Int_t);
  
  void DrawDVCSHistograms();
  void AverageBinTool();
  //void AsymmetryHistograms(PhysicsEventBuilder, Int_t );
  //  void AsymmetryHistograms(EventDVCS, TString, TString );
  void AsymmetryHistograms(PhysicsEvent, TString, TString, TString );
  void DetectorRates( EventDVCS, TString );
 
 public:
  TCanvas *c10;
  TCanvas *c20;
  TCanvas *c30;
  TCanvas *c40;
  TCanvas *c50;
  TCanvas *c60;

 public:
  Calculator calculate;
  
  Double_t APtplus;
  Double_t APtminus; 
  Double_t BPtplus; 
  Double_t BPtminus;
  Double_t Adilution, Bdilution;

 public:
 
  TH1D *h_electronICp;
  TH1D *h_electronICtheta;
  TH1D *h_electronICphi;
  TH1D *h_electronCICp;
  TH1D *h_electronCICtheta;
  TH1D *h_electronCICphi;
  TH2D *h_electronICthetaphi;

  //electron detected with photon found in the ec
  TH1D *h_electronECp;
  TH1D *h_electronECtheta;
  TH1D *h_electronECphi;
  TH1D *h_electronCECp;
  TH1D *h_electronCECtheta;
  TH1D *h_electronCECphi;
  TH2D *h_electronECthetaphi;

  //proton detected with photon found in the ic 
  TH1D *h_protonICp;
  TH1D *h_protonICtheta;
  TH1D *h_protonICphi;
  TH1D *h_protonCICp;
  TH1D *h_protonCICtheta;
  TH1D *h_protonCICphi;
  TH2D *h_protonICthetaphi;

  TH1D *h_protonECp;
  TH1D *h_protonECtheta;
  TH1D *h_protonECphi;
  TH1D *h_protonCECp;
  TH1D *h_protonCECtheta;
  TH1D *h_protonCECphi;
  TH2D *h_protonECthetaphi;

  //Kinematics Variables
 public:
  TH1D *h_q2IC;
  TH1D *h_xbjIC;
  TH1D *h_tprIC;
  TH1D *h_phiprIC;
  TH1D *h_missingmassIC;
  TH1D *h_deltaphiIC;

  TH1D *h_q2EC;
  TH1D *h_xbjEC;
  TH1D *h_tprEC;
  TH1D *h_phiprEC;
  TH1D *h_missingmassEC;
  TH1D *h_deltaphiEC;

  TH2D *h_q2xbjt;
  TH1D *h_phiplanedifference;
  TH1D *h_phi_hadlep;
  TH1D *h_phi_hadVPRP;

  
  TH3D *h_q2xbjtPOS;
  TH3D *h_q2xbjtNEG;
  
  Float_t bin_xbj[5] = { 0.1, 0.2, 0.3, 0.4, 0.55 };
  Float_t bin_tproton[5] = { 0.08, 0.18, 0.3, 0.7, 2.0 };
  Double_t bin_q2[5] = {1.0, 1.9 }; 
  Int_t binNum_xbj; 
  Int_t binNum_tproton;

  TH1D *h_Aepgyieldspp;
  TH1D *h_Aepgyieldspn;
  TH1D *h_Aepgyieldsnp;
  TH1D *h_Aepgyieldsnn;
  TH1D *h_AepgyieldsPPPN;
  TH1D *h_AepgyieldsPPPN_pol;
  TH1D *h_AepgyieldsNPNN;
  TH1D *h_AepgyieldsNPNN_pol;
  TH1D *h_Aasymmetrytop;
  TH1D *h_Aasymmetrybot;
  TH1D *h_Aasymmetry;

  TH1D *h_Bepgyieldspp;
  TH1D *h_Bepgyieldspn;
  TH1D *h_Bepgyieldsnp;
  TH1D *h_Bepgyieldsnn;
  TH1D *h_BepgyieldsPPPN;
  TH1D *h_BepgyieldsPPPN_pol;
  TH1D *h_BepgyieldsNPNN;
  TH1D *h_BepgyieldsNPNN_pol;
  TH1D *h_Basymmetrytop;
  TH1D *h_Basymmetrybot;
  TH1D *h_Basymmetry;

  TH1D *h_leptontheta;
  TH1D *h_leptonphi;
  TH2D *h_leptonthetavsphi;
  TH1D *h_hadrontheta;
  TH1D *h_hadronphi;
  TH2D *h_hadronthetavsphi;

  TH1D *h_ECleptontheta;
  TH1D *h_ECleptonphi;
  TH2D *h_ECleptonthetavsphi;
  TH1D *h_EChadrontheta;
  TH1D *h_EChadronphi;
  TH2D *h_EChadronthetavsphi;

  TH2D *h_hthetavslphi;
  

  void CarveQ2XbjBins();
  TF1 *f_q2xbj;
  
  TH2F *h_xbjtPOS;
  TH2F *h_xbjtBPOS;
  TH2F *h_q2xbjPOS;
  TH1F *h_bin_tPOS;
  TH2D *h_averagebin;
  TH2D *h_averagebinB;  
  TH2D *h_q2xbjaverage;
  Int_t xbjrange1[5] = {1, 23, 45, 67, 100 };
  Int_t tprotonrange1[5] = {0, 5, 11, 32, 100 };
  Double_t asymp[10];

  TH1D *h_ecratesA;
  TH1D *h_icratesA;

  TH1D *h_ecratesB;
  TH1D *h_icratesB;
  
  Int_t Appnp;
};
#endif
