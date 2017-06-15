#define pidhistograms_cxx

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/Calculator.h"
#include "../include/PIDHistograms.h"

#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TImage.h"
#include "TLine.h"
#include "TAttMarker.h"
#include "TColor.h"
#include "TStyle.h"
#include <TGeoPolygon.h>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <THnSparse.h>
#include <vector>

PIDHistograms::PIDHistograms(){
  //Default Constructor
  //  file = tempfile;

  //  foldernames.push_back("hns_electron");
  //foldernames.push_back("hns_proton");
  //foldernames.push_back("hns_ecphoton");
  //foldernames.push_back("hns_icphoton");

  // for (int i = 0; i < foldernames.size() ; i++){
  // file.mkdir(foldernames[i]);
  //}
  //  std::vector< Double_t> particleprop;


}

PIDHistograms::PIDHistograms(TFile *tempfile){

  //std::vector< Double_t> particleprop;

}


PIDHistograms::~PIDHistograms(){


}


void PIDHistograms::CreateDirectories( TFile *tempoutfile ){

 //  file = tempfile;

  foldernames.push_back("hns_electron");
  foldernames.push_back("hns_goodelectron");
  foldernames.push_back("hns_proton");
  foldernames.push_back("hns_goodproton");
  foldernames.push_back("hns_ecphoton");
  foldernames.push_back("hns_goodecphoton");
  foldernames.push_back("hns_icphoton");
  foldernames.push_back("hns_goodicphoton");

  for (int i = 0; i < foldernames.size() ; i++){
    tempoutfile->mkdir(foldernames[i]);
  }

  putoutfile = tempoutfile;

}

void PIDHistograms::AddCorrections( Calculator calculate ){

  calculator = calculate;

}

void PIDHistograms::InitiateAllHistograms(){

  nel_cuts = 9;//cutmanager.appliedelectroncuts.size();
  npr_cuts = 5;//cutmanager.appliedprotoncuts.size();
  necph_cuts = 7;//cutmanager.appliedphotoncuts.size();
  nicph_cuts = 3;//cutmanager.appliedicphotoncuts.size();
  electronD1 = 13;
  protonD1 = 8;
  ecphD1 = 7;
  icphD1 = 3;
  
  electronD2 = 4;
  Int_t electronbin1[13] = {100,100,100,100,100,100,100,100,100,100,100,200,200};
  Int_t electronbin2[4] = {100, 100,100,100};
  Int_t protonbin1[8] = {100,100,100,100,100,100,100,100};
  Int_t ecphbin1[7] = {100,100,100,100,100,200,200};
  Int_t icphbin1[3] = {100,100,100};
  //Order of electronsparse1 is mntm, ecinner, ecoutter, nphe, timing, theta, phi, etot, ic x, ic y, z_corr, ec_x, ec_y  - just added the ic x for the 
  Double_t electronmin1[13] = { 0.0, 0.0, 0.0, 0, -3.0, 0.0, -200.0, 0.0, -50.0, -50.0, -20.0, -100.0, -100.0 };
  Double_t electronmax1[13] = { 7.0, 0.3, 0.2, 300.0, 5.0, 50.0, 200.0, 5.5, 50.0, 50.0, 20.0, 100.0, 100.0 };
  //Order of protonsparse is mntm, zvertex, h22.b, theta, phi, -> later ic shadow x, ic shadow y  
  Double_t protonmin1[8] = { 0.0, -8.0, 0.0, 0.0, -200.0, -50.0, -50.0, -20.0 };
  Double_t protonmax1[8] = { 5.5, 8.0, 1.6, 50.0, 200.0, 50.0, 50.0, 20.0 };
  //Order of ecphotonsparse is energydep, h22.b, mntm, theta, phi -> add ec hit and ic shad
  Double_t ecphmin1[7] = { 0.0, 0.0, 0.0, 0.0, -200.0, -100.0, -100.0 };
  Double_t ecphmax1[7] = { 6.0, 1.5, 6.0, 50.0, 200.0, 100.0, 100.0 };
  //Order of icphotonsparse is energy, theta, phi, -> add ic hit later
  Double_t icphmin1[3] = {0.0, -20.0, -20.0};
  Double_t icphmax1[3] = {6.0, 20.0, 20.0 };
  
  for (int ncuts = 0; ncuts < nel_cuts; ++ncuts) {
    hns_electron.push_back(new THnSparseD(Form("hns_el_cutlvl%d", ncuts), Form("hns_el_cutlvl%d", ncuts), electronD1, electronbin1, electronmin1, electronmax1));
    hns_gelectron.push_back(new THnSparseD(Form("hns_gel_cutlvl%d", ncuts), Form("hns_gel_cutlvl%d", ncuts), electronD1, electronbin1, electronmin1, electronmax1));
  }
  for( int p = 0; p < npr_cuts; ++p ){
    hns_proton.push_back(new THnSparseD(Form("hns_pr_cutlvl%d", p), Form("hns_pr_cutlvl%d", p), protonD1, protonbin1, protonmin1, protonmax1));
    hns_gproton.push_back(new THnSparseD(Form("hns_gpr_cutlvl%d", p), Form("hns_gpr_cutlvl%d", p), protonD1, protonbin1, protonmin1, protonmax1));                                                       
  }
  for( int nphec = 0; nphec < necph_cuts; ++nphec ){
    hns_ecph.push_back(new THnSparseD(Form("hns_ecph_cutlvl%d", nphec), Form("hns_ecph_cutlvl%d", nphec), ecphD1, ecphbin1, ecphmin1, ecphmax1));
    hns_gecph.push_back(new THnSparseD(Form("hns_gecph_cutlvl%d", nphec), Form("hns_gecph_cutlvl%d", nphec), ecphD1, ecphbin1, ecphmin1, ecphmax1));
  }
  for( int nicph = 0; nicph < npr_cuts; ++nicph ){
    hns_icph.push_back(new THnSparseD(Form("hns_icph_cutlvl%d", nicph), Form("hns_icph_cutlvl%d", nicph), icphD1, icphbin1, icphmin1, icphmax1));
    hns_gicph.push_back(new THnSparseD(Form("hns_gicph_cutlvl%d", nicph), Form("hns_gicph_cutlvl%d", nicph), icphD1, icphbin1, icphmin1, icphmax1));
  }

}


std::vector<double> PIDHistograms::CreateParticleProperties( Int_t tempparticleID, Eventh22 tempevent, Int_t tempgindex){
  std::vector<double> particleprop;
  particleprop.clear();

  Double_t cmntm = tempevent.p[tempgindex];
  Double_t px = tempevent.cx[tempgindex];
  Double_t py = tempevent.cy[tempgindex];
  Double_t pz = sqrt( 1 - px*px - py*py );
  Double_t p4 = TMath::Sqrt(cmntm*cmntm);
  TLorentzVector particleLV;
  particleLV.SetPxPyPzE(cmntm*px, cmntm*py, cmntm*pz, p4 );
  Double_t particle_theta = particleLV.Theta()*(180.0/TMath::Pi());
  Double_t particle_phi = particleLV.Phi()*(180.0/TMath::Pi());

  //All the information that is calculated outside of this class.
  //TVector3 ic_pos(0, 0 ,0 );
  Int_t runnumber = calculator.run;
  Double_t targetposition = calculator.targetPos;
  TVector3 ic_pos = calculator.ICHitPosition( runnumber, tempevent, tempgindex );
  Double_t *beam_corr = calculator.RasterCorrection( runnumber, tempevent, tempgindex );
  Double_t *cosine_corr = calculator.CosineCorrection( runnumber, tempevent, tempgindex );
  TVector3 uvwhall = planes.UVWhallcord( tempevent, tempgindex );
  
  if( tempparticleID == 11 ){
    Double_t c = 30.0;
    Double_t timediff = tempevent.cc_t[tempgindex] - (tempevent.cc_r[tempgindex]/c) - tempevent.sc_t[tempgindex] + (tempevent.sc_r[tempgindex]/c);
    Double_t el_corr_mntm = calculator.ElectronCorrectedMntm( tempevent.p[tempgindex] ); 
    particleprop.push_back( tempevent.p[tempgindex] );
    particleprop.push_back(tempevent.ec_ei[tempgindex]);
    particleprop.push_back(tempevent.ec_eo[tempgindex]);
    particleprop.push_back(1.0*tempevent.nphe[tempgindex]);
    particleprop.push_back(timediff);
    particleprop.push_back(particle_theta);
    particleprop.push_back(particle_phi);
    particleprop.push_back(tempevent.etot[tempgindex]);
    //    std::cout << ic_pos.X() << std::endl;
    particleprop.push_back(ic_pos.X());
    particleprop.push_back(ic_pos.Y());
    particleprop.push_back(TMath::Abs(cosine_corr[3] - targetposition));
    particleprop.push_back(uvwhall.X());
    particleprop.push_back(uvwhall.Y());
  }
  if( tempparticleID == 2212 ){
    //protonsparse is mntm, zvertex, h22.b, theta, phi,

    Double_t pr_corr_mntm = calculator.ProtonCorrectedMntm( tempevent.p[tempgindex] );
    particleprop.push_back(tempevent.p[tempgindex]  );
    particleprop.push_back(tempevent.vz[tempgindex]);
    particleprop.push_back(tempevent.b[tempgindex]);
    particleprop.push_back(particle_theta);
    particleprop.push_back(particle_phi);
    particleprop.push_back(ic_pos.X());
    particleprop.push_back(ic_pos.Y());
    particleprop.push_back(TMath::Abs(cosine_corr[3] - targetposition));

  }
  if( tempparticleID == 11000 ){
    //ec photon - nergydep, h22.b, mntm, theta, phi
    // Need to add Energy Correction here?
    particleprop.push_back( tempevent.etot[tempgindex]);
    particleprop.push_back(tempevent.b[tempgindex]);
    particleprop.push_back(cmntm);
    particleprop.push_back(particle_theta);
    particleprop.push_back(particle_phi);
    particleprop.push_back(uvwhall.X());
    particleprop.push_back(uvwhall.Y());
  }
  if( tempparticleID == 110000 ){
    //ic photon -energy, theta, phi
    particleprop.push_back(tempevent.etc[tempgindex]);
    particleprop.push_back( tempevent.xc[tempgindex] - beam_corr[0] ); //need to use beamcorrection from calculator class 
    particleprop.push_back( tempevent.yc[tempgindex] - beam_corr[1] );
  }
  return particleprop;
}

void PIDHistograms::FillElectronTHn( std::vector<bool> tempvect, Eventh22 tempevent, Int_t tempgindex ){
  std::vector<bool>::iterator it; 
    for( it = tempvect.begin(); it!=tempvect.end(); ++it){
      if ( !tempvect[0] ){ break; }
      bool goodevent = (*it);
      if( goodevent ){ 
	//	std::cout << CreateParticleProperties( 11, tempevent, tempgindex ).size() << std::endl;
	hns_electron[ it - tempvect.begin()]->Fill( CreateParticleProperties( 11, tempevent, tempgindex ).data() ); 
      }
      //if( !goodevent ){
      //  hns_badelectron[it - tempvect.begin()]->Fill( CreateParticleProperties( 11, tempevent, tempgindex ).data() );
      // }
    }
}


void PIDHistograms::FillProtonTHn( std::vector<bool> tempvect, Eventh22 tempevent, Int_t tempgindex ){
  std::vector<bool>::iterator it;
  for( it=tempvect.begin(); it!=tempvect.end(); it++){
    if ( !tempvect[0] ){ break; }
    bool goodevent = (*it);
    if( goodevent ){
      hns_proton[it - tempvect.begin()]->Fill( CreateParticleProperties( 2212, tempevent, tempgindex ).data() );
      }
    //if( !goodevent ){
    //  hns_badelectron[it - tempvect.begin()]->Fill( CreateParticleProperties( 11, tempevent, tempgindex ).data() );
    // }
  }
}


void PIDHistograms::FillECPhotonTHn( std::vector<bool> tempvect, Eventh22 tempevent, Int_t tempgindex ){
  std::vector<bool>::iterator it;
    for( it = tempvect.begin(); it!=tempvect.end(); it++){
      if ( !tempvect[0] ){ break; }
      bool goodevent = (*it);
      if( goodevent ){
	hns_ecph[it - tempvect.begin()]->Fill( CreateParticleProperties( 11000, tempevent, tempgindex ).data() );
      }
      //if( !goodevent ){
      //  hns_badelectron[it - tempvect.begin()]->Fill( CreateParticleProperties( 11, tempevent, tempgindex ).data() );
      // }
    }
}

void PIDHistograms::FillICPhotonTHn( std::vector<bool> tempvect, Eventh22 tempevent, Int_t tempgindex ){
  std::vector<bool>::iterator it;
  for( it = tempvect.begin(); it!=tempvect.end(); it++){
    if ( !tempvect[0] ){ break; }
    bool goodevent = (*it);
    if( goodevent ){
      hns_icph[it - tempvect.begin()]->Fill( CreateParticleProperties( 110000, tempevent, tempgindex ).data() );
    }
    //if( !goodevent ){
    //  hns_badelectron[it - tempvect.begin()]->Fill( CreateParticleProperties( 11, tempevent, tempgindex ).data() );
    // }
  }
}

void PIDHistograms::FillGoodCandidateParticleTHn( Int_t tempparticleID, std::vector<bool> tempvect, Eventh22 tempevent, Int_t tempgindex ){
  std::vector<bool>::iterator it;
  for ( it = tempvect.begin(); it!=tempvect.end(); it++ ){
    
    if( tempparticleID == 11 ){
      hns_gelectron[ it - tempvect.begin()]->Fill( CreateParticleProperties( tempparticleID, tempevent, tempgindex ).data() ); 
    }
    else if( tempparticleID == 2212 ){
      hns_gproton[it - tempvect.begin()]->Fill( CreateParticleProperties( tempparticleID, tempevent, tempgindex ).data() ); 
    }
    else if( tempparticleID == 11000 ){
      hns_gecph[it - tempvect.begin()]->Fill( CreateParticleProperties( tempparticleID, tempevent, tempgindex ).data() );
    }
    else if( tempparticleID == 110000 ){
      hns_gicph[it - tempvect.begin()]->Fill( CreateParticleProperties( tempparticleID, tempevent, tempgindex ).data() );
    }
    else{
      std::cout << " Please be sure you have entered the appropriate particle ID "<< std::endl;
      exit(0);
    }
  }
}


void PIDHistograms::WriteSparses( ){ //TFile *tempoutfile ){ // Passing this as a pointer also works 
  std::vector< std::vector< THnSparseD* > > returnSparses;
  returnSparses.push_back( hns_electron ); 
  returnSparses.push_back( hns_gelectron ); 
  returnSparses.push_back( hns_proton );
  returnSparses.push_back( hns_gproton );
  returnSparses.push_back( hns_ecph );
  returnSparses.push_back( hns_gecph );
  returnSparses.push_back( hns_icph );
  returnSparses.push_back( hns_gicph );

  std::vector< std::vector< THnSparseD* > >::iterator hnsvect_it;
  std::vector< THnSparseD* >::iterator hns_it;

  int i = 0;
  for( hnsvect_it = returnSparses.begin(); hnsvect_it != returnSparses.end(); hnsvect_it++ ){

  putoutfile->cd(foldernames[i]);
    for( hns_it = (*hnsvect_it).begin(); hns_it != (*hnsvect_it).end(); hns_it++ ){
      (*hns_it)->Write();
    }
    i++;
  }
}
