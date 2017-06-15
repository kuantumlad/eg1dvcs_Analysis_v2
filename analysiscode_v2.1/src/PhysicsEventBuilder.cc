#define physicseventbuilder_cxx

#include "../include/Eventh22.h"
#include "../include/EventPID.h"
#include "../include/PhysicsEvent.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/Calculator.h"
#include "../include/BuildtDVCS.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"
#include "TString.h"
#include <iostream>
#include <cmath>

PhysicsEventBuilder::PhysicsEventBuilder(){

}

PhysicsEventBuilder::PhysicsEventBuilder( TLorentzVector tempbeam, TLorentzVector temptarget, Calculator tempcal ){//Int_t temprun){
  physicsEvent.beamElectron = tempbeam;
  physicsEvent.targetParticle = temptarget;
  physicsEvent.beamEnergy = physicsEvent.beamElectron.E();
  physicsEvent.targetMass = physicsEvent.targetParticle.E();
  InitRunParameters(tempcal);
  //  std::cout << " beam LV " << physicsEvent.beamElectron.X() << " " << physicsEvent.beamElectron.Y() << " " << physicsEvent.beamElectron.Z() << " " << physicsEvent.beamElectron.E() << std::endl;
  //std::cout << " target LV " <<  physicsEvent.targetParticle.X() << " " << physicsEvent.targetParticle.Y() << " " << physicsEvent.targetParticle.Z() << " " << physicsEvent.targetParticle.E() << std::endl;
  //std::cout << " beam energy " << physicsEvent.beamEnergy << std::endl;
  //std::cout << " target mass " << physicsEvent.targetMass << std::endl;
}

void PhysicsEventBuilder::InitRunParameters( Calculator tempcal ){

  this->calc=tempcal;
  physicsEvent.run = calc.run;
  physicsEvent.tpol = calc.targetPolarization;
  physicsEvent.periodid = calc.periodID;
  physicsEvent.targettype = calc.targetType;
  physicsEvent.waveplatepos = calc.waveplatePos;
  physicsEvent.fc0 = calc.fc_0;
  physicsEvent.fc1 = calc.fc_1;
  physicsEvent.targetpos = calc.targetPos;
  physicsEvent.beamenergy = calc.beamEnergy;

  std::cout << " init parameters - pol is " << physicsEvent.tpol << std::endl; 
 
}

PhysicsEventBuilder::~PhysicsEventBuilder(){
  
}

PhysicsEvent PhysicsEventBuilder::getPhysicsEvent(TLorentzVector tempelectronLV, TLorentzVector tempprotonLV, TLorentzVector tempphotonLV, Int_t tempphotonTopology){ 

  physicsEvent.ClearKinematics();
  //TLorentzVector electronLV = setParticleLV("electron",tempevent, eindex );
  //TLorentzVector protonLV = setParticleLV("electron",tempevent, prindex );
  //TLorentzVector ecphotonLV = setParticleLV("electron",tempevent, ecphindex );
  //physicsEvent.pel = calc.ElectronCorrectedMntm(tempevent, eindex);
  //physicsEvent.prp = calc.ProtonCorrectedMntm(tempevent, prindex);
  setElectronKinematics( tempelectronLV );
  setProtonKinematics( tempprotonLV );
  setGoodPhotonKinematics( tempphotonLV, tempphotonTopology );
  //setVectors(tempelectronLV, tempprotonLV, tempphotonLV);
  setKinematics();
  return physicsEvent; 
}

PhysicsEvent PhysicsEventBuilder::setPhysicsEvent(Eventh22 event){ 

  physicsEvent.ClearKinematics();
  //TLorentzVector electronLV = setParticleLV("electron",tempevent, eindex );
  //TLorentzVector protonLV = setParticleLV("electron",tempevent, prindex );
  //TLorentzVector ecphotonLV = setParticleLV("electron",tempevent, ecphindex );
  //physicsEvent.pel = calc.ElectronCorrectedMntm(tempevent, eindex);
  //physicsEvent.prp = calc.ProtonCorrectedMntm(tempevent, prindex);
  //  std::cout << " golden electronr " << event.goldenelectronindex << std::endl;
  //std::cout << " golden proton " <<  event.goldenprotonindex << std::endl;
  if( event.goldenelectronindex == event.goldenprotonindex ){ std::cout << " ERROR " << std::endl;}
  //  std::cout << "done " << std::endl;
  setElectronKin( event, event.goldenelectronindex );
  setProtonKin( event, event.goldenprotonindex );
  setPhotonKin( event );
  setHelicity( event );

  //setGoodPhotonKinematics( tempphotonLV, tempphotonTopology );
  setVectors();//physicsEvent.el_LV, physicsEvent.pr_LV, physicsEvent.ph_LV );
  setKinematics();
  return physicsEvent;
}

// void PhysicsEventBuilder::setRunInfo( ){

//   physicsEvent.run = calc.run;
//   physicsEvent.tpol = calc.targetPolarization;
//   physicsEvent.periodid = calc.periodID;
//   physicsEvent.targettype = calc.targetType;

// }

void PhysicsEventBuilder::setElectronKinematics( TLorentzVector tempLV ){
  //physicsEvent.pel = tempLV.Vect().Mag();
  /*  physicsEvent.pel =  tempLV.Vect().Mag();//calc.ElectronCorrectedMntm( tempLV.Vect().Mag() ); //commenting out because already corrected in PID selection.
  physicsEvent.eltheta = tempLV.Theta()*180./TMath::Pi();
  physicsEvent.elphi = tempLV.Phi()*180./TMath::Pi();
  */
}

void PhysicsEventBuilder::setElectronKin(Eventh22 tempevent, Int_t index ){

  // Need to have corrected momentum, corrected cx cy and vertex, and energy dep here
  //also have v3 for vertex (0,0,vzcorr)
  //dc sect
  //emom with XYZM
  //eth_dc using sqrt (1 - tl1cx*cx - tl1cy*cy ) into deg  same for 
  //eph_dc using atan2 tl1cy, tl1cx into deg
  //helicity , if hwp in then !hel, and if run < 59442 flip again
  // nphe, and all corrected ec energies ec_ei and ec_eo and ec_tot
  //  std::cout << " setting Electron Kin " << std::endl;
    physicsEvent.pel = calc.ElectronCorrectedMntm( tempevent.p[index] );
  //physicsEvent.pel = tempevent.p[index];
  //std::cout << " corrected - " << physicsEvent.pel << " \n" << "original - " << tempevent.p[index] << std::endl;
  Double_t *el_cos_corr = calc.CorrectedCosineCorrection( physicsEvent.run, tempevent, index, physicsEvent.pel );
  //  Double_t *ec_energy_corr = calc.ECSFCorrection( tempevent, index );
  
  Double_t el_cxc = el_cos_corr[0];
  Double_t el_cyc = el_cos_corr[1];
  Double_t el_czc = sqrt(1 - el_cxc*el_cxc - el_cyc*el_cyc);
  //std::cout <<" corrected cosine " << el_cxc << " " << el_cyc << " " << el_czc << std::endl;
  //std::cout <<" corrected z " <<  el_cos_corr[3] << std::endl;
  physicsEvent.el_vertex = el_cos_corr[3];
  physicsEvent.el_dcsect = tempevent.dc_sect[index];
  physicsEvent.el_thetaDC = acos( sqrt( 1 - tempevent.tl1_cx[index]*el_cxc - tempevent.tl1_cy[index]*el_cyc ))*(calc.RadtoDeg());
  physicsEvent.el_phiDC = atan2( tempevent.tl1_cy[index], tempevent.tl1_cx[index] )*(calc.RadtoDeg());
  //physicsEvent.el_ecei =  ec_energy_corr[0];
  //physicsEvent.el_eceo = ec_energy_corr[1];
  //physicsEvent.el_ectot = ec_energy_corr[2];
  //physicsEvent.el_ecmax = ec_energy_corr[3];
  physicsEvent.el_nphe = tempevent.nphe[index];

  physicsEvent.el_LV.SetXYZM( physicsEvent.pel*el_cxc, physicsEvent.pel*el_cyc, physicsEvent.pel*el_czc, 0.00051099907 );  
  physicsEvent.detectedElectron = physicsEvent.el_LV; // include sqrt for Energy component .SetPxPyPzE( el_cxc, el_cyc, el_czc, physicsEvent.pel*physicsEvent.pel + 0.00051099907*0.00051099907 );
  //std::cout << " DE " << physicsEvent.detectedElectron.X() << " " <<  physicsEvent.detectedElectron.Y() << " " << physicsEvent.detectedElectron.Z() << " " << physicsEvent.detectedElectron.E() << std::endl;
  physicsEvent.virtualPhoton = physicsEvent.beamElectron - physicsEvent.detectedElectron;
  
  //std::cout << " set VP " << physicsEvent.virtualPhoton.X() << " " << physicsEvent.virtualPhoton.Y() << " " << physicsEvent.virtualPhoton.Z() << " " << physicsEvent.virtualPhoton.E() << std::endl;

  //std::cout << " Beam Energy in PEB " << physicsEvent.beamEnergy << " " << physicsEvent.beamElectron.Pz() << std::endl;  
  //std::cout << " Target Mass in PEB " << physicsEvent.targetMass << std::endl;
 
}

void PhysicsEventBuilder::setProtonKinematics( TLorentzVector tempLV ){
  //  physicsEvent.prp = tempLV.Vect().Mag();//calc.ProtonCorrectedMntm( tempLV.Vect().Mag() );
    //physicsEvent.prtheta = tempLV.Theta()*180./TMath::Pi();
    //physicsEvent.prphi = tempLV.Phi()*180./TMath::Pi(); 
}

void PhysicsEventBuilder::setProtonKin(Eventh22 tempevent, Int_t index ){
  physicsEvent.prp = calc.ProtonCorrectedMntm( tempevent.p[index] );
  Double_t *cos_corr = calc.CorrectedCosineCorrection( physicsEvent.run, tempevent, index, physicsEvent.prp );
  //Double_t *pr_ec_energy_corr = calc.ECSFCorrection( tempevent, index );

  Double_t pr_cxc = cos_corr[0];
  Double_t pr_cyc = cos_corr[1];
  Double_t pr_czc = sqrt(1 - pr_cxc*pr_cxc - pr_cyc*pr_cyc);
  
  physicsEvent.pr_vertex = cos_corr[3];
  physicsEvent.pr_dcsect = tempevent.dc_sect[index];
  physicsEvent.pr_thetaDC = acos( sqrt( 1 - tempevent.tl1_cx[index]*cos_corr[0] - tempevent.tl1_cy[index]*cos_corr[1] ))*(calc.RadtoDeg());
  physicsEvent.pr_phiDC = atan2( tempevent.tl1_cy[index], tempevent.tl1_cx[index] )*(calc.RadtoDeg());
  //physicsEvent.pr_ecei =  pr_ec_energy_corr[0];
  //physicsEvent.pr_eceo = pr_ec_energy_corr[1];
  //physicsEvent.pr_ectot = pr_ec_energy_corr[2];
  //physicsEvent.pr_ecmax = pr_ec_energy_corr[3];
   physicsEvent.pr_nphe = tempevent.nphe[index];
  
  physicsEvent.pr_LV.SetXYZM(  physicsEvent.prp*pr_cxc,  physicsEvent.prp*pr_cyc,  physicsEvent.prp*pr_czc, 0.938272 );
  physicsEvent.detectedProton = physicsEvent.pr_LV;
}


void PhysicsEventBuilder::setPhotonKin( Eventh22 tempevent ){
  //These LV are corrected
  physicsEvent.phhitid = tempevent.phdetectorID;
  physicsEvent.ph_LV = tempevent.ph_LV;
  physicsEvent.detectedPhoton = tempevent.ph_LV;
  //  std::cout<< " hit location is at " << physicsEvent.phhitid << std::endl;

}


void PhysicsEventBuilder::setGoodPhotonKinematics( TLorentzVector tempLV, Int_t tempphotontopology ){
  physicsEvent.php = tempLV.Vect().Mag();
  physicsEvent.phE = tempLV.E();
  physicsEvent.phtheta = tempLV.Theta()*180./TMath::Pi();
  physicsEvent.phphi = tempLV.Phi()*180./TMath::Pi();
  physicsEvent.phhitid = tempphotontopology;
}

void PhysicsEventBuilder::setECPhotonKinematics( TLorentzVector tempLV, Int_t tempindex ){
  
  physicsEvent.i_phec = tempindex;
  physicsEvent.phecLV[tempindex - 1 ] = tempLV;
  physicsEvent.phecp[tempindex - 1 ] = tempLV.Vect().Mag();
  physicsEvent.phectheta[tempindex - 1 ] = tempLV.Theta()*(180.0/TMath::Pi() );
  physicsEvent.phecphi[tempindex - 1 ] = tempLV.Phi()*(180.0/TMath::Pi() );
  // std::cout << " EC Photon " << tempindex << " " << tempLV.Vect().Mag() << " " << tempLV.Phi()*(180.0/TMath::Pi() ) << std::endl;
  
}

void PhysicsEventBuilder::setICPhotonKinematics( TLorentzVector tempLV, Int_t tempindex ){

  physicsEvent.i_phic = tempindex;
  physicsEvent.phicLV[tempindex - 1 ] = tempLV;
  physicsEvent.phicp[tempindex - 1 ] = tempLV.Vect().Mag();
  physicsEvent.phictheta[tempindex - 1 ] = tempLV.Theta()*(180.0/TMath::Pi() );
  physicsEvent.phicphi[tempindex - 1 ] = tempLV.Phi()*(180.0/TMath::Pi() );
  //  std::cout << " IC Photon " << tempindex << " " << tempLV.Vect().Mag() << " " << tempLV.Phi()*(180.0/TMath::Pi() ) << std::endl;
}


TLorentzVector PhysicsEventBuilder::returnPhoton( Int_t nphotEC, Int_t nphotIC ){
  //std::cout << "checking which photon to return, either IC or EC " << std::endl;
  //std::cout << " num of IC photons " << nphotIC << std::endl;
  //std::cout << " num of EC photons " << nphotEC << std::endl;
  
  TLorentzVector Ph_Vec;
  if(nphotEC>0){
    //  std::cout << " sorting EC photons " << std::endl;
    TMath::Sort(nphotEC,physicsEvent.phecp,isortEC,true);
  }
  if(nphotIC>0){
    //  std::cout << " sorting IC photons " << std::endl;
    TMath::Sort(nphotIC,physicsEvent.phicp,isortIC,true);
  } 
  GoodECPhotIndex = isortEC[0];
  GoodICPhotIndex = isortIC[0];
  
  if(nphotEC==0)
    {
      Ph_Vec=physicsEvent.phicLV[GoodICPhotIndex];      
      physicsEvent.IChit = true;
      physicsEvent.EChit = false;
      //   std::cout << " No EC hit, use IC photon " << std::endl;
      //   std::cout << " Mag of IC Photon Vector " <<Ph_Vec.Vect().Mag() << std::endl;
      
    }
  if(nphotIC==0)
    {
      Ph_Vec=physicsEvent.phecLV[GoodECPhotIndex];
      physicsEvent.IChit = false;
      physicsEvent.EChit = true;
      //   std::cout << " No IC hit, use EC photon " << std::endl;
      //   std::cout << " Mag of EC Photon Vector " <<Ph_Vec.Vect().Mag() << std::endl;

    }
  if(nphotIC > 0 && nphotEC > 0)
    {
      if(physicsEvent.phicLV[GoodICPhotIndex].E() > physicsEvent.phecLV[GoodECPhotIndex].E())
        {
          Ph_Vec=physicsEvent.phicLV[GoodICPhotIndex];
	   physicsEvent.IChit = true;
	   physicsEvent.EChit = false;
	   // std::cout << " Choose IC Photon b/c has higher energy " << std::endl;
	   //  std::cout << " Mag of IC Photon Vector " <<Ph_Vec.Vect().Mag() << std::endl;
	   
        }
      if(physicsEvent.phicLV[GoodICPhotIndex].E() < physicsEvent.phecLV[GoodECPhotIndex].E())
        {
          Ph_Vec=physicsEvent.phecLV[GoodECPhotIndex];
	  physicsEvent.IChit = false;
	  physicsEvent.EChit = true;
	  // std::cout << " Choose EC Photon b/c has higher energy " << std::endl;
	  // std::cout << " Mag of EC Photon Vector " <<Ph_Vec.Vect().Mag() << std::endl;

        }
      if(physicsEvent.phicLV[GoodICPhotIndex].E() == physicsEvent.phecLV[GoodECPhotIndex].E()){
	Ph_Vec = physicsEvent.phecLV[GoodECPhotIndex];
	//std::cout << " here " << std::endl;
	physicsEvent.IChit = true;
	physicsEvent.EChit = true;
	//	std::cout << " Choose IC and E Photon b/c have SAME energy " << std::endl;
	//	std::cout << " Mag of IC/EC Photon Vector " <<Ph_Vec.Vect().Mag() << std::endl;    

      }
    }
  return Ph_Vec;
}

bool PhysicsEventBuilder::ICPhoton(){
  // bool booltest = physicsEvent.IChit;
  //std::cout << " in icphoton " << booltest << std::endl;
  if( physicsEvent.IChit ){
    return true;
  }
  return false;

}

bool PhysicsEventBuilder::ECPhoton(){

   if( physicsEvent.EChit ){
    return true;
  }
  return false;
  
}

bool PhysicsEventBuilder::ICECPhoton(){

  if( physicsEvent.IChit && physicsEvent.EChit ){
    return true;
  }
  return false;
  
}

Int_t PhysicsEventBuilder::PhotonHitLocation(PhysicsEventBuilder tempbuild){
  if( tempbuild.ICPhoton() ){
    //std::cout << " IC Photon detected " << std::endl;
    hitloc = 1000;
  }
  if( tempbuild.ECPhoton() ){
    //std::cout << " EC Photon detected " << std::endl;
    hitloc = 2000;
  }
  if( tempbuild.ICPhoton() && tempbuild.ECPhoton() ){
    // std::cout<< " IC AND EC are both detected " << std::endl;
    hitloc = 5000;
  }
  physicsEvent.phhitid = hitloc;
  return hitloc; 
}
  

//void PhysicsEventBuilder::setVectors(TLorentzVector tempelectronLVf, TLorentzVector tempprotonLVf, TLorentzVector tempphotonLVf){
void PhysicsEventBuilder::setVectors(){

  /*  physicsEvent.detectedElectron = physicsEvent.el_LV;
  physicsEvent.finalEnergy = physicsEvent.detectedElectron.E();
  physicsEvent.virtualPhoton = physicsEvent.beamElectron - physicsEvent.detectedElectron;
  physicsEvent.detectedProton = physicsEvent.pr_LV;
  */

  // Set 4-Vectors
  /*  physicsEvent.detectedElectron = tempelectronLVf; 
  physicsEvent.finalEnergy = physicsEvent.detectedElectron.E(); 
  physicsEvent.virtualPhoton = physicsEvent.beamElectron - physicsEvent.detectedElectron;
  physicsEvent.detectedProton = tempprotonLVf;
  physicsEvent.detectedPhoton = tempphotonLVf;
  */
  physicsEvent.beamElectron3.SetXYZ( physicsEvent.beamElectron.X(), physicsEvent.beamElectron.Y(), physicsEvent.beamElectron.Z() );
  physicsEvent.detectedElectron3.SetXYZ( physicsEvent.detectedElectron.X(), physicsEvent.detectedElectron.Y(), physicsEvent.detectedElectron.Z() );
  physicsEvent.targetParticle3.SetXYZ( physicsEvent.targetParticle3.X(), physicsEvent.targetParticle3.Y(), physicsEvent.targetParticle3.Z() );
  physicsEvent.virtualPhoton3.SetXYZ( physicsEvent.virtualPhoton.X(), physicsEvent.virtualPhoton.Y(), physicsEvent.virtualPhoton.Z() );
  // physicsEvent.recoilProton3.SetXYZ(  tempprotonLVf.X(), tempprotonLVf.Y(), tempprotonLVf.Z() );
  // physicsEvent.realPhoton3.SetXYZ( tempphotonLVf.X(), tempphotonLVf.Y(), tempphotonLVf.Z() );

  // ep -> epX where X should be the photon
  /*  physicsEvent.missingLV_epg = physicsEvent.beamElectron + physicsEvent.targetParticle - tempelectronLVf - tempprotonLVf - tempphotonLVf;
  physicsEvent.missingLV_ep = physicsEvent.beamElectron + physicsEvent.targetParticle - tempelectronLVf - tempprotonLVf;
  physicsEvent.missingLV_eg = physicsEvent.beamElectron + physicsEvent.targetParticle - tempelectronLVf - tempphotonLVf;
  physicsEvent.missingLV_e  = physicsEvent.beamElectron + physicsEvent.targetParticle - physicsEvent.detectedElectron;
  */
}

void PhysicsEventBuilder::setKinematics(){
  // Get the numbers
  //physicsEvent.run = currentrun;
  //std::cout << currentrun << std::endl;

  // To match Biselli results 
  //  std::cout << "VP in SetKin " << physicsEvent.virtualPhoton.X() << " " << physicsEvent.virtualPhoton.Y() << " " << physicsEvent.virtualPhoton.Z() << " " << physicsEvent.virtualPhoton.E() << std::endl;

  physicsEvent.Q2 = -(physicsEvent.virtualPhoton.Mag2());  

  physicsEvent.xB = physicsEvent.Q2/ (2 * 0.938272 * physicsEvent.virtualPhoton.E() );
  physicsEvent.T = (physicsEvent.virtualPhoton - physicsEvent.ph_LV).Mag2();
  physicsEvent.Tp = (physicsEvent.targetParticle - physicsEvent.detectedProton).Mag2();
  physicsEvent.mm2epg = (physicsEvent.beamElectron + physicsEvent.targetParticle - physicsEvent.detectedElectron - physicsEvent.detectedProton - physicsEvent.ph_LV).Mag2();
  physicsEvent.mm = (physicsEvent.beamElectron + physicsEvent.targetParticle - physicsEvent.detectedElectron - physicsEvent.detectedProton).Mag2();
  physicsEvent.protCM.SetXYZM(physicsEvent.detectedProton.X(), physicsEvent.detectedProton.Y(), physicsEvent.detectedProton.Z() , 0.938272 );
  
  TVector3 rotax(0.,1.,0.);
  TVector3 rotax2(0.,0.,1.);
  Double_t angle = physicsEvent.virtualPhoton.Theta();
  Double_t angle2 = physicsEvent.virtualPhoton.Phi();
  physicsEvent.protCM.Rotate(-angle2,rotax2);
  physicsEvent.protCM.Rotate(-angle, rotax);
  TVector3 beta(0.,0., physicsEvent.virtualPhoton.Vect().Mag()/(physicsEvent.virtualPhoton.T() + 0.938272 ));
  physicsEvent.protCM.Boost(-beta);
  physicsEvent.epsilon = 1./(1. + 2*pow( physicsEvent.virtualPhoton.Vect().Mag(),2)/physicsEvent.Q2*pow(tan(physicsEvent.detectedElectron.Theta()/2.),2));

  physicsEvent.w = ((physicsEvent.beamElectron + physicsEvent.targetParticle) - physicsEvent.detectedElectron).Mag();
  physicsEvent.deltaTheta = (physicsEvent.ph_LV).Angle( ((physicsEvent.beamElectron + physicsEvent.targetParticle) - physicsEvent.detectedElectron - physicsEvent.detectedProton).Vect() );
  physicsEvent.deltaPhi = (physicsEvent.ph_LV).Phi() - (( physicsEvent.beamElectron + physicsEvent.targetParticle) - physicsEvent.detectedElectron - physicsEvent.detectedProton).Phi();
 
  physicsEvent.leptonicPlane = physicsEvent.beamElectron.Vect().Cross(physicsEvent.detectedElectron.Vect());
  physicsEvent.hadronicPlane  = physicsEvent.detectedProton.Vect().Cross(physicsEvent.ph_LV.Vect());
  physicsEvent.phi = physicsEvent.leptonicPlane.Angle(physicsEvent.hadronicPlane);
  if( (physicsEvent.leptonicPlane.Dot(physicsEvent.ph_LV.Vect() )) < 0 ){
    physicsEvent.phi = (2*3.14159) - physicsEvent.phi;
  }
  

  physicsEvent.n_pro_vph = ((physicsEvent.detectedProton.Vect()).Cross(physicsEvent.virtualPhoton.Vect())).Unit();
  physicsEvent.n_pro_ph = ((physicsEvent.detectedProton.Vect()).Cross(physicsEvent.ph_LV.Vect())).Unit();
  physicsEvent.dephi = physicsEvent.n_pro_vph.Angle(physicsEvent.n_pro_ph);
  if( (physicsEvent.n_pro_vph.Dot(physicsEvent.detectedPhoton.Vect())) < 0. ){
    physicsEvent.dephi = -1*physicsEvent.dephi;
  }
  
  physicsEvent.perpX = ((physicsEvent.beamElectron + physicsEvent.targetParticle) - physicsEvent.detectedElectron - physicsEvent.detectedProton - physicsEvent.ph_LV).Px();
  physicsEvent.perpY = ((physicsEvent.beamElectron + physicsEvent.targetParticle) - physicsEvent.detectedElectron - physicsEvent.detectedProton - physicsEvent.ph_LV).Py();

  physicsEvent.pPerp = sqrt(physicsEvent.perpX*physicsEvent.perpX + physicsEvent.perpY*physicsEvent.perpY);


  // End of the kin variables calculated using biselli code

  /*  physicsEvent.qq = 4*(physicsEvent.beamEnergy*physicsEvent.finalEnergy)*TMath::Power(TMath::Sin(physicsEvent.detectedElectron.Theta()/2.0),2);
  physicsEvent.xbj = physicsEvent.qq/(2*physicsEvent.targetParticle.E()*physicsEvent.virtualPhoton.E());
  physicsEvent.nu = physicsEvent.virtualPhoton.E();
  physicsEvent.w = TMath::Sqrt(physicsEvent.targetMass*physicsEvent.targetMass + 2*physicsEvent.targetMass*physicsEvent.nu - physicsEvent.qq );
  physicsEvent.t_proton = (physicsEvent.detectedProton - physicsEvent.targetParticle).M2();
  physicsEvent.t_photon = (physicsEvent.beamElectron - physicsEvent.detectedElectron - physicsEvent.detectedPhoton).M2();

  physicsEvent.n_lepton = (physicsEvent.detectedElectron3.Cross(physicsEvent.beamElectron3)).Unit();
  physicsEvent.n_hadron = (physicsEvent.recoilProton3.Cross(physicsEvent.virtualPhoton3)).Unit(); // ? vhadron or no
  physicsEvent.hadronPP = (physicsEvent.recoilProton3.Cross(physicsEvent.realPhoton3)).Unit();
  physicsEvent.n_VPRP   = (physicsEvent.realPhoton3.Cross(physicsEvent.virtualPhoton3)).Unit();
  physicsEvent.deltaphi = physicsEvent.n_hadron.Angle(physicsEvent.hadronPP);

  physicsEvent.hadron_hadlep_Phi = TMath::ACos(physicsEvent.n_hadron.Dot(physicsEvent.n_lepton))*(180.0/TMath::Pi());
  physicsEvent.hadron_hadVPRP_Phi = TMath::ACos(physicsEvent.n_hadron.Dot(physicsEvent.n_VPRP))*(180.0/TMath::Pi());
  physicsEvent.PhiPlaneDifference = physicsEvent.hadron_hadlep_Phi - physicsEvent.hadron_hadVPRP_Phi ; //physicsEvent.hadron_vph_Phi - physicsEvent.hadron_rph_Phi;

  if( physicsEvent.n_hadron.Dot(physicsEvent.hadronPP) < 0.0 ) physicsEvent.deltaphi = -1*physicsEvent.deltaphi;
  //physicsEvent.deltaphi = (physicsEvent.n_hadron.Phi() - physicsEvent.hadronPP.Phi())*180./TMath::Pi();
  physicsEvent.n_lepton_theta = physicsEvent.n_lepton.Theta()*(180.0/TMath::Pi() );
  physicsEvent.n_lepton_phi = physicsEvent.n_lepton.Phi()*(180.0/TMath::Pi() );
  physicsEvent.n_hadron_theta = physicsEvent.hadronPP.Theta()*(180.0/TMath::Pi() );
  physicsEvent.n_hadron_phi = physicsEvent.hadronPP.Phi()*(180.0/TMath::Pi() );
  //add delta theta for photons

  physicsEvent.phi_pr = calc.RadtoDeg()*physicsEvent.n_lepton.Angle(physicsEvent.n_hadron);
  physicsEvent.phi_pr_asym = physicsEvent.phi_pr;
  physicsEvent.phi_ph = calc.RadtoDeg()*physicsEvent.n_lepton.Angle(physicsEvent.hadronPP);
  

  if( physicsEvent.n_lepton.Dot(physicsEvent.recoilProton3) > 0.0 ){
    physicsEvent.phi_pr = 360.0 - physicsEvent.phi_pr;
  }
  if( physicsEvent.n_lepton.Dot(physicsEvent.realPhoton3) < 0.0 ){
    physicsEvent.phi_ph = 360.0 - physicsEvent.phi_ph; 
  }

  physicsEvent.anglexg = (calc.RadtoDeg()*physicsEvent.realPhoton3.Angle(physicsEvent.missingLV_ep.Vect()));//*180./TMath::Pi();
  
  physicsEvent.anglehphg = calc.RadtoDeg()*physicsEvent.n_hadron.Angle(physicsEvent.hadronPP);
  if(physicsEvent.hadronPP.Dot(physicsEvent.recoilProton3) < 0.0 ){
    physicsEvent.anglehphg = -physicsEvent.anglehphg;
  }

  physicsEvent.xbal = physicsEvent.missingLV_epg.X();
  physicsEvent.ybal = physicsEvent.missingLV_epg.Y();
  physicsEvent.zbal = physicsEvent.missingLV_epg.Z();
  physicsEvent.ebal = physicsEvent.missingLV_epg.E();
  
  physicsEvent.mm2epg = physicsEvent.missingLV_epg.Mag2();
  physicsEvent.mm2ep = physicsEvent.missingLV_ep.Mag2();
  physicsEvent.mm2eg = physicsEvent.missingLV_eg.Mag2();
  */
}

void PhysicsEventBuilder::setHelicity( Eventh22 tempevent ){
//void PhysicsEventBuilder::setHelicity( Int_t temphel ){

  if( physicsEvent.periodid != "MC" ){
    // Account for insertion of Wave Plate
    // When wave plate is inserted (0), the ihel value must be flipped.
    Int_t eventhelicity = tempevent.ihel;
    physicsEvent.helic = eventhelicity;//tempevent.ihel;
    //std::cout << "Inside physicsevenbuilder - > Event helicity " <<  eventhelicity << std::endl;
    //    std::cout << " ________------------_______" << std::endl;
    //std::cout << " physicsEventhelic " << physicsEvent.helic << std::endl;
    //std::cout << " waveplate status " << physicsEvent.waveplatepos << std::endl;
    if( physicsEvent.waveplatepos == 0 ){
      physicsEvent.helic = !(physicsEvent.helic);
      //std::cout << " waveplate in " << physicsEvent.helic << std::endl;
    }
    if( physicsEvent.run <= 59442 ){//for PARTA the helicity needs to be flipped again
      //std::cout << "Because this is part A we need to flip the helicity again from " << physicsEvent.helic << std::endl;
      physicsEvent.helic = !(physicsEvent.helic);
      //std::cout << " to " << physicsEvent.helic << std::endl;
    }
    else{
      physicsEvent.helic = tempevent.ihel;
      //std::cout << " waveplate out " << physicsEvent.helic << std::endl;
    }
  }
  else if( physicsEvent.periodid == "MC" ){
    physicsEvent.helic = tempevent.ihel;
  }
  //std::cout << " final helicity " << physicsEvent.helic << std::endl;
}


TLorentzVector PhysicsEventBuilder::setParticleLV( TString tempparticle, Eventh22 tempevent, Int_t tempindex ){

  selectron = "electron";
  sproton = "proton";
  sphoton = "photon";
  sicphoton = "icphoton";
  TLorentzVector incidentpartLV(0,0,0,0);
 
  if( tempparticle == selectron ){
    
    cmntm = calc.ElectronCorrectedMntm( tempevent.p[tempindex] );
    Double_t *cosine_corrected = calc.CorrectedCosineCorrection( physicsEvent.run, tempevent, tempindex, cmntm);
    Double_t cx = cosine_corrected[0];
    Double_t cy = cosine_corrected[1];
    Double_t cz = cosine_corrected[2];
    p4 = cmntm;
    incidentpartLV.SetXYZM( cmntm*cx, cmntm*cy, cmntm*sqrt(1-cx*cx-cy*cy), 0.000511 );  
  }
  
  if( tempparticle == sproton ){
    cmntm = calc.ProtonCorrectedMntm( tempevent.p[tempindex] );

    Double_t *cosine_corrected = calc.CorrectedCosineCorrection( physicsEvent.run, tempevent, tempindex, cmntm);
    Double_t cx = cosine_corrected[0];
    Double_t cy = cosine_corrected[1];
    Double_t cz = cosine_corrected[2];
    mass = 0.938272;
    p4 = sqrt( mass*mass + cmntm*cmntm );
    incidentpartLV.SetXYZM(cmntm*cx, cmntm*cy, cmntm*sqrt(1-cx*cx-cy*cy), mass );  
  }
  
  /*if( tempparticle == sphoton ){
    cmntm = tempevent.p[tempindex];
    px = tempevent.cx[tempindex];
    py = tempevent.cy[tempindex];
    pz = sqrt( 1 - px*px - py*py );
    p4 = cmntm;
    incidentpartLV.SetPxPyPzE(cmntm*px, cmntm*py, cmntm*pz, p4 );  
  }
  if( tempparticle == sicphoton ){
    // Original xx and yy hit position without correcting for rastering of the beam
    Double_t xx_o = tempevent.xc[tempindex];
    Double_t yy_o = tempevent.yc[tempindex];

    /* Variables xx and yy stand for the corrected x and y position
       by taking into account the rastering of the beam across the target.
       xy_c is an array of length two containing the x and y values to correct by
    */
  /*    Double_t *xy_c = calc.RasterCorrection( physicsEvent.run, tempevent, tempindex);
    Double_t xx = xy_c[0];//xx_o - xy_c[0];
    Double_t yy = xy_c[1];//yy_o - xy_c[1];
    TVector3 icph3V;
    icph3V.SetX(xx);
    icph3V.SetY(yy);
    icph3V.SetZ(-tempevent.vz[0]); // assuming the vertex of ic photon at location of electron's vertex.
    Double_t ph_etc = tempevent.etc[tempindex];
    
    incidentpartLV.SetPxPyPzE(ph_etc*TMath::Sin(icph3V.Theta())*TMath::Cos(icph3V.Phi()),
			      ph_etc*TMath::Sin(icph3V.Theta())*TMath::Sin(icph3V.Phi()),
			      ph_etc*TMath::Cos(icph3V.Theta()),
			      ph_etc);
  }

  */
    
  return incidentpartLV;

  // TLorentzVector incidentpartLV(cmntm*px, cmntm*py, cmntm*pz, p4 );  
  //return incidentpartLV;
}



