CXX ?= g++
CXXFLAGS = -Wall -fPIC

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include
INCFLAGS += $(shell root-config --cflags)
LDFLAGS = -L$(PKG_LIBPATH) -lutilities -lcreatedb -lsvm -L/usr/local/lib -lsqlite3
LDFLAGS += $(shell root-config --libs)

MODEL_ROOTNAME = $(shell pwd | sed 's/\/[^/]*$$//')/meta/svm_candidate_learners
CXXFLAGS += -D__MODEL_ROOTNAME='"$(MODEL_ROOTNAME)"'

OS = $(shell uname)

OBJECTS = YCandFeatureExtractor.o YCandSvmAdapter.o YCandSvmScorer.o

LIBNAME = libcandselect.so

all : CXXFLAGS += -O3
all : lib

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : lib

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
	rm -f *~ $(PKG_LIBPATH)/$(LIBNAME) $(addprefix $(PKG_LIBPATH)/, $(OBJECTS))
