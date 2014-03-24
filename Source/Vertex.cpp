#include "Vertex.h"

Vertex::Vertex(Vector3 pos)
{
	this->mPos = pos;
}
void Vertex::setIndex(int index)
{
	this->mIndex = index;
}

int Vertex::getIndex()
{
	return this->mIndex;
}

Vector3 Vertex::getPosition()
{
	return this->mPos;
}

void Vertex::setColor(Vector3 color)
{
	this->mColor = color;
}
Vector3 Vertex::getColor()
{
	return this->mColor;
}

void Vertex::setPosition(Vector3 newPos)
{
	this->mPos = newPos;
}

std::pair<std::string,float> Vertex::getMetaData(int id)
{
	return mMetaData[id];
}
void Vertex::setMetaData(std::pair<std::string,float> metaData,int id)
{
	mMetaData[id] = metaData;
}
/*
float Vertex::getMetaData(int id)
{
	return mMetaData[id];
}
int Vertex::setMetaData(float data)
{
	int ret = mMetaData.size();
	mMetaData.push_back();
}
*/