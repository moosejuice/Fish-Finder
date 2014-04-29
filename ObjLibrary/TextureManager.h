//
//  TextureManager.h
//
//  A global service to handle Textures.
//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

//
//  By default, the ObjLibrary only loads textures of type .bmp.
//    However, it can also load textures of type ".png".  To do
//    this, you will need the following libraries:
//      1. ZLib 1.1.3 by Jean-loup Gailly and Mark Adlerun
//      2. LibPNG 1.0.2 by Guy Eric Schalnat, Group 42, Inc.,
//         Andreas Dilger, Glenn Randers-Pehrson
//      3. (unnamed) PNG loader library by Ben Wyatt
//
//  The assumed organization of files is as follows:
//    glpng.c
//    glpng.h
//    ObjLibrary
//      ObjLibrary library files
//    png
//      png library files
//    zlib
//      zlib library files
//
//  It would also be possible to library files, but those often
//    lead to portability issues.
//
//  To enable loading of .png files, define the macro
//    OBJ_LIBRARY_LOAD_PNG_TEXTURES.
//
//#define OBJ_LIBRARY_LOAD_PNG_TEXTURES



#include <string>

class Texture;



namespace TextureManager
{

//
//  get
//
//  Purpose: To retreive a reference to the texture with the
//	     specified name.  Name comparisons are
//	     case-insensitive.
//  Parameter(s):
//	<1> a_name: The name of the texture
//	<1> name: The name of the texture
//  Precondition(s):
//	<1> a_name != NULL
//  Returns: The Texture with name a_name/name.  If there is no
//	     texture loaded with name a_name/name, and
//	     a_name/name ends in ".bmp" (case-insensitive), a
//	     new Texture loaded from a file named a_name/name is
//	     returned.  Otherwise an all-white dummy texture is
//	     returned.
//  Side Effect: N/A
//

const Texture& get (const char* a_name);
const Texture& get (const std::string& name);

//
//  activate
//
//  Purpose: To activate the texture with the specified name.
//	      Name comparisons are case-insensitive.
//  Parameter(s):
//	<1> a_name: The name of the texture
//	<1> name: The name of the texture
//  Precondition(s):
//	<1> a_name != NULL
//  Returns: N/A
//  Side Effect: The Texture with name a_name/name is activated.
//	     If there is no texture loaded with name
//	     a_name/name, and a_name/name ends in ".bmp"
//	     (case-insensitive), a new Texture loaded from
//	     a file named a_name/name is activated.
//	     Otherwise an all-white dummy texture is
//		 returned.
//

void activate (const char* a_name);
void activate (const std::string& name);

//
//  isLoaded
//
//  Purpose: To determine if a texture with the specified name
//	     exists.  Name comparisons are case-insensitive.
//  Parameter(s):
//	<1> a_name: The name of the texture
//	<1> name: The name of the texture
//  Precondition(s):
//	<1> a_name != NULL
//  Returns: Whether there is a texture with name a_name/name.
//  Side Effect: N/A
//

bool isLoaded (const char* a_name);
bool isLoaded (const std::string& name);

//
//  isDummyTexture
//
//  Purpose: To determine if the specified Texture is the dummy
//	     texture returned when a get command fails.
//  Parameter(s):
//	<1> texture: The texture
//  Precondition(s): N/A
//  Returns: Whether texture is the dummy Texture from get.
//  Side Effect: N/A
//

bool isDummyTexture (const Texture& texture);

//
//  add
//
//  Purpose: To add the texture with the specified OpenGL
//	     texture name to the texture manager.
//  Parameter(s):
//	<1> opengl_name: The OpenGL texture name for the texture
//	<2> a_name: The name of the texture to add
//	<2> name: The name of the texture
//  Precondition(s):
//	<1> opengl_name != 0
//	<2> a_name != NULL
//	<3> !isLoaded(a_name)
//	<2> !isLoaded(name)
//  Returns: The texture with name opengl_name.
//  Side Effect: The texture with OpenGL texture a_name/name
//		 opengl_name is added to the texture manager.
//

const Texture& add (unsigned int opengl_name,
		    const char* a_name);
const Texture& add (unsigned int opengl_name,
		    const std::string& name);

//
//  add
//
//  Purpose: To add the specified Texture to the texture manager
//	     with the specified name.
//  Parameter(s):
//	<1> texture: The Texture
//	<2> a_name: The name of the texture to add
//	<2> name: The name of the texture
//  Precondition(s):
//	<1> texture.isSet()
//	<2> a_name != NULL
//	<3> !isLoaded(a_name)
//	<2> !isLoaded(name)
//  Returns: tetxure.
//  Side Effect: Texture texture is added to the texture manager
//		 with name a_name/name.
//

const Texture& add (const Texture& texture,
		    const char* a_name);
const Texture& add (const Texture& texture,
		    const std::string& name);

//
//  unloadAll
//
//  Purpose: To remove all textures from the texture manager.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: tetxure.
//  Side Effect: All textures are removed from the texture
//		 manager.
//

void unloadAll ();



};	// end of namespace TextureManager

#endif
