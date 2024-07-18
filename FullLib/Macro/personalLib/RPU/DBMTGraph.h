#include "TGraph.h"
TGraph* ConvertTH1FToTGraph(TH1F* hist) {
    // Get number of bins in the histogram
    int nBins = hist->GetNbinsX();

    // Create arrays to hold x and y values
    double* x = new double[nBins];
    double* y = new double[nBins];

    // Extract bin contents and corresponding bin centers
    for (int i = 0; i < nBins; ++i) {
        x[i] = hist->GetBinCenter(i+1); // Bin center
        y[i] = hist->GetBinContent(i+1); // Bin content
    }

    // Create TGraph
    TGraph* graph = new TGraph(nBins, x, y);
    graph->SetTitle(hist->GetTitle());
    graph->SetName(hist->GetName());

    // Optionally draw the graph
    
    delete [] x;
    delete [] y;
    return graph;
}