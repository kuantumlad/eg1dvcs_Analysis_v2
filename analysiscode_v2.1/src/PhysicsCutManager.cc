#define physicscutmanager_cxx

#include "../include/EventPID.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/PhysicsCuts.h"
#include "../include/PhysicsCutManager.h"
#include "../include/PhysicsEvent.h"
#include "../include/Calculator.h"

#include "TLorentzVector.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>
#include <vector>

PhysicsCutManager::PhysicsCutManager(){

  elastic = "electron + proton";
  inelastic = "electron + proton + X";
  s_dvcs = "DVCS";
  s_dis = "DIS";

  //DIS Cuts
  wcut = new WLorentzVectorCut();
  xcut = new BjorkenXCut();
  transversecut = new TransverseMomentumCut();
  qqcut = new QsquaredCut();
  //DVCS Cuts
  missingmasscut1 = new MissingMassCut();
  missingmasscut2 = new MissingMassCut2();
  photonenergy = new PhotonEnergy();
  deltaphicut = new CoplanarityAngleCut();
  transversemntmcut = new MissingTransverseMntm();
  angleXgcut = new CalcMeasPhotonAngle();
}

PhysicsCutManager::PhysicsCutManager(Calculator correctcut){

  elastic = "electron + proton";
  inelastic = "electron + proton + X";
  s_dvcs = "DVCS";
  s_dis = "DIS";

  //DIS Cuts
  wcut = new WLorentzVectorCut();
  xcut = new BjorkenXCut();
  transversecut = new TransverseMomentumCut(correctcut);
  qqcut = new QsquaredCut();
  //DVCS Cuts
  missingmasscut1 = new MissingMassCut(correctcut);
  missingmasscut2 = new MissingMassCut2(correctcut);
  photonenergy = new PhotonEnergy();
  deltaphicut = new CoplanarityAngleCut(correctcut);
  transversemntmcut = new MissingTransverseMntm(correctcut);
  angleXgcut = new CalcMeasPhotonAngle(correctcut);
}

PhysicsCutManager::~PhysicsCutManager(){

}

void PhysicsCutManager::DISCut(){
  
  applieddiscuts.push_back(qqcut);
  applieddiscuts.push_back(wcut);
  applieddiscuts.push_back(photonenergy);  
  //  applieddiscuts.push_back(transversecut);
  applieddiscuts.push_back(deltaphicut);
  applieddiscuts.push_back(missingmasscut2);
  applieddiscuts.push_back(missingmasscut1);
  applieddiscuts.push_back(angleXgcut);
  applieddiscuts.push_back(transversemntmcut);

  //applieddiscuts.push_back(deltaphicut);
  // // //applieddiscuts.push_back(missingmasscut2); // not in the AN
  //applieddiscuts.push_back(angleXgcut);
  //applieddiscuts.push_back(transversemntmcut);

}

void PhysicsCutManager::ExclusivityCut(){

  // appliedexclusivitycuts.push_back(photonenergy);  
  // appliedexclusivitycuts.push_back(deltaphicut);
  // appliedexclusivitycuts.push_back(missingmasscut1);
  // appliedexclusivitycuts.push_back(angleXgcut);
  // appliedexclusivitycuts.push_back(transversemntmcut);
  ////applieddiscuts.push_back(missingmasscut2); // not in the AN
  //appliedexclusivitycuts.push_back(missingmasscut);
  // appliedexclusivitycuts.push_back(deltathetacut); //
  // incorporate dependence on periodID?
  
}

void PhysicsCutManager::InitializeCutsFor(TString tempreaction ){

  if( tempreaction == s_dis ){
    DISCut();
  }
  else if( tempreaction == s_dvcs ){
    ExclusivityCut();
  }
  else if( tempreaction != s_dis ){
    std::cout << " Please enter 'DIS' or 'DVCS' into the InitializeCutsFor method argument" << std::endl;
    exit(0);
  }
}

bool PhysicsCutManager::PassCut( TString tempreaction, EventPID temppevent ){

  status = true;
  
  if( tempreaction == s_dis ){
    status = PassRoutine( applieddiscuts, temppevent );
  }
  if( tempreaction == s_dvcs ){
    status = PassRoutine( appliedexclusivitycuts, temppevent );
  }
  return status;
}

bool PhysicsCutManager::PassRoutine( std::vector<PhysicsCuts*> tempapplied, EventPID temppevent ){ 
  
  result = true;
  std::vector<PhysicsCuts*>::iterator it;
  int cutnum = 0;

  for( it = tempapplied.begin(); it != tempapplied.end(); it++ ){
    bool test =  (*it)->candidate( temppevent );
    cutnum++;
    // std::cout << " >>> Inside PassCut routine  " << test << std::endl;
    if( !(*it)->candidate( temppevent ) ){
      result = false;
      //std::cout << " >> Failing test " << cutnum << std::endl;
      break;
    }
  }
  return result;
}

  



////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////
/////
/////       The functions below were added on 2-15-2017 to check the effect of each cut on total rates
/////       It is possible they are not stable, as I have re-written them based off code from local machine
/////
/////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



std::vector< bool > PhysicsCutManager::PassCutVector( TString tempreaction,  EventPID temppevent ){

  std::vector<bool> statusvector;
  statusvector.clear();
  ///std::cout << " In pass cut vector " << std::endl;  
  if( tempreaction == s_dis ){

    //std::cout << " creating status vector" << std::endl;
    statusvector = PassRoutineVector( applieddiscuts, temppevent );
  }
  else if( tempreaction == s_dvcs ){
    statusvector = PassRoutineVector( appliedexclusivitycuts, temppevent );
  }
  else if (tempreaction != s_dis || tempreaction != s_dvcs ){
    std::cout << " Please enter 'DIS' or 'DVCS' into the InitializeCutsFor method argument" << std::endl;
    exit(0);
  }
  return statusvector;		       
}


std::vector< bool > PhysicsCutManager::PassRoutineVector( std::vector<PhysicsCuts*> tempappliedcuts, EventPID temppevent ){
  
  std::vector<bool> passfailCuts;
  passfailCuts.clear();
  std::vector< PhysicsCuts* >::iterator it;
  for( it = tempappliedcuts.begin(); it != tempappliedcuts.end(); it++ ){
    bool cutresult = (*it)->candidate(temppevent);
    passfailCuts.push_back( cutresult );
  }
  return passfailCuts;
}





