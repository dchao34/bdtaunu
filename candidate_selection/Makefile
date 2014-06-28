CXX ?= g++
CXXFLAGS = -Wall -fPIC

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include
INCFLAGS += $(shell root-config --cflags)
LDFLAGS = -L$(PKG_LIBPATH) -lutilities -L/usr/local/lib -lsqlite3
LDFLAGS += $(shell root-config --libs)

MODEL_ROOTNAME = $(shell pwd | sed 's/\/[^/]*$$//')/candidate_learners/trained
CXXFLAGS += -D__MODEL_ROOTNAME='"$(MODEL_ROOTNAME)"'

OS = $(shell uname)

OBJECTS = YCandFeatureExtractor.o \
					DDpiFeatureExtractor.o DDstarpiFeatureExtractor.o \
					DstarDpiFeatureExtractor.o DstarDstarpiFeatureExtractor.o \
					DDrhoFeatureExtractor.o DDstarrhoFeatureExtractor.o \
					DstarDrhoFeatureExtractor.o DstarDstarrhoFeatureExtractor.o \
					CandidateSvmScorer.o DDpiSvmScorer.o

LIBNAME = libcandselect.so

all : CXXFLAGS += -O3
all : lib

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : lib

lib: $(OBJECTS) svm.o
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
		SHARED_SVMLIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/libsvm.so"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
		SHARED_SVMLIB_FLAG="-shared -Wl,-soname,@rpath/libsvm.so"; \
	fi; \
	$(CXX) $${SHARED_SVMLIB_FLAG} $(PKG_LIBPATH)/svm.o -o $(PKG_LIBPATH)/libsvm.so; \
	$(CXX) $${SHARED_LIB_FLAG} $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) $(LDFLAGS) -lsvm -o $(PKG_LIBPATH)/$(LIBNAME)

$(OBJECTS) : %.o : %.cc %.h
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $(PKG_LIBPATH)/$@

svm.o: svm.cc svm.h
	  $(CXX) $(CXXFLAGS) -c svm.cc -o $(PKG_LIBPATH)/svm.o

clean:
	rm -f *~ $(PKG_LIBPATH)/$(LIBNAME) $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) \
		$(PKG_LIBPATH)/svm.o $(PKG_LIBPATH)/libsvm.so
