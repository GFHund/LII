#ifndef __VII_MESH__
#define __VII_MESH__

#include <set>
#include <iostream>
#include "Vertex.h"
#include "Face.h"

//class Mesh;

//#include "meshObserver.h"
#include "observer.h"

#define PI 3.14159265359

class Mesh
{
//friend class observer;
//friend std::ostream& operator<<(std::ostream& input,const Mesh& mesh);
private:
	std::set<Vertex*> mVertices;
	std::set<Face*> mFaces;
	int mCurMetaId;
	std::set<observer*> mObservers;
	int mProcessPercentage;
	std::string mProcessMessage;
	
	void setProcessValue(int value);
	void setProcessText(std::string text);
	
public:
	//Mesh();
	Mesh(std::set<Vertex*> vertices,std::set<Face*> face);
	~Mesh();
	std::set<Face*> getFaces();
	std::set<Vertex*> getVertices();
	int getFacesCount();
	int getVerticesCount();
	
	int getCurMetaDataId();
	void setCurMetaDataId(int id);
	
	
	void addMeshObserver(observer* observer);
	int getProcessValue();
	std::string getProcessText();
	
	//VII Methods
	void viiRelatedFaces(Vertex* point,float radius,
						std::set<Face*>& catA,
						std::set<Face*>& catB,
						std::set<Face*>& catC);
						
	void calculateCircumferenceSmallCircle(int id,float radius);
	void calculateVII(float radius);
};
#endif