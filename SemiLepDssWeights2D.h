#include "TH2F.h"
#include <map>
#include <iostream>

//
//	Weights for B->D**lnu decays from "LLSW"-model (arXiv:9705467) prediction. 
//	To be applied on B->D**lnu decays generated with ISGW2 model (generic Belle MC)
// 	For details: see Belle Note #1335
//


#ifndef SEMILEPDSSWEIGHTS2D_H
#define SEMILEPDSSWEIGHTS2D_H
class SemiLepDssWeights2D {
    private:
    TH2F*** hEntries;
    float lookup(int idx, int iBinW, int iBinCosTh, int iType);
    float lookup(int idx, float w_t, float CosTh_t, int iType);
    int nVarBins;
    int nMesons; // number of implemented lclass (6)
    const float* fTables[4]; // pointer to lclass tables (is set in the constructer)
    int nColumns[4]; // number of columns for each lclass table
    int nBinsCosTh[4]; // number cos theta bins for each lclass table
    float fCosThMin[4];
    float fCosThMax[4];
    int nBinsW[4]; // number of w bins for each lclass table
    float fWMin[4]; // minimum w value for each lclass table
    float fWMax[4]; // maximum w value for each lclass table
    int iPosWeight[4]; // column where the weight is stored in each lclass table
    int iPosErrStat[4]; // column where the statistic uncertainty is stored in each lclass table
    int iPosErrSyst[4]; // column where the systematic uncertainty is stored in each lclass table
    int iPosShape[4][3]; // column where the max change in shape is stored (0: normal shape; 1,2: deviation)
    void init(int nVarBins, const char* strVarName);

    
    public:
    SemiLepDssWeights2D();
    SemiLepDssWeights2D(int nVarBins, const char* strVarName);
    ~SemiLepDssWeights2D();
    static const float fWeights0[];
    static const float fWeights1[];
    static const float fWeights2[];
    static const float fWeights3[];
    float weight(int idx, float w_t, float CosTh_t, int iVarBin=0);
    float errStat(int idx, int iBinW, int iBinCosTh);
    float errSyst(int idx, int iBinW, int iBinCosTh);
    float calcBinError(int iVarBin);
    void reset();
    void setShape(int idx, int iShape);
    void resetShapes( void );
};

#endif //SEMILEPDSSWEIGHTS2D_H
