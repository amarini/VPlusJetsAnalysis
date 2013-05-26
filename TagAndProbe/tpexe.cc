#include "TagAndProbe.h"

#include <stdio.h>
int main(int argc, char**argv){

//config2 j nJ
if(argc<2) {printf("missing parameters\nUsage: config j nJ\n") ; return 0;}

int j=0; 
int nJ=1;
if(argc>4){
   sscanf(argv[2],"%d",&j);
   sscanf(argv[3],"%d",&nJ);
}

TagAndProbe *A=new TagAndProbe();
	
	printf("SetConfig\n");
//	A->SetDebug(1);
	A->SetConfigFile("data/config.ini",argv[1]);
	A->SetCuts();
	printf("BookFile\n");
		if(A->GetChId()==4)A->BookFile("DoubleMu");  //create a switch between these
		if(A->GetChId()==1)A->BookFile("DoubleE"); 
		if(A->GetChId()==2)A->BookFile("EMu"); 
	printf("OpenFiles\n");
	A->OpenFiles(); //use the booked files: will loop on the TChain
	printf("Create Histos\n--Outputfile\n");
	A->outFile=Form("%s/TagAndProbe_chid%d_%d_%d.root",A->ReadMult("data/config.ini",argv[1],"OUTDIR"),A->GetChId(),j,nJ);
	printf("---OutputFile=%s\n",A->outFile.c_str());
	printf("--Histos\n");
	A->CreateHistos();
	printf("Loop\n");
	A->Loop(0,j,nJ); //type=0 data 1 MC; j , nJobs
	
//	printf("Smear JES UP\n");
//	A->SetSmearType(1,"_JES_UP");
//	printf("--> Histos\n");
//	A->CreateHistos();
//	printf("--> Loop\n");
//	A->Loop(type,j,nJ); //type=0 data 1 MC; j , nJobs
//
//	printf("Smear JES DN\n");
//	A->SetSmearType(2,"_JES_DN");
//	printf("--> Histos\n");
//	A->CreateHistos();
//	printf("--> Loop\n");
//	A->Loop(type,j,nJ); //type=0 data 1 MC; j , nJobs

	printf("Write\n");
	if(A->Write("") ) printf("ERROR in Writing\n");
	return 0;

}
