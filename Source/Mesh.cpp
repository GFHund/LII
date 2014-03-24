#include "Mesh.h"

Mesh::Mesh(std::set<Vertex*> vertices,std::set<Face*> faces)
{
	this->mVertices = vertices;
	this->mFaces = faces;
	this->mCurMetaId = 0;
}

Mesh::~Mesh()
{
	for(std::set<Face*>::iterator i=this->mFaces.begin();i!=this->mFaces.end();i++)
	{
		Face* face = *i;
		delete face;
	}
	for(std::set<Vertex*>::iterator i = this->mVertices.begin();i!=this->mVertices.end();i++)
	{
		Vertex* vertex = *i;
		delete vertex;
	}
}

std::set<Face*> Mesh::getFaces()
{
	return this->mFaces;
}
std::set<Vertex*> Mesh::getVertices()
{
	return this->mVertices;
}

int Mesh::getCurMetaDataId()
{
	return this->mCurMetaId;
}
void Mesh::setCurMetaDataId(int id)
{
	this->mCurMetaId = id;
}

void Mesh::viiRelatedFaces(Vertex* point,
							float radius,
							std::set<Face*>& catA,//Alle Vertices sind im Kreis
							std::set<Face*>& catB,//Zwei Vertices sind im Kreis
							std::set<Face*>& catC)//ein Vertice ist im Kreis
{
	std::set<Face*> faces = getFaces();
	Vector3 posPoint = point->getPosition();
	for(std::set<Face*>::iterator i = faces.begin();i!=faces.end();i++)
	{
		Face* face = *i;
		int verticesInSphere = 0;
		//verticesInSphere = 0;
		Vector3 distance = posPoint - face->getA()->getPosition();
		if(distance.getLength() <= radius)
		{
			++verticesInSphere;
		}
		distance = posPoint - face->getB()->getPosition();
		if(distance.getLength() <= radius)
		{
			++verticesInSphere;
		}
		distance = posPoint - face->getC()->getPosition();
		if(distance.getLength() <= radius)
		{
			++verticesInSphere;
		}
		
		switch(verticesInSphere)
		{
			case 1:
			{
				catC.insert(face);
				break;
			}
			case 2:
			{
				catB.insert(face);
				break;
			}
			case 3:
			{
				catA.insert(face);
				break;
			}
		}
	}
}

std::set<Vector3,Vector3> circumferenceFaceCatB(Vertex* point,float radius,Vertex* in1,Vertex* in2,Vertex* out)
{
	Vector3 direction1 = out->getPosition() - in1->getPosition();
	Vector3 direction2 = out->getPosition() - in2->getPosition();
	float curKoef1 = 0.5;
	float curKoef2 = 0.5;
	float raster = 0.25;
	bool finding1 = false;
	bool finding2 = false;
	for(int i=0;i<10;i++)
	{
		Vector3 length1 = point->getPosition() - (in1->getPosition() + direction1 * curKoef1);
		Vector3 length2 = point->getPosition() - (in2->getPosition() + direction2 * curKoef2);
		
		if(length1.getLength() < radius && !finding1)
		{
			curKoef1 -= raster;
		}
		else if(length1.getLength() > radius && !finding1)
		{
			curKoef1 += raster;
		}
		else
		{
			finding1 = true;
		}
		
		if(length2.getLength() < radius && !finding2)
		{
			curKoef2 -= raster;
		}
		else if(length2.getLength() > radius && finding2)
		{
			curKoef2 += raster;
		}
		else
		{
			finding2 = true;
		}
		raster /=2;
	}
	
	Vector3 pos1 = in1->getPosition() + direction1 * curKoef1;
	Vector3 pos2 = in2->getPosition() + direction2 * curKoef1;
	//Vector3 length = pos2 - pos1;
	//return length.getLength();
	std::set<Vector3,Vector3> ret;
	ret.insert(pos1);
	ret.insert(pos2);
	return ret;
}

std::set<Vector3,Vector3> circumferenceFaceCatC(Vertex* point,float radius,Vertex* in,Vertex* out1,Vertex* out2)
{
	Vector3 direction1 = out1->getPosition() - in->getPosition();
	Vector3 direction2 = out2->getPosition() - in->getPosition();
	float curKoef1 = 0.5;
	float curKoef2 = 0.5;
	float raster = 0.25;
	bool finding1 = false;
	bool finding2 = false;
	for(int i=0;i<10;i++)
	{
		Vector3 length1 = point->getPosition() - (in->getPosition() + direction1 * curKoef1);
		Vector3 length2 = point->getPosition() - (in->getPosition() + direction2 * curKoef2);
		
		if(length1.getLength() < radius && !finding1)
		{
			curKoef1 -= raster;
		}
		else if(length1.getLength() > radius && !finding1)
		{
			curKoef1 += raster;
		}
		else
		{
			finding1 = true;
		}
		
		if(length2.getLength() < radius && !finding2)
		{
			curKoef2 -= raster;
		}
		else if(length2.getLength() > radius && finding2)
		{
			curKoef2 += raster;
		}
		else
		{
			finding2 = true;
		}
		raster /=2;
	}
	
	Vector3 pos1 = in->getPosition() + direction1 * curKoef1;
	Vector3 pos2 = in->getPosition() + direction2 * curKoef1;
	std::set<Vector3,Vector3> ret;
	ret.insert(pos1);
	ret.insert(pos2);
	return ret;
	//Vector3 length = pos2 - pos1;
	//return length.getLength();
}


void getIntersectingPoints(Vertex* point,float radius,std::set<Vector3,Vector3>& points,std::set<Face*> catB,std::set<Face*> catC)
{
	Vector3 posVertex = point->getPosition();
	for(std::set<Face*>::iterator j = catB.begin();j!=catB.end();j++)
	{
		Vertex* in1,*in2,*out;
		Face* face = *j;
		Vector3 distance1 = posVertex - face->getA()->getPosition();
		Vector3 distance2 = posVertex - face->getB()->getPosition();
		if(distance1.getLength() > radius)
		{
			out = face->getA();
			in1 = face->getB();
			in2 = face->getC();
		}
		else if(distance2.getLength() > radius)
		{
			out = face->getB();
			in1 = face->getA();
			in2 = face->getC();
		}
		else
		{
			out = face->getC();
			in1 = face->getA();
			in2 = face->getB();
		}
		
		//circumference += circumferenceFaceCatB(vertex,radius,in1,in2,out);
		std::set<Vector3,Vector3> intersectionPoints = circumferenceFaceCatB(point,radius,in1,in2,out);
		points.insert(intersectionPoints.begin(),intersectionPoints.end());
	}
	
	for(std::set<Face*>::iterator j = catC.begin();j!=catC.end();j++)
	{
		Vertex* in,*out1,*out2;
		Face* face = *j;
		Vector3 distance1 = posVertex - face->getA()->getPosition();
		Vector3 distance2 = posVertex - face->getB()->getPosition();
		if(distance1.getLength() < radius)
		{
			in = face->getA();
			out1 = face->getB();
			out2 = face->getC();
		}
		else if(distance2.getLength() < radius)
		{
			out1 = face->getA();
			out2 = face->getC();
			in = face->getB();
		}
		else
		{
			out1 = face->getA();
			out2 = face->getB();
			in = face->getC();
		}
		//circumference += circumferenceFaceCatC(vertex,radius,in,out1,out2);
		std::set<Vector3,Vector3> intersectionPoints = circumferenceFaceCatB(point,radius,in,out1,out2);
		points.insert(intersectionPoints.begin(),intersectionPoints.end());
	}
}



void Mesh::calculateCircumferenceSmallCircle(int id,float radius)
{
	std::set<Face*> catA,catB,catC;
	std::set<Vertex*> vertices = getVertices();
	for(std::set<Vertex*>::iterator i = vertices.begin();i!=vertices.end();i++)
	{
		Vertex* vertex = *i;
		Vector3 posVertex = vertex->getPosition();
		viiRelatedFaces(vertex,radius,catA,catB,catC);
		float circumference = 0;
		
		for(std::set<Face*>::iterator j = catB.begin();j!=catB.end();j++)
		{
			Vertex* in1,*in2,*out;
			Face* face = *j;
			Vector3 distance1 = posVertex - face->getA()->getPosition();
			Vector3 distance2 = posVertex - face->getB()->getPosition();
			if(distance1.getLength() > radius)
			{
				out = face->getA();
				in1 = face->getB();
				in2 = face->getC();
			}
			else if(distance2.getLength() > radius)
			{
				out = face->getB();
				in1 = face->getA();
				in2 = face->getC();
			}
			else
			{
				out = face->getC();
				in1 = face->getA();
				in2 = face->getB();
			}
			//circumference += circumferenceFaceCatB(vertex,radius,in1,in2,out);
			std::set<Vector3,Vector3> intersectionPoints = circumferenceFaceCatB(vertex,radius,in1,in2,out);
			Vector3 vec1 = *(intersectionPoints.begin());
			Vector3 vec2 = *(intersectionPoints.rbegin());
			Vector3 diff = vec1 - vec2;
			circumference += diff.getLength();
		}
		
		for(std::set<Face*>::iterator j = catC.begin();j!=catC.end();j++)
		{
			Vertex* in,*out1,*out2;
			Face* face = *j;
			Vector3 distance1 = posVertex - face->getA()->getPosition();
			Vector3 distance2 = posVertex - face->getB()->getPosition();
			if(distance1.getLength() < radius)
			{
				in = face->getA();
				out1 = face->getB();
				out2 = face->getC();
			}
			else if(distance2.getLength() < radius)
			{
				out1 = face->getA();
				out2 = face->getC();
				in = face->getB();
			}
			else
			{
				out1 = face->getA();
				out2 = face->getB();
				in = face->getC();
			}
			//circumference += circumferenceFaceCatC(vertex,radius,in,out1,out2);
			std::set<Vector3,Vector3> intersectionPoints = circumferenceFaceCatC(vertex,radius,in,out1,out2);
			Vector3 vec1 = *(intersectionPoints.begin());
			Vector3 vec2 = *(intersectionPoints.rbegin());
			Vector3 diff = vec1 - vec2;
			circumference += diff.getLength();
		}
		
		vertex->setMetaData(std::pair<std::string,float>(std::string("Circumference"),circumference),id);
		
		catA.clear();
		catB.clear();
		catC.clear();
	}
}



void Mesh::calculateVII(float radius)
{
	for(std::set<Vertex*>::iterator j=this->mVertices.begin();j!=this->mVertices.end();j++)
	{
		Vertex* vertex = *j;
		float Br = (4/3)*M_PI*radius;  
		float Vl = 0.0f;
		float Vp = 0.0f;	
		std::set<Face*> catA,catB,catC;
		viiRelatedFaces(vertex,radius,catA,catB,catC);
		
		//Vp ungenau momentan. toDo: genauer
		for(std::set<Face*>::iterator i = catA.begin();i!=catA.end();i++)
		{
			Face* face = *i;
			Vector3 vecA = face->getA()->getPosition();
			Vector3 vecB = face->getB()->getPosition();
			Vector3 vecC = face->getC()->getPosition();
			vecA.setY(0);
			vecB.setY(0);
			vecC.setY(0);
			Vector3 area = (vecB-vecA).crossProduct(vecC-vecA);
			float aj = area.getLength() / 2;
			Vector3 s = face->getA()->getPosition() + face->getB()->getPosition() + face->getC()->getPosition();
			s /= 3;
			
			Vp += s.getY() * aj;
			
			//Vp += s.getY();
		}
		
		float volumeIntegralInvariant = Vl+Vp+(Br/2);
	}
}
