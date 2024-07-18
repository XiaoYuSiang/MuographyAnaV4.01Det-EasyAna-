#include <TH2F.h>
//#include "/home/yusiang/personalLib/RPU/DBMTH1F/TH1FTitle.h"
void setTitle(TH2F* TH2FObject,const char *title,const char *Xtitle,const char *Ytitle,const char *Ztitle){
  TH2FObject->SetTitle(title);
  TH2FObject->GetXaxis()->SetTitle(Xtitle);
  TH2FObject->GetYaxis()->SetTitle(Ytitle);
  TH2FObject->GetZaxis()->SetTitle(Ztitle);
}
void setTitle(TH2F* TH2FObject,const char *Xtitle,const char *Ytitle,const char *Ztitle){
  TH2FObject->GetXaxis()->SetTitle(Xtitle);
  TH2FObject->GetYaxis()->SetTitle(Ytitle);
  TH2FObject->GetZaxis()->SetTitle(Ztitle);
}
void setTitleNone(TH2F* TH2FObject){
  TH2FObject->SetTitle("");
  TH2FObject->GetXaxis()->SetTitle("");
  TH2FObject->GetYaxis()->SetTitle("");
  TH2FObject->GetZaxis()->SetTitle("");
}
void setAxisRangeUser(TH2F* tH1FObject,double xmin,double xmax,double ymin,double ymax,double zmin,double zmax){
  //set x
  tH1FObject->GetXaxis()->SetRangeUser(xmin,xmax);
  tH1FObject->GetYaxis()->SetRangeUser(ymin,ymax);
  tH1FObject->GetZaxis()->SetRangeUser(zmin,zmax);
  //no color for the upper graph
}