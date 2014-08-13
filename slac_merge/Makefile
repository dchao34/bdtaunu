CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += $(shell root-config --cflags)
CXXFLAGS += -I/usr/local/include -Isrc/
LDFLAGS = $(shell root-config --libs)
LDFLAGS += -L/usr/local/lib -lsqlite3

OLD_GENERIC_EVENTID_PATHNAME = $(shell pwd)/old_generic_ml_assignment.txt
CXXFLAGS += -D__OLD_GENERIC_EVENTID_PATHNAME='"$(OLD_GENERIC_EVENTID_PATHNAME)"'

target_list = merge_ntp #assign_sigmc_ml assign_generic_ml
library_list = mtrand.o 
               

targets = $(target_list)
library_objects = $(library_list) #$(addprefix src/, $(library_list))

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
