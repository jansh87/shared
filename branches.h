
    struct t_run { float etot; float eher; float eler; float eth; int exp; int num; } run;
    struct t_evtnr { int num; } evtnr;
    struct t_lep { float elid; float muid; float atckpi; float atcpk; float atcppi;
	     float e; float p; float th; 
	     float dr; float dz; 
	     float es; float ps; float ths; 
    	     float ec; float pc; float thc; 
	     int id_truth;
	     int q; int mother_id; int fl_lep; int fl_mother;
    } lep1, lep2;
    struct t_dilep { 
	     float e; float p; float th; 
	     float es; float ps; float ths; 
    	     float ec; float pc; float thc;
	     float m2; 
	     float th_ll; float ths_ll;
    } dilep;
    struct t_miss {
    	     float e; float p; float th; float m2;
    	     float es; float ps; float ths;
    	     float ec; float pc; float thc;
    } miss, gmiss, emiss,extra, x, gx,vis;
    struct t_xlep {
    	     float e; float p; float th; float m2;
    	     float es; float ps; float ths;
    	     float ec; float pc; float thc;
	     float th_xl; float ths_xl;
	     float vtx_prob; float vtx_prob2;
    } xlep;
    struct t_truth {
	     float q2; float p_l;
	     float w; float costh;
	     float m;
	     float th; float thc; float ths;
	     float p; float pc; float ps;
	     float miss_m2;
	     float miss_e; float miss_p; float miss_th;
	     float miss_es; float miss_ps; float miss_ths;
	     int nkl; int nch;
    } truth;
    struct t_xc {
	    float m2; float q2; float ps;
	    int id; int daughters; int meson;
    } xc1, xc2;
    struct t_event {
	   float Eecl; float q2; 
	   float cos_thrA; float cos_thrA2; float cos_thrAm; float cos_thrB; float cos_thrC;
	   float thrX; float thrSigX; float thrSig2X; float thrSigXm;
	   int nch; int nn; int npi0; int q; int nk; int lclass; int dclass; int BB;
    } event;
    struct t_eecl {std::vector<float> energy; std::vector<float> phi; std::vector<float> theta; std::vector<float> r; 
	   std::vector<float> e9oe25; std::vector<float> width;
	   std::vector<int> nhits; std::vector<int> info; } ECLInfo, EFCInfo;
  
    struct t_tag { 
      float pcode_b; float b_mode; float sub1_mod; float sub2_mod; float sub3_mod;
      float sub4_mod; float MCinfo; float NB; float contNB; float m_bc; float delta_e;
      float cos_thr; float thr; float p; 
      float p1; float p2; float p3; float e;
      float p1_reco; float p2_reco; float p3_reco; float e_reco;
      int NFS; int fl_tag;/*int mctype;int pi0;int charged;int truth;*/} btag;

	std::vector<double> trk_dedx; 
    	std::vector<float> trk_p;  
    	std::vector<float> trk_p1;  
    	std::vector<float> trk_p2;  
    	std::vector<float> trk_p3;  
    	std::vector<float> trk_e;  
    	std::vector<float> trk_gen_p1;  
    	std::vector<float> trk_gen_p2;  
    	std::vector<float> trk_gen_p3;  
    	std::vector<float> trk_gen_e;  
    	std::vector<float> trk_th;  
	std::vector<float> cal_e ;
	std::vector<float> cal_th ;
	std::vector<float> cal_e9e25 ;
	std::vector<float> gam_p1 ;
	std::vector<float> gam_p2 ;
	std::vector<float> gam_p3 ;
	std::vector<float> gam_p1_true ;
	std::vector<float> gam_p2_true ;
	std::vector<float> gam_p3_true ;
	std::vector<int> cal_mother ;

    	std::vector<int> trk_sep;
    	std::vector<int> trk_svd_hitmap;

	char sBDecay[150];
	char sDDecay[150];
	std::vector<int> trk_nhits0; 
	std::vector<int> trk_nhits1 ;
	std::vector<int> trk_nhits3 ;
	std::vector<int> trk_nhits4 ;
               
	std::vector<float> trk_el_id; 

	std::vector<float> trk_mu_id ;

	std::vector<float> trk_pi_chi2 ;
	std::vector<int> trk_pi_ndf ;

	std::vector<float> trk_kpi ;
	std::vector<float> trk_ppi ;
	std::vector<float> trk_pk ;
	std::vector<float> trk_dr ;
	std::vector<float> trk_dz ;
	
	
	std::vector<int> trk_gen_id; 
   	std::vector<int> trk_gen_is;
	std::vector<int> trk_gen_mo_is;

