#include "meshObserver.h"

meshObserver::meshObserver(VIIStatusBar* statusBar)
{
	this->mStatusBar = statusBar;
}
/*
void meshObserver::update(Mesh* mesh)
{
	int percentage = mesh->processPercentage;
	std::string message = mesh->processMessage;
	setPercentageProcess(percentage);
	setStatusText(message);
}
*/
	
void meshObserver::update()
{
	int percentage = this->mSubject->getProcessValue();
	std::string message = this->mSubject->getProcessText();
	setPercentageProcess(percentage);
	setStatusText(message);
}
	
void meshObserver::setPercentageProcess(int percentage)
{
	this->mStatusBar->SetProcessBarValue(percentage);	
}
void meshObserver::setStatusText(std::string message)
{
	this->mStatusBar->SetStatusText(wxString(message));
}

void meshObserver::setSubject(Mesh* mesh)
{
	this->mSubject = mesh;
}