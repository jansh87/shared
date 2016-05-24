
	gStyle -> SetHistLineWidth( 1 );
	gStyle -> SetHistFillColor( kWhite );
//	gStyle -> SetLegendFillColor ( kWhite ); // only in root 5.30
	gStyle -> SetCanvasColor(kWhite);
	gStyle -> SetFrameFillColor(kWhite);
	gStyle -> SetTitleFillColor( kWhite );
	gStyle -> SetTitleBorderSize( 0 );
	gStyle -> SetOptStat( 0 );
	gStyle->SetHatchesSpacing(2);
	//gStyle -> SetTitleFontSize( 2 );
	//gStyle -> SetTitleAlign ( 0 ); 
	
 TStyle *belleStyle= new TStyle("belleStyle","Phill's  un-official plots style");
  
  // use helvetica-bold-r-normal, precision 2 (rotatable)
  Int_t belleFont = 62;
  // line thickness
  Double_t belleWidth = 2;
 
  // use plain black on white colors
  belleStyle->SetFrameBorderMode(0);
  belleStyle->SetCanvasBorderMode(0);
  belleStyle->SetPadBorderMode(0);
  belleStyle->SetPadColor(0);
  belleStyle->SetCanvasColor(0);
  belleStyle->SetStatColor(0);
  belleStyle->SetPalette(1);
  belleStyle->SetFillColor(0);
 
  // set the paper & margin sizes
  belleStyle->SetPaperSize(20,26);
  belleStyle->SetPadTopMargin(0.05);
  belleStyle->SetPadRightMargin(0.05); // increase for colz plots!!
  belleStyle->SetPadBottomMargin(0.16);
  belleStyle->SetPadLeftMargin(0.14);
 
  // use large fonts
  belleStyle->SetTextFont(belleFont);
  belleStyle->SetTextSize(0.08);
  belleStyle->SetLabelFont(belleFont,"x");
  belleStyle->SetLabelFont(belleFont,"y");
  belleStyle->SetLabelFont(belleFont,"z");
  belleStyle->SetLabelSize(0.05,"x");
  belleStyle->SetLabelSize(0.05,"y");
  belleStyle->SetLabelSize(0.05,"z");
  belleStyle->SetTitleFont(belleFont);
  belleStyle->SetTitleSize(0.06,"x");
  belleStyle->SetTitleSize(0.06,"y");
  belleStyle->SetTitleSize(0.06,"z");
	belleStyle->SetHatchesSpacing(2);
 
  // use bold lines and markers
  belleStyle->SetLineWidth(belleWidth);
  belleStyle->SetFrameLineWidth(belleWidth);
  belleStyle->SetHistLineWidth(belleWidth);
  belleStyle->SetFuncWidth(belleWidth);
  belleStyle->SetGridWidth(belleWidth);
  belleStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
 // belleStyle->SetMarkerStyle(8);
 // belleStyle->SetMarkerSize(1.0);
 
  // label offsets
  belleStyle->SetLabelOffset(0.015);
 
  // by default, do not display histogram decorations:
  belleStyle->SetOptStat(0);  
  //belleStyle->SetOptStat(1110);  // show only nent, mean, rms
  belleStyle->SetOptTitle(0);
  belleStyle->SetOptFit(0);
//  belleStyle->SetOptFit(1011); // show probability, parameters and errors
 
  // look of the statistics box:
  belleStyle->SetStatBorderSize(1);
  belleStyle->SetStatFont(belleFont);
  belleStyle->SetStatFontSize(0.05);
  belleStyle->SetStatX(0.9);
  belleStyle->SetStatY(0.9);
  belleStyle->SetStatW(0.25);
  belleStyle->SetStatH(0.15);
 
  // put tick marks on top and RHS of plots
  belleStyle->SetPadTickX(1);
  belleStyle->SetPadTickY(1);
 
  // histogram divisions: only 5 in x to avoid label overlaps
  belleStyle->SetNdivisions(505,"x");
  belleStyle->SetNdivisions(510,"y");
 
  gROOT->SetStyle("belleStyle");
  gROOT->ForceStyle();
 
  TPaveText *belleName = new TPaveText(0.65,0.8,0.9,0.9,"BRNDC");
  belleName->SetFillColor(0);
  belleName->SetTextAlign(12);
  belleName->SetBorderSize(0);
  belleName->AddText("Belle");
 
  TText *belleLabel = new TText();
  belleLabel->SetTextFont(belleFont);
  belleLabel->SetTextColor(1);
  belleLabel->SetTextSize(0.04);
  belleLabel->SetTextAlign(12);
 
  TLatex *belleLatex = new TLatex();
  belleLatex->SetTextFont(belleFont);
  belleLatex->SetTextColor(1);
  belleLatex->SetTextSize(0.04);
  belleLatex->SetTextAlign(12);
  TGaxis::SetMaxDigits(3);
 
//Add Belle Preliminary, 710 fb-1 to plots
belleLatex->SetTextSize(0.07);
//belleLatex->DrawLatex((h_data[0]->GetXaxis()->GetXmax()-h_data[0]->GetXaxis()->GetXmin())*.1+h_data[0]->GetXaxis()->GetXmin(), 6./7.*h_data[0]->GetMaximum(), "#splitline{#splitline{Belle}{Preliminary}}{#scale[0.7]{710 fb^{-1}}}");

