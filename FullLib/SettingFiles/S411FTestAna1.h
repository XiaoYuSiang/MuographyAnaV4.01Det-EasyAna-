#include <string>
/*  Choose a version of detector*/
string DetectorGeoSet = "V0401";
// string DetectorGeoSet = "V0401";
/*  Path of Macros!!!( *.C or *.h ) */
string DirAnaPath    = "/data4/YuSiang/S4Tests/At11FV3_RunTest/AnaTest1/";
/*  Path of All type Dir in root path  */
string DirMacros     = DirAnaPath+"MacroTmp/";
/*  Path of Raw Datas (*_Mu.txt) */
string DirRawData    = 
  "/data4/YuSiang/S4Tests/At11FV3_RunTest/RawMu/";
string DirHKData     =
  "/data4/YuSiang/S4Tests/At11FV3_RunTest/RawHK/";
string DirUDPData    =
  "/data4/YuSiang/S4Tests/At11FV3_RunTest/UDP/";
string DirRawRoot    = 
  "/data4/YuSiang/S4Tests/At11FV3_RunTest/rootfile/";
/*  Root path of Save Datas  */
string DirOperate    = DirAnaPath+"OperateResule/";
string DirResult     = DirAnaPath+"Result/";

string name_Raw_txt  = "*Run*_*Mu.txt";
string name_Raw_root = "*Run*_*Mu.root";
