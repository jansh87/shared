#ifndef LEPFAKE_H
#define LEPFAKE_H
#include "TH2F.h"
#include "../EffCorrClass.h"
//
//
// numberin scheme: e = 0, mu = 1, pi = 2, k = 3
class LepFake:public EffCorrClass {
    private:
    TH2F*** hEntries;
    float lookup(int lep_gen, int true_lep_gen, int iBinTheta, int iBinLepMom, int iType);
    float lookup(int lep_gen, int true_lep_gen, float theta, float plep, int iType);
    int nVarBins;
    int iError;
    TAxis* axis_theta[2];
    TAxis* axis_plep[2];
    int iPosWeight; // column where the weight is stored
    int iPosErr; // column where the uncertainty is stored
    void init(int nVarBins, const char* strVarName);
    public:
    LepFake();
    LepFake(int nVarBins, const char* strVarName);
    ~LepFake();
    static const int nColumns;
    static const int nMomBins;
    static const int nThetaBins;
    static const float fPi2ElecFake[];
    static const float fPi2MuonFake[];
    static const float fK2ElecFake[];
    static const float fK2MuonFake[];
    float weight(int lep_gen, int true_lep_gen, float theta, float plep, int iVarBin=0, int iNoError = 0, float evntWeight =1.);
    float weightError(int lep_gen, int true_lep_gen, float theta, float plep);
    virtual float getRelError(uint bin);
    float err(int lep_gen, int true_lep_gen, int iBinTheta, int iBinLepMom);
    float calcBinError(int iVarBin);
    float calcRelBinError(int iVarBin);
    void setError(int iErr){iError = iErr;} // 0 = weight, 1,2, = weight \pm rel error
    void reset();
};

#endif // LEPFAKE_H
