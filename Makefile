CXX ?= g++
CXXFLAGS = -Wall

PKG_INCPATH = ./include
PKG_LIBPATH = ./lib

INCPATH = -I$(PKG_INCPATH) -I/usr/local/include
LDPATH = -L$(PKG_LIBPATH) -L/usr/local/lib

SHARED_LIBARIES = utilities createdb candselect eventselect

CXXFLAGS = $(INCPATH)
CXXFLAGS += $(shell root-config --cflags)

LDFLAGS = $(LDPATH)
LDFLAGS += $(addprefix -l, $(SHARED_LIBARIES)) -lsqlite3
LDFLAGS += $(shell root-config --libs)

TARGETS = build_generic_db #update_event_svm_scores build_sigmc_db 

all : CXXFLAGS += -O3
all : $(TARGETS)

debug : CXX += -DDEBUG -g
debug : CXXFLAGS += -O0
debug : $(TARGETS)

$(TARGETS): % : %.o $(addsuffix .so, $(addprefix $(PKG_LIBPATH)/lib, $(SHARED_LIBARIES)))
	$(CXX) $(LDFLAGS) -Wl,-rpath,$(PKG_LIBPATH) -o $@ $<

#$(TARGETS): % : %.o $(SHARED_LIBARIES)
#	$(CXX) $(LDFLAGS) -Wl,-rpath,$(PKG_LIBPATH) -o $@ $<

$(addsuffix .o, $(TARGETS)) : %.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

#.PHONY: $(SHARED_LIBARIES)

#$(SHARED_LIBARIES) : % :
#	make -C $@

clean : 
	rm -f *~ $(TARGETS) $(addsuffix .o, $(TARGETS))
