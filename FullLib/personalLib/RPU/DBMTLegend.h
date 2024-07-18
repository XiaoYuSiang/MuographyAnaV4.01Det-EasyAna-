#include <vector>
#include <typeinfo>
#include <algorithm>
#include <TMath.h>
#include <TRandom.h>
#include <TF1.h>
void setLegendDefault(TLegend* tLegendObject){
  tLegendObject->SetFillColorAlpha (0, 0.00);
  tLegendObject->SetLineColorAlpha (0, 0.00);
}
void setLegendDefault(TLegend* tLegendObject,Int_t col){
  tLegendObject->SetFillColorAlpha (0, 0.00);
  tLegendObject->SetLineColorAlpha (0, 0.00);
  tLegendObject->SetNColumns(col);
}
void drawTF1LegendsCan(TF1 *TF1Object,char *TF1Title,double Lxm,double Lym,double LxM,double LyM,TCanvas *TCanvasObject,int PadIndex){
  int NumPar=0;
  while(strcmp(TF1Object->GetParName(NumPar),"")!=0||TF1Object->GetParameter(NumPar)!=0) NumPar++;
  //cout<<"i par"<<i<<endl;
  float 
    heiT   = 1,
    heiB   = 0,
    heio   = heiT-heiB,
    heiM   = heiT-heio/(0.05*2+0.03*NumPar)*0.1,
    wido   = 1.,
    widoL  = 0.,
    widoR  = 1.,
    widNamR= widoL+16./33.*wido,
    widVaoL= widoL+10./33.*wido,
    widVaoR= widoL+28./33.*wido,
    widPMoL= widoL+18.5/33.*wido,
    widPMoR= widoL+20.5/33.*wido,
    WidEroL= widoL+20./33.*wido,
    WidEroR= widoR+0.3;
    
  TLegend *LTF1Main  = new TLegend(widoL,(heiM+heiT)/2,widoR,heiT);
  TLegend *LTF1XNDF  = new TLegend(widoL,heiM,widoR,(heiM+heiT)/2);
  TLegend *LTF1Name  = new TLegend(widoL  ,heiB,widNamR,heiM);
  TLegend *LTF1Valu  = new TLegend(widVaoL,heiB,widVaoR,heiM);
  TLegend *LTF1PanM  = new TLegend(widPMoL,heiB,widPMoR,heiM);
  TLegend *LTF1Erro  = new TLegend(WidEroL,heiB,WidEroR,heiM);
  
  setLegendDefault(LTF1Main);
  setLegendDefault(LTF1XNDF);
  setLegendDefault(LTF1Name);
  setLegendDefault(LTF1Valu);
  setLegendDefault(LTF1PanM);
  setLegendDefault(LTF1Erro);
  if(strcmp(TF1Title,"")!=0) LTF1Main ->AddEntry(TF1Object,TF1Title,"l");
  else LTF1Main ->AddEntry(TF1Object,Form("%s",TF1Object->GetTitle()),"l");
  LTF1XNDF->AddEntry("",Form("#chi^{2}=%.4f    NDF=%d    #chi^{2}/NDF=%.4f",TF1Object->GetChisquare(),TF1Object->GetNDF(),TF1Object->GetChisquare()/TF1Object->GetNDF()),"h");
  for(int iN=0;iN<NumPar;iN++){
    LTF1Name->AddEntry("",Form("%s",TF1Object->GetParName(iN)),"h");
    LTF1Valu->AddEntry("",Form("\t%.4f    ",TF1Object->GetParameter(iN)),"h");
    LTF1PanM->AddEntry("","#pm","h");
    LTF1Erro->AddEntry("",Form("%.4f    ",TF1Object->GetParError(iN)),"h");
  }
    
  if(PadIndex==-1) TCanvasObject->cd();
  else TCanvasObject->cd(PadIndex);
  TPad *LegendPad = new TPad("Pad","Pad",Lxm,Lym,LxM,LyM);
  LegendPad->SetLineColorAlpha(0,0);
  LegendPad->SetFillColorAlpha(0,0);
  LegendPad->SetLeftMargin(0);
  LegendPad->SetBottomMargin(0);
  LegendPad->SetRightMargin(1);
  LegendPad->SetTopMargin(1);
  LegendPad->Draw();
  LegendPad->cd();
  LTF1Main->Draw("same");
  LTF1XNDF->Draw("same");
  LTF1Name->Draw("same");
  LTF1Valu->Draw("same");
  LTF1PanM->Draw("same");
  LTF1Erro->Draw("same");
  if(PadIndex==-1) TCanvasObject->cd();
  else TCanvasObject->cd(PadIndex);
}
TPad *drawTF1LegendsCan(TF1 *TF1Object,char *TF1Title,double Lxm,double Lym,double LxM,double LyM,TCanvas *TCanvasObject){
  int NumPar=0;
  while(strcmp(TF1Object->GetParName(NumPar),"")!=0||TF1Object->GetParameter(NumPar)!=0) NumPar++;
  //cout<<"i par"<<i<<endl;
  float 
    heiT   = 1,
    heiB   = 0,
    heio   = heiT-heiB,
    heiM   = heiT-heio/(0.05*2+0.03*NumPar)*0.1,
    wido   = 1.,
    widoL  = 0.,
    widoR  = 1.,
    widNamR= widoL+16./33.*wido,
    widVaoL= widoL+10./33.*wido,
    widVaoR= widoL+28./33.*wido,
    widPMoL= widoL+18.5/33.*wido,
    widPMoR= widoL+20.5/33.*wido,
    WidEroL= widoL+20./33.*wido,
    WidEroR= widoR+0.3;
    
  TLegend *LTF1Main  = new TLegend(widoL,(heiM+heiT)/2,widoR,heiT);
  TLegend *LTF1XNDF  = new TLegend(widoL,heiM,widoR*1.2,(heiM+heiT)/2);
  TLegend *LTF1Name  = new TLegend(widoL  ,heiB,widNamR,heiM);
  TLegend *LTF1Valu  = new TLegend(widVaoL,heiB,widVaoR,heiM);
  TLegend *LTF1PanM  = new TLegend(widPMoL,heiB,widPMoR,heiM);
  TLegend *LTF1Erro  = new TLegend(WidEroL,heiB,WidEroR,heiM);
  
  setLegendDefault(LTF1Main);
  setLegendDefault(LTF1XNDF);
  setLegendDefault(LTF1Name);
  setLegendDefault(LTF1Valu);
  setLegendDefault(LTF1PanM);
  setLegendDefault(LTF1Erro);
  if(strcmp(TF1Title,"")!=0) LTF1Main ->AddEntry(TF1Object,TF1Title,"l");
  else LTF1Main ->AddEntry(TF1Object,Form("%s",TF1Object->GetTitle()),"l");
  LTF1XNDF->AddEntry("",Form("#chi^{2}=%.4f    NDF=%d    #chi^{2}/NDF=%.4f",TF1Object->GetChisquare(),TF1Object->GetNDF(),TF1Object->GetChisquare()/TF1Object->GetNDF()),"h");
  for(int iN=0;iN<NumPar;iN++){
    if(TF1Object->GetParameter(iN)<2&&iN==1){
      LTF1Name->AddEntry("",Form("#color[2]{%s}",TF1Object->GetParName(iN)),"h");
    }else LTF1Name->AddEntry("",Form("%s",TF1Object->GetParName(iN)),"h");
    
    LTF1Valu->AddEntry("",Form("\t%.4f    ",TF1Object->GetParameter(iN)),"h");
    LTF1PanM->AddEntry("","#pm","h");
    LTF1Erro->AddEntry("",Form("%.4f    ",TF1Object->GetParError(iN)),"h");
  }
  //TCanvasObject->cd();
  TPad *LegendPad = new TPad("Pad","Pad",Lxm,Lym,LxM,LyM);
  LegendPad->SetLineColorAlpha(0,0);
  LegendPad->SetFillColorAlpha(0,0);
  LegendPad->SetLeftMargin(0);
  LegendPad->SetBottomMargin(0);
  LegendPad->SetRightMargin(1);
  LegendPad->SetTopMargin(1);
  LegendPad->Draw();
  LegendPad->cd();
  LTF1Main->Draw("same");
  LTF1XNDF->Draw("same");
  LTF1Name->Draw("same");
  LTF1Valu->Draw("same");
  LTF1PanM->Draw("same");
  LTF1Erro->Draw("same");
  TCanvasObject->cd();
  return LegendPad;
}