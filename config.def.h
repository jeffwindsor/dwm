#define TERMINAL        "alacritty"
#define FILES           "thunar"
#define EDITOR          "emacs"
#define WEB             "firefox"
#define WALLPAPER       "variety"
#define EXIT            "arcolinux-logout"
#define SCRN_BR_UP      "xbacklight -inc 15"
#define SCRN_BR_DOWN    "xbacklight -dec 15"
#define VOL_UP          "amixer set Master 10%+"
#define VOL_DOWN        "amixer set Master 10%-"
#define VOL_MUTE        "amixer -D pulse set Master 1+ toggle"
#define MIC_MUTE        ""
#define LOCK_SCRN       ""
#define PRINT_SCRN      ""
#define AIRPLANE_TGL    ""
#define MEDIA_PLAY      ""
#define MEDIA_STOP      ""
#define MEDIA_FRWD      ""
#define MEDIA_BACK      ""
#define SELECT_MONITOR  "/home/dev/.config/dmenu/monitor"

//#include "<X11/XF86keysym.h>"   /* multimedia keys */
#include "colors_tender.h"      /* color scheme */
#include "push.c"

static const char font[]      = "JetBrains Mono Light:size=14"; //{ "Noto Sans Mono:size=11"} 
static const char icons[]     = "FontAwesome:size=14";
//static const char *rs[]       = { col_red1, col_red5, col_red5 };
//static const char *rn[]       = { col_red1, col_darker, col_darker };
//static const char *ys[]       = { col_yellow1, col_yellow5, col_yellow5 };
//static const char *yn[]       = { col_yellow1, col_darker, col_darker };
//static const char *gs[]       = { col_green1, col_green4, col_green4 };
//static const char *gn[]       = { col_green1, col_darker, col_darker };
//static const char *bs[]       = { col_blue1, col_blue5, col_blue5 };
//static const char *bn[]       = { col_blue1, col_darker, col_darker };

/* bar */
static const int showbar      = 1;  /* 0 means no bar */
static const int topbar       = 1;  /* 0 means bottom bar */
static const int horizpadbar  = 0;  /* horizontal padding for statusbar */
static const int vertpadbar   = 7;  /* vertical padding for statusbar */
static const char *tags[]     = { "", "", "3", "4", "5", "6", "7", "8", "9" };
static const char *fonts[]    = { font, icons };
static const char *colors[][3]= {
	[SchemeStatus]   = { col_blue1, col_darker, col_darker },
    [SchemeTagsSel]  = { col_blue1, col_blue5, col_blue5 },
    [SchemeTagsNorm] = { col_blue1, col_darker, col_darker },
    [SchemeInfoSel] = { col_blue1, col_blue5, col_blue5 },
    [SchemeInfoNorm]  = { col_blue1, col_darker, col_darker },
};
static const unsigned int alphas[][3] = {        /* fg bg border */
	[SchemeTagsSel]  = { 0xff, 0xbb, 0xbb },     // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { 0xff, 0xbb, 0xbb },     // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { 0xff, 0xbb, 0xbb },     // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { 0xff, 0xbb, 0xbb },     // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeStatus]   = { 0xff, 0xbb, 0xbb },     // Statusbar right {text,background,not used but cannot be empty}
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
	{ MODKEY,            XK_space,  spawn,          {.v = dmenucmd} },
	{ MODKEY|ControlMask,XK_space,  spawn,          SHCMD("ls -p $HOME/.local/scripts | rg -v / | dmenu") },
	{ MODKEY,            XK_Return, spawn,          SHCMD(TERMINAL)},
	{ MODKEY|ShiftMask,  XK_Return, spawn,          SHCMD(FILES)},
	{ MODKEY|ControlMask,XK_Return, spawn,          SHCMD(WEB)},
	{ MODKEY,            XK_period, spawn,          SHCMD("arcolinux-tweak-tool")},
	{ MODKEY,            XK_comma,  spawn,          SHCMD(TERMINAL " -e nvim ~/src/dwm/config.h") },
	{ MODKEY,            XK_v,      spawn,          SHCMD("pavctrl")},
	{ MODKEY,            XK_Escape, spawn,          SHCMD("xfce4-taskmanager")},
	{ MODKEY,            XK_x,      spawn,          SHCMD(EXIT)},
	{ MODKEY,            XK_e,      spawn,          SHCMD(EDITOR)},
	{ ControlMask,       XK_Left,   spawn,          SHCMD(WALLPAPER " -p")},
	{ ControlMask,       XK_Right,  spawn,          SHCMD(WALLPAPER " -n")},
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
	{ MODKEY,            XK_F1,     spawn,          SHCMD(VOL_MUTE) },
	{ MODKEY,            XK_F2,     spawn,          SHCMD(VOL_DOWN) },
	{ MODKEY,            XK_F3,     spawn,          SHCMD(VOL_UP) },
    { MODKEY,            XK_F4,     spawn,          SHCMD(MIC_MUTE) },
    { MODKEY,            XK_F7,     spawn,          SHCMD(AIRPLANE_TGL)},
    { MODKEY,            XK_F9,     spawn,          SHCMD(LOCK_SCRN)},
	{ MODKEY,            XK_F10,    spawn,          SHCMD(SELECT_MONITOR) }, // RANDER to EXTERNAL LG 4K
	{ MODKEY,            XK_F11,    spawn,          SHCMD(SCRN_BR_DOWN) },
	{ MODKEY,            XK_F12,    spawn,          SHCMD(SCRN_BR_UP) },
    { MODKEY,            XK_Print,  spawn,          SHCMD(PRINT_SCRN)},
    //{ MODKEY,            XK_F,     spawn,          SHCMD(MEDIA_PLAY)},
    //{ MODKEY,            XK_F,     spawn,          SHCMD(MEDIA_STOP)},
    //{ MODKEY,            XK_F,     spawn,          SHCMD(MEDIA_FRWD)},
    //{ MODKEY,            XK_F,     spawn,          SHCMD(MEDIA_BACK)},
	//{ 0, XF86XK_MonBrightnessUp,    spawn,          SHCMD(SCRN_BR_UP) },
	//{ 0, XF86XK_MonBrightnessDown,  spawn,          SHCMD(SCRN_BR_DOWN) },
	//{ 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD(VOL_UP) },
	//{ 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD(VOL_DOWN) },
	//{ 0, XF86XK_AudioMute,          spawn,          SHCMD(VOL_MUTE) },
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
    //"nm-applet", NULL,
    //"pamac-tray", NULL,
    //"volumeicon", NULL,
    //"blueberry-tray", NULL,
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
