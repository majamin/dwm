/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#ffffff";

static const char col_background[]	= "#282a36";
//static const char col_background[]	= "#222222";
static const char col_cyan[]		= "#8be9fd";
static const char col_cyan_dim[]	= "#548e99";
static const char col_green[]		= "#50fa7b";
static const char col_orange[]		= "#ffb86c";
static const char col_pink[]		= "#ff79c6";
static const char col_purple[]		= "#bd93f9";
static const char col_red[]		= "#ff5555";
static const char col_yellow[]		= "#f1fa8c";

static const unsigned int baralpha = 0xd0;
//static const unsigned int baralpha = 0x10;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*                   fg         bg          border   */
	[SchemeNorm]     = { col_white, col_background,  col_gray2  },
	[SchemeSel]      = { col_gray2, col_background,   col_orange   },
	[SchemeCyan]     = { col_cyan,col_background, col_gray2    },
	[SchemeOrange]   = { col_orange,col_background, col_gray2    },
	[SchemePink]     = { col_pink,col_background, col_gray2    },
	[SchemePurple]   = { col_purple,col_background, col_gray2    },
	[SchemeGreen]    = { col_green,col_background, col_gray2    },
	[SchemeYellow]   = { col_yellow,   col_background,    col_gray2    },
	[SchemeRed]      = { col_red,   col_background,    col_gray2    },
	[SchemeStatus]   = { col_gray4, col_background,   col_background   },
	[SchemeTagsSel]  = { col_white, col_cyan_dim,   col_gray2  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm] = { col_gray4, col_background,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_white, col_background,   "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm] = { col_cyan_dim, col_background,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeCyan]     = { OPAQUE, baralpha, borderalpha },
	[SchemeOrange]   = { OPAQUE, baralpha, borderalpha },
	[SchemePink]     = { OPAQUE, baralpha, borderalpha },
	[SchemePurple]   = { OPAQUE, baralpha, borderalpha },
	[SchemeGreen]    = { OPAQUE, baralpha, borderalpha },
	[SchemeYellow]   = { OPAQUE, baralpha, borderalpha },
	[SchemeRed]      = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]   = { OPAQUE, baralpha, borderalpha },
        [SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
        [SchemeTagsNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
        [SchemeInfoNorm] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance         title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,            NULL,           0,         1,          0,           0,        -1 },
	{ "Brave",   NULL,            NULL,           1 << 8,    0,          0,           1,        -1 },
	{ "St",      NULL,            NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,            "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },    // Opens browser
	{ MODKEY,			XK_y,	   spawn,	   SHCMD("clipyt play") },
	{ MODKEY,                       XK_q,      killclient,     {0} },    // Forceably close client (window)
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,		XK_a,	   spawn,          SHCMD("myconfigs") }, // Open menu to edit config files
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,     SHCMD("sysact") },    // System shutdown menu
	{ MODKEY,			XK_minus,	spawn,     SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },    // Volume down 5
	{ MODKEY|ShiftMask,		XK_minus,	spawn,     SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },    // Volume down 15
	{ MODKEY,			XK_equal,	spawn,     SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },    // Volume up 5
	{ MODKEY|ShiftMask,		XK_equal,	spawn,     SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },    // Volume up 15
	{ 0,				XK_Print,  spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,  spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_Print,  spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,  spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Delete, spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },
	{ MODKEY,			XK_n,	   spawn,		SHCMD("st -e newsboat") },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

