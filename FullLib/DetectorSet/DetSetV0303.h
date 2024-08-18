
  char detVer[10] = {"V3.05"};  //detector version
  //number of boards, nuber of channel per board, number of board layers
  const int    NumBD = 16, NumCh = 16, NumLY = 4;
  //number of channel on x-axis per board, ... on y-axis ..., , ... on z-axis ..., 
  const int    NumnX =  4, NumnY =  4, NumnZ = 1;
  //number of boards on x-axis per layer, ... on y-axis ..., , ... on z-axis ..., 
  const int    NumBX[NumLY] =  {2,2,2,2};
  const int    NumBY[NumLY] =  {2,2,2,2};
  const int    NumBZ[NumLY] =  {1,1,1,1};
  const int    RiX[2] = {-7,7}, RiY[2] = {-7,7}, RiZ[2] = {0,3};
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
     1, 2, 3, 4,
     5, 6, 7, 8,
     9,10,11,12,
    13,14,15,16
  };
  //MTB ID of a board at position index(ix,iy,iz): BD[ix+NumBY*iy+NumBX*NumBY*iz]
  const int    BDLay[NumBD]= {
    0,0,0,0,
    1,1,1,1,
    2,2,2,2,
    3,3,3,3
  };
  //pwidth scale factor of MTB board because the Magnification of DAQ at index x: BDPwWei[x]
  const int    BDPwWei[NumBD] = {
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1
  };
  const int    DiriB_z[NumBD]={
    1,0,0,1,
    1,0,0,1,
    1,0,0,1,
    1,0,0,1
  };
  int cIDBack[2][NumCh]={
    {
       0, 1, 2, 3,
       4, 5, 6, 7,
       8, 9,10,11,
      12,13,14,15
    },{
       3, 2, 1, 0,
       7, 6, 5, 4,
      11,10, 9, 8,
      15,14,13,12
    },
  };
  int LayFirst[NumLY]={0,4,8,12};
  