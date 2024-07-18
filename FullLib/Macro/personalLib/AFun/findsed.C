#include <typeinfo>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "TLorentzVector.h"
#include "/home/7202018/personalLib/AFun/sigmaEff.h"
#include "Utilities.h"

using namespace std;
float s05 = 0.382924922548026;
float s10 = 0.682689492137086;
float s15 = 0.866385597462284;
float s20 = 0.954499736103642;
float s25 = 0.987580669348448;
float s30 = 0.997300203936740;
float s35 = 0.999534741841929;
float s40 = 0.999936657516334;
float s45 = 0.999993204653751;
float s50 = 0.999999426696856;
/*
  char MZee[6][60]={
  "/home/7202018/exercise/v10/Save/MzdaBE.dat",
  "/home/7202018/exercise/v10/Save/MzdaCE.dat",
  "/home/7202018/exercise/v10/Save/MzdaDE.dat",
  "/home/7202018/exercise/v10/Save/MzdaEE.dat",
  "/home/7202018/exercise/v10/Save/MzdaFE.dat",
  "/home/7202018/exercise/v10/Save/MzmcE.dat"
  };
*/
/*
void findsed(){
  //const char  inpathdata[100]={"/home/7202018/exercise/v10/Save/Mzda*"};
  //const char  inpathmc[100]={"/home/7202018/exercise/v10/Save/Mzmc*"};
  vector<float> datm;
  vector<float> date;
  vector<float> datme;
  vector<float> mcmm;
  vector<float> mcee;
  vector<float> mcme;
  vector<string> dafiles;// = find_files(inpathdata);
  vector<string> mcfiles;// = find_files(inpathmc);
  dafiles.push_back("/home/7202018/exercise/v10/Save/MzdaBE.dat");
  dafiles.push_back("/home/7202018/exercise/v10/Save/MzdaCE.dat");
  dafiles.push_back("/home/7202018/exercise/v10/Save/MzdaDE.dat");
  dafiles.push_back("/home/7202018/exercise/v10/Save/MzdaEE.dat");
  dafiles.push_back("/home/7202018/exercise/v10/Save/MzdaFE.dat");
  mcfiles.push_back("/home/7202018/exercise/v10/Save/MzmcE.dat");
  char df[5][100]={
    dafiles[0],dafiles[1],dafiles[2],dafiles[3],dafiles[4]
  }
  
  for(UInt_t i=0;i<dafiles.size();i++){
    ifstream in(df[i]);
    cout<<"open file:\t"<<dafiles[i]<<endl;
    for(float a=0,b=0; in>>a>>b;){
      datm.push_back(a);
      cout<<a<<"\t"<<b<<endl;
      date.push_back(b);
      datme.push_back(a+b);
    }
    cout<<"finished push back:\t"<<dafiles[i]<<endl;
    in.close();
  }
  for(int i=0;i<mcfiles.size();i++){
    ifstream in(Form("%s",mcfiles[i]));
    cout<<"open file:\t"<<mcfiles[i]<<endl;
    for(float a=0,b=0; in>>a>>b; ){
      mcmm.push_back(a);
      mcee.push_back(b);
      mcme.push_back(a+b);
    }
    cout<<"finished push back:\t"<<mcfiles[i]<<endl;
    in.close();
  }

  cout<<"data element:\t"<<datm.size() <<endl;
  cout<<"mcmm element:\t"<<mcmm.size() <<endl;
  float mdi = *min_element(datm.begin(), datm.end());
  float mdx = *max_element(datm.begin(), datm.end());
  float edi = *min_element(date.begin(), date.end());
  float edx = *max_element(date.begin(), date.end());
  float mdxp = *max_element(datme.begin(), datme.end());

  ofstream outsigma("./Save/outsigma.dat");

  float ROS = s10;//rangeOfSigma
  cout<<"Finding the sigmaEff of MudataSigmaE"<<endl;
  float sigmaEffdatam=sigmaEff(datm,ROS,mdi,mdx);
  outsigma<<"MudataSigmaE\t"<<sigmaEffdatam<<endl;
  cout<<"\nMudataSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of EldataSigmaE"<<endl;
  float sigmaEffdatae=sigmaEff(date,ROS,mdi,mdx);  
  outsigma<<"EldataSigmaE\t"<<sigmaEffdatae<<endl;  
  cout<<"\nEldataSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of MuMcSigmaE"<<endl;
  float sigmaEffMcm=sigmaEff(mcmm,ROS,mdi,mdx);
  outsigma<<"MuMcSigmaE\t"<<sigmaEffMcm<<endl;
  cout<<"\nMuMcSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of ElMcSigmaE"<<endl;
  float sigmaEffMce=sigmaEff(mcee,ROS,mdi,mdx);
  outsigma<<"ElMcSigmaE\t"<<sigmaEffMce<<endl;
  cout<<"\nElMcSigmaE.dat is finished." <<endl;

  cout<<"Finding the sigmaEff of ZZdataSigmaE"<<endl;
  float sigmaEffdatem=sigmaEff(datme,ROS,mdi,mdxp);
  outsigma<<"ZZdataSigmaE\t"<<sigmaEffdatem<<endl;
  cout<<"\nZZdataSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of ZZMcSigmaE"<<endl;
  float sigmaEffMcme=sigmaEff(mcme,ROS,mdi,mdxp);
  outsigma<<"ZZMcSigmaE\t"<<sigmaEffMcme<<endl;
  cout<<"\nZZMcSigmaE is finished." <<endl;

  outsigma.close();
  cout<<"sigmaEffdatam:\t"<<sigmaEffdatam<<endl;
  cout<<"sigmaEffdatae:\t"<<sigmaEffdatae<<endl;
  cout<<"sigmaEffMcm:\t"<<sigmaEffMcm<<endl;
  cout<<"sigmaEffMce:\t"<<sigmaEffMce<<endl;
  cout<<"sigmaEffdatem:\t"<<sigmaEffdatem<<endl;
  cout<<"sigmaEffMcme:\t"<<sigmaEffMcme<<endl;
}
*/

void findsed(){
  vector<float> datm;
  vector<float> date;
  vector<float> datme;
  vector<float> mcmm;
  vector<float> mcee;
  vector<float> mcme;
  char MZee[6][60]={
  "/home/7202018/exercise/v10/Save/MzdaBE.dat",
  "/home/7202018/exercise/v10/Save/MzdaCE.dat",
  "/home/7202018/exercise/v10/Save/MzdaDE.dat",
  "/home/7202018/exercise/v10/Save/MzdaEE.dat",
  "/home/7202018/exercise/v10/Save/MzdaFE.dat",
  "/home/7202018/exercise/v10/Save/MzmcE.dat"
  };
  for(int i=0;i<5;i++){
    ifstream in(MZee[i]);
    cout<<"open file:\t"<<MZee[i]<<endl;
    for(float a=0,b=0; in>>a>>b; ){
      datm.push_back(a);
      date.push_back(b);
      datme.push_back(a+b);
    }
    cout<<"finished push back:\t"<<MZee[i]<<endl;
    in.close();
  }
  ifstream in(MZee[5]);
  cout<<"open file:\t"<<MZee[5]<<endl;
  for(float a=0,b=0; in>>a>>b; ){
    mcmm.push_back(a);
    mcee.push_back(b);
    mcme.push_back(a+b);
  }
    cout<<"finished push back:\t"<<MZee[i]<<endl;
    in.close();
  

  cout<<"data element:\t"<<datm.size() <<endl;
  cout<<"mcmm element:\t"<<mcmm.size() <<endl;
  float mdi = *min_element(datm.begin(), datm.end());
  float mdx = *max_element(datm.begin(), datm.end());
  float edi = *min_element(date.begin(), date.end());
  float edx = *max_element(date.begin(), date.end());
  float mdxp = *max_element(datme.begin(), datme.end());

  ofstream outsigma("./Save/outsigma.dat");

  float ROS = s10;//rangeOfSigma
  cout<<"Finding the sigmaEff of MudataSigmaE"<<endl;
  float sigmaEffdatam=sigmaEff(datm,ROS,mdi,mdx);
  outsigma<<"MudataSigmaE\t"<<sigmaEffdatam<<endl;
  cout<<"\nMudataSigmaE is finished." <<endl;
  
  cout<<"Finding the sigmaEff of MuMcSigmaE"<<endl;
  float sigmaEffMcm=sigmaEff(mcmm,ROS,mdi,mdx);
  outsigma<<"MuMcSigmaE\t"<<sigmaEffMcm<<endl;
  cout<<"\nMuMcSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of EldataSigmaE"<<endl;
  float sigmaEffdatae=sigmaEff(date,ROS,mdi,mdx);  
  outsigma<<"EldataSigmaE\t"<<sigmaEffdatae<<endl;  
  cout<<"\nEldataSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of ElMcSigmaE"<<endl;
  float sigmaEffMce=sigmaEff(mcee,ROS,mdi,mdx);
  outsigma<<"ElMcSigmaE\t"<<sigmaEffMce<<endl;
  cout<<"\nElMcSigmaE.dat is finished." <<endl;

  cout<<"Finding the sigmaEff of ZZdataSigmaE"<<endl;
  float sigmaEffdatem=sigmaEff(datme,ROS,mdi,mdxp);
  outsigma<<"ZZdataSigmaE\t"<<sigmaEffdatem<<endl;
  cout<<"\nZZdataSigmaE is finished." <<endl;

  cout<<"Finding the sigmaEff of ZZMcSigmaE"<<endl;
  float sigmaEffMcme=sigmaEff(mcme,ROS,mdi,mdxp);
  outsigma<<"ZZMcSigmaE\t"<<sigmaEffMcme<<endl;
  cout<<"\nZZMcSigmaE is finished." <<endl;

  outsigma.close();
  cout<<"sigmaEffdatam:\t"<<sigmaEffdatam<<endl;
  cout<<"sigmaEffMcm:\t"<<sigmaEffMcm<<endl;
  cout<<"sigmaEffdatae:\t"<<sigmaEffdatae<<endl;
  cout<<"sigmaEffMce:\t"<<sigmaEffMce<<endl;
  cout<<"sigmaEffdatem:\t"<<sigmaEffdatem<<endl;
  cout<<"sigmaEffMcme:\t"<<sigmaEffMcme<<endl;
}

