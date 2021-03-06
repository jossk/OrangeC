/*
    Software License Agreement (BSD License)
    
    Copyright (c) 1997-2009, David Lindauer, (LADSoft).
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

    contact information:
        email: TouchStone222@runbox.com <David Lindauer>
*/
#define REG_MAX 32
#define R_EAX 0
#define R_ECX 1
#define R_EDX 2
#define R_EAXEDX 8
#define R_EDXECX 10
#define R_AL 16
#define R_CL  17
#define R_AX 24
#define R_CX 25
int regmap[REG_MAX][2] = {
{ 0, -1 },
{ 1, -1 },
{ 2, -1 },
{ 3, -1 },
{ 4, -1 },
{ 5, -1 },
{ 6, -1 },
{ 7, -1 },

{ 0, 2 },
{ 0, 1 },
{ 1, 2 },
{ 6, 3 },
{ 7, 3 },
{ 6, 7 },
{ -1, -1 },
{ -1, -1 },

{ 0, -1 },
{ 1, -1 },
{ 2, -1 },
{ 3, -1 },
{ 4, -1 },
{ 5, -1 },
{ 6, -1 },
{ 7, -1 },

{ 0, -1 },
{ 1, -1 },
{ 2, -1 },
{ 3, -1 },
{ 4, -1 },
{ 5, -1 },
{ 6, -1 },
{ 7, -1 },

} ;
static ARCH_REGDESC regNames[] = 
{
    { "EAX", 0, 0, -1, 5, { 8, 9, 16, 20, 24  } },
    { "ECX", 0, 1, -1, 5, { 9, 10, 17, 21, 25 } },
    { "EDX", 0, 2, -1, 5, { 8, 10, 18, 22, 26 } },
    { "EBX", 8, 3, -1, 5, { 11, 12, 19, 23, 27 } },
    { ""},
    { ""},
    { "ESI", 64, 6, -1, 3, { 11, 13, 30  } },
    { "EDI", 128, 7, -1, 3, { 12, 13, 31  } },
    { "EDX:EAX", 0, 2, 0, 10, { 0, 2, 9, 10, 16, 18, 20, 22, 24, 26 } },
    { "ECX:EAX", 0, 1, 0, 10, { 0, 1, 8, 10, 16, 17, 20, 21, 24, 25 } },
    { "EDX:ECX", 0, 2, 1, 10, { 1, 2, 8, 9,  17, 18, 21, 22, 25, 26 } },
    { "EBX:ESI", 72, 3, 6, 8, { 3, 6, 12, 13, 19, 23, 27, 30} },
    { "EBX:EDI", 136, 3, 7, 8, { 3, 7, 11, 13, 19, 23, 27, 31} },
    { "EDI:ESI", 192, 7, 6, 6, { 6, 7, 11, 12, 30, 31} },
    { "", 0 },
    { "", 0 },
    { "AL", 0, 0, -1, 5, { 0, 8, 9, 20, 24 } },
    { "CL", 0, 1, -1, 5, { 1, 9, 10, 21, 25 } },
    { "DL", 0, 2, -1, 5, { 2, 8, 10, 22, 26 } },
    { "BL", 8, 3, -1, 5, { 3, 11, 12, 23, 27 } },
    { "AH", 0, 0, -1, 5, { 0, 8, 9, 16, 24 } },
    { "CH", 0, 1, -1, 5, { 1, 9, 10, 17, 25 } },
    { "DH", 0, 2, -1, 5, { 2, 8, 10, 18, 26 } },
    { "BH", 8, 3, -1, 5, { 3, 11, 12, 19, 27 } },
    { "AX", 0, 0, -1, 5, { 0, 8, 9, 16, 20 } },
    { "CX", 0, 1, -1, 5, { 1, 9, 10, 17, 21 } },
    { "DX", 0, 2, -1, 5, { 2, 8, 10, 18, 22 } },
    { "BX", 8, 3, -1, 5, { 3, 11, 12, 19, 23 } },
    { "", 0 },
    { "", 0 },
    { "SI", 64, 6, -1, 3, { 6, 11, 13 } },
    { "DI", 128, 7, -1, 3, { 7, 12, 13 } },
} ;

static unsigned short pushedDoubleRegsArray[] = { 11, 12, 13 };
static ARCH_REGCLASS pushedDoubleRegs =
{
    NULL, 3, pushedDoubleRegsArray
};
static unsigned short unpushedDoubleRegsArray[] = { 8, 9, 10  };
static ARCH_REGCLASS unpushedDoubleRegs =
{
    NULL, 3, unpushedDoubleRegsArray
};
static unsigned short pushedDwordRegsArray[] = { 3, 6, 7 };
static ARCH_REGCLASS pushedDwordRegs =
{
    &pushedDoubleRegs, 3, pushedDwordRegsArray
};
static unsigned short unpushedDwordRegsArray[] = { 0, 1, 2 };
static ARCH_REGCLASS unpushedDwordRegs =
{
    &unpushedDoubleRegs, 3, unpushedDwordRegsArray
};
static unsigned short pushedWordRegsArray[] = { 27, 30, 31 };
static ARCH_REGCLASS pushedWordRegs =
{
    &pushedDwordRegs, 3, pushedWordRegsArray
};
static unsigned short unpushedWordRegsArray[] = { 24, 25, 26 };
static ARCH_REGCLASS unpushedWordRegs =
{
    &unpushedDwordRegs, 3, unpushedWordRegsArray
};
static unsigned short pushedByteRegsArray[] = { 19, 23 };
static ARCH_REGCLASS pushedByteRegs =
{
    &pushedWordRegs, 2, pushedByteRegsArray
};
static unsigned short unpushedByteRegsArray[] = { 16, 17, 18, 20, 21, 22 };
static ARCH_REGCLASS unpushedByteRegs =
{
    &unpushedWordRegs, 6, unpushedByteRegsArray
};
static unsigned short allByteRegsArray[] = { 16, 17, 18, 19, 20, 21, 22, 23 };
static ARCH_REGCLASS allByteRegs =
{
    NULL, 8, allByteRegsArray
};
static unsigned short allWordRegsArray[] = { 24, 25, 26, 27, 30, 31 };
static ARCH_REGCLASS allWordRegs =
{
    &allByteRegs, 6, allWordRegsArray
};
static unsigned short allDwordRegsArray[] = { 0, 1, 2, 3, 6, 7 };
static ARCH_REGCLASS allDwordRegs =
{
    &allWordRegs, 6, allDwordRegsArray
};
static unsigned short allDoubleRegsArray[] = { 8, 9, 10, 11, 12, 13 };
static ARCH_REGCLASS allDoubleRegs[] = {
    &allDwordRegs, 6, allDoubleRegsArray
};
static ARCH_REGCLASS *regClasses[22][2] =
{
    { NULL, NULL },
    { NULL, NULL },
    { &allByteRegs, &pushedByteRegs },
    { &allByteRegs, &pushedByteRegs },
    { &allWordRegs, &pushedWordRegs },
    { &allWordRegs, &pushedWordRegs },
    { &allDwordRegs, &pushedDwordRegs },
    { &allDwordRegs, &pushedDwordRegs },
    { &allDoubleRegs, &pushedDoubleRegs },
    { &allDwordRegs, &pushedDwordRegs },
    { NULL, NULL },
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL },	
    { NULL, NULL }
};
static ARCH_REGVERTEX pushedVertex = { &pushedByteRegs, NULL, NULL };
static ARCH_REGVERTEX unpushedVertex = { &unpushedByteRegs, NULL, NULL };
static ARCH_REGVERTEX regRoot = { &allDoubleRegs, &pushedVertex, &unpushedVertex } ;

static ARCH_SIZING regCosts = {
    1, /*char a_bool; */
    1, /*char a_char; */
    4, /*char a_short; */
    4, /*char a_wchar_t; */
    4, /*char a_enum; */
    4, /*char a_int; */
    4, /*char a_long; */
    8, /*char a_longlong; */
    4, /*char a_addr; */
    8, /*char a_farptr; */
    4, /*char a_farseg; */
    8, /*char a_memberptr; */    
    0, /*char a_struct; */  /* alignment only */
    0, /*char a_float; */
    0, /*char a_double; */
    0, /*char a_longdouble; */
    0,/*char a_fcomplexpad; */
    0,/*char a_rcomplexpad; */
    0,/*char a_lrcomplexpad; */
} ;

char allocOrder[] = { 1, 1 };
