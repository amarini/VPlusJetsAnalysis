ROOUNFOLDLIB=/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/
ROOUNFOLDINC=/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/src/

CPPFLAGS=`root-config --libs --cflags` -I$(ROOUNFOLDINC) -L$(ROOUNFOLDLIB) -lRooUnfold

.PHONY:all
all: TagAndProbe.a

.PHONY: TagAndProbe
TagAndProbe: TagAndProbe.o

TagAndProbe.o: ../BaseAnalysis/BaseAnalysis.h TagAndProbe.h TagAndProbe.cc
	g++ -c TagAndProbe.cc $(CPPFLAGS) 

.PHONY: BaseAnalysis
BaseAnalysis:
	cd .. && make BaseAnalysis

TagAndProbe.a: TagAndProbe BaseAnalysis
	ar  rcs TagAndProbe.a TagAndProbe.o ../BaseAnalysis/BaseAnalysis.o ../BaseAnalysis/ReadParameters.o

tpexe: tpexe.cc TagAndProbe TagAndProbe.a
	g++  tpexe.cc TagAndProbe.a $(CPPFLAGS) -o tpexe
	echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/"

.PHONY:clean
clean:
	[ -f TagAndProbe.o ] && rm TagAndProbe.o || true
	[ -f TagAndProbe.a ] && rm TagAndProbe.a || true
	[ -f tpexe ] && rm tpexe || true

tpAnalysis: tpAnalysis.cc BaseAnalysis
	g++ -D STANDALONE -o tpAnalysis tpAnalysis.cc ../BaseAnalysis/BaseAnalysis.a $(CPPFLAGS) -lRooFit -lRooFitCore
