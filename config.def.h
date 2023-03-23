/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define GAP 6
#define TERMINAL "kitty"
#define TERMCLASS "kitty"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = GAP;      /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:style:medium:size=12", "Material Design Icons Desktop:size=12" };
static const int vertpad            = GAP;      /* vertical padding of bar */
static const int sidepad            = GAP;      /* horizontal padding of bar */
static const int horizpadbar        = GAP * 1.5;        /* horizontal padding for statusbar */
static const int vertpadbar         = GAP * 1.5;        /* vertical padding for statusbar */
static const char dmenufont[]       ="JetBrainsMono Nerd Font:style:medium:size=12" ;
static const char col_gray1[]       = "#1e222a";
static const char col_gray2[]       = "#2e323a";
static const char col_gray3[]       = "#abb2bf";
static const char col_gray4[]       = "#eeeeee";
static const char col_blue[]        = "#61afef";
static const char col_red[]         = "#f87559";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_red   },
};

/* tagging */
static const char *tags[] = { "󰎤", "󰎧", "󰎪", "󰎭" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox", NULL,     NULL,           1 << 3,    0,          0,          -1,        -1 },
	{ "kitty",   NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "mpv",     NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "⨀",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "kitty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },				// Launch dmenu_run (accessing binaries on PATH)
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },					// Launch terminal (see ~/.local/src/dwm/config.deh.h)
	{ MODKEY,                       XK_b,      togglebar,      {0} },											// Toggle the statusbar on/off
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },							// Focus next client
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },							// Focus previous client
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },							// Increment client stack position
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },							// Decrement client stack position
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },						// Increase the master client width
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },						// Decrease the master client width
	{ MODKEY,                       XK_Return, zoom,           {0} },											// Toggle client master
	{ MODKEY,                       XK_Tab,    view,           {0} },											// Switch to previous tag
	{ MODKEY,                       XK_q,      killclient,     {0} },											// Kill client
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },			// Set tiling layout
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },			// Set floating layout
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },			// Set monocle layout
	{ MODKEY,                       XK_space,  setlayout,      {0} },											// Switch to previous layout
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },											// Toggle client float
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },											// Toggle client fullscreen
	{ MODKEY,                       XK_s,      togglesticky,   {0} },											// Toggle client sticky
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },							// View all tags
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },							//
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },							// Focus previous display (monitor)
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },							// Focus next display (monitor)
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },							// Move client to previous display
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },							// Move client to next display
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },											// Kill DWM
	{ MODKEY,                       XK_w,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },						// Spawn web browser (see ~/.local/src/dwm/config.deh.h)
	{ MODKEY,                       XK_y,      spawn,          {.v = (const char*[]){ "clipyt", NULL } } },						// Spawn clipyt
	{ MODKEY,                       XK_e,      spawn,          {.v = (const char*[]){ "nautilus", NULL } } },					// Spawn file browser (see ~/.local/src/dwm/config.deh.h)
	{ MODKEY,                       XK_o,      spawn,          SHCMD("find ~/.screenlayout/ -type f | dmenu | sh && ~/.local/bin/setbg") },	// Set screen layout (see ~/.screenlayout/)
	{ MODKEY|ShiftMask,          XK_BackSpace, spawn,          {.v = (const char*[]){ "sysact", NULL } } },						// Shutdown, reboot, refresh DWM
	{ 0,                            XK_Print,  spawn,          {.v = (const char*[]){ "maimpick", NULL } } },					// Take a screenshot (copies and saves)
	{ MODKEY,                       XK_equal,  spawn,          {.v = (const char*[]){ "set-volume-notify.sh", "0.1+", NULL } } },					// Volume up
	{ MODKEY,                       XK_minus,  spawn,          {.v = (const char*[]){ "set-volume-notify.sh", "0.1-", NULL } } },					// Volume down
	{ 0,                     XF86XK_AudioMute, spawn,          {.v = (const char*[]){ "set-volume-notify.sh", "0", NULL } } },						// Volume mute
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = (const char*[]){ "set-volume-notify.sh", "0.1+", NULL } } },					// Volume up
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = (const char*[]){ "set-volume-notify.sh", "0.1-", NULL } } },					// Volume down
	{ 0,               XF86XK_MonBrightnessUp, spawn,          {.v = (const char*[]){ "set-brightness-notify.sh", "+10%", NULL } } },			// Brightness up (not working? [Read](https://wiki.archlinux.org/title/Backlight))
	{ 0,             XF86XK_MonBrightnessDown, spawn,          {.v = (const char*[]){ "set-brightness-notify.sh", "10%-", NULL } } },			// Brightness down
	TAGKEYS(                        XK_1,                      0)					// Select TAG 1
	TAGKEYS(                        XK_2,                      1)					// Select TAG 2
	TAGKEYS(                        XK_3,                      2)					// Select TAG 3
	TAGKEYS(                        XK_4,                      3)					// Select TAG 4
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },									// Layout - left-click to select previous layout
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },		// Layout - right-click to select monocle layout
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },									// Layout - middle-click window title to make it master
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },			// Layout - right-click statusbar to spawn terminal
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },									// Move client with MODKEY + left-click
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },									// MODKEY + middle-click toggles client floating
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },									// Resize client with MODKEY + right-click
	{ ClkTagBar,            0,              Button1,        view,           {0} },									// Tag - left-click tag to view it
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },									// Tag - right-click tag to add it view it
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },									// Tag - MODKEY + left-click to move client to tag
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },									// Tag - MODKEY + right-click to make client visible on tag
};

