#include "minMaxColorDlg.h"



minMaxColorDlg::minMaxColorDlg(wxWindow* parent,Vector3 maxColor,Vector3 minColor)
{
	bool created = wxXmlResource::Get()->LoadDialog(this,parent,"minMaxColorDlg");
	
	//mColorPickerMin = XRCCTRL(*this,"ID_COLOR_MIN",wxColourPickerCtrl);
	//mColorPickerMax = XRCCTRL(*this,"ID_COLOR_MAX",wxColourPickerCtrl);
	mColorPickerMin = (wxColourPickerCtrl*)(FindWindowById(XRCID("ID_COLOR_MIN")));
	mColorPickerMax = (wxColourPickerCtrl*)(FindWindowById(XRCID("ID_COLOR_MAX")));
	//mColorPickerMin = (wxColourPickerCtrl*)(FindWindowByName("ID_COLOR_MIN"));
	//mColorPickerMax = (wxColourPickerCtrl*)(FindWindowByName("ID_COLOR_MAX"));
	if(mColorPickerMin == NULL || mColorPickerMax == NULL)
	//if(!created)
	{
		/*
		wxMessageBox( "Fehler beim erstellen des Dialogs",
				   "Fehler beim erstellen des Dialogs123", wxOK | wxICON_INFORMATION );
		*/
		//wxMessageDialog dialog = wxMessageDialog(this,"Fehler beim erstellen des Dialogs");
		wxMessageDialog dialog(this,"Fehler beim erstellen des Dialogs");
		dialog.ShowModal();
	}
	else
	{
		mColorPickerMin->SetColour(wxColour(minColor.getX()*255,minColor.getY()*255,minColor.getZ()*255));
		mColorPickerMax->SetColour(wxColour(maxColor.getX()*255,maxColor.getY()*255,maxColor.getZ()*255));
	}
}

void minMaxColorDlg::OnOkClick(wxCommandEvent& event)
{
	EndModal(wxID_OK);
}
void minMaxColorDlg::OnCancelClick(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}

Vector3 minMaxColorDlg::getMinColor()
{
	wxColour color = mColorPickerMin->GetColour();
	Vector3 ret = Vector3(((float)color.Red())/255.0f,((float)color.Green())/255.0f,((float)color.Blue())/255.0f);
	return ret;
}
Vector3 minMaxColorDlg::getMaxColor()
{	

	wxColour color = mColorPickerMax->GetColour();
	Vector3 ret = Vector3(((float)color.Red())/255.0f,((float)color.Green())/255.0f,((float)color.Blue())/255.0f);
	return ret;
}

BEGIN_EVENT_TABLE(minMaxColorDlg,wxDialog)
	EVT_BUTTON(wxID_OK,minMaxColorDlg::OnOkClick)
	EVT_BUTTON(wxID_CANCEL,minMaxColorDlg::OnCancelClick)
END_EVENT_TABLE()