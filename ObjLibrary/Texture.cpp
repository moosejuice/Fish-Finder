//
//  Texture.cpp
//

#include <cassert>
#include <string>	// for NULL

#include "GetGlut.h"
#include "Texture.h"

#include <iostream>
using namespace std;



Texture :: Texture ()
{
	mp_data = NULL;

	assert(invariant());
}

Texture :: Texture (unsigned int name)
{
	assert(name != 0);

	mp_data = NULL;
	set(name);

	assert(invariant());
}

Texture :: Texture (const Texture& original)
{
	mp_data = NULL;
	copy(original);

	assert(invariant());
}

Texture& Texture :: operator= (const Texture& original)
{
	if(&original != this)
	{
		setNone();
		copy(original);
	}

	assert(invariant());
	return *this;
}

Texture :: ~Texture ()
{
	setNone();
}



bool Texture :: isSet () const
{
	if(mp_data != NULL)
		return true;
	else
		return false;
}

unsigned int Texture :: getOpenGLName () const
{
	assert(isSet());

	assert(mp_data != NULL);
	return mp_data->m_texture_name;
}

void Texture :: activate () const
{
	assert(isSet());

	assert(mp_data != NULL);
	glBindTexture(GL_TEXTURE_2D, mp_data->m_texture_name);
}

bool Texture :: operator== (const Texture& other) const
{
	if(mp_data == NULL || other.mp_data == NULL)
		return false;

	assert(mp_data != NULL);
	assert(other.mp_data != NULL);
	if(mp_data->m_texture_name == other.mp_data->m_texture_name)
		return true;
	else
		return false;
}



void Texture :: set (unsigned int name)
{
	assert(name != 0);

	setNone();

	assert(mp_data == NULL);
	mp_data = new Texture::InnerData;
	mp_data->m_texture_name = name;
	mp_data->m_usages = 1;

	assert(mp_data != NULL);
	assert(invariant());
}

void Texture :: setNone ()
{
	if(isSet())
	{
		assert(mp_data->m_usages > 0);
		mp_data->m_usages--;

		if(mp_data->m_usages == 0)
		{
			// void glDeleteTextures(GLsizei n, const GLuint *textureNames); 
			glDeleteTextures(1, &(mp_data->m_texture_name));

			delete mp_data;
		}

		mp_data = NULL;
	}

	assert(mp_data == NULL);
	assert(invariant());
}



void Texture :: copy (const Texture& original)
{
	assert(!isSet());

	mp_data = original.mp_data;
	if(mp_data != NULL)
		mp_data->m_usages++;

	assert(invariant());
}

bool Texture :: invariant () const
{
	if(mp_data != NULL && mp_data->m_texture_name == 0) return false;
	if(mp_data != NULL && mp_data->m_usages < 1) return false;
	return true;
}
