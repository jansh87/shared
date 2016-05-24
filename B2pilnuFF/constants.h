#ifndef constants_h
#define constants_h
#include <cmath>

const double me = 0.000511;
const double mmu = 0.105658367;
const double mtau = 1.77682;
const double mpic = 0.13957018;
const double mpi0 = 0.1349766;
const double meta = 0.547853;
const double metap = 0.95778;  
const double mprot = 0.938272013;
//add  p Meson rho0 113  0.77549 0.1462  0.48     0       2       0 131
// const double mrho0 = 1.2751;
// const double grho0 = 0.1851;
const double mrho0 = 0.77549;
const double grho0 = 0.1491;
//const double grho0 = 0.1462;

const double momega = 0.78265;
const double mB0 = 5.2795;
const double mBc = mB0 - 0.00033;
const double mk0 = 0.497614;
const double mkc = 0.493677;
const double mDc = 1.86957;
const double mD0 = 1.86480;
const double mDstar0 = 2.00693;
const double mDstarc = 2.01022;
const double mJpsi = 3.096916;

//const double GF = 1.16637e-5; // Fermi constant PDG2011
const double GF = 1.1663788e-5; //+-0.0000007 [GeV^{-2}]Fermi constant( MuLan2011 result)
const double clight = 299792458; // [m/s]
const double tauBc = 1.641e-12; // [s]
const double ctauBc = 492.0e-6*1e15; // [fm]
const double tauB0 = 1.519e-12; // [s]
const double ctauB0 = 455.4e-6*1e15; // [fm]
const double hc = 0.1973269631; // [GeV*fm]
const double nBB = 771e6;
#define M_PI 3.14159265358979323846  /* pi */
const double SF = GF*GF/(24*pow(M_PI,3))/(hc/ctauB0);

const double e_her = 7.9965, e_ler = 3.5, cang = 22e-3;
const double p_her = sqrt(e_her*e_her - me*me);
const double p_ler = sqrt(e_ler*e_ler - me*me);

const double me2     = me*me;
const double mmu2    = mmu*mmu;
const double mtau2   = mtau*mtau;
const double mpic2   = mpic*mpic;
const double mB02    = mB0*mB0;
const double imB02   = 1/mB02;
const double mBpi    = mB0 + mpic;
const double mBpi2   = mBpi*mBpi;
const double mBstar  = 5.325;
const double mBstar2 = mBstar*mBstar;

#endif // #ifdef constants_h
