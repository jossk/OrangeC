/*
	Software License Agreement (BSD License)
	
	Copyright (c) 1997-2012, David Lindauer, (LADSoft).
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


#include "winconst.h"
#include "lsctrl.h"
#include "progress.h"

#define BROWSE_VERSION 2

#pragma pack(1)

#ifdef BORLANDC
    #define LLONG_TYPE __int64
#else 
    #define LLONG_TYPE long long
#endif 
#define MAX_COMBO_HISTORY 10

#define HBREAK 

#define CONTROL_FONT "Bitstream Vera Sans Mono"
#define CONTROL_FONT_BASIC_SIZE 14

#define DID_TABWND 1
#define DID_WATCHWND 2
#define DID_ERRORWND 3
#define DID_ASMWND 4
#define DID_MEMWND 5
#define DID_STACKWND 6
#define DID_THREADWND 7
#define DID_BPWND 8
#define DID_REGWND 9
#define DID_PROPSWND 10

#define DID_EDITTOOL 20
#define DID_BUILDTOOL 21
#define DID_DEBUGTOOL 22
#define DID_NAVTOOL 23
#define DID_BOOKMARKTOOL 24
#define DID_THREADSTOOL 25

#define IML_BP 0
#define IML_CONTINUATION 1
#define IML_STOPBP 2
#define IML_BPGRAYED 3
#define IML_STOP 4
#define IML_BOOKMARK 5
#define IML_FIF1 6
#define IML_FIF2 7
#define IML_BLANK 8
#define ILEDIT_IMAGECOUNT 9

#define TAG_BP 0
#define TAG_FIF1 1
#define TAG_FIF2 2
#define TAG_BOOKMARK 3
#define TAG_BPGRAYED 4 /* no tags gathered here, this is just a return value */
#define TAG_MAX 5

#define TAGM_SAVEFILE 0
#define TAGM_DISCARDFILE 1
#define TAGM_UPDATEDEBUG 2

#define TAGF_ENABLED 1
#define TAGF_GRAYED 2

#define HELP_MSDN 0
#define HELP_SDK 1
#define HELP_SPECIFIED 2

#define ERR_NO_WINDOW -1
#define ERR_BUILD_WINDOW 0
#define ERR_DEBUG_WINDOW 1
#define ERR_FIND1_WINDOW 2
#define ERR_FIND2_WINDOW 3

#define LANGUAGE_NONE 0
#define LANGUAGE_C 1
#define LANGUAGE_ASM 2
#define LANGUAGE_RC 3

#define EDITSIG 0xf1823794
#define RESSIG 0x1F8237A5

#define IL_CWA 0
#define IL_CONSOLE 1
#define IL_GUI 2
#define IL_LIB 3
#define IL_DLL 4
#define IL_FILES 5
#define IL_ASM 6
#define IL_CPP 7
#define IL_C 8
#define IL_H 9
#define IL_RES 10
#define IL_RC 11
#define IL_IMAGECOUNT 12



#define DEFINE_TONASM 1

#define BF_DEBUGINFO  1
#define BF_MAPFILE    2
#define BF_COMPILEVIAASM 4
#define BF_CRTDLL 8 /* obsolete */
#define BF_BROWSEINFO 16
#define BF_SHOWWARNINGS 32
#define BF_C99 64
#define BF_ANSI 128
#define BF_SHOWRETURNCODE 0x10000
#define BF_BREAKDLL 0x20000
#define BF_DEBUGEXCEPTION 0x40000
#define BF_DEBUGTOOLTIPS 0x80000
#define BF_HWBP 0x100000
#define BF_CHANGEDTARGET 0x40000000
#define BF_ALIGNSTACK    0x80000000

#define TFO_MAIN 1
#define TFO_SOURCE 2
#define TFO_INCLUDE 4
#define TFO_RESOURCE 8
#define TFO_OTHER 16

    enum
    {
        BT_CONSOLE, BT_WINDOWS, BT_DLL, BT_LIBRARY, BT_DOS, BT_RAW
    } ;
    enum
    {
        LT_STANDARD, LT_LSCRTDLL, LT_NONE, LT_CRTDLL, LT_MSVCRT
    } ;
typedef struct _settingCombo
{
	struct _settingCombo *next;
	char *displayName;
	char *value;
} SETTINGCOMBO;

typedef struct _setting
{
	struct _setting *next;
	struct _setting *children;
    struct _setting *command;
    struct _setting *assignments;
    struct _setting *depends;
	enum slType { e_separator, e_tree, e_assign, e_assignments, e_values = 100, e_choose, e_combo, e_text, e_numeric, e_color, e_font, e_printformat, e_prependtext, e_separatedtext, e_multitext } type;
	HTREEITEM hTreeItem;
	HWND hWnd;
	char *displayName;
	char *select;
	char *cls;
	char *id;
	char *deflt;
	char *value;
	char *tentative;
    char *aux;
	struct _settingCombo *combo;
	char * lowLimit, *highLimit;
    int order;
    int helpid;
} SETTING;
typedef struct _profile
{
    struct _profile *next;
    char *name;
    SETTING *debugSettings;
    SETTING *releaseSettings;
} PROFILE ;

typedef struct _profileNameList
{
    struct _profileNameList *next;
    char name[256];
} PROFILENAMELIST;
typedef struct BuildRule
{
    struct BuildRule *next;
    char name[MAX_PATH];
    PROFILE *profiles;
    int defaultRule;
    int active;
    int remove;
    int add;
} BUILDRULE;
typedef struct nameValuePair
{
    struct nameValuePair *next;
    char *name;
    char *value;
    BOOL alloced;
    BOOL assign;
} NameValuePair;

typedef struct _projectItem
{
	enum pi_type { PJ_WS, PJ_PROJ, PJ_FOLDER, PJ_FILE, PJ_RES, PJ_RESMENU = 200 } type; // shared with resources
	struct _projectItem *next;
	struct _projectItem *parent;
	struct _projectItem *children;
    struct _projectItemList *depends;
    struct _projectItem *internalDependsLink;
	char displayName[256];
	char realName[MAX_PATH];
    char outputExt[MAX_PATH];
    char outputName[MAX_PATH];
    FILETIME fileTime, outputTime;
	HTREEITEM hTreeItem, hResTreeItem;
    struct resData *resData;
    PROFILE *profiles;
    NameValuePair *mmacro;
    NameValuePair *mmcmd;
    NameValuePair *mmcustomCmd;
	BOOL expanded;
	BOOL changed;
	BOOL loaded;
    BOOL visited;
    BOOL clean;
	DWORD dbgview;
} PROJECTITEM;

typedef struct _projectItemList
{
    struct _projectItemList *next;
    PROJECTITEM *item;
} PROJECTITEMLIST;
// end new project stufff
typedef struct
{
    int id;
    char *text;
} POPUPMENUTEXT;

typedef struct
{
    int start, end;
    int color;
    int italic;
} EDITATTRIBS;

typedef struct _bkpt
{
    struct _bkpt *next;
    int *addresses;
    int *tempvals;
    BOOL active;
    int linenum;
    char module[256];
    void *extra; // to be defined later
} BREAKPOINT;

typedef struct _threads
{
    CONTEXT regs; // keep this first, it has to be DWORD aligned
    // malloc will always return DWORD alignment so we are safe
    struct _threads *next;
    struct _process *process;
    DWORD idThread;
    HANDLE hThread;
    DWORD oldaddr;
    DWORD suspcount;
    BREAKPOINT breakpoint;
    char name[256];
} THREAD;

typedef struct _scope
{
    struct _scope *next;
    int address;
    int basePtr;
    int lineno;
    char name[MAX_PATH];
    char fileName[MAX_PATH];
} SCOPE;
typedef struct dbg_info
{
    void *dbPointer;
    DWORD linkbase;
    DWORD loadbase;
} DEBUG_INFO;

typedef struct dll_info
{
    struct dll_info *next;
    DEBUG_INFO *dbg_info;
    DWORD base;
    char name[MAX_PATH];
    int fUnicode;
    int breakpoint;
    HANDLE hFile;
} DLL_INFO;

typedef struct _process
{
    struct _process *next;
    HANDLE hProcess;
    DWORD idProcess;
    DWORD base;
    DLL_INFO *dll_info;
    THREAD *threads;
    DEBUG_INFO *dbg_info;
    BREAKPOINT breakpoints;
    DWORD idTempBpThread;
    DWORD ExitAddr;
    char name[MAX_PATH];
} PROCESS;
enum DebugState
{
    notDebugging, SteppingOut, SteppingOver, SteppingIn, StepInOut,
        FinishStepOut, Running, atBreakpoint, atException, Aborting, nullState
};

typedef struct varinfo
{
    TCData watchhead;
    HTREEITEM hTreeItem, hTreeHolder;
    THREAD *thread;
    SCOPE *scope;
    struct varinfo *subtype; /* for substructures */
    struct varinfo *link; /* for next link in structure */
    int type;
	int enumfield;
    int address;
	int size;
	int derefaddress;
    int offset;
    long double fval,fvali;
    LLONG_TYPE ival;
    int bitstart;
    int bitlength;
    int outofscopereg: 1;
    int constant: 1;
    int pointer: 1;
    int enumx: 1;
    int structure: 1;
    int unionx: 1;
    int bitfield: 1;
    int array: 1;
    int outofscope: 1;
    int editable: 1;
    int udt: 1;
    int explicitreg: 1;
    int inreg: 1;
    int vararray: 1;
	int argument : 1;
    int arraysize;
    int itemsize;
    int vararraylevel;
    int *vararraylist;
    int *vararraylisttofree;
    int watchindex;
    char membername[256];
    char structtag[256];
    char value[256];
    char screenname[256];
} VARINFO;

typedef struct
{
    VARINFO *info;
    DEBUG_INFO *dbg_info;
    int cursoreip;
} WATCHINFO;

struct tag
{
    struct tag *next, *prev;
    int drawnLineno;
    int editingLineno;
    int debugLineno;
    int fileLineno;
    int charpos;
    int enabled;
    void *extra;
};

struct tagchangeln
{
    struct tagchangeln *next;
    int lineno;
    int delta;
};
struct tagfile
{
    char *next, *prev;
    char name[256];
    struct tag *tagArray[TAG_MAX];
    struct tagchangeln *changedLines;
};
typedef struct
{
//    COLORREF color;
    short effect;
    char ch;
	unsigned char Color;
//    char pad;
} INTERNAL_CHAR;

#define CRLF_DUMMY 255

// The next few constants control the UNDO mechanism
#define UNDO_MAX 1000
#define UNDO_INSERT 1
#define UNDO_DELETE 2
#define UNDO_BACKSPACE 3
#define UNDO_MODIFY 4
#define UNDO_DELETESELECTION 5
#define UNDO_INSERTSELECTION 6
#define UNDO_CASECHANGE 7
#define UNDO_AUTOEND 8
#define UNDO_AUTOBEGIN 9
#define UNDO_AUTOCHAINBEGIN 10
#define UNDO_AUTOCHAINEND 11
// a list of UNDO structures describe each operation the user performs.
// The list is traversed backwards if 'undo' is pressed.
typedef struct
{
    int preselstart;
    int preselend;
    int postselstart;
    int postselend;
	int charpos;
    int len;
    int max;
    unsigned char *data;
	int undotemp;
    char type;
    char modified: 1;
    char noChangeSel: 1;
} UNDO;

// the EDITDATA structure holds all information the edit control has
// available on a per window basis.  Note that this isn't all the information
// there is about the window; things that aren't related to editing
// may be held in structures in the EDITOR module
typedef struct
{
	struct _edlist_ *siblings ;
	unsigned char *lineData;
	int lineDataMax;
    HFONT hFont, hBoldFont, hItalicFont, hItalicBoldFont;
    HBRUSH hbrBackground;
    COLORREF defforeground;
    COLORREF defbackground;
    INTERNAL_CHAR *text;
	char highlightText[256];
    int textlen;
    int textmaxlen;
    int tabs;
    int leftmargin;
    int updowncol;
    UNDO undolist[UNDO_MAX];
    int undohead;
    int undotail;
	int redopos;
	UINT reparseTimerID;
    char undoing;
    char language;
    char modified;
    char txtFontHeight;
    char txtFontWidth;
    char nosel;
    char inserting;
    char selecting;
    char buttondown;
    char autoscrolldir;
    char ttup;
    char sendchangeonpaint;
    char readonly;
    char colorizing;
} COREDATA;

typedef struct {
	COREDATA *cd ;
	HWND self ;
    HWND tooltip;
	int id ;
    int selstartcharpos;
    int selendcharpos;
    int textshowncharpos;
    int leftshownindex;
	int matchingStart;
	int matchingEnd;
	int wheelIncrement;
    char hasfocus;
    char hiddenCaret;
} EDITDATA ;


typedef struct _edlist_
{
	struct _list_ *next;
	EDITDATA *data;
} EDLIST;

typedef struct dwinfo
{
    struct dwinfo *prev, *next;
	EDITDATA *editData;
    char dwTitle[260];
    char dwName[260];
    HWND dwHandle;
    HWND self;
    FILETIME time;
    int editorOffset;
    int dwLineNo;
    int jumplistLineno;
    int lineNumberDigits;
    DWORD temp;
    int logMRU: 1;
    int newFile : 1;
	int timing : 1;
    int uninstantiated : 1;
    int dosStyle : 1;
    int inSaveDialog : 1;
    int deferClose:1;
    int shouldClose:1;
} DWINFO;

typedef struct _databreak_
{
	struct _databreak_ *next;
	char name[256];
	BOOL active;
	DWORD address;
	DWORD size;
} DATABREAK;

#define MAX_BROWSE 50

typedef struct s_FileBrowse
{
    struct s_FileBrowse *next, *prev;
    DWINFO *info;
    int lineno;
} FILEBROWSE;


#define EDIT_PROPERTY_SHEET_COUNT 4
#define EDITPROP 0
#define PRINTFORMATPROP 1
#define GENERALPROP 2
#define INSTALLPROP 3

#define F_DOWN 1
#define F_WHOLEWORD 2
#define F_MATCHCASE 4
#define F_REGULAR 8
#define F_WILDCARD 16
#define F_OUTPUT1 32
#define F_OUTPUT2 64
#define F_OPENWINDOW 128
#define F_REPLACEALL 256
#define F_SUBDIR 512
#define F_ALL 1024

#define F_M_CURRENTDOCUMENT 0
#define F_M_OPENDOCUMENTS 1
#define F_M_CURRENTPROJECT 2
#define F_M_ALLPROJECTS 3
#define F_M_INCLUDEDIR 4
#define F_M_SPECIFIEDPATH 5
#define F_M_MAX 6

// find dialog
typedef struct {
	HWND hwndTab; // tab control
	HWND hwndDisplay; // current child dialog box
	RECT rcDisplay;
	HBITMAP plusBmp;
	HBITMAP minusBmp;
	int findOffs;
	int replaceOffs;
	int iSel;
    int findEnabled;
	DLGTEMPLATE *apRes[8 + 4];
} DLGHDR;


struct _propsData
{
    char *title;
    int protocount;
    PROFILE **prototype;
    PROJECTITEM *saveTo;
};


#define MAKEHASH_MAX 32
typedef struct hashTable
{
    struct hashTable *next;
    PROJECTITEM *pj;
    NameValuePair *pairs[MAKEHASH_MAX];
} HashTable;


#include "ocide.p"


#ifndef TTM_POPUP
#define TTM_POPUP 34
#define UNNAMED_UNION u.
#else
#define UNNAMED_UNION
#endif


#ifdef XXXXX
#define free(x) my_free(x)
#define calloc(x,y) my_calloc(x,y)
#define malloc(x,y) my_malloc(x,y)
#define realloc(x,n) my_realloc(x,n)
#define strdup(s) my_strdup(s)
#endif


#pragma pack()