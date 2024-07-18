#include <vector>
#include <typeinfo>
#include <algorithm>
#include <TMath.h>
#include <TRandom.h>
#include "../Math/DBMMath.h"
using namespace std;
using namespace DBMMath;

namespace Structure
{

  class DBMshow{
  public:

  private:
  protected:
    void SSOIPrint(){
      cout<<"────────────────Start─────Show──────Object─────Imformation────────────────"<<endl;
    }
    void OISEPrint(){
      cout<<"────────────────Object──────Imformatio───────Show──────End────────────────"<<endl;
    }
    void OTNPrint(const char* objName){
      cout<<"Object   Type:    \" "<<objName<<" \""<<endl;
    }
  };

  class DBM3DVec
  {
  public:
    double vecX, vecY, vecZ, vecL;
    double uvecX,uvecY,uvecZ;
    DBM3DVec(double X=0,double Y=0,double Z=1){
      SetVector(X,Y,Z);
    }
    DBM3DVec(const DBM3DVec *D3v){
      SetVector(D3v->vecX,D3v->vecY,D3v->vecZ);
    }
    // DBM3DVec(const DBMSpVec *spv){
      // SphToCar(spv->Rlen,spv->Dthe,spv->Dphi);
    // } @@
    virtual ~DBM3DVec(){};
    //function
    void SetVector(double X=0,double Y=0,double Z=0){
      vecX = X;
      vecY = Y;
      vecZ = Z;
      VecLen();
      SetUnitVec();
    }
    void Scale(double ratio=1){
      if(ratio==0) {
        cout<<"Warning: DBM3DVec::Scale input ratio =0"<<endl;
      }
      SetVector(vecX*ratio,vecY*ratio,vecZ*ratio);
    }
    void ReSet(){
      SetVector();
    }
    void Rotate(const double A,const double B,const double G){
      double vector3D[3]={vecX,vecY,vecZ};
      VectorRotate3D(vector3D[0],vector3D[1],vector3D[2], A, B, G);
      SetVector(vector3D[0],vector3D[1],vector3D[2]);
    }
  private:
    // void SphToCar(const double Rlen=1,const double Dthe=0,const double Dphi=0){
      // vecL = Rlen;
      // vecZ = Rlen*cos(Dthe);
      // vecX = Rlen*sin(Dthe)*cos(Dphi);
      // vecY = Rlen*sin(Dthe)*sin(Dphi);
      // SetUnitVec();
    // }
    void Show(){
      cout<<Form("vecX%13.2e  vecY%13.2e  vecZ%13.2e\n",vecX,vecY,vecZ);
      cout<<Form("uvecX%12.2e  uvecY%12.2e  uvecZ%12.2e  vecL%13.2e\n",uvecX,uvecY,uvecZ,vecL);
    }
  protected:
    void SetUnitVec(){
      if(vecL!=0){
        uvecX = vecX/vecL;  uvecY = vecY/vecL;  uvecZ = vecZ/vecL;
      }else{
        uvecX = 0; uvecY=0; uvecZ=0;
        cout<<"Warning: SetUnitVec() get a zero Vector !!"<<endl;
      }
    }
    void ReFormVec(){
      vecX = vecL * uvecX;
      vecY = vecL * uvecY;
      vecZ = vecL * uvecZ;
    }
    void VecLen(){
      double L = sqrt(vecX*vecX+vecY*vecY+vecZ*vecZ);
      if(L>minDouble) vecL = L;
      else vecL = 0;
    }
  };

  class DBMSpVec
  {
  public:
    double Rlen, Dthe, Dphi;
    DBMSpVec(double A=1,double B=0,double C=0,const char *option = "S"){
      if (strcmp(option,"S")) SetVector(A,B,C);
      if (strcmp(option,"C")) CarToSph(A,B,C);
      else {
        cout<<"DBMSpVec(A,B,C,option) option need to be \"S\" of \"C\""<<endl;
        throw;
      }
    }
    DBMSpVec(const DBMSpVec *spv){
      SetVector(spv->Rlen,spv->Dthe,spv->Dphi);
    }
    DBMSpVec(const DBM3DVec *D3v){
      CarToSph(D3v->uvecX,D3v->uvecY,D3v->uvecZ,D3v->vecL);
    }
    DBMSpVec(const double vec[3]){
      CarToSph(vec[0],vec[1],vec[2]);
    }
    virtual ~DBMSpVec(){}
    //function
    void SetVector(double R=1,double T=0,double F=0){
      if(IntOrNot(T)&&IntOrNot(F)){
        T = T/180.*PI;
        F = F/180.*PI;
      }
      Rlen = R;
      Dthe = T;
      Dphi = F;
    }
    void Scale(double ratio=1){
      if(ratio==0) {
        cout<<"Warning: DBMSpVec::Scale input ratio =0"<<endl;
        cout<<"ratio:  "<<ratio<<endl;
        throw;
      }
      SetVector(Rlen*ratio,Dthe,Dphi);
    }
    void Rotate(double dT,double dF){
      if(IntOrNot(dT)&&IntOrNot(dF)){
        dT = dT/180.*PI;
        dF = dF/180.*PI;
      }
      Dthe += dT;
      Dphi += dF;
    }
    void ReSet(){
      SetVector();
    }
  private:
    void Show(){
      cout<<Form("Rlen%13.2e  Dthe%9.1f deg  Dphi%9.1f deg\n"
                ,Rlen,Dthe/PI*180.,Dphi/PI*180.);
    }
    void CarToSph(const double uvecX,const double uvecY,const double uvecZ,const double vecL){
      Rlen = vecL;
      Dthe = acos(uvecZ);
      if(Dthe==0) Dphi=0;
      else{
        double uxDsinD = uvecX/sin(Dthe);
        if     (uxDsinD>1) uxDsinD = +1;
        else if(uxDsinD<-1) uxDsinD = -1;
        Dphi = acos(uxDsinD)+(uvecY<0)*PI;
      }
    }
    void CarToSph(const double vecX,const double vecY,const double vecZ){
      double vecL = sqrt(vecX*vecX+vecY*vecY+vecZ*vecZ);
      if(vecL==0){
        cout<<"DBMSpVec::CarToSph(ux,uy,uz) couldn't input 0 vec!!"<<endl;
        throw;
      } 
      CarToSph(vecX/vecL, vecY/vecL, vecZ/vecL, vecL);
    }
  protected:
  };

  class DBMName
  {  
  public:
    char name[30];
    DBMName(const char names[]="default"){
      SetName(names);
    }
    virtual ~DBMName(){
    }
    //function
    void SetName(const char *names){
      sprintf(name,names);
    }
    string GetName(){
      return name;
    }
  private:
    void Show(){
      cout<<"name:    "<<name<<endl;
    }
  protected:
  };

  class DBMdim
  {
  public:
    double leng, widt, heig ,size;
    DBMdim(double length=1,double width=0,double height=0){
      SetDimension(length,width,height);
    }
    virtual ~DBMdim(){};
    //function
    void SetDimension(double l=1,double w=1,double h=1){
      if(l<0||w<0||h<0){
        cout<<"Error: The component of Object DBMdim shouldn't be negative"<<endl;
        cout<<"Problem Object: DBMdim"<<endl;
        backShow(l,w,h);
        throw;
      }
      if(l<minDouble) l=0;
      if(w<minDouble) w=0;
      if(h<minDouble) h=0;
      leng = l;
      widt = w;
      heig = h;
      ImforWrite();
    }
   void Scale(double tl=1,double tw=1,double th=1){
      if(tl<0||tw<0||th<0){
        cout<<"Error: The component of Object DBMdim shouldn't scale negative ratio"<<endl;
        cout<<"Problem Object: DBMdim::Scale"<<endl;
        backShow(tl,tw,th);
        throw;
      }
      SetDimension(leng*tl,widt*tw,heig*th);
    }
    double GetDimension(int index){
      return *dim[index]; 
    }
    void GetDimension(double &Dx,double &Dy,double &Dz){
      Dx= leng;  Dy= widt;  Dz= heig;
    }
  protected:
    void backShow(double l,double w,double h){
      cout<<Form("leng%13.2e  widt%13.2e  heig%13.2e\n",l,w,h);
      // cout<<"leng\t"<<leng<<"\twidt\t"<<widt<<"\theig\t"<<heig<<endl;
    }
    void ImforWrite(){
      dim[0] = &leng;
      dim[1] = &widt;
      dim[2] = &heig;
      size = sqrt(leng*leng+widt*widt+heig*heig);
    }
  private:
    double *dim[3];
    void Show(){
      backShow(leng,widt,heig);
      // cout<<"leng\t"<<leng<<"\twidt\t"<<widt<<"\theig\t"<<heig<<endl;
    }

  };

  class DBMpos
  {
  public:
    double posX, posY, posZ;
    DBMpos(double PosX=0,double PosY=0,double PosZ=0){
      SetPosition(PosX,PosY,PosZ);
    }
    virtual ~DBMpos(){}
    //function
    void SetPosition(double X=0,double Y=0,double Z=0){
      MinDIns(X);
      MinDIns(Y);
      MinDIns(Z);
      posX = X;
      posY = Y;
      posZ = Z;
    }
    void Move(double dX=0,double dY=0,double dZ=0){
      SetPosition(posX+dX,posY+dY,posZ+dZ);
    }
    double GetPosition(int index){
      if    (index==0) return posX;
      else if(index==1) return posY;
      else if(index==2) return posZ;
      else{
        cout<<"Warning: DBMpos::GetPosition(int index(0~2)), the index out of Range!!!"<<endl;
        throw;
      }
    }
    void GetPosition(double &Px,double &Py,double &Pz){
      Px= posX;  Py= posY;  Pz= posZ;
    }
  private:
    void Show(){
      cout<<Form("posX%13.2e  posY%13.2e  posZ%13.2e\n",posX,posY,posZ);
    }
  protected:
  };

  class DBM3Drot
  {
  public:
    double theX, theY, theZ;
    DBM3Drot(double TheX=0,double TheY=0,double TheZ=0){
      theX = TheX;
      theY = TheY;
      theZ = TheZ;
    }
    virtual ~DBM3Drot(){}
    //function
    void SetRotation(double A=0,double B=0,double G=0){
      if(IntOrNot(A)&&IntOrNot(B)&&IntOrNot(G)){
        A = A/180.*PI;
        B = B/180.*PI;
        G = G/180.*PI;
      }
      theX = A;
      theY = B;
      theZ = G;
      ImforWrite();
    }
    void Rotate(double dA=0,double dB=0,double dG=0){
      if(IntOrNot(dA)&&IntOrNot(dB)&&IntOrNot(dG)){
        dA = dA/180.*PI;
        dB = dB/180.*PI;
        dG = dG/180.*PI;
      }
      SetRotation(theX+dA,theY+dB,theZ+dG);
    }
    double GetRotation(int index){
      return *rot[index]; 
    }
    void GetRotation(double &Rx,double &Ry,double &Rz){
      Rx= theX;  Ry= theY;  Rz= theZ;
    }
  private:
    double *rot[3];
    void Show(){
      cout<<Form("theX%9.1f deg  theY%9.1f deg  theZ%9.1f deg\n"
            ,theX/PI*180.,theY/PI*180.,theZ/PI*180.);
    }
    void ImforWrite(){
      rot[0] = &theX;
      rot[1] = &theY;
      rot[2] = &theZ;
    }
  protected:
  };
  
  class DBMSprot
  {
  public:
    double the, phi;
    DBMSprot(double The=0,double Phi=0){
      if(IntOrNot(The)&&IntOrNot(Phi)){
        The /=180./PI;
        Phi /=180./PI;
      }
      the = The;
      phi = Phi;
    }
    virtual ~DBMSprot(){}
    //function
    void SetRotation(double The=0,double Phi=0){
      if(IntOrNot(The)&&IntOrNot(Phi)){
        The = The/180.*PI;
        Phi = Phi/180.*PI;
      }
      the = The;
      phi = Phi;
      ImforWrite();
    }
    void Rotate(double dth=0,double dph=0){
      // cout<<"dth<<dph  "<<dth<<"  "<<dph<<endl;
      if(IntOrNot(dth)&&IntOrNot(dph)){
        dth /=180./PI;
        dph /=180./PI;
      }
      // cout<<"dth<<dph  "<<dth<<"  "<<dph<<endl;
      SetRotation(the+dth,phi+dph);
      ImforWrite();
    }
    double GetRotation(int index){
      return *rot[index]; 
    }
    void GetRotation(double &Rx,double &Ry){
      Rx= the;  Ry= phi;
    }
  private:
    double *rot[3];
    void Show(){
      cout<<Form("the%10.1f deg  phi%10.1f deg\n",the/PI*180.,phi/PI*180.);
    }
    void ImforWrite(){
      rot[0] = &the;
      rot[1] = &phi;
    }
  protected:
  };

  class DBMPoint: public DBMName, public DBMpos, public DBMshow{
  public: 
    double OPT;
    double *point[4];
    DBMPoint(const char names[]="defaultPoint", double pX=0,double pY=0,double pZ=0,double option=0):DBMName(names),DBMpos(pX,pY,pZ){
      SetOption(option);
      DBMPoint::ImforWrite();
    }
    
    DBMPoint(const DBMPoint *Object,const char names[]="defaultPoint"){ 
      SetImformation(names, Object->posX, Object->posY, Object->posZ, Object->OPT);
      DBMPoint::ImforWrite();
    }
    virtual ~DBMPoint(){
      
      //cout<<&point[0]<<"  "<<&point[1]<<endl;
    }
    
    bool ComparePoint(const DBMPoint *Pb){
      double 
        Va=(Pb->posX)-(posX),
        Vb=(Pb->posY)-(posY),
        Vc=(Pb->posZ)-(posZ);
        // cout<<(Va)<<"\t"<<(Vb)<<"\t"<<(Vc)<<endl;
      MinDIns(Va); MinDIns(Vb); MinDIns(Vc);
        // cout<<(Va)<<"\t"<<(Vb)<<"\t"<<(Vc)<<endl;
      // bool TF = ;
      // cout<<"TF      "<<TF<<endl;
      return (Va)==0&&(Vb)==0&&(Vc)==0;
    }
    double GetFar(){
      return sqrt(posX*posX+posY*posY+posZ*posZ);
    }
    
  private:
    void SetOption(double option){
      OPT = option;
    }
    void SetImformation(const char names[]="defaultPoint", double pX=0,double pY=0,double pZ=0, double option=0){
      DBMName::SetName(names);
      DBMpos::SetPosition(pX,pY,pZ);
      SetOption(option);
    }
    void ReSet(){
      SetImformation();
    }
    void ImforWrite(){
      point[0]=&posX;  point[1]=&posY;  point[2]=&posZ;  point[3]=&OPT;
    }
    void Show(bool checkMode=false){
      DBMshow::SSOIPrint();
      DBMshow::OTNPrint("DBMPoint");
      DBMName::Show();
      backShow();
      DBMshow::OISEPrint();
    }
  protected:
    void backShow(){
      DBMpos::Show();
      cout<<Form("Option:  \" %2.f \"\n",OPT);
    }
  };



  class DBMLine: public DBMName,public DBM3DVec,public DBMSpVec, public DBMpos, public DBMshow
  {
  public: 
    double *dir3D[4];//direction
    double *dirSp[3];//direction
    double *pos[3];//position
    DBMLine(const char names[]="defaultline", double dA=0,double dB=0,double dC=1,double pX=0,double pY=0,double pZ=0,const char* Mode="C"):DBMName(names),DBMpos(pX,pY,pZ){
      DBMLine::SetVector(dA,dB,dC,Mode);
      DBMLine::ImforWrite();
    }
    
    DBMLine(const DBMLine *Object,const char names[]="defaultline"){ 
      SetImformation(names, Object->vecX, Object->vecY, Object->vecZ, Object->posX, Object->posY, Object->posZ);
      cout<<names<<endl;
    }
    virtual ~DBMLine(){
    }
    
    void SetVector(double dA=0,double dB=0,double dC=1,const char* Mode="C"){
      if     (strcmp(Mode,"C")==0) Set3DVec(dA,dB,dC);
      else if(strcmp(Mode,"S")==0) SetSpVec(dA,dB,dC);
      else cout<<"Wrong Mode of DBMLine::SetVector(dA,dB,dC,Mode) \"Mode\" need to be Cartesian-'C' or Spherical-'S'"<<endl;
    }
    void Set3DVec(double dX=0,double dY=0,double dZ=1){
      DBM3DVec::SetVector(dX,dY,dZ);
      CarToSph();
    }
    void SetSpVec(double dR=1,double dT=0,double dF=0){
      DBMSpVec::SetVector(dR,dT,dF);
      SphToCar();
    }
    void SetLineLength(double t){
      *dir3D[3] = t;
      ReFormVec();
    }
    void SetLineRot(const double the,const double phi){
      DBMSpVec::Rotate(the,phi);
      SetVector(Rlen,Dthe,Dphi,"S");
    }
    double GetLineLength(){
      return *dir3D[3];
    }
    
    
    void ReSet(){
      SetVector(0,0,1);
    }
    void Show(bool checkMode=false){
      DBMshow::SSOIPrint();
      DBMshow::OTNPrint("DBMLine");
      DBMName::Show();
      backShow();
      if(checkMode){
        DBM3DVec::Show();
        DBMSpVec::Show();
        DBMpos::Show();
        cout<<Form("dir3D[0]%9.2e  dir3D[1]%9.2e  dir3D[2]%9.2e  dir3D[3]%9.2e\n",*dir3D[0],*dir3D[1],*dir3D[2],*dir3D[3]);
        cout<<Form("dirSp[0]%9.2e  dirSp[1]%9.2e  dirSp[2]%9.2e\n",*dirSp[0],*dirSp[1],*dirSp[2]);
        cout<<Form("pos[0]%11.2e  pos[1]%11.2e  pos[2]%11.2e\n",*pos[0],*pos[1],*pos[2]);
      }
      DBMshow::OISEPrint();
    }
  private:
    void CarToSph(){
      // cout<<"vecL"<<vecL<<"3"<<endl;
      Rlen = vecL;
      Dthe = acos(uvecZ);
      if(Dthe==0) Dphi=0;
      else{
        double uxDsinD = uvecX/sin(Dthe);
        if     (uxDsinD>1) uxDsinD = +1;
        else if(uxDsinD<-1) uxDsinD = -1;
        Dphi = acos(uxDsinD)+(uvecY<0)*PI;
      }
      
    }
    void SphToCar(){
      vecL = Rlen;
      vecZ = Rlen*cos(Dthe);
      vecX = Rlen*sin(Dthe)*cos(Dphi);
      vecY = Rlen*sin(Dthe)*sin(Dphi);
      DBM3DVec::SetUnitVec();
    }
    void SetImformation(const char names[]="defaultline", double dA=0,double dB=0,double dC=1,double pX=0,double pY=0,double pZ=0){
      DBMName::SetName(names);
      SetVector(dA,dB,dC,"C");
      DBMpos::SetPosition(pX,pY,pZ);
      ImforWrite();
    } 
    
  protected:
    void ImforWrite(){
      pos[0]=&posX;    pos[1]=&posY;   pos[2]=&posZ;
      dir3D[0]=&vecX;  dir3D[1]=&vecY;  dir3D[2]=&vecZ;  dir3D[3]=&vecL;
      dirSp[0]=&Rlen;  dirSp[1]=&Dthe;  dirSp[2]=&Dphi;
      if(vecL==0){
        cout<<"\tHint:"<<endl;
        cout<<"DBMLine(c.char names[], double dA,double dB,double dC,double pX,double pY,double pZ,c.char* Mode=)"<<endl;
      }
    }
    void backShow(double Rm=-1./0.,double RM=1./0.){
      cout<<"    "<<
      "x-"<<Form("%9.2e",*pos[0])<<"   "<<
      "y-"<<Form("%9.2e",*pos[1])<<"   "<<
      "z-"<<Form("%9.2e",*pos[2])<<endl;
      cout<<"LF:"<<
      "(-----------)+(-----------)+(-----------)=d, ";
      cout<<Form("d:(%-8.2e,%8.2e)",Rm,RM)<<endl;
      cout<<"     "<<
      Form("%9.2e",*dir3D[0])<<"     "<<
      Form("%9.2e",*dir3D[1])<<"     "<<
      Form("%9.2e",*dir3D[2])<<endl;
    }
  };
  
  class DBMLineS: public DBMLine
  {
  public: 
    double *Epos[3], EposX, EposY, EposZ;
    DBMLineS(const char names[]="defaultlineS", double dA=0,double dB=0,double dC=1,double pX=0,double pY=0,double pZ=0,const char* Mode="C"):DBMLine(names, dA, dB, dC, pX, pY, pZ, Mode){
      SetImformation();
    }
    
    DBMLineS(const DBMLine *Object,const char names[]="defaultlineS"):DBMLine(Object,names){ 
      SetImformation();
    }
    DBMLineS(const DBMPoint *p1,const DBMPoint *p2,const char names[]="defaultlineS"){  
      DBMLine::SetImformation(
        names,
        p2->posX-p1->posX,
        p2->posY-p1->posY,
        p2->posZ-p1->posZ,
        p1->posX,
        p1->posY,
        p1->posZ
      );
      SetImformation();
    }
    
    virtual ~DBMLineS(){}
    
    double GetLength(){
      return vecL;
    }
    
    void Show(bool checkMode=false){
      DBMshow::SSOIPrint();
      DBMshow::OTNPrint("DBMLineS");
      DBMName::Show();
      DBM3DVec::Show();
      DBMSpVec::Show();
      DBMpos::Show();
      cout<<Form("EposX%12.2e  EposY%12.2e  EposZ%12.2e\n",EposX,EposY,EposZ);
      DBMLine::backShow(0,vecL);
      if(checkMode){
        cout<<Form("dir3D[0]%9.2e  dir3D[1]%9.2e  dir3D[2]%9.2e  dir3D[3]%9.2e\n",*dir3D[0],*dir3D[1],*dir3D[2],*dir3D[3]);
        cout<<Form("dirSp[0]%9.2e  dirSp[1]%9.2e  dirSp[2]%9.2e\n",*dirSp[0],*dirSp[1],*dirSp[2]);
        cout<<Form("pos[0]%11.2e  pos[1]%11.2e  pos[2]%11.2e\n",*dirSp[0],*dirSp[1],*dirSp[2]);
      }
      DBMshow::OISEPrint();
    }
    void SetLineLength(double t){
      DBMLine::SetLineLength(t);
      EposX = vecX+posX;
      EposY = vecY+posY;
      EposZ = vecZ+posZ;
    }
  private:
    void SetImformation(){
      SetLineLength(vecL);
      ImforWrite();
    }
  protected:
    void ImforWrite(){
      pos  [0]=&posX;    pos  [1]=&posY;   pos [2]=&posZ;
      dir3D[0]=&vecX;    dir3D[1]=&vecY;   dir3D[2]=&vecZ;  dir3D[3]=&vecL;
      dirSp[0]=&Rlen;    dirSp[1]=&Dthe;   dirSp[2]=&Dphi;
      Epos [0]=&EposX;   Epos [1]=&EposY;  Epos [2]=&EposZ;
    }
    
  };
  
  class DBMPlane: public DBMName,public DBM3DVec,public DBMpos, public DBMshow
  {
  public: 
    double *plane[4];//direction
    double *cmp[3];//centre mass position
    double vecP;
    DBMPlane(const char names[]="defaultline", double dX=0,double dY=0,double dZ=1, double pX=0, double pY=0, double pZ=1):DBMName(names){
      SetImformation(dX,dY,dZ,pX,pY,pZ);
    }
    DBMPlane(const DBMPlane *Object,const char names[]="defaultline"):DBMName(names){ 
      SetImformation(Object->vecX, Object->vecY, Object->vecZ, Object->posX, Object->posY, Object->posZ);
    }
    virtual ~DBMPlane(){}

    void SetPosition(double pX= 0,double pY= 0,double pZ= 0){
      DBMpos::SetPosition(pX,pY,pZ);
      vecP = vecL + posX*uvecX+posY*uvecY+posZ*uvecZ;
    }
    void Move(double dpX= 0,double dpY= 0,double dpZ= 0){
      DBMpos::Move(dpX,dpY,dpZ);
      vecP = vecL + posX*uvecX+posY*uvecY+posZ*uvecZ;
    }
    void SetPlaneRot(const double thA,const double thB,const double thC){
      // cout<<"Please use SetPlaneRot(c.double the, c.double phi){} now!"<<endl;
      // throw;
      VectorRotate3D(*plane, thA, thB, thC);
    }
    void SetPlaneRot(const double the,const double phi){
      DBM3DVec *tmp_cal3DVec = new DBM3DVec(vecX,vecY,vecZ);
      DBMSpVec *tmp_calSpVec = new DBMSpVec(tmp_cal3DVec);
      tmp_calSpVec->Rotate(the, phi);//@@
      vecL = tmp_calSpVec->Rlen;
      vecZ = tmp_calSpVec->Rlen*cos(tmp_calSpVec->Dthe);
      vecX = tmp_calSpVec->Rlen*sin(tmp_calSpVec->Dthe)*cos(tmp_calSpVec->Dphi);
      vecY = tmp_calSpVec->Rlen*sin(tmp_calSpVec->Dthe)*sin(tmp_calSpVec->Dphi);
      // if(tmp_calSpVec->Dthe>(PI/2.)&&vecZ>0) vecZ*=-1;
      // if(tmp_calSpVec->Dphi>(PI)&&vecY>0) vecY*=-1;
      // if(tmp_calSpVec->Dphi>(PI/2.)&&tmp_calSpVec->Dphi<(3.*PI/2.)&&vecX>0) vecX*=-1;
      MinDIns(vecL);
      MinDIns(vecX);
      MinDIns(vecY);
      MinDIns(vecZ);
      DBM3DVec::SetUnitVec();
      delete tmp_cal3DVec;
      delete tmp_calSpVec;
    }
    void SetPlane(double dX=0,double dY=0,double dZ=1,double pX= 0,double pY= 0,double pZ= 0){
      DBM3DVec::SetVector(dX,dY,dZ);
      DBMPlane::SetPosition(pX,pY,pZ);
    }
    void ReSet(){
      SetPlane();
    }

    double GetPlane(int index){
      return *plane[index]; 
    }
    void GetPlane(double &Ux,double &Uy,double &Uz,double &VP){
      Ux= uvecX;  Uy= uvecY;  Uz= uvecZ; VP= vecP;
    }
    void Show(bool checkMode=false){
      DBMshow::SSOIPrint();
      DBMshow::OTNPrint("DBMPlane");
      DBMName::Show();
      backShow(checkMode);
      DBMshow::OISEPrint();
    }
  private:
    void SetImformation(double dX=0,double dY=0,double dZ=1,double pX=0,double pY=0,double pZ=1){
      SetPlane(dX,dY,dZ,pX,pY,pZ);
      ImforWrite();
    }
    void ImforWrite(){
      plane[0]=&uvecX;  plane[1]=&uvecY;  plane[2]=&uvecZ;  plane[3]=&vecP;
      cmp[0]=&posX;  cmp[1]=&posY;  cmp[2]=&posZ;
    }
  protected:
    void backShow(bool checkMode=false){
      if(checkMode){
        DBM3DVec::Show();
        DBMpos::Show();
        cout<<Form("plane[0]%9.2e  plane[1]%9.2e  plane[2]%9.2e  plane[3]%9.2e\n",*plane[0],*plane[1],*plane[2],*plane[3]);
      }
      cout<<Form("(%9.2e)x +(%9.2e)y +(%9.2e)z =%9.2e",uvecX,uvecY,uvecZ,vecP)<<endl;
    }
  };



  class DBM3DObj: public DBMName, public DBMdim, public DBMpos, public DBM3Drot,public DBMshow
  {
  public: 
    double *pos[3];
    double *dim[3];
    double *rot[3];
    
    DBM3DObj(const char names[]="default", double l=1,double w=1,double h=1,double X=0,double Y=0,double Z=0,double A=0,double B=0,double G=0):DBMName(names),DBMdim(l,w,h),DBMpos(X,Y,Z),DBM3Drot(A,B,G){
      SetName(names);
      ImforWrite();
    }
    DBM3DObj(const DBM3DObj *Object,const char names[]="default"){ 
      SetName(names);
      SetImformation(Object->leng,Object->widt,Object->heig,Object->posX,Object->posY,Object->posZ,Object->theX,Object->theY,Object->theZ);
    }
    virtual ~DBM3DObj(){
    }
    
    void Show(bool checkMode){
      if(checkMode){
        DBMshow::SSOIPrint();
        DBMshow::OTNPrint("DBM3DObj");
        backShow(checkMode);
        DBMshow::OISEPrint();
      }
    }
    void ReSet(){
      SetImformation();
    }
  private:
    
  protected:
    void backShow(bool checkMode){
      DBMName::Show();
      DBMdim::Show();
      DBMpos::Show();
      DBM3Drot::Show();
      if(checkMode){
        cout<<Form("pos[0]%11.2e  pos[1]%11.2e  pos[2]%11.2e\n",*pos[0],*pos[1],*pos[2]);
        cout<<Form("dim[0]%11.2e  dim[1]%11.2e  dim[2]%11.2e\n",*dim[0],*dim[1],*dim[2]);
        cout<<Form("rot[0]%11.2e  rot[1]%11.2e  rot[2]%11.2e\n",*rot[0],*rot[1],*rot[2]);
      }
    }
    void SetImformation(double l=1,double w=1,double h=1,double X=0,double Y=0,double Z=0,double A=0,double B=0,double G=0){
      DBMdim::SetDimension(l,w,h);
      DBMpos::SetPosition(X,Y,Z);
      DBM3Drot::SetRotation(A,B,G);
      ImforWrite();
    }
    void ImforWrite(){
      pos[0]=&posX;  pos[1]=&posY;  pos[2]=&posZ;
      dim[0]=&leng;  dim[1]=&widt;  dim[2]=&heig;
      rot[0]=&theX;  rot[1]=&theY;  rot[2]=&theZ;
    }
  };

  class DBMBox: public DBM3DObj
  {
  public: 
    DBMPlane *PF[6];
    DBMBox(const char names[]="default", double l=1,double w=1,double h=1,double X=0,double Y=0,double Z=0,double A=0,double B=0,double G=0):DBM3DObj(names,l,w,h,X,Y,Z,A,B,G){
      InitializePF();
      Update();
    }
    DBMBox(const DBMBox *Object,const char names[]="default"):DBM3DObj(Object,names){
      InitializePF();
      Update();
    }
    virtual ~DBMBox(){
      for(int i = 0; i < 6; ++i) {
        delete PF[i];
        // delete [] PP[i];
      }
    }
    
    void Update(){
      PlaneVectorDefault();
      // TempFunction();
      for(int ip=0;ip<6;ip++){
        PF[ip]->DBMPlane::SetPlaneRot(theX,theY,theZ);
        PF[ip]->DBMPlane::SetPosition(*(pos[0]),*(pos[1]),*(pos[2]));
      }
    }
    void ReSet(){
      DBM3DObj::SetImformation();
    }
    DBMPlane GetPlane(int index){
      cout<<"HAHA BUG//@@"<<endl;
      return PF[index];
    }
    void Show(bool checkMode=false){
      DBMshow::SSOIPrint();
      DBMshow::OTNPrint("DBMBox");
      backShow(checkMode);
      DBMshow::OISEPrint();
    }
  private:
    // double **PP;
    void InitializePF(){
      for(int ip=0;ip<6;ip++) PF[ip] = new DBMPlane();
    }
    void PlaneVectorDefault(){
      const char PFName[6][6]={"Plef","Prig","Pfro","Pbac","Pbot","Ptop"};
      double tmp[3];
      for(int i=0;i<6;i++){
        for(int id=0;id<3;id++)
          tmp[id] = -cos(i*PI)*(*dim[id])/2*(i/2==id);
          *PF[i]= DBMPlane(Form("%.6s_%.4s",name,PFName[i]),tmp[0],tmp[1],tmp[2]);
      }
    }
  protected:
    void backShow(bool checkMode=false){
      DBM3DObj::backShow(checkMode);
      cout<<"Box Planes:"<<endl;
      for(int i=0;i<6;i++){
        cout<<"  "<<PF[i]->GetName()<<": ";
        PF[i]->DBMPlane::backShow();
      }
    }
  };
  
  
  
  
  DBMPoint *IntSecPlaLine(DBMPlane *PF,DBMLine *LF,const char names[]="defaultlineS"){
    DBMPoint *Rs= new DBMPoint(names,0,0,0,0);
    double  t,vpt=0,dis=0;
    for(int i=0;i<3;i++){
      dis += *(PF->plane[i]) * *(LF->pos[i]);
      vpt += *(LF->dir3D[i]) * *(PF->plane[i]);
    }
    dis = dis - *(PF->plane[3]);
    MinDIns(dis);  MinDIns(vpt);

    // 1/首先判断直线是否与平面平行
    if (vpt == 0){
      for(int i=0;i<3;i++) *(Rs->point[i]) = *(LF->pos[i]);
      if(dis=0)       *(Rs->point[3]) = 0;//outside plane
      else if(dis<0)  *(Rs->point[3]) = -1;//outside plane
      else           *(Rs->point[3]) = 1;//outside plane    
    }else{
      t = -dis/vpt;

      for(int i=0;i<3;i++){
        *(Rs->point[i]) = *(LF->pos[i]) + *(LF->dir3D[i]) * t;
        MinDIns(*(Rs->point[i]));
      }
      *(Rs->point[3]) = 0;//section is on plane
    }
    return Rs;
  }
  
  bool distanceP6P(DBMPoint *P6P[6],DBMBox *BF,DBMPoint *Ps0,DBMPoint *Ps1,char option='q'){
    short tmpIndex[6]={}, iI=0;
    for(short i=0;i<6;i++){
      if((P6P[i]->OPT)==0){
        tmpIndex[iI] = i;
        // cout<<"SP@(x,y,z,B):  "<<P6P[i][0]<<","<<P6P[i][1]<<","<<P6P[i][2]<<","<<P6P[i][3]<<endl;
        iI++;
      }//else cout<<(P6P[i][3])<<endl;
    }
    if(iI==0&&option!='q'){
      cout<<"No Section"<<endl;
      return false;
      // throw;
    }
    // cout<<iI<<endl;
    
    *Ps0 = DBMPoint(P6P[tmpIndex[0]],"SP0");
    short PSNum=1;
    // P6P[tmpIndex[0]]->Show();
    for(short i=1;i<iI;i++){
      // P6P[tmpIndex[i]]->Show();
      // cout <<P6P[tmpIndex[i]]->ComparePoint(Ps0)<<"\t"<<P6P[tmpIndex[i]]->ComparePoint(Ps1)<<endl;
      if(PSNum>1){
        if((P6P[tmpIndex[i]]->ComparePoint(Ps0)==false)
         &&(P6P[tmpIndex[i]]->ComparePoint(Ps1)==false)){
          PSNum++;
        }
      }else if(PSNum==1&&P6P[tmpIndex[i]]->ComparePoint(Ps0)==false){
        *Ps1 = DBMPoint(P6P[tmpIndex[i]],"SP1");
        // Ps1->SetImformation("SP0",P6P[tmpIndex[i]]->posX,P6P[tmpIndex[i]]->posY,P6P[tmpIndex[i]]->posZ,P6P[tmpIndex[i]]->OPT);
        PSNum++;
      }
    }
    // cout <<PSNum<<"\tPSNum"<<endl;
    if(PSNum>2) {
      return false;
      if(option!='q'){
        cout<<"\n-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v\n";
        cout<<"Too much intersection point:   "<<PSNum<<"   Points\n";
          for(short i=0;i<6;i++){
            cout<<"P6P(x,y,z,A):  ("
               <<*(P6P[i]->point[0])<<","<<*(P6P[i]->point[1])<<","
               <<*(P6P[i]->point[2])<<","<<*(P6P[i]->point[3])<<")\n";
            cout<<"boxFunctions:   "
               <<*(BF->PF[i]->plane[0])<<"x+"<<*(BF->PF[i]->plane[1])<<"y+"
               <<*(BF->PF[i]->plane[2])<<"z="<<*(BF->PF[i]->plane[3])<<"\n";
          }
        cout<<"-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^\n";
        throw;
      }
    }else if(PSNum<2) {
      return false;
      if(option!='q'){
        cout<<"\n-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v-v\n";
        cout<<"Too less intersection point:   "<<PSNum<<"   Points\n";
          for(short i=0;i<6;i++){
            cout<<"P6P(x,y,z,A):  ("
               <<*(P6P[i]->point[0])<<","<<*(P6P[i]->point[1])<<","
               <<*(P6P[i]->point[2])<<","<<*(P6P[i]->point[3])<<")\n";
            cout<<"boxFunctions:   "
               <<*(BF->PF[i]->plane[0])<<"x+"<<*(BF->PF[i]->plane[1])<<"y+"
               <<*(BF->PF[i]->plane[2])<<"z="<<*(BF->PF[i]->plane[3])<<"\n";
          }
        cout<<"-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^\n";
      }
      // throw;
    }
    // for(short i=0;i<6;i++)
      // P6P[i]->Show();
    // BF->Show();
    // Ps0->Show();
    // Ps1->Show();
    return true;
  }
  
  DBMLineS *IntSecBoxLine(DBMBox *BF,DBMLine *LF,const char names[]="defaultlineS",char option='q'){
    char nam[6][3]={"p0","p1","p2","p3","p4","p5"};
    DBMPoint *IntSecP[6];
    for(int ip=0;ip<6;ip++) IntSecP[ip] = IntSecPlaLine(BF->PF[ip],LF,nam[ip]);
    // LF->Show();
    // BF->Show();
    for(short ip=0;ip<6;ip++) {
      short InOrNotPP[6] = {};
      // IntSecP[ip]->Show();
      // IntSecP[ip]->Show();
      if(*(IntSecP[ip]->point[3])==1) continue;//pro select at calculate section point
      // IntSecP[ip]->Show();
      for(short ip2=0;ip2<6;ip2++) {
        double value=0;
        for(short i=0;i<3;i++){
          value += *(IntSecP[ip]->point[i])*(*BF->PF[ip2]->plane[i]);
        }
        value-=(*BF->PF[ip2]->plane[3]);
        MinDIns(value);
        // cout<<"value\t"<<value<<"\t";
        if(value==0)      InOrNotPP[ip2]= 0;
        else if(value<0)  InOrNotPP[ip2]=-1;
        else if(value>0)  InOrNotPP[ip2]=+1;
        // cout<<InOrNotPP[ip2]<<"\t";
        //return value;
        // cout<<InOrNotPP[ip2]<<endl;
        if(InOrNotPP[ip2]>0){
          // cout<<InOrNotPP[ip2]<<endl;
          // IntSecP[ip]->Show();
          *(IntSecP[ip]->point[3])=1;
          break;
        }
      }
      // cout<<endl;
      if     (*(IntSecP[ip]->point[3])==1) continue;
      else if(InOrNotPP[0]<0&&InOrNotPP[1]<0&&InOrNotPP[2]<0
            &&InOrNotPP[3]<0&&InOrNotPP[4]<0&&InOrNotPP[5]<0)
            *(IntSecP[ip]->point[3]) = -1;
      else{
        *(IntSecP[ip]->point[3]) = 0;
        //returnValue++;
      }
      //Point[i][3]=returnValue;
      //return returnValue;
    }
    
    DBMPoint *P0 = new DBMPoint(),*P1= new DBMPoint();
    DBMLineS *Ret = new DBMLineS();
     
    if(distanceP6P(IntSecP,BF,P0,P1,option)){
        // cout<<"P0->GetFar()>P1->GetFar()"<<P0->GetFar()<<"   "<<P1->GetFar()<<endl;
      if(P0->GetFar()>P1->GetFar()){
        std::swap(P0, P1);
        P1->SetName("P0");
        P0->SetName("P1");
      }
      // cout<<"P0->GetFar()>P1->GetFar()"<<P0->GetFar()<<"   "<<P1->GetFar()<<endl;
      // cout<<"      "<<endl;
      // for(short ip=0;ip<6;ip++) IntSecP[ip]->Show();
      
      *Ret = DBMLineS(P0,P1,names);
      if(Ret->GetLength()>(BF->size)&&strcmp(Ret->name,"LST")!=0){
        // cout<<endl<<Ret->GetLength()<<endl;
        // for(short ip=0;ip<6;ip++) IntSecP[ip]->Show();
        // P0->Show();
        // P1->Show();
        // BF->Show();
        // LF->Show();
        // Ret->Show();
        // throw;
        Ret->SetName("Null");
      }
    }else{
      Ret->SetName("Null");
    }
    delete P0;
    delete P1;
    delete IntSecP[0];
    delete IntSecP[1];
    delete IntSecP[2];
    delete IntSecP[3];
    delete IntSecP[4];
    delete IntSecP[5];
    return Ret;
  }


}













/*


  class DBMSphere : public DBM3DObj
  {
  public: 

    DBMSphere(const char names[]="default", double l=1,double w=1,double h=1,double X=0,double Y=0,double Z=0,double A=0,double B=0,double G=0):DBM3DObj(names,l,w,h,X,Y,Z,A,B,G){
      Update();
    }
    DBMSphere(const DBMSphere *Object,const char names[]="default"):DBM3DObj(Object,names){ 
      Update();
    }
    virtual ~DBMSphere(){}
    double PSF[7];
    
    void Update(){
      PSF[0] = *pos[0];
      PSF[1] = *pos[1];
      PSF[2] = *pos[2];
      PSF[3] = *dim[0];
      PSF[4] = *dim[1];
      PSF[5] = *dim[2];
      PSF[6] = 1;
      //@@ Rotate
    }
    void ReSet(){
      DBM3DObj::SetImformation();
    }
  private:
    void Show(bool checkMode=false){
      DBMshow::SSOIPrint();
      DBMshow::OTNPrint("DBMSphere");
      backShow(checkMode);
      DBMshow::OISEPrint();
    }
    void PlaneFuncPrint(){
      cout<<"                       "<<
      "x-"<<Form("%9.2e",PSF[0])<<"      "<<
      "y-"<<Form("%9.2e",PSF[1])<<"      "<<
      "z-"<<Form("%9.2e",PSF[2])<<endl;
      cout<<"PSF(Ra,Rb,Rc,x,y,z,t):"<<
      "(-----------)^2 +(-----------)^2 +(-----------)^2 ="<<PSF[6]<<endl;
      cout<<"                        "<<
      Form("%9.2e",PSF[3])<<"        "<<
      Form("%9.2e",PSF[4])<<"        "<<
      Form("%9.2e",PSF[5])<<endl;
    }
    
  protected:
    void backShow(bool checkMode=false){
      DBM3DObj::backShow(checkMode);
      if(checkMode) PlaneFuncPrint();
    }
  };


*/