#ifndef Eventh22_h
#define Eventh22_h

#include "TROOT.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include <map>

class Eventh22{

 public:
  // Declaration of leaf types
  UInt_t          evntid;
  UChar_t           ihel;
  Int_t           gpart;
  Int_t           q[40];   //[gpart]
  Float_t         p[40];   //[gpart]
  Float_t         b[40];   //[gpart]
  Float_t         cx[40];   //[gpart]
  Float_t         cy[40];   //[gpart]
  Float_t         vz[40];   //[gpart]
  UChar_t         dc_sect[40];   //[gpart]
  Float_t         tl1_cx[40];   //[gpart]
  Float_t         tl1_cy[40];   //[gpart]
  UChar_t         ec_sect[40];   //[gpart]
  Float_t         ec_r[40];   //[gpart]
  Float_t         ec_t[40];   //[gpart]
  Float_t         ec_ei[40];   //[gpart]
  Float_t         ec_eo[40];   //[gpart]
  Float_t         etot[40];   //[gpart]
  UChar_t         cc_sect[40];   //[gpart]
  Float_t         cc_r[40];   //[gpart]
  Float_t         cc_t[40];   //[gpart]
  UShort_t        nphe[40];   //[gpart]
  Float_t         cc_c2[40];   //[gpart]
  UChar_t         sc_sect[40];   //[gpart]
  Float_t         sc_r[40];   //[gpart]
  Float_t         sc_t[40];   //[gpart]
  Float_t         edep[40];   //[gpart]
  UChar_t         sc_pd[40];   //[gpart]
  UChar_t         cc_pmt[40];   //[gpart]
  Float_t         ech_x[40];   //[gpart]
  Float_t         ech_y[40];   //[gpart]
  Float_t         ech_z[40];   //[gpart]
  Float_t         tl1_x[40];   //[gpart]
  Float_t         tl1_y[40];   //[gpart]
  Float_t         tl1_z[40];   //[gpart]
  Float_t         tl3_x[40];   //[gpart]
  Float_t         tl3_y[40];   //[gpart]
  Float_t         tl3_z[40];   //[gpart]
  Float_t         tl3_cx[40];   //[gpart]
  Float_t         tl3_cy[40];   //[gpart]
  Float_t         tl3_cz[40];   //[gpart]
  Int_t           id[40];   //[gpart]
  Float_t         vx[40];   //[gpart]
  Float_t         vy[40];   //[gpart]
  Int_t           svicpart;
  Float_t         xc[40];   //[svicpart]
  Float_t         yc[40];   //[svicpart]
  Float_t         etc[40];   //[svicpart]
  Float_t         ecc[40];   //[svicpart]
  Float_t         tc[40];   //[svicpart]
  UChar_t         nblk[40];   //[svicpart]
  Float_t         ich_x[40];   //[svicpart]
  Float_t         ich_y[40];   //[svicpart]
  Float_t         et[40];   //[svicpart]
  Float_t         egl[40];   //[svicpart]
  Float_t         ich_xgl[40];   //[svicpart]
  Float_t         ich_ygl[40];   //[svicpart]
  UShort_t        rastr1;
  UShort_t        rastr2;

  ///////////////////////////////////////////
  //
  //  Below are the tree variables that 
  //  are found in the Monte Carlo ntuple
  //  Added on 2-21-2017
  //                                 
  ///////////////////////////////////////////
  
  Int_t           nprt;
  Int_t           pidpart[20];   //[nprt]
  Float_t         xpart[20];   //[nprt]
  Float_t         ypart[20];   //[nprt]
  Float_t         zpart[20];   //[nprt]
  Float_t         epart[20];   //[nprt]
  Float_t         pxpart[20];   //[nprt]
  Float_t         pypart[20];   //[nprt]
  Float_t         pzpart[20];   //[nprt]
  Float_t         qpart[20];   //[nprt]
  Int_t           Ipart10[20];   //[nprt]
  Float_t         Rpart11[20];   //[nprt]
  Float_t         Rpart12[20];   //[nprt]
  Int_t           Ipart13[20];   //[nprt]
  Int_t           mcnentr;
  UChar_t         mcnpart;
  Int_t           mcevnt;
  Int_t           mcst[20];   //[mcnentr]
  Int_t           mcid[20];   //[mcnentr]
  Int_t           mcpid[20];   //[mcnentr]
  Float_t         mctheta[20];   //[mcnentr]
  Float_t         mcphi[20];   //[mcnentr]
  Float_t         mcp[20];   //[mcnentr]
  Float_t         mcm[20];   //[mcnentr]
  Float_t         mcvx[20];   //[mcnentr]
  Float_t         mcvy[20];   //[mcnentr]
  Float_t         mcvz[20];   //[mcnentr]


  //////////////////////////////////////
  //
  // Methods below Set golden index for 
  // later use in Cuts class
  //
  /////////////////////////////////////
  Int_t goldenelectronindex;
  Int_t goldenprotonindex;
  Int_t goldenecphotonindex;
  Int_t nelectron, nproton;
  Int_t necph, nicph, necicph;
  Int_t singleElectron, multiElectron, singleEP, multiProton, totalEPG, totalEPGG;

  void SetGoldenElectronIndex( Int_t );
  void SetGoldenProtonIndex( Int_t );
  void SetGoldenECPhotonIndex( Int_t );

  void SetNumGoodElectron(Int_t);
  void SetNumGoodProton(Int_t);
  void SetNumGoodPhotons(Int_t, Int_t);
  
  void ChosenPhoton( Int_t, TLorentzVector );
  Int_t phdetectorID;
  TLorentzVector ph_LV;
  void ClearCountersNIndices();

 public:
  Eventh22();
  ~Eventh22();
  
};
#endif
