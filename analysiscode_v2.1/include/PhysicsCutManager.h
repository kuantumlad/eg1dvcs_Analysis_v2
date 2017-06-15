#ifndef physicscutmanager_h
#define physicscutmanager_h

#include "PhysicsEventBuilder.h"
#include "PhysicsEvent.h"
#include "PhysicsCuts.h"
#include "Calculator.h"
#include "EventPID.h"

#include "TString.h"
#include "TMath.h"

class PhysicsCutManager {

 public:
  PhysicsCutManager();
  PhysicsCutManager( Calculator );
  ~PhysicsCutManager();

  Eventh22 tempevent;
  //  PhysicsEvent temppevent;
  
  TString elastic;
  TString inelastic;
  TString s_dvcs;
  TString s_dis;
  TString tempreaction;
  std::vector<PhysicsCuts*> appliedexclusivitycuts;
  std::vector<PhysicsCuts*> applieddiscuts;
  void ExclusivityCut();
  void DISCut();
  void InitializeCutsFor(TString);
  bool PassCut( TString, EventPID );
  bool PassRoutine( std::vector<PhysicsCuts*>, EventPID );
  std::vector< bool > PassRoutineVector( std::vector<PhysicsCuts*>, EventPID );
  std::vector< bool > PassCutVector( TString,  EventPID );
 
  bool result;
  bool status;

 public:
  MissingMassCut *missingmasscut1;
  MissingMassCut2 *missingmasscut2;
  WLorentzVectorCut *wcut;
  BjorkenXCut *xcut;
  TransverseMomentumCut *transversecut;
  QsquaredCut *qqcut;
  PhotonEnergy *photonenergy;
  CoplanarityAngleCut *deltaphicut;
  MissingTransverseMntm *transversemntmcut;
  //  CalcMeasPhotonAngle *deltathetacut;
  CalcMeasPhotonAngle *angleXgcut;
  
};

#endif
