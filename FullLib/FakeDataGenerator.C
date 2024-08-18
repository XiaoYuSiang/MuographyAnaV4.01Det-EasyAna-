#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <TRandom3.h>
#include <TH1.h>

using namespace std;

void FakeDataGenerator() {
  ofstream ofs;
  int n = 10;  // Number of entries
  float delayOfEvs[2] = {400,2.0E+6};
  // 1.6E+6 ~ 900 MB / day
  // 2.0E+6 ~ 600 MB / day
  float delayOfHits[2] = {53,15};
  float nHitsSet[2] = {5,2};
  float PWidthSet[2] = {15,2};
  const int UT0 = 1700000000;
  const int NBD = 26;
  const int NCh = 26;
  
  srand(time(0));  // Initialize random seed
  srand(0);  // Initialize random seed
  TRandom3 randGen(0); // Initialize ROOT random generator with seed 0
  
  
  TH1F *h1 = new TH1F("h1","h1",256,0,256);
  TH1F *h2 = new TH1F("h2","h2",1000,0,1000);
  int Seq[NBD][NCh]={0};
  int frame_index = 0;
  int ifile = 0;
  ofs.open(Form("/data4/YuSiang/MGFakeData/FakeData_%d_Mu.txt",ifile));
  for (int i = 0; frame_index < n;) {
    if(i-(86400)*(1+ifile)>0){
      ifile++;
      ofs.close();
      cout << "New File:  " << Form("./FakeData_%d_Mu.txt",ifile) << endl;

      ofs.open(Form("./FakeData_%d_Mu.txt",ifile));
    }
    long long unixtime = UT0 + i;
    int initial_tcnt = 0;
    frame_index++;
    // cout << "#Frame " << frame_index << " Unixtime " << unixtime << endl;
    ofs << "#Frame " << frame_index << " Unixtime " << unixtime << endl;
    for (int iseq = 0; iseq < 121; ++iseq) {
      // Calculate values
      int Nhit = randGen.Gaus(nHitsSet[0],nHitsSet[1]);
      while(Nhit<0||Nhit>64) Nhit = randGen.Gaus(nHitsSet[0],nHitsSet[1]);
      int dtcnt = -1;
      while(dtcnt<0||dtcnt>2.56E+8) dtcnt = randGen.Landau(delayOfEvs[0], delayOfEvs[1]);
      int last_tcnt = initial_tcnt + dtcnt;
      h2->Fill(dtcnt);
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
        int pwidth = randGen.Landau(PWidthSet[0], PWidthSet[1]); 
        while(pwidth<0||pwidth>256) pwidth = randGen.Landau(PWidthSet[0], PWidthSet[1]); 
        h1->Fill(pwidth);
        // Output format
        string content = Form("2\t%d\t%d\t%d\t%.12f\t%d\t%d\t%d\n", bid, cid, seq, dtime, pcnt, tcnt, pwidth);
        ofs<<content;
        // cout<<content;
        last_tcnt = tcnt;
      }
      initial_tcnt = last_tcnt;
    }
  }
  TCanvas *c1 = new TCanvas("c1","c1",640*2,480);
  c1->Divide(2,1);
  c1->cd(1);
  h1->Draw("hist");
  c1->cd(2);
  h2->Draw("hist");
}
