#include "/data4/YuSiang/personalLib/DefaultInclude.h"

using namespace std;

string FindJSONAttr( const char* TagetFile, const char* TagetAttri, const char opt='E'){
  ifstream infile(TagetFile);
  // cout<<opt<<endl;
  string tmp; 
  while(infile.good()){
    string line; 
    getline(infile, line);
    int pos = line.find(TagetAttri),pos1=-1;
    if(pos==-1) continue;
    istringstream iss(line);
    iss >> tmp >> tmp >> tmp >> tmp;
    pos = tmp.find("\"");
    pos1= tmp.find("\"",pos+1);
    // cout<<tmp<<" "<<pos<<" "<<pos1<<endl;
    for(int i=pos+1, i2 = 0; i<pos1;i++, i2++){
      tmp[i2] = tmp[i];
    }
    tmp[pos1-1] = '\0';
    infile.close();
    return tmp.data();
  }
  infile.close();
  // cout<<"27 "<<opt<<"  "<<(opt=='W')<<endl;
  if(opt=='W'){
    cerr<<"Warning: personalLib/FileIO/ReadJSON.h: Not find the Attribute \""<<TagetAttri<<"\" L.31, return \"0\""<<endl;
    return "0";
  } 
  FATAL(Form("Error: personalLib/FileIO/ReadJSON.h: Not find the Attribute \"%s\" L.31",TagetAttri));
  return "Fake!!!!";
}

char *FindJSONAttrS(const char* TagetFile, const char* TagetAttri, const char opt='E'){
  string tmp = FindJSONAttr(TagetFile,TagetAttri,opt);
  char* tmpc = new char[tmp.length() + 1];
  strcpy(tmpc, tmp.c_str());
  return tmpc;
}
int FindJSONAttrI( const char* TagetFile, const char* TagetAttri, const char opt='E'){
  string tmp = FindJSONAttr(TagetFile,TagetAttri,opt);
  return atoi(tmp.data());
}
Long64_t FindJSONAttrL( const char* TagetFile, const char* TagetAttri, const char opt='E'){
  string tmp = FindJSONAttr(TagetFile,TagetAttri,opt);
  return atol(tmp.data());
}
float FindJSONAttrF( const char* TagetFile, const char* TagetAttri, const char opt='E'){
  string tmp = FindJSONAttr(TagetFile,TagetAttri,opt);
  return atof(tmp.data());
}
double FindJSONAttrD( const char* TagetFile, const char* TagetAttri, const char opt='E'){
  string tmp = FindJSONAttr(TagetFile,TagetAttri,opt);
  return strtod(tmp.data(), nullptr);
}
bool FindJSONAttrB( const char* TagetFile, const char* TagetAttri, const char opt='E'){
  string tmp = FindJSONAttr(TagetFile,TagetAttri,opt);
  if(strcmp("true",tmp.data())==0||strcmp("True",tmp.data())==0||strcmp("TRUE",tmp.data())==0||atoi(tmp.data())==1){
    // cout<<tmp.data()<<endl;
    return 1;
  } // cout<<tmp.data()<<endl;
  return 0;
  
}

void ShowJSONFile( const char* TagetFile){
  cout<<"Content of file "<<TagetFile<<" :"<<endl;
  ifstream file(TagetFile);
  string strtmp="";
  while(getline(file,strtmp)) cout<<strtmp<<endl;
  file.close();
}