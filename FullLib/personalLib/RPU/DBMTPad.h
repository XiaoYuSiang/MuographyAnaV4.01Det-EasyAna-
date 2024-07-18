#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGaxis.h>
#include <TPad.h>

void setPadDefault(TPad* padObject, float x1, float y1, float x2, float y2){
  if (x1==-1) x1=0.14;
  if (y1==-1) y1=0.95;
  if (x2==-1) x2=0.05;
  if (y2==-1) y2=0.4;
  padObject->SetLeftMargin(x1);
  padObject->SetBottomMargin(y1);
  padObject->SetRightMargin(1-x2);
  padObject->SetTopMargin(y2);
  padObject->Draw();
}
void setPadDefault(TPad* padObject, float x1, float y1, float x2, float y2, float color){
  //default value
  if (x1==-1) x1=0.14;
  if (y1==-1) y1=0.95;
  if (x2==-1) x2=0.05;
  if (y2==-1) y2=0.4;
  if (color==-1) color=0;
  padObject->SetLeftMargin(x1);
  padObject->SetBottomMargin(y1);
  padObject->SetRightMargin(1-x2);
  padObject->SetTopMargin(y2);
  padObject->SetFillColor(color);
  padObject->Draw();
}
void setPadDefault(TPad* padObject){
  //default value
  float x1=0.14;
  float y1=0.95;
  float x2=0.05;
  float y2=0.1;
  float color=0;
  padObject->SetLeftMargin(x1);
  padObject->SetBottomMargin(y1);
  padObject->SetRightMargin(1-x2);
  padObject->SetTopMargin(y2);
  padObject->SetFillColor(color);
  padObject->Draw();
}
void setPadDefaultTNormal(TPad* padObject){
/*   float defaultleft=0.14;
  float defaulttop=1;
  float defaultright=0.05;
  float defaultbottom=0.03; */
  padObject->SetLeftMargin(0.14);
  padObject->SetBottomMargin(0.03);
  padObject->SetRightMargin(1-0.05);
  padObject->SetTopMargin(1);
  padObject->SetFillColor(0);
  padObject->Draw();
}
void setPadDefaultTDivide(TPad* padObject){
/*   float defaultleft=0.14;
  float defaulttop=0.95;
  float defaultright=0.05;
  float defaultbottom=0.4; */
  padObject->SetLeftMargin(0.14);
  padObject->SetBottomMargin(0.4);
  padObject->SetRightMargin(1-0.05);
  padObject->SetTopMargin(1);
  padObject->SetFillColor(0);
  padObject->Draw();
}