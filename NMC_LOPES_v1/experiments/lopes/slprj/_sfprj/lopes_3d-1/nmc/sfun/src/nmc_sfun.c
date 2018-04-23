/* Include files */

#include "nmc_sfun.h"
#include "nmc_sfun_debug_macros.h"
#include "c1_nmc.h"
#include "c5_nmc.h"
#include "c13_nmc.h"
#include "c14_nmc.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _nmcMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void nmc_initializer(void)
{
}

void nmc_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_nmc_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_nmc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_nmc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_nmc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==14) {
    c14_nmc_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

extern void sf_nmc_uses_exported_functions(int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[])
{
  plhs[0] = mxCreateLogicalScalar(0);
}

unsigned int sf_nmc_process_testpoint_info_call( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char machineName[128];
  if (nrhs < 3 || !mxIsChar(prhs[0]) || !mxIsChar(prhs[1]))
    return 0;

  /* Possible call to get testpoint info. */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_testpoint_info"))
    return 0;
  mxGetString(prhs[1], machineName, sizeof(machineName)/sizeof(char));
  machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
  if (!strcmp(machineName, "nmc")) {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
    switch (chartFileNumber) {
     case 1:
      {
        extern mxArray *sf_c1_nmc_get_testpoint_info(void);
        plhs[0] = sf_c1_nmc_get_testpoint_info();
        break;
      }

     case 5:
      {
        extern mxArray *sf_c5_nmc_get_testpoint_info(void);
        plhs[0] = sf_c5_nmc_get_testpoint_info();
        break;
      }

     case 13:
      {
        extern mxArray *sf_c13_nmc_get_testpoint_info(void);
        plhs[0] = sf_c13_nmc_get_testpoint_info();
        break;
      }

     case 14:
      {
        extern mxArray *sf_c14_nmc_get_testpoint_info(void);
        plhs[0] = sf_c14_nmc_get_testpoint_info();
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }

    return 1;
  }

  return 0;

#else

  return 0;

#endif

}

unsigned int sf_nmc_process_check_sum_call( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>2 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"library")) {
      char machineName[100];
      mxGetString(prhs[2], machineName,sizeof(machineName)/sizeof(char));
      machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
      if (!strcmp(machineName,"nmc")) {
        if (nrhs==3) {
          ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1498826386U);
          ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1260527318U);
          ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2379902395U);
          ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3162422717U);
        } else if (nrhs==4) {
          unsigned int chartFileNumber;
          chartFileNumber = (unsigned int)mxGetScalar(prhs[3]);
          switch (chartFileNumber) {
           case 1:
            {
              extern void sf_c1_nmc_get_check_sum(mxArray *plhs[]);
              sf_c1_nmc_get_check_sum(plhs);
              break;
            }

           case 5:
            {
              extern void sf_c5_nmc_get_check_sum(mxArray *plhs[]);
              sf_c5_nmc_get_check_sum(plhs);
              break;
            }

           case 13:
            {
              extern void sf_c13_nmc_get_check_sum(mxArray *plhs[]);
              sf_c13_nmc_get_check_sum(plhs);
              break;
            }

           case 14:
            {
              extern void sf_c14_nmc_get_check_sum(mxArray *plhs[]);
              sf_c14_nmc_get_check_sum(plhs);
              break;
            }

           default:
            ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
          }
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  } else {
    return 0;
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_nmc_autoinheritance_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "qwBHu0mYCCULb9C2iniFVE") == 0) {
          extern mxArray *sf_c1_nmc_get_autoinheritance_info(void);
          plhs[0] = sf_c1_nmc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "qwBHu0mYCCULb9C2iniFVE") == 0) {
          extern mxArray *sf_c5_nmc_get_autoinheritance_info(void);
          plhs[0] = sf_c5_nmc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 13:
      {
        if (strcmp(aiChksum, "qwBHu0mYCCULb9C2iniFVE") == 0) {
          extern mxArray *sf_c13_nmc_get_autoinheritance_info(void);
          plhs[0] = sf_c13_nmc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 14:
      {
        if (strcmp(aiChksum, "qwBHu0mYCCULb9C2iniFVE") == 0) {
          extern mxArray *sf_c14_nmc_get_autoinheritance_info(void);
          plhs[0] = sf_c14_nmc_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_nmc_get_eml_resolved_functions_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_nmc_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_nmc_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_nmc_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_nmc_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray *sf_c13_nmc_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_nmc_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 14:
      {
        extern const mxArray *sf_c14_nmc_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c14_nmc_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_nmc_third_party_uses_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c1_nmc_third_party_uses_info(void);
          plhs[0] = sf_c1_nmc_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c5_nmc_third_party_uses_info(void);
          plhs[0] = sf_c5_nmc_third_party_uses_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c13_nmc_third_party_uses_info(void);
          plhs[0] = sf_c13_nmc_third_party_uses_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c14_nmc_third_party_uses_info(void);
          plhs[0] = sf_c14_nmc_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_nmc_jit_fallback_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c1_nmc_jit_fallback_info(void);
          plhs[0] = sf_c1_nmc_jit_fallback_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c5_nmc_jit_fallback_info(void);
          plhs[0] = sf_c5_nmc_jit_fallback_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c13_nmc_jit_fallback_info(void);
          plhs[0] = sf_c13_nmc_jit_fallback_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c14_nmc_jit_fallback_info(void);
          plhs[0] = sf_c14_nmc_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_nmc_updateBuildInfo_args_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c1_nmc_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_nmc_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c5_nmc_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_nmc_updateBuildInfo_args_info();
          break;
        }
      }

     case 13:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c13_nmc_updateBuildInfo_args_info(void);
          plhs[0] = sf_c13_nmc_updateBuildInfo_args_info();
          break;
        }
      }

     case 14:
      {
        if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
          extern mxArray *sf_c14_nmc_updateBuildInfo_args_info(void);
          plhs[0] = sf_c14_nmc_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void sf_nmc_get_post_codegen_info( int nlhs, mxArray * plhs[], int nrhs, const
  mxArray * prhs[] )
{
  unsigned int chartFileNumber = (unsigned int) mxGetScalar(prhs[0]);
  char tpChksum[64];
  mxGetString(prhs[1], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  switch (chartFileNumber) {
   case 1:
    {
      if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
        extern mxArray *sf_c1_nmc_get_post_codegen_info(void);
        plhs[0] = sf_c1_nmc_get_post_codegen_info();
        return;
      }
    }
    break;

   case 5:
    {
      if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
        extern mxArray *sf_c5_nmc_get_post_codegen_info(void);
        plhs[0] = sf_c5_nmc_get_post_codegen_info();
        return;
      }
    }
    break;

   case 13:
    {
      if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
        extern mxArray *sf_c13_nmc_get_post_codegen_info(void);
        plhs[0] = sf_c13_nmc_get_post_codegen_info();
        return;
      }
    }
    break;

   case 14:
    {
      if (strcmp(tpChksum, "s9Ku2StkItLc1pZ8XekECCC") == 0) {
        extern mxArray *sf_c14_nmc_get_post_codegen_info(void);
        plhs[0] = sf_c14_nmc_get_post_codegen_info();
        return;
      }
    }
    break;

   default:
    break;
  }

  plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
}

void nmc_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _nmcMachineNumber_ = sf_debug_initialize_machine(debugInstance,"nmc","sfun",1,
    9,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_nmcMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_nmcMachineNumber_,0);
}

void nmc_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_nmc_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("nmc", "LOPES_3D");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_nmc_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
