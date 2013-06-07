#include "TChain.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"

#include <iostream>

using namespace std;


int Draw()
{
string blind="1";//"(runNum<2.03777e+05)";
string selectionData=" && abs(llM-91)<20 && jetPt[0]>30";
string selectionMC="PUWeight*( 1"+selectionData+")";//"PUWeight";
string variable="MyMath::A1(llPt,jetPt[0],jetPt[1],jetPt[2],llPhi,jetPhi[0],jetPhi[1],jetPhi[2])";//"llM";
//float lumi=40;
float lumi=19.8;
//float lumi=0.3;

gSystem->Load("MyMath_C.so");

TChain *DoubleL=new TChain("minitree"); DoubleL->Add("MiniTree/MiniTree_type0_chid4_*.root");
					DoubleL->Add("MiniTree/MiniTree_type0_chid1_*.root");
TChain *MuEG=new TChain("minitree");    MuEG   ->Add("MiniTree/MiniTree_type0_chid2_*.root");

//MC 
TChain *DY=new TChain("minitree");      DY     ->Add("MiniTree/MiniTree_type1_chid4_*.root");
                                        DY     ->Add("MiniTree/MiniTree_type1_chid1_*.root");

TChain *TT=new TChain("minitree");      TT     ->Add("MiniTree/MiniTree_type2_chid4_*.root");
                                        TT     ->Add("MiniTree/MiniTree_type2_chid1_*.root");

TChain *WJ=new TChain("minitree");      WJ     ->Add("MiniTree/MiniTree_type3_chid4_*.root");
                                        WJ     ->Add("MiniTree/MiniTree_type3_chid1_*.root");

TChain *WW=new TChain("minitree");      WW     ->Add("MiniTree/MiniTree_type4_chid4_*.root");
                                        WW     ->Add("MiniTree/MiniTree_type4_chid1_*.root");

TChain *WZ=new TChain("minitree");      WZ     ->Add("MiniTree/MiniTree_type5_chid4_*.root");
                                        WZ     ->Add("MiniTree/MiniTree_type5_chid1_*.root");

TChain *ZZ=new TChain("minitree");      ZZ     ->Add("MiniTree/MiniTree_type6_chid4_*.root");
                                        ZZ     ->Add("MiniTree/MiniTree_type6_chid1_*.root");

TCanvas *c=new TCanvas("c","c",800,600);
c->SetLogy();

Int_t nBins=200;Float_t xMin=0; Float_t xMax=4*3.1416; string title="A_{1}";
TH1F* h_LL=new TH1F("LL",title.c_str(),nBins,xMin,xMax);
	DoubleL->Draw((variable+">>LL").c_str(),(blind+selectionData).c_str(),"goff");
TH1F* h_OF=new TH1F("OF",title.c_str(),nBins,xMin,xMax);
	MuEG   ->Draw((variable+">>OF").c_str(),(blind+selectionData).c_str(),"goff");

TH1F* h_DY=new TH1F("DY",title.c_str(),nBins,xMin,xMax);
	DY     ->Draw((variable+">>DY").c_str(),selectionMC.c_str(),"goff"); h_DY->Scale(lumi);

TH1F* h_TT=new TH1F("TT",title.c_str(),nBins,xMin,xMax);
	TT     ->Draw((variable+">>TT").c_str(),selectionMC.c_str(),"goff"); h_TT->Scale(lumi);

TH1F* h_WJ=new TH1F("WJ",title.c_str(),nBins,xMin,xMax);
	WJ     ->Draw((variable+">>WJ").c_str(),selectionMC.c_str(),"goff"); h_WJ->Scale(lumi);

TH1F* h_WW=new TH1F("WW",title.c_str(),nBins,xMin,xMax);
	WW     ->Draw((variable+">>WW").c_str(),selectionMC.c_str(),"goff"); h_WW->Scale(lumi);

TH1F* h_WZ=new TH1F("WZ",title.c_str(),nBins,xMin,xMax);
	WZ     ->Draw((variable+">>WZ").c_str(),selectionMC.c_str(),"goff"); h_WZ->Scale(lumi);

TH1F* h_ZZ=new TH1F("ZZ",title.c_str(),nBins,xMin,xMax);
	ZZ     ->Draw((variable+">>ZZ").c_str(),selectionMC.c_str(),"goff"); h_ZZ->Scale(lumi);

h_LL->SetMarkerStyle(20); h_LL->SetLineColor(kBlack);
h_OF->SetMarkerStyle(29);h_OF->SetMarkerSize(0.8);h_OF->SetMarkerColor(kRed+2); h_OF->SetLineColor(kRed+2);

h_DY->SetFillColor(kYellow);   h_DY->SetLineWidth(2);h_DY->SetLineColor(kBlack);
h_TT->SetFillColor(kMagenta+2);h_TT->SetLineWidth(2);h_TT->SetLineColor(kBlack);
h_WJ->SetFillColor(kGreen+2);  h_WJ->SetLineWidth(2);h_WJ->SetLineColor(kBlack);
h_WW->SetFillColor(kGreen+2);  h_WW->SetLineWidth(2);h_WW->SetLineColor(kBlack);
h_WZ->SetFillColor(kGreen+2);  h_WZ->SetLineWidth(2);h_WZ->SetLineColor(kBlack);
h_ZZ->SetFillColor(kGreen+2);  h_ZZ->SetLineWidth(2);h_ZZ->SetLineColor(kBlack);

THStack *S_mc=new THStack("MC","MC");
	S_mc->Add(h_TT);
	S_mc->Add(h_ZZ);
	S_mc->Add(h_WZ);
	S_mc->Add(h_WW);
	S_mc->Add(h_WJ);
	S_mc->Add(h_DY);

//h_DY->Draw("HIST");
S_mc->Draw("HIST");
h_LL->Draw("P SAME");
h_OF->Draw("P SAME");
//h_DY->Draw("HIST SAME");
}
