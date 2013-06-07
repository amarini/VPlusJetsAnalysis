#include "../BaseAnalysis/BaseAnalysis.h"


class MiniTree: public BaseAnalysis
{
public:
	MiniTree();
	~MiniTree();

	int CreateHistos();
	//int SetActive(); //read list of active Branches from a configuration file
	int FillHistos();
//	int OpenFiles();
	bool BaseSelection();
	bool BaseSelectionGEN();
	int FillMiss();
	int FillHistosGEN();
	int Smear();
	int Write(string outputFile); //output File not used Here
	int Write(){return Write("");}
	string outFile;
	
protected:
	bool selGen;
	map<string,TTree*> trees;
	TFile *f_outFile;
	
	float gammaPt;
	vector<float> *jetPt_;
	vector<float> *jetEta_;
	vector<float> *jetPhi_;
	vector<float> *jetE_;
	Int_t nJets_;
};

