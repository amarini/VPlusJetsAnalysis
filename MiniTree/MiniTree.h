#include "../BaseAnalysis/BaseAnalysis.h"


class TagAndProbe: public BaseAnalysis
{
public:
	TagAndProbe();
	~TagAndProbe();

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
	float llM_passed_iso;
	float llM_failed_iso;
	float llM_passed_trigger;
	float llM_failed_trigger;
	TFile *f_outFile;
};

