 /***************************************************************************************************
	This macro will fit the MM^2 peak in the missing mass distribution ep->ep
	using a Gaussian function. The distribution is expected to peak at 0 with a width.

	This macro works if there is an input root file in the format "5c64-job#.root".
	It quits if it does not find this file.

	For each job, it:
		- creates 'figures/mmsq/job#' directory
		- fits the peaks and saves the images in 'figures/job#' directory
		- Saves the fit information in a 'mmsq-job#.dat' file in the current directory. The contents are
		  in the order:
		  		  Centroid  |  Centroid Error  | Width   | Width Error  |
		  for each Sector.
		- Plots the centroids and Widths for each Job as a function of Sectors.

	To run the macro:
		$ root -[option] mmSqfit.c
			[option] b = batch; l = interactive

	This program will exit automatically after completion.


	TAYA, Sep 25, 2018
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
#define NJOBS 7
using namespace std;

void doFit();
void fit(int fileNum);
void compare();

void mmSqfit()
{
	doFit();//comment after the first run
			//It will create necessary folders
	compare();
	gApplication->Terminate();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

void doFit()
{
	for(int i = 0; i < NJOBS; ++i)
	{
		fit(i+1);
		printf("\n\n\tJob %d done \n\n",i+1);
	}
}

void compare()
{
	TGaxis::SetMaxDigits(5);
	char jobID[50], name[20];
	int i, j;
	
	double m[NJOBS][NUMSECT], mer[NJOBS][NUMSECT], s[NJOBS][NUMSECT], ser[NJOBS][NUMSECT];
	for(i = 0; i < NJOBS; ++i)
	{
		ifstream inputFile;
		sprintf(jobID, "tables/mmsq-job%d.dat", i+1);
		inputFile.open(jobID);
		for(j = 0; j < NUMSECT; ++j)
		{
			inputFile >> m[i][j] >> mer[i][j] >> s[i][j] >> ser[i][j];
			//cout << m[i][j] << "\t" << mer[i][j] << "\t" <<  s[i][j] << "\t" << ser[i][j] << endl;
		}
		//cout << endl << endl;
	}
	

	TCanvas *canv1 = new TCanvas("canv1", "canv1", 1200,800);
		canv1->SetMargin(0.02, 0.1, 0.1, 0.1); // left right top bottom
		canv1->Draw();
	TPad *spad1 = new TPad("spad1","previouscanvas",0.11, 0.1, 0.93, 0.9);// xmin ymin xmax ymax //0.025,0.025, 0.91,0.98
		spad1->SetMargin(0.07,0.01,0.1,0.05); // left right top bottom
		spad1->Draw();
		spad1->Divide(1,2, 0.0, 0.0);

	double xSect[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

	TLine *ln = new TLine(0.8, 0.0, 7, 0.0);
		ln->SetLineColor(kGreen);
		ln->SetLineStyle(2);

	TGraphErrors  *geM[NJOBS], *geS[NJOBS];
	TMultiGraph *mgM = new TMultiGraph();
	TMultiGraph *mgS = new TMultiGraph();
	TLegend *legg = new TLegend(0.15, 0.802, 0.9083, 0.9586);//last bin 0.7,0.069,0.9,0.13 
		//legg->SetHeader("Run 2391");
	for(i = 0; i < NJOBS; ++i)	
	{
		geM[i] = new TGraphErrors(NUMSECT, xSect, m[i], NULL, mer[i]);
		//geM[i]->GetYaxis()->SetRangeUser(0.8119,1.2999);
		if(i<5)sprintf(name, "Run 2391 Job %d", i+1);
		else sprintf(name, "Run 2587 Job %d", i+1);
		geM[i]->SetName(name);
		geM[i]->SetLineColor(i+1);
		geM[i]->SetMarkerColor(i+1);		
		geM[i]->SetMarkerStyle(20);
		geM[i]->SetMarkerSize(0.9);

		geS[i] = new TGraphErrors(NUMSECT, xSect, s[i], NULL, ser[i]);
		// sprintf(name, "Job %d", i+1);
		geS[i]->SetName(name);
		geS[i]->SetLineColor(i+1);
		geS[i]->SetMarkerColor(i+1);		
		geS[i]->SetMarkerStyle(20);
		geS[i]->SetMarkerSize(0.9);

		mgM->Add((TGraphErrors *)geM[i], "APE");
		mgS->Add((TGraphErrors *)geS[i], "APE");
		legg->AddEntry((TGraphErrors *)geM[i],name,"PE");
	}
	//mgM->Add((TGraphErrors *)geM[0], "APE");
	gPad->SetTicks(1,1);
	// gPad->SetTicks("+");
	spad1->cd(1);
	mgM->Draw("APE");
	mgM->GetXaxis()->SetNdivisions(106);
	mgM->GetYaxis()->SetNdivisions(505);
	mgM->GetYaxis()->SetLabelSize(0.07);
	mgM->SetMinimum(-0.009);
	mgM->SetMaximum(0.003);
	legg->SetNColumns(4);
	legg->Draw();
	ln->Draw("same");
	

	spad1->cd(2);
	mgS->Draw("APE");
	mgS->GetXaxis()->SetLabelSize(0.07);
	mgS->GetYaxis()->SetLabelSize(0.07);
	mgS->GetXaxis()->SetNdivisions(106);
	mgS->GetYaxis()->SetNdivisions(205);
	mgS->SetMinimum(0.0);
	mgS->SetMaximum(0.0079);
	//canv1->cd();//go back to the canvas
	
		
	// mgM->GetXaxis()->SetLimits(-2.0,-0.3);
	
canv1->cd();
	TLatex maintitle;
		maintitle.SetTextAlign(23); //align center
		maintitle.SetTextSize(0.037);//percent of canvas size
		maintitle.DrawLatexNDC(0.51, 0.95, "Version 5c.6.4");

	//format x title
	TLatex xtitle;
		xtitle.SetTextAlign(21); //align center x
		xtitle.SetTextSize(0.033);//percent of canvas size
		xtitle.DrawLatexNDC(0.55, 0.07, "Sector");
	
	TLatex ytitle;
		ytitle.SetTextAlign(23); //align left justify 
		ytitle.SetTextSize(0.03); //percent of canvas size
		ytitle.SetTextAngle(90.0);
		ytitle.DrawLatexNDC(0.06, 0.72,"#mu_{MM^{2}(ep)} [GeV^{2}]");

	//format y title	
	TLatex ytitle1;
		ytitle1.SetTextAlign(23); //align left justify 
		ytitle1.SetTextSize(0.03); //percent of canvas size
		ytitle1.SetTextAngle(90.0);
		ytitle1.DrawLatexNDC(0.06, 0.32,"#sigma_{MM^{2}(ep)} [GeV^{2}]");

	canv1->SaveAs("figures/mmsq/summary/mmsqComp.pdf");
	canv1->~TCanvas();
	
}



void fit(int fileNum)
{
	TGaxis::SetMaxDigits(4);
	gStyle->SetOptFit();
	gStyle->SetOptStat(11);

	int ii, i;
	char histName[40];
	TH1F *hist;
	TLine *line1;
	TLine *line2;

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
	
	TF1 *fgaus;
	
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

	sprintf(jobID, "figures/mmsq/job%d", fileNum);
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
	sprintf(jobID, "tables/mmsq-job%d.dat", fileNum);
	yieldFile.open(jobID);
    Float_t xmin, xmax;
	
	TCanvas *canv[NUMSECT];

	for(i = 0; i < NUMSECT; ++i)	
	{
		sprintf(histName, "HMM_sec%d",i+1);
		canv[i] = new TCanvas (histName, histName);
		hist = (TH1F*)f1->Get(histName);
		hist->SetTitle("");	
		sprintf(title, "Job %d   Sector = %d", fileNum, i+1);
		hist->SetName(title);	
		hist->GetXaxis()->SetTitle("MM^{2}(ep #rightarrow ep') [GeV^{2}]");
		hist->GetXaxis()->SetTitleOffset(0.8);
		hist->GetXaxis()->CenterTitle();
		hist->GetYaxis()->SetTitle("counts");
		hist->GetYaxis()->SetTitleOffset(0.8);
		hist->GetYaxis()->CenterTitle();
		hist->SetLineColor(4);
		hist->SetLineStyle(1);
		hist->GetXaxis()->SetTitleSize(0.05);
		hist->GetYaxis()->SetTitleSize(0.05);
		hist->GetXaxis()->SetRangeUser(-0.04, 0.04);
		hist->Draw();			
		
		if(i == 1)
		{
			xmin = hist->GetBinCenter(hist->GetMaximumBin())*2.5;
			xmax = hist->GetBinCenter(hist->GetMaximumBin())*(-0.4);
		}
		else
		{
			xmin = hist->GetBinCenter(hist->GetMaximumBin())*3.5;
			xmax = hist->GetBinCenter(hist->GetMaximumBin())*(-1.11);
		}


		sprintf(histName, "fgaus%d",i);
		fgaus = new TF1(histName, "[0]* TMath::Exp(-0.5 * pow((x-[1])/[2], 2.0))", xmin, xmax);		
		fgaus->SetParameter(0, hist->GetMaximum());
		fgaus->SetParameter(1, hist->GetBinCenter(hist->GetMaximumBin()));
		fgaus->SetParameter(2, hist->GetStdDev());

		// cout << "Sector " << i+1 << "\t(-0.008, 0.001)\t" << xmin << ", " << xmax << endl;
		
		fgaus->SetLineColor(kRed);
		fgaus->SetParLimits(0, 0.0,hist->GetMaximum()*1.02);
		// if(fileNum == 5 && i == 4)
		fgaus->SetParLimits(1, hist->GetBinCenter(hist->GetMaximumBin())-0.001, hist->GetBinCenter(hist->GetMaximumBin())+0.001);
		if(fileNum < 5)
			fgaus->SetParLimits(2, 0.0,0.01);
		else
			fgaus->SetParLimits(2, 0.0,0.015);
		fgaus->SetParName(0, "Norm");
		fgaus->SetParName(1, "#mu");
		fgaus->SetParName(2, "#sigma");
		hist->Fit(fgaus, "BRQ");
		
		yieldFile << fgaus->GetParameter(1) << "\t" << fgaus->GetParError(1) << "\t" << fgaus->GetParameter(2) << "\t" << fgaus->GetParError(2) << endl;	
		
		sprintf(name,"figures/mmsq/job%d/Sector%d.pdf", fileNum, i+1);
		canv[i]->SaveAs(name);			
		canv[i]->~TCanvas();
	}
	yieldFile.close();
}



