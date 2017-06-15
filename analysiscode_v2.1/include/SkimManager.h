#ifndef SkimManager_hh
#define SkimManager_hh

//#include "RunDB.h"
#include "HistogramTool.h"
#include "DVCSHistogramTool.h"
#include "PIDHistograms.h"
#include "BPIDHistograms.h"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"
#include "TSystemFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include <map>

class SkimManager {

 public:
  SkimManager();
  ~SkimManager();

  Eventh22 event;
  Loadh22 loadh22;
  Setter setter;
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
  Int_t nthfile;
  Int_t nentries;
  TList *listtoprocess;

 public:
  const char *ext;  
  std::string sfiletoskim;
  std::size_t found;
  std::string filebasename;
  bool tempprotonbool;
  bool tempphotonbool;

 public:
  std::map< Int_t, TLorentzVector > energeticPhoton;  

 public:
  TString SkimPrefix(Int_t);
  void SkimByFile(const char*, const char*);
  void SkimByFile(const char*, Int_t, Int_t );
  // void SkimByFile( Int_t );
  void SkimLevel(Int_t, TChain*);
  void SkimCuts(TString);
  void SkimProcessEntries(TChain*, TTree*);
  void SkimProcessEntries(TChain*, TTree*, Int_t, DVCSHistogramTool, HistogramTool);
  void SkimProcessEntries(TChain*, TTree*, Int_t, DVCSHistogramTool, HistogramTool, BPIDHistograms, TFile*);  
  void SkimRoutine();
  void CloneTree();
  void Close();
  void ReadTree();

  Double_t z_posp;  
  Double_t zpos;  
};

#endif
