
COMPILER = g++
#INCLUDE =
#INCLUDE = -I/local/lib/wx/include/msw-unicod-3.0 -I/local/include/wx-3.0 -D_LARGEFILE_SOURCE=unknown -DWXUSINGDLL -DL__WXMSW__
#INCLUDE = -I/usr/local/lib/wx/include/msw-unicod-3.0 -I/usr/local/include/wx-3.0 -D_LARGEFILE_SOURCE=unknown -DWXUSINGDLL -DL__WXMSW__
INCLUDE = -I/usr/local/lib/wx/include/msw-unicode-3.0 -I/usr/local/include/wx-3.0 -D_LARGEFILE_SOURCE=unknown -DWXUSINGDLL -D__WXMSW__

CXXFLAGS = -std=c++0x
LDFLAG = -lopengl32 -lglu32

WXLIBS = $(shell wx-config --libs) $(shell wx-config --optional-libs gl)
WXINCLUDE = $(shell wx-config --cxxflags)

#WXLIBS = -L/usr/local/lib   -Wl,--subsystem,windows -mwindows -lwx_mswu_xrc-3.0 -lwx_mswu_webview-3.0 \
#		-lwx_mswu_html-3.0 -lwx_mswu_qa-3.0 -lwx_mswu_adv-3.0 -lwx_mswu_core-3.0 -lwx_baseu_xml-3.0 \
#		-lwx_baseu_net-3.0 -lwx_baseu-3.0

#STATICLIBS = /usr/local/lib/libwx_baseu-3.0.dll.a /usr/local/lib/libwx_mswu_core-3.0.dll.a /usr/local/lib/libwx_mswu_gl-3.0.dll.a

OBJECTS = Source/main.o Source/VIIFrame.o Source/VIIStatusBar.o Source/VIICanvas.o \
		  Source/colorLegend.o Source/colorChangeEvent.o Source/minMaxColorDlg.o \
		  Source/MeshManager.o Source/Mesh.o Source/Vertex.o Source/Face.o Source/Vector3.o \
		  Source/loadObjFile.o Source/loadPlyFile.o Source/MeshLoader.o Source/MeshObserver.o

#OBJECTS = Source/main.o 
#Source/VIICanvas.o

all: $(OBJECTS)
#	$(COMPILER) -oVII.exe $(OBJECTS) $(STATICLIBS) $(LDFLAG)
#	$(COMPILER) 'wx-config --cxxflags' $(OBJECTS) 'wx-config --libs --gl-libs'
	$(COMPILER) -oVII $(OBJECTS) $(WXLIBS) $(LDFLAG)

Source/main.o: Source/main.cpp
	#$(COMPILER) -c -o Source/main.o $(INCLUDE) Source/main.cpp
	$(COMPILER) -c -o Source/main.o $(WXINCLUDE) Source/main.cpp
	
Source/VIICanvas.o: Source/VIICanvas.h Source/VIICanvas.cpp
	#$(COMPILER) -c -o Source/VIICanvas.o $(INCLUDE) Source/VIICanvas.cpp 
	$(COMPILER) -c -o Source/VIICanvas.o $(WXINCLUDE) Source/VIICanvas.cpp 
	
Source/VIIFrame.o: Source/VIIFrame.h Source/VIIFrame.cpp
	$(COMPILER) -c -o Source/VIIFrame.o $(WXINCLUDE) Source/VIIFrame.cpp
	
Source/colorLegend.o: Source/colorLegend.h Source/colorLegend.cpp
	$(COMPILER) -c -o Source/colorLegend.o $(WXINCLUDE) Source/colorLegend.cpp
	
Source/colorChangeEvent.o: Source/colorChangeEvent.h Source/colorChangeEvent.cpp
	$(COMPILER) -c -o Source/colorChangeEvent.o $(WXINCLUDE) Source/colorChangeEvent.cpp
	
Source/minMaxColorDlg.o: Source/minMaxColorDlg.h Source/minMaxColorDlg.cpp
	$(COMPILER) -c -o Source/minMaxColorDlg.o $(WXINCLUDE) Source/minMaxColorDlg.cpp
	
Source/VIIStatusBar.o: Source/VIIStatusBar.h Source/VIIStatusBar.cpp
	$(COMPILER) -c -o Source/VIIStatusBar.o $(WXINCLUDE) Source/VIIStatusBar.cpp
	
Source/MeshObserver.o: Source/MeshObserver.h Source/MeshObserver.cpp
	$(COMPILER) -c -o Source/MeshObserver.o $(WXINCLUDE) Source/MeshObserver.cpp

Source/MeshManager.o:Source/MeshManager.h Source/MeshManager.cpp
	$(COMPILER) -c -o $@ $(WXINCLUDE) Source/MeshManager.cpp

#%.o: %.cpp
#	$(CXX) -c $(CXXFLAGS) $(WXINCLUDE) $< -o $@
#	$(CXX) -g -c $(CXXFLAGS) $< -o $@	
	
#alternate: 
#	$(COMPILER) -oVII.exe Source/main.cpp  $(LDFLAG)
	
clean:
	rm -f *.exe Source/*.o