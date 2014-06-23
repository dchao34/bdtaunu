CXX ?= g++
CFLAGS = -Wall -O3 -fPIC

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include
INCFLAGS += $(shell root-config --cflags)
LDFLAGS = -L$(PKG_LIBPATH) -lutilities -L/usr/local/lib -lsqlite3
LDFLAGS += $(shell root-config --libs)

PDT_FILE_PATHNAME = $(shell pwd | sed 's/\/[^/]*$$//')/meta/pdt.dat
CFLAGS += -D__PDT_FILE_PATHNAME='"$(PDT_FILE_PATHNAME)"'

OS = $(shell uname)

OBJECTS = RootReader.o BDtaunuReader.o BDtaunuMcReader.o BDtaunuSigMcReader.o \
          UpsilonCandidate.o UpsilonList.o \
          create_sigmc_database.o

LIBNAME = libcreatedb.so

lib: $(OBJECTS)
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) $(LDFLAGS) -o $(PKG_LIBPATH)/$(LIBNAME)

$(OBJECTS) : %.o : %.cc %.h
	$(CXX) $(CFLAGS) $(INCFLAGS) -c $< -o $(PKG_LIBPATH)/$@

clean:
	rm -f *~ $(PKG_LIBPATH)/$(LIBNAME) $(addprefix $(PKG_LIBPATH)/, $(OBJECTS))
