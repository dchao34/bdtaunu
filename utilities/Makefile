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
