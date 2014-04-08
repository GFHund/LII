#ifndef __VII_MESH_MANAGER__
#define __VII_MESH_MANAGER__

#include <set>
#include <vector>
#include "MeshLoader.h"
#include "Mesh.h"
#include "meshObserver.h"


class MeshManager
{
private:
	static MeshManager* mSingleton;
	MeshManager();
	MeshManager(const MeshManager&);
	std::set<Mesh*> mMeshes;
	Mesh* mActiveMesh;
	bool mExistActiveMesh;
	
	std::set<meshObserver*> mObservers;
	
public:
	static MeshManager* getSingleton();
	bool existActiveMesh();
	Mesh* getActiveMesh();
	void setActiveMesh(Mesh* mesh);
	void addObserver(meshObserver* observer);
	
	//CreateMeshFunctions
	Mesh* createMesh(Vector3* vertPos,int* faceOrder,int vertPosSize,int faceOrderSize);
	Mesh* createMeshFromFile(std::string filename);
	Mesh* createFlatMesh(int width,int height);
	Mesh* createCubeMesh(int edgeLength);
	//void addMesh(Mesh*);
	
	//Observers die beim erstellen mit übergeben werden.
};
#endif