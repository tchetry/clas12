 /***************************************************************************************************
	This macro will fit the elastic peak in ep->epX using a Gaussian function.

	This macro works if there is an input root file in the format "5c64-job#.root".
	It quits if it does not find this file

	For each job, it:
		- creates 'figures/elasticPeak/job#' directory
		- fits the peaks and saves the images in 'figures/job#' directory
		- Saves the fit information in a 'job#.dat' file in the current directory. The contents are
		  in the order:
		  		  Centroid  |  Centroid Error  | Width   | Width Error  |
		  for each Sector and each angle bin.
		- Plots the centroids and Widths for each sector as a function of scattering angle.

	To run the macro:
		$ root -b fit.c
	and follow the terminal prompts.

	This macro will exits ROOT after everything.


	TAYA, Sep 20, 2018
****************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
struct stat info;

//defined statements
#define THETABINS 8		//etheta-bins
#define THETAMIN 8.0	//minimum etheta
#define THETAMAX 22.0	//maximum etheta
#define THETABINSIZE ((THETAMAX-THETAMIN)/THETABINS)	//size of each etheta-bin
#define PI 3.14159265358979323846
#define NUMSECT 6	//number of sectors
#define NENT THETABINS*NUMSECT
const Float_t xmpr=0.938272;	//mass of proton
using namespace std;

void fit(){
	int ii, i;
	char histName[40];
	TH1F *hist;
	TLine *line1;
	TLine *line2;
	int fileNum = -9;

	double mean, sigma;
	double sigPar[4], sigParEr[4];
	double expPar[4], expParEr[4];
	double sigPar1[4], sigPar1Er[4];

	char title[200], name[200];
	double tlow[THETABINS], thigh[THETABINS];

	double thetavalue[THETABINS];
	double meanV[THETABINS];
	double meanVer[THETABINS];

	double sigmaV[THETABINS];
	double sigmaVer[THETABINS];

	char jobID[100], temp[40];

	//user input
	cout << "root file name: Job (1-7): ";
	cin >> fileNum;
	
	TF1 *fgaus;// = new TF1("fgaus", "[0]* TMath::Exp(-0.5 * pow((x-[1])/[2], 2.0))", 0.85, 0.98);
	TF1 *fgaus1;
	// TF1 *fexpo  = new TF1( "fexpo", "expo", 0.96, 1.1);
	// TF1 *fexp  = new TF1( "fexp", "[0]* TMath::Exp([1]*x)", 0.96, 1.1);
	// TF1 *ftot = new TF1("ftot", "[0]* TMath::Exp(-0.5 * pow((x-[1])/[2], 2.0)) + TMath::Exp([3] + [4]*x)", 0.9, 1.1);
	
	//initial Gaus parameters
	sigPar[0] = 500.0;	//Amplitude
	sigPar[1] = 0.94;	//Mean
	sigPar[2] = 0.01;	//Gaussian Width

	TFile *f1;
	sprintf(jobID, "jobFiles/rootFiles/5c64-job%d.root", fileNum);
	if( stat(jobID, &info ) != 0 )
	{
		cout << "\n\tNo file: '" << jobID << "' is found\n" << endl;
		gApplication->Terminate();
	}
	else
		f1 = new TFile(jobID);

	sprintf(jobID, "figures/elasticPeak/job%d", fileNum);
	if( stat(jobID, &info ) != 0 )
	{
		cout << "\nCannot access "<< jobID << endl;
		cout << " \nCreating the directory: " << jobID << "\n\n\n";

		sprintf(temp, "mkdir -p %s", jobID);
	    gSystem->Exec(temp);    	
	}
    else
    {
    	printf( "%s is a directory\n", jobID );
    }

	ofstream yieldFile;
	sprintf(jobID, "tables/job%d.dat", fileNum);
	yieldFile.open(jobID);

	
	TCanvas *canv[NENT];
	TCanvas *canv1 = new TCanvas("canv1", "canv1", 1500,800);
		//canv1->Divide(6,2);
		canv1->SetMargin(0.1, 0.1, 0.1, 0.05); // left right top bottom
		canv1->Draw();
	TPad *spad1 = new TPad("spad1","previouscanvas",0.11, 0.1, 0.93, 0.9);// xmin ymin xmax ymax //0.025,0.025, 0.91,0.98
		spad1->SetMargin(0.18,0.05,0.1,0.1); // left right top bottom
		spad1->Draw();
		spad1->Divide(6,2, 0.0, 0.0);
		
	TGraphErrors *ge[NUMSECT], *ge1[NUMSECT];

	TLine *ln = new TLine(THETAMIN, xmpr, THETAMAX, xmpr);
		ln->SetLineColor(kGreen);
		ln->SetLineStyle(2);

	for(i = 0; i < NUMSECT; ++i)	
	{
		for(ii = 0; ii<THETABINS; ++ii)
		{
			tlow[ii] = (THETAMIN + THETABINSIZE * ii );
			thigh[ii] = tlow[ii] + THETABINSIZE;			
			thetavalue[ii] = tlow[ii] + 0.5 * THETABINSIZE;
			
			sprintf(histName, "HWSec%detheta%d",i+1,ii);
			canv[i*NUMSECT+ii] = new TCanvas (histName, histName);
			hist = (TH1F*)f1->Get(histName);
			hist->SetTitle("");	
			sprintf(title, "Sector = %d;  #theta_{e} = [%1.2f,%1.2f]", i+1, tlow[ii], thigh[ii]);
			hist->SetName(title);	
			hist->GetXaxis()->SetTitle("W (ep #rightarrow ep') [GeV]");
			hist->GetXaxis()->SetTitleOffset(0.8);
			hist->GetXaxis()->CenterTitle();
			hist->GetYaxis()->SetTitle("counts");
			hist->GetYaxis()->SetTitleOffset(0.8);
			hist->GetYaxis()->CenterTitle();
			hist->SetLineColor(4);
			hist->SetLineStyle(1);
			hist->GetXaxis()->SetTitleSize(0.05);
			hist->GetYaxis()->SetTitleSize(0.05);
			hist->Draw();			
			
			sprintf(histName, "fgaus%d",i*THETABINS+ii);
			fgaus = new TF1(histName, "[0]* TMath::Exp(-0.5 * pow((x-[1])/[2], 2.0))", hist->GetBinCenter(hist->GetMaximumBin())*.9, hist->GetBinCenter(hist->GetMaximumBin())*1.1);
			
			fgaus->SetParameter(0, hist->GetMaximum());
			fgaus->SetParameter(1, hist->GetBinCenter(hist->GetMaximumBin()));
			if(hist->GetStdDev() < 0.05 && hist->GetStdDev() > 1e-3)
				fgaus->SetParameter(2, hist->GetStdDev());
			else
				fgaus->SetParameter(2, 0.03);
			
			fgaus->SetLineColor(kRed);
			fgaus->SetParLimits(0, hist->GetMaximum()*0.97,hist->GetMaximum()*1.02);
			hist->Fit(fgaus, "BRQ");
			cout << "Sector = " << i << "\tcostheta = " << ii << endl;

			sprintf(histName, "fgaus1%d",i*THETABINS+ii);
			fgaus1 = new TF1(histName, "[0]* TMath::Exp(-0.5 * pow((x-[1])/[2], 2.0))", fgaus->GetParameter(1)-fgaus->GetParameter(2)*1.5, fgaus->GetParameter(1)+fgaus->GetParameter(2));
			// fgaus1 = new TF1(histName, "[0]* TMath::Exp(-0.5 * pow((x-[1])/[2], 2.0))", hist->GetBinCenter(hist->GetMaximumBin())*.95, hist->GetBinCenter(hist->GetMaximumBin())*1.005);
			fgaus1->SetParName(0, "Norm");
			fgaus1->SetParName(1, "#mu");
			fgaus1->SetParName(2, "#sigma");

			for(int pp = 0; pp < 3; ++pp)
			{
				fgaus1->SetParameter(pp, fgaus->GetParameter(pp));
			}
			fgaus1->SetParLimits(0, hist->GetMaximum()*0.8,hist->GetMaximum());
			fgaus1->SetLineColor(kGreen);
			hist->Fit(fgaus1, "BRQ+");
			
			gStyle->SetOptFit();
			fgaus1->GetParameters(sigPar1);
						
			meanV[ii] = sigPar1[1];
			meanVer[ii] = fgaus1->GetParError(1);

			sigmaV[ii] = sigPar1[2];
			sigmaVer[ii] = fgaus1->GetParError(2);

			yieldFile << sigPar1[1] << "\t" << fgaus1->GetParError(1) << "\t" << sigPar1[2] << "\t" << fgaus1->GetParError(2) << endl;
									
			gStyle->SetOptStat(1112);
			
			sprintf(name,"figures/elasticPeak/job%d/Sector%dTheta%d.eps", fileNum, i+1, ii+1);
			canv[i*NUMSECT+ii]->SaveAs(name);			
			canv[i*NUMSECT+ii]->~TCanvas();
		}

		spad1->cd(i+1);
		ge[i] = new TGraphErrors(THETABINS, thetavalue, meanV, NULL, meanVer);
		ge[i]->GetYaxis()->SetRangeUser(0.8119,1.2999);
		sprintf(name, "Sector %d", i+1);
		ge[i]->SetTitle("");
		//ge[i]->SetMarkerColor(i+1);	
		ge[i]->SetLineColor(kRed);	
		ge[i]->SetMarkerStyle(20);
		ge[i]->SetMarkerSize(0.9);
		ge[i]->GetXaxis()->SetTitle("");
		ge[i]->GetXaxis()->CenterTitle();
		ge[i]->GetYaxis()->SetTitle("");
		ge[i]->GetYaxis()->CenterTitle();
		ge[i]->GetYaxis()->SetLabelSize(0.05);
		ge[i]->GetYaxis()->SetLabelOffset(0.04);
		ge[i]->Draw("APE");
		ln->Draw("same");

		gPad->SetTicks(1,1);// X-axis Y-axis

		spad1->cd(i+7);
		ge1[i] = new TGraphErrors(THETABINS, thetavalue, sigmaV, NULL, sigmaVer);
		ge1[i]->GetYaxis()->SetRangeUser(0.0,0.049);
		ge1[i]->SetTitle(name);
		ge1[i]->SetLineColor(kRed);		
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
		ge1[i]->Draw("APE");
	}
	canv1->cd();
	if(fileNum == 1)sprintf(name,"Job 1");
	if(fileNum == 2)sprintf(name,"Job 2");
	if(fileNum == 3)sprintf(name,"Job 3");
	if(fileNum == 4)sprintf(name,"Job 4");

	TLatex maintitle;
		maintitle.SetTextAlign(23); //align center
		maintitle.SetTextSize(0.037);//percent of canvas size
		maintitle.DrawLatexNDC(0.5, 0.95, "Run 2391_5c.6.4");
		maintitle.SetTextSize(0.03);
		maintitle.DrawLatexNDC(0.5, 0.9, name);

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

	sprintf(jobID,"figures/elasticPeak/summary/job%d.pdf", fileNum);
	canv1->SaveAs(jobID);
	canv1->~TCanvas();
	yieldFile.close();
	gApplication->Terminate();
}



