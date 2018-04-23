//#include "FDefines.h"
#include <string>

#include "KinObject.h"


/*---------------------------------------------------------------------------*/

KinObject::KinObject( void )
{}

/*---------------------------------------------------------------------------*/
KinObject::KinObject(const ObjectType inType,
                               const std::string& inName )
 : mType(inType)
 , mName(inName)
{
   mIsUpdated = false;
   mPos = Vector3d(0.0, 0.0, 0.0);
   mQuatAbs = Quaternion(0.0, 0.0, 0.0, 1.0);
   mParent = NULL;
   

}

/*---------------------------------------------------------------------------*/
//KinObject::~KinObject() {
//
//}



/*---------------------------------------------------------------------------*/
void KinObject::Update(const UpdateDirection inUpdateDirection)
{
   // obsolete, update is taken in the childs' classes
}

/*---------------------------------------------------------------------------*/
void KinObject::UpdateChildren(const UpdateDirection inUpdateDirection)
{
   KinListItem* currentChild = mChildren; 
   while( currentChild != NULL )  {
      
      currentChild->CurrentObject->Update(inUpdateDirection);
      currentChild = currentChild->NextListItem;
   }
}

/*---------------------------------------------------------------------------*/
//void KinObject::UpdateParent(KinObject inObject)

/*---------------------------------------------------------------------------*/
void KinObject::Print()
{
   std::string mystr;
   
   printf(" \n");
   mystr = this->mName;
   printf("My Name %s\n",mystr.c_str());
  
/*   if (mParentName=="")
      mystr = "No Parent";
   else
      mystr = this->mParentName;
   printf("  My ParentName %s\n", mParentName.c_str());
*/
   
}

/*---------------------------------------------------------------------------*/
void KinObject::AppendChild( KinObject* inChild  )
{
	//  find the end of the list to append to, list item NULL
	KinListItem* myLastChild = mChildren;

   if ( myLastChild == NULL) { // No children yet
      mChildren = new KinListItem( inChild );
   }
   else
   { // Seek the last child
	   while ( myLastChild->NextListItem != NULL  ) 
		   {	myLastChild = myLastChild->NextListItem; }; // not protected, oh well
	   //  append the new item to Point's list of childre
      myLastChild->NextListItem = new KinListItem(inChild);
     
   }

}
/*---------------------------------------------------------------------------*/
void KinObject::ResetUpdate()
// Sets mIsUpdated to false for itself and its Children
{
   mIsUpdated = false;
   KinListItem* currentChild = mChildren; 
   while( currentChild != NULL )  {
      
      currentChild->CurrentObject->ResetUpdate();
      currentChild = currentChild->NextListItem;
   }
}


KinListItem::KinListItem( KinObject* inCurrent)
{
   CurrentObject = inCurrent;
   NextListItem = NULL;
}
