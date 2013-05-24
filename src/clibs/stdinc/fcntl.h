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
/*  fcntl.h

    Define flag values accessible to open.

*/

#if !defined(__FCNTL_H)
#define __FCNTL_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#if defined(__cplusplus)
namespace std {
extern "C" {
#endif
int _RTL_FUNC _pipe(int *phandles, unsigned int psize, int textmode);

extern int _RTL_DATA _fmode;

/* The first three can only be set by open */

#define O_RDONLY    0
#define O_WRONLY    1
#define O_RDWR      2
#define O_ACCMODE   3       /* mask for file access modes */

/* Flag values for open only */

#define O_CREAT     0x0100  /* create and open file */
#define O_TRUNC     0x0200  /* open with truncation */
#define O_EXCL      0x0400  /* exclusive open */

/* The "open flags" defined above are not needed after open, hence they
   are re-used for other purposes when the file is running.  Sorry, it's
   getting crowded !
*/
#define _O_RUNFLAGS 0x0700
#define _O_WRITABLE 0x0100 /* file is not read-only */
#define _O_EOF      0x0200 /* set when text file hits ^Z   */

/* a file in append mode may be written to only at its end.
*/
#define O_APPEND    0x0800  /* to end of file */

/* MSDOS special bits */

#define O_CHANGED   0x1000  /* user may read these bits, but    */
#define O_DEVICE    0x2000  /*   only RTL\io functions may touch.   */
#define O_TEXT      0x4000  /* CR-LF translation    */
#define O_BINARY    0x8000  /* no translation   */

/* DOS 3.x options */

#define O_NOINHERIT 0x80
#define O_DENYALL   0x10
#define O_DENYWRITE 0x20
#define O_DENYREAD  0x30
#define O_DENYNONE  0x40

#ifdef __cplusplus
} ;
} ;
#endif

#endif  /* __FCNTL_H */

#if defined(__cplusplus) && !defined(__USING_CNAME__) && !defined(__FCNTL_H_USING_LIST)
#define __FCNTL_H_USING_LIST
using std::_pipe ;
using std::_fmode ;
#endif