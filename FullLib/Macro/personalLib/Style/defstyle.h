#include "TStyle.h"
#include "TPad.h"
#include "TColor.h"

void defstyle() {
  
  
// For the canvas:
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(500); //Height of canvas
  gStyle->SetCanvasDefW(700); //Width of canvas
  gStyle->SetCanvasDefX(10);   //POsition on screen
  gStyle->SetCanvasDefY(10);

// For the Pad:
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(2);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);

// For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(1001);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);

// For the histo:
  //gStyle->SetHistFillColor(0);
  //gStyle->SetHistFillStyle(1001);
  gStyle->SetHistLineColor(602);
  gStyle->SetHistLineStyle(1);
  gStyle->SetHistLineWidth(1);
  //gStyle->SetLegoInnerR(0.5);
  //gStyle->SetNumberContours(20);

  gStyle->SetEndErrorSize(2);
  //gStyle->SetErrorMarker(20);
  gStyle->SetErrorX(0.5);
  
  gStyle->SetMarkerStyle(1);
  
//For the fit/function:
  gStyle->SetOptFit(0);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(2);

//For the date:
  gStyle->SetOptDate(0);
  //gStyle->SetDateX(0.1);
  //gStyle->SetDateY(0.1);

// For the statistics box:
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(1111); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(0);
  gStyle->SetStatFont(42);
  gStyle->SetStatFontSize(0);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatH(0.16);
  gStyle->SetStatW(0.2);
  //gStyle->SetStatStyle(1001);
  //gStyle->SetStatX(0.98);
  //gStyle->SetStatY(0.935);

// Margins:
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadRightMargin(0.1);

// For the Global title:

  gStyle->SetOptTitle(1);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleFontSize(0.05);
 
  //gStyle->SetTitleH(0);
  //gStyle->SetTitleW(0);
  //gStyle->SetTitleX(0.5);
  //gStyle->SetTitleY(0.995);
  //gStyle->SetTitleStyle(0);
  //gStyle->SetTitleBorderSize(0);

// For the axis titles:

  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.035, "XYZ");
  
  gStyle->SetTitleXOffset(1);
  gStyle->SetTitleYOffset(1);
  
// For the axis labels:

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(1);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");

  gStyle->SetPadTickX(0);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(0);

// Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);

// For color palette
  gStyle->SetPalette(55);//kRainBow

// Postscript options:
  gStyle->SetPaperSize(20.,20.);
  // gStyle->SetLineScalePS(3);
  // gStyle->SetHeaderPS("");
  // gStyle->SetTitlePS("");

  // gStyle->SetBarOffset(0);
  // gStyle->SetBarWidth(1);
  // gStyle->SetPaintTextFormat("g");
  // gStyle->SetHistMinimumZero(0);

  gStyle->cd();
  
}