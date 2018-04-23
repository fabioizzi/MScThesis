#ifndef __c13_nmc_h__
#define __c13_nmc_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc13_nmcInstanceStruct
#define typedef_SFc13_nmcInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c13_dataWrittenToVector[4];
  uint8_T c13_doSetSimStateSideEffects;
  const mxArray *c13_setSimStateSideEffectsInfo;
  int32_T *c13_sfEvent;
  boolean_T *c13_isStable;
  uint8_T *c13_is_active_c13_nmc;
  uint8_T *c13_is_c13_nmc;
  real_T *c13_time_sig;
  real_T *c13_start_time;
  real_T *c13_InSig;
  real_T *c13_count;
  real_T *c13_mean_freq;
  real_T *c13_N;
  real_T *c13_freq;
} SFc13_nmcInstanceStruct;

#endif                                 /*typedef_SFc13_nmcInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c13_nmc_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c13_nmc_get_check_sum(mxArray *plhs[]);
extern void c13_nmc_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
