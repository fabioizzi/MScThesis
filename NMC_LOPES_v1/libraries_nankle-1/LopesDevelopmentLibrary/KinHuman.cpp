//#include "FDefines.h"
#include <string>

#include "KinHuman.h"

/*---------------------------------------------------------------------------*/





/*---------------------------------------------------------------------------*/
KinHuman::KinHuman()
{
   //Define Human points & axes
   // X = FORWARD, Y = UPWARD, Z = RIGHT


   //Define the Pelvis points and axes

   mHumanBase              = new KinPointAxis("Base", NULL);
   mPelvisMidAxial         = new KinPointAxis("Pelvis Mid + Axial", mHumanBase, EY, E0, true);
   mPelvisMidFrontal       = new KinPointAxis("Pelvis Mid + Frontal", mPelvisMidAxial, EX);
   mPelvisCoM              = new KinPointAxis("Pelvis CoM", mPelvisMidFrontal);
   
   mLeftHipAbduction       = new KinPointAxis("Left Hip Abduction", mPelvisMidFrontal, EX, E0, true);
   mLeftHipFlexion         = new KinPointAxis("Left Hip Flexion", mLeftHipAbduction, EZ);
   mLeftHipEndorotation    = new KinPointAxis("Left Hip Endorotation", mLeftHipFlexion, -EY);
   
   mLeftKneeFlexion        = new KinPointAxis("Left Knee Flexion", mLeftHipEndorotation, -EZ);
   
   mLeftFootEndorotation   = new KinPointAxis("Left Foot Endorotation", mLeftKneeFlexion, -EY, E0, true);
   mLeftFootPlantarflexion = new KinPointAxis("Left Foot Plantarflexion", mLeftFootEndorotation, -EZ);
   mLeftFootInversion      = new KinPointAxis("Left Foot Inversion", mLeftFootPlantarflexion, -EX);
   mLeftToe                = new KinPointAxis("Left Toe", mLeftFootInversion, E0);
   mLeftHeel               = new KinPointAxis("Left Heel", mLeftFootInversion, E0);

   mRightHipAbduction      = new KinPointAxis("Right Hip Abduction", mPelvisMidFrontal, -EX, E0, true);
   mRightHipFlexion        = new KinPointAxis("Right Hip Flexion", mRightHipAbduction, EZ);
   mRightHipEndorotation   = new KinPointAxis("Right Hip Endorotation", mRightHipFlexion, EY);

   mRightKneeFlexion       = new KinPointAxis("Right Knee Flexion", mRightHipEndorotation, -EZ);
   
   mRightFootEndorotation  = new KinPointAxis("Right Foot Endorotation", mRightKneeFlexion, EY, E0, true);
   mRightFootPlantarflexion= new KinPointAxis("Right Foot Plantarflexion", mRightFootEndorotation, -EZ);
   mRightFootInversion     = new KinPointAxis("Right Foot Inversion", mRightFootPlantarflexion, EX);
   mRightToe               = new KinPointAxis("Right Toe", mRightFootInversion, E0);
   mRightHeel              = new KinPointAxis("Right Heel", mRightFootInversion, E0);

}


/*---------------------------------------------------------------------------*/
KinHuman::~KinHuman() {

}

/*---------------------------------------------------------------------------*/
int KinHuman::TransformHuman2Cartesian() {
   return 0;
}



 void KinHuman::UpdateDimensions()
// --------------------------------------------------------------------
{
   // Applies the dimensions set in the global parameters to the kinematic
   // structure as defined in mHumanPoints (modify the refPos per point)

   // PM position of toe and heel is now a percentage of foot length, related to ankle pos
   // heel should be fixed relative from ankle pos, toe should be foot length from heel
   // change when exact dims are known

   //mPelvisMidAxial         ->mRefPos = Vector3d(0.0,
   //   mLengthThighLeft + mLengthShankLeft + mHeightFootLeft, 0.0); //absolute
   //mHumanBase              ->mRefPos = Vector3d(0.0,
   //   mLengthThighLeft + mLengthShankLeft + mHeightFootLeft, 0.0); //absolute
   mHumanBase              ->mRefPos = Vector3d(0.0, 0.0, 0.0);
   mPelvisCoM              ->mRefPos = Vector3d(0.0, mHeightPelvis, 0.0); // from pelvis mid

   mLeftHipAbduction       ->mRefPos = Vector3d(0.0, 0.0, -0.5*mWidthPelvis); //from pelvis mid
   mLeftKneeFlexion        ->mRefPos = Vector3d(0.0, -1.0*mLengthThighLeft, 0.0); //from hip
   mLeftFootEndorotation   ->mRefPos = Vector3d(0.0, -1.0*mLengthShankLeft, 0.0); //from knee
   mLeftToe                ->mRefPos = Vector3d(0.8*mLengthFootLeft, -1.0*mHeightFootLeft, 0.0); //from ankle
   mLeftHeel               ->mRefPos = Vector3d(-0.2*mLengthFootLeft, -1.0*mHeightFootLeft, 0.0); //from ankle

   mRightHipAbduction      ->mRefPos = Vector3d(0.0, 0.0, +0.5*mWidthPelvis); //from pelvis mid
   mRightKneeFlexion       ->mRefPos = Vector3d(0.0, -1.0*mLengthThighRight, 0.0); //from hip
   mRightFootEndorotation  ->mRefPos = Vector3d(0.0, -1.0*mLengthShankRight, 0.0); //from knee
   mRightToe               ->mRefPos = Vector3d(0.8*mLengthFootRight, -1.0*mHeightFootRight, 0.0); //from ankle
   mRightHeel              ->mRefPos = Vector3d(-0.2*mLengthFootRight, -1.0*mHeightFootRight, 0.0); //from ankle

 
 }

void KinHuman::SetDebugDimensions()
// define human dimensions. not realistic (asymmetry) for debugging only
{
   mMassPatient = 80.0;
   mLengthPatient = 1.8;
   mWidthPelvis = 0.35;
   mHeightPelvis = 0.2;
   mLengthThighLeft = 0.6;
   mLengthThighRight = 0.61;
   mLengthShankLeft = 0.55;
   mLengthShankRight = 0.53;
   mLengthFootLeft = 0.3;
   mLengthFootRight = 0.28;
   mHeightFootLeft = 0.1;
   mHeightFootRight = 0.11;
}

void KinHuman::SetInputPosAngleVector(const double inInputPosAngle[19])
{
   

   mPelvisPos = Vector3d(inInputPosAngle[0], inInputPosAngle[1], inInputPosAngle[2]);
   mPelvisAxialAngle = inInputPosAngle[3];
   mPelvisFrontalAngle = inInputPosAngle[4];
   mLeftHipAbductionAngle = inInputPosAngle[5];
   mLeftHipFlexionAngle = inInputPosAngle[6];
   mLeftHipEndorotationAngle = inInputPosAngle[7];
   mLeftKneeFlexionAngle = inInputPosAngle[8];
   mLeftFootEndorotationAngle = inInputPosAngle[9];
   mLeftFootPlantarflexionAngle = inInputPosAngle[10];
   mLeftFootInversionAngle = inInputPosAngle[11];
   mRightHipAbductionAngle = inInputPosAngle[12];
   mRightHipFlexionAngle = inInputPosAngle[13];
   mRightHipEndorotationAngle = inInputPosAngle[14];
   mRightKneeFlexionAngle = inInputPosAngle[15];
   mRightFootEndorotationAngle = inInputPosAngle[16];
   mRightFootPlantarflexionAngle = inInputPosAngle[17];
   mRightFootInversionAngle = inInputPosAngle[18];
}

void KinHuman::Update()
{
   // Pass the rotation values to the KinPointAxis instances
   
   mPelvisMidAxial->SetAngle(mPelvisAxialAngle);
   mPelvisMidFrontal->SetAngle(mPelvisFrontalAngle);

   mLeftHipAbduction->SetAngle(mLeftHipAbductionAngle);
   mLeftHipFlexion->SetAngle(mLeftHipFlexionAngle);
   mLeftHipEndorotation->SetAngle(mLeftHipEndorotationAngle);
      
   mLeftKneeFlexion->SetAngle(mLeftKneeFlexionAngle);
         
   mLeftFootEndorotation->SetAngle(mLeftFootEndorotationAngle);
   mLeftFootPlantarflexion->SetAngle(mLeftFootPlantarflexionAngle);
   mLeftFootInversion->SetAngle(mLeftFootInversionAngle);

   mRightHipAbduction->SetAngle(mRightHipAbductionAngle);
   mRightHipFlexion->SetAngle(mRightHipFlexionAngle);
   mRightHipEndorotation->SetAngle(mRightHipEndorotationAngle);
      
   mRightKneeFlexion->SetAngle(mRightKneeFlexionAngle);
         
   mRightFootEndorotation->SetAngle(mRightFootEndorotationAngle);
   mRightFootPlantarflexion->SetAngle(mRightFootPlantarflexionAngle);
   mRightFootInversion->SetAngle(mRightFootInversionAngle);
   

   mHumanBase->SetBasePos(mPelvisPos);
   mHumanBase->Update(kSelfChildren);


}

void KinHuman::SetOutputCartesian()
{
   mPosCartesian[0]  = mPelvisMidAxial->mPos;
   mPosCartesian[1]  = mPelvisCoM->mPos;
   mPosCartesian[2]  = mLeftHipAbduction->mPos;
   mPosCartesian[3]  = mLeftKneeFlexion->mPos;
   mPosCartesian[4]  = mLeftFootEndorotation->mPos;
   mPosCartesian[5]  = mLeftToe->mPos;
   mPosCartesian[6]  = mLeftHeel->mPos;
   mPosCartesian[7]  = mRightHipAbduction->mPos;
   mPosCartesian[8]  = mRightKneeFlexion->mPos;
   mPosCartesian[9]  = mRightFootEndorotation->mPos;
   mPosCartesian[10] = mRightToe->mPos;
   mPosCartesian[11] = mRightHeel->mPos;

}


