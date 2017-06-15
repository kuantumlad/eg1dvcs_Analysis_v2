#ifndef histogramtool_h
#define histogramtool_h

#include "Loadh22.h"
#include "Eventh22.h"
#include "Cuts.h"
#include "PhysicsEvent.h"
#include "Calculator.h"

#include "TH1D.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TVector3.h"
#include <THnSparse.h>


class HistogramTool {

 public:

  HistogramTool();
  ~HistogramTool();

 public:
  Eventh22 tempevent;
  Int_t tempgindex;
  ECplaneRotated planes;
  TVector3 UVWplane;
  
  void MakeElectronPlots( Eventh22, Int_t, Calculator );
  void MakeProtonPlots( Eventh22, Int_t, Calculator, Int_t );
  void MakePhotonPlots( Eventh22, Int_t, Calculator );
  void MakeICPhotonPlots( Eventh22, Int_t, Int_t );
  void MakeExclusivityPlots( PhysicsEvent );
  void TestPlots(Int_t);//(Double_t );//(Int_t, Int_t );
  void TestPlot1D( Double_t, Double_t, Double_t, Double_t, Double_t, Double_t );
  void FillPZ( double, double, double, double );
  void DrawHistograms();
  void SavePlots(TString);
  
 public:
  TCanvas *c1;
  TCanvas *c2;
  TCanvas *c3;
  TCanvas *c4;
  TCanvas *c5;
  TCanvas *c6;

 public:
  Calculator calculate;
  CCSCCut chtimediff;

 public:
  TH1D *h_electronmomentum;
  TH1D *h_ecinner;
  TH1D *h_ecouter;
  TH2D *h_ecouterVSinner;
  TH1D *h_nphe;
  TH2D *h_timingcut;
  TH2D *h_ECFiducial;
  TH2D *h_icprojection;
  TH1D *h_electronTheta;
  TH1D *h_electronPhi;
  TH2D *h_electronMntmTheta;
  TH2D *h_electronThetaPhi;
  TH2D *h_electronEtotPvsP;

 public:
  TH2D *betavsmntm;
  TH2D *h22betavsmntm;
  TH2D *h_h22beta;
  TH1D *h_vertexZproton;
  TH2D *h_icprojectionproton;
  TH1D *h_protonMntm;
  TH1D *h_protonTheta;
  TH1D *h_protonPhi;
  TH2D *h_protonMntmTheta;
  TH2D *h_protonThetaPhi;

 public:
  TH1D *h_ecdep;
  TH2D *h_h22betaphoton;
  TH2D *h_ec;
  TH2D *h_icprojectionphoton;
  TH1D *h_photonMntm;
  TH1D *h_photonTheta;
  TH1D *h_photonPhi;
  TH2D *h_photonMntmTheta;
  TH2D *h_photonThetaPhi;

 public:
  TH1D *h_missingmass;
  TH1D *h_missingmass2;
  TH1D *h_phihadron;
  TH1D *h_q2;
  TH1D *h_w;
  TH1D *h_elpx;
  TH1D *h_elpy;
  TH1D *h_elpz;
  TH1D *h_elE;

 public:
  TH1D *h_icenergy;
  TH2D *h_ichitposition;
  TH2D *h_icphoton;
  TH1D *h_ictimeraw;
  TH1D *h_icphotonTheta;
  TH1D *h_icphotonPhi;
  TH2D *h_icphotonThetaPhi;
  TH2D *h_icphotonEtheta;

 public:
  TH1I *h_test1;
  TH1D *h_test1a;
  TH1D *h_pz;
  TH1D *h_epz;
  TH1D *h_ezc;
  TH1D *h_pzc;
  TH1D *h_epzc;
  TH1D *h_vzsum;
  TH2D *h_test2;
  TH1D h_numphotons;
  TH1D *h_pr_pc;
  Double_t numelectronevents, numprotonevents;

  //THnSparse for farm runs
 public:
  /* TFile *h_outfile; */
  /* TDirectory *tofile; */
  /* TDirectory *particledirectory[4]; */
  /* Int_t electronD1; */
  /* Int_t electronD2 ; */
  /* THnSparseD* hns_electron1; // electron1 is for kin and electron2 is for fiducial  */
  /* THnSparseD* hns_electron2; */
  /* THnSparseD* hns_proton; */
  /* THnSparseD* hns_photonIC; */
  /* THnSparseD* hns_photonEC; */

 
  
};

#endif

