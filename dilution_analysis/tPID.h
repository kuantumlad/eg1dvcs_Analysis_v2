//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun  5 15:27:12 2017 by ROOT version 6.08/00
// from TTree tPID/my PID Tree
// found on file: PIDroot22_58800.root
//////////////////////////////////////////////////////////

#ifndef tPID_h
#define tPID_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TString.h"

class tPID {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxt = 1;
   const Int_t kMaxw = 1;
   const Int_t kMaxtp = 1;
   const Int_t kMaxphi = 1;

   // Declaration of leaf types
   Int_t           run;
   TString         *periodID;
   Double_t        beamEnergy;
   Int_t           beamHelicity;
   TString         *targetType;
   Double_t        targetPolarization;
   Double_t        wpstatus;
   Double_t        FC0;
   Double_t        FC1;
   Double_t        el_px;
   Double_t        el_py;
   Double_t        el_pz;
   Double_t        el_E;
   Double_t        el_vertex;
   Int_t           el_DCsect;
   Double_t        el_thetadc;
   Double_t        el_phidc;
   Int_t           el_nphe;
   Double_t        pr_px;
   Double_t        pr_py;
   Double_t        pr_pz;
   Double_t        pr_E;
   Double_t        pr_vertex;
   Int_t           pr_DCsect;
   Double_t        pr_thetadc;
   Double_t        pr_phidc;
   Int_t           pr_nphe;
   Int_t           photonTopology;
   Double_t        ph_px;
   Double_t        ph_py;
   Double_t        ph_pz;
   Double_t        ph_E;
   Double_t        qq;
   Double_t        xb;
   Double_t        t_;
   Double_t        w_;
   Double_t        tp_;
   Double_t        MM;
   Double_t        MM2epg;
   Double_t        eps;
   Double_t        deltatheta;
   Double_t        delta_phi;
   Double_t        phi_;
   Double_t        Dephi;
   Double_t        perpx;
   Double_t        perpy;
   Double_t        pPerp;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_periodID;   //!
   TBranch        *b_beamEnergy;   //!
   TBranch        *b_beamHelicity;   //!
   TBranch        *b_targetType;   //!
   TBranch        *b_targetPolarization;   //!
   TBranch        *b_wpstatus;   //!
   TBranch        *b_FC0;   //!
   TBranch        *b_FC1;   //!
   TBranch        *b_el_px;   //!
   TBranch        *b_el_py;   //!
   TBranch        *b_el_pz;   //!
   TBranch        *b_el_E;   //!
   TBranch        *b_el_vertex;   //!
   TBranch        *b_el_DCsect;   //!
   TBranch        *b_el_thetadc;   //!
   TBranch        *b_el_phidc;   //!
   TBranch        *b_el_nphe;   //!
   TBranch        *b_pr_px;   //!
   TBranch        *b_pr_py;   //!
   TBranch        *b_pr_pz;   //!
   TBranch        *b_pr_E;   //!
   TBranch        *b_pr_vertex;   //!
   TBranch        *b_pr_DCsect;   //!
   TBranch        *b_pr_thetadc;   //!
   TBranch        *b_pr_phidc;   //!
   TBranch        *b_pr_nphe;   //!
   TBranch        *b_photonTopology;   //!
   TBranch        *b_ph_px;   //!
   TBranch        *b_ph_py;   //!
   TBranch        *b_ph_pz;   //!
   TBranch        *b_ph_E;   //!
   TBranch        *b_qq;   //!
   TBranch        *b_xb;   //!
   TBranch        *b_t_;   //!
   TBranch        *b_w_;   //!
   TBranch        *b_tp_;   //!
   TBranch        *b_MM;   //!
   TBranch        *b_MM2epg;   //!
   TBranch        *b_eps;   //!
   TBranch        *b_deltatheta;   //!
   TBranch        *b_delta_phi;   //!
   TBranch        *b_phi_;   //!
   TBranch        *b_Dephi;   //!
   TBranch        *b_perpx;   //!
   TBranch        *b_perpy;   //!
   TBranch        *b_pPerp;   //!

   tPID(TTree *tree=0);
   virtual ~tPID();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tPID_cxx
tPID::tPID(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PIDroot22_58800.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PIDroot22_58800.root");
      }
      f->GetObject("tPID",tree);

   }
   Init(tree);
}

tPID::~tPID()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tPID::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tPID::LoadTree(Long64_t entry)
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

void tPID::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   periodID = 0;
   targetType = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("periodID", &periodID, &b_periodID);
   fChain->SetBranchAddress("beamEnergy", &beamEnergy, &b_beamEnergy);
   fChain->SetBranchAddress("beamHelicity", &beamHelicity, &b_beamHelicity);
   fChain->SetBranchAddress("targetType", &targetType, &b_targetType);
   fChain->SetBranchAddress("targetPolarization", &targetPolarization, &b_targetPolarization);
   fChain->SetBranchAddress("wpstatus", &wpstatus, &b_wpstatus);
   fChain->SetBranchAddress("FC0", &FC0, &b_FC0);
   fChain->SetBranchAddress("FC1", &FC1, &b_FC1);
   fChain->SetBranchAddress("el_px", &el_px, &b_el_px);
   fChain->SetBranchAddress("el_py", &el_py, &b_el_py);
   fChain->SetBranchAddress("el_pz", &el_pz, &b_el_pz);
   fChain->SetBranchAddress("el_E", &el_E, &b_el_E);
   fChain->SetBranchAddress("el_vertex", &el_vertex, &b_el_vertex);
   fChain->SetBranchAddress("el_DCsect", &el_DCsect, &b_el_DCsect);
   fChain->SetBranchAddress("el_thetadc", &el_thetadc, &b_el_thetadc);
   fChain->SetBranchAddress("el_phidc", &el_phidc, &b_el_phidc);
   fChain->SetBranchAddress("el_nphe", &el_nphe, &b_el_nphe);
   fChain->SetBranchAddress("pr_px", &pr_px, &b_pr_px);
   fChain->SetBranchAddress("pr_py", &pr_py, &b_pr_py);
   fChain->SetBranchAddress("pr_pz", &pr_pz, &b_pr_pz);
   fChain->SetBranchAddress("pr_E", &pr_E, &b_pr_E);
   fChain->SetBranchAddress("pr_vertex", &pr_vertex, &b_pr_vertex);
   fChain->SetBranchAddress("pr_DCsect", &pr_DCsect, &b_pr_DCsect);
   fChain->SetBranchAddress("pr_thetadc", &pr_thetadc, &b_pr_thetadc);
   fChain->SetBranchAddress("pr_phidc", &pr_phidc, &b_pr_phidc);
   fChain->SetBranchAddress("pr_nphe", &pr_nphe, &b_pr_nphe);
   fChain->SetBranchAddress("photonTopology", &photonTopology, &b_photonTopology);
   fChain->SetBranchAddress("ph_px", &ph_px, &b_ph_px);
   fChain->SetBranchAddress("ph_py", &ph_py, &b_ph_py);
   fChain->SetBranchAddress("ph_pz", &ph_pz, &b_ph_pz);
   fChain->SetBranchAddress("ph_E", &ph_E, &b_ph_E);
   fChain->SetBranchAddress("qq", &qq, &b_qq);
   fChain->SetBranchAddress("xb", &xb, &b_xb);
   fChain->SetBranchAddress("t_", &t_, &b_t_);
   fChain->SetBranchAddress("w_", &w_, &b_w_);
   fChain->SetBranchAddress("tp_", &tp_, &b_tp_);
   fChain->SetBranchAddress("MM", &MM, &b_MM);
   fChain->SetBranchAddress("MM2epg", &MM2epg, &b_MM2epg);
   fChain->SetBranchAddress("eps", &eps, &b_eps);
   fChain->SetBranchAddress("deltatheta", &deltatheta, &b_deltatheta);
   fChain->SetBranchAddress("delta_phi", &delta_phi, &b_delta_phi);
   fChain->SetBranchAddress("phi_", &phi_, &b_phi_);
   fChain->SetBranchAddress("Dephi", &Dephi, &b_Dephi);
   fChain->SetBranchAddress("perpx", &perpx, &b_perpx);
   fChain->SetBranchAddress("perpy", &perpy, &b_perpy);
   fChain->SetBranchAddress("pPerp", &pPerp, &b_pPerp);
   Notify();
}

Bool_t tPID::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tPID::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tPID::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tPID_cxx
