#define bpidhistograms_cxx

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/Calculator.h"
#include "../include/BPIDHistograms.h"

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



BPIDHistograms::BPIDHistograms(){


  ///////////////////////////////////////////////
  //
  // Put all bin information here for histograms
  //
  ///////////////////////////////////////////////

  el_bin1 = 100;
  el_bin2 = 200;
  el_maxp = 6.0;
  el_minp = 0.0;
  el_mineci = 0.01;
  el_maxeci = 0.4;
  el_mineco = 0.01;
  el_maxeco = 0.3;
  el_minnphe = 0.0;
  el_maxnphe = 100.0;
  el_maxt = 10.0;
  el_mint = -10.0;
  el_mintheta = 0.0;
  el_maxtheta = 70.0;
  el_minphi = -190.0;
  el_maxphi = 190.0;
  el_mincx = -1.0;
  el_maxcx = 1.0;
  el_mincy = -1.0;
  el_maxcy = 1.0;
  el_minvz = -4.0;
  el_maxvz = 4.0;
  el_minedep = 0.0;
  el_maxedep = 60.0;
  el_mintl1x = -80.0;
  el_maxtl1x = 80.0;
  el_mintl1y = -80.0;
  el_maxtl1y = 80.0;
  el_mincc2 = 0.0;
  el_maxcc2 = 0.20;
  el_minetot = 0.0;
  el_maxetot = 2.0;
  el_minect = 0.0;
  el_maxect = 70.0;
  el_minsct = 0.0;
  el_maxsct = 70.0;
  el_minei = 0.0;
  el_maxei = 1.0;


  pr_bin1 = 100;
  pr_bin2 = 200;
  pr_maxp = 4.2;
  pr_minp = 0.0;
  pr_mineci = 0.01;
  pr_maxeci = 0.4;
  pr_mineco = 0.01;
  pr_maxeco = 0.3;
  pr_minnphe = 0.0;
  pr_maxnphe = 20.0;
  pr_maxt = 5.0;
  pr_mint = -2.0;
  pr_mintheta = 0.0;
  pr_maxtheta = 100.0;
  pr_minphi = -190.0;
  pr_maxphi = 190.0;
  pr_mincx = -1.0;
  pr_maxcx = 1.0;
  pr_mincy = -1.0;
  pr_maxcy = 1.0;
  pr_minvz = -5.0;
  pr_maxvz = 5.0;
  pr_minb = 0.20;
  pr_maxb = 1.20;
  pr_minedep = 0.0;
  pr_maxedep = 60.0;
  pr_mintl1x = -80.0;
  pr_maxtl1x = 80.0;
  pr_mintl1y = -80.0;
  pr_maxtl1y = 80.0;
  pr_minetot = 0.0;
  pr_maxetot = 5.0;

  ecph_bin1 = 100;
  ecph_bin2 = 200;
  ecph_maxp = 7.0;
  ecph_minp = 0.0;
  ecph_mineci = 0.01;
  ecph_maxeci = 0.4;
  ecph_mineco = 0.01;
  ecph_maxeco = 0.3;
  ecph_minnphe = 0.0;
  ecph_maxnphe = 100.0;
  ecph_maxt = 5.0;
  ecph_mint = -2.0;
  ecph_mintheta = 0.0;
  ecph_maxtheta = 100.0;
  ecph_minphi = -190.0;
  ecph_maxphi = 190.0;
  ecph_mincx = -1.0;
  ecph_maxcx = 1.0;
  ecph_mincy = -1.0;
  ecph_maxcy = 1.0;
  ecph_minvz = -80.0;
  ecph_maxvz = -45.0;
  ecph_minb = 0.0;
  ecph_maxb = 1.20;
  ecph_minedep = 0.0;
  ecph_maxedep = 3.0;
  ecph_mintl1x = -80.0;
  ecph_maxtl1x = 80.0;
  ecph_mintl1y = -80.0;
  ecph_maxtl1y = 80.0;

  icph_bin1 = 100;
  icph_minxc = -10.0;
  icph_maxxc = 10.0;
  icph_minyc = -10.0;
  icph_maxyc = 10.0;
  icph_minetc = 0.0;
  icph_maxetc = 5.0;
  icph_minecc = 0.0;
  icph_maxecc = 100.0;
  icph_minet = 0.0;
  icph_maxet = 7.0;
  icph_minichx = -50.0;
  icph_maxichx = 50.0;
  icph_minichy = -50.0;
  icph_maxichy = 50.0;
  icph_minichxgl = -50.0;
  icph_maxichxgl = 50.0;
  icph_minichygl = -50.0;
  icph_maxichygl = 50.0;
  icph_mintheta = 2.0;
  icph_maxtheta = 20.0;
  icph_minphi = -190.0;
  icph_maxphi = 190.0;

  minrastr1 = 0.0;
  maxrastr1 = 7000.0;
  minrastr2 = 0.0;
  maxrastr2 = 7000.0;

  ec_fidmax = 400.0;
  ec_fidmin = -400.0;
  ic_fidmax = 19.0;
  ic_fidmin = -19.0;

  ic_fidshadmin = -25.0;
  ic_fidshadmax = 25.0;


  ic_shadmin = -70.0;
  ic_shadmax = 70.0;

  ///////////////////////////////
  //Variables for Corrected plots
  //
  ///////////////////////////////

  cr_minrastr1 = -0.80;
  cr_maxrastr1 = 0.80;
  cr_minrastr2 = -0.80;
  cr_maxrastr2 = 0.80;

  cr_el_pmin = 0.0;
  cr_el_pmax = 6.0;

  cr_pr_pmin = 0.0;
  cr_pr_pmax = 4.0;
  
  cr_beamxmin = -15.0;
  cr_beamxmax = 15.0;

  cr_beamymin = -15.0;
  cr_beamymax = 15.0;

  SpeedOfLight = 29.9792458;
}

BPIDHistograms::BPIDHistograms(TFile *tempoutfile){

}


BPIDHistograms::~BPIDHistograms(){

}


void BPIDHistograms::CreateHistDirectories( TFile *tempoutfile ){
 
  /* foldernames.push_back("hns_electron");
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
  */
  putoutfile = tempoutfile;



}

void BPIDHistograms::AddCorrections( Calculator calculate ){

  calculator = calculate;

}

void BPIDHistograms::ElCutBasedHist(Int_t h ){
  h_el_1d.push_back(new TH1D(Form("h1_el_p_cutlvl%d",h),Form("h1_el_p_cutlvl%d",h), el_bin1, el_minp, el_maxp ) );
  h1_el_vertex.push_back(new TH1D(Form("h1_el_vertex_cutlvl%d",h),Form("h1_el_vertex_cutlvl%d",h), el_bin1, el_minvz, el_maxvz ) );
  h1_el_cc2.push_back(new TH1D(Form("h1_el_cc2_cutlvl%d",h),Form("h1_el_cc2_cutlvl%d",h), el_bin1, el_mincc2, el_maxcc2 ) );
  h1_el_timing.push_back(new TH1D(Form("h1_el_timing_cutlvl%d",h),Form("h1_el_timinig_cutlvl%d",h), el_bin1, el_mint, el_maxt ) );
  h1_el_ecdepinner.push_back(new TH1D(Form("h1_el_ecdepinner_cutlvl%d",h),Form("h1_el_ecdepinner_cutlvl%d",h), el_bin1, el_minedep, el_maxedep ) );
  h1_el_nphe.push_back(new TH1D(Form("h1_el_nphe_cutlvl%d",h),Form("h1_el_nphe_cutlvl%d",h), el_bin1, 0, 100 ) );
  h1_el_sct.push_back(new TH1D(Form("h1_el_sct_cutlvl%d",h),Form("h1_el_sct_cutlvl%d",h), el_bin1, el_minsct, el_maxsct ) );
  h1_el_ect.push_back( new TH1D(Form("h1_el_ect_cutlvl%d",h), Form("h1_el_ect_cutlvl%d",h), el_bin1, el_minect, el_maxect ) );
  h1_el_eci.push_back( new TH1D(Form("h1_el_eci_cutlvl%d",h), Form("h1_el_eci_cutlvl%d",h), el_bin1, el_minei, el_maxei ) );

  h2_el_ecEIEO.push_back(new TH2D(Form("h2_el_ecEIEO_cutlvl%d",h),Form("h2_el_ecEIEO_cutlvl%d",h), el_bin1, el_mineci, 0.6, el_bin1, el_mineco, 0.6 ) );
  h2_el_etotvsp.push_back(new TH2D(Form("h2_el_etotvsp_cutlvl%d",h),Form("h2_el_etotvsp_cutlvl%d",h), el_bin1, el_minp, 2.5, el_bin1, el_minetot, 1.005 ) );
  h2_el_etotpvsp.push_back(new TH2D(Form("h2_el_etotpvsp_cutlvl%d",h),Form("h2_el_etotpvsp_cutlvl%d",h), el_bin1, el_minp, el_maxp, el_bin1, 0, 1 ) );
  h2_el_etotvsei.push_back(new TH2D(Form("h2_el_etotvsei_cutlvl%d",h),Form("h2_el_etotvsei_cutlvl%d",h), el_bin1, 0.005, 1.005, el_bin1, 0.005, 1.005 ) );
  h2_el_echit.push_back(new TH2D(Form("h2_el_echit_cutlvl%d",h),Form("h2_el_echit_cutlvl%d",h), el_bin1, ec_fidmin, ec_fidmax, el_bin1, ec_fidmin, ec_fidmax ) );
  h2_el_icshadhit.push_back(new TH2D(Form("h2_el_icshadhit_cutlvl%d",h),Form("h2_el_icshadhit_cutlvl%d",h), el_bin1, ic_fidshadmin, ic_fidshadmax, el_bin1, ic_fidshadmin, ic_fidshadmax ) );
  h2_el_vertexPhi.push_back(new TH2D(Form("h2_el_vertexPhi_cutlvl%d",h),Form("h2_el_vertexPhi_cutlvl%d",h), el_bin1,  -5, 20.0, el_bin1, el_minphi, el_maxphi ) );
  h2_el_ecdcsect.push_back(new TH2I(Form("h2_el_ecdcsect_cutlvl%d",h),Form("h2_el_ecdcsect_cutlvl%d",h), 7, 0, 7, 7, 0, 7 ) );  
  h2_el_ccdcsect.push_back(new TH2I(Form("h2_el_ccdcsect_cutlvl%d",h),Form("h2_el_ccdcsect_cutlvl%d",h), 7, 0, 7, 7, 0, 7 ) );
}
  ////////////////////////////////
  //
  //        Protons
  ///////////////////////////////

void BPIDHistograms::PrCutBasedHist(Int_t h ){
  h1_pr_p.push_back(new TH1D(Form("h1_pr_p_cutlvl%d",h),Form("h1_pr_p_cutlvl%d",h), pr_bin1, pr_minp, pr_maxp ) );
  h1_pr_vertex.push_back(new TH1D(Form("h1_pr_vertex_cutlvl%d",h),Form("h1_pr_vertex_cutlvl%d",h), pr_bin1, pr_minvz, pr_maxvz ) );
  h1_pr_beta.push_back(new TH1D(Form("h1_pr_beta_cutlvl%d",h),Form("h1_pr_beta_cutlvl%d",h), pr_bin1, pr_minb, pr_maxb ) );
  h1_pr_sctiming.push_back(new TH1D(Form("h1_pr_sctiming_cutlvl%d",h),Form("h1_pr_sctiming_cutlvl%d",h), pr_bin1, 0, 110 ) );
  
  h2_pr_deltaTvsp.push_back(new TH2D(Form("h2_pr_deltaTvsp_cutlvl%d",h),Form("h2_pr_deltaTvsp_cutlvl%d",h), pr_bin1, pr_minp, 3.5, pr_bin1, -80.0, 50.0 ) );
  h2_pr_deltaBvsp.push_back(new TH2D(Form("h2_pr_deltaBvsp_cutlvl%d",h),Form("h2_pr_deltaBvsp_cutlvl%d",h), pr_bin1, pr_minp, 3.5, pr_bin1, -0.3, 0.3 ) );
  h2_pr_bvsp.push_back(new TH2D(Form("h2_pr_bvsp_cutlvl%d",h),Form("h2_pr_bvsp_cutlvl%d",h), pr_bin1, pr_minp, 3.0, pr_bin1, 0, 1.2 ) );
  h2_pr_echit.push_back(new TH2D(Form("h2_pr_echit_cutlvl%d",h),Form("h2_pr_echit_cutlvl%d",h), pr_bin1, ec_fidmin, ec_fidmax, pr_bin1, ec_fidmin, ec_fidmax ) );
  h2_pr_icshadhit.push_back(new TH2D(Form("h2_pr_icshadhit_cutlvl%d",h),Form("h2_pr_icshadhit_cutlvl%d",h),  el_bin1, -25.0, 25.0, 100, -25.0, 25.0 ));// ic_fidshadmin, ic_fidshadmax, el_bin1, ic_fidshadmin, ic_fidshadmax ) );
  h2_pr_vertexPhi.push_back(new TH2D(Form("h2_pr_vertexPhi_cutlvl%d",h),Form("h2_pr_vertexPhi_cutlvl%d",h), pr_bin1,  -5, 20.0, pr_bin1, pr_minphi, pr_maxphi ) );
}

  ////////////////////////////////
  //
  //        EC Photons
  ///////////////////////////////
void BPIDHistograms::ECPhCutBasedHist(Int_t h ){
  h1_ecph_b.push_back(new TH1D(Form("h1_ecph_b_cutlvl%d",h),Form("h1_ecph_b_cutlvl%d",h), ecph_bin1, ecph_minb, ecph_maxb ) );
  h1_ecph_edep.push_back(new TH1D(Form("h1_ecph_edep_cutlvl%d",h),Form("h1_ecph_edep_cutlvl%d",h), ecph_bin1, ecph_minedep, ecph_maxedep ) );

  h2_ecph_echit.push_back(new TH2D(Form("h2_ecph_echit_cutlvl%d",h),Form("h2_ecph_echit_cutlvl%d",h), ecph_bin2, ec_fidmin, ec_fidmax, ecph_bin2, ec_fidmin, ec_fidmax ) );
  h2_ecph_icshadhit.push_back(new TH2D(Form("h2_ecph_icshadhit_cutlvl%d",h),Form("h2_ecph_icshadhit_cutlvl%d",h),  el_bin1, ic_fidshadmin, ic_fidshadmax, el_bin1, ic_fidshadmin, ic_fidshadmax ) );
}
  ////////////////////////////////
  //
  //        IC Photons
  ///////////////////////////////
void BPIDHistograms::ICPhCutBasedHist(Int_t h ){
  h1_icph_etc.push_back(new TH1D(Form("h1_icph_etc_cutlvl%d",h),Form("h1_icph_etc_cutlvl%d",h), icph_bin1, icph_minetc, icph_maxetc ) );
  h1_icph_lvE.push_back(new TH1D(Form("h1_icph_lvE_cutlvl%d",h),Form("h1_icph_lvE_cutlvl%d",h), icph_bin1, icph_minetc, icph_maxetc ) );
  h1_icph_lvTheta.push_back(new TH1D(Form("h1_icph_lvTheta_cutlvl%d",h),Form("h1_icph_lvTheta_cutlvl%d",h), icph_bin1, icph_mintheta, icph_maxtheta ) );
  h1_icph_lvPhi.push_back(new TH1D(Form("h1_icph_lvPhi_cutlvl%d",h),Form("h1_icph_lvPhi_cutlvl%d",h), icph_bin1, icph_minphi, icph_maxphi ) );

  h2_icph_ichit.push_back(new TH2D(Form("h2_icph_ichit_cutlvl%d",h),Form("h2_icph_ichit_cutlvl%d",h), icph_bin1, ic_fidmin, ic_fidmax, icph_bin1, ic_fidmin, ic_fidmax ) );
  h2_icph_moeller.push_back(new TH2D(Form("h2_icph_moeller_cutlvl%d",h),Form("h2_icph_moeller_cutlvl%d",h), icph_bin1, icph_minetc, icph_maxetc, icph_bin1, icph_mintheta, icph_maxtheta ) );
  h2_icph_lvThetaPhi.push_back(new TH2D(Form("h2_icph_lvThetaPhi_cutlvl%d",h),Form("h1_icph_lvThetaPhi_cutlvl%d",h), icph_bin1, icph_mintheta, icph_maxtheta, icph_bin1, icph_minphi, icph_maxphi ) );

}



void BPIDHistograms::InitiateALLHistograms(){
 
   
  h_el_p = new TH1D("hpid_el_p","", el_bin1, el_minp, el_maxp );
  h_el_eci = new TH1D("hpid_el_eci","", el_bin1, el_mineci, el_maxeci );
  h_el_eco = new TH1D("hpid_el_eco","",el_bin1, el_mineco, el_maxeco );
  h_el_nphe = new TH1D("hpid_el_nphe","",el_bin1, el_minnphe, el_maxnphe);
  h_el_time = new TH1D("hpid_el_time","",el_bin1, el_mint, el_maxt );
  h_el_theta = new TH1D("hpid_el_theta","",el_bin1, el_mintheta, el_maxtheta);
  h_el_phi = new TH1D("hpid_el_phi","",el_bin1, el_minphi, el_maxphi );
  h_el_cx = new TH1D("hpid_el_cx","", el_bin1, el_mincx, el_maxcx );
  h_el_cy = new TH1D("hpid_el_cy","",el_bin1, el_mincy, el_maxcy );
  h_el_vz = new TH1D("hpid_el_vz","",el_bin1, el_minvz, el_maxvz);
  h_el_edep = new TH1D("hpid_el_edep","",el_bin1, el_minedep, el_maxedep);
  h_el_tl1x = new TH1D("hpid_el_tl1x","",el_bin1, el_mintl1x, el_maxtl1x );
  h_el_tl1y = new TH1D("hpid_el_tl1y","",el_bin1, el_mintl1y, el_maxtl1y );
  h_el_vz_corr = new TH1D("hpid_el_vz_corr","",el_bin1, el_minvz, el_maxvz );

  h_pr_p = new TH1D("hpid_pr_p","", pr_bin1, pr_minp, pr_maxp );
  h_pr_b = new TH1D("hpid_pr_b","", pr_bin1, pr_minb, pr_maxb );
  h_pr_eci = new TH1D("hpid_pr_eci","", pr_bin1, pr_mineci, pr_maxeci );
  h_pr_eco = new TH1D("hpid_pr_eco","",pr_bin1, pr_mineco, pr_maxeco );
  h_pr_nphe = new TH1D("hpid_pr_nphe","",pr_bin1, pr_minnphe, pr_maxnphe);
  h_pr_time = new TH1D("hpid_pr_time","",pr_bin1, pr_mint, pr_maxt );
  h_pr_theta = new TH1D("hpid_pr_theta","",pr_bin1, pr_mintheta, pr_maxtheta);
  h_pr_phi = new TH1D("hpid_pr_phi","",pr_bin1, pr_minphi, pr_maxphi );
  h_pr_cx = new TH1D("hpid_pr_cx","", pr_bin1, pr_mincx, pr_maxcx );
  h_pr_cy = new TH1D("hpid_pr_cy","",pr_bin1, pr_mincy, pr_maxcy );
  h_pr_vz = new TH1D("hpid_pr_vz","",pr_bin1, pr_minvz, pr_maxvz);
  h_pr_edep = new TH1D("hpid_pr_edep","",pr_bin1, pr_minedep, pr_maxedep);
  h_pr_tl1x = new TH1D("hpid_pr_tl1x","",pr_bin1, pr_mintl1x, pr_maxtl1x );
  h_pr_tl1y = new TH1D("hpid_pr_tl1y","",pr_bin1, pr_mintl1y, pr_maxtl1y );
  h_pr_vz_corr = new TH1D("hpid_pr_vz_corr","",pr_bin1, pr_minvz, pr_maxvz);

 
  h_ecph_p = new TH1D("hpid_ecph_p","", ecph_bin1, ecph_minp, ecph_maxp );
  h_ecph_b = new TH1D("hpid_ecph_b","", ecph_bin1, ecph_minb, ecph_maxb );
  h_ecph_eci = new TH1D("hpid_ecph_eci","", ecph_bin1, ecph_mineci, ecph_maxeci );
  h_ecph_eco = new TH1D("hpid_ecph_eco","",ecph_bin1, ecph_mineco, ecph_maxeco );
  //h_ecph_nphe = new TH1D("hpid_ecph_nphe","",ecph_bin1, ecph_minnphe, ecph_maxnphe);
  //h_ecph_time = new TH1D("hpid_ecph_time","",ecph_bin1, ecph_mint, ecph_maxt );
  //h_ecph_theta = new TH1D("hpid_ecph_theta","",ecph_bin1, ecph_mintheta, ecph_maxtheta);
  //h_ecph_phi = new TH1D("hpid_ecph_phi","",ecph_bin1, ecph_minphi, ecph_maxphi );
  h_ecph_cx = new TH1D("hpid_ecph_cx","", ecph_bin1, ecph_mincx, ecph_maxcx );
  h_ecph_cy = new TH1D("hpid_ecph_cy","",ecph_bin1, ecph_mincy, ecph_maxcy );
  h_ecph_vz = new TH1D("hpid_ecph_vz","",ecph_bin1, ecph_minvz, ecph_maxvz);
  //h_ecph_edep = new TH1D("hpid_ecph_edep","",ecph_bin1, ecph_minedep, ecph_maxedep);
  h_ecph_tl1x = new TH1D("hpid_ecph_tl1x","",ecph_bin1, ecph_mintl1x, ecph_maxtl1x );
  h_ecph_tl1y = new TH1D("hpid_ecph_tl1y","",ecph_bin1, ecph_mintl1y, ecph_maxtl1y );

  h_icph_xc = new TH1D("hpid_icph_xc","", icph_bin1, icph_minxc,icph_maxxc );
  h_icph_yc = new TH1D("hpid_icph_xy","", icph_bin1, icph_minyc, icph_maxyc );
  h_icph_etc = new TH1D("hpid_icph_etc","",icph_bin1, icph_minetc ,icph_maxetc );
  h_icph_ecc = new TH1D("hpid_icph_ecc","",icph_bin1, icph_minecc, icph_maxecc );
  h_icph_et = new TH1D("hpid_icph_et","",icph_bin1, icph_minet, icph_maxet );
  h_icph_ichx = new TH1D("hpid_icph_ichx","",icph_bin1, icph_minichx, icph_maxichx);
  h_icph_ichy = new TH1D("hpid_icph_ichy","",icph_bin1, icph_minichy, icph_maxichy );
  h_icph_ichxgl = new TH1D("hpid_icph_ichxgl","", icph_bin1, icph_minichxgl, icph_maxichxgl);
  h_icph_ichygl = new TH1D("hpid_icph_ichygl","",icph_bin1, icph_minichygl, icph_maxichygl);
  h_icph_theta = new TH1D("hpid_icph_theta","",icph_bin1,icph_mintheta, icph_maxtheta);
  h_icph_phi = new TH1D("hpid_icph_phi","",icph_bin1, icph_minphi, icph_maxphi);
 
  h_partMulti = new TH1D("hpid_multi","",20,0,20);


  ///////////////////////////
  //
  // Below are the TH2D
  // and general variables
  //
  //////////////////////////

  h_el_ecieco = new TH2D("hpid_el_ecieco","",el_bin2, el_mineci, el_maxeci, el_bin2, el_mineco, el_maxeco );
  //  h_el_timenphe = new TH2D("hpid_el_timenphe","",el_bin2, el_minnphe, el_maxnphe, el_bin2, el_mint, el_maxt );
  h_el_echit = new TH2D("hpid_el_echit","",el_bin2, ec_fidmin, ec_fidmax, el_bin2, ec_fidmin, ec_fidmax );
  h_el_icproj = new TH2D("hpid_el_icproj","",el_bin2,  ic_shadmin, ic_shadmax, el_bin2, ic_shadmin, ic_shadmax );
  h_el_thetaphi = new TH2D("hpid_el_thetaphi","",el_bin2, el_mintheta, el_maxtheta, el_bin2, el_minphi, el_maxphi ); 
  h_el_vzPhi = new TH2D("hpid_el_vzPhi","",el_bin2, el_minvz, el_maxvz, el_bin2, el_minphi, el_maxphi );
  h_el_timenphe = new TH2D("hpid_el_timenphe","",el_bin1, 0, 100, el_bin1, -10, 10 );

  h_pr_icproj = new TH2D("hpid_pr_icproj","",pr_bin2, ic_shadmin, ic_shadmax, pr_bin2, ic_shadmin, ic_shadmax );
  h_pr_bp = new TH2D("hpid_pr_bp","",pr_bin1, pr_minp, pr_maxp, pr_bin1, pr_minb, pr_maxb );
  h_pr_bp_calc = new TH2D("hpid_pr_bp_calc","",pr_bin1, pr_minp, pr_maxp, pr_bin1, pr_minb, pr_maxb );
  h_pr_vzPhi = new TH2D("hpid_pr_vzPhi","",pr_bin2, pr_minvz, pr_maxvz, pr_bin2, pr_minphi, pr_maxphi );
  h_pr_pdeltaT = new TH2D("hpid_pr_pdeltaT","",pr_bin2, pr_minp, pr_maxp, pr_bin2, -5, 5 );
  h_pr_pdeltaB = new TH2D("hpid_pr_pdeltaB","",pr_bin2, pr_minp, pr_maxp, pr_bin2, -0.4, 0.4 );
  h_pr_ecieco = new TH2D("hpid_pr_ecieco","",pr_bin2, pr_mineci, pr_maxeci, pr_bin2, pr_mineco, pr_maxeco);
  h_pr_thetaphi = new TH2D("hpid_pr_thetaphi","",pr_bin2, 0, 65, pr_bin2, -180, 180 );

  h_ecph_ecieco = new TH2D("hpid_ecph_ecieco","",el_bin2, ecph_mineci, ecph_maxeci, el_bin2, ecph_mineco, ecph_maxeco );
  h_ecph_echit = new TH2D("hpid_ecph_echit","",el_bin2, ec_fidmin, ec_fidmax, el_bin2, ec_fidmin, ec_fidmax );
  h_ecph_icproj = new TH2D("hpid_ecph_icproj","",el_bin2, ic_shadmin, ic_shadmax, el_bin2, ic_shadmin, ic_shadmax );
  h_ecph_thetaphi = new TH2D("hpid_ecph_thetaphi","",el_bin2, ecph_mintheta, ecph_maxtheta, el_bin2, ecph_minphi, ecph_maxphi ); 
  h_ecph_becmax = new TH2D("hpid_ecph_becmax","", el_bin2, pr_minb, pr_maxb, el_bin2, 0.0, 6.0 );
  h_icph_ichit = new TH2D("hpid_icph_ichit","",el_bin1, ic_fidmin, ic_fidmax, el_bin1, ic_fidmin, ic_fidmax );
  h_icph_etctc = new TH2D("hpid_icph_etctc","",200, -200.0, 200.0, 100, 0, 6.0 ); 

  h_rastr1 = new TH1D("hpid_rastr1","",el_bin1, minrastr1, maxrastr1);
  h_rastr2 = new TH1D("hpid_rastr2","",el_bin1, minrastr2, maxrastr2);
  h_rastr12 = new TH2D("hpid_rastr12","",el_bin1, minrastr1, maxrastr1, el_bin1, minrastr2, maxrastr2 );
  /////////////////////////////
  //
  // Below are corrected histos
  //
  /////////////////////////////
  h_crrrastr1 = new TH1D("hpid_crrrastr1","",el_bin1, cr_minrastr1, cr_maxrastr1);
  h_crrrastr2 = new TH1D("hpid_crrrastr2","",el_bin1, cr_minrastr2, cr_maxrastr2);
  h_crrrastr12 = new TH2D("hPID_crrrastr12","",el_bin1, cr_minrastr1, cr_maxrastr1, el_bin1, cr_minrastr2, cr_maxrastr2);
  h_el_crp = new TH1D("hpid_el_crp","", el_bin1, cr_el_pmin, cr_el_pmax );
  h_pr_crp = new TH1D("hpid_pr_crp","", pr_bin1, cr_pr_pmin, cr_pr_pmax );

  h_el_vzPhi_corr = new TH2D("hpid_el_vzPhi_corr","",el_bin2, el_minvz, el_maxvz, el_bin2, el_minphi, el_maxphi );
  h_pr_vzPhi_corr = new TH2D("hpid_pr_vzPhi_corr","",el_bin2, el_minvz, el_maxvz, el_bin2, el_minphi, el_maxphi );

}


void BPIDHistograms::ElectronHist( Eventh22 &event, Int_t index, Int_t run ){

 
  //////////////////////////
  //
  //Calculation
  //
  //////////////////////////
     
  TVector3 projectiononIC = calculator.ICHitPosition( run, event, index );
  Double_t el_p_corrected = calculator.ElectronCorrectedMntm( event.p[index] );
  Double_t *el_cosine_corr = calculator.CorrectedCosineCorrection( run, event, index, el_p_corrected);
  Double_t el_phi = (atan2( el_cosine_corr[1], el_cosine_corr[0] ))*TMath::RadToDeg(); 
  Double_t el_theta = acos(sqrt(1 - event.tl1_cx[index]*el_cosine_corr[0] - event.tl1_cy[index]*el_cosine_corr[1]))*(TMath::RadToDeg());
  Double_t targetcenter = calculator.targetPos;

  h_el_p->Fill(event.p[index]);
  h_el_eci->Fill(event.ec_ei[index]);
  h_el_eco->Fill(event.ec_eo[index]);
  h_el_nphe->Fill(event.nphe[index]);
  h_el_time->Fill(event.cc_t[index] -event.cc_r[index]/SpeedOfLight - event.sc_t[index] + event.sc_r[index]/SpeedOfLight);
  h_el_theta->Fill(el_theta);
  h_el_phi->Fill( el_phi );
  h_el_cx->Fill(event.cx[index]);
  h_el_cy->Fill(event.cy[index]);
  h_el_vz->Fill(targetcenter - event.vz[index]);
  h_el_edep->Fill(event.edep[index]);
  h_el_tl1x->Fill(event.tl1_x[index]);
  h_el_tl1y->Fill(event.tl1_y[index]);

  h_el_ecieco->Fill(event.ec_ei[index], event.ec_eo[index] );
  h_el_echit->Fill(event.ech_x[index], event.ech_y[index] );

  h_el_icproj->Fill( event.tl1_x[index] - event.tl1_cx[index] * event.tl1_z[index], event.tl1_y[index] - event.tl1_cy[index] * event.tl1_z[index] );
  h_el_thetaphi->Fill(el_theta, el_phi );
  h_el_vzPhi->Fill(targetcenter - event.vz[index], el_phi );
 
  h_el_crp->Fill( el_p_corrected ); 
  h_el_vzPhi_corr->Fill(targetcenter - el_cosine_corr[3], el_phi );
  h_el_vz_corr->Fill(targetcenter - el_cosine_corr[3]);
  h_el_timenphe->Fill( event.nphe[index], event.cc_t[index] -event.cc_r[index]/SpeedOfLight - event.sc_t[index] + event.sc_r[index]/SpeedOfLight );
}

void BPIDHistograms::ProtonHist( Eventh22 &event, Int_t index, Int_t run  ){

  Double_t pr_p_corrected = calculator.ProtonCorrectedMntm( event.p[index] );
  Double_t *pr_cosine_corr = calculator.CorrectedCosineCorrection( run, event, index, pr_p_corrected);
  Double_t pr_phi = (atan2( pr_cosine_corr[1], pr_cosine_corr[0] ))*TMath::RadToDeg();
  Double_t pr_theta = acos(sqrt(1 - event.tl1_cx[index]*pr_cosine_corr[0] - event.tl1_cy[index]*pr_cosine_corr[1]))*(TMath::RadToDeg());
  Double_t el_starttime = event.sc_t[event.goldenelectronindex]-event.sc_r[event.goldenelectronindex]/SpeedOfLight;
  Double_t MPROT = 0.938272;
  Double_t  protonBeta=event.sc_r[index]/(event.sc_t[index]-el_starttime)/SpeedOfLight; 
  Double_t protonBetaCalc = sqrt(event.p[index]*event.p[index]/(event.p[index]*event.p[index]+MPROT*MPROT));
  Double_t deltaT = (event.sc_t[index]-el_starttime)-event.sc_r[index]/(SpeedOfLight*protonBetaCalc);
  Double_t deltaB = protonBeta-protonBetaCalc;
  Double_t targetcenter = calculator.targetPos;

  h_pr_p->Fill(event.p[index]);
  h_pr_b->Fill(event.b[index]);
  h_pr_eci->Fill(event.ec_ei[index]);
  h_pr_eco->Fill(event.ec_eo[index]);
  h_pr_nphe->Fill(event.nphe[index]);
  h_pr_theta->Fill(pr_theta);
  h_pr_phi->Fill( pr_phi );
  h_pr_cx->Fill(event.cx[index]);
  h_pr_cy->Fill(event.cy[index]);
  h_pr_vz->Fill(targetcenter - event.vz[index]);
  h_pr_edep->Fill(event.edep[index]);
  h_pr_tl1x->Fill(event.tl1_x[index]);
  h_pr_tl1y->Fill(event.tl1_y[index]);

  h_pr_bp->Fill( event.p[index], event.b[index] );
  h_pr_bp_calc->Fill(event.p[index], event.sc_r[index]/(event.sc_t[index] - el_starttime)/SpeedOfLight);  
  h_pr_pdeltaT->Fill( event.p[index], deltaT );
  h_pr_pdeltaB->Fill(event.p[index], deltaB );
  h_pr_ecieco->Fill(event.ec_ei[index], event.ec_eo[index] );

  h_pr_crp->Fill( pr_p_corrected );
  h_pr_vzPhi->Fill(targetcenter - event.vz[index], pr_phi );
  h_pr_vzPhi_corr->Fill(targetcenter - pr_cosine_corr[3], pr_phi );
  h_pr_vz_corr->Fill(targetcenter - pr_cosine_corr[3]);
  h_pr_icproj->Fill( event.tl1_x[index] - event.tl1_cx[index]*event.tl1_z[index], event.tl1_y[index] - event.tl1_cy[index]*event.tl1_z[index] );
  h_pr_thetaphi->Fill(pr_theta, pr_phi );


}

void BPIDHistograms::ECPhotons( Eventh22 &event, Int_t index, Int_t run  ){
  Double_t vertex = 0.0;
   Double_t el_starttime = event.sc_t[event.goldenelectronindex]-event.sc_r[event.goldenelectronindex]/SpeedOfLight;
   Double_t  photonBeta=event.ec_r[index]/(event.ec_t[index]-el_starttime)/SpeedOfLight; 
   //
   //   Double_t *ec_photon_energy = calculator.ECSFCorrection( event, index, run );
   //
   Double_t *corr_raster = calculator.RasterCorrection( run, event, index );

  if(event.nelectron == 1 ){
    vertex = event.vz[event.goldenelectronindex];
  }
  else if( event.nelectron == 1 && event.nproton == 1){
    vertex = fabs((event.vz[event.goldenelectronindex] + event.vz[event.goldenprotonindex])/2.);
  }
  //Double_t ecmax = (ec_photon_energy[2]>ec_photon_energy[0]+ec_photon_energy[1]?ec_photon_energy[2]:ec_photon_energy[0]+ec_photon_energy[1]);
   
  h_ecph_p->Fill(event.p[index]);
  h_ecph_b->Fill(event.b[index]);
  h_ecph_eci->Fill(event.ec_ei[index]);
  h_ecph_eco->Fill(event.ec_eo[index]);
  //h_ecph_nphe->Fill(event.nphe[index]);
  //  h_ecph_time->Fill(event.p[index]); //
  //h_ecph_theta->Fill(event.p[index]);//
  //h_ecph_phi->Fill( phi );x
  h_ecph_cx->Fill(event.cx[index]);
  h_ecph_cy->Fill(event.cy[index]);
  h_ecph_vz->Fill(vertex);
  //h_ecph_edep->Fill(event.edep[index]);
  h_ecph_tl1x->Fill(event.tl1_x[index]); //obvisouly 0 - they are neutrals
  h_ecph_tl1y->Fill(event.tl1_y[index]);

  h_ecph_ecieco->Fill(event.ec_ei[index], event.ec_eo[index] );
  //  h_ecph_icproj->Fill((event.ech_x[index]-corr_raster[0]) * -event./(h22->ech_z[nn]-h22->run->vertex_nom) + h22->xr,(h22->ech_y[nn]-h22->yr) * -h22->run->vertex_nom/(h22->ech_z[nn]-h22->run->vertex_nom) + h22->yr);    
  h_ecph_echit->Fill( event.ech_x[index], event.ech_y[index] );
  // h_ecph_thetaphi->fill(theta, phi );
  //h_ecph_becmax->Fill(photonBeta,ecmax );

}

void BPIDHistograms::ICPhotons( Eventh22 &event, Int_t index, Int_t run ){

  h_icph_xc->Fill( event.xc[index]);
  h_icph_yc->Fill( event.yc[index]);
  h_icph_etc->Fill( event.etc[index]);
  h_icph_ecc->Fill( event.ecc[index]);
  h_icph_et->Fill( event.et[index]);
  h_icph_ichx->Fill( event.ich_x[index]);
  h_icph_ichy->Fill( event.ich_y[index]);
  h_icph_ichxgl->Fill( event.ich_xgl[index]);
  h_icph_ichygl->Fill( event.ich_ygl[index]);
  //  h_icph_theta->Fill( theta );
  // h_icph_phi->Fill( phi );
  h_icph_ichit->Fill(event.xc[index], event.yc[index]);
  h_icph_etctc->Fill(event.tc[index], event.etc[index]);

}

void BPIDHistograms::MiscHistos( Eventh22 &event, Int_t index, Int_t run ){

  h_rastr1->Fill(event.rastr1);
  h_rastr2->Fill(event.rastr2);
  h_rastr12->Fill(event.rastr1, event.rastr2);

  Double_t *raster_corr = calculator.RasterCorrection( run, event, index );
  h_crrrastr1->Fill( raster_corr[0] );
  h_crrrastr2->Fill( raster_corr[1] );
  h_crrrastr12->Fill(raster_corr[0], raster_corr[1]);
  
}

void BPIDHistograms::GoodParticles(Eventh22 event, Int_t index, Int_t run  ){

}


void BPIDHistograms::ParticleMultiplicity(Int_t singEl, Int_t multEl, Int_t singEP, Int_t multProt, Int_t totEPG, Int_t totEPGG, Int_t ictot, Int_t ectot, Int_t nonzeroel, Int_t zeroel, Int_t totgoodel, Int_t totgoodprot, Int_t totgoodecphot, Int_t totgoodicphot, Int_t discount, Int_t dvcsIC, Int_t dvcsEC ){

  h_partMulti->SetBinContent(1,singEl);
  h_partMulti->SetBinContent(2,multEl);
  h_partMulti->SetBinContent(3,singEP);
  h_partMulti->SetBinContent(4,multProt);
  h_partMulti->SetBinContent(5,totEPG);
  h_partMulti->SetBinContent(6,totEPGG);
  h_partMulti->SetBinContent(7,ictot);
  h_partMulti->SetBinContent(8,ectot);
  h_partMulti->SetBinContent(9,nonzeroel);
  h_partMulti->SetBinContent(10,zeroel);
  h_partMulti->SetBinContent(11,totgoodel);
  h_partMulti->SetBinContent(12,totgoodprot);
  h_partMulti->SetBinContent(13,totgoodecphot);
  h_partMulti->SetBinContent(14,totgoodicphot);
  h_partMulti->SetBinContent(15,discount);
  h_partMulti->SetBinContent(16,dvcsIC);
  h_partMulti->SetBinContent(17,dvcsEC);


}

void BPIDHistograms::PIDHistWrite(){


  putoutfile->Write();

}

 
