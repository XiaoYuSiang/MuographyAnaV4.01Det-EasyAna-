#include <iterator>
#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <map>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TEllipse.h>
#include <TGaxis.h>
#include <TText.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include "./DBMMath.h"
#include "../RPU/DBMTCanvas.h"
using namespace std;
using namespace DBMMath;

void Incenter(const float a[2], const float b[2], const float c[2], float &Ix, float &Iy){
  float lab = sqrt(pow((b[0]-a[0]),2)+pow((b[1]-a[1]),2));
  float lac = sqrt(pow((c[0]-a[0]),2)+pow((c[1]-a[1]),2));
  float lbc = sqrt(pow((c[0]-b[0]),2)+pow((c[1]-b[1]),2));
  Ix = (a[0]*lbc+b[0]*lac+c[0]*lab)/(lab+lac+lbc);
  Iy = (a[1]*lbc+b[1]*lac+c[1]*lab)/(lab+lac+lbc);
}
void Circumcenter(const float a[2], const float b[2], const float c[2], float &Ox, float &Oy){
  // cout<<a[0]<<"\t"<<a[1]<<endl;
  // cout<<b[0]<<"\t"<<b[1]<<endl;
  // cout<<c[0]<<"\t"<<c[1]<<endl;

  float d1 = (c[0]-a[0])*(b[0]-a[0])+(c[1]-a[1])*(b[1]-a[1]);
  float d2 = (c[0]-b[0])*(a[0]-b[0])+(c[1]-b[1])*(a[1]-b[1]);
  float d3 = (a[0]-c[0])*(b[0]-c[0])+(a[1]-c[1])*(b[1]-c[1]);
  // cout<<d1<<"\t"<<d2<<"\t"<<d3<<"\t"<<endl;

  float c1 = d2*d3, c2 = d3*d1, c3 = d1*d2;
  float cal= c1+c2+c3;
  Ox = ((c2+c3)*a[0]+(c3+c1)*b[0]+(c1+c2)*c[0])/2./cal;
  Oy = ((c2+c3)*a[1]+(c3+c1)*b[1]+(c1+c2)*c[1])/2./cal;
  // cout<<Ox<<"\t"<<Oy<<endl;
  // cout<<endl;
}
void InterSection2Circle(TEllipse* E1, TEllipse* E2, vector<float> *pos){
  float pa[2]={E1->GetX1(), E1->GetY1()};
  float pb[2]={E2->GetX1(), E2->GetY1()};
  // cout<<"pa X:Y = "<<pa[0]<<":"<<pa[1]<<endl;
  // cout<<"pb X:Y = "<<pb[0]<<":"<<pb[1]<<endl;
  float ra = E1->GetR1();
  float rb = E2->GetR2();
  // cout<<"ra = "<<ra<<endl;
  // cout<<"rb = "<<rb<<endl;
  float alpha = (pa[0]-pb[0])/(pb[1]-pa[1]);
  float beta  = (rb*rb-ra*ra+pa[1]*pa[1]-pb[1]*pb[1]+pa[0]*pa[0]-pb[0]*pb[0])/(2*(pa[1]-pb[1]));
  // cout<<"x = "<<alpha<<"y + "<<beta<<endl;
  float a = alpha*alpha+1;
  float b = 2*alpha*(beta-pa[1])-2*pa[0];
  float c = pow(beta-pa[1],2)+pa[0]*pa[0]-ra*ra;
  pos[0].push_back((-b+sqrt(b*b-4*a*c))/(2*a));
  pos[0].push_back((-b-sqrt(b*b-4*a*c))/(2*a));
  pos[1].push_back(alpha*pos[0][0]+beta);
  pos[1].push_back(alpha*pos[0][1]+beta);
}

class DBMVennDiagram{
  private:
    TCanvas *cVennDia;
    char *CTitle, *CName;
    float xmin, xmax, ymin, ymax;
    float xmean, ymean, RangeSize[2];
    bool logMode;
    float na, nb, nc, nbc, nab, nac, nabc, nEls;
    float ra, rb, rc;
    float pa[2], pb[2], pc[2], pg[2];

    TEllipse *ela, *elb, *elc;

    float la_g, lb_g, lc_g;
    float dga[2], dgb[2], dgc[2];
    float pap[2], pbp[2], pcp[2];
    
    float pgabc[2][4], pgabcp[2][4], gabcp[2][4];

    vector<float> pcacb[2],pcacc[2],pcbcc[2];
    float pI1[2], pI2[2], pI3[2], pI4[2], pI5[2], pI6[2];
    float pab[2], pac[2], pbc[2], pabc[2];
    
    TText *Tna, *Tnb, *Tnc;
    TText *Tnbc, *Tnab, *Tnac, *Tnabc;
    TText *TnEls;
    TLegend *Leg, *LScaTitle, *LCTitle;
    char *nameA, *nameB, *nameC;
  public:
    DBMVennDiagram(
      const float Na=1, const float Nb=2, const float Nc=3, const bool LogMode = true,
      const float Nab=0, const float Nac=0, const float Nbc=0, const float Nabc=0, const float NEls=0,
      const char *NameA="A",const char *NameB="B",const char *NameC="C"
    ){
      SetN(Na, Nb, Nc, Nab, Nac, Nbc, Nabc, NEls);
      SetTitle(""); 
      SetName(Form("ctmp_%0.f_%0.f_%0.f_%0.f_%0.f_%0.f_%0.f_%0.f_%0.f_%s_%s_%s",
        Na, Nb, Nc, LogMode*1.0, Nab, Nac, Nbc, Nabc, NEls, NameA, NameB , NameC)); 
      // cout<<Na<<"\t"<< Nb<<"\t"<< Nc<<"\t"<< Nbc<<"\t"<< Nab<<"\t"<< Nac<<"\t"<< Nabc<<endl;
      // cout<<na<<"\t"<< nb<<"\t"<< nc<<"\t"<< nbc<<"\t"<< nab<<"\t"<< nac<<"\t"<< nabc<<endl;
      SetLogR(LogMode);
      SetGatherName(NameA, NameB, NameC);
      // Draw();
    };
    virtual ~DBMVennDiagram(){};
    void SetNS(float Na,float Nb,float Nc){ na = Na, nb = Nb, nc = Nc; };
    void SetND(float Nab,float Nac,float Nbc){ nab = Nab; nac = Nac; nbc = Nbc; };
    void SetNT(float Nabc, float NEls){ nabc = Nabc; nEls = NEls; };
    void SetN(float Na,float Nb,float Nc,float Nab,float Nac,float Nbc,float Nabc,float NEls){
      SetNS(Na, Nb, Nc);     SetND(Nab, Nac, Nbc);     SetNT(Nabc,NEls);
    }
    void SetLogR(bool LogMode){ logMode = LogMode; };
    void SetGatherName(const char *NameA,const char *NameB,const char *NameC){
      nameA = Form("%s",NameA); nameB = Form("%s",NameB); nameC = Form("%s",NameC); 
    }
    void SetTitle(const char *Cantitle){ CTitle = Form(Cantitle); };
    void SetName (const char *CanName ){ CName  = Form(CanName);  };
    void CalculateAll(){
      Cal_Radius();
      Cal_ElliCenter();
      Set_Ellipses();
      Cal_WeightCent();
      Cal_Boundry();
      Cal_TPosNSingle();
      Cal_TPosNMutiple();
    }
    void SetObjects(){
      Set_Texts();
      Set_Canvas();
      Set_Legend();
    }
    void Draw(){
      CalculateAll();
      SetObjects();
      Draw_Legend();
      Draw_Ellipses();
      Draw_Texts();
    }
    void Draw(TCanvas *cBG){
      Draw();
      DrawPadCloneOn(this->GetCanvas(),cBG);
      this->GetCanvas()->Close();
    }
    void Draw(TVirtualPad *cBG){
      Draw();
      DrawPadCloneOn(this->GetCanvas(),cBG);
      this->GetCanvas()->Close();
    }
    TCanvas *GetCanvas(){ return cVennDia; };
    TLegend *GetLegend(){ return Leg; };

  protected:
    void DrawTextAlign(TText *tt, int align = 22){
      tt->SetTextAlign(align); 
      tt->Draw("same");
    }
    void Set_Canvas(){
      cVennDia = new TCanvas(CName,CTitle,1280,0,640+4,640+28);
      cVennDia->Range(
        xmean-RangeSize[0],   ymean-RangeSize[1],
        xmean+RangeSize[0],   ymean+RangeSize[1]
      );
      // cout<<"Canvas Range: Xm/Ym/XM/YM\t";
      // cout<<xmean-RangeSize[0]*1.2<<"\t"<<ymean-RangeSize[1]*1.2<<"\t"<<xmean+RangeSize[0]*1.2<<"\t"<<ymean+RangeSize[1]*1.2<<"\n";
    }
    void Cal_ElliCenter(){
      pa[0] = 0; pa[1] = 0; pb[0] = rb/sqrt(2.); pb[1]=rb/sqrt(2.);
      pc[1] = 0.25*sqrt(2.)*rb+sqrt(0.5*rc*rc-0.125*rb*rb);
      pc[0] = -sqrt(rc*rc-pc[1]*pc[1]);
      // cout<<"pa : "<<pa[0]<<"\t"<<pa[1]<<"\n";
      // cout<<"pb : "<<pb[0]<<"\t"<<pb[1]<<"\n";
      // cout<<"pc : "<<pc[0]<<"\t"<<pc[1]<<"\n";
    }
    void Set_Ellipses(){
      ela = new TEllipse(pa[0],pa[1],ra,ra);
      elb = new TEllipse(pb[0],pb[1],rb,rb);
      elc = new TEllipse(pc[0],pc[1],rc,rc);
      // cout<<"ela: r1/r2/x1/y1: "<<ela->GetR1()<<"\t"<<ela->GetR2()<<"\t"<<ela->GetX1()<<"\t"<<ela->GetY1()<<endl;
      // cout<<"elb: r1/r2/x1/y1: "<<elb->GetR1()<<"\t"<<elb->GetR2()<<"\t"<<elb->GetX1()<<"\t"<<elb->GetY1()<<endl;
      // cout<<"elc: r1/r2/x1/y1: "<<elc->GetR1()<<"\t"<<elc->GetR2()<<"\t"<<elc->GetX1()<<"\t"<<elc->GetY1()<<endl;
      ela->SetFillColor(2.); elb->SetFillColor(3); elc->SetFillColor(4);
      ela->SetFillStyle(3505); elb->SetFillStyle(3552); elc->SetFillStyle(3559);
      // ela->SetFillColor(0); elb->SetFillColor(0); elc->SetFillColor(0);
    }
    void Cal_WeightCent(){
      
      pg[0] = (pa[0]+pb[0]+pc[0])/3.; pg[1] = (pa[1]+pb[1]+pc[1])/3.;
      // cout<<(pa[0]+pb[0]+pc[0])/3.<<"\t"<<(pa[1]+pb[1]+pc[1])/3.<<"\n";
    }
    void Cal_CircumCent(){}
    void Cal_Boundry(){
      xmin=-sqrt(rc*rc-pc[1]*pc[1])-rc;
      xmax=pb[0]+rb;
      ymin=-ra;
      ymax=pc[1]+rc;
      xmean = (xmin+xmax)/2., ymean = (ymin+ymax)/2.;
      RangeSize[0] = (xmax-xmean)*1.2; RangeSize[1] = (ymax-ymean)*1.2;
    }
    void Cal_Radius(){
     if(logMode){
        ra = log10(na), rb = log10(nb), rc= log10(nc);
     }else{
        ra =  sqrt(na), rb =  sqrt(nb), rc=  sqrt(nc);
     }
      // cout<<"n a:b:c: "<<na<<"\t"<<nb<<"\t"<<nc<<"\t"<<endl;
      // cout<<"r a:b:c: "<<ra<<"\t"<<rb<<"\t"<<rc<<"\t"<<endl;
    }
    void Cal_CurIntersection(){
      InterSection2Circle(ela,elb,pcacb);
      InterSection2Circle(ela,elc,pcacc);
      InterSection2Circle(elb,elc,pcbcc);
      pI1[0] = pcacb[0][0]; pI1[1] = pcacb[1][0];
      pI2[0] = pcacb[0][1]; pI2[1] = pcacb[1][1];
      pI3[0] = pcacc[0][0]; pI3[1] = pcacc[1][0];
      pI4[0] = pcacc[0][1]; pI4[1] = pcacc[1][1];
      pI5[0] = pcbcc[0][0]; pI5[1] = pcbcc[1][0];
      pI6[0] = pcbcc[0][1]; pI6[1] = pcbcc[1][1];
    }
    void Cal_TPosNSingle(){
      // cout<<"pg : "<<pg[0]<<"\t"<<pg[1]<<"\n";
      la_g = sqrt( pow(pg[0]-pa[0],2)+pow(pg[1]-pa[1],2));
      lb_g = sqrt( pow(pg[0]-pb[0],2)+pow(pg[1]-pb[1],2));
      lc_g = sqrt( pow(pg[0]-pc[0],2)+pow(pg[1]-pc[1],2));
      // cout<<"la_g/lb_g/lc_g : "<<la_g<<"\t"<<lb_g<<"\t"<<lc_g<<"\n";
      // cout<<"la_g/lb_g/lc_g : "<<distance(pg,pa)<<"\t"<<distance(pg,pb)<<"\t"<<distance(pg,pc)<<"\n";
      dga[0] = (pa[0]-pg[0])/la_g; dga[1] = (pa[1]-pg[1])/la_g;
      dgb[0] = (pb[0]-pg[0])/lb_g; dgb[1] = (pb[1]-pg[1])/lb_g; 
      dgc[0] = (pc[0]-pg[0])/lc_g; dgc[1] = (pc[1]-pg[1])/lc_g; 
      pap[0] = pa[0]+0.5*ra*dga[0];pap[1] = pa[1]+0.5*ra*dga[1]; 
      pbp[0] = pb[0]+0.5*rb*dgb[0];pbp[1] = pb[1]+0.5*rb*dgb[1]; 
      pcp[0] = pc[0]+0.5*rc*dgc[0];pcp[1] = pc[1]+0.5*rc*dgc[1]; 
      // cout<<"pap : "<<pap[0]<<"\t"<<pap[1]<<"\n";
      // cout<<"pbp : "<<pbp[0]<<"\t"<<pbp[1]<<"\n";
      // cout<<"pcp : "<<pcp[0]<<"\t"<<pcp[1]<<"\n";
      
    }
    void Cal_TPosNMutiple(){
      Cal_CurIntersection();
      Circumcenter(pI1,pI3,pI6,pab[0],pab[1]);
      Circumcenter(pI2,pI4,pI6,pac[0],pac[1]);
      Circumcenter(pI2,pI3,pI5,pbc[0],pbc[1]);
      Circumcenter(pI2,pI3,pI6,pabc[0],pabc[1]);
    }
    void Set_Texts(){
      Tna = new TText(pap[0],pap[1],Form("%0.f",na));
      Tnb = new TText(pbp[0],pbp[1],Form("%0.f",nb));
      Tnc = new TText(pcp[0],pcp[1],Form("%0.f",nc));
      Tnbc = new TText(pbc[0],pbc[1],Form("%0.f",nbc));
      Tnab = new TText(pab[0],pab[1],Form("%0.f",nab));
      Tnac = new TText(pac[0],pac[1],Form("%0.f",nac));
      Tnabc = new TText(pabc[0],pabc[1],Form("%0.f",nabc));
      TnEls = new TText(xmean-RangeSize[0]*0.6,ymean-RangeSize[1]*0.7,Form("%0.f",nEls));
    }
    void Set_Legend(){
      LScaTitle = new TLegend(0.8,0.95,1,1);
      LScaTitle->AddEntry("",Form((logMode?"Logarithmic Scale":"Linear Scale")),"h"); 
      Leg = new TLegend(0.8,0.75,1,0.95);
      Leg->AddEntry(ela,nameA,"F");   Leg->AddEntry(elb,nameB,"F");   Leg->AddEntry(elc,nameC,"F");
      Leg->AddEntry("","Else Case","F");
      LCTitle = new TLegend(0.0,0.91,1,1);
      LCTitle->AddEntry("",Form("%s",CTitle),"h"); 
      LCTitle->SetLineColor(0);
    }
    void Draw_Ellipses(){
      ela->Draw(); elb->Draw(); elc->Draw();
    }
    void Draw_Texts(){
      DrawTextAlign(Tna,22);    DrawTextAlign(Tnb,22);    DrawTextAlign(Tnc,22);
      DrawTextAlign(Tnbc,22);   DrawTextAlign(Tnab,22);   DrawTextAlign(Tnac,22);
      DrawTextAlign(Tnabc,22);  DrawTextAlign(TnEls,22);
    }
    void Draw_TestTG(){
      float pgabc[2][4] = {{pa[0],pb[0],pc[0],pa[0]},{pa[1],pb[1],pc[1],pa[1]}};
      TGraph *gabc = new TGraph(4,pgabc[0],pgabc[1]);
      gabc->Draw("plsame");
      float pgabcp[2][4] = {{pap[0],pbp[0],pcp[0],pap[0]},{pap[1],pbp[1],pcp[1],pap[1]}};
      TGraph *gabcp = new TGraph(4,pgabcp[0],pgabcp[1]);
      gabcp->Draw("plsame");
      TGraph *gcacbs = new TGraph(2,pcacb[0].data(),pcacb[1].data());
      gcacbs->SetMarkerStyle(33);
      gcacbs->Draw("plsame");
      TGraph *gcaccs = new TGraph(2,pcacc[0].data(),pcacc[1].data());
      gcaccs->SetMarkerStyle(33);
      gcaccs->Draw("plsame");
      TGraph *gcbccs = new TGraph(2,pcbcc[0].data(),pcbcc[1].data());
      gcbccs->SetMarkerStyle(33);
      gcbccs->Draw("plsame");
      int pgg[2][1] = {pg[0],pg[1]};
      TGraph *gg = new TGraph(1,pgg[0],pgg[1]);
      gg->SetMarkerStyle(35);
      gg->Draw("psame");
    }
    void Draw_TestIs(){
      TText *TIs[6];
      TIs[0] = new TText(pI1[0],pI1[1],Form("IA"));
      TIs[1] = new TText(pI2[0],pI2[1],Form("IB"));
      TIs[2] = new TText(pI3[0],pI3[1],Form("IC"));
      TIs[3] = new TText(pI4[0],pI4[1],Form("ID"));
      TIs[4] = new TText(pI5[0],pI5[1],Form("IE"));
      TIs[5] = new TText(pI6[0],pI6[1],Form("IF"));
      for(int i=0;i<6;i++){
        TIs[i]->SetTextAlign(22); TIs[i]->Draw();
      }
    }
    void Draw_Legend(){
      LCTitle->Draw("same"); 
      LScaTitle->Draw("same"); 
      Leg->Draw("same"); 
    };
    
};


void ExampleDiagram(){/*example*/
  DBMVennDiagram *testDia = new DBMVennDiagram(16,25,81,false,4,7,20,3,70);
  // TCanvas *c1 = new TCanvas("c1","qwd",1080,1080);
  // testDia->Draw(c1);
  testDia->SetGatherName("CaseA","CaseB","CaseC");
  testDia->SetTitle("Venn Graph of All Case Select by Condition A B C");
  testDia->Draw();
  
  testDia->GetCanvas()->Print("testDiagram.png");
  cout<<testDia->GetCanvas()->GetTitle()<<endl;
  cout<<testDia->GetCanvas()->GetName()<<endl;
  // testDia->Draw_TestTG();
  // testDia->Draw_TestIs();
}



/*
void Diagram(){

  TCanvas *c = new TCanvas("c","c",1280,0,640+4,640+28);
  int na = 100, nb =1200, nc = 5000;
  int nbc = 50; int nab = 3; int nac = 7;
  int nabc = 3;
  float ra = log10(na*1.), rb =log10(nb*1.), rc=log10(nc*1.);
  cout<<"n a:b:c: "<<na<<"\t"<<nb<<"\t"<<nc<<"\t"<<endl;
  cout<<"r a:b:c: "<<ra<<"\t"<<rb<<"\t"<<rc<<"\t"<<endl;
  float pa[2] = {0,0}, pb[2] = {rb/sqrt(2),rb/sqrt(2)};
  float pc[2] = {0};
  pc[1] = 0.25*sqrt(2)*rb+sqrt(0.5*rc*rc-0.125*rb*rb);
  pc[0] = -sqrt(rc*rc-pc[1]*pc[1]);
  float pg[2] = {(pa[0]+pb[0]+pc[0])/3.,(pa[1]+pb[1]+pc[1])/3.};
  TEllipse *ela = new TEllipse(pa[0],pa[1],ra,ra);
  TEllipse *elb = new TEllipse(pb[0],pb[1],rb,rb);
  TEllipse *elc = new TEllipse(pc[0],pc[1],rc,rc);
  ela->SetFillStyle(3001); elb->SetFillStyle(3001); elc->SetFillStyle(3001);
  ela->SetFillColor(0); elb->SetFillColor(0); elc->SetFillColor(0);
  ela->Draw(); elb->Draw(); elc->Draw();

  float xmin=-sqrt(rc*rc-pc[1]*pc[1])-rc;
  float xmax=pb[0]+rb;
  float ymin=-ra;
  float ymax=pc[1]+rc;
  float xmean = (xmin+xmax)/2., ymean = (ymin+ymax)/2.;
  float RangeSize[2]={xmax-xmean,ymax-ymean};
  c->Range(xmean-RangeSize[0]*1.2,ymean-RangeSize[1]*1.2,xmean+RangeSize[0]*1.2,ymean+RangeSize[1]*1.2);

  float db_c[2] = {(pb[0]-pc[0])/rc,(pc[1]-pb[1])/rc};

  float la_g = distance(pg,pa), lb_g = distance(pg,pb), lc_g = distance(pg,pc);
  float dga[2] = {(pa[0]-pg[0])/la_g,(pa[1]-pg[1])/la_g};
  float dgb[2] = {(pb[0]-pg[0])/lb_g,(pb[1]-pg[1])/lb_g};
  float dgc[2] = {(pc[0]-pg[0])/lc_g,(pc[1]-pg[1])/lc_g};
  
  float pap[2] = {pa[0]+0.5*ra*dga[0],pa[1]+0.5*ra*dga[1]};
  float pbp[2] = {pb[0]+0.5*rb*dgb[0],pb[1]+0.5*rb*dgb[1]};
  float pcp[2] = {pc[0]+0.5*rc*dgc[0],pc[1]+0.5*rc*dgc[1]};

  TText *Tna = new TText(pap[0],pap[1],Form("%d",na));
  Tna->SetTextAlign(22); Tna->Draw();

  TText *Tnb = new TText(pbp[0],pbp[1],Form("%d",nb));
  Tnb->SetTextAlign(22); Tnb->Draw();

  TText *Tnc = new TText(pcp[0],pcp[1],Form("%d",nc));
  Tnc->SetTextAlign(22); Tnc->Draw();


  float pgabc[2][4] = {{pa[0],pb[0],pc[0],pa[0]},{pa[1],pb[1],pc[1],pa[1]}};
  TGraph *gabc = new TGraph(4,pgabc[0],pgabc[1]);
  // gabc->Draw("plsame");

  float pgabcp[2][4] = {{pap[0],pbp[0],pcp[0],pap[0]},{pap[1],pbp[1],pcp[1],pap[1]}};
  TGraph *gabcp = new TGraph(4,pgabcp[0],pgabcp[1]);
  // gabcp->Draw("plsame");


  vector<float> pcacb[2],pcacc[2],pcbcc[2];
  InterSection2Circle(ela,elb,pcacb);
  InterSection2Circle(ela,elc,pcacc);
  InterSection2Circle(elb,elc,pcbcc);
  cout<<pcacb[0][0]<<"\t"<<pcacb[1][0]<<endl;
  cout<<pcacb[0][1]<<"\t"<<pcacb[1][1]<<endl;
  
  TGraph *gcacbs = new TGraph(2,pcacb[0].data(),pcacb[1].data());
  gcacbs->SetMarkerStyle(33);
  gcacbs->Draw("plsame");
  TGraph *gcaccs = new TGraph(2,pcacc[0].data(),pcacc[1].data());
  gcaccs->SetMarkerStyle(33);
  gcaccs->Draw("plsame");
  TGraph *gcbccs = new TGraph(2,pcbcc[0].data(),pcbcc[1].data());
  gcbccs->SetMarkerStyle(33);
  gcbccs->Draw("plsame");
  float pI1[2] = {pcacb[0][0],pcacb[1][0]};
  float pI2[2] = {pcacb[0][1],pcacb[1][1]};
  float pI3[2] = {pcacc[0][0],pcacc[1][0]};
  float pI4[2] = {pcacc[0][1],pcacc[1][1]};
  float pI5[2] = {pcbcc[0][0],pcbcc[1][0]};
  float pI6[2] = {pcbcc[0][1],pcbcc[1][1]};
  
  TText *TIs[6];
  TIs[0] = new TText(pI1[0],pI1[1],Form("IA"));
  TIs[1] = new TText(pI2[0],pI2[1],Form("IB"));
  TIs[2] = new TText(pI3[0],pI3[1],Form("IC"));
  TIs[3] = new TText(pI4[0],pI4[1],Form("ID"));
  TIs[4] = new TText(pI5[0],pI5[1],Form("IE"));
  TIs[5] = new TText(pI6[0],pI6[1],Form("IF"));
  for(int i=0;i<6;i++){
    TIs[i]->SetTextAlign(22); TIs[i]->Draw();
  }
  
  
  float pab[2]={0}; Circumcenter(pI1,pI3,pI6,pab[0],pab[1]);
  float pac[2]={0}; Circumcenter(pI2,pI4,pI6,pac[0],pac[1]);
  float pbc[2]={0}; Circumcenter(pI2,pI3,pI5,pbc[0],pbc[1]);
  float pabc[2]={0};Circumcenter(pI2,pI3,pI6,pabc[0],pabc[1]);
  
  TText *Tnbc = new TText(pbc[0],pbc[1],Form("%d",nbc));
  Tnbc->SetTextAlign(22); Tnbc->Draw();

  TText *Tnab = new TText(pab[0],pab[1],Form("%d",nab));
  Tnab->SetTextAlign(22); Tnab->Draw();

  TText *Tnac = new TText(pac[0],pac[1],Form("%d",nac));
  Tnac->SetTextAlign(22); Tnac->Draw();

  TText *Tnabc = new TText(pabc[0],pabc[1],Form("%d",nabc));
  Tnabc->SetTextAlign(22); Tnabc->Draw();
}


*/