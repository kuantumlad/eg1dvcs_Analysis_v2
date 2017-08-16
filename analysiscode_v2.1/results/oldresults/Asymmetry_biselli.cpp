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

#include <stdlib.h>
#include <iostream>
#include <string>
TFile *fOut;


void FaradayCupNormalizer(const char* directory){

  std::cout << "Getting Faraday Cup counts for normalization purposes." << std::endl;

  Double_t fc_final_PP_a = 0;
  Double_t fc_final_PN_a = 0;
  Double_t fc_final_NP_a = 0;
  Double_t fc_final_NN_a = 0;

  Double_t fc_final_PP_b = 0;
  Double_t fc_final_PN_b = 0;
  Double_t fc_final_NP_b = 0;
  Double_t fc_final_NN_b = 0;

  TSystemDirectory dir(directory,directory);
  TList *files_list = dir.GetListOfFiles();
  TSystemFile *file;

  if( files_list ){
    TIter next(files_list);
    while( (file=(TSystemFile*)next()) ){
      TString filename(file->GetName());
      std::string filetocount = (std::string)directory + (std::string)filename;
      if( !file->IsDirectory() && filename.EndsWith(".root") ){
	TFile *ogfile = new TFile((TString)filetocount);
	//NOTE: IsZombie AND NULL CHECK DID NOT WORK TO DISCARD BAD FILES(?)
	if( ogfile->GetSize() < 500 ) {std::cout << filename << std::endl;continue;}

	TTree* root_tree = (TTree*)ogfile->Get("FCValues");

	Double_t nh3fcplusplus;
	Double_t nh3fcplusminus;
	Double_t nh3fcminusplus;
	Double_t nh3fcminusminus;
	
	root_tree->SetBranchAddress("nh3fcplusplus",&nh3fcplusplus);
	root_tree->SetBranchAddress("nh3fcplusminus",&nh3fcplusminus);
	root_tree->SetBranchAddress("nh3fcminusplus",&nh3fcminusplus);
	root_tree->SetBranchAddress("nh3fcminusminus",&nh3fcminusminus);

	TRegexp regexp_run("[0-9][0-9][0-9][0-9][0-9]");
	TString s_run = filename(regexp_run);
	int run =  std::stoi((std::string)s_run);
	
       	Int_t nentries = root_tree->GetEntries();
	for( int i = 0; i < nentries; i++ ){
	  root_tree->GetEntry(i);
	  // Angela's notation: plus minus = positive helicity with negative target
	  // My notation is inverted P N = positive target with negative helicity	  
	  //GROUP A
	  if( run >= 58708 && run <= 59220 ){
	    fc_final_PP_a = fc_final_PP_a + nh3fcplusplus;
	    fc_final_PN_a = fc_final_PN_a + nh3fcminusplus;
	    fc_final_NP_a = fc_final_NP_a + nh3fcplusminus;
	    fc_final_NN_a = fc_final_NN_a + nh3fcminusminus;	    
	  }
	  //GROUP B
	  if( run >= 59221 && run <= 60184  ){
	    fc_final_PP_b = fc_final_PP_b + nh3fcplusplus;
	    fc_final_PN_b = fc_final_PN_b + nh3fcminusplus;
	    fc_final_NP_b = fc_final_NP_b + nh3fcplusminus;
	    fc_final_NN_b = fc_final_NN_b + nh3fcminusminus;
	  }	  
	  //if( run >= 60221 ){ }

	}
	ogfile->Close();
      }     
    }
  }
  
    std::cout << " Group A " << std::endl;    
    std::cout << " FC PP = " << fc_final_PP_a << std::endl;
    std::cout << " FC PN = " << fc_final_PN_a << std::endl;
    std::cout << " FC NP = " << fc_final_NP_a << std::endl;
    std::cout << " FC NN = " << fc_final_NN_a << std::endl;

    std::cout << " Group B " << std::endl;
    std::cout << " FC PP = " << fc_final_PP_b << std::endl;
    std::cout << " FC PN = " << fc_final_PN_b << std::endl;
    std::cout << " FC NP = " << fc_final_NP_b << std::endl;
    std::cout << " FC NN = " << fc_final_NN_b << std::endl;
	
}


void Asymmetry_biselli( const char* tempdirectory, const char* rootfile ){

  TFile *fIn = new TFile(rootfile);


  std::cout << ">> File name " << (TString)fIn->GetName() << std::endl;
  if( !fIn ){
    std::cout << " Could not open file " << std::endl;
  }

  //if( (TString)fIn->GetName() == "dvcsBiselliAll.root" ){
  //FaradayCupNormalizer(tempdirectory);// fIn);
    //}

  //  if( (TString)fIn->GetName() == "/lustre/expphy/work/halla/sbs/bclary/analysis/eg1dvcs_biselli_output/h_eg1_AllBiselli.root" ){
    TH1D *PP_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_PP");
    TH1D *PN_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_PN");
    TH1D *NP_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_NP");
    TH1D *NN_a = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Aepgyield_NN");

    TH1D *PP_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_PP");
    TH1D *PN_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_PN");
    TH1D *NP_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_NP");
    TH1D *NN_b = (TH1D*)fIn->Get("mon histograms/bclary_cuts/apid_Bepgyield_NN");

    Double_t ppa = PP_a->GetEntries();
    Double_t pna = PN_a->GetEntries();
    Double_t npa = NP_a->GetEntries();
    Double_t nna = NN_a->GetEntries();

    Double_t ppb = PP_b->GetEntries();
    Double_t pnb = PN_b->GetEntries();
    Double_t npb = NP_b->GetEntries();
    Double_t nnb = NN_b->GetEntries();

    Double_t finaltot = ppa + pna + npa + nna + ppb + pnb + npb + nnb;

    std::cout << " Group A " << std::endl;
    std::cout << ">> PP " << ppa << std::endl;
    std::cout << ">> PN " << pna << std::endl;
    std::cout << ">> NP " << npa << std::endl;
    std::cout << ">> NN " << nna << std::endl;
    std::cout << ">> total " << ppa + pna + npa + nna << std::endl;

    std::cout << " Group B " << std::endl;
    std::cout << ">> PP " << ppb << std::endl;
    std::cout << ">> PN " << pnb << std::endl;
    std::cout << ">> NP " << npb << std::endl;
    std::cout << ">> NN " << nnb << std::endl;
    std::cout << ">> total " << ppb + pnb + npb + nnb << std::endl;

    std::cout << ">> FINAL TOTAL DVCS RATE " << finaltot << std::endl;

    TH1D *PPPN_a = new TH1D("PPPN_a","",10,0,360);
    TH1D *NPNN_a = new TH1D("NPNN_a","",10,0,360);
    
    TH1D *PPPN_b = new TH1D("PPPN_b","",10,0,360);
    TH1D *NPNN_b = new TH1D("NPNN_b","",10,0,360);

    TH1D *PPPN_ab = new TH1D("PPPN_ab","",10,0,360);
    TH1D *NPNN_ab = new TH1D("NPNN_ab","",10,0,360);

    TH1D *numerator_a = new TH1D("numerator_a","",10,0,360);
    TH1D *denominator_a = new TH1D("denominator_a","",10,0,360);

    TH1D *asym_a = new TH1D("asym_a","",10,0,360);

    TH1D *numerator_b = new TH1D("numerator_b","",10,0,360);
    TH1D *denominator_b = new TH1D("denominator_b","",10,0,360);

    TH1D *asym_b = new TH1D("asym_b","",10,0,360);

    //Double_t dilute_a = 0.883;
    Double_t dilute_a = 0.912;
    Double_t tarpol_p_a = 0.75;  
    Double_t tarpol_n_a = 0.72;  
    Double_t fc_pp_a = 1.65813;//(4.31883);//1.0/2.69372;//1.0;//;
    Double_t fc_pn_a = 1.65679;//(4.32092);//1.0/2.69169; //
    Double_t fc_np_a = 1.7595;//(4.52718);//1.0/2.6908;//
    Double_t fc_nn_a = 1.79078;//(4.52667);//1.0/2.68963;//  

    Double_t dilute_b = 0.928;
    Double_t tarpol_p_b = 0.81;  
    Double_t tarpol_n_b = 0.75;  
    Double_t fc_pp_b = 2.6607; //(4.31883);//1.0/2.69372;//1.0;//;
    Double_t fc_pn_b = 2.66413; //(4.32092);//1.0/2.69169; //
    Double_t fc_np_b = 2.76767; //(4.52718);//1.0/2.6908;//
    Double_t fc_nn_b = 2.76589; //(4.52667);//1.0/2.68963;//  

    Double_t fc_p_a = fc_pp_a + fc_pn_a;
    Double_t fc_n_a = fc_np_a + fc_nn_a;

    Double_t fc_p_b = fc_pp_b + fc_pn_b;
    Double_t fc_n_b = fc_np_b + fc_nn_b;

    PPPN_a->Add(PP_a,PN_a,1.0,1.0);
    NPNN_a->Add(NP_a,NN_a,1.0,1.0);

    PPPN_b->Add(PP_b,PN_b,1.0, 1.0);
    NPNN_b->Add(NP_b,NN_b,1.0, 1.0);

    //PPPN_ab->Add(PPPN_a,PPPN_b,1.0,1.0);
    //NPNN_ab->Add(NPNN_a,NPNN_b,1.0,1.0);

    //GROUP A
    numerator_a->Add(PPPN_a,NPNN_a, 1.0/fc_p_a, -1.0/fc_n_a);
    denominator_a->Add(PPPN_a,NPNN_a, tarpol_n_a * dilute_a * 1.0/fc_p_a, tarpol_p_a * dilute_a * 1.0/fc_n_a);

    asym_a->Divide(numerator_a,denominator_a);

    //GROUP B
    numerator_b->Add(PPPN_b,NPNN_b, 1.0/fc_p_b, -1.0/fc_n_b);
    denominator_b->Add(PPPN_b,NPNN_b, tarpol_n_b * dilute_b * 1.0/fc_p_b, tarpol_p_b * dilute_b * 1.0/fc_n_b);

    asym_b->Divide(numerator_b,denominator_b);

    TCanvas *c1 = new TCanvas("c1","",1600,800);
    c1->Divide(3,2);
    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.14);

    //GROUP A
    c1->cd(1);
    numerator_a->SetTitle("Asy_{target}: PPPN - NPNN Group A");
    numerator_a->GetXaxis()->SetTitle("#phi"); 
    numerator_a->GetXaxis()->CenterTitle();
    numerator_a->SetMarkerStyle(8);
    numerator_a->SetMarkerSize(0.8);
    numerator_a->Draw("p");

    c1->cd(2);
    denominator_a->SetTitle("Asy_{target}: PPPN + NPNN Group A");
    denominator_a->GetXaxis()->SetTitle("#phi"); 
    denominator_a->GetXaxis()->CenterTitle();
    denominator_a->SetMarkerStyle(8);
    denominator_a->SetMarkerSize(0.8);
    denominator_a->Draw("p");

    c1->cd(3);
    asym_a->SetTitle("Raw Asy_{target} Group A");
    asym_a->GetXaxis()->SetTitle("#phi"); 
    asym_a->GetXaxis()->CenterTitle();
    asym_a->GetYaxis()->SetTitle("Asym_{tar}"); 
    asym_a->GetYaxis()->CenterTitle();
    asym_a->SetMarkerStyle(8);
    asym_a->SetMarkerSize(0.8);
    asym_a->Draw("p");  

    //GROUP B
    c1->cd(4);
    numerator_b->SetTitle("Asy_{target}: PPPN - NPNN Group B");
    numerator_b->GetXaxis()->SetTitle("#phi"); 
    numerator_b->GetXaxis()->CenterTitle();
    numerator_b->SetMarkerStyle(8);
    numerator_b->SetMarkerSize(0.8);
    numerator_b->Draw("p");

    c1->cd(5);
    denominator_b->SetTitle("Asy_{target}: PPPN + NPNN Group B");
    denominator_b->GetXaxis()->SetTitle("#phi"); 
    denominator_b->GetXaxis()->CenterTitle();
    denominator_b->SetMarkerStyle(8);
    denominator_b->SetMarkerSize(0.8);
    denominator_b->Draw("p");

    c1->cd(6);
    asym_b->SetTitle("Raw Asy_{target} Group B");
    asym_b->GetXaxis()->SetTitle("#phi"); 
    asym_b->GetXaxis()->CenterTitle();
    asym_b->GetYaxis()->SetTitle("Asym_{tar}"); 
    asym_b->GetYaxis()->CenterTitle();
    asym_b->SetMarkerStyle(8);
    asym_b->SetMarkerSize(0.8);
    asym_b->Draw("p");
  
    c1->SaveAs("asymBiselli_ab.pdf");
    //}
}

