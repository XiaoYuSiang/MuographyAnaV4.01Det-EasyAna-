#include "TCanvas.h"
#include "TPaveText.h"
#include "TVirtualPad.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
const int TCanvasAutoConsumeX = 4;
const int TCanvasAutoConsumeY = 28;
void SetCanvasMargin(TCanvas* TCanvasObject,float x0,float y0,float x1,float y1){
  TCanvasObject->SetTopMargin(y1); TCanvasObject->SetBottomMargin(y0); 
  TCanvasObject->SetLeftMargin(x0); TCanvasObject->SetRightMargin(x1);
}
void SetCanvasMargin(TVirtualPad* TVPadObject,float x0,float y0,float x1,float y1){
  TVPadObject->SetTopMargin(y1); TVPadObject->SetBottomMargin(y0); 
  TVPadObject->SetLeftMargin(x0); TVPadObject->SetRightMargin(x1);
}
void SetNoMarginCanvas(TCanvas* TCanvasObject){ SetCanvasMargin(TCanvasObject,0,0,0,0);}
void SetNoMarginCanvas(TVirtualPad* TVPadObject){ SetCanvasMargin(TVPadObject,0,0,0,0);}

void DrawPdfPng(TCanvas* TCanvasObject,const char* FileTitle){
  TCanvasObject->cd();
  TCanvasObject->Print(Form("%s.pdf",FileTitle));
  TCanvasObject->Print(Form("%s.png",FileTitle));
}

void SetCTitleSetting(TCanvas* TCanvasObject, const float TitleSize,const int TitleFont=42){
  TPaveText *ptX = (TPaveText*)(TCanvasObject->GetPrimitive("title"));
  ptX->SetTextSize(TitleSize);
  ptX->SetTextFont(TitleFont);
  TCanvasObject->Modified();
}

void SetCTitleSetting(TVirtualPad* TVPadObject, const float TitleSize,const int TitleFont=42){
  TPaveText *ptX = (TPaveText*)(TVPadObject->GetPrimitive("title"));
  ptX->SetTextSize(TitleSize);
  ptX->SetTextFont(TitleFont);
  TVPadObject->Modified();
}

void DrawPadCloneOn(TCanvas* TCanvS, TCanvas* TCanvM){ 
  TCanvM->cd();
  TCanvS->DrawClonePad();
}
void DrawPadCloneOn(TCanvas* TCanvS, TVirtualPad* TCanvM){ 
  TCanvM->cd();
  TCanvS->DrawClonePad();
}
void DrawPadCloneOn(TVirtualPad* TCanvS, TCanvas* TCanvM){
  TCanvM->cd();
  TCanvS->Draw();
}
void DrawPadCloneOn(TVirtualPad* TCanvS, TVirtualPad* TCanvM){
  TCanvM->cd();
  TCanvS->Draw();
}
TCanvas *EasyCanvas(const char* CName, const int pixelX , const int pixelY, const int DnX = 1, const int DnY = 1, const string DOutline="true"){
  TCanvas *ctmp = new TCanvas(CName,CName,pixelX+TCanvasAutoConsumeX,pixelY+TCanvasAutoConsumeY);
  if(abs(DnX)<=1&&abs(DnY)<=1){ 
    return ctmp;
    // cout<<("DnX=DnY=1\n");
    // throw;
  }else if(abs(DnX)<1||abs(DnY)<1){
    cout<<"Error: DBMTCanvas.C: EasyCanvas(const int DnX, const int DnY) shouldn't use negative/0 DnX or DnY"<<endl;
    cout<<"    Please use (-1,-1) or ( 0, 0) or ( 1, 1) to present not to do ->Divide()."<<endl;
    throw;
  }
  ctmp->Divide(DnX,DnY);
  SetNoMarginCanvas(ctmp);
  ctmp->SetBorderSize(0);
  if(int(DOutline.find("t"))!=-1){
    for(int i=1; i<=DnX*DnY; i++){
      SetNoMarginCanvas(ctmp->cd(i));
      ctmp->cd(i)->SetBorderSize(0);
    }
  }
  return ctmp;
}
TCanvas *EasyCanvas(const char* CName, const int sizeX = 960, const string xyRate = "16:9", const int DnX = 1, const int DnY = 1, const string DOutline="true"){
  size_t posSp = xyRate.find(":");
  string Str_sizerx = xyRate.substr(0, posSp);
  string Str_sizery = xyRate.substr(posSp+1, xyRate.size()-1);
  float  sizeRx = atof(Str_sizerx.data()), sizeRy = atof(Str_sizery.data());
  int pixelX = sizeX;
  int pixelY = ceil(sizeX/sizeRx*sizeRy);
  return EasyCanvas(CName,pixelX,pixelY,DnX,DnY);
}
TCanvas *EasyCanvas(const char* CName, const int sizeX = 960, const float xyRate = 1.7777, const int DnX = 1, const int DnY = 1, const string DOutline="true"){
  return EasyCanvas(CName,sizeX,int(sizeX/xyRate),DnX,DnY);
}
TCanvas *EasyCanvas(const char* CName, const int sizeX = 960, const float xRate = 16.0, const float yRate = 9.0, const int DnX = 1, const int DnY = 1, const string DOutline="true"){
  return EasyCanvas(CName,sizeX,int(sizeX/xRate*yRate),DnX,DnY);
}

TCanvas *EasyCanvas(const char* CName, const string resCode="540p", const int DnX = 1, const int DnY = 1, const string DOutline="true"){
  int px =0, py =0;
  if(int(resCode.find("pv"))!=-1||int(resCode.find("pv"))!=-1){
    if     (int(resCode.find("540"))!=-1)  px  = 540;
    else if(int(resCode.find("1440"))!=-1) px = 1440;
    else if(int(resCode.find("144"))!=-1)  px = 144;
    else if(int(resCode.find("240"))!=-1)  px = 240;
    else if(int(resCode.find("360"))!=-1)  px = 360;
    else if(int(resCode.find("480"))!=-1)  px = 480;
    else if(int(resCode.find("720"))!=-1)  px = 720;
    else if(int(resCode.find("1080"))!=-1) px = 1080;
    else if(int(resCode.find("2160"))!=-1) px = 2160;
    py = ceil(px/9. * 16.);
  }else if(int(resCode.find("p"))!=-1||int(resCode.find("p"))!=-1){
    if     (int(resCode.find("540"))!=-1)  py  = 540;
    else if(int(resCode.find("1440"))!=-1) py = 1440;
    else if(int(resCode.find("144"))!=-1)  py = 144;
    else if(int(resCode.find("240"))!=-1)  py = 240;
    else if(int(resCode.find("360"))!=-1)  py = 360;
    else if(int(resCode.find("480"))!=-1)  py = 480;
    else if(int(resCode.find("720"))!=-1)  py = 720;
    else if(int(resCode.find("1080"))!=-1) py = 1080;
    else if(int(resCode.find("2160"))!=-1) py = 2160;
    px = ceil(py/9. * 16.);
  }else if(int(resCode.find("8k"))!=-1||int(resCode.find("8K"))!=-1||int(resCode.find("UHDP"))!=-1){
    px = 7680; py = 4320;
  }else if(int(resCode.find("4k"))!=-1||int(resCode.find("4K"))!=-1||int(resCode.find("UHD"))!=-1){
    px = 3840; py = 2160;
  }else if(int(resCode.find("2k"))!=-1||int(resCode.find("2K"))!=-1||int(resCode.find("WQHD"))!=-1){
    px = 2560; py = 1440;
  }else if(int(resCode.find("1k"))!=-1||int(resCode.find("1K"))!=-1||int(resCode.find("FHD"))!=-1){
    px = 1920; py = 1080;
  }else if(int(resCode.find("HD"))!=-1){
    px = 1280; py = 720;
  }else if(int(resCode.find("qHD"))!=-1){
    px = 960; py = 540;
  }else if(int(resCode.find("SD"))!=-1){
    px = 854; py = 480;
  }else if(int(resCode.find("nHD"))!=-1){
    px = 640; py = 360;
  }
  return EasyCanvas(CName,px,py,DnX,DnY,DOutline);

}
