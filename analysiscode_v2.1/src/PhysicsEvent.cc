#define physicsevent_cxx

#include "../include/PhysicsEvent.h"
#include "../include/Calculator.h"

PhysicsEvent::PhysicsEvent( ){

  run = 0;
  polsign = 0;
  bpol = 0;
  helic  = -1;
  //periodid = "";
  targettype = "p";
  targetpos = 0.0;
  beamenergy = 0.0;
  waveplatepos = 0;
  fc0 = 0;
  fc1 = 0;
  tpol = 0;
  Q2 = 0.0;
  xB = 0.0;
  T = 0.0;
  Tp = 0.0;
  mm = 0.0;
  protCM.SetPxPyPzE(0,0,0,0);
  epsilon = 0.0;
  deltaTheta = 0.0;
  deltaPhi = 0.0;
  phi = 0.0;
  dephi = 0.0;
  perpX = 0.0;
  perpY = 0.0;
  pPerp = 0.0;

  qq = 0.0; 
  xbj = 0.0;
  w = 0;
  nu = 0.0; 
  t_proton = 0.0;
  t_photon = 0.0;
  phi_pr = 0;
  phi_pr_asym =0.0;
  phi_ph = 0;
  PhiPlaneDifference = 0.0;
  hadron_hadlep_Phi = 0.0;
  hadron_hadVPRP_Phi = 0.0;
  anglexg = 0;
  anglehphg = 0;
  deltaphi = 0.0;
  xbal = 0.0;
  ybal = 0.0;
  zbal = 0.0;
  ebal = 0;
  pel = 0;
  eltheta = 0;
  elphi = 0;
  prp = 0;
  prtheta = 0;
  prphi = 0;
  i_phec = 0;
  i_phic = 0;
  // phecp = 0;
  //phectheta = 0;
  //phecphi = 0;
  //phicp = 0;
  //phictheta = 0;
  //phicphi = 0;
  php = 0.0;
  phE = 0.0;
  phtheta = 0.0;
  phphi = 0.0;
  calcphtheta = 0.0;
  mm2epg = 0;
  mm2ep = 0;
  mm2eg = 0;

  //testing variables
  n_lepton_theta = 0;
  n_lepton_phi = 0;
  n_hadron_theta = 0;
  n_hadron_phi = 0;
  
  beamEnergy = 0.0; 
  finalEnergy = 0.0;
  pTransverse = 0.0;
  targetMass = 0.0;

  protCM.SetPxPyPzE(0,0,0,0);
  detectedElectron.SetPxPyPzE( 0, 0, 0, 0 );
  detectedProton.SetPxPyPzE( 0, 0, 0, 0 );
  detectedPhoton.SetPxPyPzE( 0, 0, 0, 0 );

   
}

PhysicsEvent::~PhysicsEvent(){

}


void PhysicsEvent::ClearKinematics(){

  //run = 0;
  //polsign = 0.0;
  //bpol = 0.0;
  helic  = 0.0;
  // periodid = "";
  // tpol = 0.0;
  Q2 = 0.0;
  xB = 0.0;
  T = 0.0;
  Tp = 0.0;
  mm = 0.0;
  protCM.SetPxPyPzE(0,0,0,0);
  epsilon = 0.0;
  deltaTheta = 0.0;
  deltaPhi = 0.0;
  phi = 0.0;
  dephi = 0.0;
  perpX = 0.0;
  perpY = 0.0;
  pPerp = 0.0;

  qq = 0.0; 
  xbj = 0.0;
  w = 0.0;
  nu = 0.0; 
  t_proton = 0.0;
  t_photon = 0.0;
  phi_pr = 0.0;
  phi_ph = 0.0;
  anglexg = 0.0;
  anglehphg = 0.0;
  deltaphi = 0.0;
  xbal = 0.0;
  ybal = 0.0;
  zbal = 0.0;
  ebal = 0.0;
  pel = 0.0;
  eltheta = 0.0;
  elphi = 0.0;
  prp = 0.0;
  prtheta = 0.0;
  prphi = 0.0;
  //phecp = 0.0;
  //phectheta = 0.0;
  //phecphi = 0.0;
  //phicp = 0.0;
  //phictheta = 0.0;
  //phicphi = 0.0;
  php = 0.0;
  phE = 0.0;
  phtheta = 0.0;
  phphi = 0.0;
  calcphtheta = 0.0;
  phthetadiff = 0.0;
  mm2epg = 0.0;
  mm2ep = 0.0;
  mm2eg = 0.0;
  
  finalEnergy = 0.0;
  pTransverse = 0.0;
  
  detectedElectron.SetPxPyPzE( 0, 0, 0, 0 );
  detectedProton.SetPxPyPzE( 0, 0, 0, 0 );
  detectedPhoton.SetPxPyPzE( 0, 0, 0, 0 );  
}

//void PhysicsEvent::InitiateRunProperties( Calculator tempcalc ){

//  this->calculator = tempcalc;
//  tpol = calculator.targetPolarization;

//}
