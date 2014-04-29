//
//  TextureManager.cpp
//

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "ObjStringOperations.h"
#include "Texture.h"
#include "TextureBmp.h"
#include "TextureManager.h"

#ifdef OBJ_LIBRARY_LOAD_PNG_TEXTURES
	#include "GetGlut.h"
	#include "../glpng.h"
#endif

using namespace std;
using namespace TextureManager;
namespace
{
	struct TextureData
	{
		string m_name;
		Texture m_texture;
	};

	vector<TextureData*> g_textures;
	Texture g_white;

	//
	//  getDummyTetxure
	//
	//  Purpose: To retreive a reference to the dummy
	//	     texture.
	//  Parameter(s): N/A
	//  Precondition(s): N/A
	//  Returns: A reference to the dummy texture.
	//  Side Effect: If the dummy texture has not been
	//		 generated, it is generated.
	//

	const Texture& getDummyTexture ()
	{
		if(!g_white.isSet())
		{
			TextureBmp white;
			g_white.set(white.addToOpenGL());
		}

		return g_white;
	}
}



const Texture& TextureManager :: get (const char* a_name)
{
	assert(a_name != NULL);

	return get(string(a_name));
}

const Texture& TextureManager :: get (const string& name)
{
	string lower = toLowercase(name);
	unsigned int texture_count = g_textures.size();

	for(unsigned int i = 0; i < texture_count; i++)
		if(g_textures[i]->m_name.compare(lower) == 0)
			return g_textures[i]->m_texture;

	if(endsWith(lower, ".bmp"))
	{
		TextureBmp texture_bmp(name.c_str());
		if(texture_bmp.isBad())
		{
			// TextureBmp prints loading error
			return getDummyTexture();
		}
		else
		{
			// flip texture to match Maya
			texture_bmp.mirrorY();
			return add(texture_bmp.addToOpenGL(), lower);
		}
	}
	else if(endsWith(lower, ".png"))
	{
#ifdef OBJ_LIBRARY_LOAD_PNG_TEXTURES
		unsigned int texture_name = pngBind(lower.c_str(), PNG_BUILDMIPMAPS, PNG_SOLID, NULL, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		if(texture_name == 0)
			return getDummyTexture();
		else
			return add(texture_name, lower);
#else
		cerr << "Error: Loading .png textures is disabled: " << lower << endl;
		return getDummyTexture();
#endif
	}
	else
	{
		cerr << "Error: Invalid image file extension: " << lower << endl;
		return getDummyTexture();
	}
}

void TextureManager :: activate (const char* a_name)
{
	assert(a_name != NULL);

	get(string(a_name)).activate();
}

void TextureManager :: activate (const std::string& name)
{
	get(name).activate();
}

bool TextureManager :: isLoaded (const char* a_name)
{
	assert(a_name != NULL);

	return isLoaded(string(a_name));
}

bool TextureManager :: isLoaded (const string& name)
{
	string lower = toLowercase(name);

	for(unsigned int i = 0; i < g_textures.size(); i++)
		if(g_textures[i]->m_name.compare(lower) == 0)
			return true;
	return false;
}

bool TextureManager :: isDummyTexture (const Texture& texture)
{
	if(texture == getDummyTexture())
		return true;
	else
		return false;
}



const Texture& TextureManager :: add (unsigned int opengl_name, const char* a_name)
{
	assert(opengl_name != 0);
	assert(a_name != NULL);
	assert(!isLoaded(a_name));

	return add(Texture(opengl_name), string(a_name));
}

const Texture& TextureManager :: add (unsigned int opengl_name, const string& name)
{
	assert(opengl_name != 0);
	assert(!isLoaded(name));

	return add(Texture(opengl_name), name);
}

const Texture& TextureManager :: add (const Texture& texture, const char* a_name)
{
	assert(texture.isSet());
	assert(a_name != NULL);
	assert(!isLoaded(a_name));

	return add(texture, string(a_name));
}

const Texture& TextureManager :: add (const Texture& texture, const string& name)
{
	assert(texture.isSet());
	assert(!isLoaded(name));

	string lower = toLowercase(name);
	unsigned int texture_count = g_textures.size();

	g_textures.push_back(new TextureData);
	g_textures[texture_count]->m_name = lower;
	g_textures[texture_count]->m_texture = texture;

	return g_textures[texture_count]->m_texture;
}

void unloadAll ()
{
	for(unsigned int i = 0; i < g_textures.size(); i++)
		delete g_textures[i];	// destructor frees video memory
	g_textures.clear();
}
