void setAxis(TH1F* tH1FObject,float XTS,float XTO,float XLS,float XLO,float YTS,float YTO,float YLS,float YLO){
  //X- xaxis ; Y- yaxis ; T- title ; L- label ; O- offset ; S- size
  //default value
  if (XTS==-1) XTS=0.05;
  if (XTO==-1) XTO=1;
  if (XLS==-1) XLS=0.15;
  if (XLO==-1) XLO=1;
  if (YTS==-1) YTS=0.09;
  if (YTO==-1) YTO=0.75;
  if (YLS==-1) YLS=0.07;
  if (YLO==-1) YLO=0.01;
  //set x
  tH1FObject->GetXaxis()->SetTitleSize(XTS);
  tH1FObject->GetXaxis()->SetTitleOffset(XTO);
  tH1FObject->GetXaxis()->SetLabelSize(XLS);
  tH1FObject->GetXaxis()->SetLabelOffset(XLO);
  //set y
  tH1FObject->GetYaxis()->SetTitleSize(YTS);
  tH1FObject->GetYaxis()->SetTitleOffset(YTO);
  tH1FObject->GetYaxis()->SetLabelSize(YLS);
  tH1FObject->GetYaxis()->SetLabelOffset(YLO);
  //no color for the upper graph
  tH1FObject->GetXaxis()->SetLabelColor(0);
  tH1FObject->SetStats(0);
}
//setAxis*Normal S- Singal pad ; T- Ywo pad
void setAxisSNormal(TH1F* tH1FObject){
  //set x
  tH1FObject->GetXaxis()->SetTitleSize(0.05);
  tH1FObject->GetXaxis()->SetTitleOffset(1);
  tH1FObject->GetXaxis()->SetLabelSize(0.15);
  tH1FObject->GetXaxis()->SetLabelOffset(1);
  //set y
  tH1FObject->GetYaxis()->SetTitleSize(0.09);
  tH1FObject->GetYaxis()->SetTitleOffset(0.75);
  tH1FObject->GetYaxis()->SetLabelSize(0.07);
  tH1FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  tH1FObject->SetStats(0);
}
void setAxisTNormal(TH1F* tH1FObject){
  //set x
  tH1FObject->GetXaxis()->SetTitleSize(0.05);
  tH1FObject->GetXaxis()->SetTitleOffset(1);
  tH1FObject->GetXaxis()->SetLabelSize(0.15);
  tH1FObject->GetXaxis()->SetLabelOffset(1);
  //set y
  tH1FObject->GetYaxis()->SetTitleSize(0.09);
  tH1FObject->GetYaxis()->SetTitleOffset(0.75);
  tH1FObject->GetYaxis()->SetLabelSize(0.06);
  tH1FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  tH1FObject->GetXaxis()->SetLabelColor(0);
  tH1FObject->SetStats(0);
}
void setAxisTDivide(TH1F* tH1FObject){
  //set x
  tH1FObject->GetXaxis()->SetTitleSize(0.2);
  tH1FObject->GetXaxis()->SetTitleOffset(1);
  tH1FObject->GetXaxis()->SetLabelSize(0.15);
  tH1FObject->GetXaxis()->SetLabelOffset(0.05);
  //set y
  tH1FObject->GetYaxis()->SetTitleSize(0.15);
  tH1FObject->GetYaxis()->SetTitleOffset(0.36);
  tH1FObject->GetYaxis()->SetLabelSize(0.12);
  tH1FObject->GetYaxis()->SetLabelOffset(0.01);
  //no color for the upper graph
  tH1FObject->SetStats(0);
}
void setAxisRangeUser(TH1F* tH1FObject,double xmin,double xmax,double ymin,double ymax){
  //set x
  tH1FObject->GetXaxis()->SetRangeUser(xmin,xmax);
  tH1FObject->GetYaxis()->SetRangeUser(ymin,ymax);
  //no color for the upper graph
}


void setAxisLabelSize(TH1F* tH1FObject,float sizeX,float sizeY){
  tH1FObject->GetXaxis()->SetLabelSize(sizeX);
  tH1FObject->GetYaxis()->SetLabelSize(sizeY);
}
void setAxisTitleSize(TH1F* tH1FObject,float sizeX,float sizeY){
  tH1FObject->GetXaxis()->SetTitleSize(sizeX);
  tH1FObject->GetYaxis()->SetTitleSize(sizeY);
}
void setAxisLabelOffset(TH1F* tH1FObject,float offX,float offY){
  tH1FObject->GetXaxis()->SetLabelOffset(offX);
  tH1FObject->GetYaxis()->SetLabelOffset(offY);
}
void setAxisTitleOffset(TH1F* tH1FObject,float offX,float offY){
  tH1FObject->GetXaxis()->SetTitleOffset(offX);
  tH1FObject->GetYaxis()->SetTitleOffset(offY);
}
void setCenterTitle(TH1F* TH1FObject,bool CX,float CY,float CZ){
  TH1FObject->GetXaxis()->CenterTitle(CX);
  TH1FObject->GetYaxis()->CenterTitle(CY);
  TH1FObject->GetZaxis()->CenterTitle(CZ);
}