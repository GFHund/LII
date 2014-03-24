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
}
void MeshManager::addMesh(Mesh* newMesh)
{
	mMeshes.insert(newMesh);
	if(mMeshes.size() == 1)
	{
		mActiveMesh = newMesh;
		this->mExistActiveMesh = true;
	}
}