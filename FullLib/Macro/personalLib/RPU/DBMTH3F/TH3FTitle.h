#include <TH3F.h>
//#include "/home/yusiang/personalLib/RPU/DBMTH1F/TH1FTitle.h"
void setTitle(TH3F* TH3FObject,const char *title,const char *Xtitle,const char *Ytitle,const char *Ztitle){
  TH3FObject->SetTitle(title);
  TH3FObject->GetXaxis()->SetTitle(Xtitle);
  TH3FObject->GetYaxis()->SetTitle(Ytitle);
  TH3FObject->GetZaxis()->SetTitle(Ztitle);
}
void setTitle(TH3F* TH3FObject,const char *Xtitle,const char *Ytitle,const char *Ztitle){
  TH3FObject->GetXaxis()->SetTitle(Xtitle);
  TH3FObject->GetYaxis()->SetTitle(Ytitle);
  TH3FObject->GetZaxis()->SetTitle(Ztitle);
}
void setTitleNone(TH3F* TH3FObject){
  TH3FObject->SetTitle("");
  TH3FObject->GetXaxis()->SetTitle("");
  TH3FObject->GetYaxis()->SetTitle("");
  TH3FObject->GetZaxis()->SetTitle("");
}
void setAxisRangeUser(TH3F* TH3FObject,double xmin,double xmax,double ymin,double ymax,double zmin,double zmax){
  //set x
  TH3FObject->GetXaxis()->SetRangeUser(xmin,xmax);
  TH3FObject->GetYaxis()->SetRangeUser(ymin,ymax);
  TH3FObject->GetZaxis()->SetRangeUser(zmin,zmax);
  //no color for the upper graph
}