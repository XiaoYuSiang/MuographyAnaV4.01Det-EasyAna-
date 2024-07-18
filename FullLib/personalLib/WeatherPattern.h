#include "TImage.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAttImage.h"
#include "TVirtualPad.h"
#include "TAttBBox2D.h"

void WeatherPattern(const char *name, Double_t xlow, Double_t ylow, Double_t xup, Double_t yup, TCanvas *Canvas0, TCanvas *Canvas1,const char *option){
  TImage *img;
  if(strcmp(option,"cloudy")==0||strcmp(option,"c")==0||strcmp(option,"C")==0||strcmp(option,"Cloudy")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/cloudy.png");
  }else if(strcmp(option,"snowy")==0||strcmp(option,"sn")==0||strcmp(option,"Sn")==0||strcmp(option,"Snowy")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/snowy.png");
  }else if(strcmp(option,"sun")==0||strcmp(option,"su")==0||strcmp(option,"Su")==0||strcmp(option,"Sun")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/sun.png");
  }else if(strcmp(option,"rainy")==0||strcmp(option,"r")==0||strcmp(option,"R")==0||strcmp(option,"Rainy")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/rainy.png");
  }else if(strcmp(option,"hurricane")==0||strcmp(option,"h")==0||strcmp(option,"H")==0||strcmp(option,"Hurricane")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/hurricane.png");
  }else if(strcmp(option,"cloudy_rain")==0||strcmp(option,"cr")==0||strcmp(option,"CR")==0||strcmp(option,"Cr")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/cloudy_rain.png");
  }else if(strcmp(option,"storm")==0||strcmp(option,"st")==0||strcmp(option,"St")==0||strcmp(option,"Storm")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/storm.png");
  }else if(strcmp(option,"N")==0||strcmp(option,"n")==0||strcmp(option,"nd")==0||strcmp(option,"Nd")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/warning.png");
  }
  //const char *name, const char *title, Double_t xlow, Double_t ylow, Double_t xup, Double_t yup, Color_t color=-1, Short_t bordersize=-1, Short_t bordermode=-2
  Canvas0->cd();
  TPad *iconPad = new TPad(name,name,xlow,ylow,xup,yup);
  iconPad->SetLeftMargin(0);
  iconPad->SetBottomMargin(0);
  iconPad->SetRightMargin(1);
  iconPad->SetTopMargin(1);
  iconPad->Draw();
  iconPad->cd();
  img->Draw("xxx");
  Canvas1->cd();
}
void WeatherPattern(const char *name, Double_t xlow, Double_t ylow, Double_t xup, Double_t yup, TCanvas *Canvas0,const char *option){
  TImage *img;
  if(strcmp(option,"cloudy")==0||strcmp(option,"c")==0||strcmp(option,"C")==0||strcmp(option,"Cloudy")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/cloudy.png");
  }else if(strcmp(option,"snowy")==0||strcmp(option,"sn")==0||strcmp(option,"Sn")==0||strcmp(option,"Snowy")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/snowy.png");
  }else if(strcmp(option,"sun")==0||strcmp(option,"su")==0||strcmp(option,"Su")==0||strcmp(option,"Sun")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/sun.png");
  }else if(strcmp(option,"rainy")==0||strcmp(option,"r")==0||strcmp(option,"R")==0||strcmp(option,"Rainy")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/rainy.png");
  }else if(strcmp(option,"hurricane")==0||strcmp(option,"h")==0||strcmp(option,"H")==0||strcmp(option,"Hurricane")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/hurricane.png");
  }else if(strcmp(option,"cloudy_rain")==0||strcmp(option,"cr")==0||strcmp(option,"CR")==0||strcmp(option,"Cr")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/cloudy_rain.png");
  }else if(strcmp(option,"storm")==0||strcmp(option,"st")==0||strcmp(option,"St")==0||strcmp(option,"Storm")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/storm.png");
  }else if(strcmp(option,"N")==0||strcmp(option,"n")==0||strcmp(option,"nd")==0||strcmp(option,"Nd")==0){
    img = TImage::Open("/home/7202018/personalLib/Pattern/warning.png");
  }
  //const char *name, const char *title, Double_t xlow, Double_t ylow, Double_t xup, Double_t yup, Color_t color=-1, Short_t bordersize=-1, Short_t bordermode=-2
  Canvas0->cd();
  TPad *iconPad = new TPad(name,name,xlow,ylow,xup,yup);
  iconPad->SetLeftMargin(0);
  iconPad->SetBottomMargin(0);
  iconPad->SetRightMargin(1);
  iconPad->SetTopMargin(1);
  iconPad->SetFillColor(-1);
  iconPad->Draw();
  iconPad->cd();
  img->Draw("xxx");
  Canvas0->cd();
}

/*
void rose_image(){
 
  TCanvas *c1 = new TCanvas("c1","",512,512);
  c1->cd();
  WeatherPattern("a1",0.5,0.5,1,1,c1,c1,"c");
  WeatherPattern("a2",0.5,0,1,0.5,c1,c1,"R");
  WeatherPattern("a3",0,0.5,0.5,1,c1,c1,"h");
  WeatherPattern("a4",0,0,0.50,0.50,c1,c1,"su");
  WeatherPattern("a4",0.25,0.25,0.75,0.750,c1,c1,"sn");

  
  c1->Print("A.png");
   
}*/