#ifndef __VII_STATUS_BAR__
#define __VII_STATUS_BAR__
/*
#include <wx/wxprec.h>
#ifndef WX_PRECOMP    
	#include <wx/wx.h>
#endif
*/
#include <wx/statusbr.h> 
#include <wx/gauge.h>

class VIIStatusBar:public wxStatusBar
{
private:
	wxGauge* processBar;
public:
	VIIStatusBar(wxWindow *parent);
	void OnSize(wxSizeEvent& event);
	void SetProcessBarValue(int value);
	
private:
	wxDECLARE_EVENT_TABLE();
};

#endif