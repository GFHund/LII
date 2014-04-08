#include <wx/wxprec.h>
#ifndef WX_PRECOMP    
	#include <wx/wx.h>
#endif

#include "wx/xrc/xmlres.h"

#include <vector>

//GUI Klassen
#include "VIIStatusBar.h"
#include "VIICanvas.h"
#include "colorLegend.h"

//Mesh Klassen
#include "MeshManager.h" //Mesh.h->meshObserver.h
//#include "Mesh.h"
//#include "meshObserver.h"

 class VIIFrame: public wxFrame
 {
 public:    
	VIIFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
 private:    
	VIICanvas* mViiCanvas;
	colorLegend* mLegend;//legende;
	wxListBox* mListBox;
	//wxGauge* processBar;
	meshObserver* mObserver;
	//wxMenuBar* menubar;
	//wxMenuItem* turnEdges;
	
	enum
	{
		ID_CANVAS = 1945,
		ID_LIST_BOX = 2000,
		ID_COLOR_LEGEND = 2001
	};
 
	void quitProgram();
	void setLegend(float minValue,float maxValue,Vector3 minColor,Vector3 maxColor);
	
	void OnOpen            (wxCommandEvent& event);    
	void OnExit            (wxCommandEvent& event);    
	void OnAbout           (wxCommandEvent& event);
	void TurnEdges         (wxCommandEvent& event);
	void createFlatSurface (wxCommandEvent& event);
	void createCube        (wxCommandEvent& event);
	void refreshSurface    (wxCommandEvent& event);
	void circumference     (wxCommandEvent& event);
	void calculateVII      (wxCommandEvent& event);	
	void OnListItemChanged (wxCommandEvent& event);
	void OnColorChanged    (colorChangeEvent& event);
	
	void InLeftDClickLegend(wxMouseEvent& event);
	void OnClose           (wxCloseEvent& event);
	
	wxDECLARE_EVENT_TABLE();
 };