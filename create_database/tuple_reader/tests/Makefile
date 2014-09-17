# Configurations
# --------------

# compiler
CXX ?= g++
CXXFLAGS = -Wall -std=c++11
CXXFLAGS += -fPIC

# Contents
# --------

BINARIES = mc_reader1

# Dependencies
# ------------

# tuple_reader 
TUPLE_READER_LIBNAME = -lTupleReader
TUPLE_READER_INC_PATH = ../
TUPLE_READER_LIB_PATH = ../lib
INCFLAGS += -I $(TUPLE_READER_INC_PATH)
LDFLAGS += -L $(TUPLE_READER_LIB_PATH) $(TUPLE_READER_LIBNAME)

# cern root
INCFLAGS += $(shell root-config --cflags)
LDFLAGS += $(shell root-config --libs)

# Build Rules
# -----------

$@ : $@.cc
	$(CXX) $(CXXFLAGS) $< -o $%

all : CXXFLAGS += -O3
all : $(BINARIES)

debug : CXX += -DDEBUG -g
debug : $(BINARIES)

$(BINARIES) : % : %.cc
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) -Wl,-rpath,$(TUPLE_READER_LIB_PATH) -o $@ $<

clean:
	rm -f *~ *.o `find . -perm +100 -type f`
