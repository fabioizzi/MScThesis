

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
#include <math.h>
#include <stdio.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
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
void FromLopes_ParseString_Outputs_wrapper(const uint8_T *str,
			const real_T *len,
			real_T *msgId,
			real_T *cnt,
			real_T *cntExpected,
			real_T *segmentModelPos,
			real_T *segmentModelVel,
			real_T *segmentModelAcc,
			real_T *segmentMeasPos,
			real_T *segmentMeasForce,
			real_T *cartesianModelPos,
			real_T *treadmill,
			real_T *analogInput,
			const int_T u_width)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
const char *fmt = "\"msgID=%lf\";"
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // segmentModelPos
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // segmentModelVel
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // segmentModelAcc
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // segmentMeasPos
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // segmentMeasForce
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // cartesianModelPos
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf];" // treadmill
        "[%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf]"; // analogInput

cnt[0] = sscanf (str,fmt,
        msgId,
        segmentModelPos+0,  segmentModelPos+1,  segmentModelPos+2,
        segmentModelPos+3,  segmentModelPos+4,  segmentModelPos+5,
        segmentModelPos+6,  segmentModelPos+7,  segmentModelPos+8,
        segmentModelPos+9,  segmentModelPos+10, segmentModelPos+11,
        segmentModelPos+12, segmentModelPos+13, segmentModelPos+14,
        segmentModelVel+0,  segmentModelVel+1,  segmentModelVel+2,
        segmentModelVel+3,  segmentModelVel+4,  segmentModelVel+5,
        segmentModelVel+6,  segmentModelVel+7,  segmentModelVel+8,
        segmentModelVel+9,  segmentModelVel+10, segmentModelVel+11,
        segmentModelVel+12, segmentModelVel+13, segmentModelVel+14,
        segmentModelAcc+0,  segmentModelAcc+1,  segmentModelAcc+2,
        segmentModelAcc+3,  segmentModelAcc+4,  segmentModelAcc+5,
        segmentModelAcc+6,  segmentModelAcc+7,  segmentModelAcc+8,
        segmentModelAcc+9,  segmentModelAcc+10, segmentModelAcc+11,
        segmentModelAcc+12, segmentModelAcc+13, segmentModelAcc+14,
        segmentMeasPos+0,  segmentMeasPos+1,  segmentMeasPos+2,
        segmentMeasPos+3,  segmentMeasPos+4,  segmentMeasPos+5,
        segmentMeasPos+6,  segmentMeasPos+7,  segmentMeasPos+8,
        segmentMeasPos+9,  segmentMeasPos+10, segmentMeasPos+11,
        segmentMeasPos+12, segmentMeasPos+13, segmentMeasPos+14,
        segmentMeasForce+0,  segmentMeasForce+1,  segmentMeasForce+2,
        segmentMeasForce+3,  segmentMeasForce+4,  segmentMeasForce+5,
        segmentMeasForce+6,  segmentMeasForce+7,  segmentMeasForce+8,
        segmentMeasForce+9,
        cartesianModelPos+0,  cartesianModelPos+1,  cartesianModelPos+2,
        cartesianModelPos+3,  cartesianModelPos+4,  cartesianModelPos+5,
        cartesianModelPos+6,  cartesianModelPos+7,  cartesianModelPos+8,
        cartesianModelPos+9,  cartesianModelPos+10, cartesianModelPos+11,
        cartesianModelPos+12, cartesianModelPos+13, cartesianModelPos+14,
        cartesianModelPos+15, cartesianModelPos+16, cartesianModelPos+17,
        cartesianModelPos+18, cartesianModelPos+19, cartesianModelPos+20,
        cartesianModelPos+21, cartesianModelPos+22, cartesianModelPos+23,
        cartesianModelPos+24, cartesianModelPos+25, cartesianModelPos+26,
        cartesianModelPos+27, cartesianModelPos+28, cartesianModelPos+29,
        cartesianModelPos+30, cartesianModelPos+31, cartesianModelPos+32,
        treadmill+0,  treadmill+1,  treadmill+2,  treadmill+3,
        treadmill+4,  treadmill+5,  treadmill+6,
        analogInput+0,  analogInput+1,  analogInput+2,  analogInput+3,
        analogInput+4,  analogInput+5,  analogInput+6,  analogInput+7,
        analogInput+8,  analogInput+9,  analogInput+10, analogInput+11,
        analogInput+12, analogInput+13, analogInput+14, analogInput+15);
// cntExpected can be 111 or 127, depending on whether the analog inputs
// are enabled. Both are fine, but any other number indicates an error.
cntExpected[0] = 111;
cntExpected[1] = 127;

/* PYTHON SCRIPT FOR GENERATING THE ABOVE CODE:
vars = [ ('segmentModelPos',15), ('segmentModelVel',15), ('segmentModelAcc',15), 
('segmentMeasPos',15), ('segmentMeasForce',10),('cartesianModelPos',33), ('treadmill',7), ('analogInput',16)]
indent = '        '

# Format string
print ('const char *fmt = "\\"msgID=%lf\\";"')
for (i,v) in enumerate(vars):
    delim = '";' if (i==len(vars)-1) else ';"'
    print ('%s"[%s]%s // %s'%(indent, ','.join(v[1]*['%lf']), delim,v[0]))

# Variables
import textwrap
opts={'width':75, 'initial_indent':indent,'subsequent_indent':indent}
def numbercommaspace(i,width=4): return ('%i,'%i).ljust(width)
y=[ textwrap.fill(''.join([ '%s+%s'%(v[0],numbercommaspace(i)) for i in range(v[1])]),**opts) for v in vars]
print('\ncnt[0] = sscanf (str,fmt,\n'+indent+'msgId,')
print('\n'.join(y)[:-1]+');')
print('cntExpected[0] = '+str(sum([v[1] for v in vars])+1)+';')

*/
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
