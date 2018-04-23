/* KinHuman_common.cpp
 *
 * Common functions that are needed both for compiling for Simulink (Level 2 S function)
 * and Matlab Command Line (mex function).
 *
 * Note: VECTOR_SIZE and N_OUTPUT_POINTS are also in other cpp functions!
 */

#include "KinHuman.h"
#define VECTOR_SIZE (3)
#define N_OUTPUT_POINTS_REDUCED (9) /* The number of 3d-points in the output */
#define N_OUTPUT_POINTS_FULL (11) /* The number of 3d-points in the output */

#ifndef real_T
typedef double real_T;
#endif

void UpdatePatientDimensions(KinHuman* KH, const real_T *patientDimensions)
{
    KH->mMassPatient      = patientDimensions[ 0];
    KH->mLengthPatient    = patientDimensions[ 1];
    KH->mWidthPelvis      = patientDimensions[ 2];
    KH->mHeightPelvis     = patientDimensions[ 3];
    KH->mLengthThighLeft  = patientDimensions[ 4];
    KH->mLengthThighRight = patientDimensions[ 5];
    KH->mLengthShankLeft  = patientDimensions[ 6];
    KH->mLengthShankRight = patientDimensions[ 7];
    KH->mLengthFootLeft   = patientDimensions[ 8];
    KH->mLengthFootRight  = patientDimensions[ 9];
    KH->mHeightFootLeft   = patientDimensions[10];
    KH->mHeightFootRight  = patientDimensions[11];
    KH->UpdateDimensions();
}

void CopyCartesianPositions(KinHuman* KH, real_T *cartesianPositions)
{
    // We copy the positions one-by-one to the output vector. Use this
    // function to see which element is which. Note that this function
    // does something different than the function within KinHuman.cpp;
    // this one is tailored towards usage with my own CartesianPositionBus, having
    // pPelvis
    // pLeftHip
    // pLeftKnee
    // pLeftAnkle
    // pLeftHeel
    // pLeftToe
    // pRightHip
    // pRightKnee
    // pRightAnkle
    // pRightHeel
    // pRightToe
    
    //KH->mPelvisMidAxial       ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*0)); // Note used in the HLC model
    KH->mPelvisCoM            ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*0));
    KH->mLeftHipAbduction     ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*1));
    KH->mLeftKneeFlexion      ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*2));
    KH->mLeftFootEndorotation ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*3));// Ankle
    KH->mLeftHeel             ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*4));
    KH->mLeftToe              ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*5));
    
    KH->mRightHipAbduction    ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*6));
    KH->mRightKneeFlexion     ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*7));
    KH->mRightFootEndorotation->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*8)); // Ankle
    KH->mRightHeel            ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*9));
    KH->mRightToe             ->mPos.copyTo(cartesianPositions+(VECTOR_SIZE*10));
}

real_T ForceOneFootOnFloor(real_T *cartesianPositions, int N)
{
    // determines the minimum y-value of all points and then subtracts this amount
    // from all y-values. The effect is that the model now 'rests' on the floor:
    // at least one of the points is at y=0 and no points are at y<0.
    //
    // Returns the original minimum (which is convenient for determining an
    // appropriate PY.
    real_T y;
    
    real_T minimum = cartesianPositions[0+1];
    for (int i=1; i<N;i++) // Skip 0; we did that with initialization of minimum
    {
        y = cartesianPositions[i*VECTOR_SIZE+1];
        if (y <minimum) minimum = y;
    }
    for (int i=0; i<N;i++)
    {
        cartesianPositions[i*VECTOR_SIZE+1] -= minimum;
    }
    
    return minimum;
}
