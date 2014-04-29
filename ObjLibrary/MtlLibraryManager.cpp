//
//  MtlLibraryManager.h
//
//  A global service to handle MtlLibraries.
//

#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "ObjStringOperations.h"
#include "MtlLibrary.h"
#include "MtlLibraryManager.h"

using namespace std;
using namespace MtlLibraryManager;
namespace
{
	std::vector<MtlLibrary*> g_mtl_libraries;
	MtlLibrary g_empty;
}



unsigned int MtlLibraryManager :: getCount ()
{
	return g_mtl_libraries.size();
}

MtlLibrary& MtlLibraryManager :: get (unsigned int index)
{
	assert(index < getCount());

	return *(g_mtl_libraries[index]);
}

MtlLibrary& MtlLibraryManager :: get (const char* a_name)
{
	assert(a_name != NULL);

	return get(string(a_name), cerr);
}

MtlLibrary& MtlLibraryManager :: get (const char* a_name, const string& logfile)
{
	assert(a_name != NULL);
	assert(logfile.compare("") != 0);

	ofstream logstream(logfile.c_str());
	MtlLibrary* p_library = &(get(string(a_name), logstream));
	logstream.close();

	return *p_library;
}

MtlLibrary& MtlLibraryManager :: get (const char* a_name, ostream& r_logstream)
{
	assert(a_name != NULL);

	return get(string(a_name), r_logstream);
}

MtlLibrary& MtlLibraryManager :: get (const string& name)
{
	return get(name, cerr);
}

MtlLibrary& MtlLibraryManager :: get (const string& name, const string& logfile)
{
	assert(logfile.compare("") != 0);

	ofstream logstream(logfile.c_str());
	MtlLibrary* p_library = &(get(name, logstream));
	logstream.close();

	return *p_library;
}

MtlLibrary& MtlLibraryManager :: get (const string& name, ostream& r_logstream)
{
	string lower = toLowercase(name);

	for(unsigned int i = 0; i < g_mtl_libraries.size(); i++)
		if(g_mtl_libraries[i]->getName().compare(lower) == 0)
			return *(g_mtl_libraries[i]);

	if(endsWith(lower, ".mtl"))
		return add(MtlLibrary(name, r_logstream));
	else
		return g_empty;
}

bool MtlLibraryManager :: isLoaded (const char* a_name)
{
	assert(a_name != NULL);

	return isLoaded(string(a_name));
}

bool MtlLibraryManager :: isLoaded (const std::string& name)
{
	string lower = toLowercase(name);

	for(unsigned int i = 0; i < g_mtl_libraries.size(); i++)
		if(g_mtl_libraries[i]->getName().compare(lower) == 0)
			return true;
	return false;
}

MtlLibrary& MtlLibraryManager :: add (const MtlLibrary& mtl_library)
{
	assert(!isLoaded(mtl_library.getName()));

	unsigned int index = g_mtl_libraries.size();
	g_mtl_libraries.push_back(new MtlLibrary(mtl_library));

	return *(g_mtl_libraries[index]);
}

void MtlLibraryManager :: unloadAll ()
{
	for(unsigned int i = 0; i < g_mtl_libraries.size(); i++)
		delete g_mtl_libraries[i];
	g_mtl_libraries.clear();
}

void MtlLibraryManager :: loadDisplayTextures ()
{
	// such simple code for such a powerful command...

	for(unsigned int i = 0; i < g_mtl_libraries.size(); i++)
		g_mtl_libraries[i]->loadDisplayTextures();
}

void MtlLibraryManager :: loadAllTextures ()
{
	// such simple code for such a powerful command...

	for(unsigned int i = 0; i < g_mtl_libraries.size(); i++)
		g_mtl_libraries[i]->loadAllTextures();
}
