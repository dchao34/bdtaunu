CXX ?= g++
CXXFLAGS = -Wall -fPIC

PKG_INCPATH = ../include
PKG_LIBPATH = ../lib
INCFLAGS = -I$(PKG_INCPATH) -I/usr/local/include
LDFLAGS = -L$(PKG_LIBPATH) -L/usr/local/lib

OS = $(shell uname)

OBJECTS = helpers.o DatReader.o
LIBNAME = libutilities.so

all : CXXFLAGS += -O3
all : lib

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : lib

lib: $(OBJECTS) svm.o mtrand.o
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
		SHARED_SVMLIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/libsvm.so"; \
		SHARED_MTRANDLIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/libmtrand.so"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
		SHARED_SVMLIB_FLAG="-shared -Wl,-soname,@rpath/libsvm.so"; \
		SHARED_MTRANDLIB_FLAG="-shared -Wl,-soname,@rpath/libmtrand.so"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) $(LDFLAGS) -o $(PKG_LIBPATH)/$(LIBNAME); \
	$(CXX) $${SHARED_SVMLIB_FLAG} $(PKG_LIBPATH)/svm.o -o $(PKG_LIBPATH)/libsvm.so; \
	$(CXX) $${SHARED_MTRANDLIB_FLAG} $(PKG_LIBPATH)/mtrand.o -o $(PKG_LIBPATH)/libmtrand.so;

$(OBJECTS) : %.o : %.cc %.h
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $(PKG_LIBPATH)/$@

svm.o: svm.cc svm.h
	  $(CXX) $(CXXFLAGS) -c svm.cc -o $(PKG_LIBPATH)/svm.o

mtrand.o: mtrand.cc mtrand.h
	  $(CXX) $(CXXFLAGS) -c mtrand.cc -o $(PKG_LIBPATH)/mtrand.o

clean:
	rm -f *~ $(PKG_LIBPATH)/$(LIBNAME) $(addprefix $(PKG_LIBPATH)/, $(OBJECTS)) \
		$(PKG_LIBPATH)/svm.o $(PKG_LIBPATH)/libsvm.so \
		$(PKG_LIBPATH)/mtrand.o $(PKG_LIBPATH)/libmtrand.so
