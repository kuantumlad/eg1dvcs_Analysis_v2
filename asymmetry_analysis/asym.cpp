#include "TMath.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "tDVCS.C"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>

std::map<Double_t, bool> goodruns;

void GoodRunSet(){

  const char* path = "/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/fcup_analysis/FinalGoodRunsGroupAB.txt";
  std::ifstream myfile;
  myfile.open(path,std::ios_base::in);

  std::string line;

  if( myfile.is_open() ){

    while ( getline(myfile,line) ){
      if( line[0] == '#' ) continue;
      
      double run, fc0, fc1;
      std::stringstream first(line);
      first >> run >> fc0 >> fc1;
      goodruns[run] = true;
      
    }

  }

}


void asym( const char* rootfile ){

  TChain *fchain = new TChain("tDVCS");
  fchain->Add(rootfile);

  tDVCS *treevar = new tDVCS(fchain);

  TH1D* h_PP = new TH1D("h_PP","",10,0,360);
  TH1D* h_PN = new TH1D("h_PN","",10,0,360);
  TH1D* h_NP = new TH1D("h_NP","",10,0,360);
  TH1D* h_NN = new TH1D("h_NN","",10,0,360);

  TH1D* h_P = new TH1D("h_P","",10,0.0,360.0);
  TH1D* h_N = new TH1D("h_N","",10,0.0,360.0);

  TH1D *h_tarpol_pos = new TH1D("h_tarpol_pos","",100,50,90);
  TH1D *h_tarpol_neg = new TH1D("h_tarpol_neg","",100,-150,-50);

  GoodRunSet();

  // double tp_P = 0.0;
  //double tp_N = 0.0;
  //double count_P = 0.0;
  /// double count_N = 0.0;
  std::map<double,double> m_eventrate, m_tarpol;

  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++ ){
    fchain->GetEntry(nn);
    
    //Work with only run group B and NH3 targets for now. Can be changed later
    std::string target = (std::string)(*treevar->TargetType);
    if( *treevar->PeriodID == 'B'
	&& (target == "NH3T" || target == "NH3B" || target == "NH3S") 
	&& goodruns[treevar->RunNumber] ){
      Int_t hel = treevar->helicity;
      Float_t tarpol = treevar->TarPol;

      m_eventrate[treevar->RunNumber] += 1;
      m_tarpol[treevar->RunNumber] = tarpol;

      if( tarpol > 0 ){ h_P->Fill((treevar->Phi)*(180.0/TMath::Pi()) ); }
      else if( tarpol < 0 ) {h_N->Fill((treevar->Phi)*(180.0/TMath::Pi()) );}

      if( tarpol > 0 && hel == 0 ){
	h_PP->Fill( (treevar->Phi)*(180.0/TMath::Pi()) );
      }
      if( tarpol > 0 && hel == 1 ){
	h_PN->Fill( (treevar->Phi)*(180.0/TMath::Pi()) );
      }
      if( tarpol < 0 && hel == 0 ){
	h_NP->Fill( (treevar->Phi)*(180.0/TMath::Pi()) );
      }
      if( tarpol < 0 && hel == 1 ){
	h_NN->Fill( (treevar->Phi)*(180.0/TMath::Pi()) );
      }
    }
  }

  // Commented out and not included in the asym bc at this stage the analysis
  // is responsible for getting the correct normalization values.
  /*  Double_t  weighted_pol_P = 0.0;
  Double_t  weighted_pol_N = 0.0;
  Double_t running_sum_P = 0.0;
  Double_t running_sum_N = 0.0;
  std::map<double,double>::iterator it = m_eventrate.begin();
  while ( it != m_eventrate.end() ){
    Double_t run = it->first;
    Double_t tp = m_tarpol[run];
    if( tp > 0 ){
      Double_t weight_P = it->second;
      weighted_pol_P+=(tp*weight_P);
      running_sum_P+=it->second;
    }
    if( tp < 0 ){
      Double_t weight_N = it->second;
      weighted_pol_N+=(tp*weight_N);
      running_sum_N+=it->second;
    }
    ++it;
  }

  std::cout << weighted_pol_P << " - " << running_sum_P << " ==> " << weighted_pol_P/running_sum_P << std::endl;
  std::cout << weighted_pol_N << " - " << running_sum_N <<  " ==> " << weighted_pol_N/running_sum_N << std::endl;
  */
  Double_t tp_P =1.0;//  (1.0/100.0)*(weighted_pol_P/running_sum_P);
  Double_t tp_N =1.0;//  (-1.0/100.0)*(weighted_pol_N/running_sum_N);

  TH1D *h_PPPN = new TH1D("h_PPPN","",10,0,360);
  TH1D *h_NPNN = new TH1D("h_NPNN","",10,0,360);
  TH1D *h_top = new TH1D("h_top","",10,0,360);
  TH1D *h_bot = new TH1D("h_bot","",10,0,360);
  TH1D *h_asym = new TH1D("h_asym","",10,0,360);
  
  Double_t dfB = 0.978053;//0.928;

  TCanvas *c1 = new TCanvas("c1","canvas",1600,800);
  gStyle->SetOptStat(0);
  //  c1->Divide(2,2);
  //c1->cd(1);
  h_PPPN->Add(h_PP,h_PN,1.0,1.0);//1.0/2.69372,1.0/2.69169);
  // h_PPPN->Draw();
  //c1->cd(2);
  h_NPNN->Add(h_NP,h_NN,1.0,1.0);//1.0/2.6908,1.0/2.68963);
  //h_NPNN->Draw();  
  //c1->cd(3);

  //Changed this to h_P and h_N as I removed the beam helicity status requirement for target-spin asy.
  h_top->Add(h_P,h_N,1.0,-1.0);
  h_bot->Add(h_P,h_N,dfB*1.0*tp_N,dfB*1.0*tp_P);
  h_asym->Divide(h_top,h_bot,1.0,1.0);
  //  h_asym->Draw("P");

  double fc_pp = 2.69372;
  double fc_pn = 2.69169;
  double fc_np = 2.6908;
  double fc_nn = 2.68963;

  double fc_p = 5.58682;
  double fc_n = 5.83815;

  std::vector<double> asym_y_all, asym_x_all;
  std::vector<double> asym_y_clean;
  for( int bin = 1; bin <=10; bin++){
    
    double_t p = h_P->GetBinContent(bin);
    double_t n = h_N->GetBinContent(bin);
    //    double_t np = h_NP->GetBinContent(bin);
    //double_t nn = h_NN->GetBinContent(bin);
    
    //    std::cout<< ">>>Bin" << bin << " " << pp << " " << pn << " " << np << " " << nn << std::endl;
    
    double p_fcn = p/fc_p;
    double n_fcn = n/fc_n;
    //    double np_fcn = np/fc_np;
    //double nn_fcn = nn/fc_nn;
    
    //First calculate the numerator of the asym expression
    double numerator = p_fcn - n_fcn;// - np_fcn - nn_fcn;

    double numerator2 = p - n;// - np -nn;
    double denominator2 = p + n;// + np + nn;

    //Then calulcate the denominator taking into account the dillution factor and average target polarization.
    //The dilution factor and avg tarPol as of 5/20/2017 are taken from the PRL paper
    double dilute_b = 0.773418;
    double tarP = 1.0;//0.81;
    double tarN = 1.0;//0.75;
    double denominator = dilute_b*(tarN*(p_fcn) + tarP*(n_fcn) );
    
    //The asymmetry for each bin (asym_y) of phi (asym_x) is thus
    asym_y_all.push_back(numerator/denominator);
    asym_y_clean.push_back(numerator2/denominator2);
    asym_x_all.push_back( h_P->GetBinCenter(bin) );
    
  }

  TCanvas *c2 = new TCanvas("c2","can2",1600,800);
  TGraph *gtemp = new TGraph(asym_x_all.size(), &(asym_x_all[0]), &(asym_y_all[0]) );
  gtemp->SetName("Raw Target-Spin Asymmetry Normalized");
  gtemp->SetTitle("Raw Target-Spin Asymmetry Normalized");
  gtemp->GetXaxis()->SetTitle("#phi [Deg]");
  gtemp->SetMarkerStyle(20);
  gtemp->SetMarkerSize(0.85);
  gtemp->SetMarkerColor(kBlue+2);
  gtemp->SetLineColor(kBlue+2);
  //  gtemp->Draw("AP");
  TGraph *gtemp2 = new TGraph(asym_x_all.size(), &(asym_x_all[0]), &(asym_y_clean[0]));
  gtemp2->SetName("Raw Target-Spin Asymmetry Unnormalized");
  gtemp2->SetTitle("Raw Target-Spin Asymmetry Unnormalized");
  gtemp2->SetMarkerStyle(20);
  gtemp2->SetMarkerSize(0.7);
  gtemp2->SetMarkerColor(kRed);

  TLegend *leg1 = new TLegend( 0.70, 0.725, 0.86, 0.875 );
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.025);
  leg1->AddEntry(gtemp,"Normalized Asym","P");
  leg1->AddEntry(gtemp2,"Unnormalized Asym","P");

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gtemp,"P");
  mg->Add(gtemp2,"P");
  mg->Draw("AP");
  mg->SetTitle("Raw Target-Spin Asymmetry Group B");
  mg->GetXaxis()->SetTitle("#phi [Deg]");
  mg->GetYaxis()->SetTitle("Asym_{meas}");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();
  leg1->Draw("same");



  c2->SaveAs("raw_ts_asym_unnorm.pdf");      
  std::cout << " Done " << std::endl;  
}

/*>>FC Normalization factors to scale the DVCS event rates in the target-spin asymmetry
>> PP: 2.69372e+10
>> PN: 2.69169e+10
>> NP: 2.6908e+10
>> NN: 2.68963e+10
*/
