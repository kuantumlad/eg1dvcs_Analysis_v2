#define bins_cxx

#include "../include/Bins.h"

#include <vector>


Bins::Bins(){

}


Bins::~Bins(){

}


void Bins::SetBinLimits(){

  x_binlimit_max.push_back(0.2);
  x_binlimit_max.push_back(0.3);
  x_binlimit_max.push_back(0.3);
  x_binlimit_max.push_back(0.4);
  x_binlimit_max.push_back(1);

  x_binlimit_min.push_back(0.1);
  x_binlimit_min.push_back(0.2);
  x_binlimit_min.push_back(0.2);
  x_binlimit_min.push_back(0.3);
  x_binlimit_min.push_back(0.4);

  t_binlimit_max.push_back(0.18);
  t_binlimit_max.push_back(0.30);
  t_binlimit_max.push_back(0.70);
  t_binlimit_max.push_back(2.0);

  t_binlimit_min.push_back(0.08);
  t_binlimit_min.push_back(0.18);
  t_binlimit_min.push_back(0.3);
  t_binlimit_min.push_back(0.7);

  qq_binlimit_max.push_back(48);
  qq_binlimit_max.push_back(34);
  qq_binlimit_max.push_back(48);
  qq_binlimit_max.push_back(45);
  qq_binlimit_max.push_back(45);

  qq_binlimit_min.push_back(15);
  qq_binlimit_min.push_back(15);
  qq_binlimit_min.push_back(34);
  qq_binlimit_min.push_back(15);
  qq_binlimit_min.push_back(15);

}
