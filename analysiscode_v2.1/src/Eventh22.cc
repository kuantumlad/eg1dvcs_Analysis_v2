#define eventh22_cxx
#include "../include/Eventh22.h"
#include <iostream>

Eventh22::Eventh22(){
  //Hello there
  goldenelectronindex = -1;
  goldenprotonindex = -1;
  goldenecphotonindex = -1;


};

Eventh22::~Eventh22(){

};


void Eventh22::SetGoldenElectronIndex( Int_t tempindex ){

  goldenelectronindex = tempindex;
 
}

void Eventh22::SetGoldenProtonIndex( Int_t tempindex ){

  goldenprotonindex = tempindex;

}

void Eventh22::SetGoldenECPhotonIndex( Int_t tempindex ){

  goldenecphotonindex = tempindex;

}

void Eventh22::SetNumGoodElectron( Int_t tempnel ){

  nelectron = tempnel;

}

void Eventh22::SetNumGoodProton( Int_t tempnprot ){

  nproton = tempnprot;

}


void Eventh22::SetNumGoodPhotons(Int_t tempgoodphot, Int_t detector ){

  if( detector == 2 ){ necph = tempgoodphot; }
  else if ( detector == 1 ){ nicph = tempgoodphot; }
  //  else if ( tempgoodphot == -1 && detector == 3 ){ necicph = necph + nicph; }


}

void Eventh22::ChosenPhoton( Int_t tempdetectorID, TLorentzVector tempLV ){

  phdetectorID = tempdetectorID;
  ph_LV = tempLV;
  //  std::cout << "chosen photon Z " << ph_LV.Z() << std::endl;
  //std::cout << " Momentum pz of photon " << ph_LV.Pz() <<std::endl;
}

void Eventh22::ClearCountersNIndices(){

  nelectron = 0;
  nproton = 0;
  necph = 0;
  nicph = 0;
  phdetectorID = 0;
  ph_LV.SetXYZM(0,0,0,0);
  goldenelectronindex = -1;
  goldenprotonindex = -1;
  goldenecphotonindex = -1;
    

}
