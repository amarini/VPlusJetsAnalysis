#include "TagAndProbe.h"
#include "math.h"

int TagAndProbe::Smear(){
	if(SmearType==0) return 0;
	if(SmearType==1){ //JES UP
			for(int i=0;i<(jetPt->size());i++)
				(*jetPt)[i]*=(1+(*jetUNC)[i] );
			return 0;
			}
	if(SmearType==2){ //JES DN
			for(int i=0;i<(jetPt->size());i++)
				(*jetPt)[i]*=(1-(*jetUNC)[i] );
			return 0;
			}
}

bool TagAndProbe::BaseSelection()
{
if(lepPt->size()<2)return false; //2 leptons
if( (*lepChId)[0]*(*lepChId)[1]!=CHID2)return false; //two muons
        //Triggers??
return true;
}

bool TagAndProbe::BaseSelectionGEN()
{
if(lepPtGEN==NULL)return false;
if(lepPtGEN->size()<2)return false; //2 leptons
if(lepChIdGEN->size()<2)return false; //2 leptons
int CHID2GEN=0;
	if(CHID2==-4) CHID2GEN=-13*13;
	if(CHID2==-1) CHID2GEN=-11*11;
	if(CHID2==-2) CHID2GEN=-11*13;
if( (*lepChIdGEN)[0]*(*lepChIdGEN)[1]!=CHID2GEN)return false; //two muons
        //Triggers??
return true;
}

int TagAndProbe::FillMiss()
{
#ifdef USE_ROOUNFOLD
response[ ("llPt"+extraLabel).c_str()]->Miss(llPtGEN,weight);
#endif
return 0;
}

int TagAndProbe::FillHistosGEN()
{
	//Gen Selection
	selGen=BaseSelectionGEN() && ( fabs(llMGEN-91)<llMCut) && (fabs( llYGEN) < ZYCut) ;
	//llMCut GEN
	if( selGen && ( (*jetPtGEN)[0] > JetPtCut))
		selGen=true;
		else selGen=false;
	if(!selGen) return 0; //---------------------------------------------
	
return 0;	
}
int TagAndProbe::FillHistos()
{
//FILL MISS AT EACH SELECTION FAILED
//before llM cut 
//debug=2;
if(debug>1)printf("Filling Histo\n");
histos[ ("nVtx" + extraLabel).c_str() ]->Fill(nVtx,weight);
histos[ ("llM" + extraLabel).c_str() ]->Fill(llM,weight);


float IsoCut=0.30;

bool IsoPass=true;
if( (*lepPFIsoRhoCor) [0] /*/(*lepPt)[0] */> IsoCut) IsoPass=false;
if( (*lepPFIsoRhoCor) [1] /*/(*lepPt)[1] */> IsoCut) IsoPass=false;


if(isTriggerMatchedFamily1 || isTriggerMatchedFamily2){ //if is triggered by someone
if(IsoPass){
	llM_passed_iso=llM;
	trees["passed_iso" + extraLabel ]->Fill();
	}
else {
	llM_failed_iso=llM;
	trees["failed_iso" + extraLabel ]->Fill();
	}
}

//I don't want isolated leptons - isolation is done later
bool TriggerPass=true;
//TODO TRIGGERPASS
if( isTriggerMatchedFamily5 || isTriggerMatchedFamily6 )
{//single mu trigger
TriggerPass=isTriggerMatchedFamily1 || isTriggerMatchedFamily2;
if(TriggerPass){
	llM_passed_trigger=llM;
	trees["passed_trigger" + extraLabel ]->Fill();
	}
else {
	llM_failed_trigger=llM;
	trees["failed_trigger" + extraLabel ]->Fill();
	}
}

if(!(fabs(llM-91)<llMCut))
	{
	if(selGen)FillMiss();
	return 0;
	} //---------------------------------------------
//after llM cut
if(debug>1)printf("Done Filling Histo\n");
}


int TagAndProbe::CreateHistos()
{

if(debug>0)printf("Creating %s -- %d \n",("nVtx"+extraLabel).c_str(),SmearType);

f_outFile=TFile::Open(outFile.c_str(),"RECREATE");
f_outFile->cd();
if(debug>0) printf("OutputFile %ld\n",long(f_outFile));

histos[("nVtx"+extraLabel).c_str()] 		= new TH1F(("nVtx"+extraLabel).c_str(),"nVtx;N_{Vtx};events",50,0,50);
if(debug>1) printf("Creating llM\n");
histos[("llM"+extraLabel).c_str()] 		= new TH1F(("llM"+extraLabel).c_str(),"llM;M^{ll};events",100,0,200);

if(debug>1) printf("Creating Trees passed_iso\n");
trees[("passed_iso"+extraLabel)] 		=new TTree(("passed_iso"+extraLabel).c_str(),"Passed");
if(debug>1) printf("Creating Trees failed_iso\n");
trees[("failed_iso"+extraLabel)] 		=new TTree(("failed_iso"+extraLabel).c_str(),"Failed");

trees[("passed_iso"+extraLabel)]->Branch("llM",&llM_passed_iso,"llM/F");
trees[("failed_iso"+extraLabel)]->Branch("llM",&llM_failed_iso,"llM/F");
trees[("passed_iso"+extraLabel)]->Branch("llPt",&llPt,"llPt/F"); //sufficient to book to add new variables
trees[("failed_iso"+extraLabel)]->Branch("llPt",&llPt,"llPt/F");
trees[("passed_iso"+extraLabel)]->Branch("runNum",&runNum,"runNum/F"); //sufficient to book to add new variables
trees[("failed_iso"+extraLabel)]->Branch("runNum",&runNum,"runNum/F");
trees[("passed_iso"+extraLabel)]->Branch("lepPt0",&lepPt[0],"lepPt0/F"); //sufficient to book to add new variables
trees[("failed_iso"+extraLabel)]->Branch("lepPt0",&lepPt[0],"lepPt0/F");

trees[("passed_trigger"+extraLabel)] 		=new TTree(("passed_trigger"+extraLabel).c_str(),"Passed");
trees[("failed_trigger"+extraLabel)] 		=new TTree(("failed_trigger"+extraLabel).c_str(),"Failed");
trees[("passed_trigger"+extraLabel)]->Branch("llM",&llM_passed_trigger,"llM/F");
trees[("failed_trigger"+extraLabel)]->Branch("llM",&llM_failed_trigger,"llM/F");
trees[("passed_trigger"+extraLabel)]->Branch("llPt",&llPt,"llPt/F");
trees[("failed_trigger"+extraLabel)]->Branch("llPt",&llPt,"llPt/F");
trees[("passed_trigger"+extraLabel)]->Branch("runNum",&runNum,"runNum/F"); //sufficient to book to add new variables
trees[("failed_trigger"+extraLabel)]->Branch("runNum",&runNum,"runNum/F");
trees[("passed_trigger"+extraLabel)]->Branch("lepPt0",&lepPt[0],"lepPt0/F"); //sufficient to book to add new variables
trees[("failed_trigger"+extraLabel)]->Branch("lepPt0",&lepPt[0],"lepPt0/F");
if(debug>1) {printf("done\n"); trees["passed_iso"]->Print();}
}

//constructor
TagAndProbe::TagAndProbe():BaseAnalysis(){f_outFile=NULL;outFile="TagAndProbe.root";}
//destructor
TagAndProbe::~TagAndProbe(){}

int TagAndProbe::Write(string outputFile){ //outputFile is useless. it is kept to overwrite the virtual function from the base class
	//I need the file already opend for the trees
	if(debug>0) printf("OutputFile %ld\n",long(f_outFile));
	if (f_outFile==NULL) {return 1;}
        f_outFile->cd();
        for(map<string,TH1F*>::iterator it=histos.begin();it!=histos.end();it++) it->second->Write();
        for(map<string,TH2F*>::iterator it=histos2.begin();it!=histos2.end();it++) it->second->Write();
        for(map<string,TTree*>::iterator it=trees.begin();it!=trees.end();it++) it->second->Write();
	return 0;
	}
