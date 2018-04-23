/*
 * KinHuman_function.cpp
 * 
 * This file is there to make a script-callable function from KinHuman.
 *
 * BEFORE USING THIS FILE IN AN S-FUNCTION, COMPILE IT WITHIN MATLAB BY TYPING:
 *
 *  mex KinHuman_function.cpp KinHuman_common.cpp KinHuman.cpp KinObject.cpp KinPointAxis.cpp
 *
 */

#include "mex.h"

#include "KinHuman.h"
#define VECTOR_SIZE (3)
#define N_OUTPUT_POINTS_FULL (11) /* The number of 3d-points in the output */

// Definition of functions (I don't want to spend an entier .h file on it)
void UpdatePatientDimensions(KinHuman* KH, const real_T *patientDimensions);
void CopyCartesianPositionsFull(KinHuman* KH, real_T *cartesianPositions);
real_T ForceOneFootOnFloor(real_T *cartesianPositions, int N);

extern void _main();

char errorMsg[255];
void AssertVector(const mxArray *x,int size, const char *name)
{
    // Generates an error message if x is not a vector of the given size.
    // Variable name can contain an identifier for the argument, used in the error message
    if (!mxIsDouble(x))
    {
        sprintf(errorMsg,"%s is not of type double.",name);
        mexErrMsgIdAndTxt("MATLAB:mexcpp:argumentError", errorMsg);
    }
    
    const mwSize *dims;
    mwSize nd= mxGetNumberOfDimensions(x);
    dims = mxGetDimensions(x);
    if (! ((nd==1 && dims[0]==size) || (nd==2 && dims[0]==1 && dims[1]==size) || (nd==2 && dims[0]==size && dims[1]==1)) )
    {
        sprintf(errorMsg,"%s is not a vector with %d elements.",name,size);
        mexErrMsgIdAndTxt("MATLAB:mexcpp:argumentError", errorMsg);
    }
}

/* Main Function.
 *
 * Inputs:
 *   PatientParameters: a 12 D vector holding all patient parameters, or [] for default parameters
 *    [mass, length, pelvisWidth, pelvisHeight, upperLegLength, upperLegLength, lowerLegLength, lowerLegLength, footLength, footLength, footHeight, footHeight];
 *   Theta: A 19D vector holding the joint angles:
 *      [PX, PY, PZ, PAX, POB, LHA, LHF, LHE, LKF, LAE, LAP, LAI, RHA, RHF, RHE, RKF, RAE, RAP, RAI] 
 *   [forceOneFootOnFloor]: if present and nonzero, it lifts the model such that one point is on the floor.
 * Outputs:
 *   Coords: A 3x9 matrix holding the positions of all points of the body (each column is one point)
 *   [PY_new]: optional, the value for PY which puts one foot on the floor (if Force... is true); else PY.
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs,const mxArray *prhs[])
{
   /* Check for proper number of arguments */

  if (nrhs != 2 && nrhs!=3) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", 
            "Wrong number of input parameters (must be 2 or 3) Usage: [C,PY] = KinHuman_function(PatientParameters,Theta,[ForceOneFootOnGround])");
  } else if (nlhs !=1 && nlhs!=2) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout", 
            "Wrong number of output parameters (must be 1 or 2) Usage: [C] = KinHuman_function(PatientParameters,Theta,[ForceOneFootOnGround]) or [C,PY_new] = ...");
  }

  bool UseDefaultParameters;
  if (mxGetNumberOfElements(prhs[0])==0)
  {
      UseDefaultParameters=true;
  } else
  {
    AssertVector(prhs[0],12,"Input argument 1 (PatientDimensions)");
    UseDefaultParameters=false;
  }
  AssertVector(prhs[1],19,"Input argument 2 (JointAngles)");
  
  // Parse input arguments
  double *patientDimensions = mxGetPr(prhs[0]);
  double *jointAngles = mxGetPr(prhs[1]);
  bool forceOneFootOnFloor;
  if (nrhs==3) forceOneFootOnFloor = ( *mxGetPr(prhs[2]) != 0); else forceOneFootOnFloor = false;
  
  // Prepare output argument 1
  plhs[0] = mxCreateNumericMatrix(3, N_OUTPUT_POINTS_FULL, mxDOUBLE_CLASS, mxREAL);
  double *cartesianPositions = mxGetPr(plhs[0]);
  
  // DO THE WORK
  KinHuman *KH = new KinHuman;
  double minimum;
  if (UseDefaultParameters)
  {
      KH->SetDebugDimensions();
      KH->UpdateDimensions();
  }
  else UpdatePatientDimensions(KH, patientDimensions);
  KH->SetInputPosAngleVector(jointAngles);
  KH->Update();
  CopyCartesianPositionsFull(KH,cartesianPositions);
    
  if (forceOneFootOnFloor)
  {
      minimum = ForceOneFootOnFloor(cartesianPositions, N_OUTPUT_POINTS_FULL);
  } else minimum=0;

  // Optional output argument 2
  if (nlhs==2)
  {
      plhs[1] = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
      double *PY_out = mxGetPr(plhs[1]);
      *PY_out = jointAngles[1] - minimum;;
  }
  return;
}
