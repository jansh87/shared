#include "LepFake.h"
#include "TMath.h"

#include<iostream>
void LepFake::init(int varBins, const char* strVar) {
    nVarBins = varBins;

    const double fMomBins[] = {0.0,  0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5,  3.0,  4.0};

    iError = 0;
    // Electrons
    axis_plep[0] = new TAxis(nMomBins, fMomBins);
    const double fThetaBinsElec[] = {0, 18, 25, 35,  40,  60,  125,  132,  151};
    axis_theta[0] = new TAxis(nThetaBins, fThetaBinsElec);

    // Muons
    axis_plep[1] = new TAxis(nMomBins, fMomBins);
    const double fThetaBinsMuon[] = {0, 17, 25, 37,  51,  117,  130,  145,  150};
    axis_theta[1] = new TAxis(nThetaBins, fThetaBinsMuon);

    iPosWeight = 4;
    iPosErr = 5;

    hEntries = new TH2F**[nVarBins];
    char text[200];
    for (int iVarBin=0; iVarBin<nVarBins; iVarBin++) {
        hEntries[iVarBin] = new TH2F*[4];
        for (int i=0; i<4; i++) {
            sprintf(text, "h_LepFakeEntries_%s_bin%03i_tableno%02i", strVar, iVarBin, i);
            hEntries[iVarBin][i] = new TH2F(text, text, nMomBins, fMomBins, nThetaBins, (i <= 1) ? fThetaBinsElec : fThetaBinsMuon);
        }
    }

}

LepFake::LepFake() {
    init(1, "default");
}

LepFake::LepFake(int varBins, const char* strVar) {
    init(varBins, strVar);
}

LepFake::~LepFake() {
    for (int iVarBin=0; iVarBin<nVarBins; iVarBin++) {
        for (int i=0; i<4; i++) {
            delete hEntries[iVarBin][i];
        }
        delete[] hEntries[iVarBin];
    }
    delete[] hEntries;
}

float LepFake::lookup(int lep_gen, int true_lep_gen, int iBinTheta, int iBinLepMom, int iType) {
    if (iType < 0 || iType >= nColumns) return -1;
    if (iBinTheta < 0 || iBinTheta>=nThetaBins) return -1;
    if (iBinLepMom < 0 || iBinLepMom >= nMomBins) return -1;
    int iPosition = iBinTheta*nColumns*nMomBins+iBinLepMom*nColumns+iType;
    if (lep_gen == 0 && true_lep_gen == 2) return fPi2ElecFake[iPosition];
    if (lep_gen == 0 && true_lep_gen == 3) return fK2ElecFake[iPosition];
    if (lep_gen == 1 && true_lep_gen == 2) return fPi2MuonFake[iPosition];
    if (lep_gen == 1 && true_lep_gen == 3) return fK2MuonFake[iPosition];
    return -1;
}


float LepFake::lookup(int lep_gen, int true_lep_gen, float theta, float plep, int iType) {
    if (lep_gen < 0 || lep_gen > 1) return -1;
    int iBinTheta = axis_theta[lep_gen]->FindBin(theta) - 1;
    int iBinLepMom = axis_plep[lep_gen]->FindBin(plep) - 1;
    float fResult = lookup(lep_gen, true_lep_gen, iBinTheta, iBinLepMom, iType);
    return fResult;
}

float LepFake::weight(int lep_gen, int true_lep_gen, float theta, float plep, int iVarBin, int iNoError) {
	if(lep_gen<0||lep_gen>1) return 1;
	if(true_lep_gen<2||true_lep_gen>3) return 1;
    float fResult = lookup(lep_gen, true_lep_gen, theta, plep, iPosWeight);
    if (fResult < 0) return 1.;
    if(!iError) {
	    if (iVarBin >= 0 && iVarBin < nVarBins && !iNoError) hEntries[iVarBin][lep_gen+2*true_lep_gen -4]->Fill(plep, theta);
	    return fResult;
    } else {
	    
	    return fResult + pow(-1, iError)*calcRelBinError(iVarBin);
    }
}

float LepFake::err(int lep_gen, int true_lep_gen, int theta, int plep) {
    float fResult = lookup(lep_gen, true_lep_gen, theta, plep, iPosErr);
    if (fResult < 0) return 0.;
    return fResult;
}

float LepFake::calcBinError(int iVarBin) {
    if (iVarBin < 0 || iVarBin >= nVarBins) return -1;
    float fErrTotStat2 = 0;
    for (int i = 0; i < 4; i++) {
        for (int iBinLepMom=0; iBinLepMom<nMomBins; iBinLepMom++) {
            for (int iBinTheta=0; iBinTheta<nThetaBins; iBinTheta++) {
                int nEntries = hEntries[iVarBin][i]->GetBinContent(iBinLepMom+1, iBinTheta+1);
                float fErrStat = err(i%2, i/2 +2, iBinTheta, iBinLepMom)*nEntries;
                fErrTotStat2 += (fErrStat*fErrStat);
            }
        }
    }
    return TMath::Sqrt(fErrTotStat2);
}

float LepFake::calcRelBinError(int iVarBin) {
    if (iVarBin < 0 || iVarBin >= nVarBins) return -1;
    float fErrTotStat2 = 0;
    float nTotalEntries = 0;
    for (int i = 0; i < 4; i++) {
        for (int iBinLepMom=0; iBinLepMom<nMomBins; iBinLepMom++) {
            for (int iBinTheta=0; iBinTheta<nThetaBins; iBinTheta++) {
                int nEntries = hEntries[iVarBin][i]->GetBinContent(iBinLepMom+1, iBinTheta+1);
		nTotalEntries += nEntries;
                float fErrStat = err(i%2, i/2+2, iBinTheta, iBinLepMom)*nEntries;
                fErrTotStat2 += (fErrStat*fErrStat);
            }
        }
    }
    if(nTotalEntries>0)
    	return TMath::Sqrt(fErrTotStat2)/nTotalEntries;
    else return 0;
}

void LepFake::reset() {
    for (int iVarBin=0; iVarBin<nVarBins; iVarBin++) {
        for (int i=0; i<4; i++) {
            hEntries[iVarBin][i]->Reset();
        }
    }
}

const int LepFake::nMomBins = 11;
const int LepFake::nThetaBins = 8;
const int LepFake::nColumns = 6;

// Lepton fake rate correction tables
const float LepFake::fPi2ElecFake[] = {
//elid >.6
/*
0, 18, 0, 0.5, 1, 0,
0, 18, 0.5, 0.75, 1, 0,
0, 18, 0.75, 1, 0.278, 0.15,
0, 18, 1, 1.25, 0.38, 0.107,
0, 18, 1.25, 1.5, 0.686, 0.16,
0, 18, 1.5, 1.75, 1.066, 0.314,
0, 18, 1.75, 2, 0.419, 0.133,
0, 18, 2, 2.25, 1.392, 0.483,
0, 18, 2.25, 2.5, 0.798, 0.348,
0, 18, 2.5, 3, 0.503, 0.193,
0, 18, 3, 4, 0.944, 0.281,

18, 25, 0, 0.5, 1, 0,
18, 25, 0.5, 0.75, 1, 0,
18, 25, 0.75, 1, 0.602, 0.092,
18, 25, 1, 1.25, 0.657, 0.092,
18, 25, 1.25, 1.5, 0.713, 0.087,
18, 25, 1.5, 1.75, 0.569, 0.072,
18, 25, 1.75, 2, 0.686, 0.086,
18, 25, 2, 2.25, 0.731, 0.102,
18, 25, 2.25, 2.5, 0.794, 0.125,
18, 25, 2.5, 3, 0.831, 0.09,
18, 25, 3, 4, 0.806, 0.086,

25, 35, 0, 0.5, 1, 0,
25, 35, 0.5, 0.75, 0.948, 0.747,
25, 35, 0.75, 1, 0.476, 0.088,
25, 35, 1, 1.25, 0.637, 0.099,
25, 35, 1.25, 1.5, 0.564, 0.081,
25, 35, 1.5, 1.75, 0.573, 0.087,
25, 35, 1.75, 2, 0.453, 0.064,
25, 35, 2, 2.25, 0.388, 0.069,
25, 35, 2.25, 2.5, 0.69, 0.098,
25, 35, 2.5, 3, 0.642, 0.07,
25, 35, 3, 4, 0.627, 0.053,

35, 40, 0, 0.5, 1, 0,
35, 40, 0.5, 0.75, 0.295, 0.288,
35, 40, 0.75, 1, 0.427, 0.145,
35, 40, 1, 1.25, 0.283, 0.056,
35, 40, 1.25, 1.5, 0.553, 0.154,
35, 40, 1.5, 1.75, 0.416, 0.098,
35, 40, 1.75, 2, 0.331, 0.076,
35, 40, 2, 2.25, 0.258, 0.069,
35, 40, 2.25, 2.5, 0.614, 0.106,
35, 40, 2.5, 3, 0.499, 0.067,
35, 40, 3, 4, 0.453, 0.027,

40, 60, 0, 0.5, 1, 0,
40, 60, 0.5, 0.75, 0.614, 0.182,
40, 60, 0.75, 1, 0.685, 0.124,
40, 60, 1, 1.25, 0.695, 0.084,
40, 60, 1.25, 1.5, 0.588, 0.061,
40, 60, 1.5, 1.75, 0.394, 0.04,
40, 60, 1.75, 2, 0.456, 0.043,
40, 60, 2, 2.25, 0.404, 0.041,
40, 60, 2.25, 2.5, 0.688, 0.064,
40, 60, 2.5, 3, 0.617, 0.044,
40, 60, 3, 4, 0.606, 0.041,

60, 125, 0, 0.5, 0.842, 0.134,
60, 125, 0.5, 0.75, 0.67, 0.059,
60, 125, 0.75, 1, 0.884, 0.067,
60, 125, 1, 1.25, 0.702, 0.043,
60, 125, 1.25, 1.5, 0.56, 0.033,
60, 125, 1.5, 1.75, 0.645, 0.036,
60, 125, 1.75, 2, 0.51, 0.03,
60, 125, 2, 2.25, 0.745, 0.047,
60, 125, 2.25, 2.5, 0.568, 0.042,
60, 125, 2.5, 3, 0.793, 0.052,
60, 125, 3, 4, 0.713, 0.072,

125, 132, 0, 0.5, 0.605, 0.159,
125, 132, 0.5, 0.75, 0.632, 0.164,
125, 132, 0.75, 1, 0.547, 0.227,
125, 132, 1, 1.25, 0.311, 0.253,
125, 132, 1.25, 1.5, 1, 0,
125, 132, 1.5, 1.75, 0.273, 0.192,
125, 132, 1.75, 2, 1, 0,
125, 132, 2, 2.25, 1.238, 0.853,
125, 132, 2.25, 2.5, 0.351, 0.283,
125, 132, 2.5, 3, 1.283, 2.129,
125, 132, 3, 4, 1, 0,

132, 151, 0, 0.5, 0.637, 0.077,
132, 151, 0.5, 0.75, 0.53, 0.067,
132, 151, 0.75, 1, 0.457, 0.065,
132, 151, 1, 1.25, 0.409, 0.051,
132, 151, 1.25, 1.5, 0.433, 0.072,
132, 151, 1.5, 1.75, 0.334, 0.079,
132, 151, 1.75, 2, 0.462, 0.111,
132, 151, 2, 2.25, 0.303, 0.222,
132, 151, 2.25, 2.5, 1.358, 0,
132, 151, 2.5, 3, 1, 0,
132, 151, 3, 4, 1, 0


*/
	//elid > .9
  0,  18, 0.000, 0.500, 1.086, 0.199,
  0,  18, 0.500, 0.750, 0.574, 0.135,
  0,  18, 0.750, 1.000, 0.575, 0.115,
  0,  18, 1.000, 1.250, 0.389, 0.072,
  0,  18, 1.250, 1.500, 0.689, 0.191,
  0,  18, 1.500, 1.750, 0.289, 0.138,
  0,  18, 1.750, 2.000, 0.583, 0.236,
  0,  18, 2.000, 2.250, 0.800, 0.801,
  0,  18, 2.250, 2.500, 2.833, 4.923,
  0,  18, 2.500, 3.000, 1.000, 0.000,
  0,  18, 3.000, 4.000, 1.000, 0.000,

 18,  25, 0.000, 0.500, 0.648, 0.223,
 18,  25, 0.500, 0.750, 0.663, 0.306,
 18,  25, 0.750, 1.000, 1.009, 0.615,
 18,  25, 1.000, 1.250, 1.000, 0.000,
 18,  25, 1.250, 1.500, 1.000, 0.000,
 18,  25, 1.500, 1.750, 1.000, 0.000,
 18,  25, 1.750, 2.000, 1.000, 0.000,
 18,  25, 2.000, 2.250, 2.775, 4.076,
 18,  25, 2.250, 2.500, 0.357, 0.315,
 18,  25, 2.500, 3.000, 1.283, 1.804,
 18,  25, 3.000, 4.000, 1.000, 0.000,

 25,  35, 0.000, 0.500, 0.634, 0.159,
 25,  35, 0.500, 0.750, 0.778, 0.095,
 25,  35, 0.750, 1.000, 1.112, 0.132,
 25,  35, 1.000, 1.250, 0.826, 0.083,
 25,  35, 1.250, 1.500, 0.646, 0.063,
 25,  35, 1.500, 1.750, 0.778, 0.070,
 25,  35, 1.750, 2.000, 0.481, 0.050,
 25,  35, 2.000, 2.250, 1.186, 0.125,
 25,  35, 2.250, 2.500, 0.624, 0.072,
 25,  35, 2.500, 3.000, 1.048, 0.084,
 25,  35, 3.000, 4.000, 0.888, 0.147,

 35,  40, 0.000, 0.500, 1.000, 0.000,
 35,  40, 0.500, 0.750, 0.581, 0.248,
 35,  40, 0.750, 1.000, 0.633, 0.166,
 35,  40, 1.000, 1.250, 1.009, 0.191,
 35,  40, 1.250, 1.500, 0.618, 0.111,
 35,  40, 1.500, 1.750, 0.403, 0.066,
 35,  40, 1.750, 2.000, 0.325, 0.063,
 35,  40, 2.000, 2.250, 0.447, 0.080,
 35,  40, 2.250, 2.500, 1.019, 0.155,
 35,  40, 2.500, 3.000, 0.673, 0.088,
 35,  40, 3.000, 4.000, 0.764, 0.088,

 40,  60, 0.000, 0.500, 1.000, 0.000,
 40,  60, 0.500, 0.750, 0.138, 0.304,
 40,  60, 0.750, 1.000, 0.219, 0.138,
 40,  60, 1.000, 1.250, 1.000, 0.000,
 40,  60, 1.250, 1.500, 0.469, 0.225,
 40,  60, 1.500, 1.750, 0.651, 0.254,
 40,  60, 1.750, 2.000, 0.268, 0.115,
 40,  60, 2.000, 2.250, 0.314, 0.121,
 40,  60, 2.250, 2.500, 1.006, 0.269,
 40,  60, 2.500, 3.000, 0.593, 0.136,
 40,  60, 3.000, 4.000, 0.582, 0.105,

 60, 125, 0.000, 0.500, 1.000, 0.000,
 60, 125, 0.500, 0.750, 0.643, 0.669,
 60, 125, 0.750, 1.000, 0.550, 0.121,
 60, 125, 1.000, 1.250, 0.722, 0.143,
 60, 125, 1.250, 1.500, 0.649, 0.117,
 60, 125, 1.500, 1.750, 0.670, 0.143,
 60, 125, 1.750, 2.000, 1.000, 0.000,
 60, 125, 2.000, 2.250, 1.000, 0.000,
 60, 125, 2.250, 2.500, 1.000, 0.000,
 60, 125, 2.500, 3.000, 1.000, 0.000,
 60, 125, 3.000, 4.000, 1.000, 0.000,

125, 132, 0.000, 0.500, 1.000, 0.000,
125, 132, 0.500, 0.750, 1.000, 0.000,
125, 132, 0.750, 1.000, 1.000, 0.000,
125, 132, 1.000, 1.250, 1.000, 0.000,
125, 132, 1.250, 1.500, 1.000, 0.000,
125, 132, 1.500, 1.750, 1.000, 0.000,
125, 132, 1.750, 2.000, 1.000, 0.000,
125, 132, 2.000, 2.250, 1.000, 0.000,
125, 132, 2.250, 2.500, 1.000, 0.000,
125, 132, 2.500, 3.000, 1.000, 0.000,
125, 132, 3.000, 4.000, 1.000, 0.000,

132, 151, 0.000, 0.500, 1.000, 0.000,
132, 151, 0.500, 0.750, 1.000, 0.000,
132, 151, 0.750, 1.000, 1.000, 0.000,
132, 151, 1.000, 1.250, 1.000, 0.000,
132, 151, 1.250, 1.500, 1.000, 0.000,
132, 151, 1.500, 1.750, 1.000, 0.000,
132, 151, 1.750, 2.000, 1.000, 0.000,
132, 151, 2.000, 2.250, 1.000, 0.000,
132, 151, 2.250, 2.500, 1.000, 0.000,
132, 151, 2.500, 3.000, 1.000, 0.000,
132, 151, 3.000, 4.000, 1.000, 0.000

};

const float LepFake::fK2ElecFake[] = {
//elid >.6
/*
0, 18, 0, 0.5, 1, 0,
0, 18, 0.5, 0.75, 1, 0,
0, 18, 0.75, 1, 0.838, 0.513,
0, 18, 1, 1.25, 0.803, 0.29,
0, 18, 1.25, 1.5, 1.565, 0.681,
0, 18, 1.5, 1.75, 0.9, 0.425,
0, 18, 1.75, 2, 0.535, 0.368,
0, 18, 2, 2.25, 0.818, 0.559,
0, 18, 2.25, 2.5, 1, 0,
0, 18, 2.5, 3, 0.841, 0.41,
0, 18, 3, 4, 1.798, 1.003,
18, 25, 0, 0.5, 1, 0,
18, 25, 0.5, 0.75, 1, 0,
18, 25, 0.75, 1, 1.461, 0.24,
18, 25, 1, 1.25, 0.715, 0.136,
18, 25, 1.25, 1.5, 0.56, 0.133,
18, 25, 1.5, 1.75, 1.075, 0.291,
18, 25, 1.75, 2, 0.59, 0.225,
18, 25, 2, 2.25, 0.614, 0.386,
18, 25, 2.25, 2.5, 1.089, 0.617,
18, 25, 2.5, 3, 0.214, 0.131,
18, 25, 3, 4, 1.171, 0.27,
25, 35, 0, 0.5, 1, 0,
25, 35, 0.5, 0.75, 1, 0,
25, 35, 0.75, 1, 1.485, 0.195,
25, 35, 1, 1.25, 1.185, 0.232,
25, 35, 1.25, 1.5, 0.647, 0.142,
25, 35, 1.5, 1.75, 0.448, 0.205,
25, 35, 1.75, 2, 1, 0,
25, 35, 2, 2.25, 1.322, 0.55,
25, 35, 2.25, 2.5, 1, 0,
25, 35, 2.5, 3, 1, 0,
25, 35, 3, 4, 1.411, 0.534,
35, 40, 0, 0.5, 1, 0,
35, 40, 0.5, 0.75, 1.411, 1.029,
35, 40, 0.75, 1, 1.191, 0.189,
35, 40, 1, 1.25, 0.642, 0.334,
35, 40, 1.25, 1.5, 1, 0,
35, 40, 1.5, 1.75, 1, 0,
35, 40, 1.75, 2, 1, 0,
35, 40, 2, 2.25, 1, 0,
35, 40, 2.25, 2.5, 1, 0,
35, 40, 2.5, 3, 1, 0,
35, 40, 3, 4, 1, 0,
40, 60, 0, 0.5, 1, 0,
40, 60, 0.5, 0.75, 0.786, 0.061,
40, 60, 0.75, 1, 1.344, 0.073,
40, 60, 1, 1.25, 1.685, 0.412,
40, 60, 1.25, 1.5, 0.819, 0.373,
40, 60, 1.5, 1.75, 1, 0,
40, 60, 1.75, 2, 1.122, 0.783,
40, 60, 2, 2.25, 0.947, 0.472,
40, 60, 2.25, 2.5, 1, 0,
40, 60, 2.5, 3, 1, 0,
40, 60, 3, 4, 1.285, 0.415,
60, 125, 0, 0.5, 2.24, 0.195,
60, 125, 0.5, 0.75, 1.178, 0.023,
60, 125, 0.75, 1, 1.513, 0.073,
60, 125, 1, 1.25, 0.86, 0.106,
60, 125, 1.25, 1.5, 0.316, 0.087,
60, 125, 1.5, 1.75, 1, 0,
60, 125, 1.75, 2, 0.815, 0.226,
60, 125, 2, 2.25, 1, 0,
60, 125, 2.25, 2.5, 1, 0,
60, 125, 2.5, 3, 1.228, 0.388,
60, 125, 3, 4, 0.896, 0.228,
125, 132, 0, 0.5, 1.254, 0.269,
125, 132, 0.5, 0.75, 1.212, 0.057,
125, 132, 0.75, 1, 1.881, 0.367,
125, 132, 1, 1.25, 1, 0,
125, 132, 1.25, 1.5, 0.395, 0.277,
125, 132, 1.5, 1.75, 1, 0,
125, 132, 1.75, 2, 1, 0,
125, 132, 2, 2.25, 1.823, 3.126,
125, 132, 2.25, 2.5, 1, 0,
125, 132, 2.5, 3, 1, 0,
125, 132, 3, 4, 1, 0,
132, 151, 0, 0.5, 2, 0.256,
132, 151, 0.5, 0.75, 1.182, 0.026,
132, 151, 0.75, 1, 1.254, 0.082,
132, 151, 1, 1.25, 0.588, 0.079,
132, 151, 1.25, 1.5, 0.853, 0.232,
132, 151, 1.5, 1.75, 3.075, 1.707,
132, 151, 1.75, 2, 0.24, 0.39,
132, 151, 2, 2.25, 1, 0,
132, 151, 2.25, 2.5, 1, 0,
132, 151, 2.5, 3, 1, 0,
132, 151, 3, 4, 1, 0


*/
//elid >.9
  0,  18, 0.000, 0.500, 1.377, 0.371,
  0,  18, 0.500, 0.750, 1.379, 0.062,
  0,  18, 0.750, 1.000, 1.556, 0.155,
  0,  18, 1.000, 1.250, 0.579, 0.121,
  0,  18, 1.250, 1.500, 0.772, 0.344,
  0,  18, 1.500, 1.750, 1.000, 0.000,
  0,  18, 1.750, 2.000, 1.000, 0.000,
  0,  18, 2.000, 2.250, 1.000, 0.000,
  0,  18, 2.250, 2.500, 1.000, 0.000,
  0,  18, 2.500, 3.000, 1.000, 0.000,
  0,  18, 3.000, 4.000, 1.000, 0.000,

 18,  25, 0.000, 0.500, 0.894, 0.493,
 18,  25, 0.500, 0.750, 1.498, 0.146,
 18,  25, 0.750, 1.000, 3.860, 1.553,
 18,  25, 1.000, 1.250, 1.000, 0.000,
 18,  25, 1.250, 1.500, 0.223, 0.300,
 18,  25, 1.500, 1.750, 1.000, 0.000,
 18,  25, 1.750, 2.000, 1.000, 0.000,
 18,  25, 2.000, 2.250, 1.628, 2.567,
 18,  25, 2.250, 2.500, 1.000, 0.000,
 18,  25, 2.500, 3.000, 1.000, 0.000,
 18,  25, 3.000, 4.000, 1.000, 0.000,

 25,  35, 0.000, 0.500, 1.974, 0.171,
 25,  35, 0.500, 0.750, 1.213, 0.043,
 25,  35, 0.750, 1.000, 1.673, 0.140,
 25,  35, 1.000, 1.250, 0.809, 0.239,
 25,  35, 1.250, 1.500, 1.000, 0.000,
 25,  35, 1.500, 1.750, 1.000, 0.000,
 25,  35, 1.750, 2.000, 1.000, 0.000,
 25,  35, 2.000, 2.250, 1.000, 0.000,
 25,  35, 2.250, 2.500, 1.000, 0.000,
 25,  35, 2.500, 3.000, 1.000, 0.000,
 25,  35, 3.000, 4.000, 1.000, 0.000,

 35,  40, 0.000, 0.500, 1.000, 0.000,
 35,  40, 0.500, 0.750, 0.813, 0.113,
 35,  40, 0.750, 1.000, 1.978, 0.266,
 35,  40, 1.000, 1.250, 1.000, 0.000,
 35,  40, 1.250, 1.500, 1.000, 0.000,
 35,  40, 1.500, 1.750, 1.000, 0.000,
 35,  40, 1.750, 2.000, 1.000, 0.000,
 35,  40, 2.000, 2.250, 1.000, 0.000,
 35,  40, 2.250, 2.500, 1.000, 0.000,
 35,  40, 2.500, 3.000, 1.000, 0.000,
 35,  40, 3.000, 4.000, 1.000, 0.000,

 40,  60, 0.000, 0.500, 1.000, 0.000,
 40,  60, 0.500, 0.750, 2.113, 1.861,
 40,  60, 0.750, 1.000, 1.484, 0.372,
 40,  60, 1.000, 1.250, 0.606, 0.424,
 40,  60, 1.250, 1.500, 1.000, 0.000,
 40,  60, 1.500, 1.750, 1.000, 0.000,
 40,  60, 1.750, 2.000, 1.000, 0.000,
 40,  60, 2.000, 2.250, 1.000, 0.000,
 40,  60, 2.250, 2.500, 1.000, 0.000,
 40,  60, 2.500, 3.000, 1.000, 0.000,
 40,  60, 3.000, 4.000, 1.000, 0.000,

 60, 125, 0.000, 0.500, 1.000, 0.000,
 60, 125, 0.500, 0.750, 1.000, 0.000,
 60, 125, 0.750, 1.000, 1.399, 0.166,
 60, 125, 1.000, 1.250, 1.304, 0.321,
 60, 125, 1.250, 1.500, 0.638, 0.169,
 60, 125, 1.500, 1.750, 0.233, 0.207,
 60, 125, 1.750, 2.000, 1.000, 0.000,
 60, 125, 2.000, 2.250, 1.000, 0.000,
 60, 125, 2.250, 2.500, 1.000, 0.000,
 60, 125, 2.500, 3.000, 1.000, 0.000,
 60, 125, 3.000, 4.000, 1.000, 0.000,

125, 132, 0.000, 0.500, 1.000, 0.000,
125, 132, 0.500, 0.750, 1.000, 0.000,
125, 132, 0.750, 1.000, 1.000, 0.000,
125, 132, 1.000, 1.250, 1.000, 0.000,
125, 132, 1.250, 1.500, 1.000, 0.000,
125, 132, 1.500, 1.750, 1.000, 0.000,
125, 132, 1.750, 2.000, 1.000, 0.000,
125, 132, 2.000, 2.250, 1.000, 0.000,
125, 132, 2.250, 2.500, 1.000, 0.000,
125, 132, 2.500, 3.000, 1.000, 0.000,
125, 132, 3.000, 4.000, 1.000, 0.000,

132, 151, 0.000, 0.500, 1.000, 0.000,
132, 151, 0.500, 0.750, 1.000, 0.000,
132, 151, 0.750, 1.000, 1.000, 0.000,
132, 151, 1.000, 1.250, 1.000, 0.000,
132, 151, 1.250, 1.500, 1.000, 0.000,
132, 151, 1.500, 1.750, 1.000, 0.000,
132, 151, 1.750, 2.000, 1.000, 0.000,
132, 151, 2.000, 2.250, 1.000, 0.000,
132, 151, 2.250, 2.500, 1.000, 0.000,
132, 151, 2.500, 3.000, 1.000, 0.000,
132, 151, 3.000, 4.000, 1.000, 0.000

};
// Eff(data)/Eff(MC)  -- Muons
// With efficiency correction and errors
const float LepFake::fPi2MuonFake[] = {
  0,  17, 0.000, 0.500, 1.000, 0.000,
  0,  17, 0.500, 0.750, 1.000, 0.000,
  0,  17, 0.750, 1.000, 1.000, 0.000,
  0,  17, 1.000, 1.250, 1.000, 0.000,
  0,  17, 1.250, 1.500, 0.807, 0.462,
  0,  17, 1.500, 1.750, 0.158, 0.129,
  0,  17, 1.750, 2.000, 2.083, 2.261,
  0,  17, 2.000, 2.250, 1.000, 0.000,
  0,  17, 2.250, 2.500, 1.000, 0.000,
  0,  17, 2.500, 3.000, 1.000, 0.000,
  0,  17, 3.000, 4.000, 1.000, 0.000,

 17,  25, 0.000, 0.500, 1.000, 0.000,
 17,  25, 0.500, 0.750, 0.323, 0.026,
 17,  25, 0.750, 1.000, 0.559, 0.029,
 17,  25, 1.000, 1.250, 0.693, 0.043,
 17,  25, 1.250, 1.500, 0.543, 0.044,
 17,  25, 1.500, 1.750, 0.711, 0.067,
 17,  25, 1.750, 2.000, 0.831, 0.101,
 17,  25, 2.000, 2.250, 0.839, 0.143,
 17,  25, 2.250, 2.500, 0.560, 0.142,
 17,  25, 2.500, 3.000, 4.424, 0.000,
 17,  25, 3.000, 4.000, 1.000, 0.000,

 25,  37, 0.000, 0.500, 1.000, 0.000,
 25,  37, 0.500, 0.750, 0.708, 0.067,
 25,  37, 0.750, 1.000, 0.756, 0.028,
 25,  37, 1.000, 1.250, 0.835, 0.040,
 25,  37, 1.250, 1.500, 0.820, 0.042,
 25,  37, 1.500, 1.750, 0.781, 0.043,
 25,  37, 1.750, 2.000, 0.735, 0.035,
 25,  37, 2.000, 2.250, 0.883, 0.095,
 25,  37, 2.250, 2.500, 0.896, 0.098,
 25,  37, 2.500, 3.000, 0.553, 0.000,
 25,  37, 3.000, 4.000, 1.000, 0.000,

 37,  51, 0.000, 0.500, 1.000, 0.000,
 37,  51, 0.500, 0.750, 0.890, 0.020,
 37,  51, 0.750, 1.000, 0.922, 0.013,
 37,  51, 1.000, 1.250, 0.887, 0.017,
 37,  51, 1.250, 1.500, 0.877, 0.020,
 37,  51, 1.500, 1.750, 0.855, 0.021,
 37,  51, 1.750, 2.000, 0.902, 0.027,
 37,  51, 2.000, 2.250, 0.916, 0.030,
 37,  51, 2.250, 2.500, 0.904, 0.034,
 37,  51, 2.500, 3.000, 0.825, 0.029,
 37,  51, 3.000, 4.000, 0.739, 0.038,

 51, 117, 0.000, 0.500, 1.000, 0.000,
 51, 117, 0.500, 0.750, 0.672, 0.284,
 51, 117, 0.750, 1.000, 0.748, 0.028,
 51, 117, 1.000, 1.250, 0.782, 0.033,
 51, 117, 1.250, 1.500, 0.719, 0.037,
 51, 117, 1.500, 1.750, 0.878, 0.048,
 51, 117, 1.750, 2.000, 0.824, 0.033,
 51, 117, 2.000, 2.250, 0.720, 0.042,
 51, 117, 2.250, 2.500, 0.816, 0.053,
 51, 117, 2.500, 3.000, 0.848, 0.046,
 51, 117, 3.000, 4.000, 0.818, 0.032,

117, 130, 0.000, 0.500, 1.000, 0.000,
117, 130, 0.500, 0.750, 0.589, 0.091,
117, 130, 0.750, 1.000, 0.583, 0.029,
117, 130, 1.000, 1.250, 0.679, 0.034,
117, 130, 1.250, 1.500, 0.741, 0.049,
117, 130, 1.500, 1.750, 0.706, 0.049,
117, 130, 1.750, 2.000, 0.661, 0.042,
117, 130, 2.000, 2.250, 0.603, 0.038,
117, 130, 2.250, 2.500, 0.662, 0.043,
117, 130, 2.500, 3.000, 0.537, 0.026,
117, 130, 3.000, 4.000, 0.554, 0.025,

130, 145, 0.000, 0.500, 1.000, 0.000,
130, 145, 0.500, 0.750, 1.000, 0.000,
130, 145, 0.750, 1.000, 1.000, 0.000,
130, 145, 1.000, 1.250, 1.000, 0.000,
130, 145, 1.250, 1.500, 1.000, 0.000,
130, 145, 1.500, 1.750, 0.173, 0.133,
130, 145, 1.750, 2.000, 0.711, 0.223,
130, 145, 2.000, 2.250, 0.246, 0.092,
130, 145, 2.250, 2.500, 0.224, 0.111,
130, 145, 2.500, 3.000, 0.182, 0.068,
130, 145, 3.000, 4.000, 0.395, 0.071,

145, 150, 0.000, 0.500, 1.000, 0.000,
145, 150, 0.500, 0.750, 1.000, 0.000,
145, 150, 0.750, 1.000, 1.000, 0.000,
145, 150, 1.000, 1.250, 1.000, 0.000,
145, 150, 1.250, 1.500, 1.000, 0.000,
145, 150, 1.500, 1.750, 1.000, 0.000,
145, 150, 1.750, 2.000, 1.000, 0.000,
145, 150, 2.000, 2.250, 1.000, 0.000,
145, 150, 2.250, 2.500, 1.000, 0.000,
145, 150, 2.500, 3.000, 1.000, 0.000,
145, 150, 3.000, 4.000, 1.000, 0.000

};
const float LepFake::fK2MuonFake[] = {
  0,  17, 0.000, 0.500, 1.000, 0.000,
  0,  17, 0.500, 0.750, 1.000, 0.000,
  0,  17, 0.750, 1.000, 1.000, 0.000,
  0,  17, 1.000, 1.250, 1.000, 0.000,
  0,  17, 1.250, 1.500, 0.345, 0.193,
  0,  17, 1.500, 1.750, 1.000, 0.000,
  0,  17, 1.750, 2.000, 0.762, 0.277,
  0,  17, 2.000, 2.250, 0.797, 0.460,
  0,  17, 2.250, 2.500, 0.854, 0.753,
  0,  17, 2.500, 3.000, 1.320, 1.161,
  0,  17, 3.000, 4.000, 1.000, 0.000,

 17,  25, 0.000, 0.500, 1.000, 0.000,
 17,  25, 0.500, 0.750, 0.489, 0.104,
 17,  25, 0.750, 1.000, 0.569, 0.055,
 17,  25, 1.000, 1.250, 0.620, 0.054,
 17,  25, 1.250, 1.500, 0.617, 0.052,
 17,  25, 1.500, 1.750, 0.591, 0.050,
 17,  25, 1.750, 2.000, 0.641, 0.053,
 17,  25, 2.000, 2.250, 0.701, 0.000,
 17,  25, 2.250, 2.500, 0.639, 0.063,
 17,  25, 2.500, 3.000, 0.580, 0.120,
 17,  25, 3.000, 4.000, 1.000, 0.000,

 25,  37, 0.000, 0.500, 1.000, 0.000,
 25,  37, 0.500, 0.750, 0.745, 0.102,
 25,  37, 0.750, 1.000, 0.728, 0.041,
 25,  37, 1.000, 1.250, 0.747, 0.046,
 25,  37, 1.250, 1.500, 0.767, 0.041,
 25,  37, 1.500, 1.750, 0.750, 0.035,
 25,  37, 1.750, 2.000, 0.760, 0.042,
 25,  37, 2.000, 2.250, 0.670, 0.050,
 25,  37, 2.250, 2.500, 0.738, 0.071,
 25,  37, 2.500, 3.000, 0.659, 0.082,
 25,  37, 3.000, 4.000, 0.851, 0.419,

 37,  51, 0.000, 0.500, 1.000, 0.000,
 37,  51, 0.500, 0.750, 0.810, 0.032,
 37,  51, 0.750, 1.000, 0.778, 0.018,
 37,  51, 1.000, 1.250, 0.895, 0.023,
 37,  51, 1.250, 1.500, 0.879, 0.021,
 37,  51, 1.500, 1.750, 0.836, 0.017,
 37,  51, 1.750, 2.000, 0.850, 0.019,
 37,  51, 2.000, 2.250, 0.813, 0.019,
 37,  51, 2.250, 2.500, 0.809, 0.021,
 37,  51, 2.500, 3.000, 0.736, 0.013,
 37,  51, 3.000, 4.000, 0.719, 0.014,

 51, 117, 0.000, 0.500, 1.000, 0.000,
 51, 117, 0.500, 0.750, 0.666, 0.334,
 51, 117, 0.750, 1.000, 0.701, 0.024,
 51, 117, 1.000, 1.250, 0.808, 0.041,
 51, 117, 1.250, 1.500, 0.753, 0.038,
 51, 117, 1.500, 1.750, 0.819, 0.039,
 51, 117, 1.750, 2.000, 0.716, 0.030,
 51, 117, 2.000, 2.250, 0.792, 0.034,
 51, 117, 2.250, 2.500, 0.828, 0.039,
 51, 117, 2.500, 3.000, 0.748, 0.028,
 51, 117, 3.000, 4.000, 0.749, 0.020,

117, 130, 0.000, 0.500, 1.000, 0.000,
117, 130, 0.500, 0.750, 1.421, 5.160,
117, 130, 0.750, 1.000, 0.568, 0.063,
117, 130, 1.000, 1.250, 0.785, 0.054,
117, 130, 1.250, 1.500, 0.682, 0.046,
117, 130, 1.500, 1.750, 0.579, 0.036,
117, 130, 1.750, 2.000, 0.638, 0.036,
117, 130, 2.000, 2.250, 0.529, 0.029,
117, 130, 2.250, 2.500, 0.528, 0.028,
117, 130, 2.500, 3.000, 0.535, 0.019,
117, 130, 3.000, 4.000, 0.525, 0.009,

130, 145, 0.000, 0.500, 1.000, 0.000,
130, 145, 0.500, 0.750, 1.000, 0.000,
130, 145, 0.750, 1.000, 1.000, 0.000,
130, 145, 1.000, 1.250, 1.000, 0.000,
130, 145, 1.250, 1.500, 0.195, 0.176,
130, 145, 1.500, 1.750, 0.497, 0.126,
130, 145, 1.750, 2.000, 0.414, 0.114,
130, 145, 2.000, 2.250, 0.383, 0.131,
130, 145, 2.250, 2.500, 0.382, 0.099,
130, 145, 2.500, 3.000, 0.345, 0.062,
130, 145, 3.000, 4.000, 0.342, 0.048,

145, 150, 0.000, 0.500, 1.000, 0.000,
145, 150, 0.500, 0.750, 1.000, 0.000,
145, 150, 0.750, 1.000, 1.000, 0.000,
145, 150, 1.000, 1.250, 1.000, 0.000,
145, 150, 1.250, 1.500, 1.000, 0.000,
145, 150, 1.500, 1.750, 1.000, 0.000,
145, 150, 1.750, 2.000, 1.000, 0.000,
145, 150, 2.000, 2.250, 1.000, 0.000,
145, 150, 2.250, 2.500, 1.000, 0.000,
145, 150, 2.500, 3.000, 1.000, 0.000,
145, 150, 3.000, 4.000, 1.000, 0.000
};
