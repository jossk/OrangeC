/*
	Software License Agreement (BSD License)
	
	Copyright (c) 1997-2008, David Lindauer, (LADSoft).
	All rights reserved.
	
	Redistribution and use of this software in source and binary forms, with or without modification, are
	permitted provided that the following conditions are met:
	
	* Redistributions of source code must retain the above
	  copyright notice, this list of conditions and the
	  following disclaimer.
	
	* Redistributions in binary form must reproduce the above
	  copyright notice, this list of conditions and the
	  following disclaimer in the documentation and/or other
	  materials provided with the distribution.
	
	* Neither the name of LADSoft nor the names of its
	  contributors may be used to endorse or promote products
	  derived from this software without specific prior
	  written permission of LADSoft.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
	PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
	TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __WCHAR_H
#define __WCHAR_H 

#pragma pack(1)

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STDARG_H
#include <stdarg.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifndef __TCHAR_H
#include <tchar.h>
#endif


/* we use UTF-8 for multibyte encoding
 * wide characters are written in network order (big endian)
 *
 * already declared in stddef.h, declared here for reference
 */
#ifndef _WINT_T_DEFINED
#define _WINT_T_DEFINED
typedef unsigned int wint_t;
#endif

#ifdef __cplusplus
namespace std {
extern "C" {
#endif

#ifndef _MBSTATE_T_DEFINED
#define _MBSTATE_T_DEFINED
typedef struct
{
  size_t left;
  wint_t value;
} mbstate_t;
#endif

struct tm;

#define WCHAR_MIN ((wchar_t) 0)
#define WCHAR_MAX ((wchar_t)(~WCHAR_MIN))

#ifndef WEOF
#define WEOF (wint_t)(-1)
#endif

wchar_t *_RTL_FUNC wcscpy (wchar_t *restrict __dest, const wchar_t *restrict __src);
wchar_t *_RTL_FUNC wcsncpy (wchar_t *restrict __dest, const wchar_t *restrict __src,
			      size_t __n);

wchar_t *_RTL_FUNC wcpcpy (wchar_t *restrict __dest, const wchar_t *restrict __src);
wchar_t *_RTL_FUNC wcpncpy (wchar_t *restrict __dest, const wchar_t *restrict __src,
			      size_t __n);

wchar_t *_RTL_FUNC wcscat (wchar_t *restrict __dest, const wchar_t *restrict __src);
wchar_t *_RTL_FUNC wcsncat (wchar_t *restrict __dest, const wchar_t *restrict __src,
			      size_t __n);

int _RTL_FUNC wcscmp (const wchar_t *__s1, const wchar_t *__s2);
int _RTL_FUNC wcsncmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n);

int _RTL_FUNC wcsicmp(wchar_t *__s1, wchar_t *__s2);
int _RTL_FUNC wcsnicmp(wchar_t *__s1, wchar_t *__s2, size_t __n);
int _RTL_FUNC _wcsicmp(wchar_t *__s1, wchar_t *__s2);
int _RTL_FUNC _wcsnicmp(wchar_t *__s1, wchar_t *__s2, size_t __n);

/* these two do blind copy/compare irregardless of locale*/
int _RTL_FUNC wcscoll (const wchar_t *__s1, const wchar_t *__s2);
size_t _RTL_FUNC wcsxfrm (wchar_t *restrict __s1, const wchar_t *restrict __s2, 
                    size_t __n);

wchar_t *_RTL_FUNC wcsdup (const wchar_t *__s);

wchar_t *_RTL_FUNC wcschr (const wchar_t *__wcs, wchar_t __wc);
wchar_t *_RTL_FUNC wcsrchr (const wchar_t *__wcs, wchar_t __wc);

size_t _RTL_FUNC wcscspn (const wchar_t *__wcs,
			    const wchar_t *__reject);
size_t _RTL_FUNC wcsspn (const wchar_t *__wcs, const wchar_t *__accept);
wchar_t *_RTL_FUNC wcspbrk (const wchar_t *__wcs,
			      const wchar_t *__accept);
wchar_t *_RTL_FUNC wcsstr (const wchar_t *__haystack,
			     const wchar_t *__needle);
wchar_t *_RTL_FUNC wcstok (wchar_t *restrict __s, const wchar_t *restrict __delim,
			     wchar_t **ptr);

wchar_t * _RTL_FUNC wcsupr(wchar_t *__s);
wchar_t * _RTL_FUNC wcslwr(wchar_t *__s);

size_t _RTL_FUNC wcslen (const wchar_t *__s);

wchar_t *_RTL_FUNC wmemchr (const wchar_t *__s, wchar_t __c, size_t __n);
int wmemcmp (const wchar_t *__s1, const wchar_t *__s2,
			 size_t __n);
wchar_t *_RTL_FUNC wmemcpy (wchar_t *restrict __s1, const wchar_t *restrict __s2,
			      size_t __n);
wchar_t *_RTL_FUNC wmemmove (wchar_t *__s1, const wchar_t *__s2,
			       size_t __n);
wchar_t *_RTL_FUNC wmemset (wchar_t *__s, wchar_t __c, size_t __n);

wint_t _RTL_FUNC btowc (int __c);
int _RTL_FUNC wctob (wint_t __c);

int _RTL_FUNC mbsinit (const mbstate_t *__ps);

size_t _RTL_FUNC mbrtowc (wchar_t *restrict __pwc, const char *restrict __s, size_t __n,
			    mbstate_t *restrict __p);
size_t _RTL_FUNC wcrtomb (char *restrict __s, wchar_t __wc, mbstate_t *restrict __ps);

size_t _RTL_FUNC mbrlen (const char *restrict __s, size_t __n, mbstate_t *restrict __ps);

size_t _RTL_FUNC mbsrtowcs (wchar_t *restrict __dst, const char **restrict __src,
			      size_t __len, mbstate_t *restrict __ps);
size_t _RTL_FUNC wcsrtombs (char *restrict __dst, const wchar_t **restrict __src,
			      size_t __len, mbstate_t *restrict __ps);

float _RTL_FUNC wcstof (const wchar_t *restrict __nptr, wchar_t **restrict __endptr);
double _RTL_FUNC wcstod (const wchar_t *restrict __nptr, wchar_t **restrict __endptr);
long double _RTL_FUNC wcstold (const wchar_t *restrict __nptr, wchar_t **restrict __endptr);
long int _RTL_FUNC wcstol (const wchar_t *restrict __nptr, wchar_t **restrict __endptr, 
                        int __base);
unsigned long int _RTL_FUNC wcstoul (const wchar_t *restrict __nptr,
				       wchar_t **restrict __endptr, int __base);
#if  __STDC_VERSION__ >= 199901L
long long int _RTL_FUNC wcstoll (const wchar_t *restrict __nptr, wchar_t **restrict __endptr,
				  int __base);
unsigned long long int _RTL_FUNC wcstoull (const wchar_t *restrict __nptr,
					    wchar_t **restrict __endptr, int __base);
#endif
double  _RTL_FUNC wtof(const wchar_t *__string);
long double  _RTL_FUNC _wtold(const wchar_t *__string);
wchar_t * _RTL_FUNC itow(int __value, wchar_t *__string, int __radix);
wchar_t * _RTL_FUNC ltow(long __value, wchar_t *__string, int __radix);

size_t _RTL_FUNC wcsftime(wchar_t *restrict __str, size_t __maxsize, 
                const wchar_t *restrict __format, const struct tm * restrict __t);

int _RTL_FUNC fwprintf(FILE * restrict __stream,
                const wchar_t * restrict __format, ...);
int _RTL_FUNC fwscanf(FILE * restrict __stream,
                const wchar_t * restrict __format, ...);
#if defined(__MSVCRT_DLL) || defined(__CRTDLL_DLL)
int _RTL_FUNC swprintf(wchar_t * restrict s,
                const wchar_t * restrict __format, ...);
#else
int _RTL_FUNC swprintf(wchar_t * restrict s,
                size_t n, const wchar_t * restrict __format, ...);
#endif
int _RTL_FUNC snwprintf(wchar_t *restrict buffer, size_t n, const wchar_t *restrict format, ...);
int _RTL_FUNC _snwprintf(wchar_t *restrict buffer, size_t n, const wchar_t *restrict format, ...);
int _RTL_FUNC swscanf(const wchar_t * restrict s,
                const wchar_t * restrict __format, ...);
int _RTL_FUNC vfwprintf(FILE * restrict __stream, const wchar_t * restrict __format,
                va_list __arg);                
int _RTL_FUNC vfwscanf(FILE * restrict __stream,
                const wchar_t * restrict __format, va_list __arg);
#if defined(__MSVCRT_DLL) || defined(__CRTDLL_DLL)
int _RTL_FUNC vswprintf(wchar_t * restrict s,
                const wchar_t * restrict __format, va_list __arg);
#else
int _RTL_FUNC vswprintf(wchar_t * restrict s, size_t n,
                const wchar_t * restrict __format, va_list __arg);
#endif
int _RTL_FUNC vsnwprintf(wchar_t *restrict buf, size_t n, 
                            const wchar_t *restrict format, va_list arglist);
int _RTL_FUNC _vsnwprintf(wchar_t *restrict buf, size_t n, 
                            const wchar_t *restrict format, va_list arglist);
int _RTL_FUNC vswscanf(const wchar_t * restrict s, const wchar_t * restrict __format,
                va_list __arg);
int _RTL_FUNC vwprintf(const wchar_t * restrict __format, va_list __arg);
int _RTL_FUNC wprintf(const wchar_t * restrict __format, ...);
int _RTL_FUNC wscanf(const wchar_t * restrict __format, ...);

wint_t _RTL_FUNC fgetwc(FILE *__stream);
wchar_t *_RTL_FUNC fgetws(wchar_t * restrict __s, int __n, FILE * restrict __stream);
wint_t _RTL_FUNC fputwc(wchar_t c, FILE *__stream);
int _RTL_FUNC fputws(const wchar_t * restrict s, FILE * restrict __stream);
int _RTL_FUNC fwide(FILE *__stream, int __mode);
wint_t _RTL_FUNC getwc(FILE *__stream);
wint_t _RTL_FUNC getwchar(void);
wint_t _RTL_FUNC putwc(wchar_t c, FILE *__stream);
wint_t _RTL_FUNC putwchar(wchar_t __c);
wint_t _RTL_FUNC ungetwc(wint_t c, FILE *__stream);
int fwide(FILE *__stream, int __mode);

#define getwc(f) fgetwc(f)
#define putwc(c,f) fputwc((c),f)
#define getwchar()  getwc(stdin)
#define putwchar(c) putwc((c), stdout)

#ifdef __cplusplus
};
};
#endif

#pragma pack()

#endif /* wchar.h  */
#if defined(__cplusplus) && !defined(__USING_CNAME__) && !defined(__WCHAR_H_USING_LIST)
#define __WCHAR_H_USING_LIST
	using std::wcscpy;
	using std::wcsncpy;
	using std::wcpcpy;
	using std::wcpncpy;
	using std::wcscat;
	using std::wcsncat;
	using std::wcscmp;
	using std::wcsncmp;
	using std::wcsicmp;
	using std::wcsnicmp;
	using std::_wcsicmp;
	using std::_wcsnicmp;
	using std::wcscoll;
	using std::wcsxfrm;
	using std::wcsdup;
	using std::wcschr;
	using std::wcsrchr;
	using std::wcscspn;
	using std::wcsspn;
	using std::wcspbrk;
	using std::wcsstr;
	using std::wcstok;
	using std::wcsupr;
	using std::wcslwr;
	using std::wcslen;
	using std::wmemchr;
	using std::wmemcmp;
	using std::wmemcpy;
	using std::wmemmove;
	using std::wmemset;
	using std::btowc;
	using std::wctob;
	using std::mbsinit;
	using std::mbrtowc;
	using std::wcrtomb;
	using std::mbrlen;
	using std::mbsrtowcs;
	using std::wcsrtombs;
	using std::wcstof;
	using std::wcstod;
	using std::wcstold;
	using std::wcstol;
	using std::wcstoul;
#if  __STDC_VERSION__ >= 199901L
	using std::wcstoll;
	using std::wcstoull;
#endif
	using std::wtof;
	using std::_wtold;
	using std::itow;
	using std::ltow;
	using std::wcsftime;
	using std::fwprintf;
	using std::fwscanf;
	using std::swprintf;
	using std::swscanf;
	using std::vfwprintf;
	using std::vfwscanf;
	using std::vswprintf;
	using std::vswscanf;
	using std::vwprintf;
	using std::wprintf;
	using std::wscanf;
	using std::fgetwc;
	using std::fgetws;
	using std::fputwc;
	using std::fputws;
	using std::fwide;
	using std::getwc;
	using std::getwchar;
	using std::putwc;
	using std::putwchar;
	using std::ungetwc;
	using std::fwide;
    using std::mbstate_t;
#endif
