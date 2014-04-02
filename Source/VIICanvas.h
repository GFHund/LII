#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/glu.h>
#include <set>
#include "MeshManager.h"

class VIICanvas: public wxGLCanvas
{
private:
	int mWidth,mHeight;
	int mAngleY;
	int mAngleX;
	int mDistanceOrigin;
	bool mShowEdges;
	wxGLContext* mContext;
	bool mLeftClicked;
	bool mRightClicked;
	wxPoint mStartPoint;
	Vector3 mMaxColor,mMinColor;
	
	void Render();
	void changeProjectionMode(bool perspective);
	void OpenGLInit();
public:
	//VIICanvas(wxFrame* parent,int* args,wxWindowID id);
	VIICanvas(wxWindow* parent,int* args,wxWindowID id,wxSize size);
	void Paintit(wxPaintEvent& event);
	void mouseEvent(wxMouseEvent& event);
	void resize(wxSizeEvent& event);
	void activateEdges(bool on);
	void setColor(Vector3 maxColor,Vector3 minColor);
	DECLARE_EVENT_TABLE()
};