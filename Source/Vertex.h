
#ifndef __VII_VERTEX__

#define __VII_VERTEX__

#include <utility>
#include <string>
#include <map>

#include "Vector3.h"


class Vertex
{
private:
	Vector3 mPos;
	Vector3 mNormal;
	Vector3 mColor;
	int mIndex;
	std::map<int,std::pair<std::string,float> > mMetaData;
public:
	Vertex(Vector3 pos);
	void setIndex(int index);
	int getIndex();
	void setColor(Vector3 color);
	Vector3 getColor();
	Vector3 getPosition();
	void setPosition(Vector3 newPos);
	std::pair<std::string,float> getMetaData(int id);
	void setMetaData(std::pair<std::string,float> metaData,int id);
};
#endif