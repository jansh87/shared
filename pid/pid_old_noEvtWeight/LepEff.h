#ifndef LEPEFF_H
#define LEPEFF_H
#include "TAxis.h"
#include "TH2F.h"
class LepEff {
    private:
    TH2F*** hEntries;
    float lookup(int lep_gen, int exp_no, int iBinTheta, int iBinLepMom, int iType);
    float lookup(int lep_gen, int exp_no, float theta, float plep, int iType);
    int nVarBins;
    int iError;
    TAxis* axis_theta[2];
    TAxis* axis_plep[2];
    float fPidCut;
    int iPidCut;
    int iPidCutOffset;
    int iPosWeight; // column where the weight is stored in each lep_gen table
    int iPosErrStat; // column where the statistic uncertainty is stored in each lep_gen table
    int iPosErrSyst1; // column where the systematic uncertainty is stored in each lep_gen table
    int iPosErrSyst2; // column where the systematic uncertainty is stored in each lep_gen table
    void init(int nVarBins, const char* strVarName, float fPid, int lep_gen);
    public:
    LepEff(float fPid, int lep_gen);
    LepEff(int nVarBins, const char* strVarName, float fPid, int lep_gen);
    ~LepEff();
    static const int nColumns;
    static const int nEffMomBins;
    static const int nEffThetaBins;
    static const float fElecEff[];
    static const float fElecEffSVD1[];
    static const float fMuonEffSVD1[];
    static const float fMuonEff31[];
    static const float fMuonEff41[];
    static const float fMuonEff51[];
    static const int exp_range[];
    float weight(int lep_gen, int exp_no, float theta, float plep, int iVarBin=0, int iNoError = 0);
    float errStat(int lep_gen, int exp_no, int iBinTheta, int iBinLepMom);
    float errSyst1(int lep_gen, int exp_no, int iBinTheta, int iBinLepMom);
    float errSyst2(int lep_gen, int exp_no, int iBinTheta, int iBinLepMom);
    float calcBinError(int iVarBin);
    float calcRelBinError(int iVarBin);
    void setError(int iErr){iError = iErr;} // 0 = weigth 1,2 =  weight \pm rel Error
    void reset();
    void DumpErrorPopulation(int iVarBin, int lep);
};

#endif // LEPEFF_H
