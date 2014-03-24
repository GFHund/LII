#include "VIICanvas.h"

void VIICanvas::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	
	glTranslatef(0,0,-mDistanceOrigin);
	glRotatef(this->mAngleX,1,0,0);
	glRotatef(this->mAngleY,0,1,0);

	MeshManager* manager = MeshManager::getSingleton();
	if(manager->existActiveMesh())
	{
		Mesh* mesh = manager->getActiveMesh();
		std::set<Face*> faces = mesh->getFaces();
		float posA[3],posB[3],posC[3];
		float colorA[3],colorB[3],colorC[3];
		
		if(this->mShowEdges)
		{
			glColor3f(0.0,0.0,0.0);
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glPolygonOffset(-1.0,-1.0);
			glBegin(GL_TRIANGLES);
			for(std::set<Face*>::iterator i = faces.begin();i!=faces.end();i++)
			{
				Face* face = *i;
				face->getA()->getPosition().getArray(posA);
				face->getB()->getPosition().getArray(posB);
				face->getC()->getPosition().getArray(posC);
				glVertex3fv(posA);
				glVertex3fv(posB);
				glVertex3fv(posC);
			}
			glEnd();
			glDisable(GL_POLYGON_OFFSET_LINE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		
		int curMetaDataId = mesh->getCurMetaDataId();
		float maxValue = 0,minValue=0;
		float deltaMinMaxValue=0.0;
		if(curMetaDataId != 0)
		{
			std::set<Vertex*> vertex = mesh->getVertices();
			std::set<Vertex*>::iterator iter = vertex.begin();
			std::pair<std::string,float> data = (*iter)->getMetaData(curMetaDataId);
			maxValue = data.second;
			minValue = data.second;
			++iter;
			for(iter;iter!=vertex.end();iter++)
			{
				data = (*iter)->getMetaData(curMetaDataId);
				if(data.second > maxValue)
				{
					maxValue = data.second;
				}
				if(data.second < minValue)
				{
					minValue = data.second;
				}
			}
			deltaMinMaxValue = maxValue - minValue;
		}
		
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_TRIANGLES);
		for(std::set<Face*>::iterator i = faces.begin();i!=faces.end();i++)
		{
			Face* face = *i;
			face->getA()->getPosition().getArray(posA);
			face->getB()->getPosition().getArray(posB);
			face->getC()->getPosition().getArray(posC);
			if(curMetaDataId == 0)
			{
				glVertex3fv(posA);
				glVertex3fv(posB);
				glVertex3fv(posC);
			}
			else
			{
				std::pair<std::string,float> dataA,dataB,dataC;
				dataA = face->getA()->getMetaData(curMetaDataId);
				dataB = face->getB()->getMetaData(curMetaDataId);
				dataC = face->getC()->getMetaData(curMetaDataId);
				
				Vector3 color1(0,0,0),color2(1,0,0);
				Vector3 colorVecA = color1 + color2 * ((dataA.second - minValue)/deltaMinMaxValue);
				Vector3 colorVecB = color1 + color2 * ((dataB.second - minValue)/deltaMinMaxValue);
				Vector3 colorVecC = color1 + color2 * ((dataC.second - minValue)/deltaMinMaxValue);
				
				colorVecA.getArray(colorA);
				colorVecB.getArray(colorB);
				colorVecC.getArray(colorC);
				glColor3fv(colorA);
				glVertex3fv(posA);
				glColor3fv(colorB);
				glVertex3fv(posB);
				glColor3fv(colorC);
				glVertex3fv(posC);
			}
		}
		glEnd();
	}
	
	
	glFlush();
	SwapBuffers();
}

void VIICanvas::OpenGLInit()
{
	static bool onInit = true;
	
	//wxGLCanvas::SetCurrent(*mContext);
	//wxPaintDC(this);
	
	if(onInit)
	{
		this->mWidth = (GLint)GetSize().x;//1024;
		this->mHeight = (GLint)GetSize().y;//768
	
		std::cout << "Initialisiere OpenGL"<<std::endl;
		wxGLCanvas::SetCurrent(*mContext);
		wxPaintDC(this);
		
		glClearColor(1.0,1.0,1.0,0.0);
		//glClearColor(0.0,0.0,0.0,0.0);
		//glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0,0,(GLint)GetSize().x,(GLint)GetSize().y);
		changeProjectionMode(true);
		onInit = false;
	}
}

void VIICanvas::changeProjectionMode(bool perspective)
{
	this->mWidth = (GLint)GetSize().x;//1024;
	this->mHeight = (GLint)GetSize().y;//768
	glViewport(0,0,(GLint)GetSize().x,(GLint)GetSize().y);
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	if(perspective)
	{
		gluPerspective(60,this->mWidth/this->mHeight,0.02,20);
	}
	else
	{
		glOrtho(-this->mWidth/2,this->mWidth/2,-this->mHeight/2,this->mHeight/2,0.02,20);
	}
	glMatrixMode(GL_MODELVIEW);
}

//VIICanvas::VIICanvas(wxFrame* parent,int* args,wxWindowID id)
VIICanvas::VIICanvas(wxWindow* parent,int* args,wxWindowID id,wxSize size)
: wxGLCanvas(parent,id,args,wxDefaultPosition,size,0,wxT("GLCanvas"))
{//wxDefaultSize wxFULL_REPAINT_ON_RESIZE|wxTRANSPARENT_WINDOW
	this->mWidth = (GLint)GetSize().x;//1024;
	this->mHeight = (GLint)GetSize().y;//768
	
	this->mAngleX = 0;
	this->mAngleY = 0;
	this->mShowEdges = false;
	this->mContext = new wxGLContext(this);
	this->mLeftClicked = false;
	this->mRightClicked = false;
	this->mStartPoint = wxPoint(0,0);
	this->mDistanceOrigin = 4;
	changeProjectionMode(true);
}
void VIICanvas::Paintit(wxPaintEvent& event)
{
	//std::cout << "Draw" << std::endl;
	OpenGLInit();
	Render();
}

void VIICanvas::mouseEvent(wxMouseEvent& event)
{
	if(event.ButtonDown(wxMOUSE_BTN_LEFT))
	{
		mLeftClicked = true;
		mStartPoint = event.GetPosition();
	}
	if(event.ButtonUp(wxMOUSE_BTN_LEFT))
	{
		mLeftClicked = false;
	}
	if(event.ButtonDown(wxMOUSE_BTN_RIGHT))
	{
		mRightClicked = true;
		mStartPoint = event.GetPosition();
	}
	if(event.ButtonUp(wxMOUSE_BTN_RIGHT))
	{
		mRightClicked = false;
	}

	if(event.Dragging())
	{
		if(mLeftClicked)
		{
			wxPoint delta = event.GetPosition() - mStartPoint;
			mAngleY += delta.x;
			mAngleX += delta.y;
			
			if(mAngleX < 0)
			{
				mAngleX = 360 + mAngleX;
			}
			
			if(mAngleY < 0)
			{
				mAngleY = 360 + mAngleY;
			}
			
			mAngleX %= 360;
			mAngleY %= 360;
			
			
			//std::cout << "AngleX: " << mAngleX << " angleY: " << mAngleY << std::endl;
			mStartPoint = event.GetPosition();
			Refresh();
		}
		else if(mRightClicked)
		{
			wxPoint delta = event.GetPosition() - mStartPoint;
			mDistanceOrigin += delta.y;
			//std::cout << "Distance: "<< mDistanceOrigin <<std::endl;
			mStartPoint = event.GetPosition();
			Refresh();
		}
	}
	
}

void VIICanvas::resize(wxSizeEvent& event)
{
	wxSize size = event.GetSize();
	mWidth = size.GetWidth();
	mHeight = size.GetHeight();
	changeProjectionMode(true);
}

void VIICanvas::activateEdges(bool on)
{
	this->mShowEdges = on;
	Refresh();
}

BEGIN_EVENT_TABLE(VIICanvas, wxGLCanvas)
	EVT_MOTION(VIICanvas::mouseEvent)
	EVT_LEFT_DOWN(VIICanvas::mouseEvent)
	EVT_LEFT_UP(VIICanvas::mouseEvent)
	EVT_RIGHT_DOWN(VIICanvas::mouseEvent)
	EVT_RIGHT_UP(VIICanvas::mouseEvent)
	EVT_PAINT(VIICanvas::Paintit)
	//EVT_SIZE(VIICanvas::resize)
END_EVENT_TABLE()