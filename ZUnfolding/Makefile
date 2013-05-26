ROOUNFOLDLIB=/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/
ROOUNFOLDINC=/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/src/

CPPFLAGS=`root-config --libs --cflags` -I$(ROOUNFOLDINC) -L$(ROOUNFOLDLIB) -lRooUnfold

ZUnfolding: ZUnfolding.cc ZAnalysis
	g++ -o ZUnfolding ZUnfolding.cc ../ZAnalysis/ZAnalysis.a  $(CPPFLAGS) 

.PHONY:ZAnalysis
ZAnalysis:
	cd .. && make ZAnalysis
