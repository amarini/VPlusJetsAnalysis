#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TROOT.h"
#include "TDirectory.h"

#include "TMath.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "../BaseAnalysis/BaseAnalysis.h"

//Roofit
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooGenericPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooFitResult.h"
#include "RooHistPdf.h"
#include "RooVoigtian.h"
#include "RooWorkspace.h"


using namespace std;
using namespace RooFit;

map<string,vector<float> > BinsCut;
float Cuts[20];
const float llM_Min=40,llM_Max=150;
TFile *fOut;
FILE *fw;
//RooWorkspace *w ;


int Fit(TTree *t,int bin0,const char*name="signal"){ // bin in [0, (n1-1)*(n2-1)*(n3-1)  -1 ]
int bin=bin0;
printf("Going to Fit bin %d\n",bin);
//Create RooFit Workspaces
	gDirectory->cd();
	string cut = "";
	for(map<string,vector<float> >::iterator it=BinsCut.begin();it!=BinsCut.end();it++)
		{
		int n=int( it->second.size() ) -1;
		if(cut!="") cut += " && ";
		cut += Form("%f<%s && %s<%f",it->second.at(bin%n),it->first.c_str(),it->first.c_str(),it->second.at(bin%n + 1) );
		bin/=n;
		}
	//var
	RooRealVar llM("llM","llM",llM_Min,llM_Max);
	RooRealVar llPt("llPt","llPt",0,4000);

//RooFormulaVar effFunc("effFunc","a+b*m+c*",RooArgList(x)) ;
  RooDataSet data("data","data",RooArgList(llM,llPt),Import(*t),Cut(cut.c_str()));

  	RooRealVar mass("mass","mass",90,llM_Min,llM_Max) ;
  	RooRealVar sigma("sigma","sigma",1,0.1,20) ;
  	RooRealVar width("width","width",1,0.5,20) ;
	
  RooVoigtian sig("sig","sig",llM,mass,sigma,width) ; //Breit-Wigner + Gauss
	RooRealVar a("a","a",0,100000) ;
	RooRealVar b("b","b",-10,10) ;
	RooRealVar f("f","fraction",0.01,1.) ;
	RooRealVar l("l","l",1,100) ;
  	//RooPolynomial bkg("bkg","bkg",llM,RooArgSet(a,b)) ;
	RooGenericPdf bkg("bkg","a+b*llM",RooArgSet(llM,a,b));
	//RooExponential bkg("bkg","bkg",llM,l);
  	//RooAddPdf bkg("bkg","bkg",RooArgList(exp,pol),f);
	RooVoigtian effFunc();  //Breit-Wight+ Gauss
	RooRealVar frac("frac","fraction",0.01,1.) ;
   
	RooAddPdf model("model","model",RooArgList(sig,bkg),frac);

//Fit
	model.fitTo(data);
//Write Output

	RooAbsReal *intSig = sig.createIntegral(llM) ;	
	printf("---%s--- %lf | m=%lf w=%lf s=%lf\n",cut.c_str(),intSig->getVal(),mass.getVal(),width.getVal(),sigma.getVal());
	fprintf(fw,"---%s--- %lf | m=%lf w=%lf s=%lf\n",cut.c_str(),intSig->getVal(),mass.getVal(),width.getVal(),sigma.getVal());

	RooPlot* frame2 = llM.frame(Bins(50)) ;
	data.plotOn(frame2) ;
	model.plotOn(frame2,LineColor(kBlue)) ;
	model.plotOn(frame2, Components(bkg),LineStyle(kDashed), LineColor(kBlue))  ;
	TCanvas *c=new TCanvas(Form("%s_bin%d",name,bin0) , "" ,600,600);
	 gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
	gPad->SetLogy();
//	frame2->Write();
	fOut->cd();
	c->Write();
	
	//w->import(frame2);
	frame2->Delete();
	//c->Delete();
}

int tpAnalysis(string outDir="./")
{
//Open Files
TFile *f1=TFile::Open( (outDir+"/TagAndProbe_chid4.root").c_str() );
if(f1==NULL) printf("Error file %s does not exisists\n",(outDir+"/TagAndProbe_chid4.root").c_str());
fOut=TFile::Open( (outDir+"/TP_Results_chid4.root").c_str(),"RECREATE" );
fw=fopen((outDir+"/TP_Results_chid4.txt").c_str(),"w" ) ;

//define bins
	BinsCut["llPt"].push_back(0);
	BinsCut["llPt"].push_back(50);
	BinsCut["llPt"].push_back(100);
	BinsCut["llPt"].push_back(150);
	BinsCut["llPt"].push_back(200);
//open Trees
TTree *tPassedIso=(TTree*)f1->Get("passed_iso");
TTree *tFailedIso=(TTree*)f1->Get("failed_iso");

if(tPassedIso==NULL) printf("Error: TreePassed does not exists\n");
if(tFailedIso==NULL) printf("Error: TreeFailed does not exists\n");

int nBinsCut=1;
for(map<string,vector<float> >::iterator it=BinsCut.begin();it!=BinsCut.end();it++)
	nBinsCut*=it->second.size()-1;

printf("nBinsCut=%d\n",nBinsCut);
for(int bin=0;bin<nBinsCut;bin++)
	{
	Fit(tPassedIso,bin,"signal");	
	Fit(tFailedIso,bin,"background");	
	}
printf("DONE\n");
fOut->Close();
fclose(fw);
//w->writeToFile((outDir+"/TP_Results_chid4.root").c_str());
return 0;
}


#ifdef STANDALONE
int main(int argc,char**argv)
{
BaseAnalysis *A=new BaseAnalysis(); //need the Read config functions
string outDir=A->ReadMult("data/config.ini",argv[1],"OUTDIR");
printf("Going To Execute tpAnalysis with OutputDir=%s\n",outDir.c_str());
return tpAnalysis(outDir);
}
#endif
