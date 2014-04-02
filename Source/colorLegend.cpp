#include "colorLegend.h"
//float colorLegend::mMinValue = 0;
//float colorLegend::mMaxValue = 10;
//Vector3 colorLegend::mMinColor = Vector3(0,0,0);
//Vector3 colorLegend::mMaxColor = Vector3(1,0,0);

colorLegend::colorLegend(wxWindow* parent,int id,float minValue,
						float maxValue,Vector3 colorMin,// = Vector3(0,0,0),
						Vector3 colorMax,const wxPoint& pos,const wxSize& size)// = Vector3(1,0,0));
: wxPanel(parent,id,pos,size)
{
	Connect(wxEVT_PAINT,wxPaintEventHandler(colorLegend::OnPaint));
	Connect(wxEVT_LEFT_DCLICK,wxMouseEventHandler(colorLegend::OnLeftDClick));
	mMinValue = minValue;
	mMaxValue = maxValue;
	mMinColor = colorMin;
	mMaxColor = colorMax;
}
void colorLegend::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	wxSize windowSize = GetSize();
	wxString maxValue,minValue;
	maxValue << mMaxValue;
	minValue << mMinValue;
	dc.DrawText(maxValue,10,0);
	dc.GradientFillLinear(wxRect(0,20,windowSize.GetWidth(),windowSize.GetHeight()-60),
						wxColour(255*mMaxColor.getX(),255*mMaxColor.getY(),255*mMaxColor.getZ()),
						wxColour(255*mMinColor.getX(),255*mMinColor.getY(),255*mMinColor.getZ()),
						wxBOTTOM);
	dc.DrawText(minValue,10,windowSize.GetHeight()-30);
}

void colorLegend::OnLeftDClick(wxMouseEvent& event)
{
	wxWindow* frame = this;
	//if(frame->GetParent() == 
	while(frame->GetParent() != NULL)
	{
		frame = frame->GetParent();
	}
	
	//VIIFrame* viiFrame = (VIIFrame*) frame;
	
	minMaxColorDlg dialog(frame,mMaxColor,mMinColor);// = new minMaxColorDlg(NULL);
	
	//wxDialog dialog;
	bool created = true;
	//bool created = wxXmlResource::Get()->LoadDialog(&dialog,frame,"minMaxColorDlg");
	
	if(dialog.ShowModal() == wxID_CANCEL || !created)
	{
		return;
	}
	
	
	Vector3 colorMax = dialog.getMaxColor();
	Vector3 colorMin = dialog.getMinColor();
	
	colorChangeEvent triggerEvent(GetId(),COLOR_CHANGE_EVT);
	triggerEvent.SetEventObject(this);
	triggerEvent.setNewMaxColor(colorMax);
	triggerEvent.setNewMinColor(colorMin);
	
	bool eventProceeded = ProcessWindowEvent(triggerEvent);
	if(!eventProceeded)
	{
		wxMessageBox( "Sorry no Event triggert",
				   "double Click event triggert", wxOK | wxICON_INFORMATION );
	}
	
	mMinColor = colorMin;
	mMaxColor = colorMax;
	
	Refresh(true);
}

Vector3 colorLegend::getMaxColor()
{
	return mMaxColor;
}
Vector3 colorLegend::getMinColor()
{
	return mMinColor;
}
float colorLegend::getMaxValue()
{
	return mMaxValue;
}
float colorLegend::getMinValue()
{
	return mMinValue;
}

void colorLegend::setMaxColor(Vector3 maxColor)
{
	mMaxColor = maxColor;
	Refresh(false);
}
void colorLegend::setMinColor(Vector3 minColor)
{
	mMinColor = minColor;
	Refresh(false);
}
void colorLegend::setMaxValue(float maxValue)
{
	mMaxValue = maxValue;
	Refresh(false);
}
void colorLegend::setMinValue(float minValue)
{
	mMinValue = minValue;
	Refresh(false);
}