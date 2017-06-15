#define dvcshistomonitor_cxx
#include "../include/DVCSHistoMonitor.h"
#include "../include/PhysicsCuts.h"
#include "../include/EventPID.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMath.h"
#include "TString.h"

#include <vector>
#include <string>
#include <map>

DVCSHistoMonitor::DVCSHistoMonitor(){


}

DVCSHistoMonitor::DVCSHistoMonitor(Calculator tempcalc){

  InitiateRunInfo( tempcalc );

}


DVCSHistoMonitor::~DVCSHistoMonitor(){


}

void DVCSHistoMonitor::InitiateRunInfo( Calculator tempcalc ){



}


void DVCSHistoMonitor::CreateDVCSHist( PhysicsCutManager pcmanager, BDVCSHistograms dvcshist ){

  //std::cout << " Creating DVCS Histograms to Fill " << std::endl;
  Int_t numdiscuts = pcmanager.applieddiscuts.size();
  //  Int_t numdvcscuts = pcmanager.appliedvcscuts.size();

  for( int i = 1; i <= numdiscuts; i++ ){

    bdvcshist.ElDVCSHist(i);
    bdvcshist.PrDVCSHist(i);
    bdvcshist.PhDVCSHist(i);
    bdvcshist.DVCSKinHistEC(i);
    bdvcshist.DVCSKinHistIC(i);
    bdvcshist.AsymHistA(i);
    bdvcshist.AsymHistB(i);

  }

}

void DVCSHistoMonitor::FillDVCSElHist( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    if( (*it) ){
    bdvcshist.h1_el_px[j]->Fill(dvcs.el_px);
    bdvcshist.h1_el_py[j]->Fill(dvcs.el_py);
    bdvcshist.h1_el_pz[j]->Fill(dvcs.el_pz);
    bdvcshist.h1_el_E[j]->Fill(dvcs.el_E);
    bdvcshist.h1_el_p[j]->Fill(dvcs.el_px);
    bdvcshist.h1_el_vertex[j]->Fill(dvcs.el_vertex);
    bdvcshist.h1_el_dcsect[j]->Fill(dvcs.el_DCsect);
    bdvcshist.h1_el_thetadc[j]->Fill(dvcs.el_thetadc);
    bdvcshist.h1_el_nphe[j]->Fill(dvcs.el_nphe);
    j++;

    }
    else{
      break;
    }
  }
}


void DVCSHistoMonitor::FillDVCSPrHist( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    if( (*it) ){
    bdvcshist.h1_pr_px[j]->Fill(dvcs.pr_px);
    bdvcshist.h1_pr_py[j]->Fill(dvcs.pr_py);
    bdvcshist.h1_pr_pz[j]->Fill(dvcs.pr_pz);
    bdvcshist.h1_pr_E[j]->Fill(dvcs.pr_E);
    bdvcshist.h1_pr_p[j]->Fill(dvcs.pr_px);
    bdvcshist.h1_pr_vertex[j]->Fill(dvcs.pr_vertex);
    bdvcshist.h1_pr_dcsect[j]->Fill(dvcs.pr_DCsect);
    bdvcshist.h1_pr_thetadc[j]->Fill(dvcs.pr_thetadc);
    bdvcshist.h1_pr_nphe[j]->Fill(dvcs.pr_nphe);
    j++;
    }
    else{
      break;
    }
  }
}


void DVCSHistoMonitor::FillDVCSPhHist( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    if( (*it) ){
    bdvcshist.h1_ph_px[j]->Fill(dvcs.ph_px);
    bdvcshist.h1_ph_py[j]->Fill(dvcs.ph_py);
    bdvcshist.h1_ph_pz[j]->Fill(dvcs.ph_pz);
    bdvcshist.h1_ph_E[j]->Fill(dvcs.ph_E);
    bdvcshist.h1_ph_p[j]->Fill(dvcs.ph_px);

    j++;
    }
    else{
      break;
    }
  }
}


void DVCSHistoMonitor::FillDVCSKinECHist( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    if( (*it) ){
    bdvcshist.h1_qq[j]->Fill(dvcs.qq);
    bdvcshist.h1_xb[j]->Fill(dvcs.xb);
    bdvcshist.h1_w[j]->Fill(dvcs.w_);
    bdvcshist.h1_t[j]->Fill(-dvcs.t_);
    bdvcshist.h1_tp[j]->Fill(-dvcs.tp_);
    bdvcshist.h1_MM[j]->Fill(dvcs.MM);
    bdvcshist.h1_MM2epg[j]->Fill(dvcs.MM2epg);
    bdvcshist.h1_eps[j]->Fill(dvcs.eps);
    bdvcshist.h1_deltatheta[j]->Fill(dvcs.deltatheta/(3.14159) * 180.0);
    bdvcshist.h1_deltaphi[j]->Fill(dvcs.delta_phi/(3.14159) * 180.0);
    //    std::cout << " ec phi " << (dvcs.phi_)/(3.14159) * 180.0 << std::endl;
    bdvcshist.h1_phi[j]->Fill((dvcs.phi_)/(3.14159) * 180.0);
    bdvcshist.h1_Dephi[j]->Fill(dvcs.Dephi/(3.14159) * 180.0);
    bdvcshist.h1_perpx[j]->Fill(dvcs.perpx);
    bdvcshist.h1_perpy[j]->Fill(dvcs.perpy);
    bdvcshist.h1_pPerp[j]->Fill(dvcs.pPerp);

    bdvcshist.h2_q2x[j]->Fill(dvcs.xb,dvcs.qq);
    bdvcshist.h2_tx[j]->Fill(-dvcs.tp_,dvcs.qq);
    bdvcshist.h2_wx[j]->Fill(dvcs.xb,dvcs.w_);
    bdvcshist.h2_wq2[j]->Fill(dvcs.qq,dvcs.w_);

    j++;
    }
    else{
      break;
    }
  }
}


void DVCSHistoMonitor::FillDVCSKinICHist( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    if( (*it) ){
    bdvcshist.h1_qq_ic[j]->Fill(dvcs.qq);
    bdvcshist.h1_xb_ic[j]->Fill(dvcs.xb);
    bdvcshist.h1_w_ic[j]->Fill(dvcs.w_);
    bdvcshist.h1_t_ic[j]->Fill(-dvcs.t_);
    bdvcshist.h1_tp_ic[j]->Fill(-dvcs.tp_);
    bdvcshist.h1_MM_ic[j]->Fill(dvcs.MM);
    bdvcshist.h1_MM2epg_ic[j]->Fill(dvcs.MM2epg);
    bdvcshist.h1_eps_ic[j]->Fill(dvcs.eps);
    bdvcshist.h1_deltatheta_ic[j]->Fill(dvcs.deltatheta/(3.14159) * 180.0);
    bdvcshist.h1_deltaphi_ic[j]->Fill(dvcs.delta_phi/(3.14159) * 180.0);
    //std::cout << " ic phi " << (dvcs.phi_)/(3.14159) * 180.0 << std::endl;
    bdvcshist.h1_phi_ic[j]->Fill((dvcs.phi_)/(3.14159) * 180.0);
    bdvcshist.h1_Dephi_ic[j]->Fill(dvcs.Dephi/(3.14159) * 180.0);
    bdvcshist.h1_perpx_ic[j]->Fill(dvcs.perpx);
    bdvcshist.h1_perpy_ic[j]->Fill(dvcs.perpy);
    bdvcshist.h1_pPerp_ic[j]->Fill(dvcs.pPerp);
    bdvcshist.h2_q2x_ic[j]->Fill(dvcs.xb,dvcs.qq);
    bdvcshist.h2_tx_ic[j]->Fill(-dvcs.tp_,dvcs.qq);
    bdvcshist.h2_wx_ic[j]->Fill(dvcs.xb,dvcs.w_);
    bdvcshist.h2_wq2_ic[j]->Fill(dvcs.qq,dvcs.w_);

    j++;
    }
    else{
      break;
    }
  }
}


void DVCSHistoMonitor::FillAsymHistA( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    //std::cout << dvcs.targetPolarization << std::endl;
    if( (*it) ){
      if( dvcs.targetPolarization > 0 && dvcs.beamHelicity == 1 ){
	bdvcshist.h1_Aepgyield_pp[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      if( dvcs.targetPolarization > 0 && dvcs.beamHelicity == 0 ){
	bdvcshist.h1_Aepgyield_pn[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      if( dvcs.targetPolarization < 0 && dvcs.beamHelicity == 1 ){
	bdvcshist.h1_Aepgyield_np[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      if( dvcs.targetPolarization < 0 && dvcs.beamHelicity == 0 ){
	bdvcshist.h1_Aepgyield_nn[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      } 

      bdvcshist.h1_Aepgyield_PPPN[j]->Add(bdvcshist.h1_Aepgyield_pp[j],bdvcshist.h1_Aepgyield_pn[j],1,1);
      bdvcshist.h1_Aepgyield_NPNN[j]->Add(bdvcshist.h1_Aepgyield_np[j],bdvcshist.h1_Aepgyield_nn[j],1,1);
      bdvcshist.h1_Aasymmetry_Top[j]->Add(bdvcshist.h1_Aepgyield_PPPN[j],bdvcshist.h1_Aepgyield_NPNN[j], 1, -1);
      bdvcshist.h1_Aasymmetry_Bot[j]->Add(bdvcshist.h1_Aepgyield_PPPN[j],bdvcshist.h1_Aepgyield_NPNN[j], 1, 1);
      bdvcshist.h1_Atargetasymmetry[j]->Divide(bdvcshist.h1_Aasymmetry_Top[j],bdvcshist.h1_Aasymmetry_Bot[j], 1.0, 1.0);
      
      //if ( j == 7 ){
	//std::cout << " tarpol: " << dvcs.targetPolarization << " helicity: " << dvcs.beamHelicity << " phi: " << dvcs.phi_/(3.14159) * 180.0 << std::endl;
      //}
      j++;
    }
    else{
      break;
    }
  }
}


void DVCSHistoMonitor::FillAsymHistB( std::vector<bool> dvcspass, EventPID dvcs, Int_t run ){
  std::vector<bool>::iterator it;
  Int_t j = 0;
  for( it = dvcspass.begin(); it != dvcspass.end(); ++it ){
    if( (*it) ){
      if( dvcs.targetPolarization > 0 && dvcs.beamHelicity == 1 ){
	bdvcshist.h1_Bepgyield_pp[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      if( dvcs.targetPolarization > 0 && dvcs.beamHelicity == 0 ){
	bdvcshist.h1_Bepgyield_pn[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      if( dvcs.targetPolarization < 0 && dvcs.beamHelicity == 1 ){
	bdvcshist.h1_Bepgyield_np[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      if( dvcs.targetPolarization < 0 && dvcs.beamHelicity == 0 ){
	bdvcshist.h1_Bepgyield_nn[j]->Fill(dvcs.phi_/(3.14159) * 180.0);
      }
      bdvcshist.h1_Bepgyield_PPPN[j]->Add(bdvcshist.h1_Bepgyield_pp[j],bdvcshist.h1_Bepgyield_pn[j],1,1);
      bdvcshist.h1_Bepgyield_NPNN[j]->Add(bdvcshist.h1_Bepgyield_np[j],bdvcshist.h1_Bepgyield_nn[j],1,1);
       
      bdvcshist.h1_Basymmetry_Top[j]->Add(bdvcshist.h1_Bepgyield_PPPN[j],bdvcshist.h1_Bepgyield_NPNN[j], 1, -1);
      bdvcshist.h1_Basymmetry_Bot[j]->Add(bdvcshist.h1_Bepgyield_PPPN[j],bdvcshist.h1_Bepgyield_NPNN[j], 1, 1);
      bdvcshist.h1_Btargetasymmetry[j]->Divide(bdvcshist.h1_Basymmetry_Top[j],bdvcshist.h1_Basymmetry_Bot[j],1.0,1.0);
      
      j++;
     
    }
    else{
      break;
    }
  }
}





