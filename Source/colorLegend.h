#ifndef __COLOR_LEGEND__
#define __COLOR_LEGEND__

#include <wx/panel.h>
#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include "Vector3.h"

#include "minMaxColorDlg.h"
#include "colorChangeEvent.h"

class colorLegend: public wxPanel
{
private:
	float mMinValue,mMaxValue;
	Vector3 mMinColor,mMaxColor;

public:
	colorLegend(wxWindow* parent,int id,
				float minValue=0,float maxValue=10,
				Vector3 colorMin = Vector3(0,0,0),Vector3 colorMax = Vector3(1,0,0),
				const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
	void OnPaint(wxPaintEvent& event);
	void OnLeftDClick(wxMouseEvent& event);
	
	Vector3 getMaxColor();
	Vector3 getMinColor();
	float getMaxValue();
	float getMinValue();
	
	void setMaxColor(Vector3 maxColor);
	void setMinColor(Vector3 minColor);
	void setMaxValue(float maxValue);
	void setMinValue(float minValue);
	
};
#endif