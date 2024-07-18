#include <TCanvas.h>
#include <TPDF.h>

void PDFCloseSave(TPDF* TPDFObject){
  TPDFObject->On();
  TPDFObject->Close();

}
void PDFCanPage(TPDF* TPDFObject,TCanvas* TCanvasObject,const char*  pageTitle,const int ithPage,const int totalPage){
  
  TCanvasObject->Update();
  TCanvasObject->cd();
  TPDFObject->On();
  if(ithPage!=1) TPDFObject->NewPage();
  TPDFObject->SetTitle(pageTitle);
  TCanvasObject->Paint();
  TPDFObject->Off();
  if(ithPage==totalPage){
    PDFCloseSave(TPDFObject);
  }
}

void PDFCanPage(TPDF* TPDFObject,TCanvas* TCanvasObject,const char*  pageTitle){
  
  TCanvasObject->Update();
  TCanvasObject->cd();
  TPDFObject->On();
  TPDFObject->NewPage();
  TPDFObject->SetTitle(pageTitle);
  TCanvasObject->Paint();
  TPDFObject->Off();
}

void PDFFinish(TPDF* TPDFObject){
  cout<<"Info : pdf file :  "<<TPDFObject->GetName()<<"  has been created"<<endl;
}
