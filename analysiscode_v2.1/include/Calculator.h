#ifndef calculator_h
#define calculator_h

#include "Eventh22.h"
#include "RunDB.h"

#include "TVector3.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include <map>

/* Class is responsible for basic geometrical calculations and setting run config parameters such as target position and beam energy.
Techinically, this class should be broken into two: geometrical cal and set run parameters. But too lazy to do this now. 
*/

class Calculator{

 public:
  Eventh22 tempevent;
  RunDB eg1rundata;
  Int_t MC;
  Int_t temprunNumber;
 public:
  Calculator();
  Calculator( Int_t );
  ~Calculator(){ delete [] xy; }
  Calculator& operator= (const Calculator& x );
  Calculator (const Calculator& x);

 public:
  Int_t KeepElectronIndex( Int_t );
  TVector3 ICHitPosition( Int_t, Eventh22 &, Int_t );
  Double_t ProtonCorrectedMntm( Double_t ); //Eventh22, Int_t );
  Double_t ElectronCorrectedMntm( Double_t );//Eventh22, Int_t );
  Double_t *PhotonCorrectECEnergy( Int_t );
  Double_t *RasterCorrection( Int_t, Eventh22 &, Int_t );
  Double_t *CosineCorrection( Int_t, Eventh22 &, Int_t );//Double_t, Double_t );
  Double_t *CorrectedCosineCorrection( Int_t, Eventh22 &, Int_t, Double_t );
  float *CorrectedCosineCorrectionf( Int_t, Eventh22 &, Int_t, Double_t );
  Double_t *DVCSCutBounds( Int_t, Int_t );
  TLorentzVector BeamEnergyCorrection( Int_t );
  Double_t TargetCorrection( Int_t );
  Double_t RadtoDeg();
  TLorentzVector ICphoton_LV( Eventh22 &, Int_t, Int_t );
  void SetFCRunValues( Int_t,  std::string );
  void SetRunParameters(Int_t);
  void StorePhotons( Eventh22 &, Int_t, Int_t, Int_t );
  void mostEnergeticPhoton( std::map< Int_t, TLorentzVector>& );
  void ClearPhotonVector();
  Double_t *ECSFCorrection( Eventh22 &, Int_t, Int_t );

  void SetPhotonTopology( Int_t );
  void SetGoodElectronIndex( Int_t );
  Int_t GetGoodElectronIndex();
  void OpenRunInfo( ) { eg1rundata.OpenDB(); }
  void Kinematics( Eventh22 &, Int_t );
  void TestMethod();
  void PrintRunInformation();
  
  //Parameters for the function used to correct the momentum for
  //proton - a, b, c, d
  //electron - e, f, g
 public:
  Double_t a, b, c, d, f, g, h;
  Int_t icID, ecID;

  std::vector<TLorentzVector> photonLV;
  std::vector<Int_t> photonhitlocation;
  
 public:
  Double_t vznom;
  Double_t eo;
  Double_t x_off;
  Double_t y_off;
  Double_t x_gain;
  Double_t y_gain;
  Double_t *xy = new Double_t[2];
  Double_t *xy_corr = new Double_t[2];

 public:
  Double_t *ec_sampfact = new Double_t[6];
  Double_t ecSF1, ecSF2, ecSF3, ecSF4, ecSF5, ecSF6;
  Double_t *ec_sfall = new Double_t[4];
 public:
  Int_t targsign;
  Double_t fc;
  Double_t thf;
  Double_t phif;
  Double_t phi0;
  Double_t dth;
  Double_t th0;
  Double_t rdc;
  Double_t vz_cor;
  Double_t xp, yp;
  Double_t czdc2, czdc, czc, czc2, czc2_rn;
  Double_t cxdc, cydc, cxc, cyc;
  Double_t xdc, ydc, zdc;
  Double_t *posrastr[2];
  Double_t p_event;
  Int_t q_event;
  //Double_t cx_corr, cy_corr, cz_corr, vz_corr;
  Double_t *cosine_corr = new Double_t[4];

 public:
  Double_t beamEnergy;
  Double_t targetPos;
  Double_t targetPolarization;
  TString targetType;
  Int_t run;
  TString periodID;
  Int_t photonTopology;
  Int_t goodelectronindex;
  Int_t waveplatePos;
  Int_t fc_0;
  Int_t fc_1;
  Double_t shiftTiming_eccut;
  Double_t offsetTiming;
  Double_t ecscalefactor;
  
  // Double_t 
  //Double_t PtPOS;
  //Double_t PtNEG;
  TVector3 DChit;


 public:
  Double_t Amm2max;
  Double_t Amm2min;
  Double_t Bmm2max;
  Double_t Bmm2min;

  Double_t AgXthetamax;
  Double_t BgXthetamax;

  Double_t Adeltaphimax;
  Double_t Adeltaphimin;
  Double_t Bdeltaphimax;
  Double_t Bdeltaphimin;

  Double_t Amntmperpmax;
  Double_t Bmntmperpmax;
  
  Double_t *dvcscutarray = new Double_t[6];
  
};

#endif

  
