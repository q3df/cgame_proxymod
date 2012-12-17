#ifndef __CG_LOCAL_H__
#define __CG_LOCAL_H__

#ifdef WIN32
#	include <Windows.h>
#	pragma warning( disable : 4996 )
#	define  QDECL   __cdecl
#	ifdef linux
#		undef linux
#	endif
#	define __DLLEXPORT__ __declspec(dllexport)
#else
#	include <string.h>
#	define  QDECL
#	define __DLLEXPORT__
#endif



# include <stdint.h>



/* Mod stuff */
#define DEFAULT_MODDIR   "baseq3"
#define DEFAULT_VMPATH   "vm/cgame.qvm"
#define GAME             "Q3A"

//<mayor>.<compat>.<minor>.<build>
#define VERSION "0.0.0.23"



typedef int32_t (QDECL *syscall_t)(uint32_t, ...);
typedef uint32_t (*pfn_t)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
typedef void (*Function)( void );
extern syscall_t g_syscall;



// Quake3 Defines...
typedef uint8_t byte;
typedef enum {qfalse, qtrue} qboolean;
//typedef int32_t fileHandle_t;

// mode parm for FS_FOpenFile
typedef enum {
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPEND_SYNC
} fsMode_t;

typedef enum {
	FS_SEEK_CUR,
	FS_SEEK_END,
	FS_SEEK_SET
} fsOrigin_t;



typedef enum {
	CG_PRINT,
	CG_ERROR,
	CG_MILLISECONDS,
	CG_CVAR_REGISTER,
	CG_CVAR_UPDATE,
	CG_CVAR_SET,
	CG_CVAR_VARIABLESTRINGBUFFER,
	CG_ARGC,
	CG_ARGV,
	CG_ARGS,
	CG_FS_FOPENFILE,
	CG_FS_READ,
	CG_FS_WRITE,
	CG_FS_FCLOSEFILE,
	CG_SENDCONSOLECOMMAND,
	CG_ADDCOMMAND,
	CG_SENDCLIENTCOMMAND,
	CG_UPDATESCREEN,
	CG_CM_LOADMAP,
	CG_CM_NUMINLINEMODELS,
	CG_CM_INLINEMODEL,
	CG_CM_LOADMODEL,
	CG_CM_TEMPBOXMODEL,
	CG_CM_POINTCONTENTS,
	CG_CM_TRANSFORMEDPOINTCONTENTS,
	CG_CM_BOXTRACE,
	CG_CM_TRANSFORMEDBOXTRACE,
	CG_CM_MARKFRAGMENTS,
	CG_S_STARTSOUND,
	CG_S_STARTLOCALSOUND,
	CG_S_CLEARLOOPINGSOUNDS,
	CG_S_ADDLOOPINGSOUND,
	CG_S_UPDATEENTITYPOSITION,
	CG_S_RESPATIALIZE,
	CG_S_REGISTERSOUND,
	CG_S_STARTBACKGROUNDTRACK,
	CG_R_LOADWORLDMAP,
	CG_R_REGISTERMODEL,
	CG_R_REGISTERSKIN,
	CG_R_REGISTERSHADER,
	CG_R_CLEARSCENE,
	CG_R_ADDREFENTITYTOSCENE,
	CG_R_ADDPOLYTOSCENE,
	CG_R_ADDLIGHTTOSCENE,
	CG_R_RENDERSCENE,
	CG_R_SETCOLOR,
	CG_R_DRAWSTRETCHPIC,
	CG_R_MODELBOUNDS,
	CG_R_LERPTAG,
	CG_GETGLCONFIG,
	CG_GETGAMESTATE,
	CG_GETCURRENTSNAPSHOTNUMBER,
	CG_GETSNAPSHOT,
	CG_GETSERVERCOMMAND,
	CG_GETCURRENTCMDNUMBER,
	CG_GETUSERCMD,
	CG_SETUSERCMDVALUE,
	CG_R_REGISTERSHADERNOMIP,
	CG_MEMORY_REMAINING,
	CG_R_REGISTERFONT,
	CG_KEY_ISDOWN,
	CG_KEY_GETCATCHER,
	CG_KEY_SETCATCHER,
	CG_KEY_GETKEY,
	CG_PC_ADD_GLOBAL_DEFINE,
	CG_PC_LOAD_SOURCE,
	CG_PC_FREE_SOURCE,
	CG_PC_READ_TOKEN,
	CG_PC_SOURCE_FILE_AND_LINE,
	CG_S_STOPBACKGROUNDTRACK,
	CG_REAL_TIME,
	CG_SNAPVECTOR,
	CG_REMOVECOMMAND,
	CG_R_LIGHTFORPOINT,
	CG_CIN_PLAYCINEMATIC,
	CG_CIN_STOPCINEMATIC,
	CG_CIN_RUNCINEMATIC,
	CG_CIN_DRAWCINEMATIC,
	CG_CIN_SETEXTENTS,
	CG_R_REMAP_SHADER,
	CG_S_ADDREALLOOPINGSOUND,
	CG_S_STOPLOOPINGSOUND,

	CG_CM_TEMPCAPSULEMODEL,
	CG_CM_CAPSULETRACE,
	CG_CM_TRANSFORMEDCAPSULETRACE,
	CG_R_ADDADDITIVELIGHTTOSCENE,
	CG_GET_ENTITY_TOKEN,
	CG_R_ADDPOLYSTOSCENE,
	CG_R_INPVS,
	// 1.32
	CG_FS_SEEK,

	/*
	CG_LOADCAMERA,
	CG_STARTCAMERA,
	CG_GETCAMERAINFO,
	*/

	CG_MEMSET = 100,
	CG_MEMCPY,
	CG_STRNCPY,
	CG_SIN,
	CG_COS,
	CG_ATAN2,
	CG_SQRT,
	CG_FLOOR,
	CG_CEIL,
	CG_TESTPRINTINT,
	CG_TESTPRINTFLOAT,
	CG_ACOS
} cgameImport_t;



/* cg_utils.c */
char* vaf( char* format, ... );



/* cg_vm.c */
int32_t callVM( int32_t cmd, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8, int32_t arg9, int32_t arg10, int32_t arg11 );
int32_t callVM_Destroy( void );
int32_t setVMPtr( int32_t arg0 );
int32_t initVM( void );


/* cg_modules */
int32_t loadModules( void );


typedef uint32_t qhandle_t;

#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_CONFIGSTRINGS	1024
#define	MAX_GAMESTATE_CHARS	16000
#define	BIG_INFO_STRING		8192  // used for system info key only

typedef struct {
	int32_t			stringOffsets[MAX_CONFIGSTRINGS];
	char		stringData[MAX_GAMESTATE_CHARS];
	int32_t			dataCount;
} gameState_t;

/*
** glconfig_t
**
** Contains variables specific to the OpenGL configuration
** being run right now.  These are constant once the OpenGL
** subsystem is initialized.
*/
typedef enum {
	TC_NONE,
	TC_S3TC
} textureCompression_t;

typedef enum {
	GLDRV_ICD,					// driver is integrated with window system
								// WARNING: there are tests that check for
								// > GLDRV_ICD for minidriverness, so this
								// should always be the lowest value in this
								// enum set
	GLDRV_STANDALONE,			// driver is a non-3Dfx standalone driver
	GLDRV_VOODOO				// driver is a 3Dfx standalone driver
} glDriverType_t;

typedef enum {
	GLHW_GENERIC,			// where everthing works the way it should
	GLHW_3DFX_2D3D,			// Voodoo Banshee or Voodoo3, relevant since if this is
							// the hardware type then there can NOT exist a secondary
							// display adapter
	GLHW_RIVA128,			// where you can't interpolate alpha
	GLHW_RAGEPRO,			// where you can't modulate alpha on alpha textures
	GLHW_PERMEDIA2			// where you don't have src*dst
} glHardwareType_t;

typedef struct {
	char					renderer_string[MAX_STRING_CHARS];
	char					vendor_string[MAX_STRING_CHARS];
	char					version_string[MAX_STRING_CHARS];
	char					extensions_string[BIG_INFO_STRING];

	int32_t						maxTextureSize;			// queried from GL
	int32_t						maxActiveTextures;		// multitexture ability

	int32_t						colorBits, depthBits, stencilBits;

	glDriverType_t			driverType;
	glHardwareType_t		hardwareType;

	qboolean				deviceSupportsGamma;
	textureCompression_t	textureCompression;
	qboolean				textureEnvAddAvailable;

	int32_t						vidWidth, vidHeight;
	// aspect is the screen's physical width / height, which may be different
	// than scrWidth / scrHeight if the pixels are non-square
	// normal screens should be 4/3, but wide aspect monitors may be 16/9
	float					windowAspect;

	int32_t						displayFrequency;

	// synonymous with "does rendering consume the entire screen?", therefore
	// a Voodoo or Voodoo2 will have this set to TRUE, as will a Win32 ICD that
	// used CDS.
	qboolean				isFullscreen;
	qboolean				stereoEnabled;
	qboolean				smpActive;		// dual processor
} glconfig_t;


typedef struct {
	/* GFX Handles */
	qhandle_t   gfxDeferSymbol;
	qhandle_t		gfxWhiteShader;
	qhandle_t		gfxCharsetShader;
	qhandle_t		gfxCharsetProp;
	qhandle_t		gfxCharsetPropGlow;
	qhandle_t		gfxCharsetPropB;

	qhandle_t		gfxLogo;

	/* Ammo hud */
	qhandle_t		gfxAmmo[16];
} cgMedia_t;


typedef struct {
	/* from cgs_t */
	gameState_t gameState; // gamestate from server
	glconfig_t  glconfig;  // rendering configuration
	int32_t clientNum;
	float   screenXScale;  // derived from glconfig
	float   screenYScale;
	int32_t levelStartTime;
	float   screenXBias;

	/* from cg */
	int32_t time;

	cgMedia_t media;
} cgs_t;


extern	cgs_t cgs;
const char *CG_ConfigString( int32_t index );


#define PROP_GAP_WIDTH			3
#define PROP_SPACE_WIDTH		8
#define PROP_HEIGHT				27
#define PROP_SMALL_SIZE_SCALE	0.75

#define BLINK_DIVISOR			200
#define PULSE_DIVISOR			75

#define UI_LEFT			0x00000000	// default
#define UI_CENTER		0x00000001
#define UI_RIGHT		0x00000002
#define UI_FORMATMASK	0x00000007
#define UI_SMALLFONT	0x00000010
#define UI_BIGFONT		0x00000020	// default
#define UI_GIANTFONT	0x00000040
#define UI_DROPSHADOW	0x00000800
#define UI_BLINK		0x00001000
#define UI_INVERSE		0x00002000
#define UI_PULSE		0x00004000

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

typedef	int32_t	fixed4_t;
typedef	int32_t	fixed8_t;
typedef	int32_t	fixed16_t;

typedef int32_t		sfxHandle_t;
typedef int32_t		fileHandle_t;
typedef int32_t		clipHandle_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846f	// matches value in gcc v2 math.h
#endif

// markfragments are returned by CM_MarkFragments()
typedef struct {
	int32_t		firstPoint;
	int32_t		numPoints;
} markFragment_t;

#define	MAX_QPATH			64		// max length of a quake game pathname
#define GLYPH_START 0
#define GLYPH_END 255
#define GLYPH_CHARSTART 32
#define GLYPH_CHAREND 127
#define GLYPHS_PER_FONT GLYPH_END - GLYPH_START + 1
typedef struct {
  int32_t height;       // number of scan lines
  int32_t top;          // top of glyph in buffer
  int32_t bottom;       // bottom of glyph in buffer
  int32_t pitch;        // width for copying
  int32_t xSkip;        // x adjustment
  int32_t imageWidth;   // width of actual image
  int32_t imageHeight;  // height of actual image
  float s;          // x offset in image where glyph starts
  float t;          // y offset in image where glyph starts
  float s2;
  float t2;
  qhandle_t glyph;  // handle to the shader with the glyph
  char shaderName[32];
} glyphInfo_t;

typedef struct {
  glyphInfo_t glyphs [GLYPHS_PER_FONT];
  float glyphScale;
  char name[MAX_QPATH];
} fontInfo_t;

typedef enum {
	RT_MODEL,
	RT_POLY,
	RT_SPRITE,
	RT_BEAM,
	RT_RAIL_CORE,
	RT_RAIL_RINGS,
	RT_LIGHTNING,
	RT_PORTALSURFACE,		// doesn't draw anything, just info for portals

	RT_MAX_REF_ENTITY_TYPE
} refEntityType_t;

typedef struct {
	refEntityType_t	reType;
	int32_t			renderfx;

	qhandle_t	hModel;				// opaque type outside refresh

	// most recent data
	vec3_t		lightingOrigin;		// so multi-part models can be lit identically (RF_LIGHTING_ORIGIN)
	float		shadowPlane;		// projection shadows go here, stencils go slightly lower

	vec3_t		axis[3];			// rotation vectors
	qboolean	nonNormalizedAxes;	// axis are not normalized, i.e. they have scale
	float		origin[3];			// also used as MODEL_BEAM's "from"
	int32_t			frame;				// also used as MODEL_BEAM's diameter

	// previous data for frame interpolation
	float		oldorigin[3];		// also used as MODEL_BEAM's "to"
	int32_t			oldframe;
	float		backlerp;			// 0.0 = current, 1.0 = old

	// texturing
	int32_t			skinNum;			// inline skin index
	qhandle_t	customSkin;			// NULL for default skin
	qhandle_t	customShader;		// use one image for the entire thing

	// misc
	byte		shaderRGBA[4];		// colors used by rgbgen entity shaders
	float		shaderTexCoord[2];	// texture coordinates used by tcMod entity modifiers
	float		shaderTime;			// subtracted from refdef time to control effect start times

	// extra sprite information
	float		radius;
	float		rotation;
} refEntity_t;

#define MAX_TOKENLENGTH		1024

typedef struct pc_token_s
{
	int32_t type;
	int32_t subtype;
	int32_t intvalue;
	float floatvalue;
	char string[MAX_TOKENLENGTH];
} pc_token_t;

#define	MAX_RENDER_STRINGS			8
#define	MAX_RENDER_STRING_LENGTH	32
#define	MAX_MAP_AREA_BYTES		32		// bit vector of area visibility
typedef struct {
	int32_t			x, y, width, height;
	float		fov_x, fov_y;
	vec3_t		vieworg;
	vec3_t		viewaxis[3];		// transformation matrix

	// time in milliseconds for shader effects and other time dependent rendering issues
	int32_t			time;

	int32_t			rdflags;			// RDF_NOWORLDMODEL, etc

	// 1 bits will prevent the associated area from rendering at all
	byte		areamask[MAX_MAP_AREA_BYTES];

	// text messages for deform text shaders
	char		text[MAX_RENDER_STRINGS][MAX_RENDER_STRING_LENGTH];
} refdef_t;

typedef struct qtime_s {
	int32_t tm_sec;     /* seconds after the minute - [0,59] */
	int32_t tm_min;     /* minutes after the hour - [0,59] */
	int32_t tm_hour;    /* hours since midnight - [0,23] */
	int32_t tm_mday;    /* day of the month - [1,31] */
	int32_t tm_mon;     /* months since January - [0,11] */
	int32_t tm_year;    /* years since 1900 */
	int32_t tm_wday;    /* days since Sunday - [0,6] */
	int32_t tm_yday;    /* days since January 1 - [0,365] */
	int32_t tm_isdst;   /* daylight savings time flag */
} qtime_t;

typedef struct {
	vec3_t		xyz;
	float		st[2];
	byte		modulate[4];
} polyVert_t;


// usercmd_t is sent to the server each client frame
typedef struct usercmd_s {
	int32_t				serverTime;
	int32_t				angles[3];
	int32_t 			buttons;
	byte			weapon;           // weapon 
	signed char	forwardmove, rightmove, upmove;
} usercmd_t;



// player_state->stats[] indexes
// NOTE: may not have more than 16
typedef enum {
	STAT_HEALTH,
	STAT_HOLDABLE_ITEM,
	STAT_WEAPONS,       // 16 bit fields
	STAT_ARMOR,
	STAT_DEAD_YAW,      // look this direction when dead (FIXME: get rid of?)
	STAT_CLIENTS_READY, // bit mask of clients wishing to exit the intermission (FIXME: configstring?)
	STAT_MAX_HEALTH     // health / armor limit, changable by handicap
} statIndex_t;



typedef enum {
	WP_NONE,

	WP_GAUNTLET,
	WP_MACHINEGUN,
	WP_SHOTGUN,
	WP_GRENADE_LAUNCHER,
	WP_ROCKET_LAUNCHER,
	WP_LIGHTNING,
	WP_RAILGUN,
	WP_PLASMAGUN,
	WP_BFG,
	WP_GRAPPLING_HOOK,

	WP_NUM_WEAPONS
} weapon_t;



#define	MAX_GENTITIES		(1<<10)
#define	ENTITYNUM_NONE		(MAX_GENTITIES-1)
#define	MAX_ENTITIES_IN_SNAPSHOT	256
// bit field limits
#define	MAX_STATS				16
#define	MAX_PERSISTANT			16
#define	MAX_POWERUPS			16
#define	MAX_WEAPONS				16		

#define	MAX_PS_EVENTS			2

typedef struct playerState_s {
	int32_t			commandTime;	// cmd->serverTime of last executed command
	int32_t			pm_type;
	int32_t			bobCycle;		// for view bobbing and footstep generation
	int32_t			pm_flags;		// ducked, jump_held, etc
	int32_t			pm_time;

	vec3_t		origin;
	vec3_t		velocity;
	int32_t			weaponTime;
	int32_t			gravity;
	int32_t			speed;
	int32_t			delta_angles[3];	// add to command angles to get view direction
									// changed by spawns, rotating objects, and teleporters

	int32_t			groundEntityNum;// ENTITYNUM_NONE = in air

	int32_t			legsTimer;		// don't change low priority animations until this runs out
	int32_t			legsAnim;		// mask off ANIM_TOGGLEBIT

	int32_t			torsoTimer;		// don't change low priority animations until this runs out
	int32_t			torsoAnim;		// mask off ANIM_TOGGLEBIT

	int32_t			movementDir;	// a number 0 to 7 that represents the reletive angle
								// of movement to the view angle (axial and diagonals)
								// when at rest, the value will remain unchanged
								// used to twist the legs during strafing

	vec3_t		grapplePoint;	// location of grapple to pull towards if PMF_GRAPPLE_PULL

	int32_t			eFlags;			// copied to entityState_t->eFlags

	int32_t			eventSequence;	// pmove generated events
	int32_t			events[MAX_PS_EVENTS];
	int32_t			eventParms[MAX_PS_EVENTS];

	int32_t			externalEvent;	// events set on player from another source
	int32_t			externalEventParm;
	int32_t			externalEventTime;

	int32_t			clientNum;		// ranges from 0 to MAX_CLIENTS-1
	int32_t			weapon;			// copied to entityState_t->weapon
	int32_t			weaponstate;

	vec3_t		viewangles;		// for fixed views
	int32_t			viewheight;

	// damage feedback
	int32_t			damageEvent;	// when it changes, latch the other parms
	int32_t			damageYaw;
	int32_t			damagePitch;
	int32_t			damageCount;

	int32_t			stats[MAX_STATS];
	int32_t			persistant[MAX_PERSISTANT];	// stats that aren't cleared on death
	int32_t			powerups[MAX_POWERUPS];	// level.time that the powerup runs out
	int32_t			ammo[MAX_WEAPONS];

	int32_t			generic1;
	int32_t			loopSound;
	int32_t			jumppad_ent;	// jumppad entity hit this frame

	// not communicated over the net at all
	int32_t			ping;			// server to game info for scoreboard
	int32_t			pmove_framecount;	// FIXME: don't transmit over the network
	int32_t			jumppad_frame;
	int32_t			entityEventSequence;
} playerState_t;

// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define	SOLID_BMODEL	0xffffff

typedef enum {
	TR_STATIONARY,
	TR_INTERPOLATE,				// non-parametric, but interpolate between snapshots
	TR_LINEAR,
	TR_LINEAR_STOP,
	TR_SINE,					// value = base + sin( time / duration ) * delta
	TR_GRAVITY
} trType_t;

typedef struct {
	trType_t	trType;
	int32_t		trTime;
	int32_t		trDuration;			// if non 0, trTime + trDuration = stop time
	vec3_t	trBase;
	vec3_t	trDelta;			// velocity, etc
} trajectory_t;

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large

typedef struct entityState_s {
	int32_t		number;			// entity index
	int32_t		eType;			// entityType_t
	int32_t		eFlags;

	trajectory_t	pos;	// for calculating position
	trajectory_t	apos;	// for calculating angles

	int32_t		time;
	int32_t		time2;

	vec3_t	origin;
	vec3_t	origin2;

	vec3_t	angles;
	vec3_t	angles2;

	int32_t		otherEntityNum;	// shotgun sources, etc
	int32_t		otherEntityNum2;

	int32_t		groundEntityNum;	// -1 = in air

	int32_t		constantLight;	// r + (g<<8) + (b<<16) + (intensity<<24)
	int32_t		loopSound;		// constantly loop this sound

	int32_t		modelindex;
	int32_t		modelindex2;
	int32_t		clientNum;		// 0 to (MAX_CLIENTS - 1), for players and corpses
	int32_t		frame;

	int32_t		solid;			// for client side prediction, trap_linkentity sets this properly

	int32_t		event;			// impulse events -- muzzle flashes, footsteps, etc
	int32_t		eventParm;

	// for players
	int32_t		powerups;		// bit flags
	int32_t		weapon;			// determines weapon and flash model, etc
	int32_t		legsAnim;		// mask off ANIM_TOGGLEBIT
	int32_t		torsoAnim;		// mask off ANIM_TOGGLEBIT

	int32_t		generic1;
} entityState_t;

// snapshots are a view of the server at a given time

// Snapshots are generated at regular time intervals by the server,
// but they may not be sent if a client's rate level is exceeded, or
// they may be dropped by the network.
typedef struct {
	int32_t				snapFlags;			// SNAPFLAG_RATE_DELAYED, etc
	int32_t				ping;

	int32_t				serverTime;		// server time the message is valid for (in msec)

	byte			areamask[MAX_MAP_AREA_BYTES];		// portalarea visibility bits

	playerState_t	ps;						// complete information about the current player at this time

	int32_t				numEntities;			// all of the entities that need to be presented
	entityState_t	entities[MAX_ENTITIES_IN_SNAPSHOT];	// at the time of this snapshot

	int32_t				numServerCommands;		// text based server commands to execute when this
	int32_t				serverCommandSequence;	// snapshot becomes current
} snapshot_t;





extern vec4_t	g_color_table[10];

#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p)	( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )

#define COLOR_BLACK		'0'
#define COLOR_RED		'1'
#define COLOR_GREEN		'2'
#define COLOR_YELLOW	'3'
#define COLOR_BLUE		'4'
#define COLOR_CYAN		'5'
#define COLOR_MAGENTA	'6'
#define COLOR_WHITE		'7'
#define COLOR_ORANGE	'8'
#define COLOR_MDGREY	'9'
#define ColorIndex(c)	( ( ( (c) - '0' ) &15 ) %10 )

#define S_COLOR_BLACK	"^0"
#define S_COLOR_RED		"^1"
#define S_COLOR_GREEN	"^2"
#define S_COLOR_YELLOW	"^3"
#define S_COLOR_BLUE	"^4"
#define S_COLOR_CYAN	"^5"
#define S_COLOR_MAGENTA	"^6"
#define S_COLOR_WHITE	"^7"
#define S_COLOR_ORANGE	"^8"
#define S_COLOR_MDGREY	"^9"


#define	SCREEN_WIDTH		640
#define	SCREEN_HEIGHT		480

#define TINYCHAR_WIDTH		(SMALLCHAR_WIDTH)
#define TINYCHAR_HEIGHT		(SMALLCHAR_HEIGHT/2)

#define SMALLCHAR_WIDTH		8
#define SMALLCHAR_HEIGHT	16

#define BIGCHAR_WIDTH		16
#define BIGCHAR_HEIGHT		16

#define	GIANTCHAR_WIDTH		32
#define	GIANTCHAR_HEIGHT	48

#endif // __CG_LOCAL_H__
