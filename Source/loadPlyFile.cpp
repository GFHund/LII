#include "MeshLoader.h"

enum plyElements
{
	PLY_MAGIC_WORD,
	FORMAT,
	COMMENT,
	ELEMENT,
	PROPERTY,
	END_HEADER,
	NONE
};

plyElements parseP(char* text,int length)
{
	switch(text[1])
	{
		case 'l':
		{
			if(text[2] == 'y')
			{
				return PLY_MAGIC_WORD;
			}
		}
		case 'r':
		{
			return PROPERTY;
		}
	}
}

plyElements parseE(char* text,int length)
{
	switch(text[1])
	{
		case 'l':
		{
			return END_HEADER;
		}
		case 'n':
		{
			return PROPERTY;
		}
	}
}

plyElements parseRow(char* text,int length)
{
	switch(text[0])
	{
		case 'p':
		{
			return parseP(text,length);
		}
		case 'f':
		{
			return FORMAT;
		}
		case 'c':
		{
			return COMMENT;
		}
		case 'e':
		{
			return parseE(text,length);
		}
	}
}

Mesh* MeshLoader::loadPlyFile(std::string filename)
{
	plyElements word = NONE;
	int lengthRow=0;
	char* curRow;
	
	
	std::ifstream is;
	is.open(filename.c_str(),std::ifstream::in);
	
	is.seekg(0,is.end);
	int length = is.tellg();
	is.seekg(0,is.beg);
	char* file = new char[length];
	is.read(file,length);
	is.close();
	
	curRow = file;
	lengthRow = strchr(curRow,'\n') - curRow;
	do
	{
		word = parseRow(curRow,lengthRow);
		
		switch(word)
		{
			case FORMAT:
			{
			
			}
		}
		if((curRow-file)+lengthRow+1 > length)
		{
			return NULL;
		}
		curRow = curRow + lengthRow + 1;
		lengthRow = strchr(curRow,'\n') - curRow;
	}while(word != END_HEADER);

	return NULL;
}