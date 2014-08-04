// Featherweight Library Amalgamation.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Featherweight Library Amalgamation.h"


// This is an example of an exported variable
FEATHERWEIGHTLIBRARYAMALGAMATION_API int nFeatherweightLibraryAmalgamation=0;

// This is an example of an exported function.
FEATHERWEIGHTLIBRARYAMALGAMATION_API int fnFeatherweightLibraryAmalgamation(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Featherweight Library Amalgamation.h for the class definition
CFeatherweightLibraryAmalgamation::CFeatherweightLibraryAmalgamation()
{
	return;
}
