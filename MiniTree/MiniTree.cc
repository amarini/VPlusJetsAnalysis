#include "MiniTree.h"
#include "math.h"

int MiniTree::Smear(){
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

bool MiniTree::BaseSelection()
{
if(lepPt->size()<2)return false; //2 leptons
if( (*lepChId)[0]*(*lepChId)[1]!=CHID2)return false; //two muons
        //Triggers??
return true;
}

bool MiniTree::BaseSelectionGEN()
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

int MiniTree::FillMiss()
{
#ifdef USE_ROOUNFOLD
response[ ("llPt"+extraLabel).c_str()]->Miss(llPtGEN,weight);
#endif
return 0;
}

int MiniTree::FillHistosGEN()
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
int MiniTree::FillHistos()
{
//FILL MISS AT EACH SELECTION FAILED
//before llM cut 
//debug=2;
if(debug>1)printf("Filling Histo\n");
histos[ ("nVtx" + extraLabel).c_str() ]->Fill(nVtx,weight);
histos[ ("llM" + extraLabel).c_str() ]->Fill(llM,weight);
	
	//clear
	jetPt_->clear();
	jetEta_->clear();
	jetPhi_->clear();
	jetE_->clear();
	
	//fill
	for(int i=0;i<jet.size() && jet[i]>=0; i++)
		{
		jetPt_->push_back ((*jetPt)[jet[i]]);	
		jetEta_->push_back((*jetEta)[jet[i]]);	
		jetPhi_->push_back((*jetPhi)[jet[i]]);	
		jetE_->push_back  ((*jetE)[jet[i]]);	
		}
	if(photonPt->size()>30)
		gammaPt=(*photonPt)[0];
	else 
		gammaPt=-1;
	
	trees["minitree" + extraLabel ]->Fill();

}


int MiniTree::CreateHistos()
{

if(debug>0)printf("Creating %s -- %d \n",("nVtx"+extraLabel).c_str(),SmearType);

f_outFile=TFile::Open(outFile.c_str(),"RECREATE");
f_outFile->cd();
if(debug>0) printf("OutputFile %ld\n",long(f_outFile));

histos[("nVtx"+extraLabel).c_str()] 		= new TH1F(("nVtx"+extraLabel).c_str(),"nVtx;N_{Vtx};events",50,0,50);
if(debug>1) printf("Creating llM\n");
histos[("llM"+extraLabel).c_str()] 		= new TH1F(("llM"+extraLabel).c_str(),"llM;M^{ll};events",100,0,200);


if(debug>1) printf("Creating Trees\n");
trees[("minitree"+extraLabel)] 		=new TTree(("minitree"+extraLabel).c_str(),"MiniTree");

trees[("minitree"+extraLabel)]->Branch("llM",&llM,"llM/F");
trees[("minitree"+extraLabel)]->Branch("llPt",&llPt,"llM/F");
trees[("minitree"+extraLabel)]->Branch("gammaPt",&gammaPt,"gammaPt/F");
	
	jetPt_=new vector<float>;
	jetEta_=new vector<float>;
	jetPhi_=new vector<float>;
	jetE_=new vector<float>;
trees[("minitree"+extraLabel)]->Branch("jetPt",&jetPt_);
trees[("minitree"+extraLabel)]->Branch("jetEta",&jetEta_);
trees[("minitree"+extraLabel)]->Branch("jetPhi",&jetPhi_);
trees[("minitree"+extraLabel)]->Branch("jetE",&jetE_);
//jet
if(debug>1) {printf("done\n"); trees["minitree"]->Print();}
}

//constructor
MiniTree::MiniTree():BaseAnalysis(){f_outFile=NULL;outFile="MiniTree.root";}
//destructor
MiniTree::~MiniTree(){}

int MiniTree::Write(string outputFile){ //outputFile is useless. it is kept to overwrite the virtual function from the base class
	//I need the file already opend for the trees
	if(debug>0) printf("OutputFile %ld\n",long(f_outFile));
	if (f_outFile==NULL) {return 1;}
        f_outFile->cd();
        for(map<string,TH1F*>::iterator it=histos.begin();it!=histos.end();it++) it->second->Write();
        for(map<string,TH2F*>::iterator it=histos2.begin();it!=histos2.end();it++) it->second->Write();
        for(map<string,TTree*>::iterator it=trees.begin();it!=trees.end();it++) it->second->Write();
	return 0;
	}
