// created by JM 2012

      

#ifndef __KINOBJECT_H__
#define __KINOBJECT_H__
/*---------------------------------------------------------------------------*/

#include <string>
#include "Vector3d.h"
#include "Quaternion.h"

enum UpdateDirection {
   kAll,
   kSelfOnly,
   kSelfParent,
   kSelfChildren
};

class KinListItem;

/*---------------------------------------------------------------------------*/
class KinObject {
   public:
      enum ObjectType {
         kPoint,
         kPointAxis,
         kLever
      };
      


      KinObject( void );

	   KinObject(
         const ObjectType inType,
         const std::string& inName);

      //virtual ~KinObject();

      virtual void Update(const UpdateDirection inUpdateDirection);
      
      void UpdateChildren(const UpdateDirection inUpdateDirection);

      void Print();

      void AppendChild( KinObject* inChild  );

      void ResetUpdate();
      
      
      std::string  mName;
      ObjectType   mType;
      bool         mIsUpdated;
      KinListItem* mChildren;
      KinListItem* mParents;
      KinObject*   mParent;
      Vector3d     mPos;
      Quaternion   mQuatAbs;

     
      //std::string  mParentName;



   private:



};


/*---------------------------------------------------------------------------*/
class KinListItem  {
public:
   KinListItem( KinObject* inCurrent);

   KinObject* CurrentObject;

   KinListItem* NextListItem;
};
#endif
