#define dvcshistogramtools_cxx

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/EventPID.h"
#include "../include/LoadPID.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/DVCSHistogramTool.h"
#include "../include/PhysicsEvent.h"
#include "../include/PhysicsEventBuilder.h"
#include "../include/Calculator.h"

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
#include <iostream>


DVCSHistogramTool::DVCSHistogramTool(){
  //Default Constructor                                                                                                                                                                                     
}

DVCSHistogramTool::DVCSHistogramTool(Int_t temprun){

  top = new TFile(Form("h_dvcs_%d.root",temprun), "recreate" );
  cdtof = new TDirectory("cdtof","cdtof","recreate");
  top->mkdir("tof");
  cdtof->cd();
  cdparticle[0] = top->mkdir("electronInformation");
  cdparticle[1] = top->mkdir("protonInformation");
  cdparticle[2] = top->mkdir("DVCSKinInformation");
   cdparticle[3] = top->mkdir("AsymmetryInformation");
   cdparticle[4] = top->mkdir("KinematicsInformation");
   cdparticle[5] = top->mkdir("DetectorRatesInformation");
   //c10 = new TCanvas("c10","Electron Information", 1400, 1400 );
  // // c20 = new TCanvas("c20","Proton Information", 1400, 1400 );
  // // c30 = new TCanvas("c30","Kinematic Information", 1400, 1400 );
  // // c40 = new TCanvas("c40","EC Photon Information", 1600, 2600 );
  // // c50 = new TCanvas("c50","Kinematics", 1400, 1400 );
  // // c60 = new TCanvas("c60","Detector Rates", 1400, 1400 );
  // // c10->Divide(4,2);
  // //electron detected with a photon found in the ic
  cdparticle[0]->cd();
  
  h_electronICp = new TH1D("h_electronICp","", 100, 0.0, 4.0 );
  h_electronICtheta = new TH1D("h_electronICtheta", "", 100, 0.0, 50.0 );
  h_electronICphi = new TH1D("h_electronICphi","", 100, -360.0, 360.0 );
  h_electronCICp = new TH1D("h_electronCICp","", 100, 0.0, 4.0 );
  h_electronCICtheta = new TH1D("h_electronCICtheta", "", 100, 0.0, 50.0 );
  h_electronCICphi = new TH1D("h_electronCICphi","", 100, -360.0, 360.0 );
  h_electronICthetaphi = new TH2D("h_electronICthetaphi","", 100, 0.0, 50.0, 200, -360.0, 360.0 );
  
  //electron detected with photon found in the ec
  h_electronECp = new TH1D("h_electronECp","", 100, 0.0, 4.0 );
  h_electronECtheta = new TH1D("h_electronECtheta","", 100, 0.0, 50.0 );
  h_electronECphi = new TH1D("h_electronECphi","", 100, -360.0, 360.0 );
  h_electronCECp = new TH1D("h_electronCECp","", 100, 0.0, 4.0 );
  h_electronCECtheta = new TH1D("h_electronCECtheta", "", 100, 0.0, 50.0 );
  h_electronCECphi = new TH1D("h_electronCECphi","", 100, -360.0, 360.0 );
  h_electronECthetaphi = new TH2D("h_electronECthetaphi","", 100, 0.0, 50.0, 200, -360.0, 360.0 );

  //c20->Divide(4,2);
  //proton detected with photon found in the ic
  cdparticle[1]->cd();
  h_protonICp = new TH1D("h_protonICp","", 100, 0.0, 4.0 );
  h_protonICtheta = new TH1D("h_protonICtheta", "", 100, 0.0, 50.0 );
  h_protonICphi = new TH1D("h_protonICphi","", 100, -360.0, 360.0 );
  h_protonCICp = new TH1D("h_protonCICp","", 100, 0.0, 4.0 );
  h_protonCICtheta = new TH1D("h_protonCICtheta", "", 100, 0.0, 50.0 );
  h_protonCICphi = new TH1D("h_protonCICphi","", 100, -360.0, 360.0 );
  h_protonICthetaphi = new TH2D("h_protonICthetaphi", "",100, 0.0, 50.0, 200, -360.0, 360.0 );

  h_protonECp = new TH1D("h_protonECp","", 100, 0.0, 4.0 );
  h_protonECtheta = new TH1D("h_protonECtheta", "", 100, 0.0, 50.0 );
  h_protonECphi = new TH1D("h_protonECphi","", 100, -360.0, 360.0 );
  h_protonCECp = new TH1D("h_protonCECp","", 100, 0.0, 4.0 );
  h_protonCECtheta = new TH1D("h_protonCECtheta", "", 100, 0.0, 50.0 );
  h_protonCECphi = new TH1D("h_protonCECphi","", 100, -360.0, 360.0 );
  h_protonECthetaphi = new TH2D("h_protonECthetaphi", "",100, 0.0, 50.0, 200, -360.0, 360.0 );

  //Kinemaic Variables
  // c30->Divide(4,2);
  cdparticle[2]->cd();
  h_q2IC = new TH1D("h_q2IC","",100, 0.0, 5.6 );
  h_xbjIC = new TH1D("h_xbjIC","",100, 0.0, 1.1 );
  h_tprIC = new TH1D("h_tprIC","",100, 0.0, 3.0 );
  h_phiprIC = new TH1D("h_phiprIC","",100, 0.0, 360.0 );
  h_missingmassIC = new TH1D("h_missingmassIC","",100, -0.5, 1.5);
  h_deltaphiIC = new TH1D("h_deltaphiIC","",100, -1.4, 1.4 );

  h_q2EC = new TH1D("h_q2EC","",100, 0.0, 5.6 );
  h_xbjEC = new TH1D("h_xbjEC","",100, 0.0, 1.1 );
  h_tprEC = new TH1D("h_tprEC","",100, 0.0, 3.0 );
  h_phiprEC = new TH1D("h_phiprEC","", 100, 0.0, 360.0 );
  h_q2xbjt = new TH2D("h_q2xbjt","", 100, 0.10, 0.7, 100, 0.0, 5.6);//, 100, 0.0, 3.0 );
  h_missingmassEC = new TH1D("h_missingmassEC","",100, -0.5, 1.5);
  h_deltaphiEC = new TH1D("h_deltaphiEC","",100, -1.4, 1.4 );


  h_phiplanedifference = new TH1D("h_phiplanedifference","",100,-180.0, 180.0 );
  h_phi_hadlep = new TH1D("h_phi_hadlep","",180,-180,360);
  h_phi_hadVPRP = new TH1D("h_phi_hadVPRP","",180,-180,360);



  cdparticle[5]->cd();
  //c40->Divide(1,9);
  // h_q2xbjtPOS = new TH3D("h_q2xbjtPOS","",100, 0.0, 5.6, 100, 0.0, 1.1, 100, 0.0, 3.0 );
  //h_q2xbjtNEG = new TH3D("h_q2xbjtNEG","",100, 0.0, 5.6, 100, 0.0, 1.1, 100, 0.0, 3.0 );
  
  binNum_xbj = sizeof(bin_xbj)/sizeof(Float_t) - 1;
  binNum_tproton = sizeof(bin_tproton)/sizeof(Float_t) - 1;
  // h_bin_xbjtPOS = new TH2F("h_bin_xbjtPOS","", binNum_xbj, bin_xbj, binNum_tproton, bin_tproton );
  // h_bin_tPOS = new TH1F("h_bin_xbjtPOS","", binNum_tproton, bin_tproton);
  h_averagebin = new TH2D("h_averagebin","", 100, 0.0, 0.65, 100, 0.00, 2.0);
  h_averagebinB = new TH2D("h_averagebinB","", 100, 0.0, 0.65, 100, 0.00, 2.0);
  h_xbjtPOS = new TH2F("h_xbjtPOS","", 100, 0.1, 0.55, 100, 0.1, 2.0 );
  h_xbjtBPOS = new TH2F("h_xbjtBPOS","", 100, 0.1, 0.55, 100, 0.1, 2.0 );

  cdparticle[3]->cd();
  h_Aepgyieldspp = new TH1D("h_AepgyieldsPP", "", 10, 0, 360 );
  h_Aepgyieldspn = new TH1D("h_AepgyieldsPN", "", 10, 0, 360 );
  h_Aepgyieldsnp = new TH1D("h_AepgyieldsNP", "", 10, 0, 360 );
  h_Aepgyieldsnn = new TH1D("h_AepgyieldsNN", "", 10, 0, 360 );
  h_AepgyieldsPPPN = new TH1D("h_AepgyieldsPPPN","", 10, 0, 360 );
  h_AepgyieldsPPPN_pol = new TH1D("h_AepgyieldsPPPN_pol","", 10, 0.0, 360 );
  h_AepgyieldsNPNN = new TH1D("h_AepgyieldsNPNN","", 10, 0, 360 );
  h_AepgyieldsNPNN_pol = new TH1D("h_AepgyieldsNPNN_pol","", 10, 0, 360 );
  h_Aasymmetrytop = new TH1D("h_Aasymmetrytop","", 10, 0.0, 360.0 );
  h_Aasymmetrybot = new TH1D("h_Aasymmetrybot","", 10, 0.0, 360.0 );
  //h_Aasymmetry = new TH1D("h_Aasymmetry","", 10, 0.0, 360.0 );

  // c50->Divide(1,9);
  h_Bepgyieldspp = new TH1D("h_BepgyieldsPP", "", 10, 0, 360 );
  h_Bepgyieldspn = new TH1D("h_BepgyieldsPN", "", 10, 0, 360 );
  h_Bepgyieldsnp = new TH1D("h_BepgyieldsNP", "", 10, 0, 360 );
  h_Bepgyieldsnn = new TH1D("h_BepgyieldsNN", "", 10, 0, 360 );
  h_BepgyieldsPPPN = new TH1D("h_BepgyieldsPPPN","", 10, 0, 360 );
  h_BepgyieldsPPPN_pol = new TH1D("h_BepgyieldsPPPN_pol","", 10, 0, 360 );
  h_BepgyieldsNPNN = new TH1D("h_BepgyieldsNPNN","", 10, 0, 360 );
  h_BepgyieldsNPNN_pol = new TH1D("h_BepgyieldsNPNN_pol","", 10, 0, 360 );
  h_Basymmetrytop = new TH1D("h_Basymmetrytop","", 10, 0.0, 360.0 );
  h_Basymmetrybot = new TH1D("h_Basymmetrybot","", 10, 0.0, 360.0 );
  //h_Basymmetry = new TH1D("h_Basymmetry","", 10, 0.0, 360.0 );

  //c60->Divide(6,2);
  cdparticle[4]->cd();

  h_leptontheta = new TH1D(" h_leptontheta","",100, -120.0, 120.0 );
  h_leptonphi = new TH1D(" h_leptonohi","",100, -180, 180 );
  h_leptonthetavsphi = new TH2D(" h_leptonthetavsphi","",100, -120.0, 120.0, 200, -200, 200 );
  h_hadrontheta = new TH1D(" h_hadrontheta","",100, -120.0, 120.0 );
  h_hadronphi = new TH1D(" h_hadronphi","",100, 180.0, 180.0 );
  h_hadronthetavsphi = new TH2D(" h_hadronthetavsphi","",100, -5.0, 140.0, 200, -200, 200 );

  h_ECleptontheta = new TH1D(" h_ECleptontheta","",100, -120.0, 120.0 );
  h_ECleptonphi = new TH1D(" h_ECleptonohi","",100, -180, 180 );
  h_ECleptonthetavsphi = new TH2D(" h_ECleptonthetavsphi","",100, -120.0, 120.0, 200, -200, 200 );
  h_EChadrontheta = new TH1D(" h_EChadrontheta","",100, -120.0, 120.0 );
  h_EChadronphi = new TH1D(" h_EChadronphi","",100, 180.0, 180.0 );
  h_EChadronthetavsphi = new TH2D("h_EChadronthetavsphi","",100, -5.0, 140.0, 200, -200, 200 );

  h_hthetavslphi = new TH2D("h_hthetavslphi","",100, -5.0, 140.0, 200, -200, 200 );

  h_ecratesA = new TH1D("h_ecratesA","",10, 0.0, 6000 );
  h_icratesA = new TH1D("h_icratesA","",10, 0.0, 6000 );

  h_ecratesB = new TH1D("h_ecratesB","",10, 0.0, 6000 );
  h_icratesB = new TH1D("h_icratesB","",10, 0.0, 6000 );
  cdtof->cd();

 
}

DVCSHistogramTool::~DVCSHistogramTool(){

}

void DVCSHistogramTool::MakeDVCSElectronPlots( PhysicsEvent physicsEvent, Int_t tempid  ){
  cdparticle[0]->cd();
  
  if( tempid == 1000 ){
    // std::cout << tempbuild.physicsEvent.pel << " > > " << std::endl;
    h_electronICp->Fill(physicsEvent.pel );
    h_electronICtheta->Fill(physicsEvent.eltheta);
    h_electronICphi->Fill(physicsEvent.elphi);
    h_electronICthetaphi->Fill(physicsEvent.eltheta, physicsEvent.elphi );

  }
  else if( tempid == 2000 ){
    // std::cout << "ec hit " << std::endl;
    h_electronECp->Fill(physicsEvent.pel);
    h_electronECtheta->Fill(physicsEvent.eltheta);
    h_electronECphi->Fill(physicsEvent.elphi);
    h_electronECthetaphi->Fill(physicsEvent.eltheta, physicsEvent.elphi );
    
  }
  if( tempid == 5000 ){
    //std::cout << " ic ec hit " << std::endl;
  }

}

void DVCSHistogramTool::MakeDVCSProtonPlots( PhysicsEvent physicsEvent, Int_t tempid  ){
   cdparticle[1]->cd();

  if( tempid == 1000 ){
    h_protonICp->Fill(physicsEvent.prp );
    h_protonICtheta->Fill(physicsEvent.prtheta);
    h_protonICphi->Fill(physicsEvent.prphi);
    h_protonICthetaphi->Fill(physicsEvent.prtheta, physicsEvent.prphi );
  }

  else if( tempid == 2000 ){
    h_protonECp->Fill(physicsEvent.prp);
    h_protonECtheta->Fill(physicsEvent.prtheta);
    h_protonECphi->Fill(physicsEvent.prphi);
    h_protonECthetaphi->Fill(physicsEvent.prtheta, tempbuild.physicsEvent.prphi );	
  }

  if( tempid == 5000 ){
    // std::cout << " ic ec hit " << std::endl;
  }
}

// void DVCSHistogramTool::MakeDVCSPhotonPlots( PhysicsEventBuilder tempbuild, Int_t tempid ){

// if( tempid == 1000 ){
//     h_photonICp->Fill( tempbuild.physicsEvent.prp );
//     h_photonICtheta->Fill(tempbuild.physicsEvent.prtheta);
//     h_photonICphi->Fill(tempbuild.physicsEvent.prphi);
//     h_photonICthetaphi->Fill(tempbuild.physicsEvent.prtheta, tempbuild.physicsEvent.prphi );
//   }

//   else if( tempid == 2000 ){
//     h_photonECp->Fill(tempbuild.physicsEvent.prp);
//     h_photonECtheta->Fill(tempbuild.physicsEvent.prtheta);
//     h_photonECphi->Fill(tempbuild.physicsEvent.prphi);
//     h_photonECthetaphi->Fill(tempbuild.physicsEvent.prtheta, tempbuild.physicsEvent.prphi );	
//   }

//   if( tempid == 5000 ){
//     // std::cout << " ic ec hit " << std::endl;
//   }
// }  



void DVCSHistogramTool::MakeDVCSKinematicsPlots( PhysicsEvent physicsEvent, Int_t tempid ){
  // IC == 1000, EC==2000, ICEC==5000
 
  cdparticle[2]->cd();
  if( tempid == 1000 ){
    h_q2IC->Fill(physicsEvent.qq );
    h_xbjIC->Fill(physicsEvent.xbj);
    h_tprIC->Fill(-physicsEvent.t_proton);
    h_phiprIC->Fill(physicsEvent.phi_pr);

    h_leptontheta->Fill(physicsEvent.n_lepton_theta);
    h_leptonphi->Fill(physicsEvent.n_lepton_phi);
    h_leptonthetavsphi->Fill(physicsEvent.n_lepton_theta, physicsEvent.n_lepton_phi);

    h_hadrontheta->Fill(physicsEvent.n_hadron_theta);
    h_hadronphi->Fill(physicsEvent.n_hadron_phi);
    h_hadronthetavsphi->Fill(physicsEvent.n_hadron_theta, physicsEvent.n_hadron_phi);

    h_hthetavslphi->Fill(physicsEvent.n_hadron_theta, physicsEvent.n_lepton_phi);
    h_missingmassIC->Fill( physicsEvent.mm2ep );
    
    
  }
  else if( tempid == 2000 ){

    h_q2EC->Fill( physicsEvent.qq );
    h_xbjEC->Fill(physicsEvent.xbj);
    h_tprEC->Fill(-physicsEvent.t_proton);
    h_phiprEC->Fill(physicsEvent.phi_pr);

    h_ECleptontheta->Fill(physicsEvent.n_lepton_theta);
    h_ECleptonphi->Fill(physicsEvent.n_lepton_phi);
    h_ECleptonthetavsphi->Fill(physicsEvent.n_lepton_theta, physicsEvent.n_lepton_phi);

    h_EChadrontheta->Fill(physicsEvent.n_hadron_theta);
    h_EChadronphi->Fill(physicsEvent.n_hadron_phi);
    h_EChadronthetavsphi->Fill(physicsEvent.n_hadron_theta, physicsEvent.n_hadron_phi);

    h_missingmassEC->Fill( physicsEvent.mm2ep );

  
  }

  if( tempid == 5000 ){
    //make ICEC histos.
  }
  if( tempbuild.physicsEvent.periodid == "A" ){
    //std::cout<< "positive helicity " << tempbuild.physicsEvent.helic <<  std::endl;
    //h_q2xbjtPOS->Fill( tempbuild.physicsEvent.qq, tempbuild.physicsEvent.xbj, -tempbuild.physicsEvent.t_proton );
    h_xbjtPOS->Fill(physicsEvent.xbj , -physicsEvent.t_proton );
  }
  if( tempbuild.physicsEvent.periodid == "B" ){
    h_xbjtBPOS->Fill( physicsEvent.xbj , -physicsEvent.t_proton );
  }
  // h_q2xbjPOS->Fill( tempbuild.physicsEvent.xbj, tempbuild.physicsEvent.qq);
  // h_bin_tPOS->Fill( -tempbuild.physicsEvent.t_proton);
  // }
  // else if ( tempbuild.physicsEvent.helic == 0 ){
  //std::cout << " negative helicity " << tempbuild.physicsEvent.helic << std::endl;
  //h_q2xbjtNEG->Fill( tempbuild.physicsEvent.qq, tempbuild.physicsEvent.xbj, -tempbuild.physicsEvent.t_proton );
  // }

  h_q2xbjt->Fill(physicsEvent.xbj, physicsEvent.qq);//, physicsEvent.t_proton );
  h_phiplanedifference->Fill(physicsEvent.PhiPlaneDifference);  
  h_phi_hadlep->Fill(physicsEvent.hadron_hadlep_Phi);
  h_phi_hadVPRP->Fill(physicsEvent.hadron_hadVPRP_Phi);


}

//void DVCSHistogramTool::AsymmetryHistograms(PhysicsEventBuilder tempbuild, Int_t tempid ){
//void DVCSHistogramTool::AsymmetryHistograms(EventDVCS event, TString TargetType, TString PeriodID){
void DVCSHistogramTool::AsymmetryHistograms(PhysicsEvent event, TString TargetType, TString PeriodID, TString TargetPola){
  
  cdparticle[3]->cd();
  // std::cout << TargetType << " " << PeriodID <<  std::endl;
  Int_t polsign = atoi( TargetPola );
  if( TargetType == "NH3T" || TargetType == "NH3B" ){
    //std::cout << tempbuild.physicsEvent.periodid << std::endl;
    if( PeriodID == "A" ){
      if( polsign > 0 && event.helic == 1 ){
	//std::cout << " target +  helicity + " << std::endl;
	h_Aepgyieldspp->Fill( event.phi_pr );
      }
      if(  polsign > 0 && event.helic == 0 ){
	//std::cout << " target + helicity - " << std::endl;
	h_Aepgyieldspn->Fill( event.phi_pr );
      }
      if(  polsign < 0 && event.helic == 1 ){
	//std::cout << " target - helicity + " << std::endl;
	h_Aepgyieldsnp->Fill( event.phi_pr );
      }
      if(  polsign < 0 && event.helic == 0 ){
	//std::cout << " target - helicity - " << std::endl;
	h_Aepgyieldsnn->Fill( event.phi_pr );
      }
    }
  
    if( PeriodID == "B" ){
      // std::cout << polsign << " " << event.helic << std::endl;
      if(  polsign  > 0 && event.helic == 1 ){
	//	std::cout << " target +  helicity + " << std::endl;
	h_Bepgyieldspp->Fill( event.phi_pr );
      }
      if(  polsign > 0 && event.helic == 0 ){
	//std::cout << " target + helicity - " << std::endl;
	h_Bepgyieldspn->Fill( event.phi_pr );
      }
      if(  polsign < 0 && event.helic == 1 ){
	//std::cout << " target - helicity + " << std::endl;
	h_Bepgyieldsnp->Fill( event.phi_pr );
      }
      if(  polsign < 0 && event.helic == 0 ){
	//std::cout << " target - helicity - " << std::endl;
	h_Bepgyieldsnn->Fill( event.phi_pr );
      }
    }
  }
  //std::cout << tempbuild.physicsEvent.periodid << std::endl;
  // if( tempperiod == "A" ){
  //    if( tempbuild.physicsEvent.tpol > 0 && tempbuild.physicsEvent.helic == 1 ){
  //      //std::cout << " target +  helicity + " << std::endl;
  //      h_Aepgyieldspp->Fill( tempbuild.physicsEvent.phi_pr );
  //    }
  //    if( tempbuild.physicsEvent.tpol > 0 && tempbuild.physicsEvent.helic == 0 ){
  //      //std::cout << " target + helicity - " << std::endl;
  //      h_Aepgyieldspn->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //    if( tempbuild.physicsEvent.tpol < 0 && tempbuild.physicsEvent.helic == 1 ){
 //      //std::cout << " target - helicity + " << std::endl;
 //      h_Aepgyieldsnp->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //    if( tempbuild.physicsEvent.tpol < 0 && tempbuild.physicsEvent.helic == 0 ){
 //      //std::cout << " target - helicity - " << std::endl;
 //      h_Aepgyieldsnn->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //  }
  
 //   if( tempperiod == "B" ){
 //    if( tempbuild.physicsEvent.tpol > 0 && tempbuild.physicsEvent.helic == 1 ){
 //      //std::cout << " target +  helicity + " << std::endl;
 //      h_Bepgyieldspp->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //    if( tempbuild.physicsEvent.tpol > 0 && tempbuild.physicsEvent.helic == 0 ){
 //      //std::cout << " target + helicity - " << std::endl;
 //      h_Bepgyieldspn->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //    if( tempbuild.physicsEvent.tpol < 0 && tempbuild.physicsEvent.helic == 1 ){
 //      //std::cout << " target - helicity + " << std::endl;
 //      h_Bepgyieldsnp->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //    if( tempbuild.physicsEvent.tpol < 0 && tempbuild.physicsEvent.helic == 0 ){
 //      //std::cout << " target - helicity - " << std::endl;
 //      h_Bepgyieldsnn->Fill( tempbuild.physicsEvent.phi_pr );
 //    }
 //   }
 // }
}


void  DVCSHistogramTool::DetectorRates( EventDVCS eventtest, TString tempperiod ){
  // cdtof->cd();
   cdparticle[5]->cd();

  if( tempperiod == "A" ){
    if( eventtest.ph_hitID == 1000 ) h_icratesA->Fill( eventtest.ph_hitID );
    if( eventtest.ph_hitID == 2000 ) h_ecratesA->Fill( eventtest.ph_hitID );
   
  }
  else if( tempperiod == "B" ){
    if( eventtest.ph_hitID == 1000 ) h_icratesB->Fill( eventtest.ph_hitID );
    if( eventtest.ph_hitID == 2000 ) h_ecratesB->Fill( eventtest.ph_hitID );
  }
    
}

void DVCSHistogramTool::DrawDVCSHistograms(){
  //top->Write();
  //delete top;
  // c10->cd(1);
  // h_electronICp->GetXaxis()->SetTitle("e^{-} momentum with IC photon [GeV]");
  // h_electronICp->GetYaxis()->SetTitle("Counts");
  // h_electronICp->GetXaxis()->CenterTitle();
  // h_electronICp->GetYaxis()->CenterTitle();
  // h_electronICp->Draw();
  // c10->cd(2);
  // h_electronICtheta->GetXaxis()->SetTitle("e^{-} #theta with IC photon [deg]");
  // h_electronICtheta->GetYaxis()->SetTitle("Counts");
  // h_electronICtheta->GetXaxis()->CenterTitle();
  // h_electronICtheta->GetYaxis()->CenterTitle();
  // h_electronICtheta->Draw();
  // c10->cd(3);
  // h_electronICphi->GetXaxis()->SetTitle("e^{-} #phi with IC photon [deg]");
  // h_electronICphi->GetYaxis()->SetTitle("Counts");
  // h_electronICphi->GetXaxis()->CenterTitle();
  // h_electronICphi->GetYaxis()->CenterTitle();
  // h_electronICphi->Draw();

  // c10->cd(4);
  // h_electronECp->GetXaxis()->SetTitle("e^{-} momentum with EC photon [GeV]");
  // h_electronECp->GetYaxis()->SetTitle("Counts");
  // h_electronECp->GetXaxis()->CenterTitle();
  // h_electronECp->GetYaxis()->CenterTitle();
  // h_electronECp->Draw();
  // c10->cd(5);
  // h_electronECtheta->GetXaxis()->SetTitle("e^{-} #theta with EC photon [deg]");
  // h_electronECtheta->GetYaxis()->SetTitle("Counts");
  // h_electronECtheta->GetXaxis()->CenterTitle();
  // h_electronECtheta->GetYaxis()->CenterTitle();
  // h_electronECtheta->Draw();
  // c10->cd(6);
  // h_electronECphi->GetXaxis()->SetTitle("e^{-} #phi with EC photon [deg]");
  // h_electronECphi->GetYaxis()->SetTitle("Counts");
  // h_electronECphi->GetXaxis()->CenterTitle();
  // h_electronECphi->GetYaxis()->CenterTitle();
  // h_electronECphi->Draw();
  // c10->cd(7);
  // h_electronICthetaphi->GetXaxis()->SetTitle("#theta");
  // h_electronICthetaphi->GetYaxis()->SetTitle("#phi");
  // h_electronICthetaphi->Draw("colz");

  

  
  // //c10->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/ElectronWithICECPhotons.pdf");

  // c20->cd(1);
  // h_protonICp->GetXaxis()->SetTitle("proton momentum with IC photon [GeV]");
  // h_protonICp->GetYaxis()->SetTitle("Counts");
  // h_protonICp->GetXaxis()->CenterTitle();
  // h_protonICp->GetYaxis()->CenterTitle();
  // h_protonICp->Draw();
  // c20->cd(2);
  // h_protonICtheta->GetXaxis()->SetTitle("proton #theta with IC photon [deg]");
  // h_protonICtheta->GetYaxis()->SetTitle("Counts");
  // h_protonICtheta->GetXaxis()->CenterTitle();
  // h_protonICtheta->GetYaxis()->CenterTitle();
  // h_protonICtheta->Draw();
  // c20->cd(3);
  // h_protonICphi->GetXaxis()->SetTitle("proton #phi with IC photon [deg]");
  // h_protonICphi->GetYaxis()->SetTitle("Counts");
  // h_protonICphi->GetXaxis()->CenterTitle();
  // h_protonICphi->GetYaxis()->CenterTitle();
  // h_protonICphi->Draw();

  // c20->cd(4);
  // h_protonECp->GetXaxis()->SetTitle("proton momentum with EC photon [GeV]");
  // h_protonECp->GetYaxis()->SetTitle("Counts");
  // h_protonECp->GetXaxis()->CenterTitle();
  // h_protonECp->GetYaxis()->CenterTitle();
  // h_protonECp->Draw();
  // c20->cd(5);
  // h_protonECtheta->GetXaxis()->SetTitle("e^{-} #theta with EC photon [deg]");
  // h_protonECtheta->GetYaxis()->SetTitle("Counts");
  // h_protonECtheta->GetXaxis()->CenterTitle();
  // h_protonECtheta->GetYaxis()->CenterTitle();
  // h_protonECtheta->Draw();
  // c20->cd(6);
  // h_protonECphi->GetXaxis()->SetTitle("e^{-} #phi with EC photon [deg]");
  // h_protonECphi->GetYaxis()->SetTitle("Counts");
  // h_protonECphi->GetXaxis()->CenterTitle();
  // h_protonECphi->GetYaxis()->CenterTitle();
  // h_protonECphi->Draw();

  // c20->cd(7);
  // h_protonICthetaphi->GetXaxis()->SetTitle("#theta");
  // h_protonICthetaphi->GetYaxis()->SetTitle("#phi");
  // h_protonICthetaphi->Draw("colz");
  
  // //c20->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/ProtonsWithICECPhotons.pdf");

  // c30->cd(1);
  // h_q2IC->GetXaxis()->SetTitle("Q^{2} IC [GeV^{2}]");
  // h_q2IC->GetYaxis()->SetTitle("Counts");
  // h_q2IC->GetXaxis()->CenterTitle();
  // h_q2IC->GetYaxis()->CenterTitle();
  // h_q2IC->Draw();

  // c30->cd(2);
  // h_xbjIC->GetXaxis()->SetTitle("X^{2} IC ");
  // h_xbjIC->GetYaxis()->SetTitle("Counts");
  // h_xbjIC->GetXaxis()->CenterTitle();
  // h_xbjIC->GetYaxis()->CenterTitle();
  // h_xbjIC->Draw();

  // c30->cd(3);
  // h_tprIC->GetXaxis()->SetTitle("-t_{Pr} IC [GeV^{2}]");
  // h_tprIC->GetYaxis()->SetTitle("Counts");
  // h_tprIC->GetXaxis()->CenterTitle();
  // h_tprIC->GetYaxis()->CenterTitle();
  // h_tprIC->Draw();

  // c30->cd(4);
  // h_phiprIC->GetXaxis()->SetTitle("#phi_{Pr} IC [GeV^{2}]");
  // h_phiprIC->GetYaxis()->SetTitle("Counts");
  // h_phiprIC->GetXaxis()->CenterTitle();
  // h_phiprIC->GetYaxis()->CenterTitle();
  // h_phiprIC->Draw();

  // c30->cd(5);
  // h_q2EC->GetXaxis()->SetTitle("Q^{2} EC [GeV^{2}]");
  // h_q2EC->GetYaxis()->SetTitle("Counts");
  // h_q2EC->GetXaxis()->CenterTitle();
  // h_q2EC->GetYaxis()->CenterTitle();
  // h_q2EC->Draw();

  // c30->cd(6);
  // h_xbjEC->GetXaxis()->SetTitle("X^{2} EC ");
  // h_xbjEC->GetYaxis()->SetTitle("Counts");
  // h_xbjEC->GetXaxis()->CenterTitle();
  // h_xbjEC->GetYaxis()->CenterTitle();
  // h_xbjEC->Draw();

  // //c30->cd(7);
  // h_tprEC->GetXaxis()->SetTitle("-t_{Pr} EC [GeV^{2}]");
  // h_tprEC->GetYaxis()->SetTitle("Counts");
  // h_tprEC->GetXaxis()->CenterTitle();
  // h_tprEC->GetYaxis()->CenterTitle();
  // h_tprEC->Draw();

  // //c30->cd(8);
  // h_phiprEC->GetXaxis()->SetTitle("#phi_{Pr} EC [GeV^{2}]");
  // h_phiprEC->GetYaxis()->SetTitle("Counts");
  // h_phiprEC->GetXaxis()->CenterTitle();
  // h_phiprEC->GetYaxis()->CenterTitle();
  // h_phiprEC->Draw();
  
  //c30->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/KinematicsWithICECPhotons.pdf");

  /* c4->cd(1);
  h_q2xbjtPOS->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2xbjtPOS->GetYaxis()->SetTitle("Xbj");
  h_q2xbjtPOS->GetZaxis()->SetTitle("-t_{proton} [GeV^{2}]");
  h_q2xbjtPOS->GetXaxis()->CenterTitle();
  h_q2xbjtPOS->GetYaxis()->CenterTitle();
  h_q2xbjtPOS->GetZaxis()->CenterTitle();
  h_q2xbjtPOS->Draw("colz");

  c4->cd(2);
  h_q2xbjtNEG->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2xbjtNEG->GetYaxis()->SetTitle("Xbj");
  h_q2xbjtNEG->GetZaxis()->SetTitle("-t_{proton} [GeV^{2}]");
  h_q2xbjtNEG->GetXaxis()->CenterTitle();
  h_q2xbjtNEG->GetYaxis()->CenterTitle();
  h_q2xbjtNEG->GetZaxis()->CenterTitle();
  h_q2xbjtNEG->Draw("colz");

  //c4->cd(1);
  // h_xbjtPOS->GetXaxis()->SetTitle("Xbj");
  // h_xbjtPOS->GetYaxis()->SetTitle("-t_{proton} [GeV^{2}]");
  // h_xbjtPOS->GetXaxis()->CenterTitle();
  // h_xbjtPOS->GetYaxis()->CenterTitle();
  // h_xbjtPOS->Draw();

  // c4->cd(2);
  // h_xbjtBPOS->GetXaxis()->SetTitle("Xbj");
  // h_xbjtBPOS->GetYaxis()->SetTitle("-t_{proton} [GeV^{2}]");
  // h_xbjtBPOS->GetXaxis()->CenterTitle();
  // h_xbjtBPOS->GetYaxis()->CenterTitle();
  // h_xbjtBPOS->Draw();

  //  c4->cd(2);
  // h_q2xbjPOS->GetXaxis()->SetTitle("Xbj");
  // h_q2xbjPOS->GetYaxis()->SetTitle("Q^{2}[GeV^{2}]");
  // h_q2xbjPOS->GetXaxis()->CenterTitle();
  // h_q2xbjPOS->GetYaxis()->CenterTitle();
  // h_q2xbjPOS->Draw();
 
  // c4->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/KinematicsWithHelicity.pdf");
  */
  
}

void DVCSHistogramTool::CarveQ2XbjBins(){

  // f_q2xbj = new TF1("f_q2xbj","5.8/( (1/(4*5.8*TMath::Power(TMath::Sin(15.0/2.0),2))) + (1/x*5.8))",0.1,1.0 );
  // c60->cd(1);
  // f_q2xbj->Draw();
  // c60->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/KinematicsFunctions.pdf");

}


void DVCSHistogramTool::AverageBinTool(){

  // for( Int_t i = 0 ; i < 4; i++){
  //   h_xbjtPOS->GetXaxis()->SetRange(xbjrange1[i], xbjrange1[i+1]);
  //   h_xbjtBPOS->GetXaxis()->SetRange(xbjrange1[i], xbjrange1[i+1]);  
  //   Double_t xavgB = h_xbjtBPOS->GetMean(1);
  //   Double_t xavg = h_xbjtPOS->GetMean(1);
  //   for( Int_t j = 0; j < 4; j++ ){
  //     h_xbjtPOS->GetYaxis()->SetRange(tprotonrange1[j] , tprotonrange1[j+1]);
  //     h_xbjtBPOS->GetYaxis()->SetRange(tprotonrange1[j] , tprotonrange1[j+1]);
  //     Double_t yavg = h_xbjtPOS->GetMean(2);
  //     Double_t yavgB = h_xbjtBPOS->GetMean(2);
  //     //std::cout << " A : " << xavg << " " << yavg << " " <<std::endl; 
  //     //std::cout << " B : " << xavgB << " " << yavgB << " " <<std::endl; 
  //     h_averagebin->Fill( xavg, yavg );
  //     //h_averagebinB->Fill( xavgB, yavgB );
  //   }
  // }
  cdparticle[3]->cd();
  APtplus = 0.75;
  APtminus = 0.72;
  BPtplus = 0.81;
  BPtminus = 0.75;
  Adilution = 0.912;
  Bdilution = 0.928;
  
  // c40->cd(1);
  // gStyle->SetErrorX(0);
  // h_Aepgyieldspp->SetMarkerStyle(20);
  // h_Aepgyieldspp->SetMarkerSize(1);
  // h_Aepgyieldspp->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Aepgyieldspp->SetTitle("A_{pp}");
  // h_Aepgyieldspp->Draw("P0");

  // c40->cd(2);
  // gStyle->SetErrorX(0);
  // h_Aepgyieldspn->SetMarkerStyle(20);
  // h_Aepgyieldspn->SetMarkerSize(1);
  // h_Aepgyieldspn->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Aepgyieldspn->SetTitle("A_{pn} red");
  // h_Aepgyieldspn->Draw("P0");

  // c40->cd(3);
  // gStyle->SetErrorX(0);
  // h_Aepgyieldsnp->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Aepgyieldsnp->SetMarkerStyle(20);
  // h_Aepgyieldsnp->SetMarkerSize(1);
  // h_Aepgyieldsnp->SetTitle("A_{np} red");
  // h_Aepgyieldsnp->Draw("P0");

  // c40->cd(4);
  // gStyle->SetErrorX(0);
  // h_Aepgyieldsnn->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Aepgyieldsnn->SetMarkerStyle(20);
  // h_Aepgyieldsnn->SetMarkerSize(1);
  // h_Aepgyieldsnn->SetTitle("A_{nn} red");  
  // h_Aepgyieldsnn->Draw("P0");

  // c40->cd(5);
  // gStyle->SetErrorX(0);
   h_AepgyieldsPPPN->Add(h_Aepgyieldspp,h_Aepgyieldspn,1,1);
   h_AepgyieldsPPPN_pol->Add(h_Aepgyieldspp,h_Aepgyieldspn, APtminus, APtminus);
  // h_AepgyieldsPPPN->SetMarkerColorAlpha( kRed, 0.35 );
  // h_AepgyieldsPPPN->SetMarkerStyle(20);
  // h_AepgyieldsPPPN->SetMarkerSize(1);
  // h_AepgyieldsPPPN->SetTitle("A_{PPPN} red");
  // h_AepgyieldsPPPN->Draw("P0");

  // c40->cd(6);
  // gStyle->SetErrorX(0);
   h_AepgyieldsNPNN->Add(h_Aepgyieldsnp,h_Aepgyieldsnn,1,1);
   h_AepgyieldsNPNN_pol->Add(h_Aepgyieldsnp,h_Aepgyieldsnn, APtplus, APtplus);
  // h_AepgyieldsNPNN->SetMarkerColorAlpha( kRed, 0.35 );
  // h_AepgyieldsNPNN->SetMarkerStyle(20);
  // h_AepgyieldsNPNN->SetMarkerSize(1);
  // h_AepgyieldsNPNN->SetTitle("A_{NPNN} red");
  // h_AepgyieldsNPNN->Draw("P0");  

  // c40->cd(7);
  // gStyle->SetErrorX(0); 
   h_Aasymmetrytop->Add(h_AepgyieldsPPPN,h_AepgyieldsNPNN,1,-1);
  // h_Aasymmetrytop->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Aasymmetrytop->SetMarkerStyle(20);
  // h_Aasymmetrytop->SetMarkerSize(1);
  // h_Aasymmetrytop->SetTitle("A_{top} red");
  // h_Aasymmetrytop->Draw("P0");

  // c40->cd(8);
   h_Aasymmetrybot->Add(h_AepgyieldsPPPN_pol,h_AepgyieldsNPNN_pol, Adilution, Adilution);
  // h_Aasymmetrybot->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Aasymmetrybot->SetMarkerStyle(20);
  // h_Aasymmetrybot->SetMarkerSize(1);
  // h_Aasymmetrybot->SetTitle("A_{bot} blue");
  // h_Aasymmetrybot->Draw("P0");  
  
  // //h_Aasymmetry->GetXaxis()->SetTitle("#phi [Deg]");
  // //h_Aasymmetry->GetYaxis()->SetTitle("Asy");
  // //h_Aasymmetry->GetXaxis()->CenterTitle();
  // //h_Aasymmetry->GetYaxis()->CenterTitle();
  // //h_Aasymmetry->Sumw2();
  

  // c40->cd(9);
  // h_Aasymmetry->Divide(h_Aasymmetrytop,h_Aasymmetrybot, 1.0, 1.0);
  // h_Aasymmetry->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Aasymmetry->SetMarkerStyle(20);
  // h_Aasymmetry->SetMarkerSize(1);
  // h_Aasymmetry->GetXaxis()->SetTitle("#phi [Deg]");
  // h_Aasymmetry->GetYaxis()->SetTitle("Asy");
  // h_Aasymmetry->GetXaxis()->CenterTitle();
  // h_Aasymmetry->GetYaxis()->CenterTitle();
  // h_Aasymmetry->SetTitle("A_{asym}");
  // h_Aasymmetry->Draw("P0");
  

  
  // // // for( Int_t i = 0 ; i < 4; i++){
  // // // h_xbjtPOS->GetXaxis()->SetRange(xbjrange1[i], xbjrange1[i+1]); 
  // // // Double_t xavg = h_xbjtPOS->GetMean(1);
  // // // for( Int_t j = 0; j < 4; j++ ){
  // // //        h_q2xbjPOS->GetYaxis()->SetRange(q2range1[j] , q2range1[j+1]);
  // // //        Double_t yavg = h_q2xbjPOS->GetMean(2);
  // // // 	 std::cout << xavg << " " << yavg << " " <<std::endl; 
  // // // 	 h_q2xbjaverage->Fill( xavg, yavg );
  // // //     }
  // // //  }

 
   
  // // // h_q2xbjaverage->SetMarkerStyle(20);
  // // // h_q2xbjaverage->SetMarkerColorAlpha( kRed, 0.35 );
  // // // h_q2xbjaverage->GetXaxis()->SetTitle("Xbj");
  // // // h_q2xbjaverage->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  // // // h_q2xbjaverage->GetXaxis()->CenterTitle();
  // // // h_q2xbjaverage->GetYaxis()->CenterTitle();
  // // // h_q2xbjaverage->Draw();

  

  // // //Used to find the correct bins to find the mean over.
  // //  // for( Int_t k = 0; k < 5 ; k++ ){
  // //  //     Int_t binx = h_q2xbjPOS->GetXaxis()->FindBin(bin_xbj[k]);
  // //  //     Int_t biny = h_q2xbjPOS->GetYaxis()->FindBin(bin_q2[k]);
  // //  //     std::cout << " xbj bins >> " << bin_xbj[k] << " " << binx << " ||  t bin " << bin_[k] << " " << biny << std::endl;
      
  // //  //    }
  
  // //c40->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/AsymmPeriodA.pdf");

   
  // // c50->cd(1);
  // // gStyle->SetErrorX(0);
  // // h_averagebin->SetMarkerStyle(20);
  // // h_averagebin->SetMarkerColorAlpha( kRed, 0.35 );
  // // h_averagebinB->SetMarkerStyle(20);
  // // h_averagebinB->SetMarkerColorAlpha( kBlue, 0.35 );
  // // h_averagebin->GetXaxis()->SetTitle("Xbj");
  // // h_averagebin->GetYaxis()->SetTitle("-t_{proton} [GeV^{2}]");
  // // h_averagebin->GetXaxis()->CenterTitle();
  // // h_averagebin->GetYaxis()->CenterTitle();
  // // h_averagebin->Draw("same");
  // // h_averagebinB->Draw("same");

  // c50->cd(1);
  // gStyle->SetErrorX(0);
  // h_Bepgyieldspp->SetMarkerStyle(20);
  // h_Bepgyieldspp->SetMarkerSize(1);
  // h_Bepgyieldspp->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Bepgyieldspp->SetTitle("B_{pp}");
  // h_Bepgyieldspp->Draw("P0");

  // c50->cd(2);
  // gStyle->SetErrorX(0);
  // h_Bepgyieldspn->SetMarkerStyle(20);
  // h_Bepgyieldspn->SetMarkerSize(1);
  // h_Bepgyieldspn->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Bepgyieldspn->SetTitle("B_{pn}");
  // h_Bepgyieldspn->Draw("P0");

  // c50->cd(3);
  // gStyle->SetErrorX(0);
  // h_Bepgyieldsnp->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Bepgyieldsnp->SetMarkerStyle(20);
  // h_Bepgyieldsnp->SetMarkerSize(1);
  // h_Bepgyieldsnp->SetTitle("B_{np}");
  // h_Bepgyieldsnp->Draw("P0");

  // c50->cd(4);
  // gStyle->SetErrorX(0);
  // h_Bepgyieldsnn->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Bepgyieldsnn->SetMarkerStyle(20);
  // h_Bepgyieldsnn->SetMarkerSize(1);
  // h_Bepgyieldsnn->SetTitle("B_{nn}");  
  // h_Bepgyieldsnn->Draw("P0");

  // c50->cd(5);
  // gStyle->SetErrorX(0);
   h_BepgyieldsPPPN->Add(h_Bepgyieldspp,h_Bepgyieldspn,1,1);
   h_BepgyieldsPPPN_pol->Add(h_Bepgyieldspp,h_Bepgyieldspn, BPtminus, BPtminus);
  // h_BepgyieldsPPPN->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_BepgyieldsPPPN->SetMarkerStyle(20);
  // h_BepgyieldsPPPN->SetMarkerSize(1);
  // h_BepgyieldsPPPN->SetTitle("B_{PPPN}");
  // h_BepgyieldsPPPN->Draw("P0");

  // c50->cd(6);
  // gStyle->SetErrorX(0);
   h_BepgyieldsNPNN->Add(h_Bepgyieldsnp,h_Bepgyieldsnn,1,1);
   h_BepgyieldsNPNN_pol->Add(h_Bepgyieldsnp,h_Bepgyieldsnn, BPtplus, BPtplus);
  // h_BepgyieldsNPNN->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_BepgyieldsNPNN->SetMarkerStyle(20);
  // h_BepgyieldsNPNN->SetMarkerSize(1);
  // h_BepgyieldsNPNN->SetTitle("B_{NPNN}");
  // h_BepgyieldsNPNN->Draw("P0");

  // c50->cd(7);
  // gStyle->SetErrorX(0); 
   h_Basymmetrytop->Add(h_BepgyieldsPPPN,h_BepgyieldsNPNN,1,-1);
  // h_Basymmetrytop->SetMarkerColorAlpha( kRed, 0.35 );
  // h_Basymmetrytop->SetMarkerStyle(20);
  // h_Basymmetrytop->SetMarkerSize(1);
  // h_Basymmetrytop->SetTitle("B_{top} red");
  // h_Basymmetrytop->Draw("P0");

  // c50->cd(8);
   h_Basymmetrybot->Add(h_BepgyieldsPPPN_pol,h_BepgyieldsNPNN_pol, Bdilution, Bdilution);
  // h_Basymmetrybot->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Basymmetrybot->SetMarkerStyle(20);
  // h_Basymmetrybot->SetMarkerSize(1);
  // h_Basymmetrybot->SetTitle("B_{bot} blue");
  // h_Basymmetrybot->Draw("P0");  
  
  // //h_Aasymmetry->GetXaxis()->SetTitle("#phi [Deg]");
  // //h_Aasymmetry->GetYaxis()->SetTitle("Asy");
  // //h_Aasymmetry->GetXaxis()->CenterTitle();
  // //h_Aasymmetry->GetYaxis()->CenterTitle();
  // //h_Aasymmetry->Sumw2();
  

  // c50->cd(9);
  // h_Basymmetry->Divide(h_Basymmetrytop,h_Basymmetrybot, 1.0, 1.0);
  // h_Basymmetry->SetMarkerColorAlpha( kBlue, 0.35 );
  // h_Basymmetry->SetMarkerStyle(20);
  // h_Basymmetry->SetMarkerSize(1);
  // h_Basymmetry->GetXaxis()->SetTitle("#phi [Deg]");
  // h_Basymmetry->GetYaxis()->SetTitle("Asy");
  // h_Basymmetry->GetXaxis()->CenterTitle();
  // h_Basymmetry->GetYaxis()->CenterTitle();
  // //h_Basymmetry->Sumw2();
  // h_Basymmetry->SetTitle("B_{asym}");
  // h_Basymmetry->Draw("P0");
  

  // //c50->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/AsymmPeriodB.pdf");  

  
  // c60->cd(1);
  // h_hthetavslphi->GetXaxis()->SetTitle("Theta");
  // h_hthetavslphi->GetYaxis()->SetTitle("Phi");
  // h_hthetavslphi->Draw("colz");
  
  // // c60->cd(1);
  // // h_leptontheta->GetXaxis()->SetTitle("Theta");
  // // h_leptontheta->Draw();
  // c60->cd(2);
  // h_leptonphi->GetXaxis()->SetTitle("Phi");
  // h_leptonphi->Draw();
  // c60->cd(3);
  // h_leptonthetavsphi->GetXaxis()->SetTitle("Theta");
  // h_leptonthetavsphi->GetYaxis()->SetTitle("Phi");
  // h_leptonthetavsphi->Draw("colz");

  // // c60->cd(4);
  // // h_hadrontheta->GetXaxis()->SetTitle("Theta");
  // // h_hadrontheta->Draw();
  // // c60->cd(5);
  // // h_hadronphi->GetXaxis()->SetTitle("Phi");
  // // h_hadronphi->Draw();
  // // c60->cd(6);
  // // h_hadronthetavsphi->GetXaxis()->SetTitle("Theta");
  // // h_hadronthetavsphi->GetYaxis()->SetTitle("Phi");
  // // h_hadronthetavsphi->Draw("colz");

  // // c60->cd(7);
  // // h_ECleptontheta->GetXaxis()->SetTitle("Theta");
  // // h_ECleptontheta->Draw();
  // // c60->cd(8);
  // // h_ECleptonphi->GetXaxis()->SetTitle("Phi");
  // // h_ECleptonphi->Draw();
  // // c60->cd(9);
  // // h_ECleptonthetavsphi->GetXaxis()->SetTitle("Theta");
  // // h_ECleptonthetavsphi->GetYaxis()->SetTitle("Phi");
  // // h_ECleptonthetavsphi->Draw("colz");

  // // c60->cd(10);
  // // h_EChadrontheta->GetXaxis()->SetTitle("Theta");
  // // h_EChadrontheta->Draw();
  // // c60->cd(11);
  // // h_EChadronphi->GetXaxis()->SetTitle("Phi");
  // // h_EChadronphi->Draw();
  // // c60->cd(12);
  // // h_EChadronthetavsphi->GetXaxis()->SetTitle("Theta");
  // // h_EChadronthetavsphi->GetYaxis()->SetTitle("Phi");
  // // h_EChadronthetavsphi->Draw("colz");

  // c60->cd(4);
  // h_ecratesA->GetXaxis()->SetTitle("ecrateA");
  // h_ecratesA->Draw();
  // c60->cd(5);
  // h_icratesA->GetXaxis()->SetTitle("icrateA");   
  // h_icratesA->Draw();
  // c60->cd(6);
  // h_ecratesB->GetXaxis()->SetTitle("ecrateB");
  // h_ecratesB->Draw();
  // c60->cd(7);
  // h_icratesB->GetXaxis()->SetTitle("icrateB");   
  // h_icratesB->Draw();
  
   top->Write();
   delete top;
// //c60->SaveAs("/Users/bclary/Documents/work/thesis work/eg1analysis/analysiscode_v1/results/DetectorHits.pdf");
    
}


  

