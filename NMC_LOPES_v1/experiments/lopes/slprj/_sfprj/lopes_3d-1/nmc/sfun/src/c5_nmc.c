/* Include files */

#include <stddef.h>
#include "blas.h"
#include "nmc_sfun.h"
#include "c5_nmc.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "nmc_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c5_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c5_IN_PurePos                  ((uint8_T)1U)
#define c5_IN_SWITCH                   ((uint8_T)2U)
#define c5_IN_Start                    ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_e_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_f_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_g_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void c5_durationReferenceTimeUpdater(SFc5_nmcInstanceStruct
  *chartInstance);
static void initialize_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void initialize_params_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void enable_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void disable_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_nmc(SFc5_nmcInstanceStruct
  *chartInstance);
static void ext_mode_exec_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void set_sim_state_c5_nmc(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_st);
static void c5_set_sim_state_side_effects_c5_nmc(SFc5_nmcInstanceStruct
  *chartInstance);
static void finalize_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void sf_gateway_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void mdl_start_c5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void initSimStructsc5_nmc(SFc5_nmcInstanceStruct *chartInstance);
static void c5_exit_atomic_SWITCH(SFc5_nmcInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_nargout, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static boolean_T c5_c_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_d_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_e_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_nmc, const char_T *c5_identifier);
static uint8_T c5_f_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_g_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_b_dataWrittenToVector, const char_T *c5_identifier, boolean_T
  c5_y[4]);
static void c5_h_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T c5_y[4]);
static const mxArray *c5_i_emlrt_marshallIn(SFc5_nmcInstanceStruct
  *chartInstance, const mxArray *c5_b_setSimStateSideEffectsInfo, const char_T
  *c5_identifier);
static const mxArray *c5_j_emlrt_marshallIn(SFc5_nmcInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc5_nmcInstanceStruct
  *chartInstance, int32_T c5_ssid);
static void c5_init_sf_message_store_memory(SFc5_nmcInstanceStruct
  *chartInstance);
static void init_dsm_address_info(SFc5_nmcInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc5_nmcInstanceStruct *chartInstance);

/* Function Definitions */
static void c5_durationReferenceTimeUpdater(SFc5_nmcInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initialize_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc5_nmc(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  *chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_doSetSimStateSideEffects = 0U;
  chartInstance->c5_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c5_is_active_c5_nmc = 0U;
  *chartInstance->c5_is_c5_nmc = c5_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_nmc(SFc5_nmcInstanceStruct
  *chartInstance)
{
  uint32_T c5_prevAniVal;
  c5_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c5_is_active_c5_nmc == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 4U, *chartInstance->c5_sfEvent);
  }

  if (*chartInstance->c5_is_c5_nmc == c5_IN_PurePos) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c5_sfEvent);
  }

  if (*chartInstance->c5_is_c5_nmc == c5_IN_SWITCH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c5_sfEvent);
  }

  if (*chartInstance->c5_is_c5_nmc == c5_IN_Start) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c5_sfEvent);
  }

  _SFD_SET_ANIMATION(c5_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  c5_update_debugger_state_c5_nmc(chartInstance);
}

static const mxArray *get_sim_state_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  real_T c5_b_hoistedGlobal;
  real_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T c5_c_hoistedGlobal;
  real_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real_T c5_d_hoistedGlobal;
  real_T c5_d_u;
  const mxArray *c5_e_y = NULL;
  uint8_T c5_e_hoistedGlobal;
  uint8_T c5_e_u;
  const mxArray *c5_f_y = NULL;
  uint8_T c5_f_hoistedGlobal;
  uint8_T c5_f_u;
  const mxArray *c5_g_y = NULL;
  const mxArray *c5_h_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(7, 1), false);
  c5_hoistedGlobal = *chartInstance->c5_count;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = *chartInstance->c5_mean_freq;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = *chartInstance->c5_freq;
  c5_c_u = c5_c_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_d_hoistedGlobal = *chartInstance->c5_start_time;
  c5_d_u = c5_d_hoistedGlobal;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_e_hoistedGlobal = *chartInstance->c5_is_active_c5_nmc;
  c5_e_u = c5_e_hoistedGlobal;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 4, c5_f_y);
  c5_f_hoistedGlobal = *chartInstance->c5_is_c5_nmc;
  c5_f_u = c5_f_hoistedGlobal;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 5, c5_g_y);
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y",
    chartInstance->c5_dataWrittenToVector, 11, 0U, 1U, 0U, 1, 4), false);
  sf_mex_setcell(c5_y, 6, c5_h_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_nmc(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_st)
{
  const mxArray *c5_u;
  boolean_T c5_bv0[4];
  int32_T c5_i0;
  c5_u = sf_mex_dup(c5_st);
  *chartInstance->c5_count = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("count", c5_u, 0)), "count");
  *chartInstance->c5_mean_freq = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("mean_freq", c5_u, 1)), "mean_freq");
  *chartInstance->c5_freq = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("freq", c5_u, 2)), "freq");
  *chartInstance->c5_start_time = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("start_time", c5_u, 3)), "start_time");
  *chartInstance->c5_is_active_c5_nmc = c5_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c5_nmc", c5_u, 4)), "is_active_c5_nmc");
  *chartInstance->c5_is_c5_nmc = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("is_c5_nmc", c5_u, 5)), "is_c5_nmc");
  c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "dataWrittenToVector", c5_u, 6)), "dataWrittenToVector", c5_bv0);
  for (c5_i0 = 0; c5_i0 < 4; c5_i0++) {
    chartInstance->c5_dataWrittenToVector[c5_i0] = c5_bv0[c5_i0];
  }

  sf_mex_assign(&chartInstance->c5_setSimStateSideEffectsInfo,
                c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c5_u, 7)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c5_u);
  chartInstance->c5_doSetSimStateSideEffects = 1U;
  c5_update_debugger_state_c5_nmc(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void c5_set_sim_state_side_effects_c5_nmc(SFc5_nmcInstanceStruct
  *chartInstance)
{
  if (chartInstance->c5_doSetSimStateSideEffects != 0) {
    chartInstance->c5_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c5_setSimStateSideEffectsInfo);
}

static void sf_gateway_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  uint32_T c5_debug_family_var_map[2];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 0.0;
  uint32_T c5_b_debug_family_var_map[3];
  real_T c5_b_nargin = 0.0;
  real_T c5_b_nargout = 1.0;
  boolean_T c5_out;
  real_T c5_c_nargin = 0.0;
  real_T c5_c_nargout = 0.0;
  real_T c5_d_nargin = 0.0;
  real_T c5_d_nargout = 1.0;
  boolean_T c5_b_out;
  real_T c5_e_nargin = 0.0;
  real_T c5_e_nargout = 0.0;
  real_T c5_hoistedGlobal;
  real_T c5_b_hoistedGlobal;
  real_T c5_c_hoistedGlobal;
  real_T c5_A;
  real_T c5_B;
  real_T c5_x;
  real_T c5_y;
  real_T c5_b_x;
  real_T c5_b_y;
  real_T c5_c_y;
  real_T c5_d_hoistedGlobal;
  real_T c5_b_B;
  real_T c5_d_y;
  real_T c5_e_y;
  real_T c5_f_y;
  real_T c5_f_nargin = 0.0;
  real_T c5_f_nargout = 1.0;
  boolean_T c5_c_out;
  real_T c5_g_nargin = 0.0;
  real_T c5_g_nargout = 0.0;
  c5_set_sim_state_side_effects_c5_nmc(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  c5_durationReferenceTimeUpdater(chartInstance);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, *chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_N, 4U, 1U, 0U,
                        *chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_InSig, 3U, 1U, 0U,
                        *chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_time_sig, 2U, 1U, 0U,
                        *chartInstance->c5_sfEvent, false);
  *chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, *chartInstance->c5_sfEvent);
  if (*chartInstance->c5_is_active_c5_nmc == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 4U, *chartInstance->c5_sfEvent);
    *chartInstance->c5_is_active_c5_nmc = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *chartInstance->c5_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c5_sfEvent);
    *chartInstance->c5_is_c5_nmc = c5_IN_Start;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c5_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_d_debug_family_names,
      c5_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    *chartInstance->c5_mean_freq = 0.0;
    chartInstance->c5_dataWrittenToVector[2U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c5_mean_freq, 6U, 4U, 2U,
                          *chartInstance->c5_sfEvent, false);
    *chartInstance->c5_count = 0.0;
    chartInstance->c5_dataWrittenToVector[1U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c5_count, 5U, 4U, 2U,
                          *chartInstance->c5_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    switch (*chartInstance->c5_is_c5_nmc) {
     case c5_IN_PurePos:
      CV_CHART_EVAL(4, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                   *chartInstance->c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_f_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_out, 2U, c5_b_sf_marshallOut,
        c5_b_sf_marshallIn);
      c5_out = CV_EML_IF(0, 0, 0, CV_RELATIONAL_EVAL(5U, 0U, 0,
        *chartInstance->c5_InSig, 1.0, -1, 0U, *chartInstance->c5_InSig == 1.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c5_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c5_sfEvent);
        *chartInstance->c5_is_c5_nmc = c5_IN_SWITCH;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_b_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        *chartInstance->c5_start_time = *chartInstance->c5_time_sig;
        chartInstance->c5_dataWrittenToVector[0U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c5_start_time, 1U, 4U, 1U,
                              *chartInstance->c5_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     *chartInstance->c5_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c5_sfEvent);
      break;

     case c5_IN_SWITCH:
      CV_CHART_EVAL(4, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   *chartInstance->c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_e_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_out, 2U, c5_b_sf_marshallOut,
        c5_b_sf_marshallIn);
      c5_b_out = CV_EML_IF(2, 0, 0, CV_RELATIONAL_EVAL(5U, 2U, 0,
        *chartInstance->c5_InSig, 0.0, -1, 0U, *chartInstance->c5_InSig == 0.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *chartInstance->c5_sfEvent);
        c5_exit_atomic_SWITCH(chartInstance);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c5_sfEvent);
        *chartInstance->c5_is_c5_nmc = c5_IN_PurePos;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        if (!chartInstance->c5_dataWrittenToVector[1U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(5U, 4U, 0U,
            *chartInstance->c5_sfEvent, false);
        }

        (*chartInstance->c5_count)++;
        chartInstance->c5_dataWrittenToVector[1U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c5_count, 5U, 4U, 0U,
                              *chartInstance->c5_sfEvent, false);
        if (!chartInstance->c5_dataWrittenToVector[2U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(6U, 4U, 0U,
            *chartInstance->c5_sfEvent, false);
        }

        if (!chartInstance->c5_dataWrittenToVector[3U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 4U, 0U,
            *chartInstance->c5_sfEvent, false);
        }

        c5_hoistedGlobal = *chartInstance->c5_mean_freq;
        c5_b_hoistedGlobal = *chartInstance->c5_N;
        c5_c_hoistedGlobal = *chartInstance->c5_N;
        c5_A = c5_hoistedGlobal * (c5_b_hoistedGlobal - 1.0);
        c5_B = c5_c_hoistedGlobal;
        c5_x = c5_A;
        c5_y = c5_B;
        c5_b_x = c5_x;
        c5_b_y = c5_y;
        c5_c_y = c5_b_x / c5_b_y;
        c5_d_hoistedGlobal = *chartInstance->c5_N;
        c5_b_B = c5_d_hoistedGlobal;
        c5_d_y = c5_b_B;
        c5_e_y = c5_d_y;
        c5_f_y = 1.0 / c5_e_y;
        *chartInstance->c5_mean_freq = c5_c_y + c5_f_y * *chartInstance->c5_freq;
        chartInstance->c5_dataWrittenToVector[2U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c5_mean_freq, 6U, 4U, 0U,
                              *chartInstance->c5_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                     *chartInstance->c5_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c5_sfEvent);
      break;

     case c5_IN_Start:
      CV_CHART_EVAL(4, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                   *chartInstance->c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_g_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_out, 2U, c5_b_sf_marshallOut,
        c5_b_sf_marshallIn);
      c5_c_out = CV_EML_IF(3, 0, 0, CV_RELATIONAL_EVAL(5U, 3U, 0,
        *chartInstance->c5_InSig, 1.0, -1, 0U, *chartInstance->c5_InSig == 1.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *chartInstance->c5_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c5_sfEvent);
        *chartInstance->c5_is_c5_nmc = c5_IN_SWITCH;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_b_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        *chartInstance->c5_start_time = *chartInstance->c5_time_sig;
        chartInstance->c5_dataWrittenToVector[0U] = true;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c5_start_time, 1U, 4U, 1U,
                              *chartInstance->c5_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     *chartInstance->c5_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c5_sfEvent);
      break;

     default:
      CV_CHART_EVAL(4, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c5_is_c5_nmc = c5_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c5_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_nmcMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  c5_init_sf_message_store_memory(chartInstance);
}

static void initSimStructsc5_nmc(SFc5_nmcInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_exit_atomic_SWITCH(SFc5_nmcInstanceStruct *chartInstance)
{
  uint32_T c5_debug_family_var_map[2];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 0.0;
  real_T c5_hoistedGlobal;
  real_T c5_b_hoistedGlobal;
  real_T c5_B;
  real_T c5_y;
  real_T c5_b_y;
  _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, *chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_c_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 1U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  if (!chartInstance->c5_dataWrittenToVector[0U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(1U, 4U, 1U, *chartInstance->c5_sfEvent,
      false);
  }

  c5_hoistedGlobal = *chartInstance->c5_time_sig;
  c5_b_hoistedGlobal = *chartInstance->c5_start_time;
  c5_B = c5_hoistedGlobal - c5_b_hoistedGlobal;
  c5_y = c5_B;
  c5_b_y = c5_y;
  *chartInstance->c5_freq = 1.0 / c5_b_y;
  chartInstance->c5_dataWrittenToVector[3U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_freq, 0U, 4U, 1U,
                        *chartInstance->c5_sfEvent, false);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c5_sfEvent);
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_nargout, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  boolean_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(boolean_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static boolean_T c5_c_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  boolean_T c5_y;
  boolean_T c5_b0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_b0, 1, 11, 0U, 0, 0U, 0);
  c5_y = c5_b0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_sf_internal_predicateOutput;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  boolean_T c5_y;
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)chartInstanceVoid;
  c5_sf_internal_predicateOutput = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_sf_internal_predicateOutput), &c5_thisId);
  sf_mex_destroy(&c5_sf_internal_predicateOutput);
  *(boolean_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_nmc_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_d_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i1;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i1, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i1;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_b_is_active_c5_nmc, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_is_active_c5_nmc),
    &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_nmc);
  return c5_y;
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_g_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_b_dataWrittenToVector, const char_T *c5_identifier, boolean_T
  c5_y[4])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_dataWrittenToVector),
                        &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_dataWrittenToVector);
}

static void c5_h_emlrt_marshallIn(SFc5_nmcInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T c5_y[4])
{
  boolean_T c5_bv1[4];
  int32_T c5_i2;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_bv1, 1, 11, 0U, 1, 0U, 1, 4);
  for (c5_i2 = 0; c5_i2 < 4; c5_i2++) {
    c5_y[c5_i2] = c5_bv1[c5_i2];
  }

  sf_mex_destroy(&c5_u);
}

static const mxArray *c5_i_emlrt_marshallIn(SFc5_nmcInstanceStruct
  *chartInstance, const mxArray *c5_b_setSimStateSideEffectsInfo, const char_T
  *c5_identifier)
{
  const mxArray *c5_y = NULL;
  emlrtMsgIdentifier c5_thisId;
  c5_y = NULL;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  sf_mex_assign(&c5_y, c5_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_setSimStateSideEffectsInfo), &c5_thisId), false);
  sf_mex_destroy(&c5_b_setSimStateSideEffectsInfo);
  return c5_y;
}

static const mxArray *c5_j_emlrt_marshallIn(SFc5_nmcInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  const mxArray *c5_y = NULL;
  (void)chartInstance;
  (void)c5_parentId;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_duplicatearraysafe(&c5_u), false);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc5_nmcInstanceStruct
  *chartInstance, int32_T c5_ssid)
{
  (void)chartInstance;
  (void)c5_ssid;
  return NULL;
}

static void c5_init_sf_message_store_memory(SFc5_nmcInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_dsm_address_info(SFc5_nmcInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_nmcInstanceStruct *chartInstance)
{
  chartInstance->c5_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S, 0);
  chartInstance->c5_isStable = (boolean_T *)ssGetDWork_wrapper(chartInstance->S,
    1);
  chartInstance->c5_is_active_c5_nmc = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 2);
  chartInstance->c5_is_c5_nmc = (uint8_T *)ssGetDWork_wrapper(chartInstance->S,
    3);
  chartInstance->c5_time_sig = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c5_start_time = (real_T *)ssGetDWork_wrapper(chartInstance->S,
    4);
  chartInstance->c5_InSig = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_count = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_mean_freq = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c5_N = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    2);
  chartInstance->c5_freq = (real_T *)ssGetDWork_wrapper(chartInstance->S, 5);
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
void sf_c5_nmc_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(532742943U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2704047349U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(467561250U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(248169349U);
}

mxArray* sf_c5_nmc_get_post_codegen_info(void);
mxArray *sf_c5_nmc_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("qwBHu0mYCCULb9C2iniFVE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_nmc_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_nmc_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_nmc_jit_fallback_info(void)
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

mxArray *sf_c5_nmc_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_nmc_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c5_nmc(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[112],T\"count\",},{M[1],M[113],T\"mean_freq\",},{M[3],M[115],T\"freq\",},{M[3],M[110],T\"start_time\",},{M[8],M[0],T\"is_active_c5_nmc\",},{M[9],M[0],T\"is_c5_nmc\",},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_nmc_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc5_nmcInstanceStruct *) chartInstance,
    msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_nmcInstanceStruct *chartInstance = (SFc5_nmcInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _nmcMachineNumber_,
           5,
           3,
           4,
           0,
           7,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_nmcMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_nmcMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _nmcMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"freq");
          _SFD_SET_DATA_PROPS(1,0,0,0,"start_time");
          _SFD_SET_DATA_PROPS(2,1,1,0,"time_sig");
          _SFD_SET_DATA_PROPS(3,1,1,0,"InSig");
          _SFD_SET_DATA_PROPS(4,1,1,0,"N");
          _SFD_SET_DATA_PROPS(5,2,0,1,"count");
          _SFD_SET_DATA_PROPS(6,2,0,1,"mean_freq");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
        }

        _SFD_CV_INIT_CHART(3,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,9,1,9);
        _SFD_CV_INIT_EML_RELATIONAL(2,0,0,1,9,-1,0);
        _SFD_CV_INIT_EML(0,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(0,0,0,1,9,1,9);
        _SFD_CV_INIT_EML_RELATIONAL(0,0,0,1,9,-1,0);
        _SFD_CV_INIT_EML(3,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(3,0,0,1,11,1,11);
        _SFD_CV_INIT_EML_RELATIONAL(3,0,0,1,11,-1,0);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _nmcMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_nmcInstanceStruct *chartInstance = (SFc5_nmcInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c5_time_sig);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c5_start_time);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c5_InSig);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c5_count);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c5_mean_freq);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c5_N);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c5_freq);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s9Ku2StkItLc1pZ8XekECCC";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_nmc_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 5, "dworkChecksum");
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

static void sf_opaque_initialize_c5_nmc(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc5_nmcInstanceStruct*) chartInstanceVar)->S);
  chart_debug_initialization(((SFc5_nmcInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
  initialize_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_nmc(void *chartInstanceVar)
{
  enable_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_nmc(void *chartInstanceVar)
{
  disable_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_nmc(void *chartInstanceVar)
{
  sf_gateway_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c5_nmc(void *chartInstanceVar)
{
  ext_mode_exec_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_nmc(SimStruct* S)
{
  return get_sim_state_c5_nmc((SFc5_nmcInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_nmc(SimStruct* S, const mxArray *st)
{
  set_sim_state_c5_nmc((SFc5_nmcInstanceStruct*)sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c5_nmc(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_nmcInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_nmc_optimization_info();
    }

    finalize_c5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_nmc((SFc5_nmcInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_nmc(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_nmc((SFc5_nmcInstanceStruct*)sf_get_chart_instance_ptr
      (S));
  }
}

mxArray *sf_c5_nmc_get_testpoint_info(void)
{
  return NULL;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x6'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size','local_queue_dwork_idx','local_queue_id'{{T\"int32\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"boolean\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 6, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 2418971710U, 1876593453U, 704030427U,
    1440927024U };

  return checksum;
}

static void mdlSetWorkWidths_c5_nmc(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_nmc_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 5);
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(941730132U));
  ssSetChecksum1(S,(240015166U));
  ssSetChecksum2(S,(3160279280U));
  ssSetChecksum3(S,(3960705645U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_nmc(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c5_nmc(SimStruct *S)
{
  SFc5_nmcInstanceStruct *chartInstance;
  chartInstance = (SFc5_nmcInstanceStruct *)utMalloc(sizeof
    (SFc5_nmcInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc5_nmcInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_nmc;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_nmc;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_nmc;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_nmc;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_nmc;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_nmc;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_nmc;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_nmc;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_nmc;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_nmc;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_nmc;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec = sf_opaque_ext_mode_exec_c5_nmc;
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
  mdl_start_c5_nmc(chartInstance);
}

void c5_nmc_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_nmc(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_nmc(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_nmc(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_nmc_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
