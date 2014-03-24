#ifndef __VII_MESH__
#define __VII_MESH__

#include <set>
#include "Vertex.h"
#include "Face.h"

class Mesh
{
private:
	std::set<Vertex*> mVertices;
	std::set<Face*> mFaces;
	int mCurMetaId;
	
public:
	//Mesh();
	Mesh(std::set<Vertex*> vertices,std::set<Face*> face);
	~Mesh();
	std::set<Face*> getFaces();
	std::set<Vertex*> getVertices();
	
	int getCurMetaDataId();
	void setCurMetaDataId(int id);
	
	//VII Methods
	void viiRelatedFaces(Vertex* point,float radius,
						std::set<Face*>& catA,
						std::set<Face*>& catB,
						std::set<Face*>& catC);
						
	void calculateCircumferenceSmallCircle(int id,float radius);
	void calculateVII(float radius);
};
#endif