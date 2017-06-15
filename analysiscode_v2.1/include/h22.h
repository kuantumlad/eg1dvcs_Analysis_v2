//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 23 16:44:03 2016 by ROOT version 6.06/04
// from TTree h22/EG1DVCSSKIM
// found on file: root22_60001_a00.root
//////////////////////////////////////////////////////////

#ifndef H22_H
#define H22_H  //edited from lowercase to upper

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

// Header file for the classes stored in the TTree if any.

class h22 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
    
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
   UShort_t        rastr1;
   UShort_t        rastr2;

   // List of branches
   TBranch        *b_evntid;   //!
   TBranch        *b_ihel;   //!
   TBranch        *b_gpart;   //!
   TBranch        *b_q;   //!
   TBranch        *b_p;   //!
   TBranch        *b_b;   //!
   TBranch        *b_cx;   //!
   TBranch        *b_cy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_dc_sect;   //!
   TBranch        *b_tl1_cx;   //!
   TBranch        *b_tl1_cy;   //!
   TBranch        *b_ec_sect;   //!
   TBranch        *b_ec_r;   //!
   TBranch        *b_ec_t;   //!
   TBranch        *b_ec_ei;   //!
   TBranch        *b_ec_eo;   //!
   TBranch        *b_etot;   //!
   TBranch        *b_cc_sect;   //!
   TBranch        *b_cc_r;   //!
   TBranch        *b_cc_t;   //!
   TBranch        *b_nphe;   //!
   TBranch        *b_cc_c2;   //!
   TBranch        *b_sc_sect;   //!
   TBranch        *b_sc_r;   //!
   TBranch        *b_sc_t;   //!
   TBranch        *b_edep;   //!
   TBranch        *b_sc_pd;   //!
   TBranch        *b_cc_pmt;   //!
   TBranch        *b_ech_x;   //!
   TBranch        *b_ech_y;   //!
   TBranch        *b_ech_z;   //!
   TBranch        *b_tl1_x;   //!
   TBranch        *b_tl1_y;   //!
   TBranch        *b_tl1_z;   //!
   TBranch        *b_tl3_x;   //!
   TBranch        *b_tl3_y;   //!
   TBranch        *b_tl3_z;   //!
   TBranch        *b_tl3_cx;   //!
   TBranch        *b_tl3_cy;   //!
   TBranch        *b_tl3_cz;   //!
   TBranch        *b_id;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_svicpart;   //!
   TBranch        *b_xc;   //!
   TBranch        *b_yc;   //!
   TBranch        *b_etc;   //!
   TBranch        *b_ecc;   //!
   TBranch        *b_tc;   //!
   TBranch        *b_nblk;   //!
   TBranch        *b_ich_x;   //!
   TBranch        *b_ich_y;   //!
   TBranch        *b_et;   //!
   TBranch        *b_egl;   //!
   TBranch        *b_ich_xgl;   //!
   TBranch        *b_ich_ygl;   //!
   TBranch        *b_rastr1;   //!
   TBranch        *b_rastr2;   //!

   h22(TTree *tree=0);
   virtual ~h22();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef h22_cxx
h22::h22(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../../run data/run6001/root22_60001_a00.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../../run data/run60001/root22_60001_a00.root");
      }
      f->GetObject("h22",tree);

   }
   Init(tree);
}

h22::~h22()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t h22::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t h22::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void h22::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evntid", &evntid, &b_evntid);
   fChain->SetBranchAddress("ihel", &ihel, &b_ihel);
   fChain->SetBranchAddress("gpart", &gpart, &b_gpart);
   fChain->SetBranchAddress("q", q, &b_q);
   fChain->SetBranchAddress("p", p, &b_p);
   fChain->SetBranchAddress("b", b, &b_b);
   fChain->SetBranchAddress("cx", cx, &b_cx);
   fChain->SetBranchAddress("cy", cy, &b_cy);
   fChain->SetBranchAddress("vz", vz, &b_vz);
   fChain->SetBranchAddress("dc_sect", dc_sect, &b_dc_sect);
   fChain->SetBranchAddress("tl1_cx", tl1_cx, &b_tl1_cx);
   fChain->SetBranchAddress("tl1_cy", tl1_cy, &b_tl1_cy);
   fChain->SetBranchAddress("ec_sect", ec_sect, &b_ec_sect);
   fChain->SetBranchAddress("ec_r", ec_r, &b_ec_r);
   fChain->SetBranchAddress("ec_t", ec_t, &b_ec_t);
   fChain->SetBranchAddress("ec_ei", ec_ei, &b_ec_ei);
   fChain->SetBranchAddress("ec_eo", ec_eo, &b_ec_eo);
   fChain->SetBranchAddress("etot", etot, &b_etot);
   fChain->SetBranchAddress("cc_sect", cc_sect, &b_cc_sect);
   fChain->SetBranchAddress("cc_r", cc_r, &b_cc_r);
   fChain->SetBranchAddress("cc_t", cc_t, &b_cc_t);
   fChain->SetBranchAddress("nphe", nphe, &b_nphe);
   fChain->SetBranchAddress("cc_c2", cc_c2, &b_cc_c2);
   fChain->SetBranchAddress("sc_sect", sc_sect, &b_sc_sect);
   fChain->SetBranchAddress("sc_r", sc_r, &b_sc_r);
   fChain->SetBranchAddress("sc_t", sc_t, &b_sc_t);
   fChain->SetBranchAddress("edep", edep, &b_edep);
   fChain->SetBranchAddress("sc_pd", sc_pd, &b_sc_pd);
   fChain->SetBranchAddress("cc_pmt", cc_pmt, &b_cc_pmt);
   fChain->SetBranchAddress("ech_x", ech_x, &b_ech_x);
   fChain->SetBranchAddress("ech_y", ech_y, &b_ech_y);
   fChain->SetBranchAddress("ech_z", ech_z, &b_ech_z);
   fChain->SetBranchAddress("tl1_x", tl1_x, &b_tl1_x);
   fChain->SetBranchAddress("tl1_y", tl1_y, &b_tl1_y);
   fChain->SetBranchAddress("tl1_z", tl1_z, &b_tl1_z);
   fChain->SetBranchAddress("tl3_x", tl3_x, &b_tl3_x);
   fChain->SetBranchAddress("tl3_y", tl3_y, &b_tl3_y);
   fChain->SetBranchAddress("tl3_z", tl3_z, &b_tl3_z);
   fChain->SetBranchAddress("tl3_cx", tl3_cx, &b_tl3_cx);
   fChain->SetBranchAddress("tl3_cy", tl3_cy, &b_tl3_cy);
   fChain->SetBranchAddress("tl3_cz", tl3_cz, &b_tl3_cz);
   fChain->SetBranchAddress("id", id, &b_id);
   fChain->SetBranchAddress("vx", vx, &b_vx);
   fChain->SetBranchAddress("vy", vy, &b_vy);
   fChain->SetBranchAddress("svicpart", &svicpart, &b_svicpart);
   fChain->SetBranchAddress("xc", xc, &b_xc);
   fChain->SetBranchAddress("yc", yc, &b_yc);
   fChain->SetBranchAddress("etc", etc, &b_etc);
   fChain->SetBranchAddress("ecc", ecc, &b_ecc);
   fChain->SetBranchAddress("tc", tc, &b_tc);
   fChain->SetBranchAddress("nblk", nblk, &b_nblk);
   fChain->SetBranchAddress("ich_x", ich_x, &b_ich_x);
   fChain->SetBranchAddress("ich_y", ich_y, &b_ich_y);
   fChain->SetBranchAddress("et", et, &b_et);
   fChain->SetBranchAddress("egl", egl, &b_egl);
   fChain->SetBranchAddress("ich_xgl", ich_xgl, &b_ich_xgl);
   fChain->SetBranchAddress("ich_ygl", ich_ygl, &b_ich_ygl);
   fChain->SetBranchAddress("rastr1", &rastr1, &b_rastr1);
   fChain->SetBranchAddress("rastr2", &rastr2, &b_rastr2);
   Notify();
}

Bool_t h22::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void h22::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t h22::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef h22_cxx
