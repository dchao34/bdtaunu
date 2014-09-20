#ifndef __BDTAUNUDEF_H__
#define __BDTAUNUDEF_H__

/*! \file bdtaunu_definitions.h
 *  \brief Constants defined for this analysis.
 *
 *  This file contains any constants and enumerations that are used
 *  throughout the analysis package.
 */

namespace bdtaunu {

const int UpsilonLund = 70553;
const int B0Lund = 511;
const int BcLund = 521;
const int D0Lund = 421;
const int DcLund = 411;
const int Dstar0Lund = 423;
const int DstarcLund = 413;
const int KSLund = 310;
const int rhoLund = 213;
const int pi0Lund = 111;
const int KLund = 321;
const int piLund = 211;
const int eLund = 11;
const int muLund = 13;
const int tauLund = 15;
const int gammaLund = 22;
const int protonLund = 2212;
const int neutronLund = 2112;

//! B meson flavors.
enum BFlavor {
  kB0 = 1,                 /*!< \f$ B^0 \f$ */
  kBc = 2,                 /*!< \f$ B^\pm \f$ */
  kUndefinedBFlavor = -1,  /*!< Undefined */
};

//! Reconstructed tau decay modes.
enum TauMode {
  ktau_pi = 1,               /*!< \f$ \tau^+\rightarrow \pi^+ \f$ */
  ktau_rho = 2,              /*!< \f$ \tau^+\rightarrow \rho^+ \f$ */
  ktau_e = 3,               /*!< \f$ \tau^+\rightarrow \e^+ \f$ */
  ktau_mu = 4,               /*!< \f$ \tau^+\rightarrow \mu^+ \f$ */
  kUndefinedTauMode = -1,    /*!< Undefined */
};

//! Candidate types.
/*! Different candidate types have different sets of features that are
 * useful in the analysis. They are distinguished based on the type of
 * D meson (D or D*) that is present on the signal and tag side, and
 * also whether the tau decays into an alleged pi or rho meson. 
 * 
 * A notable use of this distinction is in best candidate selection.
 * Each candidate type has a unique trained learner to assign a score 
 * for any candidates assigned to that category. */
enum CandType {
  kDDpi = 0,                  /*!< \f$ B_{tag}\rightarrow D,\,B_{sig}\rightarrow D,\,\tau\rightarrow\pi \f$ */
  kDDstarpi = 1,              /*!< \f$ B_{tag}\rightarrow D,\,B_{sig}\rightarrow D^*,\,\tau\rightarrow\pi \f$ */
  kDstarDpi = 2,              /*!< \f$ B_{tag}\rightarrow D^*,\,B_{sig}\rightarrow D,\,\tau\rightarrow\pi \f$ */
  kDstarDstarpi = 3,          /*!< \f$ B_{tag}\rightarrow D^*,\,B_{sig}\rightarrow D^*,\,\tau\rightarrow\pi \f$ */
  kDDrho = 4,                 /*!< \f$ B_{tag}\rightarrow D,\,B_{sig}\rightarrow D,\,\tau\rightarrow\rho \f$ */
  kDDstarrho = 5,             /*!< \f$ B_{tag}\rightarrow D,\,B_{sig}\rightarrow D^*,\,\tau\rightarrow\rho \f$ */
  kDstarDrho = 6,             /*!< \f$ B_{tag}\rightarrow D^*,\,B_{sig}\rightarrow D,\,\tau\rightarrow\rho \f$ */
  kDstarDstarrho = 7,         /*!< \f$ B_{tag}\rightarrow D^*,\,B_{sig}\rightarrow D^*,\,\tau\rightarrow\rho \f$ */
  kUndefinedCandType = -1,    /*!< Undefined */
};

//! Sample types. 
/*! This is an attribute attached to \f$\Upsilon(4S)\f$ candidates. It
 * is the sample type that the event would be assigned to if this
 * candidate were to be chosen as the best candidate to represent it. */
enum SampleType {
  kBcD = 0,                     /*!< \f$ B^u \rightarrow D \f$ */
  kBcDstar = 1,                 /*!< \f$ B^u \rightarrow D^* \f$ */
  kB0D = 2,                     /*!< \f$ B^d \rightarrow D \f$ */
  kB0Dstar = 3,                 /*!< \f$ B^d \rightarrow D^* \f$ */
  kUndefinedSampleType = -1,    /*!< Undefined */
};

//! Truth \f$\tau\f$ MC Types. See Details. 
/*! Truth \f$\tau\f$ MC Types for truth \f$B\f$'s decaying as 
 * \f$B\rightarrow D^{(*)}\tau\nu_\tau\f$. Any other \f$B\f$ decay types
 * will have this value undefined. */
enum TauMcType {

  //! Truth \f$\tau\f$ decays as \f$\tau\rightarrow e+\nu_e+X\f$.
  ktau_e_mc = 0, 

  //! Truth \f$\tau\f$ decays as \f$\tau\rightarrow \mu+\nu_\mu+X\f$.
  ktau_mu_mc = 1, 

  //! Truth \f$\tau\f$ decays as \f$\tau\rightarrow K+X\f$.
  ktau_k_mc = 2, 

  //! Truth \f$\tau\f$ decays as \f$\tau\rightarrow X\f$.
  /*! \f$X\f$ is any sequence of particles not involving \f$e, \mu, K\f$. */
  ktau_h_mc = 3, 

  //! Undefined \f$\tau\f$ MC type.
  kUndefinedTauMcType = -1, 
};


}

#endif
