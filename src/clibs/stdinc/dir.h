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

#ifndef __DIR_H
#define __DIR_H

#pragma pack(1)

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define WILDCARDS 0x01
#define EXTENSION 0x02
#define FILENAME  0x04
#define DIRECTORY 0x08
#define DRIVE     0x10

#define MAXDRIVE  3

#define _A_NORMAL   0x00        /* Normal file, no attributes */
#define _A_RDONLY   0x01        /* Read only attribute */
#define _A_HIDDEN   0x02        /* Hidden file */
#define _A_SYSTEM   0x04        /* System file */
#define _A_VOLID    0x08        /* Volume label */
#define _A_SUBDIR   0x10        /* Directory */
#define _A_ARCH     0x20        /* Archive */

#ifdef __cplusplus
namespace std {
extern "C" {
#endif

#ifndef _FFBLK_DEF
#define _FFBLK_DEF
struct  ffblk   {
    unsigned char   ff_reserved[21];
    unsigned char   ff_attrib;            /* attribute byte for matched file */
    unsigned short  ff_ftime;           /* time of last write to file */
    unsigned short  ff_fdate;           /* date of last write to file */
    unsigned long   ff_fsize;           /* size of file */
    char            ff_name[13];         /* asciiz name of matched file */
    char	    ff_uu[256];
};
#endif

#define MAXPATH   260
#define MAXDIR    256
#define MAXFILE   256
#define MAXEXT    256


int         _RTL_FUNC    chdir( const char  *__path );
int         _RTL_FUNC    findfirst( const char  *__path,
                                    struct ffblk  *__ffblk,
                                    int __attrib );
int         _RTL_FUNC    findnext( struct ffblk  *__ffblk );
void        _RTL_FUNC    fnmerge( char  *__path,
                                    const char  *__drive,
                                    const char  *__dir,
                                    const char  *__name,
                                    const char  *__ext );
int         _RTL_FUNC    fnsplit(const char  *__path,
                                    char  *__drive,
                                    char  *__dir,
                                    char  *__name,
                                    char  *__ext );
int         _RTL_FUNC    getcurdir( int __drive, char  *__directory );
char  *     _RTL_FUNC    getcwd( char  *__buf, int __buflen );
int         _RTL_FUNC    getdisk( void );
int         _RTL_FUNC    mkdir( const char  *__path );
char  *     _RTL_FUNC    mktemp( char  *__template );
int         _RTL_FUNC    rmdir( const char  *__path );
char  *     _RTL_FUNC    searchpath( const char  *__file );
int         _RTL_FUNC    setdisk( int __drive );

int _RTL_FUNC _chdir(const char *);
char * _RTL_FUNC _getcwd(char *, int);
int _RTL_FUNC _mkdir(const char *);
int _RTL_FUNC _rmdir(const char *);

#ifdef __cplusplus
} ;
} ;
#endif

#pragma pack()

#endif  /* __DIR_H */

#if defined(__cplusplus) && !defined(__USING_CNAME__) && !defined(__DIR_H_USING_LIST)
#define __DIR_H_USING_LIST
    using std::chdir;
    using std::_chdir;
    using std::findfirst;
    using std::findnext;
    using std::fnmerge;
    using std::fnsplit;
    using std::getcurdir;
    using std::getcwd;
    using std::_getcwd;
    using std::getdisk;
    using std::mkdir;
    using std::_mkdir;
    using std::mktemp;
    using std::rmdir;
    using std::_rmdir;
    using std::searchpath;
    using std::setdisk;
    using std::ffblk;
#endif
