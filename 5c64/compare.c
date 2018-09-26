//defined statements
#define THETABINS 8
#define THETAMIN 8.0
#define THETAMAX 22.0
#define THETABINSIZE ((THETAMAX-THETAMIN)/THETABINS)	//size of each e-bin
#define PI 3.14159265358979323846
#define NUMSECT 6
#define NENT THETABINS*NUMSECT
const Float_t xmpr=0.938272;
using namespace std;

void compare(){
	int ii, i;
	char histName[40];
	TH1F *hist;
	TLine *line1;
	TLine *line2;
	
	char title[200], name[200];
	double tlow[THETABINS], thigh[THETABINS];

	double thetavalue[THETABINS];
	double meanV[THETABINS];
	double meanVer[THETABINS];

	double sigmaV[THETABINS];
	double sigmaVer[THETABINS];

	double m1[NENT], m1er[NENT], s1[NENT], s1er[NENT];
	double m2[NENT], m2er[NENT], s2[NENT], s2er[NENT];
	double m3[NENT], m3er[NENT], s3[NENT], s3er[NENT];
	double m4[NENT], m4er[NENT], s4[NENT], s4er[NENT];

	double m1bin[THETABINS], m1erbin[THETABINS], s1bin[THETABINS], s1erbin[THETABINS];
	double m2bin[THETABINS], m2erbin[THETABINS], s2bin[THETABINS], s2erbin[THETABINS];
	double m3bin[THETABINS], m3erbin[THETABINS], s3bin[THETABINS], s3erbin[THETABINS];
	double m4bin[THETABINS], m4erbin[THETABINS], s4bin[THETABINS], s4erbin[THETABINS];

	ifstream yieldF1;
	yieldF1.open("tables/job1.dat");
	for(i = 0; i < NENT; i++)
	{
		yieldF1 >> m1[i] >> m1er[i] >> s1[i] >> s1er[i];
	}
	yieldF1.close();

	ifstream yieldF2;
	yieldF2.open("tables/job2.dat");
	for(i = 0; i < NENT; i++)
	{
		yieldF2 >> m2[i] >> m2er[i] >> s2[i] >> s2er[i];
	}
	yieldF2.close();

	ifstream yieldF3;
	yieldF3.open("tables/job3.dat");
	for(i = 0; i < NENT; i++)
	{
		yieldF3 >> m3[i] >> m3er[i] >> s3[i] >> s3er[i];
	}
	yieldF3.close();

	ifstream yieldF4;
	yieldF4.open("tables/job4.dat");
	for(i = 0; i < NENT; i++)
	{
		yieldF4 >> m4[i] >> m4er[i] >> s4[i] >> s4er[i];
	}
	yieldF4.close();

	TCanvas *canv1 = new TCanvas("canv1", "canv1", 1500,800);
		//canv1->Divide(6,2);
		canv1->SetMargin(0.1, 0.1, 0.1, 0.05); // left right top bottom
		canv1->Draw();
	TPad *spad1 = new TPad("spad1","previouscanvas",0.11, 0.1, 0.93, 0.9);// xmin ymin xmax ymax //0.025,0.025, 0.91,0.98
		spad1->SetMargin(0.18,0.05,0.1,0.1); // left right top bottom
		spad1->Draw();
		spad1->Divide(6,2, 0.0, 0.0);

	TGraphErrors  *ge[NUMSECT], *ge1[NUMSECT], *ge2[NUMSECT], *ge3[NUMSECT];
	TGraphErrors *ge4[NUMSECT], *ge5[NUMSECT], *ge6[NUMSECT], *ge7[NUMSECT];
	TMultiGraph *mg[NUMSECT], *mg1[NUMSECT];
	TLegend *legg = new TLegend(0.26, 0.65, 0.78, 0.96);//last bin 0.7,0.069,0.9,0.13 
		legg->SetHeader("Run 2391");
	for(i = 0; i < NUMSECT; ++i)	
	{
		//cout << " For energy " << egamLow[i] << "-" << egamHigh[i] << endl;
		for(ii = 0; ii<THETABINS; ++ii)
		{
			tlow[ii] = (THETAMIN + THETABINSIZE * ii );
			thigh[ii] = tlow[ii] + THETABINSIZE;
			thetavalue[ii] = tlow[ii] + 0.5 * THETABINSIZE;			
			
			m1bin[ii] = m1[i*THETABINS+ii];		m1erbin[ii] = m1er[i*THETABINS+ii];
			s1bin[ii] = s1[i*THETABINS+ii];		s1erbin[ii] = s1er[i*THETABINS+ii];

			m2bin[ii] = m2[i*THETABINS+ii];		m2erbin[ii] = m2er[i*THETABINS+ii];
			s2bin[ii] = s2[i*THETABINS+ii];		s2erbin[ii] = s2er[i*THETABINS+ii];

			m3bin[ii] = m3[i*THETABINS+ii];		m3erbin[ii] = m3er[i*THETABINS+ii];
			s3bin[ii] = s3[i*THETABINS+ii];		s3erbin[ii] = s3er[i*THETABINS+ii];

			m4bin[ii] = m4[i*THETABINS+ii];		m4erbin[ii] = m4er[i*THETABINS+ii];
			s4bin[ii] = s4[i*THETABINS+ii];		s4erbin[ii] = s4er[i*THETABINS+ii];
		}
		mg[i] = new TMultiGraph();
		mg1[i] = new TMultiGraph();
		
		ge[i] = new TGraphErrors(THETABINS, thetavalue, m1bin, NULL, m1erbin);
		ge[i]->GetYaxis()->SetRangeUser(0.8119,1.2999);
		sprintf(name, "Sector %d", i+1);
		ge[i]->SetTitle("");
		ge[i]->SetLineColor(kRed);
		ge[i]->SetMarkerColor(kBlue);		
		ge[i]->SetMarkerStyle(20);
		ge[i]->SetMarkerSize(0.9);
		ge[i]->GetXaxis()->SetTitle("");
		ge[i]->GetXaxis()->CenterTitle();
		ge[i]->GetYaxis()->SetTitle("");
		ge[i]->GetYaxis()->CenterTitle();
		ge[i]->GetYaxis()->SetLabelSize(0.05);
		//ge[i]->GetXaxis()->SetLabelSize(0.05);
		ge[i]->GetYaxis()->SetLabelOffset(0.04);
		//ge[i]->GetXaxis()->SetLabelOffset(0.04);
		//ge[i]->Draw("APE");

		gPad->SetTicks(1,1);// X-axis Y-axis

		//spad1->cd(i+7);
		ge1[i] = new TGraphErrors(THETABINS, thetavalue, s1bin, NULL, s1er);
		ge1[i]->GetYaxis()->SetRangeUser(0.0,0.049);
		ge1[i]->SetTitle(name);
		ge1[i]->SetLineColor(kRed);
		ge1[i]->SetMarkerColor(kBlue);	
		ge1[i]->SetMarkerStyle(20);
		ge1[i]->SetMarkerSize(0.9);
		ge1[i]->GetXaxis()->SetTitle("");
		ge1[i]->GetXaxis()->CenterTitle();
		ge1[i]->GetYaxis()->SetTitle("");
		ge1[i]->GetYaxis()->CenterTitle();
		ge1[i]->GetYaxis()->SetLabelSize(0.05);
		ge1[i]->GetXaxis()->SetLabelSize(0.05);
		ge1[i]->GetYaxis()->SetLabelOffset(0.04);
		ge1[i]->GetXaxis()->SetLabelOffset(0.02);
		//ge1[i]->Draw("APE");
		//ge[i]->SetTitle("");
		//----------------------------------------------------------------//----------------------------------------------------------------

		ge2[i] = new TGraphErrors(THETABINS, thetavalue, m2bin, NULL, m2erbin);
		ge2[i]->GetYaxis()->SetRangeUser(0.8119,1.2999);
		sprintf(name, "Sector %d", i+1);
		ge2[i]->SetTitle("");
		ge2[i]->SetLineColor(kRed);
		ge2[i]->SetMarkerColor(kGreen);		
		ge2[i]->SetMarkerStyle(20);
		ge2[i]->SetMarkerSize(0.9);
		ge2[i]->GetXaxis()->SetTitle("");
		ge2[i]->GetXaxis()->CenterTitle();
		ge2[i]->GetYaxis()->SetTitle("");
		ge2[i]->GetYaxis()->CenterTitle();
		ge2[i]->GetYaxis()->SetLabelSize(0.05);
		//ge[i]->GetXaxis()->SetLabelSize(0.05);
		ge2[i]->GetYaxis()->SetLabelOffset(0.04);
		//ge[i]->GetXaxis()->SetLabelOffset(0.04);
		//ge[i]->Draw("APE");

		

		//spad1->cd(i+7);
		ge3[i] = new TGraphErrors(THETABINS, thetavalue, s2bin, NULL, s2erbin);
		ge3[i]->GetYaxis()->SetRangeUser(0.0,0.049);
		//ge3[i]->SetTitle(name);
		ge3[i]->SetLineColor(kRed);
		ge3[i]->SetMarkerColor(kGreen);	
		ge3[i]->SetMarkerStyle(20);
		ge3[i]->SetMarkerSize(0.9);
		ge3[i]->GetXaxis()->SetTitle("");
		ge3[i]->GetXaxis()->CenterTitle();
		ge3[i]->GetYaxis()->SetTitle("");
		ge3[i]->GetYaxis()->CenterTitle();
		ge3[i]->GetYaxis()->SetLabelSize(0.05);
		ge3[i]->GetXaxis()->SetLabelSize(0.05);
		ge3[i]->GetYaxis()->SetLabelOffset(0.04);
		ge3[i]->GetXaxis()->SetLabelOffset(0.02);


		//----------------------------------------------------------------//----------------------------------------------------------------
		ge4[i] = new TGraphErrors(THETABINS, thetavalue, m3bin, NULL, m3erbin);
		ge4[i]->GetYaxis()->SetRangeUser(0.8119,1.2999);
		sprintf(name, "Sector %d", i+1);
		ge4[i]->SetTitle("");
		ge4[i]->SetLineColor(kRed);
		ge4[i]->SetMarkerColor(kRed);		
		ge4[i]->SetMarkerStyle(20);
		ge4[i]->SetMarkerSize(0.9);
		ge4[i]->GetXaxis()->SetTitle("");
		ge4[i]->GetXaxis()->CenterTitle();
		ge4[i]->GetYaxis()->SetTitle("");
		ge4[i]->GetYaxis()->CenterTitle();
		ge4[i]->GetYaxis()->SetLabelSize(0.05);
		//ge4[i]->GetXaxis()->SetLabelSize(0.05);
		ge4[i]->GetYaxis()->SetLabelOffset(0.04);
		//ge4[i]->GetXaxis()->SetLabelOffset(0.04);
		//ge4[i]->Draw("APE");

		gPad->SetTicks(1,1);// X-axis Y-axis

		//spad1->cd(i+7);
		ge5[i] = new TGraphErrors(THETABINS, thetavalue, s3bin, NULL, s3er);
		ge5[i]->GetYaxis()->SetRangeUser(0.0,0.049);
		ge5[i]->SetTitle(name);
		ge5[i]->SetLineColor(kRed);
		ge5[i]->SetMarkerColor(kRed);	
		ge5[i]->SetMarkerStyle(20);
		ge5[i]->SetMarkerSize(0.9);
		ge5[i]->GetXaxis()->SetTitle("");
		ge5[i]->GetXaxis()->CenterTitle();
		ge5[i]->GetYaxis()->SetTitle("");
		ge5[i]->GetYaxis()->CenterTitle();
		ge5[i]->GetYaxis()->SetLabelSize(0.05);
		ge5[i]->GetXaxis()->SetLabelSize(0.05);
		ge5[i]->GetYaxis()->SetLabelOffset(0.04);
		ge5[i]->GetXaxis()->SetLabelOffset(0.02);
		//ge1[i]->Draw("APE");
		//ge[i]->SetTitle("");
		//----------------------------------------------------------------//----------------------------------------------------------------

		ge6[i] = new TGraphErrors(THETABINS, thetavalue, m4bin, NULL, m4erbin);
		ge6[i]->GetYaxis()->SetRangeUser(0.8119,1.2999);
		sprintf(name, "Sector %d", i+1);
		ge6[i]->SetTitle("");
		ge6[i]->SetLineColor(kBlack);
		ge6[i]->SetMarkerColor(kBlack);		
		ge6[i]->SetMarkerStyle(20);
		ge6[i]->SetMarkerSize(0.9);
		ge6[i]->GetXaxis()->SetTitle("");
		ge6[i]->GetXaxis()->CenterTitle();
		ge6[i]->GetYaxis()->SetTitle("");
		ge6[i]->GetYaxis()->CenterTitle();
		ge6[i]->GetYaxis()->SetLabelSize(0.05);
		//ge[i]->GetXaxis()->SetLabelSize(0.05);
		ge6[i]->GetYaxis()->SetLabelOffset(0.04);
		//ge[i]->GetXaxis()->SetLabelOffset(0.04);
		//ge[i]->Draw("APE");

		

		//spad1->cd(i+7);
		ge7[i] = new TGraphErrors(THETABINS, thetavalue, s4bin, NULL, s4erbin);
		ge7[i]->GetYaxis()->SetRangeUser(0.0,0.049);
		//ge7[i]->SetTitle(name);
		ge7[i]->SetLineColor(kRed);
		ge7[i]->SetMarkerColor(kBlack);	
		ge7[i]->SetMarkerStyle(20);
		ge7[i]->SetMarkerSize(0.9);
		ge7[i]->GetXaxis()->SetTitle("");
		ge7[i]->GetXaxis()->CenterTitle();
		ge7[i]->GetYaxis()->SetTitle("");
		ge7[i]->GetYaxis()->CenterTitle();
		ge7[i]->GetYaxis()->SetLabelSize(0.05);
		ge7[i]->GetXaxis()->SetLabelSize(0.05);
		ge7[i]->GetYaxis()->SetLabelOffset(0.04);
		ge7[i]->GetXaxis()->SetLabelOffset(0.02);
		//----------------------------------------------------------------//----------------------------------------------------------------


		
		//ge[i]->Draw("AP");

		gPad->SetTicks(1,1);// X-axis Y-axis
		
		spad1->cd(i+1);
		mg[i]->Add((TGraphErrors *)ge[i], "APE");
		mg[i]->Add((TGraphErrors *)ge2[i], "APE");
		mg[i]->Add((TGraphErrors *)ge4[i], "APE");
		mg[i]->Add((TGraphErrors *)ge6[i], "APE");
		mg[i]->Draw("same");

		//mg->GetXaxis()->SetLimits(0.8119,1.2999);
		mg[i]->SetMinimum(0.8119);
		mg[i]->SetMaximum(1.2999);

		if(i == 0)
		{
			legg->AddEntry((TGraphErrors *)ge[i],"Job 1","PE");
			legg->AddEntry((TGraphErrors *)ge2[i],"Job 2","PE");
			legg->AddEntry((TGraphErrors *)ge4[i],"Job 3","PE");
			legg->AddEntry((TGraphErrors *)ge6[i],"Job 4","PE");
			legg->Draw();
		}
		

		spad1->cd(i+7);
		mg1[i]->Add((TGraphErrors *)ge1[i], "APE");
		mg1[i]->Add((TGraphErrors *)ge3[i], "APE");
		mg1[i]->Add((TGraphErrors *)ge5[i], "APE");
		mg1[i]->Add((TGraphErrors *)ge7[i], "APE");
		mg1[i]->Draw("APE");

		//mg1->GetXaxis()->SetLimits(0.0,0.049);
		mg1[i]->SetMinimum(0.01);
		mg1[i]->SetMaximum(0.049);
	}
	
	
	

	canv1->cd();
	TLatex maintitle;
		maintitle.SetTextAlign(23); //align center
		maintitle.SetTextSize(0.037);//percent of canvas size
		maintitle.DrawLatexNDC(0.5, 0.95, "Run 2391 Version 5c.6.4");

	//format x title
	TLatex xtitle;
		xtitle.SetTextAlign(21); //align center x
		xtitle.SetTextSize(0.035);//percent of canvas size
		xtitle.DrawLatexNDC(0.5, 0.05, "#theta [deg]");
	
	TLatex ytitle;
		ytitle.SetTextAlign(23); //align left justify 
		ytitle.SetTextSize(0.035); //percent of canvas size
		ytitle.SetTextAngle(90.0);
		ytitle.DrawLatexNDC(0.07, 0.75,"#mu_{W} [GeV]");

	//format y title	
	TLatex ytitle1;
		ytitle1.SetTextAlign(23); //align left justify 
		ytitle1.SetTextSize(0.035); //percent of canvas size
		ytitle1.SetTextAngle(90.0);
		ytitle1.DrawLatexNDC(0.07, 0.25,"#sigma_{W} [GeV]");

	canv1->SaveAs("figures/elasticPeak/summary/comp.pdf");
	canv1->~TCanvas();
	
}



