#define CutManager_cxx

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/Calculator.h"

#include "TString.h"
#include "TMath.h"

#include <vector>
#include <iostream>

CutManager::CutManager(){
  
  sproton = "proton";
  selectron = "electron";
  sphoton = "ecphoton";
  sicphoton = "icphoton";

  //No tempcorrect here because this will be used for the MC analysis which
  // do not need run dependent corrections

  negchargecut = new NegativeChargeCut();
  poschargecut = new PositiveChargeCut();
  neutchargecut = new NeutralChargeCut();
  momentumcut = new MomentumCut();
  momentumcutproton = new MomentumProtonCut();
  electronpreliminary = new ElectronPreliminaryCut();
  etotvsp = new EnergyMntmCut();
  energydepcut = new EnergyDepCut();
  deltabetacut = new DeltaBetaCut();
  betacut = new BetaCut();
  ecdepinner = new ECDepInner();
  ecinnerghost = new ECDepInnerOther();
  ecdepouter = new ECDepOuter();
  sctimecut = new SCtiming();
  timingcut = new CCSCCut();
  ccc2cut = new CC2Cut();
  zvertex = new ZVertexCut();
  zvertexproton = new ZVertexProtonCut();
  uplanecut = new ECUplaneCut();
  vplanecut = new ECVplaneCut();
  wplanecut = new ECWplaneCut();
  uplanecutphoton = new ECUplaneCutPhoton();//
  vplanecutphoton = new ECVplaneCutPhoton();//
  wplanecutphoton = new ECWplaneCutPhoton();//
  iccut = new ICCut();
  moellerelectroncut = new MoellerElectronCut();
  icshadowcut = new ICShadowCut();
  icshadowcutproton = new ICShadowCutProton();
  icneutralshadowcut  = new ICNeutralShadowCut();
  lowbetacut = new MinBetaCut();
  icenergycut = new ICEnergyCut();
  icnoisecut  = new ICNoiseCut();
  icenergythetacut = new ICEnergyThetaCut();
  nphecut = new NPhotonCut();
};

CutManager::CutManager( Calculator tempcorrect ){
  
  sproton = "proton";
  selectron = "electron";
  sphoton = "ecphoton";
  sicphoton = "icphoton";

  //Manually add 'tempcorrect' to the cuts for run dependent cuts
  negchargecut = new NegativeChargeCut(tempcorrect);
  poschargecut = new PositiveChargeCut(tempcorrect);
  neutchargecut = new NeutralChargeCut(tempcorrect);
  ectimecut = new ECTimeCut(tempcorrect);
  sctimecut0 = new SCTimeCut(tempcorrect);
  ecdcmatchcut = new ECDCMatchCut(tempcorrect);
  ccdcmatchcut = new CCDCMatchCut(tempcorrect);
  momentumcut = new MomentumCut(tempcorrect);
  momentumcutproton = new MomentumProtonCut(tempcorrect);
  electronpreliminary = new ElectronPreliminaryCut(tempcorrect);
  protonpreliminary = new ProtonPreliminaryCut(tempcorrect);
  etotvsp = new EnergyMntmCut(tempcorrect);
  energydepcut = new EnergyDepCut(tempcorrect);
  deltabetacut = new DeltaBetaCut(tempcorrect);//
  betacut = new BetaCut(tempcorrect);//
  ecdepinner = new ECDepInner(tempcorrect);
  ecinnerghost = new ECDepInnerOther(tempcorrect);//
  ecdepouter = new ECDepOuter(tempcorrect);//
  sctimecut = new SCtiming(tempcorrect);//
  timingcut = new CCSCCut(tempcorrect);//
  ccc2cut = new CC2Cut(tempcorrect);//
  zvertex = new ZVertexCut(tempcorrect);
  zvertexproton = new ZVertexProtonCut(tempcorrect);
  uplanecut = new ECUplaneCut(tempcorrect);//
  vplanecut = new ECVplaneCut(tempcorrect);//
  wplanecut = new ECWplaneCut(tempcorrect);//
  uplanecutphoton = new ECUplaneCutPhoton(tempcorrect);//
  vplanecutphoton = new ECVplaneCutPhoton(tempcorrect);//
  wplanecutphoton = new ECWplaneCutPhoton(tempcorrect);//
  iccut = new ICCut(tempcorrect);
  moellerelectroncut = new MoellerElectronCut(tempcorrect);//
  icshadowcut = new ICShadowCut(tempcorrect);
  icshadowcutproton = new ICShadowCutProton(tempcorrect);
  icneutralshadowcut  = new ICNeutralShadowCut(tempcorrect);
  lowbetacut = new MinBetaCut(tempcorrect);//
  icenergycut = new ICEnergyCut(tempcorrect);//
  icnoisecut  = new ICNoiseCut(tempcorrect);
  icenergythetacut = new ICEnergyThetaCut( tempcorrect );
  nphecut = new NPhotonCut(tempcorrect);//
};

void CutManager::ManageIndividualCuts(Calculator tempcorrect){

  icneutralshadowcut = new ICNeutralShadowCut(tempcorrect);

}

void CutManager::InitializeCutsFor(TString tempparticlename){
  if(tempparticlename == selectron){
    ElectronCuts();
  }
  else if(tempparticlename == sproton){
    ProtonCuts();
  }
  else if(tempparticlename == sphoton){
    PhotonCuts();
  }
  else if(tempparticlename == sicphoton){
    ICPhotonCuts();
  }

};

void CutManager::AddCut( std::vector<Cuts*> tempvector, Cuts* newcut ){

  tempvector.push_back(newcut);
  
};

void CutManager::ElectronCuts(){
 
  //Ordered in Angela's way
  //  appliedelectroncuts.push_back(negchargecut);
  appliedelectroncuts.push_back(negchargecut);
  appliedelectroncuts.push_back(sctimecut0);
  appliedelectroncuts.push_back(ectimecut);
  appliedelectroncuts.push_back(ecdcmatchcut);
  appliedelectroncuts.push_back(electronpreliminary);//ccdcmatchcut);
  appliedelectroncuts.push_back(momentumcut);
  appliedelectroncuts.push_back(ecdepinner); 
  appliedelectroncuts.push_back(etotvsp);
  appliedelectroncuts.push_back(zvertex);
  appliedelectroncuts.push_back(ccc2cut);
  //appliedelectroncuts.push_back(ecdepouter); // not in AN, but removes hits with zero energy deposited!
  // not in AN
     appliedelectroncuts.push_back(timingcut); // problem with MC
  //appliedelectroncuts.push_back(nphecut); // not in AN
  appliedelectroncuts.push_back(uplanecut);
  appliedelectroncuts.push_back(wplanecut);
  appliedelectroncuts.push_back(vplanecut);
  appliedelectroncuts.push_back(icshadowcut);  
  ////appliedelectroncuts.push_back(lowbetacut);
  //*/
};

void CutManager::ProtonCuts(){
  
  appliedprotoncuts.push_back(poschargecut);
  appliedprotoncuts.push_back(protonpreliminary);
  // appliedprotoncuts.push_back(momentumcutproton); // not in AN
  appliedprotoncuts.push_back(zvertexproton);
  appliedprotoncuts.push_back(sctimecut);
  appliedprotoncuts.push_back(deltabetacut);
  // // //appliedprotoncuts.push_back(lowbetacut);
  appliedprotoncuts.push_back(icshadowcutproton);
  //*/
};

void CutManager::PhotonCuts(){
  
  appliedphotoncuts.push_back(neutchargecut);
  
  appliedphotoncuts.push_back(betacut);
  appliedphotoncuts.push_back(energydepcut); // needs correction so that etot is etot/0.273 ?
  // appliedphotoncuts.push_back(ecdepouter);// while not in AN or Biselli's analysis it is still useful to get rid of those events
  appliedphotoncuts.push_back(uplanecutphoton);
  appliedphotoncuts.push_back(vplanecutphoton);
  appliedphotoncuts.push_back(wplanecutphoton);
  appliedphotoncuts.push_back(icneutralshadowcut); 
 //appliedphotoncuts.push_back(lowbetacut); 
};

void CutManager::ICPhotonCuts(){
 
  appliedicphotoncuts.push_back(icenergycut);
  appliedicphotoncuts.push_back(iccut);
  appliedicphotoncuts.push_back(moellerelectroncut);
  //appliedicphotoncuts.push_back(lowbetacut);
  //appliedicphotoncuts.push_back(icnoisecut);
  //appliedicphotoncuts.push_back(icenergythetacut);
 
};

bool CutManager::PassCut( TString tempparticle, Eventh22 &tempevent, Int_t tempgindex ){

  status = true;
  
  if( tempparticle == selectron ){
    status = PassRoutine( appliedelectroncuts, tempevent, tempgindex );
  }
  else if( tempparticle == sproton ){
    status = PassRoutine( appliedprotoncuts, tempevent, tempgindex );
  }
  else if( tempparticle == sphoton ){
    status = PassRoutine( appliedphotoncuts, tempevent, tempgindex );
  }
  else if( tempparticle == sicphoton ){
    status = PassRoutine( appliedicphotoncuts, tempevent, tempgindex );
  }
  else{
    std::cout << " >> Please enter either 'electron', 'proton', 'ecphoton', or 'icphoton' into first arguement of PassCut << " << std::endl;
    exit(0);
  }
  return status;
}
  
      
bool CutManager::PassRoutine( std::vector<Cuts*> tempapplied, Eventh22 &tempevent, Int_t tempgindex ){

  result = true;
  std::vector<Cuts*>::iterator it;
  int cutnum = 0;

  for( it = tempapplied.begin(); it != tempapplied.end(); it++ ){
    //cutnum++;
    //std::cout << " >>> Inside PassCut routine  " << std::endl;
    if( !(*it)->candidate( tempevent, tempgindex ) ){
      result = false;
      //std::cout << " >> Failing test " << cutnum << std::endl;
      break;
    }
  }
  return result;
}

void CutManager::SummerizeOut( TString particle ){

  if( particle == "electron" ){
    std::cout << " Summary of Electron Pass Rates " << std::endl;
    Summerize(appliedelectroncuts);
  }
  if( particle == "proton" ){
    std::cout << " Summary of Proton Pass Rates " << std::endl;
    Summerize(appliedprotoncuts);
  }
  if( particle == "ECphoton"){
    std::cout << " Summary of ECphotons Pass Rates " << std::endl;
    Summerize(appliedphotoncuts);
  }
  if( particle == "ICphoton"){
    std::cout << " Summary of ICphotons Pass Rates " << std::endl;
    Summerize(appliedicphotoncuts);
  }
  //else{
  //  std::cout << " Please Enter electron, proton, ECphoton, or ICphoton" << std::endl;
  //  exit(0);
  // }
}

void CutManager::Summerize( std::vector<Cuts*> tempapplied ){
  std::vector<Cuts*>::iterator it;
  for( it = tempapplied.begin(); it != tempapplied.end(); it++ ){
    std::cout << ">>" << (*it)->PassRate() << std::endl;
  }
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////
/////
/////       The functions below were added on 2-15-2017 to check the effect of each cut on total rates
/////       It is possible they are not stable, as I have re-written them based off code from local machine
/////
/////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



std::vector< bool > CutManager::PassCutVector( TString tempparticle, Eventh22 &tempevent, Int_t tempgindex ){

  std::vector<bool> statusvector;
  statusvector.clear();

  if( tempparticle == selectron ){
    statusvector = PassRoutineVector( appliedelectroncuts, tempevent, tempgindex );
  }
  else if( tempparticle == sproton ){
    statusvector = PassRoutineVector( appliedprotoncuts, tempevent, tempgindex );
  }
  else if( tempparticle == sphoton ){
    statusvector = PassRoutineVector( appliedphotoncuts, tempevent, tempgindex );
  }
  else if( tempparticle == sicphoton ){
    statusvector = PassRoutineVector( appliedicphotoncuts, tempevent, tempgindex );
  }
  else{
    std::cout << " Please enter either 'electron', 'proton', 'ecphoton', or 'icphoton', into first arguement of PassCut Routine " << std::endl;
    exit(0);
  }
  return statusvector;		       
}


std::vector< bool > CutManager::PassRoutineVector( std::vector<Cuts*> tempappliedcuts, Eventh22 &tempevent, Int_t tempgindex ){
  
  std::vector<bool> passfailCuts;
  passfailCuts.clear();
  std::vector< Cuts* >::iterator it;
  for( it = tempappliedcuts.begin(); it != tempappliedcuts.end(); it++ ){
    bool cutresult = (*it)->candidate(tempevent, tempgindex);
    passfailCuts.push_back( cutresult );
  }
  return passfailCuts;
}
