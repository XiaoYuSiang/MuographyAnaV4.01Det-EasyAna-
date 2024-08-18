#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include <TChain.h>
#include <string>
#include "path_dir.h"
using namespace std;
using namespace MuoAna_path_dir;

Long64_t FileSize(const char *CheckFileName, const char OPT ='-'){
  ifstream fin(CheckFileName, ifstream::in | ifstream::binary);
  fin.seekg(0, ios::end);
  Long64_t length = fin.tellg();
  fin.close();
  if(OPT!='Q'&&OPT!='q') cout << length << " Bytes." << endl;
  return length;
}

vector<string> RawMuList(const string DirOperate){
  vector<string> MuFilePathList;
  string TmpFileRoute = DirOperate+"DataTxtNameAna.dat";
  string fileName;
  // cout<<MuFilePathList<<endl;
  ifstream in(TmpFileRoute.data());
  for(int i= 0; in>>fileName ; i++){
    int Slash_pos = int(fileName.rfind("/"));
    
    size_t start = Slash_pos+1; 
    size_t end = fileName.find("Mu.txt", start);
    if(int(end) = -1) fileName.find("MU.txt", start);
    string filetmp = fileName.substr(start, end - start);
    MuFilePathList.push_back(filetmp);
    cout<<MuFilePathList[i]<<endl;
  }
  return MuFilePathList;
}


void FilesCheck(){
  vector<string> ArrName = RawMuList(DirOperate);
  string outName="FileSheet.csv";
  ofstream outlist((DirOperate+outName).data());
  string outContent = "#File Name\tRun\tUP-UDP\tUP-Mu\tUP-Hk";
  outContent+="\tConvert\tUts\tUtf";
  outContent+="\tSize-UDP\tSize-Mu\tSize-HK\tSize-Root\n";
  outlist<<outContent; 
  outContent = "";
  for(int ifile=0;ifile<int(ArrName.size());ifile++){
    if( ArrName[ifile]=="END") break;
    string filename = ArrName[ifile];
    outlist<<filename<<",";
    int run_pos = int(filename.find("_Run"));
    if(run_pos==-1) run_pos = int(filename.find("_run"));
    if(run_pos==-1){
      cout<<"Please Enter the true Format of file Name in:"<<endl;
      cout<<"  Line 17 ArrName[1000]={} or adjust _Run/_run"<<endl;
      throw;
    }else{
      size_t start = run_pos + 4; 
      size_t end = filename.find('_', start);
      string A_value = filename.substr(start, end - start);
      outlist<<A_value<<",";
    }
    Long64_t 
      FS_UDP   = FileSize((DirUDPData+filename+"UDP.txt").data()),
      FS_RawMu = FileSize((DirRawData+filename+"Mu.txt").data()),
      FS_RawHk = FileSize((DirHKData+filename+"HK.txt").data()),
      FS_RotMu = FileSize((DirRawRoot+filename+"Mu.root").data());
    cout<<(DirUDPData+filename+"UDP.txt").data()<<endl;
    if(FS_UDP>1) outlist<<"Yes,"; else outlist<<"No,";
    if(FS_RawMu>1) outlist<<"Yes,"; else outlist<<"No,";
    if(FS_RawHk>1) outlist<<"Yes,"; else outlist<<"No,";
    if(FS_RotMu>1){
      string fileName = (DirRawRoot+ArrName[ifile]+"Mu.root");
      outlist<<"Yes,";
      TChain tDataTMP("t");
      cout<<"Add TChain: "<<fileName<<endl;
      Long64_t uttmp=0,utitmp=0,utftmp=0; 
      tDataTMP.SetBranchAddress("unixtime",&uttmp);
      tDataTMP.Add(fileName.data());
      tDataTMP.GetEntry(0);
      outlist<<uttmp<<",";
      tDataTMP.GetEntry(tDataTMP.GetEntries()-1);
      outlist<<uttmp<<",";
      
    }else outlist<<"No,-1,-1,";
    outlist<<FS_UDP<<","<<FS_RawMu<<","<<FS_RawHk<<","<<FS_RotMu<<endl;
  }
  
  cout<<"Finish the read of pcnt and unixtime of RawMu datas."<<endl;
  cout<<"File save at: "<<outName<<endl;
  outlist.close();
  throw;
}