#ifndef physicscuts_h
#define physicscuts_h

#include "PhysicsEvent.h"
#include "EventPID.h"
#include "Calculator.h"

class PhysicsCuts{

 public:

  Calculator calculate;

  PhysicsCuts();
  PhysicsCuts(Calculator);
  ~PhysicsCuts();
  
  virtual bool candidate(EventPID);
  void InitiatePhysRunProperties( Calculator );

 public:
  //  PhysicsEvent event;
  EventPID event;

 public:
  Double_t min_missingmass;
  Double_t max_missingmass;
  Double_t min_w;
  Double_t max_w;
  Double_t min_xbj;
  Double_t max_xbj;
  Double_t min_t;
  Double_t max_t;
  Double_t min_qq;
  Double_t max_qq;
  Double_t min_photonenergy;

  Double_t min_deltaphi, max_deltaphi;
  Double_t min_mtranmntm, max_mtranmntm;
  Double_t min_deltatheta, max_deltatheta;

  Int_t photonTopology, photontopology;
  Int_t runnumber;

};


class MissingMassCut : public PhysicsCuts{

 public:
  MissingMassCut();
  MissingMassCut(Calculator tempcalc);
  ~MissingMassCut();
  bool candidate( EventPID );

};

class MissingMassCut2 : public PhysicsCuts{
  //added for comparison to angela
 public:
  MissingMassCut2();
  MissingMassCut2(Calculator tempcalc);
  ~MissingMassCut2();
  bool candidate( EventPID );

};

class WLorentzVectorCut : public PhysicsCuts{

 public:
  WLorentzVectorCut();
  ~WLorentzVectorCut();
  bool candidate( EventPID );

};

class BjorkenXCut : public PhysicsCuts{

 public:
  BjorkenXCut();
  ~BjorkenXCut();
  bool candidate( EventPID );

};

class TransverseMomentumCut : public PhysicsCuts{

 public:
  TransverseMomentumCut();
  TransverseMomentumCut(Calculator tempcalc);
  ~TransverseMomentumCut();

  bool candidate( EventPID );

};


class QsquaredCut : public PhysicsCuts{

 public:
  QsquaredCut();
  //  QsquaredCut(Calculator tempcalc);
  ~QsquaredCut();
  bool candidate( EventPID );
  //void ExclusivityCut();
  //bool PassCut( TString, Eventh22, Int_t );
  

};

class PhotonEnergy: public PhysicsCuts{

 public:
  PhotonEnergy();
  ~PhotonEnergy();
  bool candidate( EventPID );
  
};

class CoplanarityAngleCut : public PhysicsCuts{

 public:
  CoplanarityAngleCut();
  CoplanarityAngleCut(Calculator tempcalc);
  ~CoplanarityAngleCut();
  bool candidate( EventPID );
};

class MissingTransverseMntm : public PhysicsCuts{
  public:
  MissingTransverseMntm();
  MissingTransverseMntm(Calculator tempcalc);
 ~MissingTransverseMntm();

 bool candidate(EventPID);
};

class CalcMeasPhotonAngle: public PhysicsCuts{
 public:
  CalcMeasPhotonAngle();
  CalcMeasPhotonAngle(Calculator tempcalc);  
  ~CalcMeasPhotonAngle();

  bool candidate( EventPID );
};
  
#endif
