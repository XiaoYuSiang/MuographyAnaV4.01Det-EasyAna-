#include "/data4/YuSiang/personalLib/DefaultInclude.h"
#include <TFile.h>
#include <TTree.h>
using namespace std;

char typeCheck(const string typeStr){
  if(typeStr=="string"||typeStr=="char*"||typeStr=="Char*"||typeStr=="String"||typeStr=="str"||typeStr=="Str") 
    return 'C';
  if(typeStr=="char"||typeStr=="Char"||typeStr=="Char_t"||typeStr=="B") 
    return 'B';
  if(typeStr=="uchar"||typeStr=="UChar"||typeStr=="UChar_t"||typeStr=="b") 
    return 'b';
  if(typeStr=="short"||typeStr=="Short"||typeStr=="Short_t"||typeStr=="S") 
    return 'S';
  if(typeStr=="ushort"||typeStr=="UShort"||typeStr=="UShort_t"||typeStr=="s") 
    return 's';
  if(typeStr=="int"||typeStr=="Int"||typeStr=="Int_t"||typeStr=="signed"||typeStr=="signed int"||typeStr=="I") 
    return 'I';
  if(typeStr=="uint"||typeStr=="UInt"||typeStr=="UInt_t"||typeStr=="unsigned"||typeStr=="unsigned int"||typeStr=="i") 
    return 'i';
  if(typeStr=="float"||typeStr=="Float"||typeStr=="Float_t"||typeStr=="F"||typeStr=="f") 
    return 'F';
  if(typeStr=="double"||typeStr=="Double"||typeStr=="Double_t"||typeStr=="D"||typeStr=="d") 
    return 'D';
  if(typeStr=="long"||typeStr=="Long"||typeStr=="Long64_t"||typeStr=="long int"||typeStr=="signed long"||typeStr=="signed long int"||typeStr=="L") 
    return 'L';
  if(typeStr=="ulong"||typeStr=="ULong_t"||typeStr=="ULong64_t"||typeStr=="ULong"||typeStr=="unsigned long"||typeStr=="unsigned long int"||typeStr=="l") 
    return 'l';
  if(typeStr=="bool"||typeStr=="Bool_t"||typeStr=="boolean"||typeStr=="O"||typeStr=="o") 
    return 'O';
  FATAL(Form("Error: ReadPTXT.C: c typeCheck(c.str. typeStr): typeStr is not a true value!\n Now, the value is: %s",typeStr.data()));
}
int GetFormIndex(const char typeC){
  if(typeC=='C') return 0;
  if(typeC=='B') return 1;   if(typeC=='b') return 2;
  if(typeC=='S') return 3;   if(typeC=='s') return 4;
  if(typeC=='I') return 5;   if(typeC=='i') return 6;
  if(typeC=='F') return 7;   if(typeC=='D') return 8;
  if(typeC=='L') return 9;   if(typeC=='l') return 10;
  if(typeC=='O') return 11;
  FATAL(Form("Error: ReadPTXT.C: c GetFormIndex(c.c. typeC): typeC is not a true value!\n Now, the value is: %s",typeC));
}
string formName[12]={
  "Char_t",
  "Char_t","UChar_t",
  "Short_t","UShort_t",
  "Int_t","UInt_t",
  "Float_t","Double_t",
  "Long64_t","ULong64_t",
  "Bool_t"
};


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
  vector <string> ParIName;
  for(int i=0;i<parNums;i++){
    ParIName.push_back(Form("Par%d",i));
  }
  for(int i=0;i<parNums;i++){
    outCpp<<"  "<<formName[GetFormIndex(VarForms[i])]<<" "<<ParIName[i].data();
    if(VarForms[i]=='C') outCpp<<"[100]={\"\"}"; 
    outCpp<<";"<<endl;
    outCpp<<Form("  t->Branch(\"%s\",&%s,\"%s/%c\");",VarNames[i].data(),ParIName[i].data(),VarNames[i].data(),VarForms[i])<<endl;
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
    outCpp<<">>"<<ParIName[i].data();
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