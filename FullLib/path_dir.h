#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>

namespace MuoAna_path_dir{
  
  
  void locatedDirbyPath(string path_dir){
    char cmdline[180];
    sprintf(cmdline,"mkdir -p %s",path_dir.data());
    if (system(cmdline)!=0){
      // cout<<"Don't find dir path:  "<<path_dir<<", and create this directory"<<endl;
      system(cmdline);
    }
  }
  /*  Path of Macros!!!( *.C or *.h ) */
  string DirMacros     = "/data4/YuSiang/MGFakeData/Ana/MacroTmp/";
  /*  Path of Raw Datas (*_Mu.txt) */
  string DirRawData    = "/data4/YuSiang/MGFakeData/";
  string DirRawRoot    = "/data4/YuSiang/MGFakeData/Ana/rootfile/";
  /*  Root path of Save Datas  */
  string DirAnaPath    = "/data4/YuSiang/MGFakeData/Ana/";
  /*  Path of All type Dir in root path  */
  string DirOperate    = "/data4/YuSiang/MGFakeData/Ana/OperateResule/";
  string DirResult     = "/data4/YuSiang/MGFakeData/Ana/Result/";

  string name_Raw_txt  = "FakeData*_*Mu*.txt";
  string name_Raw_root = "FakeData*_*Mu*.root";
  
  void locateDataSpace(){
    
    locatedDirbyPath(DirRawRoot);
    locatedDirbyPath(DirAnaPath);
    locatedDirbyPath(DirOperate);
    locatedDirbyPath(DirResult);
    system(("cp -r ./Macro/* "+DirMacros).data());
    system(("cp ./path_dir.h "+DirMacros).data());
    system(("cp ./AnaVariable.h "+DirMacros).data());
    // cout<<("cp -r ./Macro/* "+DirMacros).data()<<endl;
  // throw;  
  }
};
