#include <TH3F.h>
/*
void setAxis(TH3F* TH3FObject,float XTS,float XTO,float XLS,float XLO,float YTS,float YTO,float YLS,float YLO){
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
  TH3FObject->GetXaxis()->SetTitleSize(XTS);
  TH3FObject->GetXaxis()->SetTitleOffset(XTO);
  TH3FObject->GetXaxis()->SetLabelSize(XLS);
  TH3FObject->GetXaxis()->SetLabelOffset(XLO);
  //set y
  TH3FObject->GetYaxis()->SetTitleSize(YTS);
  TH3FObject->GetYaxis()->SetTitleOffset(YTO);
  TH3FObject->GetYaxis()->SetLabelSize(YLS);
  TH3FObject->GetYaxis()->SetLabelOffset(YLO);
  //no color for the upper graph
  TH3FObject->GetXaxis()->SetLabelColor(0);
  TH3FObject->SetStats(0);
}
void setAxisTNormal(TH3F* TH3FObject){
  //set x
  TH3FObject->GetXaxis()->SetTitleSize(0.05);
  TH3FObject->GetXaxis()->SetTitleOffset(1);
  TH3FObject->GetXaxis()->SetLabelSize(0.15);
  TH3FObject->GetXaxis()->SetLabelOffset(1);
  //set y
  TH3FObject->GetYaxis()->SetTitleSize(0.10);
  TH3FObject->GetYaxis()->SetTitleOffset(0.6);
  TH3FObject->GetYaxis()->SetLabelSize(0.08);
  TH3FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  TH3FObject->GetXaxis()->SetLabelColor(0);
  TH3FObject->SetStats(0);
}
void setAxisTDivide(TH3F* TH3FObject){
  //set x
  TH3FObject->GetXaxis()->SetTitleSize(0.2);
  TH3FObject->GetXaxis()->SetTitleOffset(1);
  TH3FObject->GetXaxis()->SetLabelSize(0.2);
  TH3FObject->GetXaxis()->SetLabelOffset(0.05);
  //set y
  TH3FObject->GetYaxis()->SetTitleSize(0.15);
  TH3FObject->GetYaxis()->SetTitleOffset(0.36);
  TH3FObject->GetYaxis()->SetLabelSize(0.2);
  TH3FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  TH3FObject->SetStats(0);
}
*/

void setAxisLabelSize(TH3F* TH3FObject,float sizeX,float sizeY,float sizeZ){
  TH3FObject->GetXaxis()->SetLabelSize(sizeX);
  TH3FObject->GetYaxis()->SetLabelSize(sizeY);
  TH3FObject->GetZaxis()->SetLabelSize(sizeZ);
}
void setAxisTitleSize(TH3F* TH3FObject,float sizeX,float sizeY,float sizeZ){
  TH3FObject->GetXaxis()->SetTitleSize(sizeX);
  TH3FObject->GetYaxis()->SetTitleSize(sizeY);
  TH3FObject->GetZaxis()->SetTitleSize(sizeZ);
}
void setAxisLabelOffset(TH3F* TH3FObject,float offX,float offY,float offZ){
  TH3FObject->GetXaxis()->SetLabelOffset(offX);
  TH3FObject->GetYaxis()->SetLabelOffset(offY);
  TH3FObject->GetZaxis()->SetLabelOffset(offZ);
}
void setAxisTitleOffset(TH3F* TH3FObject,float offX,float offY,float offZ){
  TH3FObject->GetXaxis()->SetTitleOffset(offX);
  TH3FObject->GetYaxis()->SetTitleOffset(offY);
  TH3FObject->GetZaxis()->SetTitleOffset(offZ);
}
void setAxisCenterTitle(TH3F* TH3FObject,bool CX,float CY,float CZ){
  TH3FObject->GetXaxis()->CenterTitle(CX);
  TH3FObject->GetYaxis()->CenterTitle(CY);
  TH3FObject->GetZaxis()->CenterTitle(CZ);
}