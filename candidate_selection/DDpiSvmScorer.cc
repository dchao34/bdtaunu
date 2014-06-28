#include "DDpiSvmScorer.h"

DDpiSvmScorer::DDpiSvmScorer(
	const char *model_fname, 
  const char *scale_fname) : 
	CandidateSvmScorer(2, 9, 10, 9, 0, 0) {
	Initialize(model_fname, scale_fname);
}

DDpiSvmScorer::~DDpiSvmScorer() {
	Cleanup();
}

