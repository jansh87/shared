#ifndef KPIEFF_H
#define KPIEFF_H
#include "TAxis.h"
#include "TH2F.h"
class KPiEff {
    private:
    TH2F*** hEntries;
    float lookup(int isKaon, int iBinTheta, int iBinLepMom, int exp, int iType);
    float lookup(int isKaon, float theta, float plep, int exp, int iType);
    int nVarBins;
    TAxis* axis_theta[2];
    TAxis* axis_plep[2];
    static float* fKPiEffSVD1;
    static float* fKPiEffSVD2;
    int iPidCut;
    int iPidCutOffset;
    int iPosWeight; // column where the weight is stored
    int iPosErrStat; // column where the uncertainty is stored
    int iPosErrSyst; // column where the uncertainty is stored
    int iPosFlag; // column where the flag is stored (OK, no events, fit failed)
    void init(int nVarBins, const char* strVarName, float fPid, int isKaon);
    public:
    KPiEff(float fPid, int isKaon);
    KPiEff(int nVarBins, const char* strVarName, float fPid, int isKaon);
    ~KPiEff();
    static void Term();
    static const int nColumns;
    static const int nMomBins;
    static const int nThetaBins;
//    static const float fKaonEffSVD1[];
//    static const float fKaonPionFakeSVD1[];
//    static const float fPionEffSVD1[];
//    static const float fPionKaonFakeSVD1[];
//    static const float fKaonEff31[];
//    static const float fKaonPionFake31[];
//    static const float fPionEff31[];
//    static const float fPionKaonFake31[];
    float weight(int isKaon, float theta, float plep, int exp, int iVarBin=0);
    float errStat(int isKaon, int iBinTheta, int iBinLepMom, int exp);
    float errSyst(int isKaon, int iBinTheta, int iBinLepMom, int exp);
    float calcBinError(int iVarBin, int exp);
    void reset();
};

#endif // KPIEFF_H
