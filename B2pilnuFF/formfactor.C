#include "formfactor.h"
#include "TRandom3.h"

// const double clight = 299792458; // [m/s]
// const double hc = 0.1973269631; // [GeV*fm]
// Branching fraction depend on q2
double Bsemff::dBdq2(double q2) const {
  if(q2<ml2) return 0;
  const double iq2 = 1/q2;
  const double t = q2 - mB02 - mH2;
  const double ppic2 = 0.25*t*t*imB02 - mH2;
  if(ppic2<0) return 0;
  const double ppic = sqrt(ppic2);
  double fp2 = norm(ffvector(q2));
  double f02 = norm(ffscalar(q2));
  double res = GF*GF/(24*pow(M_PI,3))*pow(q2-ml2,2)*ppic*imB02*iq2*iq2*
    (
     (1 + 0.5*ml2*iq2)*mB02*ppic*ppic*fp2
     + 0.375*ml2*iq2*pow(mB02-mH2,2)*f02
     );
  double itau = res*clight*1e3/hc; // inverse picoseconds
  return itau;
}

cdouble Bsemff_MC::ffvector(const double q2) const {
  const double f0 = 0.261, a = -2.03, b = 1.293;
  const double t = q2*imB02;
  return f0/(1+t*(a+t*b));
}

cdouble Bsemff_MC::ffscalar(const double q2) const {
  const double f0 = 0.261, a = -0.27, b = -0.752;
  const double t = q2*imB02;
  return f0/(1+t*(a+t*b));
}  

Bsemff_BCL::Bsemff_BCL(double m2):Bsemff(m2),Kv(0),Ks(0),bvk(0),bsk(0){
  double t0 = mBpi*pow(sqrt(mB0)-sqrt(mH),2);
  SetAux(t0);
  InitParameters();
}

void Bsemff_BCL::InitParameters(bool random){
//  belle tagged(pi+ + pi0), belle untagged (pi+), babar untagged(pi+ + pi0) 
//  MIGRAD MINIMIZATION HAS CONVERGED.
//  MIGRAD WILL VERIFY CONVERGENCE AND ERROR MATRIX.
//  COVARIANCE MATRIX CALCULATED SUCCESSFULLY
//  FCN=44.7815 FROM MIGRAD    STATUS=CONVERGED     130 CALLS         131 TOTAL
//                      EDM=2.53549e-06    STRATEGY= 2      ERROR MATRIX ACCURATE 
//   EXT PARAMETER                                   STEP         FIRST   
//   NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
//    1  b0           4.55997e-01   2.87015e-02   1.63321e-05  -1.10412e-01
//    2  b1          -5.23488e-01   9.09821e-02   6.71724e-05  -1.11175e-02
//    3  b2          -3.21633e-02   7.65592e-01   2.84678e-04  -3.19534e-03
//    4  b3          -1.73007e+00   1.97166e+00   9.02743e-04  -5.85756e-04
//    5  Vub          3.38618e+00   2.20247e-01   5.97613e-05  -7.19738e-03
//  EXTERNAL ERROR MATRIX.    NDIM=  25    NPAR=  5    ERR DEF=1
//  C =
//   8.238e-04 -5.623e-04 -3.386e-03 -4.920e-04 -5.792e-03 
//  -5.623e-04  8.278e-03 -2.820e-02  2.791e-03  1.426e-03 
//  -3.386e-03 -2.820e-02  5.861e-01 -1.318e+00 -4.312e-03 
//  -4.920e-04  2.791e-03 -1.318e+00  3.887e+00  1.007e-01 
//  -5.792e-03  1.426e-03 -4.312e-03  1.007e-01  4.860e-02 
//  PARAMETER  CORRELATION COEFFICIENTS  
//        NO.  GLOBAL      1      2      3      4      5
//         1  0.98507   1.000 -0.215 -0.154 -0.009 -0.915
//         2  0.97474  -0.215  1.000 -0.405  0.016  0.071
//         3  0.99365  -0.154 -0.405  1.000 -0.873 -0.026
//         4  0.99036  -0.009  0.016 -0.873  1.000  0.232
//         5  0.97151  -0.915  0.071 -0.026  0.232  1.000
// Unitarity constraint: 0.107344
// chi^2 = 44.7815 ndf = 45 Prob(chi^2, ndf) = 0.481137
//
// Cholesky decomposition of C = L * L^T:
  double L[5][5] = {
    { 2.87014992e-02,               0,               0,               0,               0},
    {-1.95909552e-02,  8.88478765e-02,               0,               0,               0},
    {-1.17988439e-01, -3.43381456e-01,  6.74017199e-01,               0,               0},
    {-1.71420962e-02,  2.76294948e-02, -1.94407926e+00,  3.27039489e-01,               0},
    {-2.01793417e-01, -2.84426680e-02, -5.62126691e-02, -3.44071581e-02,  5.22452218e-02}
  };

  double bv[] = {0.455997, -0.523488, -0.00321633, -1.73007};
  //  const double bv[] = {0.420, -0.514};                 // Eq.29
  //  const double bv[] = {0.421, -0.476, -0.399};         // Eq.30
  //  const double bv[] = {0.421, -0.469, -0.178, -0.825}; // Eq.31
  //  const double bv[] = {0.42, -0.47, -0.18, -0.83};     // Eq.39
  const int nv = sizeof(bv)/sizeof(bv[0]);
  if(random){
    double r[5],cr[5];
    for(int i=0;i<5;i++) r[i] = gRandom->Gaus();
    for(int i=0;i<5;i++){
      cr[i] = 0;
      for(int j=0;j<i+1;j++){
	cr[i] += L[i][j]*r[j];
      }
    }
    for(int i=0; i<nv; i++) bv[i] += cr[i];
  }

  //  for(int i=0; i<nv; i++) cout<<bv[i]<<" "; cout<<endl;
  SetVectorParams(nv,bv);
  
  //  const double bs[] = {0.595147,-1.12026};
  const double b01 = -4; // form factor slope from Table 1 @ arXiv:1103.2655v2
  const double z0 = abs(zparam(0));
  const double f0 = abs(ffvector(0));
  const double bs[] = {f0*(1-z0*b01),f0*b01}; // be sure f^+(0) = f^0(0)
  //  cout<<bs[0]<<" "<<bs[1]<<endl;
  SetScalarParams(sizeof(bs)/sizeof(bs[0]),bs);  
}

Bsemff_BCL::~Bsemff_BCL(){
  if (bvk) delete [] bvk;
  if (bsk) delete [] bsk;
}

void Bsemff_BCL::SetVectorParams(int k, const double *b){
  if(k!=Kv){
    if(bvk) delete [] bvk;
    bvk = new double[k];
    Kv = k;
  }
  memcpy(bvk,b,k*sizeof(double));
}

void Bsemff_BCL::SetScalarParams(int k, const double *b){
  if(k!=Ks){
    if(bsk) delete [] bsk;
    bsk = new double[k];
    Ks = k;
  }
  memcpy(bsk,b,k*sizeof(double));
}

cdouble Bsemff_BCL::ffvector(const double q2) const {
  cdouble zq2[Kv+1];
  const cdouble zq2f = zparam(q2);
  zq2[0] = 1;
  for(int k=1;k<=Kv;k++){
    zq2[k] = zq2[k-1]*zq2f;
  }
  cdouble sum = 0;
  cdouble r0 = zq2[Kv]/Kv;
  r0 = (Kv&1)?-r0:r0;
  for(int k=0;k<Kv;k++){
    sum += bvk[k]*(zq2[k] - k*r0); r0 = -r0;
  }
  return mBstar2/(mBstar2-q2)*sum;
}

cdouble Bsemff_BCL::ffscalar(const double q2) const {
  const cdouble zq2f = zparam(q2);
  cdouble sum = 0;
  cdouble zq2k = 1;
  for(int k=0;k<Ks;k++){
    sum += bsk[k]*zq2k;
    zq2k *= zq2f;
  }
  return sum;
}
  
void Bsemff_BCL::SetAux(double t0){
  kt = sqrt(mBpi2-t0);
}

cdouble Bsemff_BCL::zparam(const double q2) const {
  const cdouble kq = sqrt(cdouble(mBpi2-q2));
  return (kq-kt)/(kq+kt);
}

void Bsemff_BCL::Print(){
  for(int i=0;i<Kv;i++)cout<<bvk[i]<<" "; cout<<endl;
  for(int i=0;i<Ks;i++)cout<<bsk[i]<<" "; cout<<endl;
}

Bsemff_KMOW::Bsemff_KMOW(double m2):Bsemff_BCL(m2){
  double q2min = -6.0; // [GeV^2]
  double t0 = mBpi2-2*sqrt((mB0*mH)*(mBpi2-q2min));
  SetAux(t0);
  
  const double bv[] = {0.281,-1.62};
  const double bs[] = {0.281,-3.98};
  
  SetVectorParams(2,bv);
  SetScalarParams(2,bs);  
}

cdouble Bsemff_KMOW::ffvector(const double q2) const {
  cdouble zq2[Kv+1], z0[Kv+1];
  const cdouble zq2f = zparam(q2);
  const cdouble z0f = zparam(0);
  zq2[0] = 1;
  z0[0] = 1;
  for(int k=1;k<=Kv;k++){
    zq2[k] = zq2[k-1]*zq2f;
    z0[k] = z0[k-1]*z0f;
  }
  cdouble sum = 0;
  cdouble r0 = (zq2[Kv]-z0[Kv])/Kv;
  r0 = ((Kv+1)&1)?-r0:r0;
  for(int k=1;k<Kv;k++){
    sum += bvk[k]*(zq2[k] - z0[k] - k*r0); r0 = -r0;
  }
  return mBstar2/(mBstar2-q2)*bvk[0]*(1.0 + sum);
}
  
cdouble Bsemff_KMOW::ffscalar(const double q2) const {
  const cdouble zq2f = zparam(q2);
  const cdouble z0f = zparam(0);
  cdouble zq2k = zq2f;
  cdouble z0k = z0f;
  cdouble sum = 0;
  for(int k=1;k<Ks;k++){
    sum += bsk[k]*(zq2k-z0k);
    zq2k *= zq2f;
    z0k *= z0f;
  }
  return bsk[0]*(1.0 + sum);
}

Bsemff_MC *gFF0, *gFF1, *gFFmct;
Bsemff_BCL *gFF2, *gFF3, *gFFbclt;
Bsemff_KMOW *gFF4, *gFF5;
double dGdq2e(double *x, double *p){
  if(!gFF0) gFF0 = new Bsemff_MC(me2);
  return p[0]*gFF0->dBdq2(x[0]);
}
double dGdq2m(double *x, double *p){
  if(!gFF1) gFF1 = new Bsemff_MC(mmu2);
  return p[0]*gFF1->dBdq2(x[0]);
}
double dGdq2t(double *x, double *p){
  if(!gFFmct) gFFmct = new Bsemff_MC(mtau2);
  return p[0]*gFFmct->dBdq2(x[0]);
}
double dGdq2bcle(double *x, double *p){
  if(!gFF2) gFF2 = new Bsemff_BCL(me2);
  return p[0]*gFF2->dBdq2(x[0]);
}
double dGdq2bclm(double *x, double *p){
  if(!gFF3) gFF3 = new Bsemff_BCL(mmu2);
  return p[0]*gFF3->dBdq2(x[0]);
}
double dGdq2bclt(double *x, double *p){
  if(!gFFbclt) gFFbclt = new Bsemff_BCL(mtau2);
  return p[0]*gFFbclt->dBdq2(x[0]);
}
double dGdq2kmowe(double *x, double *p){
  if(!gFF4) gFF4 = new Bsemff_KMOW(me2);
  return p[0]*gFF4->dBdq2(x[0]);
}
double dGdq2kmowm(double *x, double *p){
  if(!gFF5) gFF5 = new Bsemff_KMOW(mmu2);
  return p[0]*gFF5->dBdq2(x[0]);
}

double _fp(double *x, double *p){
  if(!gFF0) gFF0 = new Bsemff_MC(me2);
  return abs(gFF0->ffvector(x[0])*(1-x[0]/mBstar2));
}
double _f0(double *x, double *p){
  if(!gFF0) gFF0 = new Bsemff_MC(me2);
  return abs(gFF0->ffscalar(x[0]));
}

Bsemff_BCL *gFF6;
double _f0bcl(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  ((Bsemff_BCL*)gFF6)->SetScalarParams(2,p);
  return abs(gFF6->ffscalar(x[0]));
}
double _f0bcli(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  ((Bsemff_BCL*)gFF6)->SetScalarParams(2,p);
  return gFF6->ffscalar(x[0]).imag();
}
double _f0bclr(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  ((Bsemff_BCL*)gFF6)->SetScalarParams(2,p);
  return gFF6->ffscalar(x[0]).real();
}

double _fpbcl(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  ((Bsemff_BCL*)gFF6)->SetVectorParams(4,p);
  return abs(gFF6->ffvector(x[0])*(1-x[0]/mBstar2));
}
double _fpbcli(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  ((Bsemff_BCL*)gFF6)->SetVectorParams(4,p);
  return gFF6->ffvector(x[0]).imag();
}
double _fpbclr(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  ((Bsemff_BCL*)gFF6)->SetVectorParams(4,p);
  return gFF6->ffvector(x[0]).real();
}
double _map(double *x, double *p){
  if(!gFF6) gFF6 = new Bsemff_BCL(me2);
  return ((Bsemff_BCL*)gFF6)->zparam(x[0]).real();
}

Bsemff_KMOW *gFF7;
double _f0kmow(double *x, double *p){
  if(!gFF7) gFF7 = new Bsemff_KMOW(me2);
  ((Bsemff_KMOW*)gFF7)->SetScalarParams(2,p);
  return abs(gFF7->ffscalar(x[0]));
}
double _f0kmowi(double *x, double *p){
  if(!gFF7) gFF7 = new Bsemff_KMOW(me2);
  ((Bsemff_KMOW*)gFF7)->SetScalarParams(2,p);
  return gFF7->ffscalar(x[0]).imag();
}
double _f0kmowr(double *x, double *p){
  if(!gFF7) gFF7 = new Bsemff_KMOW(me2);
  ((Bsemff_KMOW*)gFF7)->SetScalarParams(2,p);
  return gFF7->ffscalar(x[0]).real();
}

double _fpkmow(double *x, double *p){
  if(!gFF7) gFF7 = new Bsemff_KMOW(me2);
  ((Bsemff_KMOW*)gFF7)->SetVectorParams(2,p);
  return abs(gFF7->ffvector(x[0]));
}
double _fpkmowi(double *x, double *p){
  if(!gFF7) gFF7 = new Bsemff_KMOW(me2);
  ((Bsemff_KMOW*)gFF7)->SetVectorParams(2,p);
  return gFF7->ffvector(x[0]).imag();
}
double _fpkmowr(double *x, double *p){
  if(!gFF7) gFF7 = new Bsemff_KMOW(me2);
  ((Bsemff_KMOW*)gFF7)->SetVectorParams(2,p);
  return gFF7->ffvector(x[0]).real();
}

#ifdef DOTEST
int main(){
  Bsemff_reweight rw;
  for(int i=0;i<1000;i++){
    rw.setrandomff_mu();
    cout<<rw.n_mu_i<<" ";
    for(double x=1;x<27;x+=1){
      cout<<rw.reweight_mu(x)<<" ";
    }
    cout<<endl;
  }
  return 0;
}
#endif
