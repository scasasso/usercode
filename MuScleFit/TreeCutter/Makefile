SOURCES=TreeCutter.cpp dict.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=letscut

CC      = g++
CCFLAG = -g -c -Wall  $(shell root-config --cflags)
LDFLAG = $(shell root-config --libs) -L/usr/local/root/lib -lGenVector

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAG)

.cpp.o:
	$(CC) -I. $(CCFLAG) -o $@ $<

dict.cpp: Muon.h GenMuonPair.h MuonPair.h LinkDef.h
	rootcint -f $@ -c $^

all: $(SOURCES) $(EXECUTABLE) 

clean:
	rm -f *.o *.so
	rm -f letscut

