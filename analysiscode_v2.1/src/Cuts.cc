#define Cuts_cxx
#include "../include/Cuts.h"
#include "../include/Eventh22.h"
#include "../include/Loadh22.h"
#include "../include/Calculator.h"
#include "../include/RunDB.h"

#include "TMath.h"
#include "TVector3.h"
#include "TString.h"
#include "TGeoPolygon.h"
#include "TCutG.h"

#include <iostream>

Cuts::Cuts () {

  /*  qelectron = -1; // eg1Cuts.Query("Level1CutParameters","ElectronCharge");
  qproton = 1;// eg1Cuts.Query("Level1CutParameters","ProtonCharge");
  qphoton = 0; //eg1Cuts.Query("Level1CutParameters","PhotonCharge");
  min_momentum = 0.80;// 0.735;//0.62;// eg1Cuts.Query("Level1CutParameters","MomentumCut");
  min_momentumproton = 0;//0.30;
  max_etotp = 0.45; //should be changed to a function of p
  min_etotp = 0.20;
  min_edeptot = 0.25;//0.40;//eg1Cuts.Query("Level1CutParameters","MinEDepTotCut"); changed from 0.25
  max_betadiff = 0.05;//eg1Cuts.Query("Level1CutParameters","BetaDiffCut");
  min_betacut = 0.92;//0.80;//0.95;//eg1Cuts.Query("Level1CutParameters","BetaCut");
  max_betacut = 1.06; //if we have a min beta cut we should also have a max beta cut;
  min_ecdepinner = 0.06;// eg1Cuts.Query("Level1CutParameters","ECEICut");
  min_ecdepinnerghost = 0.0;
  min_ecdepouter = 0.0;//eg1Cuts.Query("Level1CutParameters","ECEOCut");
  min_timecut = -2.0;//-1.2;//-2.0;///1000000000.0;//-1.0/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMin");
  max_timecut = 2.0;///1000000000.0;//1.5/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMax");
  max_ccc2 = 0.10;
  min_zvertex = -71.5;//eg1Cuts.Query("Level1CutParameters","ZVCutMin");
  max_zvertex = -63.5;//eg1Cuts.Query("Level1CutParameters","ZVCutMax");
  zvertexlimit = 3.0;
  zvertexlimitproton = 4.0;
  max_U = 390.0;//400.0;//390.0;//eg1Cuts.Query("Level1CutParameters","UCutMax");
  min_U = 40.0;//eg1Cuts.Query("Level1CutParameters","UCutMin");
  max_V = 360.0;
  min_V = 60.0;//0.0;//60.0;
  max_W = 390.0;
  min_W = 60.0;//0.0;//60.0;
  min_icenergy = 0.40;
  min_icdep = 0.25;//0.40;// 0.15;
  */
}

Cuts::Cuts (Calculator tempcalc) {

  InitiateRunProperties(tempcalc);
  if( runnumber == -1 ){
  qelectron = -1; // eg1Cuts.Query("Level1CutParameters","ElectronCharge");
  qproton = 1;// eg1Cuts.Query("Level1CutParameters","ProtonCharge");
  qphoton = 0; //eg1Cuts.Query("Level1CutParameters","PhotonCharge");
  min_momentum = 0.80;// 0.735;//0.62;// eg1Cuts.Query("Level1CutParameters","MomentumCut");
  min_momentumproton = 0;//0.3;
  max_etotp = 0.45;//0.40; //should be changed to a function of p
  min_etotp = 0.12;//0.20;
  min_edeptot = 0.25;//0.40;//eg1Cuts.Query("Level1CutParameters","MinEDepTotCut"); changed from 0.25
  max_betadiff = 0.05;//eg1Cuts.Query("Level1CutParameters","BetaDiffCut");
  min_betacut = 0.92;//0.80;//0.95;//eg1Cuts.Query("Level1CutParameters","BetaCut");
  max_betacut = 1.06; //if we have a min beta cut we should also have a max beta cut;
  min_ecdepinner = 0.06;// eg1Cuts.Query("Level1CutParameters","ECEICut");
  min_ecdepinnerghost = 0.0;
  min_ecdepouter = 0.0;//eg1Cuts.Query("Level1CutParameters","ECEOCut");
  min_timecut = 3.0;//1000000000.0;//-1.0/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMin");
  max_timecut = 5.5;///1000000000.0;//1.5/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMax");
  //min_timecut = -1.0/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMin");
  //max_timecut = 1.5/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMax");
  max_ccc2 = 0.15;
  min_zvertex = -71.5;//eg1Cuts.Query("Level1CutParameters","ZVCutMin");
  max_zvertex = -63.5;//eg1Cuts.Query("Level1CutParameters","ZVCutMax");
  zvertexlimit = 3.0;
  zvertexlimitproton = 4;
  max_U = 400.0;//390.0;//eg1Cuts.Query("Level1CutParameters","UCutMax");
  min_U = 40.0;//eg1Cuts.Query("Level1CutParameters","UCutMin");
  max_V = 360.0;
  min_V = 0.0;//60.0;
  max_W = 390.0;
  min_W = 0.0;//60.0;
  min_icenergy = 0.40; // was 0.25
  min_icdep = 0.15;//0.25;// 0.40; // changed from 0.15
  }
  else if( runnumber != -1) {
  qelectron = -1; // eg1Cuts.Query("Level1CutParameters","ElectronCharge");
  qproton = 1;// eg1Cuts.Query("Level1CutParameters","ProtonCharge");
  qphoton = 0; //eg1Cuts.Query("Level1CutParameters","PhotonCharge");
  min_momentum = 0.80;// 0.735;//0.62;// eg1Cuts.Query("Level1CutParameters","MomentumCut");
  min_momentumproton = 0;//0.3;
  max_etotp = 0.45;//0.40; //should be changed to a function of p
  min_etotp = 0.12;//0.20;
  min_edeptot = 0.25;//0.40;//eg1Cuts.Query("Level1CutParameters","MinEDepTotCut"); changed from 0.25
  max_betadiff = 0.05;//eg1Cuts.Query("Level1CutParameters","BetaDiffCut");
  min_betacut = 0.92;//0.80;//0.95;//eg1Cuts.Query("Level1CutParameters","BetaCut");
  max_betacut = 1.06; //if we have a min beta cut we should also have a max beta cut;
  min_ecdepinner = 0.06;// eg1Cuts.Query("Level1CutParameters","ECEICut");
  min_ecdepinnerghost = 0.0;
  min_ecdepouter = 0.0;//eg1Cuts.Query("Level1CutParameters","ECEOCut");
  min_timecut = -2.0;///1000000000.0;//-1.0/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMin");
  max_timecut = 2.0;///1000000000.0;//1.5/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMax");
  //min_timecut = -1.0/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMin");
  //max_timecut = 1.5/1000000000.0;//eg1Cuts.Query("Level1CutParameters","TimingCutMax");
  max_ccc2 = 0.15;
  min_zvertex = -71.5;//eg1Cuts.Query("Level1CutParameters","ZVCutMin");
  max_zvertex = -63.5;//eg1Cuts.Query("Level1CutParameters","ZVCutMax");
  zvertexlimit = 3.0;
  zvertexlimitproton = 4.0;
  max_U = 390.0;//eg1Cuts.Query("Level1CutParameters","UCutMax");
  min_U = 40.0;//eg1Cuts.Query("Level1CutParameters","UCutMin");
  max_V = 360.0;
  min_V = 60.0;
  max_W = 390.0;
  min_W = 60.0;
  min_icenergy = 0.40; // was 0.25
  min_icdep = 0.15;//0.25;// 0.40; // changed from 0.15
  }
  npass = 0;
}

bool Cuts::candidate( Eventh22 &candidate, Int_t gindex ){
  return true;
}

Double_t Cuts::PassRate( ){
 return npass;
}
			   

void Cuts::InitiateRunProperties(Calculator tempcalc){
  this->calculate=tempcalc;
  beamenergy = calculate.beamEnergy;
  runnumber = calculate.run;
  targetpos = calculate.targetPos;
  targettype = calculate.targetType;
  shifttime = calculate.shiftTiming_eccut;
  offsettiming = calculate.offsetTiming;
  ecSF1_corr = calculate.ecSF1;
  ecSF2_corr = calculate.ecSF2;
  ecSF3_corr = calculate.ecSF3;
  ecSF4_corr = calculate.ecSF4;
  ecSF5_corr = calculate.ecSF5;
  ecSF6_corr = calculate.ecSF6;
  partID = calculate.periodID;
  if( partID=="A"){ part = 1; }
  else if( partID=="B" ){ part = 2;}
  else if (partID=="C" ){ part = 3; }
  waveplatepos = calculate.waveplatePos;
  fc0  = calculate.fc_0;
  fc1 = calculate.fc_1;
  /*     
  std::cout << " Table or Run Properties " << std::endl;
  std::cout << " benergy " << beamenergy << std::endl;
  std::cout << " tposition " << targetpos << std::endl;
  std::cout << " ttype " << targettype << std::endl;
  std::cout << " shifttime  " << shifttime << std::endl;
  std::cout << " offsettime " << offsettiming << std::endl;
  std::cout << " ecSF1 " << ecSF1_corr << std::endl;
  std::cout << " ecSF2 " << ecSF2_corr << std::endl;
  std::cout << " ecSF3 " << ecSF3_corr << std::endl;
  std::cout << " ecSF4 " << ecSF4_corr << std::endl;
  std::cout << " ecSF5 " << ecSF5_corr << std::endl;
  std::cout << " ecSF6 " << ecSF6_corr << std::endl;
  std::cout << " Wave plate position " << waveplatepos << std::endl;
  std::cout << " Faraday Cup 0 " << fc0 << std::endl;
  std::cout << " Faraday Cup 1 " << fc1 << std::endl;
  */

}

void Cuts::SetGoodParticleIndex(Calculator tempcalc){

  //  this->calculate=tempcalc;
  //  goodelectronIndex = calculate.goodelectronindex;
  
}



/******************************************************************* 


Below are all the cuts that will be used for particle identification


********************************************************************/
// Charge Cuts
NegativeChargeCut::NegativeChargeCut( ){
  std::cout << " default constructor activated " << std::endl;
}

//Example of the incorporating corrections on a per run basis.
NegativeChargeCut::NegativeChargeCut( Calculator tempcalc ) : Cuts(tempcalc){

}

NegativeChargeCut::~NegativeChargeCut(){
  
}

bool NegativeChargeCut::candidate(Eventh22 &particle, Int_t gindex){
  if( particle.q[gindex] == -1 ){
    //npass++;
    return true;
  }
  return false;
}

/*

Positive Charge Cut

*/


PositiveChargeCut::PositiveChargeCut(){
  //What does this do
}

PositiveChargeCut::PositiveChargeCut( Calculator tempcalc ) : Cuts(tempcalc){

}

PositiveChargeCut::~PositiveChargeCut(){
  
}

bool PositiveChargeCut::candidate(Eventh22 &particle, Int_t gindex){
  if( particle.q[gindex] == 1 ){ //changed from > 0
    npass++;
    return true;
  }
  return false;
}

/*

Neutral Charge Cut

*/

NeutralChargeCut::NeutralChargeCut(){
  //What does this do
}

NeutralChargeCut::NeutralChargeCut( Calculator tempcalc ) : Cuts(tempcalc){

}

NeutralChargeCut::~NeutralChargeCut(){
  
}

bool NeutralChargeCut::candidate(Eventh22 &particle, Int_t gindex){
  if( particle.q[gindex] == 0 ){
    npass++;
    return true;
  }
  return false;
}

/*
 
  Momentum Cut

 */

MomentumCut::MomentumCut(){

}

MomentumCut::MomentumCut( Calculator tempcalc ) : Cuts(tempcalc){

}

MomentumCut::~MomentumCut(){

}

bool MomentumCut::candidate(Eventh22 &particle, Int_t gindex){
  
  if( particle.p[gindex] > min_momentum ){
    npass++;
    return true;
  }
  return false;
  
}

MomentumProtonCut::MomentumProtonCut(){

}

MomentumProtonCut::MomentumProtonCut( Calculator tempcalc ) : Cuts(tempcalc){

}

MomentumProtonCut::~MomentumProtonCut(){

}

bool MomentumProtonCut::candidate(Eventh22 &particle, Int_t gindex){

  if( particle.p[gindex] > min_momentumproton ){
    npass++;
    return true;
  }
  return false;
  
}

/*

Preliminary Biselli Electron Cut

*/

ElectronPreliminaryCut::ElectronPreliminaryCut(){

}

ElectronPreliminaryCut::ElectronPreliminaryCut( Calculator tempcalc ) : Cuts( tempcalc ){

}

ElectronPreliminaryCut::~ElectronPreliminaryCut(){

}

bool ElectronPreliminaryCut::candidate(Eventh22 &particle, Int_t gindex){

  if(particle.q[gindex]==-1 && particle.ec_t[gindex] != 0 && particle.sc_t[gindex] != 0 &&
      particle.ec_sect[gindex] == particle.dc_sect[gindex] && 
      particle.dc_sect[gindex] == particle.cc_sect[gindex] ){
    npass++;
    return true;
  }
  return false;
}

ECTimeCut::ECTimeCut(){

}

ECTimeCut::ECTimeCut( Calculator tempcalc ) : Cuts( tempcalc ){

}

ECTimeCut::~ECTimeCut(){

}

bool ECTimeCut::candidate(Eventh22 &particle, Int_t tempgindex ){

  if( particle.ec_t[tempgindex] != 0 ){
    return true;
  }
  return false;
}


SCTimeCut::SCTimeCut(){

}

SCTimeCut::SCTimeCut( Calculator tempcalc ) : Cuts( tempcalc ){

}

SCTimeCut::~SCTimeCut(){

}

bool SCTimeCut::candidate(Eventh22 &particle, Int_t tempgindex ){

  if( particle.sc_t[tempgindex] != 0 ){
    return true;
  }
  return false;
}

ECDCMatchCut::ECDCMatchCut(){

}

ECDCMatchCut::ECDCMatchCut( Calculator tempcalc ) : Cuts( tempcalc ){

}

ECDCMatchCut::~ECDCMatchCut(){

}

bool ECDCMatchCut::candidate( Eventh22 &event, Int_t gindex ){

  if( particle.ec_sect[gindex] == particle.dc_sect[gindex] && particle.dc_sect[gindex] == particle.cc_sect[gindex] ){
    return true;
  }
  return false;
}


CCDCMatchCut::CCDCMatchCut(){

}

CCDCMatchCut::CCDCMatchCut( Calculator tempcalc ) : Cuts( tempcalc ){

}

CCDCMatchCut::~CCDCMatchCut(){

}

bool CCDCMatchCut::candidate( Eventh22 &event, Int_t gindex ){

  if( particle.dc_sect[gindex] == particle.cc_sect[gindex] ){
    return true;
  }
  return false;
}



/* 

Biselli's preliminary proton cuts


*/


ProtonPreliminaryCut::ProtonPreliminaryCut(){

}

ProtonPreliminaryCut::ProtonPreliminaryCut( Calculator tempcalc ) : Cuts ( tempcalc ){

}

ProtonPreliminaryCut::~ProtonPreliminaryCut(){

}

bool ProtonPreliminaryCut::candidate( Eventh22 &particle, Int_t gindex ){

  if (  particle.p[gindex] > 0 ){
    npass++;
    return true;
  }
  return false;
}


/*

Energy Momentum Cut
 
*/

EnergyMntmCut::EnergyMntmCut(){

}

EnergyMntmCut::EnergyMntmCut( Calculator tempcalc ) : Cuts(tempcalc){

}

EnergyMntmCut::~EnergyMntmCut(){

}

bool EnergyMntmCut::candidate( Eventh22 &particle, Int_t gindex ){
  //Int_t isortEC[2];
  Double_t energydep = particle.etot[gindex];
  Double_t energyInOut = particle.ec_ei[gindex] + particle.ec_eo[gindex];
  //Double_t findmaxenergydep[2] = { energydep, energyInOut };
  //TMath::Sort(2,findmaxenergydep,isortEC,true);
  //Int_t GoodEnergyIndex = isortEC[0];
  //std::cout << " etot"  << energydep << std::endl;
  //std::cout << " esum " << energyInOut << std::endl;
  //std::cout << " max energy value is " << findmaxenergydep[GoodEnergyIndex] << std::endl;
  // Double_t maxenergydep = findmaxenergydep[GoodEnergyIndex];
  Double_t maxenergydep = (particle.etot[gindex]>particle.ec_ei[gindex]+particle.ec_eo[gindex]?particle.etot[gindex]:particle.ec_ei[gindex]+particle.ec_eo[gindex]);
  //Double_t maxenergydep = TMath::Max(energydep, energyInOut);
  Double_t mntm = particle.p[gindex];

  // 1-31-2017 changed the p back to p-0.12
  // 3/2/2017 changed to match angela
  if( (maxenergydep/(mntm)) > min_etotp ){//&& (maxenergydep/(mntm - 0.12)) < max_etotp ){ //changed from p - 0.12 to p in denominator    
    npass++;
    return true;
  }
  return false;
}

/* 

Energy Cut (for photons)

*/

EnergyDepCut::EnergyDepCut(){

}

EnergyDepCut::EnergyDepCut( Calculator tempcalc ) : Cuts(tempcalc){
  //std::cout << " using new constructor " << std::endl;

}

EnergyDepCut::~EnergyDepCut(){

}

bool EnergyDepCut::candidate( Eventh22 &particle, Int_t gindex ){
   // 0 -> etot , 1 -> ec_ei, 2 -> ec_eo
  // Double_t *ec_corr = calculate.PhotonCorrectECEnergy( runnumber, particle, gindex );
  // Double_t ecmax = (ec_corr[0]>ec_corr[1]+ec_corr[2]?ec_corr[0]:ec_corr[1]+ec_corr[2]);
  Double_t etot_corr = particle.etot[gindex];
  Double_t ei_corr = particle.ec_ei[gindex];
  Double_t eo_corr = particle.ec_eo[gindex];
  Int_t ecsector = particle.ec_sect[gindex];
  
   if( 0 < ecsector && ecsector < 7 ){
     ecscalefactor = 0.0;
     if( ecsector == 1 ) ecscalefactor = ecSF1_corr;
     if( ecsector == 2 ) ecscalefactor = ecSF2_corr;
     if( ecsector == 3 ) ecscalefactor = ecSF3_corr;
     if( ecsector == 4 ) ecscalefactor = ecSF4_corr;
     if( ecsector == 5 ) ecscalefactor = ecSF5_corr;
     if( ecsector == 6 ) ecscalefactor = ecSF6_corr;
     //  std::cout << " The scalefactor is " << ecscalefactor << std::endl;
   }
   if( 0 < particle.etot[gindex] &&  particle.etot[gindex] < 5 ){
     etot_corr = particle.etot[gindex]*( 0.2765/ecscalefactor );
   }
   if( 0 < particle.ec_ei[gindex] && particle.ec_ei[gindex] < 5 ){
     ei_corr = particle.ec_ei[gindex]*( 0.2765/ecscalefactor );
   }
   if( 0 < particle.ec_eo[gindex] && particle.ec_eo[gindex] < 5 ){
     eo_corr = particle.ec_eo[gindex]*( 0.2765/ecscalefactor );
   }
   Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);
   
   /*if( particle.ec_ei[gindex] != 0 ){ 
     if( ei_corr > 0.06 ){ 
       return true; 
     }
   }
   else if ( particle.ec_ei[gindex] == 0 ){
     if( ecmax - eo_corr > 0.06 ){
       return true;
     }
   }
   */
   Double_t energygamma = ecmax/0.2765;
   if( energygamma > 0.25 ){
     npass++;
     return true;
   }
     //Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);
     //Double_t edeptot = ecmax/0.273; // changed from 0.273 - > changed to 0.25 for the 0.4 cut -
   
     //if( edeptot > min_edeptot ){
     // return true;
      // }
  return false;
}

/* 

Delta Beta cut

*/

DeltaBetaCut::DeltaBetaCut(){
  
}

DeltaBetaCut::DeltaBetaCut( Calculator tempcalc ) : Cuts(tempcalc){

}

DeltaBetaCut::~DeltaBetaCut(){

}


Double_t DeltaBetaCut::MaxBeta( Eventh22 &particle, Int_t gindex){

  Double_t maxbeta = (particle.p[gindex]/sqrt(particle.p[gindex]*particle.p[gindex]+0.938272*0.938272) + 0.02)*(1.2+0.92*particle.p[gindex])/(1+particle.p[gindex]);
  return maxbeta;
}

Double_t DeltaBetaCut::MinBeta( Eventh22 &particle, Int_t gindex){

  Double_t minbeta = (particle.p[gindex]/sqrt(particle.p[gindex]*particle.p[gindex]+0.938272*0.938272) - 0.05)*(0.9+1.06*particle.p[gindex])/(1+particle.p[gindex]);
  return minbeta;
}

bool DeltaBetaCut::candidate(Eventh22 &particle, Int_t gindex){

  Double_t massproton = 0.938272;
  Double_t h22beta = particle.b[gindex];
  Double_t momentum = particle.p[gindex];
  Double_t calcbeta = momentum/(sqrt(momentum*momentum + massproton*massproton));
  Double_t h22betadiff = h22beta - calcbeta;
  //if( std::abs(h22betadiff) < max_betadiff ){
  //return true;
  //}
  //std::cout << " >> " << h22beta << " > " << MaxBeta( particle, gindex ) << std::endl;
  Double_t SpeedOfLight = 29.9792458;
  Double_t StartTime=particle.sc_t[particle.goldenelectronindex]-particle.sc_r[particle.goldenelectronindex]/SpeedOfLight; 
  //  sc_r[nn]/(sc_t[nn]-StartTime)/SpeedOfLight;
  Double_t protonBeta = particle.sc_r[gindex]/(particle.sc_t[gindex] - StartTime)/SpeedOfLight;
  if( protonBeta > MinBeta(particle, gindex) && protonBeta < MaxBeta( particle,gindex ) ){
    npass++;
    return true;
  }
  return false;
}

Double_t DeltaBetaCut::h22betadiff( Eventh22 &particle, Int_t gindex ){
  Double_t massproton = 0.938272;
  Double_t h22beta = particle.b[gindex];
  Double_t momentum = particle.p[gindex];
  Double_t calcbeta = momentum/(sqrt(momentum*momentum + massproton*massproton));
  Double_t h22betadifference = h22beta - calcbeta;

  return h22betadifference;
  
}

BetaCut::BetaCut(){

}

BetaCut::BetaCut( Calculator tempcalc ) : Cuts(tempcalc){

}

BetaCut::~BetaCut(){

}


bool BetaCut::candidate(Eventh22 &particle, Int_t gindex){
  // 1-31-2017 change cut to b< max && b > min 
  Double_t SpeedOfLight = 29.9792458;
  Double_t StartTime=particle.sc_t[particle.goldenelectronindex]-particle.sc_r[particle.goldenelectronindex]/SpeedOfLight; 
  Double_t betacalc = particle.ec_r[gindex]/(particle.ec_t[gindex]-StartTime)/SpeedOfLight;
  if( betacalc > min_betacut ){ // && particle.b[gindex] < max_betacut ){ //mod to match silvia's cut to compare with run 59519
    npass++;
    return true;
  }
  return false; 
}

/*
Min Beta Cut to remove events with b = 0 -- though it doesn't quite solve the problem.... 
*/

MinBetaCut::MinBetaCut(){

}

MinBetaCut::MinBetaCut( Calculator tempcalc ) : Cuts(tempcalc){

}

MinBetaCut::~MinBetaCut(){

}

bool MinBetaCut::candidate(Eventh22 &particle, Int_t gpart){

  if( particle.b[gpart] > 0 ){
    return true;
  }
  return false;
}


/*
EC Inner and EC Outer Cut
*/

ECDepInner::ECDepInner(){

}

ECDepInner::ECDepInner( Calculator tempcalc ) : Cuts(tempcalc){
  //std::cout << " using new constructor " << std::endl;

}

ECDepInner::~ECDepInner(){

}

bool ECDepInner::candidate(Eventh22 &particle, Int_t gindex){
  // 0 -> etot , 1 -> ec_ei, 2 -> ec_eo
  // Double_t *ec_corr = calculate.PhotonCorrectECEnergy( runnumber, particle, gindex );
  // Double_t ecmax = (ec_corr[0]>ec_corr[1]+ec_corr[2]?ec_corr[0]:ec_corr[1]+ec_corr[2]);
  // if( ec_corr[1] == 0 && ((ecmax - ec_corr[2]) > min_ecdepinner ) ){
  //   return true;
  // } 
  // if( ec_corr[1] !=0 && ec_corr[1] > min_ecdepinner ){
  //   return true;
  // }
  //  Int_t ecscalefactor = 0;
  Double_t etot_corr = particle.etot[gindex];
  Double_t ei_corr = particle.ec_ei[gindex];
  Double_t eo_corr = particle.ec_eo[gindex];
  Int_t ecsector = particle.ec_sect[gindex];
  //std::cout << " Electron sector is " << runnumber << std::endl;
  if( 0 < ecsector && ecsector < 7 ){
    ecscalefactor = 0;
    //std::cout << " Going to set ecscalefactor for sect " << ecsector << std::endl;
    if( ecsector == 1 ){ ecscalefactor = ecSF1_corr;}
    if( ecsector == 2 ){ ecscalefactor = ecSF2_corr;}
    if( ecsector == 3 ) ecscalefactor = ecSF3_corr;
    if( ecsector == 4 ) ecscalefactor = ecSF4_corr;
    if( ecsector == 5 ) ecscalefactor = ecSF5_corr;
    if( ecsector == 6 ) ecscalefactor = ecSF6_corr;
    //std::cout << " The scalefactor is " << ecscalefactor << std::endl;
  }

  //std::cout << " Since the electron hit " << ecsector << "the ecSF is " << ecscalefactor << std::endl;

  if( 0.0 < particle.etot[gindex] &&  particle.etot[gindex] < 5.0 ){
    etot_corr = particle.etot[gindex]*( 0.2765/ecscalefactor );
    //std::cout << " etot corrected to " << etot_corr << std::endl;
  }
  if( 0.0 < particle.ec_ei[gindex] && particle.ec_ei[gindex] < 5.0 ){
    ei_corr = particle.ec_ei[gindex]*( 0.2765/ecscalefactor );
    //std::cout << " ei corrected to " << ei_corr << std::endl;
  }
  if( 0.0 < particle.ec_eo[gindex] && particle.ec_eo[gindex] < 5.0 ){
    eo_corr = particle.ec_eo[gindex]*( 0.2765/ecscalefactor );
    //  std::cout << " eo corrected to " << eo_corr << std::endl;
  }
  
  Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);
  
  if( ei_corr !=0 && ei_corr > min_ecdepinner ){
    npass++;
    return true;
  }
  else if ( ei_corr == 0 && ((ecmax - eo_corr) > min_ecdepinner ) ){
    npass++;  
    return true;
  } 
  
  // if( particle.ec_ei[gindex] > min_ecdepinner ){
  //   return true;
  // }

return false;
}

ECDepInnerOther::ECDepInnerOther(){

}

ECDepInnerOther::ECDepInnerOther( Calculator tempcalc ) : Cuts(tempcalc){

}

ECDepInnerOther::~ECDepInnerOther(){

}

bool ECDepInnerOther::candidate(Eventh22 &particle, Int_t gindex){
  Double_t ecdepinner = particle.ec_ei[gindex];
  if( ecdepinner > min_ecdepinnerghost ){
    return true;
  }
  return false;
}

ECDepOuter::ECDepOuter(){

}

ECDepOuter::ECDepOuter( Calculator tempcalc ) : Cuts(tempcalc){

}

ECDepOuter::~ECDepOuter(){

}

bool ECDepOuter::candidate(Eventh22 &particle, Int_t gindex){
  Double_t ecdepouter = particle.ec_eo[gindex];
  if( ecdepouter > min_ecdepouter ){
    return true;
  }
  return false;
}

SCtiming::SCtiming(){

}

SCtiming::SCtiming( Calculator tempcalc ) : Cuts(tempcalc){

}

SCtiming::~SCtiming(){

}

bool SCtiming::candidate( Eventh22 &particle, Int_t gindex ){

  if( particle.sc_t[gindex] < 100.0  && particle.sc_t[gindex] > 0.0 ){
    npass++; 
   return true;
  }
  return false;
  
}


/* 
SC & CC coincidence timing cut
Purpose is to time the arrive of a particle in two detectors, SC and CC. If the timing is between cut,
then it is a good event. 
*/

CCSCCut::CCSCCut(){

}

CCSCCut::CCSCCut( Calculator tempcalc ) : Cuts(tempcalc){

}

CCSCCut::~CCSCCut(){
}

bool CCSCCut::candidate( Eventh22 &particle, Int_t gindex){
  //Removed the ec_shift time and the results then matched angela's code results. 3-03-2017
  Double_t SpeedOfLight = 29.9792458;
  Double_t el_time = (std::fabs(particle.cc_t[gindex] - particle.cc_r[gindex]/SpeedOfLight - particle.sc_t[gindex] + particle.sc_r[gindex]/SpeedOfLight + offsettiming ));
  //std::cout << " CCSCCut  el time - " << el_time << std::endl;
  //std::cout << " CCSCCut offsettiming - " << offsettiming << std::endl;
   
  if( el_time <= 2 ){
    // std::cout << " CCSCCut  - " << particle.cc_t[gindex] << std::endl;
    //std::cout << " CCSCCut  - " << particle.cc_r[gindex]/SpeedOfLight << std::endl;
    //std::cout << " CCSCCut  - " << particle.sc_t[gindex] << std::endl;
    //std::cout << " CCSCCut  - " << particle.sc_r[gindex]/SpeedOfLight << std::endl;
    
    npass++;
    return true;
  }
  return false;
}

Double_t CCSCCut::ReturnTimeDiff( Eventh22 &particle, Int_t gindex ){

  Double_t cc_t = particle.cc_t[gindex]/1000000000;  
  Double_t cc_r = particle.cc_r[gindex]/100;
  Double_t sc_t = particle.sc_t[gindex]/1000000000;
  Double_t sc_r = particle.sc_r[gindex]/100;
  Double_t c = 299792458.0;
  
  Double_t timediff = cc_t - (cc_r/c) - sc_t + (sc_r/c);
  return timediff;
}

/*

CC_2 Cut 

*/

CC2Cut::CC2Cut(){

}

CC2Cut::CC2Cut( Calculator tempcalc ) : Cuts(tempcalc){

}

CC2Cut::~CC2Cut(){

}

bool CC2Cut::candidate( Eventh22 &particle, Int_t gindex ){

  if ( particle.cc_c2[gindex] < 0.15 ){//max_ccc2 ){
    npass++;
    return true;
  }
  return false;
}

/*

ZVertex Cut
 
*/ 
ZVertexCut::ZVertexCut(){

}


ZVertexCut::ZVertexCut( Calculator tempcalc ) : Cuts(tempcalc){
  //std::cout << " using new constructor " << std::endl;

}

ZVertexCut::~ZVertexCut(){

}

bool ZVertexCut::candidate(Eventh22 &particle, Int_t gindex){
  //std::cout << targetpos << std::endl;
  Double_t *vz_corrected = calculate.CosineCorrection( runnumber, particle, gindex);
  Double_t Zvertex = vz_corrected[3];
  Double_t targetcenter = targetpos;
  // std::cout << Zvertex << std::endl;
  Double_t Zvertexdiff = TMath::Abs( Zvertex - targetcenter );
  //std::cout << zvertexlimit << std::endl;
  if( Zvertexdiff <= zvertexlimit ){ 
    npass++;
    return true;
  }
  return false;
}

/*

ZVertexProton Cut (different from above cut which is for the electron )
 
*/ 
ZVertexProtonCut::ZVertexProtonCut(){

}

ZVertexProtonCut::ZVertexProtonCut( Calculator tempcalc ) : Cuts(tempcalc){
  //std::cout << " using new constructor " << std::endl;

}

ZVertexProtonCut::~ZVertexProtonCut(){

}

bool ZVertexProtonCut::candidate(Eventh22 &particle, Int_t gindex){
  
  Double_t *vz_corrected = calculate.CosineCorrection( runnumber, particle, gindex);
  Double_t Zvertex = vz_corrected[3];
  Double_t targetcenter = targetpos;
  Double_t Zvertexdiff = std::fabs( Zvertex -  targetcenter );
  if( Zvertexdiff <= zvertexlimitproton ){
    npass++;
    return true;
  }
  return false;
}


/* 
EC UVW rotation
 */
ECplaneRotated::ECplaneRotated(){
}

ECplaneRotated::ECplaneRotated( Calculator tempcalc ) : Cuts(tempcalc){

}

ECplaneRotated::~ECplaneRotated(){

}

TVector3 ECplaneRotated::UVW(Eventh22 &particle, Int_t gindex){
  
  Float_t u, v, w, xi, yi, zi;
  Float_t pi = 3.14159265;
  Float_t EC_the = 0.4363323;
  Float_t EC_phi;
  Float_t ylow   = -182.974;
  Float_t yhi    = 189.956;
  Float_t tgrho  = 1.95325;
  Float_t sinrho = 0.8901256;
  Float_t cosrho = 0.455715;
  Float_t rot[3][3];

  double x = particle.ech_x[gindex];
  double y = particle.ech_y[gindex];
  double z = particle.ech_z[gindex];

  double at = TMath::ATan2( y, x );// atan2(y, x);
  if (at < 0.) at += 2*pi;
    
  double phi = (180.0/pi)*at;
  phi=phi+30.;
  if (phi>=360.) phi=phi-360.;
    
  EC_phi = ((int)(phi/60.)) * 1.0471975;
      
  rot[0][0] = cos(EC_the)*cos(EC_phi);
  rot[0][1] = -sin(EC_phi);
  rot[0][2] = sin(EC_the)*cos(EC_phi);
  rot[1][0] = cos(EC_the)*sin(EC_phi);
  rot[1][1] = cos(EC_phi);
  rot[1][2] = sin(EC_the)*sin(EC_phi);
  rot[2][0] = -sin(EC_the);
  rot[2][1] = 0.; 
  rot[2][2] = cos(EC_the);

  yi=x*rot[0][0]+y*rot[1][0]+z*rot[2][0];
  xi=x*rot[0][1]+y*rot[1][1]+z*rot[2][1];
  zi=x*rot[0][2]+y*rot[1][2]+z*rot[2][2];

  zi=zi-510.32;
    
  u = (yi-ylow)/sinrho;
  v = (yhi-ylow)/tgrho-xi+(yhi-yi)/tgrho;
  w = ((yhi-ylow)/tgrho+xi+(yhi-yi)/tgrho)/2./cosrho;

  
  TVector3 UVWrotated( u, v, w );
  return UVWrotated;
}

TVector3 ECplaneRotated::UVWAngela(Eventh22 &particle, Int_t gindex ){

  /* ANGELA's CODE to convert x,y,z EC hit 
     in CLAS coordinate system
     into u,v,w distances of the EC hit. */

  Float_t ex=0.;
  Float_t wy=0.;
  Float_t zd=0.;
  Float_t yu=0.;
  Float_t ve=0.;
  Float_t wu=0.;
  Float_t xi=0.;
  Float_t yi=0.;
  Float_t zi=0.;
  Float_t ec_phy = 0.;
  Float_t phy = 0.;
  Float_t rot[3][3];

  // Parameters
  Float_t ec_the = 0.4363323;
  Float_t ylow = -182.974;
  Float_t yhi = 189.956;
  Float_t tgrho = 1.95325;
  Float_t sinrho = 0.8901256;
  Float_t cosrho = 0.455715;

  // Variables
  ex = particle.ech_x[gindex];//xyz[0];
  wy = particle.ech_y[gindex];//xyz[1];
  zd = particle.ech_z[gindex];//xyz[2];

  phy = TMath::ATan2(wy,ex)*57.29578;
  if(phy<0.){phy = phy + 360;}
  phy = phy+30.;
  if(phy>360.){phy = phy-360.;}

  ec_phy = ((Int_t) (phy/60.))*1.0471975;

  rot[0][0] = TMath::Cos(ec_the)*TMath::Cos(ec_phy);
  rot[0][1] = -TMath::Sin(ec_phy);
  rot[0][2] = TMath::Sin(ec_the)*TMath::Cos(ec_phy);
  rot[1][0] = TMath::Cos(ec_the)*TMath::Sin(ec_phy);
  rot[1][1] = TMath::Cos(ec_phy);
  rot[1][2] = TMath::Sin(ec_the)*TMath::Sin(ec_phy);
  rot[2][0] = -TMath::Sin(ec_the);
  rot[2][1] = 0.;
  rot[2][2] = TMath::Cos(ec_the);

  yi = ex*rot[0][0]+wy*rot[1][0]+zd*rot[2][0];
  xi = ex*rot[0][1]+wy*rot[1][1]+zd*rot[2][1];
  zi = ex*rot[0][2]+wy*rot[1][2]+zd*rot[2][2];
  zi = zi-510.32 ;

  yu = (yi-ylow)/sinrho;
  ve = (yhi-ylow)/tgrho - xi + (yhi-yi)/tgrho;
  wu = ((yhi-ylow)/tgrho + xi + (yhi-yi)/tgrho)/2./cosrho;

  TVector3 result3(yu,ve,wu);

  return result3;

  
}

TVector3 ECplaneRotated::UVWhallcord(Eventh22 &particle, Int_t gindex){
    
  Float_t u, v, w, xi, yi, zi;
  Float_t pi = 3.14159265;
  Float_t EC_the = 0.4363323;
  Float_t EC_phi;
  Float_t ylow   = -182.974;
  Float_t yhi    = 189.956;
  Float_t tgrho  = 1.95325;
  Float_t sinrho = 0.8901256;
  Float_t cosrho = 0.455715;
  Float_t rot[3][3];

  double x = particle.ech_x[gindex];
  double y = particle.ech_y[gindex];
  double z = particle.ech_z[gindex];

  double at = atan2(y, x);
  if (at < 0) at += 2*pi;

  double phi = (180.0/pi)*at;
  phi=phi+30.;
  if (phi>=360.) phi=phi-360.;
    
  EC_phi = (int)(phi/60.) * 1.0471975;
      
  rot[0][0] = cos(EC_the)*cos(EC_phi);
  rot[0][1] = -sin(EC_phi);
  rot[0][2] = sin(EC_the)*cos(EC_phi);
  rot[1][0] = cos(EC_the)*sin(EC_phi);
  rot[1][1] = cos(EC_phi);
  rot[1][2] = sin(EC_the)*sin(EC_phi);
  rot[2][0] = -sin(EC_the);
  rot[2][1] = 0.; 
  rot[2][2] = cos(EC_the);

  yi=x*rot[0][0]+y*rot[1][0]+z*rot[2][0];
  xi=x*rot[0][1]+y*rot[1][1]+z*rot[2][1];
  zi=x*rot[0][2]+y*rot[1][2]+z*rot[2][2];

  zi=zi-510.32;
    
  u = (yi-ylow)/sinrho;
  v = (yhi-ylow)/tgrho-xi+(yhi-yi)/tgrho;
  w = ((yhi-ylow)/tgrho+xi+(yhi-yi)/tgrho)/2./cosrho;
  
  TVector3 UVWhall( x, y, z );
  //TVector3 UVWhall( u, v, w );

  return UVWhall;  
}

/* 
EC UVW plane Cuts 
 */

ECUplaneCut::ECUplaneCut(){

}

ECUplaneCut::ECUplaneCut( Calculator tempcalc ) : Cuts(tempcalc){

}

ECUplaneCut::~ECUplaneCut(){

}

bool ECUplaneCut::candidate(Eventh22 &particle, Int_t gindex){

  ECplaneRotated planes;
  //TVector3 UVWplane = planes.UVW(particle, gindex);
  TVector3 UVWaplane = planes.UVWAngela(particle, gindex);

  if( (UVWaplane.X() < 400) && (UVWaplane.X() > 40) ){
    npass++;
    return true;
  }
  return false;  
}

ECVplaneCut::ECVplaneCut(){

}

ECVplaneCut::ECVplaneCut( Calculator tempcalc ) : Cuts(tempcalc){

}

ECVplaneCut::~ECVplaneCut(){

}

bool ECVplaneCut::candidate(Eventh22 &particle , Int_t gindex){

  ECplaneRotated planes;
  //TVector3 UVWplane = planes.UVW(particle, gindex);
  TVector3 UVWplane = planes.UVWAngela(particle, gindex);

  if( (UVWplane.Y() < 360) ){
    npass++;
    return true;
  }
  return false;
}

ECWplaneCut::ECWplaneCut(){

}

ECWplaneCut::ECWplaneCut( Calculator tempcalc ) : Cuts(tempcalc){

}

ECWplaneCut::~ECWplaneCut(){

}

bool ECWplaneCut::candidate(Eventh22 &particle, Int_t gindex){

  ECplaneRotated planes;
  //TVector3 UVWplane = planes.UVW(particle, gindex);
  TVector3 UVWplane = planes.UVWAngela(particle, gindex);

  if( (UVWplane.Z() < 390) ){
    npass++;
    return true;
  }
  return false;  
}
///////////////////////////////////////////////////////////////

ECUplaneCutPhoton::ECUplaneCutPhoton(){

}

ECUplaneCutPhoton::ECUplaneCutPhoton( Calculator tempcalc ) : Cuts(tempcalc){

}

ECUplaneCutPhoton::~ECUplaneCutPhoton(){

}

bool ECUplaneCutPhoton::candidate(Eventh22 &particle, Int_t gindex){

  ECplaneRotated planes;
  //TVector3 UVWplane = planes.UVW(particle, gindex);
  TVector3 UVWaplane = planes.UVWAngela(particle, gindex);

  if( (UVWaplane.X() < 400) && (UVWaplane.X() > 40) ){
    npass++;
    return true;
  }
  return false;  
}

ECVplaneCutPhoton::ECVplaneCutPhoton(){

}

ECVplaneCutPhoton::ECVplaneCutPhoton( Calculator tempcalc ) : Cuts(tempcalc){

}

ECVplaneCutPhoton::~ECVplaneCutPhoton(){

}

bool ECVplaneCutPhoton::candidate(Eventh22 &particle , Int_t gindex){

  ECplaneRotated planes;
  //TVector3 UVWplane = planes.UVW(particle, gindex);
  TVector3 UVWplane = planes.UVWAngela(particle, gindex);

  if( (UVWplane.Y() < 360) ){
    npass++;
    return true;
  }
  return false;
}

ECWplaneCutPhoton::ECWplaneCutPhoton(){

}

ECWplaneCutPhoton::ECWplaneCutPhoton( Calculator tempcalc ) : Cuts(tempcalc){

}

ECWplaneCutPhoton::~ECWplaneCutPhoton(){

}

bool ECWplaneCutPhoton::candidate(Eventh22 &particle, Int_t gindex){

  ECplaneRotated planes;
  //TVector3 UVWplane = planes.UVW(particle, gindex);
  TVector3 UVWplane = planes.UVWAngela(particle, gindex);

  if( (UVWplane.Z() < 390) ){
    npass++;
    return true;
  }
  return false;  
}
//////////////////////////////////////////////////////
/*

IC Cuts

 */
ICCut::ICCut(){
  //std::cout << " using default constructor " << std::endl;
}

ICCut::ICCut( Calculator tempcalc ) : Cuts(tempcalc){
  //std::cout << " using new constructor " << std::endl;

}

ICCut::~ICCut(){

}

bool ICCut::candidate(Eventh22 &particle, Int_t sindex ){

  // std::cout<< " >> run number is " << calculate.run << std::endl;
   
  static const float dx = 1.346; // cm
  static const float dy = 1.360;
  static const float nin = 3.250;
  static const float nout = 10.75;
  static const float root2 = TMath::Sqrt(2);
  static const float pi = 3.14159265;

  // Original xx and yy hit position without correcting for rastering of the beam
  Double_t xx_o = particle.xc[sindex];
  Double_t yy_o = particle.yc[sindex];

  Double_t *xy_corr = calculate.RasterCorrection( runnumber, particle, sindex );
  /* Variables xx and yy stand for the corrected x and y position
     by taking into account the rastering of the beam across the target.
     xy_c is an array of length two containing the x and y values to correct by
  */

  Double_t xx = fabs(xx_o);
  Double_t yy = fabs(yy_o);

  //std::cout << xx_o << " " << xx << std::endl;
  //std::cout << yy_o << " " << yy << std::endl;
  
  //  bool outside1 = true;
  // bool outside2 = true;

  /*  // INNER: 
  if (fabs(xx) / dx < nin){
    if (fabs(yy) / dy < nin){
      if (fabs(xx / dx - yy / dy) < nin * root2){
	if (fabs(xx / dx + yy / dy) < nin * root2){
	  outside1 = false;
	}
      }
    }
  }
  
  // OUTER:
  if (fabs(xx) / dx > nout || fabs(yy) / dy > nout ||
      fabs(xx / dx - yy / dy) > nout * root2 ||
      fabs(xx / dx + yy / dy) > nout * root2){
    outside2 = false;
  }
  */
  /*  // INNER: 
  if ( xx / dx < nin){
    if ( yy / dy < nin){
      if ( (xx / dx - yy / dy) < nin * root2){
	if ( (xx / dx + yy / dy) < nin * root2){
	  outside1 = false;
	}
      }
    }
  }
  
  // OUTER:
  if ((xx) / dx > nout || (yy) / dy > nout ||
      (xx / dx - yy / dy) > nout * root2 ||
      (xx / dx + yy / dy) > nout * root2){
    outside2 = false;
  }
  */
  
  Float_t stepX        =  1.346;
  Float_t stepY        =  1.360;
  Float_t innerICEdge  =  3.250;
  Float_t outerICEdge  =  10.75;  
  
  // Bool_t cutThis =  true;
  Double_t absPhX2 = xx;
  Double_t absPhY2 = yy;
  
  if (
      // check if the hit is in inner no fly zone
      ( ( absPhX2 / stepX ) < innerICEdge                                    &&
	( absPhY2 / stepY ) < innerICEdge                                    &&
	( absPhX2 / stepX ) + (absPhY2 / stepY) < innerICEdge*TMath::Sqrt(2) &&
	( absPhX2 / stepX ) - (absPhY2 / stepY) < innerICEdge*TMath::Sqrt(2) 
	) 
      
      ||
      
      // check if the hit is in the outer no fly zone
      ( ( absPhX2 / stepX ) > outerICEdge                                    ||
	( absPhY2 / stepY ) > outerICEdge                                    ||
	( absPhX2 / stepX ) + (absPhY2 / stepY) > outerICEdge*TMath::Sqrt(2) ||
	( absPhX2 / stepX ) - (absPhY2 / stepY) > outerICEdge*TMath::Sqrt(2)  
	)
      ) {
    // if the hit is in either of the no fly zones assign true value
    //cutThis = true;
   
    return false;
  }
  
  //  if(!cutThis){
  //  npass++;
  // }
  npass++;

  //if( outside1 && outside2 ){
  //  return true;
  // }
  //return false;
  return true;
}

MoellerElectronCut::MoellerElectronCut(){

}

MoellerElectronCut::MoellerElectronCut( Calculator tempcalc ) : Cuts(tempcalc) {

}

MoellerElectronCut::~MoellerElectronCut(){

}

bool MoellerElectronCut::candidate(Eventh22 &particle, Int_t sindex ){

  TLorentzVector icphoton_lv = calculate.ICphoton_LV( particle, sindex, runnumber );
  //  std::cout << part << std::endl;
  if( part == 1 ){
    //    std::cout << part << std::endl;
    if( icphoton_lv.E() > 0.35 && icphoton_lv.Theta()*TMath::RadToDeg() > ( (-6.5/1.2)*icphoton_lv.E() + 7.5 ) ){
      npass++;
      return true;
    }
  }
  else if( part == 2 ){
    if( icphoton_lv.E() > 0.3 && icphoton_lv.Theta()*TMath::RadToDeg() > ( (-6.5/1.6)*icphoton_lv.E() + 6.5 ) ){
      npass++;
      return true;
    }
  }
  return false;
}

ICEnergyCut::ICEnergyCut(){

}

ICEnergyCut::ICEnergyCut( Calculator tempcalc ) : Cuts(tempcalc){

}

ICEnergyCut::~ICEnergyCut(){

}

bool ICEnergyCut::candidate(Eventh22 &event, Int_t sindex){

  if( event.etc[sindex] > min_icdep ){
    npass++;
    return true;
  }

  return false;
}

  
/* 

IC Shadow on DC cut 

*/

ICShadowCut::ICShadowCut(){
  
}

ICShadowCut::ICShadowCut( Calculator tempcalc ) : Cuts( tempcalc ){
  
}

ICShadowCut::~ICShadowCut(){

}

bool ICShadowCut::ICOK(float x, float y, int it, int part ){

  // returns 1 if particle doesn't hit IC frame/support
  // x and y are particle positions at IC front face in cm
  // it, is 1 for standard/regular, 2 for tight cut (1 cm all around)
  int iphi = 0;
  float phi= 0.0;
  float r = 0.0;
  float rv_partb[72] = {18.5, 18.5, 19.0, 19.5,
			20.0, 26.0, 26.0, 26.0, 26.0, 20.0, 20.0, 20.5, 
			21.0, 22, 24, 24.0, 24.0, 24.0,24.0, 24.0, 24.0, 24, 24.0, 21.0, 
			20.5, 20.0, 20.0, 26.0, 26.0, 26.0, 26.0, 20.5, 20.5, 20.5, 20.0,
			20.0, 20.0, 20.0, 20.5, 20.5, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
			20.5, 20.5, 20.5, 20.5, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
			20.0, 20.0, 20.0, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			19.0, 19.0, 18.5, 18.5 };
  float rv_parta[72] = {18.5, 18.5, 19.0, 19.5,
			20.0, 26.0, 26.0, 26.0, 26.0, //left leg
			20.0, 20.0, 20.5, 21.0, 22,
			23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, //bottom
			21.0, 20.5, 20.0, 20.0,
			26.0, 26.0, 26.0, 26.0, //right leg
			20.5, 19.5, 19.5, 19.0, 19.0, 19.0, 19.0, 19.5, 19.5, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0,
			19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			20.0,20.0, 20.0, 20.0,
			19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			19.0, 19.0, 18.5, 18.5 };
  float *rv;
  if(part==1){
    rv=rv_parta;
    //cout<<"using parta rv vector"<<rv[14]<<endl;
  }
  else if(part==2){
    rv=rv_partb;
    //cout<<"using partb rv vector"<<rv[14]<<endl;
  }
  else {
    //defaulting to part b cuts
    rv=rv_partb;
  }
  bool result = 0;

  phi = atan2(y,x)*57.29578 + 180.; 
  iphi = int (phi/5.0) + 1;
  if(iphi>72) iphi=72;
  r = sqrt(x*x + y*y);
  if(it == 1) result = r > rv [iphi-1];
  if(it == 2) result = r > (rv[iphi-1] + 1.0);
  return result;
  
}

bool ICShadowCut::Fid_Cut_IC(int irun, float Charge, float Momentum, float TL1_x, float TL1_y, float TL1_z, float TL1_cx, float TL1_cy, int TypeOfCut, bool DelPhiOrNot){

  float xic = 0;
  float yic = 0;
  bool okf=1;
 
  xic = TL1_x - TL1_cx * TL1_z;
  yic = TL1_y - TL1_cy * TL1_z;

  if(TypeOfCut==1) okf = ICOK(xic, yic, 1, part );
  if(TypeOfCut==2) okf = ICOK(xic, yic, 2, part );

  float phi,phixy,targsign,diff,phicorr;

  targsign = -1.0;
  if(irun > 60222) targsign = 1.0;

  phi  = atan2(TL1_cy,TL1_cx) * 57.295 ;
  phixy= atan2(TL1_y ,TL1_x ) * 57.295 ;
  diff = phi - phixy ;

  if(diff < -180.) diff = diff + 360.0;
  if(diff >  180.) diff = diff - 360.0;

  phicorr = Charge * targsign * (0.0025 / Momentum) * 57.0;
  diff = diff + 0.3 + phicorr;
  
  if (DelPhiOrNot == 1)
    {
      if( fabs(diff) > 10.0)
	{
	  okf = 0;
	}
    }
  return okf;
}

// Here we are passing the vertex/origin of the event to reconstruct the path of the neutral particle.
// vx, vy come from the raster correction and vz is the vertex from the electron, but could be electron and proton averaged (do this in future)
bool ICShadowCut::NeutralFid_Cut_IC(float Vx, float Vy, float Vz, float Echx, float Echy, float Echz, int TypeOfCut,int part){
  float xic = 0.0;
  float yic = 0.0;
  bool okf=1;

  xic = (Echx-Vx) * -Vz/(Echz-Vz) + Vx;
  yic = (Echy-Vy) * -Vz/(Echz-Vz) + Vy;

  if(TypeOfCut==1) okf = ICOK(xic, yic, 1,part);
  if(TypeOfCut==2) okf = ICOK(xic, yic, 2,part);
 
  return okf;
}

bool ICShadowCut::candidate( Eventh22 &particle, Int_t gindex ){
 
  Double_t tlx = particle.tl1_x[gindex];
  Double_t tly = particle.tl1_y[gindex];
  Double_t tlz = particle.tl1_z[gindex];
  Double_t tlcx = particle.tl1_cx[gindex];
  Double_t tlcy = particle.tl1_cy[gindex];
  
  int charge = particle.q[gindex];
  double momentum = particle.p[gindex];
 
    if( Fid_Cut_IC(runnumber, charge, momentum, tlx, tly, tlz, tlcx, tlcy, 1, 0) ){
      npass++;
      return true;
    }
  return false;
}

/*


Proton Shadow Cuts 


*/

ICShadowCutProton::ICShadowCutProton(){
  
}

ICShadowCutProton::ICShadowCutProton( Calculator tempcalc ) : Cuts( tempcalc ){
  
}

ICShadowCutProton::~ICShadowCutProton(){

}


bool ICShadowCutProton::ICOKproton(float x, float y, int it, int part ){

  // returns 1 if particle doesn't hit IC frame/support
  // x and y are particle positions at IC front face in cm
  // it, is 1 for standard/regular, 2 for tight cut (1 cm all around)
  int iphi = 0;
  float phi= 0.0;
  float r = 0.0;
  float rv_partb[72] = {18.5, 18.5, 19.0, 19.5,
			20.0, 26.0, 26.0, 26.0, 26.0, 20.0, 20.0, 20.5, 
			21.0, 22, 24, 24.0, 24.0, 24.0,24.0, 24.0, 24.0, 24, 24.0, 21.0, 
			20.5, 20.0, 20.0, 26.0, 26.0, 26.0, 26.0, 20.5, 20.5, 20.5, 20.0,
			20.0, 20.0, 20.0, 20.5, 20.5, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
			20.5, 20.5, 20.5, 20.5, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
			20.0, 20.0, 20.0, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			19.0, 19.0, 18.5, 18.5 };
  float rv_parta[72] = {18.5, 18.5, 19.0, 19.5,
			20.0, 26.0, 26.0, 26.0, 26.0, //left leg
			20.0, 20.0, 20.5, 21.0, 22,
			23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, //bottom
			21.0, 20.5, 20.0, 20.0,
			26.0, 26.0, 26.0, 26.0, //right leg
			20.5, 19.5, 19.5, 19.0, 19.0, 19.0, 19.0, 19.5, 19.5, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0,
			19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			20.0,20.0, 20.0, 20.0,
			19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			19.0, 19.0, 18.5, 18.5 };
  float *rv;
  if(part==1){
    rv=rv_parta;
    //cout<<"using parta rv vector"<<rv[14]<<endl;
  }
  else if(part==2){
    rv=rv_partb;
    //cout<<"using partb rv vector"<<rv[14]<<endl;
  }
  else {
    //defaulting to part b cuts
    rv=rv_partb;
  }
  bool result = 0;

  phi = atan2(y,x)*57.29578 + 180.; 
  iphi = int (phi/5.0) + 1;
  if(iphi>72) iphi=72;
  r = sqrt(x*x + y*y);
  if(it == 1) result = r > rv [iphi-1];
  if(it == 2) result = r > (rv[iphi-1] + 1.0);
  return result;
  
}

bool ICShadowCutProton::Fid_Cut_ICproton(int irun, float Charge, float Momentum, float TL1_x, float TL1_y, float TL1_z, float TL1_cx, float TL1_cy, int TypeOfCut, bool DelPhiOrNot){

  float xic = 0;
  float yic = 0;
  bool okf=1;
 
  xic = TL1_x - TL1_cx * TL1_z;
  yic = TL1_y - TL1_cy * TL1_z;

  if(TypeOfCut==1) okf = ICOKproton(xic, yic, 1, part );
  if(TypeOfCut==2) okf = ICOKproton(xic, yic, 2, part );

  float phi,phixy,targsign,diff,phicorr;

  targsign = -1.0;
  if(irun > 60222) targsign = 1.0;

  phi  = atan2(TL1_cy,TL1_cx) * 57.295 ;
  phixy= atan2(TL1_y ,TL1_x ) * 57.295 ;
  diff = phi - phixy ;

  if(diff < -180.) diff = diff + 360.0;
  if(diff >  180.) diff = diff - 360.0;

  phicorr = Charge * targsign * (0.0025 / Momentum) * 57.0;
  diff = diff + 0.3 + phicorr;
  
  if (DelPhiOrNot == 1)
    {
      if( fabs(diff) > 10.0)
	{
	  okf = 0;
	}
    }
  return okf;
}

bool ICShadowCutProton::candidate( Eventh22 &particle, Int_t gindex ){
 
  Double_t tlx = particle.tl1_x[gindex];
  Double_t tly = particle.tl1_y[gindex];
  Double_t tlz = particle.tl1_z[gindex];
  Double_t tlcx = particle.tl1_cx[gindex];
  Double_t tlcy = particle.tl1_cy[gindex];
  
  int charge = particle.q[gindex];
  double momentum = particle.p[gindex];
 
    if( Fid_Cut_ICproton(runnumber, charge, momentum, tlx, tly, tlz, tlcx, tlcy, 1, 0) ){
      npass++;
      return true;
    }
  return false;
}


///////////////////////////////////////////////


ICNeutralShadowCut::ICNeutralShadowCut(){
  
}

ICNeutralShadowCut::ICNeutralShadowCut( Calculator tempcalc ) : Cuts( tempcalc ){
  // mycalculator = tempcalc;
}

ICNeutralShadowCut::~ICNeutralShadowCut(){

}

bool ICNeutralShadowCut::ICNeutralOK(float x, float y, int it, int part ){

  // returns 1 if particle doesn't hit IC frame/support
  // x and y are particle positions at IC front face in cm
  // it, is 1 for standard/regular, 2 for tight cut (1 cm all around)
  int iphi = 0;
  float phi= 0.0;
  float r = 0.0;
  float rv_partb[72] = {18.5, 18.5, 19.0, 19.5,
			20.0, 26.0, 26.0, 26.0, 26.0, 20.0, 20.0, 20.5, 
			21.0, 22, 24, 24.0, 24.0, 24.0,24.0, 24.0, 24.0, 24, 24.0, 21.0, 
			20.5, 20.0, 20.0, 26.0, 26.0, 26.0, 26.0, 20.5, 20.5, 20.5, 20.0,
			20.0, 20.0, 20.0, 20.5, 20.5, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
			20.5, 20.5, 20.5, 20.5, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
			20.0, 20.0, 20.0, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			19.0, 19.0, 18.5, 18.5 };
  float rv_parta[72] = {18.5, 18.5, 19.0, 19.5,
			20.0, 26.0, 26.0, 26.0, 26.0, //left leg
			20.0, 20.0, 20.5, 21.0, 22,
			23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, 23.5, //bottom
			21.0, 20.5, 20.0, 20.0,
			26.0, 26.0, 26.0, 26.0, //right leg
			20.5, 19.5, 19.5, 19.0, 19.0, 19.0, 19.0, 19.5, 19.5, 19.0, 19.0, 19.0, 19.0, 19.0, 19.0,
			19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			20.0,20.0, 20.0, 20.0,
			19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5, 19.5,
			19.0, 19.0, 18.5, 18.5 };
  float *rv;
  if(part==1){
    rv=rv_parta;
    //cout<<"using parta rv vector"<<rv[14]<<endl;
  }
  else if(part==2){
    rv=rv_partb;
    //cout<<"using partb rv vector"<<rv[14]<<endl;
  }
  else {
    //defaulting to part b cuts
    rv=rv_partb;
  }
  bool result = 0;

  phi = atan2(y,x)*57.29578 + 180.; 
  iphi = int (phi/5.0) + 1;
  if(iphi>72) iphi=72;
  r = sqrt(x*x + y*y);
  if(it == 1) result = r > rv [iphi-1];
  if(it == 2) result = r > (rv[iphi-1] + 1.0);
  return result;
  
}

bool ICNeutralShadowCut::NeutralFid_Cut_IC(float Vx, float Vy, float Vz, float Echx, float Echy, float Echz, int TypeOfCut,int part){
  float xic = 0.0;
  float yic = 0.0;
  bool okf=1;
  //use electron index for vz 
  xic = (Echx-Vx) * -Vz/(Echz-Vz) + Vx;
  yic = (Echy-Vy) * -Vz/(Echz-Vz) + Vy;

  if(TypeOfCut==1) okf = ICNeutralOK(xic, yic, 1,part);
  if(TypeOfCut==2) okf = ICNeutralOK(xic, yic, 2,part);
 
  return okf;
}

bool ICNeutralShadowCut::candidate( Eventh22 &particle, Int_t gindex ){
  bool icneutralshadowc = false;
  Double_t echx = particle.ech_x[gindex];
  Double_t echy = particle.ech_y[gindex];
  Double_t echz = particle.ech_z[gindex];
  Double_t *xy_c = calculate.RasterCorrection( runnumber, particle, gindex ); // returns the x and y coordinate of the event ( where particles originate) also need vz, get from event.vz[electronindex]

  if ( runnumber != -1 ){ 
    icneutralshadowc =  NeutralFid_Cut_IC( xy_c[0], xy_c[1], targetpos,  echx, echy, echz, 1, part); 
  }
  else if( runnumber == -1 ){
    icneutralshadowc = true;
  }

  if(icneutralshadowc ){ 
    npass++;
    return true;
  }  
  return false;
}

ICNoiseCut::ICNoiseCut(){
  
}

ICNoiseCut::ICNoiseCut( Calculator tempcalc ) : Cuts( tempcalc ){
  
}

bool ICNoiseCut::candidate( Eventh22 &particle, Int_t gindex ){
  TGeoPolygon icCrystalborder(4);
  Double_t x_icCrystal[4] = { -7.0, -4.0, -4.0, -7.0 };//-11.5, -11.5, -23.10, -23.10, -10.30, 9.91, 23.73, 23.73, 12.30, 12.30 };
  Double_t y_icCrystal[4] = { -9.0, -9.0, -7.0, -7.0 };//-26.07, -23.10, -12.85, 11.50, 22.95, 22.95, 13.10, -12.40, -22.36, -26.07};
  icCrystalborder.SetXY(x_icCrystal, y_icCrystal);
  icCrystalborder.FinishPolygon();
  
  Double_t xx_o = particle.xc[gindex];
  Double_t yy_o = particle.yc[gindex];
  
  Double_t *xy_c = calculate.RasterCorrection( runnumber, particle, gindex);
  Double_t xx = xy_c[0];//xx_o - xy_c[0];
  Double_t yy = xy_c[1];//yy_o - xy_c[1];

  Double_t a_icpos[2] = { xx, yy };
  bool NoisyICCrystalHit = icCrystalborder.Contains(a_icpos);

  if( NoisyICCrystalHit ){
    return false;
  }
  return true;
}

ICEnergyThetaCut::ICEnergyThetaCut(){

}

ICEnergyThetaCut::ICEnergyThetaCut( Calculator tempcalc ) : Cuts( tempcalc ){

}

bool ICEnergyThetaCut::candidate( Eventh22 &particle, Int_t sindex ){

  Double_t ICdepenergy = particle.etc[sindex];

  Double_t xx_o = particle.xc[sindex];
  Double_t yy_o = particle.yc[sindex];
  
  Double_t *xy_c = calculate.RasterCorrection( runnumber, particle, sindex);
  Double_t xx = xy_c[0];//xx_o - xy_c[0];
  Double_t yy = xy_c[1];//yy_o - xy_c[1];
  TVector3 icph3V;
  icph3V.SetX(xx_o);
  icph3V.SetY(yy_o);
  icph3V.SetZ(-particle.vz[0]); // assumes that the vertex is from the first particle in array which may or may not electron

  Double_t icph_theta = icph3V.Theta()*(180.0/TMath::Pi());

  if( ICdepenergy*12.0 + icph_theta > 9.0 ){
    return true;
  }
  return false;

  
}

NPhotonCut::NPhotonCut(){

}

NPhotonCut::NPhotonCut( Calculator tempcalc ) : Cuts(tempcalc){

}

bool NPhotonCut::candidate( Eventh22 &particle, Int_t gindex ){

  if( particle.nphe[ gindex ] > 20 ){
    return true;
  }
  return false;
}

 
