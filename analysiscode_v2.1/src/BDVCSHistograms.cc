#define bdvcshistograms_cxx

#include "../include/BDVCSHistograms.h"
#include "../include/EventPID.h"
#include "../include/LoadPID.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
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

BDVCSHistograms::BDVCSHistograms(){

  el_bin1 = 100;
  el_minpx = -3.0;
  el_maxpx = 3.0;
  el_minpy = -3.0;
  el_maxpy = 3.0;
  el_minpz = 0.0;
  el_maxpz = 5.5;
  el_minE = 0.0;
  el_maxE = 5.5;
  el_minp = 0;
  el_maxp = 5.5;
  el_minvz = -70.0;
  el_maxvz = -50.0;
  el_minthetadc = -180;
  el_maxthetadc = 180;
  el_minnphe = 0;
  el_maxnphe = 100;

  pr_bin1 = 100;
  pr_minpx = -3.0;
  pr_maxpx = 3.0;
  pr_minpy = -3.0;
  pr_maxpy = 3.0;
  pr_minpz = 0.0;
  pr_maxpz = 4.0;
  pr_minE = 0.0;
  pr_maxE = 5.5;
  pr_minp = 0;
  pr_maxp = 5.5;
  pr_minvz = -70.0;
  pr_maxvz = -55.0;
  pr_minthetadc = -180;
  pr_maxthetadc = 180;
  pr_minnphe = 0;
  pr_maxnphe = 20;

  ph_bin1 = 100;
  ph_minpx = -3.0;
  ph_maxpx = 3.0;
  ph_minpy = -3.0;
  ph_maxpy = 3.0;
  ph_minpz = 0.0;
  ph_maxpz = 4.0;
  ph_minE = 0.0;
  ph_maxE = 5.5;
  ph_minp = 0;
  ph_maxp = 5.5;

  dvcs_bin1 = 100;
  qq_min = 0.80;
  qq_max = 5.5;
  xb_min = 0.05;
  xb_max = 1.0;
  w_min = 0.0;
  w_max = 4.0;
  t_min = 0.0;
  t_max = 5.5;
  tp_min = 0;
  tp_max = 5;
  MM_min = -1.0;
  MM_min = 4.0;
  MM2epg_min = -1.5;
  MM2epg_max = 4.;
  eps_min = 0.5;
  eps_max = 1;
  deltatheta_min = 0;
  deltatheta_max = 90;
  deltaphi_min = -180;
  deltaphi_max = 180;
  phi_min = 0.0;
  phi_max = 360.0;
  Dephi_min = -180;
  Dephi_max = 180;
  perpx_min = 0;
  perpx_max = 1;
  perpy_min = 0;
  perpy_max = 1;
  pPerp_min = 0;
  pPerp_max = 1.0;

  Aasymbin1 = 10;
  Aasy_min = 0;
  Aasy_max = 360;

  Basymbin1 = 10;
  Basy_min = 0;
  Basy_max = 360;



}

BDVCSHistograms::~BDVCSHistograms(){


}

void BDVCSHistograms::CreateDVCSHistograms( TFile *tempoutputfile ){

  poutfile = tempoutputfile;

}


void BDVCSHistograms::AddCorrection( Calculator calculate ){

  calc = calculate;

}

void BDVCSHistograms::ElDVCSHist(Int_t h){

  h1_el_px.push_back( new TH1D(Form("h1_el_px_cutlvl%d",h),Form("h1_el_px_cutlvl%d",h), el_bin1, el_minpx, el_maxpx) );
  h1_el_py.push_back( new TH1D(Form("h1_el_py_cutlvl%d",h),Form("h1_el_py_cutlvl%d",h), el_bin1, el_minpy, el_maxpy) );
  h1_el_pz.push_back( new TH1D(Form("h1_el_pz_cutlvl%d",h),Form("h1_el_pz_cutlvl%d",h), el_bin1, el_minpz, el_maxpz) );
  h1_el_E.push_back( new TH1D(Form("h1_el_E_cutlvl%d",h),Form("h1_el_E_cutlvl%d",h), el_bin1, el_minE, el_maxE) );
  h1_el_p.push_back( new TH1D(Form("h1_el_p_cutlvl%d",h),Form("h1_el_p_cutlvl%d",h), el_bin1, el_minp, el_maxp) );
  h1_el_vertex.push_back( new TH1D(Form("h1_el_vertex_cutlvl%d",h),Form("h1_el_vertex_cutlvl%d",h), el_bin1, el_minvz, el_maxvz) );
  h1_el_dcsect.push_back( new TH1D(Form("h1_el_dcsect_cutlvl%d",h),Form("h1_el_dcsect_cutlvl%d",h), 8, 0, 7) );
  h1_el_thetadc.push_back( new TH1D(Form("h1_el_thetadc_cutlvl%d",h),Form("h1_el_thetadc_cutlvl%d",h), el_bin1, el_minthetadc, el_maxthetadc) );
  h1_el_nphe.push_back( new TH1D(Form("h1_el_nphe_cutlvl%d",h),Form("h1_el_nphe_cutlvl%d",h), el_bin1, el_minnphe, el_maxnphe) );

}

void BDVCSHistograms::PrDVCSHist( Int_t h ){

  h1_pr_px.push_back( new TH1D(Form("h1_pr_px_cutlvl%d",h),Form("h1_pr_px_cutlvl%d",h), pr_bin1, pr_minpx, pr_maxpx) );
  h1_pr_py.push_back( new TH1D(Form("h1_pr_py_cutlvl%d",h),Form("h1_pr_py_cutlvl%d",h), pr_bin1, pr_minpy, pr_maxpy) );
  h1_pr_pz.push_back( new TH1D(Form("h1_pr_pz_cutlvl%d",h),Form("h1_pr_pz_cutlvl%d",h), pr_bin1, pr_minpz, pr_maxpz) );
  h1_pr_E.push_back( new TH1D(Form("h1_pr_E_cutlvl%d",h),Form("h1_pr_E_cutlvl%d",h), pr_bin1, pr_minE, pr_maxE) );
  h1_pr_p.push_back( new TH1D(Form("h1_pr_p_cutlvl%d",h),Form("h1_pr_p_cutlvl%d",h), pr_bin1, pr_minp, pr_maxp) );
  h1_pr_vertex.push_back( new TH1D(Form("h1_pr_vertex_cutlvl%d",h),Form("h1_pr_vertex_cutlvl%d",h), pr_bin1, pr_minvz, pr_maxvz) );
  h1_pr_dcsect.push_back( new TH1D(Form("h1_pr_dcsect_cutlvl%d",h),Form("h1_pr_dcsect_cutlvl%d",h), 8, 0, 7) );
  h1_pr_thetadc.push_back( new TH1D(Form("h1_pr_thetadc_cutlvl%d",h),Form("h1_pr_thetadc_cutlvl%d",h), pr_bin1, pr_minthetadc, pr_maxthetadc) );
  h1_pr_nphe.push_back( new TH1D(Form("h1_pr_nphe_cutlvl%d",h),Form("h1_pr_nphe_cutlvl%d",h), pr_bin1, pr_minnphe, pr_maxnphe) );

}

void BDVCSHistograms::PhDVCSHist( Int_t h ){

  h1_ph_px.push_back( new TH1D(Form("h1_ph_px_cutlvl%d",h),Form("h1_ph_px_cutlvl%d",h), ph_bin1, ph_minpx, ph_maxpx) );
  h1_ph_py.push_back( new TH1D(Form("h1_ph_py_cutlvl%d",h),Form("h1_ph_py_cutlvl%d",h), ph_bin1, ph_minpy, ph_maxpy) );
  h1_ph_pz.push_back( new TH1D(Form("h1_ph_pz_cutlvl%d",h),Form("h1_ph_pz_cutlvl%d",h), ph_bin1, ph_minpz, ph_maxpz) );
  h1_ph_E.push_back( new TH1D(Form("h1_ph_E_cutlvl%d",h),Form("h1_ph_E_cutlvl%d",h), ph_bin1, ph_minE, ph_maxE) );
  h1_ph_p.push_back( new TH1D(Form("h1_ph_p_cutlvl%d",h),Form("h1_ph_p_cutlvl%d",h), ph_bin1, ph_minp, ph_maxp) );

}

void BDVCSHistograms::DVCSKinHistEC( Int_t h ){

  h1_qq.push_back(  new TH1D(Form("h1_dvcs_qq_cutlvl%d",h),Form("h1_dvcs_qq_cutlvl%d",h), dvcs_bin1, qq_min, qq_max) );
  h1_xb.push_back(  new TH1D(Form("h1_dvcs_xb_cutlvl%d",h),Form("h1_dvcs_xb_cutlvl%d",h), dvcs_bin1, xb_min, xb_max) );
  h1_w.push_back(  new TH1D(Form("h1_dvcs_w_cutlvl%d",h),Form("h1_dvcs_w_cutlvl%d",h), dvcs_bin1, w_min, w_max) );
  h1_t.push_back(  new TH1D(Form("h1_dvcs_t_cutlvl%d",h),Form("h1_dvcs_t_cutlvl%d",h), dvcs_bin1, t_min, t_max) );
  h1_tp.push_back(  new TH1D(Form("h1_dvcs_tp_cutlvl%d",h),Form("h1_dvcs_tp_cutlvl%d",h), dvcs_bin1, tp_min, tp_max) );
  h1_MM.push_back(  new TH1D(Form("h1_dvcs_mm_cutlvl%d",h),Form("h1_dvcs_mm_cutlvl%d",h), dvcs_bin1, -1.0, 4.0) );
  h1_MM2epg.push_back(  new TH1D(Form("h1_dvcs_mm2epg_cutlvl%d",h),Form("h1_dvcs_mm2epg_cutlvl%d",h), dvcs_bin1, MM2epg_min, MM2epg_max) );
  h1_eps.push_back(  new TH1D(Form("h1_dvcs_eps_cutlvl%d",h),Form("h1_dvcs_eps_cutlvl%d",h), dvcs_bin1, eps_min, eps_max) );
  h1_deltatheta.push_back(  new TH1D(Form("h1_dvcs_deltatheta_cutlvl%d",h),Form("h1_dvcs_deltatheta_cutlvl%d",h), dvcs_bin1, deltatheta_min, deltatheta_max) );
  h1_deltaphi.push_back(  new TH1D(Form("h1_dvcs_deltaphi_cutlvl%d",h),Form("h1_dvcs_deltaphi_cutlvl%d",h), dvcs_bin1, deltaphi_min, deltaphi_max) );
  h1_phi.push_back(  new TH1D(Form("h1_dvcs_phi_cutlvl%d",h),Form("h1_dvcs_phi_cutlvl%d",h), dvcs_bin1, phi_min, phi_max) );
  h1_Dephi.push_back(  new TH1D(Form("h1_dvcs_dephi_cutlvl%d",h),Form("h1_dvcs_dephi_cutlvl%d",h), dvcs_bin1, Dephi_min, Dephi_max) );
  h1_perpx.push_back(  new TH1D(Form("h1_dvcs_perpx_cutlvl%d",h),Form("h1_dvcs_perpx_cutlvl%d",h), dvcs_bin1, perpx_min, perpx_max) );
  h1_perpy.push_back(  new TH1D(Form("h1_dvcs_perpy_cutlvl%d",h),Form("h1_dvcs_perpy_cutlvl%d",h), dvcs_bin1, perpy_min, perpy_max) );
  h1_pPerp.push_back(  new TH1D(Form("h1_dvcs_pPerp_cutlvl%d",h),Form("h1_dvcs_pPerp_cutlvl%d",h), dvcs_bin1, pPerp_min, pPerp_max) );

  h2_q2x.push_back( new TH2D(Form("h2_dvcs_q2x_cutlvl%d",h),Form("h2_dvcs_q2x_cutlvl%d",h), dvcs_bin1, xb_min, xb_max, dvcs_bin1, qq_min, qq_max ));
  h2_tx.push_back( new TH2D(Form("h2_dvcs_tx_cutlvl%d",h),Form("h2_dvcs_tx_cutlvl%d",h), dvcs_bin1, xb_min, xb_max, dvcs_bin1, tp_min, tp_max ));
  h2_wx.push_back( new TH2D(Form("h2_dvcs_wx_cutlvl%d",h),Form("h2_dvcs_wx_cutlvl%d",h), dvcs_bin1, xb_min, xb_max, dvcs_bin1, w_min, w_max ));
  h2_wq2.push_back( new TH2D(Form("h2_dvcs_wq2_cutlvl%d",h),Form("h2_dvcs_wq2_cutlvl%d",h), dvcs_bin1, qq_min, qq_max, dvcs_bin1, w_min, w_max ));
  

}

void BDVCSHistograms::DVCSKinHistIC( Int_t h ){

  h1_qq_ic.push_back(  new TH1D(Form("h1_dvcs_qq_cutlvl%d_ic",h),Form("h1_dvcs_qq_cutlvl%d_ic",h), dvcs_bin1, qq_min, qq_max) );
  h1_w_ic.push_back(  new TH1D(Form("h1_dvcs_w_cutlvl%d_ic",h),Form("h1_dvcs_w_cutlvl%d_ic",h), dvcs_bin1, w_min, w_max) );
  h1_xb_ic.push_back(  new TH1D(Form("h1_dvcs_xb_cutlvl%d_ic",h),Form("h1_dvcs_xb_cutlvl%d_ic",h), dvcs_bin1, xb_min, xb_max) );
  h1_t_ic.push_back(  new TH1D(Form("h1_dvcs_t_cutlvl%d_ic",h),Form("h1_dvcs_t_cutlvl%d_ic",h), dvcs_bin1, t_min, t_max) );
  h1_tp_ic.push_back(  new TH1D(Form("h1_dvcs_tp_cutlvl%d_ic",h),Form("h1_dvcs_tp_cutlvl%d_ic",h), dvcs_bin1, tp_min, tp_max) );
  h1_MM_ic.push_back(  new TH1D(Form("h1_dvcs_mm_cutlvl%d_ic",h),Form("h1_dvcs_mm_cutlvl%d_ic",h), dvcs_bin1, -1, 4.0) );
  h1_MM2epg_ic.push_back(  new TH1D(Form("h1_dvcs_mm2epg_cutlvl%d_ic",h),Form("h1_dvcs_mm2epg_cutlvl%d_ic",h), dvcs_bin1, MM2epg_min, MM2epg_max) );
  h1_eps_ic.push_back(  new TH1D(Form("h1_dvcs_eps_cutlvl%d_ic",h),Form("h1_dvcs_eps_cutlvl%d_ic",h), dvcs_bin1, eps_min, eps_max) );
  h1_deltatheta_ic.push_back(  new TH1D(Form("h1_dvcs_deltatheta_cutlvl%d_ic",h),Form("h1_dvcs_deltatheta_cutlvl%d_ic",h), dvcs_bin1, deltatheta_min, deltatheta_max) );
  h1_deltaphi_ic.push_back(  new TH1D(Form("h1_dvcs_deltaphi_cutlvl%d_ic",h),Form("h1_dvcs_deltaphi_cutlvl%d_ic",h), dvcs_bin1, deltaphi_min, deltaphi_max) );
  h1_phi_ic.push_back(  new TH1D(Form("h1_dvcs_phi_cutlvl%d_ic",h),Form("h1_dvcs_phi_cutlvl%d_ic",h), dvcs_bin1, phi_min, phi_max) );
  h1_Dephi_ic.push_back(  new TH1D(Form("h1_dvcs_dephi_cutlvl%d_ic",h),Form("h1_dvcs_dephi_cutlvl%d_ic",h), dvcs_bin1, Dephi_min, Dephi_max) );
  h1_perpx_ic.push_back(  new TH1D(Form("h1_dvcs_perpx_cutlvl%d_ic",h),Form("h1_dvcs_perpx_cutlvl%d_ic",h), dvcs_bin1, perpx_min, perpx_max) );
  h1_perpy_ic.push_back(  new TH1D(Form("h1_dvcs_perpy_cutlvl%d_ic",h),Form("h1_dvcs_perpy_cutlvl%d_ic",h), dvcs_bin1, perpy_min, perpy_max) );
  h1_pPerp_ic.push_back(  new TH1D(Form("h1_dvcs_pPerp_cutlvl%d_ic",h),Form("h1_dvcs_pPerp_cutlvl%d_ic",h), dvcs_bin1, pPerp_min, pPerp_max) );

  h2_q2x_ic.push_back( new TH2D(Form("h2_dvcs_q2x_cutlvl%d_ic",h),Form("h2_dvcs_q2x_cutlvl%d_ic",h), dvcs_bin1, xb_min, xb_max, dvcs_bin1, qq_min, qq_max ) );
  h2_tx_ic.push_back( new TH2D(Form("h2_dvcs_tx_cutlvl%d_ic",h),Form("h2_dvcs_tx_cutlvl%d_ic",h), dvcs_bin1, xb_min, xb_max, dvcs_bin1, tp_min, tp_max ) );
  h2_wx_ic.push_back( new TH2D(Form("h2_dvcs_wx_cutlvl%d_ic",h),Form("h2_dvcs_wx_cutlvl%d_ic",h), dvcs_bin1, xb_min, xb_max, dvcs_bin1, w_min, w_max ) );
  h2_wq2_ic.push_back( new TH2D(Form("h2_dvcs_wq2_cutlvl%d_ic",h),Form("h2_dvcs_wq2_cutlvl%d_ic",h), dvcs_bin1, qq_min, qq_max, dvcs_bin1, w_min, w_max ) );

 
}

void BDVCSHistograms::AsymHistA( Int_t h ){

  h1_Aepgyield_pp.push_back( new TH1D(Form("h1_Aepgyield_PP_cutlvl%d",h),Form("h1_Aepgyield_PP_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_pn.push_back( new TH1D(Form("h1_Aepgyield_PN_cutlvl%d",h),Form("h1_Aepgyield_PN_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_np.push_back( new TH1D(Form("h1_Aepgyield_NP_cutlvl%d",h),Form("h1_Aepgyield_NP_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_nn.push_back( new TH1D(Form("h1_Aepgyield_NN_cutlvl%d",h),Form("h1_Aepgyield_NN_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_PPPN.push_back( new TH1D(Form("h1_Aepgyield_PPPN_cutlvl%d",h),Form("h1_Aepgyield_PPPN_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_PPPN_pol.push_back( new TH1D(Form("h1_Aepgyield_PPPN_pol_cutlvl%d",h),Form("h1_Aepgyield_PPPN_pol_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_NPNN.push_back( new TH1D(Form("h1_Aepgyield_NPNN_cutlvl%d",h),Form("h1_Aepgyield_NPNN_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aepgyield_NPNN_pol.push_back( new TH1D(Form("h1_Aepgyield_NPNN_pol_cutlvl%d",h),Form("h1_Aepgyield_NPNN_pol_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aasymmetry_Top.push_back( new TH1D(Form("h1_Aasymmetry_top_cutlvl%d",h),Form("h1_Aasymmetry_top_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Aasymmetry_Bot.push_back( new TH1D(Form("h1_Aasymmetry_bot_cutlvl%d",h),Form("h1_Aasymmetry_bot_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );
  h1_Atargetasymmetry.push_back( new TH1D(Form("h1_Atargetasymmetry_cutlvl%d",h),Form("h1_Atargetasymmetry_cutlvl%d",h), Aasymbin1, Aasy_min, Aasy_max ) );


}

void BDVCSHistograms::AsymHistB( Int_t h ){

  h1_Bepgyield_pp.push_back( new TH1D(Form("h1_Bepgyield_PP_cutlvl%d",h),Form("h1_Bepgyield_PP_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_pn.push_back( new TH1D(Form("h1_Bepgyield_PN_cutlvl%d",h),Form("h1_Bepgyield_PN_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_np.push_back( new TH1D(Form("h1_Bepgyield_NP_cutlvl%d",h),Form("h1_Bepgyield_NP_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_nn.push_back( new TH1D(Form("h1_Bepgyield_NN_cutlvl%d",h),Form("h1_Bepgyield_NN_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_PPPN.push_back( new TH1D(Form("h1_Bepgyield_PPPN_cutlvl%d",h),Form("h1_Bepgyield_PPPN_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_PPPN_pol.push_back( new TH1D(Form("h1_Bepgyield_PPPN_pol_cutlvl%d",h),Form("h1_Bepgyield_PPPN_pol_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_NPNN.push_back( new TH1D(Form("h1_Bepgyield_NPNN_cutlvl%d",h),Form("h1_Bepgyield_NPNN_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Bepgyield_NPNN_pol.push_back( new TH1D(Form("h1_Bepgyield_NPNN_pol_cutlvl%d",h),Form("h1_Bepgyield_NPNN_pol_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Basymmetry_Top.push_back( new TH1D(Form("h1_Basymmetry_top_cutlvl%d",h),Form("h1_Basymmetry_top_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Basymmetry_Bot.push_back( new TH1D(Form("h1_Basymmetry_bot_cutlvl%d",h),Form("h1_Basymmetry_bot_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );
  h1_Btargetasymmetry.push_back( new TH1D(Form("h1_Btargetasymmetry_cutlvl%d",h),Form("h1_Btargetasymmetry_cutlvl%d",h), Basymbin1, Basy_min, Basy_max ) );

}




