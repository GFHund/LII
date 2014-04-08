#include "MeshManager.h"



MeshManager::MeshManager()
{
	this->mActiveMesh = 0;
	this->mExistActiveMesh = false;
}
MeshManager::MeshManager(const MeshManager&)
{
}

MeshManager* MeshManager::mSingleton = 0;

MeshManager* MeshManager::getSingleton()
{
	if(mSingleton == 0)
	{
		mSingleton = new MeshManager();
	}
	else
	{
		return mSingleton;
	}
}

bool MeshManager::existActiveMesh()
{
	return this->mExistActiveMesh;
}

Mesh* MeshManager::getActiveMesh()
{
	return mActiveMesh;
}
void MeshManager::setActiveMesh(Mesh* mesh)
{
	mActiveMesh = mesh;
	for(std::set<meshObserver*>::iterator i = this->mObservers.begin();i!=this->mObservers.end();i++)
	{
		meshObserver* observer = *i;
		observer->setSubject(mesh);
		mesh->addMeshObserver(observer);
	}
	if(!mExistActiveMesh)
	{
		mExistActiveMesh = !mExistActiveMesh;
	}
}

void MeshManager::addObserver(meshObserver* observer)
{
	this->mObservers.insert(observer);
}

/*
void MeshManager::addMesh(Mesh* newMesh)
{
	mMeshes.insert(newMesh);
	if(mMeshes.size() == 1)
	{
		mActiveMesh = newMesh;
		this->mExistActiveMesh = true;
	}
}
*/

Mesh* MeshManager::createMesh(Vector3* vertPos,int* faceOrder,int vertPosSize,int faceOrderSize)
{
	return NULL;
}
Mesh* MeshManager::createMeshFromFile(std::string filename)
{
	MeshLoader loader;
	Mesh* mesh = loader.loadMeshFile(filename);
	if(mesh != NULL)
	{
		mMeshes.insert(mesh);
	}
	return mesh;
}
Mesh* MeshManager::createFlatMesh(int width,int height)
{
	/*
	Vertex* A = new Vertex(Vector3(-1,-1,0));
	Vertex* B = new Vertex(Vector3(0,-1,0));
	Vertex* C = new Vertex(Vector3(1,-1,0));
	Vertex* D = new Vertex(Vector3(-1,0,0));
	
	Vertex* E = new Vertex(Vector3(0,0,0));
	Vertex* F = new Vertex(Vector3(1,0,0));
	Vertex* G = new Vertex(Vector3(-1,1,0));
	Vertex* H = new Vertex(Vector3(0,1,0));
	
	Vertex* I = new Vertex(Vector3(1,1,0));
	Face* fA = new Face(D,A,B);
	Face* fB = new Face(D,B,E);
	
	Face* fC = new Face(B,C,E);
	Face* fD = new Face(E,C,F);
	
	Face* fE = new Face(D,E,G);
	Face* fF = new Face(G,E,H);
	
	Face* fG = new Face(E,F,H);
	Face* fH = new Face(H,F,I);
	
	std::set<Vertex*> vertices;
	vertices.insert(A);
	vertices.insert(B);
	vertices.insert(C);
	vertices.insert(D);
	vertices.insert(E);
	vertices.insert(F);
	vertices.insert(G);
	vertices.insert(H);
	vertices.insert(I);
	std::set<Face*> faces;
	faces.insert(fA);
	faces.insert(fB);
	faces.insert(fC);
	faces.insert(fD);
	
	faces.insert(fE);
	faces.insert(fF);
	faces.insert(fG);
	faces.insert(fH);
	
	Mesh* mesh = new Mesh(vertices,faces);
	mMeshes.insert(mesh);
	return mesh;
	*/
	
	//int numVert = 10;

	//MeshManager* manager = MeshManager::getSingleton();
	
	std::set<Vertex*> vertices;
	std::vector<Vertex*> vertices2;//(20*20,0);
	std::set<Face*> faces;
	
	//for(int j=-10;j<11;j++)
	//for(int j=-numVert/2;j<numVert/2+1;j++)
	for(int j=-height/2;j<height/2+1;j++)
	{
		//for(int i=-10;i<11;i++)
		//for(int i=-numVert/2;i<numVert/2+1;i++)
		for(int i=-width/2;i<width/2+1;i++)
		{
			Vertex* vert = new Vertex(Vector3(i,j,0));
			//vert->setIndex((i+10)+(j+10)*20);
			//vert->setIndex((i+numVert/2)+(j+numVert/2)*numVert);
			vert->setIndex((i+width/2)+(j+height/2)*width);
			//vertices.insert(vert);
			//vertices2[(i+10)+(j+10)*20] = vert;
			vertices2.push_back(vert);
		}	
	}
	
	//for(int i=0;i<20;i++)
	for(int i=0;i<width;i++)
	{
		//for(int j=0;j<20;j++)
		for(int j=0;j<height;j++)
		{
			/*
			Vertex* A = vertices2[i+(numVert+1)*j];//0
			Vertex* B = vertices2[(i+1)+(numVert+1)*j];//1
			Vertex* C = vertices2[(i+1)+(numVert+1)*(j+1)];//3
			Vertex* D = vertices2[i+(numVert+1)*(j+1)];//2
			*/
			
			Vertex* A = vertices2[i+(width+1)*j];//0
			Vertex* B = vertices2[(i+1)+(width+1)*j];//1
			Vertex* C = vertices2[(i+1)+(width+1)*(j+1)];//3
			Vertex* D = vertices2[i+(width+1)*(j+1)];//2
			
			Face* fA = new Face(A,B,C);
			Face* fB = new Face(C,A,D);
			faces.insert(fA);
			faces.insert(fB);
		}
	}
	
	vertices = std::set<Vertex*>(vertices2.begin(),vertices2.end());
	
	Mesh* mesh = new Mesh(vertices,faces);
	mMeshes.insert(mesh);
	return mesh;
}
Mesh* MeshManager::createCubeMesh(int edgeLength)
{
	std::set<Vertex*> vertices;
	std::set<Face*> faces;
	Vertex* vertice[8];
	Face* face[12];
	/*
	vertice[0] = new Vertex(Vector3(-1,-1,1));
	vertice[1] = new Vertex(Vector3( 1,-1,1));
	vertice[2] = new Vertex(Vector3(-1, 1,1));
	vertice[3] = new Vertex(Vector3( 1, 1,1));
	
	vertice[4] = new Vertex(Vector3(-1,-1,-1));
	vertice[5] = new Vertex(Vector3( 1,-1,-1));
	vertice[6] = new Vertex(Vector3(-1, 1,-1));
	vertice[7] = new Vertex(Vector3( 1, 1,-1));
	*/
	float halfEdge = ((float)edgeLength)/2;
	vertice[0] = new Vertex(Vector3(-halfEdge,-halfEdge,halfEdge));
	vertice[1] = new Vertex(Vector3( halfEdge,-halfEdge,halfEdge));
	vertice[2] = new Vertex(Vector3(-halfEdge, halfEdge,halfEdge));
	vertice[3] = new Vertex(Vector3( halfEdge, halfEdge,halfEdge));
	
	vertice[4] = new Vertex(Vector3(-halfEdge,-halfEdge,-halfEdge));
	vertice[5] = new Vertex(Vector3( halfEdge,-halfEdge,-halfEdge));
	vertice[6] = new Vertex(Vector3(-halfEdge, halfEdge,-halfEdge));
	vertice[7] = new Vertex(Vector3( halfEdge, halfEdge,-halfEdge));
	
	vertice[0]->setIndex(0);
	vertice[1]->setIndex(1);
	vertice[2]->setIndex(2);
	vertice[3]->setIndex(3);
	
	vertice[4]->setIndex(4);
	vertice[5]->setIndex(5);
	vertice[6]->setIndex(6);
	vertice[7]->setIndex(7);
	
	face[0] = new Face(vertice[0],vertice[1],vertice[2]);
	face[1] = new Face(vertice[3],vertice[2],vertice[1]);
	
	face[2] = new Face(vertice[4],vertice[6],vertice[5]);
	face[3] = new Face(vertice[7],vertice[6],vertice[5]);
	
	face[4] = new Face(vertice[2],vertice[3],vertice[4]);
	face[5] = new Face(vertice[4],vertice[3],vertice[5]);
	
	face[6] = new Face(vertice[3],vertice[1],vertice[7]);
	face[7] = new Face(vertice[7],vertice[1],vertice[5]);
	
	face[8] = new Face(vertice[0],vertice[2],vertice[6]);
	face[9] = new Face(vertice[0],vertice[6],vertice[4]);
	
	face[10] = new Face(vertice[5],vertice[0],vertice[4]);
	face[11] = new Face(vertice[0],vertice[5],vertice[1]);
	
	for(int i=0;i<8;i++)
	{
		vertices.insert(vertice[i]);
	}
	for(int i=0;i<12;i++)
	{
		faces.insert(face[i]);
	}
	Mesh* mesh = new Mesh(vertices,faces);
	mMeshes.insert(mesh);
	return mesh;
}