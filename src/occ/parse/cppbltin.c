/*
    Software License Agreement (BSD License)
    
    Copyright (c) 1997-2011, David Lindauer, (LADSoft).
    All rights reserved.
    
    Redistribution and use of this software in source and binary forms, 
    with or without modification, are permitted provided that the following 
    conditions are met:
    
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
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
    OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
    OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
/* declare in select has multiple vars */
#include "compiler.h"
extern INCLUDES *includes;
extern char *errorfile;
extern int errorline;
static char *cppbuiltin = "void * operator new(unsigned size); " 
    "void * operator new[](unsigned size); " 
    "void   operator delete  (void *); " 
	"void   operator delete[](void *); "
    "void * __dynamic_cast(void *, void *, void *); " 
    "void   _CatchCleanup(); " 
    "void * __GetTypeInfo(void *block, void *instance); " 
    "void _ThrowException(void *,void *,void*); " 
	"void _RethrowException(); "
    "void __arrCall(void *, int, int, int); ";

void ParseBuiltins(void)
{
    if (cparams.prm_cplusplus)
    {
        LEXEME *lex;
        FILE *handle = includes->handle;
        char *p = includes->lptr;
        errorfile="--builtin--";
        includes->lptr = cppbuiltin;
        includes->handle = NULL;
        lex = getsym();
        if (lex)
        {
            while ((lex = declare(lex, NULL, NULL, sc_global, lk_none, NULL, TRUE, FALSE, FALSE, ac_public)) != NULL) ;
        }
        includes->handle = handle;
        includes->lptr = p;
    }
}