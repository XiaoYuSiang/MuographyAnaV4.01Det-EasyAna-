#include <limits.h>
#include "./DBMTPad.h"
#include "./DBMTLegend.h"
#include "./DBMTPDF.h"
#include "./DBMTCanvas.h"
#include "./DBMTH1F/TH1FAxis.h"
#include "./DBMTH1F/TH1FLine.h"
#include "./DBMTH1F/TH1FMark.h"
#include "./DBMTH1F/TH1FOper.h"
#include "./DBMTH1F/TH1FTitle.h"
using namespace std; 
void setTH1FDefault(TH1F* tH1FObject,TString option,int divi){
  option.ToLower();
  bool M=false, D=false, T=false, S=false, U=false, B=false;
  // M- Monticalro ; D- Data ; T- Two pad ; U- Normal ; B- base pad ; S- Single pad`; 
  int num = (int)option.Length();
  for (int i = 0;i < num ; i++){
    if (option[i]=='m') M = true;
    if (option[i]=='d') D = true;
    if (option[i]=='t') T = true;
    if (option[i]=='s') S = true;
    if (option[i]=='u') U = true;
    if (option[i]=='b') B = true;
  }
  if ( M == true ){
    setLineMonc(tH1FObject);
    setMarkMonc(tH1FObject);
  }else if( D == true ){
    setLineData(tH1FObject);
    setMarkData(tH1FObject);
  }
  if ( T == true ){
    if ( U == true ){
      setAxisTNormal(tH1FObject);
    }else if ( B == true ){
      setAxisTDivide(tH1FObject);
    }
  }else if( S == true ){
    setAxisSNormal(tH1FObject);
    if ( U == true || B == true ){
      cout<<"U & B option can't use at the same time"<<endl;
    }
  }
  setTitleNone(tH1FObject);
  tH1FObject->GetYaxis()->SetNdivisions(divi);
}

void FindYRangeTH1F(const TH1F* tH1FObj,float &ReturnYm,float &ReturnYM,const int precision=1,const float Trigger_MinY=0.1,const float Trigger_MaxY=2){
  
  float maxcon = INT_MIN*1., mincon = INT_MAX*1.;
  for(int i0=0;i0<tH1FObj->GetNbinsX();i0++){
    float contmp = tH1FObj->GetBinContent(i0+1);
    if(contmp>=Trigger_MinY && contmp<=Trigger_MaxY){
      if(maxcon<contmp)  maxcon = contmp;
      if(mincon>contmp)  mincon = contmp;
    }
  }
  
  ReturnYM = float(int(maxcon*pow(10,precision)*1.1)+pow(10,precision-1))
              /float(pow(10,precision));
  ReturnYm = float(int(mincon*pow(10,precision)*1))
              /float(pow(10,precision));
  
}


TH1F* TGraphToTH1F(
  TGraph* G0, string Name, string Title, int Nbin, double Range0, double Range1
){
  vector<float> vXhisto;
  for (int i = 0; i <= G0->GetN()-1; ++i) {
    double x0, y0, x1, y1;
    if(i==0){
      G0->GetPoint(i  , x0, y0);
      G0->GetPoint(i+1, x1, y1);
      vXhisto.push_back((3*x0-x1)*0.5);
    }
    if( i == G0->GetN()-1 ){
      G0->GetPoint(i-1, x0, y0);
      G0->GetPoint(i  , x1, y1);
      vXhisto.push_back((3*x1-x0)*0.5);
    }else{
      G0->GetPoint(i  , x0, y0);
      G0->GetPoint(i+1, x1, y1);
      vXhisto.push_back(0.5*(x0+x1));
    }
    // cout<<vXhisto[vXhisto.size()-1]<<endl;
  }
  
  TH1F* htmp = new TH1F("htmp", "htmp", vXhisto.size()-1, vXhisto.data());
  for (int i = 0; i < G0->GetN(); ++i) {
    double x0, y0;
    G0->GetPoint(i, x0, y0);
    htmp->Fill(x0,y0);
  }
  // htmp->Draw("hsame");
  
  TH1F* hReBin = new TH1F(Name.data(), Title.data(), Nbin, Range0, Range1);
  for (int i = 0; i < G0->GetN(); ++i) {
    int center1 = hReBin->GetBinCenter(i+1);
    int wid1b2 = htmp->GetBinWidth(i+1)/2;
    int bin0 = htmp->FindBin(center1-wid1b2);
    int bin1 = htmp->FindBin(center1+wid1b2);
    float Val =0, wids = 0;
    for(int ib=bin0;ib<=bin1;ib++){
      Val += htmp->GetBinContent(ib)*htmp->GetBinWidth(ib);
      wids += htmp->GetBinWidth(ib);
    }
    Val/=wids;
    hReBin->Fill(center1,Val);
  }
  hReBin->SetLineColor(2);
  
  delete htmp;
  return hReBin;
}
