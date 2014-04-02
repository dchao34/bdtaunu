enum BFlav {
  kB0 = 1,
  kBc = 2,
  kUndefinedBFlav = -1,
};

enum DMode {
  kDc_Kpipi = 1,
  kDc_Kpipipi0 = 2,
  kDc_KsK = 3,
  kDc_Kspi = 4,
  kDc_Kspipi0 = 5,
  kDc_Kspipipi = 6,
  kDc_KKpi = 7,
  kD0_Kpi = 8,
  kD0_Kpipi0 = 9,
  kD0_Kpipipi = 10,
  kD0_Kpipipipi0 = 11,
  kD0_Kspipi = 12,
  kD0_Kspipipi0 = 13,
  kD0_Kspi0 = 14,
  kD0_KK = 15,
  kUndefinedDMode = -1,
};

enum DstarMode {
  kNoDstar = 0,
  kDstar0_D0pi0 = 1,
  kDstar0_D0gamma = 2,
  kDstarc_D0pi = 3,
  kDstarc_Dcpi0 = 4,
  kDstarc_Dcgamma = 5,
  kUndefinedDstarMode = -1,
};

enum TauMode {
  ktau_pi = 1,
  ktau_rho = 2,
  kUndefinedTauMode = -1,
};

enum CandType {
  kDDpi = 0,
  kDDstarpi = 1,
  kDstarDpi = 2,
  kDstarDstarpi = 3,
  kDDrho = 4,
  kDDstarrho = 5,
  kDstarDrho = 6,
  kDstarDstarrho = 7,
  kUndefinedCandType = -1,
};

enum SampleType {
  kBcD = 0,
  kBcDstar = 1,
  kB0D = 2,
  kB0Dstar = 3,
  kUndefinedSampleType = -1,
};
