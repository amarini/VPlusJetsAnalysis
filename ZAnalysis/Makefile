ROOUNFOLDLIB=/home/root_v5-34-05/RooUnfold-1.1.1/
ROOUNFOLDINC=/home/root_v5-34-05/RooUnfold-1.1.1/src/

CPPFLAGS=`root-config --libs --cflags` -I$(ROOUNFOLDINC) -L$(ROOUNFOLDLIB) -lRooUnfold

.PHONY:all
all: ZAnalysis.a

.PHONY: ZAnalysis
ZAnalysis: ZAnalysis.o

ZAnalysis.o: ../BaseAnalysis/BaseAnalysis.h ZAnalysis.h ZAnalysis.cc
	g++ -c ZAnalysis.cc $(CPPFLAGS) 

.PHONY: BaseAnalysis
BaseAnalysis:
	cd .. && make BaseAnalysis

ZAnalysis.a: ZAnalysis BaseAnalysis
	ar  rcs ZAnalysis.a ZAnalysis.o ../BaseAnalysis/BaseAnalysis.o ../BaseAnalysis/ReadParameters.o

zexe: zexe.cc ZAnalysis ZAnalysis.a
	g++ -o zexe zexe.cc ZAnalysis.a $(CPPFLAGS) 
	echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/"

.PHONY:clean
clean:
	[ -f ZAnalysis.o ] && rm ZAnalysis.o || true
	[ -f ZAnalysis.a ] && rm ZAnalysis.a || true
	[ -f zexe ] && rm zexe || true
