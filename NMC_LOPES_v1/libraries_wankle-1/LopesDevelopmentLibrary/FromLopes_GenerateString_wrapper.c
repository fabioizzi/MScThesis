

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <string.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void FromLopes_GenerateString_Outputs_wrapper(const real_T *EnableAnalogInput,
			uint8_T *s,
			real_T *s_len)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
strcpy(s,"set msgid 2;get segmentmodelpos;get segmentmodelvel;get segmentmodelacc;get segmentmeaspos;get segmentmeasforce;get cartesianmodelpos;get treadmill");

if (EnableAnalogInput[0])
{
        strcat(s,";get analoguserinputs");
}
s_len[0] = (double)strlen(s);
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
