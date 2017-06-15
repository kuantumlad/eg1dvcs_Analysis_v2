#ifndef cuts_h
#define cuts_h

#include "TVector3.h"

#include "Loadh22.h"
#include "Eventh22.h"
#include "Calculator.h"
#include "Setter.h"

class Cuts{

 public:
  Eventh22 particle;
  Calculator calculate;
  RunDB eg1rundata;
  //Setter getter;// = new Setter; //&getobj;
  // Setter getter;

  Cuts();
  Cuts( Calculator );
  ~Cuts(){;};

 public:
  Int_t qelectron;
  Int_t qproton;
  Int_t qphoton;
  Double_t min_momentum;
  Double_t min_momentumproton;
  Double_t max_etotp, min_etotp;
  Double_t min_edeptot;
  Double_t max_betadiff;
  Double_t min_betacut;
  Double_t max_betacut;
  Double_t min_ecdepinner;
  Double_t min_ecdepinnerghost;
  Double_t min_ecdepouter;
  Double_t min_timecut;
  Double_t max_timecut;
  Double_t max_ccc2;
  Double_t min_zvertex;
  Double_t max_zvertex;
  Double_t zvertexlimit;
  Double_t zvertexlimitproton;
  Double_t max_U; Double_t min_U;
  Double_t max_V; Double_t min_V;
  Double_t max_W; Double_t min_W;
  Double_t min_icenergy;
  Double_t min_icdep;

  public:
  Double_t beamenergy;
  Double_t targetpos;
  Double_t targetpolarization;
  Int_t goodelectronIndex;
  TString targettype;
  Int_t runnumber;
  Double_t vz_corrected;
  Double_t shifttime, offsettiming;
  Double_t ecSF1_corr, ecSF2_corr, ecSF3_corr, ecSF4_corr, ecSF5_corr, ecSF6_corr;
  Int_t waveplatepos, fc0, fc1;
  TString partID; Int_t part;  
  virtual bool candidate(Eventh22 &, Int_t);
  void InitiateRunProperties( Calculator );
  void SetGoodParticleIndex( Calculator );

  Double_t PassRate();
  Int_t npass;
};

//Leaving as an example of how to include corrections to cut class
class NegativeChargeCut : public Cuts{

 public:
  NegativeChargeCut();
  NegativeChargeCut( Calculator tempcalc );
  ~NegativeChargeCut();
  bool candidate( Eventh22 &, Int_t );

};

class PositiveChargeCut : public Cuts{

 public:
  PositiveChargeCut();
  PositiveChargeCut(Calculator tempcalc);
  ~PositiveChargeCut();
  bool candidate( Eventh22 &, Int_t );

};

class NeutralChargeCut : public Cuts{

 public:
  NeutralChargeCut();
  NeutralChargeCut(Calculator tempcalc);
  ~NeutralChargeCut();
  bool candidate( Eventh22 &, Int_t );

};

class ECTimeCut : public Cuts{
 public:
  ECTimeCut();
  ECTimeCut(Calculator tempcalc);
  ~ECTimeCut();
  bool candidate( Eventh22 &, Int_t );
};

class SCTimeCut : public Cuts{
 public:
  SCTimeCut();
  SCTimeCut(Calculator tempcalc);
  ~SCTimeCut();
  bool candidate( Eventh22 &, Int_t );
};

class ECDCMatchCut : public Cuts {
 public:
  ECDCMatchCut();
  ECDCMatchCut(Calculator tempcalc);
  ~ECDCMatchCut();
  bool candidate( Eventh22 &, Int_t );

};

class CCDCMatchCut : public Cuts {
 public:
  CCDCMatchCut();
  CCDCMatchCut(Calculator tempcalc);
  ~CCDCMatchCut();
  bool candidate( Eventh22 &, Int_t );

};


class MomentumCut : public Cuts{

 public:
  MomentumCut();
  MomentumCut(Calculator tempcalc);
  ~MomentumCut();
  bool candidate( Eventh22 &, Int_t );

};

class MomentumProtonCut : public Cuts{

 public:
  MomentumProtonCut();
  MomentumProtonCut(Calculator tempcalc);
  ~MomentumProtonCut();
  bool candidate( Eventh22 &, Int_t );

};

class EnergyMntmCut : public Cuts{
 public:
  EnergyMntmCut();
  EnergyMntmCut(Calculator tempcalc);
  ~EnergyMntmCut();
  bool candidate( Eventh22 &, Int_t );
};

class ElectronPreliminaryCut : public Cuts {
 public:
  ElectronPreliminaryCut();
  ElectronPreliminaryCut(Calculator tempcalc);
  ~ElectronPreliminaryCut();
  bool candidate( Eventh22 &, Int_t );
};

class ProtonPreliminaryCut : public Cuts{
 public:
  ProtonPreliminaryCut();
  ProtonPreliminaryCut(Calculator tempcalc);
  ~ProtonPreliminaryCut();
  bool candidate( Eventh22 &, Int_t );
};


class EnergyDepCut : public Cuts{

 public:
  EnergyDepCut();
  EnergyDepCut( Calculator tempcalc );
  ~EnergyDepCut();
  Double_t ecscalefactor;
  bool candidate( Eventh22 &, Int_t );

};

class DeltaBetaCut : public Cuts{

 public:
  DeltaBetaCut();
  DeltaBetaCut(Calculator tempcalc);
  ~DeltaBetaCut();
  Double_t MinBeta( Eventh22 &, Int_t );
  Double_t MaxBeta( Eventh22 &, Int_t );
  bool candidate( Eventh22 &, Int_t );
  Double_t h22betadiff( Eventh22 &, Int_t );

};

class BetaCut : public Cuts{

 public:
  BetaCut();
  BetaCut(Calculator tempcalc);
  ~BetaCut();
  bool candidate( Eventh22 &, Int_t );

};

class MinBetaCut : public Cuts{

 public:
  MinBetaCut();
  MinBetaCut(Calculator tempcalc);
  ~MinBetaCut();
  bool candidate( Eventh22 &, Int_t );
};

class ECDepInner : public Cuts{

 public:
  ECDepInner();
  ECDepInner( Calculator tempcalc );
  ~ECDepInner();
  bool candidate( Eventh22 &, Int_t );
  Double_t ecscalefactor;

};

class ECDepInnerOther : public Cuts{

 public:
  ECDepInnerOther();
  ECDepInnerOther(Calculator tempcalc);
  ~ECDepInnerOther();
  bool candidate( Eventh22 &, Int_t );

};

class ECDepOuter : public Cuts{

 public:
  ECDepOuter();
  ECDepOuter(Calculator tempcalc);
  ~ECDepOuter();
  bool candidate( Eventh22 &, Int_t );

};

class SCtiming : public Cuts{

 public:
  SCtiming();
  SCtiming(Calculator tempcalc);
  ~SCtiming();
  bool candidate( Eventh22 &, Int_t );

};

class CCSCCut : public Cuts{

 public:
  CCSCCut();
  CCSCCut(Calculator tempcalc);
  ~CCSCCut();
  bool candidate( Eventh22 &, Int_t );
  Double_t ReturnTimeDiff( Eventh22 &, Int_t );

};

class CC2Cut : public Cuts{

 public:
  CC2Cut();
  CC2Cut(Calculator tempcalc);
  ~CC2Cut();
  bool candidate( Eventh22 &, Int_t );
};

class ZVertexCut : public Cuts{

 public:
  ZVertexCut();
  ZVertexCut( Calculator tempcalc );
  ~ZVertexCut();
  bool candidate( Eventh22 &, Int_t );

};

class ZVertexProtonCut : public Cuts{

 public:
  ZVertexProtonCut();
  ZVertexProtonCut( Calculator tempcalc );
  ~ZVertexProtonCut();
  bool candidate( Eventh22 &, Int_t );

};

class ECplaneRotated : public Cuts{
 public:
  ECplaneRotated();
  ECplaneRotated(Calculator tempcalc);
  ~ECplaneRotated();
  TVector3 UVW( Eventh22 &, Int_t );
  TVector3 UVWAngela( Eventh22 &, Int_t );
  TVector3 UVWhallcord( Eventh22 &, Int_t );
};

class ECUplaneCut : public Cuts{

 public:
  ECUplaneCut();
  ECUplaneCut(Calculator tempcalc);
  ~ECUplaneCut();
  bool candidate( Eventh22 &, Int_t );

};
  
class ECVplaneCut : public Cuts{

 public:
  ECVplaneCut();
  ECVplaneCut(Calculator tempcalc);
  ~ECVplaneCut();
  bool candidate( Eventh22 &, Int_t );

};

class ECWplaneCut : public Cuts{

 public:
  ECWplaneCut();
  ECWplaneCut(Calculator tempcalc);
  ~ECWplaneCut();
  bool candidate( Eventh22 &, Int_t );

};

//////////////////////////////////////
class ECUplaneCutPhoton : public Cuts{

 public:
  ECUplaneCutPhoton();
  ECUplaneCutPhoton(Calculator tempcalc);
  ~ECUplaneCutPhoton();
  bool candidate( Eventh22 &, Int_t );

};
  
class ECVplaneCutPhoton : public Cuts{

 public:
  ECVplaneCutPhoton();
  ECVplaneCutPhoton(Calculator tempcalc);
  ~ECVplaneCutPhoton();
  bool candidate( Eventh22 &, Int_t );

};

class ECWplaneCutPhoton : public Cuts{

 public:
  ECWplaneCutPhoton();
  ECWplaneCutPhoton(Calculator tempcalc);
  ~ECWplaneCutPhoton();
  bool candidate( Eventh22 &, Int_t );

};

//////////////////////////////////////

class ICCut : public Cuts {

 public:
  ICCut();
  ICCut( Calculator tempcalc );
  ~ICCut();
  bool candidate( Eventh22 &, Int_t );

};

class MoellerElectronCut : public Cuts{

 public:
  MoellerElectronCut();
  MoellerElectronCut( Calculator );
  ~MoellerElectronCut();
  bool candidate( Eventh22 &, Int_t );
};

class ICEnergyCut : public Cuts{
 public:
  ICEnergyCut();
  ICEnergyCut(Calculator tempcalc);
  ~ICEnergyCut();
  bool candidate( Eventh22 &, Int_t );
};
  

class ICShadowCut : public Cuts{
 public:
  ICShadowCut();
  ICShadowCut( Calculator );
  ~ICShadowCut();
  bool ICOK( float, float, int, int );
  bool Fid_Cut_IC(int , float , float , float, float, float, float, float, int, bool);
  bool NeutralFid_Cut_IC(float, float, float, float, float, float, int, int);
  bool candidate( Eventh22 &, Int_t );
};

class ICShadowCutProton : public Cuts{
 public:
  ICShadowCutProton();
  ICShadowCutProton( Calculator );
  ~ICShadowCutProton();
  bool ICOKproton( float, float, int, int );
  bool Fid_Cut_ICproton(int , float , float , float, float, float, float, float, int, bool);
  bool candidate( Eventh22 &, Int_t );
};

class ICNeutralShadowCut : public Cuts {
 public:
  ICNeutralShadowCut();
  ICNeutralShadowCut( Calculator );
  ~ICNeutralShadowCut();
  Calculator mycalculator;
  bool ICNeutralOK( float, float, int, int );
  // bool Fid_Cut_IC(int , float , float , float, float, float, float, float, int, bool);
  bool NeutralFid_Cut_IC(float, float, float, float, float, float, int, int);
  bool candidate( Eventh22 &, Int_t );
};

class ICNoiseCut : public Cuts{
 public:
  ICNoiseCut();
  ICNoiseCut( Calculator tempcalc);
  ~ICNoiseCut(){ ; };
  bool candidate( Eventh22 &, Int_t );
};

class ICEnergyThetaCut : public Cuts{

 public:
  ICEnergyThetaCut();
  ICEnergyThetaCut( Calculator tempcal );
  ~ICEnergyThetaCut(){;};
  bool candidate( Eventh22 &, Int_t );
  
};

class NPhotonCut : public Cuts{

 public:
  NPhotonCut();
  NPhotonCut(Calculator tempcalc);
  ~NPhotonCut(){;};
  bool candidate( Eventh22 &, Int_t );
  
};

class ICTimingCut : public Cuts{

 public:
  ICTimingCut();
  ICTimingCut( Calculator tempcalc );
  ~ICTimingCut(){;};
  bool candidate( Eventh22 &, Int_t );
  
};

#endif
