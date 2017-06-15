//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 24 22:22:06 2017 by ROOT version 6.08/00
// from TTree tDVCS/my final DVCS Event Tree
// found on file: h_eg1_groupB.root
//////////////////////////////////////////////////////////

#ifndef tDVCS_h
#define tDVCS_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TString.h"

class tDVCS {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           RunNumber;
   TString         *PeriodID;
   TString         *TargetType;
   Int_t           pol_sign;
   Int_t           wp_status;
   Int_t           fc0;
   Int_t           fc1;
   Double_t        b_energy;
   Int_t           helicity;
   Float_t         TarPol;
   Float_t         Q2;
   Float_t         Xbj;
   Float_t         W;
   Float_t         t_Pr;
   Float_t         t_Ph;
   Float_t         Phi_Pr_Asym;
   Float_t         Delta_phi;
   Float_t         Phi;
   Float_t         AngleXg;
   Float_t         Xbal;
   Float_t         Ybal;
   Float_t         Ebal;
   Float_t         mm2_epg;
   Float_t         mm;
   Float_t         fel_px;
   Float_t         fel_py;
   Float_t         fel_pz;
   Float_t         fel_E;
   Float_t         fel_vz;
   Float_t         fel_thetadc;
   Float_t         fel_dcsect;
   Float_t         fpr_px;
   Float_t         fpr_py;
   Float_t         fpr_pz;
   Float_t         fpr_E;
   Float_t         fpr_vz;
   Float_t         fpr_thetadc;
   Float_t         fpr_dcsect;
   Float_t         fph_px;
   Float_t         fph_py;
   Float_t         fph_pz;
   Float_t         fph_E;
   Int_t           fph_ID;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_PeriodID;   //!
   TBranch        *b_TargetType;   //!
   TBranch        *b_pol_sign;   //!
   TBranch        *b_wp_status;   //!
   TBranch        *b_fc0;   //!
   TBranch        *b_fc1;   //!
   TBranch        *b_b_energy;   //!
   TBranch        *b_helicity;   //!
   TBranch        *b_TarPol;   //!
   TBranch        *b_Q2;   //!
   TBranch        *b_Xbj;   //!
   TBranch        *b_W;   //!
   TBranch        *b_t_Pr;   //!
   TBranch        *b_t_Ph;   //!
   TBranch        *b_Phi_Pr_Asym;   //!
   TBranch        *b_Delta_phi;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_AngleXg;   //!
   TBranch        *b_Xbal;   //!
   TBranch        *b_Ybal;   //!
   TBranch        *b_Ebal;   //!
   TBranch        *b_mm2_epg;   //!
   TBranch        *b_mm;   //!
   TBranch        *b_fel_px;   //!
   TBranch        *b_fel_py;   //!
   TBranch        *b_fel_pz;   //!
   TBranch        *b_fel_E;   //!
   TBranch        *b_fel_vz;   //!
   TBranch        *b_fel_thetadc;   //!
   TBranch        *b_fel_dcsect;   //!
   TBranch        *b_fpr_px;   //!
   TBranch        *b_fpr_py;   //!
   TBranch        *b_fpr_pz;   //!
   TBranch        *b_fpr_E;   //!
   TBranch        *b_fpr_vz;   //!
   TBranch        *b_fpr_thetadc;   //!
   TBranch        *b_fpr_dcsect;   //!
   TBranch        *b_fph_px;   //!
   TBranch        *b_fph_py;   //!
   TBranch        *b_fph_pz;   //!
   TBranch        *b_fph_E;   //!
   TBranch        *b_fph_ID;   //!

   tDVCS(TTree *tree=0);
   virtual ~tDVCS();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tDVCS_cxx
tDVCS::tDVCS(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("h_eg1_groupB.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("h_eg1_groupB.root");
      }
      f->GetObject("tDVCS",tree);

   }
   Init(tree);
}

tDVCS::~tDVCS()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tDVCS::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tDVCS::LoadTree(Long64_t entry)
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

void tDVCS::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   PeriodID = 0;
   TargetType = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("PeriodID", &PeriodID, &b_PeriodID);
   fChain->SetBranchAddress("TargetType", &TargetType, &b_TargetType);
   fChain->SetBranchAddress("pol_sign", &pol_sign, &b_pol_sign);
   fChain->SetBranchAddress("wp_status", &wp_status, &b_wp_status);
   fChain->SetBranchAddress("fc0", &fc0, &b_fc0);
   fChain->SetBranchAddress("fc1", &fc1, &b_fc1);
   fChain->SetBranchAddress("b_energy", &b_energy, &b_b_energy);
   fChain->SetBranchAddress("helicity", &helicity, &b_helicity);
   fChain->SetBranchAddress("TarPol", &TarPol, &b_TarPol);
   fChain->SetBranchAddress("Q2", &Q2, &b_Q2);
   fChain->SetBranchAddress("Xbj", &Xbj, &b_Xbj);
   fChain->SetBranchAddress("W", &W, &b_W);
   fChain->SetBranchAddress("t_Pr", &t_Pr, &b_t_Pr);
   fChain->SetBranchAddress("t_Ph", &t_Ph, &b_t_Ph);
   fChain->SetBranchAddress("Phi_Pr_Asym", &Phi_Pr_Asym, &b_Phi_Pr_Asym);
   fChain->SetBranchAddress("Delta_phi", &Delta_phi, &b_Delta_phi);
   fChain->SetBranchAddress("Phi", &Phi, &b_Phi);
   fChain->SetBranchAddress("AngleXg", &AngleXg, &b_AngleXg);
   fChain->SetBranchAddress("Xbal", &Xbal, &b_Xbal);
   fChain->SetBranchAddress("Ybal", &Ybal, &b_Ybal);
   fChain->SetBranchAddress("Ebal", &Ebal, &b_Ebal);
   fChain->SetBranchAddress("mm2_epg", &mm2_epg, &b_mm2_epg);
   fChain->SetBranchAddress("mm", &mm, &b_mm);
   fChain->SetBranchAddress("fel_px", &fel_px, &b_fel_px);
   fChain->SetBranchAddress("fel_py", &fel_py, &b_fel_py);
   fChain->SetBranchAddress("fel_pz", &fel_pz, &b_fel_pz);
   fChain->SetBranchAddress("fel_E", &fel_E, &b_fel_E);
   fChain->SetBranchAddress("fel_vz", &fel_vz, &b_fel_vz);
   fChain->SetBranchAddress("fel_thetadc", &fel_thetadc, &b_fel_thetadc);
   fChain->SetBranchAddress("fel_dcsect", &fel_dcsect, &b_fel_dcsect);
   fChain->SetBranchAddress("fpr_px", &fpr_px, &b_fpr_px);
   fChain->SetBranchAddress("fpr_py", &fpr_py, &b_fpr_py);
   fChain->SetBranchAddress("fpr_pz", &fpr_pz, &b_fpr_pz);
   fChain->SetBranchAddress("fpr_E", &fpr_E, &b_fpr_E);
   fChain->SetBranchAddress("fpr_vz", &fpr_vz, &b_fpr_vz);
   fChain->SetBranchAddress("fpr_thetadc", &fpr_thetadc, &b_fpr_thetadc);
   fChain->SetBranchAddress("fpr_dcsect", &fpr_dcsect, &b_fpr_dcsect);
   fChain->SetBranchAddress("fph_px", &fph_px, &b_fph_px);
   fChain->SetBranchAddress("fph_py", &fph_py, &b_fph_py);
   fChain->SetBranchAddress("fph_pz", &fph_pz, &b_fph_pz);
   fChain->SetBranchAddress("fph_E", &fph_E, &b_fph_E);
   fChain->SetBranchAddress("fph_ID", &fph_ID, &b_fph_ID);
   Notify();
}

Bool_t tDVCS::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tDVCS::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tDVCS::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tDVCS_cxx
