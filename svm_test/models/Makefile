CXX = g++

CXXFLAGS = -Wall -O3
LDFLAGS = -L$(shell pwd)

main : main.o CandidateSVM.o DDpiCandidateSVM.o DstarDstarrhoCandidateSVM.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ libsvm.so.2

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

CandidateSVM.o : CandidateSVM.cc CandidateSVM.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

DDpiCandidateSVM.o : DDpiCandidateSVM.cc DDpiCandidateSVM.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

DstarDstarrhoCandidateSVM.o : DstarDstarrhoCandidateSVM.cc DstarDstarrhoCandidateSVM.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean : 
	rm -f main main.o CandidateSVM.o DDpiCandidateSVM.o DstarDstarrhoCandidateSVM.o
