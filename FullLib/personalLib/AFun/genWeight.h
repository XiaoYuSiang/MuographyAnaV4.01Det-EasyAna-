#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include "TLorentzVector.h"
#include "TTree.h"
#include "TProfile.h"
void Genweightcal(const char* inpaths,const char* sapaths) {
  cout<<"\tfind genweight"<<endl;
  vector<string> files = find_files(inpaths);
  //Printf("Files found: %i", (int) files.size());
  TreeReader data(inpaths);
  ofstream out(Form("%sGen.dat",sapaths));
  TLorentzVector mu[2], Zmm;
  cout <<"total event:\t"<<data.GetEntriesFast()<<endl;
  Double_t totalgen = 0;
  for (Long64_t ev = 0; ev <data.GetEntriesFast(); ++ev) {
    data.GetEntry(ev);    
    Float_t genWeight = data.GetFloat("genWeight");
    if (genWeight > 0){
      genWeight = 1.;
    }else{
      genWeight = -1.;
    }
    totalgen += genWeight;
    out<<genWeight<<endl;
  }
  out<<totalgen<<endl;
  cout<<Form("%sGen.dat is located",sapaths)<<endl;
  cout<<"total event is\t:" <<totalgen<<endl;
}
float Genweightcal(const char* inpaths,const char* sapaths,double XS,double Luminosity) {/*
  cout<<"\tfind genweight"<<endl;
  vector<string> files = find_files(inpaths);
  //Printf("Files found: %i", (int) files.size());
  TreeReader data(inpaths);
  ofstream out(Form("%sGen.dat",sapaths));
  TLorentzVector mu[2], Zmm;
  cout <<"total event:\t"<<data.GetEntriesFast()<<endl;
  double totalgen = 0;
  for (Long64_t ev = 0; ev <data.GetEntriesFast(); ++ev) {
    data.GetEntry(ev);    
    Float_t genWeight = data.GetFloat("genWeight");
    if (genWeight > 0){
      genWeight = 1.;
    }else{
      genWeight = -1.;
    }
    totalgen += genWeight;
    out<<genWeight<<endl;
  }
  out<<totalgen<<endl;
  cout<<Form("%sGen.dat is located",sapaths)<<endl;
  cout<<"genweight is\t:" <<(float) (XS*Luminosity/(totalgen*1.0))<<endl;
  */
  return 1.;//(float) (XS*Luminosity/(totalgen*1.0));
}