#ifndef physicseventbuilder_h
#define physicseventbuilder_h

#include "PhysicsEvent.h"
#include "Calculator.h"
#include "BuildtDVCS.h"
#include "Eventh22.h"
#include "EventPID.h"

#include "TLorentzVector.h"
#include "TMath.h"

class PhysicsEventBuilder {

 public:
  PhysicsEventBuilder();
  PhysicsEventBuilder( TLorentzVector, TLorentzVector, Calculator );//Int_t );
  ~PhysicsEventBuilder();

  void InitRunParameters( Calculator );

 public:
  PhysicsEvent physicsEvent;
  // Eventh22 tempevent;
  void setBeamElectron( Int_t );
  void setVectors();
  void setVectors(TLorentzVector electron, TLorentzVector proton);
  void setVectors(TLorentzVector electron, TLorentzVector proton, TLorentzVector photon);
  TLorentzVector setParticleLV(TString, Eventh22, Int_t);
  void setHelicity( Eventh22 );
  void setKinematics();
  void setElectronKinematics(TLorentzVector);
  void setElectronKin(Eventh22, Int_t );
  void setProtonKinematics(TLorentzVector);
  void setProtonKin(Eventh22, Int_t);
  void setPhotonKin(Eventh22);
  void setGoodPhotonKinematics (TLorentzVector, Int_t);
  void setECPhotonKinematics(TLorentzVector, Int_t);  
  void setICPhotonKinematics(TLorentzVector, Int_t);
  TLorentzVector returnPhoton( Int_t, Int_t );
  bool ICPhoton(), ECPhoton(), ICECPhoton();
  Int_t PhotonHitLocation( PhysicsEventBuilder );
    
 public:
  PhysicsEvent getPhysicsEvent(TLorentzVector detectedElectron);
  PhysicsEvent getPhysicsEvent(TLorentzVector, TLorentzVector);
  PhysicsEvent getPhysicsEvent(TLorentzVector, TLorentzVector, TLorentzVector );
  PhysicsEvent getPhysicsEvent(TLorentzVector, TLorentzVector, TLorentzVector, Int_t);
  PhysicsEvent getPhysicsEvent( Eventh22, Int_t, Int_t, Int_t, Int_t );
  PhysicsEvent setPhysicsEvent(Eventh22);

 public:
  Eventh22 tempevent;
  Calculator calc;
  Double_t mass;
  Double_t cmntm; 
  Double_t px, cx;
  Double_t py, cy;
  Double_t pz, cz;
  Double_t p4;
  Double_t vz_crr;
  Int_t currentrun;
  
 public:
  TString selectron;
  TString sproton;
  TString sphoton;
  TString sicphoton;
  Int_t hitloc;

 public:
  Int_t isortEC[10], isortIC[10];
  Int_t GoodECPhotIndex, GoodICPhotIndex;
  
};
#endif
