#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class ChSet {
public:
  int GCH;
  int IBD;
  int ICH;
  int IX;
  int IY;
  int IZ;
  int Dir;
  bool Alive;
  ChSet(){ Alive = 0;}
  ChSet(int gch, int ibd, int ich, int ix, int iy, int iz, int dir)
    : GCH(gch), IBD(ibd), ICH(ich), IX(ix), IY(iy), IZ(iz), Dir(dir) {
    Alive = 1;
  }
  virtual void Show(){
    std::cout << GCH << "\t" << IBD << "\t" << ICH << "\t"
      << IX << "\t" << IY << "\t" << IZ << "\t" << Dir << std::endl;
  }
};
    // LoadChTable(data,filename);

void LoadChTable(
  std::map<int, ChSet>& data,
  const std::string filename)
{
  int NullRet = system("pwd");
  // cout<<filename<<endl;
  std::ifstream file(filename);
  std::string line;
  
  // 跳過標題行
  std::getline(file, line);
  // cout<<line<<endl;
  // 讀取數據行
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    int gch, ibd, ich, ix, iy, iz, dir;

    iss >> gch >> ibd >> ich >> ix >> iy >> iz >> dir;
    data[gch] = ChSet(gch, ibd, ich, ix, iy, iz, dir);
  }
  
}

void LoadChTable(const std::string filename){
  std::map<int, ChSet> data;
  LoadChTable(data,filename);
  for(int idata = 0;idata<int(data.size());idata++){
    data[idata].Show();
  }
}
