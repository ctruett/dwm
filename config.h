/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Cousine:size=10";
static const char normbordercolor[] = "#666666";
static const char normbgcolor[]     = "#080808";
static const char normfgcolor[]     = "#888888";
static const char selbordercolor[]  = "#ff0000";
static const char selbgcolor[]      = "#080808";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 3;
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	// { NULL,           NULL,         NULL,       0,     True,   -1 },
	{ "NULL",         "Dialog",     NULL,       0,     True,   -1 },
	// { "Firefox",      "Navigator",  NULL,       1<<1,  False,  -1 },
	// { "Firefox",      "DTA",        NULL,       1<<1,  False,  -1 },
	// { "Qjackctl",     NULL,         NULL,       0,     True,   -1 },
	// { "Xchat",        NULL,         NULL,       1<<2,  False,  -1 },
	// { "Thunderbird",  NULL,         NULL,       1<<3,  False,  -1 },
};

/* layout(s) */
static const float mfact        = 0.7;   /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;     /* number of clients in master area */
static const Bool resizehints   = False; /* True means respect size hints in tiled resizals */
static const Bool clicktofocus  = True;  /* Change focus only on click */

#include "tcl.h"
#include "bstack.c"
static const Layout layouts[] = {
	{ "TTT",      bstack }, 
	{ "[]|",      tile },
	{ "[ ]",      monocle },
	{ "><>",      NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define CTRLKEY ControlMask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                        KEY,  view,        {.ui = 1 << TAG} },  \
{ CTRLKEY,                       KEY,  toggleview,  {.ui = 1 << TAG} },  \
{ CTRLKEY|ShiftMask,             KEY,  tag,         {.ui = 1 << TAG} },  \
{ MODKEY|ControlMask|ShiftMask,  KEY,  toggletag,   {.ui = 1 << TAG} },  

/* commands */
static const char scratchpadname[] = "TODO";
static const char *dmenucmd[]      = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]       = { "urxvt", NULL };
static const char *browse[]        = { "thunar", NULL };
static const char *vim[]           = { "urxvt", "-e", "vim", NULL };
static const char *scratchpadcmd[] = { "urxvt", "-title", scratchpadname, "-geometry", "90x30", "-e", "vim", "/home/chris/Documents/todo.chklst", NULL };

static Key keys[] = {
	/* modifier,                           key,        function,          argument,                 */
	{ MODKEY,                              XK_j,       focusstack,        {.i = +1 } },
	{ MODKEY,                              XK_k,       focusstack,        {.i = -1 } },
	{ MODKEY|ShiftMask,                    XK_j,       pushdown,          {0} },
	{ MODKEY|ShiftMask,                    XK_k,       pushup,            {0} },
	{ MODKEY|ShiftMask,                    XK_equal,   incnmaster,        {.i = +1 } },
	{ MODKEY|ShiftMask,                    XK_minus,   incnmaster,        {.i = -1 } },

	{ MODKEY|ShiftMask,                    XK_c,       killclient,        {0} },
	{ MODKEY|ControlMask|ShiftMask,        XK_q,       quit,              {0} },

	{ MODKEY,                              XK_Tab,     view,              {0} },
	// { MODKEY,                              XK_f,       togglemax,         {0} },
	// { MODKEY,                              XK_c,       centerwindow,      {0} },
	{ MODKEY,                              XK_b,       setlayout,         {.v = &layouts[0]} },
	{ MODKEY,                              XK_t,       setlayout,         {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,                    XK_Return,  setlayout,         {.v = &layouts[2]} },
	// { MODKEY,                              XK_b,       setlayout,         {.v = &layouts[1]} },
	// { MODKEY,                              XK_f,       setlayout,         {.v = &layouts[3]} },

	{ MODKEY,                              XK_l,       setmfact,          {.f = +0.025} },
	{ MODKEY,                              XK_h,       setmfact,          {.f = -0.025} },

	{ MODKEY,                              XK_e,       spawn,             {.v = browse } },
	{ MODKEY,                              XK_p,       spawn,             {.v = dmenucmd } },
	{ MODKEY,                              XK_Return,  spawn,             {.v = termcmd } },
	{ MODKEY,                              XK_v,       spawn,             {.v = vim } },

	{ MODKEY|ControlMask,                  XK_grave,   spawn,             {.v = scratchpadcmd } },
	{ MODKEY,                              XK_grave,   togglescratch,     {.v = scratchpadcmd } },

	{ MODKEY|ShiftMask,                    XK_space,   togglefloating,    {0} },
	{ MODKEY,                              XK_m,       zoom,              {0} },

	{ MODKEY|ShiftMask,                    XK_0,       tag,               {.ui = ~0 } },
		TAGKEYS(                             XK_1,       0)
		TAGKEYS(                             XK_2,       1)
		TAGKEYS(                             XK_3,       2)
		TAGKEYS(                             XK_4,       3)
		TAGKEYS(                             XK_5,       4)
		TAGKEYS(                             XK_6,       5)
		TAGKEYS(                             XK_7,       6)
		TAGKEYS(                             XK_8,       7)
		TAGKEYS(                             XK_9,       8)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1} },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	// { ClkTagBar,            0,              Button4,        cycle,          {.i = -1} },
	// { ClkTagBar,            0,              Button5,        cycle,          {.i = +1} },
};
