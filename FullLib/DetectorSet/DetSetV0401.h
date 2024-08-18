
  char detVer[10] = {"V4.01"};  //detector version
  //number of boards, nuber of channel per board, number of board layers
  const int    NumBD = 26, NumCh = 16, NumLY = 4;
  //number of channel on x-axis per board, ... on y-axis ..., , ... on z-axis ..., 
  const int    NumnX =  4, NumnY =  4, NumnZ = 1;
  //number of boards on x-axis per layer, ... on y-axis ..., , ... on z-axis ..., 
  const int    NumBX[NumLY] =  {3,2,2,3};
  const int    NumBY[NumLY] =  {3,2,2,3};
  const int    NumBZ[NumLY] =  {1,1,1,1};
  const int    RiX[2] = {-11,11}, RiY[2] = {-11,11}, RiZ[2] = {0,3};
  const int    DRiX = 2,DRiY = 2,DRiZ = 1;
  const int    MotherBoard = 1;
  //Size of Scintillator on X=bx, Y=by, Z=bz dim. , unit: mm
  const double bx  = 50., by  = 50., bz  = 12. ;
  //gap size MTBs on X=bx, Y=by, Z=bz dim. , unit: mm
  const double gbx = 0  , gby = 0. , gbz = 500.;
  //half size of Scintillator on XYZ dim
  const double bx_2 = bx/2., by_2 = by/2., bz_2 = bz/2.;
  const int    BD[NumBD]   = 
  {
    1,2,3,4,5,6,7,8,9,
    10,11,12,13,
    14,15,16,17,
    18,19,20,21,22,23,24,25,26
  };
  //MTB ID of a board at position index(ix,iy,iz): BD[ix+NumBY*iy+NumBX*NumBY*iz]
  const int    BDLay[NumBD]= {
    0,0,0,0,0,0,0,0,0,
    1,1,1,1,
    2,2,2,2,
    3,3,3,3,3,3,3,3,3
  };
  //pwidth scale factor of MTB board because the Magnification of DAQ at index x: BDPwWei[x]
  const int    BDPwWei[NumBD] = {
    1,1,1,1,1,1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,1,1,1,1,1
  };
  const int    DiriB_z[NumBD]={
    0,1,0,1,0,1,0,1,0,
    1,0,0,1,
    1,0,0,1,
    0,1,0,1,0,1,0,1,0
  };
  int cIDBack[2][NumCh]={
    {
      15,14,13,12,
      11,10, 9, 8,
       7, 6, 5, 4,
       3, 2, 1, 0
    },{
      12,13,14,15,
       8, 9,10,11,
       4, 5, 6, 7,
       0, 1, 2, 3
    },
  };
  int LayFirst[NumLY]={0,9,13,17};