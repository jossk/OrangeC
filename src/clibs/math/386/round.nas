;Software License Agreement (BSD License)
;
;Copyright (c) 1997-2008, David Lindauer, (LADSoft).
;All rights reserved.
;
;Redistribution and use of this software in source and binary forms, with or without modification, are
;permitted provided that the following conditions are met:
;
;* Redistributions of source code must retain the above
;  copyright notice, this list of conditions and the
;  following disclaimer.
;
;* Redistributions in binary form must reproduce the above
;  copyright notice, this list of conditions and the
;  following disclaimer in the documentation and/or other
;  materials provided with the distribution.
;
;* Neither the name of LADSoft nor the names of its
;  contributors may be used to endorse or promote products
;  derived from this software without specific prior
;  written permission of LADSoft.
;
;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
;WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
;PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
;ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
;TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
;ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
%include "matherr.inc"

%ifdef __BUILDING_CRTL_DLL
[export _round]
[export _roundf]
[export _roundl]
%endif
[global _round]
[global _roundf]
[global _roundl]
[global round]
SECTION data CLASS=DATA USE32
nm	db	"round",0

two dd 2
SECTION code CLASS=CODE USE32
round:
    fld1
    fld st1
    fscale
    fxch
    popone ; input, *2
    fld st0
    frndint
    call checkinvalid
    jc xit1
    fsubp st1 ; input, possibly 0
    ftst
    fstsw ax
    sahf
    popone
    mov cl,0
    jnz nearest
    ftst
    fstsw ax
    sahf
    mov cl,8
    ja nearest
    mov cl,4
nearest:
    sub esp,4
    fnstcw	[esp]
    mov	ax,[esp]
    and	ah,0f3h
    or ah,cl
    mov	[esp+2],ax
    fldcw	[esp+2]
    frndint
    call checkinvalid
xit:
    fldcw	[esp]
    add esp,4
    ret
xit1:
    fxch
    popone
    jmp xit
_roundf:
    fld	dword[esp+4]
    sub dl,dl
    jmp short roundx
_roundl:
    fld	tword[esp+4]
    mov dl,2
    jmp short roundx
_round:
    fld	qword[esp+4]
    mov dl,1
roundx:    
    lea eax,[nm]
    call clearmath
    call round
    ret