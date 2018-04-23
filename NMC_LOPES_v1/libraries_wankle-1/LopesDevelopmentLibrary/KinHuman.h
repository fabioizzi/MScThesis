// created by JM 2012

      

#ifndef __KINHUMAN_H__
#define __KINHUMAN_H__
/*---------------------------------------------------------------------------*/

#include <string>
#include "Quaternion.h"
#include "vector3d.h"    
//#include "KinAxis.h"
//#include "KinPoint.h"
#include "KinPointAxis.h"
#include "KinObject.h"

// Unit Vectors, for rotation and translation
const Vector3d EX = Vector3d(1.0, 0.0, 0.0);
const Vector3d EY = Vector3d(0.0, 1.0, 0.0);
const Vector3d EZ = Vector3d(0.0, 0.0, 1.0);
const Vector3d E0 = Vector3d(0.0, 0.0, 0.0);


class KinHuman {
public:
   KinHuman();

   //KinHuman(const KinHuman &inKinHuman);

   ~KinHuman();


   int TransformHuman2Cartesian();

   void UpdateDimensions();

   void SetDebugDimensions();

   void SetInputPosAngleVector(const double inInputPosAngle[19]);

   void Update();

   void SetOutputCartesian();


public:
   //KinAxis*           mHumanAxes[16];
   //KinPoint*          mHumanPoints[12];
   double             mInputPosAngle[19];
   Vector3d           mPelvisPos;
   double             mPelvisAxialAngle;
   double             mPelvisFrontalAngle;
   double             mLeftHipAbductionAngle;
   double             mLeftHipFlexionAngle;
   double             mLeftHipEndorotationAngle;
   double             mLeftKneeFlexionAngle;
   double             mLeftFootEndorotationAngle;
   double             mLeftFootPlantarflexionAngle;
   double             mLeftFootInversionAngle;
   double             mRightHipAbductionAngle;
   double             mRightHipFlexionAngle;
   double             mRightHipEndorotationAngle;
   double             mRightKneeFlexionAngle;
   double             mRightFootEndorotationAngle;
   double             mRightFootPlantarflexionAngle;
   double             mRightFootInversionAngle;




   Vector3d           mPosCartesian[12];

   KinPointAxis*      mHumanBase;
   KinPointAxis*      mPelvisMidAxial;
   KinPointAxis*      mPelvisMidFrontal;
   KinPointAxis*      mPelvisCoM;
   KinPointAxis*      mLeftHipAbduction;
   KinPointAxis*      mLeftHipFlexion;
   KinPointAxis*      mLeftHipEndorotation;
   
   KinPointAxis*      mLeftKneeFlexion;
   
   KinPointAxis*      mLeftFootEndorotation;
   KinPointAxis*      mLeftFootPlantarflexion;
   KinPointAxis*      mLeftFootInversion;
   KinPointAxis*      mLeftToe;
   KinPointAxis*      mLeftHeel;

   KinPointAxis*      mRightHipAbduction;
   KinPointAxis*      mRightHipFlexion;
   KinPointAxis*      mRightHipEndorotation;

   KinPointAxis*      mRightKneeFlexion;
   
   KinPointAxis*      mRightFootEndorotation;
   KinPointAxis*      mRightFootPlantarflexion;
   KinPointAxis*      mRightFootInversion;
   KinPointAxis*      mRightToe;
   KinPointAxis*      mRightHeel;


   
   // patient dimensions
   double    mMassPatient;
   double    mLengthPatient;
   double    mWidthPelvis;
   double    mHeightPelvis;
   double    mLengthThighLeft;
   double    mLengthThighRight;
   double    mLengthShankLeft;
   double    mLengthShankRight;
   double    mLengthFootLeft;
   double    mLengthFootRight;
   double    mHeightFootLeft;
   double    mHeightFootRight;

      

   private:



};
/*
class KinHumanInterfaceNode : public InterfaceNode
{
public:
   KinHumanInterfaceNode( InterfaceNode* inParentNode,
                          const std::string& inName,
                          KinHuman* inKinHuman);
private:
   KinHuman* mKinHuman;
};
*/

/*---------------------------------------------------------------------------*/
#endif
