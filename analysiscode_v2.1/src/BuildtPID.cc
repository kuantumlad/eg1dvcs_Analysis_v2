#define buildtPID

#include "../include/BuildtPID.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/PhysicsEvent.h"

#include "TTree.h"
#include "TMath.h"
#include "TBranch.h"
#include "TString.h"
#include "TLorentzVector.h"

BuildtPID::BuildtPID(){

  run = 0;
  beamEnergy = 0.0;
  beamHelicity = 0.0;
  targetPolarization = 0.0;
  //targetPos = 0.0;
  //  periodID = new TString();
  wpstatus = 0.0;
  FC0 = 0.0;
  FC1 = 0.0;

  el_px = 0.0;
  el_py = 0.0;
  el_pz = 0.0;
  el_E = 0.0;
  el_vertex = 0.0;
  el_dcsect = 0.0;
  el_thetadc = 0.0;
  el_phidc = 0.0;
  el_ecei = 0.0;
  el_eceo = 0.0;
  el_ectot = 0.0;
  el_ecmax = 0.0;
  el_nphe = 0.0;

  pr_px = 0.0;
  pr_py = 0.0;
  pr_pz = 0.0;
  pr_E = 0.0;
  pr_vertex = 0.0;
  pr_dcsect = 0.0;
  pr_thetadc = 0.0;
  pr_phidc = 0.0;
  pr_ecei = 0.0;
  pr_eceo = 0.0;
  pr_ectot = 0.0;
  pr_ecmax = 0.0;
  pr_nphe = 0.0;

  photonTopology = 0;
  ph_px = 0.0;
  ph_py = 0.0;
  ph_pz = 0.0;
  ph_E = 0.0;

  //__________________________
  //
  //Added 3/10/2017
  //__________________________
  el_vertex = 0.0;
  el_dcsect = 0;
  el_thetadc = 0.0;
  el_phidc = 0.0;
  el_ecei = 0.0;
  el_eceo = 0.0;
  el_ectot = 0.0;
  el_ecmax =0.0;
  el_nphe = 0;
  //  el_LVx = 0.0;
  //el_LVy = 0.0;
  //el_LVz = 0.0;
  //el_LVm = 0.0;

  pr_vertex = 0.0;
  pr_dcsect = 0;
  pr_thetadc = 0.0;
  pr_phidc = 0.0;
  pr_ecei = 0.0;
  pr_eceo = 0.0;
  pr_ectot = 0.0;
  pr_ecmax =0.0;
  pr_nphe = 0;
  //pr_LVx = 0.0;
  //pr_LVy = 0.0;
  //pr_LVz = 0.0;
  //pr_LVm = 0.0;
  qq = 0;
  xb = 0;// tempphysics.xB;
  t_ =  0;//tempphysics.T;
  w_ =  0;//tempphysics.w;
  tp_ = 0;// tempphysics.Tp;
  MM =  0;//tempphysics.mm;
  MM2epg=  0;//tempphysics.mm2epg;
  eps = 0;// tempphysics.epislon;
  deltatheta =  0;//tempphysics.deltaTheta;
  delta_phi =  0;//tempphysics.deltaPhi;
  phi_ =  0;//tempphysics.phi;
  Dephi =  0;//tempphysics.dephi;
  perpx_ =  0;//tempphysics.perpX;
  perpy_ =  0;//tempphysics.perpY;
  pperp_ = 0;// tempphysics.pPerp;



  // ecph_px = 0.0;
  // ecph_py = 0.0;
  // ecph_pz = 0.0;
  // ecph_E = 0.0;

}

BuildtPID::~BuildtPID(){

}


void BuildtPID::InitPIDTree(){

  tPID = new TTree("tPID","my PID Tree");
  tPID->SetDirectory(0);

  tPID->Branch("run", &run);
  tPID->Branch("periodID", &periodID,16000,0);
  tPID->Branch("beamEnergy", &beamEnergy);  
  tPID->Branch("beamHelicity", &beamHelicity);
  tPID->Branch("targetType", &targetType,16000,0);
  tPID->Branch("targetPolarization", &targetPolarization);
  //tPID->Branch("targetPos", &targetPos);
  tPID->Branch("wpstatus", &wpstatus);
  tPID->Branch("FC0", &FC0);
  tPID->Branch("FC1", &FC1);
  tPID->Branch("el_px", &el_px );
  tPID->Branch("el_py", &el_py);
  tPID->Branch("el_pz", &el_pz);
  tPID->Branch("el_E", &el_E);
  tPID->Branch("el_vertex", &el_vertex );
  tPID->Branch("el_DCsect", &el_dcsect );
  tPID->Branch("el_thetadc", &el_thetadc );
  tPID->Branch("el_phidc", &el_phidc );
  //tPID->Branch("el_ecei", &el_ecei );
  //tPID->Branch("el_eceo", &el_eceo );
  //tPID->Branch("el_ectot", &el_ectot );
  //tPID->Branch("el_ecmax", &el_ecmax );
  tPID->Branch("el_nphe",&el_nphe);

  tPID->Branch("pr_px", &pr_px);
  tPID->Branch("pr_py", &pr_py);
  tPID->Branch("pr_pz", &pr_pz);
  tPID->Branch("pr_E", &pr_E);
  tPID->Branch("pr_vertex", &pr_vertex );
  tPID->Branch("pr_DCsect", &pr_dcsect );
  tPID->Branch("pr_thetadc", &pr_thetadc );
  tPID->Branch("pr_phidc", &pr_phidc );
  //tPID->Branch("pr_ecei", &pr_ecei );
  //tPID->Branch("pr_eceo", &pr_eceo );
  //tPID->Branch("pr_ectot", &pr_ectot );
  //tPID->Branch("pr_ecmax", &pr_ecmax );
  tPID->Branch("pr_nphe",&pr_nphe);

  tPID->Branch("photonTopology", &photonTopology);
  tPID->Branch("ph_px", &ph_px);
  tPID->Branch("ph_py", &ph_py);
  tPID->Branch("ph_pz", &ph_pz);
  tPID->Branch("ph_E", &ph_E);

  tPID->Branch("qq",&qq);
  tPID->Branch("xb",&xb);
  tPID->Branch("t_",&t_);
  tPID->Branch("w_",&w_);
  tPID->Branch("tp_",&tp_);
  tPID->Branch("MM",&MM);
  tPID->Branch("MM2epg",&MM2epg);
  tPID->Branch("eps",&eps);
  tPID->Branch("deltatheta",&deltatheta);
  tPID->Branch("delta_phi",&delta_phi);
  tPID->Branch("phi_",&phi_);
  tPID->Branch("Dephi",&Dephi);
  tPID->Branch("perpx",&perpx_);
  tPID->Branch("perpy",&perpy_);
  tPID->Branch("pPerp",&pperp_);


 
}

void BuildtPID::Fill( PhysicsEvent tempphysics ){

  run = tempphysics.run;
  periodID = tempphysics.periodid;
  beamEnergy = tempphysics.beamElectron.E();
  beamHelicity  = tempphysics.helic;
  pol_sign = tempphysics.polsign;
  targetType = tempphysics.targettype;
  targetPolarization = tempphysics.tpol;
  wpstatus = tempphysics.waveplatepos;
  FC0 = tempphysics.fc0;
  FC1 = tempphysics.fc1;

  
  el_px = tempphysics.detectedElectron.X();
  el_py = tempphysics.detectedElectron.Y();
  el_pz = tempphysics.detectedElectron.Z();
  el_E = tempphysics.detectedElectron.E();
  el_vertex = tempphysics.el_vertex;
  el_dcsect = tempphysics.el_dcsect;
  el_thetadc = tempphysics.el_thetaDC;
  el_phidc = tempphysics.el_phiDC;
  el_ecei = tempphysics.el_ecei;
  el_eceo = tempphysics.el_eceo;
  el_ectot = tempphysics.el_ectot;
  el_ecmax = tempphysics.el_ecmax;
  el_nphe = tempphysics.el_nphe;

  pr_px = tempphysics.detectedProton.X();
  pr_py = tempphysics.detectedProton.Y();
  pr_pz = tempphysics.detectedProton.Z();
  pr_E = tempphysics.detectedProton.E();
  pr_vertex = tempphysics.pr_vertex;
  pr_dcsect = tempphysics.pr_dcsect;
  pr_thetadc = tempphysics.pr_thetaDC;
  pr_phidc = tempphysics.pr_phiDC;
  pr_ecei = tempphysics.pr_ecei;
  pr_eceo = tempphysics.pr_eceo;
  pr_ectot = tempphysics.pr_ectot;
  pr_ecmax = tempphysics.pr_ecmax;
  pr_nphe = tempphysics.pr_nphe;

  photonTopology = tempphysics.phhitid;
  ph_px = tempphysics.detectedPhoton.X();
  ph_py = tempphysics.detectedPhoton.Y();
  ph_pz = tempphysics.detectedPhoton.Z();
  ph_E = tempphysics.detectedPhoton.E();

  qq = tempphysics.Q2;
  xb = tempphysics.xB;
  t_ = tempphysics.T;
  tp_ = tempphysics.Tp;
  w_ = tempphysics.w;
  //tp = tempphysics.Tp;
  MM = tempphysics.mm;
  MM2epg= tempphysics.mm2epg;
  eps = tempphysics.epsilon;
  deltatheta = tempphysics.deltaTheta;
  delta_phi = tempphysics.deltaPhi;
  phi_ = tempphysics.phi;
  Dephi = tempphysics.dephi;
  perpx_ = tempphysics.perpX;
  perpy_ = tempphysics.perpY;
  pperp_ = tempphysics.pPerp;

  tPID->Fill();
}

  
void BuildtPID::WriteToTree(){
  
  tPID->Write();
  tPID->AutoSave();
}
		
void BuildtPID::PrintTree(){
		  
  tPID->Scan();
 
}




 
