#ifndef buildtskim_h
#define buildtskim_h

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "PhysicsEventBuilder.h"
#include "PhysicsEvent.h"
#include "TLorentzVector.h"

class BuildtSkim {

 public:
  BuildtSkim();
  ~BuildtSkim();

 public:
    TTree *tSkim;

      // Declaration of leaf types
  UInt_t          evntid;
  UChar_t         ihel;
  Int_t           gpart;
  Int_t           q[10];   //[gpart]
  Float_t         p[10];   //[gpart]
  Float_t         b[10];   //[gpart]
  Float_t         cx[10];   //[gpart]
  Float_t         cy[10];   //[gpart]
  Float_t         cz[10];
  Float_t         vz[10];   //[gpart]
  UChar_t         dc_sect[10];   //[gpart]
  Float_t         tl1_cx[10];   //[gpart]
  Float_t         tl1_cy[10];   //[gpart]
  UChar_t         ec_sect[10];   //[gpart]
  Float_t         ec_r[10];   //[gpart]
  Float_t         ec_t[10];   //[gpart]
  Float_t         ec_ei[10];   //[gpart]
  Float_t         ec_eo[10];   //[gpart]
  Float_t         etot[10];   //[gpart]
  UChar_t         cc_sect[10];   //[gpart]
  Float_t         cc_r[10];   //[gpart]
  Float_t         cc_t[10];   //[gpart]
  UShort_t        nphe[10];   //[gpart]
  Float_t         cc_c2[10];   //[gpart]
  UChar_t         sc_sect[10];   //[gpart]
  Float_t         sc_r[10];   //[gpart]
  Float_t         sc_t[10];   //[gpart]
  Float_t         edep[10];   //[gpart]
  UChar_t         sc_pd[10];   //[gpart]
  UChar_t         cc_pmt[10];   //[gpart]
  Float_t         ech_x[10];   //[gpart]
  Float_t         ech_y[10];   //[gpart]
  Float_t         ech_z[10];   //[gpart]
  Float_t         tl1_x[10];   //[gpart]
  Float_t         tl1_y[10];   //[gpart]
  Float_t         tl1_z[10];   //[gpart]
  Float_t         tl3_x[10];   //[gpart]
  Float_t         tl3_y[10];   //[gpart]
  Float_t         tl3_z[10];   //[gpart]
  Float_t         tl3_cx[10];   //[gpart]
  Float_t         tl3_cy[10];   //[gpart]
  Float_t         tl3_cz[10];   //[gpart]
  Int_t           id[10];   //[gpart]
  Float_t         vx[10];   //[gpart]
  Float_t         vy[10];   //[gpart]
  Int_t           svcicpart;
  Float_t         xc[10];   //[svicpart]
  Float_t         yc[10];   //[svicpart]
  Float_t         etc[10];   //[svicpart]
  Float_t         ecc[10];   //[svicpart]
  Float_t         tc[10];   //[svicpart]
  UChar_t         nblk[10];   //[svicpart]
  Float_t         ich_x[10];   //[svicpart]
  Float_t         ich_y[10];   //[svicpart]
  Float_t         et[10];   //[svicpart]
  Float_t         egl[10];   //[svicpart]
  Float_t         ich_xgl[10];   //[svicpart]
  Float_t         ich_ygl[10];   //[svicpart]
  UShort_t        rastr1;
  UShort_t        rastr2;
  Float_t xy;

 public:
    PhysicsEvent pevent;
    void Fill( Eventh22 );
    void InitSkim();
    void WriteToTree();
    void PrintTree();
    void GetEntry( Int_t entry ){ tSkim->GetEntry(entry); }
    Int_t skimEntries( ) { return tSkim->GetEntries();};
    
};


#endif
  
