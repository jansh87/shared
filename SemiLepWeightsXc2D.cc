// ///////////////////////////////////////////////////////////
// Weigthts for Xc -> X l nu decays
// to correct the Belle generic MC (latest version).
// ISGW2 -> SLPOLE/SLBKPOLE
//
// Author: Christian Oswald, Uni Bonn, 2014.
// Version: 1.0
// ////////////////////////////////////////////////////////////

#include "SemiLepWeightsXc2D.h"
#include "TMath.h"
void SemiLepWeightsXc2D::init(int varBins, const char* strVar) {
    nVarBins = varBins;

    nlclass = 5;

    // D0 -> K l nu
    lclass2index[21] = 0;
    index2lclass[0] = 21;
    nBinsLepMom[0] = 10;
    nColumns[0] = 7;
    fTables[0] = f2DWeights21;
    nBinsQ2[0] = 10;
    fQ2Min[0] = 0;
    fQ2Max[0] = 1.2;
    fPlepMin[0] = 0;
    fPlepMax[0] = 0.9;
    iPosWeight[0] = 4;
    iPosErrStat[0] = 5;
    iPosErrSyst[0] = 6;

    // D0 -> K* l nu
    lclass2index[22] = 1;
    index2lclass[1] = 22;
    nBinsLepMom[1] = 10;
    nColumns[1] = 7;
    fTables[1] = f2DWeights22;
    nBinsQ2[1] = 10;
    fQ2Min[1] = 0;
    fQ2Max[1] = 1.1;
    fPlepMin[1] = 0;
    fPlepMax[1] = 0.7;
    iPosWeight[1] = 4;
    iPosErrStat[1] = 5;
    iPosErrSyst[1] = 6;

    // D -> K l nu
    lclass2index[23] = 2;
    index2lclass[2] = 23;
    nBinsLepMom[2] = 10;
    nColumns[2] = 7;
    fTables[2] = f2DWeights23;
    nBinsQ2[2] = 10;
    fQ2Min[2] = 0;
    fQ2Max[2] = 1.2;
    fPlepMin[2] = 0;
    fPlepMax[2] = 0.9;
    iPosWeight[2] = 4;
    iPosErrStat[2] = 5;
    iPosErrSyst[2] = 6;

    // D -> K* l nu
    lclass2index[24] = 3;
    index2lclass[3] = 24;
    nBinsLepMom[3] = 10;
    nColumns[3] = 7;
    fTables[3] = f2DWeights24;
    nBinsQ2[3] = 10;
    fQ2Min[3] = 0;
    fQ2Max[3] = 1.1;
    fPlepMin[3] = 0;
    fPlepMax[3] = 0.7;
    iPosWeight[3] = 4;
    iPosErrStat[3] = 5;
    iPosErrSyst[3] = 6;

    // Ds -> phi l nu
    lclass2index[25] = 4;
    index2lclass[4] = 25;
    nBinsLepMom[4] = 10;
    nColumns[4] = 7;
    fTables[4] = f2DWeights25;
    nBinsQ2[4] = 10;
    fQ2Min[4] = 0;
    fQ2Max[4] = 1.0;
    fPlepMin[4] = 0;
    fPlepMax[4] = 0.7;
    iPosWeight[4] = 4;
    iPosErrStat[4] = 5;
    iPosErrSyst[4] = 6;

    hEntries = new TH2F**[nVarBins];
    char text[200];
    for (int iVarBin=0; iVarBin<nVarBins; iVarBin++) {
        hEntries[iVarBin] = new TH2F*[nlclass];
        for (int i=0; i<nlclass; i++) {
            int lclass = index2lclass[i];
            sprintf(text, "h_SLWeightEntries_old_%s_bin%03i_lclass%02i", strVar, iVarBin, lclass);
            hEntries[iVarBin][i] = new TH2F(text, text, nBinsQ2[i], fQ2Min[i], fQ2Max[i], nBinsLepMom[i], fPlepMin[i], fPlepMax[i]);
        }
    }
}

SemiLepWeightsXc2D::SemiLepWeightsXc2D() {
    init(1, "default");
}

SemiLepWeightsXc2D::SemiLepWeightsXc2D(int varBins, const char* strVar) {
    init (varBins, strVar);
}

SemiLepWeightsXc2D::~SemiLepWeightsXc2D() {
    for (int iVarBin=0; iVarBin<nVarBins; iVarBin++) {
        for (int i=0; i<nlclass; i++) {
            delete hEntries[iVarBin][i];
        }
        delete[] hEntries[iVarBin];
    }
    delete[] hEntries;
}

float SemiLepWeightsXc2D::lookup(int i, int iBinQ2, int iBinLepMom, int iType) {
    if (iType < 0 || iType >= nColumns[i]) return -1;
    if (iBinQ2 < 0 || iBinQ2>=nBinsQ2[i]) return -1;
    if (iBinLepMom < 0 || iBinLepMom >= nBinsLepMom[i]) return -1;
    int iPosition = iBinLepMom*nColumns[i]*nBinsQ2[i]+iBinQ2*nColumns[i]+iType;
    return fTables[i][iPosition];
}


float SemiLepWeightsXc2D::lookup(int i, float q2_t, float lep_ps_t, int iType) {
    int iBinQ2 = int (q2_t*nBinsQ2[i]/(fQ2Max[i]-fQ2Min[i]));
    int iBinLepMom = int(lep_ps_t*nBinsLepMom[i]/(fPlepMax[i]-fPlepMin[i]));
    return lookup(i, iBinQ2, iBinLepMom, iType);
}

float SemiLepWeightsXc2D::weight(int lclass, float q2_t, float lep_ps_t, int iVarBin, int iNoError) {
    if (lclass2index.find(lclass) == lclass2index.end()) return 1.;
    int i = lclass2index[lclass];
    float fResult = lookup(i, q2_t, lep_ps_t, iPosWeight[i]);
    if (fResult < 0) return 1.;
    if(!iError) {
   	if (iVarBin >= 0 && iVarBin < nVarBins && !iNoError) hEntries[iVarBin][i]->Fill(q2_t, lep_ps_t);
    	return fResult;
    } else {
	return fResult + pow(-1, iError)*calcRelBinError(iVarBin);
    }
}

float SemiLepWeightsXc2D::errStat(int lclass, int iBinQ2, int iBinLepMom) {
    if (lclass2index.find(lclass) == lclass2index.end()) return -1;
    int i = lclass2index[lclass];
    float fResult = lookup(i, iBinQ2, iBinLepMom, iPosErrStat[i]);
    if (fResult < 0) return 0.;
    return fResult;
}

float SemiLepWeightsXc2D::errSyst(int lclass, int iBinQ2, int iBinLepMom) {
    if (lclass2index.find(lclass) == lclass2index.end()) return -1;
    int i = lclass2index[lclass];
    float fResult = lookup(i, iBinQ2, iBinLepMom, iPosErrSyst[i]);
    if (fResult < 0) return 0.;
    return fResult;
}

float SemiLepWeightsXc2D::calcBinError(int iVarBin) {
    // loop over all q2 bins
    float fErrTotStat2 = 0.;
    float fErrTotSyst = 0.;
    for (int i = 0; i <= nlclass; i++) {
        int lclass = index2lclass[i];
        for (int iBinLepMom=0; iBinLepMom<nBinsLepMom[i]; iBinLepMom++) {
            for (int iBinQ2=0; iBinQ2<nBinsQ2[i]; iBinQ2++) {
                int nEntries = hEntries[iVarBin][i]->GetBinContent(iBinQ2+1,iBinLepMom+1);
                float fErrStat = errStat(lclass, iBinQ2, iBinLepMom)*nEntries;
                fErrTotStat2 += (fErrStat*fErrStat);
                float fErrSyst = errSyst(lclass, iBinQ2, iBinLepMom)*nEntries;
                fErrTotSyst += fErrSyst;
            }
        }
    }
    return TMath::Sqrt(fErrTotStat2 + fErrTotSyst*fErrTotSyst);
}

float SemiLepWeightsXc2D::calcRelBinError(int iVarBin) {
    // loop over all q2 bins
    float fErrTotStat2 = 0.;
    float fErrTotSyst = 0.;
    float nTotalEntries = 0;
    for (int i = 0; i <= nlclass; i++) {
        int lclass = index2lclass[i];
        for (int iBinLepMom=0; iBinLepMom<nBinsLepMom[i]; iBinLepMom++) {
            for (int iBinQ2=0; iBinQ2<nBinsQ2[i]; iBinQ2++) {
                int nEntries = hEntries[iVarBin][i]->GetBinContent(iBinQ2+1,iBinLepMom+1);
		nTotalEntries += nEntries;
                float fErrStat = errStat(lclass, iBinQ2, iBinLepMom)*nEntries;
                fErrTotStat2 += (fErrStat*fErrStat);
                float fErrSyst = errSyst(lclass, iBinQ2, iBinLepMom)*nEntries;
                fErrTotSyst += fErrSyst;
            }
        }
    }
    if(nTotalEntries >0)
    	return TMath::Sqrt(fErrTotStat2 + fErrTotSyst*fErrTotSyst)/nTotalEntries;
    else 
	return 0;
}
float SemiLepWeightsXc2D::calcBinError(int iVarBin, bool isSyst) {
    // loop over all q2 bins
    float fErrTotStat2 = 0.;
    float fErrTotSyst = 0.;
    for (int i = 0; i <= nlclass; i++) {
        int lclass = index2lclass[i];
        for (int iBinLepMom=0; iBinLepMom<nBinsLepMom[i]; iBinLepMom++) {
            for (int iBinQ2=0; iBinQ2<nBinsQ2[i]; iBinQ2++) {
                int nEntries = hEntries[iVarBin][i]->GetBinContent(iBinQ2+1,iBinLepMom+1);
                if (!isSyst) {
                    float fErrStat = errStat(lclass, iBinQ2, iBinLepMom)*nEntries;
                    fErrTotStat2 += (fErrStat*fErrStat);
                } else {
                    float fErrSyst = errSyst(lclass, iBinQ2, iBinLepMom)*nEntries;
                    fErrTotSyst += fErrSyst;
                }
            }
        }
    }
    return TMath::Sqrt(fErrTotStat2 + fErrTotSyst*fErrTotSyst);
}

void SemiLepWeightsXc2D::reset() {
    for (int iVarBin=0; iVarBin<nVarBins; iVarBin++) {
        for (int i=0; i<nlclass; i++) {
            hEntries[iVarBin][i]->Reset();
        }
    }
}

// ----- D0___K_l_nu -----
// SLBKPOLE with alpha = 0.22
const float SemiLepWeightsXc2D::f2DWeights21[] = {
    0.00, 0.09, 0.00, 0.12, 0.8906, 0.0451, 0.0289,
    0.00, 0.09, 0.12, 0.24, 0.8866, 0.0855, 0.0301,
    0.00, 0.09, 0.24, 0.36, 0.9000, 0.3249, 0.0263,
    0.00, 0.09, 0.36, 0.48, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.48, 0.60, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.60, 0.72, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.72, 0.84, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.84, 0.96, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.96, 1.08, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 1.08, 1.20, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.00, 0.12, 0.8689, 0.0241, 0.0351,
    0.09, 0.18, 0.12, 0.24, 0.9500, 0.0282, 0.0128,
    0.09, 0.18, 0.24, 0.36, 0.8866, 0.0368, 0.0301,
    0.09, 0.18, 0.36, 0.48, 0.9622, 0.0555, 0.0096,
    0.09, 0.18, 0.48, 0.60, 0.9375, 0.1271, 0.0161,
    0.09, 0.18, 0.60, 0.72, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.72, 0.84, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.84, 0.96, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.96, 1.08, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 1.08, 1.20, 1.0000, 0.0000, 0.0000,
    0.18, 0.27, 0.00, 0.12, 0.8642, 0.0194, 0.0364,
    0.18, 0.27, 0.12, 0.24, 0.8871, 0.0207, 0.0299,
    0.18, 0.27, 0.24, 0.36, 0.9106, 0.0227, 0.0234,
    0.18, 0.27, 0.36, 0.48, 0.9597, 0.0254, 0.0103,
    0.18, 0.27, 0.48, 0.60, 0.9627, 0.0310, 0.0095,
    0.18, 0.27, 0.60, 0.72, 1.0454, 0.0439, 0.0111,
    0.18, 0.27, 0.72, 0.84, 1.0372, 0.0780, 0.0091,
    0.18, 0.27, 0.84, 0.96, 0.9524, 0.3124, 0.0122,
    0.18, 0.27, 0.96, 1.08, 1.0000, 0.0000, 0.0000,
    0.18, 0.27, 1.08, 1.20, 1.0000, 0.0000, 0.0000,
    0.27, 0.36, 0.00, 0.12, 0.8998, 0.0174, 0.0264,
    0.27, 0.36, 0.12, 0.24, 0.9025, 0.0180, 0.0256,
    0.27, 0.36, 0.24, 0.36, 0.9413, 0.0190, 0.0151,
    0.27, 0.36, 0.36, 0.48, 0.9325, 0.0202, 0.0175,
    0.27, 0.36, 0.48, 0.60, 1.0019, 0.0217, 0.0005,
    0.27, 0.36, 0.60, 0.72, 0.9839, 0.0241, 0.0041,
    0.27, 0.36, 0.72, 0.84, 1.0446, 0.0284, 0.0109,
    0.27, 0.36, 0.84, 0.96, 1.0689, 0.0373, 0.0167,
    0.27, 0.36, 0.96, 1.08, 1.1133, 0.0614, 0.0268,
    0.27, 0.36, 1.08, 1.20, 1.4839, 0.1643, 0.0974,
    0.36, 0.45, 0.00, 0.12, 0.8631, 0.0168, 0.0367,
    0.36, 0.45, 0.12, 0.24, 0.9075, 0.0171, 0.0242,
    0.36, 0.45, 0.24, 0.36, 0.9355, 0.0176, 0.0167,
    0.36, 0.45, 0.36, 0.48, 0.9156, 0.0180, 0.0220,
    0.36, 0.45, 0.48, 0.60, 0.9939, 0.0189, 0.0015,
    0.36, 0.45, 0.60, 0.72, 0.9958, 0.0200, 0.0011,
    0.36, 0.45, 0.72, 0.84, 1.0307, 0.0212, 0.0076,
    0.36, 0.45, 0.84, 0.96, 1.0393, 0.0234, 0.0096,
    0.36, 0.45, 0.96, 1.08, 1.0814, 0.0269, 0.0196,
    0.36, 0.45, 1.08, 1.20, 1.1714, 0.0340, 0.0395,
    0.45, 0.54, 0.00, 0.12, 0.8614, 0.0168, 0.0372,
    0.45, 0.54, 0.12, 0.24, 0.8918, 0.0172, 0.0286,
    0.45, 0.54, 0.24, 0.36, 0.9323, 0.0173, 0.0175,
    0.45, 0.54, 0.36, 0.48, 0.9334, 0.0177, 0.0172,
    0.45, 0.54, 0.48, 0.60, 0.9854, 0.0181, 0.0037,
    0.45, 0.54, 0.60, 0.72, 1.0355, 0.0187, 0.0087,
    0.45, 0.54, 0.72, 0.84, 1.0681, 0.0196, 0.0165,
    0.45, 0.54, 0.84, 0.96, 1.0995, 0.0205, 0.0237,
    0.45, 0.54, 0.96, 1.08, 1.1767, 0.0220, 0.0406,
    0.45, 0.54, 1.08, 1.20, 1.1668, 0.0240, 0.0385,
    0.54, 0.63, 0.00, 0.12, 0.8602, 0.0177, 0.0376,
    0.54, 0.63, 0.12, 0.24, 0.8994, 0.0179, 0.0265,
    0.54, 0.63, 0.24, 0.36, 0.9143, 0.0180, 0.0224,
    0.54, 0.63, 0.36, 0.48, 0.9598, 0.0183, 0.0103,
    0.54, 0.63, 0.48, 0.60, 0.9414, 0.0186, 0.0151,
    0.54, 0.63, 0.60, 0.72, 1.0177, 0.0190, 0.0044,
    0.54, 0.63, 0.72, 0.84, 1.0659, 0.0196, 0.0159,
    0.54, 0.63, 0.84, 0.96, 1.0853, 0.0201, 0.0205,
    0.54, 0.63, 0.96, 1.08, 1.1494, 0.0209, 0.0348,
    0.54, 0.63, 1.08, 1.20, 1.1394, 0.0223, 0.0326,
    0.63, 0.72, 0.00, 0.12, 0.8634, 0.0200, 0.0367,
    0.63, 0.72, 0.12, 0.24, 0.9052, 0.0201, 0.0249,
    0.63, 0.72, 0.24, 0.36, 0.9363, 0.0203, 0.0165,
    0.63, 0.72, 0.36, 0.48, 0.9603, 0.0204, 0.0101,
    0.63, 0.72, 0.48, 0.60, 0.9739, 0.0210, 0.0066,
    0.63, 0.72, 0.60, 0.72, 1.0334, 0.0213, 0.0082,
    0.63, 0.72, 0.72, 0.84, 1.0769, 0.0214, 0.0185,
    0.63, 0.72, 0.84, 0.96, 1.1028, 0.0224, 0.0244,
    0.63, 0.72, 0.96, 1.08, 1.0871, 0.0230, 0.0209,
    0.63, 0.72, 1.08, 1.20, 1.1291, 0.0240, 0.0303,
    0.72, 0.81, 0.00, 0.12, 0.9042, 0.0260, 0.0252,
    0.72, 0.81, 0.12, 0.24, 0.9072, 0.0259, 0.0243,
    0.72, 0.81, 0.24, 0.36, 0.9233, 0.0263, 0.0199,
    0.72, 0.81, 0.36, 0.48, 0.9393, 0.0269, 0.0156,
    0.72, 0.81, 0.48, 0.60, 0.9443, 0.0272, 0.0143,
    0.72, 0.81, 0.60, 0.72, 1.0073, 0.0278, 0.0018,
    0.72, 0.81, 0.72, 0.84, 1.0790, 0.0288, 0.0190,
    0.72, 0.81, 0.84, 0.96, 1.1137, 0.0293, 0.0269,
    0.72, 0.81, 0.96, 1.08, 1.0917, 0.0312, 0.0219,
    0.72, 0.81, 1.08, 1.20, 1.1830, 0.0331, 0.0419,
    0.81, 0.90, 0.00, 0.12, 1.0053, 0.0592, 0.0013,
    0.81, 0.90, 0.12, 0.24, 0.8333, 0.0621, 0.0455,
    0.81, 0.90, 0.24, 0.36, 0.8737, 0.0672, 0.0337,
    0.81, 0.90, 0.36, 0.48, 0.9274, 0.0698, 0.0188,
    0.81, 0.90, 0.48, 0.60, 0.9155, 0.0768, 0.0221,
    0.81, 0.90, 0.60, 0.72, 0.9686, 0.0842, 0.0080,
    0.81, 0.90, 0.72, 0.84, 0.9421, 0.0923, 0.0149,
    0.81, 0.90, 0.84, 0.96, 1.1950, 0.1075, 0.0444,
    0.81, 0.90, 0.96, 1.08, 1.3814, 0.1333, 0.0801,
    0.81, 0.90, 1.08, 1.20, 1.0000, 0.1873, 0.0000
};

// ----- D0___KStar_l_nu -----
// SLPOLE r_2 = 0.8, r_V = 1.6, M_A = 2.5 GeV, M_V = 2.1 GeV
const float SemiLepWeightsXc2D::f2DWeights22[] = {
    0.00, 0.07, 0.00, 0.11, 0.8461, 0.0337, 0.0417,
    0.00, 0.07, 0.11, 0.22, 0.7331, 0.0616, 0.0770,
    0.00, 0.07, 0.22, 0.33, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.33, 0.44, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.44, 0.55, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.55, 0.66, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.66, 0.77, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.77, 0.88, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.00, 0.11, 0.9808, 0.0207, 0.0049,
    0.07, 0.14, 0.11, 0.22, 0.8367, 0.0203, 0.0445,
    0.07, 0.14, 0.22, 0.33, 0.8112, 0.0248, 0.0521,
    0.07, 0.14, 0.33, 0.44, 0.8525, 0.0713, 0.0398,
    0.07, 0.14, 0.44, 0.55, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.55, 0.66, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.66, 0.77, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.77, 0.88, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.00, 0.11, 1.0696, 0.0189, 0.0168,
    0.14, 0.21, 0.11, 0.22, 0.9265, 0.0178, 0.0191,
    0.14, 0.21, 0.22, 0.33, 0.8652, 0.0166, 0.0361,
    0.14, 0.21, 0.33, 0.44, 0.8380, 0.0169, 0.0441,
    0.14, 0.21, 0.44, 0.55, 0.8053, 0.0267, 0.0539,
    0.14, 0.21, 0.55, 0.66, 1.0465, 0.2133, 0.0114,
    0.14, 0.21, 0.66, 0.77, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.77, 0.88, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.00, 0.11, 1.1286, 0.0192, 0.0302,
    0.21, 0.28, 0.11, 0.22, 1.0200, 0.0174, 0.0049,
    0.21, 0.28, 0.22, 0.33, 0.9287, 0.0162, 0.0185,
    0.21, 0.28, 0.33, 0.44, 0.9066, 0.0153, 0.0245,
    0.21, 0.28, 0.44, 0.55, 0.8782, 0.0148, 0.0324,
    0.21, 0.28, 0.55, 0.66, 0.8850, 0.0183, 0.0305,
    0.21, 0.28, 0.66, 0.77, 0.8141, 0.0529, 0.0512,
    0.21, 0.28, 0.77, 0.88, 1.3333, 0.7638, 0.0714,
    0.21, 0.28, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.28, 0.35, 0.00, 0.11, 1.1319, 0.0195, 0.0309,
    0.28, 0.35, 0.11, 0.22, 1.0465, 0.0178, 0.0114,
    0.28, 0.35, 0.22, 0.33, 1.0047, 0.0166, 0.0012,
    0.28, 0.35, 0.33, 0.44, 0.9835, 0.0156, 0.0042,
    0.28, 0.35, 0.44, 0.55, 0.9545, 0.0149, 0.0116,
    0.28, 0.35, 0.55, 0.66, 0.9272, 0.0143, 0.0189,
    0.28, 0.35, 0.66, 0.77, 0.9182, 0.0158, 0.0213,
    0.28, 0.35, 0.77, 0.88, 0.9810, 0.0351, 0.0048,
    0.28, 0.35, 0.88, 0.99, 1.2759, 0.2480, 0.0606,
    0.28, 0.35, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.35, 0.42, 0.00, 0.11, 1.1757, 0.0205, 0.0404,
    0.35, 0.42, 0.11, 0.22, 1.0372, 0.0186, 0.0091,
    0.35, 0.42, 0.22, 0.33, 1.0291, 0.0175, 0.0072,
    0.35, 0.42, 0.33, 0.44, 0.9963, 0.0165, 0.0009,
    0.35, 0.42, 0.44, 0.55, 0.9594, 0.0157, 0.0104,
    0.35, 0.42, 0.55, 0.66, 0.9644, 0.0149, 0.0091,
    0.35, 0.42, 0.66, 0.77, 0.9657, 0.0147, 0.0087,
    0.35, 0.42, 0.77, 0.88, 0.9663, 0.0163, 0.0086,
    0.35, 0.42, 0.88, 0.99, 0.9461, 0.0382, 0.0139,
    0.35, 0.42, 0.99, 1.10, 1.0556, 0.1645, 0.0135,
    0.42, 0.49, 0.00, 0.11, 1.1950, 0.0219, 0.0444,
    0.42, 0.49, 0.11, 0.22, 1.1032, 0.0202, 0.0245,
    0.42, 0.49, 0.22, 0.33, 1.0790, 0.0192, 0.0190,
    0.42, 0.49, 0.33, 0.44, 1.0295, 0.0180, 0.0073,
    0.42, 0.49, 0.44, 0.55, 1.0297, 0.0172, 0.0073,
    0.42, 0.49, 0.55, 0.66, 1.0211, 0.0165, 0.0052,
    0.42, 0.49, 0.66, 0.77, 1.0438, 0.0160, 0.0107,
    0.42, 0.49, 0.77, 0.88, 1.0384, 0.0160, 0.0094,
    0.42, 0.49, 0.88, 0.99, 1.0192, 0.0219, 0.0048,
    0.42, 0.49, 0.99, 1.10, 1.0568, 0.0628, 0.0138,
    0.49, 0.56, 0.00, 0.11, 1.1755, 0.0246, 0.0403,
    0.49, 0.56, 0.11, 0.22, 1.1026, 0.0230, 0.0244,
    0.49, 0.56, 0.22, 0.33, 1.1176, 0.0220, 0.0278,
    0.49, 0.56, 0.33, 0.44, 1.0581, 0.0207, 0.0141,
    0.49, 0.56, 0.44, 0.55, 1.0691, 0.0198, 0.0167,
    0.49, 0.56, 0.55, 0.66, 1.0677, 0.0191, 0.0164,
    0.49, 0.56, 0.66, 0.77, 1.0640, 0.0187, 0.0155,
    0.49, 0.56, 0.77, 0.88, 1.0637, 0.0191, 0.0154,
    0.49, 0.56, 0.88, 0.99, 1.1416, 0.0254, 0.0331,
    0.49, 0.56, 0.99, 1.10, 1.1257, 0.0586, 0.0296,
    0.56, 0.63, 0.00, 0.11, 1.1495, 0.0299, 0.0348,
    0.56, 0.63, 0.11, 0.22, 1.1905, 0.0284, 0.0435,
    0.56, 0.63, 0.22, 0.33, 1.1186, 0.0271, 0.0280,
    0.56, 0.63, 0.33, 0.44, 1.0847, 0.0261, 0.0203,
    0.56, 0.63, 0.44, 0.55, 1.1408, 0.0254, 0.0329,
    0.56, 0.63, 0.55, 0.66, 1.0993, 0.0250, 0.0237,
    0.56, 0.63, 0.66, 0.77, 1.1250, 0.0258, 0.0294,
    0.56, 0.63, 0.77, 0.88, 1.0865, 0.0317, 0.0207,
    0.56, 0.63, 0.88, 0.99, 1.0871, 0.0546, 0.0209,
    0.56, 0.63, 0.99, 1.10, 1.1813, 0.1039, 0.0416,
    0.63, 0.70, 0.00, 0.11, 1.1114, 0.0453, 0.0264,
    0.63, 0.70, 0.11, 0.22, 1.1733, 0.0436, 0.0399,
    0.63, 0.70, 0.22, 0.33, 1.1481, 0.0426, 0.0345,
    0.63, 0.70, 0.33, 0.44, 1.1646, 0.0443, 0.0380,
    0.63, 0.70, 0.44, 0.55, 1.1939, 0.0473, 0.0442,
    0.63, 0.70, 0.55, 0.66, 1.2182, 0.0571, 0.0492,
    0.63, 0.70, 0.66, 0.77, 0.9492, 0.0834, 0.0130,
    0.63, 0.70, 0.77, 0.88, 1.0234, 0.1243, 0.0058,
    0.63, 0.70, 0.88, 0.99, 1.0000, 0.1873, 0.0000,
    0.63, 0.70, 0.99, 1.10, 1.5000, 0.2635, 0.1000
};

// ----- D___K_l_nu -----
// SLBKPOLE with alpha = 0.22
const float SemiLepWeightsXc2D::f2DWeights23[] = {
    0.00, 0.09, 0.00, 0.12, 0.8531, 0.0461, 0.0396,
    0.00, 0.09, 0.12, 0.24, 0.8882, 0.0824, 0.0296,
    0.00, 0.09, 0.24, 0.36, 0.5500, 0.3754, 0.1452,
    0.00, 0.09, 0.36, 0.48, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.48, 0.60, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.60, 0.72, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.72, 0.84, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.84, 0.96, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 0.96, 1.08, 1.0000, 0.0000, 0.0000,
    0.00, 0.09, 1.08, 1.20, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.00, 0.12, 0.8852, 0.0242, 0.0305,
    0.09, 0.18, 0.12, 0.24, 0.8900, 0.0280, 0.0291,
    0.09, 0.18, 0.24, 0.36, 0.9479, 0.0368, 0.0134,
    0.09, 0.18, 0.36, 0.48, 1.0509, 0.0566, 0.0124,
    0.09, 0.18, 0.48, 0.60, 0.6667, 0.1409, 0.1000,
    0.09, 0.18, 0.60, 0.72, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.72, 0.84, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.84, 0.96, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 0.96, 1.08, 1.0000, 0.0000, 0.0000,
    0.09, 0.18, 1.08, 1.20, 1.0000, 0.0000, 0.0000,
    0.18, 0.27, 0.00, 0.12, 0.8644, 0.0193, 0.0364,
    0.18, 0.27, 0.12, 0.24, 0.9230, 0.0207, 0.0200,
    0.18, 0.27, 0.24, 0.36, 0.9527, 0.0227, 0.0121,
    0.18, 0.27, 0.36, 0.48, 0.9354, 0.0257, 0.0167,
    0.18, 0.27, 0.48, 0.60, 0.9841, 0.0312, 0.0040,
    0.18, 0.27, 0.60, 0.72, 1.0362, 0.0445, 0.0089,
    0.18, 0.27, 0.72, 0.84, 1.1062, 0.0808, 0.0252,
    0.18, 0.27, 0.84, 0.96, 0.7826, 0.3147, 0.0610,
    0.18, 0.27, 0.96, 1.08, 1.0000, 0.0000, 0.0000,
    0.18, 0.27, 1.08, 1.20, 1.0000, 0.0000, 0.0000,
    0.27, 0.36, 0.00, 0.12, 0.8764, 0.0176, 0.0329,
    0.27, 0.36, 0.12, 0.24, 0.8997, 0.0181, 0.0264,
    0.27, 0.36, 0.24, 0.36, 0.9400, 0.0192, 0.0155,
    0.27, 0.36, 0.36, 0.48, 0.9553, 0.0204, 0.0114,
    0.27, 0.36, 0.48, 0.60, 0.9969, 0.0219, 0.0008,
    0.27, 0.36, 0.60, 0.72, 1.0317, 0.0242, 0.0078,
    0.27, 0.36, 0.72, 0.84, 1.0250, 0.0280, 0.0062,
    0.27, 0.36, 0.84, 0.96, 1.1067, 0.0364, 0.0253,
    0.27, 0.36, 0.96, 1.08, 1.0450, 0.0606, 0.0110,
    0.27, 0.36, 1.08, 1.20, 0.9639, 0.1567, 0.0092,
    0.36, 0.45, 0.00, 0.12, 0.8735, 0.0169, 0.0338,
    0.36, 0.45, 0.12, 0.24, 0.8869, 0.0172, 0.0300,
    0.36, 0.45, 0.24, 0.36, 0.9103, 0.0177, 0.0235,
    0.36, 0.45, 0.36, 0.48, 0.9598, 0.0183, 0.0103,
    0.36, 0.45, 0.48, 0.60, 0.9703, 0.0191, 0.0075,
    0.36, 0.45, 0.60, 0.72, 1.0175, 0.0200, 0.0043,
    0.36, 0.45, 0.72, 0.84, 1.0442, 0.0214, 0.0108,
    0.36, 0.45, 0.84, 0.96, 1.1018, 0.0237, 0.0242,
    0.36, 0.45, 0.96, 1.08, 1.1131, 0.0270, 0.0268,
    0.36, 0.45, 1.08, 1.20, 1.1365, 0.0345, 0.0320,
    0.45, 0.54, 0.00, 0.12, 0.8967, 0.0168, 0.0272,
    0.45, 0.54, 0.12, 0.24, 0.8958, 0.0171, 0.0275,
    0.45, 0.54, 0.24, 0.36, 0.9095, 0.0175, 0.0237,
    0.45, 0.54, 0.36, 0.48, 0.9439, 0.0177, 0.0144,
    0.45, 0.54, 0.48, 0.60, 0.9634, 0.0181, 0.0093,
    0.45, 0.54, 0.60, 0.72, 1.0447, 0.0189, 0.0109,
    0.45, 0.54, 0.72, 0.84, 1.0365, 0.0194, 0.0090,
    0.45, 0.54, 0.84, 0.96, 1.0856, 0.0205, 0.0205,
    0.45, 0.54, 0.96, 1.08, 1.1209, 0.0222, 0.0285,
    0.45, 0.54, 1.08, 1.20, 1.1638, 0.0242, 0.0379,
    0.54, 0.63, 0.00, 0.12, 0.8918, 0.0177, 0.0286,
    0.54, 0.63, 0.12, 0.24, 0.8923, 0.0180, 0.0285,
    0.54, 0.63, 0.24, 0.36, 0.9310, 0.0181, 0.0179,
    0.54, 0.63, 0.36, 0.48, 0.9639, 0.0183, 0.0092,
    0.54, 0.63, 0.48, 0.60, 1.0106, 0.0188, 0.0026,
    0.54, 0.63, 0.60, 0.72, 1.0240, 0.0192, 0.0059,
    0.54, 0.63, 0.72, 0.84, 1.0800, 0.0196, 0.0192,
    0.54, 0.63, 0.84, 0.96, 1.0978, 0.0202, 0.0233,
    0.54, 0.63, 0.96, 1.08, 1.0814, 0.0211, 0.0195,
    0.54, 0.63, 1.08, 1.20, 1.1948, 0.0225, 0.0444,
    0.63, 0.72, 0.00, 0.12, 0.9017, 0.0201, 0.0259,
    0.63, 0.72, 0.12, 0.24, 0.9342, 0.0200, 0.0170,
    0.63, 0.72, 0.24, 0.36, 0.9436, 0.0202, 0.0145,
    0.63, 0.72, 0.36, 0.48, 0.9471, 0.0203, 0.0136,
    0.63, 0.72, 0.48, 0.60, 0.9612, 0.0208, 0.0099,
    0.63, 0.72, 0.60, 0.72, 0.9967, 0.0211, 0.0008,
    0.63, 0.72, 0.72, 0.84, 1.0567, 0.0215, 0.0138,
    0.63, 0.72, 0.84, 0.96, 1.0680, 0.0223, 0.0164,
    0.63, 0.72, 0.96, 1.08, 1.1472, 0.0229, 0.0343,
    0.63, 0.72, 1.08, 1.20, 1.1676, 0.0240, 0.0387,
    0.72, 0.81, 0.00, 0.12, 0.8972, 0.0258, 0.0271,
    0.72, 0.81, 0.12, 0.24, 0.8752, 0.0263, 0.0333,
    0.72, 0.81, 0.24, 0.36, 0.9631, 0.0264, 0.0094,
    0.72, 0.81, 0.36, 0.48, 0.9561, 0.0269, 0.0112,
    0.72, 0.81, 0.48, 0.60, 0.9614, 0.0273, 0.0098,
    0.72, 0.81, 0.60, 0.72, 0.9531, 0.0281, 0.0120,
    0.72, 0.81, 0.72, 0.84, 1.0762, 0.0287, 0.0183,
    0.72, 0.81, 0.84, 0.96, 1.1319, 0.0296, 0.0309,
    0.72, 0.81, 0.96, 1.08, 1.1257, 0.0306, 0.0296,
    0.72, 0.81, 1.08, 1.20, 1.1192, 0.0335, 0.0281,
    0.81, 0.90, 0.00, 0.12, 0.8786, 0.0570, 0.0323,
    0.81, 0.90, 0.12, 0.24, 0.9418, 0.0612, 0.0150,
    0.81, 0.90, 0.24, 0.36, 1.0779, 0.0646, 0.0188,
    0.81, 0.90, 0.36, 0.48, 0.8835, 0.0672, 0.0309,
    0.81, 0.90, 0.48, 0.60, 1.0239, 0.0725, 0.0059,
    0.81, 0.90, 0.60, 0.72, 1.0400, 0.0809, 0.0098,
    0.81, 0.90, 0.72, 0.84, 1.0837, 0.0897, 0.0201,
    0.81, 0.90, 0.84, 0.96, 1.0652, 0.1026, 0.0158,
    0.81, 0.90, 0.96, 1.08, 1.0948, 0.1284, 0.0226,
    0.81, 0.90, 1.08, 1.20, 1.0597, 0.1703, 0.0145
};

// ----- D___KStar_l_nu -----
// SLPOLE r_2 = 0.8, r_V = 1.6, M_A = 2.5 GeV, M_V = 2.1 GeV
const float SemiLepWeightsXc2D::f2DWeights24[] = {
    0.00, 0.07, 0.00, 0.11, 0.8828, 0.0345, 0.0311,
    0.00, 0.07, 0.11, 0.22, 0.8155, 0.0600, 0.0508,
    0.00, 0.07, 0.22, 0.33, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.33, 0.44, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.44, 0.55, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.55, 0.66, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.66, 0.77, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.77, 0.88, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.00, 0.11, 0.9813, 0.0211, 0.0047,
    0.07, 0.14, 0.11, 0.22, 0.8567, 0.0202, 0.0386,
    0.07, 0.14, 0.22, 0.33, 0.8048, 0.0248, 0.0541,
    0.07, 0.14, 0.33, 0.44, 0.7891, 0.0688, 0.0589,
    0.07, 0.14, 0.44, 0.55, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.55, 0.66, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.66, 0.77, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.77, 0.88, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.00, 0.11, 1.0669, 0.0190, 0.0162,
    0.14, 0.21, 0.11, 0.22, 0.9340, 0.0179, 0.0171,
    0.14, 0.21, 0.22, 0.33, 0.8634, 0.0167, 0.0367,
    0.14, 0.21, 0.33, 0.44, 0.8290, 0.0171, 0.0467,
    0.14, 0.21, 0.44, 0.55, 0.8584, 0.0272, 0.0381,
    0.14, 0.21, 0.55, 0.66, 1.2162, 0.2219, 0.0488,
    0.14, 0.21, 0.66, 0.77, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.77, 0.88, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.00, 0.11, 1.1235, 0.0192, 0.0291,
    0.21, 0.28, 0.11, 0.22, 1.0109, 0.0174, 0.0027,
    0.21, 0.28, 0.22, 0.33, 0.9330, 0.0163, 0.0173,
    0.21, 0.28, 0.33, 0.44, 0.8954, 0.0155, 0.0276,
    0.21, 0.28, 0.44, 0.55, 0.8795, 0.0148, 0.0320,
    0.21, 0.28, 0.55, 0.66, 0.8838, 0.0183, 0.0309,
    0.21, 0.28, 0.66, 0.77, 0.8170, 0.0523, 0.0504,
    0.21, 0.28, 0.77, 0.88, 0.6667, 0.9129, 0.1000,
    0.21, 0.28, 0.88, 0.99, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.28, 0.35, 0.00, 0.11, 1.1237, 0.0197, 0.0291,
    0.28, 0.35, 0.11, 0.22, 1.0406, 0.0178, 0.0100,
    0.28, 0.35, 0.22, 0.33, 0.9727, 0.0167, 0.0069,
    0.28, 0.35, 0.33, 0.44, 0.9660, 0.0157, 0.0086,
    0.28, 0.35, 0.44, 0.55, 0.9209, 0.0148, 0.0206,
    0.28, 0.35, 0.55, 0.66, 0.9125, 0.0145, 0.0229,
    0.28, 0.35, 0.66, 0.77, 0.8915, 0.0158, 0.0287,
    0.28, 0.35, 0.77, 0.88, 0.9044, 0.0352, 0.0251,
    0.28, 0.35, 0.88, 0.99, 1.1316, 0.2226, 0.0309,
    0.28, 0.35, 0.99, 1.10, 1.0000, 0.0000, 0.0000,
    0.35, 0.42, 0.00, 0.11, 1.1362, 0.0204, 0.0319,
    0.35, 0.42, 0.11, 0.22, 1.0921, 0.0189, 0.0220,
    0.35, 0.42, 0.22, 0.33, 1.0417, 0.0176, 0.0102,
    0.35, 0.42, 0.33, 0.44, 0.9884, 0.0165, 0.0029,
    0.35, 0.42, 0.44, 0.55, 1.0033, 0.0156, 0.0008,
    0.35, 0.42, 0.55, 0.66, 0.9669, 0.0150, 0.0084,
    0.35, 0.42, 0.66, 0.77, 0.9668, 0.0147, 0.0084,
    0.35, 0.42, 0.77, 0.88, 0.9512, 0.0162, 0.0125,
    0.35, 0.42, 0.88, 0.99, 0.9354, 0.0369, 0.0167,
    0.35, 0.42, 0.99, 1.10, 0.7128, 0.1599, 0.0839,
    0.42, 0.49, 0.00, 0.11, 1.1252, 0.0217, 0.0295,
    0.42, 0.49, 0.11, 0.22, 1.0955, 0.0202, 0.0228,
    0.42, 0.49, 0.22, 0.33, 1.0740, 0.0191, 0.0178,
    0.42, 0.49, 0.33, 0.44, 1.0309, 0.0182, 0.0076,
    0.42, 0.49, 0.44, 0.55, 1.0891, 0.0173, 0.0213,
    0.42, 0.49, 0.55, 0.66, 1.0280, 0.0163, 0.0069,
    0.42, 0.49, 0.66, 0.77, 1.0231, 0.0159, 0.0057,
    0.42, 0.49, 0.77, 0.88, 1.0187, 0.0159, 0.0046,
    0.42, 0.49, 0.88, 0.99, 0.9968, 0.0215, 0.0008,
    0.42, 0.49, 0.99, 1.10, 1.1876, 0.0627, 0.0429,
    0.49, 0.56, 0.00, 0.11, 1.1461, 0.0243, 0.0340,
    0.49, 0.56, 0.11, 0.22, 1.1093, 0.0230, 0.0259,
    0.49, 0.56, 0.22, 0.33, 1.1372, 0.0221, 0.0321,
    0.49, 0.56, 0.33, 0.44, 1.0785, 0.0207, 0.0189,
    0.49, 0.56, 0.44, 0.55, 1.1136, 0.0199, 0.0269,
    0.49, 0.56, 0.55, 0.66, 1.0824, 0.0192, 0.0198,
    0.49, 0.56, 0.66, 0.77, 1.0476, 0.0186, 0.0116,
    0.49, 0.56, 0.77, 0.88, 1.0712, 0.0190, 0.0172,
    0.49, 0.56, 0.88, 0.99, 1.0720, 0.0249, 0.0174,
    0.49, 0.56, 0.99, 1.10, 1.0122, 0.0589, 0.0030,
    0.56, 0.63, 0.00, 0.11, 1.2011, 0.0301, 0.0457,
    0.56, 0.63, 0.11, 0.22, 1.0858, 0.0286, 0.0206,
    0.56, 0.63, 0.22, 0.33, 1.1317, 0.0270, 0.0309,
    0.56, 0.63, 0.33, 0.44, 1.1294, 0.0260, 0.0304,
    0.56, 0.63, 0.44, 0.55, 1.0808, 0.0253, 0.0194,
    0.56, 0.63, 0.55, 0.66, 1.1207, 0.0248, 0.0285,
    0.56, 0.63, 0.66, 0.77, 1.1004, 0.0258, 0.0239,
    0.56, 0.63, 0.77, 0.88, 1.1017, 0.0316, 0.0242,
    0.56, 0.63, 0.88, 0.99, 1.1024, 0.0540, 0.0244,
    0.56, 0.63, 0.99, 1.10, 0.9347, 0.1020, 0.0169,
    0.63, 0.70, 0.00, 0.11, 1.1255, 0.0443, 0.0295,
    0.63, 0.70, 0.11, 0.22, 1.1765, 0.0437, 0.0405,
    0.63, 0.70, 0.22, 0.33, 1.2150, 0.0442, 0.0485,
    0.63, 0.70, 0.33, 0.44, 1.1269, 0.0434, 0.0298,
    0.63, 0.70, 0.44, 0.55, 1.0419, 0.0465, 0.0102,
    0.63, 0.70, 0.55, 0.66, 1.1434, 0.0569, 0.0334,
    0.63, 0.70, 0.66, 0.77, 1.1776, 0.0845, 0.0408,
    0.63, 0.70, 0.77, 0.88, 1.1000, 0.1212, 0.0238,
    0.63, 0.70, 0.88, 0.99, 1.1250, 0.1837, 0.0294,
    0.63, 0.70, 0.99, 1.10, 1.3478, 0.2752, 0.0741
};

//----- Ds__phi_l_nu -----
// SLPOLE r_2 = 0.8, r_V = 1.8, M_A = 2.28 GeV, M_V = 2.1 GeV
const float SemiLepWeightsXc2D::f2DWeights25[] = {
    0.00, 0.07, 0.00, 0.10, 0.8729, 0.0603, 0.0339,
    0.00, 0.07, 0.10, 0.20, 0.7163, 0.0753, 0.0826,
    0.00, 0.07, 0.20, 0.30, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.30, 0.40, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.40, 0.50, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.50, 0.60, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.60, 0.70, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.70, 0.80, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.80, 0.90, 1.0000, 0.0000, 0.0000,
    0.00, 0.07, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.00, 0.10, 0.9615, 0.0405, 0.0098,
    0.07, 0.14, 0.10, 0.20, 0.8982, 0.0328, 0.0268,
    0.07, 0.14, 0.20, 0.30, 0.7883, 0.0334, 0.0592,
    0.07, 0.14, 0.30, 0.40, 0.8284, 0.0604, 0.0469,
    0.07, 0.14, 0.40, 0.50, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.50, 0.60, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.60, 0.70, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.70, 0.80, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.80, 0.90, 1.0000, 0.0000, 0.0000,
    0.07, 0.14, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.00, 0.10, 1.1312, 0.0352, 0.0308,
    0.14, 0.21, 0.10, 0.20, 1.0081, 0.0299, 0.0020,
    0.14, 0.21, 0.20, 0.30, 0.8806, 0.0264, 0.0317,
    0.14, 0.21, 0.30, 0.40, 0.8163, 0.0241, 0.0506,
    0.14, 0.21, 0.40, 0.50, 0.8150, 0.0287, 0.0510,
    0.14, 0.21, 0.50, 0.60, 1.0035, 0.0836, 0.0009,
    0.14, 0.21, 0.60, 0.70, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.70, 0.80, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.80, 0.90, 1.0000, 0.0000, 0.0000,
    0.14, 0.21, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.00, 0.10, 1.1342, 0.0329, 0.0314,
    0.21, 0.28, 0.10, 0.20, 1.0179, 0.0287, 0.0044,
    0.21, 0.28, 0.20, 0.30, 0.9402, 0.0263, 0.0154,
    0.21, 0.28, 0.30, 0.40, 0.8938, 0.0239, 0.0280,
    0.21, 0.28, 0.40, 0.50, 0.8979, 0.0217, 0.0269,
    0.21, 0.28, 0.50, 0.60, 0.9017, 0.0214, 0.0258,
    0.21, 0.28, 0.60, 0.70, 0.8219, 0.0372, 0.0489,
    0.21, 0.28, 0.70, 0.80, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.80, 0.90, 1.0000, 0.0000, 0.0000,
    0.21, 0.28, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.28, 0.35, 0.00, 0.10, 1.1329, 0.0320, 0.0311,
    0.28, 0.35, 0.10, 0.20, 1.0527, 0.0290, 0.0128,
    0.28, 0.35, 0.20, 0.30, 1.0168, 0.0264, 0.0042,
    0.28, 0.35, 0.30, 0.40, 0.9758, 0.0244, 0.0061,
    0.28, 0.35, 0.40, 0.50, 0.9281, 0.0224, 0.0186,
    0.28, 0.35, 0.50, 0.60, 0.9551, 0.0209, 0.0115,
    0.28, 0.35, 0.60, 0.70, 0.9387, 0.0195, 0.0158,
    0.28, 0.35, 0.70, 0.80, 0.9206, 0.0271, 0.0207,
    0.28, 0.35, 0.80, 0.90, 0.4667, 0.4577, 0.1818,
    0.28, 0.35, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.35, 0.42, 0.00, 0.10, 1.0526, 0.0319, 0.0128,
    0.35, 0.42, 0.10, 0.20, 1.0496, 0.0289, 0.0121,
    0.35, 0.42, 0.20, 0.30, 1.0399, 0.0274, 0.0098,
    0.35, 0.42, 0.30, 0.40, 1.0296, 0.0252, 0.0073,
    0.35, 0.42, 0.40, 0.50, 0.9942, 0.0236, 0.0015,
    0.35, 0.42, 0.50, 0.60, 0.9566, 0.0220, 0.0111,
    0.35, 0.42, 0.60, 0.70, 0.9800, 0.0206, 0.0051,
    0.35, 0.42, 0.70, 0.80, 0.9688, 0.0196, 0.0079,
    0.35, 0.42, 0.80, 0.90, 0.9673, 0.0290, 0.0083,
    0.35, 0.42, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.42, 0.49, 0.00, 0.10, 1.0782, 0.0329, 0.0188,
    0.42, 0.49, 0.10, 0.20, 1.1220, 0.0309, 0.0288,
    0.42, 0.49, 0.20, 0.30, 1.0805, 0.0290, 0.0194,
    0.42, 0.49, 0.30, 0.40, 1.0498, 0.0273, 0.0122,
    0.42, 0.49, 0.40, 0.50, 1.0901, 0.0259, 0.0216,
    0.42, 0.49, 0.50, 0.60, 1.0630, 0.0243, 0.0153,
    0.42, 0.49, 0.60, 0.70, 1.0275, 0.0227, 0.0068,
    0.42, 0.49, 0.70, 0.80, 0.9928, 0.0216, 0.0018,
    0.42, 0.49, 0.80, 0.90, 0.9916, 0.0217, 0.0021,
    0.42, 0.49, 0.90, 1.00, 1.0938, 0.1729, 0.0224,
    0.49, 0.56, 0.00, 0.10, 1.1548, 0.0359, 0.0359,
    0.49, 0.56, 0.10, 0.20, 1.1059, 0.0343, 0.0251,
    0.49, 0.56, 0.20, 0.30, 1.1896, 0.0330, 0.0433,
    0.49, 0.56, 0.30, 0.40, 1.0657, 0.0310, 0.0159,
    0.49, 0.56, 0.40, 0.50, 1.0567, 0.0290, 0.0138,
    0.49, 0.56, 0.50, 0.60, 1.1066, 0.0273, 0.0253,
    0.49, 0.56, 0.60, 0.70, 1.0596, 0.0263, 0.0145,
    0.49, 0.56, 0.70, 0.80, 1.0666, 0.0251, 0.0161,
    0.49, 0.56, 0.80, 0.90, 1.0699, 0.0285, 0.0169,
    0.49, 0.56, 0.90, 1.00, 1.4118, 0.3170, 0.0854,
    0.56, 0.63, 0.00, 0.10, 1.0991, 0.0433, 0.0236,
    0.56, 0.63, 0.10, 0.20, 1.0798, 0.0411, 0.0192,
    0.56, 0.63, 0.20, 0.30, 1.1000, 0.0389, 0.0238,
    0.56, 0.63, 0.30, 0.40, 1.1028, 0.0380, 0.0244,
    0.56, 0.63, 0.40, 0.50, 1.1467, 0.0355, 0.0342,
    0.56, 0.63, 0.50, 0.60, 1.1194, 0.0337, 0.0282,
    0.56, 0.63, 0.60, 0.70, 1.1299, 0.0344, 0.0305,
    0.56, 0.63, 0.70, 0.80, 1.1663, 0.0424, 0.0384,
    0.56, 0.63, 0.80, 0.90, 1.0495, 0.1391, 0.0121,
    0.56, 0.63, 0.90, 1.00, 1.0000, 0.0000, 0.0000,
    0.63, 0.70, 0.00, 0.10, 1.2186, 0.0628, 0.0493,
    0.63, 0.70, 0.10, 0.20, 1.1591, 0.0620, 0.0368,
    0.63, 0.70, 0.20, 0.30, 1.2407, 0.0612, 0.0537,
    0.63, 0.70, 0.30, 0.40, 1.0532, 0.0631, 0.0129,
    0.63, 0.70, 0.40, 0.50, 1.1655, 0.0668, 0.0382,
    0.63, 0.70, 0.50, 0.60, 1.2944, 0.0949, 0.0642,
    0.63, 0.70, 0.60, 0.70, 1.2857, 0.3563, 0.0625,
    0.63, 0.70, 0.70, 0.80, 1.0000, 0.0000, 0.0000,
    0.63, 0.70, 0.80, 0.90, 1.0000, 0.0000, 0.0000,
    0.63, 0.70, 0.90, 1.00, 1.0000, 0.0000, 0.0000
};
