// created by JM 2012

      

#ifndef __KINPOINTAXIS_H__
#define __KINPOINTAXIS_H__
/*---------------------------------------------------------------------------*/

#include <string>
#include "Quaternion.h"
#include "vector3d.h"            // for vector use in QVecRot
#include "KinObject.h"



//class KinListItem;


/*---------------------------------------------------------------------------*/
class KinPointAxis : public KinObject
{
   public:
      KinPointAxis(
         const std::string& inName,
         KinObject* inParent = NULL,
         const Vector3d& inRefDir = Vector3d(0.0, 0.0, 0.0), 
         const Vector3d& inRefPos = Vector3d(0.0, 0.0, 0.0),
         bool inAxisGrounded = false);
         
      //virtual ~KinPointAxis();
      ~KinPointAxis();


      void SetRefPos(const Vector3d& inRefDir);

      void SetRefDir(const Vector3d& inRefPos);

      void SetAxisGrounded(bool inBool);

      void SetAngle(double inAngle);
      
      void Translate(const Vector3d& inPos);

      void SetBasePos(const Vector3d& inPos);

      virtual void Update(const UpdateDirection inUpdateDirection);


      void PrintSelf();


	 

      std::string    mName;
      Vector3d       mRefPos;
      //Vector3d       mPos;
      
      Vector3d	      mRefDir;
      Vector3d       mDir;
      double         mAngle;
      Quaternion     mQuatRel;
      bool           mIsAxisGrounded;


   private:


};



/*---------------------------------------------------------------------------*/
#endif
