#include "MiniTree.h"

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char**argv){

//config2 j nJ
if(argc<2) {printf("missing parameters\nUsage: config j nJ type\n") ; return 0;}

int j=0; 
int nJ=1;
if(argc>3){
   sscanf(argv[2],"%d",&j);
   sscanf(argv[3],"%d",&nJ);
}
int type=0; //0 -Data
sscanf(argv[4],"%d",&type);
printf("j=%d  nJ=%d type=%d\n",j,nJ,type);

MiniTree *A=new MiniTree();
	
	printf("SetConfig\n");
//	A->SetDebug(1);
	A->SetConfigFile("data/config.ini",argv[1]);
	A->SetCuts();
	printf("BookFile\n");
	switch (type)
	{
	case 0:
		if(A->GetChId()==4)A->BookFile("DoubleMu");  //create a switch between these
		if(A->GetChId()==1)A->BookFile("DoubleE"); 
		if(A->GetChId()==2)A->BookFile("MuEG"); 
		break;
	case 1: A->BookFile("DY"); break;
	case 2: A->BookFile("TT"); break;
	case 3: A->BookFile("WJ"); break;
	case 4: A->BookFile("WW"); break;
	case 5: A->BookFile("WZ"); break;
	case 6: A->BookFile("ZZ"); break;
	}
	printf("OpenFiles\n");
	A->OpenFiles(); //use the booked files: will loop on the TChain
	printf("Create Histos\n--Outputfile\n");
	A->outFile=Form("%s/MiniTree_type%d_chid%d_%d_%d.root",A->ReadMult("data/config.ini",argv[1],"OUTDIR"),type,A->GetChId(),j,nJ);
	printf("---OutputFile=%s\n",A->outFile.c_str());
	printf("--Histos\n");
	A->CreateHistos();
	printf("Loop\n");
	A->Loop(type,j,nJ); //type=0 data 1 MC; j , nJobs
	
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
	system(Form("touch %s/MiniTree_type%d_chid%d_%d_%d.done",A->ReadMult("data/config.ini",argv[1],"OUTDIR"),type,A->GetChId(),j,nJ) );
	return 0;

}
