ROOUNFOLDLIB=/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/
ROOUNFOLDINC=/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/src/

CPPFLAGS=`root-config --libs --cflags` 
#-I$(ROOUNFOLDINC) -L$(ROOUNFOLDLIB) -lRooUnfold

.PHONY:all
all: MiniTree.a

.PHONY: MiniTree
MiniTree: MiniTree.o

MiniTree.o: ../BaseAnalysis/BaseAnalysis.h MiniTree.h MiniTree.cc
	g++ -c MiniTree.cc $(CPPFLAGS) 

.PHONY: BaseAnalysis
BaseAnalysis:
	cd .. && make BaseAnalysis

MiniTree.a: MiniTree BaseAnalysis
	ar  rcs MiniTree.a MiniTree.o ../BaseAnalysis/BaseAnalysis.o ../BaseAnalysis/ReadParameters.o

tree.exe: tree.cc MiniTree MiniTree.a
	g++  tree.cc MiniTree.a $(CPPFLAGS) -o tree.exe
	echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/"

.PHONY:clean
clean:
	[ -f MiniTree.o ] && rm MiniTree.o || true
	[ -f MiniTree.a ] && rm MiniTree.a || true
	[ -f tree.exe ] && rm tree.exe || true

