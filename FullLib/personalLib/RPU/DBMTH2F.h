
#include "DBMTH1F.h"
//#include "DBMTPad.h"
//#include "DBMTLegend.h"
#include "./DBMTH2F/TH2FAxis.h"
//#include <./DBMTH1F/TH2FLine.h>
//#include <./DBMTH1F/TH2FMark.h>
//#include <./DBMTH1F/TH2FOper.h>
#include "./DBMTH2F/TH2FTitle.h"



void FindYRangeTH2F(const TH2F* tH2FObj,float &ReturnZm,float &ReturnZM,const int precision=1,const float Trigger_MinZ=0.1,const float Trigger_MaxZ=2){
  float maxcon = INT_MIN*1., mincon = INT_MAX*1.;
  
  for(int i0=0;i0<tH2FObj->GetNbinsX();i0++){
    for(int i1=0;i1<tH2FObj->GetNbinsY();i1++){
      float contmp = tH2FObj->GetBinContent(i0+1,i1+1);
      if(contmp>=Trigger_MinZ && contmp<=Trigger_MaxZ){
        if(maxcon<contmp)  maxcon = contmp;
        if(mincon>contmp)  mincon = contmp;
      }
    }
  }
  ReturnZM = float(int(maxcon*pow(10,precision)*1.1)+pow(10,precision-1))
              /float(pow(10,precision));
  ReturnZm = float(int(mincon*pow(10,precision)*1))
              /float(pow(10,precision));
  
}

