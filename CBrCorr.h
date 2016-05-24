

class CBrCorr
{
    public:
        string Name;
        char Type; //type: e = same error for +-; n = take charge into account

        int lclass;
        int dclass;
        string sDecay;

        float MCBr;
        float Br;
        float Weight(){return Br/MCBr;};

        CBrCorr(){};
        CBrCorr(string, int, int, float, float, char type = 'e');
        CBrCorr(string, string , float, float, char type = 'e');
};



CBrCorr::CBrCorr(string n, int clc, int dcl, float mc, float br, char type)
{
    Name.assign( n );
    Type = type;

    lclass  = clc;
    dclass  = dcl;

    sDecay.assign("0");

    MCBr    = mc;
    Br      = br;

    
};


CBrCorr::CBrCorr(string n,string bd, float mc, float br, char type)
{
    Name.assign( n );
    Type = type;

    lclass  = 100;
    dclass  = 100;

    sDecay.assign( bd );

    MCBr    = mc;
    Br      = br;

   
};
