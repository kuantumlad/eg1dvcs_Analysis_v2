#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"
#include "TStyle.h"

#include <vector>
#include <iostream>
#include <cmath>

TFile *fOut;

Int_t RunNumber;
TString *TargetType;
Int_t helicity;
Float_t TarPol;
Double_t b_energy;
Float_t Q2;
Float_t W;
Float_t Xbj;
Float_t Phi;
Float_t t_Ph;
Float_t fel_E;
const char* tarhel[] = {"PP","PN","NP","NN"};
  

void SetBrAddress(TTree *temptree){

  temptree->SetBranchAddress("RunNumber",&RunNumber);
  temptree->SetBranchAddress("TargetType",&TargetType);
  temptree->SetBranchAddress("helicity",&helicity);
  temptree->SetBranchAddress("TarPol",&TarPol);
  temptree->SetBranchAddress("b_energy",&b_energy);
  temptree->SetBranchAddress("Q2",&Q2);
  temptree->SetBranchAddress("W",&W);
  temptree->SetBranchAddress("Xbj",&Xbj);
  temptree->SetBranchAddress("Phi",&Phi);
  temptree->SetBranchAddress("t_Ph",&t_Ph);
  temptree->SetBranchAddress("fel_E",&fel_E);

}


//Finds the appropriate Q2-xb & -t bin values
std::vector<int> FindBin( double beam, double tempq, double tempfel_E, double tempx, double tempt ){
 
  int xqbin;
  int tbin;
  std::vector<int> tempbin;
  tempbin.clear();

  //Theta is in degrees
  double theta = (acos(1 - tempq/(2*tempfel_E*beam)))*(180.0/TMath::Pi());
 
  if( (0.1 < tempx && tempx < 0.2) &&  (15 < theta && theta < 48 )){
    xqbin = 0;
  }
  if( (0.2 < tempx && tempx < 0.3) &&  (15 < theta && theta < 34 )){
    xqbin = 1;
  }
  if( (0.2 < tempx && tempx < 0.3) &&  (34 < theta && theta < 48 )){
    xqbin = 2;
  }
  if( (0.3 < tempx && tempx < 0.4) &&  (15 < theta && theta < 45 )){
    xqbin = 3;
  }
  if( (0.4 < tempx ) &&  (15 < theta && theta < 45 )){
    xqbin = 4;
  }

  if( 0.08 < -tempt && -tempt < 0.18 ){
    tbin = 0;
  }
  if( 0.18 < -tempt && -tempt < 0.3 ){
    tbin = 1;
  }
  if( 0.3 < -tempt && -tempt < 0.7 ){
    tbin = 2;
  }
  if( 0.7 < -tempt && -tempt < 2.0 ){
    tbin = 3;
  }
  
  tempbin.push_back(xqbin);
  tempbin.push_back(tbin);
  
  return tempbin;
}

void Draw(  const char* th, TH1D* histtemp[5][4] ){
  std::cout << " Drawing " << th << "configuration to canvas " << std::endl;
  
  for( int i = 0; i < 5; i++ ){
    TCanvas *c1 = new TCanvas(Form("c1_%s_xq%d",th,i),Form("c1_%s_xq%d",th,i),800,800);
    c1->Divide(2,2);    
    for( int j = 0; j < 4; j++ ){
      c1->cd(j+1);
      histtemp[i][j]->Draw();
    } 
  }
}

  
void AsymBin( const char* rootfile ){

  TFile *fIn = new TFile(rootfile);

  std::cout<< "Beginning Binning Routine" << std::endl;
  TTree *tDVCS = (TTree*)fIn->Get("tDVCS");

  SetBrAddress(tDVCS);
  
  int nentries = tDVCS->GetEntries();
  std::cout << ">> Number of Entries to process is "<< nentries << std::endl;

  int th_bin = 4;
  int xq_bin = 5;
  int t_bin = 4;

  //Phi distribution for different Q2-x && -t bins
  // for a target polarization and helicity pair
  TH1D* h_bin_PP[5][4];  
  TH1D* h_bin_PN[5][4]; 
  TH1D* h_bin_NP[5][4]; 
  TH1D* h_bin_NN[5][4];

  TH1D* h_asy_PP = new TH1D("h_asy_PP","",10,0,360);
  TH1D* h_asy_PN = new TH1D("h_asy_PN","",10,0,360);
  TH1D* h_asy_NP = new TH1D("h_asy_NP","",10,0,360);
  TH1D* h_asy_NN = new TH1D("h_asy_NN","",10,0,360);
  //Target Types used for Asymmetry
  TString nh3t("NH3T"); 
  TString nh3b("NH3B"); 
  TString nh3s("NH3S"); 
  
  for( int xq = 0; xq < xq_bin; xq++ ){
      for( int t = 0; t < t_bin; t++ ){
	h_bin_PP[xq][t] = new TH1D( Form("h_PP_xq%d_t%d",xq,t), Form("h_PP_xq%d_t%d",xq,t), 10, 0, 360 );
	h_bin_PN[xq][t] = new TH1D( Form("h_PN_xq%d_t%d",xq,t), Form("h_PN_xq%d_t%d",xq,t), 10, 0, 360 );
	h_bin_NP[xq][t] = new TH1D( Form("h_NP_xq%d_t%d",xq,t), Form("h_NP_xq%d_t%d",xq,t), 10, 0, 360 );
	h_bin_NN[xq][t] = new TH1D( Form("h_NN_xq%d_t%d",xq,t), Form("h_NN_xq%d_t%d",xq,t), 10, 0, 360 );
      }  
    }
  

  TH2D *h_q2x_bin0 = new TH2D("h_q2x_bin0","", 100, 0.1, 0.7, 100, 0.8, 5.5);
  TH2D *h_q2x_bin1 = new TH2D("h_q2x_bin1","", 100, 0.1, 0.7, 100, 0.8, 5.5);
  TH2D *h_q2x_bin2 = new TH2D("h_q2x_bin2","", 100, 0.1, 0.7, 100, 0.8, 5.5);
  TH2D *h_q2x_bin3 = new TH2D("h_q2x_bin3","", 100, 0.1, 0.7, 100, 0.8, 5.5);
  TH2D *h_q2x_bin4 = new TH2D("h_q2x_bin4","", 100, 0.1, 0.7, 100, 0.8, 5.5);
  TH2D *h_q2x_binall = new TH2D("h_q2x_binall","", 100, 0.1, 0.7, 100, 0.8, 5.5);

  TH2D *h_tx_bin1 = new TH2D("h_tx_bin1","", 100, 0.12, 0.6, 100, 0.15, 2 );
  TH2D *h_tx_bin2 = new TH2D("h_tx_bin2","", 100, 0.12, 0.6, 100, 0.15, 2 );
  TH2D *h_tx_bin3 = new TH2D("h_tx_bin3","", 100, 0.12, 0.6, 100, 0.15, 2 );
  TH2D *h_tx_bin4 = new TH2D("h_tx_bin4","", 100, 0.12, 0.6, 100, 0.15, 2 );
  TH2D *h_tx_binall = new TH2D("h_tx_binall","", 100, 0.12, 0.6, 100, 0.15, 2 );

  std::cout << ">> Looping over entries and determining events bin number in Q2-Xbj and -t space." << std::endl;
  for( int i = 0; i<nentries; i++){
    tDVCS->GetEntry(i);
    
    if( *TargetType == nh3t || *TargetType == nh3b ){// *TargetType == nh3s ){
	
	std::vector<int> eventbins = FindBin( b_energy, Q2, fel_E, Xbj, t_Ph );

	if( std::abs(eventbins[0]) > 4 || std::abs(eventbins[1]) > 3 ) continue;
	if( eventbins.size() < 1 ){ std::cout << " ERROR " << 	std::endl;}
	
	if( eventbins[0] == 0 ){
	  h_q2x_bin0->Fill(Xbj,Q2);
	}
	if( eventbins[0] == 1 ){
	  h_q2x_bin1->Fill(Xbj,Q2);
	}
	if( eventbins[0] == 2 ){
	  h_q2x_bin2->Fill(Xbj,Q2);
	}
	if( eventbins[0] == 3 ){
	  h_q2x_bin3->Fill(Xbj,Q2);
	}
	if( eventbins[0] == 4 ){
	  h_q2x_bin4->Fill(Xbj,Q2);
	}
	h_q2x_binall->Fill(Xbj,Q2);

	if( eventbins[1] == 0 ){
	  h_tx_bin1->Fill(Xbj,-t_Ph);
	}
	if( eventbins[1] == 1 ){
	  h_tx_bin2->Fill(Xbj,-t_Ph);
	}
	if( eventbins[1] == 2 ){
	  h_tx_bin3->Fill(Xbj,-t_Ph);
	}
	if( eventbins[1] == 3 ){
	  h_tx_bin4->Fill(Xbj,-t_Ph);
	}
	h_tx_binall->Fill(Xbj,-t_Ph);
	  
	if( TarPol > 0 && helicity == 1 ){
	  h_asy_PP->Fill(Phi*(180.0/TMath::Pi()));
	  h_bin_PP[eventbins[0]][eventbins[1]]->Fill(Phi*(180.0/TMath::Pi()));
	}
	if( TarPol > 0 && helicity == 0 ){
	  h_asy_PN->Fill(Phi*(180.0/TMath::Pi()));
	  h_bin_PN[eventbins[0]][eventbins[1]]->Fill(Phi*(180.0/TMath::Pi()));
	}
	if( TarPol < 0 && helicity == 1 ){
	  h_asy_NP->Fill(Phi*(180.0/TMath::Pi()));
	  h_bin_NP[eventbins[0]][eventbins[1]]->Fill(Phi*(180.0/TMath::Pi()));
	}
	if( TarPol < 0 && helicity == 0 ){
	  h_asy_NN->Fill(Phi*(180.0/TMath::Pi()));
	  h_bin_NN[eventbins[0]][eventbins[1]]->Fill(Phi*(180.0/TMath::Pi()));
	}
      }
    }
    //FC Normalization factors below. Divide each PP,PN, NP, and NN by these values
    //N++, N+-. N-+, and N-- are : 4.31883, 4.32092,  4.52718, 4.52667, respectively.
  //  fOut->cd();
  TCanvas *c2 = new TCanvas("q2x_check","q2x_check",1600,1600);
  c2->Divide(2,3);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);
  c2->cd(1);
  h_q2x_bin0->GetXaxis()->SetTitle("Xbj");
  h_q2x_bin0->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2x_bin0->SetTitle("Q^{2}-x_{b} space: 0.1 < x < 0.2 & 15#circ < #theta_{e} < 48#circ");
  h_q2x_bin0->Draw("colz"); 
  c2->cd(2);
  h_q2x_bin1->GetXaxis()->SetTitle("Xbj");
  h_q2x_bin1->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2x_bin1->SetTitle("Q^{2}-x_{b} space: 0.2<x<0.3 & 15#circ<#theta_{e}<34#circ");
  h_q2x_bin1->Draw("colz");
  c2->cd(3);
  h_q2x_bin2->GetXaxis()->SetTitle("Xbj");
  h_q2x_bin2->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2x_bin2->SetTitle("Q^{2}-x_{b} space: 0.2<x<0.3 & 34#circ<#theta_{e}<48#circ");
  h_q2x_bin2->Draw("colz");
  c2->cd(4);
  h_q2x_bin3->GetXaxis()->SetTitle("Xbj");
  h_q2x_bin3->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2x_bin3->SetTitle("Q^{2}-x_{b} space: 0.3<x<0.4 & 15#circ<#theta_{e}<45#circ");
  h_q2x_bin3->Draw("colz");
  c2->cd(5);
  h_q2x_bin4->GetXaxis()->SetTitle("Xbj");
  h_q2x_bin4->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2x_bin4->SetTitle("Q^{2}-x_{b} space: 0.4<x & 15#circ<#theta_{e}<45#circ");
  h_q2x_bin4->Draw("colz");
  c2->cd(6);
  h_q2x_binall->GetXaxis()->SetTitle("Xbj");
  h_q2x_binall->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  h_q2x_binall->SetTitle("Q^{2}-x_{b} space: All bins");
  h_q2x_binall->Draw("colz");

  TCanvas *c3 = new TCanvas("tx_check","tx_check",1600,1600);
  c3->Divide(2,3);
  c3->cd(1);
  h_tx_bin1->GetXaxis()->SetTitle("Xbj");
  h_tx_bin1->GetYaxis()->SetTitle("-t");
  h_tx_bin1->SetTitle("-t - x_{b} space: 0.08 < -t < 0.18");
  h_tx_bin1->Draw("colz");
  c3->cd(2);
  h_tx_bin2->GetXaxis()->SetTitle("Xbj");
  h_tx_bin2->GetYaxis()->SetTitle("-t");
  h_tx_bin2->SetTitle("-t - x_{b} space: 0.18 < -t < 0.3");
  h_tx_bin2->Draw("colz");
  c3->cd(3);
  h_tx_bin3->GetXaxis()->SetTitle("Xbj");
  h_tx_bin3->GetYaxis()->SetTitle("-t");
  h_tx_bin3->SetTitle("-t - x_{b} space: 0.3 < -t < 0.7");
  h_tx_bin3->Draw("colz");
  c3->cd(4);
  h_tx_bin4->GetXaxis()->SetTitle("Xbj");
  h_tx_bin4->GetYaxis()->SetTitle("-t");
  h_tx_bin4->SetTitle("-t - x_{b} space: 0.7 < -t < 2.0");
  h_tx_bin4->Draw("colz");
  c3->cd(5);
  h_tx_binall->GetXaxis()->SetTitle("Xbj");
  h_tx_binall->GetYaxis()->SetTitle("-t");
  h_tx_binall->SetTitle("-t - x_{b} space: All bins");
  h_tx_binall->Draw("colz");

  double fc_pp = 4.31883;
  double fc_pn = 4.32092;
  double fc_np = 4.52718;
  double fc_nn = 4.52667;
  
  //Asym over all bins
  std::vector<double> asym_y_all, asym_x_all;
  for( int bin = 1; bin <=10; bin++){
    
    double_t pp = h_asy_PP->GetBinContent(bin);
    double_t pn = h_asy_PN->GetBinContent(bin);
    double_t np = h_asy_NP->GetBinContent(bin);
    double_t nn = h_asy_NN->GetBinContent(bin);
    
    std::cout<< ">>>Bin" << bin << " " << pp << " " << pn << " " << np << " " << nn << std::endl;
    
    double pp_fcn = pp/fc_pp;
    double pn_fcn = pn/fc_pn;
    double np_fcn = np/fc_np;
    double nn_fcn = nn/fc_nn;
    
    //First calculate the numerator of the asym expression
    double numerator = pp_fcn + pn_fcn - np_fcn - nn_fcn;
    
    //Then calulcate the denominator taking into account the dillution factor and average target polarization.
    //The dilution factor and avg tarPol as of 5/20/2017 are taken from the PRL paper
    double dilute_b = 0.928;
    double tarP = 0.81;
    double tarN = 0.75;
    double denominator = dilute_b*(tarN*(pp_fcn + pn_fcn) + tarP*(np_fcn + nn_fcn) );
    
    //The asymmetry for each bin (asym_y) of phi (asym_x) is thus
    asym_y_all.push_back(numerator/denominator);
    asym_x_all.push_back( h_asy_PP->GetBinCenter(bin) );
    
  }
  TH1D *h_asy_PPPN = new TH1D("h_asy_PPPN","",10,0,360);
  TH1D *h_asy_NPNN = new TH1D("h_asy_NPNN","",10,0,360);
  TH1D *h_asy_top = new TH1D("h_asy_top","",10,0,360);
  TH1D *h_asy_bot = new TH1D("h_asy_bot","",10,0,360);
  TH1D *h_asym_all = new TH1D("h_asym_all","",10,0,360);
  
  TCanvas *c4 = new TCanvas("c4_asym_all","c4_asym_all", 1600, 800);
  c4->Divide(1,2);
  c4->cd(1);
  TGraph *gtemp2 = new TGraph(asym_x_all.size(),&(asym_x_all[0]),&(asym_y_all[0]));
  gtemp2->SetName("tg_asym_all");
  gtemp2->SetTitle("tg_asym_all");
  gtemp2->GetXaxis()->SetTitle("#phi [Deg]");
  gtemp2->SetMarkerStyle(20);
  gtemp2->SetMarkerSize(0.7);
  gtemp2->SetMarkerColor(kBlue+2);
  gtemp2->SetLineColor(kBlue+2);
  gtemp2->Draw("AP");
  c4->cd(2);
  h_asy_PPPN->Add(h_asy_PP,h_asy_PN,1.0/fc_pp,1.0/fc_pn);
  h_asy_PPPN->Draw();
  h_asy_NPNN->Add(h_asy_NP,h_asy_NN,1.0/fc_np,1.0/fc_nn);
  h_asy_top->Add(h_asy_PPPN,h_asy_NPNN,1.0,-1.0);
  h_asy_bot->Add(h_asy_PPPN,h_asy_NPNN,0.75*0.928,0.81*0.928);
  h_asym_all->Divide(h_asy_top,h_asy_bot,1.0,1.0);
  h_asym_all->SetMarkerSize(0.6);
  h_asym_all->Draw("P0");
  
  std::vector<double> asym_y, asym_x;
  fOut = new TFile("asym.root","RECREATE");
  
  for( int i = 0; i < 5; i++ ){
    TCanvas *c1 = new TCanvas(Form("c1_xq%d",i),Form("c1_xq%d",i),800,800);
    c1->Divide(2,2);    
    
    for( int j = 0; j < 4; j++ ){
      //Loop over bin contents of each histogram
      for( int b = 1; b <= 10; b++ ){
	int pp = h_bin_PP[i][j]->GetBinContent(b);
	int pn = h_bin_PN[i][j]->GetBinContent(b);
	int np = h_bin_NP[i][j]->GetBinContent(b);
	int nn = h_bin_NN[i][j]->GetBinContent(b);
	
	//std::cout << " >> " << i << " " << j << " " << pp << " " << pn << " " << np << " " << nn << std::endl;
	double pp_fcn = pp/fc_pp;
	double pn_fcn = pn/fc_pn;
	double np_fcn = np/fc_np;
	double nn_fcn = nn/fc_nn;
	
	//First calculate the numerator of the asym expression
	double numerator = pp_fcn + pn_fcn - np_fcn - nn_fcn;
	
	//Then calulcate the denominator taking into account the dillution factor and average target polarization.
	//The dilution factor and avg tarPol as of 5/20/2017 are taken from the PRL paper
	double dilute_b = 0.928;
	double tarP = 0.81;
	double tarN = 0.75;
	double denominator = dilute_b*(tarN*(pp_fcn + pn_fcn) + tarP*(np_fcn + nn_fcn) );
	
	//The asymmetry for each bin (asym_y) of phi (asym_x) is thus
	asym_y.push_back(numerator/denominator);
	asym_x.push_back( h_bin_PP[i][j]->GetBinCenter(b) );
      }
      //End bin loop
      //Now create a TGraph for each Q2-x and -t bin
      std::cout << " Creating TGraph " << std::endl;
      c1->cd(j+1);
      TGraph *gtemp = new TGraph(asym_x.size(),&(asym_x[0]),&(asym_y[0]));
      gtemp->SetName(Form("h_asym_q2x%d_t%d",i,j));
      gtemp->SetTitle(Form("h_asym_q2x%d_t%d",i,j));
      gtemp->GetXaxis()->SetTitle("#phi [Deg]");
      gtemp->SetMarkerStyle(20);
      gtemp->SetMarkerSize(0.7);
      gtemp->SetMarkerColor(kBlue+2);
      gtemp->SetLineColor(kBlue+2);
      gtemp->Draw("AP");
      asym_x.clear();
      asym_y.clear();
      
      fOut->cd();
      gtemp->Write("AP");
    }     
  }
  
  std::cout << ">> Saving and Closing output file."<< std::endl;
  fOut->Save();
  fOut->Close();
  std::cout << ">> Complete " << std::endl;
    /* std::vector<double> x,y;
    gtemp->SetName("same");
    gtemp->SetTitle("same");
    //    gtemp->SetMarker,...
    //  gtemp->GetXaxis()->
    //  gtemp->Draw("AP");


    //rootfile->cd();
    


    //Draw Histograms
    Draw( "PP", h_bin_PP );
    Draw( "PN", h_bin_PN );
    Draw( "NP", h_bin_NP );
    Draw( "NN", h_bin_NN );
    
    */
}


