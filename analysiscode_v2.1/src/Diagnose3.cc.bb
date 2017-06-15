#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/PhysicsCutManager.h"
#include "../include/PhysicsEvent.h"
#include "../include/EventDVCS.h"
#include "../include/LoadDVCS.h"
#include "../include/HistogramTool.h"
#include "../include/SkimManager.h"
#include "../include/RunDB.h"

#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH3D.h"
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
//Max files on local disk is 362

Int_t main( void ){
  
  TCanvas *c40 = new TCanvas("c40","Asym", 1400, 1400 );
  c40->Divide(1,10);
  
  TH1D *h_Aepgyieldspp = new TH1D("h_AepgyieldsPP", "", 10, 0, 360 );
  TH1D *h_Aepgyieldspn = new TH1D("h_AepgyieldsPN", "", 10, 0, 360 );
  TH1D *h_Aepgyieldsnp = new TH1D("h_AepgyieldsNP", "", 10, 0, 360 );
  TH1D *h_Aepgyieldsnn = new TH1D("h_AepgyieldsNN", "", 10, 0, 360 );
  TH1D *h_AepgyieldsPPPN = new TH1D("h_AepgyieldsPPPN","", 10, 0, 360 );
  TH1D *h_AepgyieldsPPPN_pol = new TH1D("h_AepgyieldsPPPN_pol","", 10, 0, 360 );
  TH1D *h_AepgyieldsNPNN = new TH1D("h_AepgyieldsNPNN","", 10, 0, 360 );
  TH1D *h_AepgyieldsNPNN_pol = new TH1D("h_AepgyieldsNPNN_pol","", 10, 0, 360 );
  TH1D *h_Aasymmetrytop = new TH1D("h_Aasymmetrytop","", 10, 0.0, 360.0 );
  TH1D *h_Aasymmetrybot = new TH1D("h_Aasymmetrybot","", 10, 0.0, 360.0 );
  TH1D *h_Aasymmetry = new TH1D("h_Aasymmetry","", 10, 0.0, 360.0 );

  TH1D *h_Bepgyieldspp = new TH1D("h_BepgyieldsPP", "", 10, 0, 360 );
  TH1D *h_Bepgyieldspn = new TH1D("h_BepgyieldsPN", "", 10, 0, 360 );
  TH1D *h_Bepgyieldsnp = new TH1D("h_BepgyieldsNP", "", 10, 0, 360 );
  TH1D *h_Bepgyieldsnn = new TH1D("h_BepgyieldsNN", "", 10, 0, 360 );
  TH1D *h_BepgyieldsPPPN = new TH1D("h_BepgyieldsPPPN","", 10, 0, 360 );
  TH1D *h_BepgyieldsPPPN_pol = new TH1D("h_BepgyieldsPPPN_pol","", 10, 0, 360 );
  TH1D *h_BepgyieldsNPNN = new TH1D("h_BepgyieldsNPNN","", 10, 0, 360 );
  TH1D *h_BepgyieldsNPNN_pol = new TH1D("h_BepgyieldsNPNN_pol","", 10, 0, 360 );
  TH1D *h_Basymmetrytop = new TH1D("h_Basymmetrytop","", 10, 0.0, 360.0 );
  TH1D *h_Basymmetrybot = new TH1D("h_Basymmetrybot","", 10, 0.0, 360.0 );
  TH1D *h_Basymmetry = new TH1D("h_Basymmetry","", 10, 0.0, 360.0 );
 
  Double_t APtplus = 0.75;
  Double_t APtminus = 0.72;
  Double_t BPtplus = 0.81;
  Double_t BPtminus = 0.75;
  Double_t Adilution = 0.912;
  Double_t Bdilution = 0.928;
  
  
  LoadDVCS tDVCS;
  RunDB eg1rundata;
  tDVCS.MakeChain("/Users/bclary/Documents/work/run data/DVCSresults/",400);
  tDVCS.Init();
  Int_t nentries = tDVCS.NumEntries();
 
  // PhysicsCutManager pmanagertest;
  // CutManager managertest;
  // PhysicsEvent peventtest;

  // pmanagertest.InitializeCutsFor("electron + proton");
  // managertest.InitializeCutsFor("electron");
  // managertest.InitializeCutsFor("proton");
  // managertest.InitializeCutsFor("photon");

  // HistogramTool histtoolto;

  // //PhysicsEventBuilder eventbuild;
  // TLorentzVector electronLVi( 0, 0, 5.95, 5.95 );
  // TLorentzVector protonLVi( 0, 0, 0, 0.938 );
  // PhysicsEventBuilder eventbuild( electronLVi, protonLVi );
  // TLorentzVector protoncandLVf, photoncandLVf;
  
  // Int_t numgoodelectron = 0;
  // Int_t numgoodproton = 0;
  // Int_t numgoodphoton = 0;
  // Int_t counter = 0;

  for( Int_t i = 0; i<nentries; i++ ){
    
    tDVCS.GetEntry(i);
    EventDVCS event = tDVCS.GetEvent();

    eg1rundata.OpenDB();
    TString PeriodID = eg1rundata.Query("RunConfiguration","PeriodID", event.RunNumber );
    TString TargetType = eg1rundata.Query("TargetConfiguration","Target", event.RunNumber );
    eg1rundata.CloseDB();

    if( TargetType == "NH3T" || TargetType == "NH3B" ){
      //std::cout << tempbuild.physicsEvent.periodid << std::endl;
      if( PeriodID == "A" ){
	if( event.TarPol > 0 && event.helicity == 1 ){
	  //std::cout << " target +  helicity + " << std::endl;
	  h_Aepgyieldspp->Fill( event.Phi_Pr );
	}
	if(  event.TarPol  > 0 && event.helicity == 0 ){
	  //std::cout << " target + helicity - " << std::endl;
	  h_Aepgyieldspn->Fill( event.Phi_Pr );
	}
	if(  event.TarPol  < 0 && event.helicity == 1 ){
	  //std::cout << " target - helicity + " << std::endl;
	  h_Aepgyieldsnp->Fill( event.Phi_Pr );
	}
	if(  event.TarPol  < 0 && event.helicity == 0 ){
	  //std::cout << " target - helicity - " << std::endl;
	  h_Aepgyieldsnn->Fill( event.Phi_Pr );
	}
      }
  
      if( PeriodID == "B" ){
	if(  event.TarPol  > 0 && event.helicity == 1 ){
	  //std::cout << " target +  helicity + " << std::endl;
	  h_Bepgyieldspp->Fill( event.Phi_Pr );
	}
	if(  event.TarPol > 0 && event.helicity == 0 ){
	  //std::cout << " target + helicity - " << std::endl;
	  h_Bepgyieldspn->Fill( event.Phi_Pr );
	}
	if(  event.TarPol < 0 && event.helicity == 1 ){
	  //std::cout << " target - helicity + " << std::endl;
	  h_Bepgyieldsnp->Fill( event.Phi_Pr );
	}
	if(  event.TarPol < 0 && event.helicity == 0 ){
	  //std::cout << " target - helicity - " << std::endl;
	  h_Bepgyieldsnn->Fill( event.Phi_Pr );
	}
      }
    }

    // bool electron = managertest.PassCut("electron",eventtest, 0);
    // if( electron ){
    //   numgoodelectron++;
    //   TLorentzVector electronLVf = eventbuild.setParticleLV("electron",eventtest, 0);
      
    //   histtoolto.MakeElectronPlots(eventtest, 0);
    //   bool foundproton = false;
    //   bool foundphoton = false;
    //   for( Int_t k = 1; k < gparts; k++){
    //   	if( !foundproton ){
    //   	  foundproton = managertest.PassCut("proton",eventtest, k);	  
    //   	  //histtoolto.MakeProtonPlots(eventtest, k);
    //   	  protoncandLVf = eventbuild.setParticleLV("proton",eventtest,k);
    //   	}
    //   	if ( !foundphoton ){
    //   	  foundphoton = managertest.PassCut("photon",eventtest, k);
    //   	  //histtoolto.MakePhotonPlots(eventtest, k);
    //   	  photoncandLVf = eventbuild.setParticleLV("photon",eventtest, k);
    //   	}
    //   }
  }

  c40->cd(2);
  gStyle->SetErrorX(0);
  h_Aepgyieldspp->SetMarkerStyle(20);
  h_Aepgyieldspp->SetMarkerSize(1);
  h_Aepgyieldspp->SetMarkerColorAlpha( kRed, 0.35 );
  h_Bepgyieldspp->SetMarkerStyle(20);
  h_Bepgyieldspp->SetMarkerSize(1);
  h_Bepgyieldspp->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Bepgyieldspp->SetTitle("A_{pp} red, B_{pp} blue");
  h_Bepgyieldspp->Draw("P");
  h_Aepgyieldspp->Draw("P same");

  c40->cd(3);
  gStyle->SetErrorX(0);
  h_Bepgyieldspn->SetMarkerStyle(20);
  h_Bepgyieldspn->SetMarkerSize(1);
  h_Bepgyieldspn->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Aepgyieldspn->SetMarkerStyle(20);
  h_Aepgyieldspn->SetMarkerSize(1);
  h_Aepgyieldspn->SetMarkerColorAlpha( kRed, 0.35 );
  h_Bepgyieldspn->SetTitle("A_{pn} red, B_{pn} blue");
  h_Bepgyieldspn->Draw("P");
  h_Aepgyieldspn->Draw("P same");

  c40->cd(4);
  gStyle->SetErrorX(0);
  h_Aepgyieldsnp->SetMarkerColorAlpha( kRed, 0.35 );
  h_Aepgyieldsnp->SetMarkerStyle(20);
  h_Aepgyieldsnp->SetMarkerSize(1);
  h_Bepgyieldsnp->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Bepgyieldsnp->SetMarkerStyle(20);
  h_Bepgyieldsnp->SetMarkerSize(1);
  //h_epgyieldsnp->Add(h_epgyieldspp,1);
  h_Bepgyieldsnp->SetTitle("A_{np} red, B_{np} blue");
  h_Bepgyieldsnp->Draw("P");
  h_Aepgyieldsnp->Draw("P same");

  c40->cd(5);
  gStyle->SetErrorX(0);
  h_Aepgyieldsnn->SetMarkerColorAlpha( kRed, 0.35 );
  h_Aepgyieldsnn->SetMarkerStyle(20);
  h_Aepgyieldsnn->SetMarkerSize(1);
  h_Bepgyieldsnn->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Bepgyieldsnn->SetMarkerStyle(20);
  h_Bepgyieldsnn->SetMarkerSize(1);
  //h_epgyieldsnn->Add(h_epgyieldspn,1);
  h_Bepgyieldsnn->SetTitle("A_{nn} red, B_{nn} blue");  
  h_Bepgyieldsnn->Draw("P");
  h_Aepgyieldsnn->Draw("P same");

  c40->cd(6);
  gStyle->SetErrorX(0);
  h_AepgyieldsPPPN->Add(h_Aepgyieldspp,h_Aepgyieldspn,1,1);
  h_AepgyieldsPPPN_pol->Add(h_Aepgyieldspp,h_Aepgyieldspn, APtminus, APtminus);
  h_AepgyieldsPPPN->SetMarkerColorAlpha( kRed, 0.35 );
  h_AepgyieldsPPPN->SetMarkerStyle(20);
  h_AepgyieldsPPPN->SetMarkerSize(1);
  h_BepgyieldsPPPN->Add(h_Bepgyieldspp,h_Bepgyieldspn,1,1);
  h_BepgyieldsPPPN_pol->Add(h_Bepgyieldspp,h_Bepgyieldspn, BPtminus, BPtminus);
  h_BepgyieldsPPPN->SetMarkerColorAlpha( kBlue, 0.35 );
  h_BepgyieldsPPPN->SetMarkerStyle(20);
  h_BepgyieldsPPPN->SetMarkerSize(1);
  h_BepgyieldsPPPN->SetTitle("A_{PPPN} red, B_{PPPN} blue");
  h_BepgyieldsPPPN->Draw("P");
  h_AepgyieldsPPPN->Draw("P same");

  c40->cd(7);
  gStyle->SetErrorX(0);
  h_AepgyieldsNPNN->Add(h_Aepgyieldsnp,h_Aepgyieldsnn,1,1);
  h_AepgyieldsNPNN_pol->Add(h_Aepgyieldsnp,h_Aepgyieldsnn, APtplus, APtplus);
  h_AepgyieldsNPNN->SetMarkerColorAlpha( kRed, 0.35 );
  h_AepgyieldsNPNN->SetMarkerStyle(20);
  h_AepgyieldsNPNN->SetMarkerSize(1);
  h_BepgyieldsNPNN->Add(h_Bepgyieldsnp,h_Bepgyieldsnn,1,1);
  h_BepgyieldsNPNN_pol->Add(h_Bepgyieldsnp,h_Bepgyieldsnn, BPtplus, BPtplus);
  h_BepgyieldsNPNN->SetMarkerColorAlpha( kBlue, 0.35 );
  h_BepgyieldsNPNN->SetMarkerStyle(20);
  h_BepgyieldsNPNN->SetMarkerSize(1);
  h_BepgyieldsNPNN->SetTitle("A_{NPNN} red, B_{NPNN} blue");
  h_BepgyieldsNPNN->Draw("P");  
  h_AepgyieldsNPNN->Draw("P same");

  c40->cd(8);
  gStyle->SetErrorX(0); 
  h_Aasymmetrytop->Add(h_AepgyieldsPPPN,h_AepgyieldsNPNN,1,-1);
  h_Aasymmetrybot->Add(h_AepgyieldsPPPN_pol,h_AepgyieldsNPNN_pol, Adilution, Adilution);
  h_Aasymmetrytop->SetMarkerColorAlpha( kRed, 0.35 );
  h_Aasymmetrytop->SetMarkerStyle(20);
  h_Aasymmetrytop->SetMarkerSize(1);
  h_Aasymmetrybot->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Aasymmetrybot->SetMarkerStyle(20);
  h_Aasymmetrybot->SetMarkerSize(1);
  h_Aasymmetrytop->SetTitle("A_{top} red, A_{bot} blue");
  h_Aasymmetrytop->Draw("P");
  h_Aasymmetrybot->Draw("P same");
  
  
  c40->cd(9);
  h_Basymmetrytop->Add(h_BepgyieldsPPPN,h_BepgyieldsNPNN,1,-1);
  h_Basymmetrybot->Add(h_BepgyieldsPPPN_pol,h_BepgyieldsNPNN_pol, Bdilution, Bdilution);
  h_Basymmetrytop->SetMarkerColorAlpha( kRed, 0.35 );
  h_Basymmetrytop->SetMarkerStyle(20);
  h_Basymmetrytop->SetMarkerSize(1);
  h_Basymmetrybot->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Basymmetrybot->SetMarkerStyle(20);
  h_Basymmetrybot->SetMarkerSize(1);
  h_Basymmetrytop->SetTitle("B_{top} red, B_{bot} blue");
  h_Basymmetrytop->Draw("P");
  h_Basymmetrybot->Draw("P same");
  
 
  //h_Aasymmetry->GetXaxis()->SetTitle("#phi [Deg]");
  //h_Aasymmetry->GetYaxis()->SetTitle("Asy");
  //h_Aasymmetry->GetXaxis()->CenterTitle();
  //h_Aasymmetry->GetYaxis()->CenterTitle();
  //h_Aasymmetry->Sumw2();
  

  c40->cd(10);
  h_Aasymmetry->Divide(h_Aasymmetrytop,h_Aasymmetrybot, 1.0, 1.0);
  h_Aasymmetry->SetMarkerColorAlpha( kRed, 0.35 );
  h_Aasymmetry->SetMarkerStyle(20);
  h_Aasymmetry->SetMarkerSize(1);
  h_Basymmetry->Divide(h_Basymmetrytop,h_Basymmetrybot, 1.0, 1.0);
  h_Basymmetry->SetMarkerColorAlpha( kBlue, 0.35 );
  h_Basymmetry->SetMarkerStyle(20);
  h_Basymmetry->SetMarkerSize(1);
  h_Basymmetry->GetXaxis()->SetTitle("#phi [Deg]");
  h_Basymmetry->GetYaxis()->SetTitle("Asy");
  h_Basymmetry->GetXaxis()->CenterTitle();
  h_Basymmetry->GetYaxis()->CenterTitle();
  //h_Basymmetry->Sumw2();
  h_Basymmetry->SetTitle("A_{asym} red, B_{asym} blue");
  h_Basymmetry->Draw("P");
  h_Aasymmetry->Draw("P same");

  c40->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/KinematicsWithHelicity.pdf");
  
  return 0;
}
