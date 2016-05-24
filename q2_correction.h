// Jan Hasenbusch
// 04.02.2013
//source: Phill for D*
//source: CKM Page/xcmodel for D**

    enum{NoDmeson,
        Dmeson,
	    Dpi,
        Dstar,
	    Dstarpi,
        D1,
        D2star,
        Dstar0,
        Dp1,
        D_2S,
        Dstar_2S,
        D_s,
        otherXc
    };			


TH1F *q2_tmp;
TH1F *q2test;
TH1F *q2test1;
TH1F *q2test2;
TH1F *q2test3;
TH1F *q2test4;
TH1F *q2test5;
TH1F *q2test6;

TH1F *q2testd;
TH1F *q2test1d;
TH1F *q2test2d;

void InitQ2()
{
	TFile *f1;

	f1 = new TFile("~/work/bctaunu/shared/q2_weights.root");
	q2test = (TH1F*)((TH1F*)gDirectory->Get("q2test"))->Clone();
	q2test ->SetDirectory(0);

	q2test1 = (TH1F*)((TH1F*)gDirectory->Get("q2test1"))->Clone();
	q2test1 ->SetDirectory(0);

	q2test2 = (TH1F*)((TH1F*)gDirectory->Get("q2test2"))->Clone();
	q2test2 ->SetDirectory(0);

	q2test3 = (TH1F*)((TH1F*)gDirectory->Get("q2test3"))->Clone();
	q2test3 ->SetDirectory(0);

	q2test4 = (TH1F*)((TH1F*)gDirectory->Get("q2test4"))->Clone();
	q2test4 ->SetDirectory(0);

	q2test5 = (TH1F*)((TH1F*)gDirectory->Get("q2test5"))->Clone();
	q2test5 ->SetDirectory(0);

	q2test6 = (TH1F*)((TH1F*)gDirectory->Get("q2test6"))->Clone();
	q2test6 ->SetDirectory(0);

	q2testd = (TH1F*)((TH1F*)gDirectory->Get("q2testd"))->Clone();
	q2testd ->SetDirectory(0);

	q2test1d = (TH1F*)((TH1F*)gDirectory->Get("q2test1d"))->Clone();
	q2test1d ->SetDirectory(0);

	q2test2d = (TH1F*)((TH1F*)gDirectory->Get("q2test2d"))->Clone();
	q2test2d ->SetDirectory(0);

	f1->Close();
	f1->Delete();

}


//#ifndef NOQ2COR
//	std::cout<<"----------------\n"
//	<<"init shape corrections\n"
//	std::cout<<"----------------"<<std::endl;
	//InitQ2();
//#else
//	std::cout<<"----------------\n"
//	<<"shape corrections NOT available!\n"
//	std::cout<<"----------------"<<std::endl;
//#endif



//D**

//D1lnu
float ff3_central[] = {
          0.788, 
          0.805, 
          0.855, 
          0.933, 
          0.974, 
          1.021, 
          1.084, 
          1.180, 
          1.146, 
          1.248, 
          1.255, 
          1.298, 
          1.247, 
          1.297, 
          1.385, 
          1.369, 
          0.000, 
          1.000, 
          1.000, 
          1.000, 
          1.000, 
          1.000}; 

float ff3_lower[] = {
          0.663,
          0.709,
          0.784,
          0.886,
          0.954,
          1.028,
          1.118,
          1.244,
          1.233,
          1.367,
          1.398,
          1.468,
          1.432,
          1.512,
          1.641,
          1.650,
          0.000,
          1.000,
          1.000,
          1.000,
          1.000,
          1.000};

float ff3_upper[] = {
          0.913,
          0.900,
          0.926,
          0.980,
          0.994,
          1.015,
          1.050,
          1.116,
          1.060,
          1.129,
          1.112,
          1.127,
          1.061,
          1.081,
          1.130,
          1.088,
          0.000,
          1.000,
          1.000,
          1.000,
          1.000,
          1.000};

//D2starlnu
float ff4_central[] = {
          0.813, 
          0.808, 
          0.823, 
          0.916, 
          1.006, 
          1.012, 
          1.005, 
          1.155, 
          1.192, 
          1.142, 
          1.253, 
          1.266, 
          1.414, 
          1.256, 
          1.433, 
          1.750, 
          1.000, 
          1.000, 
          1.000, 
          1.000, 
          1.000, 
          1.000}; 

float ff4_lower[] = {
          0.658,
          0.694,
          0.743,
          0.862,
          0.980,
          1.018,
          1.039,
          1.224,
          1.292,
          1.263,
          1.413,
          1.453,
          1.649,
          1.488,
          1.724,
          2.134,
          1.000,
          1.000,
          1.000,
          1.000,
          1.000,
          1.000};

float ff4_upper[] = {
          0.968,
          0.921,
          0.903,
          0.971,
          1.031,
          1.007,
          0.971,
          1.086,
          1.091,
          1.020,
          1.093,
          1.079,
          1.178,
          1.023,
          1.143,
          1.365,
          1.000,
          1.000,
          1.000,
          1.000,
          1.000,
          1.000};

//D0starlnu
float ff5_central[] = {
          0.823, 
          0.901, 
          0.937, 
          0.966, 
          1.020, 
          1.019, 
          1.044, 
          1.144, 
          1.150, 
          1.094, 
          1.289, 
          1.174, 
          1.210, 
          1.164, 
          1.017, 
          0.927, 
          0.744, 
          0.083, 
          0.000, 
          0.000, 
          1.000, 
          1.000}; 

float ff5_lower[] = {
          0.842,
          0.919,
          0.954,
          0.980,
          1.030,
          1.024,
          1.042,
          1.136,
          1.134,
          1.070,
          1.252,
          1.130,
          1.155,
          1.100,
          0.952,
          0.859,
          0.682,
          0.075,
          0.000,
          0.000,
          1.000,
          1.000};

float ff5_upper[] = {
          0.804,
          0.882,
          0.921,
          0.953,
          1.010,
          1.015,
          1.045,
          1.153,
          1.166,
          1.117,
          1.327,
          1.217,
          1.265,
          1.227,
          1.082,
          0.994,
          0.806,
          0.090,
          0.000,
          0.000,
          1.000,
          1.000};

//Dp1lnu
float ff6_central[] = {
          0.638, 
          0.731, 
          0.800, 
          0.896, 
          0.990, 
          0.991, 
          1.116, 
          1.164, 
          1.267, 
          1.329, 
          1.457, 
          1.528, 
          1.529, 
          1.601, 
          1.592, 
          1.401, 
          0.487, 
          0.000, 
          0.000, 
          1.000, 
          1.000, 
          1.000}; 

float ff6_lower[] = {
          0.518,
          0.633,
          0.727,
          0.847,
          0.967,
          0.995,
          1.148,
          1.223,
          1.357,
          1.447,
          1.611,
          1.715,
          1.739,
          1.844,
          1.858,
          1.654,
          0.585,
          0.000,
          0.000,
          1.000,
          1.000,
          1.000};

float ff6_upper[] = {
          0.758,
          0.829,
          0.873,
          0.945,
          1.013,
          0.987,
          1.084,
          1.105,
          1.178,
          1.211,
          1.302,
          1.341,
          1.318,
          1.357,
          1.327,
          1.147,
          0.389,
          0.000,
          0.000,
          1.000,
          1.000,
          1.000};

float GetDssCorr(int dclass, float q2, int c = 0)
{

	if(c>2 || c<0) {cout<<"D**q2correction Error: invalid argument"<<endl; return 1;}

	int tq2 = (int)(22.*q2/11.);
	if(tq2>20) return 1;

	if(dclass == D1) 
	{
		if(c == 0) return ff3_central[tq2];
		if(c == 1) return ff3_lower[tq2];
		if(c == 2) return ff3_upper[tq2];
	}
	if(dclass == D2star) 
	{
		if(c == 0) return ff4_central[tq2];
		if(c == 1) return ff4_lower[tq2];
		if(c == 2) return ff4_upper[tq2];
	}
	if(dclass == Dstar0) 
	{
		if(c == 0) return ff5_central[tq2];
		if(c == 1) return ff5_lower[tq2];
		if(c == 2) return ff5_upper[tq2];
	}
	if(dclass == Dp1) 
	{
		if(c == 0) return ff6_central[tq2];
		if(c == 1) return ff6_lower[tq2];
		if(c == 2) return ff6_upper[tq2];
	}
	return 1;
}

float GetDCorr(int dclass, float q2, int idsys=0 )
{

	q2_tmp = NULL;
	if(dclass==Dmeson){
		if(idsys==0) 
			q2_tmp = q2test;
		else if(idsys==1)
			q2_tmp = q2test1;
		else if(idsys==2)
			q2_tmp = q2test2;
		else if(idsys==3)
			q2_tmp = q2test3;
		else if(idsys==4)
			q2_tmp = q2test4;
		else if(idsys==5)
			q2_tmp = q2test5;
		else if(idsys==6)
			q2_tmp = q2test6;
	     }
	if(dclass==Dstar){
		if(idsys==0) 
			q2_tmp = q2testd;
		else if(idsys==1)
			q2_tmp = q2test1d;
		else if(idsys==2)
			q2_tmp = q2test2d;
	}
	if(dclass>Dstar)
		return  GetDssCorr(dclass,q2,idsys);
	if(!q2_tmp){return 1;}
	
	float weight = q2_tmp->GetBinContent(q2_tmp->FindBin(q2));
	if(weight<0.1)weight=1.;
	return weight;
}

