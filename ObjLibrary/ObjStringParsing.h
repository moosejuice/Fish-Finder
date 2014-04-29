//
//  ObjStringParsing.h
//
//  A set of functions used in parsing OBJ files.
//

#ifndef OBJ_STRING_PARSING_H
#define OBJ_STRING_PARSING_H

#include <string>



//
//  nextToken
//
//  Purpose: To determine the index of the next token character
//	     in the specified string.  The next token is here
//	     defined to start with next non-whitespace character
//	     following a whitespace character at or after the
//	     current position.
//  Parameter(s):
//	<1> str: The string to search
//	<2> current: The index to begin searching at
//  Precondition(s): N/A
//  Returns: The index of the beginning of the next token.  If
//	     there is no next token, string::npos is returned.
//  Side Effect: N/A
//

size_t nextToken (const std::string& str, size_t current);

//
//  getTokenLength
//
//  Purpose: To determine the length of the token starting with
//	     the specified character in the specified string.
//	     The token length is here defined as the number of
//	     characters, including the specified character,
//	      before the next whitespace character.
//  Parameter(s):
//	<1> str: The string to search
//	<2> current: The beginning of the token
//  Precondition(s): N/A
//  Returns: The length of the token beginning with current.  If
//	     current is a whitespace character or lies outside
//	     of the string, 0 is returned.
//  Side Effect: N/A
//

size_t getTokenLength (const std::string& str, size_t current);

//
//  nextSlashInToken
//
//  Purpose: To determine the index of the next slash ('/')
//	     character in the current token of the specified
//	     string, and after the specified position.
//  Parameter(s):
//	<1> str: The string to search
//	<2> current: The index to begin searching at
//  Precondition(s): N/A
//  Returns: The index of the next slash in this token.  If
//	     there is no next slash, string::npos is returned.
//  Side Effect: N/A
//

size_t nextSlashInToken(const std::string& str, size_t current);



#endif
