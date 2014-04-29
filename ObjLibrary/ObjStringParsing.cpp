//
//  ObjStringParsing.cpp
//

#include <string>

#include "ObjStringParsing.h"

using namespace std;



size_t nextToken (const string& str, size_t current)
{
	size_t length = str.length();
	bool seen_whitespace = false;

	// return out of loop when next token is found
	for(size_t i = current; i < length; i++)
	{
		if(seen_whitespace)
		{
			if(!isspace(str[i]))
				return i;
		}
		else
		{
			if(isspace(str[i]))
				seen_whitespace = true;
		}
	}

	// you only get here if there is no next token
	return string::npos;
}

size_t getTokenLength (const string& str, size_t current)
{
	size_t length = str.length();

	// return out of loop when next token is found
	for(size_t i = current; i < length; i++)
	{
		if(isspace(str[i]))
			return i - current;
	}

	// you only get here if there is no next token
	return length - current;
}

size_t nextSlashInToken (const string& str, size_t current)
{
	size_t length = str.length();

	// return out of loop when next token is found
	for(size_t i = current; i < length; i++)
	{
		if(str[i] == '/')
			return i;
		else if(isspace(str[i]))
			return string::npos;
	}

	// you only get here if there is no next token
	return string::npos;
}
