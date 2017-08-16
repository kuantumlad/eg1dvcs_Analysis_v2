#define calculator_cc

#include "../include/Calculator.h"
#include "../include/RunDB.h"

#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include <iostream>
#include <map>
Calculator::Calculator(){

  //Might neeed to add run dependence here for the target position
  //and momentum corrections
  //eg1rundata.OpenDB();

  //Taken from Andrey Kim's analysis paper (change per Run Part)
  //proton momentum correction parameters
  a = 0.992767;
  b = 0.0146232;
  c = 0.0084665;
  d = 0.0032769;

  //electron momentum correction parameters
  f = 0.9997360;
  g = 0.0105136;
  h = 0.00515416;

  beamEnergy = 0.0;
  icID = 1000;
  ecID = 2000;
  MC = -1;
}



Calculator::Calculator( Int_t temprunnumber ){

  //Taken from Andrey Kim's analysis paper (change per Run Part)
  //proton momentum correction parameters
  a = 0.992767;
  b = 0.0146232;
  c = 0.0084665;
  d = 0.0032769;

  //electron momentum correction parameters
  f = 0.9997360;
  g = 0.0105136;
  h = 0.00515416;

  icID = 1000;
  ecID = 2000;

  float cf = 0.0084665;
  //  std::cout << " float " << cf << std::endl;
  //std::cout << " double " << c << std::endl;
  temprunNumber = temprunnumber;
  MC = -1;

}

//Calculator::~Calculator(){

//}


// Borrowed from Andrey
TVector3 Calculator::ICHitPosition( Int_t temprunnumber, Eventh22 &tempevent, Int_t tempgindex ){

  if( tempevent.q[tempgindex] != 0 ){
    // //DC hit location
    Double_t tlx = tempevent.tl1_x[tempgindex];
    Double_t tly = tempevent.tl1_y[tempgindex];
    Double_t tlz = tempevent.tl1_z[tempgindex];
    Double_t tlcx = tempevent.tl1_cx[tempgindex];
    Double_t tlcy = tempevent.tl1_cy[tempgindex];

    // //Equation of a line to calculate the x,y,z IC locations using the DC hit (tl1_*) and slope (tl1_c*)
    // //DChit.SetXYZ(tlx - tlcx*tlz,
    // //tly - tlcy*tlz,
    // //tlz );
    Double_t icbx = tlx + (16.0 - tlz)*tlcx/(sqrt(1-tlcx*tlcx-tlcy*tlcy));
    Double_t icby = tly + (16.0 - tlz)*tlcy/(sqrt(1-tlcx*tlcx-tlcy*tlcy));    
   
    DChit.SetXYZ( icbx,
		  icby,
		  tlz );
    
    //Shadow Calculations
    TVector3 ICextrapolatedhitcharged = DChit;
    return ICextrapolatedhitcharged;
  }
  //Repeat for neutral particles but with position on EC and nominal vertex position, the target position
  else{
    Double_t *xy_c = RasterCorrection( temprunnumber, tempevent, tempgindex );
    Double_t ec_x = tempevent.ech_x[tempgindex];
    Double_t ec_y = tempevent.ech_y[tempgindex];
    Double_t ec_z = tempevent.ech_z[tempgindex];
    Double_t nomvz = targetPos;//-67.97;//targetPos;
    // DChit.SetXYZ( xy_c[0] + (ec_x - xy_c[0])*(-nomvz/(ec_z  - nomvz)),
    //  		  xy_c[1] + (ec_y - xy_c[1])*(-nomvz/(ec_z  - nomvz)),
    //  		  0);
    // Add correction to the direction cosines. 
    //Double_t *cosine_corr = CosineCorrection( temprunnumber, tempevent, tempgindex );
    //Double_t cx_corr = cosine_corr[0];
    //Double_t cy_corr = cosine_corr[1];
    Double_t Cx = tempevent.cx[tempgindex];
    Double_t Cy = tempevent.cy[tempgindex];
    
    Double_t n_icbx = xy_c[0] + (16.0 - targetPos)*Cx/sqrt(1 - Cx*Cx - Cy*Cy );
    Double_t n_icby = xy_c[1] + (16.0 - targetPos)*Cy/sqrt(1 - Cx*Cx - Cy*Cy );
    DChit.SetXYZ( n_icbx,
		  n_icby,
		  0 ); // 0 because we don't actually care about this component.
    TVector3 ICextrapolatedhitneutral = DChit;
    return ICextrapolatedhitneutral;
  }
				 
}


Double_t Calculator::ElectronCorrectedMntm( Double_t mntm ){//Eventh22 tempevent, Int_t tempgindex ){
  Double_t correctedelectronmomentum = mntm;
  //   std::cout << " run " << run << std::endl;
  // std::cout << " temprunNumber " << temprunNumber << std::endl;
  //std::cout << " original p is - " << mntm << std::endl;
  if( run != MC ){
    //correctedelectronmomentum = mntm*( f + g/mntm - h/(mntm*mntm));
   
    correctedelectronmomentum = mntm*( 0.997360 + 0.0105136/mntm - 0.00515416/(pow(mntm,2)));
    //    std::cout << "Correcting p to - " << correctedelectronmomentum << std::endl;
  }  
  return correctedelectronmomentum;
}

Double_t Calculator::ProtonCorrectedMntm( Double_t mntm ){// Eventh22 tempevent, Int_t tempgindex ){
  Double_t correctedprotonmomentum = mntm;
  //  std::cout <<  run << std::endl;
  //std::cout << " original p is - " << mntm << std::endl;
  if( run != MC ){
    //correctedprotonmomentum = mntm*( a + b/mntm - c/(mntm*mntm) + d/(mntm*mntm*mntm));
    //correctedprotonmomentum = mntm*( a + b/mntm - c/(pow(mntm,2)) + d/(pow(mntm,3)));
        correctedprotonmomentum = mntm*(0.992767 +0.0147232/mntm - 0.0084665/(pow(mntm,2)) + 0.0032769/(pow(mntm,3)) );
	//std::cout << "Correcting p to - " << correctedprotonmomentum << std::endl;
  }
  return correctedprotonmomentum;
}

Double_t *Calculator::PhotonCorrectECEnergy(  Int_t temprunnumber ){
  if ( temprunnumber != MC ){
    ec_sampfact[0] = 0.0;
    ec_sampfact[1] = 0.0;
    ec_sampfact[2] = 0.0;
    ec_sampfact[3] = 0.0;
    ec_sampfact[4] = 0.0;
    ec_sampfact[5] = 0.0;
    //ecenergy_corr[0] = tempevent.etot[tempgindex];
    //ecenergy_corr[1] = tempevent.ec_ei[tempgindex];
    //ecenergy_corr[2] = tempevent.ec_eo[tempgindex];
    
    //if( 0 < tempevent.ec_sect[tempgindex] && tempevent.ec_sect[tempgindex] < 7 ){ 
    string ec_sectorbase("ECSector");
    
    //int ec_sector = tempevent.ec_sect[tempgindex] - 1;
    for( Int_t nn = 0; nn < 6; nn ++ ){
      string s_ec_sector = std::to_string(nn);
      TString s_ec_sect = ec_sectorbase + s_ec_sector;
      string s_ecSector = std::string(s_ec_sect); 
      eg1rundata.OpenDB();
      TString s_ecscalefactor = eg1rundata.Query("ECEnergyCorrection",s_ecSector,temprunnumber );
      eg1rundata.CloseDB();
      
      ecscalefactor = atof(s_ecscalefactor);
      ec_sampfact[nn] = ecscalefactor;
      // if( 0 < tempevent.etot[tempgindex] && tempevent.etot[tempgindex] < 5 ){
      //   Double_t etot_corr = tempevent.etot[tempgindex]*( 0.2765/ecscalefactor );
      //   ecenergy_corr[0] = etot_corr;
      // }
      // if( 0 < tempevent.ec_ei[tempgindex] && tempevent.ec_ei[tempgindex] < 5 ){
      //   Double_t ei_corr = tempevent.ec_ei[tempgindex]*( 0.2765/ecscalefactor );
      //   ecenergy_corr[1] = ei_corr;
      // }
      // if( 0 < tempevent.ec_eo[tempgindex] && tempevent.ec_eo[tempgindex] < 5 ){
      //   Double_t eo_corr = tempevent.ec_eo[tempgindex]*( 0.2765/ecscalefactor );
      //   ecenergy_corr[2] = eo_corr;
      // }
    }
  }
  else if( temprunnumber == MC ){
    ec_sampfact[0] = 1.0;
    ec_sampfact[1] = 1.0;
    ec_sampfact[2] = 1.0;
    ec_sampfact[3] = 1.0;
    ec_sampfact[4] = 1.0;
    ec_sampfact[5] = 1.0;
  } 
  return ec_sampfact;
}


//Double_t *Calculator::BeamCorrection( Int_t run, Int_t rastr1, Int_t rastr2 ){
Double_t *Calculator::RasterCorrection( Int_t run, Eventh22 &tempevent, Int_t index ){
  
  // x and y offsets seem to change from time to time for no
  // apparant reason. Nominal zero of the ADC is 4000, ! so differences
  //from this indicates where the beam ! centroid physically was relative
  //to the magnetic ! center of CLAS. Note: 400 ADC counts is about 1 mm.
  //std::cout << run  << std::endl;
  if ( run != MC ){
    //std::cout << run  << std::endl;

    Double_t rastr1 = tempevent.rastr1;
    Double_t rastr2 = tempevent.rastr2;
    x_off = 3660;
    if(run>=59153) x_off =  3730;
    if(run>=59221) x_off =  3580;
    if(run>=59601) x_off =  3590;
    if(run>=59910) x_off =  3780;
    if(run>=59945) x_off =  3620;
    if(run>=60223) x_off =  3940;
    if(run>=60557) x_off =  3980;
    
    y_off = 4520;
    if(run>=58821) y_off = 4330;
    if(run>=59221) y_off = 4530;
    if(run>=59551) y_off = 4410;
    if(run>=59621) y_off = 4350;
    if(run>=59977) y_off = 3950;
    if(run>=60006) y_off = 4350;
    if(run>=60223) y_off = 3900;
    if(run>=60396) y_off = 3650;
    if(run>=60566) y_off = 3450;
    
    // get gain factors that convert ADC counts to cm
    // Note: these are inversely proportion to beam energy
    // also, get eo and vz at center of target
    
    // start with 5.9 gev
    x_gain =  0.000229;
    y_gain = -0.000250;
    vznom = -57.95;
    eo = 5.885;
    
    // switch to 4.8 gev
    if(run>= 59161){
      x_gain =  0.000284;
      y_gain = -0.000313;
      vznom = -67.97;
      eo = 4.726;
    }
    
    // switch to 5.95 gev
    if(run>= 59221){
      x_gain =  0.000225;
      y_gain = -0.000243;
      vznom = -67.97;
      eo = 5.952;
    }
    
    // switch to 5.7 GeV
    if(run>= 60223){
      x_gain =  0.000239;
      y_gain = -0.000258;
      vznom = -68.18;
      eo = 5.752;
    }
    
    // default
    xy[0] = 0;
    xy[1] = 0;
    
    // values out of range
    if((rastr1>=1500&&rastr1<=10000)||(rastr2>=1500&&rastr2<=10000))
      {   //actually get xr,yr
	
	xy[0] = (rastr1 - x_off) * x_gain;
	xy[1] = (rastr2 - y_off) * y_gain;
	//std::cout<<"sub rater1: "<<xy[0]<<std::endl;
      }
    //return the values of the x and y position of the event in the target
    xy_corr[0] = xy[0];//tempevent.xc[index] - xy[0]; 2-24-2017 
    xy_corr[1] = xy[1];//tempevent.yc[index] - xy[1];
    
  }
  else if ( run == MC ){
    std::cout << "wtf is this printin " << std::endl;
    //Set x and y off/gain to 0 for MC ?
    x_off = 0;
    y_off = 0;
    
    x_gain = 0.0;                                                                                                                                                                                     
    y_gain = 0.0;
    vznom = -67.8;  //double check with silvia                                                                                                                                                                                 
    eo = 5.966;  
    xy_corr[0] = 0.0;//tempevent.xc[index];
    xy_corr[1] = 0.0;//tempevent.yc[index];
    
  }
  return xy_corr;
}

// Borrowed from Silvia
Double_t  *Calculator::CosineCorrection( Int_t temprunnumber, Eventh22 &tempevent, Int_t tempgindex ){
  p_event = tempevent.p[tempgindex] ;
  //  std::cout << " run " << temprunnumber  << std::endl;
  if( temprunnumber != MC ){
    
    xdc = 0; ydc = 0; zdc = 0; cxdc = 0; cydc = 0; vz_cor = 0; //czc=1;
    cosine_corr[0] = 0;
    cosine_corr[1] = 0;
    cosine_corr[2] = 0;
    cosine_corr[3] = 0;
    
    q_event = tempevent.q[tempgindex];
    
    xdc = tempevent.tl1_x[tempgindex];
    ydc = tempevent.tl1_y[tempgindex];
    zdc = tempevent.tl1_z[tempgindex];
    
    cxdc = tempevent.tl1_cx[tempgindex];
    cydc = tempevent.tl1_cy[tempgindex];
    if( p_event>=0.001&&(q_event == 1 || q_event == -1 ) && (pow(cxdc,2) + pow(cydc,2) )< 1 ){
      //if( tempevent.p[tempgindex] > 0.001 && (tempevent.q[tempgindex]==-1 || tempevent.q[tempgindex]==1) && ((tempevent.tl1_cx[tempgindex]*tempevent.tl1_cx[tempgindex] + tempevent.tl1_cy[tempgindex]*tempevent.tl1_cy[tempgindex])<1) ){
      
      // overall integral B*dl correction factor
      // We ran 4.97 T, so "field correction" is 0.995
      fc = 0.995;
      
      // sign of target field compared to simulations
      targsign = -1;
      if(temprunnumber>60222) targsign = 1;
      
      // Get nominal th and phi at DC1 in radians
      czdc2 = 1.0 - cxdc*cxdc - cydc*cydc;
      if(czdc2>0) czdc = sqrt(czdc2);
      else czdc = 0.;
      thf = acos(czdc);
      phif = atan2(cydc, cxdc);
      
      // Get phi0 without raster correction yet
      phi0 = phif + targsign*fc*(0.186 + 0.045*thf*thf + 0.008*thf*thf*thf + 0.0032*thf*thf*thf / pow(p_event,2)) * q_event / p_event  ;
      
      // correction to polar angle from focusing effect
      // first, get focusing term for beam (x,y)=0.
      dth = fc * (0.90*thf + 1.2*thf*thf*thf) / (100.0*p_event*p_event);
      
      // displacement of beam along trajectory (xp) and
      // perpendicular to it (yp)
      Double_t *posrastr = RasterCorrection( temprunnumber, tempevent, tempgindex );
      xp =  (posrastr[0]) * cos(phi0) + (posrastr[1]) * sin(phi0);
      yp = -(posrastr[0]) * sin(phi0) + (posrastr[1]) * cos(phi0);
      
      // correction to dth from radial target field, which
      // only depends on raster x and y but not vertex z
      // Also, no effect on peak at zero!
      dth = dth*(1.0 + targsign * q_event * p_event * (0.5 / thf) * (yp/0.75));
      
      // Now can get cz
      th0 = thf + dth;
      czc = cos(th0);
      
      //Now phi0 again, this time including raster correction
      phi0 = phif + targsign * fc * (0.186 + 0.045*pow(thf,2) + 0.008*pow(thf,3) + 0.0032 * pow(thf,3) / pow(p_event,2)) * q_event / p_event * (1.0 - 0.09 * (0.35/thf) * xp );
      
      // Get cx and cy using this cz
      cxc = sin(th0) * cos(phi0);
      cyc = sin(th0) * sin(phi0);
      
      // renomalize czc
      czc2 = 1 - cxc*cxc - cyc*cyc;
      if(czc2>0) czc = sqrt(czc2);
      else czc = 0;
      // Apply target field rotation correction
      // do I need targsign here????
      cxc = cxc - targsign * q_event * czc * 0.0007 / p_event;
      cyc = cyc + targsign * q_event * czc * 0.0022 / p_event;
      
      // renomalize czc
      
      czc2_rn =  1 - cxc*cxc - cyc*cyc;
      if(czc2_rn>0) czc = sqrt(czc2_rn);
      else czc =0;
      // Get vertex z in cm
      rdc = sqrt(pow(xdc - posrastr[0],2) + pow(ydc - posrastr[1],2));
      vz_cor = zdc - (rdc -  22. * cos(th0) * (tan(th0) - tan(thf))) /tan(thf);
      
      // cx_corr = cxc;
      // cy_corr = cyc;
      // cz_corr = czc;
      // vz_corr = vz_cor;
      // std::cout << cx_corr << " " << cy_corr << " " << cz_corr << " " << vz_corr << std::endl;
      
      cosine_corr[0] = cxc;
      cosine_corr[1] = cyc;
      cosine_corr[2] = czc;
      cosine_corr[3] = vz_cor;
      
    }
  }
  else if (temprunnumber == MC ){
    
    cosine_corr[0] = tempevent.tl1_cx[tempgindex];                                                                                                                                                         
    cosine_corr[1] = tempevent.tl1_cy[tempgindex];  
    cosine_corr[2] = sqrt( 1 - tempevent.tl1_cx[tempgindex]*tempevent.tl1_cx[tempgindex] - tempevent.tl1_cy[tempgindex]*tempevent.tl1_cy[tempgindex]);
    cosine_corr[3] = tempevent.vz[tempgindex];
  }
  return cosine_corr;
  //return 0;
}


//Corrected with momentum corections
Double_t  *Calculator::CorrectedCosineCorrection( Int_t temprunnumber, Eventh22 &tempevent, Int_t tempgindex, Double_t tempcorrectedmomentum ){
  p_event = 0;
  p_event =  tempcorrectedmomentum;
  //std::cout << " temprun " << temprunnumber << " - MC  = " << MC << std::endl;
  if( temprunnumber != MC ){
    
    xdc = 0; ydc = 0; zdc = 0; cxdc = 0; cydc = 0; vz_cor = 0; //czc = 1;
    cosine_corr[0] = 0;
    cosine_corr[1] = 0;
    cosine_corr[2] = 0;
    cosine_corr[3] = 0;
    
    q_event = tempevent.q[tempgindex];
    
    xdc = tempevent.tl1_x[tempgindex];
    ydc = tempevent.tl1_y[tempgindex];
    zdc = tempevent.tl1_z[tempgindex];
    
    cxdc = tempevent.tl1_cx[tempgindex];
    cydc = tempevent.tl1_cy[tempgindex];
    if( p_event>=0.001&&(q_event == 1 || q_event == -1 ) && (pow(cxdc,2) + pow(cydc,2) )< 1 ){
      //if( tempevent.p[tempgindex] > 0.001 && (tempevent.q[tempgindex]==-1 || tempevent.q[tempgindex]==1) && ((tempevent.tl1_cx[tempgindex]*tempevent.tl1_cx[tempgindex] + tempevent.tl1_cy[tempgindex]*tempevent.tl1_cy[tempgindex])<1) ){
      
      // overall integral B*dl correction factor
      // We ran 4.97 T, so "field correction" is 0.995
      fc = 0.995;
      
      // sign of target field compared to simulations
      targsign = -1;
      if(temprunnumber>60222) targsign = 1;
      
      // Get nominal th and phi at DC1 in radians
      // czdc2 = 1. - pow(cxdc,2) - pow(cydc,2);
      czdc2 = 1. - pow(cxdc,2) - pow(cydc,2);
      if(czdc2>0) czdc = sqrt(czdc2);
      else czdc = 0.;
      thf = acos(czdc);
      phif = atan2(cydc, cxdc);
      
      // Get phi0 without raster correction yet
      phi0 = phif + targsign*fc*(0.186 + 0.045*pow(thf,2) + 0.008*pow(thf,3) + 0.0032*pow(thf,3) / pow(p_event,2)) * q_event / p_event  ;
      
      // correction to polar angle from focusing effect
      // first, get focusing term for beam (x,y)=0.
      dth = fc * (0.90*thf + 1.2*pow(thf,3)) / (100*pow(p_event,2));
      
      // displacement of beam along trajectory (xp) and
      // perpendicular to it (yp)
      Double_t *posrastr = RasterCorrection( temprunnumber, tempevent, tempgindex );
      xp =  posrastr[0] * cos(phi0) + posrastr[1] * sin(phi0);
      yp = -posrastr[0] * sin(phi0) + posrastr[1] * cos(phi0);
      
      // correction to dth from radial target field, which
      // only depends on raster x and y but not vertex z
      // Also, no effect on peak at zero!
      dth = dth*(1. + targsign * q_event * p_event * (0.5 / thf) * (yp/0.75));
      
      // Now can get cz
      th0 = thf + dth;
      czc = cos(th0);
      
      //Now phi0 again, this time including raster correction
      phi0 = phif + targsign * fc * (0.186 + 0.045*pow(thf,2) + 0.008*pow(thf,3) + 0.0032 * pow(thf,3) / pow(p_event,2)) * q_event / p_event * (1. - 0.09 * (0.35/thf) * xp );
      
      // Get cx and cy using this cz
      cxc = sin(th0) * cos(phi0);
      cyc = sin(th0) * sin(phi0);
      
      // renomalize czc
      czc2 = 1. - cxc*cxc - cyc*cyc;
      if(czc2>0) czc = sqrt(czc2);
      else czc = 0;
      // Apply target field rotation correction
      // do I need targsign here????
       cxc = cxc - targsign * q_event * czc * 0.0007 / p_event;
       cyc = cyc + targsign * q_event * czc * 0.0022 / p_event;
      
      // renomalize czc
      
      czc2_rn =  1. - pow(cxc,2) - pow(cyc,2);
      if(czc2_rn>0) czc = sqrt(czc2_rn);
      else czc =0;
      // Get vertex z in cm
      rdc = sqrt(pow(xdc - posrastr[0],2) + pow(ydc - posrastr[1],2));
      vz_cor = zdc - (rdc -  22. * cos(th0) * (tan(th0) - tan(thf))) /tan(thf);
      
      // cx_corr = cxc;
      // cy_corr = cyc;
      // cz_corr = czc;
      // vz_corr = vz_cor;
      // std::cout << cx_corr << " " << cy_corr << " " << cz_corr << " " << vz_corr << std::endl;
      
      cosine_corr[0] = cxc;
      cosine_corr[1] = cyc;
      cosine_corr[2] = czc;
      cosine_corr[3] = vz_cor;
      //  std::cout << " post corrected vz " << vz_cor << std::endl;
    }
  }
  else if (temprunnumber == MC ){
    
    cosine_corr[0] = tempevent.tl1_cx[tempgindex];                                                                                                                                                         
    cosine_corr[1] = tempevent.tl1_cy[tempgindex];  
    cosine_corr[2] = sqrt( 1 - tempevent.tl1_cx[tempgindex]*tempevent.tl1_cx[tempgindex] - tempevent.tl1_cy[tempgindex]*tempevent.tl1_cy[tempgindex]);
    cosine_corr[3] = tempevent.vz[tempgindex];
  }
  return cosine_corr;
}


Double_t *Calculator::DVCSCutBounds( Int_t temprunnumber, Int_t phtop ){

  dvcscutarray[0] = 0;
  dvcscutarray[1] = 0;
  dvcscutarray[2] = 0;
  dvcscutarray[3] = 0;
  dvcscutarray[4] = 0;
  dvcscutarray[5] = 0;
  if( temprunnumber != MC ){
   eg1rundata.OpenDB();
   TString s_period = eg1rundata.Query("RunConfiguration","PeriodID",temprunnumber );
   eg1rundata.CloseDB();
  if( phtop == icID ){
    // IC DVCS CUTS
    Amm2max = 0.181;
    Amm2min = -0.167;
    Bmm2max = 0.161;
    Bmm2min = -0.150;

    AgXthetamax = 1.055;
    BgXthetamax = 0.976;

    Adeltaphimax = 1.647;
    Adeltaphimin = -1.773;
    Bdeltaphimax = 1.289;
    Bdeltaphimin = -1.495;

    Amntmperpmax =  0.096;
    Bmntmperpmax = 0.095;
  }
  else if ( phtop == ecID ){

    Amm2max = 0.164;
    Amm2min = -0.105;
    Bmm2max = 0.167;
    Bmm2min = -0.114;

    AgXthetamax = 2.52;
    BgXthetamax = 2.38;

    Adeltaphimax = 1.782;
    Adeltaphimin = -1.686;
    Bdeltaphimax = 1.979;
    Bdeltaphimin = -1.875;

    Amntmperpmax =  0.284;
    Bmntmperpmax = 0.279;
  }
  
  if( s_period == "A" ){
    dvcscutarray[0] = Amm2max;
    dvcscutarray[1] = Amm2min;
    dvcscutarray[2] = AgXthetamax;
    dvcscutarray[3] = Adeltaphimax;
    dvcscutarray[4] = Adeltaphimin;
    dvcscutarray[5] = Amntmperpmax;
    
  }
  if( s_period == "B" ){
    dvcscutarray[0] = Bmm2max;
    dvcscutarray[1] = Bmm2min;
    dvcscutarray[2] = BgXthetamax;
    dvcscutarray[3] = Bdeltaphimax;
    dvcscutarray[4] = Bdeltaphimin;
    dvcscutarray[5] = Bmntmperpmax;
  }
  }
  else if(temprunnumber == MC){
    dvcscutarray[0] = 0.5;                                                                                                                                                                             
    dvcscutarray[1] = -0.5;                                                                                                                                                                             
    dvcscutarray[2] = 2.0;                                                                                                                                                                         
    dvcscutarray[3] = 1.5;                                                                                                                                                                        
    dvcscutarray[4] = -1.5;                                                                                                                                                                        
    dvcscutarray[5] = 0.8;
  }
  return dvcscutarray;
}

TLorentzVector Calculator::BeamEnergyCorrection( Int_t temprun ){
  TLorentzVector beamLV;
  if( temprun != MC ){
  eg1rundata.OpenDB();
  TString s_energy = eg1rundata.Query("GoodRunConfig","BeamEnergy", temprun );
  eg1rundata.CloseDB();
    
  beamEnergy = atof(s_energy);
  beamLV.SetPxPyPzE( 0, 0, beamEnergy, beamEnergy );
  }
  else if( temprun == MC ){
    beamLV.SetPxPyPzE(0, 0, 5.966, 5.966 );
  }
  return beamLV;
}

Double_t Calculator::RadtoDeg(){

  Double_t deg = 180.0/TMath::Pi();

  return deg;
}

void Calculator::SetPhotonTopology( Int_t tempphotondetectorID ){

  photonTopology = tempphotondetectorID;
  
}

TLorentzVector Calculator::ICphoton_LV( Eventh22 &tempevent, Int_t sindex, Int_t temprunnumber ){
  //added changed to this 
  Double_t etc_dep = tempevent.etc[sindex];  
  Double_t z_pos = 0.;
  //removed the calculation using the uncorrected hit position, now accounts for the rastering of the beam
  Double_t el_pcorr = ElectronCorrectedMntm(tempevent.p[tempevent.goldenelectronindex]);
  Double_t *vz_corr_el = CorrectedCosineCorrection( temprunnumber, tempevent, tempevent.goldenelectronindex, el_pcorr );
  Double_t vz_el = vz_corr_el[3];
  z_pos = fabs(vz_corr_el[3]);// fabs(tempevent.vz[tempevent.goldenelectronindex]); //this is the vertex of the event.
  if( tempevent.nproton == 1 ){
    Double_t pr_pcorr = ProtonCorrectedMntm( tempevent.p[tempevent.goldenprotonindex] );
    Double_t *vz_corr_pr = CorrectedCosineCorrection( temprunnumber, tempevent, tempevent.goldenprotonindex, pr_pcorr );
    z_pos = fabs((vz_el + vz_corr_pr[3])/2.);
  }
  /* Variables xx and yy stand for the corrected x and y position
     by taking into account the rastering of the beam across the target.
     xy_c is an array of length two containing the x and y values to correct by
  */
  Double_t *xy_c = RasterCorrection( temprunnumber, tempevent, sindex);
  
  TLorentzVector gmom_temp(0.,0.,0.,0.);
  TVector3 g3mom_temp(0.,0.,0.);

  if( temprunnumber != MC ){
    g3mom_temp.SetXYZ( tempevent.xc[sindex] - xy_c[0], tempevent.yc[sindex] - xy_c[1], z_pos );
  }
  else if ( temprunnumber == MC ){
    g3mom_temp.SetXYZ( tempevent.xc[sindex] - tempevent.mcvx[sindex], tempevent.yc[sindex] - tempevent.mcvy[sindex], z_pos );
  }

  gmom_temp.SetXYZT(etc_dep*(g3mom_temp.Unit()).X(),etc_dep*(g3mom_temp.Unit()).Y(),etc_dep*(g3mom_temp.Unit()).Z(), tempevent.etc[sindex] );

  return gmom_temp;
}

void Calculator::SetFCRunValues( Int_t temprun, std::string tempfilename ){

  if( temprun != MC ){
    eg1rundata.OpenDB();

    TString s_wpposition = eg1rundata.Query("FCWPConfiguration","HalfWP",temprun );
    //std::cout << " hwp " <<  s_wpposition << std::endl;
    //std::cout << "setting fc values " << tempfilename  << std::endl;
    std::string filefordb = "\"" + tempfilename + "\"";
    TString s_fc0 = eg1rundata.Query("GoodFileWithFC","FC0",filefordb,"GoodFileID");
    //std::cout << " fc0 " << s_fc0 << std::endl;
    TString s_fc1 = eg1rundata.Query("GoodFileWithFC","FC1",filefordb,"GoodFileID");
    //std::cout << " fc1 " << s_fc1 << std::endl;
    eg1rundata.CloseDB();
    waveplatePos = atoi(s_wpposition);
    Double_t fc_0temp = atof(s_fc0);
    Double_t fc_1temp = atof(s_fc1);

    if( waveplatePos == 1 ){
      std::cout << " need to change fc0 and fc1 values bc the waveplate is in and flips the helicity " << std::endl;
      fc_0 = fc_1temp;
      fc_1 = fc_0temp;
    }
    else{
      fc_0 = fc_0temp;
      fc_1 = fc_1temp;
    }
    //std::cout << " >> " << fc_0 << " " << fc_1 << std::endl;
  }

}


void Calculator::SetRunParameters( Int_t temprunnumber ){
  //Beam & Target Position Correction
  
  
  if( temprunnumber != MC ){
    eg1rundata.OpenDB();
    TString s_targetType = eg1rundata.Query("TargetConfiguration","Target", temprunnumber );
    
    TString s_energy = eg1rundata.Query("FCWPConfiguration","BeamEnergy", temprunnumber );    
   
    TString s_targetpos = eg1rundata.Query("GoodRunConfig","TargetPosition", temprunnumber );
    
    TString s_targetpolarization = eg1rundata.Query("TargetConfiguration","Polarization", temprunnumber );
    
    TString s_period = eg1rundata.Query("RunConfiguration","PeriodID",temprunnumber );
    
    //TString s_wpposition = eg1rundata.Query("FCWPConfiguration","HalfWP",temprunnumber );
    
    //TString s_fc0 = eg1rundata.Query("FCWPConfiguration","FC0",temprunnumber );
    
    //TString s_fc1 = eg1rundata.Query("FCWPConfiguration","FC1",temprunnumber );
    eg1rundata.CloseDB();
    
    beamEnergy = atof(s_energy);
    targetPos = atof(s_targetpos);
    targetPolarization = atof(s_targetpolarization);
    periodID = s_period;
    run = temprunnumber;
    targetType = s_targetType;
    //waveplatePos = atoi(s_wpposition);
    //fc_0 = atoi(s_fc0);
    //fc_1 = atoi(s_fc1);
    shiftTiming_eccut = -6.0;
    offsetTiming = 0;
    if( s_period == "B" ) {offsetTiming = -0.1446;}
    
    Double_t *ecSF_corr = PhotonCorrectECEnergy( temprunnumber );
    ecSF1 = ecSF_corr[0];
    ecSF2 = ecSF_corr[1];
    ecSF3 = ecSF_corr[2];
    ecSF4 = ecSF_corr[3];
    ecSF5 = ecSF_corr[4];
    ecSF6 = ecSF_corr[5];
  }
  else if( temprunnumber == MC ){
    //Angela's MC values for Beam and Vertex
    // Vertex:
    // 1 - 57.95
    // 2 - 67.97
    // 3 - 68.18
    // Beam:
    // 1 - 5.887
    // 2 - 5.954
    // 3 - 5.752
   
    beamEnergy = 5.887;// atof(s_energy);
    targetPos = -57.95;//atof(s_targetpos);
    targetPolarization = 1;//atof(s_targetpolarization);
    periodID = "MC";//s_period;
    run = temprunnumber;
    targetType = "P";//s_targetType;
    waveplatePos = -1;//atoi(s_wpposition);
    fc_0 = 0;//atoi(s_fc0);
    fc_1 = 0;//atoi(s_fc1);
    shiftTiming_eccut = -6.0;
    offsetTiming = 0.0;// -0.1446;
    //Double_t *ecSF_corr = PhotonCorrectECEnergy( temprunnumber );
    ecSF1 =  0.272;
    ecSF2 =  0.272;//ecSF_corr[1];
    ecSF3 =  0.272;//ecSF_corr[2];
    ecSF4 =  0.272;// ecSF_corr[3];
    ecSF5 =  0.272;//ecSF_corr[4];
    ecSF6 =  0.272;//ecSF_corr[5];
  }
}

//Copy Assignment
Calculator& Calculator::operator= (const Calculator& x ){
  run = x.run;
  beamEnergy = x.beamEnergy;
  targetPos = x.targetPos;
  targetPolarization = x.targetPolarization;
  targetType = x.targetType;
  periodID = x.periodID;
  photonTopology = x.photonTopology;
  waveplatePos = x.waveplatePos;
  fc_0 = x.fc_0;
  fc_1 = x.fc_1;
  vznom = x.vznom;
  eo = x.eo;
  x_off = x.x_off;
  y_off = x.y_off;
  x_gain = x.x_gain;
  y_gain = x.y_gain;
  xy[0] = x.xy[0];
  xy[1] = x.xy[1];
  //  cosine_corr[0] = x.cosine_corr[0];
  // cosine_corr[1] = x.cosine_corr[1];
  //cosine_corr[2] = x.cosine_corr[2];
  //cosine_corr[3] = x.cosine_corr[3];
  shiftTiming_eccut = x.shiftTiming_eccut;
  offsetTiming = x.offsetTiming;
  // ec_sampfact[0] = x.ec_sampfact[0];
  // ec_sampfact[1] = x.ec_sampfact[1];
  // ec_sampfact[2] = x.ec_sampfact[2];
  // ec_sampfact[3] = x.ec_sampfact[3];
  // ec_sampfact[4] = x.ec_sampfact[4];
  // ec_sampfact[5] = x.ec_sampfact[5];
  ecSF1 = x.ecSF1;
  ecSF2 = x.ecSF2;
  ecSF3 = x.ecSF3;
  ecSF4 = x.ecSF4;
  ecSF5 = x.ecSF5;
  ecSF6 = x.ecSF6;  
  return *this;
}

Calculator::Calculator (const Calculator& x){
  run = x.run;
  beamEnergy = x.beamEnergy;
  targetPos = x.targetPos;
  targetPolarization = x.targetPolarization;
  targetType = x.targetType;
  periodID = x.periodID;
  photonTopology = x.photonTopology;
  waveplatePos = x.waveplatePos;
  fc_0 = x.fc_0;
  fc_1 = x.fc_1;
  vznom = x.vznom;
  eo = x.eo;
  x_off = x.x_off;
  y_off = x.y_off;
  x_gain = x.x_gain;
  y_gain = x.y_gain;
  xy[0] = x.xy[0];
  xy[1] = x.xy[1];
  // cosine_corr[0] = x.cosine_corr[0];
  // cosine_corr[1] = x.cosine_corr[1];
  // cosine_corr[2] = x.cosine_corr[2];
  //cosine_corr[3] = x.cosine_corr[3];
  shiftTiming_eccut = x.shiftTiming_eccut;
  offsetTiming = x.offsetTiming;
  // ec_sampfact[0] = x.ec_sampfact[0];
  // ec_sampfact[1] = x.ec_sampfact[1];
  // ec_sampfact[2] = x.ec_sampfact[2];
  // ec_sampfact[3] = x.ec_sampfact[3];
  // ec_sampfact[4] = x.ec_sampfact[4];
  // ec_sampfact[5] = x.ec_sampfact[5];
  ecSF1 = x.ecSF1;
  ecSF2 = x.ecSF2;
  ecSF3 = x.ecSF3;
  ecSF4 = x.ecSF4;
  ecSF5 = x.ecSF5;
  ecSF6 = x.ecSF6; 
}

void Calculator::StorePhotons( Eventh22 &event, Int_t index, Int_t hitloc, Int_t run ){
  // Stores the hit location and LV (corrected) for each photon hit
  TLorentzVector tempLV(0,0,0,0);
  TVector3 tempv3(0,0,0);
  //Take the starting positin as the average position of the electron and proton
  Double_t z_pos = 0.;
  Double_t vz_corr_e = 0.;
  Double_t vz_corr_pro = 0.; 
  if( event.nelectron == 1 ) { //std::cout << " 1 el " << std::endl;
  Double_t el_pcorr = ElectronCorrectedMntm(event.p[event.goldenelectronindex]);
  Double_t *vz_corr_el = CorrectedCosineCorrection( run, event, event.goldenelectronindex, el_pcorr );
  z_pos = fabs(vz_corr_el[3]);// fabs(tempevent.vz[tempevent.goldenelectronindex]); //this is the vertex of the event.
  //if( hitloc == 2 ) std::cout<< " using " << z_pos << std::endl;
  vz_corr_e = vz_corr_el[3];
  }
  if( event.nproton == 1 ){
    Double_t pr_pcorr = ProtonCorrectedMntm( event.p[event.goldenprotonindex] );
    // std::cout << " one proton here " << std::endl;
    Double_t *vz_corr_pr = CorrectedCosineCorrection( run, event, event.goldenprotonindex, pr_pcorr );
    vz_corr_pro = vz_corr_pr[3];
    z_pos = fabs((vz_corr_e + vz_corr_pr[3])/2.);
  }
  //  std::cout << " z pos " << z_pos << std::endl;
  

  Double_t *xy_c = RasterCorrection( run, event, index);
  

  // This Line is responsible for the time crunch 
  //  Double_t *ecSF = PhotonCorrectECEnergy( run );  
  Double_t ecSF[6] = {0.2,0.2,0.2,0.2,0.2,0.2};
  //  std::cout << " -- " << ecSF1 << std::endl;
  if( hitloc == 2 ){
    Double_t etot_corr = event.etot[index];
    Double_t ei_corr = event.ec_ei[index];
    Double_t eo_corr = event.ec_eo[index];
    Int_t ecsector = event.ec_sect[index];
    
    if( 0 < ecsector && ecsector < 7 ){
      if( ecsector == 1 ) ecscalefactor = ecSF1;//[0];
      if( ecsector == 2 ) ecscalefactor = ecSF2;//[1];
      if( ecsector == 3 ) ecscalefactor = ecSF3;//[2];
      if( ecsector == 4 ) ecscalefactor = ecSF4;//[3];
      if( ecsector == 5 ) ecscalefactor = ecSF5;//[4];
      if( ecsector == 6 ) ecscalefactor = ecSF6;//[5];
      //  std::cout << " The scalefactor is " << ecscalefactor << std::endl;
    }
    if( 0 < event.etot[index] &&  event.etot[index] < 5 ){
      etot_corr = event.etot[index]*( 0.2765/ecscalefactor );
    }
    if( 0 < event.ec_ei[index] && event.ec_ei[index] < 5 ){
      ei_corr = event.ec_ei[index]*( 0.2765/ecscalefactor );
    }
    if( 0 < event.ec_eo[index] && event.ec_eo[index] < 5 ){
      eo_corr = event.ec_eo[index]*( 0.2765/ecscalefactor );
    }
    Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);
  
    Double_t energygamma=ecmax/0.2765;                                                                                                                                           
  
    if( run != MC ){
    tempv3.SetXYZ( event.ech_x[index] - xy_c[0], event.ech_y[index] - xy_c[1], event.ech_z[index] - z_pos );
    }
    else if ( run == MC ){
      tempv3.SetXYZ( event.ech_x[index] - event.mcvx[index], event.ech_y[index] - event.mcvy[index], event.ech_z[index] - z_pos );
    }             
    // std::cout << " Z of photon " << (tempv3.Unit()).Z() << std::endl;
    //std::cout << " Z of photon with minus " << -(tempv3.Unit()).Z() << std::endl;
    tempLV.SetXYZM( energygamma*(tempv3.Unit()).X(), energygamma*(tempv3.Unit()).Y(), energygamma*(tempv3.Unit()).Z(), 0 );
  }
  else if( hitloc == 1 ){
    if( run != MC ){
      tempv3.SetXYZ( event.xc[index] - xy_c[0], event.yc[index] - xy_c[1], z_pos );
    }
    else if ( run == MC ){
      tempv3.SetXYZ( event.xc[index] - event.mcvx[index], event.yc[index] - tempevent.mcvy[index], z_pos );
    }
    tempLV.SetXYZT( event.etc[index]*(tempv3.Unit()).X(), event.etc[index]*(tempv3.Unit()).Y(), event.etc[index]*(tempv3.Unit()).Z(), event.etc[index] );
 }
 
  photonLV.push_back(tempLV);
  photonhitlocation.push_back(hitloc);
  
  // std::cout << " size of photonlv " << photonLV.size() <<  " energy of " << tempLV.E() << std::endl;
  //std::cout << " size of photonhitlocation " << photonhitlocation.size() << " hit location is " << hitloc << std::endl; 
}

void Calculator::mostEnergeticPhoton( std::map< Int_t, TLorentzVector>& photonMap ){
  // std::cout << " Finding most energetic photon now " << std::endl;
  std::vector<TLorentzVector>::iterator it, ret;
  std::vector<Int_t>::iterator ithitloc, rethitloc;
  if( photonLV.size() != 0 && photonhitlocation.size() != 0 ){ 
  ret = photonLV.begin();
  ithitloc = rethitloc = photonhitlocation.begin();
  for( it = photonLV.begin(); it != photonLV.end(); ++it ){
    if( it->E() > ret->E() ){
      ret = it;
      rethitloc = ithitloc;
    }
    ++ithitloc;
  }
  //  std::cout << " Chosen photon is from " << *rethitloc << " energy " << ret->E() << std::endl;
    photonMap[*rethitloc] = *ret;
    //    std::cout << " most energetic photon " <<  ret->Z() << std::endl;
  }
}

void Calculator::ClearPhotonVector(){

  photonLV.clear();
  photonhitlocation.clear();

}

Double_t *Calculator::ECSFCorrection( Eventh22 &event, Int_t index, Int_t run ) {
  
  ec_sfall[0] =0;
  ec_sfall[1] =0;
  ec_sfall[2] =0;
  ec_sfall[3] =0;

  Double_t etot_corr = event.etot[index];
  Double_t ei_corr = event.ec_ei[index];
  Double_t eo_corr = event.ec_eo[index];
  Int_t ecsector = event.ec_sect[index];
  Double_t Ecscalefactor = 0.2765;

  Double_t *ecSF_corr = PhotonCorrectECEnergy( run );

  if( 0 < ecsector && ecsector < 7 ){
    if( ecsector == 1 ) Ecscalefactor = ecSF_corr[0];
    if( ecsector == 2 ) Ecscalefactor = ecSF_corr[1];
    if( ecsector == 3 ) Ecscalefactor = ecSF_corr[2];
    if( ecsector == 4 ) Ecscalefactor = ecSF_corr[3];
    if( ecsector == 5 ) Ecscalefactor = ecSF_corr[4];
    if( ecsector == 6 ) Ecscalefactor = ecSF_corr[5];
   
  }
  //  std::cout << " The scalefactor is " << Ecscalefactor << std::endl;
  
 if( 0 < event.etot[index] &&  event.etot[index] < 5 ){
    etot_corr = event.etot[index]*( 0.2765/Ecscalefactor );
  }
  if( 0 < event.ec_ei[index] && event.ec_ei[index] < 5 ){
    ei_corr = event.ec_ei[index]*( 0.2765/Ecscalefactor );
  }
  if( 0 < event.ec_eo[index] && event.ec_eo[index] < 5 ){
    eo_corr = event.ec_eo[index]*( 0.2765/Ecscalefactor );
  }
  Double_t ecmax = (etot_corr>ei_corr+eo_corr?etot_corr:ei_corr+eo_corr);

  ec_sfall[0] = ei_corr;
  ec_sfall[1] = eo_corr;
  ec_sfall[2] = etot_corr;
  ec_sfall[3] = ecmax;


  //  std::cout << ec_sfall[0] <<  ec_sfall[1] <<  ec_sfall[2] <<  ec_sfall[3] << std::endl; 
  return ec_sfall;
 
}

void Calculator::PrintRunInformation(){
  std::cout << " >>>>>>>>>>>>>> RUN " << run << " INFORMATION <<<<<<<<<<<< " << std::endl;
  std::cout << " Run - " << run << std::endl;
  std::cout << " Period ID - " << periodID << std::endl;
  std::cout << " Beam Energy - " << beamEnergy << std::endl;
  std::cout << " Target Type - " << targetType << std::endl;
  std::cout << " Target Position - " << targetPos << std::endl;
  std::cout << " Target Polarization - " << targetPolarization << std::endl;
  std::cout << " Waveplate Position - " << waveplatePos << std::endl;
  std::cout << " FC 0 - " << fc_0 << std::endl;
  std::cout << " FC 1 - " << fc_1 << std::endl;
  //std::cout << " X off - " << x_off << std::endl;
  //std::cout << " Y off - " << y_off << std::endl;
  //std::cout << " X gain - " << x_gain << std::endl;
  //std::cout << " Y gain - " << y_gain << std::endl;
  std::cout << " Shift Timing - " << shiftTiming_eccut << std::endl;
  std::cout << " Offset Timing - " << offsetTiming << std::endl;
  std::cout << " ECSF 1 - " << ecSF1  << std::endl;
  std::cout << " ECSF 2 - " << ecSF2  << std::endl;
  std::cout << " ECSF 3 - " << ecSF3  << std::endl;
  std::cout << " ECSF 4 - " << ecSF4  << std::endl;
  std::cout << " ECSF 5 - " << ecSF5  << std::endl;
  std::cout << " ECSF 6 - " << ecSF6  << std::endl;

}


  


