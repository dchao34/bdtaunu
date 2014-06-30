CXX ?= g++
CXXFLAGS = -Wall -fPIC

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include
INCFLAGS += $(shell root-config --cflags)
LDFLAGS = -L$(PKG_LIBPATH) -lutilities -L/usr/local/lib -lsqlite3
LDFLAGS += $(shell root-config --libs)

PDT_FILE_PATHNAME = $(shell pwd | sed 's/\/[^/]*$$//')/meta/pdt.dat
CXXFLAGS += -D__PDT_FILE_PATHNAME='"$(PDT_FILE_PATHNAME)"'

OS = $(shell uname)

OBJECTS = RootReader.o BDtaunuReader.o BDtaunuMcReader.o BDtaunuSigMcReader.o \
          UpsilonCandidate.o UpsilonList.o \
          SQLiteTableBuilder.o EventSQLiteTableBuilder.o McEventSQLiteTableBuilder.o \
					CandidateSQLiteTableBuilder.o McCandidateSQLiteTableBuilder.o \
					EventStatusSQLiteTableBuilder.o OptimalCandidateSQLiteTableBuilder.o

LIBNAME = libcreatedb.so

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
