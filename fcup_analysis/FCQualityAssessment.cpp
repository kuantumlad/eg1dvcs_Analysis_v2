//////////////////////////////////////////////////////////
//
//
//   Macro written by Brandon Clary
//   5-26-2017
//   Purpose: In order to make sure the DVCS events found 
//            from the analysis are suited for use in the 
//            target-spin, beam-spin, and double-spin asym
//            calculations we must verify the quality of a
//            run. The 'quality' of a run in meaured by the
//            taking the ratio of DVCS events from a run to 
//            the sum of positive and negative helicity 
//            electrons deposited in the FC. This macro chains
//            together all the DVCS files, and counts the number
//            of DVCS per run along with the total FC per run by
//            using the values provided by the text document.
//            The mean and stdev of the maximum is computed then 
//            those values are used to seperate good and bad 
//            quality runs. Finally a TGraph is saved to illustrate
//            the seperation.
//
// ***** FILE IS OBSOLETE!!!! DO NOT USE!!!!!*****
//
/////////////////////////////////////////////////////////
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TChain.h"
#include "TColor.h"
#include "TFunction.h"
#include "TF1.h"
#include "TLegend.h"
#include "TLine.h"
#include "TArrow.h"
#include "TLatex.h"

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iterator>
#include <algorithm>
#include "tDVCS.C"

void FittingMethod( TH1D *h_temp ){

  ///////////////////////////////////////////////////////
  //fitting method 
  TCanvas *c_temp = new TCanvas(Form("%s",h_temp->GetName()),Form("%s",h_temp->GetName()),800,800);

  Double_t xlow, xhigh, histmax;
  Int_t binlow, binhigh, binmax;

  binmax= h_temp->GetMaximumBin();
  histmax = h_temp->GetMaximum();
  binlow = binmax;
  binhigh = binmax;

  Double_t percentofmax = 0.65;

  while( h_temp->GetBinContent(binhigh++) >= percentofmax*histmax && binhigh <= h_temp->GetNbinsX() ){};
  while( h_temp->GetBinContent(binlow--) >= percentofmax*histmax && binlow>=1 ) {};

  xlow=h_temp->GetBinLowEdge(binlow);
  xhigh=h_temp->GetBinLowEdge(binhigh+1);

  h_temp->Fit("gaus","","",xlow,xhigh);

  TF1 *ftemp = (TF1*)h_temp->GetListOfFunctions()->FindObject("gaus");

  Double_t ftemp_mean = ftemp->GetParameter(1);
  Double_t ftemp_stdev = ftemp->GetParameter(2);

  c_temp->cd(1);
  h_temp->Draw();
  //  c_temp->SaveAs(Form("%s",h_temp->GetName()));

  //end fitting method
  ///////////////////////////////////////////////////////
}



void FCQualityAssessment( const char* rootfile ){

  //Bring in DVCS tree and chain files together
  TChain *fchain = new TChain("tDVCS");
  fchain->Add(rootfile);

  tDVCS *treevar = new tDVCS(fchain);

  std::map<Double_t,Int_t> dvcs_per_run_nh3;
  std::map<Double_t,Int_t> dvcs_per_run_c12;
  std::map<Double_t,Int_t> dvcs_per_run_all;

  //Insert runs from period A and B into map with nDVCS
  for( Long64_t nn = 0; nn < fchain->GetEntries(); nn++){
    fchain->GetEntry(nn);
    std::string target = (std::string)(*treevar->TargetType);
    if( (*treevar->PeriodID == 'A' || *treevar->PeriodID == 'B') && ( target == "NH3T" || target == "NH3B" || target == "NH3S" ) ){
    dvcs_per_run_nh3[treevar->RunNumber]+=1;
    }
    if( (*treevar->PeriodID == 'A' || *treevar->PeriodID == 'B') && target == "C12" ){
    dvcs_per_run_c12[treevar->RunNumber]+=1;
    }
    if(  (*treevar->PeriodID == 'A' || *treevar->PeriodID == 'B') ){
      dvcs_per_run_all[treevar->RunNumber]+=1;
    }
  }

  std::cout << " dvcs_per_run_nh3 size " << dvcs_per_run_nh3.size() << std::endl;
  std::cout << " dvcs_per_run_c12 size " << dvcs_per_run_c12.size() << std::endl;


  //Get the fc0 and fc1 value for each run from the following txt file
  // Here we will have three maps, one for fc0, fc1, and fc0+fc1
  std::map<Int_t, Double_t> fc0_per_run, fc1_per_run, fcsum_per_run;

  const char *path = "Clary_GoodFCValues.txt";
  std::ifstream myfile;
  myfile.open(path, std::ios_base::in);
  
  std::string line;
  if( myfile.is_open() ){
    
    while( getline(myfile,line) ){
	if( line[0] == '#' ) continue;	
	int col1, col2, col3;
	std::stringstream first(line);
	first >> col1 >> col2 >> col3;
	fc0_per_run[col1]=col2;
	fc1_per_run[col1]=col3;
	fcsum_per_run[col1]=col2 + col3;

    }    
  }  

  // Draw the fraction of DVCS events to the total accumulated charge (fc0+fc1)
  TCanvas *c1 = new TCanvas("c1","",1600,800);
  c1->Divide(1,1);
  std::vector<Double_t> runs_nh3, bad_runs_nh3, allruns;
  std::vector<Double_t> fc0, fc1, dvcstocharge_nh3, bad_dvcstocharge_nh3;

  TH1D *h_dvcstocharge_nh3 = new TH1D("h_dvcstocharge_nh3","",50,0.0000000001,0.0000015); 

  Double_t fit_mean_nh3 = 0.000000796591;
  Double_t fit_stdev_nh3 = 0.0000000638639;
  std::map<Double_t, Int_t>::iterator it = dvcs_per_run_nh3.begin();
  Double_t eventchargeratio = 0.0;

  const char *pathout = "FinalGoodRuns_GroupAB_NH3_vtest.txt";
  std::ofstream outfile;
  outfile.open(pathout,std::ios_base::in);

  //Determine if run is of good quality

  Double_t sigma_nh3 = 3.0;
  Double_t sigma_c12 = 3.0;

  while( it != dvcs_per_run_nh3.end() ){
    Double_t run = it->first;
    Int_t dvcsevents = it->second;
    Double_t fc0fc1_charge = fcsum_per_run[run];
    //    std::cout << "run " << run << " -- dvcsevents " << dvcsevents << std::endl;
    if( fc0fc1_charge == 0 ){
      eventchargeratio = 0;
    }
    else{ 
      eventchargeratio = dvcsevents/fc0fc1_charge;
    }
    //std::cout << "eventcharge ratio " << eventchargeratio << std::endl;
    allruns.push_back(run);
    fc0.push_back(fc0_per_run[run]);
    fc1.push_back(fc1_per_run[run]);

    //Add a std::cout statement below to produce a final good runs list for nh3 runs
    if( eventchargeratio <= (fit_mean_nh3 + sigma_nh3*fit_stdev_nh3) && (eventchargeratio) >= (fit_mean_nh3 - sigma_nh3*fit_stdev_nh3) ) {
    runs_nh3.push_back(run);
    dvcstocharge_nh3.push_back(eventchargeratio);
    
    ///////// Write to output file NH3 
    outfile << run << std::endl;
    }
    else{
      bad_runs_nh3.push_back(run);
      bad_dvcstocharge_nh3.push_back(eventchargeratio); 
    }
    h_dvcstocharge_nh3->Fill(eventchargeratio);//dvcsevents/fc0fc1_charge);
    it++;
  } 

  std::cout << " Good NH3 dvcstocharge map size " << dvcstocharge_nh3.size() << " -- Bad NH3 dvcstocharge map size" << bad_dvcstocharge_nh3.size() << std::endl;

  TH1D *h_dvcstocharge_c12 = new TH1D("h_dvcstocharge_c12","",50,0.0000000001,0.0000015); 
  Double_t eventcharge_ratio_c12 = 0.0;
  std::vector<Double_t> dvcstocharge_c12, bad_dvcstocharge_c12;
  std::vector<Double_t> runs_c12, bad_runs_c12;


  Double_t fit_mean_c12 = 0.000000255105;
  Double_t fit_stdev_c12 = 0.0000000524801;

  const char *pathout_c12 = "FinalGoodRuns_GroupAB_C12_vtest.txt";
  std::ofstream outfile_c12;
  outfile_c12.open(pathout_c12,std::ios_base::in);

  //Eventcharge ratio for the C12 target
  for( std::map<Double_t, Int_t>::iterator it = dvcs_per_run_c12.begin(); it != dvcs_per_run_c12.end(); ++it ){
    Double_t run_c12 = it->first;
    Int_t dvcsevents_c12 = it->second;

    if( fcsum_per_run[run_c12] == 0 ){
      eventcharge_ratio_c12 = 0;
    }
    else {

      eventcharge_ratio_c12 = dvcsevents_c12/fcsum_per_run[run_c12];
    }

    //Add a std::cout statement here to print good C12 runs out
    if( eventcharge_ratio_c12 <= (fit_mean_c12 + sigma_c12*fit_stdev_c12) && (eventcharge_ratio_c12) >= (fit_mean_c12 - sigma_c12*fit_stdev_c12) ) {
    runs_c12.push_back(run_c12);
    dvcstocharge_c12.push_back(eventcharge_ratio_c12);
    /////////// Write to output file c12
    outfile_c12 << run_c12 << std::endl;
    }
    else{
    bad_runs_c12.push_back(run_c12);
    bad_dvcstocharge_c12.push_back(eventcharge_ratio_c12);
    }  
     h_dvcstocharge_c12->Fill(eventcharge_ratio_c12);
  }

  std::cout << " Good C12 dvcstocharge map size " << dvcstocharge_c12.size() << " -- Bad C12 dvcstocharge map size" << bad_dvcstocharge_c12.size() << std::endl;

  //Event charge ratio for all targets from Run Group A and B
  TH1D *h_dvcstocharge_all = new TH1D("h_dvcstocharge_all", "", 50, 0.0000000001, 0.0000015); 
  Double_t eventcharge_ratio_all = 0.0;
  for(  std::map<Double_t, Int_t >::iterator it = dvcs_per_run_all.begin(); it != dvcs_per_run_all.end(); ++it ){
    Double_t run_all = it->first;
    Int_t dvcsevents_all = it->second;
    if( fcsum_per_run[run_all] == 0 ){
      eventcharge_ratio_all = 0;
    }
    else {
      eventcharge_ratio_all = dvcsevents_all/fcsum_per_run[run_all];
    }
    h_dvcstocharge_all->Fill(eventcharge_ratio_all);
  }

  FittingMethod(h_dvcstocharge_nh3);
  FittingMethod(h_dvcstocharge_c12);

  //TGraph *g_fc0 = new TGraph(allruns.size(), &(allruns[0]), &(fc0[0]));
  //TGraph *g_fc1 = new TGraph(allruns.size(), &(allruns[0]), &(fc1[0]));
  TGraph *g_dvcstocharge_nh3 = new TGraph(runs_nh3.size(), &(runs_nh3[0]), &(dvcstocharge_nh3[0]));
  TGraph *g_dvcstocharge_c12 = new TGraph(runs_c12.size(), &(runs_c12[0]), &(dvcstocharge_c12[0]));
  TGraph *g_baddvcstocharge_nh3 = new TGraph(bad_runs_nh3.size(), &(bad_runs_nh3[0]), &(bad_dvcstocharge_nh3[0]) );
  TGraph *g_baddvcstocharge_c12 = new TGraph(bad_runs_c12.size(), &(bad_runs_c12[0]), &(bad_dvcstocharge_c12[0]) );


  /*c1->cd();
  gPad->SetLogy();
  gPad->SetGrid();
  g_fc0->SetTitle("Total FC0 charge per Run (Group B)");
  g_fc0->SetMarkerStyle(8);
  g_fc0->SetMarkerSize(0.8);
  g_fc0->SetMarkerColor(kBlue+2);
  g_fc0->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  g_fc0->GetYaxis()->SetTitle("FC0 total charge");
  g_fc0->GetXaxis()->CenterTitle(); 
  g_fc0->GetYaxis()->CenterTitle();
  g_fc0->Draw("AP");
 
  c2->cd();
  gPad->SetLogy();
  gPad->SetGrid();
  g_fc1->SetTitle("Total FC1 charge per Run (Group B)");
  g_fc1->SetMarkerStyle(8);
  g_fc1->SetMarkerSize(0.8);
  g_fc1->SetMarkerColor(kRed);
  g_fc1->GetXaxis()->SetTitle("eg1-dvcs Run Number");
  g_fc1->GetYaxis()->SetTitle("FC1 total charge");
  g_fc1->GetXaxis()->CenterTitle(); 
  g_fc1->GetYaxis()->CenterTitle();
  g_fc1->Draw("AP");
  */
  
  TLine *topcut_nh3 = new TLine(58750,fit_mean_nh3 + sigma_nh3*fit_stdev_nh3, 60200,fit_mean_nh3 + sigma_nh3*fit_stdev_nh3);
  TLine *lowercut_nh3 = new TLine(58750,fit_mean_nh3 - sigma_nh3*fit_stdev_nh3, 60200,fit_mean_nh3 - sigma_nh3*fit_stdev_nh3);
  TLine *topcut_c12 = new TLine(58750,fit_mean_c12 + sigma_c12*fit_stdev_c12, 60200,fit_mean_c12 + sigma_c12*fit_stdev_c12);
  TLine *lowercut_c12 = new TLine(58750,fit_mean_c12 - sigma_c12*fit_stdev_c12, 60200,fit_mean_c12 - sigma_c12*fit_stdev_c12);

  c1->cd(1);
  gPad->SetLogy();
  gPad->SetGrid();
  TLegend *leg = new TLegend( 0.75, 0.375, 0.9, 0.625 );
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->AddEntry(g_dvcstocharge_nh3,"Accepted for NH3","P");
  leg->AddEntry(g_baddvcstocharge_nh3,"Rejected for NH3","P");
  leg->AddEntry(g_dvcstocharge_c12,"Accepted for C12","P");
  leg->AddEntry(g_baddvcstocharge_c12,"Rejected for C12","P");
  g_baddvcstocharge_nh3->SetTitle("DVCS Events to Total Charge Ratio");
  g_baddvcstocharge_nh3->GetXaxis()->SetTitle("EG1-DVCS Run Number ");
  g_baddvcstocharge_nh3->GetYaxis()->SetTitle("N_{DVCS}/Q_{total}");
  g_baddvcstocharge_nh3->GetXaxis()->CenterTitle(); 
  g_baddvcstocharge_nh3->GetYaxis()->CenterTitle();
  g_baddvcstocharge_c12->SetTitle("DVCS Events to Total Charge Ratio ");
  g_baddvcstocharge_c12->GetXaxis()->SetTitle("EG1-DVCS Run Number ");
  g_baddvcstocharge_c12->GetYaxis()->SetTitle("N_{DVCS}/Q_{total}");
  g_baddvcstocharge_c12->GetXaxis()->CenterTitle(); 
  g_baddvcstocharge_c12->GetYaxis()->CenterTitle();
 
  g_dvcstocharge_nh3->SetMarkerStyle(8);
  g_dvcstocharge_nh3->SetMarkerSize(0.8);
  g_dvcstocharge_nh3->SetMarkerColor(kBlue+2);
  g_dvcstocharge_c12->SetMarkerStyle(22);
  g_dvcstocharge_c12->SetMarkerSize(0.8);
  g_dvcstocharge_c12->SetMarkerColor(kBlue+2);

  g_baddvcstocharge_nh3->SetMarkerStyle(8);
  g_baddvcstocharge_nh3->SetMarkerSize(0.8);
  g_baddvcstocharge_nh3->SetMarkerColor(kRed);
  g_baddvcstocharge_nh3->Draw("AP");

  g_baddvcstocharge_c12->SetMarkerStyle(22);
  g_baddvcstocharge_c12->SetMarkerSize(0.8);
  g_baddvcstocharge_c12->SetMarkerColor(kRed);
  g_baddvcstocharge_c12->Draw("P");
 
  g_dvcstocharge_nh3->Draw("P");
  g_dvcstocharge_c12->Draw("P");
  leg->Draw("same");

  topcut_nh3->SetLineColor(kRed);
  topcut_nh3->Draw("same");
  lowercut_nh3->SetLineColor(kRed);
  lowercut_nh3->Draw("same");

  topcut_c12->SetLineColor(kRed);
  topcut_c12->Draw("same");
  lowercut_c12->SetLineColor(kRed);
  lowercut_c12->Draw("same");
  
  //c1->SaveAs("QAgroupABC.pdf");
  //c2->SaveAs("FC1_groupB.pdf");

  TCanvas *c_all = new TCanvas("c_all","c_all",800,500);
  c_all->Divide(1,1);
  c_all->cd(1);
  gStyle->SetOptStat(0);

  TLegend *leg2 = new TLegend( 0.75, 0.375, 0.9, 0.625 );
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->AddEntry(h_dvcstocharge_nh3, "NH3 Target", "f");
  leg2->AddEntry(h_dvcstocharge_c12, "C12 Target", "f");
  
  h_dvcstocharge_nh3->SetTitle("Number of DVCS events to total FC charge Group A&B");
  h_dvcstocharge_nh3->GetXaxis()->SetTitle("N_{DVCS}/FC_{total}");
  h_dvcstocharge_nh3->SetFillColorAlpha(kRed-4,0.7);
  h_dvcstocharge_c12->SetFillColorAlpha(kBlue-2,0.7);
  h_dvcstocharge_nh3->Draw("hist");
  h_dvcstocharge_c12->Draw("same + hist");
  leg2->Draw("same");


  myfile.close();  
}
