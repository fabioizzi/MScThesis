//*********************************************************************
// Copyright © 2008 Fokker Control Systems B.V.
//*********************************************************************
//
// file    : Quaternion.h
// purpose : Unit quaternion struct
// usage   : Used for orientation and rotation calculations
//
// --------------------------------------------------------------------
//  2009-08-16 NB 1.0 1 changed implementation of invert method
//  2008-08-16 PL 1.0 0 created
// --------------------------------------------------------------------
// History logging by RCS
//*********************************************************************

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "math.h"
#include "vector3d.h"            // for vector use in QVecRot
// #include "X3DRotation.h"
// struct    X3DRotation;

//---------------------------------------------------------------------
//    struct Quaternion
//---------------------------------------------------------------------

struct Quaternion
{
   // quaternion fields
   // try to map the first three on a vector v,
   // the fourth on a scalar w
   double q1, q2, q3, q4;

   // -----------------------------------------------------------------
   // constructors
   // -----------------------------------------------------------------

   Quaternion( void )
   {
      q1 = 0.0;
      q2 = 0.0;
      q3 = 0.0;
      q4 = 1.0;
   }

   Quaternion( const Quaternion &inQuat )
   {
      q1 = inQuat.q1;
      q2 = inQuat.q2;
      q3 = inQuat.q3;
      q4 = inQuat.q4;
   }

   Quaternion( const double inq1,
               const double inq2,
               const double inq3,
               const double inq4 )
   {
      q1 = inq1;
      q2 = inq2;
      q3 = inq3;
      q4 = inq4;
   }

   Quaternion( const Vector3d inVec, double inAngle )
   {
      Vector3d tempVec = inVec;
      if ( tempVec.normalize() )  {
         double sinHalf = sin( 0.5 * inAngle );
         double cosHalf = cos( 0.5 * inAngle );
         q1 = sinHalf * tempVec.x;
         q2 = sinHalf * tempVec.y;
         q3 = sinHalf * tempVec.z;
         q4 = cosHalf;
      }  else { 
         neutralize();
      }
   }

/*

   TODO - solve interdenpency problem,
          forward declaration does not seem to work.

   Quaternion( const X3DRotation inRot )
   {
      Vector3d v = inRot.axis;
      if ( v.normalize() )  {
         double sinHalf = sin( 0.5 * inRot.angle );
         double cosHalf = cos( 0.5 * inRot.angle );
         q1 = sinHalf * v.x;
         q2 = sinHalf * v.y;
         q3 = sinHalf * v.z;
         q4 = cosHalf;
      }  else neutralize();
   }
*/
   // -----------------------------------------------------------------
   // note:
   //    Assignment between vectors with the = operator is
   //    member by member. This is an automatic compiler default in C++.
   // -----------------------------------------------------------------

   // -----------------------------------------------------------------
   // cast to a double* (array)
   // -----------------------------------------------------------------

   operator double* ()
   {
      return &q1;
   }

   operator const double* () const
   {
      return (const double*) &q1;
   }

   // -----------------------------------------------------------------
   // assigment (element copy) from and to array
   // -----------------------------------------------------------------

   inline void operator=( const double inA[4] ) {
      q1 = inA[0];
      q2 = inA[1];
      q3 = inA[2];
      q4 = inA[3];
   }

   inline void operator=( const float inA[4] ) {
      q1 = inA[0];
      q2 = inA[1];
      q3 = inA[2];
      q4 = inA[3];
   }

   inline void copyTo( double outA[4] ) {
      outA[0] = q1;
      outA[1] = q2;
      outA[2] = q3;
      outA[3] = q4;
   }

   inline void copyTo( float outA[4] ) {
      outA[0] = static_cast<float>(q1);
      outA[1] = static_cast<float>(q2);
      outA[2] = static_cast<float>(q3);
      outA[3] = static_cast<float>(q4);
   }

   // -----------------------------------------------------------------
   // array-like element referencing
   // -----------------------------------------------------------------

   inline double &operator[]( int i ) {
      if( i <= 0 ) return q1;
      if( i == 1 ) return q2;
      if( i == 2 ) return q3;
      return q4;
   }

   inline const double &operator[]( int i ) const {
      if( i <= 0 ) return q1;
      if( i == 1 ) return q2;
      if( i == 2 ) return q3;
      return q4;
      }

   // -----------------------------------------------------------------
   // length and norm
   // -----------------------------------------------------------------

   inline double lengthSq() {
      return q1*q1 + q2*q2 + q3*q3+ q4*q4;
   }

   inline double length() {
      return sqrt( q1*q1 + q2*q2 + q3*q3 + q4*q4 );
   }

   inline bool normalizeFromLength( const double inLength ) {
      if ( inLength <= 0.0 ) {
         return false;
      }
      q1 /= inLength;
      q2 /= inLength;
      q3 /= inLength;
      q4 /= inLength;
      return true;
   }

   inline bool normalize() {
      double length = sqrt( q1*q1 + q2*q2 + q3*q3 + q4*q4 );
      if ( length == 0.0 )  {
         return false;
      }
      q1 /= length;
      q2 /= length;
      q3 /= length;
      q4 /= length;
      return true;
   }

   inline double normalizeReturnLength() {
      double lengthSq = q1*q1 + q2*q2 + q3*q3+ q4*q4;
      if ( lengthSq <= 0.0 ) {
         return 0.0;
      }
      double length = sqrt( lengthSq );
      q1 /= length;
      q2 /= length;
      q3 /= length;
      q4 /= length;
      return length;
   }

//   inline double normalizeCheap() {
      // TODO - renormalize with approximate equation for small creep
//      normalize();
//   }

   inline void neutralize() {
      q1 = 0.0;
      q2 = 0.0;
      q3 = 0.0;
      q4 = 1.0;
   }

   inline void invert() {
      q1 =  -q1;
      q2 =  -q2;
      q3 =  -q3;
   }


   inline void Set( const Vector3d inVec, const double inAngle ) {
      Vector3d tempVec = inVec;
      if ( tempVec.normalize() )  {
         double sinHalf = sin( 0.5 * inAngle );
         double cosHalf = cos( 0.5 * inAngle );
         q1 = sinHalf * tempVec.x;
         q2 = sinHalf * tempVec.y;
         q3 = sinHalf * tempVec.z;
         q4 = cosHalf;
      }  else { 
         neutralize();
      }
   }
};


// end of struct Quaternion
// --------------------------------------------------------------------

//---------------------------------------------------------------------
//
//    OVERLOADED OPERATORS
//
// note:
//    All of these operators *return* results (via the stack).
//    Hopefully this does not hurt performance too much.
//    For inline assigmnents see code inside the struct, above.
//
// note2:
//    Only multiplication operators.
//    Most other operators would only be misleading when used with a
//    unit quaternion. If necessary, they can be don element by element.
//    Intentionally *not* supported are :
//    - adding unit quaternions.
//    - multiplying unit quaternions by a real scalar.
//    - unary minus
//---------------------------------------------------------------------


inline bool operator==( Quaternion &inQ1,
                        Quaternion &inQ2 ) {
   return (
         ( inQ1.q1 == inQ2.q1 )
      && ( inQ1.q2 == inQ2.q2 )
      && ( inQ1.q3 == inQ2.q3 )
      && ( inQ1.q4 == inQ2.q4 ) );
}


//---------------------------------------------------------------------
// Quaternion product
// note :
// Order of quaternions is very relevant, qA*qB <> qB*qA
// But order of evaluation does not matter, so code like :
//    qD = qA * qB * qC
// is always OK, no matter whether it is evaluated as
// qD = ( qA * qB ) * qC  or as qD = qA * ( qB * qC ).
//---------------------------------------------------------------------

inline Quaternion operator*( const Quaternion &inQ1,
                             const Quaternion &inQ2 )
{
   return Quaternion (
        inQ1.q1 * inQ2.q4
      + inQ1.q2 * inQ2.q3
      - inQ1.q3 * inQ2.q2
      + inQ1.q4 * inQ2.q1,

       -inQ1.q1 * inQ2.q3
      + inQ1.q2 * inQ2.q4
      + inQ1.q3 * inQ2.q1
      + inQ1.q4 * inQ2.q2,

        inQ1.q1 * inQ2.q2
      - inQ1.q2 * inQ2.q1
      + inQ1.q3 * inQ2.q4
      + inQ1.q4 * inQ2.q3,

       -inQ1.q1 * inQ2.q1
      - inQ1.q2 * inQ2.q2
      - inQ1.q3 * inQ2.q3
      + inQ1.q4 * inQ2.q4 );
}

// -----------------------------------------------------------------
// Return inverse on the stack (no in-place inverse )
// -----------------------------------------------------------------

   inline Quaternion QuatInverse( Quaternion inQuat )
   {
      Quaternion result( inQuat );
      result.invert();
      return result;
   }

inline Quaternion operator/( const Quaternion &inQ1,
                             const Quaternion &inQ2 )
{
   return ( inQ1 * QuatInverse( inQ2 ) );
}

inline double inProduct( const Quaternion &inQ1,
                         const Quaternion &inQ2 )
{
   // said to return cos( angle ) between quaternions, check this
   return  ( inQ1.q1 * inQ2.q1 +
             inQ1.q2 * inQ2.q2 +
             inQ1.q3 * inQ2.q3 +
             inQ1.q4 * inQ2.q4   );
}

//---------------------------------------------------------------------
// Quaternion-vector-quaternion product (vector rotation)
// note : Maybe make more efficient later with elements expanded
//---------------------------------------------------------------------

inline Vector3d QVecRot( const Quaternion &inQuat,
                         const Vector3d   &inVec  )
{
   Quaternion 
      VecExtend = Quaternion( inVec.x, inVec.y, inVec.z, 0.0 );
   Quaternion
      qTemp( inQuat * VecExtend * QuatInverse( inQuat ) );

   return Vector3d ( qTemp.q1,  qTemp.q2,  qTemp.q3 );
}



//---------------------------------------------------------------------
// Quaternion-reconstruction from rotated X' Z' vectors
// based on Matlab script quatFromTwoVectors.m by PL.
// implemented by JM modified by working with unit vectors
//---------------------------------------------------------------------

inline Quaternion QFromXZ(  Vector3d   &inXNew,
                          Vector3d   &inZNew )
{
   Vector3d dir1, dir2, dir3;
   //v1Before = unitVector(v1Before)
   Vector3d xOld = Vector3d(1.0, 0.0, 0.0);
   //v2Before = unitVector(v2Before)
   Vector3d zOld = Vector3d(0.0, 0.0, 1.0);


   //v1After  = unitVector(v1After)
   Vector3d xNew = inXNew;
   xNew.normalize();
   //v2After  = unitVector(v2After)
   Vector3d zNew( inZNew.normalized());
   //zNew.normalized();

   //% axis of rotation is "middelloodlijn" of both end point differences
   //qAxis = cross( v1After-v1Before, v2After-v2Before);
   Vector3d qAxis = crossProduct(xNew - xOld, zNew - zOld);
   
 
   //if ( norm( qAxis, 'fro') > 0 ),
   if (qAxis.lengthSq() > 0.01) {
      //% the "normal", general case
      //qAxis = unitVector( qAxis)
      qAxis.normalize();
      //% choose the best (most orthogonal) vector to find the angle
      //if abs( dot( qAxis, v1Before)) < abs( dot( qAxis, v2Before)),
      if (fabs(dotProduct(qAxis, xOld)) < fabs(dotProduct(qAxis,zOld))){
         dir1 = crossProduct(qAxis,xOld);
         dir2 = crossProduct(qAxis,xNew);
      } else {
         dir1 = crossProduct(qAxis,zOld);
         dir2 = crossProduct(qAxis,zNew);
      }
   }
   return Quaternion();

   //end;
   //% special cases
   //if ( v1After == v1Before ),
   if (xNew==xOld){
      qAxis = xOld;

      dir1 = crossProduct(qAxis, zOld);
      dir2 = crossProduct(qAxis, zNew);
   }
   //if ( v2After == v2Before ), 
   if (zNew ==zOld){
      qAxis = zOld;
      dir1 = crossProduct(qAxis, xOld);
      dir2 = crossProduct(qAxis, xNew);
   }
   dir1.normalize();
   dir2.normalize();

   dir3 = crossProduct(qAxis, dir1);
   dir3.normalize();
   double angle = atan2( dotProduct( dir3, dir2), dotProduct( dir1, dir2));
   return Quaternion(qAxis, angle);


   
}

#endif

// ===========================  *  *  *  ==============================
