CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += $(shell root-config --cflags)
CXXFLAGS += -I/usr/local/include -Isrc/
LDFLAGS = $(shell root-config --libs)
LDFLAGS += -L/usr/local/lib -lsqlite3

PDT_FILE_PATHNAME = $(shell pwd)/meta/pdt.dat
CXXFLAGS += -D__PDT_FILE_PATHNAME='"$(PDT_FILE_PATHNAME)"'

target_list = main
library_list =  RootReader.o BDtaunuReader.o DatReader.o \
                utilities.o bdtaunu_create_sqldatabase.o \
                UpsilonCandidate.o UpsilonList.o BDtaunuMcReader.o

targets = $(target_list)
library_objects = $(addprefix src/, $(library_list))

all : CXXFLAGS += -O3
all : $(targets)

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : $(targets)

$(targets) : % : %.o $(library_objects)
	$(CXX) $(LDFLAGS) -o $@ $^

$(addsuffix .o, $(targets)) : %.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(library_objects) : %.o : %.cc %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean : 
	rm -f $(targets) $(addsuffix .o, $(targets)) $(library_objects)
