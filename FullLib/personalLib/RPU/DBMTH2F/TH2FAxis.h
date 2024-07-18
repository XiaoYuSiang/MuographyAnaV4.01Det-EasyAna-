#include <TH2F.h>
/*
void setAxis(TH2F* TH2FObject,float XTS,float XTO,float XLS,float XLO,float YTS,float YTO,float YLS,float YLO){
  //X- xaxis ; Y- yaxis ; T- title ; L- label ; O- offset ; S- size
  //default value
  if (XTS==-1) XTS=0.05;
  if (XTO==-1) XTO=1;
  if (XLS==-1) XLS=0.15;
  if (XLO==-1) XLO=1;
  if (YTS==-1) YTS=0.1;
  if (YTO==-1) YTO=0.55;
  if (YLS==-1) YLS=0.08;
  if (YLO==-1) YLO=0.01;
  //set x
  TH2FObject->GetXaxis()->SetTitleSize(XTS);
  TH2FObject->GetXaxis()->SetTitleOffset(XTO);
  TH2FObject->GetXaxis()->SetLabelSize(XLS);
  TH2FObject->GetXaxis()->SetLabelOffset(XLO);
  //set y
  TH2FObject->GetYaxis()->SetTitleSize(YTS);
  TH2FObject->GetYaxis()->SetTitleOffset(YTO);
  TH2FObject->GetYaxis()->SetLabelSize(YLS);
  TH2FObject->GetYaxis()->SetLabelOffset(YLO);
  //no color for the upper graph
  TH2FObject->GetXaxis()->SetLabelColor(0);
  TH2FObject->SetStats(0);
}
void setAxisTNormal(TH2F* TH2FObject){
  //set x
  TH2FObject->GetXaxis()->SetTitleSize(0.05);
  TH2FObject->GetXaxis()->SetTitleOffset(1);
  TH2FObject->GetXaxis()->SetLabelSize(0.15);
  TH2FObject->GetXaxis()->SetLabelOffset(1);
  //set y
  TH2FObject->GetYaxis()->SetTitleSize(0.10);
  TH2FObject->GetYaxis()->SetTitleOffset(0.6);
  TH2FObject->GetYaxis()->SetLabelSize(0.08);
  TH2FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  TH2FObject->GetXaxis()->SetLabelColor(0);
  TH2FObject->SetStats(0);
}
void setAxisTDivide(TH2F* TH2FObject){
  //set x
  TH2FObject->GetXaxis()->SetTitleSize(0.2);
  TH2FObject->GetXaxis()->SetTitleOffset(1);
  TH2FObject->GetXaxis()->SetLabelSize(0.2);
  TH2FObject->GetXaxis()->SetLabelOffset(0.05);
  //set y
  TH2FObject->GetYaxis()->SetTitleSize(0.15);
  TH2FObject->GetYaxis()->SetTitleOffset(0.36);
  TH2FObject->GetYaxis()->SetLabelSize(0.2);
  TH2FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  TH2FObject->SetStats(0);
}
*/

void setAxisLabelSize(TH2F* TH2FObject,float sizeX,float sizeY,float sizeZ){
  TH2FObject->GetXaxis()->SetLabelSize(sizeX);
  TH2FObject->GetYaxis()->SetLabelSize(sizeY);
  TH2FObject->GetZaxis()->SetLabelSize(sizeZ);
}
void setAxisTitleSize(TH2F* TH2FObject,float sizeX,float sizeY,float sizeZ){
  TH2FObject->GetXaxis()->SetTitleSize(sizeX);
  TH2FObject->GetYaxis()->SetTitleSize(sizeY);
  TH2FObject->GetZaxis()->SetTitleSize(sizeZ);
}
void setAxisLabelOffset(TH2F* TH2FObject,float offX,float offY,float offZ){
  TH2FObject->GetXaxis()->SetLabelOffset(offX);
  TH2FObject->GetYaxis()->SetLabelOffset(offY);
  TH2FObject->GetZaxis()->SetLabelOffset(offZ);
}
void setAxisTitleOffset(TH2F* TH2FObject,float offX,float offY,float offZ){
  TH2FObject->GetXaxis()->SetTitleOffset(offX);
  TH2FObject->GetYaxis()->SetTitleOffset(offY);
  TH2FObject->GetZaxis()->SetTitleOffset(offZ);
}
void setAxisCenterTitle(TH2F* TH2FObject,bool CX,float CY,float CZ){
  TH2FObject->GetXaxis()->CenterTitle(CX);
  TH2FObject->GetYaxis()->CenterTitle(CY);
  TH2FObject->GetZaxis()->CenterTitle(CZ);
}