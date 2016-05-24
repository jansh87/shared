
#ifndef _CVAR_H
#define _CVAR_H

#ifndef nbins_const
#define nbins_const 30
#endif

class CVar
{
	public:
	string Name;
	string LeafName;
	string xTitle;

	int nBins;
	float xMin;
	float xMax;

	float *xBins;

	float *var;

	bool fl_var_alloc;
	bool fl_logy;

	float val(){return *var;};

	CVar(string,float*, float,float);
	CVar(string,float*, int, float,float);
	CVar(string,string,float*, float,float);
	CVar(string,string,float*, int,float,float);
	//call w/o variable pointer
	CVar(string, float,float);
	CVar(string, int, float,float);
	CVar(string,string, float,float);
	CVar(string,string,int,float,float);
	//variable binwidth
	CVar(string,float*, float*);
	CVar(string,float*, int, float*);
	CVar(string,string,float*, float*);
	CVar(string,string,float*, int,float*);
	CVar();
	CVar(const CVar&);
	~CVar();
	
	void SetVar(float v){*var = v;};

};
CVar::CVar()
{
	Name.assign("0");
	xTitle.assign("0");
	nBins = nbins_const;
	xMin = 0;
	xMax = 1;
	xBins = NULL;
	var = NULL;
	fl_var_alloc = false;
	fl_logy = false;
}
CVar::~CVar()
{
	if(fl_var_alloc)
	{ 
		delete var; 
		var = NULL; 
		fl_var_alloc = false;
	}
}
CVar::CVar(const CVar& B)
{
	Name=B.Name;
	xTitle=B.xTitle;
	nBins = B.nBins;
	xMin = B.xMin;
	xMax = B.xMax;
	xBins = B.xBins;
	fl_var_alloc = B.fl_var_alloc;
	fl_logy = B.fl_logy;
	if(!fl_var_alloc)
		var = B.var;
	else
		var = new float(*B.var);
}
CVar::CVar(string name, float *v, float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(name);
	nBins = nbins_const;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = v;
	fl_var_alloc = false;
	fl_logy = false;

}
CVar::CVar(string name, float *v, int bins, float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(name);
	nBins = bins;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = v;	
	fl_var_alloc = false;
	fl_logy = false;
}
CVar::CVar(string name, string xtitle, float *v,  float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(xtitle);
	nBins = nbins_const;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = v;	
	fl_var_alloc = false;
	fl_logy = false;
}
CVar::CVar(string name, string xtitle, float *v, int bins,   float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(xtitle);
	nBins = bins;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = v;
	fl_var_alloc = false;
	fl_logy = false;
}
//call w/o variable pointer
CVar::CVar(string name, float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(name);
	nBins = nbins_const;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = new float(0);
	fl_logy = false;
	fl_var_alloc = true;

}
CVar::CVar(string name, int bins, float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(name);
	nBins = bins;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = new float(0);
	fl_var_alloc = true;
	fl_logy = false;
}
CVar::CVar(string name, string xtitle,float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(xtitle);
	nBins = nbins_const;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = new float(0);
	fl_var_alloc = true;
	fl_logy = false;
}
CVar::CVar(string name, string xtitle, int bins,   float Min, float Max)
{
	Name.assign(name);
	xTitle.assign(xtitle);
	nBins = bins;
	xMin = Min;
	xMax = Max;
	xBins = NULL;
	var = new float(0);
	fl_var_alloc = true;
	fl_logy = false;
}
//variable binwidth
CVar::CVar(string name, float *v,  float* xb)
{
	Name.assign(name);
	xTitle.assign(name);
	nBins = nbins_const;
	xMin = xb[0];
	xMax = 0;
	xBins = xb;
	var = v;
	fl_var_alloc = false;
	fl_logy = false;

}
CVar::CVar(string name, float *v, int bins,  float* xb)
{
	Name.assign(name);
	xTitle.assign(name);
	nBins = bins;
	xMin = xb[0];
	xMax = xb[bins];
	xBins = xb;
	var = v;	
	fl_var_alloc = false;
	fl_logy = false;
}
CVar::CVar(string name, string xtitle, float *v, float* xb)
{
	Name.assign(name);
	xTitle.assign(xtitle);
	nBins = nbins_const;
	xMin = xb[0];
	xMax = xb[nbins_const];
	xBins = xb;
	var = v;	
	fl_var_alloc = false;
	fl_logy = false;
}
CVar::CVar(string name, string xtitle, float *v, int bins,  float* xb)
{
	Name.assign(name);
	xTitle.assign(xtitle);
	nBins = bins;
	xMin = xb[0];
	xMax = xb[bins];
	xBins = xb;
	var = v;
	fl_var_alloc = false;
	fl_logy = false;
}
#endif
