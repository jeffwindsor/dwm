#define TERMINAL "alacritty"

#include "patches/tender_colors.h"
#include "patches/selfrestart.c"

// bar
static const char *tags[]   = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
#include "patches/shiftview.c"
static const int showbar    = 1;        /* 0 means no bar */
static const int topbar     = 1;        /* 0 means bottom bar */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gandolf, col_darker, col_darker },
	[SchemeSel]  = { col_text,    col_bg,   col_bg   },
	//[SchemeNorm] = { col_blue2, col_blue5, col_blue4 },
	//[SchemeSel]  = { col_yellow2, col_blue4, col_blue4 },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg    border     */
	[SchemeNorm] = { OPAQUE, 0x44, 0x44 },
	[SchemeSel]  = { OPAQUE, 0x44, 0x44 },
};

// systray
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;     /* 0 means no systray */

// windows
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const char *fonts[]          = { "JetBrains Mono Light:size=12" }; //{ "Noto Sans Mono:size=11"} 

// layout(s)
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const Layout layouts[]   = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "<!>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, 
    "-fn", "JetBrains Mono Light:size=12", 
    "-nb", col_bg, "-nf", col_yellow1, 
    "-sb", col_yellow3, "-sf", col_yellow1,
    NULL };

static Key keys[] = {
	/* modifier          key        function        argument */
	{ MODKEY,            XK_space,  spawn,          {.v = dmenucmd} },
	{ MODKEY,            XK_Return, spawn,          SHCMD(TERMINAL)},
	{ MODKEY|ShiftMask,  XK_Return, spawn,          SHCMD("thunar")},
	{ MODKEY|ControlMask,XK_Return, spawn,          SHCMD("firefox")},
	{ MODKEY,            XK_period, spawn,          SHCMD("arcolinux-tweak-tool")},
	{ MODKEY,            XK_comma,  spawn,          SHCMD(TERMINAL " -e nvim ~/src/dwm/config.h") },
	{ MODKEY,            XK_v,      spawn,          SHCMD("pavctrl")},
	{ MODKEY,            XK_Escape, spawn,          SHCMD("xfce4-taskmanager")},
	{ MODKEY,            XK_x,      spawn,          SHCMD("arcolinux-logout")},
	{ MODKEY,            XK_e,      spawn,          SHCMD("emacs")},
	{ ControlMask,       XK_Left,   spawn,          SHCMD("variety -p")},
	{ ControlMask,       XK_Right,  spawn,          SHCMD("variety -n")},
	{ MODKEY,            XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,            XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,            XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,            XK_q,      killclient,     {0} },
    { MODKEY,            XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,            XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,            XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,            XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY,            XK_Up,     focusstack,     {.i = +1 } },
	{ MODKEY,            XK_Down,   focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,  XK_r,      self_restart,   {0} },
	//{ 0, XF86XK_MonBrightnessUp,    spawn,          SHCMD("xbacklight -inc 15") },
	//{ 0, XF86XK_MonBrightnessDown,  spawn,          SHCMD("xbacklight -dec 15") },
	//{ 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD("amixer set Master 10%+") },
	//{ 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD("amixer set Master 10%-") },
	//{ 0, XF86XK_AudioMute,          spawn,          SHCMD("amixer -D pulse set Master 1+ toggle") },
	TAGKEYS(             XK_1,                      0)
	TAGKEYS(             XK_2,                      1)
	TAGKEYS(             XK_3,                      2)
	TAGKEYS(             XK_4,                      3)
	TAGKEYS(             XK_5,                      4)
	TAGKEYS(             XK_6,                      5)
	TAGKEYS(             XK_7,                      6)
	TAGKEYS(             XK_8,                      7)
	TAGKEYS(             XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
       /* click                event mask      button          function        argument */
       { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
       { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
       { ClkWinTitle,          0,              Button2,        zoom,           {0} },
       //{ ClkStatusText,        0,              Button1,        spawn,          {.v = taskcmd } },
       //{ ClkStatusText,        0,              Button2,        spawn,          {.v = filecmd } },
       //{ ClkStatusText,        0,              Button3,        spawn,          {.v = calendar } },
       { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
       { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
       { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
       { ClkTagBar,            0,              Button1,        view,           {0} },
       { ClkTagBar,            0,              Button3,        toggleview,     {0} },
       { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
       { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, clasdmenucmds
	 *	WM_NAME(STRING) = title
	 *  use tags mask to point an application to a specific workspace
	 */
	/* class                       instance    title      tags mask      isfloating   monitor */
	{ "Gimp",                      NULL,       NULL,       0,            0,           -1 },
	{ "Xfce4-terminal",            NULL,       NULL,       0,            1,           -1 },
	{ "firefox",                   NULL,       NULL,       0,            0,           -1 },
	{ "Arcolinux-welcome-app.py",  NULL,       NULL,       0,            1,           -1 },
};

