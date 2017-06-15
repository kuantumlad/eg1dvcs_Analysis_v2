#define histogramtools_cxx

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/HistogramTool.h"
//#include "../include/PhysicsEvent.h"
#include "../include/Calculator.h"

#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH1I.h"
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
#include <THnSparse.h>


HistogramTool::HistogramTool(){

  // h_outfile = new TFile("hns_PID.root", "recreate" );
  // tofile = new TDirectory("tofile","tofile","recreate");
  // h_outfile->mkdir("tof");
  // tofile->cd();
  
  // particledirectory[0] = h_outfile->mkdir("electron");
  // particledirectory[1] = h_outfile->mkdir("proton");
  // particledirectory[2] = h_outfile->mkdir("photonIC");
  // particledirectory[3] = h_outfile->mkdir("photonEC");
 
  // particledirectory[0]->cd();
  // electronD1 = 8;
  // electronD2 = 4;
  // Int_t electronbin1[8] = {100,100,100,100,100,100,100,100};
  // Int_t electronbin2[4] = {100, 100,100,100};
  // //Order of electronsparse1 is mntm, ecinner, ecoutter, nphe, timing, theta, phi, etot
  // Double_t electronmin1[8] = { 0.0, 0.0, 0.0, 0, -3.0/1000000000.0, 0.0, -200.0, 0.0};
  // Double_t electronmax1[8] = { 7.0, 0.3, 0.2, 300.0, 5.0/1000000000.0, 50.0, 200.0, 5.5 };
  // // Order of electronsparse2 is ecx, ecy, icx, icy
  // Double_t electronmin2[4] = { -400.0, -400.0, -50.0, -50.0 };
  // Double_t electronmax2[4] = { 400.0, 400.0,50.0, 50.0 };
  // hns_electron1 = new THnSparseD("hns_electron1","hns_electron1", electronD1, electronbin1, electronmin1, electronmax1 );
  // hns_electron2 = new THnSparseD("hns_electron2","hns_electron2", electronD2, electronbin2, electronmin2, electronmax2 );
  // tofile->cd();

  
  c1 = new TCanvas("c1","Electron with Stage 1 Cuts", 1400, 1400 );
  c2 = new TCanvas("c2","Proton with Stage 1 Cuts", 1400, 1400 );
  c3 = new TCanvas("c3","Photon with Stage 2 Cuts", 1800, 1400 );
  c4 = new TCanvas("c4","Exclusivity Cuts", 1600, 800 );
  c5 = new TCanvas("c5","IC Photon Cuts", 1400, 1400 );
  c6 = new TCanvas("c6","Test Cuts", 1600, 800 );

  c1->Divide(5,3);
  h_electronmomentum = new TH1D("h_electronmomentum","",100, 0.0, 7.0 );
  h_ecinner = new TH1D("h_ecinner","",100, 0.0, 0.3 );
  h_ecouter = new TH1D("h_ecouter","",100, 0.0, 0.2 );
  h_ecouterVSinner = new TH2D("h_ecouterVSinner","",100, 0.0, 0.4, 100, 0.0, 0.2 );
  h_nphe = new TH1D("Nphe", "", 100, 0.0, 300.0 );
  h_timingcut = new TH2D("timing with cuts","", 100, 0.0, 300.0, 100, -1.0/1000000000.0, 15.0/1000000000.0);
  h_ECFiducial = new TH2D( "EC_fidcuts","", 200, -400.0, 400.0, 200, -400.0, 400.0);
  h_icprojection = new TH2D(" Projection onto IC","",  100, -50.0, 50.0, 100, -50.0, 50.0 );
  h_electronTheta = new TH1D("electron theta ","", 100, 0.0, 50.0 );
  h_electronPhi = new TH1D("electron phi","", 100, -200.0, 200.0 );
  h_electronMntmTheta = new TH2D("electron p vs theta","", 100, 0.0, 6.0, 100, 0.0, 100.0 );
  h_electronThetaPhi = new TH2D("electron theta vs phi","", 100, 0.0, 60.0, 200, -200.0, 200.0 );
  h_electronEtotPvsP = new TH2D("h_electronEtotPvsP","",100,0.0,5.0,100,0.15,0.55);


  c2->Divide(4,2);
  betavsmntm = new TH2D("betavsmntm","", 100, 0.20, 2.0, 100, -0.20, 0.80 );
  h22betavsmntm = new TH2D("h22betavsmntm","", 100, 0.20, 2.0, 100, -0.20, 0.80 );
  h_h22beta  = new TH2D("h_h22beta","", 100, 0.0, 2.0, 100, 0.0, 1.2 );
  h_vertexZproton = new TH1D("protonvertex","", 100, -8.0, 8.0 );
  h_icprojectionproton = new TH2D("Proton Projection onto IC","", 100, -50.0, 50.0, 100, -50.0, 50.0 );
  h_protonMntm = new TH1D("proton momentum ","", 100, 0.0, 6.0 );
  h_protonTheta = new TH1D("proton theta ","", 100, 0.0, 50.0 );
  h_protonPhi = new TH1D("proton phi","", 100, -200.0, 200.0 );
  h_protonMntmTheta = new TH2D("proton p vs theta","", 100, 0.0, 6.0, 100, 0.0, 100.0 );
  h_protonThetaPhi = new TH2D("proton theta vs phi","", 100, 0.0, 100.0, 200, -200, 200.0 );
  
  c3->Divide(3,1);
  h_ecdep = new TH1D("h_ecdep","", 100, 0.0, 6.0 );
  h_h22betaphoton = new TH2D("h22beta","", 100, 0.0, 2.0, 100, 0.0, 1.2 );
  h_ec = new TH2D( "EC_photonfidcuts","", 200, -400, 400, 200, -400.0, 400.0);
  h_icprojectionphoton = new TH2D("EC Photon Projection onto IC","", 100, -50.0, 50.0, 100, -50.0, 50.0);
  h_photonMntm = new TH1D("photon momentum ","", 100, 0.0, 6.0 );
  h_photonTheta = new TH1D("photon theta ","", 100, 0.0, 50.0 );
  h_photonPhi = new TH1D("photon phi","", 100, -200.0, 200.0 );
  h_photonMntmTheta = new TH2D("photon p vs theta","", 100, 0.0, 6.0, 100, 0.0, 100.0 );
  h_photonThetaPhi = new TH2D("EC photon theta vs phi","", 100, 0.0, 50.0, 200, -200.0, 200.0 );

  c4->Divide(3,2);
  h_q2 = new TH1D("h_q2","",100, 0.0, 5.0 );
  h_w = new TH1D("h_w","", 100, -1.0, 5.0 );
  h_elE = new TH1D("h_elE","", 100, 0.0, 5.8 );
  h_elpx = new TH1D("h_elpx","", 100,-3.0, 3.0 );
  h_elpy= new TH1D("h_elpy","", 100, -3.0, 3.0 );
  h_elpz = new TH1D("h_elpz","", 100, 0.0, 5.0 );

  c5->Divide(3,1);
  h_icenergy = new TH1D("h_icenergy","",100, 0.0, 5.0);
  h_ichitposition = new TH2D("h_ichitposition", "", 200, -16.0, 16.0, 200, -16.0, 16.0);
  //h_ichitposition = new TH2D("h_ichitposition", "", 200, -10.0, 0.0, 200, -10.0, 0.0);
  h_icphoton = new TH2D("icphoton","",100, 3.5, 16.0, 100, 0.0, 4.0 );
  h_ictimeraw = new TH1D("h_ictimeraw","",150,-100.0, 100.0 );
  h_icphotonTheta = new TH1D("IC photon theta ","", 100, 0.0, 20.0 );
  h_icphotonPhi = new TH1D("IC photon phi","", 100, -200.0, 200.0 );
  h_icphotonThetaPhi = new TH2D("IC photon theta vs phi","", 100, 0.0, 20.0, 400, -200.0, 200.0 );
  h_icphotonEtheta = new TH2D("IC photon energy vs theta ","", 100, 0.0, 15.0, 100, 0.0, 2.0 );

  c6->Divide(4,2);
  h_test1 = new TH1I("h_test1","", 10, 0, 10);
  h_test1a = new TH1D("h_ez","",100, 45.0, 80.0 );
  h_pz = new TH1D("h_pz","",100,45.0,80.0);
  h_epz = new TH1D("h_epz","",100,45.0,80.0);
  h_ezc = new TH1D("h_ezc","",100,45.0,80.0);
  h_pzc = new TH1D("h_pzc","",100,45.0,80.0);
  h_epzc = new TH1D("h_epzc","",100,45.0,80.0);
  h_vzsum = new TH1D ("h_epvzsum","",120,45.0,150.0);
  h_test2 = new TH2D("h_test2","", 100, -100, 100, 100, 0, 5.0 );
  h_pr_pc = new TH1D("h_pr_pc","",100, 0.0, 5.0 );
  //h_numphotons = new TH1D("h_numphotons","", 100, 0.0, 10.0);

  numelectronevents = 0; numprotonevents = 0;  

}

HistogramTool::~HistogramTool(){
  //delete testsparse;
}



void HistogramTool::MakeElectronPlots( Eventh22 tempevent, Int_t tempgindex, Calculator tempcalc ){

  //ECplaneRotated planes;
  //CCSCCut chtimediff;
  Double_t timediff = chtimediff.ReturnTimeDiff(tempevent, tempgindex );
  TVector3 UVWplane = planes.UVW(tempevent, tempgindex);
  TVector3 uvwhall = planes.UVWhallcord(tempevent, tempgindex);
  Double_t u = UVWplane.X();
  Double_t v = UVWplane.Y();
  Double_t x = uvwhall.X();
  Double_t y = uvwhall.Y();
  double ecx = tempevent.ech_x[tempgindex];
  double ecy = tempevent.ech_y[tempgindex];
  double ecz = tempevent.ech_z[tempgindex];
  TVector3 ic_pos = calculate.ICHitPosition( tempcalc.run , tempevent, tempgindex );
  h_electronmomentum->Fill(tempevent.p[tempgindex]);
  h_ecinner->Fill(tempevent.ec_ei[tempgindex]);
  h_ecouter->Fill(tempevent.ec_eo[tempgindex]);
  h_ecouterVSinner->Fill(tempevent.ec_ei[tempgindex], tempevent.ec_eo[tempgindex]);
  h_timingcut->Fill(tempevent.nphe[tempgindex], timediff);
  h_nphe->Fill(tempevent.nphe[tempgindex]);
  h_ECFiducial->Fill(x, y);
  Double_t cmntm = tempevent.p[tempgindex];
  Double_t px = tempevent.cx[tempgindex];
  Double_t py = tempevent.cy[tempgindex];
  Double_t pz = sqrt( 1 - px*px - py*py );
  Double_t p4 = TMath::Sqrt(cmntm*cmntm + 0.938*0.938);
  TLorentzVector eLV;
  eLV.SetPxPyPzE(cmntm*px, cmntm*py, cmntm*pz, p4 );
  h_electronTheta->Fill( eLV.Theta()*(180.0/TMath::Pi()) );
  h_electronPhi->Fill( eLV.Phi()*(180.0/TMath::Pi()) );
  h_electronMntmTheta->Fill( tempevent.p[tempgindex], eLV.Theta()*(180.0/TMath::Pi()) );
  h_electronThetaPhi->Fill( eLV.Theta()*(180.0/TMath::Pi()), eLV.Phi()*(180.0/TMath::Pi()) );
  h_icprojection->Fill( ic_pos.X(), ic_pos.Y() );
  h_electronEtotPvsP->Fill( tempevent.p[tempgindex], tempevent.etot[tempgindex]/(tempevent.p[tempgindex]) );

  //particledirectory[0]->cd();
  //Order of hsn_electron1 is mntm, ecinner, ecoutter, nphe, timing, theta, phi, etot
  //Double_t electroncontent1[8] = { tempevent.p[tempgindex], tempevent.ec_ei[tempgindex], tempevent.ec_eo[tempgindex], tempevent.nphe[tempgindex]*1.0, timediff, eLV.Theta()*(180.0/TMath::Pi()), eLV.Phi()*(180.0/TMath::Pi()), tempevent.etot[tempgindex]/(tempevent.p[tempgindex])  };
  // Order of electronsparse2 is ecx, ecy, icx, icy
  //Double_t electroncontent2[4] = { x, y, ic_pos.X(), ic_pos.Y()  };
  //hns_electron1->Fill(electroncontent1,1);
  // hns_electron2->Fill(electroncontent2,1);  
  // tofile->cd();
}

void HistogramTool::MakeProtonPlots( Eventh22 tempevent, Int_t tempgindex, Calculator tempcalc, Int_t temprun  ){

  TGeoPolygon icborder(10);
  Double_t x_iccut[10] = {-11.5, -11.5, -23.10, -23.10, -10.30, 9.91, 23.73, 23.73, 12.30, 12.30 };
  Double_t y_iccut[10] = {-26.07, -23.10, -12.85, 11.50, 22.95, 22.95, 13.10, -12.40, -22.36, -26.07};
  icborder.SetXY(x_iccut,y_iccut);
  icborder.FinishPolygon();

  TVector3 ic_pos = calculate.ICHitPosition( tempcalc.run, tempevent, tempgindex );
    
  DeltaBetaCut betadiff;
  Double_t h22betadiff = betadiff.h22betadiff( tempevent, tempgindex );
  h22betavsmntm->Fill( tempevent.p[tempgindex], h22betadiff );
  h_h22beta->Fill( tempevent.p[tempgindex], tempevent.b[tempgindex] );

  Double_t *vz_corrected = calculate.CosineCorrection( temprun, tempevent, tempgindex);
  Double_t Zvertex = vz_corrected[3];
  h_vertexZproton->Fill(Zvertex - tempcalc.targetPos);
  
  h_icprojectionproton->Fill(ic_pos.X(), ic_pos.Y() );
  h_protonMntm->Fill( tempevent.p[tempgindex] );
  Double_t cmntm = tempevent.p[tempgindex];
  Double_t px = tempevent.cx[tempgindex];
  Double_t py = tempevent.cy[tempgindex];
  Double_t pz = sqrt( 1 - px*px - py*py );
  Double_t p4 = TMath::Sqrt(cmntm*cmntm);
  TLorentzVector pLV;
  pLV.SetPxPyPzE(cmntm*px, cmntm*py, cmntm*pz, p4 );  
  h_protonTheta->Fill( pLV.Theta()*(180.0/TMath::Pi()) );
  h_protonPhi->Fill( pLV.Phi()*(180.0/TMath::Pi()) );
  h_protonMntmTheta->Fill(  tempevent.p[tempgindex], pLV.Theta()*(180.0/TMath::Pi()) );
  h_protonThetaPhi->Fill(pLV.Theta()*180./TMath::Pi(), pLV.Phi()*180./TMath::Pi() );
}

void HistogramTool::MakePhotonPlots( Eventh22 tempevent, Int_t tempgindex, Calculator tempcalc ){
  
  ECplaneRotated planes;
  TVector3 uvwhall = planes.UVWhallcord(tempevent, tempgindex);
  Double_t x = uvwhall.X();
  Double_t y = uvwhall.Y();

  Double_t etotphoton = tempevent.etot[tempgindex];

 Double_t mntm = tempevent.p[tempgindex];
 Double_t px = tempevent.cx[tempgindex];
 Double_t py = tempevent.cy[tempgindex];
 Double_t pz = sqrt( 1 - px*px - py*py );
 Double_t p4 = mntm;
 TLorentzVector phLV;
 phLV.SetPxPyPzE(mntm*px, mntm*py, mntm*pz, p4 );  

 TGeoPolygon icborder(10);
 Double_t x_iccut[10] = {-11.5, -11.5, -23.10, -23.10, -10.30, 9.91, 23.73, 23.73, 12.30, 12.30 };
 Double_t y_iccut[10] = {-26.07, -23.10, -12.85, 11.50, 22.95, 22.95, 13.10, -12.40, -22.36, -26.07};
 icborder.SetXY(x_iccut,y_iccut);
 icborder.FinishPolygon();

 TVector3 ic_pos = calculate.ICHitPosition( tempcalc.run, tempevent, tempgindex );
 h_icprojectionphoton->Fill( ic_pos.X(), ic_pos.Y() );

 
 h_ecdep->Fill((etotphoton)/0.273);
 h_h22betaphoton->Fill(tempevent.etot[tempgindex], tempevent.b[tempgindex]);
 h_ec->Fill(x,y);
 h_photonMntm->Fill( mntm );
 h_photonTheta->Fill( phLV.Theta()*(180.0/TMath::Pi()) );
 h_photonPhi->Fill( phLV.Phi()*(180.0/TMath::Pi()) );
 h_photonThetaPhi->Fill( phLV.Theta()*(180.0/TMath::Pi()), phLV.Phi()*(180.0/TMath::Pi()) );

 
}

void HistogramTool::MakeICPhotonPlots( Eventh22 tempevent, Int_t tempsindex, Int_t temprunnum ){

  h_icenergy->Fill(tempevent.etc[tempsindex]);
  //  h_ichitposition->Fill( tempevent.xc[tempsindex], tempevent.yc[tempsindex] );
  h_ictimeraw->Fill( tempevent.tc[tempsindex] );

  Double_t xx_o = tempevent.xc[tempsindex];
  Double_t yy_o = tempevent.yc[tempsindex];
  
  Double_t *xy_c = calculate.RasterCorrection( temprunnum, tempevent, tempsindex);
  Double_t xx = xy_c[0];//xx_o - xy_c[0];
  Double_t yy = xy_c[1];//yy_o - xy_c[1];
  TVector3 icph3V;
  icph3V.SetX(xx);
  icph3V.SetY(yy);
  icph3V.SetZ(-tempevent.vz[0]);

  Double_t icph_phi = icph3V.Phi()*(180.0/TMath::Pi()); 

  // if( icph_phi < -140.0 && icph_phi > -120.0 ){
  
  
  //incidentpartLV.SetPxPyPzE(tempevent.etc[tempsindex]*TMath::Sin(icph3V.Theta())*TMath::Cos(icph3V.Phi()),
  //			    tempevent.etc[tempsindex]*TMath::Sin(icph3V.Theta())*TMath::Sin(icph3V.Phi()),
  ///			    tempevent.etc[tempsindex]*TMath::Cos(icph3V.Theta()),
  //			    tempevent.etc[tempsindex]);
  // TGeoPolygon icborder(4);
  // Double_t x_iccut[4] = { -6.1, -4.6, -4.6, -6.1};//-11.5, -11.5, -23.10, -23.10, -10.30, 9.91, 23.73, 23.73, 12.30, 12.30 };
  // Double_t y_iccut[4] = {-8.45, -7.1, -7.1, -8.45 };//-26.07, -23.10, -12.85, 11.50, 22.95, 22.95, 13.10, -12.40, -22.36, -26.07};
  // icborder.SetXY(x_iccut, y_iccut);
  // icborder.FinishPolygon();
  // icborder.Draw();
  
  h_ichitposition->Fill( xx, yy );
  h_icphoton->Fill(sqrt( xx*xx + yy*yy), tempevent.etc[tempsindex]);
  h_icphotonEtheta->Fill( icph3V.Theta()*(180.0/TMath::Pi()), tempevent.etc[tempsindex] );

  h_icphotonTheta->Fill( icph3V.Theta()*(180.0/TMath::Pi()) );
  h_icphotonPhi->Fill( icph3V.Phi()*(180.0/TMath::Pi()) );
  h_icphotonThetaPhi->Fill( icph3V.Theta()*(180.0/TMath::Pi()), icph3V.Phi()*(180.0/TMath::Pi()) );
  // }
}

void HistogramTool::MakeExclusivityPlots( PhysicsEvent dvcs ){

  h_q2->Fill(dvcs.Q2);
  h_w->Fill( dvcs.w );
  //  std::cout << " filling with " << dvcs.pel << std::endl;
  h_elE->Fill( dvcs.pel );
  h_elpx->Fill( dvcs.detectedElectron.Px() );
  h_elpy->Fill( dvcs.detectedElectron.Py() );
  h_elpz->Fill( dvcs.detectedElectron.Pz() );  

}

void HistogramTool::TestPlots( Int_t number ){// Int_t numelectronevents, Int_t numprotonevents ){

  //h_test1->Fill( number );
  // Hold the total number of Events with at least one electron and at least one proton
  //std::cout <<" " <<  numelectronevents++ << std::endl;
  //h_test1->Fill( numelectronevents );
  //numprotonevents++;
  //  h_test1->Fill(testvar);

  
}

void HistogramTool::TestPlot1D( Double_t ezc, Double_t pzc, Double_t epzc, Double_t ez, Double_t pz, Double_t epz ){

  h_test1a->Fill(ez);
  //  h_pz->Fill(pz);
  h_epz->Fill(epz);
  h_ezc->Fill(ezc);
  //h_pzc->Fill(pzc);
  h_epzc->Fill(epzc);

}

void HistogramTool::FillPZ( double pv, double pvc, double epsum, double pr_pc ){

  h_pz->Fill(pv);
  h_pzc->Fill( pvc );
  h_vzsum->Fill( epsum );
  h_pr_pc->Fill(pr_pc);



}


void HistogramTool::DrawHistograms(){
  //h_outfile->Write();
  //delete h_outfile;
  // particledirectory[0]->cd();
  // hns_electron1->Write();
  // tofile->cd();
  // h_outfile->Write();
  
  Double_t ymax = h_ecinner->GetMaximum();
  Float_t energycut_pion = 0.060;
  TLine *pioncut = new TLine( energycut_pion, 0.0, energycut_pion, ymax );
  TLine *pioncut2 = new TLine( energycut_pion, 0.015, energycut_pion, 0.20 );
  //std::cout << " Total Events wal 1 proton " << h_test1->GetEntries() << std::endl;

  c1->cd(1);
  h_ecinner->Draw();
  h_ecinner->SetTitle("EC_{inner} for Electron Candidates");
  h_ecinner->GetXaxis()->SetTitle("E_{inner} [GeV]");
  h_ecinner->GetXaxis()->CenterTitle();
  pioncut->SetLineColor(2);
  pioncut->Draw("same");
  //std::cout << " Total entries " << h_ecinner->GetEntries() << std::endl;
  
  c1->cd(2);
  h_ecouter->Draw();
  h_ecouter->SetTitle("EC_{outer} for Electron Candidates");
  h_ecouter->GetXaxis()->SetTitle("E_{outer} [GeV]");
  h_ecouter->GetXaxis()->CenterTitle();

  c1->cd(3);  
  h_ecouterVSinner->Draw("colz");
  h_ecouterVSinner->SetTitle("EC_{in} vs EC_{outer} for Electron Candidates");
  h_ecouterVSinner->GetXaxis()->SetTitle("E_{inner}");
  h_ecouterVSinner->GetXaxis()->CenterTitle();
  h_ecouterVSinner->GetYaxis()->SetTitle("E_{outer}");
  h_ecouterVSinner->GetYaxis()->CenterTitle();
  pioncut2->SetLineColor(2);
  pioncut2->Draw("same");

  c1->cd(4);
  h_electronmomentum->GetXaxis()->SetTitle("p_{neg charge} (GeV)");
  h_electronmomentum->GetYaxis()->SetTitle("Number of Events");
  h_electronmomentum->GetXaxis()->CenterTitle();
  h_electronmomentum->GetYaxis()->CenterTitle();
  h_electronmomentum->Draw();
  h_electronmomentum->SetTitle("Momentum histogram for Electron Candidates");
  h_electronmomentum->Draw();

  c1->cd(5);
  h_timingcut->Draw("colz");
  h_timingcut->SetTitle("#Delta (Cherenkov) time vs N_{phe} for Electron Candidates (A & B)");
  h_timingcut->GetXaxis()->SetTitle("N_{phe} x 10 ");
  h_timingcut->GetXaxis()->CenterTitle();
  h_timingcut->GetYaxis()->SetTitle("#Deltat [ns]");
  h_timingcut->GetYaxis()->CenterTitle();
  
  c1->cd(6);
  h_nphe->Draw();
  h_nphe->SetTitle("N_{phe} from Electron Candidates ");
  h_nphe->GetXaxis()->SetTitle("N_{phe} x 10 ");
  h_nphe->GetXaxis()->CenterTitle();

  c1->cd(7);
  h_ECFiducial->SetTitle("EC Fiducial Cuts for Electron Candidates");
  h_ECFiducial->GetXaxis()->SetTitle("EC x [cm]");
  h_ECFiducial->GetYaxis()->SetTitle("EC y [cm]");
  h_ECFiducial->GetXaxis()->CenterTitle();
  h_ECFiducial->GetYaxis()->CenterTitle();
  h_ECFiducial->Draw("colz");

  c1->cd(8);
  h_icprojection->SetTitle("IC Projection Electron Candidates");
  h_icprojection->GetXaxis()->SetTitle("IC x [cm]");
  h_icprojection->GetYaxis()->SetTitle("IC y [cm]");
  h_icprojection->GetXaxis()->CenterTitle();
  h_icprojection->GetYaxis()->CenterTitle();
  h_icprojection->Draw("colz");


  c1->cd(9);
  h_electronTheta->Draw();
  h_electronTheta->GetXaxis()->SetTitle("Theta (deg)");
  h_electronTheta->GetYaxis()->SetTitle("Counts");
  h_electronTheta->GetXaxis()->CenterTitle();
  h_electronTheta->GetYaxis()->CenterTitle();
  c1->cd(10);
  h_electronPhi->GetXaxis()->SetTitle("Phi (deg)");
  h_electronPhi->GetYaxis()->SetTitle("Counts");
  h_electronPhi->GetXaxis()->CenterTitle();
  h_electronPhi->GetYaxis()->CenterTitle();
  h_electronPhi->Draw();
  c1->cd(11);
  h_electronMntmTheta->GetXaxis()->SetTitle("Mntm [GeV]");
  h_electronMntmTheta->GetYaxis()->SetTitle("Theta [deg]");
  h_electronMntmTheta->GetXaxis()->CenterTitle();
  h_electronMntmTheta->GetYaxis()->CenterTitle();
  h_electronMntmTheta->Draw("colz");

  c1->cd(12);
  h_electronThetaPhi->GetXaxis()->SetTitle("Theta  [deg]");
  h_electronThetaPhi->GetYaxis()->SetTitle("Phi [deg]");
  h_electronThetaPhi->GetXaxis()->CenterTitle();
  h_electronThetaPhi->GetYaxis()->CenterTitle();
  h_electronThetaPhi->Draw("colz");

  c1->cd(13);
  h_electronEtotPvsP->GetXaxis()->SetTitle("Momentum [GeV/c]");
  h_electronEtotPvsP->GetYaxis()->SetTitle("E_{tot}/Momentum [c]");
  h_electronEtotPvsP->GetXaxis()->CenterTitle();
  h_electronEtotPvsP->GetYaxis()->CenterTitle();
  h_electronEtotPvsP->Draw("colz");
  
  // c1->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ElectronResults_v1.pdf");
  //   c1->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/ElectronResults_v1png.png");
  // c1->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ElectronResults_v1jpg.jpg");

  
 /* 

  Proton Histograms 

  */
  
  //Make visible cuts using TLine or TF1
  TLine *topcut = new TLine( 0.20, 0.05, 2.0, 0.05);
  TLine *botcut = new TLine( 0.20, -0.05, 2.0, -0.05);

  TF1 *maxbetacut = new TF1("maxbetacut","(x/(sqrt( x*x + [0]*[0])))", 0.30, 2.0);
  TF1 *minbetacut = new TF1("minbetacut","(x/(sqrt( x*x + [0]*[0])))", 0.30, 2.0);
  const Double_t massproton = 0.938;
  const Double_t minmassproton = 0.90*massproton;
  const Double_t maxmassproton = 1.10*massproton;
  maxbetacut->SetParameter(0,minmassproton);
  minbetacut->SetParameter(0,maxmassproton);
  
  c2->cd(1);
  h22betavsmntm->Draw("colz");
  topcut->SetLineColor(kRed);
  botcut->SetLineColor(kRed);
  topcut->Draw("same");
  botcut->Draw("same");
  h22betavsmntm->SetTitle("#Delta#beta_{h22} vs p_{positive} for Proton Candidate");
  h22betavsmntm->GetXaxis()->SetTitle("p (GeV)");
  h22betavsmntm->GetYaxis()->SetTitle("#Delta#beta");
  h22betavsmntm->GetYaxis()->CenterTitle();
  h22betavsmntm->GetXaxis()->CenterTitle();
  h22betavsmntm->GetYaxis()->CenterTitle();

  c2->cd(2);
  h_h22beta->Draw("colz");
  h_h22beta->SetTitle("#beta_{h22} vs p_{positive}");
  h_h22beta->GetXaxis()->SetTitle("p (GeV)");
  h_h22beta->GetYaxis()->SetTitle("#beta");
  h_h22beta->GetXaxis()->CenterTitle();
  h_h22beta->GetYaxis()->CenterTitle();
  maxbetacut->Draw("same");
  minbetacut->Draw("same");

 
  c2->cd(3);
  h_vertexZproton->Draw();
  h_vertexZproton->SetTitle("Z_{vertex} for Proton Candidate");
  h_vertexZproton->GetXaxis()->SetTitle("Z_{vertex} [cm]");
  h_vertexZproton->GetXaxis()->CenterTitle();
  h_vertexZproton->GetYaxis()->CenterTitle();
  
  c2->cd(4);
  h_icprojectionproton->SetTitle("Proton IC Projection Electron Candidates");
  h_icprojectionproton->GetXaxis()->SetTitle("IC x [cm]");
  h_icprojectionproton->GetYaxis()->SetTitle("IC y [cm]");
  h_icprojectionproton->GetXaxis()->CenterTitle();
  h_icprojectionproton->GetYaxis()->CenterTitle();
  h_icprojectionproton->Draw("colz");

  c2->cd(5);
  h_protonMntm->GetXaxis()->SetTitle("Mntm [GeV]");
  h_protonMntm->GetYaxis()->SetTitle("Counts");
  h_protonMntm->GetXaxis()->CenterTitle();
  h_protonMntm->GetYaxis()->CenterTitle();
  h_protonMntm->Draw();
  c2->cd(6);
  h_protonTheta->GetXaxis()->SetTitle("Theta (GeV)");
  h_protonTheta->GetYaxis()->SetTitle("Counts");
  h_protonTheta->GetXaxis()->CenterTitle();
  h_protonTheta->GetYaxis()->CenterTitle();
  h_protonTheta->Draw();
  c2->cd(7);
  h_protonPhi->GetXaxis()->SetTitle("Mntm [GeV]");
  h_protonPhi->GetYaxis()->SetTitle("Theta [deg]");
  h_protonPhi->GetXaxis()->CenterTitle();
  h_protonPhi->GetYaxis()->CenterTitle();
  h_protonPhi->Draw();

  c2->cd(8);
  h_protonMntmTheta->GetXaxis()->SetTitle("Mntm [GeV]");
  h_protonMntmTheta->GetYaxis()->SetTitle("Theta [deg]");
  h_protonMntmTheta->GetXaxis()->CenterTitle();
  h_protonMntmTheta->GetYaxis()->CenterTitle();
  h_protonMntmTheta->Draw("colz");

  c2->cd(9);
  h_protonThetaPhi->GetXaxis()->SetTitle("Theta [deg]");
  h_protonThetaPhi->GetYaxis()->SetTitle("Phi [deg]");
  h_protonThetaPhi->Draw("colz");
  
  // c2->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/ProtonResults_v1.pdf");
  //c2->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/ProtonResults_v1png.png");
  
  /* 

     Photon Histograms 

  */
  
  Double_t ymaxphoton = h_ecdep->GetMaximum();
  Double_t edepmin = 0.30; //GeV
  TLine *edepcut = new TLine( edepmin ,0.0, edepmin, ymaxphoton);
  TLine *photoncut = new TLine( 0.0, 0.95, 2.0, 0.95 );
  TLine *photoncuttop = new TLine( 0.0, 1.06, 2.0, 1.06 );
  TF1 *mollercut = new TF1("mollercut","0.67 - 0.0642674*x",0.0,7.9); //used points (3.6,0.44) (7.49,0.19) and wolfram alpha

  c3->cd(1);
  h_ecdep->Draw("colz");
  h_ecdep->SetTitle("Energy distribution for neutrals using etot");
  h_ecdep->GetXaxis()->SetTitle("Energy [GeV]");
  h_ecdep->GetXaxis()->CenterTitle();
  edepcut->SetLineColor(kRed);
  edepcut->Draw("same");

  c3->cd(2);
  h_h22betaphoton->Draw("colz");
  h_h22betaphoton->SetTitle("#beta_{h22} vs E_{tot} for neutrals in EC");
  h_h22betaphoton->GetXaxis()->SetTitle("Energy [GeV]");
  h_h22betaphoton->GetXaxis()->CenterTitle();
  photoncut->SetLineColor(kRed);
  photoncuttop->SetLineColor(kRed);
  photoncut->Draw("same");
  photoncuttop->Draw("same");

  c3->cd(3);
  h_ec->SetTitle("EC fiducial cuts for photon with all photons cuts");
  h_ec->GetXaxis()->SetTitle("EC x [cm]");
  h_ec->GetYaxis()->SetTitle("EC y [cm]");
  h_ec->GetXaxis()->CenterTitle();
  h_ec->GetYaxis()->CenterTitle();
  h_ec->Draw("colz");

  // c3->cd(4);
  // h_icprojectionphoton->SetTitle("EC photon ic projection");
  // h_icprojectionphoton->GetXaxis()->SetTitle("IC x [cm]");
  // h_icprojectionphoton->GetYaxis()->SetTitle("IC y [cm]");
  // h_icprojectionphoton->GetXaxis()->CenterTitle();
  // h_icprojectionphoton->GetYaxis()->CenterTitle();
  // h_icprojectionphoton->Draw("colz");

  //h_photonThetaPhi->GetXaxis()->SetTitle("Theta [deg]");
  //h_photonThetaPhi->GetYaxis()->SetTitle("Phi [deg]");
  //h_photonThetaPhi->Draw("colz");
  
  // c3->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/PhotonResults_v1.pdf");
  //c3->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/PhotonResults_v1png.png");

  
  /*c4->cd(1);
  h_missingmass->SetTitle("Missing Mass for Elastic Events");
  h_missingmass->GetXaxis()->SetTitle("Mass (GeV)");
  h_missingmass->GetXaxis()->CenterTitle();
  h_missingmass->Draw();

  c4->cd(2);
  h_missingmass2->SetTitle("t_proton for Elastic Events");
  h_missingmass2->GetXaxis()->SetTitle("Mass (GeV)");
  h_missingmass2->GetXaxis()->CenterTitle();
  h_missingmass2->Draw();

  c4->cd(3);
  h_phihadron->SetTitle("#phi_{hadron}");
  h_phihadron->GetXaxis()->SetTitle("Phi [deg]");
  h_phihadron->GetXaxis()->CenterTitle();
  h_phihadron->Draw();
  */
  //c4->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ExclusivityResults_v3.pdf");
  gPad->SetLogz();

  c5->SetLogy();
  c5->cd(1);
  //h_icphoton->Draw("SPEC zs(1)"); 
  // h_icphoton->SetTitle("IC Photons: Moeller Cut");
  // h_icphoton->GetYaxis()->SetTitle("IC Photon Energy [GeV]");
  // h_icphoton->GetXaxis()->SetTitle("IC Hit Radius [cm]");
  // h_icphoton->GetXaxis()->CenterTitle();
  // h_icphoton->GetYaxis()->CenterTitle();
  // h_icphoton->Draw("colz");

  c5->cd(1);
  h_icphotonEtheta->GetXaxis()->SetTitle("#theta_{#gamma} [deg]");  
  h_icphotonEtheta->GetYaxis()->SetTitle("E_{#gamma} [GeV]");
  h_icphotonEtheta->Draw("colz");

  // c5->cd(2);
  // h_icenergy->Draw();
  // h_icenergy->SetTitle("IC Photons: Energy Reconstructed");
  // h_icenergy->GetXaxis()->SetTitle("Energy reconstructed [GeV]");
  // h_icenergy->GetXaxis()->CenterTitle();

  c5->cd(2);
  h_ichitposition->Draw("colz");
  h_ichitposition->SetTitle("IC Photons: IC Hit Position");
  h_ichitposition->GetXaxis()->SetTitle(" x [cm]");
  h_ichitposition->GetYaxis()->SetTitle(" y [cm]");
  h_ichitposition->GetXaxis()->CenterTitle();
  h_ichitposition->GetYaxis()->CenterTitle();

  // c5->cd(4);
  // //gPad->SetLogy();
  // h_ictimeraw->Draw();
  // h_ictimeraw->SetTitle("Timing of Events in the IC");
  // h_ictimeraw->GetXaxis()->SetTitle("tc [ns]");
  // h_ictimeraw->GetXaxis()->CenterTitle();

  // c5->cd(5);
  // h_icphotonTheta->GetXaxis()->SetTitle("Theta [deg]");
  // h_icphotonTheta->Draw();

  //c5->cd(3);
  //h_icphotonPhi->GetXaxis()->SetTitle("Phi [deg]");
  //h_icphotonPhi->Draw();

  // c5->cd(7);
  // h_icphotonThetaPhi->GetXaxis()->SetTitle("Theta [deg]");
  // h_icphotonThetaPhi->GetYaxis()->SetTitle("Phi [deg]");
  // h_icphotonThetaPhi->Draw("colz");

  // c5->cd(8);
  // h_icphotonEtheta->GetXaxis()->SetTitle("#theta_{#gamma} [deg]");  
  // h_icphotonEtheta->GetYaxis()->SetTitle("E_{#gamma} [GeV]");
  // h_icphotonEtheta->Draw("colz");
  
  // c5->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/ICphotons_v1.pdf");
  //std::cout<< " Electron & Proton & Photon Plots Created " << std::endl;

  c4->cd(1);
  //h_test1a->Draw();
  h_q2->Draw();
  c4->cd(2);
  h_w->Draw();
  c4->cd(3);
  h_elE->Draw();
  c4->cd(4);
  h_elpx->Draw();
  c4->cd(5);
  h_elpy->Draw();
  c4->cd(6);
  h_elpz->Draw();
  //c6->cd(7);
  //h_vzsum->Draw();
  //c6->cd(8);
  //h_pr_pc->Draw();
  //  std::cout << h_test1a->GetMean() <<  std::endl;
  //std::cout <<   h_test1a->GetStdDev() << std::endl;
  //std::cout << " bin 0 " << h_test1->GetBinContent(0) << std::endl;
  //std::cout << " bin 1 " << h_test1->GetBinContent(1) << std::endl;
  //std::cout << " bin 2 " << h_test1->GetBinContent(2) << std::endl;
  //std::cout << " bin 3 " << h_test1->GetBinContent(3) << std::endl;
  //std::cout << " bin 4 " << h_test1->GetBinContent(4) << std::endl;
  //std::cout << " bin 5 " << h_test1->GetBinContent(5) << std::endl;
  //std::cout << " bin 6 " << h_test1->GetBinContent(6) << std::endl;
  //std::cout << " bin 7 " << h_test1->GetBinContent(7) << std::endl;
  //std::cout << " bin 8 " << h_test1->GetBinContent(8) << std::endl;
  //std::cout << " bin 9 " << h_test1->GetBinContent(9) << std::endl;
  //std::cout << " bin 10 " << h_test1->GetBinContent(10) << std::endl;
  //Int_t binsum = h_test1->GetBinContent(1) + h_test1->GetBinContent(2) + h_test1->GetBinContent(3) + h_test1->GetBinContent(4) + h_test1->GetBinContent(5) + h_test1->GetBinContent(6) + h_test1->GetBinContent(7) + h_test1->GetBinContent(8) + h_test1->GetBinContent(9) + h_test1->GetBinContent(10);*/
  // std::cout << " TOTAL " << binsum << std::endl;
  //  c6->cd(2);
   // h_test1->Draw();
  //c4->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/analysiscode_v2.1/htest_v1.png");

  /*  
  c1->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sElectronResults_v1.pdf"),tempanalysistype);                                                                                                                                       
  c1->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sElectronResults_v1.png"), tempanalysistype);                                                                                                                                      
  //  c1->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ElectronResults_v1jpg.jpg");                                                                                                                                                   
                                                                                                                                                                                                                                                                           
  c2->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sProtonResults_v1.pdf"), tempanalysistype);                                                                                                                                       
  c2->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sProtonResults_v1.png", tempanalysistype);                                                                                                                                               
                                                                                                                                                                                                                                                                          
  c3->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sECPhotonResults_v1.pdf"), tempanalysistype);                                                                                                                                      
  c3->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sECPhotonResults_v1.png"), tempanalysistype);                                                                                                                                                                                                                                                                                                                                                                                                   
  //  c4->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ExclusivityResults_v3.pdf");                                                                                                                                              
  c5->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sICphotons_v1.pdf"), tempanalysistype );  
  */


}


void HistogramTool::SavePlots(TString tempanalysistype){
  /*
    
  c1->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sElectronResults_v1.pdf"),tempanalysistype);                                    
  c1->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sElectronResults_v1.png"), tempanalysistype); 
  //  c1->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ElectronResults_v1jpg.jpg");

  c2->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sProtonResults_v1.pdf"), tempanalysistype);
  c2->SaveAs("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sProtonResults_v1.png", tempanalysistype); 
 
  c3->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sECPhotonResults_v1.pdf"), tempanalysistype);                                                      
  c3->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sECPhotonResults_v1.png"), tempanalysistype);  

  //  c4->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v2/results/ExclusivityResults_v3.pdf");                                                                                  
  c5->SaveAs(Form("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/tempresults/%sICphotons_v1.pdf"), tempanalysistype );  
  */
}
