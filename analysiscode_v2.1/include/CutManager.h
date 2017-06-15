#ifndef cutmanager_h
#define cutmanager_h

#include "Loadh22.h"
#include "Eventh22.h"
#include "Cuts.h"
#include "Calculator.h"

#include "TString.h"

#include <iostream>
#include <vector>
#include <map>

class CutManager : public Cuts{

 public:
  
  CutManager();
  CutManager( Calculator );
  ~CutManager(){;};
  Eventh22 event;
  //Calculator tempcorrect;

 public:
  TString sproton;
  TString selectron;
  TString sphoton;
  TString sicphoton;
  std::vector<Cuts*> appliedelectroncuts;
  std::vector<Cuts*> appliedprotoncuts;
  std::vector<Cuts*> appliedphotoncuts;
  std::vector<Cuts*> appliedicphotoncuts;

  bool result;
  bool status;
  
 public: 
  void AddCut(std::vector<Cuts*>, Cuts*);
  void DeleteCuts();
  void InitializeCutsFor(TString); //Or pass the PID number?
  void ManageIndividualCuts(Calculator);
  bool PassCut( TString, Eventh22 &, Int_t );
  bool PassRoutine( std::vector<Cuts*>, Eventh22 &, Int_t );

  void ElectronCuts();
  void ProtonCuts();
  void PhotonCuts();
  void ICPhotonCuts();
  void Summerize(std::vector<Cuts*>);
  void SummerizeOut(TString);

 public:
  std::vector<bool> PassRoutineVector( std::vector<Cuts*>, Eventh22 &, Int_t );
  std::vector<bool> PassCutVector( TString, Eventh22 &, Int_t );
  
 public:
  NegativeChargeCut *negchargecut;
  PositiveChargeCut *poschargecut;
  NeutralChargeCut *neutchargecut;
  ECTimeCut *ectimecut;
  SCTimeCut *sctimecut0;
  ECDCMatchCut *ecdcmatchcut;
  CCDCMatchCut *ccdcmatchcut;
  MomentumCut *momentumcut;
  MomentumProtonCut *momentumcutproton;
  ElectronPreliminaryCut *electronpreliminary;
  ProtonPreliminaryCut *protonpreliminary;
  EnergyMntmCut *etotvsp;
  EnergyDepCut *energydepcut;
  DeltaBetaCut *deltabetacut;
  BetaCut *betacut;
  MinBetaCut *lowbetacut;
  ECDepInner *ecdepinner;
  ECDepInnerOther *ecinnerghost;
  ECDepOuter *ecdepouter;
  SCtiming *sctimecut;
  CCSCCut *timingcut;
  CC2Cut *ccc2cut;
  ZVertexCut *zvertex;
  ZVertexProtonCut *zvertexproton;
  ECUplaneCut *uplanecut;
  ECVplaneCut *vplanecut;
  ECWplaneCut *wplanecut;
  ECUplaneCutPhoton *uplanecutphoton;
  ECVplaneCutPhoton *vplanecutphoton;
  ECWplaneCutPhoton *wplanecutphoton;
  ICCut *iccut;
  MoellerElectronCut *moellerelectroncut;
  ICShadowCut *icshadowcut;
  ICShadowCutProton *icshadowcutproton;
  ICNeutralShadowCut *icneutralshadowcut;
  ICEnergyCut *icenergycut;
  ICNoiseCut *icnoisecut;
  ICEnergyThetaCut *icenergythetacut;
  NPhotonCut *nphecut;
  
};
#endif
