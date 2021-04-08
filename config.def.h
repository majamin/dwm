/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 24;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu:size=12", "JoyPixels:pixelsize=12" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_grey[]        = "#888888";

/*
 * Colors from https://www.w3schools.com/colors/colors_compound.asp
 */
static const char col_bg1[]		= "#ebf1fb";
static const char col_fg1[]		= "#135feb";
static const char col_bg2[]		= "#ffc42e";
static const char col_fg2[]		= "#760dc6";
static const char col_dark[]		= "#230a37";

/*
 * Colors from https://www.w3schools.com/colors/colors_compound.asp
 */
//static const char col_bg1[]		= "#f5f7d4";
//static const char col_fg1[]		= "#d61a46";
//static const char col_bg2[]		= "#e4f132";
//static const char col_fg2[]		= "#559e54";
//static const char col_dark[]		= "#0a3409";

/*
 * Colors from https://www.w3schools.com/colors/colors_compound.asp
 */
//static const char col_bg1[]		= "#e3f7d4";
//static const char col_fg1[]		= "#66b032";
//static const char col_bg2[]		= "#8601af";
//static const char col_fg2[]		= "#fb9902";
//static const char col_dark[]		= "#2a0934";

static const unsigned int baralpha = 0xd0;
//static const unsigned int baralpha = 0x10;
static const unsigned int borderalpha = OPAQUE; // don't make borders transparent

static const char *colors[][3]      = {
	/*                   fg        bg         border         */
	[SchemeNorm]     = { col_dark, col_bg1,                   },
	[SchemeSel]      = { col_dark, col_bg1,   col_bg2         },
	[SchemeOne]      = { col_dark, col_bg1,   col_dark        },
	[SchemeTwo]      = { col_fg2,  col_bg1,   col_dark        },
	[SchemeThree]    = { col_fg1,  col_bg1,   col_dark        },
	[SchemeStatus]   = { col_dark, col_bg1,   col_dark        },
	[SchemeTagsSel]  = { col_dark, col_bg1,   col_dark        }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm] = { col_grey, col_bg1,   "#000000"       }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_dark, col_bg1,   "#000000"       }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm] = { col_dark, col_bg1,   "#000000"       }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]   = { OPAQUE, baralpha, borderalpha },
	[SchemeOne]      = { OPAQUE, baralpha, borderalpha },
	[SchemeTwo]      = { OPAQUE, baralpha, borderalpha },
	[SchemeThree]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoNorm] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "❶", "❷", "❸", "❹"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance         title             tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,            NULL,             1 << 2,    0,          0,           1,        -1 },
	{ "Brave",   NULL,            NULL,             1 << 3,    0,          0,           1,        -1 },
	{ "Firefox", NULL,            NULL,             1 << 3,    0,          0,           1,        -1 },
	{ "St",      NULL,            NULL,             0,         0,          1,           0,        -1 },
	{ NULL,      NULL,            "Event Tester",   0,         1,          0,           1,        -1 }, /* xev */
	{ NULL,      NULL,            "xzoom",          0,         1,          0,           1,        -1 },
	{ NULL,      NULL,            "mpv-clipyt",     0,         1,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg1, "-nf", col_dark, "-sb", col_bg2, "-sf", col_dark, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "40x20-1-1", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,         spawn,          {.v = dmenucmd } },    // open program with dmenu
	{ MODKEY,                       XK_Return,    spawn,          {.v = termcmd } },    // open terminal
	{ MODKEY,                       XK_grave,     togglescratch,  {.v = scratchpadcmd } }, // open scratchpad terminal
	{ MODKEY,                       XK_b,         togglebar,      {0} },    // toggle statusbar
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },    // focus on window up in stack
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },    // focus on window down in stack
	{ MODKEY,                       XK_w,         spawn,          SHCMD("$BROWSER") },    // Opens browser
	{ MODKEY,                       XK_y,         spawn,          SHCMD("clipyt") },    // Play clipboard and on-disk media all-in-one
	{ MODKEY,                       XK_slash,     spawn,          SHCMD("clipyt -p") },    // Pause/play spawned clipyt
	{ MODKEY,                       XK_q,         killclient,     {0} },    // Forceably close client (window)
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },    // Move window up in stack
	{ MODKEY,                       XK_d,         incnmaster,     {.i = -1 } },    // Move window down in stack
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },    // Decrease master window size
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },    // Increase master window size
	{ MODKEY|ShiftMask,             XK_l,         spawn,          SHCMD("slock") },    // Lock the screen; type passwd to unlock
	{ MODKEY|ShiftMask,             XK_Return,    zoom,           {0} }, // make focused window master
	{ MODKEY|ShiftMask,             XK_BackSpace, spawn,          SHCMD("sysact") },    // System shutdown menu
	{ MODKEY,                       XK_minus,     spawn,          SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },    // Volume down 5
	{ MODKEY|ShiftMask,             XK_minus,     spawn,          SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },    // Volume down 15
	{ MODKEY,                       XK_equal,     spawn,          SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },    // Volume up 5
	{ MODKEY|ShiftMask,             XK_equal,     spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },    // Volume up 15
	{ 0,                            XK_Print,     spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },    // Take a screenshot; placed in home directory
	{ ShiftMask,                    XK_Print,     spawn,          SHCMD("maimpick") },    // select screenshot type
	{ MODKEY,                       XK_Print,     spawn,          SHCMD("dmenurecord") },    // select screen recording
	{ MODKEY,                       XK_Delete,    spawn,          SHCMD("dmenurecord kill") },    // stops recording
	{ MODKEY,                       XK_Scroll_Lock, spawn,        SHCMD("killall screenkey || screenkey &") },    // restart screenkey
	{ MODKEY,                       XK_v,         spawn,          SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
	{ MODKEY,                       XK_n,         spawn,          SHCMD(TERMINAL " -e newsboat") },    // open newsboat
	{ MODKEY,                       XK_semicolon, spawn,          SHCMD("dmenuunicode") },    // open unicode menu
	{ MODKEY,                       XK_Tab,       view,           {0} },    // return to previous tag
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} },    // set tiling window layout
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[1]} },    // set floating window layout
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[2]} },    // set monocle window layout
	{ MODKEY,                       XK_space,     setlayout,      {0} },    // toggle layout view
	{ MODKEY|ShiftMask,             XK_space,     togglefloating, {0} },    // float selected window
	{ MODKEY|ShiftMask,             XK_f,         togglefullscr,  {0} },    // fullscreen selected window
	{ MODKEY,                       XK_s,         togglesticky,   {0} },    // selected window becomes persistant across tags
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },    // toggle all tags
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },    // toggle all tags shown
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
	{ 0,                            XF86XK_AudioMute,         spawn,  SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,  SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,  SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioPrev,         spawn,  SHCMD("mpc prev") },
	{ 0,                            XF86XK_AudioNext,         spawn,  SHCMD("mpc next") },
	{ 0,                            XF86XK_AudioPause,        spawn,  SHCMD("mpc pause") },
	{ 0,                            XF86XK_AudioPlay,         spawn,  SHCMD("mpc play") },
	{ 0,                            XF86XK_AudioStop,         spawn,  SHCMD("mpc stop") },
	{ 0,                            XF86XK_AudioRewind,       spawn,  SHCMD("mpc seek -10") },
	{ 0,                            XF86XK_AudioForward,      spawn,  SHCMD("mpc seek +10") },
	{ 0,                            XF86XK_AudioMedia,        spawn,  SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0,                            XF86XK_PowerOff,          spawn,  SHCMD("sysact") },
	{ 0,                            XF86XK_Sleep,             spawn,  SHCMD("sudo -A zzz") },
	/* { 0, XF86XK_Battery,         spawn,  SHCMD("") }, */
	{ 0,                            XF86XK_TouchpadToggle,    spawn,  SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0,                            XF86XK_TouchpadOff,       spawn,  SHCMD("synclient TouchpadOff=1") },
	{ 0,                            XF86XK_TouchpadOn,        spawn,  SHCMD("synclient TouchpadOff=0") },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,  SHCMD("xbacklight -inc 15") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,  SHCMD("xbacklight -dec 15") },
	TAGKEYS(                        XK_1,                     0)
	TAGKEYS(                        XK_2,                     1)
	TAGKEYS(                        XK_3,                     2)
	TAGKEYS(                        XK_4,                     3)
	TAGKEYS(                        XK_5,                     4)
	TAGKEYS(                        XK_6,                     5)
	TAGKEYS(                        XK_7,                     6)
	TAGKEYS(                        XK_8,                     7)
	TAGKEYS(                        XK_9,                     8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
