// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FEATHERWEIGHTLIBRARYAMALGAMATION_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FEATHERWEIGHTLIBRARYAMALGAMATION_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FEATHERWEIGHTLIBRARYAMALGAMATION_EXPORTS
#define FEATHERWEIGHTLIBRARYAMALGAMATION_API __declspec(dllexport)
#else
#define FEATHERWEIGHTLIBRARYAMALGAMATION_API __declspec(dllimport)
#endif

// This class is exported from the Featherweight Library Amalgamation.dll
class FEATHERWEIGHTLIBRARYAMALGAMATION_API CFeatherweightLibraryAmalgamation {
public:
	CFeatherweightLibraryAmalgamation(void);
	// TODO: add your methods here.
};

extern FEATHERWEIGHTLIBRARYAMALGAMATION_API int nFeatherweightLibraryAmalgamation;

FEATHERWEIGHTLIBRARYAMALGAMATION_API int fnFeatherweightLibraryAmalgamation(void);
