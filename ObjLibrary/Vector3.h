//
//  Vector3.h
//
//  A module to store a math-style vector of length 3 and simple
//    operations that can be performed on it.
//

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cassert>
#include <iostream>
#include <cmath>




//
//  VECTOR3_IS_FINITE
//
//  A cross-platform macro that resolves into the appropriate
//    function to check if a floating point value is finite.
//    A floating point value is considered to be finite if it is
//    not any of the following:
//      -> positive infinity
//      -> negative infinity
//      -> NaN (not a number: 0/0)
//

#ifdef _WIN32
  // Microsoft non-standard function
  #include <cfloat>
  #define VECTOR3_IS_FINITE(n) _finite(n)
#elif __WIN32__
  // Microsoft non-standard function
  #include <cfloat>
  #define VECTOR3_IS_FINITE(n) _finite(n)
#else
  //  In theory, POSIX includes the isfinite macro defined in
  //    the C99 standard.  This macro is not included in any ISO
  //    C++ standard yet (as of January 2013).  However, this
  //    function does not seem to work.
  //#define VECTOR3_IS_FINITE(n) isfinite(n)
  #define VECTOR3_IS_FINITE(n) true
#endif



//
//  Vector3
//
//  A class to store a math-style vector of length 3.  The 3
//    numbers that compose a Vector3 are refered to as its
//    elements and may be accesed using dot notation.  The
//    associated functions are mostly declared inline for speed
//    reasons.  In theory, this class should be as fast (or
//    faster, when using pass-by-reference) as using double
//    values, but more convenient.
//
//  The norm of a Vector3 is its "length", the distance along
//    it.  There also exist functions to determine the norm of a
//    Vector3 along each axis-aligned plane.  These functions
//    calculate the norm the projection of this Vector3 to the
//    specified plane.  This returns the same result as
//    calculating the norm of a copy of the Vector3 with the
//    element for the excluded axis set to 0.0.
//

class Vector3
{
public:
//
//  Member Fields
//
//  These are the elements of the Vector3.  They can be queried
//    and changed freely without disrupting the operation of the
//    Vector3 instance.
//

	double x;
	double y;
	double z;

//
//  These are some standard Vector3s that may be useful
//

	static const Vector3 ZERO;
	static const Vector3 ONE;
	static const Vector3 UNIT_X_PLUS;
	static const Vector3 UNIT_X_MINUS;
	static const Vector3 UNIT_Y_PLUS;
	static const Vector3 UNIT_Y_MINUS;
	static const Vector3 UNIT_Z_PLUS;
	static const Vector3 UNIT_Z_MINUS;

public:
//
//  Default Constructor
//
//  Purpose: To create a new Vector3 that is the zero vector.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Vector3 is created with elements
//		 (0.0, 0.0, 0.0).
//

	Vector3 () : x(0.0), y(0.0), z(0.0)
	{}

//
//  Constructor
//
//  Purpose: To create a new Vector3 with the specified
//	     elements.
//  Parameter(s):
//	<1> x
//	<2> y
//	<3> z: The elements for the new Vector3
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Vector3 is created with elements
//		 (x, y, z).
//

	Vector3 (double X, double Y, double Z)
				      : x(X), y(Y), z(Z)
	{}

//
//  Copy Constructor
//
//  Purpose: To create a new Vector3 with the same elements as
//	     an existing Vector3.
//  Parameter(s):
//	<1> original: The Vector3 to copy
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Vector3 is created with the same elements
//		 as original.
//

	Vector3 (const Vector3& original) : x(original.x),
					    y(original.y),
					    z(original.z)
	{}

//
//  Destructor
//
//  Purpose: To safely destroy this Vector3 without memeory
//	     leaks.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: All dynamically allocated memeory is freed.
//

	~Vector3 ()
	{}

//
//  Assignment Operator
//
//  Purpose: To set the elements of this Vector3 to be equal to
//	     the elements of another.
//  Parameter(s):
//	<1> original: The Vector3 to copy
//  Precondition(s): N/A
//  Returns: A reference to this Vector3.
//  Side Effect: The elements of this Vector3 are set to the
//		 elements of original.
//

	Vector3& operator= (const Vector3& original)
	{
		//  Testing for self-assignment would take
		//    longer than just copying the values.
		x = original.x;
		y = original.y;
		z = original.z;

		return *this;
	}

//
//  Equality Operator
//
//  Purpose: To determine if this Vector3 is equal to another.
//	     Two Vector3s are equal IFF each of their elements
//	     are equal.
//  Parameter(s):
//	<1> other: The Vector3 to compare to
//  Precondition(s): N/A
//  Returns: Whether this Vector3 and other are equal.
//  Side Effect: N/A
//

	bool operator== (const Vector3& other) const
	{
		if(x != other.x) return false;
		if(y != other.y) return false;
		if(z != other.z) return false;
		return true;
	}

//
//  Inequality Operator
//
//  Purpose: To determine if this Vector3 and another are
//	     unequal.  Two Vector3s are equal IFF each of their
//	     elements are equal.
//  Parameter(s):
//	<1> other: The Vector3 to compare to
//  Precondition(s): N/A
//  Returns: Whether this Vector3 and other are unequal.
//  Side Effect: N/A
//

	inline bool operator!= (const Vector3& other) const
	{
		if(x != other.x) return true;
		if(y != other.y) return true;
		if(z != other.z) return true;
		return false;
	}

//
//  Negation Operator
//
//  Purpose: To create a new Vector3 that is the addative
//	     inverse of this Vector3.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: A Vector3 with elements (-x, -y, -z).
//  Side Effect: N/A
//

	Vector3 operator- () const
	{
		return Vector3(-x, -y, -z);
	}

//
//  Addition Operator
//
//  Purpose: To create a new Vector3 equal to the sum of this
//	     Vector3 and another.
//  Parameter(s):
//	<1> right: The Vector3 to add to this Vector3
//  Precondition(s): N/A
//  Returns: A Vector3 with elements
//	     (x + right.x, y + right.y, z + right.z).
//  Side Effect: N/A
//

	inline Vector3 operator+ (const Vector3& right) const
	{
		return Vector3(x + right.x,
			       y + right.y,
			       z + right.z);
	}

//
//  Subtraction Operator
//
//  Purpose: To create a new Vector3 equal to the differance of
//	     this Vector3 and another.
//  Parameter(s):
//	<1> right: The Vector3 to subtract from this Vector3
//  Precondition(s): N/A
//  Returns: A Vector3 with elements
//	     (x - other.x, y - other.y, z - other.z).
//  Side Effect: N/A
//

	Vector3 operator- (const Vector3& right) const
	{
		return Vector3(x - right.x,
			       y - right.y,
			       z - right.z);
	}

//
//  Multiplication Operator
//
//  Purpose: To create a new Vector3 equal to the product of
//	     this Vector3 and a scalar.
//  Parameter(s):
//	<1> factor: The scalar to multiply this Vector3 by
//  Precondition(s): N/A
//  Returns: A Vector3 with elements
//	     (x * factor, y * factor, z * factor).
//  Side Effect: N/A
//

	Vector3 operator* (double factor) const
	{
		return Vector3(x * factor,
			       y * factor,
			       z * factor);
	}

//
//  Division Operator
//
//  Purpose: To create a new Vector3 equal to this Vector3
//	     divided by a scalar.
//  Parameter(s):
//	<1> divisor: The scalar to divide this Vector3 by
//  Precondition(s):
//	<1> divisor != 0.0
//  Returns: A Vector3 with elements
//	     (x / divisor, y / divisor, z / divisor).
//  Side Effect: N/A
//

	Vector3 operator/ (double divisor) const
	{
		assert(divisor != 0.0);

		return Vector3(x / divisor,
			       y / divisor,
			       z / divisor);
	}

//
//  Addition Assignment Operator
//
//  Purpose: To set this Vector3 to the sum of itself and
//	     another Vector3.
//  Parameter(s):
//	<1> right: The Vector3 to add to this Vector3
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The elements of this Vector3 are set to
//		 (x + right.x, y + right.y, z + right.z).
//

	Vector3& operator+= (const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;

		return *this;
	}

//
//  Subtraction Assignment Operator
//
//  Purpose: To set this Vector3 to the differance of itself and
//	     another Vector3.
//  Parameter(s):
//	<1> right: The Vector3 to subtract from this Vector3
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The elements of this Vector3 are set to
//		 (x - right.x, y - right.y, z - right.z).
//

	Vector3& operator-= (const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;

		return *this;
	}

//
//  Multiplication Assignment Operator
//
//  Purpose: To set this Vector3 to the product of itself and a
//	     scalar.
//  Parameter(s):
//	<1> factor: The scalar to multiply this Vector3 by
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The elements of this Vector3 are set to
//		 (x * factor, y * factor, z * factor).
//

	Vector3& operator*= (double factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;

		return *this;
	}

//
//  Division Assignment Operator
//
//  Purpose: To set this Vector3 to equal to the quotient of
//	     itself divided by a scalar.
//  Parameter(s):
//	<1> divisor: The scalar to divide this Vector3 by
//  Precondition(s):
//	<1> divisor != 0.0
//  Returns: N/A
//  Side Effect: The elements of this Vector3 are set to
//		 (x / divisor, y / divisor, z / divisor).
//

	Vector3& operator/= (double divisor)
	{
		assert(divisor != 0.0);

		x /= divisor;
		y /= divisor;
		z /= divisor;

		return *this;
	}

//
//  isFinite
//
//  Purpose: To determine if all components of this Vector3 are
//	     finite numbers.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether this Vector3 has only finite components.
//  Side Effect: N/A
//

	bool isFinite () const
	{
		if(!VECTOR3_IS_FINITE(x)) return false;
		if(!VECTOR3_IS_FINITE(y)) return false;
		if(!VECTOR3_IS_FINITE(z)) return false;
		return true;
	}

//
//  isZero
//
//  Purpose: To determine if this Vector3 is the zero vector.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether this Vector3 is equal to (0.0, 0.0, 0.0).
//  Side Effect: N/A
//

	bool isZero () const
	{
		if(x != 0.0) return false;
		if(y != 0.0) return false;
		if(z != 0.0) return false;
		return true;
	}

//
//  isNormal
//  isUnit
//
//  Purpose: To determine if this Vector3 is a unit vector.
//	     These functions require 12 significant digits (6
//	     for the square of the norm).
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether this Vector3 has a norm of 1.0.
//  Side Effect: N/A
//

	bool isNormal () const
	{
		double norm_sqr_minus_1 = getNormSquared() - 1;

		if(norm_sqr_minus_1 >  1e-6)
			return false;
		if(norm_sqr_minus_1 < -1e-6)
			return false;
		return true;
	}
	bool isUnit () const
	{
		double norm_sqr_minus_1 = getNormSquared() - 1;

		if(norm_sqr_minus_1 >  1e-6)
			return false;
		if(norm_sqr_minus_1 < -1e-6)
			return false;
		return true;
	}

//
//  getNorm
//
//  Purpose: To determine the norm of this Vector3.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The norm of this Vector3.
//  Side Effect: N/A
//

	double getNorm () const
	{
		return sqrt(x * x + y * y + z * z);
	}

//
//  getNormSquared
//
//  Purpose: To determine the square of the norm of this
//	     Vector3.  This is significantly faster than
//	     calculating the norm itself.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The square of the norm of this Vector3.
//  Side Effect: N/A
//

	double getNormSquared () const
	{
		return x * x + y * y + z * z;
	}

//
//  isNormLessThan
//  isNormGreaterThan
//
//  Purpose: To determine if the norm of this Vector3 is
//	     less/greater than the specified value.  This is
//	     significantly faster than calculating the norm
//	     itself.
//  Parameter(s):
//	<1> length: The length to check against
//  Precondition(s):
//	<1> length >= 0.0
//  Returns: Whether the norm of this Vector3 is less/greater
//	     than length.
//  Side Effect: N/A
//

	double isNormLessThan (double length) const
	{
		assert(length >= 0.0);

		return getNormSquared() < length * length;
	}

	double isNormGreaterThan (double length) const
	{
		assert(length >= 0.0);

		return getNormSquared() > length * length;
	}

//
//  isNormLessThan
//  isNormGreaterThan
//
//  Purpose: To determine if the norm of this Vector3 is
//	     less/greater than the norm of the specified
//	     Vector3.  This is significantly faster than
//	     calculating the norms themselves.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s): N/A
//  Returns: Whether the norm of this Vector3 is less/greater
//	     than the norm of other.
//  Side Effect: N/A
//

	double isNormLessThan (const Vector3& other) const
	{
		return getNormSquared() < other.getNormSquared();
	}

	double isNormGreaterThan (const Vector3& other) const
	{
		return getNormSquared() > other.getNormSquared();
	}

//
//  getNormXY
//  getNormXZ
//  getNormYZ
//
//  Purpose: To determine the norm of this Vector3 projected to
//	     the indicated plane.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The norm of this Vector3 projected to the xy/xz/yz
//	     plane.
//  Side Effect: N/A
//

	double getNormXY () const
	{
		return sqrt(x * x + y * y);
	}
	double getNormXZ () const
	{
		return sqrt(x * x + z * z);
	}
	double getNormYZ () const
	{
		return sqrt(y * y + z * z);
	}

//
//  getNormXYSquared
//  getNormXZSquared
//  getNormYZSquared
//
//  Purpose: To determine the square of the norm of this Vector3
//	     projected to the indicated plane.  This is
//	     significantly faster than caculating the projected
//	     norm itself.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The square of the norm of this Vector3 projected to
//	     the xy/xz/yz plane.
//  Side Effect: N/A
//

	double getNormXYSquared () const
	{
		return x * x + y * y;
	}
	double getNormXZSquared () const
	{
		return x * x + z * z;
	}
	double getNormYZSquared () const
	{
		return y * y + z * z;
	}

//
//  getNormalized
//
//  Purpose: To create a normalized copy of this Vector3.
//  Parameter(s): N/A
//  Precondition(s):
//	<1> isFinite()
//	<2> !isZero()
//  Returns: A Vector3 with the same direction as this Vector3
//	     and a norm of 1.0.
//  Side Effect: N/A
//

	Vector3 getNormalized () const
	{
		assert(isFinite());
		assert(!isZero());

		assert(getNorm() != 0.0);
		double norm_ratio = 1.0 / getNorm();
		return Vector3(x * norm_ratio,
			       y * norm_ratio,
			       z * norm_ratio);
	}

//
//  getCopyWithNorm
//
//  Purpose: To create a Vector3 with the same direction as this
//	     Vector3 and the specified norm.
//  Parameter(s):
//	<1> norm: The new norm
//  Precondition(s):
//	<1> isFinite()
//	<2> !isZero()
//	<3> norm >= 0.0
//  Returns: A Vector3 with the same direction as this Vector3
//	     and a norm of norm.
//  Side Effect: N/A
//

	Vector3 getCopyWithNorm (double norm) const
	{
		assert(isFinite());
		assert(!isZero());
		assert(norm >= 0.0);

		assert(getNorm() != 0.0);
		double norm_ratio = norm / getNorm();
		return Vector3(x * norm_ratio,
			       y * norm_ratio,
			       z * norm_ratio);
	}

//
//  set
//
//  Purpose: To change this Vector3 to have the specified
//	     elements.
//  Parameter(s):
//	<1> X
//	<2> Y
//	<3> Z: The new elements for this Vector3
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: This Vector3 is set to (X, Y, Z).
//

	void set (double X, double Y, double Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

//
//  setZero
//
//  Purpose: To change this Vector3 to be the zero vector.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: This Vector3 is set to (0.0, 0.0, 0.0).
//

	void setZero ()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

//
//  normalize
//
//  Purpose: To change this Vector3 have a norm of 1.0.
//  Parameter(s): N/A
//  Precondition(s):
//	<1> isFinite()
//	<2> !isZero()
//  Returns: N/A
//  Side Effect: This Vector3 is set to have a norm of 1.0.  The
//		 direction of this Vector3 is unchanged.
//

	void normalize ()
	{
		assert(isFinite());
		assert(!isZero());

		assert(getNorm() != 0.0);
		double norm_ratio = 1.0 / getNorm();

		x *= norm_ratio;
		y *= norm_ratio;
		z *= norm_ratio;

		assert(isNormal());
	}

//
//  setNorm
//
//  Purpose: To change the norm of this Vector3.
//  Parameter(s):
//	<1> norm: The new norm
//  Precondition(s):
//	<1> isFinite()
//	<2> !isZero()
//	<3> norm >= 0.0
//  Returns: N/A
//  Side Effect: This Vector3 is set to have a norm of norm.
//		 The direction of this Vector3 is unchanged.
//

	void setNorm (double norm)
	{
		assert(isFinite());
		assert(!isZero());
		assert(norm >= 0.0);

		assert(getNorm() != 0.0);
		double norm_ratio = norm / getNorm();

		x *= norm_ratio;
		y *= norm_ratio;
		z *= norm_ratio;

		assert(getNormSquared() - (norm * norm) <  1e-6);
		assert(getNormSquared() - (norm * norm) > -1e-6);
	}

//
//  componentProduct
//
//  Purpose: To calculate the component-wise product of this
//	     Vector3 and another Vector3.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: A Vector2 with elements
//	     (x * other.x, y * other.y, z * other.z).
//  Side Effect: N/A
//

	Vector3 componentProduct (const Vector3& other)
	{
		assert(isFinite());
		assert(other.isFinite());

		return Vector3(x * other.x,
			       y * other.y,
			       z * other.z);
	}

//
//  dotProduct
//
//  Purpose: To determine the dot/scaler/inner product of this
//	     Vector3 and another Vector3.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: *this (dot) other.
//  Side Effect: N/A
//

	double dotProduct (const Vector3& other) const
	{
		assert(isFinite());
		assert(other.isFinite());

		return x * other.x + y * other.y + z * other.z;
	}

//
//  crossProduct
//
//  Purpose: To determine the cross/vector product of this
//	     Vector3 and another Vector3.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: *this (cross) other.
//  Side Effect: N/A
//

	Vector3 crossProduct (const Vector3& other) const
	{
		assert(isFinite());
		assert(other.isFinite());

		return Vector3(y * other.z - z * other.y,
			       z * other.x - x * other.z,
			       x * other.y - y * other.x);
	}

//
//  getDistance
//
//  Purpose: To determine the Euclidian distance between this
//	     Vector3 and another Vector3.  If you only need to
//	     determine if the distance to another Vector3 is
//	     less or greater than some value, consider using one
//	     of the isDistanceLessThan or isDistanceGreaterThan
//	     functions.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: The Euclidean distance between this Vector3 and
//	     other.
//  Side Effect: N/A
//

	double getDistance (const Vector3& other) const
	{
		double diff_x = x - other.x;
		double diff_y = y - other.y;
		double diff_z = z - other.z;

		return sqrt(diff_x * diff_x +
		            diff_y * diff_y +
		            diff_z * diff_z);
	}

//
//  getDistanceSquared
//
//  Purpose: To determine the square of the Euclidian distance
//	     between this Vector3 and another Vector3.  This
//	     function is significantly faster than getDistance().
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: The square of the Euclidian distance between this
//	     Vector3 and other.
//  Side Effect: N/A
//

	double getDistanceSquared (const Vector3& other) const
	{
		double diff_x = x - other.x;
		double diff_y = y - other.y;
		double diff_z = z - other.z;

		return diff_x * diff_x +
		       diff_y * diff_y +
		       diff_z * diff_z;
	}

//
//  isDistanceLessThan
//
//  Purpose: To determine if the Euclidian distance between this
//	     Vector3 and another Vector3 is less/greater than
//	     the specified value.  This function is
//	     significantly faster than getDistance().
//  Parameter(s):
//	<1> other: The other Vector3
//	<2> distance: The cutoff distance
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: Whether the Euclidian distance between Vector3 and
//	     other is less/greater than distance.
//  Side Effect: N/A
//

	bool isDistanceLessThan (const Vector3& other,
				 double distance) const
	{
		return (getDistanceSquared(other) <
			distance * distance);
	}
	bool isDistanceGreaterThan (const Vector3& other,
				    double distance) const
	{
		return (getDistanceSquared(other) >
			distance * distance);
	}

//
//  getManhattenDistance
//
//  Purpose: To determine the Manhatten distance between this
//	     Vector3 and another Vector3.  This is the sum of
//	     the differences between corresponding components.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: The Manhatten distance between this Vector3 and
//	     other.
//  Side Effect: N/A
//

	double getManhattenDistance (const Vector3& other) const
	{
		return fabs(x - other.x) +
		       fabs(y - other.y) +
		       fabs(z - other.z);
	}

//
//  getChessboardDistance
//
//  Purpose: To determine the chessboard distance between this
//	     Vector3 and another Vector3.  This is the largest
//	     differences between corresponding components.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: The chessboard distance between this Vector3 and
//	     other.
//  Side Effect: N/A
//

	double getChessboardDistance(const Vector3& other) const
	{
		double dx = fabs(x - other.x);
		double dy = fabs(y - other.y);
		double dz = fabs(z - other.z);

		return (dx < dy) ? ((dy < dz) ? dz : dy)
				 : ((dx < dz) ? dz : dx);
	}

//
//  isParallel
//
//  Purpose: To determine whether this Vector3 is parallel to
//	     the specified Vector3.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//  Returns: Whether this Vector3 is parallel to other.  The
//	     zero vector is assumed to be parallel to all
//	     Vector3s.
//  Side Effect: N/A
//

	bool isParallel (const Vector3& other) const
	{
		assert(isFinite());
		assert(other.isFinite());

		if(crossProduct(other).getNormSquared() < 1e-20)
			return true;
		else
			return false;
	}

//
//  projection
//
//  Purpose: To determione the projection of this Vector3 onto
//	     another Vector3.
//  Parameter(s):
//	<1> project_onto: The Vector3 to be projected onto 
//  Precondition(s):
//	<1> isFinite()
//	<2> other.isFinite()
//	<3> !project_onto.isZero()
//  Returns: The projection of this Vector3 onto project_onto.
//	     This is the component of this Vector3 with the same
//	     (or opposite) direction as project_onto.
//  Side Effect: N/A
//

	Vector3 projection (const Vector3& project_onto) const
	{
		assert(isFinite());
		assert(project_onto.isFinite());
		assert(!project_onto.isZero());

		double norm = dotProduct(project_onto) /
			      project_onto.getNormSquared();

		return project_onto * norm;
	}

//
//  cosAngle
//
//  Purpose: To determine the cosine of the angle between this
//	     Vector3 and another Vector3.
//  Parameter(s):
//	<1> other: The other Vector3
//  Precondition(s):
//	<1> isFinite()
//	<2> !isZero()
//	<3> other.isFinite()
//	<4> !other.isZero()
//  Returns: The cosine of the angle between this Vector3 and
//	     other.
//  Side Effect: N/A
//

	double cosAngle (const Vector3& other) const;

//
//  getRotationX
//
//  Purpose: To determine how far this Vector3 is rotated in
//	     radians around the x-axis, assuming the
//	     yz-component of the original Vector3 was on the
//	     xy-plane and had a positive y-component.
//  Parameter(s): N/A
//  Precondition(s):
//	<1> isFinite()
//	<2> y != 0.0 || z != 0.0
//  Returns: The current rotation of this Vector3 around the
//	     x-axis in radians.
//  Side Effect: N/A
//

	double getRotationX () const
	{
		assert(isFinite());
		assert(y != 0.0 || z != 0.0);

		return atan2(z, y);
	}

//
//  getRotationY
//
//  Purpose: To determine how far this Vector3 is rotated in
//	     radians around the y-axis, assuming the
//	     zx-component of the original Vector3 was on the
//	     yz-plane and had a positive z-component.
//  Parameter(s): N/A
//  Precondition(s):
//	<1> isFinite()
//	<2> z != 0.0 || x != 0.0
//  Returns: The current rotation of this Vector3 around the
//	     y-axis in radians.
//  Side Effect: N/A
//

	double getRotationY () const
	{
		assert(isFinite());
		assert(z != 0.0 || x != 0.0);

		return atan2(x, z);
	}

//
//  getRotationZ
//
//  Purpose: To determine how far this Vector3 is rotated in
//	     radians around the z-axis, assuming the
//	     xy-component of the original Vector3 was on the
//	     zx-plane and had a positive x-component.
//  Parameter(s): N/A
//  Precondition(s):
//	<1> isFinite()
//	<2> x != 0.0 || y != 0.0
//  Returns: The current rotation of this Vector3 around the
//	     z-axis in radians.
//  Side Effect: N/A
//

	double getRotationZ () const
	{
		assert(isFinite());
		assert(x != 0.0 || y != 0.0);

		return atan2(y, x);
	}

//
//  getRotatedX
//  getRotatedY
//  getRotatedZ
//
//  Purpose: To create a copy of this Vector3 rotated around the
//	     z/y/z-axis by the specified angle.
//  Parameter(s):
//	<1> radians: The angles to rotate in radians
//  Precondition(s):
//	<1> isFinite()
//  Returns: A copy of this Vector3 rotated radians radians
//	     around the x/y/z-axis.
//  Side Effect: N/A
//

	Vector3 getRotatedX (double radians) const
	{
		assert(isFinite());

		double sin_angle = sin(radians);
		double cos_angle = cos(radians);

		return Vector3(x,
			       cos_angle * y - sin_angle * z,
			       sin_angle * y + cos_angle * z);
	}

	Vector3 getRotatedY (double radians) const
	{
		assert(isFinite());

		double sin_angle = sin(radians);
		double cos_angle = cos(radians);

		return Vector3(sin_angle * z + cos_angle * x,
			       y,
			       cos_angle * z - sin_angle * x);
	}

	Vector3 getRotatedZ (double radians) const
	{
		assert(isFinite());

		double sin_angle = sin(radians);
		double cos_angle = cos(radians);

		return Vector3(cos_angle * x - sin_angle * y,
			       sin_angle * x + cos_angle * y,
			       z);
	}

//
//  getRotatedAxes
//
//  Purpose: To create a copy of this Vector3 rotated around the
//	     x- and z-axes by the specified angles.
//  Parameter(s):
//	<1> radians_x
//	<2> radians_z: The angles to rotate in radians
//  Precondition(s):
//	<1> isFinite()
//  Returns: A copy of this Vector3 rotated radians_x radians
//	     around the x-axis and then radians_z radians around
//	     the z-axis.
//  Side Effect: N/A
//

	Vector3 getRotatedAxes (double radians_x,
				double radians_z) const
	{
		assert(isFinite());

		return getRotatedX(radians_x).
					 getRotatedZ(radians_z);
	}

//
//  getRotatedArbitrary
//
//  Purpose: To create a copy of this Vector3 rotated around the
//	     specified axis by the specified angle.
//  Parameter(s):
//	<1> axis: The axis to rotate around
//	<2> radians: The angle to rotate in radians
//  Precondition(s):
//	<1> isFinite()
//	<2> axis.isFinite()
//	<3> axis.isNormal()
//  Returns: A copy of this Vector3 rotated radians radians
//	     around axis axis.
//  Side Effect: N/A
//

	Vector3 getRotatedArbitrary (const Vector3& axis,
				     double radians) const;

//
//  rotateX
//  rotateY
//  rotateZ
//
//  Purpose: To rotate this Vector3 around the z/y/z-axis by the
//	     specified angle.
//  Parameter(s):
//	<1> radians: The angles to rotate in radians
//  Precondition(s):
//	<1> isFinite()
//  Returns: N/A
//  Side Effect: This Vector3 is rotated radians radians around
//		 the x/y/z-axis.
//

	void rotateX (double radians)
	{
		assert(isFinite());

		double sin_angle = sin(radians);
		double cos_angle = cos(radians);

		set(x,
		    cos_angle * y - sin_angle * z,
		    sin_angle * y + cos_angle * z);
	}

	void rotateY (double radians)
	{
		assert(isFinite());

		double sin_angle = sin(radians);
		double cos_angle = cos(radians);

		set(sin_angle * z + cos_angle * x,
		    y,
		    cos_angle * z - sin_angle * x);
	}

	void rotateZ (double radians)
	{
		assert(isFinite());

		double sin_angle = sin(radians);
		double cos_angle = cos(radians);

		set(cos_angle * x - sin_angle * y,
		    sin_angle * x + cos_angle * y,
		    z);
	}

//
//  rotateAxes
//
//  Purpose: To rotate this Vector3 around the x- and z-axes by
//	     the specified angles.
//  Parameter(s):
//	<1> radians_x
//	<2> radians_z: The angles to rotate in radians
//  Precondition(s):
//	<1> isFinite()
//  Returns: N/A
//  Side Effect: This Vector3 is rotated around the x-axis by
//		 radians_x radians and then around the z-axis
//		 by radians_z radians.
//

	void rotateAxes (double radians_x, double radians_z)
	{
		assert(isFinite());

		rotateX(radians_x);
		rotateZ(radians_z);
	}

//
//  rotateArbitrary
//
//  Purpose: To rotate this Vector3 around the specified axis by
//	     the specified angle.
//  Parameter(s):
//	<1> axis: The axis to rotate around
//	<2> radians: The angle to rotate in radians
//  Precondition(s):
//	<1> isFinite()
//	<2> axis.isFinite()
//	<3> axis.isNormal()
//  Returns: N/A
//  Side Effect: This Vector3 is rotated by radians radians
//		 around axis axis.
//

	void rotateArbitrary (const Vector3& axis,
			      double radians);

//
//  getMatrixProduct
//
//  Purpose: To create a copy of this Vector3 multiplied by the
//	     specified 3x3 matrix.
//  Parameter(s):
//	<1> e11		+-----+-----+-----+
//	<2> e12		| e11 | e12 | e13 |
//	<3> e13		+-----+-----+-----+
//	<4> e21		| e21 | e22 | e23 |
//	<5> e22		+-----+-----+-----+
//	<6> e23		| e31 | e32 | e33 |
//	<7> e31		+-----+-----+-----+
//	<8> e32
//	<9> e33: The matrix elements
//  Precondition(s):
//	<1> isFinite()
//  Returns: A copy of this Vector3 multiplied by the matrix
//	     composed of the nine specified elements.
//  Side Effect: N/A
//

	Vector3 getMatrixProduct (double e11,
				  double e12,
				  double e13,
				  double e21,
				  double e22,
				  double e23,
				  double e31,
				  double e32,
				  double e33) const;

//
//  getRandomUnitVector
//
//  Purpose: To generate a Vector3 of norm 1 and with a uniform
//	     random direction.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: A uniform random unit vector.
//  Side Effect: N/A
//

	static Vector3 getRandomUnitVector ();

//
//  getClosestPointOnLine
//
//  Purpose: To determine the point on a specified line segment
//	     closest to the specified point.
//  Parameter(s):
//	<1> l1
//	<2> l2: The two ends of the line segment
//	<3> p: The point
//	<4> bounded: Whether the solution must line between the
//		     ends of the line segment
//  Precondition(s):
//	<1> l1.isFinite()
//	<2> l2.isFinite()
//	<3> p.isFinite()
//	<4> l1 != l2
//  Returns: The point on the line from l1 to l2 that is closest
//	     to point p.  If bounded == true, the point returned
//	     will lie between or on points l1 and l2.
//	     Otherwise, the point returned may lie anywhere
//	     along the line l1 and l2 define.
//  Side Effect: N/A
//

	static Vector3 getClosestPointOnLine (const Vector3& l1,
					      const Vector3& l2,
					      const Vector3& p,
					      bool bounded);
};

//
//  Stream Insertion Operator
//
//  Purpose: To print the specified Vector3 to the specified
//	     output stream.
//  Parameter(s):
//	<1> r_os: The output stream
//	<2> vector: The Vector3
//  Precondition(s): N/A
//  Returns: A reference to r_os.
//  Side Effect: vector is printed to r_os.
//

std::ostream& operator<< (std::ostream& r_os,
			  const Vector3& vector);

//
//  Multiplication Operator
//
//  Purpose: To create a new Vector3 equal to the product of
//	     the specified scalar and the specified Vector3.
//  Parameter(s):
//	<1> scalar: The scalar
//	<2> vector: The Vector3
//  Precondition(s): N/A
//  Returns: A Vector3 with elements (vector.x * scalar,
//	     vector.y * scalar, vector.z * scalar).
//  Side Effect: N/A
//

inline Vector3 operator* (double scalar, const Vector3& vector)
{
	return Vector3(vector.x * scalar,
		       vector.y * scalar,
		       vector.z * scalar);
}



#endif
