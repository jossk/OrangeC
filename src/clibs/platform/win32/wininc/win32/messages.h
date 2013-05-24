/* 
   Messages.h

   Windows32 API message definitions

   Copyright (C) 1996 Free Software Foundation, Inc.

   Author: Scott Christley <scottc@net-community.com>

   This file is part of the Windows32 API Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   If you are interested in a warranty or support for this source code,
   contact Scott Christley <scottc@net-community.com> for more information.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation, 
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   -----------
   DAL 2003 - this file modified extensively for my compiler.  New
   definitionswnwn added as well.
*/
/* WARNING:  This file is automatically generated. */

#ifndef _GNU_H_WINDOWS32_MESSAGES
#define _GNU_H_WINDOWS32_MESSAGES

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Application bar */

/* Application bar notifications */

/* Buttons */
#define BM_CLICK	(245)
#define BM_GETCHECK	(240)
#define BM_GETIMAGE	(246)
#define BM_GETSTATE	(242)
#define BM_SETCHECK	(241)
#define BM_SETIMAGE	(247)
#define BM_SETSTATE	(243)
#define BM_SETSTYLE	(244)
#define BN_CLICKED	(0)
#define BN_DBLCLK	(5)
#define BN_DISABLE	(4)
#define BN_DOUBLECLICKED	(5)
#define BN_HILITE	(2)
#define BN_KILLFOCUS	(7)
#define BN_PAINT	(1)
#define BN_PUSHED	(2)
#define BN_SETFOCUS	(6)
#define BN_UNHILITE	(3)
#define BN_UNPUSHED	(3)

/* Combo Box */
#define CB_ADDSTRING	(323)
#define CB_DELETESTRING	(324)
#define CB_DIR	(325)
#define CB_FINDSTRING	(332)
#define CB_FINDSTRINGEXACT	(344)
#define CB_GETCOUNT	(326)
#define CB_GETCURSEL	(327)
#define CB_GETDROPPEDCONTROLRECT	(338)
#define CB_GETDROPPEDSTATE	(343)
#define CB_GETDROPPEDWIDTH	(351)
#define CB_GETEDITSEL	(320)
#define CB_GETEXTENDEDUI	(342)
#define CB_GETHORIZONTALEXTENT	(349)
#define CB_GETITEMDATA	(336)
#define CB_GETITEMHEIGHT	(340)
#define CB_GETLBTEXT	(328)
#define CB_GETLBTEXTLEN	(329)
#define CB_GETLOCALE	(346)
#define CB_GETTOPINDEX	(347)
#define CB_INITSTORAGE	(353)
#define CB_INSERTSTRING	(330)
#define CB_LIMITTEXT	(321)
#define CB_RESETCONTENT	(331)
#define CB_SELECTSTRING	(333)
#define CB_SETCURSEL	(334)
#define CB_SETDROPPEDWIDTH	(352)
#define CB_SETEDITSEL	(322)
#define CB_SETEXTENDEDUI	(341)
#define CB_SETHORIZONTALEXTENT	(350)
#define CB_SETITEMDATA	(337)
#define CB_SETITEMHEIGHT	(339)
#define CB_SETLOCALE	(345)
#define CB_SETTOPINDEX	(348)
#define CB_SHOWDROPDOWN	(335)

/* Combo Box notifications */
#define CBN_CLOSEUP	(8)
#define CBN_DBLCLK	(2)
#define CBN_DROPDOWN	(7)
#define CBN_EDITCHANGE	(5)
#define CBN_EDITUPDATE	(6)
#define CBN_ERRSPACE	(-1)
#define CBN_KILLFOCUS	(4)
#define CBN_SELCHANGE	(1)
#define CBN_SELENDCANCEL	(10)
#define CBN_SELENDOK	(9)
#define CBN_SETFOCUS	(3)

/* Control Panel */

/* Device messages */

/* Drag list box */
#define DL_BEGINDRAG	(1157)
#define DL_CANCELDRAG	(1160)
#define DL_DRAGGING	(1158)
#define DL_DROPPED	(1159)

/* Default push button */
#define DM_GETDEFID	(1024)
#define DM_REPOSITION	(1026)
#define DM_SETDEFID	(1025)

/* RTF control */
#define EM_CANPASTE	(1074)
#define EM_CANUNDO	(198)
#define EM_CHARFROMPOS	(215)
#define EM_DISPLAYBAND	(1075)
#define EM_EMPTYUNDOBUFFER	(205)
#define EM_EXGETSEL	(1076)
#define EM_EXLIMITTEXT	(1077)
#define EM_EXLINEFROMCHAR	(1078)
#define EM_EXSETSEL	(1079)
#define EM_FINDTEXT	(1080)
#define EM_FINDTEXTEX	(1103)
#define EM_FINDWORDBREAK	(1100)
#define EM_FMTLINES	(200)
#define EM_FORMATRANGE	(1081)
#define EM_GETCHARFORMAT	(1082)
#define EM_GETEVENTMASK	(1083)
#define EM_GETFIRSTVISIBLELINE	(206)
#define EM_GETHANDLE	(189)
#define EM_GETLIMITTEXT	(213)
#define EM_GETLINE	(196)
#define EM_GETLINECOUNT	(186)
#define EM_GETMARGINS	(212)
#define EM_GETMODIFY	(184)
#define EM_GETIMECOLOR	(1129)
#define EM_GETIMEOPTIONS	(1131)
#define EM_GETOPTIONS	(1102)
#define EM_GETOLEINTERFACE	(1084)
#define EM_GETPARAFORMAT	(1085)
#define EM_GETPASSWORDCHAR	(210)
#define EM_GETPUNCTUATION	(1125)
#define EM_GETRECT	(178)
#define EM_GETSEL	(176)
#define EM_GETSELTEXT	(1086)
#define EM_GETTEXTRANGE	(1099)
#define EM_GETTHUMB	(190)
#define EM_GETWORDBREAKPROC	(209)
#define EM_GETWORDBREAKPROCEX	(1104)
#define EM_GETWORDWRAPMODE	(1127)
#define EM_HIDESELECTION	(1087)
#define EM_LIMITTEXT	(197)
#define EM_LINEFROMCHAR	(201)
#define EM_LINEINDEX	(187)
#define EM_LINELENGTH	(193)
#define EM_LINESCROLL	(182)
#define EM_PASTESPECIAL	(1088)
#define EM_POSFROMCHAR	(214)
#define EM_REPLACESEL	(194)
#define EM_REQUESTRESIZE	(1089)
#define EM_SCROLL	(181)
#define EM_SCROLLCARET	(183)
#define EM_SELECTIONTYPE	(1090)
#define EM_SETBKGNDCOLOR	(1091)
#define EM_SETCHARFORMAT	(1092)
#define EM_SETEVENTMASK	(1093)
#define EM_SETHANDLE	(188)
#define EM_SETIMECOLOR	(1128)
#define EM_SETIMEOPTIONS	(1130)
#define EM_SETLIMITTEXT	(197)
#define EM_SETMARGINS	(211)
#define EM_SETMODIFY	(185)
#define EM_SETOLECALLBACK	(1094)
#define EM_SETOPTIONS	(1101)
#define EM_SETPARAFORMAT	(1095)
#define EM_SETPASSWORDCHAR	(204)
#define EM_SETPUNCTUATION	(1124)
#define EM_SETREADONLY	(207)
#define EM_SETRECT	(179)
#define EM_SETRECTNP	(180)
#define EM_SETSEL	(177)
#define EM_SETTABSTOPS	(203)
#define EM_SETTARGETDEVICE	(1096)
#define EM_SETWORDBREAKPROC	(208)
#define EM_SETWORDBREAKPROCEX	(1105)
#define EM_SETWORDWRAPMODE	(1126)
#define EM_STREAMIN	(1097)
#define EM_STREAMOUT	(1098)
#define EM_UNDO	(199)

/* Edit control */
#define EN_CHANGE	(768)
#define EN_CORRECTTEXT	(1797)
#define EN_DROPFILES	(1795)
#define EN_ERRSPACE	(1280)
#define EN_HSCROLL	(1537)
#define EN_IMECHANGE	(1799)
#define EN_KILLFOCUS	(512)
#define EN_MAXTEXT	(1281)
#define EN_MSGFILTER	(1792)
#define EN_OLEOPFAILED	(1801)
#define EN_PROTECTED	(1796)
#define EN_REQUESTRESIZE	(1793)
#define EN_SAVECLIPBOARD	(1800)
#define EN_SELCHANGE	(1794)
#define EN_SETFOCUS	(256)
#define EN_STOPNOUNDO	(1798)
#define EN_UPDATE	(1024)
#define EN_VSCROLL	(1538)

/* File Manager extensions */

/* File Manager extensions DLL events */

/* List box */
#define LB_ADDFILE	(406)
#define LB_ADDSTRING	(384)
#define LB_DELETESTRING	(386)
#define LB_DIR	(397)
#define LB_FINDSTRING	(399)
#define LB_FINDSTRINGEXACT	(418)
#define LB_GETANCHORINDEX	(413)
#define LB_GETCARETINDEX	(415)
#define LB_GETCOUNT	(395)
#define LB_GETCURSEL	(392)
#define LB_GETHORIZONTALEXTENT	(403)
#define LB_GETITEMDATA	(409)
#define LB_GETITEMHEIGHT	(417)
#define LB_GETITEMRECT	(408)
#define LB_GETLOCALE	(422)
#define LB_GETSEL	(391)
#define LB_GETSELCOUNT	(400)
#define LB_GETSELITEMS	(401)
#define LB_GETTEXT	(393)
#define LB_GETTEXTLEN	(394)
#define LB_GETTOPINDEX	(398)
#define LB_INITSTORAGE	(424)
#define LB_INSERTSTRING	(385)
#define LB_ITEMFROMPOINT	(425)
#define LB_RESETCONTENT	(388)
#define LB_SELECTSTRING	(396)
#define LB_SELITEMRANGE	(411)
#define LB_SELITEMRANGEEX	(387)
#define LB_SETANCHORINDEX	(412)
#define LB_SETCARETINDEX	(414)
#define LB_SETCOLUMNWIDTH	(405)
#define LB_SETCOUNT	(423)
#define LB_SETCURSEL	(390)
#define LB_SETHORIZONTALEXTENT	(404)
#define LB_SETITEMDATA	(410)
#define LB_SETITEMHEIGHT	(416)
#define LB_SETLOCALE	(421)
#define LB_SETSEL	(389)
#define LB_SETTABSTOPS	(402)
#define LB_SETTOPINDEX	(407)

/* List box notifications */
#define LBN_DBLCLK	(2)
#define LBN_ERRSPACE	(-2)
#define LBN_KILLFOCUS	(5)
#define LBN_SELCANCEL	(3)
#define LBN_SELCHANGE	(1)
#define LBN_SETFOCUS	(4)

/* Control notification */
#define NM_CHAR (-18)
#define NM_CLICK	(-2)
#define NM_CUSTOMDRAW (-12)
#define NM_DBLCLK	(-3)
#define NM_HOVER (-13)
#define NM_KEYDOWN (-15)
#define NM_KILLFOCUS	(-8)
#define NM_LDOWN (-20)
#define NM_NCHITTEST (-14)
#define NM_OUTOFMEMORY	(-1)
#define NM_RCLICK	(-5)
#define NM_RDBLCLK	(-6)
#define NM_RDOWN (-21)
#define NM_RELEASEDCAPTURE (-16)
#define NM_RETURN	(-4)
#define NM_SETCURSOR (-17)
#define NM_SETFOCUS	(-7)


/* Power status */

/* Scroll bar control */
#define SBM_ENABLE_ARROWS	(228)
#define SBM_GETPOS	(225)
#define SBM_GETRANGE	(227)
#define SBM_GETSCROLLINFO	(234)
#define SBM_SETPOS	(224)
#define SBM_SETRANGE	(226)
#define SBM_SETRANGEREDRAW	(230)
#define SBM_SETSCROLLINFO	(233)

/* Static control */
#define STM_GETICON	(369)
#define STM_GETIMAGE	(371)
#define STM_SETICON	(368)
#define STM_SETIMAGE	(370)

/* Static control notifications */
#define STN_CLICKED	(0)
#define STN_DBLCLK	(1)
#define STN_DISABLE	(3)
#define STN_ENABLE	(2)

/* Window messages */

#define WM_ACTIVATE	(6)
#define WM_ACTIVATEAPP	(28)
#define WM_ASKCBFORMATNAME	(780)
#define WM_CANCELJOURNAL	(75)
#define WM_CANCELMODE	(31)
#define WM_CAPTURECHANGED	(533)
#define WM_CHANGECBCHAIN	(781)
#define WM_CHAR	(258)
#define WM_CHARTOITEM	(47)
#define WM_CHILDACTIVATE	(34)
#define WM_CHOOSEFONT_GETLOGFONT	(1025)
#define WM_CHOOSEFONT_SETLOGFONT	(1125)
#define WM_CHOOSEFONT_SETFLAGS	(1126)
#define WM_CLEAR	(771)
#define WM_CLOSE	(16)
#define WM_COMMAND	(273)
#define WM_COMPACTING	(65)
#define WM_COMPAREITEM	(57)
#define WM_CONTEXTMENU	(123)
#define WM_COPY	(769)
#define WM_COPYDATA	(74)
#define WM_CREATE	(1)
#define WM_CTLCOLORBTN	(309)
#define WM_CTLCOLORDLG	(310)
#define WM_CTLCOLOREDIT	(307)
#define WM_CTLCOLORLISTBOX	(308)
#define WM_CTLCOLORMSGBOX	(306)
#define WM_CTLCOLORSCROLLBAR	(311)
#define WM_CTLCOLORSTATIC	(312)
#define WM_CUT	(768)
#define WM_DEADCHAR	(259)
#define WM_DELETEITEM	(45)
#define WM_DESTROY	(2)
#define WM_DESTROYCLIPBOARD	(775)
#define WM_DEVICECHANGE	(537)
#define WM_DEVMODECHANGE	(27)
#define WM_DISPLAYCHANGE	(126)
#define WM_DRAWCLIPBOARD	(776)
#define WM_DRAWITEM	(43)
#define WM_DROPFILES	(563)
#define WM_ENABLE	(10)
#define WM_ENDSESSION	(22)
#define WM_ENTERIDLE	(289)
#define WM_ENTERMENULOOP	(529)
#define WM_ENTERSIZEMOVE	(561)
#define WM_ERASEBKGND	(20)
#define WM_EXITMENULOOP	(530)
#define WM_EXITSIZEMOVE	(562)
#define WM_FONTCHANGE	(29)
#define WM_GETDLGCODE	(135)
#define WM_GETFONT	(49)
#define WM_GETHOTKEY	(51)
#define WM_GETICON	(127)
#define WM_GETMINMAXINFO	(36)
#define WM_GETTEXT	(13)
#define WM_GETTEXTLENGTH	(14)
#define WM_HELP	(83)
#define WM_HOTKEY	(786)
#define WM_HSCROLL	(276)
#define WM_HSCROLLCLIPBOARD	(782)
#define WM_ICONERASEBKGND	(39)
#define WM_IME_CHAR	(646)
#define WM_IME_COMPOSITION	(271)
#define WM_IME_COMPOSITIONFULL	(644)
#define WM_IME_CONTROL	(643)
#define WM_IME_ENDCOMPOSITION	(270)
#define WM_IME_KEYDOWN	(656)
#define WM_IME_KEYUP	(657)
#define WM_IME_NOTIFY	(642)
#define WM_IME_SELECT	(645)
#define WM_IME_SETCONTEXT	(641)
#define WM_IME_STARTCOMPOSITION	(269)
#define WM_INITDIALOG	(272)
#define WM_INITMENU	(278)
#define WM_INITMENUPOPUP	(279)
#define WM_INPUTLANGCHANGE	(81)
#define WM_INPUTLANGCHANGEREQUEST	(80)
#define WM_KEYDOWN	(256)
#define WM_KEYUP	(257)
#define WM_KILLFOCUS	(8)
#define WM_LBUTTONDBLCLK	(515)
#define WM_LBUTTONDOWN	(513)
#define WM_LBUTTONUP	(514)
#define WM_MBUTTONDBLCLK	(521)
#define WM_MBUTTONDOWN	(519)
#define WM_MBUTTONUP	(520)
#define WM_MDIACTIVATE	(546)
#define WM_MDICASCADE	(551)
#define WM_MDICREATE	(544)
#define WM_MDIDESTROY	(545)
#define WM_MDIGETACTIVE	(553)
#define WM_MDIICONARRANGE	(552)
#define WM_MDIMAXIMIZE	(549)
#define WM_MDINEXT	(548)
#define WM_MDIREFRESHMENU	(564)
#define WM_MDIRESTORE	(547)
#define WM_MDISETMENU	(560)
#define WM_MDITILE	(550)
#define WM_MEASUREITEM	(44)
#define WM_MENUCHAR	(288)
#define WM_MENUSELECT	(287)
#define WM_MOUSEACTIVATE	(33)
#define WM_MOUSEMOVE	(512)
#define WM_MOUSEWHEEL (522)
#define WM_MOVE	(3)
#define WM_MOVING	(534)
#define WM_NCACTIVATE	(134)
#define WM_NCCALCSIZE	(131)
#define WM_NCCREATE	(129)
#define WM_NCDESTROY	(130)
#define WM_NCHITTEST	(132)
#define WM_NCLBUTTONDBLCLK	(163)
#define WM_NCLBUTTONDOWN	(161)
#define WM_NCLBUTTONUP	(162)
#define WM_NCMBUTTONDBLCLK	(169)
#define WM_NCMBUTTONDOWN	(167)
#define WM_NCMBUTTONUP	(168)
#define WM_NCMOUSEMOVE	(160)
#define WM_NCPAINT	(133)
#define WM_NCRBUTTONDBLCLK	(166)
#define WM_NCRBUTTONDOWN	(164)
#define WM_NCRBUTTONUP	(165)
#define WM_NEXTDLGCTL	(40)
#define WM_NOTIFY	(78)
#define WM_NOTIFYFORMAT	(85)
#define WM_NULL         (0)
#define WM_PAINT	(15)
#define WM_PAINTCLIPBOARD	(777)
#define WM_PAINTICON	(38)
#define WM_PALETTECHANGED	(785)
#define WM_PALETTEISCHANGING	(784)
#define WM_PARENTNOTIFY	(528)
#define WM_PASTE	(770)
#define WM_PENWINFIRST  (896)
#define WM_PENWINLAST  (911)
#define WM_POWER	(72)
#define WM_POWERBROADCAST	(536)
#define WM_PRINT	(791)
#define WM_PRINTCLIENT	(792)
#define WM_PSD_ENVSTAMPRECT	(1029)
#define WM_PSD_FULLPAGERECT	(1025)
#define WM_PSD_GREEKTEXTRECT	(1028)
#define WM_PSD_MARGINRECT	(1027)
#define WM_PSD_MINMARGINRECT	(1026)
#define WM_PSD_PAGESETUPDLG	(1024)
#define WM_PSD_YAFULLPAGERECT	(1030)
#define WM_QUERYDRAGICON	(55)
#define WM_QUERYENDSESSION	(17)
#define WM_QUERYNEWPALETTE	(783)
#define WM_QUERYOPEN	(19)
#define WM_QUEUESYNC	(35)
#define WM_QUIT	(18)
#define WM_RBUTTONDBLCLK	(518)
#define WM_RBUTTONDOWN	(516)
#define WM_RBUTTONUP	(517)
#define WM_RENDERALLFORMATS	(774)
#define WM_RENDERFORMAT	(773)
#define WM_SETCURSOR	(32)
#define WM_SETFOCUS	(7)
#define WM_SETFONT	(48)
#define WM_SETHOTKEY	(50)
#define WM_SETICON	(128)
#define WM_SETREDRAW	(11)
#define WM_SETTEXT	(12)
#define WM_SETTINGCHANGE	(26)
#define WM_SHOWWINDOW	(24)
#define WM_SIZE	(5)
#define WM_SIZECLIPBOARD	(779)
#define WM_SIZING	(532)
#define WM_SPOOLERSTATUS	(42)
#define WM_STYLECHANGED	(125)
#define WM_STYLECHANGING	(124)
#define WM_SYSCHAR	(262)
#define WM_SYSCOLORCHANGE	(21)
#define WM_SYSCOMMAND	(274)
#define WM_SYSDEADCHAR	(263)
#define WM_SYSKEYDOWN	(260)
#define WM_SYSKEYUP	(261)
#define WM_TCARD	(82)
#define WM_TIMECHANGE	(30)
#define WM_TIMER	(275)
#define WM_UNDO	(772)
#define WM_USER	(1024)
#define WM_USERCHANGED	(84)
#define WM_VKEYTOITEM	(46)
#define WM_VSCROLL	(277)
#define WM_VSCROLLCLIPBOARD	(778)
#define WM_WINDOWPOSCHANGED	(71)
#define WM_WINDOWPOSCHANGING	(70)
#define WM_WININICHANGE	(26)

/* Window message ranges */
#define WM_KEYFIRST	(256)
#define WM_KEYLAST	(264)
#define WM_MOUSEFIRST	(512)
#define WM_MOUSELAST	(521)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GNU_H_WINDOWS32_MESSAGES */