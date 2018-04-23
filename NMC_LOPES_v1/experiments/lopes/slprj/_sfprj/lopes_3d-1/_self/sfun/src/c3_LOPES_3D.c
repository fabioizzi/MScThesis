/* Include files */

#include <stddef.h>
#include "blas.h"
#include "LOPES_3D_sfun.h"
#include "c3_LOPES_3D.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "LOPES_3D_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c3_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c3_IN_ActiveState              ((uint8_T)1U)
#define c3_IN_Start                    ((uint8_T)2U)
#define c3_IN_Init                     ((uint8_T)1U)
#define c3_IN_LonR                     ((uint8_T)2U)
#define c3_IN_RonL                     ((uint8_T)3U)
#define c3_IN_StartLeft                ((uint8_T)4U)
#define c3_IN_StartRight               ((uint8_T)5U)
#define c3_IN_StoppedLeft              ((uint8_T)6U)
#define c3_IN_StoppedRight             ((uint8_T)7U)
#define c3_IN_StoppingLeft             ((uint8_T)8U)
#define c3_IN_StoppingRight            ((uint8_T)9U)
#define c3_IN_SwingLeft                ((uint8_T)10U)
#define c3_IN_SwingRight               ((uint8_T)11U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_e_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_g_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_h_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_i_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_j_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_k_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_l_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_m_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_n_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_o_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_p_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_q_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_r_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_s_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_t_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_u_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_v_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_w_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_x_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_y_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_ab_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_bb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c3_cb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void c3_durationReferenceTimeUpdater(SFc3_LOPES_3DInstanceStruct
  *chartInstance);
static void initialize_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void initialize_params_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct
  *chartInstance);
static void enable_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void disable_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct
  *chartInstance);
static void ext_mode_exec_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct
  *chartInstance);
static void set_sim_state_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void c3_set_sim_state_side_effects_c3_LOPES_3D
  (SFc3_LOPES_3DInstanceStruct *chartInstance);
static void finalize_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void sf_gateway_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void mdl_start_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void initSimStructsc3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_ActiveState(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_exit_internal_ActiveState(SFc3_LOPES_3DInstanceStruct
  *chartInstance);
static void c3_StartLeft(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_StoppingRight(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_StoppedRight(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_SwingRight(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_SwingLeft(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_StartRight(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_StoppingLeft(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_StoppedLeft(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void c3_enter_atomic_Start(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static real_T c3_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_nargout, const char_T *c3_identifier);
static real_T c3_b_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static boolean_T c3_c_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_d_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint8_T c3_e_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_b_is_ActiveState, const char_T *c3_identifier);
static uint8_T c3_f_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_g_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_b_dataWrittenToVector, const char_T *c3_identifier,
  boolean_T c3_y[2]);
static void c3_h_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y[2]);
static const mxArray *c3_i_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct
  *chartInstance, const mxArray *c3_b_setSimStateSideEffectsInfo, const char_T
  *c3_identifier);
static const mxArray *c3_j_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc3_LOPES_3DInstanceStruct
  *chartInstance, int32_T c3_ssid);
static void c3_init_sf_message_store_memory(SFc3_LOPES_3DInstanceStruct
  *chartInstance);
static void init_dsm_address_info(SFc3_LOPES_3DInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc3_LOPES_3DInstanceStruct *chartInstance);

/* Function Definitions */
static void c3_durationReferenceTimeUpdater(SFc3_LOPES_3DInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initialize_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc3_LOPES_3D(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  *chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_doSetSimStateSideEffects = 0U;
  chartInstance->c3_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
  *chartInstance->c3_is_active_c3_LOPES_3D = 0U;
  *chartInstance->c3_is_c3_LOPES_3D = c3_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct
  *chartInstance)
{
  uint32_T c3_prevAniVal;
  c3_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c3_is_active_c3_LOPES_3D == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_c3_LOPES_3D == c3_IN_ActiveState) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_StartLeft) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_LonR) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_StoppingRight) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_StoppedRight) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_Init) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_SwingRight) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_SwingLeft) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_StartRight) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_RonL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_StoppingLeft) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_ActiveState == c3_IN_StoppedLeft) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_c3_LOPES_3D == c3_IN_Start) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
  }

  _SFD_SET_ANIMATION(c3_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  c3_update_debugger_state_c3_LOPES_3D(chartInstance);
}

static const mxArray *get_sim_state_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  const mxArray *c3_b_y = NULL;
  real_T c3_b_hoistedGlobal;
  real_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  uint8_T c3_c_hoistedGlobal;
  uint8_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  uint8_T c3_d_hoistedGlobal;
  uint8_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  uint8_T c3_e_hoistedGlobal;
  uint8_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  const mxArray *c3_g_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(6, 1), false);
  c3_hoistedGlobal = *chartInstance->c3_State;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_hoistedGlobal = *chartInstance->c3_DesState;
  c3_b_u = c3_b_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_c_hoistedGlobal = *chartInstance->c3_is_active_c3_LOPES_3D;
  c3_c_u = c3_c_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_d_hoistedGlobal = *chartInstance->c3_is_c3_LOPES_3D;
  c3_d_u = c3_d_hoistedGlobal;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_e_hoistedGlobal = *chartInstance->c3_is_ActiveState;
  c3_e_u = c3_e_hoistedGlobal;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 4, c3_f_y);
  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y",
    chartInstance->c3_dataWrittenToVector, 11, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c3_y, 5, c3_g_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_u;
  boolean_T c3_bv0[2];
  int32_T c3_i0;
  c3_u = sf_mex_dup(c3_st);
  *chartInstance->c3_State = c3_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("State", c3_u, 0)), "State");
  *chartInstance->c3_DesState = c3_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("DesState", c3_u, 1)), "DesState");
  *chartInstance->c3_is_active_c3_LOPES_3D = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c3_LOPES_3D", c3_u, 2)),
    "is_active_c3_LOPES_3D");
  *chartInstance->c3_is_c3_LOPES_3D = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_c3_LOPES_3D", c3_u, 3)), "is_c3_LOPES_3D");
  *chartInstance->c3_is_ActiveState = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_ActiveState", c3_u, 4)), "is_ActiveState");
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "dataWrittenToVector", c3_u, 5)), "dataWrittenToVector", c3_bv0);
  for (c3_i0 = 0; c3_i0 < 2; c3_i0++) {
    chartInstance->c3_dataWrittenToVector[c3_i0] = c3_bv0[c3_i0];
  }

  sf_mex_assign(&chartInstance->c3_setSimStateSideEffectsInfo,
                c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c3_u, 6)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c3_u);
  chartInstance->c3_doSetSimStateSideEffects = 1U;
  c3_update_debugger_state_c3_LOPES_3D(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void c3_set_sim_state_side_effects_c3_LOPES_3D
  (SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  if (chartInstance->c3_doSetSimStateSideEffects != 0) {
    chartInstance->c3_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c3_setSimStateSideEffectsInfo);
}

static void sf_gateway_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  c3_set_sim_state_side_effects_c3_LOPES_3D(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  c3_durationReferenceTimeUpdater(chartInstance);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_StartLeg, 4U, 1U, 0U,
                        *chartInstance->c3_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_MeasPhase, 3U, 1U, 0U,
                        *chartInstance->c3_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_PhasePerc, 2U, 1U, 0U,
                        *chartInstance->c3_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_InputState, 1U, 1U, 0U,
                        *chartInstance->c3_sfEvent, false);
  *chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
  if (*chartInstance->c3_is_active_c3_LOPES_3D == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_active_c3_LOPES_3D = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_c3_LOPES_3D = c3_IN_Start;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
    c3_enter_atomic_Start(chartInstance);
  } else {
    switch (*chartInstance->c3_is_c3_LOPES_3D) {
     case c3_IN_ActiveState:
      CV_CHART_EVAL(0, 0, 1);
      c3_ActiveState(chartInstance);
      break;

     case c3_IN_Start:
      CV_CHART_EVAL(0, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                   *chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_ab_debug_family_names,
        c3_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      c3_out = CV_EML_IF(0, 0, 0, CV_RELATIONAL_EVAL(5U, 0U, 0,
        *chartInstance->c3_InputState, 2.0, -1, 0U,
        *chartInstance->c3_InputState == 2.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c3_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
        *chartInstance->c3_is_c3_LOPES_3D = c3_IN_ActiveState;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, *chartInstance->c3_sfEvent);
        *chartInstance->c3_is_ActiveState = c3_IN_Init;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                     *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_l_debug_family_names,
          c3_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        if (CV_EML_IF(12, 1, 2, *chartInstance->c3_StartLeg == 1.0)) {
          *chartInstance->c3_State = 501.0;
          chartInstance->c3_dataWrittenToVector[0U] = true;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 12U,
                                *chartInstance->c3_sfEvent, false);
        } else {
          if (CV_EML_IF(12, 1, 3, *chartInstance->c3_StartLeg == 2.0)) {
            *chartInstance->c3_State = 502.0;
            chartInstance->c3_dataWrittenToVector[0U] = true;
            _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 12U,
                                  *chartInstance->c3_sfEvent, false);
          }
        }

        _SFD_SYMBOL_SCOPE_POP();
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, *chartInstance->c3_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c3_is_c3_LOPES_3D = c3_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_LOPES_3DMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  c3_init_sf_message_store_memory(chartInstance);
}

static void initSimStructsc3_LOPES_3D(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_ActiveState(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 1.0;
  boolean_T c3_b_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_c_nargin = 0.0;
  real_T c3_c_nargout = 0.0;
  real_T c3_d_nargin = 0.0;
  real_T c3_d_nargout = 1.0;
  boolean_T c3_c_out;
  real_T c3_e_nargin = 0.0;
  real_T c3_e_nargout = 0.0;
  real_T c3_f_nargin = 0.0;
  real_T c3_f_nargout = 1.0;
  boolean_T c3_d_out;
  real_T c3_g_nargin = 0.0;
  real_T c3_g_nargout = 0.0;
  real_T c3_h_nargin = 0.0;
  real_T c3_h_nargout = 1.0;
  boolean_T c3_e_out;
  real_T c3_i_nargin = 0.0;
  real_T c3_i_nargout = 0.0;
  real_T c3_j_nargin = 0.0;
  real_T c3_j_nargout = 1.0;
  boolean_T c3_f_out;
  real_T c3_k_nargin = 0.0;
  real_T c3_k_nargout = 0.0;
  real_T c3_l_nargin = 0.0;
  real_T c3_l_nargout = 1.0;
  boolean_T c3_g_out;
  real_T c3_m_nargin = 0.0;
  real_T c3_m_nargout = 0.0;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_bb_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  c3_out = CV_EML_IF(17, 0, 0, CV_RELATIONAL_EVAL(5U, 17U, 0,
    *chartInstance->c3_InputState, 1.0, -1, 0U, *chartInstance->c3_InputState ==
    1.0));
  _SFD_SYMBOL_SCOPE_POP();
  guard1 = false;
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, *chartInstance->c3_sfEvent);
    c3_exit_internal_ActiveState(chartInstance);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_c3_LOPES_3D = c3_IN_Start;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
    c3_enter_atomic_Start(chartInstance);
    guard1 = true;
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
    switch (*chartInstance->c3_is_ActiveState) {
     case c3_IN_Init:
      CV_STATE_EVAL(0, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   *chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_s_debug_family_names,
        c3_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      c3_b_out = CV_EML_IF(2, 0, 0, CV_RELATIONAL_EVAL(5U, 2U, 0,
        *chartInstance->c3_StartLeg, 2.0, -1, 0U, *chartInstance->c3_StartLeg ==
        2.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c3_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
        *chartInstance->c3_is_ActiveState = c3_IN_StartRight;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_g_debug_family_names,
          c3_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        *chartInstance->c3_State = 202.0;
        chartInstance->c3_dataWrittenToVector[0U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 5U,
                              *chartInstance->c3_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                     *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_q_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_out, 2U, c3_b_sf_marshallOut,
          c3_b_sf_marshallIn);
        c3_c_out = CV_EML_IF(15, 0, 0, CV_RELATIONAL_EVAL(5U, 15U, 0,
          *chartInstance->c3_StartLeg, 1.0, -1, 0U, *chartInstance->c3_StartLeg ==
          1.0));
        _SFD_SYMBOL_SCOPE_POP();
        if (c3_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, *chartInstance->c3_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
          *chartInstance->c3_is_ActiveState = c3_IN_StartLeft;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *chartInstance->c3_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_debug_family_names,
            c3_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_e_nargin, 0U,
            c3_sf_marshallOut, c3_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_e_nargout, 1U,
            c3_sf_marshallOut, c3_sf_marshallIn);
          *chartInstance->c3_State = 201.0;
          chartInstance->c3_dataWrittenToVector[0U] = true;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 4U,
                                *chartInstance->c3_sfEvent, false);
          _SFD_SYMBOL_SCOPE_POP();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                       *chartInstance->c3_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c3_sfEvent);
      guard1 = true;
      break;

     case c3_IN_LonR:
      CV_STATE_EVAL(0, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                   *chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_r_debug_family_names,
        c3_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_f_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_f_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_d_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      guard3 = false;
      if (CV_EML_COND(7, 0, 0, CV_RELATIONAL_EVAL(5U, 7U, 0,
            *chartInstance->c3_MeasPhase, 2.0, -1, 0U,
            *chartInstance->c3_MeasPhase == 2.0))) {
        if (CV_EML_COND(7, 0, 1, CV_RELATIONAL_EVAL(5U, 7U, 1,
              *chartInstance->c3_DesState, 2.0, -1, 0U,
              *chartInstance->c3_DesState == 2.0))) {
          CV_EML_MCDC(7, 0, 0, true);
          CV_EML_IF(7, 0, 0, true);
          c3_d_out = true;
        } else {
          guard3 = true;
        }
      } else {
        if (!chartInstance->c3_dataWrittenToVector[1U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 5U, 7U,
            *chartInstance->c3_sfEvent, false);
        }

        guard3 = true;
      }

      if (guard3 == true) {
        CV_EML_MCDC(7, 0, 0, false);
        CV_EML_IF(7, 0, 0, false);
        c3_d_out = false;
      }

      _SFD_SYMBOL_SCOPE_POP();
      if (c3_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, *chartInstance->c3_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
        *chartInstance->c3_is_ActiveState = c3_IN_SwingRight;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_e_debug_family_names,
          c3_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_g_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_g_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        *chartInstance->c3_State = 102.0;
        chartInstance->c3_dataWrittenToVector[0U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 11U,
                              *chartInstance->c3_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                     *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_m_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_h_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_h_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_e_out, 2U, c3_b_sf_marshallOut,
          c3_b_sf_marshallIn);
        if (!chartInstance->c3_dataWrittenToVector[1U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 5U, 10U,
            *chartInstance->c3_sfEvent, false);
        }

        c3_e_out = CV_EML_IF(10, 0, 0, CV_RELATIONAL_EVAL(5U, 10U, 0,
          *chartInstance->c3_DesState, 3.0, -1, 0U, *chartInstance->c3_DesState ==
          3.0));
        _SFD_SYMBOL_SCOPE_POP();
        if (c3_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, *chartInstance->c3_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
          *chartInstance->c3_is_ActiveState = c3_IN_StoppingRight;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, *chartInstance->c3_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_c_debug_family_names,
            c3_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i_nargin, 0U,
            c3_sf_marshallOut, c3_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i_nargout, 1U,
            c3_sf_marshallOut, c3_sf_marshallIn);
          *chartInstance->c3_State = 301.0;
          chartInstance->c3_dataWrittenToVector[0U] = true;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 9U,
                                *chartInstance->c3_sfEvent, false);
          _SFD_SYMBOL_SCOPE_POP();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                       *chartInstance->c3_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
      guard1 = true;
      break;

     case c3_IN_RonL:
      CV_STATE_EVAL(0, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                   *chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_u_debug_family_names,
        c3_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_j_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_j_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_f_out, 2U, c3_b_sf_marshallOut,
        c3_b_sf_marshallIn);
      guard2 = false;
      if (CV_EML_COND(5, 0, 0, CV_RELATIONAL_EVAL(5U, 5U, 0,
            *chartInstance->c3_MeasPhase, 4.0, -1, 0U,
            *chartInstance->c3_MeasPhase == 4.0))) {
        if (CV_EML_COND(5, 0, 1, CV_RELATIONAL_EVAL(5U, 5U, 1,
              *chartInstance->c3_DesState, 2.0, -1, 0U,
              *chartInstance->c3_DesState == 2.0))) {
          CV_EML_MCDC(5, 0, 0, true);
          CV_EML_IF(5, 0, 0, true);
          c3_f_out = true;
        } else {
          guard2 = true;
        }
      } else {
        if (!chartInstance->c3_dataWrittenToVector[1U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 5U, 5U,
            *chartInstance->c3_sfEvent, false);
        }

        guard2 = true;
      }

      if (guard2 == true) {
        CV_EML_MCDC(5, 0, 0, false);
        CV_EML_IF(5, 0, 0, false);
        c3_f_out = false;
      }

      _SFD_SYMBOL_SCOPE_POP();
      if (c3_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, *chartInstance->c3_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
        *chartInstance->c3_is_ActiveState = c3_IN_SwingLeft;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_f_debug_family_names,
          c3_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_k_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_k_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        *chartInstance->c3_State = 104.0;
        chartInstance->c3_dataWrittenToVector[0U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 10U,
                              *chartInstance->c3_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                     *chartInstance->c3_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_x_debug_family_names,
          c3_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_l_nargin, 0U, c3_sf_marshallOut,
          c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_l_nargout, 1U,
          c3_sf_marshallOut, c3_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_g_out, 2U, c3_b_sf_marshallOut,
          c3_b_sf_marshallIn);
        if (!chartInstance->c3_dataWrittenToVector[1U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 5U, 9U,
            *chartInstance->c3_sfEvent, false);
        }

        c3_g_out = CV_EML_IF(9, 0, 0, CV_RELATIONAL_EVAL(5U, 9U, 0,
          *chartInstance->c3_DesState, 3.0, -1, 0U, *chartInstance->c3_DesState ==
          3.0));
        _SFD_SYMBOL_SCOPE_POP();
        if (c3_g_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, *chartInstance->c3_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
          *chartInstance->c3_is_ActiveState = c3_IN_StoppingLeft;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, *chartInstance->c3_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_i_debug_family_names,
            c3_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_m_nargin, 0U,
            c3_sf_marshallOut, c3_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_m_nargout, 1U,
            c3_sf_marshallOut, c3_sf_marshallIn);
          *chartInstance->c3_State = 302.0;
          chartInstance->c3_dataWrittenToVector[0U] = true;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 8U,
                                *chartInstance->c3_sfEvent, false);
          _SFD_SYMBOL_SCOPE_POP();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                       *chartInstance->c3_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, *chartInstance->c3_sfEvent);
      guard1 = true;
      break;

     case c3_IN_StartLeft:
      CV_STATE_EVAL(0, 0, 4);
      c3_StartLeft(chartInstance);
      guard1 = true;
      break;

     case c3_IN_StartRight:
      CV_STATE_EVAL(0, 0, 5);
      c3_StartRight(chartInstance);
      guard1 = true;
      break;

     case c3_IN_StoppedLeft:
      CV_STATE_EVAL(0, 0, 6);
      c3_StoppedLeft(chartInstance);
      if (*chartInstance->c3_is_c3_LOPES_3D != c3_IN_ActiveState) {
      } else {
        guard1 = true;
      }
      break;

     case c3_IN_StoppedRight:
      CV_STATE_EVAL(0, 0, 7);
      c3_StoppedRight(chartInstance);
      if (*chartInstance->c3_is_c3_LOPES_3D != c3_IN_ActiveState) {
      } else {
        guard1 = true;
      }
      break;

     case c3_IN_StoppingLeft:
      CV_STATE_EVAL(0, 0, 8);
      c3_StoppingLeft(chartInstance);
      guard1 = true;
      break;

     case c3_IN_StoppingRight:
      CV_STATE_EVAL(0, 0, 9);
      c3_StoppingRight(chartInstance);
      guard1 = true;
      break;

     case c3_IN_SwingLeft:
      CV_STATE_EVAL(0, 0, 10);
      c3_SwingLeft(chartInstance);
      guard1 = true;
      break;

     case c3_IN_SwingRight:
      CV_STATE_EVAL(0, 0, 11);
      c3_SwingRight(chartInstance);
      guard1 = true;
      break;

     default:
      CV_STATE_EVAL(0, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
      guard1 = true;
      break;
    }
  }

  if (guard1 == true) {
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
  }
}

static void c3_exit_internal_ActiveState(SFc3_LOPES_3DInstanceStruct
  *chartInstance)
{
  switch (*chartInstance->c3_is_ActiveState) {
   case c3_IN_Init:
    CV_STATE_EVAL(0, 1, 1);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_LonR:
    CV_STATE_EVAL(0, 1, 2);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_RonL:
    CV_STATE_EVAL(0, 1, 3);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_StartLeft:
    CV_STATE_EVAL(0, 1, 4);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_StartRight:
    CV_STATE_EVAL(0, 1, 5);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_StoppedLeft:
    CV_STATE_EVAL(0, 1, 6);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_StoppedRight:
    CV_STATE_EVAL(0, 1, 7);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_StoppingLeft:
    CV_STATE_EVAL(0, 1, 8);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_StoppingRight:
    CV_STATE_EVAL(0, 1, 9);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_SwingLeft:
    CV_STATE_EVAL(0, 1, 10);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, *chartInstance->c3_sfEvent);
    break;

   case c3_IN_SwingRight:
    CV_STATE_EVAL(0, 1, 11);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, *chartInstance->c3_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 1, 0);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
    break;
  }
}

static void c3_StartLeft(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_p_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  guard1 = false;
  if (CV_EML_COND(4, 0, 0, CV_RELATIONAL_EVAL(5U, 4U, 0,
        *chartInstance->c3_PhasePerc, 0.0, -1, 4U, *chartInstance->c3_PhasePerc >
        0.0))) {
    if (CV_EML_COND(4, 0, 1, CV_RELATIONAL_EVAL(5U, 4U, 1,
          *chartInstance->c3_PhasePerc, 2.0, -1, 2U,
          *chartInstance->c3_PhasePerc < 2.0))) {
      CV_EML_MCDC(4, 0, 0, true);
      CV_EML_IF(4, 0, 0, true);
      c3_out = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 == true) {
    CV_EML_MCDC(4, 0, 0, false);
    CV_EML_IF(4, 0, 0, false);
    c3_out = false;
  }

  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_LonR;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_b_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    *chartInstance->c3_State = 101.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 2U,
                          *chartInstance->c3_sfEvent, false);
    *chartInstance->c3_DesState = *chartInstance->c3_InputState;
    chartInstance->c3_dataWrittenToVector[1U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_DesState, 0U, 4U, 2U,
                          *chartInstance->c3_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U, *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *chartInstance->c3_sfEvent);
}

static void c3_StoppingRight(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_o_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  c3_out = CV_EML_IF(14, 0, 0, CV_RELATIONAL_EVAL(5U, 14U, 0,
    *chartInstance->c3_PhasePerc, 50.0, -1, 4U, *chartInstance->c3_PhasePerc >
    50.0));
  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_StoppedRight;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_d_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    *chartInstance->c3_State = 401.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 7U,
                          *chartInstance->c3_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U, *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, *chartInstance->c3_sfEvent);
}

static void c3_StoppedRight(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_y_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  c3_out = CV_EML_IF(12, 0, 0, CV_RELATIONAL_EVAL(5U, 12U, 0,
    *chartInstance->c3_InputState, 2.0, -1, 0U, *chartInstance->c3_InputState ==
    2.0));
  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_c3_LOPES_3D = c3_IN_Start;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
    c3_enter_atomic_Start(chartInstance);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U, *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, *chartInstance->c3_sfEvent);
}

static void c3_SwingRight(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_t_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  c3_out = CV_EML_IF(8, 0, 0, CV_RELATIONAL_EVAL(5U, 8U, 0,
    *chartInstance->c3_PhasePerc, 50.0, -1, 4U, *chartInstance->c3_PhasePerc >
    50.0));
  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_RonL;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_h_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    *chartInstance->c3_State = 103.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 3U,
                          *chartInstance->c3_sfEvent, false);
    *chartInstance->c3_DesState = *chartInstance->c3_InputState;
    chartInstance->c3_dataWrittenToVector[1U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_DesState, 0U, 4U, 3U,
                          *chartInstance->c3_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                 *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, *chartInstance->c3_sfEvent);
}

static void c3_SwingLeft(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_n_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  guard1 = false;
  if (CV_EML_COND(6, 0, 0, CV_RELATIONAL_EVAL(5U, 6U, 0,
        *chartInstance->c3_PhasePerc, 0.0, -1, 4U, *chartInstance->c3_PhasePerc >
        0.0))) {
    if (CV_EML_COND(6, 0, 1, CV_RELATIONAL_EVAL(5U, 6U, 1,
          *chartInstance->c3_PhasePerc, 2.0, -1, 2U,
          *chartInstance->c3_PhasePerc < 2.0))) {
      CV_EML_MCDC(6, 0, 0, true);
      CV_EML_IF(6, 0, 0, true);
      c3_out = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 == true) {
    CV_EML_MCDC(6, 0, 0, false);
    CV_EML_IF(6, 0, 0, false);
    c3_out = false;
  }

  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_LonR;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_b_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    *chartInstance->c3_State = 101.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 2U,
                          *chartInstance->c3_sfEvent, false);
    *chartInstance->c3_DesState = *chartInstance->c3_InputState;
    chartInstance->c3_dataWrittenToVector[1U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_DesState, 0U, 4U, 2U,
                          *chartInstance->c3_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                 *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, *chartInstance->c3_sfEvent);
}

static void c3_StartRight(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_w_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  guard1 = false;
  if (CV_EML_COND(3, 0, 0, CV_RELATIONAL_EVAL(5U, 3U, 0,
        *chartInstance->c3_PhasePerc, 50.0, -1, 4U, *chartInstance->c3_PhasePerc
        > 50.0))) {
    if (CV_EML_COND(3, 0, 1, CV_RELATIONAL_EVAL(5U, 3U, 1,
          *chartInstance->c3_PhasePerc, 52.0, -1, 2U,
          *chartInstance->c3_PhasePerc < 52.0))) {
      CV_EML_MCDC(3, 0, 0, true);
      CV_EML_IF(3, 0, 0, true);
      c3_out = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 == true) {
    CV_EML_MCDC(3, 0, 0, false);
    CV_EML_IF(3, 0, 0, false);
    c3_out = false;
  }

  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_RonL;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_h_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    *chartInstance->c3_State = 103.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 3U,
                          *chartInstance->c3_sfEvent, false);
    *chartInstance->c3_DesState = *chartInstance->c3_InputState;
    chartInstance->c3_dataWrittenToVector[1U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_DesState, 0U, 4U, 3U,
                          *chartInstance->c3_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U, *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, *chartInstance->c3_sfEvent);
}

static void c3_StoppingLeft(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_v_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  guard1 = false;
  if (CV_EML_COND(13, 0, 0, CV_RELATIONAL_EVAL(5U, 13U, 0,
        *chartInstance->c3_PhasePerc, 0.0, -1, 4U, *chartInstance->c3_PhasePerc >
        0.0))) {
    if (CV_EML_COND(13, 0, 1, CV_RELATIONAL_EVAL(5U, 13U, 1,
          *chartInstance->c3_PhasePerc, 2.0, -1, 2U,
          *chartInstance->c3_PhasePerc < 2.0))) {
      CV_EML_MCDC(13, 0, 0, true);
      CV_EML_IF(13, 0, 0, true);
      c3_out = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 == true) {
    CV_EML_MCDC(13, 0, 0, false);
    CV_EML_IF(13, 0, 0, false);
    c3_out = false;
  }

  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_StoppedLeft;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_j_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    *chartInstance->c3_State = 402.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 6U,
                          *chartInstance->c3_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U, *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, *chartInstance->c3_sfEvent);
}

static void c3_StoppedLeft(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_cb_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  c3_out = CV_EML_IF(11, 0, 0, CV_RELATIONAL_EVAL(5U, 11U, 0,
    *chartInstance->c3_InputState, 2.0, -1, 0U, *chartInstance->c3_InputState ==
    2.0));
  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_ActiveState = c3_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_c3_LOPES_3D = c3_IN_Start;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, *chartInstance->c3_sfEvent);
    c3_enter_atomic_Start(chartInstance);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U, *chartInstance->c3_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, *chartInstance->c3_sfEvent);
}

static void c3_enter_atomic_Start(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[2];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 0.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_k_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  if (CV_EML_IF(12, 1, 0, *chartInstance->c3_StartLeg == 1.0)) {
    *chartInstance->c3_State = 501.0;
    chartInstance->c3_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 12U,
                          *chartInstance->c3_sfEvent, false);
  } else {
    if (CV_EML_IF(12, 1, 1, *chartInstance->c3_StartLeg == 2.0)) {
      *chartInstance->c3_State = 502.0;
      chartInstance->c3_dataWrittenToVector[0U] = true;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c3_State, 5U, 4U, 12U,
                            *chartInstance->c3_sfEvent, false);
    }
  }

  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_nargout, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  return c3_y;
}

static real_T c3_b_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static boolean_T c3_c_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_sf_internal_predicateOutput;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_sf_internal_predicateOutput = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_sf_internal_predicateOutput), &c3_thisId);
  sf_mex_destroy(&c3_sf_internal_predicateOutput);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_LOPES_3D_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c3_nameCaptureInfo;
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_d_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i1;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i1, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  uint8_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(uint8_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static uint8_T c3_e_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_b_is_ActiveState, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_is_ActiveState),
    &c3_thisId);
  sf_mex_destroy(&c3_b_is_ActiveState);
  return c3_y;
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_is_ActiveState;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y;
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)chartInstanceVoid;
  c3_b_is_ActiveState = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_is_ActiveState),
    &c3_thisId);
  sf_mex_destroy(&c3_b_is_ActiveState);
  *(uint8_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_g_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_b_dataWrittenToVector, const char_T *c3_identifier,
  boolean_T c3_y[2])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_dataWrittenToVector),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_dataWrittenToVector);
}

static void c3_h_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y[2])
{
  boolean_T c3_bv1[2];
  int32_T c3_i2;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_bv1, 1, 11, 0U, 1, 0U, 1, 2);
  for (c3_i2 = 0; c3_i2 < 2; c3_i2++) {
    c3_y[c3_i2] = c3_bv1[c3_i2];
  }

  sf_mex_destroy(&c3_u);
}

static const mxArray *c3_i_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct
  *chartInstance, const mxArray *c3_b_setSimStateSideEffectsInfo, const char_T
  *c3_identifier)
{
  const mxArray *c3_y = NULL;
  emlrtMsgIdentifier c3_thisId;
  c3_y = NULL;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  sf_mex_assign(&c3_y, c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_setSimStateSideEffectsInfo), &c3_thisId), false);
  sf_mex_destroy(&c3_b_setSimStateSideEffectsInfo);
  return c3_y;
}

static const mxArray *c3_j_emlrt_marshallIn(SFc3_LOPES_3DInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  const mxArray *c3_y = NULL;
  (void)chartInstance;
  (void)c3_parentId;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_duplicatearraysafe(&c3_u), false);
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc3_LOPES_3DInstanceStruct
  *chartInstance, int32_T c3_ssid)
{
  (void)chartInstance;
  (void)c3_ssid;
  return NULL;
}

static void c3_init_sf_message_store_memory(SFc3_LOPES_3DInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_dsm_address_info(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc3_LOPES_3DInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S, 0);
  chartInstance->c3_isStable = (boolean_T *)ssGetDWork_wrapper(chartInstance->S,
    1);
  chartInstance->c3_is_active_c3_LOPES_3D = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 2);
  chartInstance->c3_is_c3_LOPES_3D = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 3);
  chartInstance->c3_is_ActiveState = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 4);
  chartInstance->c3_InputState = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_PhasePerc = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_MeasPhase = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c3_StartLeg = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c3_State = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_DesState = (real_T *)ssGetDWork_wrapper(chartInstance->S, 5);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

static uint32_T* sf_get_sfun_dwork_checksum(void);
void sf_c3_LOPES_3D_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3489532658U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4125879068U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(301419950U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1774146671U);
}

mxArray* sf_c3_LOPES_3D_get_post_codegen_info(void);
mxArray *sf_c3_LOPES_3D_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("4X1iGOL97lktM6t4XjC9UG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo = sf_c3_LOPES_3D_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_LOPES_3D_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_LOPES_3D_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("early");
  mxArray *fallbackReason = mxCreateString("ext_mode");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c3_LOPES_3D_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c3_LOPES_3D_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c3_LOPES_3D(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[31],T\"State\",},{M[3],M[32],T\"DesState\",},{M[8],M[0],T\"is_active_c3_LOPES_3D\",},{M[9],M[0],T\"is_c3_LOPES_3D\",},{M[9],M[33],T\"is_ActiveState\",},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_LOPES_3D_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc3_LOPES_3DInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_LOPES_3DInstanceStruct *chartInstance = (SFc3_LOPES_3DInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _LOPES_3DMachineNumber_,
           3,
           13,
           18,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_LOPES_3DMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_LOPES_3DMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _LOPES_3DMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"DesState");
          _SFD_SET_DATA_PROPS(1,1,1,0,"InputState");
          _SFD_SET_DATA_PROPS(2,1,1,0,"PhasePerc");
          _SFD_SET_DATA_PROPS(3,1,1,0,"MeasPhase");
          _SFD_SET_DATA_PROPS(4,1,1,0,"StartLeg");
          _SFD_SET_DATA_PROPS(5,2,0,1,"State");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,0);
          _SFD_STATE_INFO(12,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,12);
          _SFD_ST_SUBSTATE_COUNT(0,11);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,2);
          _SFD_ST_SUBSTATE_INDEX(0,2,3);
          _SFD_ST_SUBSTATE_INDEX(0,3,4);
          _SFD_ST_SUBSTATE_INDEX(0,4,5);
          _SFD_ST_SUBSTATE_INDEX(0,5,6);
          _SFD_ST_SUBSTATE_INDEX(0,6,7);
          _SFD_ST_SUBSTATE_INDEX(0,7,8);
          _SFD_ST_SUBSTATE_INDEX(0,8,9);
          _SFD_ST_SUBSTATE_INDEX(0,9,10);
          _SFD_ST_SUBSTATE_INDEX(0,10,11);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,11,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(4,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(9,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(7,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(11,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(10,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(3,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(8,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(6,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(12,1,0,0,4,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(12,1,0,13,29,47,67);
        _SFD_CV_INIT_EML_IF(12,1,1,47,67,-1,67);
        _SFD_CV_INIT_EML_IF(12,1,2,97,113,131,151);
        _SFD_CV_INIT_EML_IF(12,1,3,131,151,-1,151);
        _SFD_CV_INIT_EML(10,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(10,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(10,0,0,1,14,-1,0);
        _SFD_CV_INIT_EML(6,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(6,0,0,1,31,1,31);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 14, 31 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(6,0,0,1,31,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(6,0,0,1,14,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(6,0,1,18,31,-1,2);
        _SFD_CV_INIT_EML(14,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(14,0,0,1,15,1,15);
        _SFD_CV_INIT_EML_RELATIONAL(14,0,0,1,15,-1,4);
        _SFD_CV_INIT_EML(4,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(4,0,0,1,31,1,31);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 14, 31 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(4,0,0,1,31,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(4,0,0,1,14,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(4,0,1,18,31,-1,2);
        _SFD_CV_INIT_EML(15,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(15,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(15,0,0,1,14,-1,0);
        _SFD_CV_INIT_EML(7,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(7,0,0,1,28,1,28);

        {
          static int condStart[] = { 1, 17 };

          static int condEnd[] = { 15, 28 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(7,0,0,1,28,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(7,0,0,1,15,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(7,0,1,17,28,-1,0);
        _SFD_CV_INIT_EML(2,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(2,0,0,1,14,-1,0);
        _SFD_CV_INIT_EML(8,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(8,0,0,1,15,1,15);
        _SFD_CV_INIT_EML_RELATIONAL(8,0,0,1,15,-1,4);
        _SFD_CV_INIT_EML(5,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(5,0,0,1,29,1,29);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 15, 29 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(5,0,0,1,29,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(5,0,0,1,15,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(5,0,1,18,29,-1,0);
        _SFD_CV_INIT_EML(13,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(13,0,0,1,31,1,31);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 14, 31 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(13,0,0,1,31,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(13,0,0,1,14,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(13,0,1,18,31,-1,2);
        _SFD_CV_INIT_EML(3,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(3,0,0,1,32,1,32);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 15, 32 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(3,0,0,1,32,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(3,0,0,1,15,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(3,0,1,18,32,-1,2);
        _SFD_CV_INIT_EML(9,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(9,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(9,0,0,1,14,-1,0);
        _SFD_CV_INIT_EML(12,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(12,0,0,1,16,1,16);
        _SFD_CV_INIT_EML_RELATIONAL(12,0,0,1,16,-1,0);
        _SFD_CV_INIT_EML(0,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(0,0,0,1,16,1,16);
        _SFD_CV_INIT_EML_RELATIONAL(0,0,0,1,16,-1,0);
        _SFD_CV_INIT_EML(17,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(17,0,0,1,16,1,16);
        _SFD_CV_INIT_EML_RELATIONAL(17,0,0,1,16,-1,0);
        _SFD_CV_INIT_EML(11,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(11,0,0,1,16,1,16);
        _SFD_CV_INIT_EML_RELATIONAL(11,0,0,1,16,-1,0);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _LOPES_3DMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_LOPES_3DInstanceStruct *chartInstance = (SFc3_LOPES_3DInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c3_InputState);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c3_PhasePerc);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c3_MeasPhase);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c3_StartLeg);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c3_State);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c3_DesState);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s8hOEgWFcLWRM8KfavFdkVB";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_LOPES_3D_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 3, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c3_LOPES_3D(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar)
    ->S);
  chart_debug_initialization(((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
  initialize_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_LOPES_3D(void *chartInstanceVar)
{
  enable_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_LOPES_3D(void *chartInstanceVar)
{
  disable_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_LOPES_3D(void *chartInstanceVar)
{
  sf_gateway_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c3_LOPES_3D(void *chartInstanceVar)
{
  ext_mode_exec_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_LOPES_3D(SimStruct* S)
{
  return get_sim_state_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_LOPES_3D(SimStruct* S, const mxArray *st)
{
  set_sim_state_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c3_LOPES_3D(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_LOPES_3D_optimization_info();
    }

    finalize_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_LOPES_3D(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_LOPES_3D((SFc3_LOPES_3DInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

mxArray *sf_c3_LOPES_3D_get_testpoint_info(void)
{
  return NULL;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x6'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size','local_queue_dwork_idx','local_queue_id'{{T\"int32\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"boolean\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 6, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 2026099410U, 2954910018U, 1570653546U,
    3115618816U };

  return checksum;
}

static void mdlSetWorkWidths_c3_LOPES_3D(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_LOPES_3D_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 3);
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1591317273U));
  ssSetChecksum1(S,(4008665170U));
  ssSetChecksum2(S,(3094445406U));
  ssSetChecksum3(S,(4118128792U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_LOPES_3D(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c3_LOPES_3D(SimStruct *S)
{
  SFc3_LOPES_3DInstanceStruct *chartInstance;
  chartInstance = (SFc3_LOPES_3DInstanceStruct *)utMalloc(sizeof
    (SFc3_LOPES_3DInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc3_LOPES_3DInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_LOPES_3D;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_LOPES_3D;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_LOPES_3D;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_LOPES_3D;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_LOPES_3D;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_LOPES_3D;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_LOPES_3D;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_LOPES_3D;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_LOPES_3D;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_LOPES_3D;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_LOPES_3D;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec = sf_opaque_ext_mode_exec_c3_LOPES_3D;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c3_LOPES_3D(chartInstance);
}

void c3_LOPES_3D_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_LOPES_3D(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_LOPES_3D(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_LOPES_3D(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_LOPES_3D_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
