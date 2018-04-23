#ifndef __c5_nmc_h__
#define __c5_nmc_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc5_nmcInstanceStruct
#define typedef_SFc5_nmcInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c5_dataWrittenToVector[4];
  uint8_T c5_doSetSimStateSideEffects;
  const mxArray *c5_setSimStateSideEffectsInfo;
  int32_T *c5_sfEvent;
  boolean_T *c5_isStable;
  uint8_T *c5_is_active_c5_nmc;
  uint8_T *c5_is_c5_nmc;
  real_T *c5_time_sig;
  real_T *c5_start_time;
  real_T *c5_InSig;
  real_T *c5_count;
  real_T *c5_mean_freq;
  real_T *c5_N;
  real_T *c5_freq;
} SFc5_nmcInstanceStruct;

#endif                                 /*typedef_SFc5_nmcInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_nmc_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_nmc_get_check_sum(mxArray *plhs[]);
extern void c5_nmc_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
