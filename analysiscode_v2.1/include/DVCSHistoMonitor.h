#ifndef dvcshistomonitor_hh
#define dvcshistomonitor_hh

#include "EventPID.h"
#include "PhysicsCutManager.h"
#include "BDVCSHistograms.h"
#include "Calculator.h"

#include <vector>

class DVCSHistoMonitor{

 public: 
  DVCSHistoMonitor();
  DVCSHistoMonitor(Calculator);
  ~DVCSHistoMonitor();

  EventPID dvcs;
  PhysicsCutManager pcmanager;
  BDVCSHistograms bdvcshist;
  Calculator calculator;

  void InitiateRunInfo( Calculator );
  void CreateDVCSHist( PhysicsCutManager, BDVCSHistograms );
  void FillDVCSElHist( std::vector<bool>, EventPID, Int_t); 
  void FillDVCSPrHist( std::vector<bool>, EventPID, Int_t); 
  void FillDVCSPhHist( std::vector<bool>, EventPID, Int_t); 
  void FillDVCSKinECHist( std::vector<bool>, EventPID, Int_t); 
  void FillDVCSKinICHist( std::vector<bool>, EventPID, Int_t); 
  void FillAsymHistA( std::vector<bool>, EventPID, Int_t);  
  void FillAsymHistB( std::vector<bool>, EventPID, Int_t); 

};
#endif
