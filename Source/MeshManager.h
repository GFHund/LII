#ifndef __VII_MESH_MANAGER__
#define __VII_MESH_MANAGER__

#include <set>
#include "Mesh.h"

class MeshManager
{
private:
	static MeshManager* mSingleton;
	MeshManager();
	MeshManager(const MeshManager&);
	std::set<Mesh*> mMeshes;
	Mesh* mActiveMesh;
	bool mExistActiveMesh;
	
public:
	static MeshManager* getSingleton();
	bool existActiveMesh();
	Mesh* getActiveMesh();
	void setActiveMesh(Mesh* mesh);
	void addMesh(Mesh*);
};
#endif