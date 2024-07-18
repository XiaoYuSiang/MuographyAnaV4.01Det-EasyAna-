#ifndef DEFAULTINCLUDE_H
#define DEFAULTINCLUDE_H
#include "/data4/YuSiang/personalLib/DefaultInclude.h"
#endif

using namespace std;

string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const char* Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"  "<<"\""<<TagetAttri<<"\":\t\""<<Value<<"\",\n";
  file.close();
  return TagetFile;
}
string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const int* Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"  "<<"\""<<TagetAttri<<"\":\t\""<<Value<<"\",\n";
  file.close();
  return TagetFile;
}
string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const Long64_t* Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"  "<<"\""<<TagetAttri<<"\":\t\""<<Value<<"\",\n";
  file.close();
  return TagetFile;
}
string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const float* Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"  "<<"\""<<TagetAttri<<"\":\t\""<<Value<<"\",\n";
  file.close();
  return TagetFile;
}
string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const double* Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"  "<<"\""<<TagetAttri<<"\":\t\""<<Value<<"\",\n";
  file.close();
  return TagetFile;
}
string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const string Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"  "<<"\""<<TagetAttri<<"\":\t\""<<Value<<"\",\n";
  file.close();
  return TagetFile;
}
string SaveAttrJSON( const char* TagetFile, const char* TagetAttri, const bool Value){
  fstream file(TagetFile,fstream::out|fstream::app);
  if(Value==1) file<<"  "<<"\""<<TagetAttri<<"\":\t\"true\",\n";
  else file<<"  "<<"\""<<TagetAttri<<"\":\t\"false\",\n";
  file.close();
  return TagetFile;
}
void SaveBLinJSON( const char* TagetFile){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<endl;
  file.close();
}

char *ReCreateJSON( const char* TagetFile){
  fstream file(TagetFile,fstream::out);
  file<<"{\n";
  file.close();
  return Form("%s",TagetFile);
}
char *EndWriteJSON( const char* TagetFile){
  fstream file(TagetFile,fstream::out|fstream::app);
  file<<"}\n";
  file.close();
  return Form("Finish the edition of: %s !",TagetFile); 
}