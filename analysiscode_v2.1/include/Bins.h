#ifndef Bins_hh
#define Bins_hh

#include "TMath.h"
#include <vector>

class Bins {

 public:
  Bins();
  ~Bins();

 public:
  void SetBinLimits();

 protected:
  std::vector<Double_t> x_binlimit_max;
  std::vector<Double_t> t_binlimit_max;
  std::vector<Double_t> qq_binlimit_max;

  std::vector<Double_t> x_binlimit_min;
  std::vector<Double_t> t_binlimit_min;
  std::vector<Double_t> qq_binlimit_min;

};

#endif
