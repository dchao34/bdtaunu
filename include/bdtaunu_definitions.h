#ifndef __BDTAUNUDEFINITIONS_H__
#define __BDTAUNUDEFINITIONS_H__

/*! \file bdtaunu_definitions.h
 *  \brief Constants defined for this analysis.
 *
 *  This file contains any constants and enumerations that are used
 *  throughout the analysis package.
 */

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
 * Note that we are currently ignoring \f$\gamma\f$ daughters that
 * have energy below 20 MeV. */
enum BMcType {

  //! Dummy label for when there are no truth \f$B\f$ mesons.
  kNoB = 0,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{(*)}\tau\nu_\tau\f$.
  kDtau = 1,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{(*)}\ell\nu_\ell\f$
  /*! \f$\ell=e,\,\mu\f$. */
  kDl = 2,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{(*)}\ell\nu_\ell X\f$
  /*! \f$X\f$ is any sequence of particles. */
  kD_SL = 3,

  //! Truth \f$B\f$ decays as \f$B\rightarrow D^{**}\ell\nu_\ell X\f$
  /*! \f$X\f$ is any sequence of particles. */
  kDstarstar_SL = 4,

  //! Truth \f$B\f$ decays as \f$B\rightarrow X\ell\nu_\ell\f$
  /*! \f$X\f$ is any sequence of particles not involving a charm meson. */
  k0Charm_SL = 5,

  //! Truth \f$B\f$ decays hadronically. Daughters contain no charm mesons. 
  k0Charm_Had = 6,

  //! Truth \f$B\f$ decays hadronically. Daughters contain 1 charm meson. 
  k1Charm_Had = 7,

  //! Truth \f$B\f$ decays hadronically. Daughters contain 2 charm mesons. 
  k2Charm_Had = 8,

  //! Undefined B MC type. Indicates error. 
  kUndefinedBMcType = -1,
};

//! MC Event Types. 
/*! This labels Monte Carlo events into various signal and background
 * truth categories. 
 * 
 * The categorization is based on the #BMcType of the two truth
 * \f$B\f$ mesons. */
enum McEventType {

  //! Signal event. 
  /*! An event is a signal if there exists at least one truth \f$B\f$
   * which decays in the mode \f$B\rightarrow D^{(*)}\tau\nu_\tau\f$.
   * This is the case when both #BMcType are #kDtau. */
  kSignal = 0,

  //! Normalization event. 
  /*! An event is normalization if there exists at least one truth \f$B\f$
   * which decays in the mode \f$B\rightarrow D^{(*)}\ell\nu_\ell\f$,
   * where \f$\ell=e,\,\mu\f$, and the other truth \f$B\f$ is not
   * #kDtau.
   *
   * This is the case when at least one #BMcType is #kDl and the other
   * is not #kDtau. */
  kNormalization = 1,

  //! Semileptonic-Semileptonic background. 
  /*! Event when both truth \f$B\f$ mesons are either #kD_SL,
   * #kDstarstar_SL, or #k0Charm_SL. */
  kSLSL_Bkg = 2,

  //! Semileptonic-Hadron background. 
  /*! Event when one truth \f$B\f$ mesons is either #k0Charm_Had,
   * #k1Charm_Had, or #k2Charm_Had, and the other is either #kD_SL,
   * #kDstarstar_SL, or #k0Charm_SL. */
  kSLHad_Bkg = 3,

  //! Hadron-Hadron background. 
  /*! Event when both truth \f$B\f$ mesons are either #k0Charm_Had,
   * #k1Charm_Had, or #k2Charm_Had. */
  kHadHad_Bkg = 4,

  //! Continuum event. 
  kContinuum_Bkg = 5,

  //! Undefined MC event type. Indicates error. 
  kUndefinedMcEventType = -1,
};

#endif
