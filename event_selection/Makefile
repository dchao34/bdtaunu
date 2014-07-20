CXX ?= g++
CXXFLAGS = -Wall -fPIC

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include
INCFLAGS += $(shell root-config --cflags)

SHARED_LIBARIES = utilities createdb sqlite3
LDFLAGS = -L$(PKG_LIBPATH) -L/usr/local/lib
LDFLAGS += $(addprefix -l, $(SHARED_LIBARIES))
LDFLAGS += $(shell root-config --libs)

MODEL_ROOTNAME = $(shell pwd | sed 's/\/[^/]*$$//')/meta/svm_event_learners
CXXFLAGS += -D__MODEL_ROOTNAME='"$(MODEL_ROOTNAME)"'

OS = $(shell uname)

OBJECTS = SQLiteAccessor.o SQLiteReader.o EventSQLiteReader.o \
				  SQLiteUpdater.o EventStatusSQLiteUpdater.o \
				  EventFeatureExtractor.o

LIBNAME = libeventselect.so

HEADER_ONLY = EventFeatureExtractorFactory.h

BINARIES = create_libsvm_data


all : CXXFLAGS += -O3
all : lib $(BINARIES)

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : lib $(BINARIES)

$(BINARIES) : % : %.o lib
	$(CXX) $(LDFLAGS) $(patsubst lib%,-l%,$(basename $(LIBNAME))) -Wl,-rpath,$(PKG_LIBPATH) -o $@ $<

$(addsuffix .o, $(BINARIES)) : %.o : %.cc $(HEADER_ONLY)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

lib : $(OBJECTS)
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) $(LDFLAGS) -o $(PKG_LIBPATH)/$(LIBNAME)

$(OBJECTS) : %.o : %.cc %.h
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $(PKG_LIBPATH)/$@

clean : 
	rm -f *~ $(BINARIES) $(addsuffix .o, $(BINARIES)) \
		$(PKG_LIBPATH)/$(LIBNAME) $(addprefix $(PKG_LIBPATH)/, $(OBJECTS))
