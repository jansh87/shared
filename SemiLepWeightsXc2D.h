// ///////////////////////////////////////////////////////////
// Weigthts for B -> D(*) l nu and Bs -> Ds(*) l nu decays
// to correct the Belle generic MC (latest version).
// Using HFAG 2013 form factors and the HQET2 EvtGen model.
// Detailed documentation: BN 1335
//
// Author: Christian Oswald, Uni Bonn, 2013-2014.
// Version: 1.0
// ////////////////////////////////////////////////////////////


#include "TH2F.h"
#include <map>

#ifndef SEMILEPWEIGHTSXC2D_H
#define SEMILEPWEIGHTSXC2D_H
class SemiLepWeightsXc2D {
    private:
    TH2F*** hEntries;
    float lookup(int lclass, int iBinQ2, int iBinLepMom, int iType);
    float lookup(int lclass, float q2_t, float lep_ps_t, int iType);
    std::map<int,int> lclass2index;
    std::map<int,int> index2lclass;
    int nVarBins;
    int iError;
    int nlclass; // number of implemented lclass (4)
    const float* fTables[5]; // pointer to lclass tables (is set in the constructer)
    int nColumns[5]; // number of columns for each lclass table
    int nBinsLepMom[5]; // number p_l bins for each lclass table
    int nBinsQ2[5]; // number of q2 bins for each lclass table
    float fQ2Min[5]; // minimum q2 value for each lclass table
    float fQ2Max[5]; // maximum q2 value for each lclass table
    float fPlepMin[5]; // minimum p_l value for each lclass table
    float fPlepMax[5]; // maximum p_l value for each lclass table
    int iPosWeight[5]; // column where the weight is stored in each lclass table
    int iPosErrStat[5]; // column where the statistic uncertainty is stored in each lclass table
    int iPosErrSyst[5]; // column where the systematic uncertainty is stored in each lclass table
    void init(int nVarBins, const char* strVarName);
    public:
    SemiLepWeightsXc2D();
    SemiLepWeightsXc2D(int nVarBins, const char* strVarName);
    ~SemiLepWeightsXc2D();
    static const float f2DWeights21[];
    static const float f2DWeights22[];
    static const float f2DWeights23[];
    static const float f2DWeights24[];
    static const float f2DWeights25[];
    float weight(int lclass, float q2_t, float lep_ps_t, int iVarBin=0, int iNoError = 0);
    float errStat(int lclass, int iBinQ2, int iBinLepMom);
    float errSyst(int lclass, int iBinQ2, int iBinLepMom);
    float calcBinError(int iVarBin);
    float calcRelBinError(int iVarBin);
    float calcBinError(int iVarBin, bool isSyst);
    void setError(int iErr){iError = iErr;} // 0 = weigth 1,2 =  weight \pm rel Error
    void reset();
};

#endif //SEMILEPWEIGHTSXC2D_H
