#define c12epx_cxx
// The class definition in c12epx.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("c12epx.C")
// root> T->Process("c12epx.C","some options")
// root> T->Process("c12epx.C+")
//


#include "c12epx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TVector3.h>
#include <TLorentzVector.h>

//defined statements
#define THETABINS 8
#define THETAMIN 8.0
#define THETAMAX 22.0
#define THETABINSIZE ((THETAMAX-THETAMIN)/THETABINS)	//size of each e-bin
#define NUMSECT 6
#define NENT THETABINS*NUMSECT

const Float_t Ebeam=2.224;
//const Float_t Ebeam=10.60;
const Float_t xmpr=0.938272;
const Float_t xmpi=0.139570;
const Float_t xmkp=0.493677;
const Float_t Pi=3.14159265;

using namespace std;

TLorentzVector P4beam={ 0., 0., Ebeam, Ebeam };
TLorentzVector P4inc={ 0., 0., Ebeam, (Ebeam+xmpr) };

TH1F *Hmmesq = new TH1F("mmesq","MM^{2}(e)",500,-1.0,4.0);
TH1F *HW = new TH1F("W","W = MM(e)",300,0.5,2.0);
TH1F *HWs1 = new TH1F("Ws1","W = MM(e) Sector 1",300,0.5,2.0);
TH1F *HQ2 = new TH1F("Q2","Q^{2} {e1}",200,0.0,1.0);
TH2F *HQ2W = new TH2F("Q2W","Q^{2} v. W {e1}",100,0.5,2.0,100,0.0,1.0);

TH1F *Hmmepsq = new TH1F("mmepsq","MM^{2}(ep)",400,-0.2,0.2);
TH1F *HmmepsqS1 = new TH1F("mmepsqS1","MM^{2}(ep) Sector 1",400,-0.2,0.2);
TH2F *HWmmepsq = new TH2F("Wmmepsq","W vs MM^{2}(ep)",200,-0.2,0.2,200,0.5,2.0);
TH2F *HWphidif = new TH2F("Wphidif","#phi(e)-#phi(p) vs W",100,0.8,1.6,120,0.0,360.0);
TH1F *HWep = new TH1F("Wep","MM(e) {MMep=0}",300,0.5,2.0);
TH1F *HWepS1 = new TH1F("WepS1","MM(e) Sector 1 {MMep=0}",300,0.5,2.0);
TH2F *HWthetae = new TH2F("Wthetae","Theta(e) vs W",100,0.8,1.6,100,5.0,30.0);
TH2F *HWthetap = new TH2F("Wthetap","Theta(p) vs W",100,0.8,1.6,100,0.0,90.0);
TH2F *HWthetaep = new TH2F("WthetaeNp","#theta_{e} + #theta_{p} vs W",100,0.8,1.6,100,80.0,90.0);

TH1F *Hmmephsq = new TH1F("mmephsq","MM^{2}(ep#pi-)",400,-1,1);
TH2F *HmmephVph = new TH2F("mmephVph","P(#pi-) v. MM^{2}(ep#pi-)",200,-1,1,200,0,2);
TH2F *HmmephVmppi = new TH2F("mmephVmppi","M(p#pi-) v. MM^{2}(ep#pi-)",200,-1,1,200,1,3);
TH1F *Hmmeph = new TH1F("mmeph","MM(ep#pi-)",400,0,1);
TH1F *HmmehC1 = new TH1F("mmehC1","MM(e#pi-) [MM(ep#pi-)>0]",400,0,2);
TH1F *HmmepsqC1 = new TH1F("mmepsqC1","MM^2(ep) [MM(ep#pi-)>0]",400,-1,1);
TH1F *HmppiC1 = new TH1F("mppiC1","M(p #pi-) [MM(ep#pi-)>0]",400,1,3);
TH1F *HmppiC2 = new TH1F("mppiC2","M(p #pi-) [MM(ep#pi-)>0,P(#pi)>1.6]",400,1,3);

TH1F *HistW[NUMSECT][THETABINS];
TH1F *HistMM[NUMSECT];

void c12epx::Begin(TTree * /*tree*/)
{
	TString option = GetOption();

	fOutput->Add(Hmmesq);
	fOutput->Add(HW);
	fOutput->Add(HWs1);
	fOutput->Add(HQ2);
	fOutput->Add(HQ2W);

	fOutput->Add(Hmmepsq);
	fOutput->Add(HmmepsqS1);
	fOutput->Add(HWmmepsq);
	fOutput->Add(HWphidif);
	fOutput->Add(HWep);
	fOutput->Add(HWepS1);
	fOutput->Add(HWthetae);
	fOutput->Add(HWthetap);
	fOutput->Add(HWthetaep);

	fOutput->Add(Hmmephsq);
	fOutput->Add(HmmephVph);
	fOutput->Add(HmmephVmppi);
	fOutput->Add(Hmmeph);
	fOutput->Add(HmmehC1);
	fOutput->Add(HmmepsqC1);
	fOutput->Add(HmppiC1);
	fOutput->Add(HmppiC2);
}

void c12epx::SlaveBegin(TTree * /*tree*/)
{
	 TString option = GetOption();

	char HistWName[20], title[100];

	for(int i = 0; i < NUMSECT; ++i)
	{
		sprintf(HistWName, "HMM_sec%d",i+1);
		sprintf(title, "Sector %d MM^{2}(ep #rightarrow ep')",i+1);
		HistMM[i] = new TH1F(HistWName, title, 500, -0.1, 0.1);
		fOutput->Add(HistMM[i]);
	}

	for(int j = 0; j < NUMSECT; ++j)
	{
		for(int i = 0; i < THETABINS; ++i)
		{
			sprintf(HistWName, "HWSec%detheta%d",j+1,i);
			sprintf(title, "Sector %d W(ep #rightarrow ep') in #theta_{e} bin %d",j+1,i+1);
			HistW[j][i] = new TH1F(HistWName, title, 500, 0.85, 1.5);
			fOutput->Add(HistW[j][i]);
		}
	}
}

Bool_t c12epx::Process(Long64_t entry)
{
	 fReader.SetEntry(entry);

	 Float_t px[10],py[10],pz[10];
	 TVector3 P3ele,P3pro,P3pip,P3pim,P3pi,P3gam1,P3gam2;
	 TLorentzVector P4ele,P4pro,P4pip,P4pim,P4pi,P4gam1,P4gam2;
	 Float_t W2,W=0,Q2,msq2g,m2g;

	int ic = 0;

	Int_t npid = REC_Particle_pid.GetSize();
	Int_t npindex = REC_Track_pindex.GetSize();

	if( npid > 1 && npid < 10)
	{
		Int_t nele=0, iele[5]={0}, esect[5]={0};
		Int_t ngam=0, igam[5]={0};
		Int_t npro=0, ipro[5]={0};
		Int_t npip=0, ipip[5]={0};
		Int_t npim=0, ipim[5]={0};
		Int_t nkp=0, ikp[5]={0};
		for( Int_t i=0; i<npid; i++ )
		{
			px[i] = REC_Particle_px[i];
			py[i] = REC_Particle_py[i];
			pz[i] = REC_Particle_pz[i];
			if( REC_Particle_pid[i] == 11 )
			{
				if(nele<5) iele[nele]=i;
				// get sector info
				for(Int_t j=0; j<npindex; j++)
				{
					if(REC_Track_pindex[j] == i && REC_Track_detector[j] == 6)
						esect[nele] = REC_Track_sector[j];
				}
				nele++;
			}
			if( REC_Particle_pid[i] == 22 )
			{
				if(ngam<5) igam[ngam]=i;
					ngam++;
			}
			/*
			if( REC_Particle_pid[i] == 2212 ) {
			if(npro<5) ipro[npro]=i;
			npro++;
			}
			*/
			if( REC_Particle_pid[i] == 211) 
			{
				if(npip<5)
					ipip[npip]=i;
				npip++;
			}
			if( REC_Particle_pid[i] == -211)
			{
				if(npim<5) ipim[npim]=i;
				npim++;
			}
			if( REC_Particle_pid[i] == 321) 
			{
				if(nkp<5) ikp[nkp]=i;
				nkp++;
			}
			for(Int_t j=0; j<npindex; j++)
			{
				if(REC_Track_pindex[j] == i)
				{
					if(REC_Track_detector[j] == 5)
					{
						if(npro<5) ipro[npro]=i;
						npro++;
					}
				}
			}
			// end PID

			if( nele == 1 )
			{
				Int_t ii = iele[0];
				Float_t efac = 1.00;//momentum fraction
				//Float_t efac = 1.04;//momentum fraction
				P3ele.SetXYZ(efac*px[ii],efac*py[ii],efac*pz[ii]);
				P4ele.SetVect(P3ele);
				P4ele.SetE( P3ele.Mag() );
				W2 = (P4inc - P4ele).M2();
				Q2 = -(P4beam - P4ele).M2();
				Hmmesq->Fill( W2 );
				if(W2 > 0.001 ) 
				{
					W = sqrt(W2);
					//W = sqrt(W2) - 0.2*(Q2-0.6);
					HW->Fill( W );
					if(esect[ii] == 1) HWs1->Fill( W );
						HQ2->Fill( Q2 );
					HQ2W->Fill( W, Q2 );
				}
				if( npro == 1 )
				{
					Int_t jj = ipro[0];
					Float_t pfac = 1.00;
					P3pro.SetXYZ(pfac*px[jj],pfac*py[jj],pfac*pz[jj]);
					P4pro.SetVect(P3pro);
					P4pro.SetE( sqrt(P3pro.Mag()*P3pro.Mag()+xmpr*xmpr) );

					Float_t xmmepsq = (P4inc - P4ele - P4pro).M2();
					Hmmepsq->Fill(xmmepsq);

					if(esect[ii] == 1)
						HmmepsqS1->Fill(xmmepsq);

					//check angles
					Float_t phidiff = P3ele.Phi()-P3pro.Phi();
					if(phidiff < 0.0) phidiff += 2*Pi;
						HWphidif->Fill( W, phidiff*360./(2.0*Pi) );

					// if(W2 > 0.001 && fabs(xmmepsq)<0.01)
					// // if(esect[ii] < 1 && esect[ii] > 6)
					// 	cout << esect[ii]-1 << "\t" << esect[ii] << "--------\n";
					//HistMM[esect[ii]]->Fill(xmmepsq);

					if(esect[ii] > 0 && esect[ii] < 7)
						HistMM[esect[ii]-1]->Fill(xmmepsq);
					

					if(W2 > 0.001 && fabs(xmmepsq)<0.01 )
					{
						HWmmepsq->Fill(xmmepsq,W);
						HWep->Fill(W);
						if(esect[ii] == 1)
							HWepS1->Fill(W);

						Float_t etheta = P3ele.Theta()*180./Pi;
						Float_t ptheta = P3pro.Theta()*180./Pi;
						Float_t thetaep = (Float_t)(etheta + ptheta);
						HWthetae->Fill( W, etheta );
						HWthetap->Fill( W, ptheta );

						if( fabs(phidiff*360./(2.0*Pi) - 180.) < 10.0)
							HWthetaep->Fill( W,thetaep);

						if (etheta > THETAMIN && etheta <= THETAMAX)
						{
							ic = int((etheta-THETAMIN)/THETABINSIZE);
							HistW[esect[ii]-1][ic]->Fill(W);
						}
					}


					if( npim == 1 )
					{
						jj = ipim[0];
						P3pi.SetXYZ(px[jj],py[jj],pz[jj]);
						P4pi.SetVect(P3pi);
						P4pi.SetE( sqrt(P3pi.Mag()*P3pi.Mag()+xmpi*xmpi) );
						Float_t xmmephsq = (P4inc - P4ele - P4pro - P4pi).M2();
						Hmmephsq->Fill(xmmephsq);
						HmmephVph-> Fill( xmmephsq, P3pi.Mag() );
						Float_t xmppi = (P4pro+P4pi).M();
						HmmephVmppi-> Fill( xmmephsq, xmppi );
						if( xmmephsq > -0.2 ) 
						{
							Float_t xmmeph = sqrt(xmmephsq);
							Hmmeph->Fill( xmmeph );
							Float_t xmmeh = (P4inc - P4ele - P4pi).M();
							HmmehC1->Fill(xmmeh);
							HmmepsqC1->Fill(xmmepsq);
							HmppiC1->Fill(xmppi);
							if(P3pi.Mag()>1.6 && P3pi.Mag()<1.8)
								HmppiC2->Fill(xmppi);
						}
					}//npip
				}//npro=1
			}//nele=1
		}//npid loop
	}//(npid>1)
	return kTRUE;
}

void c12epx::SlaveTerminate()
{
}

void c12epx::Terminate()
{
	//TFile* outfile=new TFile("c12exp.root","recreate");
	char fileName[30];
	sprintf(fileName, "jobFiles/rootFiles/5c64-job1.root");
	TFile* outfile=new TFile(fileName,"recreate");
	fOutput->Write();
	outfile->Close();
	cout << "\n\n\t" << fileName << " created!!" << endl << endl;
	// delete outfile;
}
