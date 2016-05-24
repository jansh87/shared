#include "TF1.h"
#include "constants.h"
#include <cmath>
#include <complex>

using namespace std;
template<typename _Tp>
inline complex<_Tp>
operator/(const complex<_Tp>& __x, const int& __y){
  complex<_Tp> __r0 = __x;
  complex<_Tp> __r1 = __y;
  __r0 /= __r1;
  return __r0;
}

template<typename _Tp>
inline complex<_Tp>
operator*(const int& __x, const complex<_Tp>& __y){
  complex<_Tp> __r0 = __x;
  return __r0*__y;
}

typedef complex<double> cdouble;

class Bsemff{
protected:
  double ml2;
  double mH,mH2;
public:
  Bsemff(double m2):ml2(m2),mH(mpic){mH2 = mH*mH;}

  virtual ~Bsemff(){}
  
  virtual cdouble ffvector(const double q2) const = 0;
  virtual cdouble ffscalar(const double q2) const = 0;

  // Branching fraction depend on q2
  virtual double dBdq2(double q2) const;
  double GetMass() const { return ml2; }
  void SetHMass(double x){mH = x; mH2 = mH*mH;}
  double GetHMass() const {return mH;}
  virtual void InitParameters(bool random=false) {};
};

class Bsemff_MC: public Bsemff {
public:
  Bsemff_MC(double m2):Bsemff(m2){}
  virtual ~Bsemff_MC(){};
  virtual cdouble ffvector(const double q2) const ;
  virtual cdouble ffscalar(const double q2) const ;
};

class Bsemff_BCL: public Bsemff {
  double kt;
protected:
  int Kv;
  int Ks;
  double *bvk; // [Kv]
  double *bsk; // [Ks]
public:
  Bsemff_BCL(double m2);
  virtual ~Bsemff_BCL();
  void SetVectorParams(int k, const double *b);
  void SetScalarParams(int k, const double *b);
  virtual cdouble ffvector(const double q2) const;
  virtual cdouble ffscalar(const double q2) const;
  virtual void SetAux(double t0);
  cdouble zparam(const double q2) const ;
  void Print();
  void InitParameters(bool random=false);
};

class Bsemff_KMOW: public Bsemff_BCL{
public:
  Bsemff_KMOW(double m2);
  virtual ~Bsemff_KMOW(){}

  virtual cdouble ffvector(const double q2) const;
  virtual cdouble ffscalar(const double q2) const;
};

//size_t ncall;
class Bsemff_reweight{
public:
  Bsemff *denom_el, *numer_el;
  Bsemff *denom_mu, *numer_mu;
  double d_el_i, n_el_i, d_mu_i, n_mu_i;
  static double rr(const double q2, const Bsemff *ff) {
    const double ml2 = ff->GetMass();
    if(q2<ml2) return 0;
    const double iq2 = 1/q2;
    const double mH2 = pow(ff->GetHMass(),2);
    const double t = q2 - mB02 - mH2;
    const double ppic2 = 0.25*t*t*imB02 - mH2;
    if(ppic2<0) return 0;
    const double ppic = sqrt(ppic2);
    double fp2 = norm(ff->ffvector(q2));
    double f02 = norm(ff->ffscalar(q2));
    double c = pow(q2-ml2,2)*ppic*imB02*iq2*iq2;
    double res = (1 + 0.5*ml2*iq2)*mB02*ppic*ppic*fp2 + 
      0.375*ml2*iq2*pow(mB02-mH2,2)*f02;
    return c*res;
  }

protected:
  static double DoIntegral(const Bsemff *ff){
    double a = ff->GetMass(), b = pow(mB0 - ff->GetHMass(),2);

    const double kCST = 5./1000;

    double x[12] = { 0.96028985649753623,  0.79666647741362674,
		     0.52553240991632899,  0.18343464249564980,
		     0.98940093499164993,  0.94457502307323258,
		     0.86563120238783174,  0.75540440835500303,
		     0.61787624440264375,  0.45801677765722739,
		     0.28160355077925891,  0.09501250983763744};
   
    double w[12] = { 0.10122853629037626,  0.22238103445337447,
		     0.31370664587788729,  0.36268378337836198,
		     0.02715245941175409,  0.06225352393864789,
		     0.09515851168249278,  0.12462897125553387,
		     0.14959598881657673,  0.16915651939500254,
		     0.18260341504492359,  0.18945061045506850};

    double fEpsAbs = 1e-15, fEpsRel = 1e-15;
    double h = 0;
    if (b == a) return h;
    double aconst = kCST/std::abs(b-a);
    double aa = a;
    double bb = b;

    do {
      double mean = 0.5*(bb + aa);
      double delt = 0.5*(bb - aa);

      double s8 = 0;
      for (int i=0;i<4;i++) {
	double dx = delt*x[i];
	double fp = rr(mean+dx,ff);
	double fm = rr(mean-dx,ff);
	s8 += w[i]*(fp + fm);
      }
      s8 *= delt;

      double s16 = 0;
      for (int i=4;i<12;i++) {
	double dx = delt*x[i];
	double fp = rr(mean+dx,ff);
	double fm = rr(mean-dx,ff);
	s16 += w[i]*(fp + fm);
      }
      s16 *= delt;

      //      cout<<aa<<" "<<bb<<" "<<s8<<" "<<s16<<" "<<s16-s8<<endl;
      double error = std::abs(s16-s8);
      if (error <= fEpsAbs || error <= fEpsRel*std::abs(s16)){
	h += s16;
	if(bb != b){
	  aa = bb;
	  bb = b;
	  continue;
	}
	break;
      } else {
	if(1.0 + aconst*std::abs(delt) != 1.0){
	  bb = mean;
	  continue;
	}
	//      MATH_WARN_MSG("ROOT::Math::GausIntegratorOneDim", "Failed to reach the desired tolerance");
	h = s8;  //this is a crude approximation (cernlib function returned 0 !)
	break;
      }
    }while(1);

    return h;
  }

  static double ffinteg(const Bsemff *ff, int N = 10000) {
    double xmin = ff->GetMass(), xmax = pow(mB0 - ff->GetHMass(),2);
    double h = (xmax-xmin)/N;

    double sum = rr(xmin,ff) + rr(xmax,ff);

    double sum4 = 0;
    for(int i=1;i<N;i+=2)
      sum4 += rr(xmin + h*i, ff);

    double sum2 = 0;
    for(int i=2;i<N;i+=2)
      sum2 += rr(xmin + h*i, ff);

    return h*(sum+4*sum4+2*sum2)/3;
  }

public:
  Bsemff_reweight(){
    denom_el = new Bsemff_MC(me2);
    numer_el = new Bsemff_BCL(me2);
    denom_mu = new Bsemff_MC(mmu2);
    numer_mu = new Bsemff_BCL(mmu2);
    d_el_i = DoIntegral(denom_el);
    n_el_i = DoIntegral(numer_el);
    d_mu_i = DoIntegral(denom_mu);
    n_mu_i = DoIntegral(numer_mu);
  }
  
  ~Bsemff_reweight(){
    delete denom_el;
    delete numer_el;
    delete denom_mu;
    delete numer_mu;
  }
  
  double reweight_el(const double q2) const {
    double num = rr(q2,numer_el);
    double den = rr(q2,denom_el);
    if(den>0) return (d_el_i*num)/(n_el_i*den);
    return 1;
  }
  
  double reweight_mu(const double q2) const {
    double num = rr(q2,numer_mu);
    double den = rr(q2,denom_mu);
    if(den>0) return (d_mu_i*num)/(n_mu_i*den);
    return 1;
  }

  void setrandomff_mu(){
    numer_mu->InitParameters(true);
    n_mu_i = DoIntegral(numer_mu);
  }

  void setrandomff_el(){
    numer_el->InitParameters(true);
    n_el_i = DoIntegral(numer_el);
  }
};
