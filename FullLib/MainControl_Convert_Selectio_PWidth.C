// #include <ROOT/RDataFrame.hxx>
#include <TROOT.h>
#include <unistd.h>
#include <iostream>
#include "path_dir.h"
using namespace std;
using namespace MuoAna_path_dir;
string path_Mac = "./Macro/";
void MainControl_Convert_Selectio_PWidth(){
  gSystem->SetBuildDir((DirMacros+"tmpdir").data(), kTRUE);

  locateDataSpace();
  system(("rm "+DirOperate+"DataTxtNameAna.dat").data());
  system(("ls -1 "+DirRawData+name_Raw_txt+">>"+DirOperate+"DataTxtNameAna.dat").data());
  
  
  system(("root -l -b -q "+DirMacros+"CaConvertorV3.C+").data());
  
  
  system(("rm "+DirOperate+"DataRootNameAna.dat").data());
  system(("ls -1 "+DirRawRoot+name_Raw_root+">>"+DirOperate+"DataRootNameAna.dat").data());
  
  system(("root -l -b -q "+DirMacros+"DSLAnaV5.C+\\\(0,0\\)").data());
  
  
  /*Convert Raw_Mu.root to be Gap*.root by tcnt cut*/
  system(Form("root -l -b -q %sEventAnaV6.C+\\\(%d\\)",DirMacros.data(),28)); 

  system(Form("root -l -b -q %sPWidthAnaV401.C+\\\(%d\\)",DirMacros.data(),28)); 


  
  
  cout<<"End the Program for:  "<<name_Raw_txt<<endl;
  throw;
  


}
