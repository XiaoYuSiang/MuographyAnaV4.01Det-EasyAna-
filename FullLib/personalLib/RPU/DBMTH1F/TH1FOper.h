#include <iostream>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <TH1F.h>
void Normalized(TH1F* tH1FObject){
  tH1FObject->Sumw2();
  tH1FObject->Scale(1./tH1FObject->Integral(-1,-1));
}
void Normalized(TH1F* tH1FObject, double x_min, double x_max){
  tH1FObject->Sumw2();
  tH1FObject->Scale(1./tH1FObject->Integral(x_min,x_max));
}
void DaMcSumw2(TH1F* tH1FObject1, TH1F* tH1FObject2){
  tH1FObject1->Sumw2();
  tH1FObject2->Sumw2();
}
/*
TH1F* TH1FConvolution(TH1F* tH1FObject1, TH1F* tH1FObject2,char* ResultName=Form("%sOXO%s",tH1FObject1->GetName(),tH1FObject2->GetName()),char* ResuleTitle="Title"){
  int    BinXNum1     = tH1FObject1->GetNbinsX();
  double BinWid1      = tH1FObject1->GetBinWidth(1);
  double LeftX1       = tH1FObject1->GetBinCenter(0)-BinWid1/2;
  double RightX1      = tH1FObject1->GetBinCenter(BinXNum1)+BinWid1/2;
  
  int    BinXNum2     = tH1FObject2->GetNbinsX();
  double BinWid2      = tH1FObject2->GetBinWidth(1);
  double LeftX2       = tH1FObject2->GetBinCenter(0)-BinWid2/2;
  double RightX2      = tH1FObject2->GetBinCenter(BinXNum2)+BinWid2/2;
  double LeftX,RightX,BinWid; int BinNum;
  if(LeftX2 <LeftX1 ) LeftX = LeftX2 ; else LeftX = LeftX1;
  if(RightX2>RightX1) RightX= RightX2; else RightX= RightX1;
  if(BinWid2<BinWid1) BinWid= BinWid2; else BinWid= BinWid1;
  BinNum = (RightX-LeftX)/BinWid;
  TH1F* tH1FObjectR = new TH1F(ResultName,ResuleTitle,BinXNum2,LeftX2,RightX2)
  for(int ibin=0;i<BinXNum2) 
  
  
  
}*/
double TH1FConvolutionValue(TH1F* tH1FObject1, TH1F* tH1FObject2,int ixshift=0){
  int BinNum,BinNum1,BinNum2;
  BinNum1 = tH1FObject1->GetNbinsX();
  BinNum2 = tH1FObject2->GetNbinsX();
  if(BinNum2>BinNum1) BinNum = BinNum1; else BinNum = BinNum2;
  double sum=0;
  for(int ibin=0;ibin<BinNum;ibin++) {
    double tmp = 0;
    double decrease ;//= 1./(1.0*int(xTCut-xx));
    double xx = tH1FObject1->GetBinCenter(ibin+ixshift);
    if (xx<0) decrease = 0;
    else if (xx<1.7) decrease = pow(sin(xx/0.8/1.7),2);
    else             decrease = 1.;
    double normalizeFac = tH1FObject1->Integral(0+ixshift,90)*tH1FObject2->Integral(0,90);
    sum +=tH1FObject1->GetBinContent(ibin+ixshift)
         *decrease
         *(tH1FObject2->GetBinContent(ibin))
         /normalizeFac;
    
  }
  return sum;
}
TH1F* TH1FConvolution(TH1F* tH1FObject1, TH1F* tH1FObject2,const char* ResultName="Name",const char* ResuleTitle="Title"){
  /*
  tH1FObject1 is the tool TH1F 
  tH1FObject2 is the target TH1F 
  */
  cout<<"sprintf"<<endl;
  //Form("%sOXO%s",tH1FObject1->GetName(),tH1FObject2->GetName());
  TH1F* tH1FObjectR = new TH1F(ResultName,ResuleTitle,180,-90+.5,90+.5);
  cout<<"tH1FObjectR"<<endl;
  for(int ix=-90;ix<90;ix++){
    if(ix!=-90||ix!=90){
      tH1FObjectR->Fill(ix,
        (TH1FConvolutionValue(tH1FObject1,tH1FObject2,ix)
        +TH1FConvolutionValue(tH1FObject1,tH1FObject2,ix-1)
        +TH1FConvolutionValue(tH1FObject1,tH1FObject2,ix+1)
        )/3.
      );
    }
    else tH1FObjectR->Fill(ix,TH1FConvolutionValue(tH1FObject1,tH1FObject2,ix));
  }
  return tH1FObjectR;
}