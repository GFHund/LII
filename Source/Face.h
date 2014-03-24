#include "Vertex.h"
class Face
{
private:
	Vector3 mNormal;
	Vertex* mA,*mB,*mC;

	public:
	Face(Vertex* A,Vertex* B,Vertex* C);
	Vertex* getA();
	Vertex* getB();
	Vertex* getC();
	Vector3 getNormal(bool normalize);
};