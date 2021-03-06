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
/*      compiler header file    */


#define CI_CONSTRUCTOR 0
#define CI_DESTRUCTOR 1
#define CI_NEW 2
#define CI_DELETE 3
#define CI_NEWA (compl+1+2)
#define CI_DELETEA (compl+2+2)
#define CI_LIT (compl + 3+2)

#define issymchar(x) (((x) >= 0) && (isalnum(x) || (x) == '_'))
#define isstartchar(x) (((x) >= 0) && (isalpha(x) || (x) == '_'))

#define STD_PRAGMA_FENV 1
#define STD_PRAGMA_FCONTRACT 2
#define STD_PRAGMA_CXLIMITED 4

#define MACRO_REPLACE_SIZE 32768

typedef struct
{
    LCHAR *str;
    int count;
} SLCHAR;
/* keywords and symbols */
enum e_kw
{
    /* first comes all the C++ overloadable operators */
    /* be sure to change expectlist if you insert things */
    kw_new, kw_delete, plus, minus, star, divide, leftshift, rightshift, mod, eq,
        neq, lt, leq, gt, geq, assign, asplus, asminus, astimes, asdivide,
        asmod, asleftshift, asrightshift, asand, asor, asxor, autoinc, autodec,
        openbr, openpa, pointstar, pointsto, comma, lor, land, not, or, and, uparrow,
        compl, kw_newa, kw_dela, quot,
        
    /* then generic stuff that isn't overloadable or is internal */
    id, hook, colon, begin, end, dot,
        closebr, closepa, ellipse, semicolon, hash, classsel,
        dotstar, lassign, 
    /* Finally tokens for keywords */
    kw_int, kw_void, kw_char, kw_float, kw_double, kw_struct, kw_union, kw_long,
        kw_short, kw_unsigned, kw_signed, kw_auto, kw_extern, kw_register,
        kw_typedef, kw_static, kw_goto, kw_return, kw_sizeof, kw_break,
        kw_continue, kw_if, kw_else, kw_for, kw_do, kw_while, kw_switch,
        kw_case, kw_default, kw_enum, kw_volatile, kw_const,
        kw__trap, kw__interrupt, kw__fault, kw__absolute, kw__genword,
        kw__Complex, kw_restrict, kw__Imaginary, kw___I, kw__INF, kw__NAN, 
        kw_typeof, kw__Pragma, kw_atomic, kw_noreturn, kw_generic,
    /* C++ */
    kw_public, kw_private, kw_protected, kw_class, kw_friend, kw_namespace,
        kw_using, kw_this, kw_operator, kw_inline, kw_virtual, kw_try, kw_throw,
        kw_catch, kw_template, kw_bool, kw_true, kw_false, kw_wchar_t,
        kw_static_cast, kw_dynamic_cast, kw_reinterpret_cast, kw_const_cast,
        kw_typeid, kw_typename, kw_explicit, kw_decltype,
        kw_export, kw_static_assert, kw_alignas, kw_alignof, kw_char16_t,
        kw_char32_t, kw_mutable, kw_nullptr, kw_noexcept, kw_thread_local, kw_constexpr,
        kw_final, kw_override,
    /* Extended */
    kw_atomic_flag_test_set, kw_atomic_flag_clear, kw_atomic_fence, kw_atomic_kill_dependency,
        kw_atomic_load, kw_atomic_store, kw_atomic_modify, kw_atomic_cmpswp, kw_atomic_var_init,
        kw__pascal, kw__stdcall, kw__cdecl, kw__intrinsic, kw_asm, kw__loadds,
        kw__far, kw_asmreg, kw_asminst, kw__indirect, kw__export, kw__import, kw___func__,
        kw__near, kw__seg, kw___typeid, kw___int64, kw_alloca,
    /* These next are generic register names */
    kw_D0, kw_D1, kw_D2, kw_D3, kw_D4, kw_D5, kw_D6, kw_D7, kw_D8, kw_D9, kw_DA,
        kw_DB, kw_DC, kw_DD, kw_DE, kw_DF, kw_A0, kw_A1, kw_A2, kw_A3, kw_A4,
        kw_A5, kw_A6, kw_A7, kw_A8, kw_A9, kw_AA, kw_AB, kw_AC, kw_AD, kw_AE,
        kw_AF, kw_F0, kw_F1, kw_F2, kw_F3, kw_F4, kw_F5, kw_F6, kw_F7, kw_F8,
        kw_F9, kw_FA, kw_FB, kw_FC, kw_FD, kw_FE, kw_FF, kw_cr0, kw_cr1, kw_cr2,
        kw_cr3, kw_cr4, kw_cr5, kw_cr6, kw_cr7, kw_dr0, kw_dr1, kw_dr2, kw_dr3,
        kw_dr4, kw_dr5, kw_dr6, kw_dr7, kw_tr0, kw_tr1, kw_tr2, kw_tr3, kw_tr4,
        kw_tr5, kw_tr6, kw_tr7, eol, eof, kw_none
};

enum ovcl 
{
    ovcl_unary_numeric, ovcl_unary_numericptr, ovcl_unary_int,
    ovcl_unary_prefix, ovcl_unary_postfix, 
    ovcl_unary_pointer, ovcl_unary_any, ovcl_binary_any,
    ovcl_binary_numericptr, ovcl_binary_numeric, ovcl_binary_int, 
    ovcl_assign_any, ovcl_assign_numericptr, ovcl_assign_numeric, ovcl_assign_int,
    ovcl_pointsto, ovcl_openbr, ovcl_openpa, ovcl_comma
};
typedef struct
{ 
    FPF r;
    FPF i;
} _COMPLEX_S;

enum e_node
{

    en_void, en_not_lvalue, en_argnopush, en_voidnz, en_shiftby, 
    en_global, en_auto, en_labcon, en_absolute, en_pc, en_label, en_const, en_threadlocal,
    en_c_bit, en_c_bool, en_c_c, en_c_uc, en_c_wc, en_c_s, en_c_u16, en_c_us, en_c_i, en_c_ui, 
    en_c_u32, en_c_l, en_c_ul, en_c_ll, en_c_ull, en_c_f, en_c_d, en_c_ld,
        en_c_p, en_c_sp, en_c_fp, en_c_fc, en_c_dc, en_c_ldc,
        en_c_fi, en_c_di, en_c_ldi, en_x_bool, en_x_bit, en_x_i, en_x_ui, en_x_l, en_x_ul,
        en_x_ll, en_x_ull, en_x_f, en_x_d, en_x_ld, en_x_fi, en_x_di, en_x_ldi, en_x_fp, en_x_sp,
        en_x_fc, en_x_dc, en_x_ldc,en_x_c, en_x_uc, en_x_wc, en_x_u16, en_x_u32, en_x_s, en_x_us, en_x_label, 
        en_l_bool, en_l_c, en_l_uc, en_l_u16, en_l_u32, en_l_wc, en_l_s, en_l_us, en_l_i, en_l_ui,
        en_l_l, en_l_ul, en_l_ll, en_l_ull, en_l_f, en_l_d, en_l_ld,  en_l_p, en_l_ref,
        en_l_fi, en_l_di, en_l_ldi, en_l_fc, en_l_dc, en_l_ldc, en_l_fp, en_l_sp, en_l_bit,
        en_nullptr, en_memberptr, en_mp_as_bool, en_mp_compare,
        en_trapcall, en_func, en_intcall, en_tempref, 
        en_arraymul, en_arraylsh, en_arraydiv, en_arrayadd, en_structadd,
        en_add, en_sub, en_mul, en_mod, en_div, en_lsh, en_rsh, en_ursh,
        en_cond, en_assign, en_eq, en_ne, 
        en_uminus, en_not, en_compl, en_ascompl, en_lt, en_le, en_gt, en_ge,
        en_and, en_or, en_land, en_lor, en_xor, en_umul, en_autoinc, en_autodec,
        en_udiv, en_umod, en_ugt, en_uge, en_ule, en_ult, en_blockclear, en_stackblock, 
        en_blockassign, en_rshd, en_bits,
        en_this, en_imode, en_x_p, en_substack, en_alloca,
        en_loadstack, en_savestack, en_stmt, en_atomic, en_placeholder
};
/*      statement node descriptions     */

enum e_stmt
{
    st_line, st_expr, st_declare, st_goto, st_asmgoto, st_asmcond, 
    st_loopgoto, st_select, st_notselect, st_varstart, st_dbgblock,
    st_switch, st_return, st_block, st__genword, st_passthrough, 
    st_datapassthrough, st_abs, st_throw, st_tryblock, st_label
};

/* storage classes */
enum e_sc
{
        sc_static, sc_localstatic, sc_auto, sc_register, sc_global, sc_external, 
        sc_parameter, sc_type, sc_typedef, sc_member, sc_cast, sc_defunc, sc_label, sc_ulabel,
        sc_overloads, sc_constant, sc_enumconstant, sc_absolute,
        sc_friendlist, sc_const, sc_tconst, sc_classmember, sc_constexpr,
           sc_memberreg, sc_namespace, sc_namespacealias, sc_temp, sc_virtual
};

/* basic types */
enum e_bt
{
    /* keep this ordering and dont insert anything before the end of the
     * basic types, type comparisons (LOSTCONV) depends on the ordering,
     * and the debug info has a table indexed by type
     */
    bt_bit, bt_bool, bt_char, bt_unsigned_char, bt_short, bt_char16_t, bt_unsigned_short, 
    bt_wchar_t, bt_enum, bt_int, bt_char32_t, bt_unsigned, bt_long, bt_unsigned_long, bt_long_long,
        bt_unsigned_long_long, bt_float, bt_double, bt_long_double, bt_float_imaginary,
        bt_double_imaginary, bt_long_double_imaginary, bt_float_complex, 
        bt_double_complex, bt_long_double_complex,
    /* end of basic types */
    bt_void, 
    /* end of debug needs */
    bt_signed, bt_static, bt_atomic, bt_const, bt_volatile, bt_restrict, bt_far, bt_near, bt_seg,
    bt_aggregate, bt_untyped, bt_typedef, bt_pointer, bt_lref, bt_rref, bt_struct,
        bt_union, bt_func, bt_class, bt_ifunc, bt_any, bt_auto,
        bt_match_none, bt_ellipse, bt_memberptr, bt_cond,
        bt_consplaceholder, bt_templateplaceholder, bt_string,
        /* last */
        bt_none
};
enum e_lk { lk_none, lk_cdecl, lk_pascal, lk_stdcall, lk_c, lk_cpp,
    lk_interrupt, lk_fault, lk_inline, lk_noreturn, lk_threadlocal, 
    lk_import, lk_export, lk_auto };
    
enum e_ac { ac_private, ac_protected, ac_public, ac_none };
typedef struct expr
{
    struct expr *left, *right;
    enum e_node type;
    int pragmas;
    long size; /* For block moves */
    union
    {
        LLONG_TYPE i;
        FPF f;
        _COMPLEX_S c;
        struct sym *sp; /* sym will be defined later */
        char *name; /* name during base class processing */
        struct functioncall *func;
        struct _atomicData *ad;
        struct stmt *stmt;
        struct _imode_ *imode;
    } v;
    int lockOffset;
    char bits;
    char startbit;
    int isvolatile:1;
    int isrestrict:1;
    int isatomic:1;
    int atomicinit:1;
    int unionoffset:1;
    int isfunc:1;
} EXPRESSION;

typedef struct casedata
{
    struct casedata *next;
    LLONG_TYPE val;
    int label;
    char *file;
    int line;
} CASEDATA;

union u_val    {
        LLONG_TYPE i; /* int val */
        ULLONG_TYPE u; /* nsigned val */
        FPF f; /* float val */
        _COMPLEX_S c;
        union
        {
            char *a; /* string val */
            LCHAR *w;
        } s;
        struct _defstruct *defs ; /* macro definition */
    } ;
typedef    struct type
    {
        enum e_bt type; /* the type */
        long size; /* total size of type */
        struct type *btp; /* pointer to next type (pointers & arrays */
        int used:1; /* type has actually been used in a declaration or cast or expression */
        int array:1; /* not a dereferenceable pointer */
        int vla:1;   /* varriable length array */
        int unsized:1; /* type doesn't need a size */
        int hasbits:1; /* type is a bit type */
        int anonymousbits:1; /* type is a bit type without a name */
        int scoped:1; /* c++ scoped enumeration */
        int fixed:1; /* c++ fixed enumeration */
        char bits; /* -1 for not a bit val, else bit field len */
        char startbit; /* start of bit field */
        struct sym *sp; /* pointer to a symbol which describes the type */
        /* local symbol tables */
        HASHTABLE *syms; /* Symbol table for structs & functions */
        HASHTABLE *tags; /* Symbol table for nested types*/
        int dbgindex; /* type index for debugger */
        int alignment; /* alignment pref for this structure/class/union   */
        EXPRESSION *esize; /* enode version of size */
        int vlaindex; /* index into the vararray */
    } TYPE;
typedef struct _linedata
{
    struct _linedata *next;
    char *line;
    char *file;
    int lineno;
    int fileindex;
} LINEDATA;

typedef struct stmt
{
    struct stmt *next;
    struct stmt *lower;
    struct stmt *blockTail;
    enum e_stmt type;
    EXPRESSION *select;
    LINEDATA *lineData;
    TYPE *returntype;
    struct sym *sym;
    CASEDATA *cases;
    int blocknum;
    int charpos;
    int line;
    char *file;
    int label;
    int breaklabel;
    int altlabel;
    int hasvla: 1;
    int purelabel: 1;
} STATEMENT;

typedef struct blockdata
{
    struct blockdata *next;
    enum e_stmt type;
    CASEDATA *cases;
    STATEMENT *head, *tail;
    STATEMENT *blockTail;
    int breaklabel;
    int continuelabel;
    int defaultlabel;
    int needlabel:1;
    int hasbreak:1;
    int hassemi:1;
    int nosemi:1; /* ok to skip semi */
    int lastcaseordefault:1;
} BLOCKDATA;

typedef struct init
{
    struct init *next;
    int offset;
    TYPE *basetp;
    EXPRESSION *exp;
    int tag; /* sequence number */
    
} INITIALIZER;
    
typedef struct ifunc
{
    STATEMENT *stmt;
    HASHTABLE *syms;
    HASHTABLE *tags;
} INLINEFUNC;

typedef struct __nsv
{
    struct __nsv *next;
    HASHTABLE *syms;
    HASHTABLE *tags;
    LIST *childNameSpaces;
    LIST *usingDirectives;    
    LIST *inlineDirectives;    
    struct sym *origname;
    struct sym *name;
} NAMESPACEVALUES;
/* symbols */
typedef struct sym
{
    char *name;
    char *decoratedName; /* symbol name with decorations, as used in output format */
    char *errname; /* name to be used in errors */
    char *declfile ; /* file symbol was declared in */
    int  declline ; /* line number symbol was declared at */
    int declcharpos ; /* character position symbol was declared at */
    int declfilenum; /* the file number */
    int paramSize;
    int sizeNoVirtual; /* size without virtual classes and thunks */
    struct sym *parent;
    struct sym *parentClass;
    struct sym *parentNameSpace;
    struct sym *vtabsp;
    NAMESPACEVALUES *nameSpaceValues;
    LINEDATA *linedata;
    enum e_sc storage_class; /* storage class */
    enum e_lk linkage; /* cdecl, pascal, stdcall, inline */
    enum e_lk linkage2; /* export, import */
    enum e_lk linkage3; /* noreturn */
    enum e_ac access; /* c++ access rights for members */
    int operatorId; /* operator id, CI + kw for an operator function */
    struct _imode_ *imaddress;
    struct _imode_ *imvalue;
    struct _im_list *imind;
    struct _imode_ *imstore;
    INLINEFUNC inlineFunc;
#ifdef PARSER_ONLY
    int      ccEndLine;      /* end line for code completion */
    ULLONG_TYPE   ccStructId;     /* code completion struct id */
#endif
    unsigned declaring: 1; /* currently being declared */
    unsigned hasproto: 1; /* C/90 language prototype was encountered */
    unsigned intagtable: 1; /* it is in a tag table */
    unsigned dontlist: 1; /* it is a system include, don't put in list file */
    unsigned allocate: 1; /* variable is used, allocate space for it */
    unsigned indecltable: 1; /* global already in dump table */
    unsigned spaceallocated: 1; /* space has been allocated */
    unsigned regmode: 2; /* 0 = pure var, 1 = addr in reg, 2 = value in reg*/
    unsigned loadds: 1; /* to load data seg (limited) */
    unsigned farproc: 1; /* this procedure should be terminated with retf */
    unsigned indirect: 1; /* This procedure is to be called indirectly. */
    unsigned calleenearret: 1; /* true if callee provided a place for the return
        value */
    unsigned hasunnamed: 1; /* structure has unnamed substructs */
    unsigned isunnamed: 1; /* substructure is unnamed */
    unsigned recalculateParameters: 1; /* inline func needs its parameters
        recalculated */
    unsigned nullsym: 1; /* if was a callblock return which isn't used */
        unsigned iglobal: 1; /* if a temp variable has gone global */
        unsigned pushedtotemp: 1; /* if a local variable has been transformed to a temp */
        unsigned anonymous: 1; /* if it is a generated variable */
        unsigned usedasbit: 1; /* used in a bit field op */
        unsigned inasm: 1; /* a way to force the local optimizer to leave autos on the stack */
        unsigned assigned: 1; /* value has been assigned */
        unsigned altered: 1;
        unsigned used: 1; /* value has been fetched */
        unsigned genreffed: 1; /* reffed in codegen */
        unsigned allocaUsed: 1;
        unsigned oldstyle : 1; /* pointer to a names list if an old style function arg */
        unsigned spillVar : 1; /* backend allocator spill variable */
        unsigned noGlobal : 1; /* no global opts on this temp var */
        unsigned storeTemp : 1; /* is a storetemp */
        unsigned loadTemp : 1; /* is a loadtemp */
        unsigned visited : 1; /* temproary which means it is visited */
        unsigned constexpression : 1; /* declared with constexpression */
        unsigned addressTaken : 1; /* address taken */
        unsigned wasUsing : 1; /* came to this symbol table as a result of 'using' */
        unsigned redeclared : 1; /* symbol was declared more than once */
        unsigned deleted : 1; /* function was deleted */
        unsigned isfinal :1 ; /* class or virtual function is final */
        unsigned isoverride : 1; /* virtual function marked override */
        unsigned ispure : 1; /* pure virtual function */
        unsigned hasvtab : 1; /* class has a vtab */
        unsigned hascons : 1; /* class has a user-defined constructor */
        unsigned isabstract:1; /* class is abstract */
        unsigned accessspecified : 1; /* class has access specifiers */
        unsigned safefunc : 1; /* RTL helper function with no side effects */
        unsigned throughClass : 1; /* last search was found through a class */
        int __func__label; /* label number for the __func__ keyword */
        int ipointerindx; /* pointer index for pointer opts */
    int nextid; /* ID to use for nextage purposes (binary output) */
    int offset; /* address offset of data in the given seg, or optimize register */
    int label; /* label number for statics */
    int paramsize; /* Size of parameter list for stdcall functions */
    int retcount; /* number of return statements in a function */
    int structAlign; /* alignment of structures/ unions */
    /* Also name for CPP overload lists */
    /* also default for template parameters, is a TYP */
    char *importfile; /* import name */
    struct sym *mainsym; /* pointer to the global version of a copied symbol */
    /* these fields depend on storage_class */
    union u_val value;
    struct _baseClass *baseClasses;
    struct _vbaseEntry *vbaseEntries;
    struct _vtabEntry *vtabEntries;
    struct lexeme *deferredCompile ;
    struct init * init;
    LIST *friends;
    /* Type declarations */
    struct type *tp;
} SYMBOL;

typedef struct _baseClass
{
    struct _baseClass *next;
    SYMBOL *cls;
    enum e_ac accessLevel;
    BOOL isvirtual;
    unsigned offset;
} BASECLASS;
typedef struct _virtualFunc
{
    struct _virtualFunc *next;
    SYMBOL *func;
} VIRTUALFUNC;
typedef struct _vtabEntry
{
    struct _vtabEntry *next;
    struct _vtabEntry *children;
    struct _virtualFunc *virtuals;
    SYMBOL *cls;
    unsigned dataOffset;
    unsigned vtabOffset;
    BOOL isvirtual;
    BOOL isdead;
} VTABENTRY;
typedef struct _vbaseEntry
{
    struct _vbaseEntry *next;
    SYMBOL *cls;
    BOOL alloc;
    unsigned pointerOffset;
    unsigned structOffset;
} VBASEENTRY;
typedef struct arglist
{
    struct arglist *next;
    TYPE *tp;
    EXPRESSION *exp;
    EXPRESSION *rootexp;
} ARGLIST;

typedef struct functioncall
{
    SYMBOL *sp;
    TYPE *functp;
    EXPRESSION *fcall;
    ARGLIST *arguments;
    SYMBOL *returnSP;
    EXPRESSION *returnEXP;
    EXPRESSION *thisptr;
    TYPE *thistp;
    int novtab : 1;
    int ascall:1;
} FUNCTIONCALL;

#define MAX_STRLEN      16384
#define MAX_STLP1       (MAX_STRLEN + 1)

/* error list */
struct errl
{
    struct errl *next;
    int errornumber;
    void *data;
};

/* used for error skimming */
#define BALANCE struct balance
#define BAL_PAREN   0
#define BAL_BRACKET 1
#define BAL_BEGIN 2
#define ERRORS struct errl

struct balance
{
    struct balance *back;
    short type;
    short count;
};

typedef struct kwblk
{
    char *name;
    int len;
    enum e_kw key;
    enum
    {
        KW_NONE = 0, KW_CPLUSPLUS = 1, KW_INLINEASM = 2, KW_NONANSI = 4, KW_C99 = 8, 
        KW_C1X = 16, KW_ASSEMBLER = 32,
        KW_386 = 128, KW_68K= 256, KW_ALL = 0x40000000
    } matchFlags;
    enum 
    {
        TT_BASE = 1, TT_BOOL=2, TT_INT = 4, TT_FLOAT= 8, TT_COMPLEX = 16, 
        TT_TYPEQUAL = 32, TT_POINTERQUAL = 64, TT_UNARY = 128, TT_BINARY = 0x100,
        TT_OPERATOR = 0x200, TT_ASSIGN = 0x400, TT_RELATION = 0x800, TT_EQUALITY = 0x1000,
        TT_INEQUALITY = 0x2000, TT_POINTER = 0x4000, TT_STORAGE_CLASS = 0x8000,
        TT_CONTROL = 0x10000, TT_BLOCK = 0x20000, TT_PRIMARY = 0x40000, TT_SELECTOR = 0x80000,
        TT_VAR = 0x100000, TT_BASETYPE = 0x200000, TT_INCREMENT = 0x400000,
        TT_SWITCH = 0x800000, TT_ENUM = 0x1000000, TT_STRUCT = 0x2000000, 
        TT_TYPENAME=0x4000000, TT_TYPEDEF = 0x8000000, TT_VOID = 0x10000000, TT_CLASS = 0x20000000,
        TT_LINKAGE = 0x40000000,TT_DECLARE = 0x80000000, TT_UNKNOWN = 0
    } tokenTypes;
/*    ASMNAME *data; */
}KEYWORD;


#define MATCHTYPE(lex, tp) (lex && (lex)->type == (tp))
#define ISID(lex) (lex && (lex)->type == l_id)
#define ISKW(lex) (lex && (lex)->type == l_kw)
#define MATCHKW(lex, keyWord) (ISKW(lex) && ((lex)->kw->key == keyWord))
#define KWTYPE(lex, types) (ISKW(lex) && (((lex)->kw->key == kw_auto ? (cparams.prm_cplusplus ? TT_BASETYPE : TT_STORAGE_CLASS ) :(lex)->kw->tokenTypes) & (types)))
#define KW(lex) (ISKW(lex) ? (lex)->kw->key : kw_none)

typedef struct lexeme
{
    struct lexeme *next;
    enum e_lexType { l_none, l_i, l_ui, l_l, l_ul, l_ll, l_ull, l_f, l_d, l_ld, l_I, 
            l_id, l_kw, 
            l_astr, l_wstr,  l_ustr, l_Ustr, l_u8str, 
            l_achr, l_wchr, l_uchr, l_Uchr, 
            l_qualifiedname, l_asminst, l_asmreg
         } type;
    union u_val value;
    char *litaslit;
    char *suffix;
    char *file;
    int line;
    int charindex;
    KEYWORD *kw;
    SYMBOL *typequal;
} LEXEME;

typedef struct _string
{
    struct _string *next;
    enum e_lexType strtype;
    int size;
    int label;
    char *suffix;
    SLCHAR **pointers;
} STRING;
#define INCL_LEVEL_MAX 16

#define MAX_INLINE_NESTING 100

#define OPT_RESHAPE 1
#define OPT_LSTRENGTH 2
#define OPT_GLOBAL 4
#define OPT_CONSTANT 8
#define OPT_INVARIANT 16

// must match stdatomic.h
enum e_mo {
    mo_relaxed=1,
    mo_acquire,
    mo_release,
    mo_acq_rel,
    mo_seq_cst   
} ;

enum e_ao {
    ao_init,
    ao_flag_set_test,
    ao_flag_clear,
    ao_fence,
    ao_load,
    ao_store,
    ao_modify,
    ao_cmpswp
} ;
typedef struct _atomicData
{
    enum e_ao atomicOp;
    EXPRESSION *memoryOrder1;
    EXPRESSION *memoryOrder2;
    EXPRESSION *flg;
    EXPRESSION *address;
    EXPRESSION *value;
    EXPRESSION *third;
    TYPE *tp;
} ATOMICDATA;

#define ATOMIC_FLAG_SPACE getSize(bt_int)
