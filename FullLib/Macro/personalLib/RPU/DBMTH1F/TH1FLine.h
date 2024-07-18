void setLine(TH1F* tH1FObject, int fillcolor, int linecolor, int linestyle, int linewidth){
  //default value
  if (fillcolor==-1) fillcolor=0;
  if (linecolor==-1) linecolor=1;
  if (linestyle==-1) linestyle=0;
  if (linewidth==-1) linewidth=0.5;
  tH1FObject->SetFillColor(fillcolor);
  tH1FObject->SetLineColor(linecolor);
  tH1FObject->SetLineStyle(linestyle);
  tH1FObject->SetLineWidth(linewidth);
}
void setStandard(TGraph* standardObject){
  standardObject->SetLineColor(1);
  standardObject->SetLineWidth(0.5);  
  standardObject->SetLineStyle(2); 
}
void setLineData(TH1F* tH1FObject){
  tH1FObject->SetFillColor(0);
  tH1FObject->SetLineColor(1);
  tH1FObject->SetLineStyle(0);
  tH1FObject->SetLineWidth(0.5);
}
void setLineMonc(TH1F* tH1FObject){
  tH1FObject->SetFillColor(kGreen-7);
  tH1FObject->SetLineColor(kGreen-7);
  tH1FObject->SetLineStyle(0);
  tH1FObject->SetLineWidth(0.5);
}
void setLineBaground(TH1F* tH1FObject, int index){
  tH1FObject->SetFillColor(1+index);
  tH1FObject->SetLineColor(0);
  tH1FObject->SetLineStyle(0);
  tH1FObject->SetLineWidth(0);
}