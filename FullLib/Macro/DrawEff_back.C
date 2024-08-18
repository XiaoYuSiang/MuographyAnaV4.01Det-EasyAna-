#include <typeinfo>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TKey.h>
#include <TGaxis.h>
#include <TText.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TPaveText.h>
#include <TObjString.h>
#include <TGraphErrors.h>
#include "AnaVariable.h"
#include "path_dir.h"
#include "DSLData.h"
#include "LoadChTable.h"
#include "TF1.h"

using namespace std;
using namespace MuoAna_path_dir;
using namespace MuographAnaVariable;
using namespace DataConst;

const double EffSet = 0.80;
void DrawEff(  const int index = 28)
{
  gStyle->SetPadLeftMargin(0.08);
  gStyle->SetPadRightMargin(0.18);
  gStyle->SetPaintTextFormat(".2f");
  
  std::map<int, ChSet> ChTable;
  LoadChTable(ChTable,DirDetector+"ChannelTable"+DetectorGeoSet+".dat");
  ChSet PosTable[(RiX[1]-RiX[0])/DRiX+1][(RiY[1]-RiY[0])/DRiY+1][(RiZ[1]-RiZ[0])/DRiZ+1];
  int iCom = 0;
  for(int ich = 0 ; ich < int(ChTable.size()) ; ich++ ){
    ChSet POSTMP(ChTable[ich]);
    POSTMP.Alive = true;
    iCom++;
    PosTable[(POSTMP.IX-RiX[0])/DRiX][(POSTMP.IY-RiY[0])/DRiY][(POSTMP.IZ-RiZ[0])/DRiZ] = POSTMP;
    
    // cout<<POSTMP.IX<<"\t"<<POSTMP.IY<<"\t"<<POSTMP.IZ<<"\t"<<POSTMP.GCH<<"\t"<<POSTMP.IBD<<"\t"<<POSTMP.ICH<<endl;
  }
  cout<<"iCom = "<<iCom<<endl;
  double eventGap = eventGapTcnt[index]*1.;
  const string finName = Form("%sSTGapT%d_%s_nHTH%dL%d.root",DirOperate.data(),int(eventGap),TimeStr,TriggerS,TriggerL);

  const int NumLY = 4;
  TFile *fIn = new TFile(finName.data(),"open");
  TTree *t = (TTree*) fIn->Get("t");
  int nbinsX = (RiX[1]-RiX[0])/DRiX+1, nbinsY = (RiY[1]-RiY[0])/DRiY+1;
  int RIXbin[2] = {RiX[0]-1,RiX[1]+1};
  int RIYbin[2] = {RiY[0]-1,RiY[1]+1};
  TH2F *hFull[NumLY-2];
  TH2F *hLose[NumLY-2];
  int TID[NumLY-2];
  int FullTID = 0;
  for(int iLY=0;iLY<NumLY;iLY++) FullTID+= pow(10,iLY);
  for(int iLY=1;iLY<NumLY-1;iLY++){
    TID[iLY-1] = FullTID-pow(10,NumLY-iLY-1);
    hLose[iLY-1] = new TH2F("hLost","",nbinsX,RIXbin[0],RIXbin[1],nbinsY,RIYbin[0],RIYbin[1]);
    hLose[iLY-1]->SetName(Form("h%d",TID[iLY-1]));
    hLose[iLY-1]->SetTitle(Form("Lost @ Z=%d ;iX;iY;  Count",iLY));
    hLose[iLY-1]-> GetYaxis() -> SetTitleOffset(1.2);
    hFull[iLY-1] = new TH2F("hFull","",nbinsX,RIXbin[0],RIXbin[1],nbinsY,RIYbin[0],RIYbin[1]);
    hFull[iLY-1]->SetName(Form("h%d@%d",TID[iLY-1],iLY));
    hFull[iLY-1]->SetTitle(Form("All catch @ Z=%d;iX;iY;  Count",iLY));

    hFull[iLY-1]-> GetYaxis() -> SetTitleOffset(1.2);
    hFull[iLY-1]-> GetZaxis() -> SetTitleOffset(1.6);
    hFull[iLY-1]-> GetZaxis() -> RotateTitle(1);
    hFull[iLY-1]-> GetZaxis() -> SetLabelSize(0.03);
    hFull[iLY-1]-> GetXaxis() -> CenterTitle(1);
    hFull[iLY-1]-> GetYaxis() -> CenterTitle(1);

    hFull[iLY-1]->GetXaxis()->SetNdivisions(8);
    hFull[iLY-1]->GetYaxis()->SetNdivisions(8);
    //  hFull[iLY-1]-> GetYaxis() -> CenterLabel(1);
    hFull[iLY-1]-> SetStats(0);
    hFull[iLY-1]-> Sumw2(1);
  }
    
  const int NGpx = 4, NGpy = (NumLY-2);
  TCanvas *c1 = new TCanvas("c1","c1",810*NGpx+4,750*(NGpy)+28);
  
  c1->Divide(NGpx,NGpy);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadLeftMargin(0.15);
  for(int iLay=1;iLay<NumLY-1;iLay++)
    c1->cd((iLay-1)*NGpx+4)->Divide(NumBX[iLay],NumBY[iLay]);
  TF1 *gaus = new TF1("gaus", "gaus", 0.65, 0.997);
  // string tmp = "&&DiX==0&&DiY==0";
  const int NSe = 2;
  string Condition[NSe] = {"","&&DiX==0&&DiY==0"};
  string SaveGName[NSe] = {"AllSTL","iPXPY0"};
  
  TH1F *hEffAVGLine = new TH1F("hEffAVGLine","hEffAVGLine",1,0,NumCh);
  hEffAVGLine->SetLineColor(4);
  hEffAVGLine->SetLineStyle(2);
  hEffAVGLine->SetBinContent(1,EffSet);
  
  cout<<103<<endl;
  for(int iSE =0; iSE<NSe;iSE++){
    TH1F *hAllEff = new TH1F("hAllEff","All Eff. fit;Efficiency;Ratio",200,.65,1.15);
    TH1F *hAllEff2 = new TH1F("hAllEff2","All Eff. fit;Efficiency;Ratio",200,.65,1.15);
    TH2F *hEff[2], *hSum[2];
    for(int i=0;i<NumLY-2;i++){
      string Target = Form("iX0-DiX*%d:iY0-DiY*%d",i+1,i+1);
      c1->cd((i)*NGpx+1);
      t->Draw(Form("%s>>%s",Target.data(),hFull[i]->GetName()),Form("TrackID==%d%s",FullTID,Condition[iSE].data()),"colz");
      c1->cd((i)*NGpx+2);
      t->Draw(Form("%s>>%s",Target.data(),hLose[i]->GetName()),Form("TrackID==%d%s",TID[i],Condition[iSE].data()),"colz");
      hLose[i] -> Sumw2(1);
      hLose[i] -> SetStats(0);
      hLose[i] -> GetZaxis() -> SetTitleOffset(1.6);
      hLose[i] -> GetZaxis() -> SetLabelSize(0.03);
      // hLose[i] -> GetZaxis() -> SetTitleOffset(-0.4);
      hLose[i] -> GetZaxis() -> RotateTitle(1);
      hLose[i] -> GetXaxis() -> CenterTitle(1);
      hLose[i] -> GetYaxis() -> CenterTitle(1);
      
      hEff[i] = (TH2F*) hFull[i]->Clone();
      hSum[i] = (TH2F*) hFull[i]->Clone();
      hEff[i] -> SetName(Form("hEffZ%d",i+1));
      hSum[i] -> SetName(Form("hSumZ%d",i+1));
      hEff[i] -> SetTitle(Form("Efficiency @ Z = %d;iX;iY;Efficiency",i+1));
      hSum[i] -> Add(hLose[i]);
      hEff[i] -> Divide( hSum[i] );
      c1->cd((i)*NGpx+3);
      hEff[i]->Draw("coltextez");
      
    }
    // c1->Print("EffGraphDixiy0.gif");
    int iChs = 0;
    TH1F *h1[NumBD];
    for(int iBD=0;iBD<NumBD;iBD++){
      h1[iBD] = new TH1F(Form("hEffCh%02.0f",iBD*1.),Form("MTB %02.0f;Channel ID;Efficiency",BD[iBD]*1.),NumCh,0,NumCh);
      h1[iBD]->GetYaxis()->SetTitleOffset(1.6);
      h1[iBD]->GetYaxis()->SetRangeUser(0.70,1.00);
      h1[iBD]->SetStats(0);
    }
    for(int iLay=1;iLay<NumLY-1;iLay++){
      
      for(int iBinX = 1;iBinX<=nbinsX;iBinX++){
        for(int iBinY = 1;iBinY<=nbinsY;iBinY++){
          int ix = (hEff[iLay-1]->GetXaxis()->GetBinCenter(iBinX)-RiX[0])/DRiX;
          int iy = (hEff[iLay-1]->GetYaxis()->GetBinCenter(iBinY)-RiY[0])/DRiY;
          float Eff = hEff[iLay-1]->GetBinContent(iBinX,iBinY);
          float Err = hEff[iLay-1]->GetBinError(iBinX,iBinY);
          int   Sta = hSum[iLay-1]->GetBinContent(iBinX,iBinY);
          if(PosTable[ix][iy][iLay].Alive){
            int iBD = PosTable[ix][iy][iLay].IBD;
            int iCH = PosTable[ix][iy][iLay].ICH;
            int gch = PosTable[ix][iy][iLay].GCH;
            // cout<<ix<<"\t"<<iy<<"\t"<<gch<<"\t"<<iBD<<"\t"<<iCH<<"\t"<<Sta<<"\t"<<Eff<<"\t"<<Err<<endl;
            iChs++;
            h1[iBD]->SetBinContent(PosTable[ix][iy][iLay].ICH+1,Eff);
            h1[iBD]->SetBinError(PosTable[ix][iy][iLay].ICH+1,Err);
            gaus->SetParameters(1, Eff, Err);
            
            hAllEff->FillRandom("gaus",100000);
            hAllEff2->Fill(Eff);
          }
        }
      }
      for(int iBD=LayFirst[iLay];iBD<LayFirst[iLay+1];iBD++){
        c1->cd((iLay-1)*NGpx+4)->cd(iBD-LayFirst[iLay]+1);
        h1[iBD]->Draw("ep");
        hEffAVGLine->Draw("h][same");
      }
      
    }
    cout<<175<<endl;
    c1->Print((DirResultEff+"Eff"+SaveGName[iSE]+".gif").data());
    // c1->Clear();
    cout<<"ichs "<<iChs<<endl;
    TCanvas *c2 = new TCanvas("c2","c2",810+4,810+28);
    for(int i=1;i<hAllEff->GetNbinsX();i++ ){
      if(hAllEff->GetBinCenter(i)>1){
        hAllEff->Fill(1,hAllEff->GetBinContent(i));
        hAllEff->SetBinContent(i,-1);
        hAllEff->SetBinError(i,-1);
      }
    }
    cout<<hAllEff->Integral(-1,-1)<<"\t"<<hAllEff2->Integral(-1,-1)<<endl;
    hAllEff->Scale(1./hAllEff->Integral(-1,-1));
    hAllEff2->Sumw2();
    hAllEff2->Scale(1./hAllEff2->Integral(-1,-1));
    hAllEff->Fit("gaus","R");
    hAllEff->SetStats(0);
    hAllEff->Draw("he");
    hAllEff->GetFunction("gaus")->Draw("lsame");
    

    double amplitude = gaus->GetParameter(0);
    double mean = gaus->GetParameter(1);
    double sigma = gaus->GetParameter(2);
    TPaveText *pt = new TPaveText(0.7, 0.6, 0.95, 0.9, "NDC");
    pt->AddText(Form("#mu: %.4f", mean));
    pt->AddText(Form("  #pm %.4f", gaus->GetParError(1)));
    pt->AddText(Form("#sigma: %.4f", sigma));
    pt->AddText(Form("  #pm %.4f", gaus->GetParError(2)));
    pt->AddText(Form("#chi^{2}/NDF: %.2f/%d", gaus->GetChisquare(),gaus->GetNDF()));
    pt->SetFillColor(0); // Set background color to white
    pt->Draw();
    c2->Print((DirResultEff+"EffAverage"+SaveGName[iSE]+".gif").data());

    hAllEff2->Fit("gaus","R");
    hAllEff2->SetStats(0);
    hAllEff2->SetLineColor(1);
    hAllEff2->SetMarkerColor(1);
    hAllEff2->SetMarkerStyle(20);
    hAllEff2->SetLineWidth(2);
    hAllEff2->SetMarkerSize(1.5);
    hAllEff2->Draw("pe");
    hAllEff2->GetFunction("gaus")->Draw("lsame");
    amplitude = gaus->GetParameter(0);
    mean = gaus->GetParameter(1);
    sigma = gaus->GetParameter(2);
    TPaveText *p2t = new TPaveText(0.7, 0.6, 0.95, 0.9, "NDC");
    p2t->AddText(Form("#mu: %.4f", mean));
    p2t->AddText(Form("  #pm %.4f", gaus->GetParError(1)));
    p2t->AddText(Form("#sigma: %.4f", sigma));
    p2t->AddText(Form("  #pm %.4f", gaus->GetParError(2)));
    p2t->AddText(Form("#chi^{2}/NDF: %.2f/%d", gaus->GetChisquare(),gaus->GetNDF()));
    p2t->SetFillColor(0); // Set background color to white
    p2t->Draw();
    c2->Print((DirResultEff+"EffAverage2"+SaveGName[iSE]+".gif").data());
    c2->Close();
    cout<<231<<endl;
  }
  c1->Close();

}