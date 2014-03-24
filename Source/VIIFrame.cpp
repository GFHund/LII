#include "VIIFrame.h"

VIIFrame::VIIFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
{
	wxXmlResource::Get()->LoadFrame(this,NULL,"VIIFrame");
	
	wxPanel* panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(600,600));
	
	int args[] = {WX_GL_RGBA,WX_GL_DOUBLEBUFFER,WX_GL_DEPTH_SIZE,16,0};
	//viiCanvas = new VIICanvas(this,args,1945,wxSize(500,500));
	mViiCanvas = new VIICanvas(panel,args,1945,wxSize(500,500));
	
	wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);
	//boxSizer->Add(viiCanvas,1,wxEXPAND);
	boxSizer->Add(mViiCanvas);
	
	this->mListBox = new wxListBox(panel,2000,wxDefaultPosition,wxSize(100,100));
	//wxListBox* listBox = new wxListBox(this,2000,wxDefaultPosition,wxSize(100,100));
	//boxSizer->Add(listBox,0,wxALIGN_RIGHT);
	wxString noneItem("none");
	mListBox->InsertItems(1,&noneItem,0);
	
	boxSizer->Add(mListBox);
	
	SetSizerAndFit(boxSizer);
	
}


 void VIIFrame::quitProgram()
 {
	//Close(true);
	Destroy();
 }
 
 void VIIFrame::OnExit(wxCommandEvent& event)
 {
	//Close( true );
	std::cout << "Exit Program" << std::endl;
	quitProgram();
 }
 
 void VIIFrame::OnAbout(wxCommandEvent& event)
 {
	 wxMessageBox( "This is a wxWidgets' Hello world sample",
				   "About Hello World", wxOK | wxICON_INFORMATION );
 }
 
 void VIIFrame::OnOpen(wxCommandEvent& event)
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
 /*
	toDo: Button Checked machen oder nicht
 */
void VIIFrame::TurnEdges(wxCommandEvent& event)
{
	static bool on = false;
	on = !on;
	
	mViiCanvas->activateEdges(on);
	/*
	viiCanvas
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
	*/
}
 
void VIIFrame::createFlatSurface(wxCommandEvent& event)
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

void VIIFrame::createCube(wxCommandEvent& event)
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
	Refresh(false);
	//Update();
}

void VIIFrame::refreshSurface(wxCommandEvent& event)
{
	Refresh();
}

void VIIFrame::circumference(wxCommandEvent& event)
{
	wxTextEntryDialog* textDialog = new wxTextEntryDialog(this,"Enter Radius:");
	if(textDialog->ShowModal() == wxID_CANCEL)
	{
		return;
	}
	
	wxString userString = textDialog->GetValue();
	float radius = atof(userString.c_str());
	if(radius == 0.0f)
	{
		wxMessageBox( "radius is not a number or equal to 0.0",
				   "Error", wxOK | wxICON_ERROR );
		return;
	}
	
	MeshManager* manager = MeshManager::getSingleton();
	Mesh* mesh = manager ->getActiveMesh();
	int id = this->mListBox->GetCount();
	mesh->calculateCircumferenceSmallCircle(id,radius);
	
	std::set<Vertex*> meshVertices = mesh->getVertices();
	Vertex* vertex = *(meshVertices.begin());
	std::pair<std::string,float> metaData = vertex->getMetaData(1);
	wxString label(metaData.first);
	this->mListBox->InsertItems(1,&label,0);
}

void VIIFrame::calculateVII(wxCommandEvent& event)
{
	MeshManager* manager = MeshManager::getSingleton();
	Mesh* mesh = manager ->getActiveMesh();
	//mesh->calculateCircumference();
}

void VIIFrame::OnListItemChanged(wxCommandEvent& event)
{
	if(event.IsSelection())
	{
		int index = event.GetSelection();
		wxString text = event.GetString();
		Mesh* mesh = MeshManager::getSingleton()->getActiveMesh();
		mesh->setCurMetaDataId(index);
	}
}

void VIIFrame::OnClose(wxCloseEvent& event)
{
	quitProgram();
}

wxBEGIN_EVENT_TABLE(VIIFrame, wxFrame)    
	EVT_MENU(wxID_OPEN,   VIIFrame::OnOpen)    
	EVT_MENU(wxID_EXIT,  VIIFrame::OnExit)    
	EVT_MENU(wxID_ABOUT, VIIFrame::OnAbout)
	EVT_MENU(XRCID("ID_VIEW_EDGES"), VIIFrame::TurnEdges)
	EVT_MENU(XRCID("ID_CREATE_FLAT_SURFACE"), VIIFrame::createFlatSurface)
	EVT_MENU(XRCID("ID_CREATE_CUBE"),VIIFrame::createCube)
	//EVT_MENU(XRCID("ID_REFRESH"),MyFrame::refreshSurface)
	EVT_MENU(XRCID("ID_CIRCUMFERENCE"),VIIFrame::circumference)
	EVT_MENU(XRCID("ID_CALCULATE_VII"),VIIFrame::calculateVII)
	EVT_LISTBOX(2000,VIIFrame::OnListItemChanged)
	EVT_CLOSE(VIIFrame::OnClose)
wxEND_EVENT_TABLE()