#include "Face.h"
Face::Face(Vertex* A,Vertex* B,Vertex* C)
{
	this->mA = A;
	this->mB = B;
	this->mC = C;
}

Vertex* Face::getA()
{
	return this->mA;
}
Vertex* Face::getB()
{
	return this->mB;
}
Vertex* Face::getC()
{
	return this->mC;
}

Vector3 Face::getNormal(bool normalize)
{
	Vector3 vec1 = this->mB->getPosition() - this->mA->getPosition();
	Vector3 vec2 = this->mC->getPosition() - this->mA->getPosition();
	Vector3 ret = vec1.crossProduct(vec2);
	if(normalize)
	{
		ret.normalize();
	}
	return ret;
}