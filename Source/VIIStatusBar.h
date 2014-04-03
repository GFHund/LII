#include <wx/statusbr.h> 
#include <wx/gauge.h>

class VIIStatusBar:public wxStatusBar
{
private:
	wxGauge* processBar;
public:
	VIIStatusBar(wxWindow *parent);
	void OnSize(wxSizeEvent& event);
	
private:
	wxDECLARE_EVENT_TABLE();
};

