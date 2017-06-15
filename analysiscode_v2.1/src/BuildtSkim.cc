#define buildtskim_cxx

#include "../include/BuildtSkim.h"
#include "../include/Eventh22.h"
#include "../include/Calculator.h"
#include "TTree.h"
#include "TMath.h"
#include "TBranch.h"
#include "TString.h"
#include "TLorentzVector.h"

#include <iostream>

BuildtSkim::BuildtSkim(){

}

BuildtSkim::~BuildtSkim(){

}

void BuildtSkim::InitSkim(){

  tSkim = new TTree("tSkim","my PID Tree");
  tSkim->SetDirectory(0);

  tSkim->Branch("evntid", &evntid);
  tSkim->Branch("ihel", &ihel);
  tSkim->Branch("gpart", &gpart);  
  tSkim->Branch("q", q);
  tSkim->Branch("p", p);
  tSkim->Branch("b", b);
  tSkim->Branch("cx", cx);
  tSkim->Branch("cy", cy);
  tSkim->Branch("cz", cz);
  tSkim->Branch("vz", vz);
  tSkim->Branch("dc_sect", dc_sect);
  tSkim->Branch("tl1_cx", tl1_cx);
  tSkim->Branch("tl1_cy", tl1_cy);
  tSkim->Branch("ec_sect", ec_sect);
  tSkim->Branch("ec_r", ec_r);
  tSkim->Branch("ec_t", ec_t);
  tSkim->Branch("ec_ei", ec_ei);
  tSkim->Branch("ec_eo", ec_ei);
  tSkim->Branch("etot", etot);
  tSkim->Branch("cc_sect", cc_sect);
  tSkim->Branch("cc_r", cc_r);
  tSkim->Branch("cc_t", cc_t);
  tSkim->Branch("nphe", nphe);
  tSkim->Branch("cc_c2", cc_c2);
  tSkim->Branch("sc_sect", sc_sect);
  tSkim->Branch("sc_r", sc_r);
  tSkim->Branch("sc_t", sc_t);
  tSkim->Branch("edep", edep);
  tSkim->Branch("sc_pd", sc_pd);
  tSkim->Branch("cc_pmt", cc_pmt);
  tSkim->Branch("ech_x", ech_x);
  tSkim->Branch("ech_y", ech_y);
  tSkim->Branch("ech_z", ech_z);
  tSkim->Branch("tl1_x", tl1_x);
  tSkim->Branch("tl1_y", tl1_y);
  tSkim->Branch("tl1_z", tl1_z);
  tSkim->Branch("tl3_x", tl3_x);
  tSkim->Branch("tl3_y", tl3_y);
  tSkim->Branch("tl3_z", tl3_z);
  tSkim->Branch("tl3_cx", tl3_cx);
  tSkim->Branch("tl3_cy", tl3_cy);
  tSkim->Branch("tl3_cz", tl3_cz);
  tSkim->Branch("id", id);
  tSkim->Branch("vx", vx);
  tSkim->Branch("vy", vy);
  tSkim->Branch("svcicpart", &svcicpart);
  tSkim->Branch("xc", xc);
  tSkim->Branch("xy", xy);
  tSkim->Branch("etc", ecc);
  tSkim->Branch("tc", tc);
  tSkim->Branch("nblk", nblk);
  tSkim->Branch("ich_x", ich_x);
  tSkim->Branch("ich_y", ich_y);
  tSkim->Branch("et", et);
  tSkim->Branch("egl", egl);
  tSkim->Branch("ich_xgl", ich_xgl );
  tSkim->Branch("ich_ygl", ich_ygl );
  tSkim->Branch("rastr1", rastr1);
  tSkim->Branch("rastr2", rastr2);
}

void BuildtSkim::Fill( Eventh22 tempevent ){
  /*  evntid = tempevent.evntid;
  ihel = tempevent.ihel;
  gpart  = tempevent.gpart;
  q[k] = tempevent.q[m];   //[gpart]
  p[k] = tempevent.p[m];   //[gpart]
  b[k] = tempevent.b[m];   //[gpart]
  cx[k] = tempevent.cx[m];   //[gpart]
  cy[k] = tempevent.cy[m];   //[gpart]
  vz[k] = tempevent.vz[m];   //[gpart]
  dc_sect[k] = tempevent.dc_sect[m];   //[gpart]
  tl1_cx[k] = tempevent.tl1_cx[m];   //[gpart]
  tl1_cy[k] = tempevent.tl1_cy[m];   //[gpart]
  ec_sect[k] = tempevent.ec_sect[m];   //[gpart]
  ec_r[k] = tempevent.ec_r[m];   //[gpart]
  ec_t[k] = tempevent.ec_t[k];   //[gpart]
  ec_ei[k] = tempevent.ec_ei[m];   //[gpart]
  ec_eo[k] = tempevent.ec_eo[m];   //[gpart]
  etot[k] = tempevent.etot[m];   //[gpart]
  cc_sect[k] = tempevent.cc_sect[m];   //[gpart]
  cc_r[k] = tempevent.cc_r[m];   //[gpart]
  cc_t[k] = tempevent.cc_t[m];   //[gpart]
  nphe[k] = tempevent.nphe[m];   //[gpart]
  cc_c2[k] = tempevent.cc_c2[m];   //[gpart]
  sc_sect[k] = tempevent.sc_sect[m];   //[gpart]
  sc_r[k] = tempevent.sc_r[m];   //[gpart]
  sc_t[k] = tempevent.sc_t[m];   //[gpart]
  edep[k] = tempevent.edep[m];   //[gpart]
  sc_pd[k] = tempevent.sc_pd[m];   //[gpart]
  cc_pmt[k] = tempevent.cc_pmt[m];   //[gpart]
  ech_x[k] = tempevent.ech_x[m];   //[gpart]
  ech_y[k] = tempevent.ech_y[m];   //[gpart]
  ech_z[k] = tempevent.ech_z[m];   //[gpart]
  tl1_x[k] = tempevent.tl1_x[m];   //[gpart]
  tl1_y[k] = tempevent.tl1_y[m];   //[gpart]
  tl1_z[k] = tempevent.tl1_z[m];   //[gpart]
  tl3_x[k] = tempevent.tl3_x[m];   //[gpart]
  tl3_y[k] = tempevent.tl3_y[m];    //[gpart]
  tl3_z[k] = tempevent.tl3_z[m];    //[gpart]
  tl3_cx[k] = tempevent.tl3_cx[m];   //[gpart]
  tl3_cy[k] = tempevent.tl3_cy[m];   //[gpart]
  tl3_cz[k] = tempevent.tl3_cz[m];   //[gpart]
  id[k] = tempevent.id[m];   //[gpart]
  vx[k] = tempevent.vx[m];   //[gpart]
  vy[k] = tempevent.vy[m];   //[gpart]
  svicpart = tempevent.svicpart;
  xc[k] = tempevent.xc[m];   //[svicpart]
  yc[k] = tempevent.yc[m];   //[svicpart]
  etc[k] = tempevent.etc[m];   //[svicpart]
  ecc[k] = tempevent.ecc[m];   //[svicpart]
  tc[k] = tempevent.tc[m];   //[svicpart]
  nblk[k] = tempevent.nblk[m];   //[svicpart]
  ich_x[k] = tempevent.ich_x[m];   //[svicpart]
  ich_y[k] = tempevent.ich_y[m];   //[svicpart]
  et[k] = tempevent.et[m];   //[svicpart]
  egl[k] = tempevent.egl[m]; //[svicpart]
  ich_xgl[k] = tempevent.ich_xgl[k];   //[svicpart]
  ich_ygl[k] = tempevent.ich_ygl[m];   //[svicpart]
  rastr1 = tempevent.rastr1;
  rastr2 = tempevent.rastr2;
  // for loop, add calc arguement and the other shit for indexing 
  tSkim->Fill();
  */}

void BuildtSkim::WriteToTree(){

  tSkim->Write();
  tSkim->AutoSave();
}

void BuildtSkim::PrintTree(){

  tSkim->Scan();
  
}
