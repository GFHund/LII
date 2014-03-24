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
	DECLARE_EVENT_TABLE()
};