#include "MeshLoader.h"


Mesh* MeshLoader::loadObjFile(std::string filename)
{
	//std::ifstream is(filename,std::ifstream::binary);
	std::ifstream is;
	is.open(filename.c_str(),std::ifstream::in);
	
	is.seekg(0,is.end);
	int length = is.tellg();
	is.seekg(0,is.beg);
	char* file = new char[length];
	is.read(file,length);
	
	is.close();
	std::set<Vertex*> vertices;
	std::set<Face*> faces;
	
	int q = 0;
	
	for(int i=0;i<length;i++)
	{
		if(file[i]=='#' || (file[i]=='v' && file[i+1] == 't') || (file[i]=='v' && file[i+1] == 'p') ||(file[i]=='v' && file[i+1] == 'n'))
		{
			for(i;i<length;i++)
			{
				if(file[i] == '\n')
				{
					break;
				}
			}
		}
		else if(file[i]=='v' && file[i+1]==' ')
		{
			char* row = file + i;
			row = row+2;
			char* position = strchr(row,'\n');
			int length = position - row;
			char* vertexString = new char[length];
			strncpy(vertexString,row,length);
			//printf("%i Ausgelesen: %s\n",q,vertexString);
			char* koordinate;
			char token = ' '; 
			koordinate = strtok(vertexString,&token);
			//printf("%s\n",koordinate);
			float koordinateNumber[3];
			koordinateNumber[0] = atof(koordinate);
			int j = 1;
			while(koordinate != NULL)
			{
				koordinate = strtok(NULL,&token);
				koordinateNumber[j] = atof(koordinate);
				//printf("%i %f\n",j,koordinateNumber[j]);
				j++;
				if(j >= 3)
				{
					break;
				}
			}
			/*
			printf("ergebnis: ");
			for(int u=0;u<3;u++)
			{
				printf("%f",koordinateNumber[u]);
			}
			printf("\n");
			*/
			Vector3 posVertice = Vector3(koordinateNumber[0],koordinateNumber[1],koordinateNumber[2]);
			
			Vertex* vert = new Vertex(posVertice);
			vertices.insert(vert);
			vert->setIndex(vertices.size());
			
			//std::cout << vertices.size() << ": " << posVertice << " " << q << std::endl;
			
			i += 2 + length;
			q++;
			delete[] vertexString;
		}
		/*
		else if(if(file[i]=='v' && file[i+1]=='t')
		{
		
		}
		*/
		else if(file[i]=='f' && file[i+1]==' ')
		{
			//std::cout <<"-------------------"<<std::endl;
			char* row = file + i;
			row = row+2;
			char* position = strchr(row,'\n');
			int length = position - row;
			char* faceString = new char[length+1];
			strncpy(faceString,row,length+1);
			
			//std::cout <<"String: "<< faceString << std::endl;
			
			char* vertex;
			char token = ' ';
			vertex = strtok(faceString,&token);
			int verticesIndizes[4];
			
			verticesIndizes[0] = atoi(vertex);
			int j = 1;
			if(strchr(vertex,'/')==NULL)
			{
				//std::cout << "Char: " ;
				while(vertex != NULL)
				{
					//vertex = strtok(faceString,&token);
					vertex = strtok(NULL,&token);
					verticesIndizes[j] = atoi(vertex);
					//std::cout << vertex <<" ";
					j++;
					if(j>=4)
					{
						break;
					}
				}
				//std::cout << std::endl;
				//std::cout << "j: " << j << std::endl;
				int numLoops = 4;
				if(j<4)
				{
					numLoops = 3;
				}
				//std::cout << "numLoops: " << numLoops << std::endl;
				Vertex* vertices4Faces[4];
				for(int k=0;k<numLoops;k++)
				{
					for(std::set<Vertex*>::iterator l = vertices.begin();l!=vertices.end();l++)
					{
						Vertex* temp = *l;
						if(temp->getIndex() == verticesIndizes[k])
						{
							vertices4Faces[k] = *l;
							break;
						}
					}
				}
				
				if(j==4)
				{
					/*
					for(int x = 0;x<4;x++)
					{
						std::cout << verticesIndizes[x]<<" ";
					}
					std::cout <<"k"<< std::endl;
					*/
					faces.insert(new Face(vertices4Faces[0],vertices4Faces[1],vertices4Faces[2]));
					faces.insert(new Face(vertices4Faces[0],vertices4Faces[2],vertices4Faces[3]));
				}
				else
				{
					faces.insert(new Face(vertices4Faces[0],vertices4Faces[1],vertices4Faces[2]));
				}
				//std::cout << "---------------------------"<<std::endl;
			}
			else
			{
			
			}
			delete[] faceString;
		}
	}
	int t = 0;
	/*
	std::cout << vertices.size()<<std::endl;
	for(std::set<Vertex*>::iterator i = vertices.begin();i!=vertices.end();i++)
	{
		Vertex* v = *i;
		Vector3 vec = v->getPosition();
		std::cout << t << ": " << vec << " " << v->getIndex() << std::endl;
		t++;
	}
	
	std::cout << faces.size() << std::endl;
	int j=0;
	for(std::set<Face*>::iterator i = faces.begin();i!=faces.end();i++)
	{
		Vertex* A,*B,*C;
		Face* f = *i;
		A = f->getA();
		B = f->getB();
		C = f->getC();
		std::cout << j << " " << A->getIndex() <<"\t"<< B->getIndex() <<"\t"<< C->getIndex() << std::endl;
		j++;
	}
	*/
	
	delete[] file;
	
	return new Mesh(vertices,faces);
	
	/*
	std::set<Vertex*> vertices;
	while(true)
	{
		int i = is.get();
		if(is.eof() == true)
		{
			break;
		}
		
		if(i == 'v')
		{
			while()
		}
	}
	*/
}