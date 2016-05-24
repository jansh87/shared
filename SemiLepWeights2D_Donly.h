#include "TH2F.h"
#include <map>
#include <iostream>

#ifndef SEMILEPWEIGHTS2D_H
#define SEMILEPWEIGHTS2D_H
class SemiLepWeights2D {
    private:
    TH2F*** hEntries;
    float lookupQ2(int lclass, int iBinQ2, int iBinLepMom, int iType);
    float lookupW(int lclass, int iBinW, int iBinCosTh, int iType);
    float lookup(int lclass, float w_t, float CosTh_t, float q2_t, float lep_ps_t,int iType);
    std::map<int,int> lclass2index;
    std::map<int,int> index2lclass;
    int nVarBins;
    int nlclass; // number of implemented lclass (6)
    const float* fTables[6]; // pointer to lclass tables (is set in the constructer)
    int nColumns[6]; // number of columns for each lclass table
    int nBinsLepMom[6]; // number p_l bins for each lclass table
    float fLepMomMin[6];
    float fLepMomMax[6];
    int nBinsQ2[6]; // number of q2 bins for each lclass table
    float fQ2Min[6]; // minimum q2 value for each lclass table
    float fQ2Max[6]; // maximum q2 value for each lclass table
    //in case of D** mesons, q2 = w and LepMom = cosTheta
    int iPosWeight[6]; // column where the weight is stored in each lclass table
    int iPosErrStat[6]; // column where the statistic uncertainty is stored in each lclass table
    int iPosErrSyst[6]; // column where the systematic uncertainty is stored in each lclass table
    int iPosShape[6][3]; // column where the max change in shape is stored (0: normal shape; 1,2: deviation)
    void init(int nVarBins, const char* strVarName);

    float Q2(float w, int idx);
    float LepMom(float CosTh, float w, int idx);
    
    static const float fMesonMasses[];
    static const float fmB;

    public:
    SemiLepWeights2D();
    SemiLepWeights2D(int nVarBins, const char* strVarName);
    ~SemiLepWeights2D();
    static const float f2DWeightsCoarse1[];
    static const float f2DWeightsCoarse2[];
    static const float f2DWeightsFine1[];
    static const float f2DWeightsFine2[];
    static const float fWeights3[];
    static const float fWeights4[];
    static const float fWeights5[];
    static const float fWeights6[];
    float weight(int lclass, float w_t, float CosTh_t, int iVarBin=0);
    float weight(int lclass, float w_t, float CosTh_t, float q2_t, float LepMom_t, int iVarBin=0);
    float getRelError(int iVarBin);
    float errStat(int lclass, int iBinQ2, int iBinLepMom);
    float errSyst(int lclass, int iBinQ2, int iBinLepMom);
    float calcBinError(int iVarBin);
    void reset();
    void setShape(int lclass, int iShape);
    void resetShapes( void );
};

#endif //SEMILEPWEIGHTS2D_H
