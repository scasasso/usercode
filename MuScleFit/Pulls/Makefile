SOURCES=Pulls.cpp dict.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pull

CC      = g++
CCFLAG = -g -c -Wall  $(shell root-config --cflags)
LDFLAG = $(shell root-config --libs) -L/opt/local/root/lib -lGenVector

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAG)

.cpp.o:
	$(CC) -I. $(CCFLAG) -o $@ $<

dict.cpp: ../Validation/Muon.h ../Validation/MuonPair.h GenMuonPair.h LinkDef.h
	rootcint -f $@ -c $^

all: $(SOURCES) $(EXECUTABLE) 

.PHONY: clean cleanest

clean:
	rm -f $(OBJECTS) dict.cpp dict.h
	rm -f pull