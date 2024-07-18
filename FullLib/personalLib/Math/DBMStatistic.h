#include <typeinfo>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

inline double VecTot( const vector<double> vData ){
  double ret = 0;
  for( Long64_t i=0 ; i<Long64_t(vData.size()) ; i++)
    ret+=vData[i];
  return ret;
}
inline double VecAvg( const vector<double> vData ){
  return VecTot(vData)/double(vData.size());
}

inline double VecErr( const vector<double> vData ){
  double mean = VecAvg(vData);
  double ret = 0;
  for( Long64_t i=0 ; i<Long64_t(vData.size()) ; i++)
    ret+=pow(vData[i]-mean,2);
  return sqrt(ret/double(vData.size()));
}
double VecMax( const vector<double> vData){
  return *max_element(vData.begin(), vData.end());
}
double VecMin( const vector<double> vData){
  return *min_element(vData.begin(), vData.end());
}