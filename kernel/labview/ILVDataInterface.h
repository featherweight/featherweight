/* this ALWAYS GENERATED file contains the definitions for the interfaces */
#ifndef __ILVDataInterface_h__
#define __ILVDataInterface_h__

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)
#define NIDL_STDMETHODCALLTYPE __stdcall
#else // WIN32
#define NIDL_STDMETHODCALLTYPE
#endif // WIN32

#ifndef NIDL_EXTERN_C
#ifdef __cplusplus
#define NIDL_EXTERN_C extern "C"
#else // __cplusplus
#define NIDL_EXTERN_C
#endif // __cplusplus
#endif // NIDL_EXTERN_C

#ifndef NIDL_INTERFACE
#if defined(WIN32) || (defined(PHARLAP) && PHARLAP)
#define NIDL_INTERFACE(x) struct __declspec(uuid(x))
#else // WIN32
#define NIDL_INTERFACE(x) struct
#endif // WIN32
#endif // NIDL_INTERFACE
/* Forward Declarations */

#ifndef __ILVData_FWD_DEFINED__
#define __ILVData_FWD_DEFINED__
typedef struct ILVData ILVData;
#endif  /* __ILVData_FWD_DEFINED__ */

#ifndef __ILVBoolean_FWD_DEFINED__
#define __ILVBoolean_FWD_DEFINED__
typedef struct ILVBoolean ILVBoolean;
#endif  /* __ILVBoolean_FWD_DEFINED__ */

#ifndef __ILVInt8_FWD_DEFINED__
#define __ILVInt8_FWD_DEFINED__
typedef struct ILVInt8 ILVInt8;
#endif  /* __ILVInt8_FWD_DEFINED__ */

#ifndef __ILVInt16_FWD_DEFINED__
#define __ILVInt16_FWD_DEFINED__
typedef struct ILVInt16 ILVInt16;
#endif  /* __ILVInt16_FWD_DEFINED__ */

#ifndef __ILVInt32_FWD_DEFINED__
#define __ILVInt32_FWD_DEFINED__
typedef struct ILVInt32 ILVInt32;
#endif  /* __ILVInt32_FWD_DEFINED__ */

#ifndef __ILVInt64_FWD_DEFINED__
#define __ILVInt64_FWD_DEFINED__
typedef struct ILVInt64 ILVInt64;
#endif  /* __ILVInt64_FWD_DEFINED__ */

#ifndef __ILVuInt8_FWD_DEFINED__
#define __ILVuInt8_FWD_DEFINED__
typedef struct ILVuInt8 ILVuInt8;
#endif  /* __ILVuInt8_FWD_DEFINED__ */

#ifndef __ILVuInt16_FWD_DEFINED__
#define __ILVuInt16_FWD_DEFINED__
typedef struct ILVuInt16 ILVuInt16;
#endif  /* __ILVuInt16_FWD_DEFINED__ */

#ifndef __ILVuInt32_FWD_DEFINED__
#define __ILVuInt32_FWD_DEFINED__
typedef struct ILVuInt32 ILVuInt32;
#endif  /* __ILVuInt32_FWD_DEFINED__ */

#ifndef __ILVuInt64_FWD_DEFINED__
#define __ILVuInt64_FWD_DEFINED__
typedef struct ILVuInt64 ILVuInt64;
#endif  /* __ILVuInt64_FWD_DEFINED__ */

#ifndef __ILVFloat32_FWD_DEFINED__
#define __ILVFloat32_FWD_DEFINED__
typedef struct ILVFloat32 ILVFloat32;
#endif  /* __ILVFloat32_FWD_DEFINED__ */

#ifndef __ILVFloat64_FWD_DEFINED__
#define __ILVFloat64_FWD_DEFINED__
typedef struct ILVFloat64 ILVFloat64;
#endif  /* __ILVFloat64_FWD_DEFINED__ */

#ifndef __ILVFloatExt_FWD_DEFINED__
#define __ILVFloatExt_FWD_DEFINED__
typedef struct ILVFloatExt ILVFloatExt;
#endif  /* __ILVFloatExt_FWD_DEFINED__ */

#ifndef __ILVComplex64_FWD_DEFINED__
#define __ILVComplex64_FWD_DEFINED__
typedef struct ILVComplex64 ILVComplex64;
#endif  /* __ILVComplex64_FWD_DEFINED__ */

#ifndef __ILVComplex128_FWD_DEFINED__
#define __ILVComplex128_FWD_DEFINED__
typedef struct ILVComplex128 ILVComplex128;
#endif  /* __ILVComplex128_FWD_DEFINED__ */

#ifndef __ILVComplexExt_FWD_DEFINED__
#define __ILVComplexExt_FWD_DEFINED__
typedef struct ILVComplexExt ILVComplexExt;
#endif  /* __ILVComplexExt_FWD_DEFINED__ */

#ifndef __ILVArray_FWD_DEFINED__
#define __ILVArray_FWD_DEFINED__
typedef struct ILVArray ILVArray;
#endif  /* __ILVArray_FWD_DEFINED__ */

#ifndef __ILVString_FWD_DEFINED__
#define __ILVString_FWD_DEFINED__
typedef struct ILVString ILVString;
#endif  /* __ILVString_FWD_DEFINED__ */

#ifndef __ILVCluster_FWD_DEFINED__
#define __ILVCluster_FWD_DEFINED__
typedef struct ILVCluster ILVCluster;
#endif  /* __ILVCluster_FWD_DEFINED__ */


/* Header files for imported files */

#include "unknwn.h"

/* Declarations */

// ==================================================================
// NI CONFIDENTIAL													
// (c) Copyright 2006-2008 by National Instruments Corp.				
// All rights reserved.												
//																	
// @file		ILVDataInterface.idl									
// @brief	Interface definitions for LabVIEW data.					
//			The files ILVDataInterface_i.c and ILVDataInterface.h	
//			are generated using ILVDataInterface.idl.				
// ==================================================================
#include "extcode.h"
#include "ILVTypeInterface.h"
#ifndef _fundtypes_H
typedef char int8_t;

typedef unsigned char uint8_t;

typedef short int16_t;

typedef unsigned short uint16_t;

typedef int int32_t;

typedef unsigned int uint32_t;

typedef char int8;

typedef unsigned char uInt8;

typedef uInt8 uChar;

typedef short int int16;

typedef unsigned short int uInt16;

typedef long int32;

typedef unsigned long uInt32;

typedef float float32;

typedef double float64;

typedef __int64 int64;

typedef unsigned __int64 uInt64;

typedef struct  {
   int32 mlo;
   int32 mhi;
   int16 e;
} floatExt;

typedef struct  {
   float32 re;
   float32 im;
} cmplx64;

typedef struct  {
   float64 re;
   float64 im;
} cmplx128;

typedef struct  {
   floatExt re;
   floatExt im;
} cmplxExt;

typedef int32 Bool32;

typedef __int64 int64_t;

typedef unsigned __int64 uint64_t;

typedef long HRESULT;

typedef long SCODE;

typedef unsigned int uintptr_t;

typedef unsigned char* va_list;

typedef unsigned int size_t;

typedef size_t rsize_t;

typedef int intptr_t;

typedef int ptrdiff_t;

typedef unsigned short wint_t;

typedef unsigned short wctype_t;

typedef int errcode;

typedef int errno_t;

typedef long __time32_t;

typedef __int64 __time64_t;

typedef __time64_t time_t;

typedef struct threadlocaleinfostruct {
} threadlocaleinfostruct;

typedef struct threadmbcinfostruct {
} threadmbcinfostruct;

typedef struct threadlocaleinfostruct {
}* pthreadlocinfo;

typedef struct threadmbcinfostruct {
}* pthreadmbcinfo;

typedef struct __lc_time_data {
} __lc_time_data;

typedef struct localeinfo_struct {
   pthreadlocinfo locinfo;
   pthreadmbcinfo mbcinfo;
}* _locale_t;

typedef struct localeinfo_struct {
   pthreadlocinfo locinfo;
   pthreadmbcinfo mbcinfo;
} _locale_tstruct;

typedef struct tagLC_ID {
   unsigned short wLanguage;
   unsigned short wCountry;
   unsigned short wCodePage;
}* LPLC_ID;

typedef struct tagLC_ID {
   unsigned short wLanguage;
   unsigned short wCountry;
   unsigned short wCodePage;
} LC_ID;

typedef struct threadlocaleinfostruct {
   int refcount;
   unsigned int lc_codepage;
   unsigned int lc_collate_cp;
   unsigned long lc_handle[6];
   LC_ID lc_id[6];
   struct  {
   unsigned char* locale;
   wchar_t* wlocale;
   int* refcount;
   int* wrefcount;
} lc_category[6];
   int lc_clike;
   int mb_cur_max;
   int* lconv_intl_refcount;
   int* lconv_num_refcount;
   int* lconv_mon_refcount;
   struct lconv {
}* lconv;
   int* ctype1_refcount;
   unsigned short* ctype1;
   const unsigned short* pctype;
   const unsigned char* pclmap;
   const unsigned char* pcumap;
   struct __lc_time_data {
}* lc_time_curr;
} threadlocinfo;

   virtual int* NIDL_STDMETHODCALLTYPE _errno(void) = 0;
   virtual errno_t NIDL_STDMETHODCALLTYPE _set_errno(
      int _Value) = 0;
   virtual errno_t NIDL_STDMETHODCALLTYPE _get_errno(
      int* _Value) = 0;
   virtual unsigned long NIDL_STDMETHODCALLTYPE __threadid(void) = 0;
   virtual uintptr_t NIDL_STDMETHODCALLTYPE __threadhandle(void) = 0;
typedef int32 MgErr;

typedef uInt8 LVBoolean;

#endif // ifndef _fundtypes
/* Generated header for interface ILVData */

NIDL_EXTERN_C const IID IID_ILVData;

/* {4a4264a2-d5d8-468d-9675-6f1df777b295} */
NIDL_INTERFACE("4a4264a2-d5d8-468d-9675-6f1df777b295") ILVData : public IUnknown
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE GetType(
      ILVTypeDescriptor** typeDescriptor) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Equals(
      ILVData* data,
      Bool32* isEqual) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Copy(
      ILVData** dataOut) = 0;
} ;

/* Generated header for interface ILVBoolean */

NIDL_EXTERN_C const IID IID_ILVBoolean;

/* {7ab091d1-4154-48e2-bf98-55cc20335184} */
NIDL_INTERFACE("7ab091d1-4154-48e2-bf98-55cc20335184") ILVBoolean : public ILVData
{
public:
   virtual LVBoolean NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      LVBoolean value) = 0;
} ;

/* Generated header for interface ILVInt8 */

NIDL_EXTERN_C const IID IID_ILVInt8;

/* {f3ee3676-1e8e-42c2-8355-e4c07d4eb769} */
NIDL_INTERFACE("f3ee3676-1e8e-42c2-8355-e4c07d4eb769") ILVInt8 : public ILVData
{
public:
   virtual int8 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      int8 value) = 0;
} ;

/* Generated header for interface ILVInt16 */

NIDL_EXTERN_C const IID IID_ILVInt16;

/* {8567dfb4-0d6d-46d0-b87f-a5b680d3cd82} */
NIDL_INTERFACE("8567dfb4-0d6d-46d0-b87f-a5b680d3cd82") ILVInt16 : public ILVData
{
public:
   virtual int16 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      int16 value) = 0;
} ;

/* Generated header for interface ILVInt32 */

NIDL_EXTERN_C const IID IID_ILVInt32;

/* {878fcd1e-c70f-4940-8e54-461a4d1bb5b3} */
NIDL_INTERFACE("878fcd1e-c70f-4940-8e54-461a4d1bb5b3") ILVInt32 : public ILVData
{
public:
   virtual int32 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      int32 value) = 0;
} ;

/* Generated header for interface ILVInt64 */

NIDL_EXTERN_C const IID IID_ILVInt64;

/* {0344d202-0f76-4efb-ad02-deec0b480e47} */
NIDL_INTERFACE("0344d202-0f76-4efb-ad02-deec0b480e47") ILVInt64 : public ILVData
{
public:
   virtual int64 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      int64 value) = 0;
} ;

/* Generated header for interface ILVuInt8 */

NIDL_EXTERN_C const IID IID_ILVuInt8;

/* {35ce47f1-7a7a-43c2-a663-a6340cd72ebb} */
NIDL_INTERFACE("35ce47f1-7a7a-43c2-a663-a6340cd72ebb") ILVuInt8 : public ILVData
{
public:
   virtual uInt8 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      uInt8 value) = 0;
} ;

/* Generated header for interface ILVuInt16 */

NIDL_EXTERN_C const IID IID_ILVuInt16;

/* {f1d1b174-ce67-4c6e-ada6-064f3f49ba42} */
NIDL_INTERFACE("f1d1b174-ce67-4c6e-ada6-064f3f49ba42") ILVuInt16 : public ILVData
{
public:
   virtual uInt16 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      uInt16 value) = 0;
} ;

/* Generated header for interface ILVuInt32 */

NIDL_EXTERN_C const IID IID_ILVuInt32;

/* {edfcfa65-5fe2-45b9-a372-467946433e84} */
NIDL_INTERFACE("edfcfa65-5fe2-45b9-a372-467946433e84") ILVuInt32 : public ILVData
{
public:
   virtual uInt32 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      uInt32 value) = 0;
} ;

/* Generated header for interface ILVuInt64 */

NIDL_EXTERN_C const IID IID_ILVuInt64;

/* {b173fe84-2ce5-4d23-b1b2-da1f469e2c31} */
NIDL_INTERFACE("b173fe84-2ce5-4d23-b1b2-da1f469e2c31") ILVuInt64 : public ILVData
{
public:
   virtual uInt64 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      uInt64 value) = 0;
} ;

/* Generated header for interface ILVFloat32 */

NIDL_EXTERN_C const IID IID_ILVFloat32;

/* {947ab4f3-5a0c-491a-9f3e-1ffa6ca9b3af} */
NIDL_INTERFACE("947ab4f3-5a0c-491a-9f3e-1ffa6ca9b3af") ILVFloat32 : public ILVData
{
public:
   virtual float32 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      float32 value) = 0;
} ;

/* Generated header for interface ILVFloat64 */

NIDL_EXTERN_C const IID IID_ILVFloat64;

/* {6ba720b2-7641-4657-9a88-e4805c07d953} */
NIDL_INTERFACE("6ba720b2-7641-4657-9a88-e4805c07d953") ILVFloat64 : public ILVData
{
public:
   virtual float64 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      float64 value) = 0;
} ;

/* Generated header for interface ILVFloatExt */

NIDL_EXTERN_C const IID IID_ILVFloatExt;

/* {35b495a1-ef73-4602-a91e-5307ea364870} */
NIDL_INTERFACE("35b495a1-ef73-4602-a91e-5307ea364870") ILVFloatExt : public ILVData
{
public:
   virtual floatExt NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      floatExt value) = 0;
} ;

/* Generated header for interface ILVComplex64 */

NIDL_EXTERN_C const IID IID_ILVComplex64;

/* {b34b09a6-e681-4b7b-b81f-27718a7ac22d} */
NIDL_INTERFACE("b34b09a6-e681-4b7b-b81f-27718a7ac22d") ILVComplex64 : public ILVData
{
public:
   virtual cmplx64 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      cmplx64 value) = 0;
} ;

/* Generated header for interface ILVComplex128 */

NIDL_EXTERN_C const IID IID_ILVComplex128;

/* {29cf50ff-334a-416b-8e62-4305d724ea74} */
NIDL_INTERFACE("29cf50ff-334a-416b-8e62-4305d724ea74") ILVComplex128 : public ILVData
{
public:
   virtual cmplx128 NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      cmplx128 value) = 0;
} ;

/* Generated header for interface ILVComplexExt */

NIDL_EXTERN_C const IID IID_ILVComplexExt;

/* {09b41f06-659b-4fb8-8c8c-6641fde83303} */
NIDL_INTERFACE("09b41f06-659b-4fb8-8c8c-6641fde83303") ILVComplexExt : public ILVData
{
public:
   virtual cmplxExt NIDL_STDMETHODCALLTYPE Get(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      cmplxExt value) = 0;
} ;

/* Generated header for interface ILVArray */

typedef struct ArrayDimensionSpecifier {
   size_t dimensionSize;
   ptrdiff_t stride;
} ArrayDimensionSpecifier;
typedef struct ArraySpecifier {
   void* dataPtr;
   ArrayDimensionSpecifier dimensionSpecifier[1];
} ArraySpecifier;
NIDL_EXTERN_C const IID IID_ILVArray;

/* {5b5e5197-5580-431a-ad73-9ab7261d394d} */
NIDL_INTERFACE("5b5e5197-5580-431a-ad73-9ab7261d394d") ILVArray : public ILVData
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE GetNumDimensions(
      uInt32* numDimensions) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetDimensions(
      size_t* dimensionsBuffer) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetNumElements(
      size_t* numElements) = 0;
   virtual Bool32 NIDL_STDMETHODCALLTYPE IsEmpty(void) = 0;
   virtual void NIDL_STDMETHODCALLTYPE Clear(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetArraySpecifier(
      ArraySpecifier* arraySpecifier) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElement(
      size_t* indices,
      Bool32 makeCopy,
      ILVData** element) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE SetElement(
      size_t* indices,
      ILVData* element) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Resize(
      size_t* dimensions) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Reshape(
      size_t* dimensions) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE IndexArray(
      size_t* indices,
      ILVArray** array) = 0;
} ;

// Template version of ArraySpecifier for use with multiple dimensions
// Use this to declare a multi-dimensional ArraySpecifier on the stack (avoiding the heap allocator)
// Usage:
//	ArraySpecifierT<3> arraySpec; // 3-dimensional array specifier
//	err = pIface->GetArraySpecifier((ArraySpecifier*)&arraySpec); // Cast necessary to convert to C-style ArraySpecifier
#if defined(__cplusplus)
template<int nDims> struct ArraySpecifierT
{
	void* dataPtr;
	ArrayDimensionSpecifier dimensionSpecifier[nDims];
};
#endif // defined(__cplusplus)
/* Generated header for interface ILVString */

NIDL_EXTERN_C const IID IID_ILVString;

/* {c021ae89-68d7-47e9-9ed7-69d9501c4f24} */
NIDL_INTERFACE("c021ae89-68d7-47e9-9ed7-69d9501c4f24") ILVString : public ILVData
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE Get(
      const uChar** stringBuffer,
      size_t* bufferLength) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetCStr(
      const uChar** buffer) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Set(
      const uChar* stringBuffer,
      size_t bufferLength) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE SetILVString(
      const ILVString* str) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Append(
      const uChar* stringBuffer,
      size_t bufferLength) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE AppendILVString(
      const ILVString* str) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Insert(
      size_t position,
      const uChar* stringBuffer,
      size_t bufferLength) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE InsertILVString(
      size_t position,
      const ILVString* str) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Replace(
      size_t position,
      const uChar* stringBuffer,
      size_t numElements) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE ReplaceILVString(
      size_t position,
      const ILVString* str) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Erase(
      size_t position,
      size_t numElements) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE Clear(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetCapacity(
      size_t* capacity) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE SetCapacity(
      size_t capacity) = 0;
   virtual Bool32 NIDL_STDMETHODCALLTYPE IsEmpty(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE SubString(
      size_t position,
      size_t length,
      ILVString** subString) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetLength(
      size_t* length) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElement(
      size_t position,
      uChar* element) = 0;
} ;

/* Generated header for interface ILVCluster */

NIDL_EXTERN_C const IID IID_ILVCluster;

/* {5377527d-a5aa-4819-8933-adbf444e9ff4} */
NIDL_INTERFACE("5377527d-a5aa-4819-8933-adbf444e9ff4") ILVCluster : public ILVData
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElement(
      uInt32 position,
      Bool32 makeCopy,
      ILVData** element) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE SetElement(
      uInt32 position,
      ILVData* element) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetScalarElement(
      uInt32 position,
      uInt32 elementSize,
      void* element) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE SetScalarElement(
      uInt32 position,
      uInt32 elementSize,
      void* element) = 0;
} ;



#endif /* __ILVDataInterface_h__ */
