#include "ReadJSON.h"
#include "WriteJSON.h"
#include "AppendHeadFile.h"


Long64_t FileSize(const char *CheckFileName, const char OPT ='-'){
  ifstream fin(CheckFileName, ifstream::in | ifstream::binary);
  fin.seekg(0, ios::end);
  Long64_t length = fin.tellg();
  fin.close();
  if(OPT!='Q'&&OPT!='q') cout << length << " Bytes." << endl;
  return length;
}