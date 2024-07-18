#include <TH1F.h>

void setTitle(TH1F* tH1FObject,const char *title,const char *Xtitle,const char *Ytitle){
  tH1FObject->SetTitle(title);
  tH1FObject->GetXaxis()->SetTitle(Xtitle);
  tH1FObject->GetYaxis()->SetTitle(Ytitle);
}
void setTitle(TH1F* tH1FObject,const char *Xtitle,const char *Ytitle){
  tH1FObject->GetXaxis()->SetTitle(Xtitle);
  tH1FObject->GetYaxis()->SetTitle(Ytitle);
}
void setTitleNone(TH1F* tH1FObject){
  tH1FObject->SetTitle("");
  tH1FObject->GetXaxis()->SetTitle("");
  tH1FObject->GetYaxis()->SetTitle("");
}