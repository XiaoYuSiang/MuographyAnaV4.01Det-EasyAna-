#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <TFile.h>
#include <TTree.h>
#include <map>
#ifndef DEFNtupleV8_YS_H
  #define DEFNtupleV8_YS_H
    #include "./personalLib/RootFile/untuplizerv8_YuSiang01.h"
#endif
using namespace std;
namespace MuographGobelForm{//@@ADD read.h at IMF
  class scintillator{
  public:
    char  name[30];
    int   GeneralID, boardID, channelID;
    int   iX,  iY,  iZ;
    int   BiX, BiY, BiZ;
    float pX,  pY,  pZ;
    float sX,  sY,  sZ;
    bool  face;//true = face outside, false = face inside
    float Threshold;//unit: mVolt
    float Voltage;//unit: Volt
    float PwWei;//related to the resistance
    float Efficiency;//100% = 1.
    float EffSta;//Num of Eff data for marge different experiment
    
    scintillator(const char names[]="default", double GID=0,double BID=0,double CID=0){
      SetName(names);
      SetID(GID, BID, CID);
      SetIndex();
      SetBIndex();
      SetPosition();
      face = true;//true = face outside, false = face inside
      SetParameters();
      EffSta = 0;
    }
    virtual ~scintillator(){}
    
    void SetName(const char names[]="default"){
      sprintf(name,names);
    }
    char *GetName(){
      return name;
    }
    void SetID(int GID=0, int BID=0, int CID=0){
      GeneralID = GID;
      boardID   = BID;
      channelID = CID;
    }
    void SetIndex(int ix=0, int iy=0, int iz=0){
      iX = ix;
      iY = iy;
      iZ = iz;
    }
    void SetBIndex(int bix=0, int biy=0, int biz=0){
      BiX = bix;
      BiY = biy;
      BiZ = biz;
    }
    void SetPosition(int px=0, int py=0, int pz=0){
      pX = px;
      pY = py;
      pZ = pz;
    }
    void SetParameters(
      const float Tr = 60, const float Vt = 29, 
      const float PW = 1., const float Ef = 1.
    ){
      Threshold  = Tr;
      Voltage    = Vt;
      PwWei      = PW;
      Efficiency = Ef;
    }
    void Clear(){
      SetName();
      SetID();
      SetIndex();
      SetBIndex();
      SetPosition();
      face = true;//true = face outside, false = face inside
      SetParameters();
      EffSta = 0;
    }
    
    
    void SetSciTreeBranch(TTree *tPos){
      tPos->Branch("GeneralID"   ,&GeneralID    , "GeneralID/I" );
      tPos->Branch("name"        ,&name         , "name/C"      );
      tPos->Branch("boardID"     ,&boardID      , "boardID/I"   );
      tPos->Branch("channelID"   ,&channelID    , "channelID/I" );
      tPos->Branch("BiX"         ,&BiX          , "BiX/I"       );
      tPos->Branch("BiY"         ,&BiY          , "BiY/I"       );
      tPos->Branch("BiZ"         ,&BiZ          , "BiZ/I"       );
      tPos->Branch("iX"          ,&iX           , "iX/I"        );
      tPos->Branch("iY"          ,&iY           , "iY/I"        );
      tPos->Branch("iZ"          ,&iZ           , "iZ/I"        );
      tPos->Branch("pX"          ,&pX           , "pX/F"        );
      tPos->Branch("pY"          ,&pY           , "pY/F"        );
      tPos->Branch("pZ"          ,&pZ           , "pZ/F"        );
      tPos->Branch("face"        ,&face         , "face/O"      );
      tPos->Branch("Threshold"   ,&Threshold    , "Threshold/F" );
      tPos->Branch("Voltage"     ,&Voltage      , "Voltage/F"   );
      tPos->Branch("PwWei"       ,&PwWei        , "PwWei/F"     );
      tPos->Branch("Efficiency"  ,&Efficiency   , "Efficiency/F");
      tPos->Branch("EffSta"      ,&EffSta       , "EffSta/F"    );
    }
    void SetSciTreeBranchAddress(TTree *tPos,bool Beasy=true){ 
      tPos->SetBranchAddress("GeneralID"   ,&GeneralID   ); 
      if(Beasy) tPos->SetBranchAddress("name"        ,&name        );
      tPos->SetBranchAddress("boardID"     ,&boardID     );
      tPos->SetBranchAddress("channelID"   ,&channelID   );
      tPos->SetBranchAddress("BiX"         ,&BiX         );
      tPos->SetBranchAddress("BiY"         ,&BiY         );
      tPos->SetBranchAddress("BiZ"         ,&BiZ         ); 
      tPos->SetBranchAddress("iX"          ,&iX          );
      tPos->SetBranchAddress("iY"          ,&iY          );
      tPos->SetBranchAddress("iZ"          ,&iZ          );
      tPos->SetBranchAddress("pX"          ,&pX          );
      tPos->SetBranchAddress("pY"          ,&pY          ); 
      tPos->SetBranchAddress("pZ"          ,&pZ          );
      tPos->SetBranchAddress("face"        ,&face        );
      if(Beasy){
        tPos->SetBranchAddress("Threshold"   ,&Threshold   );
        tPos->SetBranchAddress("Voltage"     ,&Voltage     );
        tPos->SetBranchAddress("PwWei"       ,&PwWei       ); 
        tPos->SetBranchAddress("Efficiency"  ,&Efficiency  );
        tPos->SetBranchAddress("EffSta"      ,&EffSta      );
      }
    }
  private:
  protected:
    void Sci_CoutNotation(){
      cout<<"#Name\t\t\tGID\tBID\tCID\tiX\tiY\tiZ\tpX\tpY\tpZ\tface\tPwWei\n";
    }
    void Sci_CoutPrint(){
      cout<<name<<"\t"<<GeneralID<<"\t"<<boardID<<"\t"<<channelID<<"\t"<<iX<<"\t"<<iY<<"\t"<<iZ<<"\t"<<pX<<"\t"<<pY<<"\t"<<pZ<<"\t"<<face<<"\t"<<PwWei<<endl;
    }
    void Sci_TxtNotation(ofstream &out){
      out<<"#GID\tBID\tCID\tiX\tiY\tiZ\tpX\tpY\tpZ\tface\tPwWei"<<endl;
    }
    void Sci_CsvNotation(ofstream &out){
      out<<"#GID,BID,CID,iX,iY,iZ,pX,pY,pZ,face,PwWei"<<endl;
    }
    void Sci_TxtPrint(ofstream &out){
      out<<GeneralID<<"\t"<<boardID<<"\t"<<channelID<<"\t"<<iX<<"\t"<<iY<<"\t"<<iZ<<"\t"<<pX<<"\t"<<pY<<"\t"<<pZ<<"\t"<<face<<endl;
    }
    void Sci_CsvPrint(ofstream &out){
      out<<GeneralID<<","<<boardID<<","<<channelID<<","<<iX<<","<<iY<<","<<iZ<<","<<pX<<","<<pY<<","<<pZ<<","<<face<<","<<PwWei<<endl;
    }
  }; 
  
  
  class tempSensor{
  public:
    int   GeneralID, boardID, TChID;
    int   BiX, BiY, BiZ;
    float pX,  pY,  pZ;
    bool  face;//true = face outside, false = face inside
    
    tempSensor(){}
    tempSensor& operator=(const tempSensor &TS) {
      SetID(TS.GeneralID,TS.boardID,TS.TChID);
      SetBIndex(TS.BiX,TS.BiY,TS.BiZ);
      SetPosition(TS.pX,TS.pY,TS.pZ);
      face = TS.face;
      
    };
    
    virtual ~tempSensor(){}
    
    void SetID(int GID=0, int BID=0, int CID=0){
      GeneralID = GID;
      boardID   = BID;
      TChID     = CID;
    }
    void SetBIndex(int bix=0, int biy=0, int biz=0){
      BiX = bix;
      BiY = biy;
      BiZ = biz;
    }
    
    void SetID_Face_Ver(int TGID,int TBID,int TCID, bool Bface, const char *Ver= "V3.05"){
      SetID(TGID,TBID,TCID);
      face = Bface;
      ID_MTBVerSetpXYZ(TCID,Bface,Ver);
    }
    void SetPosition(float fpx = 0,float fpy = 0,float fpz = 0){
      pX = fpx;
      pY = fpy;
      pZ = fpz;
    }
    void MoveBPosition(float mpx = 0,float mpy = 0,float mpz = 0){
      //cout<<pX<<"\t"<<pY<<"\t"<<pZ<<"\t";
      pX += mpx;
      pY += mpy;
      pZ += mpz;
      //cout<<pX<<"\t"<<pY<<"\t"<<pZ<<"\n";
    }
    
    void SetTSTreeBranch(TTree *t){
      t->Branch("GeneralID" , &GeneralID);
      t->Branch("boardID"   , &boardID  );
      t->Branch("TChID"     , &TChID    );
      t->Branch("BiX"       , &BiX      );
      t->Branch("BiY"       , &BiY      );
      t->Branch("BiZ"       , &BiZ      );
      t->Branch("pX"        , &pX       );
      t->Branch("pY"        , &pY       );
      t->Branch("pZ"        , &pZ       );
      t->Branch("face"      , &face     );
    }
    void SetTSTreeBranchAddress(TTree *t){
      t->SetBranchAddress("GeneralID" , &GeneralID);
      t->SetBranchAddress("boardID"   , &boardID  );
      t->SetBranchAddress("TChID"     , &TChID    );
      t->SetBranchAddress("BiX"       , &BiX      );
      t->SetBranchAddress("BiY"       , &BiY      );
      t->SetBranchAddress("BiZ"       , &BiZ      );
      t->SetBranchAddress("pX"        , &pX       );
      t->SetBranchAddress("pY"        , &pY       );
      t->SetBranchAddress("pZ"        , &pZ       );
      t->SetBranchAddress("face"      , &face     );
    }
  private:
    void ID_MTBVerSetpXYZ(int TCID, bool Bface, const char *Ver= "V03_05"){

      if(strcmp(Ver,"V02_00")==0){
        if((Bface!=1)||TCID<0||TCID>5){
          cout<<"Error!!! Please Enter true TChID in tempSensor::SetVerMTB(int TChID, c.char *Ver)"<<endl;
          cout<<"Now, TChID: "<<TCID<<endl;
          throw;
        }
        pX = V200BTSpXYZ[0][TCID];
        pY = V200BTSpXYZ[1][TCID];
        pZ = V200BTSpXYZ[2][TCID];
      }else if(strcmp(Ver,"V02_03")==0){
        if((Bface!=0&&Bface!=1)||TCID<0||TCID>5){
          cout<<"Error!!! Please Enter true TChID in tempSensor::SetVerMTB(int TChID, c.char *Ver)"<<endl;
          cout<<"Now, TChID: "<<TCID<<endl;
          throw;
        }
        pX = V305BTSpXYZ[Bface][0][TCID];
        pY = V305BTSpXYZ[Bface][1][TCID];
        pZ = V305BTSpXYZ[Bface][2][TCID];
      }else if(strcmp(Ver,"V03_05")==0){
        if((Bface!=0&&Bface!=1)||TCID<0||TCID>5){
          cout<<"Error!!! Please Enter true TChID in tempSensor::SetVerMTB(int TChID, c.char *Ver)"<<endl;
          cout<<"Now, TChID: "<<TCID<<endl;
          throw;
        }
        pX = V305BTSpXYZ[Bface][0][TCID];
        pY = V305BTSpXYZ[Bface][1][TCID];
        pZ = V305BTSpXYZ[Bface][2][TCID];
      }else{
        cout<<"Error!!! Please Enter true Ver in tempSensor::SetVerMTB(int TChID, c.char *Ver)"<<endl;
        throw;
      }
    }
  protected:
    
    
  };
  
  
  
  class Detector{
  public:
    char  name[30];
    char  Version[10];
    int   DetectorID;
    int   NumLY, NumBD, NumCh;
    int   NumnX, NumnY, NumnZ;
    int   NumBX, NumBY, NumBZ;
    int   NSci;
    float DetPx, DetPy, DetPz;
    float DetTh, DetPh;
    scintillator *Scintillators[];
    //double 
    //ex: Shimen 24.839314, 121.271310

    Detector(const char names[]="default", const char Ver[]="V2.0", const double DID=0){
      SetName(names);
      SetVersion(Ver);
      Initialize(DID);
    }
    virtual ~Detector(){}
    
    void SetName(const char *names){
      sprintf(name,names);
    }
    char *GetName(){
      return this->name;
    }
    void SetVersion(const char Ver[]="V2.0"){
      sprintf(Version,Ver);
    }
    void SetID(const int DID=0){
      DetectorID = DID;
    }
    

    void Initialize(const double DID=0){
      SetID(DID);

      NSci = 0;
    }
    
    void Fill(const scintillator *TmpSci){
      Scintillators[NSci] = (scintillator*) TmpSci;
      NSci++;
    }

  private:
  protected:
 
  };
  
  
  class Experiment{
  public:
    char  name[30];
    char  site[10];
    int   ExperimentID, NDet;
    float Latitude, Longitude; 
    Long64_t  StartUTime, EndUTime;
    Detector *Detectors[];
    Experiment(const char names[]="IndoorTest", const float Lati = 24.971510, const float Long = 121.192117, const char AddSiteName[]="S4_509"){
      SetName(names);
      Initialize();
      SetSite(AddSiteName);
      SetPosition(Lati,Long);
    }
    Experiment(const char names[]="IndoorTest", const char SiteName[]="S4_509"){
      Initialize();
      SetName(names);
      SetSite(SiteName);
      // FindPos(site);
    }
    virtual ~Experiment(){}
    
    void SetName(const char *names){
      sprintf(name,names);
    }
    char *GetName(){
      return name;
    }
    void SetPosition( const float Lati = 24.971510, const float Long = 121.192117 ){
      Latitude  = Lati;
      Longitude = Long;
    }
    void SetID(int EID=0){
      ExperimentID = EID;
    }
    int GetID(){
      return ExperimentID;
    }
    
    void SetSite(const char SiteName[]="S4_509"){
      sprintf(site,SiteName);
    }
    string GetSite(){
      return site;
    }
    // void FindPos(const char SiteName[]="S4_509"){
      // for(int iCaseName=0;iCaseName<4;iCaseName++){
        // if(strcmp(SiteName,Sites[iCaseName])==0){
          // Latitude  = Latitudes [iCaseName];
          // Longitude = Longitudes[iCaseName];
          // break;
        // }
      // }
    // }
    //Move to LoadODET.h
    void SetUTRange(const Long64_t UTS=0, const Long64_t UTE=0){
      
      StartUTime   = UTS;
      EndUTime     = UTE;
    }
    void Initialize(){
      ExperimentID = 0;
      SetUTRange();
      NDet = 0;
    }
    void Fill(const Detector *TmpDet){
      Detectors[NDet] = (Detector*) TmpDet;
      NDet++;
    }
      
  private:
  protected:
    /*
    void Sci_CoutNotation(){
      cout<<"#Name\t\t\tGID\tBID\tCID\tiX\tiY\tiZ\tpX\tpY\tpZ\tface\tPwWei\n";
    }
    void Sci_CoutPrint(){
      cout<<name<<"\t"<<GeneralID<<"\t"<<boardID<<"\t"<<channelID<<"\t"<<iX<<"\t"<<iY<<"\t"<<iZ<<"\t"<<pX<<"\t"<<pY<<"\t"<<pZ<<"\t"<<face<<"\t"<<PwWei<<endl;
    }
    void Sci_TxtNotation(ofstream &out){
      out<<"#GID\tBID\tCID\tiX\tiY\tiZ\tpX\tpY\tpZ\tface\tPwWei"<<endl;
    }
    void Sci_CsvNotation(ofstream &out){
      out<<"#GID,BID,CID,iX,iY,iZ,pX,pY,pZ,face,PwWei"<<endl;
    }
    void Sci_TxtPrint(ofstream &out){
      out<<GeneralID<<"\t"<<boardID<<"\t"<<channelID<<"\t"<<iX<<"\t"<<iY<<"\t"<<iZ<<"\t"<<pX<<"\t"<<pY<<"\t"<<pZ<<"\t"<<face<<endl;
    }
    void Sci_CsvPrint(ofstream &out){
      out<<GeneralID<<","<<boardID<<","<<channelID<<","<<iX<<","<<iY<<","<<iZ<<","<<pX<<","<<pY<<","<<pZ<<","<<face<<","<<PwWei<<endl;
    }
    */
  };


  class RunData{
  public:
    char     RunName[7];
    int      RunID;
    int      StartDay, StaY, StaM, StaD;
    int      EndDay  , EndY, EndM, EndD;
    float    DPhi;
    float    DTheta;
    Long64_t StartUT;
    Long64_t EndUT;
    
    RunData(){
      SetIni();
    }

    ~RunData(){};
    
    void SetIni(){
      RunName[0] = '-';
      StartDay = -1;
      EndDay   = -1;
      StartUT = -1;
      EndUT   = -1;
      DPhi    =  0;
      DTheta  =  0; 
    }
    
    void sortRunInf(){
      sscanf(RunName,"%*3s%d",&RunID);
      sscanf(Form("%d",StartDay),"%4d%2d%2d",&StaY,&StaM,&StaD);
      sscanf(Form("%d",EndDay  ),"%4d%2d%2d",&EndY,&EndM,&EndD);
      StartUT = YMDHmSZtoUT(StaY,StaM,StaD);
      EndUT   = YMDHmSZtoUT(EndY,EndM,EndD);
    }
    
    
  private:

    
  };
  
  class HouseKeepingData{
  public:
    Long64_t  unixtime , dunixtime;
    Long64_t  dtimeInt0, dtimeInt1;
    int boardID;
    int TempCen, TempFPG;
    int Temps1, Temps2, Temps3, Temps4;
    int Humidity, Pressure, Altitude;
    int degX, degY, degZ;
    int accX, accY, accZ;
    int magX, magY, magZ;;
    
    HouseKeepingData(){
      unixtime = -1; dunixtime = -1;
      dtimeInt0 = -1; dtimeInt1 = -1;
      boardID = -1;
      TempCen = -1; TempFPG = -1;
      Temps1 = -1; Temps2 = -1; Temps3 = -1; Temps4 = -1;
      Humidity = -1; Pressure = -1; Altitude = -1;
      degX = -1; degY = -1; degZ = -1;
      accX = -1; accY = -1; accZ = -1;
      magX = -1; magY = -1; magZ = -1;
    };
    
    virtual ~HouseKeepingData(){};

    void SetHKTreeBranch(TTree *t){
      t->Branch("unixtime" , &unixtime );
      t->Branch("dunixtime", &dunixtime);
      t->Branch("dtimeInt0", &dtimeInt0);
      t->Branch("dtimeInt1", &dtimeInt1);
      t->Branch("boardID"  , &boardID  );
      t->Branch("TempCen"  , &TempCen  );
      t->Branch("TempFPG"  , &TempFPG  );
      t->Branch("Temps1"   , &Temps1   );
      t->Branch("Temps2"   , &Temps2   );
      t->Branch("Temps3"   , &Temps3   );
      t->Branch("Temps4"   , &Temps4   );
      t->Branch("Humidity" , &Humidity );
      t->Branch("Pressure" , &Pressure );
      t->Branch("Altitude" , &Altitude );
      t->Branch("degX"     , &degX     );
      t->Branch("degY"     , &degY     );
      t->Branch("degZ"     , &degZ     );
      t->Branch("accX"     , &accX     );
      t->Branch("accY"     , &accY     );
      t->Branch("accZ"     , &accZ     );
      t->Branch("magX"     , &magX     );
      t->Branch("magY"     , &magY     );
      t->Branch("magZ"     , &magZ     );
    }
    void SetHKTreeBranchAddress(TTree *t){
      t->SetBranchAddress("unixtime" , &unixtime );
      t->SetBranchAddress("dunixtime", &dunixtime);
      t->SetBranchAddress("dtimeInt0", &dtimeInt0);
      t->SetBranchAddress("dtimeInt1", &dtimeInt1);
      t->SetBranchAddress("boardID"  , &boardID  );
      t->SetBranchAddress("TempCen"  , &TempCen  );
      t->SetBranchAddress("TempFPG"  , &TempFPG  );
      t->SetBranchAddress("Temps1"   , &Temps1   );
      t->SetBranchAddress("Temps2"   , &Temps2   );
      t->SetBranchAddress("Temps3"   , &Temps3   );
      t->SetBranchAddress("Temps4"   , &Temps4   );
      t->SetBranchAddress("Humidity" , &Humidity );
      t->SetBranchAddress("Pressure" , &Pressure );
      t->SetBranchAddress("Altitude" , &Altitude );
      t->SetBranchAddress("degX"     , &degX     );
      t->SetBranchAddress("degY"     , &degY     );
      t->SetBranchAddress("degZ"     , &degZ     );
      t->SetBranchAddress("accX"     , &accX     );
      t->SetBranchAddress("accY"     , &accY     );
      t->SetBranchAddress("accZ"     , &accZ     );
      t->SetBranchAddress("magX"     , &magX     );
      t->SetBranchAddress("magY"     , &magY     );
      t->SetBranchAddress("magZ"     , &magZ     );
    }
    
    void HK_Tem_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<TempCen<<"\t"<<TempFPG<<"\t"<<Temps1<<"\t"<<Temps2<<"\t"<<Temps3<<"\t"<<Temps4<<endl;
    }
    void HK_Deg_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<degX<<"\t"<<degY<<"\t"<<degZ<<endl;
    }
    void HK_Acc_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<accX<<"\t"<<accY<<"\t"<<accZ<<endl;
    }
    void HK_Mag_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<magX<<"\t"<<magY<<"\t"<<magZ<<endl;
    }
    void HK_Hum_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<Humidity<<endl;
    }
    void HK_Pre_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<Pressure<<endl;
    }
    void HK_Alt_TxtOuput(ofstream &out){
      out<<boardID<<"\t"<<unixtime<<"\t"<<dunixtime<<"\t"<<Altitude<<endl;
    }
    
  };
  
  class EffciencyData{
  public:
    int GeneralID, boardID, ChannelID;
    int statistic;
    float effiency, uncertiantyless, uncertiantyhigh;
    bool alive;
    EffciencyData(){
      alive     = false;
      boardID   = -1;
      GeneralID = -1;
      ChannelID = -1;
      statistic = -1;
      effiency  = -1;
      uncertiantyless = -1;
      uncertiantyhigh = -1;
    }
    EffciencyData(ifstream &in){
      if(in>>boardID>>ChannelID>>GeneralID>>effiency&&
        in>>statistic>>uncertiantyless>>uncertiantyhigh)
        alive = true;
    }
    void Show(){
      cout<<boardID<<"\t"<<ChannelID<<"\t"<<GeneralID<<"\t";
      cout<<effiency<<"\t"<<statistic<<"\t"<<uncertiantyless<<"\t"<<uncertiantyhigh<<endl;
    }
    void Clear(){
      alive     = false;
      boardID   = -1;
      GeneralID = -1;
      ChannelID = -1;
      statistic = -1;
      effiency  = -1;
      uncertiantyless = -1;
      uncertiantyhigh = -1;
    }
  };
  
  class GeometricAreaData{
  public:
    string poscode;
    float Vux, Vuy, Vuz;
    float Vwx, Vwy, Vwz;
    float DXZ, DYZ;
    float AreaFactor;
    int   NumbFactor;
    int   SymFactor;
    bool  Empty;
    
    GeometricAreaData(){
      SetPosCode();
      SetUnixVector();
      SetWeiVector();
      SetDirectDXYZ();
      SetAreaFactor();
      SetNumberFactor();
      SetSymmitryFactor();
      Empty = true;
    };
    
    virtual ~GeometricAreaData(){};

    

    void SetPosCode(const char *pscod="0,0_0,0_0,0"){
      poscode = pscod;//sprintf(poscode,"%s",);
    }
    void SetUnixVector(const float vx = 0, const float  vy = 0, const float  vz = 1){
      Vux= vx; Vuy= vy; Vuz= vz;
    }
    void SetWeiVector(const float vx = 0, const float  vy = 0, const float  vz = 1){
      Vwx= vx; Vwy= vy; Vwz= vz;
    }
    void SetDirectDXYZ(const float dxz = 0, const float  dyz = 0){ 
      DXZ = dxz; DYZ = dyz;
    }
    void SetAreaFactor(const float AF = 0.025623723){
      AreaFactor = AF;
    }
    void SetNumberFactor(const float NF = 64){
      NumbFactor = NF;
    }
    void SetSymmitryFactor(const float SF = 1){
      SymFactor = SF;
    }
    
    
    void ShowTitle(){
      cout<<"poscode"<<
      Form("\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
        "Vux", "Vuy", "Vuz", "Vwx", "Vwy", "Vwz", "DXZ", "DYZ",
        "AreaFactor", "NumbFactor", "SymFactor");
    }
    void Show(){
      cout<<poscode<<
      Form("\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\n", 
        Vux, Vuy, Vuz, Vwx, Vwy, Vwz, DXZ, DYZ,
        AreaFactor, NumbFactor, SymFactor);
    }
    
    
  };
  
  class VertTrackData{
  public:
    int       TrackIndex, frame, EvIndex;
    Long64_t  unixtime;
    int       tYear, tMonth, tDate, tHour, tMinute, tSecond;
    int       nLayers, iHit, eventHit;
    int       BLay;
    vector<Int_t>    board, channel, iX, iY, iZ;
    vector<Int_t>    BiX, BiY, BiZ;
    vector<Int_t>    pwidth,pwidthScaleFactor;
    vector<Int_t>    pcnt;
    vector<Long64_t> tcnt;
    vector<Double_t> dtime;
    Int_t    *board_,*channel_,*iX_,*iY_,*iZ_;
    Int_t    *BiX_,*BiY_,*BiZ_;
    Int_t    *pwidth_,*pwidthScaleFactor_;
    Int_t    *pcnt_;
    Long64_t *tcnt_;
    Double_t *dtime_;
    VertTrackData(const int OriTrackIndex = 0){
      TrackIndex = OriTrackIndex;
    };
    virtual ~VertTrackData(){};

    void SetTreeBranch(TTree *tree){
      tree->Branch("TrackIndex" ,&TrackIndex  );
      tree->Branch("frame"      ,&frame       );
      tree->Branch("EvIndex"    ,&EvIndex     );
      tree->Branch("unixtime"   ,&unixtime    );
      tree->Branch("tYear"      ,&tYear       );
      tree->Branch("tMonth"     ,&tMonth      );
      tree->Branch("tDate"      ,&tDate       );
      tree->Branch("tHour"      ,&tHour       );
      tree->Branch("tMinute"    ,&tMinute     );
      tree->Branch("tSecond"    ,&tSecond     );
      tree->Branch("nLayers"    ,&nLayers     );
      tree->Branch("BLay"       ,&BLay        );
      tree->Branch("iHit"       ,&iHit        );
      tree->Branch("eventHit"   ,&eventHit    );
      tree->Branch("board"      ,&board       );
      tree->Branch("channel"    ,&channel     );
      tree->Branch("iX"         ,&iX          );
      tree->Branch("iY"         ,&iY          );
      tree->Branch("iZ"         ,&iZ          );
      tree->Branch("BiX"        ,&BiX         );
      tree->Branch("BiY"        ,&BiY         );
      tree->Branch("BiZ"        ,&BiZ         );
      tree->Branch("pwidth"     ,&pwidth      );
      tree->Branch("pwidthScaleFactor",&pwidthScaleFactor);
      tree->Branch("pcnt"       ,&pcnt        );
      tree->Branch("tcnt"       ,&tcnt        );
      tree->Branch("dtime"      ,&dtime       );
    }
    void GetTreeReaderTGap(TreeReader &TreeReaderdata, const Long64_t ev){
      TreeReaderdata.GetEntry(ev);
      frame    = TreeReaderdata.GetInt("frame");
      EvIndex  = TreeReaderdata.GetInt("EvIndex");
      unixtime = TreeReaderdata.GetLong64("unixtime");
      tYear    = TreeReaderdata.GetInt("tYear");
      tMonth   = TreeReaderdata.GetInt("tMonth");
      tDate    = TreeReaderdata.GetInt("tDate");
      tHour    = TreeReaderdata.GetInt("tHour");
      tMinute  = TreeReaderdata.GetInt("tMinute");
      tSecond  = TreeReaderdata.GetInt("tSecond");
      nLayers  = TreeReaderdata.GetInt("nLayers");
      eventHit = TreeReaderdata.GetInt("nH");
      board_   = TreeReaderdata.GetPtrInt("board");
      channel_ = TreeReaderdata.GetPtrInt("channel");
      pwidth_  = TreeReaderdata.GetPtrInt("pwidth");
      pwidthScaleFactor_   =
                 TreeReaderdata.GetPtrInt("pwidthScaleFactor");
      pcnt_    = TreeReaderdata.GetPtrInt("pcnt");
      tcnt_    = TreeReaderdata.GetPtrLong64("tcnt");
      dtime_   = TreeReaderdata.GetPtrDouble("dtime");
      // cout<<board_[0]<<"\t"<<channel_[0]<<endl;
    }
    void GetTreeReaderVTrack(TreeReader &TreeReaderdata, const Long64_t ev){
      TreeReaderdata.GetEntry(ev);
      TrackIndex = TreeReaderdata.GetInt("TrackIndex");
      frame    = TreeReaderdata.GetInt("frame");
      EvIndex  = TreeReaderdata.GetInt("EvIndex");
      unixtime = TreeReaderdata.GetLong64("unixtime");
      tYear    = TreeReaderdata.GetInt("tYear");
      tMonth   = TreeReaderdata.GetInt("tMonth");
      tDate    = TreeReaderdata.GetInt("tDate");
      tHour    = TreeReaderdata.GetInt("tHour");
      tMinute  = TreeReaderdata.GetInt("tMinute");
      tSecond  = TreeReaderdata.GetInt("tSecond");
      nLayers  = TreeReaderdata.GetInt("nLayers");
      BLay     = TreeReaderdata.GetInt("BLay");
      iHit     = TreeReaderdata.GetInt("iHit");
      eventHit = TreeReaderdata.GetInt("eventHit");
      board_   = TreeReaderdata.GetPtrInt("board");
      channel_ = TreeReaderdata.GetPtrInt("channel");
      iX_      = TreeReaderdata.GetPtrInt("iX");
      iY_      = TreeReaderdata.GetPtrInt("iY");
      iZ_      = TreeReaderdata.GetPtrInt("iZ");
      BiX_     = TreeReaderdata.GetPtrInt("BiX");
      BiY_     = TreeReaderdata.GetPtrInt("BiY");
      BiZ_     = TreeReaderdata.GetPtrInt("BiZ");
      pwidth_  = TreeReaderdata.GetPtrInt("pwidth");
      pwidthScaleFactor_   =
                 TreeReaderdata.GetPtrInt("pwidthScaleFactor");
      pcnt_    = TreeReaderdata.GetPtrInt("pcnt");
      tcnt_    = TreeReaderdata.GetPtrLong64("tcnt");
      dtime_   = TreeReaderdata.GetPtrDouble("dtime");
    }
    void TReaderPtrToVec(){
      for(int iiHit=0;iiHit<iHit;iiHit++){
        board.push_back(board_[iiHit]);
        channel.push_back(channel_[iiHit]);
        iX.push_back(iX_[iiHit]);
        iY.push_back(iY_[iiHit]);
        iZ.push_back(iZ_[iiHit]);
        BiX.push_back(BiX_[iiHit]);
        BiY.push_back(BiY_[iiHit]);
        BiZ.push_back(BiZ_[iiHit]);
        pwidth.push_back(pwidth_[iiHit]);
        pwidthScaleFactor.push_back(pwidthScaleFactor_[iiHit]);
        pcnt.push_back(pcnt_[iiHit]);
        tcnt.push_back(tcnt_[iiHit]);
        dtime.push_back(dtime_[iiHit]);
      }
    }
    void Clear(){
      BLay   =0;
      board.clear();
      channel.clear();
      pwidth.clear();
      pwidthScaleFactor.clear();
      pcnt.clear();
      iX.clear();
      iY.clear();
      iZ.clear();
      BiX.clear();
      BiY.clear();
      BiZ.clear();
      tcnt.clear();
      dtime.clear();
      iHit = 0;
    }
  };
  
  
  class MuEleIDData{
  public:
    int       TrackIndex;
    Long64_t  unixtime;
    int       tYear, tMonth, tDate, tHour, tMinute, tSecond;
    int       nLayers, iHit, nH;
    bool      ElectronID, MuonID, NoiseID;
    short     IDtight;
    vector<Int_t>    board, channel, iX, iY, iZ;
    vector<Int_t>    pwidth,pwidthScaleFactor;
    vector<Int_t>    pcnt;
    vector<Long64_t> tcnt;
    vector<Double_t> dtime;
    vector<Long64_t> dtimeInt;
    Int_t    *board_,*channel_, *iX_, *iY_, *iZ_;
    Int_t    *pwidth_,*pwidthScaleFactor_;
    Int_t    *pcnt_;
    Long64_t *tcnt_;
    Double_t *dtime_;
    Long64_t *dtimeInt_;
    MuEleIDData(const int OriTrackIndex = 0){
      TrackIndex = OriTrackIndex;
      ElectronID=false;
      MuonID=false;
      NoiseID=false;
    };
    virtual ~MuEleIDData(){};

    void SetTreeBranch(TTree *tree){
      tree->Branch("TrackIndex",&TrackIndex);
      tree->Branch("unixtime",&unixtime);

      tree->Branch("nH" ,&nH);
      tree->Branch("nLayers",&nLayers);
      tree->Branch("iHit",&iHit);
      tree->Branch("tYear",&tYear);
      tree->Branch("tMonth",&tMonth);
      tree->Branch("tDate",&tDate);
      tree->Branch("tHour",&tHour);
      tree->Branch("tMinute",&tMinute);
      tree->Branch("tSecond",&tSecond);

      tree->Branch("ElectronID",&ElectronID);
      tree->Branch("MuonID"   ,&MuonID);
      tree->Branch("NoiseID"  ,&NoiseID);
      tree->Branch("IDtight"  ,&IDtight);
      tree->Branch("board",&board);
      tree->Branch("channel",&channel);
      tree->Branch("iX",&iX);
      tree->Branch("iY",&iY);
      tree->Branch("iZ",&iZ);
      tree->Branch("pwidth",&pwidth);
      tree->Branch("pwidthScaleFactor",&pwidthScaleFactor); 
      tree->Branch("pcnt",&pcnt);
      tree->Branch("tcnt",&tcnt);
      tree->Branch("dtime",&dtime);
      tree->Branch("dtimeInt",&dtimeInt);
    }
    void GetTreeReaderTGap(TreeReader &TreeReaderdata, const Long64_t ev){
      TreeReaderdata.GetEntry(ev);
      unixtime = TreeReaderdata.GetLong64("unixtime");
      tYear    = TreeReaderdata.GetInt("tYear");
      tMonth   = TreeReaderdata.GetInt("tMonth");
      tDate    = TreeReaderdata.GetInt("tDate");
      tHour    = TreeReaderdata.GetInt("tHour");
      tMinute  = TreeReaderdata.GetInt("tMinute");
      tSecond  = TreeReaderdata.GetInt("tSecond");
      nLayers  = TreeReaderdata.GetInt("nLayers");
      nH       = TreeReaderdata.GetInt("nH");
      iHit     = nH;
      board_   = TreeReaderdata.GetPtrInt("board");
      channel_ = TreeReaderdata.GetPtrInt("channel");
      pwidth_  = TreeReaderdata.GetPtrInt("pwidth");
      pwidthScaleFactor_ 
               = TreeReaderdata.GetPtrInt("pwidthScaleFactor");;
      pcnt_    = TreeReaderdata.GetPtrInt("pcnt");
      tcnt_    = TreeReaderdata.GetPtrLong64("tcnt");
      dtime_   = TreeReaderdata.GetPtrDouble("dtime");
      dtimeInt_= TreeReaderdata.GetPtrLong64("dtimeInt");
    }
    void GetTreeReaderMEID(TreeReader &TreeReaderdata, const Long64_t ev){
      TreeReaderdata.GetEntry(ev);
      TrackIndex = TreeReaderdata.GetInt("TrackIndex");
      unixtime   = TreeReaderdata.GetLong64("unixtime");
      tYear      = TreeReaderdata.GetInt("tYear");
      tMonth     = TreeReaderdata.GetInt("tMonth");
      tDate      = TreeReaderdata.GetInt("tDate");
      tHour      = TreeReaderdata.GetInt("tHour");
      tMinute    = TreeReaderdata.GetInt("tMinute");
      tSecond    = TreeReaderdata.GetInt("tSecond");
      ElectronID = TreeReaderdata.GetBool("ElectronID");
      MuonID     = TreeReaderdata.GetBool("MuonID");
      NoiseID    = TreeReaderdata.GetBool("NoiseID");
      IDtight    = TreeReaderdata.GetShort("IDtight");
      nLayers    = TreeReaderdata.GetInt("nLayers");
      iHit       = TreeReaderdata.GetInt("iHit");
      nH         = TreeReaderdata.GetInt("nH");
      board_     = TreeReaderdata.GetPtrInt("board");
      channel_   = TreeReaderdata.GetPtrInt("channel");
      iX_        = TreeReaderdata.GetPtrInt("iX");
      iY_        = TreeReaderdata.GetPtrInt("iY");
      iZ_        = TreeReaderdata.GetPtrInt("iZ");
      pwidth_    = TreeReaderdata.GetPtrInt("pwidth");
      pwidthScaleFactor_ 
                 = TreeReaderdata.GetPtrInt("pwidthScaleFactor");
      pcnt_      = TreeReaderdata.GetPtrInt("pcnt");
      tcnt_      = TreeReaderdata.GetPtrLong64("tcnt");
      dtime_     = TreeReaderdata.GetPtrDouble("dtime");
      dtimeInt_  = TreeReaderdata.GetPtrLong64("dtimeInt");
    }
    void TReaderPtrToVec(){
      for(int iiHit=0;iiHit<iHit;iiHit++){
        board   .push_back(board_   [iiHit]); 
        channel .push_back(channel_ [iiHit]);
        iX      .push_back(iX_      [iiHit]); 
        iY      .push_back(iY_      [iiHit]); 
        iZ      .push_back(iZ_      [iiHit]);
        pwidth  .push_back(pwidth_  [iiHit]);
        pwidthScaleFactor
                .push_back(pwidthScaleFactor_[iiHit]); 
        pcnt    .push_back(pcnt_    [iiHit]);
        tcnt    .push_back(tcnt_    [iiHit]);
        dtime   .push_back(dtime_   [iiHit]);
        dtimeInt.push_back(dtimeInt_[iiHit]);
      }
    }
    void Clear(){
      MuonID =false;
      ElectronID=false;
      NoiseID =false;
      IDtight =0;
      pwidth.clear();
      pwidthScaleFactor.clear();
      board.clear();
      channel.clear();
      pcnt.clear();
      tcnt.clear();
      dtime.clear();
      dtimeInt.clear();
      iX.clear();
      iY.clear();
      iZ.clear();
    }
  };
};



  

void GobelFormats(){}