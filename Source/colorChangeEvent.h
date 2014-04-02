#include "Vector3.h"
#include <wx/event.h>

class colorChangeEvent:public wxEvent
{
private:
	Vector3 mNewColorMax;
	Vector3 mNewColorMin;
public:
	colorChangeEvent(int winid,wxEventType eventType = wxEVT_NULL);
	virtual wxEvent* Clone() const;
	
	Vector3 getNewMaxColor();
	Vector3 getNewMinColor();
	void setNewMaxColor(Vector3 newColor);
	void setNewMinColor(Vector3 newColor);
};
wxDEFINE_EVENT(COLOR_CHANGE_EVT,colorChangeEvent);
//wxDECLARE_EVENT(COLOR_CHANGE_EVT,colorChangeEvent);

typedef void (wxEvtHandler::*colorChangeEventHandler)(colorChangeEvent&);
#define colorChangeEventHandler(func) wxEVENT_HANDLER_CAST(colorChangeEventHandler,func)
//#define colorChangeEventHandler(func) (&func)
#define COLOR_CHANGE_EVT(id,func) wx__DECLARE_EVT1(COLOR_CHANGE_EVT,id,colorChangeEventHandler(func))

//#define COLOR_CHANGE_EVT(id,func) DECLARE_EVENT_TABLE_ENTRY(COLOR_CHANGE_EVT,id,),