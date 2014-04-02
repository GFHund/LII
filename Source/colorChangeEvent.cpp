#include "colorChangeEvent.h"

colorChangeEvent::colorChangeEvent(int winid,wxEventType eventType)
:wxEvent(winid,eventType)
{
	
}

wxEvent* colorChangeEvent::Clone() const
{
	return new colorChangeEvent(*this);
}

Vector3 colorChangeEvent::getNewMaxColor()
{
	return mNewColorMax;
}
Vector3 colorChangeEvent::getNewMinColor()
{
	return mNewColorMin;
}
void colorChangeEvent::setNewMaxColor(Vector3 newColor)
{
	this->mNewColorMax = newColor;
}
void colorChangeEvent::setNewMinColor(Vector3 newColor)
{
	this->mNewColorMin = newColor;
}

//wxDEFINE_EVENT(COLOR_CHANGE_EVT,colorChangeEvent);