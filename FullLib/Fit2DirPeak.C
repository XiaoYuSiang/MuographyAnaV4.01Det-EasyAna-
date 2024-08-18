void Fit2DirPeak(string outputFilename = "DtimeResult_ToSky.gif"){
  TFile *f1 = new TFile("/mnt/d/Desktop/SFTPTMp/ConvertTGapToTxt/Ana18R19/OperateResule/STGapT300_S20230328E20230504_nHTH1L64.root","open");
  TTree *t = (TTree*) f1->Get("t");

  TH1F *h0t1 = new TH1F("h0t1","#Delta tcnt(L1 - L0)",150,-100,50);
  TH1F *h0t2 = new TH1F("h0t2","#Delta tcnt(L2 - L0)",150,-100,50);
  TH1F *h0t3 = new TH1F("h0t3","#Delta tcnt(L3 - L0)",150,-100,50);
  
  t->Draw("tcnt[1]-tcnt[0]>>h0t1","TrackID==1111","goff");
  t->Draw("tcnt[2]-tcnt[0]>>h0t2","TrackID==1111","goff");
  t->Draw("tcnt[3]-tcnt[0]>>h0t3","TrackID==1111","goff");

  h0t1 = (TH1F*) h0t1->Rebin(1,"h0t1");
  h0t2 = (TH1F*) h0t2->Rebin(1,"h0t2");
  h0t3 = (TH1F*) h0t3->Rebin(1,"h0t3");
  
  h0t1 ->Scale(1./h0t1->Integral(-1,-1));
  h0t2 ->Scale(1./h0t2->Integral(-1,-1));
  h0t3 ->Scale(1./h0t3->Integral(-1,-1));
  h0t1 ->SetLineColor(1);
  h0t2 ->SetLineColor(2);
  h0t3 ->SetLineColor(4);
  
  TF1* fmode = new TF1("fmod","gaus(0)+gaus(3)",-150,50);
  double partmps[6] = {1000,-60,10,1000,-40,20};
  fmode->SetParameters(partmps);
  fmode->SetParLimits(0,0.01,0.2);
  fmode->SetParLimits(1,-80,0);
  fmode->SetParLimits(2,8,60);
  fmode->SetParLimits(3,0.01,0.2);
  fmode->SetParLimits(4,-80,0);
  fmode->SetParLimits(5,8,80);
  
  TF1 *f0t1 = (TF1*) fmode->Clone(); f0t1->SetName("f0t1");
  TF1 *f0t2 = (TF1*) fmode->Clone(); f0t2->SetName("f0t2");
  TF1 *f0t3 = (TF1*) fmode->Clone(); f0t3->SetName("f0t3");
  f0t1->SetLineColor(h0t1->GetLineColor());
  f0t2->SetLineColor(h0t2->GetLineColor());
  f0t3->SetLineColor(h0t3->GetLineColor());
  TCanvas *c1 = new TCanvas("c1","c1",640*2+4,640*2+28);
  c1->Divide(2,2);
  c1->cd(1);
  h0t1->Fit("f0t1","R");
  h0t1->Draw("h][");
  f0t1->Draw("lsame");
  TPaveText *p0t1 = new TPaveText(0.7, 0.6, 0.99, 0.99, "NDC");
  p0t1->AddText(Form("#mu_{0}: %.1f #pm %.0f", f0t1->GetParameter(1),f0t1->GetParError(1)));
  p0t1->AddText(Form("#sigma_{0}: %.1f #pm %.0f", f0t1->GetParameter(2),f0t1->GetParError(2)));
  p0t1->AddText(Form("#mu_{1}: %.1f #pm %.0f", f0t1->GetParameter(4),f0t1->GetParError(4)));
  p0t1->AddText(Form("#sigma_{1}: %.1f #pm %.0f", f0t1->GetParameter(5),f0t1->GetParError(5)));
  p0t1->SetFillColor(0);
  p0t1->Draw();
  
  c1->cd(2);
  h0t2->Fit("f0t2","R");
  h0t2->Draw("h][");
  f0t2->Draw("lsame");
  TPaveText *p0t2 = new TPaveText(0.7, 0.6, 0.99, 0.99, "NDC");
  p0t2->AddText(Form("#mu_{0}: %.1f #pm %.0f", f0t2->GetParameter(1),f0t2->GetParError(1)));
  p0t2->AddText(Form("#sigma_{0}: %.1f #pm %.0f", f0t2->GetParameter(2),f0t2->GetParError(2)));
  p0t2->AddText(Form("#mu_{1}: %.1f #pm %.0f", f0t2->GetParameter(4),f0t2->GetParError(4)));
  p0t2->AddText(Form("#sigma_{1}: %.1f #pm %.0f", f0t2->GetParameter(5),f0t2->GetParError(5)));
  p0t2->SetFillColor(0);
  p0t2->Draw();
  
  c1->cd(3);
  h0t3->Fit("f0t3","R");
  h0t3->Draw("h][");
  f0t3->Draw("lsame");
  TPaveText *p0t3 = new TPaveText(0.7, 0.6, 0.99, 0.99, "NDC");
  p0t3->AddText(Form("#mu_{0}: %.1f #pm %.0f", f0t3->GetParameter(1),f0t3->GetParError(1)));
  p0t3->AddText(Form("#sigma_{0}: %.1f #pm %.0f", f0t3->GetParameter(2),f0t3->GetParError(2)));
  p0t3->AddText(Form("#mu_{1}: %.1f #pm %.0f", f0t3->GetParameter(4),f0t3->GetParError(4)));
  p0t3->AddText(Form("#sigma_{1}: %.1f #pm %.0f", f0t3->GetParameter(5),f0t3->GetParError(5)));
  p0t3->SetFillColor(0);
  p0t3->Draw();
  
  c1->cd(4);
  float max[4];
  max [0] = h0t1->GetMaximum() + h0t1->GetBinError(h0t1->GetMaximumBin());
  max [1] = h0t2->GetMaximum() + h0t2->GetBinError(h0t2->GetMaximumBin());
  max [2] = h0t3->GetMaximum() + h0t3->GetBinError(h0t3->GetMaximumBin());
  if(max [0]>max [1]) max [3] = max [0]; else max [3] = max [1];
  if(max [2]>max [3]) max [3] = max [2];
  // cout<<max [0]<<"\t"<<max [1]<<"\t"<<max [2]<<"\t"<<max [3]<<endl;
  TH1F *hmod = (TH1F*) h0t1->Clone(); hmod->SetName("hMod"); hmod->SetTitle("");
  hmod->Draw("AXIS");
  hmod->GetXaxis()->SetRangeUser(h0t3->GetMean()-h0t3->GetRMS()*3,h0t1->GetMean()+h0t1->GetRMS()*3);
  hmod->GetYaxis()->SetRangeUser(0,max [3]*1.1);
  h0t1->SetLineColor(1);
  h0t1->Draw("pe][same");
  h0t2->SetLineColor(2);
  h0t2->Draw("pe][same");
  h0t3->SetLineColor(4);
  h0t3->Draw("pe][same");
  
  
  
  TLegend *l = new TLegend(0.75,0.6,0.99,0.99);
  l->AddEntry(h0t1,"#Delta t(L0-L1)","pel");
  l->AddEntry(f0t1,"2 Gaus. fit","l");
  l->AddEntry(h0t2,"#Delta t(L0-L2)","pel");
  l->AddEntry(f0t2,"2 Gaus. fit","l");
  l->AddEntry(h0t3,"#Delta t(L0-L3)","pel");
  l->AddEntry(f0t3,"2 Gaus. fit","l");
  l->Draw();
  c1->Print(outputFilename.data());


  
}