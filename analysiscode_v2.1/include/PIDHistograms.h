#ifndef PIDHistograms_hh
#define PIDHistograms_hh

#include "../include/Loadh22.h"
#include "../include/Eventh22.h"
#include "../include/Cuts.h"
#include "../include/Calculator.h"
#include "../include/CutManager.h"
#include "../include/BuildtPID.h"

#include <vector>
#include <THnSparse.h>
#include <TFile.h>

class PIDHistograms : public Calculator{

  
 public:
  PIDHistograms();
  PIDHistograms(TFile*);
  ~PIDHistograms();

  void InitiateAllHistograms();
  void CreateDirectories( TFile* );
  Double_t *CreateElectronProperties( Eventh22, Int_t );
  Double_t *electronproperites = new Double_t[8];

  std::vector<double> CreateParticleProperties( Int_t, Eventh22, Int_t );
  std::vector< Double_t> particleprop;
  
  void FillElectronTHn( std::vector<bool>, Eventh22, Int_t );
  void FillProtonTHn( std::vector<bool>, Eventh22, Int_t );
  void FillECPhotonTHn( std::vector<bool>, Eventh22, Int_t );
  void FillICPhotonTHn( std::vector<bool>, Eventh22, Int_t );
  void FillGoodCandidateParticleTHn( Int_t, std::vector<bool>, Eventh22, Int_t); 


  void WriteSparses( );
  void WriteSparses( TFile* );


 public:

  TFile *putoutfile;
  std::vector< TString > foldernames;

  BuildtPID buildtPID;
  Int_t electronD1;  
  Int_t electronD2;
  std::vector<THnSparseD*> hns_electron;
  std::vector<THnSparseD*> hns_proton;
  std::vector<THnSparseD*> hns_ecph;
  std::vector<THnSparseD*> hns_icph;
  //Below vector containers are for particles that pass all their respective cuts
  std::vector<THnSparseD*> hns_gelectron;
  std::vector<THnSparseD*> hns_gproton;
  std::vector<THnSparseD*> hns_gecph;
  std::vector<THnSparseD*> hns_gicph;
  
 
  Int_t nel_cuts, npr_cuts, necph_cuts, nicph_cuts, protonD1, ecphD1,icphD1;

 public:
  Calculator calculator;
  ECplaneRotated planes; // This class has the hall cordinates for the EC hit. It's not in the calculator class though it should really be. :/
  void AddCorrections( Calculator );

};

#endif
