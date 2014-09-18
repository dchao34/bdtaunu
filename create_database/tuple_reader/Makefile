# Configurations
# --------------

# compiler
CXX ?= g++
CXXFLAGS = -Wall -std=c++11 
CXXFLAGS += -fPIC

# library name
LIBNAME = libTupleReader.so

# path to compiled libaries
PKG_LIBPATH = lib

# package Contents
SOURCES = BDtaunuHelpers.cc UpsilonCandidate.cc \
					RootReader.cc BDtaunuReader.cc BDtaunuMcReader.cc \
					RecoIndexer.cc RecoGraphVisitors.cc RecoGraphManager.cc \
					RecoDTypeCatalogue.cc \
					McGraphManager.cc McBTypeCatalogue.cc McGraphVisitors.cc

# Dependencies
# ------------

# boost
INCFLAGS += -I$(BOOST_ROOT)

# cern root
INCFLAGS += $(shell root-config --cflags)
LDFLAGS += $(shell root-config --libs)

# particle data file
PDT_FILE_PATHNAME = $(shell pwd | sed 's/\/[^/]*$$//')/tuple_reader/meta/pdt.dat
CXXFLAGS += -D__PDT_FILE_PATHNAME='"$(PDT_FILE_PATHNAME)"'

# Build Rules
# -----------

.PHONY: all debug lib clean distclean

OBJECTS = $(addprefix $(PKG_LIBPATH)/, $(patsubst %.cc, %.o, $(SOURCES)))
DEPENDENCIES = $(addprefix $(PKG_LIBPATH)/, $(patsubst %.cc, %.d, $(SOURCES)))

all : CXXFLAGS += -O3
all : lib

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : lib

lib : $(PKG_LIBPATH)/$(LIBNAME)

$(PKG_LIBPATH)/$(LIBNAME) : $(OBJECTS)
	if [ "$(shell uname)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} $(OBJECTS) $(LDFLAGS) -o $@

$(OBJECTS) : $(PKG_LIBPATH)/%.o : %.cc %.h $(PKG_LIBPATH)/%.d
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(DEPENDENCIES) : $(PKG_LIBPATH)/%.d : %.cc %.h Makefile
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -MM -MT $(PKG_LIBPATH)/$*.o -c $< -o $@

clean:
	rm -f *~ $(PKG_LIBPATH)/$(LIBNAME) $(OBJECTS)

distclean:
	rm -f *~ $(PKG_LIBPATH)/$(LIBNAME) $(OBJECTS) $(DEPENDENCIES)

-include $(DEPENDENCIES)

