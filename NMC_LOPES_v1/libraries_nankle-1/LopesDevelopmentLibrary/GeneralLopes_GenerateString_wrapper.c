

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
#include <stdio.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void GeneralLopes_GenerateString_Outputs_wrapper(const real_T *DesiredState,
			const boolean_T *DesiredStateChanged,
			const real_T *SegmentInertia,
			const boolean_T *SegmentInertiaChanged,
			const real_T *WatchdogTimeout,
			const real_T *i,
			uint8_T *s,
			real_T *s_len)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
const char *states[]={"off","init","home","stop","position","force"};
int l; // string length
int st; // state number
sprintf(s,"set msgID %d;get state;get iscabinetbluebuttonpressed;get isinitok;get isMotorsOk;get isTreadmillEmpty;get isPatientDefined",(int)i[0]);
l = (int)strlen(s);

if (DesiredStateChanged[0])
{
    st = (int)DesiredState[0];
    l=l+sprintf(s+l,";set state %s;set watchdogtimeout %d", states[st], (st==0?0:((int)WatchdogTimeout[0])));
}

if (SegmentInertiaChanged[0])
{
    l=l+sprintf(s+l, ";set inertia [%f,%f,%f,%f,%f,0.5,%f,%f,%f,0.5]",
            SegmentInertia[0],SegmentInertia[1],SegmentInertia[2],
            SegmentInertia[3],SegmentInertia[4],SegmentInertia[5],
            SegmentInertia[6],SegmentInertia[7]);
}

s_len[0] = (double)l;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
