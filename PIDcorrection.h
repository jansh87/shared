
//Efficiency of lepton identification

//Fake rates of lepton identification for pions

TFile *f1=0;
TH2F *hid =0;
TH2F *hid_eid_svd1 =0;
TH2F *hid_eid_svd2 =0;
TH2F *hid_muid_7_27 =0;
TH2F *hid_muid_31_39 =0;
TH2F *hid_muid_41_49 =0;
TH2F *hid_muid_51_65 =0;
TH2F *hid_kid =0;

void InitPID()
{
      f1= new TFile("PID_eid_caseB_e7-27.root");
      hid_eid_svd1 = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_eid_svd1 -> SetDirectory(0);
      f1->Close();
      f1->Delete();
      f1= new TFile("PID_eid_caseB_e31-65.root");
      hid_eid_svd2 = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_eid_svd2 -> SetDirectory(0);

      f1->Close();
      f1->Delete();
      f1= new TFile("PID_muid_caseB_e7-27.root");
      hid_muid_7_27 = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_muid_7_27 -> SetDirectory(0);

      f1->Close();
      f1->Delete();
      f1= new TFile("PID_muid_caseB_e31-39.root");
      hid_muid_31_39 = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_muid_31_39 -> SetDirectory(0);

      f1->Close();
      f1->Delete();
      f1= new TFile("PID_muid_caseB_e41-49.root");
      hid_muid_41_49 = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_muid_41_49 -> SetDirectory(0);

      f1->Close();
      f1->Delete();
      f1= new TFile("PID_muid_caseB_e51-65.root");
      hid_muid_51_65 = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_muid_51_65 -> SetDirectory(0);

      f1->Close();
      f1->Delete();
      f1= new TFile("kid.root");
      hid_kid = (TH2F*)((TH2F*) gDirectory->Get("id"))->Clone();
      hid_kid -> SetDirectory(0);

      f1->Close();
      f1->Delete();


}


#ifndef NOPID
	cout<<"----------------\n"
	<<"init PID corrections\n"
	cout<<"----------------"<<endl;
	InitPID();
#else
	cout<<"----------------\n"
	<<"PID corrections NOT available!\n"
	cout<<"----------------"<<endl;
#endif

float LepID(int leptag, double exp_no, double plab, double thetalab){

    if(exp_no<30&&leptag==0) 
	    hid = hid_eid_svd1;
    if(exp_no>30&&leptag==0)
	    hid = hid_eid_svd2;
    if(exp_no<30&&leptag==1)
	    hid = hid_muid_7_27;
    if(exp_no>30&&exp_no<40&&leptag==1)
	    hid = hid_muid_31_39;
    if(exp_no>40&&exp_no<50&&leptag==1)
	    hid = hid_muid_41_49;
    if(exp_no>50&&leptag==1)
	    hid = hid_muid_51_65;

    //TH2F* hidstat = (TH2F*) gDirectory->Get("idstat");
    //TH2F* hidsys1 = (TH2F*) gDirectory->Get("idsys1");
    //TH2F* hidsys2 = (TH2F*) gDirectory->Get("idsys2");

    return hid->GetBinContent(hid->FindBin(plab,thetalab));
    //cout<<"bin weight "<<hid->GetBinContent(hid->FindBin(plab,thetalab))<<endl;

}
//kaon/pion id
float KID(double plab, double thetalab){
  int np(31);
  if(plab>4.5) np=0;
  else if(plab>4.0) np=1;
  else if(plab>3.6) np=2;
  else if(plab>3.0) np = 20 - (int)(plab*5);
  else if(plab>0.5) np = 35 - (int)(plab*10);
  int nt(0);
  if(thetalab>0.842) nt=11; // forward
  else if(thetalab>0.692) nt=10; // A2
  else if(thetalab>.542) nt=9; // A1
  else if(thetalab>.435) nt=8; // B
  else if(thetalab>.355) nt=7; // C
  else if(thetalab>.209) nt=6; // D
  else if(thetalab>.017) nt=5; // E
  else if(thetalab>-.152) nt=4; // F
  else if(thetalab>-.300) nt=3; // G
  else if(thetalab>-.511) nt=2; // H
  else if(thetalab>-.612) nt=1; // I
  
  
//  TH2F* hidstat = (TH2F*) gDirectory->Get("idstat");
//  TH2F* hidsys1 = (TH2F*) gDirectory->Get("idsys1");
  //cout<<"bin weight "<<hid->GetBinContent(hid->FindBin(np,nt))<<endl;
    return hid_kid->GetBinContent(hid_kid->FindBin(np,nt));
}

