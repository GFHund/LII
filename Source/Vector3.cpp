#include "Vector3.h"

std::ostream& operator <<(std::ostream& input,const Vector3& vector)
{
	return (input << "[" << vector.getX()<< "\t" << vector.getY()<<"\t" << vector.getZ() <<"]");
}

Vector3::Vector3()
{
	this->mX = 0;
	this->mY = 0;
	this->mZ = 0;
}

Vector3::Vector3(float x,float y,float z)
{
	this->mX = x;
	this->mY = y;
	this->mZ = z;
}

float Vector3::getX() const
{
	return this->mX;
}
float Vector3::getY() const
{
	return this->mY;
}
float Vector3::getZ() const
{
	return this->mZ;
}
void Vector3::setX(float x)
{
	this->mX = x;
}
void Vector3::setY(float y)
{
	this->mY = y;
}
void Vector3::setZ(float z)
{
	this->mZ = z;
}

void Vector3::getArray(float* array)
{
	array[0] = this->mX;
	array[1] = this->mY;
	array[2] = this->mZ;
}

void Vector3::normalize()
{
	float length = getLength();
	(*this) /= length;
}
float Vector3::getLength()
{
	return sqrt(this->mX * this->mX + 
				this->mY * this->mY +
				this->mZ * this->mZ);
				
}
Vector3 Vector3::operator +(Vector3 operator2)
{
	Vector3 ret;
	ret.setX(this->mX + operator2.getX());
	ret.setY(this->mY + operator2.getY());
	ret.setZ(this->mZ + operator2.getZ());
	return ret;
}
Vector3 Vector3::operator *(float skalar)
{
	Vector3 ret;
	ret.setX(this->mX * skalar);
	ret.setY(this->mY * skalar);
	ret.setZ(this->mZ * skalar);
	return ret;
}
Vector3 Vector3::operator *(Vector3 operator2)//Dot Product
{
	
}
Vector3 Vector3::operator -(Vector3 operator2)
{
	Vector3 ret;
	ret.setX(this->mX - operator2.getX());
	ret.setY(this->mY - operator2.getY());
	ret.setZ(this->mZ - operator2.getZ());
	return ret;
}
Vector3 Vector3::operator /(float skalar)
{
	Vector3 ret;
	ret.setX(this->mX / skalar);
	ret.setY(this->mY / skalar);
	ret.setZ(this->mZ / skalar);
	return ret;
}
void Vector3::operator +=(Vector3 operator2)
{
	this->mX += operator2.getX();
	this->mY += operator2.getY();
	this->mZ += operator2.getZ();
}
void Vector3::operator *=(float skalar)
{
	this->mX *= skalar;
	this->mY *= skalar;
	this->mZ *= skalar;
}
void Vector3::operator *=(Vector3 operator2)//Dot Product
{

}
void Vector3::operator -=(Vector3 operator2)
{
	this->mX -= operator2.getX();
	this->mY -= operator2.getY();
	this->mZ -= operator2.getZ();
}
void Vector3::operator /=(float skalar)
{
	this->mX /= skalar;
	this->mY /= skalar;
	this->mZ /= skalar;
}
/*
bool Vector3::operator ==(const Vector3& vec1,const Vector3& vec2)
{
	if(vec1.getX() == vec2.getX() && vec1.getY() == vec2.getY() && vec1.getZ() == vec2.getZ())
	{
		return true;
	}
	return false;
}
*/
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


bool Vector3::operator() (const Vector3& lhs,const Vector3& rhs)const
{
	/*
	if(lhs == rhs)
	{
		return false;
	}
	*/
	
	if(lhs.getX() == rhs.getX())
	{
		if(lhs.getY() == rhs.getY())
		{
			if(lhs.getZ() == rhs.getZ())
			{
				return false;
			}
			return lhs.getZ() < rhs.getZ();
		}
		
		return lhs.getY() < rhs.getY();
	}
	
	return lhs.getX() < rhs.getX();
}

Vector3 Vector3::crossProduct(Vector3 operator2)
{
	float retX = this->mY * operator2.getZ() - this->mZ * operator2.getY();
	float retY = this->mX * operator2.getZ() - this->mZ * operator2.getX();
	float retZ = this->mY * operator2.getX() - this->mX * operator2.getY();
	return Vector3(retX,retY,retZ);
}