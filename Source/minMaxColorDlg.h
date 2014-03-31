#include <wx/dialog.h>
#include <wx/clrpicker.h>
#include "wx/xrc/xmlres.h"
#include <wx/msgdlg.h>
#include "Vector3.h"

class minMaxColorDlg:public wxDialog
{
private:
	wxColourPickerCtrl* mColorPickerMax;
	wxColourPickerCtrl* mColorPickerMin;

public:
	minMaxColorDlg(wxWindow* parent,Vector3 maxColor,Vector3 minColor);
	void OnOkClick(wxCommandEvent& event);
	void OnCancelClick(wxCommandEvent& event);
	
	Vector3 getMinColor();
	Vector3 getMaxColor();
	
	DECLARE_EVENT_TABLE()
};