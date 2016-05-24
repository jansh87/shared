#include<cmath>
#include<TLorentzVector.h>


class MyParticle
{
    public:
        TLorentzVector P;
        TLorentzVector genP;
        float dr, dz;
        int pid;
        int pid_true;
        int charge;
	int gen_id;
	int gen_ist;
	int gen_mo_id;

	int flag;

        MyParticle(){};
        MyParticle(float, float, float, float, int);
        MyParticle(float, float, float, float, int, int);
        MyParticle(float, float, float, float, int, int,float,float);
};


MyParticle::MyParticle(float x, float y, float z, float e, int sep)
{
	MyParticle(x,y,z,e,sep,1,0.,0.);
}
MyParticle::MyParticle(float x, float y, float z, float e, int sep, int q)
{
	MyParticle(x,y,z,e,sep,q,0,0);
}

MyParticle::MyParticle(float x, float y, float z, float e, int sep, int q, float Dr, float Dz)
{
    P=TLorentzVector(x,y,z,e);
    pid = sep%10;
    pid_true = sep/10;
    charge =q;
    dr=Dr;
    dz=Dz;

    flag = 0;
}
