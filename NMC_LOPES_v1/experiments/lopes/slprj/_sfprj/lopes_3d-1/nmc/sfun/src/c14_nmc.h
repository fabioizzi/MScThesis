#ifndef __c14_nmc_h__
#define __c14_nmc_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc14_nmcInstanceStruct
#define typedef_SFc14_nmcInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c14_dataWrittenToVector[4];
  uint8_T c14_doSetSimStateSideEffects;
  const mxArray *c14_setSimStateSideEffectsInfo;
  int32_T *c14_sfEvent;
  boolean_T *c14_isStable;
  uint8_T *c14_is_active_c14_nmc;
  uint8_T *c14_is_c14_nmc;
  real_T *c14_time_sig;
  real_T *c14_start_time;
  real_T *c14_InSig;
  real_T *c14_count;
  real_T *c14_mean_freq;
  real_T *c14_N;
  real_T *c14_freq;
} SFc14_nmcInstanceStruct;

#endif                                 /*typedef_SFc14_nmcInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c14_nmc_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c14_nmc_get_check_sum(mxArray *plhs[]);
extern void c14_nmc_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
