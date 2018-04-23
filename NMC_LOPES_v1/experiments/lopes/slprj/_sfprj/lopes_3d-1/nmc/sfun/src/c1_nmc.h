#ifndef __c1_nmc_h__
#define __c1_nmc_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_nmcInstanceStruct
#define typedef_SFc1_nmcInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c1_dataWrittenToVector[4];
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
  int32_T *c1_sfEvent;
  boolean_T *c1_isStable;
  uint8_T *c1_is_active_c1_nmc;
  uint8_T *c1_is_c1_nmc;
  real_T *c1_time_sig;
  real_T *c1_start_time;
  real_T *c1_InSig;
  real_T *c1_count;
  real_T *c1_mean_freq;
  real_T *c1_N;
  real_T *c1_freq;
} SFc1_nmcInstanceStruct;

#endif                                 /*typedef_SFc1_nmcInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_nmc_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_nmc_get_check_sum(mxArray *plhs[]);
extern void c1_nmc_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
