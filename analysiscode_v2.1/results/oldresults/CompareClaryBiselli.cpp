#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TPad.h"
#include "TAttMarker.h"
#include "TTree.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TSystemFile.h"
#include "TRegexp.h"

#include "TChain.h"
#include "TTree.h"
#include "tDVCS.C"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <set>

std::vector< Double_t > ang_AB;
std::vector< Double_t > bcl_AB;
std::map<Double_t, Double_t > Ang_rate;
std::map<Double_t, Double_t > Bcl_rate;

void CompareBiselli( const char* bisellidir ){
  TSystemDirectory dir(bisellidir, bisellidir);
  TList *files_list = dir.GetListOfFiles();
  TSystemFile *file;

  Double_t ang_bad = 0;
  Double_t bcl_bad = 0;
  Double_t run_bad = 0;

  TH1D *h_A_p_cl = new TH1D("h_A_p_cl","",10,0.0,360.0);
  TH1D *h_A_n_cl = new TH1D("h_A_n_cl","",10,0.0,360.0);

  TH1D *h_B_p_cl = new TH1D("h_B_p_cl","",10,0.0,360.0);
  TH1D *h_B_n_cl = new TH1D("h_B_n_cl","",10,0.0,360.0);

  TH1D *h_A_p_bs = new TH1D("h_A_p_bs","",10,0.0,360.0);
  TH1D *h_A_n_bs = new TH1D("h_A_n_bs","",10,0.0,360.0);

  TH1D *h_B_p_bs = new TH1D("h_B_p_bs","",10,0.0,360.0);
  TH1D *h_B_n_bs = new TH1D("h_B_n_bs","",10,0.0,360.0);


  TH1D *h_Atop_cl = new TH1D("h_Atop_cl","",10,0.0,360.0);
  TH1D *h_Abot_cl = new TH1D("h_Abot_cl","",10,0.0,360.0);
  
  TH1D *h_Atop_bs = new TH1D("h_Atop_bs","",10,0.0,360.0);
  TH1D *h_Abot_bs = new TH1D("h_Abot_bs","",10,0.0,360.0);

  TH1D *h_Btop_cl = new TH1D("h_Btop_cl","",10,0.0,360.0);
  TH1D *h_Bbot_cl = new TH1D("h_Bbot_cl","",10,0.0,360.0);
  
  TH1D *h_Btop_bs = new TH1D("h_Btop_bs","",10,0.0,360.0);
  TH1D *h_Bbot_bs = new TH1D("h_Bbot_bs","",10,0.0,360.0);

  TH1D *h_asy_A_cl = new TH1D("h_asy_A_cl","",10,0.0,360.0);
  TH1D *h_asy_B_cl = new TH1D("h_asy_B_cl","",10,0.0,360.0);

  TH1D *h_asy_A_bs = new TH1D("h_asy_A_bs","",10,0.0,360.0);
  TH1D *h_asy_B_bs = new TH1D("h_asy_B_bs","",10,0.0,360.0);

  TH1D *h_tempA_p = new TH1D("h_tempA_p","",10,0.0,360.0);
  TH1D *h_tempA_n = new TH1D("h_tempA_n","",10,0.0,360.0);
  TH1D *h_tempB_p = new TH1D("h_tempB_p","",10,0.0,360.0);
  TH1D *h_tempB_n = new TH1D("h_tempB_n","",10,0.0,360.0);


  std::vector< Double_t > A_p_bs, A_n_bs, B_p_bs, B_n_bs;


  if( files_list ){
    TIter next(files_list);
    while( (file=(TSystemFile*)next()) ){
      TString filename(file->GetName());
      std::string filetocount = (std::string)bisellidir + (std::string)filename;
      if( !file->IsDirectory() && filename.EndsWith(".root") ){
	TFile *ogfile = new TFile((TString)filetocount);

	//NOTE: IsZombie AND NULL CHECK DID NOT WORK TO DISCARD BAD FILES(?)
	if( ogfile->GetSize() < 5000 ) continue;
	TRegexp regexp_run("[0-9][0-9][0-9][0-9][0-9]");
	TString s_run = filename(regexp_run);
	int run =  std::stoi((std::string)s_run);

	TFile *bcfile = new TFile(Form("/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output/DVCSclary_runs/h_dvcs_%d.root",run));
	if (!bcfile ) { std::cout << " FILE NOT FOUND " << std::endl;}	
	TChain *fchain = new TChain("tDVCS");
	
	//ALTERNATIVE TO CHECKING FILES
	int count = 0;
	count+=fchain->Add(Form("/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output/DVCSclary_runs/h_dvcs_%d.root",run));
	if( !fchain ){ std::cout << " ERROR " << count << std::endl; return ;}
	tDVCS *treevar = new tDVCS(fchain);

	Long64_t nentries = fchain->GetEntries();
	Double_t a_p = 0;
	Double_t a_n = 0;
	Double_t b_p = 0;
	Double_t b_n = 0;
	long int nevents = 0;
	
	while( treevar->GetEntry(nevents++) ){
	  std::string target = (std::string)(*treevar->TargetType);
	  std::string group = (std::string)(*treevar->PeriodID); 
	  Int_t run = (treevar->RunNumber);
	  Double_t asy_phi = (treevar->Phi)*(180.0/3.1415926);
	  Double_t tarpol = treevar->TarPol;
	  if( group == 'A' ){// && (target == "NH3T" || target == "NH3B") ){
	    if( tarpol > 0 ){
	      a_p++;
	    }
	    else if( tarpol < 0 ){
	      a_n++;
	    }
	  }
	  if( group == 'B' ){// && (target == "NH3T" || target == "NH3B") ){
	    if( tarpol > 0 ){
	      b_p++;
	    }
	    else if( tarpol < 0 ){
	      b_n++;
	    }
	  }
	}

	TH1D *bcl_dvcs = (TH1D*)bcfile->Get("h1_el_p_cutlvl8");
	TH1D *ang_a_pp = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Aepgyield_PP");
	TH1D *ang_a_pn = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Aepgyield_PN");
	TH1D *ang_a_np = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Aepgyield_NP");
	TH1D *ang_a_nn = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Aepgyield_NN");

	TH1D *ang_b_pp = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Bepgyield_PP");
	TH1D *ang_b_pn = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Bepgyield_PN");
	TH1D *ang_b_np = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Bepgyield_NP");
	TH1D *ang_b_nn = (TH1D*)ogfile->Get("mon histograms/bclary_cuts/apid_Bepgyield_NN");

	Double_t aang_pp = ang_a_pp->GetEntries();
	Double_t aang_pn = ang_a_pn->GetEntries();
	Double_t aang_np = ang_a_np->GetEntries();
	Double_t aang_nn = ang_a_nn->GetEntries();

	Double_t bang_pp = ang_b_pp->GetEntries();
	Double_t bang_pn = ang_b_pn->GetEntries();
	Double_t bang_np = ang_b_np->GetEntries();
	Double_t bang_nn = ang_b_nn->GetEntries();

	Double_t ang_total = aang_pp + aang_pn + aang_np + aang_nn + bang_pp + bang_pn + bang_np + bang_nn;
	Double_t bcl_total = a_p + a_n + b_p + b_n; 
	if( ang_total != bcl_total ){
	  //std::cout << run << " " << ang_total << " " << bcl_total << std::endl;
	  ang_bad+=ang_total;
	  bcl_bad+=bcl_total;
	  run_bad++;
	}
	//ADDED ONLY BECAUSE THERE ARE SEVERAL ANNOYING DIFFERENCES RELATED TO DEFINED TARGET POSITION AND BEAM ENERGY (WHICH ARE WRONG IN BISELLI'S CODE)
	//NOT WORTH CHANGING OVER, THEREFORE ANALYSIS IS OVER FILES THAT DO MATCH
	else if( ang_total == bcl_total ){
	  //std::cout << " Equal Rates " << std::endl;
	  if( run >= 58708 && run <= 59220 ){
	    std::cout << "run " << run << std::endl;
	    h_tempA_p->Add(ang_a_pp, ang_a_pn, 1.0, 1.0);
	    std::cout << " >> " << h_tempA_p->GetEntries() << std::endl;
	    for( int b = 1; b <= h_tempA_p->GetXaxis()->GetNbins(); b++ ){
	      h_A_p_bs->SetBinContent(b, h_tempA_p->GetBinContent(b));
	      //std::cout << " >> " << h_tempA_p->GetBinContent(b) << std::endl;
	    }
	    h_tempA_n->Add(ang_a_np,ang_a_nn);
	    for( int b = 1; b <= h_tempA_n->GetXaxis()->GetNbins(); b++ ){
	      h_A_n_bs->SetBinContent(b, h_tempA_n->GetBinContent(b));
	    }
	  }

	  if( run >= 59221 && run <= 60184 ){
	     h_tempB_p->Add(ang_b_pp,ang_b_pn);
	     for( int b = 1; b <= h_tempB_p->GetXaxis()->GetNbins(); b++ ){
	       h_B_p_bs->SetBinContent(b, h_tempB_p->GetBinContent(b));
	    }
	    h_tempB_n->Add(ang_b_np,ang_b_nn);
	    for( int b = 1; b <= h_tempB_p->GetXaxis()->GetNbins(); b++ ){
	      h_B_n_bs->SetBinContent(b, h_tempB_n->GetBinContent(b));
	    }
	    //h_B_p_bs->Add(ang_b_pp,ang_b_pn);
	    //h_B_n_bs->Add(ang_b_np,ang_b_nn);
	    //std::cout << ">> " << h_A_p_bs->GetEntries() << std::endl;
	  }

	  nevents = 0;
	  while( treevar->GetEntry(nevents++) ){
	    std::string target = (std::string)(*treevar->TargetType);
	    std::string group = (std::string)(*treevar->PeriodID); 
	    Int_t run = (treevar->RunNumber);
	    Double_t asy_phi = (treevar->Phi)*(180.0/3.1415926);
	    Double_t tarpol = treevar->TarPol;
	    //std::cout << " >> " << target << " " << group << " " << run << " "<< asy_phi << " " << tarpol << std::endl;
	    if( group == 'A' ){// && (target == "NH3T" || target == "NH3B") ){
	      if( tarpol > 0 ){
		h_A_p_cl->Fill(asy_phi);
	      }
	      else if( tarpol < 0 ){
		h_A_n_cl->Fill(asy_phi);//h_tsA_P->Fill(asy_phi);
	      }
	    }
	    if( group == 'B' ){// && (target == "NH3T" || target == "NH3B") ){
	      if( tarpol > 0 ){
		h_B_p_cl->Fill(asy_phi);
	      }
	      else if( tarpol < 0 ){
		h_B_n_cl->Fill(asy_phi);
	      }
	    }
	  }	  
	}


	

	
	Ang_rate[run] = ang_total;
	Bcl_rate[run] = bcl_total;
	
	ogfile->Close();
	bcfile->Close();

      }
    }     
  }

  //ADD AND DIVIDE CLARY AND BISELLI HISTOGRAMS
  //CLARY
  Double_t dilute_a = 0.912;
  Double_t dilute_b = 0.928;
  Double_t tarpol_p_a = 0.75;
  Double_t tarpol_n_a = 0.72;
  Double_t fc_A_pp = 1.65813;
  Double_t fc_A_pn = 1.65679;
  Double_t fc_A_np = 1.7595;
  Double_t fc_A_nn = 1.76078;

  Double_t fc_A_p = fc_A_pp + fc_A_pn;
  Double_t fc_A_n = fc_A_np + fc_A_nn;
  
  Double_t fc_B_pp = 2.6607;
  Double_t fc_B_pn = 2.66413;
  Double_t fc_B_np = 2.76767;
  Double_t fc_B_nn = 2.76589;

  Double_t fc_B_p = fc_B_pp + fc_B_pn;
  Double_t fc_B_n = fc_B_np + fc_B_nn;
  
  h_Atop_cl->Add(h_A_p_cl,h_A_n_cl, 1.0/fc_A_p, -1.0/fc_A_n);
  h_Abot_cl->Add(h_A_p_cl,h_A_n_cl, dilute_a*(1.0/fc_A_p), dilute_a*(1.0/fc_A_n));
  h_asy_A_cl->Divide(h_Atop_cl, h_Abot_cl, 1.0, 1.0);

  h_Btop_cl->Add(h_B_p_cl,h_B_n_cl, 1.0/fc_B_p, -1.0/fc_B_n);
  h_Bbot_cl->Add(h_B_p_cl,h_B_n_cl, dilute_b*(1.0/fc_B_p), dilute_b*(1.0/fc_B_n));
  h_asy_B_cl->Divide(h_Btop_cl, h_Bbot_cl, 1.0, 1.0);

  h_Atop_bs->Add(h_A_p_bs,h_A_n_bs, 1.0/fc_A_p, -1.0/fc_A_n);
  h_Abot_bs->Add(h_A_p_bs,h_A_n_bs, dilute_a*(1.0/fc_A_p), dilute_a*(1.0/fc_A_n));
  h_asy_A_bs->Divide(h_Atop_bs,h_Abot_bs);
  
  h_Btop_bs->Add(h_B_p_bs,h_B_n_bs, 1.0/fc_B_p, -1.0/fc_B_n);
  h_Bbot_bs->Add(h_B_p_bs,h_B_n_bs, dilute_b*(1.0/fc_B_p), dilute_b*(1.0/fc_B_n));
  h_asy_B_bs->Divide(h_Btop_bs,h_Bbot_bs);
  
  TCanvas *c1 = new TCanvas("c1","",1200,900);
  gStyle->SetOptStat(0);
  c1->Divide(3,2);
  c1->cd(1);
  h_Atop_cl->SetMarkerStyle(8);
  h_Atop_cl->SetMarkerSize(0.8);
  h_Btop_cl->SetMarkerStyle(8);
  h_Btop_cl->SetMarkerSize(0.8);
  h_Atop_cl->GetXaxis()->SetTitle("#phi [deg] Clary");
  h_Btop_cl->SetMarkerColor(kRed);
  h_Atop_cl->Draw("p");
  h_Btop_cl->Draw("p+same");

  c1->cd(2);
  h_Abot_cl->SetMarkerStyle(8);
  h_Abot_cl->SetMarkerSize(0.8);
  h_Bbot_cl->SetMarkerStyle(8);
  h_Bbot_cl->SetMarkerSize(0.8);
  h_Bbot_cl->SetMarkerColor(kRed);
  h_Abot_cl->Draw("p");
  h_Bbot_cl->Draw("p+same");

  c1->cd(3);
  h_asy_A_cl->SetMarkerStyle(8);
  h_asy_A_cl->SetMarkerSize(0.8);
  h_asy_B_cl->SetMarkerStyle(8);
  h_asy_B_cl->SetMarkerSize(0.8);
  h_asy_B_cl->SetMarkerColor(kRed);
  h_asy_B_cl->SetMarkerColor(kRed);
  h_asy_A_cl->Draw("p");
  h_asy_B_cl->Draw("p+same");

  c1->cd(4);
  h_A_p_cl->Draw();
  h_A_n_cl->Draw("same+hist");

  c1->cd(5);
  h_B_p_cl->Draw();
  h_B_n_cl->Draw("same+hist");

  TCanvas *c2 = new TCanvas("c2","",1200,900);
  c2->Divide(3,2);

  c2->cd(1);
  h_Atop_bs->SetMarkerStyle(8);
  h_Atop_bs->SetMarkerSize(0.8);
  h_Btop_bs->SetMarkerStyle(8);
  h_Btop_bs->SetMarkerSize(0.8);
  h_Atop_bs->Draw("p");
  h_Btop_bs->Draw("p+same");

  c2->cd(2);
  h_Abot_bs->SetMarkerStyle(8);
  h_Abot_bs->SetMarkerSize(0.8);
  h_Bbot_bs->SetMarkerStyle(8);
  h_Bbot_bs->SetMarkerSize(0.8);
  h_Bbot_bs->SetMarkerColor(kRed);
  h_Abot_bs->Draw("p");
  h_Bbot_bs->Draw("p+same");

  c2->cd(3);
  h_asy_A_bs->SetMarkerStyle(8);
  h_asy_A_bs->SetMarkerSize(0.8);
  h_asy_B_bs->SetMarkerStyle(8);
  h_asy_B_bs->SetMarkerSize(0.8);
  h_asy_B_bs->SetMarkerColor(kRed);
  h_asy_A_bs->Draw("p");
  h_asy_B_bs->Draw("p+same");

  c2->cd(4);
  h_A_n_bs->Draw();
  h_A_p_bs->Draw("same+hist");

  c2->cd(5);
  h_B_p_bs->Draw();
  h_B_n_bs->Draw("same+hist");

  std::cout << ">> Entries is BS asy " << h_asy_A_bs->GetEntries() << std::endl;

  std::cout << ">>>  Results  <<<" << std::endl;
  std::cout << ">> Number of unequl runs " << run_bad << std::endl;
  std::cout << ">> Clary rates " << bcl_bad << std::endl;
  std::cout << ">> Biselli rates " << ang_bad << std::endl;
  std::cout << ">> Difference Bis - Cla = " << ang_bad - bcl_bad << std::endl; 

}



void CompareClaryBiselli(const char* tempclary, const char* tempbiselli ){

  std::cout << ">> Starting comparison between Clary and Biselli final output files " << std::endl;
  CompareBiselli(tempbiselli);

}
