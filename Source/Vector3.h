
#ifndef __VII_VECTOR3__

#define __VII_VECTOR3__
#include <iostream>
#include <math.h>

class Vector3
{
	friend std::ostream& operator<<(std::ostream& input,const Vector3& vector);
	private:
	float mX;
	float mY;
	float mZ;
	
	public:
	Vector3();
	Vector3(float x,float y,float z);
	
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void getArray(float* array);
	
	void normalize();
	float getLength();
	Vector3 operator +(Vector3 operator2);
	Vector3 operator *(float skalar);
	Vector3 operator *(Vector3 operator2);//Dot Product
	Vector3 operator -(Vector3 operator2);
	Vector3 operator /(float skalar);
	void operator +=(Vector3 operator2);
	void operator *=(float skalar);
	void operator *=(Vector3 operator2);//Dot Product
	void operator -=(Vector3 operator2);
	void operator /=(float skalar);
	
	//bool operator ==(const Vector3& vec1,const Vector3& vec2);
	
	bool operator ()(const Vector3& lhs,const Vector3& rhs)const;
	
	Vector3 crossProduct(Vector3 operator2);
};
//std::ostream& operator<<(std::ostream& input,const Vector3& vector);
//bool operator ==(const Vector3& vec1,const Vector3& vec2);
/*
bool operator ==(const Vector3& vec1,const Vector3& vec2)
{
	if(vec1.getX() == vec2.getX() && vec1.getY() == vec2.getY() && vec1.getZ() == vec2.getZ())
	{
		return true;
	}
	return false;
}
*/

#endif