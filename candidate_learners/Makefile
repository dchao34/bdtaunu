CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += $(shell root-config --cflags)
CXXFLAGS += -I/usr/local/include -I../src/
LDFLAGS = $(shell root-config --libs)
LDFLAGS += -L/usr/local/lib -lsqlite3

target_list = main
library_list = YCandFeatureExtractor.o \
							 DDpiFeatureExtractor.o
header_only_list = YCandFeatureExtractorFactory.h

targets = $(target_list)
library_objects = $(library_list)

all : CXXFLAGS += -O3
all : $(targets)

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : $(targets)

$(targets) : % : %.o $(library_objects)
	$(CXX) $(LDFLAGS) -o $@ $^

$(addsuffix .o, $(targets)) : %.o : %.cc $(header_only_list)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(library_objects) : %.o : %.cc %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean : 
	rm -f $(targets) $(addsuffix .o, $(targets)) $(library_objects)
