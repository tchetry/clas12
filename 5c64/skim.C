/***
	This macro will create job files to process for next analysis from the input files.

	Make sure to change the output file name according to the input files

***/

void job1();

void skim()
{
	job1();
	gApplication->Terminate();
}


void job1()
{
	TFile f1("../5c64/jobFiles/out_clas_002391.0.9_job1.root");
	if( TTree *clas12 = (TTree*)f1.Get("clas12"))
		clas12->Process("c12epx.C");
}

