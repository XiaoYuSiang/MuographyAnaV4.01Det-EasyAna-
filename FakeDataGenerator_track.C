#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <TRandom3.h>
#include <TH1.h>
#include <TH2F.h>
#include <TCanvas.h>

#include "./Macro/LoadChTable.h"
#include "./AnaVariable.h"
using namespace std;
using namespace MuographAnaVariable;
string DirMacros = "./Macro/" ;
string SavePath = "/data4/YuSiang/MGFakeData/";
string SaveBaseName = "FakeData_Track_E080";
int n = 300000;  // Number of entries
float delayOfEvs[2] = {400,1.0E+6};
// 1.6E+6 ~ 900 MB / day
// 2.0E+6 ~ 600 MB / day
float delayOfHits[2] = {53,15};
float nHitsSet[2] = {5,2};
float PWidthSet[2] = {15,2};
const int UT0 = 1700000000;
const int NBD = 26;
const int NCh = 16;
const float RTrack = 0.6;
const float EffSet = 0.80;
const float RNoise = 0.34;
 // ratio of track in random hit
 
class HitSet : public ChSet {
public:
    float PX, PY, PZ;
    int PWidth, NID;
    HitSet() : ChSet(), PX(0), PY(0), PZ(0) { PWidth = -1; NID = 0;}

    HitSet(int gch, int ibd, int ich, int ix, int iy, int iz, int dir, float px, float py, float pz)
        : ChSet(gch, ibd, ich, ix, iy, iz, dir), PX(px), PY(py), PZ(pz) { PWidth = -1; NID = 0;}
    HitSet(const ChSet& chset)
        : ChSet(chset), PX(chset.IX*bx_2), PY(chset.IY*by_2), PZ(chset.IZ*bz_2)
        { PWidth = -1; NID = 0;}

    virtual void Show() {
        ChSet::Show(); // 呼叫基類的 Show() 函數
        std::cout << PX << "\t" << PY << "\t" << PZ << std::endl;
    }
    ~HitSet() {}
};

void FakeDataGenerator_track() {
  std::map<int, ChSet> ChTable;
  LoadChTable(ChTable,(DirMacros+"ChannelTableV0401.dat").data());
  HitSet PosTable[(RiX[1]-RiX[0])/DRiX+1][(RiY[1]-RiY[0])/DRiY+1][(RiZ[1]-RiZ[0])/DRiZ+1];
  for(int ich = 0 ; ich < int(ChTable.size()) ; ich++ ){
    HitSet POSTMP(ChTable[ich]);
    PosTable[(POSTMP.IX-RiX[0])/DRiX][(POSTMP.IY-RiY[0])/DRiY][(POSTMP.IZ-RiZ[0])/DRiZ] = POSTMP;
    // cout<<ich<<"\t"<<POSTMP.IX<<","<<POSTMP.IY<<","<<POSTMP.IZ<<"\t"<<(POSTMP.IX-RiX[0])/DRiX<<","<<(POSTMP.IY-RiY[0])/DRiY<<","<<(POSTMP.IZ-RiZ[0])/DRiZ<<endl;
  }
  ofstream ofs;
  // throw;
  srand(time(0));  // Initialize random seed
  srand(0);  // Initialize random seed
  TRandom3 randGen(0); // Initialize ROOT random generator with seed 0
  
  
  // TH1F *h1 = new TH1F("h1","h1",256,0,256);
  // TH1F *h2 = new TH1F("h2","h2",1000,0,1000);
  int Seq[NBD][NCh]={0};
  int frame_index = 0;
  int ifile = 0;
  ofs.open(Form("%s%s_%d_Mu.txt",SavePath.data(),SaveBaseName.data(),ifile));
  // TH2F *hp0 = new TH2F("hp0","pX0 VS pY0;pX0;py0;count",880,-44,44,880,-44,44);
  // TH2F *hd0 = new TH2F("hd0","pd0 VS pd0;pd0;pd0;count",880,-44,44,880,-44,44);
  // TH2F *hp0S = new TH2F("hp0S","Select pX0 VS pY0;pX0;py0;count",880,-44,44,880,-44,44);
  // TH2F *hd0S = new TH2F("hd0S","Select pd0 VS pd0;pd0;pd0;count",880,-44,44,880,-44,44);
  for (int i = 0; frame_index < n;) {
    if(i%1000==0)
      cout<<"\r"<<100*i/float(n)<<"%"<<flush;
    if(i-(86400)*(1+ifile)>0){
      ifile++;
      ofs.close();
      cout << endl << "New File:  " << Form("%s%s_%d_Mu.txt",SavePath.data(),SaveBaseName.data(),ifile) << endl;

      ofs.open(Form("%s%s_%d_Mu.txt",SavePath.data(),SaveBaseName.data(),ifile));
    }
    long long unixtime = UT0 + i;
    int initial_tcnt = 0;
    frame_index++;
    // cout << "#Frame " << frame_index << " Unixtime " << unixtime << endl;
    ofs << "#Frame " << frame_index << " Unixtime " << unixtime << endl;
    
    for (int iseq = 0; iseq < 121; ++iseq) {
      // Calculate values
      if(randGen.Uniform(0,1) > RTrack){
        // cout<<96<<"----";
        // int Nhit = randGen.Gaus(nHitsSet[0],nHitsSet[1]);
        int Nhit = randGen.Gaus(nHitsSet[0],nHitsSet[1]);
        while(Nhit<0||Nhit>3) Nhit = randGen.Gaus(nHitsSet[0],nHitsSet[1]);
        int dtcnt = -1;
        while(dtcnt<0||dtcnt>2.56E+8) dtcnt = randGen.Landau(delayOfEvs[0], delayOfEvs[1]);
        int last_tcnt = initial_tcnt + dtcnt;
        // h2->Fill(dtcnt);

        for (int ih = 0; iseq < 121&&ih<Nhit; ++ih,++iseq) {
          int bid = rand() % NBD + 1;
          int cid = rand() % NCh;
          int seq = Seq[bid-1][cid]++;
          if(seq>1023) Seq[bid-1][cid] = 0;
          int tcnt = randGen.Gaus(delayOfHits[0],delayOfHits[1]);
          while(tcnt<0) tcnt = randGen.Gaus(delayOfHits[0],delayOfHits[1]);
          tcnt+=last_tcnt;
          if(last_tcnt>2.56E+8){
            i++;
            tcnt -= 2.56E+8;
          }
          int pcnt = i;
          double dtime = tcnt / 2.56E+8 + pcnt;
          int pwidth = randGen.Landau(1, PWidthSet[1]); 
          while(pwidth<0||pwidth>256) pwidth = randGen.Landau(1, PWidthSet[1]); 
          // h1->Fill(pwidth);
          // Output format
          string content = Form("0\t%d\t%d\t%d\t%.12f\t%d\t%d\t%d", bid, cid, seq, dtime, pcnt, tcnt, pwidth);
          ofs<<content<<endl;
          // cout<<content;
          last_tcnt = tcnt;
        }
        initial_tcnt = last_tcnt;
        // cout<<"---128"<<endl;
      }else{
        // cout<<130<<endl;
        double pX[NumLY] = {randGen.Uniform(RiX[0]-1,RiX[1]+1)};
        double pY[NumLY] = {randGen.Uniform(RiY[0]-1,RiY[1]+1)};
        double dpX = randGen.Uniform(RiX[0]-1,RiX[1]+1)/(NumLY+1.);
        double dpY = randGen.Uniform(RiY[0]-1,RiY[1]+1)/(NumLY+1.);
        // hp0->Fill(pX[0],pY[0]);
        // hd0->Fill(dpX,dpY);
        vector<HitSet> trackTMP;
        // cout<<122<<endl;
        for(int iLay=0;iLay<NumLY;iLay++){
          pX[iLay] = pX[0] + dpX*iLay;
          pY[iLay] = pY[0] + dpY*iLay;
          int tmpIX = (pX[iLay]-RiX[0]+1)/DRiX;
          int tmpIY = (pY[iLay]-RiY[0]+1)/DRiY;
          
          bool fire = 1;
          if(iLay==1||iLay==2) fire &= -8<=pX[iLay]&&pX[iLay]<=8 && -8<=pY[iLay]&&pY[iLay]<=8;
          else fire &= -12<=pX[iLay]&&pX[iLay]<=12 && -12<=pY[iLay]&&pY[iLay]<=12;
          if(!fire) break;
          
          // cout<<"Fire "<<tmpIX<<"\t"<<tmpIY<<"\t"<<iLay<<"\n";
          fire &= randGen.Uniform(0,1) < EffSet;
          if(fire){
            trackTMP.push_back(PosTable[tmpIX][tmpIY][iLay]);
            int PWidthtmp = -1;
            while(PWidthtmp<0||PWidthtmp>256)
              PWidthtmp = randGen.Landau(PWidthSet[0], PWidthSet[1]); 
            trackTMP[trackTMP.size()-1].PWidth = PWidthtmp; 
            trackTMP[trackTMP.size()-1].NID = 2;
            int NNoise = randGen.Exp(RNoise);
            // if(NNoise>0) cout<<160<<"\t"<<NNoise<<endl;
            for(int iNoise=0;iNoise<NNoise;iNoise++){
              // cout<<162<<" "<<iNoise<<" / "<<NNoise<<endl;

              int NiX = -1;
              int NiY = -1;
              int GCHTMP = -1;
              bool WithSame = true;
              while(WithSame){
                NiX = randGen.Uniform(0,(RiX[1]-RiX[0])/DRiX+1);
                NiY = randGen.Uniform(0,(RiY[1]-RiY[0])/DRiY+1);
                GCHTMP = PosTable[NiX][NiY][iLay].GCH;
                if(!PosTable[NiX][NiY][iLay].Alive) continue;
                bool bSta = false;
                for(int iT = 0; iT<int(trackTMP.size());iT++){
                  // cout<<"Checking: "<<iT<<endl;
                  if(trackTMP[iT].GCH==GCHTMP){
                    bSta = true;
                    break;
                  }
                }
                WithSame = bSta;
              }
              
              trackTMP.push_back(PosTable[NiX][NiY][iLay]);
              trackTMP[trackTMP.size()-1].NID = 1;
              trackTMP[trackTMP.size()-1].PWidth = randGen.Gaus(PWidthSet[0], PWidthSet[1]); 
              while(trackTMP[trackTMP.size()-1].PWidth<0||trackTMP[trackTMP.size()-1].PWidth>256) 
                trackTMP[trackTMP.size()-1].PWidth = randGen.Gaus(PWidthSet[0], PWidthSet[1]); 
              
            }
            
          }
          // if(iLay==1) hp0S->Fill(pX[iLay],pY[iLay]);
          // if(iLay==0) hd0S->Fill(dpX,dpY);
          // if(fire) cout<<"Inte "<<tmpIX<<"\t"<<tmpIY<<"\t"<<iLay<<"\n";
        }
        int Nhit = trackTMP.size();
        // cout<<196<<" "<<Nhit<<endl;
        int dtcnt = -1;
        
        while(dtcnt<0||dtcnt>2.56E+8) dtcnt = randGen.Landau(delayOfEvs[0], delayOfEvs[1]);
        int last_tcnt = initial_tcnt + dtcnt;
        // h2->Fill(dtcnt);

        // cout<<204<<endl;
        for (int ih = 0; iseq < 121&&ih<Nhit; ++ih,++iseq) {
          // cout<<211<<" IH now = "<<ih<<" / "<<Nhit<<endl;
          int bid = trackTMP[ih].IBD+1;
          int cid = trackTMP[ih].ICH; 
          // cout<<trackTMP[ih].GCH<<"\t"<<bid<<"\t"<<cid<<endl;
          if(cid==-1) {
            cout<<trackTMP[ih].GCH<<"\t"<<bid<<"\t"<<cid<<endl;
            throw;
          }
          // cout<<212<<" "<<Seq[bid-1][cid]<<endl;
          int seq = Seq[bid-1][cid]++;
          // cout<<214<<" "<<seq<<endl;
          if(seq==1023) Seq[bid-1][cid] = 0;
          // cout<<215<<endl;
          int tcnt = randGen.Gaus(delayOfHits[0],delayOfHits[1]);
          while(tcnt<0) tcnt = randGen.Gaus(delayOfHits[0],delayOfHits[1]);
          tcnt+=last_tcnt;
          // cout<<218<<endl;
          if(last_tcnt>2.56E+8){
            i++;
            tcnt -= 2.56E+8;
          }
          int pcnt = i;
          double dtime = tcnt / 2.56E+8 + pcnt;
          // cout<<224<<endl;
          int pwidth = trackTMP[ih].PWidth; 
          // cout<<225<<" "<<pwidth<<endl;
          // Output format
          string content = Form("%d\t%d\t%d\t%d\t%.12f\t%d\t%d\t%d", trackTMP[ih].NID ,bid, cid, seq, dtime, pcnt, tcnt, pwidth);
          // cout<<232<<" "<<content<<endl;
          ofs<<content<<endl;
          // cout<<"239  content\n";
          last_tcnt = tcnt;
        }
        // cout<<242<<endl;
        initial_tcnt = last_tcnt;
        // cout<<244<<endl;
      }
    }
  }
  // TCanvas *c1 = new TCanvas("c1","c1",640*4+4,480*4+28);

  // c1->Divide(2,2);
  // c1->cd(1);
  // hp0  ->Draw("hist");
  // c1->cd(2);
  // hp0S ->Draw("hist");
  // c1->cd(3);
  // hd0  ->Draw("hist");
  // c1->cd(4);
  // hd0S ->Draw("hist");
  // c1->Print((SavePath+"PosSet.gif").data());
}
