#ifndef pidhistomonitor_hh
#define pidhistomonitor_hh

#include "Eventh22.h"
#include "Loadh22.h"
#include "CutManager.h"
#include "BPIDHistograms.h"
#include "Calculator.h"

#include <vector>


class PIDHistoMonitor{

 public:
  PIDHistoMonitor();
  PIDHistoMonitor(Calculator);
  ~PIDHistoMonitor();

  Eventh22 event;
  CutManager cutmanager;
  BPIDHistograms bpidhist;
  Calculator calculator;

  void InitiateRunInfo( Calculator );
  void CreatePIDHist(CutManager, BPIDHistograms);
  void FillElectronHisto( std::vector<bool>, Eventh22 &, Int_t, Int_t );
  void FillProtonHisto( std::vector<bool>, Eventh22 &, Int_t, Int_t );
  void FillECPhotonHisto( std::vector<bool>, Eventh22 &, Int_t, Int_t );
  void FillICPhotonHisto( std::vector<bool>, Eventh22 &, Int_t, Int_t );
 
 private:
  Double_t SpeedOfLight;
  Double_t target_vz;
  Double_t shiftTime;
  Double_t offsetTime;
  Double_t ecsf1;
  Double_t ecsf2; 
  Double_t ecsf3;
  Double_t ecsf4;
  Double_t ecsf5;
  Double_t ecsf6;
  Double_t ecscalefactor;

};
#endif
