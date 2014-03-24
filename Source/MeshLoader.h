#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Mesh.h"

class MeshLoader
{
private:
	Mesh* loadPlyFile(std::string filename);
	Mesh* loadObjFile(std::string filename);
public:

	Mesh* loadMeshFile(std::string filename);
};