#ifndef DWEIGHTSPARAM
#define DWEIGHTSPARAM
#include "../../Dss/BF/FFCorrClass.h"
#include "SemiLepWeights2D_Donly.h"

//wrapper class
class DWeightsParam: public FFCorrClass{

public:
	virtual double reweight(uint iBin){
		
		if(dict[iBin] > -1)
			return 1. + dict[iBin]*par;
		else {
		
			dict[iBin] = s.getRelError(iBin);
			return 1. + dict[iBin]*par; 
		}
	
	}
	virtual double reweight(uint, uint){};
	
	DWeightsParam(int nBins, string name): s(SemiLepWeights2D(nBins,name.c_str())){
		
		dict = new double[nBins];
		for(int i = 0; i<nBins; i++)
			dict[i] = -10;
	
	};
	
	void SetPar(double p){par = p;};
	
	float weight(float w_t, float CosTh_t, float q2_t, float LepMom_t, int iVarBin=0){
		return s.weight(2, w_t, CosTh_t, q2_t, LepMom_t, iVarBin);
	};
	
	
private:

	double par;
	SemiLepWeights2D s;
	double *dict;

};

#endif
