#include <wx/wxprec.h>
#ifndef WX_PRECOMP    
	#include <wx/wx.h>
#endif

#include "wx/xrc/xmlres.h"

#include <vector>

#include "VIICanvas.h"
#include "MeshLoader.h"
#include "MeshManager.h"

 class VIIFrame: public wxFrame
 {
 public:    
	VIIFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
 private:    
	VIICanvas* mViiCanvas;
	wxListBox* mListBox;
 
	void quitProgram();
	void OnOpen           (wxCommandEvent& event);    
	void OnExit           (wxCommandEvent& event);    
	void OnAbout          (wxCommandEvent& event);
	void TurnEdges        (wxCommandEvent& event);
	void createFlatSurface(wxCommandEvent& event);
	void createCube       (wxCommandEvent& event);
	void refreshSurface   (wxCommandEvent& event);
	void circumference    (wxCommandEvent& event);
	void calculateVII     (wxCommandEvent& event);	
	void OnListItemChanged(wxCommandEvent& event);
	void OnClose          (wxCloseEvent& event);
	
	wxDECLARE_EVENT_TABLE();
 };