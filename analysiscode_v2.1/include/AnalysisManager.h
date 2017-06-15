#ifndef AnalysisManager_hh
#define AnalysisManager_hh

#include "RunDB.h"
#include "HistogramTool.h"
#include "DVCSHistogramTool.h"
#include "BDVCSHistograms.h"
#include "EventDVCS.h"
#include "LoadDVCS.h"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"
#include "TSystemFile.h"
#include "TTree.h"

class AnalysisManager {

 public:
  AnalysisManager();
  ~AnalysisManager();

  EventDVCS event;
  LoadDVCS loadDVCS;
  // RunDB eg1db;  

 public:
  TChain *originalChain;
  TFile *skimfile;
  TFile *originalfile;
  TTree *originaltree;
  TList *files;
  TSystemFile *file;
  TTree *clonedtree;
  TString filetoskim;
  TString tempfiletoskim;
  TString skimprefix;
  TString filename;
  Int_t filecounter;
  Double_t fileprogress;
  Int_t progressbar;
  Int_t nentries;
  Int_t runnum;

  TLorentzVector el_LV, pr_LV, photonLV;


 public:
  const char *ext;  
  std::string sfiletoskim;
  std::size_t found;
  std::string filebasename;
  bool tempprotonbool;
  bool tempphotonbool;

 public:
  TString SkimPrefix(Int_t);
  Int_t RunNumb(TString);
  void AnalyzeByFile(const char*, const char*);
  void AnalyzeLevel(Int_t, TChain*);
  void SkimCuts(TString);
  void AnalyzeProcessEntries(TChain*, TTree*);
  void AnalyzeEntries(TChain*, TTree*, Int_t, DVCSHistogramTool, BDVCSHistograms );
  void AnalyzeEntries(TChain*, TTree*, Int_t, BDVCSHistograms );
  void SkimRoutine();
  void CloneTree();
  void Close();
  void ReadTree();
  
  
};

#endif
