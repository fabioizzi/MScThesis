#ifndef __c3_LOPES_3D_h__
#define __c3_LOPES_3D_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_LOPES_3DInstanceStruct
#define typedef_SFc3_LOPES_3DInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c3_dataWrittenToVector[2];
  uint8_T c3_doSetSimStateSideEffects;
  const mxArray *c3_setSimStateSideEffectsInfo;
  int32_T *c3_sfEvent;
  boolean_T *c3_isStable;
  uint8_T *c3_is_active_c3_LOPES_3D;
  uint8_T *c3_is_c3_LOPES_3D;
  uint8_T *c3_is_ActiveState;
  real_T *c3_InputState;
  real_T *c3_PhasePerc;
  real_T *c3_MeasPhase;
  real_T *c3_StartLeg;
  real_T *c3_State;
  real_T *c3_DesState;
} SFc3_LOPES_3DInstanceStruct;

#endif                                 /*typedef_SFc3_LOPES_3DInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_LOPES_3D_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_LOPES_3D_get_check_sum(mxArray *plhs[]);
extern void c3_LOPES_3D_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
