
// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "main.h"

 bool VIIApp::OnInit()
 {
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load("mainGui.xrc");
	
	VIIFrame *frame = new VIIFrame( "Hello World", wxPoint(50, 50), wxSize(1024, 768) );
	frame->Show(true);
	
	return true;
 }
 
 
 wxIMPLEMENT_APP(VIIApp);
/*

class MyApp: public wxApp
{
	public:   
	virtual bool OnInit();
	wxGLCanvas* MyGLCanvas;
 };
 
 class MyFrame: public wxFrame
 {
 public:    
	 MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
 private:    
	 void quitProgram();
	 void OnOpen(wxCommandEvent& event);    
	 void OnExit(wxCommandEvent& event);    
	 void OnAbout(wxCommandEvent& event);

	 void TurnEdges(wxCommandEvent& event);
	 
	 void createFlatSurface(wxCommandEvent& event);
	 void createCube(wxCommandEvent& event);
	 void refreshSurface(wxCommandEvent& event);
	 void circumference(wxCommandEvent& event);
	 
	 void OnClose(wxCloseEvent& event);
	 wxDECLARE_EVENT_TABLE();
 };
 
 enum{
	ID_CIRCUMFERENCE = 1,
	ID_VIEW_EDGES=5,
	ID_CREATE_FLAT_SURFACE = 2,
	ID_CREATE_CUBE = 3,
	ID_REFRESH=4
 };
 
 wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)    
	 EVT_MENU(wxID_OPEN,   MyFrame::OnOpen)    
	 EVT_MENU(wxID_EXIT,  MyFrame::OnExit)    
	 EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	 EVT_MENU(ID_VIEW_EDGES, MyFrame::TurnEdges)
	 EVT_MENU(ID_CREATE_FLAT_SURFACE, MyFrame::createFlatSurface)
	 EVT_MENU(ID_CREATE_CUBE,MyFrame::createCube)
	 EVT_MENU(ID_REFRESH,MyFrame::refreshSurface)
	 EVT_MENU(ID_CIRCUMFERENCE,MyFrame::circumference);
	 EVT_CLOSE(MyFrame::OnClose)
 wxEND_EVENT_TABLE()
 
 wxIMPLEMENT_APP(MyApp);
 bool MyApp::OnInit()
 {
	 MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(1024, 768) );
	 
	 int args[] = {WX_GL_RGBA,WX_GL_DOUBLEBUFFER,WX_GL_DEPTH_SIZE,16,0};
	 MyGLCanvas = new VIICanvas(frame,args,1945);
	 //hallll
	 frame->Show( true );
	 return true;
 }
 
 
 void MyFrame::OnClose(wxCloseEvent& event)
{
	quitProgram();
}
 
 
 MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(NULL, wxID_ANY, title, pos, size)
{    
	wxMenu *menuFile = new wxMenu;
	 menuFile->Append(wxID_OPEN, "&Open Mesh...\tCtrl-O",
	 "Help string shown in status bar for this menu item");
	 menuFile->AppendSeparator();
	 menuFile->Append(wxID_EXIT);
	 
	 wxMenu *menuView = new wxMenu;
	 menuView->Append(ID_VIEW_EDGES,"&Show Edges");//Unicode haekchen: 2713
	 
	 wxMenu* menuEdit = new wxMenu;
	 wxMenu* menuVII = new wxMenu;
	 menuVII->Append(ID_CIRCUMFERENCE,"&Circumference");
	 
	 wxMenu *menuSurfaces = new wxMenu;
	 menuSurfaces->Append(ID_CREATE_FLAT_SURFACE,"&Flat Surface");
	 menuSurfaces->Append(ID_CREATE_CUBE,"&Cube");
	 menuSurfaces->Append(ID_REFRESH,"&Refresh");
	 
	 wxMenu *menuHelp = new wxMenu;
	 menuHelp->Append(wxID_ABOUT);
	 wxMenuBar *menuBar = new wxMenuBar;
	 menuBar->Append( menuFile    , "&File" );
	 menuBar->Append(menuEdit     , "&Edit");
	 menuBar->Append(menuView     , "&View");
	 menuBar->Append( menuSurfaces, "&Create Surface");
	 menuBar->Append(menuVII      ,"&VII Functions");
	 menuBar->Append( menuHelp    , "&Help" );
	 SetMenuBar( menuBar );
	 CreateStatusBar();
	 SetStatusText( "Welcome to wxWidgets!" );
 }
 
 void MyFrame::quitProgram()
 {
	//Close(true);
	Destroy();
 }
 
 void MyFrame::OnExit(wxCommandEvent& event)
 {
	//Close( true );
	std::cout << "Exit Program" << std::endl;
	quitProgram();
 }
 
 void MyFrame::OnAbout(wxCommandEvent& event)
 {
	 wxMessageBox( "This is a wxWidgets' Hello world sample",
				   "About Hello World", wxOK | wxICON_INFORMATION );
 }
 
 void MyFrame::OnOpen(wxCommandEvent& event)
 {
	//wxLogMessage("Hello world from wxWidgets!");
	
	wxFileDialog openFileDialog(this,_("Open Mesh file"),"","","Mesh files (*.ply;*.obj)|*.ply;*.obj",
								wxFD_OPEN|wxFD_FILE_MUST_EXIST);
								
	if(openFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	
	wxString Path = openFileDialog.GetPath();
	MeshLoader loader;
	Mesh* mesh = loader.loadMeshFile(Path.ToStdString());
	if(mesh == NULL)
	{
		wxLogMessage("Cannot Load File");
		return;
	}
	MeshManager* manager = MeshManager::getSingleton();
	manager->addMesh(mesh);
	Refresh();
 }
 
void MyFrame::TurnEdges(wxCommandEvent& event)
{
	static bool on = false;
	on = !on;
	wxWindowList children = GetChildren();
	//std::cout << children.GetCount() << std::endl;
	wxWindowList::iterator iter;
	for(iter = children.begin();iter != children.end();++iter)
	{
		wxWindow* windows = *iter;
		if(windows->GetId() == 1945)
		{
			//std::cout << "drin " << on << std::endl;
			VIICanvas* canvas = (VIICanvas*)windows;
			canvas->activateEdges(on);
			break;
		}
	}
	
	wxMenuItem* item = (wxMenuItem*)event.GetEventObject();
	if(item.getId() == ID_VIEW_EDGES)
	{
		std::cout << "gefunden" << std::endl;
	}
}
 
void MyFrame::createFlatSurface(wxCommandEvent& event)
{
	MeshManager* manager = MeshManager::getSingleton();
	
	std::set<Vertex*> vertices;
	std::vector<Vertex*> vertices2;//(20*20,0);
	std::set<Face*> faces;
	
	for(int j=-10;j<11;j++)
	{
		for(int i=-10;i<11;i++)
		{
			Vertex* vert = new Vertex(Vector3(i,j,0));
			vert->setIndex((i+10)+(j+10)*20);
			//vertices.insert(vert);
			//vertices2[(i+10)+(j+10)*20] = vert;
			vertices2.push_back(vert);
		}	
	}
	
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			Vertex* A = vertices2[i+20*j];
			Vertex* B = vertices2[(i+1)+20*j];
			Vertex* C = vertices2[(i+1)+20*(j+1)];
			Vertex* D = vertices2[i+20*(j+1)];
			
			Face* fA = new Face(A,B,C);
			Face* fB = new Face(A,C,D);
			faces.insert(fA);
			faces.insert(fB);
		}
	}
	
	vertices = std::set<Vertex*>(vertices2.begin(),vertices2.end());
	
	Mesh* mesh = new Mesh(vertices,faces);
	manager->addMesh(mesh);
	Refresh();
	//std::cout << "Update" << std::endl;
	//Update();
}

void MyFrame::createCube(wxCommandEvent& event)
{
	MeshManager* manager = MeshManager::getSingleton();
	std::set<Vertex*> vertices;
	std::set<Face*> faces;
	Vertex* vertice[8];
	Face* face[12];
	vertice[0] = new Vertex(Vector3(-1,-1,1));
	vertice[1] = new Vertex(Vector3( 1,-1,1));
	vertice[2] = new Vertex(Vector3(-1, 1,1));
	vertice[3] = new Vertex(Vector3( 1, 1,1));
	
	vertice[4] = new Vertex(Vector3(-1,-1,-1));
	vertice[5] = new Vertex(Vector3( 1,-1,-1));
	vertice[6] = new Vertex(Vector3(-1, 1,-1));
	vertice[7] = new Vertex(Vector3( 1, 1,-1));
	
	vertice[0]->setIndex(0);
	vertice[1]->setIndex(1);
	vertice[2]->setIndex(2);
	vertice[3]->setIndex(3);
	
	vertice[4]->setIndex(4);
	vertice[5]->setIndex(5);
	vertice[6]->setIndex(6);
	vertice[7]->setIndex(7);
	
	face[0] = new Face(vertice[0],vertice[1],vertice[2]);
	face[1] = new Face(vertice[3],vertice[2],vertice[1]);
	
	face[2] = new Face(vertice[4],vertice[6],vertice[5]);
	face[3] = new Face(vertice[7],vertice[6],vertice[5]);
	
	face[4] = new Face(vertice[2],vertice[3],vertice[4]);
	face[5] = new Face(vertice[4],vertice[3],vertice[5]);
	
	face[6] = new Face(vertice[3],vertice[1],vertice[7]);
	face[7] = new Face(vertice[7],vertice[1],vertice[5]);
	
	face[8] = new Face(vertice[0],vertice[2],vertice[6]);
	face[9] = new Face(vertice[0],vertice[6],vertice[4]);
	
	face[10] = new Face(vertice[5],vertice[0],vertice[4]);
	face[11] = new Face(vertice[0],vertice[5],vertice[1]);
	
	for(int i=0;i<8;i++)
	{
		vertices.insert(vertice[i]);
	}
	for(int i=0;i<12;i++)
	{
		faces.insert(face[i]);
	}
	Mesh* mesh = new Mesh(vertices,faces);
	manager->addMesh(mesh);
	Refresh();
}

void MyFrame::refreshSurface(wxCommandEvent& event)
{
	Refresh();
}

*/