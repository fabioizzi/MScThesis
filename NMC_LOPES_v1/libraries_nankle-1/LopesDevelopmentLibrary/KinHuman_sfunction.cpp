/*
 BEFORE USING THIS FILE IN AN S-FUNCTION, COMPILE IT WITHIN MATLAB BY TYPING:
 
 mex KinHuman_sfunction.cpp KinHuman_common.cpp KinHuman.cpp KinObject.cpp KinPointAxis.cpp
 
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  KinHuman_sfunction
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "KinHuman.h"
#define VECTOR_SIZE (3)
#define N_OUTPUT_POINTS_REDUCED (11) /* The number of 3d-points in the output */

// Definition of functions (I don't want to spend an entire .h file on it)
void UpdatePatientDimensions(KinHuman* KH, const real_T *patientDimensions);
void CopyCartesianPositions(KinHuman* KH, real_T *cartesianPositions);
real_T ForceOneFootOnFloor(real_T *cartesianPositions, int N);


/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 * See matlabroot/simulink/src/sfuntmpl_doc.c for more details.
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
     /* real_T and double should be the same for this s-function
      (otherwise, we cannot call KH->SetInputPosAngleVector directly). */
    if (sizeof(real_T) != sizeof(double))
    {
        ssSetErrorStatus(S,"Error: real_T and double should be the same for this s-function!");
    }
    /* See sfuntmpl_doc.c for more details on the macros below */

    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 4)) return;
    ssSetInputPortWidth(S, 0, 12); // PatientDimensions
    ssSetInputPortWidth(S, 1, 1);  // PatientDimensionsChanged
    ssSetInputPortWidth(S, 2, 19); // JointAngles
    ssSetInputPortWidth(S, 3, 1);  // OneFootOnGround 
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    ssSetInputPortRequiredContiguous(S, 1, true); /*direct input signal access*/
    ssSetInputPortRequiredContiguous(S, 2, true); /*direct input signal access*/
    ssSetInputPortRequiredContiguous(S, 3, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortDirectFeedThrough(S, 3, 1);

    if (!ssSetNumOutputPorts(S, 2)) return;
    ssSetOutputPortWidth(S, 0, N_OUTPUT_POINTS_REDUCED*VECTOR_SIZE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortWidth(S, 1, 1); // PY
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 1); // one int which indicates if this is the first execution of the block
    ssSetNumPWork(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
     ssSetIWorkValue(S, 0, 1); // Set first element to zero - bool isFirstTime
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
     ssSetPWorkValue(S,0, (void*) new KinHuman()); // Create a new class 
  }
#endif /*  MDL_START */

/** Function to update the patient dimensions. Use this function to see
 * which element in the vector is which...
 */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const real_T *patientDimensions = (const real_T*) ssGetInputPortSignal(S,0);
    const real_T *patientDimensionsChanged = (const real_T*) ssGetInputPortSignal(S,2);
    const real_T *jointAngles = (const real_T*) ssGetInputPortSignal(S,2);
    const real_T *forceOneFootOnFloor = (const real_T*) ssGetInputPortSignal(S,3); // If true, the value 
        // of PY is ignored and the model is lifted such that the lowest point is at y=0
    real_T       *cartesianPositions = (real_T*)ssGetOutputPortSignal(S,0);
    real_T       *PY_out = (real_T*)ssGetOutputPortSignal(S,1);
    
    
    KinHuman* KH = (KinHuman*) ssGetPWorkValue(S,0);
    bool isFirstTime = (bool)ssGetIWorkValue(S,0);
    
    if (patientDimensionsChanged[0] || isFirstTime)
    {
        UpdatePatientDimensions(KH, patientDimensions);
        ssSetIWorkValue(S,0,0); // bool isFirstTime;
    }
    KH->SetInputPosAngleVector(jointAngles);
    KH->Update();

    /* It is dangerous to use KH->SetOutputCartesian and assume that
     * it will form a 12*3 vector; if someone changes Vector3d.h, it
     * will fail without notice. So let's use our own copy function. */
    CopyCartesianPositions(KH,cartesianPositions);
    
    real_T minimum;
    if (forceOneFootOnFloor[0])
    {
        minimum = ForceOneFootOnFloor(cartesianPositions, N_OUTPUT_POINTS_REDUCED);
    } else minimum=0;
    
    /* If forceOneFootOnFloor is true, we 'lift' the model up to a
     * certain height. It is convenient to know the PY value which is
     * consistent with the new height. For this, we subtract the minimum
     * from the original PY
     */
    *PY_out = jointAngles[1] - minimum;
}



#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    // Delete the class again
    delete (KinHuman*)ssGetPWorkValue(S,0);
}


/*======================================================*
 * See sfuntmpl_doc.c for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
