#ifndef BinsHisto_hh
#define BinsHisto_hh

#include "Bins.h"

#include <TH1D.h>

class BinsHisto {

 public:
  BinsHisto();
  ~BinsHisto();

  void InitializeBinHistograms();
  
  const static TH1D* h1_phi[3][3][6][6][3];


};
#endif
