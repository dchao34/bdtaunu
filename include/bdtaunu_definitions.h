#ifndef __BDTAUNUDEFINITIONS_H__
#define __BDTAUNUDEFINITIONS_H__

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

//! Reconstructed D decay modes.
enum DMode {
  kDc_Kpipi = 1,          /*!< \f$ D^+\rightarrow K^-\pi^+\pi^- \f$ */
  kDc_Kpipipi0 = 2,       /*!< \f$ D^+\rightarrow K^-\pi^+\pi^-\pi^0 \f$ */
  kDc_KsK = 3,            /*!< \f$ D^+\rightarrow K_s K^+ \f$ */
  kDc_Kspi = 4,           /*!< \f$ D^+\rightarrow K_s\pi^+ \f$ */
  kDc_Kspipi0 = 5,        /*!< \f$ D^+\rightarrow K_s\pi^+\pi^0 \f$ */
  kDc_Kspipipi = 6,       /*!< \f$ D^+\rightarrow K_s\pi^+\pi^-\pi^+ \f$ */
  kDc_KKpi = 7,           /*!< \f$ D^+\rightarrow K^+K^-\pi^+ \f$ */
  kD0_Kpi = 8,            /*!< \f$ D^0\rightarrow K^-\pi^+ \f$ */
  kD0_Kpipi0 = 9,         /*!< \f$ D^0\rightarrow K^-\pi^+\pi^0 \f$ */
  kD0_Kpipipi = 10,       /*!< \f$ D^0\rightarrow K^-\pi^+\pi^+\pi^- \f$ */
  kD0_Kpipipipi0 = 11,    /*!< \f$ D^0\rightarrow K^-\pi^+\pi^+\pi^-\pi^0 \f$ */
  kD0_Kspipi = 12,        /*!< \f$ D^0\rightarrow K_s\pi^+\pi^- \f$ */
  kD0_Kspipipi0 = 13,     /*!< \f$ D^0\rightarrow K_s\pi^+\pi^-\pi^0 \f$ */
  kD0_Kspi0 = 14,         /*!< \f$ D^0\rightarrow K_s\pi^0 \f$ */
  kD0_KK = 15,            /*!< \f$ D^0\rightarrow K^+K^- \f$ */
  kUndefinedDMode = -1,   /*!< Undefined */
};

//! Reconstructed D* decay modes.
enum DstarMode {
  kNoDstar = 0,                  /*!< No \f$ D^* \f$ in \f$ B \f$ decay */
  kDstar0_D0pi0 = 1,             /*!< \f$ D^{*0}\rightarrow D^0\pi^0 \f$ */
  kDstar0_D0gamma = 2,           /*!< \f$ D^{*0}\rightarrow D^0\gamma \f$ */
  kDstarc_D0pi = 3,              /*!< \f$ D^{*+}\rightarrow D^0\pi^+ \f$ */
  kDstarc_Dcpi0 = 4,             /*!< \f$ D^{*+}\rightarrow D^+\pi^0 \f$ */
  kDstarc_Dcgamma = 5,           /*!< \f$ D^{*+}\rightarrow D^+\gamma \f$ */
  kUndefinedDstarMode = -1,      /*!< Undefined */
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

//! Truth B MC Types.
/*! This labels truth \f$B\f$ mesons into various decay categories
 * that will be helpful in characterizing whether the event is signal
 * or background. 
 *
 * The label is done by examining the \f$B\f$ meson's decay daughters. 
 *
 * \f$B\f$ \f$\gamma\f$ daughters are currently ignored in determining 
 * the MC type. However, the energy of the photon with the highest energy 
 * is saved; one can use this to determine whether the event has radiative 
 * photons involved. Therefore, the following descriptions omit the 
 * \f$+n\gamma\f$, \f$n\geq0\f$, though this is needed to be technically 
 * correct. */
enum BMcType {

  //! No truth \f$B\f$ mesons.
  kCont = 0,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D\tau\nu_\tau\f$.
  kDtau = 1,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{*}\tau\nu_\tau\f$.
  kDstartau = 2,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D\ell\nu_\ell\f$
  /*! \f$\ell=e,\,\mu\f$. */
  kDl = 3,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{*}\ell\nu_\ell\f$
  /*! \f$\ell=e,\,\mu\f$. */
  kDstarl = 4,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{**}\ell\nu_\ell X\f$
  /*! \f$X\f$ is any sequence of particles. */
  kDstarstar_res = 5,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{(*)}n\pi^{\pm,0}\ell\nu_\ell X\f$
  /*! \f$X\f$ is any sequence of particles. */
  kDstarstar_nonres = 6,

  //! Truth \f$B\f$ decays as \f$B\rightarrow X\ell\nu_\ell\f$
  /*! \f$X\f$ is any sequence of particles not involving a charm meson. */
  kCharmless_SL = 7,

  //! Truth \f$B\f$ decays hadronically. Daughters contain no charm mesons. 
  k0Charm_Had = 8,

  //! Truth \f$B\f$ decays hadronically. Daughters contain 1 charm meson. 
  k1Charm_Had = 9,

  //! Truth \f$B\f$ decays hadronically. Daughters contain 2 charm mesons. 
  k2Charm_Had = 10,

  //! Undefined B MC type. Indicates error. 
  kUndefinedBMcType = -1,
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


//! MC Event Types, Definition A. This will soon be obsolete. 
/*! This labels Monte Carlo events into various signal and background
 * truth categories. 
 * 
 * The categorization is based on the #BMcType of the two truth
 * \f$B\f$ mesons. */
enum McEventTypeA {

  //! \f$B\rightarrow D\tau\nu_\tau\f$ signal event.
  /*! An event is in this category if there exists at least one truth \f$B\f$
   * which decays in the mode \f$B\rightarrow D\tau\nu_\tau\f$. 
   * If one truth \f$B\f$ is \f$B\rightarrow D\tau\nu_\tau\f$ and the other 
   * is \f$B\rightarrow D\tau\nu_\tau\f$, then it is assigned with probability
   * 0.5 to either #kDtau_SigA or #kDstartau_SigA. */
  kDtau_SigA = 0,

  //! \f$B\rightarrow D^*\tau\nu_\tau\f$ signal event.
  /*! An event is in this category there exists at least one truth \f$B\f$
   * which decays in the mode \f$B\rightarrow D^*\tau\nu_\tau\f$.
   * If one truth \f$B\f$ is \f$B\rightarrow D\tau\nu_\tau\f$ and the other 
   * is \f$B\rightarrow D\tau\nu_\tau\f$, then it is assigned with probability
   * 0.5 to either #kDtau_SigA or #kDstartau_SigA. */
  kDstartau_SigA = 1,

  //! \f$B\rightarrow D\ell\nu_\ell\f$ normalization event.
  /*! An event is in this category if there exists at least one truth \f$B\f$
   * which decays in the mode \f$B\rightarrow D\ell\nu_\ell\f$,
   * and the event is neither #kDtau_SigA, #kDstartau_SigA, or #kDstarstar_BkgA.
   *
   * If one truth \f$B\f$ is \f$B\rightarrow D\ell\nu_\ell\f$ and the other 
   * is \f$B\rightarrow D\ell\nu_\ell\f$, then it is assigned with probability
   * 0.5 to either #kDl_NormA or #kDstarl_NormA. */
  kDl_NormA = 2,

  //! \f$B\rightarrow D^*\ell\nu_\ell\f$ normalization event.
  /*! An event is in this category there exists at least one truth \f$B\f$
   * which decays in the mode \f$B\rightarrow D^*\ell\nu_\ell\f$,
   * and the event is neither #kDtau_SigA, #kDstartau_SigA, or #kDstarstar_BkgA.
   *
   * If one truth \f$B\f$ is \f$B\rightarrow D\ell\nu_\ell\f$ and the other 
   * is \f$B\rightarrow D\ell\nu_\ell\f$, then it is assigned with probability
   * 0.5 to either #kDl_NormA or #kDstarl_NormA. */
  kDstarl_NormA = 3,

  //! \f$D^{**}\f$ background event. 
  /*! The event has at least one truth \f$B\f$ with #BMcType #kDstarstar_SL,
   *  and the event is neither #kDtau_Sig or #kDstartau_Sig. */
  kDstarstar_BkgA = 4,

  //! Semileptonic background. 
  /*! Event when one truth \f$B\f$ mesons is either #k0Charm_Had,
   * #k1Charm_Had, or #k2Charm_Had, and the other is either #kD_SL,
   * #kDstarstar_SL, or #k0Charm_SL. */
  kSL_BkgA = 5,

  //! Hadronic background. 
  /*! Event when both truth \f$B\f$ mesons are either #k0Charm_Had,
   * #k1Charm_Had, or #k2Charm_Had. */
  kHad_BkgA = 6,

  //! Continuum background. 
  kCont_BkgA = 7,

  //! Undefined MC event type. Indicates error. 
  kUndefinedMcEventTypeA = -1,
};

}

#endif
