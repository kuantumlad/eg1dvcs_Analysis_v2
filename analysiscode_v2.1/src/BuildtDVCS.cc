#define buildtdvcs_cxx

#include "../include/BuildtDVCS.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/PhysicsEvent.h"
#include "../include/EventPID.h"
#include "TTree.h"
#include "TMath.h"
#include "TBranch.h"
#include "TString.h"
#include "TLorentzVector.h"


#include <iostream>

BuildtDVCS::BuildtDVCS(){

  RunNumber = 0;
  pol_sign = 0;
  beampol = 0;
  helicity = 0;
  wp_status =  0;
  fc0 = 0;
  fc1 = 0;

  fel_px = 0;
  fel_py = 0;
  fel_pz = 0;
  fel_E = 0;
  fel_vz = 0;
  fel_dcsect = 0;
  fel_thetadc = 0;
  fel_ecmax = 0;

  fpr_px = 0;
  fpr_py = 0;
  fpr_pz = 0;
  fpr_E = 0;
  fpr_vz = 0;
  fpr_dcsect = 0;
  fpr_thetadc = 0;
  fpr_ecmax = 0;

  fph_px = 0;
  fph_py = 0;
  fph_pz = 0;
  fph_E = 0;
  fph_ID = 0;

  Q2 = 0;
  Xbj = 0;
  t_Pr = 0;
  t_Ph = 0;
  W = 0;
  mm = 0;
  mm2_epg = 0;
  AngleXg = 0;
  //  Delta_Phi = tempphysics.deltaphi;
  Phi_Pr_Asym = 0;
  Delta_phi = 0;
  Phi = 0;
  Xbal = 0;
  Ybal = 0;
  Zbal = 0;
  Ebal = 0;

}

BuildtDVCS::~BuildtDVCS(){

}
void BuildtDVCS::InitTree(){

  tDVCS = new TTree("tDVCS","my final DVCS Event Tree");
  tDVCS->SetDirectory(0);

  tDVCS->Branch("RunNumber", &RunNumber);
  tDVCS->Branch("PeriodID", &PeriodID, 16000,0);
  tDVCS->Branch("TargetType", &TargetType, 16000,0);  
  tDVCS->Branch("pol_sign", &pol_sign);
  tDVCS->Branch("wp_status",&wp_status);
  tDVCS->Branch("fc0",&fc0);
  tDVCS->Branch("fc1",&fc1);
  tDVCS->Branch("b_energy", &b_energy);
  tDVCS->Branch("helicity", &helicity);
  tDVCS->Branch("TarPol", &TarPol);

  tDVCS->Branch("Q2", &Q2);
  tDVCS->Branch("Xbj", &Xbj);
  tDVCS->Branch("W", &W);
  tDVCS->Branch("t_Pr", &t_Pr);
  tDVCS->Branch("t_Ph", &t_Ph);
  tDVCS->Branch("Phi_Pr_Asym",&Phi_Pr_Asym);
  tDVCS->Branch("Delta_phi", &Delta_phi);
  tDVCS->Branch("Phi", &Phi);
  tDVCS->Branch("AngleXg", &AngleXg);
  tDVCS->Branch("Xbal", &Xbal);
  tDVCS->Branch("Ybal", &Ybal);
  tDVCS->Branch("Ebal", &Ebal);
  tDVCS->Branch("mm2_epg", &mm2_epg);
  tDVCS->Branch("mm", &mm);

  tDVCS->Branch("fel_px", &fel_px);
  tDVCS->Branch("fel_py", &fel_py);
  tDVCS->Branch("fel_pz", &fel_pz);
  tDVCS->Branch("fel_E", &fel_E);
  tDVCS->Branch("fel_vz", &fel_vz);
  tDVCS->Branch("fel_thetadc", &fel_thetadc);
  tDVCS->Branch("fel_dcsect", &fel_dcsect);

  tDVCS->Branch("fpr_px", &fpr_px);
  tDVCS->Branch("fpr_py", &fpr_py);
  tDVCS->Branch("fpr_pz", &fpr_pz);
  tDVCS->Branch("fpr_E", &fpr_E);
  tDVCS->Branch("fpr_vz", &fpr_vz);
  tDVCS->Branch("fpr_thetadc", &fpr_thetadc);
  tDVCS->Branch("fpr_dcsect", &fpr_dcsect);

  tDVCS->Branch("fph_px", &fph_px);
  tDVCS->Branch("fph_py", &fph_py);
  tDVCS->Branch("fph_pz", &fph_pz);
  tDVCS->Branch("fph_E",  &fph_E);
  tDVCS->Branch("fph_ID", &fph_ID);
  //tDVCS->Branch("mm2_eg", &mm2_eg);
}

void BuildtDVCS::Fill( EventPID tempphysics ){
 
  RunNumber = tempphysics.run;
  PeriodID = tempphysics.periodID;
  helicity  = tempphysics.beamHelicity;
  pol_sign = tempphysics.polsign;
  TargetType = tempphysics.targetType;
  TarPol = tempphysics.targetPolarization;
  wp_status = tempphysics.wpstatus;
  b_energy = tempphysics.beamEnergy;
  fc0 = tempphysics.FC0;
  fc1 = tempphysics.FC1;

  fel_px = tempphysics.el_px;
  fel_py = tempphysics.el_py;
  fel_pz = tempphysics.el_pz;
  fel_E = tempphysics.el_E;
  fel_vz = tempphysics.el_vertex;
  fel_dcsect = tempphysics.el_DCsect;
  fel_thetadc = tempphysics.el_thetadc;

  fpr_px = tempphysics.pr_px;
  fpr_py = tempphysics.pr_py;
  fpr_pz = tempphysics.pr_pz;
  fpr_E = tempphysics.pr_E;
  fpr_vz = tempphysics.pr_vertex;
  fpr_dcsect = tempphysics.pr_DCsect;
  fpr_thetadc = tempphysics.pr_thetadc;

  fph_px = tempphysics.ph_px;
  fph_py = tempphysics.ph_py;
  fph_pz = tempphysics.ph_pz;
  fph_E = tempphysics.ph_E;
  fph_ID = tempphysics.photonTopology;
  
  Q2 = tempphysics.qq;
  Xbj = tempphysics.xb;
  t_Pr = tempphysics.t_;
  t_Ph = tempphysics.tp_; 
  W = tempphysics.w_;
  mm = tempphysics.MM;
  mm2_epg = tempphysics.MM2epg;
  AngleXg = tempphysics.deltatheta;
  //  Delta_Phi = tempphysics.deltaphi;
  Phi_Pr_Asym = tempphysics.Dephi;
  Delta_phi = tempphysics.delta_phi;
  Phi = tempphysics.phi_;
  Xbal = tempphysics.perpx;
  Ybal = tempphysics.perpy;
  Ebal = tempphysics.pPerp;
  //calcph_theta = tempphysics.calcphtheta;
  
  tDVCS->Fill();
}

void BuildtDVCS::WriteToTree(){

  tDVCS->Write();
  tDVCS->AutoSave();
}

void BuildtDVCS::PrintTree(){

  tDVCS->Scan();
  
}
