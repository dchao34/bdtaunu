CXX ?= g++
CXXFLAGS = -Wall -fPIC -std=c++11

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include -I$(BOOST_ROOT)
INCFLAGS += $(shell root-config --cflags)

SHARED_LIBARIES = utilities sqlite3
LDFLAGS = -L$(PKG_LIBPATH) -L/usr/local/lib
LDFLAGS += $(addprefix -l, $(SHARED_LIBARIES))
LDFLAGS += $(shell root-config --libs)

PDT_FILE_PATHNAME = $(shell pwd | sed 's/\/[^/]*$$//')/meta/pdt.dat
CXXFLAGS += -D__PDT_FILE_PATHNAME='"$(PDT_FILE_PATHNAME)"'

OS = $(shell uname)

OBJECTS = UpsilonCandidate.o \
					RootReader.o BDtaunuReader.o \
					RecoIndexer.o \
					RecoGraphVisitors.o RecoGraphManager.o

LIBNAME = libcreatedb.so

HEADER_ONLY = RecoGraph.h RecoParticles.h BDtaunuGraphWriter.h

BINARIES = test2 test #test1 test_bgl

all : CXXFLAGS += -O3
all : lib $(BINARIES)

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : lib

$(BINARIES) : % : %.o lib
	$(CXX) $(LDFLAGS) $(patsubst lib%,-l%,$(basename $(LIBNAME))) -Wl,-rpath,$(PKG_LIBPATH) -o $@ $<

$(addsuffix .o, $(BINARIES)) : %.o : %.cc $(HEADER_ONLY)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

lib: $(OBJECTS)
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) $(LDFLAGS) -o $(PKG_LIBPATH)/$(LIBNAME)

$(OBJECTS) : %.o : %.cc %.h
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $(PKG_LIBPATH)/$@

clean:
	rm -f *~ $(BINARIES) $(addsuffix .o, $(BINARIES)) \
		$(PKG_LIBPATH)/$(LIBNAME) $(addprefix $(PKG_LIBPATH)/, $(OBJECTS))
