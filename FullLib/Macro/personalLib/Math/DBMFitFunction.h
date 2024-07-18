#include <vector>
#include <typeinfo>
#include <algorithm>
#include <TMath.h>
#include <TRandom.h>
#include <TF1.h>
#include "./DBMConT.h"
using namespace TMath;

Double_t Line2Dfun(Double_t *x, Double_t *par) {
  double xx = x[0];
  double slope = par[0];//Scale = Area
  double ofset = par[1];//Most Probable Value

  return xx*slope + ofset;
}



Double_t langaufun(Double_t *x, Double_t *par) {
   //Fit parameters:
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation), 
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.
  // Numeric constants
  // Control constants
  Double_t np = 100.0;      // number of convolution steps
  Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas
  // Variables
  Double_t xx;
  Double_t mpc;
  Double_t fland;
  Double_t sum = 0.0;
  Double_t xlow,xupp;
  Double_t step;
  Double_t i;

  // MP shift correction
  mpc = par[1] - LD_mpshift * par[0]; 

  // Range of convolution integral
  xlow = x[0] - sc * par[3];
  xupp = x[0] + sc * par[3];

  step = (xupp-xlow) / np;

  // Convolution integral of Landau and Gaussian by sum
  for(i=1.0; i<=np/2; i++) {
     xx = xlow + (i-.5) * step;
     fland = TMath::Landau(xx,mpc,par[0]) / par[0];
     sum += fland * TMath::Gaus(x[0],xx,par[3]);

     xx = xupp - (i-.5) * step;
     fland = TMath::Landau(xx,mpc,par[0]) / par[0];
     sum += fland * TMath::Gaus(x[0],xx,par[3]);
  }
  return (par[2] * step * sum * invsq2pi / par[3]);
}

Double_t landaufun(Double_t *x, Double_t *par) {
  double xx = x[0];
  double Sca = par[0];//Scale = Area
  double Mpv = par[1];//Most Probable Value
  double Sig = par[2];//Sigma
  return invsq2pi*Sca*exp(-(((xx+1)-Mpv)/Sig+exp(-(xx+1)+Mpv)/Sig)/2.);
}
TString landaufun(TF1 *TF1Object){
  TF1Object->SetParNames(
    "LSca","LMPV","LSig"
  );
  return "Pars:\tLSca\tLMPV\tLSig";
}

Double_t gaussifun(Double_t *x, Double_t *par) {
  double xx = x[0];
  double Sca = par[0];//Scale = Area
  double Mpv = par[1];//Most Probable Value
  double Sig = par[2];//Sigma
  return invsq2pi*Sca*exp(-(pow((xx-Mpv)/Sig,2))/2.);
}

Double_t HitFitFun_85(Double_t *x, Double_t *par){//Landau + Gaussian
  double xx = x[0];
  double   parL [3]={par[0],par[1],par[2]};
  double   parG [3]={par[3],par[4],par[5]};
  Double_t xTCut =par[6];
  double   decrease ;//= 1./(1.0*int(xTCut-xx));
  if (xx<0) decrease = 0;
  else if (xx<xTCut) decrease = pow(sin(xx/0.8/xTCut),2);
  else               decrease = 1.;
  
  
  return (landaufun(x,parL) + gaussifun(x,parG))*decrease;
}
TString HitFitFun_85(TF1 *TF1Object){
  TF1Object->SetParNames(
    "LSca","LMPV","LSig",
    "GSca","GMpv","GSig",
    "xTCut"
  );
  return "Pars:\tLSca\tLMPV\tLSig\tGSca\tGMpv\tGSig\txTCut";
}
Double_t HitFitFun_0(Double_t *x, Double_t *par){//Landau + Gaussian
  double xx = x[0];
  double   parL1 [3]={par[0],par[1],par[2]};
  double   parL2 [3]={par[3],par[4],par[5]};
  Double_t xTCut =par[6];
  return (landaufun(x,parL1) + landaufun(x,parL2))*((xx-xTCut)>0);
}
TString HitFitFun_0(TF1 *TF1Object){
  TF1Object->SetParNames(
    "L1Sca","L1MPV","L1Sig",
    "L2Sca","L2MPV","L2Sig",
    "xTCut"
  );
  return "Pars:\tL1Sca\tL1MPV\tL1Sig\tL2Sca\tL2MPV\tL2Sig\txTCut";
}
  
Double_t N_HitFitFun_0(Double_t *x, Double_t *par){
  double xx = x[0];
  double   parL [3]={par[0],par[1],par[2]};
  double   parLG[4]={par[3],par[4],par[5],par[6]};
  Double_t xTCut =par[7];
  return (landaufun(x,parL) + langaufun(x,parLG))*((xx-xTCut)>0);
}
TString N_HitFitFun_0(TF1 *TF1Object){
  TF1Object->SetParNames(
    "LSca","LMPV","LSig",
    "LGSca","LGMPV","LGAre","LGSig",
    "xTCut"
  );
  return "Pars:\tLSca\tLMPV\tLSig\tLGSca\tLGMPV\tLGAre\tLGSig\txTCut";
}
Double_t HitFit2lgFun_0(Double_t *x, Double_t *par){
  double xx = x[0];
  double   parLG1[4]={par[0],par[1],par[2],par[3]};
  double   parLG2[4]={par[4],par[5],par[6],par[7]};
  Double_t xTCut =par[8];
  return (langaufun(x,parLG1) + langaufun(x,parLG2))*((xx-xTCut)>0);
}
TString HitFit2lgFun_0(TF1 *TF1Object){
  TF1Object->SetParNames(
    "LG1Sca","LG1MPV","LG1Are","LG1Sig",
    "LG2Sca","LG2MPV","LG2Are","LG2Sig",
    "xTCut"
  );
  return "Pars:\tLG1Sca\tLG1MPV\tLG1Are\tLG1Sig\tLG2Sca\tLG2MPV\tLG2Are\tLG2Sig\txTCut";
}
Double_t HitFitFun_85_Base_B5C03(Double_t *x, Double_t *par){//Landau + Gaussian
  double Sca     = par[0];//Scale = Area
  double Mpv1    = par[1];//Most Probable Value
  double Sig     = par[3];//Sigma
  double xTCut   = par[4];
  double xx      = x[0];
  const double ScaG = 0.268,Off0 = 12.8,Sig0 = 2.3,SigG = 5.087;
  // const double ScaG = 0.305,Off0 = 16.8,Sig0 = 2.3,SigG = 4.2;
  double   parL [3]={1,Mpv1,1*par[3]};
  double   parG [3]={ScaG,Mpv1+Off0*Sig/Sig0,SigG*par[3]};
  double   decrease ;//= 1./(1.0*int(xTCut-xx));
  if (xx<0) decrease = 0;
  else if (xx<xTCut) decrease = pow(sin(xx/0.8/xTCut),2);
  else               decrease = 1.;
  
  par[2] = Mpv1+Off0*Sig/Sig0;//Most Probable Value
  return Sca*(landaufun(x,parL) + gaussifun(x,parG))*decrease;
}
Double_t HitFitFun_85_Base_B5C13(Double_t *x, Double_t *par){//Landau + Gaussian
  double Sca     = par[0];//Scale = Area
  double Mpv1    = par[1];//Most Probable Value
  double Sig     = par[3];//Sigma
  double xTCut   = par[4];
  double xx      = x[0];
 // const double ScaG = 0.268,Off0 = 12.8,Sig0 = 2.3,SigG = 5.087;
  const double ScaG = 0.305,Off0 = 16.8,Sig0 = 2.3,SigG = 4.2;
  double   parL [3]={1,Mpv1,1*par[3]};
  double   parG [3]={ScaG,Mpv1+Off0*Sig/Sig0,SigG*par[3]};
  double   decrease ;//= 1./(1.0*int(xTCut-xx));
  if (xx<0) decrease = 0;
  else if (xx<xTCut) decrease = pow(sin(xx/0.8/xTCut),2);
  else               decrease = 1.;
  
  par[2] = Mpv1+Off0*Sig/Sig0;//Most Probable Value
  return Sca*(landaufun(x,parL) + gaussifun(x,parG))*decrease;
}
Double_t HitFitFun_85_Base_B1C02(Double_t *x, Double_t *par){//Landau + Gaussian
  double Sca     = par[0];//Scale = Area
  double Mpv1    = par[1];//Most Probable Value
  double Sig     = par[3];//Sigma
  double xTCut   = par[4];
  double xx      = x[0];
 // const double ScaG = 0.268,Off0 = 12.8,Sig0 = 2.3,SigG = 5.087;
  const double ScaG = 0.29,Off0 = 12.8,Sig0 = 2.3,SigG = 4.8;
  double   parL [3]={1,Mpv1,1*par[3]};
  double   parG [3]={ScaG,Mpv1+Off0*Sig/Sig0,SigG*par[3]};
  double   decrease ;//= 1./(1.0*int(xTCut-xx));
  if (xx<0) decrease = 0;
  else if (xx<xTCut) decrease = pow(sin(xx/0.8/xTCut),2);
  else               decrease = 1.;
  
  par[2] = Mpv1+Off0*Sig/Sig0;//Most Probable Value
  return Sca*(landaufun(x,parL) + gaussifun(x,parG))*decrease;
}
Double_t HitFitFun_85_Base_B4C03(Double_t *x, Double_t *par){//Landau + Gaussian
  double Sca     = par[0];//Scale = Area
  double Mpv1    = par[1];//Most Probable Value
  double Sig     = par[3];//Sigma
  double xTCut   = par[4];
  double xx      = x[0];
 // const double ScaG = 0.268,Off0 = 12.8,Sig0 = 2.3,SigG = 5.087;
  const double ScaG = 0.31,Off0 = 14,Sig0 = 2.3,SigG = 4.8;
  double   parL [3]={1,Mpv1,1*par[3]};
  double   parG [3]={ScaG,Mpv1+Off0*Sig/Sig0,SigG*par[3]};
  double   decrease ;//= 1./(1.0*int(xTCut-xx));
  if (xx<0) decrease = 0;
  else if (xx<xTCut) decrease = pow(sin(xx/0.8/xTCut),2);
  else               decrease = 1.;
  
  par[2] = Mpv1+Off0*Sig/Sig0;//Most Probable Value
  return Sca*(landaufun(x,parL) + gaussifun(x,parG))*decrease;
}
TString HitFitFun_85_Base_B5C03(TF1 *TF1Object){
  TF1Object->SetParNames(
    "Sca","MPV1","MPV2","Sig","xTCut"
  );
  return "Pars:\tSca\tMPV1\tMPV2\tSig\txTCut";
}

