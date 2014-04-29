//
//  ObjStringOperations.h
//

#include <cassert>
#include <string>

#include "ObjStringOperations.h"

using namespace std;



string toLowercase (const string& str)
{
	unsigned int length = str.length();
	string result;

	result.resize(length);
	for(unsigned int i = 0; i < length; i++)
	{
		char c = str[i];
		if(c >= 'A' && c <= 'Z')
			result[i] = c - 'A' + 'a';
		else
			result[i] = c;
	}

	return result;
}

bool endsWith (const std::string& str, const char* a_end)
{
	assert(a_end != NULL);

	return endsWith(str, string(a_end));
}

bool endsWith (const std::string& str, const std::string& end)
{
	unsigned int str_length = str.length();
	unsigned int end_length = end.length();

	if(str_length < end_length)
		return false;

	for(unsigned int i = 1; i <= end_length; i++)
		if(end[end_length - i] != str[str_length - i])
			return false;

	return true;
}

