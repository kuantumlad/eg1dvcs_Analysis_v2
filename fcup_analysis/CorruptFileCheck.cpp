#include <TFile.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TMath.h>
#include <TString.h>
#include "TROOT.h"
#include "TBrowser.h"
#include <iostream>
#include <string>
#include "TChain.h"
#include "TRegexp.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"
#include "TList.h"

///////////////////////////////////////////////////////////////
//
// By: Brandon Clary
//     6-7-2017
//
//Check to find which files in the tempdirname have a null pointer to the file,
//have a bad TTree or TChain, and to see if it is a Zombie file.
//This is to check if certain files were accidently used in the 
//counting the FC charge.
//
/////////////////////////////////////////////////////////////////

TSystemFile *file;

void CorruptFileCheck( const char* tempdirname ){

  int i = 0.0;
  Double_t goodfile_cnt = 0.0;
  Double_t badfile_cnt = 0.0;
  Double_t badtree_cnt = 0.0;

  const char* ext = ".root";

  TSystemDirectory dir(tempdirname, tempdirname);
  TList *files = dir.GetListOfFiles();
  // TSystemFile *testfind = (TSystemFile*)files->FindObject("root22_59519_a00.root");
  // std::cout <<  testfind->GetName() << std::endl;
  if (files){
    TIter next(files);
    
    while((file=(TSystemFile*)next()) ){
      TString filename = file->GetName();
      TString filetoskim = (std::string)tempdirname + filename;
      if( !file->IsDirectory() && filename.EndsWith(ext) ){
	TFile *originalfile = new TFile(filetoskim);
	//	std::cout << ">> Checking " << filetoskim << std::endl;
	if(originalfile == 0 || file->IsZombie() ){
	  std::cout << "NULL pointer for originalfile - "<< filetoskim << std::endl;
	  badfile_cnt++;
	  originalfile->Close();
	  continue;
	}
	
	TTree *originaltree = (TTree*) originalfile->Get("tPID");
	TChain *originalChain = (TChain*)originalfile->Get("tPID");
	if( originaltree == 0 || originalChain == 0 ){
	  std::cout << "NULL pointer for originaltree or originalChain - tPID"  << std::endl;
	  badtree_cnt++;
	  originalfile->Close();
	  continue;
	}
	originalfile->Close();
	goodfile_cnt++;
       
      }
      if( i%1000 == 0 ) std::cout << i << std::endl;
      i++;
    }
  }
  std::cout << "----------- REPORT CARD ---------- " << std::endl;
  std::cout << " Number of good files " << goodfile_cnt << std::endl;
  std::cout << " Number of bad files " << badfile_cnt << std::endl;
  std::cout << " Number of bad TTrees " << badtree_cnt << std::endl;
  std::cout << ">> Complete " << std::endl;
}
