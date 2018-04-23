//#include "FDefines.h"
#include <string>

#include "KinPointAxis.h"


/*---------------------------------------------------------------------------*/
KinPointAxis::KinPointAxis(
             const std::string& inName,
             KinObject* inParent,
             const Vector3d& inRefDir, 
             const Vector3d& inRefPos,
             bool inAxisGrounded)
 : KinObject(kPointAxis, inName)
 , mName(inName)
 , mRefDir(inRefDir)
 , mRefPos(inRefPos)
 , mIsAxisGrounded(inAxisGrounded)

{
	mAngle = 0.0;
   mDir = Vector3d(0.0, 0.0, 0.0);
   mPos = Vector3d(0.0, 0.0, 0.0);

   if (inParent != NULL) {
      this->mParent = inParent;
      inParent->AppendChild(this);
   }
   mChildren = NULL;
}

void KinPointAxis::SetRefDir(const Vector3d& inRefDir)
{
   mRefDir = inRefDir;
}

void KinPointAxis::SetRefPos(const Vector3d& inRefPos)
{
   mRefPos = inRefPos;
}

void KinPointAxis::SetAxisGrounded(bool inBool)
{
   mIsAxisGrounded = inBool;
}

void KinPointAxis::SetAngle(double inAngle)
{
   mAngle = inAngle;
   mQuatRel = Quaternion( mRefDir, mAngle);
   if ((mParent == NULL)|(mIsAxisGrounded)) {
      mQuatAbs = mQuatRel;
   }
   else //dependent on parentquaternion
   {
      if (mParent->mType==kPointAxis)
         mQuatAbs = mParent->mQuatAbs * mQuatRel;
      else
         mQuatAbs = mQuatRel;
   }

}

void KinPointAxis::Translate(const Vector3d& inPos)
{
   mPos += inPos;
}

void KinPointAxis::SetBasePos(const Vector3d& inPos)
{
   mPos = inPos + mRefPos;
}


void KinPointAxis::Update(const UpdateDirection inUpdateDirection)
{
   // KinPointAxis consists of a point and an axis through that point
   // A KinPointAxis is connected to a parentpointaxis.
   // First calculate the point by taking the parent position and quaternion
   // Then update it's own abolute quaternion.
   // At the end update all the children of the KinPointAxis

   // Check if object has parent and if they require updating
   Vector3d mPosBase;

   bool updateParent = (inUpdateDirection==kAll)|(inUpdateDirection==kSelfParent);
   if (mParent!=NULL)
   {
      if ((!mParent->mIsUpdated)&updateParent)
      {
         printf("My parent is not updated\n");
         printf("start update my parent [\n");
         //mParentPointAxis->Update(kSelfParent);
         //mParentPointAxis->Update(inUpdateDirection);
         mParent->Update(inUpdateDirection);
         printf("end update my parent ]\n");
      }

      // Start the self update routine
      mPosBase = mParent->mPos;
      if (mParent->mType==kPointAxis)
      {
         mPos = QVecRot(mParent->mQuatAbs, mRefPos) + mPosBase;
         // Update the absolute quaternion
         if (mIsAxisGrounded) {// independent on parentquaternion
            mQuatAbs = mQuatRel;
         }
         else //dependent on parentquaternion
         {
            mQuatAbs = mParent->mQuatAbs * mQuatRel;
         }
      }
      else
      {
         mPos = mRefPos +mPosBase;
         mQuatAbs = mQuatRel;
      }


   }
   else //No parentpointaxis 
   {
      // Update the absolute quaternion
      mQuatAbs = mQuatRel;
   }

   // Don't know if this part is necessary, it is required when the axes must be plotted
   mDir = QVecRot(mQuatAbs, mRefDir);

   mIsUpdated = true;
   // End of the self update

   // Update the Children
   if ((inUpdateDirection==kAll)|(inUpdateDirection==kSelfChildren))
      UpdateChildren(inUpdateDirection);

}


/*---------------------------------------------------------------------------*/
