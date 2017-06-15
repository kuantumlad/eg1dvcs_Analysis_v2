#define pidhistomonitor_cxx
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/PIDHistoMonitor.h"
#include "../include/Loadh22.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMath.h"
#include "TString.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>



PIDHistoMonitor::PIDHistoMonitor(){

}


PIDHistoMonitor::PIDHistoMonitor(Calculator tempcalc){
  InitiateRunInfo( tempcalc );
  SpeedOfLight = 29.9792458;

}

PIDHistoMonitor::~PIDHistoMonitor(){

}

void PIDHistoMonitor::InitiateRunInfo( Calculator tempcalc ){
  this->calculator = tempcalc;
  target_vz = calculator.targetPos;
  shiftTime = calculator.shiftTiming_eccut;
  offsetTime = calculator.offsetTiming;
  ecsf1 = calculator.ecSF1;
  ecsf2 = calculator.ecSF2;
  ecsf3 = calculator.ecSF3;
  ecsf4 = calculator.ecSF4;
  ecsf5 = calculator.ecSF5;
  ecsf6 = calculator.ecSF6;

}

//create levels of histo for each cut
void PIDHistoMonitor::CreatePIDHist( CutManager cmanager, BPIDHistograms pidhist){

  std::cout << ">>> Creating Histograms to Fill <<< " << std::endl;
  Int_t numelcuts = cmanager.appliedelectroncuts.size();
  Int_t numprcuts = cmanager.appliedprotoncuts.size();
  Int_t numecphcuts = cmanager.appliedphotoncuts.size();
  Int_t numicphcuts = cmanager.appliedicphotoncuts.size();

  for(int i = 1; i <= numelcuts; i++ ){    
    bpidhist.ElCutBasedHist(i);    
  }
  for(int i = 1; i <= numprcuts; i++ ){    
    bpidhist.PrCutBasedHist(i);    
  }
  for(int i = 1; i <= numecphcuts; i++ ){    
    bpidhist.ECPhCutBasedHist(i);
  }
  for(int i = 1; i <= numicphcuts; i++ ){    
    bpidhist.ICPhCutBasedHist(i);
  }
}

void PIDHistoMonitor::FillElectronHisto( std::vector<bool> temppassrate, Eventh22 &event, Int_t index, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  //  Double_t *ec_energy_corr = calculator.ECSFCorrection( event, index, run );
      
  for( it = temppassrate.begin(); it != temppassrate.end(); ++it ){
    if( (*it) ){
      Double_t *el_cosine = calculator.CosineCorrection( run, event, index);
      Double_t el_phi = (atan2( el_cosine[1], el_cosine[0] ))*TMath::RadToDeg();
      Double_t el_theta = acos(sqrt(1 - event.tl1_cx[index]*el_cosine[0] - event.tl1_cy[index]*el_cosine[1]))*(TMath::RadToDeg()); 

      Double_t etot_corr = event.etot[index];
      Double_t ei_corr = event.ec_ei[index];
      Double_t eo_corr = event.ec_eo[index];
      Int_t ecsector = event.ec_sect[index];
      //std::cout << " Electron sector is " << runnumber << std::endl;
      if( 0 < ecsector && ecsector < 7 ){
	ecscalefactor = 0;
	//std::cout << " Going to set ecscalefactor for sect " << ecsector << std::endl;
	if( ecsector == 1 ){ ecscalefactor = ecsf1;}
	if( ecsector == 2 ){ ecscalefactor = ecsf2;}
	if( ecsector == 3 ) ecscalefactor = ecsf3;
	if( ecsector == 4 ) ecscalefactor = ecsf4;
	if( ecsector == 5 ) ecscalefactor = ecsf5;
	if( ecsector == 6 ) ecscalefactor = ecsf6;
	//std::cout << " The scalefactor is " << ecscalefactor << std::endl;
      }
      //std::cout << " Since the electron hit " << ecsector << "the ecSF is " << ecscalefactor << std::endl;
      if( 0.0 < event.etot[index] &&  event.etot[index] < 5.0 ){
	etot_corr = event.etot[index]*( 0.2765/ecscalefactor );
	//std::cout << " etot corrected to " << etot_corr << std::endl;
      }
      if( 0.0 < event.ec_ei[index] && event.ec_ei[index] < 5.0 ){
	ei_corr = event.ec_ei[index]*( 0.2765/ecscalefactor );
	//std::cout << " ei corrected to " << ei_corr << std::endl;
      }
      if( 0.0 < event.ec_eo[index] && event.ec_eo[index] < 5.0 ){
	eo_corr = event.ec_eo[index]*( 0.2765/ecscalefactor );
	//  std::cout << " eo corrected to " << eo_corr << std::endl;
      }
      Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);
      
      bpidhist.h_el_1d[j]->Fill(event.p[index]);
      bpidhist.h1_el_vertex[j]->Fill(-target_vz + el_cosine[3]);
      bpidhist.h1_el_cc2[j]->Fill(event.cc_c2[index]);
      bpidhist.h1_el_timing[j]->Fill(event.cc_t[index] -event.cc_r[index]/SpeedOfLight - event.sc_t[index] + event.sc_r[index]/SpeedOfLight);//event.cc_t[index] - event.cc_r[index]/SpeedOfLight - event.sc_t[index] + event.sc_r[index]/SpeedOfLight+shiftTime+offsetTime));
      bpidhist.h1_el_ecdepinner[j]->Fill(event.edep[index]);
      bpidhist.h1_el_nphe[j]->Fill(event.nphe[index]);
      bpidhist.h1_el_sct[j]->Fill(event.sc_t[index]);
      bpidhist.h1_el_ect[j]->Fill(event.ec_t[index]);
      
      if( event.ec_ei[index] != 0 ){
	bpidhist.h1_el_eci[j]->Fill(ei_corr);
      }
      else{
	bpidhist.h1_el_eci[j]->Fill(ecmax - eo_corr);
      }
      
      bpidhist.h2_el_ecEIEO[j]->Fill(ei_corr, eo_corr);
      bpidhist.h2_el_etotvsp[j]->Fill(event.p[index], ecmax);
      bpidhist.h2_el_etotpvsp[j]->Fill(event.p[index], ecmax/event.p[index]);
      bpidhist.h2_el_etotvsei[j]->Fill(ei_corr, ecmax );
      bpidhist.h2_el_echit[j]->Fill(event.ech_x[index], event.ech_y[index]);
      bpidhist.h2_el_icshadhit[j]->Fill(event.tl1_x[index] - event.tl1_cx[index]*event.tl1_z[index], event.tl1_y[index] - event.tl1_cy[index]*event.tl1_z[index] );
      bpidhist.h2_el_vertexPhi[j]->Fill(-target_vz + event.vz[index], el_phi);
      bpidhist.h2_el_ecdcsect[j]->Fill(event.ec_sect[index],event.dc_sect[index]);
      bpidhist.h2_el_ccdcsect[j]->Fill(event.dc_sect[index],event.cc_sect[index]);
      
      j++;	
    }
    else {
      break;
    }
  }
}

  void PIDHistoMonitor::FillProtonHisto( std::vector<bool> temppassrate, Eventh22 &event, Int_t index, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = temppassrate.begin(); it != temppassrate.end(); ++it ){
    if( (*it) ){
      Double_t el_starttime = event.sc_t[event.goldenelectronindex]-event.sc_r[event.goldenelectronindex]/SpeedOfLight; 
      Double_t *pr_cosine = calculator.CosineCorrection( run, event, index);
      Double_t pr_phi = (atan2( pr_cosine[1], pr_cosine[0] ))*TMath::RadToDeg();
      Double_t pr_theta = acos(sqrt(1 - event.tl1_cx[index]*pr_cosine[0] - event.tl1_cy[index]*pr_cosine[1]))*(TMath::RadToDeg()); 
      Double_t MPROT = 0.938272;
      Double_t protonBeta = event.sc_r[index]/(event.sc_t[index]-el_starttime)/SpeedOfLight;
      Double_t protonBetaCalc = sqrt(event.p[index]*event.p[index]/(event.p[index]*event.p[index]+MPROT*MPROT));
      Double_t deltaT = (event.sc_t[index]- el_starttime) - event.sc_r[index]/(SpeedOfLight*protonBetaCalc);
      Double_t deltaB = protonBeta - protonBetaCalc;

      bpidhist.h1_pr_p[j]->Fill(event.p[index]);
      bpidhist.h1_pr_vertex[j]->Fill(-target_vz + pr_cosine[3]);
      bpidhist.h1_pr_beta[j]->Fill(event.b[index]);
      bpidhist.h1_pr_sctiming[j]->Fill(event.sc_t[index]);//el_starttime);
      bpidhist.h2_pr_deltaTvsp[j]->Fill(event.p[index], deltaT );
      bpidhist.h2_pr_deltaBvsp[j]->Fill( event.p[index], deltaB );
      bpidhist.h2_pr_bvsp[j]->Fill( event.p[index], protonBeta );

      bpidhist.h2_pr_echit[j]->Fill(event.ech_x[index], event.ech_y[index]);
      bpidhist.h2_pr_icshadhit[j]->Fill(event.tl1_x[index] - event.tl1_cx[index]*event.tl1_z[index], event.tl1_y[index] - event.tl1_cy[index]*event.tl1_z[index] );
      bpidhist.h2_pr_vertexPhi[j]->Fill(-target_vz + event.vz[index], pr_phi);
      j++;	
    }
    else {
      break;
    }
  }
}

void PIDHistoMonitor::FillECPhotonHisto( std::vector<bool> temppassrate, Eventh22 &event, Int_t index, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = temppassrate.begin(); it != temppassrate.end(); ++it ){
    if( (*it) ){
      
      Double_t etot_corr = event.etot[index];
      Double_t ei_corr = event.ec_ei[index];
      Double_t eo_corr = event.ec_eo[index];
      Int_t ecsector = event.ec_sect[index];
      //std::cout << " Electron sector is " << runnumber << std::endl;
      if( 0 < ecsector && ecsector < 7 ){
	ecscalefactor = 0;
	//std::cout << " Going to set ecscalefactor for sect " << ecsector << std::endl;
	if( ecsector == 1 ){ ecscalefactor = ecsf1;}
	if( ecsector == 2 ){ ecscalefactor = ecsf2;}
	if( ecsector == 3 ) ecscalefactor = ecsf3;
	if( ecsector == 4 ) ecscalefactor = ecsf4;
	if( ecsector == 5 ) ecscalefactor = ecsf5;
	if( ecsector == 6 ) ecscalefactor = ecsf6;
	//std::cout << " The scalefactor is " << ecscalefactor << std::endl;
      }
      //std::cout << " Since the electron hit " << ecsector << "the ecSF is " << ecscalefactor << std::endl;
      if( 0.0 < event.etot[index] &&  event.etot[index] < 5.0 ){
	etot_corr = event.etot[index]*( 0.2765/ecscalefactor );
	//std::cout << " etot corrected to " << etot_corr << std::endl;
      }
      if( 0.0 < event.ec_ei[index] && event.ec_ei[index] < 5.0 ){
	ei_corr = event.ec_ei[index]*( 0.2765/ecscalefactor );
	//std::cout << " ei corrected to " << ei_corr << std::endl;
      }
      if( 0.0 < event.ec_eo[index] && event.ec_eo[index] < 5.0 ){
	eo_corr = event.ec_eo[index]*( 0.2765/ecscalefactor );
	//  std::cout << " eo corrected to " << eo_corr << std::endl;
      }
      Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);
      Double_t *posrastr = calculator.RasterCorrection( run, event, index );      
      Double_t el_starttime = event.sc_t[event.goldenelectronindex]-event.sc_r[event.goldenelectronindex]/SpeedOfLight; 
      Double_t photonBeta = event.ec_r[index]/(event.ec_t[index]-el_starttime)/SpeedOfLight;

      bpidhist.h1_ecph_b[j]->Fill(photonBeta);
      bpidhist.h1_ecph_edep[j]->Fill(ecmax/0.2765);
      bpidhist.h2_ecph_echit[j]->Fill(event.ech_x[index], event.ech_y[index]);
      bpidhist.h2_ecph_icshadhit[j]->Fill((event.ech_x[index]- posrastr[0]) * -target_vz/(event.ech_z[index]-target_vz) + posrastr[0],(event.ech_y[index]-posrastr[1]) * -target_vz/(event.ech_z[index]-target_vz) + posrastr[1]);
      j++;	
    }
    else {
      break;
    }
  }
}

void PIDHistoMonitor::FillICPhotonHisto( std::vector<bool> temppassrate, Eventh22 &event, Int_t index, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = temppassrate.begin(); it != temppassrate.end(); ++it ){
    if( (*it) ){
      TLorentzVector icphotonLV;
      icphotonLV = calculator.ICphoton_LV(event, index, run );
      bpidhist.h1_icph_etc[j]->Fill(event.etc[index]);
      bpidhist.h1_icph_lvE[j]->Fill(icphotonLV.E());
      bpidhist.h1_icph_lvTheta[j]->Fill(icphotonLV.Theta()*(TMath::RadToDeg()));
      bpidhist.h1_icph_lvPhi[j]->Fill(icphotonLV.Phi()*(TMath::RadToDeg()));
      bpidhist.h2_icph_ichit[j]->Fill(event.xc[index], event.yc[index]);
      bpidhist.h2_icph_moeller[j]->Fill(event.etc[index], icphotonLV.Theta()*TMath::RadToDeg());
      bpidhist.h2_icph_lvThetaPhi[j]->Fill(icphotonLV.Theta()*TMath::RadToDeg(),icphotonLV.Phi()*TMath::RadToDeg());

      j++;	
    }
    else {
      break;
    }
  }
}

