#include "../shared/CBrCorr.h"
#include<cstdio>
#include<map>
#include<vector>
#include"TH1F.h"
 
#define _nDecayChars 50
#ifndef _BrLog
#define _BrLog 1
#endif
 
 
 
class CorrectBf
{
    public:
        static std::vector<CBrCorr> vBBf;
        std::map<string,CBrCorr> mBBf;
        std::map<string,CBrCorr> mDBf;
        std::map<string,CBrCorr> mDssFix;
        string Bdecay;
        string Ddecay;
        std::vector<string> Ddecays;
 
    TH1F *hBdecays;
    TH1F *hDdecays;
 
        void split( string );
        void splitD( string );
    static vector<string>* SplitDString(string&);
    void InitBrCorr();
    static void NoCharge(string&);
    
    bool fl_DssMC;
     
    void EqualCP(string&);
    void PrintMaxima(TH1F*, int);
    float weight(string, std::map<string,CBrCorr>&);
 
    FILE *fpLog;
 
 
     
 
 
 
        CorrectBf(bool DssMC = 1);
        ~CorrectBf();
        float weightB(int, int);
        float weightB(string&);
         float weightB(char *);
        float weightD(char *);
        float weightD(string&);
        float FixDss(string&);
        float FixDss(char *);
};
std::vector<CBrCorr> CorrectBf::vBBf;
 
CorrectBf::CorrectBf(bool DssMC)
{
    fl_DssMC = DssMC;
    InitBrCorr();
    fpLog = fopen(Form("CorrectBf_%i.log",fl_DssMC),"w"); 
    hBdecays = new TH1F("hBdecays","hBdecays",10001,0,10000);
    hDdecays = new TH1F("hDdecays","hDdecays",10001,0,10000);
}
 
CorrectBf::~CorrectBf()
{
    PrintMaxima(hBdecays,30);
    PrintMaxima(hDdecays,30);
    fclose(fpLog);
    hBdecays->Delete();
    hDdecays->Delete();
 
}
void CorrectBf::InitBrCorr()
{
     
    CBrCorr tmp;
    
    if(fl_DssMC){
    //Dss MC
      //B+-                 //pdg eval, pdg fit
                            //2.27
    tmp = CBrCorr("B2D0lnu" , 2 , 1 , 2.31 ,  2.29, 'n');  //MCBr , br measured
    vBBf.push_back( tmp );
                        //5.69
    tmp = CBrCorr("B2D*0lnu" , 2 , 3 , 5.79 , 5.69 , 'n');
    vBBf.push_back( tmp );
 
 
    //B0
 
                        //2.19
    tmp = CBrCorr("B2D-lnu" , -2 , 1 , 2.13 , 2.13 , 'n');
    vBBf.push_back( tmp );
 
                        //4.93
    tmp = CBrCorr("B2D*-lnu" , -2 , 3 , 5.33 ,5.3 , 'n');
    vBBf.push_back( tmp );
 
    //B+
 
 

    //Dss MC to LLSW
    //to HFAG
    tmp = CBrCorr("B2D_10lnu" , 2 , 5 ,0.68, 0.67, 'n');//0.74 );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D0*0lnu" , 2 , 7 , 0.67, 0.44, 'n');//0.26 );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D'_10lnu" , 2 , 8 , 0.3, 0.20, 'n');//0.47 );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D_2*0lnu" , 2 , 6 , 0.6, 0.3, 'n');//0.52  );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D*pi" , 2 , 4 , 0.10 , 0.15, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2Dpilnu" , 2 , 2 , 0.16 , 0.31 , 'n');
    vBBf.push_back( tmp );
    tmp = CBrCorr("B2D2Slnu" , 2 , 9 , 0.5 , 0.1 , 'n');
    vBBf.push_back( tmp );
    tmp = CBrCorr("B2D*2Slnu" , 2 , 10 , 0.5 , 0.6 , 'n');
    vBBf.push_back( tmp );
     
//alles nochmal fuer B0 -> einfacher fuer separate skalierung
 
 
 
    
    tmp = CBrCorr("B02D_10lnu" , -2 , 5 , 0.68 , 0.63, 'n');//0.74, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02D0*0lnu" , -2 , 7 , 0.67 , 0.4, 'n');// 0.26, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02D'_10lnu" , -2 , 8 , 0.3 ,0.18, 'n'); // 0.47 , 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02D_2*0lnu" , -2 , 6 , 0.6 , 0.28, 'n');//0.52 , 'n');
    vBBf.push_back( tmp );
 
 
     
    tmp = CBrCorr("B02D*pi" , -2 , 4 , 0.06 , 0.14, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02Dpilnu" , -2 , 2 , 0.10 , 0.29 , 'n');
    vBBf.push_back( tmp );
     
    tmp = CBrCorr("B02D2Slnu" , -2 , 9 , 0.5 , 0.09 , 'n');
    vBBf.push_back( tmp );
    tmp = CBrCorr("B02D*2Slnu" , -2 , 10 , 0.5 , 0.56, 'n');
    vBBf.push_back( tmp );      
     
     
     } else {
     
    
    //Gen MC
      //B+-                 //pdg eval, pdg fit
                            //2.27
    tmp = CBrCorr("B2D0lnu" , 2 , 1 , 2.31 ,  2.29, 'n');  //MCBr , br measured
    vBBf.push_back( tmp );
                        //5.69
    tmp = CBrCorr("B2D*0lnu" , 2 , 3 , 5.79 , 5.60 , 'n');
    vBBf.push_back( tmp );
 
 
    //B0
 
                        //2.19
    tmp = CBrCorr("B2D-lnu" , -2 , 1 , 2.13 , 2.18 , 'n');
    vBBf.push_back( tmp );
 
                        //4.93
    tmp = CBrCorr("B2D*-lnu" , -2 , 3 , 5.33 , 5.10 , 'n');
    vBBf.push_back( tmp );
 
    //B+
    
 

 
    //Dss MC to LLSW
    //to HFAG
    tmp = CBrCorr("B2D_10lnu" , 2 , 5 ,0.81, 0.43, 'n');//0.74 );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D0*0lnu" , 2 , 7 , 0.91, 0.44, 'n');//0.26 );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D'_10lnu" , 2 , 8 , 0.81, 0.2, 'n');//0.47 );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D_2*0lnu" , 2 , 6 , 0.39, 0.37, 'n');//0.52  );
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2D*pi" , 2 , 4 , 0.10 , 0.2, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B2Dpilnu" , 2 , 2 , 0.16 , 0.048 , 'n');
    vBBf.push_back( tmp );
    tmp = CBrCorr("B2D2Slnu" , 2 , 9 , 0.02 , 0.1 , 'n');
    vBBf.push_back( tmp );
    tmp = CBrCorr("B2D*2Slnu" , 2 , 10 , 0.05 , 0.1 , 'n');
    vBBf.push_back( tmp );
     
//alles nochmal fuer B0 -> einfacher fuer separate skalierung
 
 
 
    
    tmp = CBrCorr("B02D_10lnu" , -2 , 5 , 0.74 , 0.43, 'n');//0.74, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02D0*0lnu" , -2 , 7 , 0.84 , 0.44, 'n');// 0.26, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02D'_10lnu" , -2 , 8 , 0.74 ,0.2, 'n'); // 0.47 , 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02D_2*0lnu" , -2 , 6 , 0.36 , 0.37, 'n');//0.52 , 'n');
    vBBf.push_back( tmp );
 
 
     
    tmp = CBrCorr("B02D*pi" , -2 , 4 , 0.09 , 0.2, 'n');
    vBBf.push_back( tmp );
 
    tmp = CBrCorr("B02Dpilnu" , -2 , 2 , 0.15 , 0.048 , 'n');
    vBBf.push_back( tmp );
     
    tmp = CBrCorr("B02D2Slnu" , -2 , 9 , 0.02 , 0.1 , 'n');
    vBBf.push_back( tmp );
    tmp = CBrCorr("B02D*2Slnu" , -2 , 10 , 0.05 , 0.1 , 'n');
    vBBf.push_back( tmp );      
    }
    //the inclusive sum has to match the measuered one. recale all sl decays exept D/D* final states
     
    float B2Xlnu = 10.8;
    float B02Xlnu = 10.1;
     
     
    //B+
    float sum_all = 0;
    float sum_scaled = 0;   
    float scale2Incl; 
    /*for(unsigned i = 0; i < vBBf.size();++i)
    {
        if(vBBf[i].lclass<0) continue;
        sum_all+=vBBf[i].Br;
        if(i>=4)
            sum_scaled+=vBBf[i].Br;
        cout<<vBBf[i].Name<<" "<<vBBf[i].Br<<endl;
    }
     
    scale2Incl = (B2Xlnu-(sum_all-sum_scaled))/sum_scaled;
    cout<<sum_all<<" "<<sum_scaled<<" "<<scale2Incl<<endl;
    for(unsigned i = 4; i < vBBf.size();++i)
    { 
        if(vBBf[i].lclass < 0) continue;
        vBBf[i].Br*=scale2Incl;
        //cout<<vBBf[i].Br<<" "<<vBBf[i].Weight()<<endl;
    }
     
     sum_all = 0;
     sum_scaled = 0;    
    for(unsigned i = 0; i < vBBf.size();++i)
    {
        if(vBBf[i].lclass>0) continue;
        sum_all+=vBBf[i].Br;
        if(i>=4)
            sum_scaled+=vBBf[i].Br;
            cout<<vBBf[i].Name<<" "<<vBBf[i].Br<<endl;
    }
     
     scale2Incl = (B02Xlnu-(sum_all-sum_scaled))/sum_scaled;
     cout<<sum_all<<" "<<sum_scaled<<" "<<scale2Incl<<endl;
    for(unsigned i = 4; i < vBBf.size();++i)
    { 
        if(vBBf[i].lclass > 0) continue;
        vBBf[i].Br*=scale2Incl;
    }
     */
     
     
    float BXtaunu = 2.48; //auch im fitconstraint aendern!
        float B0Xtaunu = 2.33;
        //b+
        tmp = CBrCorr("BDtaunu" , 1 , 1 , 0.77 , 0.77, 'n');
        vBBf.push_back( tmp );
         
    tmp = CBrCorr("BD*taunu" , 1 , 3 , 1.54 , 1.54, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD1taunu" , 1 , 5 , 0.13 , 0.13, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD2taunu" , 1 , 6 , 0.08 ,0.08, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD1'taunu" , 1 , 7 , 0.12 , 0.12, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD0*taunu" , 1 , 8 , 0.16 , 0.16, 'n');
        vBBf.push_back( tmp );
         
        //b0
        tmp = CBrCorr("BDtaunu" , -1 , 1 , 0.71 , 0.71, 'n');
        vBBf.push_back( tmp );
         
    tmp = CBrCorr("BD*taunu" , -1 , 3 , 1.42 , 1.42, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD1taunu" , -1 , 5 , 0.12 , 0.12, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD2taunu" , -1 , 6 , 0.08 , 0.08, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD1'taunu" , -1 , 7 , 0.12 , 0.12, 'n');
        vBBf.push_back( tmp );
         
        tmp = CBrCorr("BD0*taunu" , -1 , 8 , 0.15 , 0.15, 'n');
        vBBf.push_back( tmp );
     
    //B+
    sum_all = 0;
    sum_scaled = 0;    
    for(unsigned i = 0; i < vBBf.size();++i)
    {
        if(vBBf[i].lclass!=1) continue;
        sum_all+=vBBf[i].Br;
        sum_scaled+=vBBf[i].Br;
    }
     
     scale2Incl = (BXtaunu-(sum_all-sum_scaled))/sum_scaled;
 
    for(unsigned i = 0; i < vBBf.size();++i)
    { 
        if(vBBf[i].lclass != 1) continue;
        vBBf[i].Br*=scale2Incl;
    }
     
     sum_all = 0;
     sum_scaled = 0;    
    for(unsigned i = 0; i < vBBf.size();++i)
    {
        if(vBBf[i].lclass != -1) continue;
        sum_all+=vBBf[i].Br;
        sum_scaled+=vBBf[i].Br;
    }
     
     scale2Incl = (B0Xtaunu-(sum_all-sum_scaled))/sum_scaled;
 
    for(unsigned i = 0; i < vBBf.size();++i)
    { 
        if(vBBf[i].lclass  != -1) continue;
        vBBf[i].Br*=scale2Incl;
    }
        
        

   
 //B->ulnu
  
   float b0ulnu =  3.418e-1; //in %
   float bpulnu =  3.670e-1;
 
/*
    tmp = CBrCorr("B02pi-enu" ,  "511_211_11_12"  , 1.36 , 1.45 );
    mBBf[tmp.sDecay] = tmp;
    tmp = CBrCorr("B02pi-munu" ,  "511_211_13_14"  , 1.36 , 1.45 );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B02rho-enu" ,  "511_213_11_12"  , 2.77 , 2.79 ); //br = average of hfag and alexeis result
    mBBf[tmp.sDecay] = tmp;
    tmp = CBrCorr("B02rho-munu" ,  "511_213_13_14"  , 2.77 , 2.79 );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B+2pi0enu" ,  "521_111_11_12"  , 0.73 , 0.78 ); //B0 Br with lifetime correction (cf HFAG)
    mBBf[tmp.sDecay] = tmp;
    tmp = CBrCorr("B+2pi0munu" ,  "521_111_13_14"  , 0.73 , 0.78 );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B+2rho0enu" ,  "521_113_11_12"  , 1.49 ,1.58 ); //br = average of hfag and alexeis result
    mBBf[tmp.sDecay] = tmp;
    tmp = CBrCorr("B+2rho0munu" ,  "521_113_13_14"  , 1.49 , 1.58);
    mBBf[tmp.sDecay] = tmp;
*/
    //B0 hadronic
/*
    tmp = CBrCorr("B02D+a1-" ,  "511_20213_411"  , 0.75 , 0.6 );//
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B2D+Ds-" ,  "511_411_431"  , 0.65 , 0.72 );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B2D*+D*0K-" ,  "511_413_423_321"  , 1.18 , 1.06 );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B2D*0rho+" ,  "521_423_213"  , 1.55 , 1. );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B2D03pi" ,  "521_421_211_211_211"  , 0.46 , 0.5 );
    mBBf[tmp.sDecay] = tmp;
     
 
    tmp = CBrCorr("B2D0Ds+" ,  "521_421_431"  , 1. , 0.9 );
    mBBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("B2D*0D*+K0" ,  "521_423_413_311"  , 0.78 , 0.92 );
    mBBf[tmp.sDecay] = tmp;
  */ 
    CBrCorr cB0("B0X","511X",0,0);
    CBrCorr cBp("B+X","521X",0,0);
    for(auto it = mBBf.begin(); it!=mBBf.end();it++)    
    {
        if(it->first[1] == '1')
        { cB0.MCBr += it->second.MCBr; cB0.Br += it->second.Br;}
        else if(it->first[1] == '2')
        { cBp.MCBr += it->second.MCBr; cBp.Br += it->second.Br;}  
    }
    cB0.Br += 2*B02Xlnu + B0Xtaunu + 2*b0ulnu;  cB0.MCBr += 2*10.45 + B0Xtaunu + 2*b0ulnu;
    cBp.Br += 2*B2Xlnu + BXtaunu+ 2*bpulnu; cBp.MCBr += 2*11.35 +  BXtaunu + 2*bpulnu;
     
    cB0.Br = 100-cB0.Br;
    cBp.Br = 100-cBp.Br;
    cB0.MCBr = 100-cB0.MCBr;
    cBp.MCBr = 100-cBp.MCBr;
     
    //cB0.Weight = (cB0.Br)/(cB0.MCBr);
    //cBp.Weight = (cBp.Br)/(cBp.MCBr);
    mBBf[cB0.sDecay] = cB0;
    mBBf[cBp.sDecay] = cBp;
 
 
    //Ddecays
     
    //D+ SL PDG 2016
    tmp = CBrCorr("D+2K0elnu" , "411_311_11_12" , 6.8 , 8.83 );
    mDBf[tmp.sDecay] = tmp;
    
    tmp = CBrCorr("D+2K*0elnu" , "411_313_11_12" , 3.1 , 5.53 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+2K2*0elnu" , "411_315_11_12" , 0.9 , 0.15 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+2Kpielnu" , "411_321_211_11_12" , 1. , 0.18 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D+2K0pielnu" , "411_311_211_11_12" , 1. , 0.18 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+pi0elnu" , "411_111_11_12" , 0.31 , 0.405 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+etaelnu" , "411_221_11_12" , 0.3 , 0.114 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+eta'elnu" , "411_331_11_12" , 0.05 , 0.022 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+rho0elnu" , "411_113_11_12" , 0.31 , 0.218 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+omegaelnu" , "411_223_11_12" , 0.31 , 0.182 ); 
    mDBf[tmp.sDecay] = tmp;

 
    tmp = CBrCorr("D+2K0munu" , "411_311_13_14" , 6.8 , 9.3 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D+2K*0munu" , "411_313_13_14" , 3.1 , 5.53 );
    mDBf[tmp.sDecay] = tmp;
     
   tmp = CBrCorr("D+2K2*0munu" , "411_315_13_14" , 0.9 , 0.15 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+2Kpimunu" , "411_321_211_13_14" , 1. , 0.18 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D+2K0pimunu" , "411_311_211_13_14" , 1. , 0.18 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+pi0munu" , "411_111_13_14" , 0.31 , 0.405 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+etamunu" , "411_221_13_14" , 0.3 , 0.114 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+eta'munu" , "411_331_13_14" , 0.05 , 0.022 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+rho0munu" , "411_113_13_14" , 0.31 , 0.218 ); 
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+omegamunu" , "411_223_13_14" , 0.31 , 0.182 ); 
    mDBf[tmp.sDecay] = tmp;
    
    tmp = CBrCorr("D+munu" , "411_13_14" , 0.08 , 3.74E-2 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+taunu" , "411_15_16" , 0.24 , 1.2E-1 );
    mDBf[tmp.sDecay] = tmp;
 
 
 
    tmp = CBrCorr("D02K+elnu" , "421_321_11_12" , 3.41 , 3.57 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D02K*+elnu" , "421_323_11_12" , 2.07 , 2.16 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D02K2*+elnu" , "421_325_11_12" , 0.18 , 0.18 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0pielnu" , "421_211_11_12" , 0.26 , 0.289 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0rhoelnu" , "421_213_11_12" , 0.19 , 0.177 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0b1elnu" , "421_10213_11_12" , 0.05 , 0.05 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D02K+pi0elnu" , "421_321_111_11_12" , 0.22 , 0.12 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D02K0pielnu" , "421_311_211_11_12" , 0.22 , 0.17 );
    mDBf[tmp.sDecay] = tmp;
     
     
     
    tmp = CBrCorr("D02K+munu" , "421_321_13_14" , 3.41 , 3.33 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D02K*+munu" , "421_323_13_14" , 2.07 , 1.92 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D02K2*+munu" , "421_325_13_14" , 0.18 , 0.18 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0pimunu" , "421_211_13_14" , 0.26 , 0.289 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0rhomunu" , "421_213_13_14" , 0.19 , 0.177 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0b1munu" , "421_10213_13_14" , 0.05 , 0.05 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D02K+pi0munu" , "421_321_111_13_14" , 0.22 , 0.12 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D02K0pimunu" , "421_311_211_13_14" , 0.22 , 0.17 );
    mDBf[tmp.sDecay] = tmp;
     
    //D+ hadronic
     /*
    //D+ -> (Kpi)pi PDG 2016
    tmp = CBrCorr("D+rho+K0" , "411_213_311" , 6.4 , 2*6.04 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+a1+K0" , "411_20213_311" , 6.95 , 3. ); //nicht in K0 pipi0!
    //mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+K*0pi" , "411_313_211" , 1.95 , 1.55555556);
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+K0*0pi" , "411_10311_211" , 3.78 , 1.62016202 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+K''*0pi" , "411_30313_211" , 1.47 , 1.39534884 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D+K0pipi0" , "411_311_211_111" , 4.51 , 1.16 );
    mDBf[tmp.sDecay] = tmp;
 
 
    tmp = CBrCorr("D+Kpipi" , "411_321_211_111" , 9.594 , 9.13 );//(wie in tagcor?!)
    //mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D+Kpipipi0" , "411_321_211_211_111" , 6.03 , 5.99 );//(wie in tagcor?!)
    //mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D+Kpipipipi" , "411_321_211_211_211_211" , 0.6252 , 0.56 );//(wie in tagcor?!)
    //mDBf[tmp.sDecay] = tmp;
     
//D0 hadronic K0pipi
 
 
    tmp = CBrCorr("D0rho0K0" , "421_113_311" , 1.02 , 1.29 );//%
    mDBf[tmp.sDecay] = tmp;
     tmp = CBrCorr("D0omegaK0" , "421_223_311" , 2.18 , 2.75 );
    mDBf[tmp.sDecay] = tmp;
     tmp = CBrCorr("D0f0K0" , "421_10221_311" , 1.2 , 0.47 );
    mDBf[tmp.sDecay] = tmp;
     tmp = CBrCorr("D0f'0K0" , "421_10331_311" , 1.2 , 4.67 );
    mDBf[tmp.sDecay] = tmp;
     tmp = CBrCorr("D0K*pi" , "421_313_211" , 5.17 , 5.05 );
    mDBf[tmp.sDecay] = tmp;
     tmp = CBrCorr("D0K0*-pi" , "421_10321_211" , 0.58 , 0.82 );
    mDBf[tmp.sDecay] = tmp;
     tmp = CBrCorr("D0K2*-pi" , "421_325_211" , 0.04 , 0.2 );
    mDBf[tmp.sDecay] = tmp;
 
 
     
    tmp = CBrCorr("D0K+pi" , "421_321_211" , 3.82 , 3.87 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0K+pipi0" , "421_321_211_111" , 13.42 , 13.9 );//nonres (wie in tagcor?!)
   // mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0K+3pi" , "421_321_211_211_211" , 1.17 , 1.88 ); //nonres (wie in tagcor?!)
   // mDBf[tmp.sDecay] = tmp;
     
      
     
    tmp = CBrCorr("D0rhoK-" , "421_213_321" , 8.96 , 11.1 );
    mDBf[tmp.sDecay] = tmp;
     
    tmp = CBrCorr("D0a1K-" , "421_20213_321" , 7.5 , 7.47 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D0K*pi" , "421_323_211" , 5.17 , 8.48 );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D0K0pi0" , "421_311_111" , 2.26 , 1.2 + 1. );
    mDBf[tmp.sDecay] = tmp;
 
    tmp = CBrCorr("D0Kpiomega" , "421_321_211_223" , 2.26 , 3.1 );
    mDBf[tmp.sDecay] = tmp;
 */
    CBrCorr cD0("D0X","421X",0,0);
    CBrCorr cDp("D+X","411X",0,0);
    for(auto it = mDBf.begin(); it!=mDBf.end();it++)
    {
        if(it->first[1] == '2')
        { cD0.MCBr += it->second.MCBr; cD0.Br += it->second.Br;}
        else if(it->first[1] == '1')
        { cDp.MCBr += it->second.MCBr; cDp.Br += it->second.Br;}  
    }
    cD0.Br = 100-cD0.Br;
    cDp.Br = 100-cDp.Br;
    cD0.MCBr = 100-cD0.MCBr;
    cDp.MCBr = 100-cDp.MCBr;
    //cD0.Weight = (cD0.Br)/(cD0.MCBr);
    //cDp.Weight = (cDp.Br)/(cDp.MCBr);
    mDBf[cD0.sDecay] = cD0;
    mDBf[cDp.sDecay] = cDp;
    
    
    
    //DssFix Fix isospin 
 //D**0->
 
 double DssEta = 0.;
 double Dpi = 0.667;
 double Dpi0 = 0.333;
 double Dpipi = 0.3429;
 double Dpipi0 = 0.6476;
 double Dpi0pi0 = 0.0095;

 tmp = CBrCorr("D0*0->D+pi" , 	    	"10421_411_211" , 0.4331 , Dpi ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0pi0" , 	    	"10421_421_111" , 0.2162 , Dpi0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*0pipi" ,    	"10421_423_211_211" , 0.0401 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*+pipi0" ,   	"10421_413_211_111" , 0.0757 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*0pi0pi0" ,  	"10421_423_111_111" , 0.0011 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0pipi" ,     	"10421_421_211_211" , 0.0401 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D+pipi0" ,    	"10421_411_211_111" , 0.0757 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0pi0pi0" , 	"10421_421_111_111" , 0.0011 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*0eta" , 	"10421_423_221" , 0.0585 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0eta" , 		"10421_421_221" , 0.0585 , DssEta  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D1'0->D*+pi" , 		"20423_413_211" , 0.5003 , Dpi  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D*0pi0" , 	"20423_423_111" , 0.2498 , Dpi0 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0pipi" ,     	"20423_421_211_211" , 0.049 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D+pipi0" ,    	"20423_411_211_111" , 0.0925 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0pi0pi0" , 	"20423_421_111_111" , 0.0014 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0eta" , 		"20423_421_221" , 0.0714 , DssEta  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D+rho" , 		"20423_411_213" , 0.0238 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0rho0" , 	"20423_421_113" , 0.0119 , 0  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D10->D*pi" , 		"10423_413_211" , 0.4193 , Dpi*0.64  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->D*0pi0" , 		"10423_423_111" , 0.2093 , Dpi0*0.64 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->D0pipi" ,     	"10423_421_211_211" , 0.1273 , Dpipi*0.36  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->Dpipi0" ,    	"10423_411_211_111" , 0.2405 , Dpipi0*0.36  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->D0pi0pi0" , 	"10423_421_111_111" , 0.0035 , Dpi0pi0*0.36   ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D20->D*pi" , 		"425_413_211" , 0.1167 , Dpi*0.39  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D*0pi0" , 		"425_423_111" , 0.0583 , Dpi0*0.39 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D+pi" , 		"425_411_211" , 0.2335 , Dpi*0.61 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D0pi0" , 		"425_421_111" , 0.1166 , Dpi0*0.61 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D0pipi" ,     	"425_421_211_211" , 0.1086 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D+pipi0" ,    	"425_411_211_111" , 0.2051 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D0pi0pi0" , 	"425_421_111_111" , 0.003 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D0eta" , 		"425_421_221" , 0.1583 , DssEta  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D2S0->D0pipi" ,     	"100421_421_211_211" , 0.1143 , Dpipi*0.25  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D+pipi0" ,    	"100421_411_211_111" , 0.2159 , Dpipi0*0.25  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D0pi0pi0" , 	"100421_421_111_111" , 0.0032 , Dpi0pi0*0.25  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D0*pi" , 		"100421_10411_211" , 0.2223 , Dpi*0.25 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D0*0pi0" , 	"100421_10421_111" , 0.111 , Dpi0*0.25  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D*0pi0" , 	"100421_423_111" , 0.0555 , Dpi0*0.25 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D*+pi" , 		"100421_413_211" , 0.1112 , Dpi*0.25  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D2+pi" , 		"100421_415_211" , 0.1112 , Dpi*0.25 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D20pi0" , 	"100421_425_111" , 0.0555 , Dpi0*0.25 ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D*2S0->D0pipi" ,     	"100423_421_211_211" , 0.1143 ,0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D+pipi0" ,    	"100423_411_211_111" , 0.2159 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D0pi0pi0" , 	"100423_421_111_111" , 0.0032 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D'1+pi" , 	"100423_20413_211" , 0.2223 , 0 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D'10pi0" , 	"100423_20423_111" , 0.111 , 0  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D2S0gamma" , 	"100423_100421_22" , 0.1667 , 0 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D2S+pi" , 	"100423_100411_211" , 0.1112 , Dpi ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D2S0pi0" , 	"100423_100421_111" , 0.0555 , Dpi0 ); mDssFix[tmp.sDecay] = tmp;
 /*
 
 tmp = CBrCorr("D0*0->D+pi" , 	    	"10421_411_211" , 0.4331 , 0.4331 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0pi0" , 	    	"10421_421_111" , 0.2162 ,  0.2162  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*0pipi" ,    	"10421_423_211_211" , 0.0401 , 0.0401  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*+pipi0" ,   	"10421_413_211_111" , 0.0757 , 0.0757  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*0pi0pi0" ,  	"10421_423_111_111" , 0.0011 , 0.0011  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0pipi" ,     	"10421_421_211_211" , 0.0401 , 0.0401  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D+pipi0" ,    	"10421_411_211_111" , 0.0757 , 0.0757  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0pi0pi0" , 	"10421_421_111_111" , 0.0011 , 0.0011  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D*0eta" , 	"10421_423_221" , 0.0585 , 0.0585  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*0->D0eta" , 		"10421_421_221" , 0.0585 , 0.0585  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D1'0->D*+pi" , 		"20423_413_211" , 0.5003 , 0.5003  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D*0pi0" , 	"20423_423_111" , 0.2498 , 0.2498 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0pipi" ,     	"20423_421_211_211" , 0.049 , 0.049  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D+pipi0" ,    	"20423_411_211_111" , 0.0925 , 0.0925  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0pi0pi0" , 	"20423_421_111_111" , 0.0014 , 0.0014 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0eta" , 		"20423_421_221" , 0.0714 , 0.0714  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D+rho" , 		"20423_411_213" , 0.0238 , 0.0238  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'0->D0rho0" , 	"20423_421_113" , 0.0119 , 0.0119  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D10->D*pi" , 		"10423_413_211" , 0.4193 , 0.4193  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->D*0pi0" , 		"10423_423_111" , 0.2093 , 0.2093 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->D0pipi" ,     	"10423_421_211_211" , 0.1273 , 0.1273  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->Dpipi0" ,    	"10423_411_211_111" , 0.2405 , 0.2405   ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D10->D0pi0pi0" , 	"10423_421_111_111" , 0.0035 , 0.0035   ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D20->D*pi" , 		"425_413_211" , 0.1167 , 0.1167  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D*pi0" , 		"425_423_111" , 0.0583 , 0.0583 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D0pi" , 		"425_411_211" , 0.2335 , 0.2335  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D+pi0" , 		"425_421_111" , 0.1166 , 0.1166 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D+pipi" ,     	"425_421_211_211" , 0.1086 , 0.1086  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D0pipi0" ,    	"425_411_211_111" , 0.2051 , 0.2051  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D+pi0pi0" , 	"425_421_111_111" , 0.003 , 0.003  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D20->D+eta" , 		"425_421_221" , 0.1583 ,  0.1583  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D2S0->D+pipi" ,     	"100421_421_211_211" , 0.1143 , 0.1143  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D0pipi0" ,    	"100421_411_211_111" , 0.2159 , 0.2159  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D+pi0pi0" , 	"100421_421_111_111" , 0.0032 , 0.0032  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D0*0pi" , 	"100421_10411_211" , 0.2223 , 0.2223 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D0*+pi0" , 	"100421_10421_111" , 0.111 , 0.111  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D*+pi0" , 	"100421_423_111" , 0.1112 , 0.1112 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D*0pi" , 		"100421_413_211" ,0.0555 , 0.0555  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D20pi" , 		"100421_415_211" , 0.1112 , 0.1112 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S0->D2+pi0" , 	"100421_425_111" , 0.0555 , 0.0555 ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D*2S0->D0pipi" ,     	"100423_421_211_211" , 0.1143 , 0.1143  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D+pipi0" ,    	"100423_411_211_111" , 0.2159 , 0.2159  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D0pi0pi0" , 	"100423_421_111_111" , 0.0032 , 0.0032  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D'1+pi" , 	"100423_20413_211" , 0.2223 , 0.2223 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D'10pi0" , 	"100423_20423_111" , 0.111 , 0.111  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D2S0gamma" , 	"100423_100421_22" , 0.1667 , 0.1667 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D2S+pi" , 	"100423_100411_211" , 0.1112 , 0.1112 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S0->D2S0pi0" , 	"100423_100421_111" , 0.0555 , 0.0555 ); mDssFix[tmp.sDecay] = tmp;
 */
 //D**+ ->
 tmp = CBrCorr("D0*+->D0pi" , 	    "10411_421_211" , 	mDssFix["10421_421_111"].MCBr , mDssFix["10421_411_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D+pi0" , 	    "10411_411_111" , 	mDssFix["10421_411_211"].MCBr , mDssFix["10421_421_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D*+pipi" ,    "10411_413_211_211" , mDssFix["10421_423_211_211"].MCBr , mDssFix["10421_423_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D*0pipi0" ,   "10411_423_211_111" , mDssFix["10421_413_211_111"].MCBr , mDssFix["10421_413_211_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D*+pi0pi0" ,  "10411_413_111_111" , mDssFix["10421_423_111_111"].MCBr , mDssFix["10421_423_111_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D+pipi" ,     "10411_411_211_211" ,mDssFix["10421_421_211_211"].MCBr , mDssFix["10421_421_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D0pipi0" ,    "10411_421_211_111" ,  mDssFix["10421_411_211_111"].MCBr , mDssFix["10421_411_211_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D+pi0pi0" , 	"10411_411_111_111" ,  mDssFix["10421_421_111_111"].MCBr , mDssFix["10421_421_111_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D*+eta" , 	"10411_413_221" , 	mDssFix["10421_423_221"].MCBr , mDssFix["10421_423_221"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D+eta" , 		"10411_411_221" , 	mDssFix["10421_421_221"].MCBr , mDssFix["10421_421_221"].Br  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D1'+->D*0pi" , 		"20413_423_211" , mDssFix["20423_423_111"].MCBr , mDssFix["20423_413_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D*+pi0" , 	"20413_413_111" , mDssFix["20423_413_211"].MCBr , mDssFix["20423_423_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D+pipi" ,     "20413_411_211_211" , mDssFix["20423_421_211_211"].MCBr , mDssFix["20423_421_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D0pipi0" ,    "20413_421_211_111" , mDssFix["20423_411_211_111"].MCBr , mDssFix["20423_411_211_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D+pi0pi0" , 	"20413_411_111_111" , mDssFix["20423_421_111_111"].MCBr , mDssFix["20423_421_111_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D+eta" , 		"20413_411_221" , mDssFix["20423_421_221"].MCBr , mDssFix["20423_421_221"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D0rho" , 		"20413_421_213" , mDssFix["20423_411_213"].MCBr , mDssFix["20423_411_213"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D+rho0" , 	"20413_411_113" , mDssFix["20423_421_113"].MCBr , mDssFix["20423_421_113"].Br  ); mDssFix[tmp.sDecay] = tmp;
 
 
 tmp = CBrCorr("D1+->D*0pi" , 		"10413_423_211" , mDssFix["10423_423_111"].MCBr , mDssFix["10423_413_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D*+pi0" , 		"10413_413_111" , mDssFix["10423_413_211"].MCBr , mDssFix["10423_423_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D+pipi" ,     	"10413_411_211_211" , mDssFix["10423_421_211_211"].MCBr , mDssFix["10423_421_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D0pipi0" ,    	"10413_421_211_111" , mDssFix["10423_411_211_111"].MCBr , mDssFix["10423_411_211_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D+pi0pi0" , 	"10413_411_111_111" , mDssFix["10423_421_111_111"].MCBr , mDssFix["10423_421_111_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 
 
 tmp = CBrCorr("D2+->D*0pi" , 		"415_423_211" , mDssFix["425_423_111"].MCBr , mDssFix["425_413_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D*+pi0" , 		"415_413_111" , mDssFix["425_413_211"].MCBr , mDssFix["425_423_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D0pi" , 		"415_421_211" , mDssFix["425_421_111"].MCBr , mDssFix["425_411_211"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D+pi0" , 		"415_411_111" , mDssFix["425_411_211"].MCBr , mDssFix["425_421_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D+pipi" ,     	"415_411_211_211" , mDssFix["425_421_211_211"].MCBr , mDssFix["425_421_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D0pipi0" ,    	"415_421_211_111" , mDssFix["425_411_211_111"].MCBr , mDssFix["425_411_211_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D+pi0pi0" , 	"415_411_111_111" , mDssFix["425_421_111_111"].MCBr , mDssFix["425_421_111_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D+eta" , 		"415_411_221" , mDssFix["425_421_221"].MCBr , mDssFix["425_421_221"].Br  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D2S+->D+pipi" ,     	"100411_411_211_211" , mDssFix["100421_421_211_211"].MCBr , mDssFix["100421_421_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0pipi0" ,    	"100411_421_211_111" , mDssFix["100421_411_211_111"].MCBr , mDssFix["100421_411_211_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D+pi0pi0" , 	"100411_411_111_111" , mDssFix["100421_421_111_111"].MCBr , mDssFix["100421_421_111_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0*0pi" , 	"100411_10421_211" , mDssFix["100421_10421_111"].MCBr , mDssFix["100421_10411_211"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0*+pi0" , 	"100411_10411_111" , mDssFix["100421_10411_211"].MCBr , mDssFix["100421_10421_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D*+pi0" , 	"100411_413_111" , mDssFix["100421_413_211"].MCBr , mDssFix["100421_423_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D*0pi" , 		"100411_423_211" ,mDssFix["100421_423_111"].MCBr , mDssFix["100421_413_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D20pi" , 		"100411_425_211" , mDssFix["100421_425_111"].MCBr , mDssFix["100421_415_211"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D2+pi0" , 	"100411_415_111" , mDssFix["100421_415_211"].MCBr , mDssFix["100421_425_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 
 
 tmp = CBrCorr("D*2S+->D+pipi" ,     	"100413_411_211_211" , mDssFix["100423_421_211_211"].MCBr , mDssFix["100423_421_211_211"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D0pipi0" ,    	"100413_421_211_111" , mDssFix["100423_411_211_111"].MCBr , mDssFix["100423_411_211_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D+pi0pi0" , 	"100413_411_111_111" , mDssFix["100423_421_111_111"].MCBr , mDssFix["100423_421_111_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D'10pi" , 	"100413_20423_211" , mDssFix["100423_20423_111"].MCBr , mDssFix["100423_20413_211"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D'1+pi0" , 	"100413_20413_111" , mDssFix["100423_20413_211"].MCBr , mDssFix["100423_20423_111"].Br  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S+gamma" , 	"100413_100411_22" , mDssFix["100423_100421_22"].MCBr , mDssFix["100423_100421_22"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S0pi" , 	"100413_100421_211" , mDssFix["100423_100421_111"].MCBr , mDssFix["100423_100411_211"].Br ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S+pi0" , 	"100413_100411_111" , mDssFix["100423_100411_211"].MCBr , mDssFix["100423_100421_111"].Br ); mDssFix[tmp.sDecay] = tmp;
 
 for(auto mt = mDssFix.begin(); mt != mDssFix.end(); ++mt){
 
 	cout<<mt->second.Name<<" "<<mt->second.Weight()<<" "<<mt->second.MCBr<<" "<<mt->second.Br<<endl;
 
 }
 
 /*
 tmp = CBrCorr("D0*+->D*+pi0" , "10411_413_111" , 1. , 0.5  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D*0pi" , "10411_423_211" , 1. , 2.  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D1'+->D*+pi0" , "20413_413_111" , 1. , 0.499 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D*0pi" , "20413_423_211" , 1. , 2.003  ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D1+->D*+pi0" , "10413_413_111" , 1. , 0.499 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D*0pi" , "10413_423_211" , 1. , 2.003  ); mDssFix[tmp.sDecay] = tmp;

 tmp = CBrCorr("D2+->D*+pi0" , "415_413_111" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D*0pi" , "415_423_211" , 1. , 2.  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D0pi" , "415_421_211" , 1. , 2. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D+pi0" , "415_411_111" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D2S+->D*+pi0" , "100411_413_111" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D*0pi" , "100411_423_211" , 1. , 2.003  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0*0pi" , "100411_10421_211" , 1. , 2.003 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0*+pi0" , "100411_10411_111" , 1. , 0.5  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D20pi" , "100411_425_211" , 1. , 2.003 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D2+pi0" , "100411_415_111" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;

 tmp = CBrCorr("D*2S+->D'10pi" , "100413_20423_211" , 1. , 2.00 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D'1+pi0" , "100413_20413_111" , 1. , 0.5  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S0pi" , "100413_100421_211" , 1. , 2. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S+pi0" , "100413_100411_111" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;
*/
/* tmp = CBrCorr("D1+->D*+" , "10413_413" , 1. , 0.499 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D*0" , "10413_423" , 1. , 2.003  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D0" , "10413_421" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1+->D+" , "10413_411" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D2+->D*+" , "415_413" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D*0" , "415_423" , 1. , 2.  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D0" , "415_421" , 1. , 1.565 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2+->D+" , "415_411" , 1. , 0.639 ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D0*+->D*+" , "10411_413" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D*0" , "10411_423" , 1. , 1.  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D0" , "10411_421" , 1. , 1.825 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D0*+->D+" , "10411_411" , 1. , 0.548 ); mDssFix[tmp.sDecay] = tmp;
 
 tmp = CBrCorr("D1'+->D*+" , "20413_413" , 1. , 0.499 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D*0" , "20413_423" , 1. , 2.003  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D0" , "20413_421" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D1'+->D+" , "20413_411" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 
 
 
 tmp = CBrCorr("D2S+->D*+" , "100411_413" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D*0" , "100411_423" , 1. , 2.003  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0" , "100411_421" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D+" , "100411_411" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0*0" , "100411_10421" , 1. , 2.003 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D0*+" , "100411_10411" , 1. , 0.5  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D20" , "100411_425" , 1. , 2.003 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D2S+->D2+" , "100411_415" , 1. , 0.5 ); mDssFix[tmp.sDecay] = tmp;


 tmp = CBrCorr("D*2S+->D*+" , "100413_413" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D*0" , "100413_423" , 1. , 1.  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D0" , "100413_421" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D+" , "100413_411" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D'10" , "100413_20423" , 1. , 2.003 ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D'1+" , "100413_20413" , 1. , 0.5  ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S0" , "100413_100421" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
 tmp = CBrCorr("D*2S+->D2S+" , "100413_100411" , 1. , 1. ); mDssFix[tmp.sDecay] = tmp;
*/
 
}


float CorrectBf::FixDss(string &s)
{
    if(s[0]=='0') return 1.;
    double weight=1;
    string stmp = s;
    NoCharge(stmp);
    Ddecays.clear();
    splitD(stmp);
    for(std::vector<string>::iterator it = Ddecays.begin();it!= Ddecays.end(); it++){
	    for(auto mt = mDssFix.begin(); mt != mDssFix.end(); ++mt){
	    
	    	if(it->find(mt->first) == 0){
	    		weight *= mt->second.Weight();
	    	 	if(!(weight>=0 && weight<20))
    				cout<<mt->first<<" "<<weight<<endl;
   
	    		
	    	}
	    		
	    
	    }
    }
    Ddecays.clear();
    return weight;
}

float CorrectBf::FixDss(char *s)
{
    if(s[0]=='0') return 1.;
    double weight=1;
    string stmp = s;
    NoCharge(stmp);
    Ddecays.clear();
    splitD(stmp);
    for(std::vector<string>::iterator it = Ddecays.begin();it!= Ddecays.end(); it++){
	    for(auto mt = mDssFix.begin(); mt != mDssFix.end(); ++mt){
	    
	    	if(it->find(mt->first) == 0){
	    		weight *= mt->second.Weight();
	    	 	if(!(weight>=0 && weight<20))
    				cout<<mt->first<<" "<<weight<<endl;
   
	    		
	    	}
	    }
    }
    Ddecays.clear();
    return weight;
}



float CorrectBf::weightB(int lcl, int dcl)
{
 
    int lclass;
    for(std::vector<CBrCorr>::iterator it = vBBf.begin();
            it != vBBf.end(); it++)
    {
        if(it -> Type == 'e')
           lclass= abs(lcl);
        else
            lclass =lcl;
 
        if(it -> lclass == lclass)
        {
            if(it -> dclass == dcl)
        	{
        		//cout<<it->Weight()<<" "<<lcl<<" "<<lclass<<" "<<dcl<<" "<<it->Br<<endl;
        		fprintf(fpLog,"%s\t%i\t%i\t%i\t%f\n",it->Name.c_str(), lcl, lclass, dcl, it->Weight());
                	return it -> Weight();
        	}
        }
 
    }
 
    return 1.;
 
 
}
 
/*
 
void print_all(string s)
{
    for(int i =0; i<= s.capacity(); i++)
    {
        if(s[i] == '\n') cout<<"\\n";
        else if(s[i] == '\0') cout<<"\\0";
        else if(s[i] == '\t') cout<<"\\t";
        else cout<<s[i];
    }
    cout<<endl;
}
*/
float CorrectBf::weight(string s, std::map<string,CBrCorr> &m)
{
    NoCharge(s); //so far everything charge independent
    float fWeight;
 
    std::map<string,CBrCorr>::iterator it = m.find(string(s.c_str()));
    if(it != m.end())
    {
        fWeight = it->second.Weight();
    fprintf(fpLog,"%s\t%f\n", s.c_str(), fWeight);
    }
    else
    {
        size_t first = s.find_first_of('_');
        string sNew = s.substr(0,first)+"X";
        //cout<<"search "<<sNew<<endl;
        std::map<string,CBrCorr>::iterator it = m.find(string(sNew.c_str()));
        if(it != m.end())
    {
            fWeight = it->second.Weight();
        fprintf(fpLog,"%s\t%f\n", sNew.c_str(), fWeight);
    }
        else
            fWeight = 1;
         
    }
 
    return fWeight;
 
}
 
float CorrectBf::weightB(string &s)
{
    if(s[0]=='0') return 1.;
    string stmp = s;
    NoCharge(stmp);
    hBdecays->Fill(stmp.c_str(),1.);
    return weight(s,mBBf);
}
 
float CorrectBf::weightB(char *s)
{
    if(s[0]=='0') return 1.;
    string stmp = string(s);
    NoCharge(stmp);
    hBdecays->Fill(stmp.c_str(),1.);
    return weight(s,mBBf);
}
 
float CorrectBf::weightD(string &s)
{
    if(s[0]=='0') return 1.;
    splitD(s);
    string stmp;
            
    float fWeight = 1.;
    if(Ddecays.size()>0)
    {
        for(std::vector<string>::iterator it = Ddecays.begin();
            it!= Ddecays.end(); it++)
        {
        fWeight *= weight(*it,mDBf);
        stmp = *it;
        NoCharge(stmp);
        hDdecays->Fill(stmp.c_str(),1.);
        }
    }
 
    Ddecays.clear();
    return fWeight;
}
 
float CorrectBf::weightD(char *s)
{
    if(s[0]=='0') return 1.;
    splitD(s);
    string stmp;
            
    float fWeight = 1.;
    if(Ddecays.size()>0)
    {
        for(std::vector<string>::iterator it = Ddecays.begin();
            it!= Ddecays.end(); it++)
        {
        fWeight *= weight(*it,mDBf);
        stmp = *it;
        NoCharge(stmp);
        hDdecays->Fill(stmp.c_str(),1.);
        }
    }
 
    Ddecays.clear();
    //cout<<fWeight<<endl;
    return fWeight;
}
 
void CorrectBf::PrintMaxima(TH1F* hist, int nmax)
{
    fprintf(fpLog,"\n\n------------------------\n print most common decays: \n");
    int maxbin;
    for(int i = 0; i<nmax; i++)
    {
        if(i>hist->GetNbinsX())continue;
 
        maxbin = hist->GetMaximumBin();
        if(hist->GetBinContent(maxbin)<=0) break;
 
        fprintf(fpLog,"%s\t\t\t%i\n",
            hist->GetXaxis()->GetBinLabel(maxbin),
            (int)hist->GetBinContent(maxbin));
 
        hist->SetBinContent(maxbin,0);
    }
    fprintf(fpLog,"\n\n------------------------\n\n");
}
 
void CorrectBf::split(string s)
{
    //split aa(bb)cc to aacc, bb
    size_t first=0, last;
    string stmp;
    first = s.find_first_of('('); //search for the first opening and closing bracket
    if(first!=string::npos)
    {
        last = s.find_last_of(')');
        if(last == string::npos){ 
     //       cout<<"CorrectBf::splitD: missing closing bracket in "<<s<<'\n';
            fprintf(fpLog,"CorrectBf::splitD: missing closing bracket in %s\n",s.c_str());
            return;
        }
        stmp = s.substr(0,first) + s.substr(last+1); //keep whats outside the outer brackets
        Ddecays.push_back(stmp);
        stmp = s.substr(first+1,last-first-1); //pass whats inside the brackets agin
        splitD(stmp);
         
    }
    else if (s[0] != '0') //if not '0' string and no brackets
        Ddecays.push_back( s );
    else return;
}
 
void CorrectBf::splitD(string s)
{
    //split ab(c)d to abd, bc
    size_t first=0, last;
    string stmp;
            //cout<<"CorrectBf::received: "<<s<<endl;
    first = s.find_first_of('('); //search for the first opening and closing bracket
    if(first!=string::npos)
    {
        last = s.find_last_of(')');
        if(last == string::npos){ 
     //       cout<<"CorrectBf::splitD: missing closing bracket in "<<s<<'\n';
            fprintf(fpLog,"CorrectBf::splitD: missing closing bracket in %s\n",s.c_str());
            return;
        }
        stmp = s.substr(0,first) + s.substr(last+1); //keep whats outside the outer brackets
            //cout<<"CorrectBf::push_back: "<<stmp<<endl;
        Ddecays.push_back(stmp);
    size_t idx = s.find_last_of("+-_",first-1); //get the number right before the brackets
    //cout<<s<<" "<<idx<<endl;
    if(idx==0){cout<<"AUA"<<endl; }
    if(s[idx] == '_')
            stmp = s.substr(idx+1, first - idx-1) + s.substr(first+1,last-first-1); //pass whats before and inside the brackets agin
        else
            stmp = s.substr(idx, first - idx) + s.substr(first+1,last-first-1); //pass whats before and inside the brackets agin
        
            //cout<<"CorrectBf::pass: "<<stmp<<endl;
        splitD(stmp);
         
    }
    else if (s[0] != '0') //if not '0' string and no brackets
        Ddecays.push_back( s );
    else return;
}
 
vector<string>* CorrectBf::SplitDString(string &s)
{
   vector<string> *DDec = new vector<string>;
    
    //split ab(c)d to abd, bc
    size_t first=0, last;
    string stmp;
            //cout<<"CorrectBf::received: "<<s<<endl;
    first = s.find_first_of('('); //search for the first opening and closing bracket
    if(first!=string::npos)
    {
        last = s.find_last_of(')');
        if(last == string::npos){ 
            cout<<"CorrectBf::splitD: missing closing bracket in "<<s<<'\n';
         //   fprintf(fpLog,"CorrectBf::splitD: missing closing bracket in %s\n",s.c_str());
            return DDec;
        }
        stmp = s.substr(0,first) + s.substr(last+1); //keep whats outside the outer brackets
            //cout<<"CorrectBf::push_back: "<<stmp<<endl;
             
        DDec->push_back(stmp);
       
    size_t idx = s.find_last_of("+-_",first-1); //get the number right before the brackets
       if(s[idx] == '_')
            stmp = s.substr(idx+1, first - idx-1) + s.substr(first+1,last-first-1); //pass whats before and inside the brackets agin
        else
            stmp = s.substr(idx, first - idx) + s.substr(first+1,last-first-1); //pass whats before and inside the brackets agin
        
           // cout<<"CorrectBf::pass: "<<stmp<<endl;
    vector<string> *DDec2 =  SplitDString(stmp);
    for(int i = 0; i< DDec2->size(); i++)
    {
        DDec->push_back((*DDec2)[i]);
    }
        delete DDec2;
    } else if (s[0] != '0'){
        DDec->push_back(s);
    }
    return DDec;    
}
 
void CorrectBf::EqualCP( string &dec)
{
 
    if(dec[0] == '+')
        return;
 
    for(unsigned i = 0; i<dec.length(); i++)
    {
        if(dec[i] == '+') dec[i] = '-';
        else if(dec[i] == '-') dec[i] = '+';
    }
    return;
}
 
void CorrectBf::NoCharge(string &dec)
{
 
    if(dec[0] == '+' || dec[0] == '-')//remove leading sign
    {
        for(unsigned i = 0; i<dec.length()-1; i++)
        {
            if(dec[i+1] == '+' || dec[i+1] == '-') 
                dec[i] = '_';
            else dec[i] = dec[i+1];
        }
        dec.erase(dec.end()-1);
    } else
    {
        for(unsigned i = 0; i<dec.length(); i++)
        {
            if(dec[i] == '+' || dec[i] == '-') dec[i] = '_';
        }
    }
             
    return;
 
}
 
string EqualCP( string dec)
{
 
    if(dec[0] == '+')
        return dec;
 
    for(unsigned i = 0; i<dec.length(); i++)
    {
        if(dec[i] == '+') dec[i] = '-';
        else if(dec[i] == '-') dec[i] = '+';
    }
    return dec;
}
 
string NoCharge(string dec)
{
 
    if(dec[0] == '+' || dec[0] == '-')//remove leading sign
    {
        for(unsigned i = 0; i<dec.length()-1; i++)
        {
            if(dec[i+1] == '+' || dec[i+1] == '-') dec[i] = '_';
            else dec[i] = dec[i+1];
        }
        dec.erase(dec.end()-1);
    } else
    {
        for(unsigned i = 0; i<dec.length(); i++)
        {
            if(dec[i] == '+' || dec[i] == '-') dec[i] = '_';
        }
    }
             
    return dec;
 
}
 
string NoSubDecay(string &dec)
{
 
    string dec_tmp;
    int j = 0;
    int nBrackets = 0;
 
    for(unsigned i = 0; i<dec.length();i++)
    {
        if(dec[i] == '(') {nBrackets++; continue;}
        else if(dec[i] == ')') {nBrackets--; continue;}
 
        if(!nBrackets)
        {
            dec_tmp.push_back( dec[i] );
            j++;
        }
    }
    if(nBrackets != 0) 
    {
        //cout<<"Error: unmatching brackets! ("<<nBrackets<<")" <<"\n string: "<<dec<<endl;
        return string(dec);
    }
    return dec_tmp;
 
}
 
/*
string GetSubDecay(string dec, bool fl_return_null = true)
{
 
    unsigned j;
    bool fl_match = false;
    for( unsigned i = 0; i<dec.length(); ++i)
    {
        if(dec[i]== '(')
        {//get not only the string within the brackets, but the number before, too
            for(j = i-1; j>0;j--)
            {
                if(dec[j]== '_' || dec[j] == '+' || dec[j] == '-')
                {
                    fl_match =true;
                    break;
                }
            }
        }
 
        if(fl_match) break;
    }
    //subdecy found?
    if(!fl_match)
    {
        if(fl_return_null) return string("0");
        else return dec;
    }
    string dec_tmp;
    int nBrackets = 0;
    for(unsigned i = 0;j<dec.length();j++,i++)
    {
        if(dec[j] == '(')
            nBrackets++;
         
        if(dec[j] == ')')
            nBrackets--;
        if(nBrackets == 0)
        {
            if(dec[j]==')') break; 
            dec_tmp.push_back( dec[j]);
        }
        else if(nBrackets == 1)
        {
            if(dec[j]=='(') {i--;continue;}
            dec_tmp.push_back( dec[j]);
        }
        else 
        {
            dec_tmp.push_back( dec[j]);
        }
 
 
    }
 
    if(nBrackets != 0) 
    {
        //cout<<"Error: unmatching brackets! ("<<nBrackets<<")" <<"\n string: "<<dec<<endl;
        return dec;
    }
    return dec_tmp;
 
 
}
*/
/*
float BrCorrection(int lclass, int dclass, char* BDecay, char* DDecay)
{
 
    float weight = 1;
    bool fl_match = false;
    string BDecay_tmp;
    int nDDecay_lvl = 0;
    string DDecay_tmp;
    string DDecay_tmp_nosub;
    string DDecay_tmp1;
    string DDecay_tmp_nosub1;
    string DDecay_tmp2;
    string DDecay_tmp_nosub2;
     
 
        BDecay_tmp.assign( NoCharge( BDecay ) );
 
    if(DDecay[0]!='0')
    {
        DDecay_tmp.assign( NoCharge( DDecay ) );
        DDecay_tmp_nosub.assign( NoSubDecay( DDecay_tmp ) );
 
        if(DDecay_tmp_nosub[0] != '0')
        {
            DDecay_tmp1.assign( GetSubDecay(DDecay_tmp) );
            DDecay_tmp_nosub1.assign( NoSubDecay( DDecay_tmp1 ) );
            if(DDecay_tmp_nosub1[0] != '0')
            {
                DDecay_tmp2.assign( GetSubDecay(GetSubDecay(DDecay_tmp)) );
                DDecay_tmp_nosub2.assign( NoSubDecay( DDecay_tmp2 ) );
                if(DDecay_tmp_nosub2[0] != '0')
                    nDDecay_lvl = 3;
                else nDDecay_lvl =2;
            }
            else nDDecay_lvl =1;
        }
        else nDDecay_lvl = 0;
    }
    else nDDecay_lvl =0;
 
    for(std::vector<CBrCorr>::iterator it = VBrCorr.begin(); 
            it != VBrCorr.end(); ++it )
    {
        if(it->Type == 'e')
        {
            if(it->lclass<100 && it->lclass != abs(lclass) ) continue;
            if(it->dclass<100 && it->dclass != abs(dclass) ) continue;
            if(it->BDecay[0] != '0' && BDecay_tmp.find( it->BDecay ) == string::npos  ) continue;
        if(it->DDecay[0] != '0')
            {
                if(nDDecay_lvl>0)
                {
                    if(DDecay_tmp_nosub.find( it->DDecay ) != string::npos  )
                    {
                    weight *= it->Weight;
                        if(_BrLog)
                        fprintf(BrCorrLog, "1 %s\t%i(%i)\t%i(%i)\t%s(%s)\t%s(%s/%s)\t%f\n",
                        it->Name.c_str(), it->lclass, lclass,  it->dclass, dclass, 
                        it->BDecay.c_str(), BDecay, it->DDecay.c_str(), DDecay_tmp_nosub.c_str(),DDecay, it->Weight  );
                    }
 
                    if(nDDecay_lvl>1)
                    {
                        if(DDecay_tmp_nosub1.find( it->DDecay ) != string::npos  )
                        {
                        weight *= it->Weight;
                            if(_BrLog)
                            fprintf(BrCorrLog, "2 %s\t%i(%i)\t%i(%i)\t%s(%s)\t%s(%s/%s)\t%f\n",
                            it->Name.c_str(), it->lclass, lclass,  it->dclass, dclass, 
                            it->BDecay.c_str(), BDecay, it->DDecay.c_str(), DDecay_tmp_nosub1.c_str(),DDecay, it->Weight  );
                        }
                        if(nDDecay_lvl>2)
                        {
                            if(DDecay_tmp_nosub2.find( it->DDecay ) != string::npos  )
                            {
                            weight *= it->Weight;
                                if(_BrLog)
                                fprintf(BrCorrLog, "3 %s\t%i(%i)\t%i(%i)\t%s(%s)\t%s(%s/%s)\t%f\n",
                                it->Name.c_str(), it->lclass, lclass,  it->dclass, dclass, 
                                it->BDecay.c_str(), BDecay, it->DDecay.c_str(), DDecay_tmp_nosub2.c_str(),DDecay, it->Weight  );
                            }
                        }
                        continue;
                    }
                    continue;
                }
                continue;
            }
 
        
 
        }else{
            if(it->lclass<100 && it->lclass != lclass ) continue;
            if(it->dclass<100 && it->dclass != dclass ) continue;
            BDecay_tmp.assign( BDecay );
            if(it->BDecay[0] != '0' && BDecay_tmp.find( it->BDecay ) == string::npos  ) continue;
            DDecay_tmp.assign( DDecay );
            if(it->DDecay[0] != '0' && DDecay_tmp.find( it->DDecay ) == string::npos  ) continue;
        }
 
        weight *= it->Weight;
        if(_BrLog)
        fprintf(BrCorrLog, "%s\t%i(%i)\t%i(%i)\t%s(%s)\t%s(%s)\t%f\n",
            it->Name.c_str(), it->lclass, lclass,  it->dclass, dclass, 
            it->BDecay.c_str(), BDecay, it->DDecay.c_str(), DDecay, it->Weight  );
        break;
 
    }
 
 
 
    return weight;
};
*/
