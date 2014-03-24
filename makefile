
COMPILER = g++
#INCLUDE =
#INCLUDE = -I/local/lib/wx/include/msw-unicod-3.0 -I/local/include/wx-3.0 -D_LARGEFILE_SOURCE=unknown -DWXUSINGDLL -DL__WXMSW__
#INCLUDE = -I/usr/local/lib/wx/include/msw-unicod-3.0 -I/usr/local/include/wx-3.0 -D_LARGEFILE_SOURCE=unknown -DWXUSINGDLL -DL__WXMSW__
INCLUDE = -I/usr/local/lib/wx/include/msw-unicode-3.0 -I/usr/local/include/wx-3.0 -D_LARGEFILE_SOURCE=unknown -DWXUSINGDLL -D__WXMSW__

LDFLAG = -lopengl32 -lglu32

WXLIBS = $(shell wx-config --libs) $(shell wx-config --optional-libs gl)
WXINCLUDE = $(shell wx-config --cxxflags)

#WXLIBS = -L/usr/local/lib   -Wl,--subsystem,windows -mwindows -lwx_mswu_xrc-3.0 -lwx_mswu_webview-3.0 \
#		-lwx_mswu_html-3.0 -lwx_mswu_qa-3.0 -lwx_mswu_adv-3.0 -lwx_mswu_core-3.0 -lwx_baseu_xml-3.0 \
#		-lwx_baseu_net-3.0 -lwx_baseu-3.0

#STATICLIBS = /usr/local/lib/libwx_baseu-3.0.dll.a /usr/local/lib/libwx_mswu_core-3.0.dll.a /usr/local/lib/libwx_mswu_gl-3.0.dll.a

OBJECTS =  Source/MeshManager.o Source/Mesh.o Source/Vertex.o Source/main.o Source/VIICanvas.o \
		Source/Face.o Source/Vector3.o Source/loadObjFile.o Source/loadPlyFile.o Source/MeshLoader.o \
		Source/VIIFrame.o

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
	
#alternate: 
#	$(COMPILER) -oVII.exe Source/main.cpp  $(LDFLAG)
	
clean:
	rm -f *.exe Source/*.o