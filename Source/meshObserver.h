#ifndef __MESH_OBSERVER__
#define __MESH_OBSERVER__


#include <string>
#include "VIIStatusBar.h"
#include "Mesh.h"
#include "observer.h"
/*
class observer
{
public:
	void 
};
*/
//class Mesh;
//class VIIStatusBar;

class meshObserver:public observer
{
private:
	VIIStatusBar* mStatusBar;
	Mesh* mSubject;

public:
	//meshObserver(Mesh* subject,VIIStatusBar* statusBar);
	meshObserver(VIIStatusBar* statusBar);
	
	//void update(Mesh* mesh);
	void update();
	void setPercentageProcess(int percentage);
	void setStatusText(std::string message);
	
	void setSubject(Mesh* mesh);
	
	//virtual void setPercentageProcess(int percentage) = 0;
	//virtual void setStatusText(std::string message) = 0;
};

#endif