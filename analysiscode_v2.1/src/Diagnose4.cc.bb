#include "../include/Cuts.h"
#include "../include/CutManager.h"
#include "../include/PhysicsCutManager.h"
#include "../include/PhysicsEvent.h"
#include "../include/Calculator.h"
#include "../include/EventPID.h"
#include "../include/LoadPID.h"
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
 
  TH1D *h_Basymmetrybot = new TH1D("h_Basymmetrybot","", 10, 0.0, 360.0 );
  TH1D *h_Basymmetry = new TH1D("h_Basymmetry","", 10, 0.0, 360.0 );
 
  LoadPID tPID;
  RunDB eg1rundata;
  tPID.MakeChain("/Users/bclary/Documents/work/run data/DVCSresults/",93);
  tPID.Init();
  Int_t nentries = tPID.NumEntries();

  Calculator rundep;
  rundep.SetRunParameters(59519);
  PhysicsEvent physevents;
  PhysicsCutManager physmanager(rundep);
  
  physmanager.InitializeCutsFor("DIS");
  physmanager.InitializeCutsFor("DVCS");
  TLorentzVector target( 0, 0, 0, 0.938 );
  PhysicsEventBuilder buildPhys(rundep.BeamEnergyCorrection(59519), target, rundep );
  
  Int_t iccounter = 0 ;
  Int_t eccounter = 0;
  for( Int_t i = 0; i<nentries; i++ ){
    TLorentzVector el_LV( 0, 0, 0, 0);
    TLorentzVector pr_LV( 0, 0, 0, 0);
    TLorentzVector ph_LV( 0, 0, 0, 0);
  
    tPID.GetEntry(i);
    EventPID pidevent = tPID.GetEvent();
    
    el_LV.SetPxPyPzE( pidevent.el_px,
		      pidevent.el_py,
		      pidevent.el_pz,
		      pidevent.el_E );
    
    pr_LV.SetPxPyPzE( pidevent.pr_px,
		      pidevent.pr_py,
		      pidevent.pr_pz,
		      pidevent.pr_E );
    
    ph_LV.SetPxPyPzE( pidevent.ph_px,
		      pidevent.ph_py,
		      pidevent.ph_pz,
		      pidevent.ph_E );
    
    eg1rundata.OpenDB();
    //TString PeriodID = eg1rundata.Query("RunConfiguration","PeriodID", event.RunNumber );
    //TString TargetType = eg1rundata.Query("TargetConfiguration","Target", event.RunNumber );
    eg1rundata.CloseDB();


    // std::cout << " DIS Test Here " << std::endl;
    bool foundDIS = false;
      if( !foundDIS ){
      	foundDIS = physmanager.PassCut("DIS", buildPhys.getPhysicsEvent( el_LV, pr_LV, ph_LV ) );
      	if( foundDIS ){
      	  // std::cout << " Found DIS reaction " << std::endl;
      	  // std::cout << " DVCS Test Here " << std::endl;
	  // 1000 -> IC and 2000 -> EC 
	  if ( pidevent.photonTopology == 1000 ) {
	    iccounter++;
	  }
	  if( pidevent.photonTopology == 2000 ){
	    eccounter++;
	  }
	  // bool foundDVCS = false;
	  //if ( !foundDVCS ){
	  //foundDVCS = physmanager.PassCut("DVCS", buildPhys.getPhysicsEvent( el_LV, pr_LV, ph_LV ) );
	  //if( foundDVCS ){
      	      //std::cout << " Found DVCS reaction " << std::endl;
      	      //buildPhys.setHelicity( pidevent.beamHelicity );		  
	      // dvcshisttool.MakeDVCSElectronPlots( buildPhys, photondetectorhitID );
      	      //dvcshisttool.MakeDVCSProtonPlots( buildPhys, photondetectorhitID );
      	      //dvcshisttool.AsymmetryHistograms(buildPhys, -1 );
	      // buildtDVCS.Fill( buildPhys.getPhysicsEvent( el_LV, pr_LV, photonLV ) );


      	      //dvcshisttool.MakeDVCSKinematicsPlots( buildPhys, photondetectorhitID );

      	      //fillcounter++;
	  // }
      	  //}
      	}	
      }

  }

std::cout << " total ic hits " << iccounter << " total ec hits " << eccounter << std::endl;
  return 0;
}
