#define SELECT_MONITOR  "/home/dev/.config/dmenu/monitor"

#include "colors_tender.h"      /* color scheme */
#include "push.c"

/* bar */
static const int showbar      = 1;  /* 0 means no bar */
static const int topbar       = 1;  /* 0 means bottom bar */
static const int horizpadbar  = 0;  /* horizontal padding for statusbar */
static const int vertpadbar   = 7;  /* vertical padding for statusbar */
static const char *tags[]     = { "", "", "3", "4", "5", "6", "7", "8", "9" };
static const char *fonts[]    = { "JetBrains Mono Light:size=12", "FontAwesome:size=12" };
static const char *colors[][3]= {   /* fg bg border */
	[SchemeNorm] = { col_blue1, col_blue7, col_blue4 },
    [SchemeSel]  = { col_blue1, col_blue5, col_blue3 },
};
static const unsigned int alphas[][3] = { /* fg bg border */
	[SchemeNorm] = { 0xff, 0xbb, 0xff },
    [SchemeSel]  = { 0xff, 0xbb, 0xff },
};

/* dmenu */
static char dmenumon[2]       = "0";   /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };

/* systray */
static const unsigned int systraypinning = 0;     /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;     /* systray spacing */
static const int systraypinningfailfirst = 1;     /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 0;     /* 0 means no systray */

/* windows */
static const unsigned int borderpx       = 1;     /* border pixel of windows */
static const unsigned int gappx          = 5;     /* gaps between windows */
static const unsigned int snap           = 32;    /* snap pixel */

/* layout(s) */
static const float mfact                 = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster                 = 1;     /* number of clients in master area */
static const int resizehints             = 1;     /* 1 means respect size hints in tiled resizals */
static const Layout layouts[]            = {      /* symbom arrange function */
	{ "[]=",      tile },                         /* first entry is default */
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
static Key keys[] = {
	/* modifier          key        function        argument */
	{ ShiftMask,         XK_Left,   setgaps,        {.i = -1 } },
	{ ShiftMask,         XK_Right,  setgaps,        {.i = +1 } },
	{ MODKEY,            XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,            XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,            XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,XK_q,      quit,           {1} },
	{ MODKEY|ControlMask,XK_r,      quit,           {1} },
    { MODKEY,            XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,            XK_j,      pushdown,       {0} }, //push down in the window stack
	{ MODKEY,            XK_k,      pushup,         {0} }, //push up in the window stack
	{ MODKEY,            XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY|ControlMask,XK_l,      incnmaster,     {.i = +1 } },
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

/*    click                event mask      button          function        argument */
static Button buttons[] = {
    
    /* layout icon on bar */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },  //cycle layouts

    /* title portion of bar */
    //{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
    
    /* status portion of bar */
    //{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1 } }, //SIGNAL DWMBLOCKS >> $BLOCKBUTTON = 1 
    //{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2 } }, //SIGNAL DWMBLOCKS >> $BLOCKBUTTON = 2   
    //{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3 } }, //SIGNAL DWMBLOCKS >> $BLOCKBUTTON = 3 

    /* tag portion of bar */
    { ClkTagBar,            0,              Button1,        view,           {0} }, // select tag
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} }, // move window to tag

    /* windows */
    //{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    //{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    //{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

static const Rule rules[] = {
	/* class                       instance    title      tags mask      isfloating   monitor */
	//{ "Gimp",                      NULL,       NULL,       0,            0,           -1 },
	//{ "Xfce4-terminal",            NULL,       NULL,       0,            1,           -1 },
	{ "firefox",                   NULL,       NULL,       0,            0,           -1 },
	{ "Arcolinux-welcome-app.py",  NULL,       NULL,       0,            1,           -1 },
};

static const char *const autostart[] = {
    "sxhkd", NULL,
    "nm-applet", NULL,
    "pamac-tray", NULL,
    "volumeicon", NULL,
    "blueberry-tray", NULL,
    "variety", NULL,
    "xfce4-power-manager", NULL,
    "/usr/lib/xfce4/notifyd/xfce4-notifyd", NULL,
    "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
    "picom", "-b", NULL,
    "numlockx", "on", NULL,
    "dwmblocks", NULL,
    //"slstatus", NULL,
	NULL
};
