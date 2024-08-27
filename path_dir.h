#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include "./SettingFiles/S411FTestAna1.h"


namespace MuoAna_path_dir{
  string DirResultPW = DirResult+"PWidth/";
  string DirResultRate = DirResult+"ChRate/";
  string DirResultEff = DirResult+"Efficiency/";
  string DirDetector  = DirMacros+"DetectorSet/";
  
  void locatedDirbyPath(string path_dir){
    char cmdline[180];
    sprintf(cmdline,"mkdir -p %s",path_dir.data());
    
    if (system(cmdline)!=0){
      // cout<<"Don't find dir path:  "<<path_dir<<", and create this directory"<<endl;
      int NullRet = system(cmdline);
    }
  }
  
    
  void AppendHeadFile(const char *OriginalFile, const char *AppendFile, const char *TargetFile, const char opt = 'N') {
    ifstream input_fileO(OriginalFile);
    ifstream input_fileA(AppendFile);
    ofstream output_file(TargetFile);
    
    string line;
    string lineA;
    stringstream TmpOuput;
    while (getline(input_fileO, line)){
      TmpOuput << line << '\n';
      if(opt=='D') cout << line << '\n';
    } 
    string TmpOuputs = TmpOuput.str();
    if(opt=='D') cout<<TmpOuputs<<endl;
    Long64_t posOfLastRightBr = 0, posOfLastRightBrTmp = 0;
    while(1){
      posOfLastRightBrTmp = TmpOuputs.find("}",posOfLastRightBr+1);
      if(posOfLastRightBrTmp!=-1){
        posOfLastRightBr = posOfLastRightBrTmp;
        if(opt=='D')  cout<<posOfLastRightBr<<"\t"<<TmpOuputs[posOfLastRightBr]<<endl;
      } 
      else break;
    }
    TmpOuputs[posOfLastRightBr] = '\0';
    output_file<<TmpOuputs.substr(0,posOfLastRightBr)<<endl;
    input_fileO.close();
    
    while (getline(input_fileA, line)) output_file << line << '\n';
    
    input_fileA.close();
    
    output_file<<"}";
    output_file.close();
    if(opt=='D') {
      ifstream input_fileOPT(TargetFile);
      while (getline(input_fileOPT, line)) cout << line << '\n';
    }
  }
  
  
  void locateDataSpace(){
    AppendHeadFile("./AnaVariable.h",("./DetectorSet/DetSet"+DetectorGeoSet+".h").data(), "./Macro/AnaVariable.h");
    locatedDirbyPath(DirRawRoot);
    locatedDirbyPath(DirAnaPath);
    locatedDirbyPath(DirOperate);
    locatedDirbyPath(DirResult);
    locatedDirbyPath(DirResultPW);
    locatedDirbyPath(DirResultEff);
    locatedDirbyPath(DirResultRate);
    locatedDirbyPath(DirDetector);
    cout<<("mkdir -p "+DirMacros).data()<<endl;
    cout<<("cp -r ./Macro/* "+DirMacros).data()<<endl;
    cout<<("cp ./path_dir.h "+DirMacros).data()<<endl;
    cout<<("cp -r ./DetectorSet "+DirMacros).data()<<endl;
    cout<<("cp -r ./SettingFiles "+DirMacros).data()<<endl;
    int NullRet = system("cd ./");
    NullRet = system(("mkdir -p "+DirMacros).data());
    NullRet = system(("cp -r ./Macro/* "+DirMacros).data());
    NullRet = system(("cp ./path_dir.h "+DirMacros).data());
    NullRet = system(("cp -r ./DetectorSet "+DirMacros).data());
    NullRet = system(("cp -r ./SettingFiles "+DirMacros).data());
    // cout<<("cp -r ./Macro/* "+DirMacros).data()<<endl;
  // throw;  
  }
};
