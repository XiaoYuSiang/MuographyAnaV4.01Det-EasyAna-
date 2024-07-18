#include "/data4/YuSiang/personalLib/DefaultInclude.h"
using namespace std;
char typeCheck(const string typeStr){
  if(typeStr=="string"||typeStr=="char*"||typeStr=="Char*"||typeStr=="String") 
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
  "string",
  "Char_t","UChar_t",
  "Short_t","UShort_t",
  "Int_t","UInt_t",
  "Float_t","Double_t",
  "Long64_t","ULong64_t",
  "Bool_t"
};
