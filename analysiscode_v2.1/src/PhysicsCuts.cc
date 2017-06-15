#define physicscuts_cxx

#include "../include/PhysicsCuts.h"
#include "../include/RunDB.h"
#include "../include/Calculator.h"

#include "TMath.h"
#include "TLorentzVector.h"
#include <cmath>

// Cuts on MM2, W, Q2, E_gamma are DIS cuts.

PhysicsCuts::PhysicsCuts(){

  // min_missingmass = -0.15;
  // max_missingmass = 0.15;

  min_w = 2.0;
  max_w = 7.0;//5.5;

  min_xbj = 0.0;
  max_xbj = 1.1;
  
  min_qq = 1.0;
  max_qq = 7.0;//5.5;

  min_photonenergy = 1.0;

  // min_deltaphi = -20.0;
  // max_deltaphi = 20.0;

  // max_mtranmntm = 2.0;
  
  // max_deltatheta = 20.0;//2.52; // partB 2.38

}

PhysicsCuts::PhysicsCuts(Calculator tempcalc){

  //min_missingmass = -0.15;
  //max_missingmass = 0.15;

   min_w = 2.0;
   max_w = 7.0;//5.5;

  min_xbj = 0.0;
  max_xbj = 1.1;
  
  min_qq = 1.0;
  max_qq = 7.0;//5.5;

  min_photonenergy = 1.0;

  //min_deltaphi = -20.0;
  //max_deltaphi = 20.0;

  // max_mtranmntm = 2.0;
  
  //max_deltatheta = 20.0;//2.52; // partB 2.38
  InitiatePhysRunProperties(tempcalc);

}

PhysicsCuts::~PhysicsCuts(){;}

bool PhysicsCuts::candidate(EventPID event){
  return true;
}

void PhysicsCuts::InitiatePhysRunProperties(Calculator tempcalc){
  this->calculate=tempcalc;
  runnumber = calculate.run;
 
}

/*

Missing Mass Cut

*/

MissingMassCut::MissingMassCut(){
  
}

MissingMassCut::MissingMassCut( Calculator tempcalc ) : PhysicsCuts(tempcalc){

}

MissingMassCut::~MissingMassCut(){

}

bool MissingMassCut::candidate( EventPID event ){
  photontopology = event.photonTopology;
  //std::cout<< photontopology << std::endl;
  //Double_t *dvcsarray_c = calculate.DVCSCutBounds( runnumber, photontopology );
  //std::cout <<  dvcsarray_c[1] << " mm2 " << dvcsarray_c[0] << std::endl;

  Double_t mm2max = 0.3;// dvcsarray_c[0];//0.3;// dvcsarray_c[0];
  Double_t mm2min = 0.0;//dvcsarray_c[1];
  if( event.MM < mm2max ){//&& event.MM > mm2min ){
    //if( fabs( event.mm2ep ) < mm2max ){
    return true;
  }
  return false;
}

// Another missing mass cut but for epg - using to compare with Angela
//
//
//
//
//

MissingMassCut2::MissingMassCut2(){
  
}

MissingMassCut2::MissingMassCut2( Calculator tempcalc ) : PhysicsCuts(tempcalc){

}

MissingMassCut2::~MissingMassCut2(){

}

bool MissingMassCut2::candidate( EventPID event ){
  photontopology = event.photonTopology;
  //Double_t *dvcsarray_c = calculate.DVCSCutBounds( runnumber, photontopology );
  //std::cout <<  dvcsarray_c[1] << " mm2 " << dvcsarray_c[0] << std::endl;

  Double_t mm2max = 0.1;// dvcsarray_c[0];
  Double_t mm2min = 0.0;// dvcsarray_c[1];
  //if( event.mm2ep < mm2max && event.mm2ep > mm2min ){
  if( fabs( event.MM2epg ) < mm2max ){
    return true;
  }
  return false;
}


/* 

W Lorentz Vector

*/

WLorentzVectorCut::WLorentzVectorCut(){

}

WLorentzVectorCut::~WLorentzVectorCut(){

}

bool WLorentzVectorCut::candidate( EventPID event ){

  if( event.w_ > 2 ){// && event.w < max_w ){
    return true;
  }
  return false;
}

/* 

Bjorken cut 

*/

BjorkenXCut::BjorkenXCut(){

}

BjorkenXCut::~BjorkenXCut(){

}

bool BjorkenXCut::candidate( EventPID event ){

  if( min_xbj < event.xb && event.xb < max_xbj ){
    return true;
  }
  return false;
}

/*

Transerve Momentum Cut 

*/


TransverseMomentumCut::TransverseMomentumCut(){

}

TransverseMomentumCut::TransverseMomentumCut( Calculator tempcalc ) : PhysicsCuts(tempcalc){

}

TransverseMomentumCut::~TransverseMomentumCut(){

}

bool TransverseMomentumCut::candidate( EventPID event ){
  if( -event.tp_ < event.qq ){
    return true;
  }
  return false;
}

/* 

Q^2 Cut

*/

QsquaredCut::QsquaredCut(){

}

QsquaredCut::~QsquaredCut(){

}

bool QsquaredCut::candidate( EventPID event ){
  // std::cout << " in qq cut " << event.qq << std::endl;
  if( 1 < event.qq ){ // && event.qq < max_qq ){
    return true;
  }
  return false;
}


PhotonEnergy::PhotonEnergy(){

}

PhotonEnergy::~PhotonEnergy(){

}

bool PhotonEnergy::candidate( EventPID event ){
  
  if( event.ph_E > 1){// min_photonenergy ){
    return true;
  }
  return false;
}


CoplanarityAngleCut::CoplanarityAngleCut(){

}

CoplanarityAngleCut::CoplanarityAngleCut( Calculator tempcalc ) : PhysicsCuts(tempcalc){

}

CoplanarityAngleCut::~CoplanarityAngleCut(){

}

bool CoplanarityAngleCut::candidate( EventPID event ){
  photontopology = event.photonTopology;
  //photontopology = event.photonTopology;
  //Double_t *dvcsarray_c = calculate.DVCSCutBounds( runnumber, photontopology );
  //Double_t deltaphi_max = dvcsarray_c[3];// 2.0;// dvcsarray_c[3];
  //Double_t deltaphi_min = dvcsarray_c[4];//-2.0;//dvcsarray_c[4];
  Double_t deltaphideg = event.Dephi/(3.14159) * 180;//*(180.0/TMath::Pi() );
  if( fabs(event.Dephi)/(3.14159) * 180.0 < 2 ){// deltaphi_max && deltaphideg > deltaphi_min ){
    return true;
  }
  return false;
  
}

MissingTransverseMntm::MissingTransverseMntm(){

}

MissingTransverseMntm::MissingTransverseMntm( Calculator tempcalc ) : PhysicsCuts(tempcalc){

}

MissingTransverseMntm::~MissingTransverseMntm(){

}

bool MissingTransverseMntm::candidate( EventPID event ){
  //photontopology = event.photonTopology;
  //Double_t *dvcsarray_c = calculate.DVCSCutBounds( runnumber, photontopology );
  
  //Double_t pt_max = dvcsarray_c[5];//];0.15;// dvcsarray_c[5];
  Double_t mtranmntm = TMath::Sqrt(event.perpx*event.perpx + event.perpy*event.perpy);
  if( mtranmntm < 0.15 ){
    return true;
  }
  return false;
}

CalcMeasPhotonAngle::CalcMeasPhotonAngle(){

}


CalcMeasPhotonAngle::CalcMeasPhotonAngle( Calculator tempcalc ) : PhysicsCuts(tempcalc){

}

CalcMeasPhotonAngle::~CalcMeasPhotonAngle(){

}

bool CalcMeasPhotonAngle::candidate( EventPID event ){
  //photontopology = event.photonTopology;
  //Double_t *dvcsarray_c = calculate.DVCSCutBounds( runnumber, photontopology );
  //std::cout << event.anglexg << std::endl;
  //Double_t XgAngle_max = dvcsarray_c[2];//1.5;//dvcsarray_c[2];
  if( event.deltatheta/(3.14159) * 180 < 1.5 ){// XgAngle_max ){
    return true;
  }
  return false;
}
