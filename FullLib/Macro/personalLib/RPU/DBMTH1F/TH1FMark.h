void setMark(TH1F* tH1FObject, int markcolor, int markstyle, float marksize){
  if (markstyle==-1) markstyle=4;
  if (marksize==-1) marksize=2.5/2;
  tH1FObject->SetMarkerColor(markcolor);
  tH1FObject->SetMarkerStyle(markstyle);
  tH1FObject->SetMarkerSize(marksize);
}
void setMarkData(TH1F* tH1FObject){
  tH1FObject->SetMarkerColor(1);
  tH1FObject->SetMarkerStyle(4);
  tH1FObject->SetMarkerSize(2.5/4);
}
void setMarkBaground(TH1F* tH1FObject, int index){
  tH1FObject->SetMarkerColor(index+1);
  tH1FObject->SetMarkerStyle(1);
  tH1FObject->SetMarkerSize(1);
}
void setMarkMonc(TH1F* tH1FObject){
  tH1FObject->SetMarkerColor(0);
  tH1FObject->SetMarkerStyle(0);
  tH1FObject->SetMarkerSize(0);
}
