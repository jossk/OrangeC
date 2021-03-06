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
/*
 * keyword module
 */
#include "compiler.h"
#include "math.h"
#include <limits.h>
#define KWHASHSIZE 253

#ifndef LONGLONG_MAX
#define LONGLONG_MAX LONG_MAX
#endif

#define KW_HASH
#define MAX_LOOKBACK 1024

extern COMPILER_PARAMS cparams ;
extern INCLUDES *includes;
extern char *errorfile;
extern int errorline;

int endline;

static LEXEME *alternateLex;
static BOOL usingAlternateLex;
static ULLONG_TYPE llminus1;
static LEXEME llex[MAX_LOOKBACK];
static int index, head, tail, mark, top;
#ifdef KW_HASH
HASHTABLE *kwhash;
#endif

KEYWORD keywords[] = {
    { "!", 1,  not, KW_ASSEMBLER, TT_UNARY | TT_OPERATOR },
    { "!=", 2,  neq, 0, TT_RELATION | TT_EQUALITY},
    { "#", 1,  hash, 0, TT_UNKNOWN},
    { "%", 1,  mod, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "%:", 2,  hash, 0, TT_UNKNOWN},
    { "%>", 2,  end, 0, TT_CONTROL | TT_BLOCK},
    { "%=", 2,  asmod, 0, TT_ASSIGN | TT_OPERATOR },
    { "&", 1,  and, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "&&", 2,  land, 0, TT_BINARY | TT_OPERATOR },
    { "&=", 2,  asand, 0, TT_ASSIGN | TT_OPERATOR },
    { "(", 1,  openpa, KW_ASSEMBLER, TT_PRIMARY },
    { ")", 1,  closepa, KW_ASSEMBLER, TT_PRIMARY },
    { "*", 1,  star, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "*=", 2,  astimes, 0, TT_ASSIGN | TT_OPERATOR },
    { "+", 1,  plus, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "++", 2,  autoinc, 0, TT_UNARY | TT_INCREMENT },
    { "+=", 2,  asplus, 0, TT_ASSIGN | TT_OPERATOR },
    { ",", 1,  comma, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "-", 1,  minus, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "--", 2,  autodec, 0, TT_UNARY | TT_INCREMENT },
    { "-=", 2,  asminus, 0, TT_ASSIGN | TT_OPERATOR },
    { "->", 2,  pointsto,0, TT_BINARY | TT_POINTER},
    { "->*", 3,  pointstar, 0, TT_BINARY | TT_POINTER },
    { ".", 1,  dot, 0, TT_BINARY | TT_POINTER },
    { ".*", 2,  dotstar, 0, TT_BINARY | TT_POINTER },
    { "...", 3,  ellipse },
    { "/", 1,  divide, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "/=", 2,  asdivide, 0, TT_ASSIGN | TT_OPERATOR },
    { ":", 1,  colon, KW_ASSEMBLER },
    { "::", 2,  classsel, 0, TT_BINARY | TT_SELECTOR },
    { ":>", 2,  closebr, 0, TT_BINARY | TT_POINTER },
    { ";", 1,  semicolon, KW_ASSEMBLER, TT_CONTROL },
    { "<", 1,  lt, 0, TT_RELATION | TT_INEQUALITY },
    { "<%", 2,  begin, 0, TT_CONTROL | TT_BLOCK},
    { "<:", 2,  openbr, 0, TT_BINARY | TT_POINTER },
    { "<<", 2,  leftshift, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "<<=", 3,  asleftshift, 0, TT_ASSIGN | TT_OPERATOR },
    { "<=", 2,  leq, 0, TT_RELATION | TT_INEQUALITY },
    { "=", 1,  assign, 0, TT_ASSIGN | TT_OPERATOR | TT_BASE },
    { "==", 2,  eq, 0, TT_RELATION | TT_EQUALITY },
    { ">", 1,  gt, 0, TT_RELATION | TT_INEQUALITY },
    { ">=", 2,  geq, 0, TT_RELATION | TT_INEQUALITY },
    { ">>", 2,  rightshift, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { ">>=", 3,  asrightshift, 0, TT_ASSIGN | TT_OPERATOR },
    { "?", 1,  hook, 0, TT_BINARY | TT_OPERATOR },
    { "[", 1,  openbr, 0, TT_BINARY | TT_POINTER },
    { "]", 1,  closebr, 0, TT_BINARY | TT_POINTER },
    { "^", 1,  uparrow, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "^=", 2,  asxor, 0, TT_ASSIGN | TT_OPERATOR },
    { "_A0", 3,  kw_A0, KW_NONANSI | KW_68K, TT_VAR },
    { "_A1", 3,  kw_A1, KW_NONANSI | KW_68K, TT_VAR  },
    { "_A2", 3,  kw_A2, KW_NONANSI | KW_68K, TT_VAR  },
    { "_A3", 3,  kw_A3, KW_NONANSI | KW_68K, TT_VAR  },
    { "_A4", 3,  kw_A4, KW_NONANSI | KW_68K, TT_VAR  },
    { "_A5", 3,  kw_A5, KW_NONANSI | KW_68K, TT_VAR  },
    { "_A6", 3,  kw_A6, KW_NONANSI | KW_68K, TT_VAR  },
    { "_A7", 3,  kw_A7, KW_NONANSI | KW_68K, TT_VAR  },
    { "_Alignas", 8,  kw_alignas, KW_C1X, TT_CONTROL },
    { "_Alignof", 8,  kw_alignof, KW_C1X, TT_UNARY | TT_OPERATOR },
    { "_Atomic", 7,  kw_atomic, KW_C1X, TT_POINTERQUAL | TT_TYPEQUAL | TT_BASETYPE },
    { "_Bool", 5,  kw_bool, 0, TT_BASETYPE | TT_BOOL},
    { "_CR0", 4,  kw_cr0, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR1", 4,  kw_cr1, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR2", 4,  kw_cr2, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR3", 4,  kw_cr3, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR4", 4,  kw_cr4, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR5", 4,  kw_cr5, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR6", 4,  kw_cr6, KW_NONANSI | KW_386, TT_VAR  },
    { "_CR7", 4,  kw_cr7, KW_NONANSI | KW_386, TT_VAR  },
    { "_CS", 3,  kw_A8, KW_NONANSI | KW_386, TT_VAR  },
    { "_Complex", 8,  kw__Complex, 0, TT_BASETYPE | TT_COMPLEX },
    { "_D0", 3,  kw_D0, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D1", 3,  kw_D1, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D2", 3,  kw_D2, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D3", 3,  kw_D3, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D4", 3,  kw_D4, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D5", 3,  kw_D5, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D6", 3,  kw_D6, KW_NONANSI | KW_68K, TT_VAR  },
    { "_D7", 3,  kw_D7, KW_NONANSI | KW_68K, TT_VAR  },
    { "_DR0", 4,  kw_dr0, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR1", 4,  kw_dr1, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR2", 4,  kw_dr2, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR3", 4,  kw_dr3, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR4", 4,  kw_dr4, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR5", 4,  kw_dr5, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR6", 4,  kw_dr6, KW_NONANSI | KW_386, TT_VAR  },
    { "_DR7", 4,  kw_dr7, KW_NONANSI | KW_386, TT_VAR  },
    { "_DS", 3,  kw_A9, KW_NONANSI | KW_386, TT_VAR  },
    { "_EAX", 4,  kw_D0, KW_NONANSI | KW_386, TT_VAR  },
    { "_EBP", 4,  kw_D5, KW_NONANSI | KW_386, TT_VAR  },
    { "_EBX", 4,  kw_D3, KW_NONANSI | KW_386, TT_VAR  },
    { "_ECX", 4,  kw_D1, KW_NONANSI | KW_386, TT_VAR  },
    { "_EDI", 4,  kw_D7, KW_NONANSI | KW_386, TT_VAR  },
    { "_EDX", 4,  kw_D2, KW_NONANSI | KW_386, TT_VAR  },
    { "_ES", 3,  kw_AA, KW_NONANSI | KW_386, TT_VAR  },
    { "_ESI", 4,  kw_D6, KW_NONANSI | KW_386, TT_VAR  },
    { "_ESP", 4,  kw_D4, KW_NONANSI | KW_386, TT_VAR  },
    { "_FP0", 4,  kw_F0, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP1", 4,  kw_F1, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP2", 4,  kw_F2, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP3", 4,  kw_F3, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP4", 4,  kw_F4, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP5", 4,  kw_F5, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP6", 4,  kw_F6, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FP7", 4,  kw_F7, KW_NONANSI | KW_68K | KW_386, TT_VAR  },
    { "_FS", 3,  kw_AB, KW_NONANSI | KW_386, TT_VAR  },
    { "_Generic", 8,  kw_generic, KW_C1X, TT_VAR },
    { "_GS", 3,  kw_AC, KW_NONANSI | KW_386, TT_VAR  },
    { "_INF", 4, kw__INF, 0, TT_VAR },
    { "_Imaginary",10,  kw__Imaginary, 0, TT_BASETYPE | TT_COMPLEX  },
    { "_NAN", 4, kw__NAN, 0, TT_VAR },
    { "_Noreturn", 9,  kw_noreturn, KW_C1X, TT_LINKAGE },
    { "_Pragma", 7,  kw__Pragma, KW_C99, TT_UNARY | TT_OPERATOR },
    { "_SS", 3,  kw_AD, KW_NONANSI | KW_386, TT_VAR  },
    { "_Static_assert", 14, kw_static_assert, KW_C1X, 0 },
    { "_Thread_local", 13,  kw_thread_local, KW_C1X, TT_LINKAGE },
    { "_TR0", 4,  kw_tr0, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR1", 4,  kw_tr1, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR2", 4,  kw_tr2, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR3", 4,  kw_tr3, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR4", 4,  kw_tr4, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR5", 4,  kw_tr5, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR6", 4,  kw_tr6, KW_NONANSI | KW_386, TT_VAR  },
    { "_TR7", 4,  kw_tr7, KW_NONANSI | KW_386, TT_VAR  },
    { "__I", 3,  kw___I, 0, TT_VAR  },
    { "__atomic_cmpswp", 15, kw_atomic_cmpswp, 0, TT_VAR },
    { "__atomic_fence", 14, kw_atomic_fence, 0, TT_VAR },
    { "__atomic_flag_test_set", 22, kw_atomic_flag_test_set, 0, TT_VAR },
    { "__atomic_flag_clear", 19, kw_atomic_flag_clear, 0, TT_VAR },
    { "__atomic_load", 13, kw_atomic_load, 0, TT_VAR },
    { "__atomic_modify", 15, kw_atomic_modify, 0, TT_VAR },
    { "__atomic_store", 14, kw_atomic_store, 0, TT_VAR },
    { "__atomic_var_init", 17, kw_atomic_var_init, 0, TT_VAR },
    { "__cdecl", 7,  kw__cdecl, 0, TT_LINKAGE },
    { "__char16_t", 10,  kw_char16_t, KW_CPLUSPLUS | KW_C1X, TT_BASETYPE | TT_INT },
    { "__char32_t", 10,  kw_char32_t, KW_CPLUSPLUS | KW_C1X, TT_BASETYPE | TT_INT },
    { "__export", 8,  kw__export, KW_NONANSI | KW_ALL, TT_LINKAGE},
    { "__func__", 8,  kw___func__, KW_C99 | KW_CPLUSPLUS, TT_UNARY | TT_OPERATOR },
    { "__import", 8,  kw__import, KW_NONANSI | KW_ALL, TT_LINKAGE},
    { "__int16", 7,  kw_short, KW_NONANSI | KW_386, TT_BASETYPE | TT_INT },
    { "__int32", 7,  kw_int, KW_NONANSI | KW_386, TT_BASETYPE | TT_INT | TT_BASE },
    { "__int64", 7,  kw___int64, KW_NONANSI | KW_386, TT_BASETYPE | TT_INT },
    { "__int8", 6,  kw_char, KW_NONANSI | KW_386, TT_BASETYPE | TT_INT },
    { "__kill_dependency", 17, kw_atomic_kill_dependency, 0, TT_VAR },
    { "__pascal", 8,  kw__pascal, KW_NONANSI | KW_ALL, TT_LINKAGE},
    { "__stdcall", 9,  kw__stdcall, KW_NONANSI | KW_ALL, TT_LINKAGE},
    { "__typeid", 8,  kw___typeid, KW_CPLUSPLUS, 0},
    { "_absolute", 9,  kw__absolute, KW_NONANSI | KW_ALL, TT_STORAGE_CLASS},
    { "_cdecl", 6,  kw__cdecl, KW_NONANSI, TT_LINKAGE },
    { "_export", 7,  kw__export, KW_NONANSI, TT_LINKAGE},
//	{ "_far", 4,  kw__far, KW_NONANSI, TT_TYPEQUAL | TT_POINTERQUAL },
    { "_fault", 6,  kw__fault, KW_NONANSI, TT_LINKAGE},
    { "_genbyte", 8,  kw__genword, KW_NONANSI | KW_386, TT_UNARY | TT_OPERATOR},
    { "_genword", 8,  kw__genword, KW_NONANSI | KW_68K, TT_UNARY | TT_OPERATOR},
    { "_import", 7,  kw__import, KW_NONANSI, TT_LINKAGE},
    { "_indirect", 9,  kw__indirect, KW_NONANSI | KW_ALL},
    { "_interrupt",10,  kw__interrupt, KW_NONANSI, TT_LINKAGE},
    { "_intrinsic",10,  kw__intrinsic, KW_NONANSI | KW_ALL, TT_TYPEQUAL},
    { "_loadds", 7,  kw__loadds, KW_NONANSI | KW_386, TT_TYPEQUAL},
//	{ "_near", 5,  kw__near, KW_NONANSI | KW_ALL, TT_TYPEQUAL | TT_POINTERQUAL},
    { "_pascal", 7,  kw__pascal, KW_NONANSI | KW_ALL, TT_LINKAGE},
    { "_seg", 4,  kw__seg, KW_NONANSI | KW_ALL, TT_TYPEQUAL | TT_POINTERQUAL},
    { "_stdcall", 8,  kw__stdcall, KW_NONANSI | KW_ALL, TT_LINKAGE},
    { "_trap", 5,  kw__trap, KW_NONANSI | KW_ALL, TT_OPERATOR | TT_UNARY},
    { "alignas", 7,  kw_alignas, KW_CPLUSPLUS, TT_CONTROL },
    { "alignof", 7,  kw_alignof, KW_CPLUSPLUS, TT_UNARY | TT_OPERATOR },
    { "alloca", 6,  kw_alloca, KW_NONANSI | KW_ALL, TT_OPERATOR | TT_UNARY},
    { "asm", 3,  kw_asm, KW_NONANSI | KW_ALL, TT_CONTROL },
    { "auto", 4,  kw_auto, 0, TT_STORAGE_CLASS },
    { "bool", 4,  kw_bool, KW_CPLUSPLUS, TT_BASETYPE | TT_BOOL },
    { "break", 5,  kw_break, 0, TT_CONTROL },
    { "case", 4,  kw_case, 0, TT_CONTROL | TT_SWITCH },
    { "catch", 5,  kw_catch, KW_CPLUSPLUS, TT_CONTROL },
    { "cdecl", 5,  kw__cdecl, 0, TT_LINKAGE },
    { "char", 4,  kw_char, 0, TT_BASETYPE | TT_INT },
    { "class", 5,  kw_class, KW_CPLUSPLUS, TT_BASETYPE | TT_STRUCT },
    { "const", 5,  kw_const, KW_ASSEMBLER, TT_POINTERQUAL | TT_TYPEQUAL },
    { "const_cast",10,  kw_const_cast, KW_CPLUSPLUS, TT_UNARY | TT_OPERATOR },
    { "constexpr", 9,  kw_constexpr, KW_CPLUSPLUS, TT_DECLARE},
    { "continue", 8,  kw_continue, 0, TT_CONTROL },
    { "decltype", 8,  kw_decltype, KW_CPLUSPLUS, TT_BASETYPE | TT_OPERATOR },
    { "default", 7,  kw_default, 0, TT_CONTROL },
    { "delete", 6,  kw_delete, KW_CPLUSPLUS, TT_UNARY | TT_OPERATOR },
    { "do", 2,  kw_do, 0, TT_CONTROL },
    { "double", 6,  kw_double, 0, TT_BASETYPE | TT_FLOAT },
    { "dynamic_cast",12,  kw_dynamic_cast, KW_CPLUSPLUS, TT_UNARY | TT_OPERATOR },
    { "else", 4,  kw_else, 0, TT_CONTROL },
    { "enum", 4,  kw_enum, 0, TT_BASETYPE | TT_ENUM },
    { "explicit", 8,  kw_explicit, KW_CPLUSPLUS, TT_UNKNOWN },
    { "export", 6,  kw_export, KW_CPLUSPLUS, TT_UNKNOWN },
    { "extern", 6,  kw_extern, KW_ASSEMBLER, TT_STORAGE_CLASS },
    { "false", 4, kw_false, KW_CPLUSPLUS, TT_VAR },
//	{ "far", 3,  kw__far, KW_NONANSI | KW_ALL, TT_POINTERQUAL | TT_TYPEQUAL},
    { "final", 5, kw_final, KW_CPLUSPLUS, 0 },
    { "float", 5,  kw_float, 0, TT_BASETYPE | TT_FLOAT },
    { "for", 3,  kw_for, 0, TT_CONTROL },
    { "friend", 6,  kw_friend, KW_CPLUSPLUS, TT_DECLARE },
    { "goto", 4,  kw_goto, 0, TT_CONTROL },
    { "if", 2,  kw_if, 0, TT_CONTROL },
    { "inline", 6,  kw_inline, KW_C99 | KW_CPLUSPLUS, TT_LINKAGE },
    { "int", 3,  kw_int, 0, TT_BASETYPE | TT_INT | TT_BASE },
    { "long", 4,  kw_long, 0, TT_BASETYPE | TT_INT },
    { "mutable", 7,  kw_mutable, KW_CPLUSPLUS, 0},
    { "namespace", 9,  kw_namespace, KW_CPLUSPLUS, TT_STORAGE_CLASS },
//	{ "near", 4,  kw__near, KW_NONANSI | KW_ALL, TT_POINTERQUAL | TT_TYPEQUAL},
    { "new", 3,  kw_new, KW_CPLUSPLUS, TT_OPERATOR | TT_UNARY },
    { "noexcept", 8,  kw_noexcept, KW_CPLUSPLUS, TT_CONTROL},
    { "nullptr", 7,  kw_nullptr, KW_CPLUSPLUS,  TT_VAR},
    { "operator", 8,  kw_operator, KW_CPLUSPLUS, TT_OPERATOR },
    { "override", 8, kw_override, KW_CPLUSPLUS, 0 },
    { "private", 7,  kw_private, KW_CPLUSPLUS, TT_CLASS },
    { "protected", 9,  kw_protected, KW_CPLUSPLUS, TT_CLASS },
    { "public", 6,  kw_public, KW_CPLUSPLUS | KW_ASSEMBLER, TT_CLASS },
    { "register", 8,  kw_register, 0, TT_STORAGE_CLASS },
    { "reinterpret_cast",16,  kw_reinterpret_cast, KW_CPLUSPLUS, TT_OPERATOR | TT_UNARY },
    { "restrict", 8,  kw_restrict, KW_C99, TT_POINTERQUAL | TT_TYPEQUAL },
    { "return", 6,  kw_return, 0, TT_CONTROL },
    { "short", 5,  kw_short, 0, TT_BASETYPE | TT_INT },
    { "signed", 6,  kw_signed, 0, TT_BASETYPE | TT_INT },
    { "sizeof", 6,  kw_sizeof, 0, TT_UNARY | TT_OPERATOR },
    { "static", 6,  kw_static, 0, TT_STORAGE_CLASS },
    { "static_assert", 13, kw_static_assert, KW_CPLUSPLUS, 0 },
    { "static_cast",11,  kw_static_cast, KW_CPLUSPLUS, TT_UNARY | TT_OPERATOR },
    { "struct", 6,  kw_struct, 0, TT_BASETYPE | TT_STRUCT },
    { "switch", 6,  kw_switch, 0, TT_CONTROL },
    { "template", 8,  kw_template, KW_CPLUSPLUS, TT_STORAGE_CLASS },
    { "this", 4,  kw_this, KW_CPLUSPLUS, TT_VAR },
    { "thread_local", 12,  kw_thread_local, KW_CPLUSPLUS, TT_LINKAGE },
    { "throw", 5,  kw_throw, KW_CPLUSPLUS, TT_OPERATOR | TT_UNARY },
    { "true", 4, kw_true, KW_CPLUSPLUS, TT_VAR },
    { "try", 3,  kw_try, KW_CPLUSPLUS, TT_CONTROL },
    { "typedef", 7,  kw_typedef, 0, TT_BASETYPE | TT_TYPEDEF | TT_STORAGE_CLASS },
    { "typeid", 6,  kw_typeid, KW_CPLUSPLUS, TT_UNKNOWN },
    { "typename", 8,  kw_typename, KW_CPLUSPLUS, TT_BASETYPE | TT_TYPENAME },
    { "typeof", 6,  kw_typeof, 0, TT_BASETYPE | TT_OPERATOR },
    { "union", 5,  kw_union, 0, TT_BASETYPE | TT_STRUCT },
    { "unsigned", 8,  kw_unsigned, 0, TT_BASETYPE | TT_INT | TT_BASE },
    { "using", 5,  kw_using, KW_CPLUSPLUS, TT_CONTROL },
    { "virtual", 7,  kw_virtual, KW_CPLUSPLUS, TT_STORAGE_CLASS },
    { "void", 4,  kw_void, 0, TT_BASETYPE | TT_VOID },
    { "volatile", 8,  kw_volatile, 0, TT_TYPEQUAL | TT_POINTERQUAL },
    { "wchar_t", 7,  kw_wchar_t, KW_CPLUSPLUS, TT_BASETYPE },
    { "while", 5,  kw_while, 0, TT_CONTROL },
    { "{", 1,  begin, 0, TT_CONTROL | TT_BLOCK},
    { "|", 1,  or, KW_ASSEMBLER, TT_BINARY | TT_OPERATOR },
    { "|=", 2,  asor, 0, TT_ASSIGN | TT_OPERATOR },
    { "||", 2,  lor, 0, TT_BINARY | TT_OPERATOR },
    { "}", 1,  end, 0, TT_CONTROL | TT_BLOCK},
    { "~", 1,  compl, KW_ASSEMBLER, TT_UNARY | TT_OPERATOR },
};

#define TABSIZE (sizeof(keywords)/ sizeof(keywords[0]))
static BOOL kwmatches(KEYWORD *kw);
void lexini(void)
/*
 * create a keyword hash table
 */
{
#ifdef KW_HASH
    int i;
    kwhash = CreateHashTable(1024);
    for (i=0; i < TABSIZE; i++)
    {
        if (kwmatches(&keywords[i]))
            insert((SYMBOL *)&keywords[i], kwhash);
    }
#endif
    llminus1 = 0;
    llminus1--;
}

/*-------------------------------------------------------------------------*/


#ifndef KW_HASH
static KEYWORD *binarySearch(char *name)
{
    int top = TABSIZE;
    int bottom =  - 1;
    int v;
    KEYWORD *kw;
    while (top - bottom > 1)
    {
        int mid = (top + bottom) / 2;
        kw = &keywords[mid];
        v = strncmp(name, kw->name, kw->len);
        if (v < 0)
        {
            top = mid;
        }
        else
        {
            bottom = mid;
        }
    }
    if (bottom == -1)
        return 0;
    kw = &keywords[bottom];
    v = strncmp(name, kw->name, kw->len);
    if (v)
        return 0;
    return  &keywords[bottom];
}
#endif
static BOOL kwmatches(KEYWORD *kw)
{
    if (cparams.prm_assemble)
        return !!(kw->matchFlags & KW_ASSEMBLER);
    else if (!kw->matchFlags || kw->matchFlags == KW_ASSEMBLER)
        return TRUE;
    else if (((kw->matchFlags & KW_CPLUSPLUS) && cparams.prm_cplusplus) ||
        (kw->matchFlags & (KW_C99 | KW_C1X)) ||
        ((kw->matchFlags & (KW_NONANSI | KW_INLINEASM)) && !cparams.prm_ansi))
    {
            if (kw->matchFlags & KW_NONANSI)
            {
                /* fill in here for processor specific */
            }
            return TRUE;
    }
    return FALSE;
}
KEYWORD *searchkw(char **p)
/*
 * see if the current symbol is a keyword
 */
{
    KEYWORD *kw;
    char buf[1000], *q = buf,*q1 = *p;
    if (isstartchar(*q1))
    {
        int len = 0;
        while (issymchar(*q1))
        {
            len++;
            *q++ = *q1++;
        }
        *q = 0;
#ifdef KW_HASH
        kw = (KEYWORD *)search(buf, kwhash);
        if (kw)
#else
        kw = (KEYWORD *)binarySearch(buf);
        if (kw && kwmatches(kw))
#endif
        {
            if (len == kw->len)
            {
                BOOL count = 0;
                if (kw->matchFlags & (KW_C99 | KW_C1X))
                {
                    if (cparams.prm_c99 && (kw->matchFlags & KW_C99))
                        count++;
                    if (cparams.prm_c1x && (kw->matchFlags & KW_C1X))
                        count++;
                    if (cparams.prm_cplusplus && (kw->matchFlags & KW_CPLUSPLUS))
                        count++;
                    if (!count)
                    {
                        errorstr(ERR_C99_KEYWORD, buf);
                        return NULL;
                    }
                }
                *p = *p + len;
                return kw;
            }
        }
    }
    else
    {
        KEYWORD *found;
#ifdef KW_HASH
        int len = 0;
        while (ispunct(*q1))
            *q++ = *q1++, len++;
        if (len)
        {
            buf[len] = 0;
            while (len && (found = (KEYWORD *)search(buf, kwhash)) == NULL)
            {
                buf[--len] = 0;
            }
            if (found)		
#else
        *q++ = *q1++;
        *q = 0;
        kw = (KEYWORD *)binarySearch(buf);
        if (kw)
        {
            KEYWORD *list = kw;
            found = kw;
            while (list < &keywords[0] + sizeof(keywords)/sizeof(keywords[0])
                   && buf[0] == list->name[0])
            {
                if (!strncmp(list->name, *p, list->len))
                {
                    found = list;
                }
                list++;
            }
            if (kwmatches(found))
#endif
            {
                *p = *p + found->len;
                return found;
            }
        }
    }
    return NULL;
}
int getChar(char **source, enum e_lexType *tp)
{
    enum e_lexType v = l_achr;
    char *p = *source;
    if (*p == 'L')
    {
        v = l_wchr;
        p++;
    }
    else if (cparams.prm_cplusplus || cparams.prm_c1x)
    {
        if (*p == 'u')
        {
            v = l_uchr;
            p++;
        }
        else if (*p == 'U')
        {
            v = l_Uchr;
            p++;
        }
    }
    if (*p == '\'')
    {
        int i ;
        p++;
        i = getsch(v == l_Uchr ? 8 : v == l_wchr || v == l_uchr ? 4 : 2, &p);
        if (i == INT_MIN)
        {
            error(ERR_INVALID_CHAR_CONSTANT);
            i = '0';
        }
        if (*p != '\'')
        {
            if (v == l_uchr || v == l_Uchr)
            {
                error(ERR_CHAR1632_CONSTANT_TOO_LONG);
            }
            else
            {
                int j;
                j = getsch(v == l_Uchr ? 8 : v == l_wchr || v == l_uchr ? 4 : 2, &p);
                if (j == INT_MIN)
                {
                    error(ERR_INVALID_CHAR_CONSTANT);
                    j = '0';
                }
                i += j << 8;
                if (*p != '\'')
                {
                    error(ERR_UNTERM_CHAR_CONSTANT);
                }
                else
                    p++;
            }
        }
        else
            p++;
        *tp = v;
        *source = p;
        return i;
    }
    return INT_MIN;
}
SLCHAR *getString(char **source, enum e_lexType *tp)
{
    BOOL raw = FALSE;
    BOOL found = FALSE;
    char *p = *source;
    LCHAR data[32768], *dest = data;
    int len = sizeof(data)/sizeof(data[0]);
    int count = 0;
    BOOL errored = FALSE;
    enum e_lexType v = l_astr;
    if (*p == 'L')
    {
        v = l_wstr;
        p++;
    }
    else if (cparams.prm_cplusplus || cparams.prm_c1x)
    {
        if (*p == 'u')
        {
            v = l_ustr;
            p++;
            if (*p == '8')
            {
                v = l_u8str;
                p++;
            }
        }
        else if (*p == 'U')
        {
            v = l_Ustr;
            p++;
        }
    }
    if (cparams.prm_cplusplus && *p == 'R')
    {
        raw = TRUE;
        p++;
    }
    if (*p == '"')
    {
        p++;
        if (raw)
        {
            // fixme utf8 raw strings...
            char preamble[16];
            int pcount = 0, qcount;
            LCHAR *qpos = 0;
            int lineno = includes->line;
            char st[2];
            BOOL err = FALSE;
            while (TRUE)
            {
                if (*p)
                    st[0] = *p++;
                else if (getstring(st, 1, includes->handle))
                {
                    errorint(ERR_EOF_RAW_STRING, lineno);
                    *source = p;
                    return NULL;
                }
                if (err)
                {
                    if (st[0] == '"')
                    {
                        SLCHAR *rv;
                        int i;
                        *source = p;
                        IncGlobalFlag();
                        rv = Alloc(sizeof(SLCHAR));
                        rv->str = (LCHAR *)Alloc(1);
                        rv->str[0] = 0;
                        rv->count = 1;
                        DecGlobalFlag();
                        return rv;
                    }                    
                }
                else if (st[0] == '(')
                {
                    break;
                }
                else if (st[0] == '\n' || st[0] == ' ' || st[0] == '\v' || st[0] == '\t' || st[0] == '\f' || st[0] == ')' || count >= 16)
                {
                    error(ERR_RAW_STRING_INVALID_CHAR);
                    err = TRUE;
                }
                else
                {
                    preamble[pcount++] = st[0];
                }
            }
            if (st[0] != '(')
                error(ERR_RAW_STRING_INVALID_CHAR);
            else while(TRUE)
            {
                if (*p)
                    st[0] = *p++;
                else if (getstring(st, 1, includes->handle))
                {
                    errorint(ERR_EOF_RAW_STRING, lineno);
                    *source = p;
                    return NULL;
                }
                else
                {
                    if (st[0] == '\n')
                    {
                        ++includes->line;
                        ++errorline;
                    }
                }
                if (len == 1)
                {
                    error(ERR_STRING_CONSTANT_TOO_LONG);
                }
                else
                {
                    *dest ++ = st[0];
                    len--;
                    count++;
                    if (st[0] == ')')
                    {
                        qcount = 0;
                        qpos = dest;
                    }
                    else if (qpos)
                    {
                        if (qcount == pcount)
                        {
                            if (st[0] == '"')
                            {
                                count -= 2 + pcount;
                                dest -= 2 + pcount;
                                break;
                            }
                        }
                        if (st[0] != preamble[qcount])
                            qpos = 0;
                        else
                            qcount++;
                    }
                }
            }
            *dest = 0;
            found = TRUE;
            while (isspace(*p))
                p++;
            *source = p;
        }
        else
        {
            while (*p && *p != '"')
            {
                int i ;
                i = getsch(v == l_Ustr || v == l_u8str ? 8 : v == l_wstr || v == l_ustr ? 4 : 2, &p);
                if (i == INT_MIN)
                {
                    if (!errored)
                    {
                        errored++;
                        error(ERR_INVALID_STRING_CONSTANT);
                    }
                }
                if (len == 1)
                    error(ERR_STRING_CONSTANT_TOO_LONG);
                else
                {
                    if (v == l_u8str && i > 0x7f)
                    {
                        if (i > 0x10ffff)
                            error(ERR_INVALID_CHAR_CONSTANT);
                        if (i < (1 << (6 + 5)))
                        {
                            *dest++ = 0xC0 + (i >> 6);
                            *dest++ = 0x80 + (i & 0x3f);
                            len-=2;
                            count+=2;
                        }
                        else if ( i < (1 << (6 + 6 + 4)))
                        {
                            *dest++ = 0xe0 + (i >> 12);
                            *dest++ = 0x80 + ((i >> 6) & 0x3f);
                            *dest++ = 0x80 + (i & 0x3f);
                            len-=3;
                            count+=3;
                        }
                        else
                        {
                            *dest++ = 0xf0 + ((i >> 18 & 0x7));
                            *dest++ = 0x80 + ((i >> 12) & 0x3f);
                            *dest++ = 0x80 + ((i >> 6) & 0x3f);
                            *dest++ = 0x80 + (i & 0x3f);
                            len-=4;
                            count+=4;
                        }
                    }
                    else
                    {
                        if (v == l_ustr && (i & 0xffff0000))
                            error(ERR_INVALID_CHAR_CONSTANT);
                        if (v == l_Ustr && i > 0x10ffff)
                            error(ERR_INVALID_CHAR_CONSTANT);
                        *dest++ = i;
                        len--;
                        count++;
                    }
                }
            }
            *dest = 0;
            if (*p != '"')
                error(ERR_UNTERM_STRING_CONSTANT);
            else
                p++;
            found = TRUE;
            while (isspace(*p))
                p++;
            *source = p;
        }
    }
    *tp = v;
    if (found)
    {
        SLCHAR *rv;
        int i;
        IncGlobalFlag();
        rv = Alloc(sizeof(SLCHAR));
        rv->str = (LCHAR *)Alloc(count * sizeof(LCHAR));
        for (i=0; i < count; i++)
        {
            rv->str[i] = data[i];
        }
        rv->count = count;
        DecGlobalFlag();
        return rv;
    }
    return NULL;
}
static int radix36(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return INT_MAX;
}
static LLONG_TYPE getbase(int b, char **ptr)
{
    LLONG_TYPE i;
    char *s = *ptr;
    int j;
    int errd = 0;
    i = 0;
    while ((j = radix36(**ptr)) < b)
    {
        (*ptr)++;
        if (i > (llminus1 - j) / b)
            if (!errd)
            {
                printf("%s\n", s);
                error(ERR_CONSTTOOLARGE);
                errd++;
            }
        i = i * b + j;
    }
    return i;
}

/*
 *      getfrac - get fraction part of a floating number.
 */
static void getfrac(int radix, char **ptr, FPF *rval)
{
    ULLONG_TYPE i = 0;
    int pow = 0, j, k = 0;
    FPF temp, temp1;
    while ((j = radix36(**ptr)) < radix)
    {
        i = radix * i + j;
        pow--;
        if (++k == (int)(sizeof(i) * CHAR_BIT * M_LN2 / M_LN10))
        {
            UnsignedLongLongToFPF(&temp, i);
            if (radix == 10)
                FPFMultiplyPowTen(&temp, pow);
            else
                temp.exp += 4 * pow;
            AddSubFPF(0,rval,&temp,&temp1);
            *rval = temp1;
            k = 0;
            i = 0;
        }
        (*ptr)++;
    }
    UnsignedLongLongToFPF(&temp, i);
    if (radix == 10)
        FPFMultiplyPowTen(&temp, pow);
    else
        temp.exp += 4 * pow;
    AddSubFPF(0,rval,&temp,&temp1);
    *rval = temp1;
}

/*
 *      getexp - get exponent part of floating number.
 */
static int getexp(char **ptr)
{
    BOOL neg = FALSE;
    int ival;
    if (**ptr == '-')
    {
        neg = TRUE;
        (*ptr)++;
    }
    else
    {
        if (**ptr == '+')
            (*ptr)++;
    }
    ival = getbase(10, ptr);
    if (neg)
        ival =  - ival;
    return ival;
}

/*
 *      getnum - get a number from input.
 *
 *      getnum handles all of the numeric input. it accepts
 *      decimal, octal, hexidecimal, and floating point numbers.
 */
int getNumber(char **ptr, char **end, char *suffix, FPF *rval, LLONG_TYPE *ival)
{
    char buf[200],  *p = buf ;
    int radix = 10;
    int floatradix = 0;
    BOOL hasdot = FALSE;
    BOOL floating = FALSE;
    enum e_lexType lastst ;
    if (!isdigit(**ptr) && **ptr != '.')
        return  INT_MIN;
    if (**ptr == '.' && !isdigit(*(*ptr + 1)))
        return INT_MIN;
    if (**ptr == '0')
    {
        (*ptr)++;
        if (**ptr == 'x' || **ptr == 'X')
        {
            (*ptr)++;
            radix = 16;
        }
        else
            radix = 8;
    }
    else if (cparams.prm_assemble && **ptr == '$')
    {
        radix = 16;
        (*ptr)++;
    }
    while (radix36(**ptr) < radix || cparams.prm_assemble && radix36(**ptr) < 16)
    {
        *p++ = **ptr;
        (*ptr)++;
    }
    if (**ptr == '.')
    {
        hasdot = TRUE;
        if (radix == 8)
            radix = 10;
        *p++ = **ptr;
        (*ptr)++;
        while (radix36(**ptr) < radix)
        {
            *p++ = **ptr;
            (*ptr)++;
        }
    }
    if ((**ptr == 'e' || **ptr == 'E') && radix != 16)
        radix = floatradix = 10;
    else if ((**ptr == 'p' || **ptr == 'P') && radix == 16)
    {
           floatradix = 2;
    } 
    else if (radix == 16 && hasdot)
    {
        error(ERR_INVFPCONST);
    }

    if (floatradix)
    {
        *p++ = **ptr;
        (*ptr)++;
        if (**ptr == '-' || **ptr == '+')
        {
            *p++ = **ptr;
            (*ptr)++;
        }
        while (radix36(**ptr) < 10)
        {
            *p++ = **ptr;
            (*ptr)++;
        }
    }

    *p = 0;
    if (!floatradix && radix != 16 && cparams.prm_assemble)
    {
        char *q = buf;
        while (*q && radix36(*q) < 10)
            q++ ;
        if (*q)
        {
            radix = 16;
            while (*q && radix36(*q) < 16)
                q++;
            if (*q)
            {
                return INT_MIN;
            }
            if (**ptr != 'H' && **ptr != 'h')
            {
                return INT_MIN;
            }
            (*ptr)++;
        }
    }
    p = buf;
    /* at this point the next char is any qualifier after the number*/

    if (radix36(*p) < radix)
        *ival = getbase(radix, &p);
    else
    {
           *ival = 0;
    }
    if (*p == '.')
    {
        p++;
        UnsignedLongLongToFPF(rval,*ival);
        getfrac(radix, &p, rval);
        floating = TRUE;
        *ival = 0;
    }
    if (*p == 'e' ||  *p == 'E' ||  *p == 'p' ||  *p == 'P')
    {
        if (!floating)
        {
            UnsignedLongLongToFPF(rval, *ival);
            floating = TRUE;
        }
        p++;
        *ival = getexp(&p);
    }
    *end = *ptr;
    *suffix = 0;
    if (isstartchar(**ptr))
    {
        char *ufd = suffix;
        while (issymchar(**ptr))
            *ufd++ = *(*ptr)++;
        *ufd = 0;
    }
    if (!floating)
    {
        lastst = l_i;
        if (!stricmp(suffix, "L"))
        {
            lastst = l_l;
            suffix[0] = 0;
        }
        else if (!stricmp(suffix, "U"))
        {
            lastst = l_ui;
            suffix[0] = 0;
        }
        else if (!stricmp(suffix, "UL") || !stricmp(suffix, "LU"))
        {
            lastst = l_ul;
            suffix[0] = 0;
        }
        else if ((cparams.prm_c99 || cparams.prm_cplusplus) && !stricmp(suffix, "LL") || !cparams.prm_ansi && !stricmp(suffix, "i64"))
        {
            lastst = l_ll;
            suffix[0] = 0;
        }
        else if ((cparams.prm_c99 || cparams.prm_cplusplus) && (!stricmp(suffix, "ULL") || !stricmp(suffix, "LLU")) || !cparams.prm_ansi && !stricmp(suffix, "ui64"))
        {
            lastst = l_ull;
            suffix[0] = 0;
        }
        else if (suffix[0])
        {
            if (!cparams.prm_cplusplus)
            {
                suffix[0] = 0;
                error(ERR_INVCONST);
            }
            else
            {
                lastst = l_ull;
            }
        }
        if (lastst == l_i) /* no qualifiers */
        {
            if (*ival > INT_MAX)
            {
                lastst = l_ui;
                if (radix == 10 || (ULLONG_TYPE)*ival > UINT_MAX)
                {
                    lastst = l_l;
                    if (*ival > LONG_MAX)
                    {
                        lastst = l_ul;
                        if (radix == 10 || (ULLONG_TYPE)*ival > ULONG_MAX)
                        {
                            if (radix == 10 || *ival > ULLONG_MAX)
                            {
                                lastst = l_ll;
                            }
                            else
                                lastst = l_ull;
                        }
                    }
                }
            }
        }
    }
    else
    {
        /* floating point too large goes to infinity... */
        if (floatradix == 2)
        {
           rval->exp += *ival;
        }
        else
        {
           FPFMultiplyPowTen(rval,*ival);
        }
        if (!stricmp(suffix, "F"))
        {
            lastst = l_f;
            CastToFloat(ISZ_FLOAT, rval);
            suffix[0] = 0;
        }
        else if (!stricmp(suffix, "L"))
        {
            lastst = l_ld;
            CastToFloat(ISZ_LDOUBLE, rval);
            suffix[0] = 0;
        } 
        else if (suffix[0])
        {
            if (!cparams.prm_cplusplus)
            {
                suffix[0] = 0;
                error(ERR_INVCONST);
            }
            lastst = l_ld;
            CastToFloat(ISZ_LDOUBLE, rval);
        }
        else
        {
            lastst = l_d;
            CastToFloat(ISZ_DOUBLE, rval);
        }
    }
    return lastst;
}
int getId(char **ptr , char *dest)
{
    if (!isstartchar(**ptr))
        return INT_MIN;
    while (issymchar(**ptr) || **ptr == '\\')
    {
        if (**ptr == '\\')
        {
            ULLONG_TYPE n=0;
            int i;
            if ((*ptr)[1] == 'u')
            {
                for (i=0; i < 4; i++)
                {
                    int c = (*ptr)[i+2];
                    if (!isxdigit(c))
                        break;
                    else
                    {
                        c -= '0';
                        if (c >= 10)
                            c -= 7;
                        n = n * 16 + c;
                    }
                }
                if (i < 4)
                    break;
                        
            }
            else if ((*ptr)[1] == 'U')
            {
                for (i=0; i < 8; i++)
                {
                    int c = (*ptr)[i+2];
                    if (!isxdigit(c))
                        break;
                    else
                    {
                        c -= '0';
                        if (c >= 10)
                            c -= 7;
                        n = n * 16 + c;
                    }
                }
                if (i < 8)
                    break;
            }
            else
                break;
            if (n <= 0x20 || n >= 0x7f && n <= 0x9f ||
                n >=0xd800 && n<= 0xdfff)
                pperror(ERR_INVCONST, 0);
        }
        *dest++ = *(*ptr)++;
    }
    *dest = 0;
    return 0;
}
LEXEME *SkipToNextLine(void)
{
    head = tail = index = 0;
    while (*includes->lptr)
        includes->lptr++;
    return getsym();
}
LEXEME *getsym(void)
{
    LEXEME *lex;
    KEYWORD *kw ;
    enum e_lexType tp;
    BOOL contin ;
    FPF rval;
    LLONG_TYPE ival;
    static char buf[2048];
    static int pos = 0;
    int cval;
    LCHAR *strptr;

    if (index != head)
    {
        lex =  &llex[index];
        top = index = (index+1)%MAX_LOOKBACK;
        return lex;
    }
    lex = &llex[head];	
    if (head == (tail + MAX_LOOKBACK - 1) % MAX_LOOKBACK)
    {
        tail = (tail+1) %MAX_LOOKBACK;
    }
    top = index = head = (head+1) %MAX_LOOKBACK;
    if (usingAlternateLex)
    {
        if (!alternateLex)
            return NULL;
        *lex = *alternateLex;
        alternateLex = alternateLex->next;
        return lex;
    }
    do
    {
        contin = FALSE;
        do
        {
            if (!includes)
                return NULL;
            if (!includes->lptr || !*includes->lptr)
                if (getline())
                {
                    return NULL;
                }
            while (isspace(*includes->lptr))
                includes->lptr++;
        } while (*includes->lptr == 0);
        lex->charindex = includes->lptr - includes->inputline;
        lex->line = endline = errorline;
        lex->file = errorfile;
        if ((cval = getChar(&includes->lptr, &tp)) != INT_MIN)
        {
               if (tp == l_achr && !cparams.prm_charisunsigned && !(cval & 0xffffff00))
                cval = (int)(char)cval;
            if (tp == l_uchr && (cval & 0xffff0000))
                error(ERR_INVALID_CHAR_CONSTANT);
            lex->value.i = cval;
            if (!cparams.prm_cplusplus)
                lex->type = l_i;
            else
                lex->type = tp;
            if (isstartchar(*includes->lptr))
            {
                char suffix[256], *p = suffix;
                while (issymchar(*includes->lptr))
                    *p++ = *includes->lptr++;
                *p = 0;
                if (!cparams.prm_cplusplus)
                    error(ERR_INVCONST);
                else
                    lex->suffix = litlate(suffix);
            }
        }
        else if ((strptr = getString(&includes->lptr, &tp)) != NULL)
        {
            lex->value.s.w = strptr;
            lex->type = tp == l_u8str ? l_astr : tp;
            if (isstartchar(*includes->lptr) && !isspace(*(includes->lptr-1)))
            {
                char suffix[256], *p = suffix;
                while (issymchar(*includes->lptr))
                    *p++ = *includes->lptr++;
                *p = 0;
                if (!cparams.prm_cplusplus)
                    error(ERR_INVCONST);
                else
                    lex->suffix = litlate(suffix);
            }
        }
        else if (*includes->lptr != 0)
        {
            char suffix[256];
            char *start = includes->lptr;
            char *end = &includes->lptr;
            if ((cval = getNumber(&includes->lptr, &end, suffix, &rval, &ival)) != INT_MIN)
            {
                if (cval < l_f)
                    lex->value.i = ival;
                else
                    lex->value.f = rval;
                if (suffix[0])
                {
                    lex->suffix = litlate(suffix);
                    memcpy(suffix, start, end - start);
                    suffix[end - start] = 0;
                    lex->litaslit = litlate(suffix);
                }
                lex->type = cval;
            }
            else if ((kw= searchkw(&includes->lptr)) != NULL)
            {
                lex->type = l_kw;
                lex->kw = kw;
            }
            else if (getId(&includes->lptr, buf + pos) != INT_MIN)
            {
                lex->value.s.a = buf+pos;
                lex->type = l_id;
                pos += strlen(buf+pos)+ 1;
                if (pos >= sizeof(buf) - 512)
                    pos = 0;
            }
            else
            {
                contin = TRUE;
                errorint(ERR_UNKNOWN_CHAR, *includes->lptr++);
            }
        }
        else
        {
            contin = TRUE;
        }
    } while (contin);
    return lex;
}
void marksym(void)
{
    mark = (top + MAX_LOOKBACK-1)%MAX_LOOKBACK;
}
LEXEME *backupsym(int rel)
{
    if (rel == 0)
        index = mark;
    else
        index = (index + MAX_LOOKBACK - rel -1) %MAX_LOOKBACK;
    return getsym();
}
LEXEME *SetAlternateLex(LEXEME *lex, LEXEME *lexList)
{
    static LEXEME lastLex;
    alternateLex = lexList;
    usingAlternateLex = lexList != NULL;
    if (usingAlternateLex)
    {
        lastLex = *lex;
        if (lastLex.type == l_id)
            lastLex.value.s.a = litlate(lastLex.value.s.a);
        top = index = mark = head;
        return getsym();
    }
    else
    {
        top = index = mark = head = 1;
        llex[0] = lastLex;
        return &llex[0];
    }
}