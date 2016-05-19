#ifndef _hosttype_H
#define _hosttype_H
/**
	NI CONFIDENTIAL
	(c) Copyright 1990-2016 by National Instruments Corp.
	All rights reserved.

	@file
	@brief	Host specific definitions, etc.

*/

#if Mac // use forward includes to define types needed for managerp.h
struct EventRecord;
struct RGBColor;
typedef struct Palette *PalettePtr, **PaletteHandle;
typedef struct Cursor *CursPtr, **CursHandle;
typedef struct Picture  *PicPtr, **PicHandle;
typedef struct GDevice *GDPtr, **GDHandle;
typedef struct OpaqueWindowPtr *WindowPtr;
typedef struct OpaqueMenuRef *MenuRef,  *MenuHandle;
typedef struct OpaqueGrafPtr *GrafPtr, *CGrafPtr, *GWorldPtr;
struct BitMap;
struct Pattern;
#include <stdio.h>

#endif	/* Mac */

#if Unix
#include <stdio.h>
#include <string.h>
#endif /* Unix */

#if MSWin
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

#ifndef _WIN32_WINNT
	#if _MSC_VER <= 1499 // MSVC 8.0 or earlier
		#define _WIN32_WINNT 0x0400
	#else
		#if (OpSystem==kMSWin32)
			#define _WIN32_WINNT 0x0501
		#else
			#define _WIN32_WINNT 0x0600
		#endif // (OpSystem==kMSWin32)
	#endif
#else
	#ifndef MSWin_DISABLE_MIN_WINVER_CHECK
		#if _MSC_VER <= 1499 // MSVC 8.0 or earlier
			#if (_WIN32_WINNT < 0x0400)
				#error _WIN32_WINNT must be >= 0x0400.
			#endif // (_WIN32_WINNT < 0x0400)
		#else
			/* Ensure that the _WIN32_WINNT version is adequate. */
			#if (OpSystem==kMSWin32)
				#if (_WIN32_WINNT < 0x0501)
					#undef _WIN32_WINNT
					#define _WIN32_WINNT 0x0501
				#endif // (_WIN32_WINNT < 0x0501)
			#else
				#if (_WIN32_WINNT < 0x0600)
					#undef _WIN32_WINNT
					#define _WIN32_WINNT 0x0600
				#endif // (_WIN32_WINNT < 0x0600)
			#endif // (OpSystem==kMSWin32)
		#endif
	#endif /* MSWin_DISABLE_MIN_WINVER_CHECK */
#endif /* #ifndef _WIN32_WINNT */

#pragma warning (push)
#pragma warning (disable : 4701) /* local variable 'XXX' may be used without having been initialized */
#include <windows.h>
#include <ole2.h>
#pragma warning (pop)
#pragma warning (disable : 4001) /* nonstandard extension 'single line comment' was used */

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1
#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0
#endif /* MSWin */

#endif /* _hosttype_H */
