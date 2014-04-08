#include "VIIStatusBar.h"

VIIStatusBar::VIIStatusBar(wxWindow *parent)
: wxStatusBar(parent,wxID_ANY,wxSTB_DEFAULT_STYLE,"VIIStatusBar")
{
	processBar = new wxGauge(this,wxID_ANY,100);
	
	int widths[] = {-1,100};
	
	SetFieldsCount(2);
	SetStatusWidths(2,widths);
	
	SetMinHeight(processBar->GetBestSize().GetHeight());
}

void VIIStatusBar::OnSize(wxSizeEvent& event)
{
	wxRect rect;
	if(!GetFieldRect(1,rect))
	{
		event.Skip();
		return;
	}
	wxRect rectGauge = rect;
	rectGauge.Deflate(2);
	processBar->SetSize(rectGauge);
	event.Skip();
}

void VIIStatusBar::SetProcessBarValue(int value)
{
	if(value < 0 || value > processBar->GetRange())
	{
		return;
	}
	processBar->SetValue(value);
}

BEGIN_EVENT_TABLE(VIIStatusBar, wxStatusBar)
    EVT_SIZE(VIIStatusBar::OnSize)
END_EVENT_TABLE()