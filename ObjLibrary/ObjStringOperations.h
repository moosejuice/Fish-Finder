//
//  ObjStringOperations.h
//

#ifndef OBJ_STRING_OPERATIONS_H
#define OBJ_STRING_OPERATIONS_H

#include <string>



//
//  toLowercase
//
//  Purpose: To convert the specified string to lowercase.
//  Parameter(s):
//	<1> str: The string to convert
//  Precondition(s): N/A
//  Returns: a_str in lowercase.
//  Side Effect: N/A
//

std::string toLowercase (const std::string& str);

//
//  endsWith
//
//  Purpose: To determine if the specified string ends with the
//	     specified C-string.
//  Parameter(s):
//	<1> str: The string to test
//	<2> end: The end C-string
//  Precondition(s):
//	<1> a_end != NULL
//  Returns: Whether str ends with end.
//  Side Effect: N/A
//

bool endsWith (const std::string& str, const char* a_end);

//
//  endsWith
//
//  Purpose: To determine if the specified string ends with the
//	     specified other string.
//  Parameter(s):
//	<1> str: The string to test
//	<2> end: The end string
//  Precondition(s): N/A
//  Returns: Whether str ends with end.
//  Side Effect: N/A
//

bool endsWith (const std::string& str, const std::string& end);

#endif
