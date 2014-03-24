#include "MeshLoader.h"

Mesh* MeshLoader::loadMeshFile(std::string filename)
{
	std::size_t found = filename.find(".ply");
	if(found !=std::string::npos)
	{
		return loadPlyFile(filename);
	}
	found = filename.find(".obj");
	if(found != std::string::npos)
	{
		return loadObjFile(filename);
	}
}