ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)
CXXFLAGS      =-I$(ROOTSYS)/include -O -Wall -fPIC

SOURCEDIR	=  ./

HEADERDIR	=  ./

MAKE	=	make

object	+=	His_BKGtt.o
object	+=	His_BKGww.o
object	+=	His_BKGzz.o
object	+=	His_sig_mhp800_ATLAS.o

all: $(object) main.exe
.PHONY : all

$(object): %.o: %.C
	g++ -c $< -o $@ -I $(ROOTCFLAGS) -I .

main.exe:main.C
	g++ -O3 -Wall -I $(ROOTCFLAGS) $^ -o $@ $(object) -I . $(ROOTLIBS) -lMinuit	-lRooFitCore	-lRooFit 

echo:
	echo "object=$(object)"
	echo "ROOTCFLAGS=$(ROOTCFLAGS)"
	echo "ROOTLIBS=$(ROOTLIBS)"
	echo "ROOTGLIBS=$(ROOTGLIBS)"
	echo "ROOTSYS=$(ROOTSYS)"
	echo "PATH=$(PATH)"
	echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)"
.PHONY : echo

.PHONY : clean
clean: 
	rm -rf main.exe *.o *~ 
deadcor.exe:



