#ifndef _extcode_H
#define _extcode_H
/**
	(c) Copyright 1990-2014 by National Instruments Corp.
	All rights reserved.

	@author National Instruments Corp.
	@file
	@brief  This document reflects what is published in the CIN manual.
	
	DO NOT MODIFY THIS FILE. It is automatically generated.
*/

#include "platdefines.h"
#include "fundtypes.h"

/* define this to keep C++ isms from littering the code */
#ifdef __cplusplus
	/* single instance extern C functions: */
	#define EXTERNC extern "C"
	/* single instance extern C VARIABLES (needed because MSVC unnecessarily
	   mangles global variable names): */
	#define EEXTERNC extern "C"
	/* begin of extern c block: */
	#define BEGINEXTERNC extern "C" {
	/* end of externc block */
	#define ENDEXTERNC }
	/* default function argument value */
	#define DEFAULTARG(a)= a
#else
	#define EXTERNC
	#define EEXTERNC extern
	#define BEGINEXTERNC
	#define ENDEXTERNC
	#define DEFAULTARG(a)
#endif /* __cplusplus */

/* Mark a function as using C calling conventions. */
#if !defined(_FUNCC)
	#if MSWin && (ProcessorType == kX86)
		#define _FUNCC __cdecl
	#else
		#define _FUNCC
	#endif
#endif

/* Mark a function as using standard (Pascal) calling conventions. */
#if !defined(_FUNCSTDCALL)
	#if MSWin && (ProcessorType == kX86)
		#define _FUNCSTDCALL __stdcall
	#else
		#define _FUNCSTDCALL
	#endif
#endif

/* FORCE_INLINE: cause a function to be inlined even when not optimizing */
#if MSWin
	#define FORCE_INLINE __forceinline
#elif Compiler == kGCC
	#define FORCE_INLINE inline __attribute__((always_inline))
#else
	#define FORCE_INLINE inline
#endif

/* Multi-threaded categorization tags. */
#ifndef TH_REENTRANT
	/* function is completely reentrant and calls only same */
	#define TH_REENTRANT
#endif
#ifndef TH_PROTECTED
	#define TH_PROTECTED  /* function uses mutex calls protect itself */
#endif
#ifndef TH_SINGLE_UI
	/* function is known to be used only from UI thread */
	#define TH_SINGLE_UI 
#endif
#ifndef TH_UNSAFE
	/* function is NOT thread safe and needs to be made so */
	#define TH_UNSAFE
#endif
	/* Variable tags */
#ifndef TH_READONLY
	/* (global) variable is never written to after startup */
	#define TH_READONLY
#endif

/* Explicitly define this if you want to use deprecated exported functions */
#ifndef USE_DEPRECATED_EXPORTS
	#define USE_DEPRECATED_EXPORTS 0
#endif

/* Debugging ON section Begin */
#ifndef DBG
	#define DBG 1
#endif
/*	Debugging ON section End */

/* Debugging OFF section Begin
#undef DBG
#define DBG 0
 * Debugging OFF section End */

#if defined(__cplusplus)
	#if !defined(NI_STATIC_CAST)
		/** @brief Peform a C++ static cast.
			@param T the type to cast to
			@param v the item to cast
		*/
		#define NI_STATIC_CAST(T,v) static_cast<T>(v)
	#endif /* !defined(NI_STATIC_CAST) */
	#if !defined(NI_CONST_CAST)
		/** @brief Peform a C++ const cast.
			@param T the type to cast to
			@param v the item to cast
		*/
		#define NI_CONST_CAST(T,v) const_cast<T>(v)
	#endif /* !defined(NI_CONST_CAST) */
	#if !defined(NI_REINTERPRET_CAST)
		/** @brief Peform a C++ reinterpret cast.
			@param T the type to cast to
			@param v the item to cast
		*/
		#define NI_REINTERPRET_CAST(T,v) reinterpret_cast<T>(v)
	#endif /* !defined(NI_REINTERPRET_CAST) */
#else /* ! C++ */
	#if !defined(NI_STATIC_CAST)
		/** @brief Peform a C static cast.
			@param T the type to cast to
			@param v the item to cast
		*/
		#define NI_STATIC_CAST(T,v) ((T)(v))
	#endif /* !defined(NI_STATIC_CAST) */
	#if !defined(NI_CONST_CAST)
		/** @brief Peform a C const cast.
			@param T the type to cast to
			@param v the item to cast
		*/
		#define NI_CONST_CAST(T,v) ((T)(v))
	#endif /* !defined(NI_CONST_CAST) */
	#if !defined(NI_REINTERPRET_CAST)
		/** @brief Peform a C reinterpret cast.
			@param T the type to cast to
			@param v the item to cast
		*/
	#define NI_REINTERPRET_CAST(T,v) ((T)(v))
	#endif /* !defined(NI_REINTERPRET_CAST) */
#endif /* defined(__cplusplus) */

#if Mac
	/* These must be defined before we start including Mac headers. */
	#ifndef ACCESSOR_CALLS_ARE_FUNCTIONS
		#define ACCESSOR_CALLS_ARE_FUNCTIONS 1
	#endif
	#ifndef OPAQUE_TOOLBOX_STRUCTS
		#define OPAQUE_TOOLBOX_STRUCTS 1
	#endif
	#include <Carbon/Carbon.h>
#endif // Mac

#include "lv_prolog.h"

#if !Mac
	/* These are native types on the Mac. */
	typedef uChar Str31[32];
	typedef uChar Str255[256];

#if USE_DEPRECATED_EXPORTS
	/* All of these are provided by Types.h on the Mac */
	typedef uChar		*StringPtr, **StringHandle;
	typedef const uChar	*ConstStringPtr;
#endif /* USE_DEPRECATED_EXPORTS */
#endif /* !Mac */

#if !Mac
	/** @brief Compatibility value for Mac-specific error code value.
	    @deprecated Unless using the Mac-specific OSStatus or OSErr type, you should use mgNoErr.

		A future release may place this definition behind the USE_DEPRECATED_EXPORTS guard.
	*/
	#define noErr mgNoErr
#endif /* !Mac */

typedef const uChar	ConstStr255[256];

/* Using 1 instead of 0 avoids a warning in GCC */
#define Offset(type, field)		((NI_REINTERPRET_CAST(size_t,(&NI_REINTERPRET_CAST(type*,1)->field)))-1)


/* Various mechanisms to define opaque types. */
#define LV_PRIVATE(T)	typedef struct T##_t { void *p; } *T
#define LV_PRIVATE_HANDLE(T)	 struct T##_t; typedef struct T##_t **T
#define LV_PRIVATE_POINTER(T)	 struct T##_t; typedef struct T##_t *T
#define LV_PRIVATE_POINTER_FWD(T)	typedef struct T##_t *T /* for forward declarations */

/** Legacy 16-bit Boolean type */
typedef uInt16 LVBooleanU16;
#define LVBooleanU16True	NI_STATIC_CAST(LVBooleanU16,0x8000)
#define LVBooleanU16False	NI_STATIC_CAST(LVBooleanU16,0x0000)

/** Standard Boolean type */
typedef uInt8 LVBoolean;
#define LVBooleanTrue		NI_STATIC_CAST(LVBoolean,1)
#define LVBooleanFalse		NI_STATIC_CAST(LVBoolean,0)
#define LVTRUE				LVBooleanTrue			/* for CIN users */
#define LVFALSE				LVBooleanFalse

/** @brief Opaque type used for various unique identifiers. */
typedef uInt32 MagicCookie;
#define kNotAMagicCookie NI_STATIC_CAST(MagicCookie,0)	/* canonical invalid MagicCookie value */

/** @brief The opaque type used by the Resource Manager. */
typedef MagicCookie RsrcFile;
#define kNotARsrcFile NI_STATIC_CAST(RsrcFile,kNotAMagicCookie)	/* canonical invalid RsrcFile */

/** @brief Basic unsigned character pointer and handle types. */
typedef uChar		*UPtr, **UHandle;
typedef const uChar	*ConstUPtr, **ConstUHandle;
typedef uChar * const *UConstHandle;

/** @brief C-style (NULL-terminated) string types. */
typedef uChar		*CStr;
typedef const uChar	*ConstCStr;

/** @brief Pascal-style string types. 1-byte length followed by data. */
typedef uChar		*PStr, **PStrHandle;
typedef const uChar	*ConstPStr, **ConstPStrHandle;

typedef double floatNum;

/** @brief Concatenated Pascal string types. */
typedef struct {
	int32	cnt;		/* number of pascal strings that follow */
	uChar	str[1];		/* cnt bytes of concatenated pascal strings */
} CPStr, *CPStrPtr, **CPStrHandle;

/** @brief Long Pascal-style string types. */
typedef struct {
	int32	cnt;		/* number of bytes that follow */
	uChar	str[1];		/* cnt bytes */
} LStr, *LStrPtr, **LStrHandle;
typedef LStr const* ConstLStrP;
typedef LStr const*const* ConstLStrH;

/** @brief Opaque type used by the Path Manager API. */
#ifdef __cplusplus
	class PathRef;
#else
	typedef struct PATHREF PathRef;
#endif /* __cplusplus */
typedef PathRef*		Path;
typedef const PathRef*	ConstPath;

/** @brief Translate an error code from any NI product into its text description.
	@param errCode the error code to translate
	@param errText receives the error description
	@return LVBooleanFalse iff error code is not found in the error code text files, LVBooleanTrue if the code was found. */
TH_REENTRANT EXTERNC LVBoolean _FUNCC NIGetOneErrorCode(int32 errCode, LStrHandle *errText);

/** @brief Manager error code type. */
typedef int32 MgErr;

/** @brief Manager error codes. */
enum {
	mgNoErr=0,
	mgArgErr=1,
	mFullErr,			/* Memory Mgr	2-3		*/
	mZoneErr,

	fEOF,				/* File Mgr		4-12	*/
	fIsOpen,
	fIOErr,
	fNotFound,
	fNoPerm,
	fDiskFull,
	fDupPath,
	fTMFOpen,
	fNotEnabled,

	rFNotFound,			/* Resource Mgr 13-15	*/
	rAddFailed,
	rNotFound,

	iNotFound,			/* Image Mgr	16-17	*/
	iMemoryErr,

	dPenNotExist,		/* Draw Mgr		18		*/

	cfgBadType,			/* Config Mgr	19-22	*/
	cfgTokenNotFound,
	cfgParseError,
	cfgAllocError,

	ecLVSBFormatError,	/* extCode Mgr	23		*/
	ecLVSBSubrError,	/* extCode Mgr	24		*/
	ecLVSBNoCodeError,	/* extCode Mgr	25		*/

	wNullWindow,		/* Window Mgr	26-27	*/
	wDestroyMixup,

	menuNullMenu,		/* Menu Mgr		28		*/

	pAbortJob,			/* Print Mgr	29-35	*/
	pBadPrintRecord,
	pDriverError,
	pWindowsError,
	pMemoryError,
	pDialogError,
	pMiscError,

	dvInvalidRefnum,	/* Device Mgr	36-41	*/
	dvDeviceNotFound,
	dvParamErr,
	dvUnitErr,
	dvOpenErr,
	dvAbortErr,

	bogusError,			/* generic error 42 */
	cancelError,		/* cancelled by user 43 */

	OMObjLowErr,		/* object message dispatcher errors 44-52 */
	OMObjHiErr,
	OMObjNotInHeapErr,
	OMOHeapNotKnownErr,
	OMBadDPIdErr,
	OMNoDPinTabErr,
	OMMsgOutOfRangeErr,
	OMMethodNullErr,
	OMUnknownMsgErr,

	mgNotSupported,

	ncBadAddressErr,		/* Net Connection errors 54-66 */
	ncInProgress,
	ncTimeOutErr,
	ncBusyErr,
	ncNotSupportedErr,
	ncNetErr,
	ncAddrInUseErr,
	ncSysOutOfMem,
	ncSysConnAbortedErr,	/* 62 */
	ncConnRefusedErr,
	ncNotConnectedErr,
	ncAlreadyConnectedErr,
	ncConnClosedErr,		/* 66 */

	amInitErr,				/* (Inter-)Application Message Manager 67- */

	occBadOccurrenceErr,	/* 68  Occurrence Mgr errors */
	occWaitOnUnBoundHdlrErr,
	occFunnyQOverFlowErr,

	fDataLogTypeConflict,	/* 71 */
	ecLVSBCannotBeCalledFromThread, /* ExtCode Mgr	72*/
	amUnrecognizedType,
	mCorruptErr,
	ecLVSBErrorMakingTempDLL,
	ecLVSBOldCIN,			/* ExtCode Mgr	76*/

	dragSktNotFound,		/* Drag Manager 77 - 80*/
	dropLoadErr,
	oleRegisterErr,
	oleReleaseErr,

	fmtTypeMismatch,		/* String processing (printf, scanf) errors */
	fmtUnknownConversion,
	fmtTooFew,
	fmtTooMany,
	fmtScanError,

	ecLVSBFutureCIN,		/* ExtCode Mgr	86*/

	lvOLEConvertErr,
	rtMenuErr,
	pwdTampered,			/* Password processing */
	LvVariantAttrNotFound,		/* LvVariant attribute not found 90-91*/
	LvVariantTypeMismatch,		/* Cannot convert to/from type */

	axEventDataNotAvailable,	/* Event Data Not Available 92-96*/
	axEventStoreNotPresent,		/* Event Store Not Present */
	axOccurrenceNotFound,		/* Occurence Not Found */
	axEventQueueNotCreated,		/* Event Queue not created */
	axEventInfoNotAvailable,	/* Event Info is not available */

	oleNullRefnumPassed,		/* Refnum Passed is Null */

	omidGetClassGUIDErr,		/* Error retrieving Class GUID from OMId 98-100*/
	omidGetCoClassGUIDErr,		/* Error retrieving CoClass GUID from OMId */
	omidGetTypeLibGUIDErr,		/* Error retrieving TypeLib GUID from OMId */

	appMagicBad,				/* bad built application magic bytes */

	iviInvalidDowncast,         /* IVI Invalid downcast*/
	iviInvalidClassSesn,		/* IVI No Class Session Opened */

	maxErr,						/* max manager 104-107 */
	maxConfigErr,				/* something not right with config objects */
	maxConfigLoadErr,			/* could not load configuration */
	maxGroupNotSupported,

	ncSockNotMulticast,			/* net connection multicast specific errors 108-112 */
	ncSockNotSinglecast,
	ncBadMulticastAddr,
	ncMcastSockReadOnly,
	ncMcastSockWriteOnly,

	ncDatagramMsgSzErr,			/* net connection Datagram message size error 113 */

	bufferEmpty,				/* CircularLVDataBuffer (queues/notifiers) */
	bufferFull,					/* CircularLVDataBuffer (queues/notifiers) */
	dataCorruptErr,				/* error unflattening data */

	requireFullPathErr,			/* supplied folder path where full file path is required  */
	folderNotExistErr,			/* folder doesn't exist */

	ncBtInvalidModeErr,			/* invalid Bluetooth mode 119 */
	ncBtSetModeErr,				/* error setting Bluetooth mode 120 */

	mgBtInvalidGUIDStrErr,		/* The GUID string is invalid 121 */

	rVersInFuture,			/* Resource file is a future version 122 */

	mgErrTimeOut,			/* General-purpose timeout 123 */
	mgErrStringCannotContainNull,	/* An LStr contained a null character in a place that does not support null characters 124 */
	mgErrStackOverflow,			/* Stack overflow detected 125 */

	ncSocketQueryFailed, /* 126: Failed to query socket state */
	ncNotInetSocket, /* 127: Not an IP4 internet socket */

	mgErrSentinel,	// 128

	mgPrivErrBase = 500,	/* Start of Private Errors */
	mgPrivErrLast = 599,	/* Last allocated in Error DB */


	kAppErrorBase = 1000,	/* Start of application errors */
	kAppLicenseErr = 1380,	/* Failure to check out license error */
	kAppCharsetConvertErr =1396, /* could not convert text from charset to charset */
	kAppErrorLast = 1399	/* Last allocated in Error DB */
};

typedef MagicCookie Occurrence;
#ifndef kNonOccurrence
	#ifdef __cplusplus
		#define kNonOccurrence static_cast<Occurrence>(kNotAMagicCookie)
	#else
		#define kNonOccurrence ((Occurrence)(kNotAMagicCookie))
	#endif
#endif

TH_PROTECTED EXTERNC MgErr _FUNCC Occur(Occurrence o);

/*** Time type ***/
#if OpSystem==kLinux && ProcessorType==kX64
	typedef unsigned long lvtime;
#else
	typedef uInt32 lvtime;
#endif

EXTERNC TH_REENTRANT void StdToT(lvtime *t);
EXTERNC TH_REENTRANT void TToStd(lvtime *t);

/* forward definitions of ATime128 (time stamp) for DLLs and CINs */
#ifdef __cplusplus
class ATime128;
#else
typedef struct ATIME128 ATime128;
#endif /* __cplusplus */
typedef ATime128* ATime128Ptr;

#ifdef __cplusplus
class LvVariant;
#else
typedef struct LVVARIANT LvVariant;
#endif
typedef LvVariant* LvVariantPtr;

/* forward definitions of HWAVEFORM and HWAVES for DLLs and CINs */
#if !defined(__cplusplus) || defined(NICOM_C_INTERFACES)
typedef struct IWaveform IWaveform;
typedef struct IWaves IWaves;
#else
class IWaveform;
class IWaves;
#endif

typedef IWaveform* HWAVEFORM;
typedef IWaves* HWAVES;

/** Used for converting from NICOM to different flavors of LV-WDT */
enum {
	kWDTUniform =0L,	/*< Uniform Flt64 WDT */
	kArrayWDTUniform	/*< Array of uniform flt64 WDT */
};

/*** Numeric Support Functions and Utilities ***/
/** @brief These values describe various scalar numeric types. */
typedef enum {	iB=1, iW, iL, iQ, uB, uW, uL, uQ, fS, fD, fX, cS, cD, cX } NumType;

#define _NumericTypeCast_(T,v)	NI_STATIC_CAST(T,v)
#define _NumericTypeCastTwice_(T1,T2,v) _NumericTypeCast_(T1,_NumericTypeCast_(T2,v))

#define HiNibble(x)		_NumericTypeCast_(uInt8,((x)>>4) & 0x0F)
#define LoNibble(x)		_NumericTypeCast_(uInt8,(x) & 0x0F)
#define HiByte(x)		_NumericTypeCast_(int8,_NumericTypeCast_(int16,x)>>8)
#define LoByte(x)		_NumericTypeCast_(int8,x) 
#define Word(hi,lo)		((_NumericTypeCast_(int16,hi)<<8) | _NumericTypeCastTwice_(int16, uInt8, lo))
#define Hi16(x)			_NumericTypeCast_(int16, _NumericTypeCast_(int32, x) >> 16)
#define Lo16(x)			_NumericTypeCastTwice_(int16, int32, x)
#define Long(hi,lo)		((_NumericTypeCast_(int32,hi)<<16) | _NumericTypeCastTwice_(int32, uInt16,lo))
#define Hi32(x)			_NumericTypeCast_(int32,_NumericTypeCast_(int64,x)>>32)
#define Lo32(x)			_NumericTypeCastTwice_(int32, int64, x)

#define Cat2Chrs(c1,c2) \
		(	((_NumericTypeCastTwice_(int16,uInt8,c1))<< 8) \
		|	((_NumericTypeCastTwice_(int16,uInt8,c2))    ) )
#define Cat4Chrs(c1,c2,c3,c4) \
		(	((_NumericTypeCastTwice_(int32,uInt8,c1))<<24) \
		|	((_NumericTypeCastTwice_(int32,uInt8,c2))<<16) \
		|	((_NumericTypeCastTwice_(int32,uInt8,c3))<< 8) \
		|	((_NumericTypeCastTwice_(int32,uInt8,c4))    ) )
#define Cat8Chrs(c1,c2,c3,c4, c5, c6, c7, c8) \
		(	((_NumericTypeCastTwice_(int64,uInt8,c1))<<56) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c2))<<48) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c3))<<40) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c4))<<32) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c5))<<24) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c6))<<16) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c7))<< 8) \
		|	((_NumericTypeCastTwice_(int64,uInt8,c8))    ) )
#ifdef NIDL
	#define RTToL(c1,c2,c3,c4)	0
#else
#if NI_BIG_ENDIAN
	#define RTToL(c1,c2,c3,c4)	Cat4Chrs(c1,c2,c3,c4)
	#define RTToW(c1,c2)		Cat2Chrs(c1,c2)
	#define IntFrom4Chars(s)	_NumericTypeCast_(int32,s)
#else
	#define RTToL(c1,c2,c3,c4)	Cat4Chrs(c4,c3,c2,c1)
	#define RTToW(c1,c2)		Cat2Chrs(c2,c1)
	#define IntFrom4Chars(s)	((_NumericTypeCast_(int32,s)<<24)|((_NumericTypeCast_(int32,s)&0x0000ff00)<<8)|(_NumericTypeCast_(uInt32,s)>>24)|((_NumericTypeCast_(int32,s)&0x00ff0000)>>8))
#endif /* NI_BIG_ENDIAN */
#endif /* NIDL */

#if !Palm
/** @brief Computes absolute value of a number.
	@param n is an integer argument
	@return the absolute value of n

	@deprecated Call abs() instead.
*/
TH_REENTRANT EXTERNC int32 _FUNCC Abs(int32);

/** @brief Computes min of two numbers.
	@param n the first integer argument
	@param m the second integer argument
	@return the min of n and m */
TH_REENTRANT EXTERNC int32 _FUNCC Min(int32 n, int32 m);

/** @brief Computes max of two numbers.
	@param n the first integer argument
	@param m the second integer argument
	@return the max of n and m */
TH_REENTRANT EXTERNC int32 _FUNCC Max(int32 n, int32 m);
#endif /* !Palm */

#if (ProcessorType==kX86) || (ProcessorType==kM68000)
	#define UseGetSetIntMacros	1
#else
	#define UseGetSetIntMacros	0
#endif

#if UseGetSetIntMacros
	#define GetAWord(p)		(*(int16*)(p))
	#define SetAWord(p,x)	(*(int16*)(p)= x)
	#define GetALong(p)		(*(int32*)(p))
	#define SetALong(p,x)	(*(int32*)(p)= x)
#else
TH_REENTRANT EXTERNC int32 _FUNCC	GetALong(const void *);
TH_REENTRANT EXTERNC int32 _FUNCC	SetALong(void *, int32);
TH_REENTRANT EXTERNC int16 _FUNCC	GetAWord(const void *);
TH_REENTRANT EXTERNC int16 _FUNCC	SetAWord(void *, int16);
#endif

#if !Palm
/* Avoid conflict with functions in LabWindows CVI that can arise for LabVIEW DLLs used in CVI projects. */
#ifndef _CVI_
/** @brief Coerce a value to be in the range [low,high].
	@param i the value to test for coersion
	@param low the lower limit
	@param high the upper limit
	@return the coerced value */
TH_REENTRANT EXTERNC int32 _FUNCC Pin(int32 i, int32 low, int32 high);	
#endif /* _CVI_ */
#endif /* !Palm */

/** @brief Generate a random number between 0 and 1.
	@param xp receives the randomly generated value */
TH_PROTECTED EXTERNC void _FUNCC RandomGen(float64 *xp);

/*** C-style String Support Functions ***/
#if !Palm
TH_REENTRANT EXTERNC Bool32 _FUNCC IsDigit(uChar);
TH_REENTRANT EXTERNC Bool32 _FUNCC IsAlpha(uChar);
TH_REENTRANT EXTERNC Bool32 _FUNCC IsPunct(uChar);
TH_REENTRANT EXTERNC Bool32 _FUNCC IsLower(uChar);
TH_REENTRANT EXTERNC Bool32 _FUNCC IsUpper(uChar);
TH_REENTRANT EXTERNC int32 _FUNCC ToUpper(int32);
TH_REENTRANT EXTERNC int32 _FUNCC ToLower(int32);
TH_REENTRANT EXTERNC uChar _FUNCC HexChar(int32);
TH_REENTRANT EXTERNC int32 _FUNCC StrLen(const uChar *);
TH_REENTRANT EXTERNC int32 _FUNCC StrCat(CStr, ConstCStr);
TH_REENTRANT EXTERNC CStr _FUNCC StrCpy(CStr, ConstCStr);
TH_REENTRANT EXTERNC CStr _FUNCC StrNCpy(CStr, ConstCStr, const size_t);
TH_REENTRANT EXTERNC int32 _FUNCC StrCmp(ConstCStr, ConstCStr);
TH_REENTRANT EXTERNC int32 _FUNCC StrNCmp(ConstCStr, ConstCStr, const size_t);
TH_REENTRANT EXTERNC int32 _FUNCC StrNCaseCmp(ConstCStr, ConstCStr, const size_t);

/** @brief Search a string for a substring.
	@param s the string to search
	@param r the string to search for within s
	@return nonzero value if r is found within s
	
	@note Comparisons are case-insensitive.
	@note Whitespace in s is ignored.
*/
TH_REENTRANT EXTERNC int32 _FUNCC StrIStr(ConstCStr s, ConstCStr r);
#endif /* !Palm */

/*** Pascal-Style String Support Functions ***/
#if __cplusplus
inline uChar*       PStrBuf(const PStr b)		{ return &(b[1]); }
inline uChar&       PStrLen(const PStr b)		{ return b[0]; }	// # of chars in string
inline const uChar* PStrBuf(const ConstPStr b)	{ return &(b[1]); }
inline uChar        PStrLen(const ConstPStr b)	{ return b[0]; }	// # of chars in string
inline uInt16       PStrSize(const ConstPStr b)	{ return static_cast<uInt16>(b?PStrLen(b)+1:0); } // # of bytes including length;
																					   // The return type is uInt16, not uChar. It cannot be uChar since
																					   //	a) Maximum PStr length is 255
																					   //	b) PStrSize is length plus 1
																					   //	c) 255 + 1 = 256
																					   //	d) 256 is greater than the maximum value of a uChar (255)
#else
#define PStrBuf(b)		(&((PStr)(b))[1])
#define PStrLen(b)		(((PStr)(b))[0])				/* # of chars in string */
#define PStrSize(b)		(b?PStrLen(b)+1:0)				/* # of bytes including length */
#endif /* __cplusplus */

TH_REENTRANT EXTERNC int32 _FUNCC PStrCat(PStr, ConstPStr);
TH_REENTRANT EXTERNC PStr _FUNCC PStrCpy(PStr, ConstPStr);
TH_REENTRANT EXTERNC PStr _FUNCC PStrNCpy(PStr, ConstPStr, int32);
TH_REENTRANT EXTERNC int32 _FUNCC PStrCmp(ConstPStr, ConstPStr);
TH_REENTRANT EXTERNC int32 _FUNCC PPStrCmp(ConstPStr*, ConstPStr*);
TH_REENTRANT EXTERNC int32 _FUNCC PStrCaseCmp(ConstPStr, ConstPStr);
TH_REENTRANT EXTERNC int32 _FUNCC PPStrCaseCmp(ConstPStr*, ConstPStr*);
TH_REENTRANT EXTERNC int32 _FUNCC PToCStr(ConstPStr, CStr);
TH_REENTRANT EXTERNC PStr _FUNCC PStrDup(ConstPStr buf);
TH_REENTRANT EXTERNC int32 _FUNCC CToPStr(ConstCStr, PStr);

/*** Long Pascal-Style String Support Functions ***/

/* Helpers for LStr handles that allow for empty strings encoded as NULL handles.
   Use LHStr macros instead of passing a *h to LStrBuf/Len/Size for right hand side refs. */
#define LHStrPtr(sh)	((sh)?*(sh):NULL)				/* Get LStr* (produces NULL ptr for NULL handle */
#define LHStrBuf(sh)	((sh)?(&(*(sh))->str[0]):NULL)	/* same as LStrBuf, but on string handle */
#define LHStrLen(sh)	((sh)?((*(sh))->cnt):0)			/* same as LStrLen, but on string handle */
#define LHStrSize(sh)	(LHStrLen(sh)+sizeof(int32))	/* same as LStrSize, but on string handle */

#define LStrBuf(sp)	(&((sp))->str[0])				/* pointer to first char of string */
#define LStrLen(sp)	(((sp))->cnt)					/* # of chars in string */
#define LStrSize(sp)	(LStrLen(sp)+sizeof(int32))		/* # of bytes including length */

TH_REENTRANT EXTERNC int32 _FUNCC LStrCmp(ConstLStrP l1, ConstLStrP l2);
TH_REENTRANT EXTERNC int32 _FUNCC LStrCaseCmp(ConstLStrP l1, ConstLStrP l2);
TH_REENTRANT EXTERNC int32 _FUNCC PtrLenStrCmp(const uChar *s1, int32 s1len, const uChar *s2, int32 s2len);
TH_REENTRANT EXTERNC int32 _FUNCC PtrLenStrCaseCmp(const uChar *s1, int32 s1len, const uChar *s2, int32 s2len);
TH_REENTRANT EXTERNC int32 _FUNCC LHStrCmp(ConstLStrH lh1, ConstLStrH lh2);
TH_REENTRANT EXTERNC int32 _FUNCC LHStrCaseCmp(ConstLStrH lh1, ConstLStrH lh2);

TH_REENTRANT EXTERNC uInt32 _FUNCC LToCStrN(ConstLStrP source, CStr dest, uInt32 destSize);
TH_REENTRANT EXTERNC int32 _FUNCC LToPStr(ConstLStrP source, PStr dest);
TH_REENTRANT EXTERNC int32 _FUNCC PToLStr(ConstPStr source, LStrPtr dest);
TH_REENTRANT EXTERNC MgErr _FUNCC PStrToDSLStr(PStr buf, LStrHandle *lStr); /* deprecated */

#if USE_DEPRECATED_EXPORTS
/** @brief Convert a long Pascal-style string to a C-style string.
	@param lstr the long pascal string to convert
	@param cstr receives the contents of the Lstr
	@return length (in bytes) of converted string
	@pre cstr is large enough to contain lstr ((LStrLen(lstr) + 1) or more bytes)
	@deprecated Use LToCStrN() instead.
*/
TH_REENTRANT EXTERNC int32 _FUNCC LToCStr(ConstLStrP lstr, CStr cstr);
#endif /* USE_DEPRECATED_EXPORTS */

/*** Concatenated Pascal String Support Functions ***/
#define CPStrLen		LStrLen			/* concatenated Pascal vs. LabVIEW strings */
#define CPStrBuf		LStrBuf			/* concatenated Pascal vs. LabVIEW strings */

TH_REENTRANT EXTERNC int32 _FUNCC CPStrSize(CPStrPtr);
TH_REENTRANT EXTERNC int32 _FUNCC CPStrCmp(CPStrPtr, CPStrPtr);
TH_REENTRANT EXTERNC MgErr _FUNCC CPStrInsert(CPStrHandle, ConstPStr, int32);
TH_REENTRANT EXTERNC void _FUNCC CPStrRemove(CPStrHandle, int32);
TH_REENTRANT EXTERNC PStr _FUNCC CPStrIndex(CPStrHandle, int32);
TH_REENTRANT EXTERNC MgErr _FUNCC CPStrReplace(CPStrHandle, ConstPStr, int32);

TH_REENTRANT EXTERNC MgErr _FUNCC DbgPrintf(const char *buf, ...);

/** Refer to SPrintf() */
TH_PROTECTED EXTERNC int32 DBPrintf(const char *fmt, ...);

TH_REENTRANT EXTERNC int32 _FUNCC SPrintf(CStr buf, ConstCStr fmt, ...);
TH_REENTRANT EXTERNC int32 _FUNCC SPrintfp(CStr buf, ConstPStr fmt, ...);

TH_REENTRANT EXTERNC MgErr _FUNCC LStrPrintf(LStrHandle str, CStr fmt, ...);

TH_REENTRANT EXTERNC int32 _FUNCC PPrintf(PStr, ConstCStr, ...);
TH_REENTRANT EXTERNC int32 _FUNCC PPrintfp(PStr, ConstPStr, ...);

#ifndef NIDL
/*** Sort / Search Utilities ***/
/** @brief Comparison function pointer type definiton. */
typedef int32 (_FUNCC *CompareProcPtr)(const void *lhs, const void *rhs);

/* Avoid conflict with functions in LabWindows CVI that can arise for LabVIEW DLLs used in CVI projects. */
#ifndef _CVI_
TH_REENTRANT EXTERNC int32 _FUNCC BinSearch(const void*, int32, int32, const void*, CompareProcPtr);
#endif /* _CVI_ */
TH_REENTRANT EXTERNC void _FUNCC QSort(void*, int32, int32, CompareProcPtr);
#endif /* NIDL */

/*** Time Functions ***/
/** @brief Date/time record. */
typedef struct {
	int32	sec;	/* 0:59 */
	int32	min;	/* 0:59 */
	int32	hour;	/* 0:23 */
	int32	mday;	/* day of the month, 1:31 */
	int32	mon;	/* month of the year, 1:12 */
	int32	year;	/* year, 1904:2040 */
	int32	wday;	/* day of the week, 1:7 for Sun:Sat */
	int32	yday;	/* day of year (julian date), 1:366 */
	int32	isdst;	/* 1 if daylight savings time */
} DateRec;

TH_REENTRANT EXTERNC void _FUNCC SecsToDate(uInt32, DateRec*);
TH_REENTRANT EXTERNC uInt32 _FUNCC DateToSecs(DateRec*);
TH_REENTRANT EXTERNC lvtime _FUNCC TimeInSecs(void);
TH_UNSAFE EXTERNC CStr _FUNCC DateCString(uInt32, int32);
TH_UNSAFE EXTERNC CStr _FUNCC TimeCString(uInt32, int32);
TH_UNSAFE EXTERNC CStr _FUNCC ASCIITime(uInt32);

TH_REENTRANT EXTERNC uInt32 _FUNCC MilliSecs();

/*** The Memory Manager ***/
/*
	For parameters to the memory manager functions below
	p means pointer
	h means handle
	ph means pointer to handle
*/
TH_REENTRANT EXTERNC UHandle _FUNCC DSNewHandle(size_t);
TH_REENTRANT EXTERNC UHandle _FUNCC DSNewHClr(size_t);
TH_REENTRANT EXTERNC UHandle _FUNCC DSNewAlignedHandle(size_t, size_t alignment, size_t alignmentOffset);
TH_REENTRANT EXTERNC UHandle _FUNCC DSNewAlignedHClr(size_t, size_t alignment, size_t alignmentOffset);
TH_REENTRANT EXTERNC UPtr _FUNCC DSNewPtr(size_t);
TH_REENTRANT EXTERNC UPtr _FUNCC DSNewPClr(size_t);
TH_REENTRANT EXTERNC MgErr _FUNCC DSCopyHandle(void *ph, const void *hsrc);
TH_REENTRANT EXTERNC MgErr _FUNCC DSSetHandleSize(void *h, size_t);
TH_REENTRANT EXTERNC MgErr _FUNCC DSSetHSzClr(void *h, size_t);
TH_REENTRANT EXTERNC MgErr _FUNCC DSSetAlignedHandleSize(void *h, size_t, size_t alignment, size_t alignmentOffset);
TH_REENTRANT EXTERNC MgErr _FUNCC DSSetAlignedHSzClr(void *h, size_t, size_t alignment, size_t alignmentOffset);
TH_REENTRANT EXTERNC MgErr _FUNCC DSDisposeHandle(void *h);
TH_REENTRANT EXTERNC MgErr _FUNCC DSDisposePtr(void *p);

enum { kDSHandleZoneCheckNone, kDSHandleZoneCheckResize, kDSHandleZoneCheckAll };
TH_REENTRANT EXTERNC void _FUNCC DSSetHandleChecking(int32 level);

#if !Palm
TH_REENTRANT EXTERNC MgErr _FUNCC DSCheckHandle(const void *h);
TH_REENTRANT EXTERNC MgErr _FUNCC DSCheckPtr(void *p);
TH_REENTRANT EXTERNC size_t _FUNCC DSGetHandleSize(const void *h);
TH_REENTRANT EXTERNC UHandle _FUNCC DSRecoverHandle(void *p);
TH_REENTRANT EXTERNC MgErr _FUNCC DSHeapCheck(Bool32);
TH_REENTRANT EXTERNC size_t _FUNCC DSMaxMem(void);

/** @brief Describes memory statistics. */
typedef struct {
	int32 totFreeSize;    // free physical RAM in bytes (RT only)
	int32 maxFreeSize;    // largest free contiguous block in bytes (VxWorks/PharLap only)
	int32 unused1;        // was nFreeBlocks, but this was never filled in
	size_t totAllocSize;  // memory usage of LabVIEW itself in bytes
	size_t unused2;       // was maxAllocSize
	int32 unused3;        // was nPointers
	int32 unused4;        // was nUnlockedHdls
	int32 unused5;        // was nLockedHdls
	uInt64 totPhysSize;   // total physical RAM in bytes (RT only)
	int32 reserved1;
	int32 reserved2;
} MemStatRec;

TH_REENTRANT EXTERNC MgErr _FUNCC DSMemStats(MemStatRec *msrp);
#endif /* !Palm */

#if !Palm
TH_REENTRANT EXTERNC void _FUNCC ClearMem(void*, size_t);
TH_REENTRANT EXTERNC void _FUNCC MoveBlock(const void *src, void *dest, size_t); /* accepts zero bytes */
/* Avoid conflict with functions in LabWindows CVI that can arise for LabVIEW DLLs used in CVI projects. */
#ifndef _CVI_
TH_REENTRANT EXTERNC void _FUNCC SwapBlock(void *src, void *dest, size_t);
#endif /* _CVI_ */
#endif /* !Palm */
TH_REENTRANT EXTERNC int32 _FUNCC BlockCmp(const void * p1, const void * p2, size_t n);

#if USE_DEPRECATED_EXPORTS
#if !Palm
TH_REENTRANT EXTERNC MgErr _FUNCC AZCheckHandle(const void *h);
TH_REENTRANT EXTERNC MgErr _FUNCC AZCheckPtr(void *p);
TH_REENTRANT EXTERNC MgErr _FUNCC AZDisposeHandle(void *h);
TH_REENTRANT EXTERNC MgErr _FUNCC AZDisposePtr(void *p);
TH_REENTRANT EXTERNC size_t _FUNCC AZGetHandleSize(const void *h);
TH_REENTRANT EXTERNC MgErr _FUNCC AZHLock(void *h);
TH_REENTRANT EXTERNC MgErr _FUNCC AZHUnlock(void *h);
TH_REENTRANT EXTERNC void _FUNCC AZHPurge(void *h);
TH_REENTRANT EXTERNC void _FUNCC AZHNoPurge(void *h);
TH_REENTRANT EXTERNC UHandle _FUNCC AZNewHandle(size_t);
TH_REENTRANT EXTERNC UHandle _FUNCC AZNewHClr(size_t);
TH_REENTRANT EXTERNC UPtr _FUNCC AZNewPtr(size_t);
TH_REENTRANT EXTERNC UPtr _FUNCC AZNewPClr(size_t);
TH_REENTRANT EXTERNC UHandle _FUNCC AZRecoverHandle(void *p);
TH_REENTRANT EXTERNC MgErr _FUNCC AZSetHandleSize(void *h, size_t);
TH_REENTRANT EXTERNC MgErr _FUNCC AZSetHSzClr(void *h, size_t);
TH_REENTRANT EXTERNC int32 _FUNCC AZHeapCheck(Bool32);
TH_REENTRANT EXTERNC size_t _FUNCC AZMaxMem(void);
TH_REENTRANT EXTERNC MgErr _FUNCC AZMemStats(MemStatRec *msrp);
TH_REENTRANT EXTERNC MgErr _FUNCC AZSetHandleFromPtr(void *ph, const void *psrc, size_t n);
#endif /* !Palm */
#endif /* USE_DEPRECATED_EXPORTS */

/*** The File Manager ***/

/** @brief Opaque type used by the File Manager API for a file descriptor. */
LV_PRIVATE(File);

/** @brief Initial enumeration type for file types.
	The enumeration is used to increase type safety but does not list all possible values.
*/
typedef enum _FMFileType
{
	kInvalidType     = 0, /**< not a valid file type */
	kUnknownFileType = RTToL('?','?','?','?'), /**< unknown file type */
	kTextFileType    = RTToL('T','E','X','T'), /**< text file */
	kHardDiskDirType = RTToL('h','d','s','k'), /**< hard disk directory */
	kFloppyDirType   = RTToL('f','l','p','y'), /**< floppy drive type */
	kNetDriveDirType = RTToL('s','r','v','r')  /**< network volume */
} FMFileType;

/** @brief Type for file creator codes.
	The enumeration is used to increase type safety but does not list all possible values.*/
typedef enum _FMFileCreator
{
	kInvalidCreator = 0, /**< not a vaild file creator */
	kUnknownCreator = RTToL('?','?','?','?'), /**< unknown creator */
	kLVCreatorType  = RTToL('L','B','V','W') /**< LabVIEW creator */
} FMFileCreator;

/** @brief Flags describing a file used by the FMListDetails data structure. */
#define kIsFile         0x01 /**< entry refers to a file (as opposed to a directory) */
#define kRecognizedType 0x02 /**< file's type was recognized (e.g. VI, et. al.) */
#define kIsLink         0x04 /**< entry refers to a shortcut / alias / link */
#define kFIsInvisible   0x08 /**< entry refers to a hidden file */
#define kIsTopLevelVI   0x10 /**< Used only for VIs in archives */
#define kErrGettingType 0x20 /**< error occurred getting type info */
#if Mac
#define kFIsStationery  0x40 /**< file is stationery */
#endif /* Mac */

/** @brief Data used with FListDir to describe the files listed in a directory. */
typedef struct _FMListDetails
{
	int32 flags; /**< descriptive flags for the file (see kIsFile, et. al. above) */
	FMFileType type; /**< type of the file */
} FMListDetails;

/** @brief Data types used to describe a list of entries from a directory. */
typedef CPStr FDirEntRec, *FDirEntPtr, **FDirEntHandle;

/** @brief UNIX read permission bits (octal). */
#define fileReadBits	0444L

/** @brief UNIX write permission bits (octal). */
#define fileWriteBits	0222L

/** @brief UNIX execute permission bits (octal). */
#define fileExecBits	0111L

/** @brief UNIX read/write access permissions for a file. This is usually the default access to assign newly created files. */
#define fDefaultAccess (fileReadBits | fileWriteBits)

/** @brief Descriptive information about a file. */
typedef struct {
	FMFileType type;       /**< system specific file type-- 0 for directories */
	FMFileCreator creator; /**< system specific file creator-- 0 for directories */
	int32	permissions;   /**< system specific file access rights */
	int32	size;          /**< file size in bytes (data fork on Mac) or entries in folder */
	int32	rfSize;        /**< resource fork size (on Mac only) */
	uInt32	cdate;         /**< creation date */
	uInt32	mdate;         /**< last modification date */
	Bool32	folder;        /**< indicates whether path refers to a folder */
	Bool32	isInvisible;   /**< indicates whether the file is visible in File Dialog */
	struct {
		int16 v; /**< vertical coordinate */
		int16 h; /**< horizontal coordinate */
	} location;            /**< system specific geographical location (on Mac only) */
	Str255	owner;         /**< owner (in pascal string form) of file or folder */
	Str255	group;         /**< group (in pascal string form) of file or folder (Mac, Linux only) */
} FInfoRec, *FInfoPtr;

/** @brief Retrieve information about a file or directory.
	@param path absolute path to a file or directory
	@param infop pointer to a FInfoRec structure which receives information about the file or directory
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to access the file or directory due to permissions in the file system
	          - fNotFound: the file or directory does not exist at the specified location
	@note If @p path is a shortcut, it is resolved to the actual path. (Windows only)
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FGetInfo(ConstPath path, FInfoPtr infop);

/** @brief Modify information about a file or directory.
	@param path absolute path to a file or directory
	@param infop pointer to a FInfoRec structure which contains information about the file or directory
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to access the file or directory due to permissions in the file system
	          - fNotFound: the file or directory does not exist at the specified location
	@note If @p path is a shortcut, it is resolved to the actual path. (Windows only)
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FSetInfo(ConstPath path, const FInfoPtr infop);

/** @brief Used to specify fields of interest in a FInfoRec64 structure. */
typedef uInt32 FGetInfoWhich;
enum {
	kFGetInfoType        = 1L <<  0, /**< enable the type field */
	kFGetInfoCreator     = 1L <<  1, /**< enable the creator field */
	kFGetInfoPermissions = 1L <<  2, /**< enable the permissions field */
	kFGetInfoSize        = 1L <<  3, /**< enable the size field */
	kFGetInfoRFSize      = 1L <<  4, /**< enable the rfSize field */
	kFGetInfoCDate       = 1L <<  5, /**< enable the cdate field */
	kFGetInfoMDate       = 1L <<  6, /**< enable the mdate field */
	kFGetInfoFolder      = 1L <<  7, /**< enable the folder field */
	kFGetInfoIsInvisible = 1L <<  8, /**< enable the isInvisible field */
	kFGetInfoLocation    = 1L <<  9, /**< enable the location field */
	kFGetInfoOwner       = 1L << 10, /**< enable the owner field */
	kFGetInfoGroup       = 1L << 11, /**< enable the group field */
	kFGetInfoAll         = 0xEFFFFFFFL /**< enable all fields in FInfoRec64 */
};

/** @brief Descriptive information about a file, with large file support. */
typedef struct {
	FMFileType type;       /**< system specific file type-- 0 for directories */
	FMFileCreator creator; /**< system specific file creator-- 0 for directories */
	int32	permissions;   /**< system specific file access rights */
	int64	size;          /**< file size in bytes (data fork on Mac) or entries in folder */
	int64	rfSize;        /**< resource fork size (on Mac only) */
	uInt32	cdate;         /**< creation date */
	uInt32	mdate;         /**< last modification date */
	Bool32	folder;        /**< indicates whether path refers to a folder */
	Bool32	isInvisible;   /**< indicates whether the file is visible in File Dialog */
	struct {
		int16 v; /**< vertical coordinate */
		int16 h; /**< horizontal coordinate */
	} location;            /**< system specific geographical location (on Mac only) */
	Str255	owner;         /**< owner (in pascal string form) of file or folder */
	Str255	group;         /**< group (in pascal string form) of file or folder (Mac, Linux only) */
} FInfoRec64, *FInfo64Ptr;

/** @brief Retrieve information about a file or directory (supports files > 2 GB in size).
	@param path absolute path to a file or directory
	@param infop pointer to a FInfoRec64 structure which receives information about the file or directory
	@param which describes which portions of the FInfoRec64 should be acquired (in C++, this argument defaults to kFGetInfoAll)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to access the file or directory due to permissions in the file system
	          - fNotFound: the file or directory does not exist at the specified location
	@note If @p path is a shortcut, it is resolved to the actual path. (Windows only)
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FGetInfo64(ConstPath path, FInfo64Ptr infop, const FGetInfoWhich which DEFAULTARG(kFGetInfoAll));

/** @brief Modify information about a file or directory (supports files > 2 GB in size).
	@param path absolute path to a file or directory
	@param infop pointer to a FInfoRec64 structure which contains information about the file or directory
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to access the file or directory due to permissions in the file system
	          - fNotFound: the file or directory does not exist at the specified location
	@note If @p path is a shortcut, it is resolved to the actual path. (Windows only)
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FSetInfo64(ConstPath path, const FInfo64Ptr infop);

/** @brief Modes available to open a file. */
enum {
	openReadWrite,                  /**< open the file for reading and writing */
	openReadOnly,                   /**< open the file for reading */
	openWriteOnly,                  /**< open the file for writing (on Mac, this may enforce exclusive access to the file) */
	openWriteOnlyTruncate,          /**< open the file for writing, emptying the file on open */
	openReadWriteUnbuffered,        /**< open the file for reading and writing , disabling system caching (Windows only) */
	openReadOnlyUnbuffered,         /**< open the file for reading , disabling system caching (Windows only) */
	openWriteOnlyUnbuffered,        /**< open the file for writing , disabling system caching (Windows only) */
	openWriteOnlyTruncateUnbuffered /**< open the file for writing, emptying the file on open and disabling system caching (Windows only) */
};

/** @brief When opening a file, restrict concurrent access to the file.
	@note Deny modes are not supported on all operating systems.
*/
enum {
	denyReadWrite, /**< deny others the ability to open a file for reading or writing */
	denyWriteOnly, /**< deny others the ability to open a file for writing */
	denyNeither    /**< do not deny others from opening the file for any purpose */
};

/** @brief Create and open a file in the specified mode, assigning permissions and optionally the group.
	@param fdp receives a file descriptor; 0 if the operation fails
	@param path absolute path to the file to create
	@param permissions file system permissions to assign to the new file
	@param openMode the file access mode to use when opening the file
	@param denyMode defines concurrent access policy for the file (not supported on all platforms)
	@param group the group to assign to the file (Mac, Linux only)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to create the file due to permissions in the file system
	          - fDupPath: a file already exists at the requested location
	          - fTMFOpen: unable to open the file because too many files have already been opened

	@note In VxWorks, the @p denyMode parameter has no effect.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FCreate(File *fdp, ConstPath path, const int32 permissions, const int32 openMode, const int32 denyMode, ConstPStr group);

/** @brief Create and open a file in the specified mode, assigning permissions and optionally the group.
           If the file already exists, truncate it.
	@param fdp receives a file descriptor; 0 if the operation fails
	@param path absolute path to the file to create
	@param permissions file system permissions to assign to the new file
	@param openMode the file access mode to use when opening the file
	@param denyMode defines concurrent access policy for the file (not supported on all platforms)
	@param group the group to assign to the file (Mac, Linux only)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to create the file due to permissions in the file system
	          - fTMFOpen: unable to open the file because too many files have already been opened

	@note In VxWorks, the @p denyMode parameter has no effect.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FCreateAlways(File *fdp, ConstPath path, const int32 access, const int32 openMode, const int32 denyMode, ConstPStr group);

/** @brief Open an existing file in the specified mode.
	@param fdp receives a file descriptor; 0 if the operation fails
	@param path absolute path to the file to create
	@param openMode the file access mode to use when opening the file
	@param denyMode defines concurrent access policy for the file (not supported on all platforms)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to open the file due to permissions in the file system
	          - fTMFOpen: unable to open the file because too many files have already been opened

	@note In VxWorks, the @p denyMode parameter has no effect.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMOpen(File *fdp, ConstPath path, const int32 openMode, const int32 denyMode);

/** @brief Close the file associated with the given file descriptor.
	@param fd the file descriptor of the file to close
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fNotFound: the file does not exist at the specified location
	          - fIOErr: a general error occurred

	@note Calling FMClose() with an invalid file descriptor may cause your program to crash in some operating systems.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMClose(File fd);

/** @brief Seek modes for FMSeek() and FMSeek64(). */
enum {
	fStart = 1, /**< move file marker relative to start of file */
	fEnd,       /**< move file marker relative to end of file */
	fCurrent    /**< move file marker relative to the current file marker position within the file */
};

/** @brief Set the position mark for a file to the specified point.
	@param fd file descriptor of the file whose marker is to be set
	@param ofst new position for the file marker, intepreted by @p mode
	@param mode move the file marker relative to the specified location (start, end, or current)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fEOF: attempted to move the file marker past the end of the file, or before the start
	          - fIOErr: a general error occurred

	When the @p mode is fEnd, the @p ofst value must be <= 0, and when @p mode is
	fStart, the @p ofst value must be >= 0. Attempts to seek before the start of the
	file result in the file marker being set to the beginning of the file, while
	attempting to seek past the end of the file leaves the file marker at the end of the file.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMSeek(File fd, const int32 ofst, const int32 mode);

/** @brief Set the position mark for a file to the specified point (supports files > 2 GB in size).
	@param fd file descriptor of the file whose marker is to be set
	@param ofst new position for the file marker, intepreted by @p mode
	@param mode move the file marker relative to the specified location (start, end, or current)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fEOF: attempted to move the file marker past the end of the file, or before the start
	          - fIOErr: a general error occurred

	When the @p mode is fEnd, the @p ofst value must be <= 0, and when @p mode is
	fStart, the @p ofst value must be >= 0. Attempts to seek before the start of the
	file result in the file marker being set to the beginning of the file, while
	attempting to seek past the end of the file leaves the file marker at the end of the file.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMSeek64(File fd, const int64 ofst, const int32 mode);

/** @brief Get the current position of the file marker in the file.
	@param fd file descriptor of the file whose marker position is to be retrieved
	@param ofstp receives the position (in bytes) of the file marker, relative to the beginning of the file
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMTell(File fd, int32 *ofstp);

/** @brief Get the current position of the file marker in the file (supports files > 2 GB in size).
	@param fd file descriptor of the file whose marker position is to be retrieved
	@param ofstp receives the position (in bytes) of the file marker, relative to the beginning of the file
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMTell64(File fd, int64 *ofstp);

/** @brief Get the size of the file in bytes.
	@param fd file descriptor of the file whose size is to be retrieved
	@param sizep receives the size of the file (in bytes); if an error occurs, the value is undefined
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FGetEOF(File fd, int32 *sizep);

/** @brief Get the size of the file in bytes (supports files > 2 GB in size).
	@param fd file descriptor of the file whose size is to be retrieved
	@param sizep receives the size of the file (in bytes); if an error occurs, the value is undefined
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FGetEOF64(File fd, int64 *sizep);

/** @brief Set the size of a file.
	@param fd file descriptor of the file whose size is to be changed
	@param size new size for the file (in bytes)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to create the file due to permissions in the file system
	          - fDiskFull: not enough disk space
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FSetEOF(File fd, const int32 size);

/** @brief Set the size of a file (supports files > 2 GB in size).
	@param fd file descriptor of the file whose size is to be changed
	@param size new size for the file (in bytes)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to modify the file due to permissions in the file system
	          - fDiskFull: not enough disk space
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FSetEOF64(File fd, const int64 size);

/** @brief Lock or unlock a range within a file, preventing (or allowing) write access.
	@param fd file descriptor of the file to lock or unlock a range within
	@param mode lock / unlock range begins at @p offset relative to the specified location (start, end, or current)
	@param offset position of the first byte to lock / unlock in the file, as determined by @p mode
	@param count number of bytes to lock or unlock
	@param lock if TRUE, the specified range is locked, if FALSE, it is unlocked
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to lock the file due to permissions in the file system

	@note In VxWorks, this function has no effect, and this function will never return an error.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FLockOrUnlockRange(File fd, const int32 mode, const int32 offset, const int32 count, const Bool32 lock);

/** @brief Read the requested number of bytes from the given file.
	@param fd file descriptor of the file to read
	@param inCount number of bytes to read
	@param outCountp receives the number of bytes actually read (ignored if NULL)
	@param buffer receives the data
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fEOF: end of file reached before requested amount of data could be read
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMRead(File fd, const int32 inCount, int32 *outCountp, UPtr buffer);

/** @brief Write the supplied data to the given file.
	@param fd file descriptor of the file to write to
	@param inCount number of bytes to write to the file
	@param outCountp receives number of bytes actually written to the file
	@param buffer the data to write to the file
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
	          - fNoPerm: unable to write to the file due to permissions in the file system or deny mode during concurrent access
	          - fDiskFull: not enough disk space
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMWrite(File fd, const int32 inCount, int32 *outCountp, ConstUPtr buffer);

/** @brief Print formatted text to a file.
	@param fd file descriptor of the file to write to
	@param fmt format specifier string
	@param ... arguments that provide data for the format specifier string
	@return number of bytes written to the file, -1 if an error occurred
*/
TH_REENTRANT EXTERNC int32 _FUNCC FPrintf(File, ConstCStr fmt, ...);

/** @brief Write buffered data to disk.
	@param fd file descriptor of the file to flush to disk
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FFlush(File fd);

/** @brief Values returned from the FExists() function. */
enum {
	kFNotExist = 0L, /**< the file or directory does not exist */
	kFIsFile,        /**< the path refers to a file */
	kFIsFolder       /**< the path refers to a directory */
};

/** @brief Determine whether the given path exists, and if it is a file or directory.
	@param path absolute path to a file or directory to check
	@return one of the values kFNotExist, kFIsFile, or kFIsFolder
*/
TH_REENTRANT EXTERNC int32 _FUNCC FExists(ConstPath path);

/** @brief Determine if the given path refers to a directory.
	@param p absolute path to check
	@return TRUE if @p path refers to a folder, otherwise FALSE
*/
#define FIsFolder(path) ((Bool32)(FExists((path)) == kFIsFolder))

/** @brief Get file system access rights information for the specified file or directory.
	@param path absolute path to the file or directory to query
	@param owner receives name of the owner of the file or directory (may not be NULL)
	@param group receives name of the group of the file or directory (may not be NULL)
	@param permPtr receives the UNIX-style file permissions bits of the file or direcotry (may not be NULL)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fNotFound: the file or directory does not exist at the specified location
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FGetAccessRights(ConstPath path, PStr owner, PStr group, int32 *permPtr);

/** @brief Set file system access rights information for the specified file or directory.
	@param path absolute path to the file or direcotry whose access rights are being modified
	@param owner new owner of the file (ignored if NULL)
	@param group new group of the file or directory (ignored if NULL)
	@param permPtr new UNIX-style permissions for the file or directory (ignored if NULL)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to modify the permissions in the file system due to restrictions imposed by the OS or file system
	          - fIOErr: a general error occurred

	@note If all off @p owner, @p group and @p permPtr are NULL, the function is a no-op and returns mgNoErr.

	@note In VxWorks, this function has no effect, and will never return an error.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FSetAccessRights(ConstPath path, ConstPStr owner, ConstPStr group, const int32 *permPtr);

/** @brief Move or rename a file or directory.
	@param oldPath absolute path to the file or directory to move
	@param newPath absolute path to the destination for the file or directory
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - mFullErr: ran out of memory during the operation
	          - fIsOpen: file is already open and may not be moved
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to move the file or directory due to restrictions imposed by the OS or file system
	          - fIOErr: a general error occurred
	          - fDiskFull: not enough disk space
	          - fDupPath: a directory or file already exists at the destination
	          - fTMFOpen: unable to open the source file because too many files have already been opened
	@note In Windows, shortcuts in @p oldPath will be resolved prior to executing the move.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMove(ConstPath oldPath, ConstPath newPath);

/** @brief Copy a file or directory from one location to another, preserving access rights and other information.
	@param oldPath absolute path to a file or directory to copy
	@param newPath absolute path for the copy of the file or directory
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - mFullErr: ran out of memory during the operation
	          - fIsOpen: file is already open and may not be moved
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to move the file or directory due to restrictions imposed by the OS or file system
	          - fIOErr: a general error occurred
	          - fDiskFull: not enough disk space
	          - fDupPath: a directory or file already exists at the destination
	          - fTMFOpen: unable to open the source file because too many files have already been opened
	@note In Windows, if @p oldPath is a shortcut, it is resolved prior to executing the copy.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FCopy(ConstPath oldPath, ConstPath newPath);

/** @brief Permanently delete a file or empty directory.
	@param path absolute path to the file or empty directory to delete
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIsOpen: file is already open and may not be moved
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to move the file or directory due to restrictions imposed by the OS or file system
	          - fIOErr: a general error occurred

	@note If @p path refers to a shortcut, alias, or symbolic link, the respective shortcut, alias, or
	      link will be removed, not the target of the shortcut / alias / symbolic link.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FRemove(ConstPath path);

/** @brief Place a file or directory into the system's trash / recycle bin.
	@param path absolute path to the file or empty directory to delete
	@param showConfigDlgs if TRUE, the operating system may display a dialog requesting confirmation of the operation
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIsOpen: file is already open and may not be moved
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to move the file or directory due to restrictions imposed by the OS or file system
	          - fIOErr: a general error occurred

	@note When called on operating systems other than Mac or Windows, this function behaves
	      as if you called FRemove(), which permanently deletes the file or directory.

	@note In some cases, the operating system may display a progress dialog during the operation,
	      even if @p showConfigDlgs is FALSE. The dialog will not require user interaction.

	@note If @p path refers to a shortcut, alias, or symbolic link, the respective shortcut, alias, or
	      link will be removed, not the target of the shortcut / alias / symbolic link.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FRemoveToRecycle(ConstPath path, const Bool32 showConfirmDlgs);

/** @brief Create a directory with the given permissions.
	@param path the absolute path of the directory to create
	@param permissions the access rights to assign to the diretory (typically folderDefaultPerm)
	@return result operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fNotFound: the file or directory does not exist at the specified location
	          - fNoPerm: unable to create the directory due to permissions in the file system
	          - fIOErr: a general error occurred

	@note In VxWorks, the @p permissions argument has no effect.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FNewDir(ConstPath path, const int32 permissions);

/** @brief Data structure describing a disk volume. */
typedef struct {
	uInt32	size; /**< size in bytes of a volume */
	uInt32	used; /**< number of bytes used on volume */
	uInt32	free; /**< number of bytes available for use on volume */
} VInfoRec;

/** @brief Get information about the volume containing the specified path, returning base volume path via the provided path.
	@param path absolute path from which to extract volume information
	@param vInfo receives information about the volume on which @p path exists
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred

	@note This function modifies the contents of the @p path argument.

	@note This function has been deprecated. Use FMGetVolInfo() or FMGetVolInfo64() instead.
	      It is unable to return accurate information for volumes 4 GB in size.
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FGetVolInfo(Path path, VInfoRec *vInfo);

/** @brief Get information about the volume containing the specified path.
	@param path in: absolute path from which to extract volume information; out: contains the base volume path
	@param pFreeBytes receives number of free bytes on the volume containing @p path (may be NULL)
	@param pTotalBytes receives total size in bytes of the volume containing @p path (may be NULL)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMGetVolInfo(ConstPath path, float64 *pFreeBytes, float64 *pTotalBytes);

/** @brief Get information about the volume containing the specified path.
	@param path absolute path from which to extract volume information
	@param pFreeBytes receives number of free bytes on the volume containing @p path (may be NULL)
	@param pTotalBytes receives total size in bytes of the volume containing @p path (may be NULL)
	@param pSectorSize receives size in bytes of the sectors on the volume containing @p path (may be NULL)
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - fIOErr: a general error occurred
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMGetVolInfo64(ConstPath path, uInt64 *pFreeBytes, uInt64 *pTotalBytes, uInt32 *pSectorSize);

/** @brief Get the path for the root of the volume for a given path.
	@param path absolute path from which to extract the volume path
	@param volPath receives the base volume path
	@return result of the operation:
	          - mgNoErr: success
	          - mgArgErr: an invalid argument was passed to the function
	          - mFullErr: out of memory

	@todo Test this function and verify what happens when *volPath == path (especially on Linux).
*/
TH_REENTRANT EXTERNC MgErr _FUNCC FMGetVolPath(ConstPath path, Path *volPath);

TH_REENTRANT EXTERNC MgErr _FUNCC FListDir(ConstPath path, FDirEntHandle list, FMListDetails **);

/*** The Path Manager ***/

/* FileNameCmp compares two PStr's with the same case-sensitivity as */
/* the filesystem. */
/* FileNameNCmp compares two CStr's (to length n) with the same */
/* case-sensitivity as the filesystem. */
/* FileNameIndCmp compares two PStr's (passing pointers to the string */
/* pointers) with the same case-sensitivity as the filesystem. */
#if Mac || MSWin || VxWorks
#define FileNameCmp		PStrCaseCmp
#define FileNameNCmp	StrNCaseCmp
#define FileNameIndCmp	PPStrCaseCmp
#elif Unix
#define FileNameCmp		PStrCmp
#define FileNameNCmp	StrNCmp
#define FileNameIndCmp	PPStrCmp
#endif

/** @brief Path type codes */
enum {	fAbsPath,
	fRelPath,
	fNotAPath,
	fUNCPath,		/**< uncfilename */
	nPathTypes };

TH_REENTRANT EXTERNC MgErr _FUNCC FRelPath(ConstPath start, ConstPath end, Path relPath);
TH_REENTRANT EXTERNC MgErr _FUNCC FAddPath(ConstPath basePath, ConstPath relPath, Path newPath);
TH_REENTRANT EXTERNC MgErr _FUNCC FAppendName(Path path, ConstPStr name);
TH_REENTRANT EXTERNC MgErr _FUNCC FName(ConstPath path, PStrHandle name);
TH_REENTRANT EXTERNC MgErr _FUNCC FNamePtr(ConstPath path, PStr name);
TH_REENTRANT EXTERNC MgErr _FUNCC FDirName(ConstPath path, Path dir);
TH_REENTRANT EXTERNC MgErr _FUNCC FVolName(ConstPath path, Path vol);
TH_REENTRANT EXTERNC Path _FUNCC FMakePath(Path path, int32 type, ...);
TH_REENTRANT EXTERNC Path _FUNCC FEmptyPath(Path);
TH_REENTRANT EXTERNC Path _FUNCC FNotAPath(Path);
TH_REENTRANT EXTERNC Bool32 _FUNCC FIsAPath(ConstPath);
TH_REENTRANT EXTERNC int32 _FUNCC FDepth(ConstPath path);

TH_REENTRANT EXTERNC MgErr _FUNCC FPathToPath(Path *p);
TH_REENTRANT EXTERNC MgErr _FUNCC FPathCpy(Path dst, ConstPath src);
TH_REENTRANT EXTERNC MgErr _FUNCC FTextToPath(ConstUPtr, int32, Path*);
TH_REENTRANT EXTERNC MgErr _FUNCC FPathToDSString(ConstPath, LStrHandle*);
TH_REENTRANT EXTERNC UHandle _FUNCC PathToCString(ConstPath );
TH_REENTRANT EXTERNC MgErr _FUNCC FStringToPath(ConstLStrH, Path*);
TH_REENTRANT EXTERNC MgErr _FUNCC FPathToFileSystemDSString(ConstPath p, LStrHandle *txt);
TH_REENTRANT EXTERNC MgErr _FUNCC FFileSystemCStrToPath(ConstCStr text, Path *p);

TH_REENTRANT EXTERNC Bool32 _FUNCC FStrFitsPat(const uChar*, const uChar*, int32, int32);
TH_REENTRANT EXTERNC int32 _FUNCC FPathCmp(ConstPath, ConstPath);
TH_REENTRANT EXTERNC int32 _FUNCC FPathCmpLexical(ConstPath, ConstPath);
TH_REENTRANT EXTERNC MgErr _FUNCC FSetPathType(Path, int32);
TH_REENTRANT EXTERNC MgErr _FUNCC FGetPathType(ConstPath, int32*);
TH_REENTRANT EXTERNC Bool32 _FUNCC FIsEmptyPath(ConstPath);
TH_REENTRANT EXTERNC Bool32 _FUNCC FIsAPathOrNotAPath(ConstPath);
TH_REENTRANT EXTERNC Bool32 _FUNCC FIsAPathOfType(ConstPath, int32);
TH_REENTRANT EXTERNC LStrHandle _FUNCC FGetDefGroup(LStrHandle);

/** @brief Releases memory and sets pointer to NULL. */
TH_REENTRANT EXTERNC void _FUNCC FDestroyPath(Path *pp);
/** @brief Use of FDestroyPath recommended over FDisposePath. */
TH_REENTRANT EXTERNC MgErr _FUNCC FDisposePath(Path p);

TH_REENTRANT EXTERNC int32 _FUNCC FUnFlattenPath(UPtr fp, Path *pPtr);
TH_REENTRANT EXTERNC int32 _FUNCC FFlattenPath(ConstPath p, UPtr fp);

/** @brief Get the absolute LV Path to directory where executable is. */
TH_REENTRANT EXTERNC MgErr _FUNCC FAppPath(Path p);

typedef MagicCookie LVRefNum;

TH_REENTRANT EXTERNC MgErr _FUNCC FNewRefNum(ConstPath, File, LVRefNum*);
TH_REENTRANT EXTERNC Bool32 _FUNCC FIsARefNum(LVRefNum);
TH_REENTRANT EXTERNC MgErr _FUNCC FDisposeRefNum(LVRefNum);
TH_REENTRANT EXTERNC MgErr _FUNCC FRefNumToFD(LVRefNum, File*);
TH_REENTRANT EXTERNC MgErr _FUNCC FRefNumToPath(LVRefNum, Path);
TH_REENTRANT EXTERNC MgErr _FUNCC FArrToPath(UHandle, Bool32, Path);
TH_REENTRANT EXTERNC MgErr _FUNCC FPathToArr(ConstPath, Bool32*, UHandle);

typedef MagicCookie LVUserEventRef;
TH_REENTRANT EXTERNC MgErr _FUNCC PostLVUserEvent(LVUserEventRef ref, void *data);

/** @brief Custom data used for external function calls (such as the Call Library Node). */
typedef void* InstanceDataPtr;

TH_REENTRANT EXTERNC MgErr _FUNCC CallChain(UHandle);

TH_REENTRANT EXTERNC MgErr _FUNCC NumericArrayResize(int32, int32, UHandle*, size_t);

/*** Application Builder ***/

/** @brief This function provides the thread specific last error message set during 
           previous calls to exposed API in LabVIEW built shared library. This function
		   should be used when error-out clusters are configured to return error-code 
		   as return value using application builder.		   
	@param errstr  User allocated buffer to store error message. User must allocate sufficient memory.
	@param len     Size in bytes of allocated buffer 'errstr'.
*/
TH_REENTRANT EXTERNC void _FUNCC LVGetLastErrorMsg(CStr errstr, int32 len);

/** @brief Clears out the previous error message for a current thread.
*/
TH_REENTRANT EXTERNC void _FUNCC LVClearLastErrorMsg();

/*** CIN-specific Functions ***/
TH_REENTRANT  EXTERNC int32 _FUNCC SetCINArraySize(uChar **elmtH, int32 elmtNum, int32 newNumElmts);
TH_REENTRANT  EXTERNC int32 _FUNCC GetDSStorage(void);
TH_REENTRANT  EXTERNC int32 _FUNCC SetDSStorage(int32 newval);
TH_REENTRANT  EXTERNC int16* _FUNCC GetTDPtr(void);
TH_REENTRANT  EXTERNC uChar* _FUNCC GetLVInternals(void);

/* selectors for CINProperties */
enum { kCINIsReentrant };

#define CIN EXTERNC

CIN int32 _FUNCC CINInit(void);
CIN int32 _FUNCC CINDispose(void);
CIN int32 _FUNCC CINAbort(void);
CIN int32 _FUNCC CINLoad(uInt32 reserved);
CIN int32 _FUNCC CINUnload(void);
CIN int32 _FUNCC CINSave(uInt32 reserved);
CIN int32 _FUNCC CINProperties(int32 selector, void *arg);

#define ENTERLVSB
#define LEAVELVSB

/* CINInit -- Called after the VI is loaded or recompiled. */
#define UseDefaultCINInit CIN MgErr _FUNCC CINInit() { return mgNoErr; }

/* CINDispose -- Called before the VI is unloaded or recompiled.*/
#define UseDefaultCINDispose CIN MgErr _FUNCC CINDispose() { return mgNoErr; }

/* CINAbort-- Called when the VI is aborted. */
#define UseDefaultCINAbort CIN MgErr _FUNCC CINAbort() { return mgNoErr; }

/* CINLoad -- Called when the VI is loaded. */
#define UseDefaultCINLoad CIN MgErr _FUNCC CINLoad(uInt32 reserved) { Unused(reserved); return mgNoErr; }

/* CINUnload -- Called when the VI is unloaded. */
#define UseDefaultCINUnload CIN MgErr _FUNCC CINUnload() { return mgNoErr; }

/* CINSave -- Called when the VI is saved. */
#define UseDefaultCINSave CIN MgErr _FUNCC CINSave(uInt32 reserved) { Unused(reserved); return mgNoErr; }

#include "lv_epilog.h"

#endif /* _extcode_H */
