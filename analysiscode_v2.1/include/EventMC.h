#ifndef EventMC_h
#define EventMC_h

#include "TROOT.h"
#include "TMath.h"

class EventMC{

 public:
   // Declaration of leaf types
   UInt_t          evntid;
   UChar_t         ihel;
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

 public:
   EventMC();
   ~EventMC();
  
};
#endif
