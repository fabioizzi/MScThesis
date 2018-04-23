/* PCI_1761_RELAY.C
 *
 * This file is the driver for the relay card PCI_1761. 
 * (actually, it was originally for the PCI_IIRO8, but it works equally fine
 * on the PCI_1761. In order to avoid confusion, I chose to rename it).
 *
 * Note that this driver only supports limited functionality of
 * the card: it only provides output for the
 * relays; inputs are not implemented (neither is reading back the state
 * of the relays). The input of this block is a double, but the value
 * is interpreted as an unsigned char. That value is sent to the
 * relays. If you send a whole number 0<=x<=255 to it, this will work
 * perfectly. Otherwise, the result may be unpredictable (depending on
 * how much you know about C typecasts).
 *
 * The base address of the PCI card can be changed dynamically during
 * model execution (for the Lopes in the Roessingh, it should be at 0xe0c0).
 *
 * This driver was based on the following Matlab-file:
      $Revision: 1.6.4.5 $ $Date: 2009/08/08 01:15:48 $
      doadvpcl818.c - xPC Target, non-inlined S-function driver for digital output section of Advantech PCL-818 series boards
      Copyright 1996-2009 The MathWorks, Inc.
 */

#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	PCI_1761_Relay

#include 	<stddef.h>
#include 	<stdlib.h>
#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#else
#include 	<windows.h>
#include 	"xpcimports.h"
#endif


/* Parameters and Inputs */
#define NUM_PARAMS             (1)
#define BASE_ADDRESS_ARG       (ssGetSFcnParam(S,0))

/* Convert S Function Parameters to Varibles */

#define BASE_ADDRESS ((uint_T) mxGetPr(BASE_ADDRESS_ARG)[0])

/*====================*
 * S-function methods *
 *====================*/

static void mdlCheckParameters(SimStruct *S)
{
}

static void mdlInitializeSizes(SimStruct *S)
{
    // ssPrintf("InitializeSizes\n");
    ssSetNumSFcnParams(S, NUM_PARAMS);
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S))
    {
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL)
        {
            return;
        }
    } else
    {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S,0,1);
    
    
    if (!ssSetNumOutputPorts(S, 0)) return;
    /* Uncomment this if you want to use one output port, e.g. for debugging:
    ssSetOutputPortWidth(S,0,1);
    ssSetOutputPortSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOutputPortOffsetTime(S, 0, 0.0);
    */

    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetSFcnParamNotTunable(S,0);
    
    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE);
	
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0);
}


#define MDL_START
static void mdlStart(SimStruct *S)
{
    // ssPrintf("Start. Base: %d\n",BASE_ADDRESS);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    // Uncomment for using an output port, e.g. for debugging: 
    // real_T *y = ssGetOutputPortSignal(S,0);
    
    unsigned char input_as_uint8 = (unsigned char) (*ssGetInputPortRealSignalPtrs(S,0)[0]);
#ifndef MATLAB_MEX_FILE	
    rl32eOutpB(BASE_ADDRESS,input_as_uint8);
#endif /* MATLAB_MEX_FILE */

    // For debugging:
    // ssPrintf("%d\n",(int)input_as_uint8);
}

static void mdlTerminate(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	rl32eOutpB(BASE_ADDRESS,0);
#endif /* MATLAB_MEX_FILE */
}

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
