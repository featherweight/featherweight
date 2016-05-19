/**
	(c) Copyright 2007-2016 by National Instruments Corp.
	All rights reserved.

	@file
	@brief  Restore structure alignment after including lv_prolog.h.

	You must include this after including lv_prolog.h.
	
	@note Never put include guards in this header. It is designed to be included multiple times.

	@pre This header requires that the lv_prolog.h header be included before it.
*/

#if !defined(NIDL)
/* Restore byte packing to its previous setting. */
#if MSWin && (ProcessorType == kX86)
	#pragma pack(pop)
#elif Mac
	#pragma options align=reset
#endif /* struct alignment restore */
#endif /* !defined(NIDL) */
