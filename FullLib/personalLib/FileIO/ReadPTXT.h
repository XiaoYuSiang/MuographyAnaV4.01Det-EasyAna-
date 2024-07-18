#include "FileTypeInfo.h"
#include <TFile.h>
#include <TTree.h>
using namespace std;

void ConvertPTxtToRfile(
  const string FileName, const vector<string> VarNames, const vector<char> VarForms, 
  const string RootFile="tmprootfile.root", const string describe="A tree", const char quiet ='N'
){
  ifstream in(FileName.data());
  // vector<FormData> vforms;
  int parNums = int(VarForms.size());
  string tmpfileName = "outCpp";
  string tmpCfileName = tmpfileName+".C";
  string tmpDfileName = tmpfileName+"_C.d";
  string tmpSOfileName = tmpfileName+"_C.so";

  ofstream outCpp(tmpCfileName.data());
  outCpp<<"#include \"/data4/YuSiang/personalLib/DefaultInclude.h\""<<endl;
  outCpp<<"#include <TFile.h>"<<endl;
  outCpp<<"#include <TTree.h>"<<endl;
  outCpp<<"using namespace std;"<<endl;
  outCpp<<"void outCpp(){"<<endl;
  outCpp<<"  TFile *f = new TFile(\""<<RootFile<<"\",\"recreate\");"<<endl;
  outCpp<<"  TTree *t = new TTree(\"t\",\""<<describe.data()<<"\");"<<endl;
  outCpp<<"  ifstream in(\""<<FileName.data()<<"\");"<<endl;
  for(int i=0;i<parNums;i++){
    outCpp<<"  "<<formName[GetFormIndex(VarForms[i])]<<" "<<VarNames[i].data()<<";"<<endl;
    outCpp<<Form("  t->Branch(\"%s\",&%s,\"%s/%c\");",VarNames[i].data(),VarNames[i].data(),VarNames[i].data(),VarForms[i])<<endl;
  }
  
  outCpp<<"  while(in.good()){"<<endl;
  outCpp<<"    string Tmp_str;"<<endl;
  outCpp<<"    getline(in,Tmp_str);"<<endl;
  outCpp<<"    if(int(Tmp_str.find(\"#\"))!=-1){\n"<<endl;
  if(quiet=='N')
    outCpp<<"      cout<<\"PTXT skip: \"<<Tmp_str<<endl;"<<endl;
  outCpp<<"      continue;"<<endl;
  outCpp<<"    }"<<endl;
  
  outCpp<<"    istringstream iss(Tmp_str);"<<endl;
  outCpp<<"    iss";
  for(int i=0;i<parNums;i++)
    outCpp<<">>"<<VarNames[i].data();
  outCpp<<";"<<endl;
  outCpp<<"    t->Fill();"<<endl;
  outCpp<<"  }"<<endl;
  outCpp<<"  f->Write();"<<endl;
  outCpp<<"  f->Close();"<<endl;
  outCpp<<"}"<<endl;
  outCpp.close();
  system(Form("root -l -b -q %s+",tmpCfileName.data()));
  system(Form("rm %s",tmpCfileName.data()));
  system(Form("rm %s",tmpDfileName.data()));
  system(Form("rm %s",tmpSOfileName.data()));
  // throw;
}

void ConvertPTxtToRfile(
  const string FileName, const string VarNames, const string VarForms, 
  const string RootFile="tmprootfile.root", const string describe="A tree", const char quiet ='N'
){
  vector <int> pos_VarNames, pos_VarForms;
  pos_VarNames.push_back(-1); pos_VarForms.push_back(-1);
  for(int ipos = 0 ; ipos  <int(VarNames.size()) ; ipos++)
    if(VarNames[ipos]==':') pos_VarNames.push_back(ipos);
  for(int ipos = 0 ; ipos  <int(VarForms.size()) ; ipos++)
    if(VarForms[ipos]==':') pos_VarForms.push_back(ipos);
  pos_VarNames.push_back(int(VarNames.size())-1); pos_VarForms.push_back(int(VarForms.size())-1);

  vector<string> vVarNames;
  vector<char>   vVarForms;
  // cout<<"Num_PosVarName\tNum_PosVerForm\t"<<int(pos_VarNames.size())<<"\t"<<int(pos_VarForms.size())<<endl;
  // cout<<VarNames<<endl;
  // for(int ipos = 0 ; ipos  <int(pos_VarNames.size()) ; ipos++)
    // cout<<VarNames[pos_VarNames[ipos]+1]<<"\t"<<VarNames[pos_VarNames[ipos+1]]<<endl;
  
  for(int ipos = 0 ; ipos  <int(pos_VarNames.size())-1 ; ipos++){
    int sizeStr = pos_VarNames[ipos+1]-pos_VarNames[ipos]-1*(ipos!=(int(pos_VarNames.size())-2));
    vVarNames.push_back(string(VarNames.substr(pos_VarNames[ipos]+1, sizeStr)));
  }
  
  
  // FATAL("127");
  // for(int ipos = 0 ; ipos  <int(pos_VarForms.size()) ; ipos++)
    // cout<<VarForms[pos_VarForms[ipos]+1]<<"\t"<<VarForms[pos_VarForms[ipos+1]]<<endl;
  
  for(int ipos = 0 ; ipos  <int(pos_VarForms.size())-1 ; ipos++){
    int sizeStr = pos_VarForms[ipos+1]-pos_VarForms[ipos]-1*(ipos!=(int(pos_VarForms.size())-2));
    vVarForms.push_back(typeCheck(string(VarForms.substr(pos_VarForms[ipos]+1, sizeStr))));
    // cout<<typeCheck(string(VarForms.substr(pos_VarForms[ipos]+1, sizeStr)))<<endl;
  }

  // for(int ipos = 0 ; ipos  <int(pos_VarForms.size()) ; ipos++)
    // vVarForms.push_back(typeCheck(VarNames.substr(pos_VarForms[ipos]+1, pos_VarForms[ipos+1])));
  
  // for(int ipos = 0 ; ipos  <int(vVarNames.size()) ; ipos++)
    // cout<<vVarNames[ipos]<<endl;
  // cout<<"----------------------------------"<<endl;
  // for(int ipos = 0 ; ipos  <int(vVarForms.size()) ; ipos++)
    // cout<<vVarForms[ipos]<<endl;
  ConvertPTxtToRfile(FileName,vVarNames,vVarForms,RootFile,describe,quiet);
}

void ReadPTXT(){
  string s1 = "En:eta:time:index", s2 ="F:F:I:I";
  string TargetRootFile = "test.root";
  ConvertPTxtToRfile("/data4/YuSiang/personalLib/FileIO/test.ptxt",s1,s2,TargetRootFile,"test Tree",'q');
}