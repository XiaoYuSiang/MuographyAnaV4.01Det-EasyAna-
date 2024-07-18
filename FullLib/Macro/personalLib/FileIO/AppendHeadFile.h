#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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