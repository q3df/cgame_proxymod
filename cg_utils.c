#include <stdarg.h>
#include <stdio.h>

#include "cg_local.h"
#include "cg_utils.h"

#ifdef _WIN32
	#define vsnprintf _vsnprintf
#endif



vec4_t    colorBlack  = {0, 0, 0, 1};
vec4_t    colorRed  = {1, 0, 0, 1};
vec4_t    colorGreen  = {0, 1, 0, 1};
vec4_t    colorBlue = {0, 0, 1, 1};
vec4_t    colorYellow = {1, 1, 0, 1};
vec4_t    colorMagenta= {1, 0, 1, 1};
vec4_t    colorCyan = {0, 1, 1, 1};
vec4_t    colorWhite  = {1, 1, 1, 1};
vec4_t    colorLtGrey = {0.75, 0.75, 0.75, 1};
vec4_t    colorMdGrey = {0.5, 0.5, 0.5, 1};
vec4_t    colorDkGrey = {0.25, 0.25, 0.25, 1};



char* vaf(char* format, ...) {
	va_list	argptr;
	static char str[1024];

	va_start(argptr, format);
	vsnprintf(str, 1024, format, argptr);
	va_end(argptr);

	return str;
}



const char *getConfigString( int32_t index ) {
	if( index < 0 || index >= MAX_CONFIGSTRINGS ) {
		g_syscall( CG_ERROR, vaf( "CG_ConfigString: bad index: %i", index ));
	}
	return cgs.gameState.stringData + cgs.gameState.stringOffsets[index];
}



snapshot_t *getSnap( void ) {
	static snapshot_t tmp;
	uint32_t curSnapNum;
	uint32_t servertime;

 	g_syscall( CG_GETCURRENTSNAPSHOTNUMBER, &curSnapNum, &servertime );
	g_syscall( CG_GETSNAPSHOT, curSnapNum, &tmp );

	return &tmp;
}



playerState_t *getPs( void ) {
	snapshot_t *tmp;
	tmp = getSnap( );

	return &tmp->ps;
}



int8_t isInAir( playerState_t *ps ) {
	if( ps == NULL )
		return -1;
	else
		return (ps->groundEntityNum == ENTITYNUM_NONE)?qtrue:qfalse;
}



int8_t isJumping( playerState_t *ps ) {
	if( ps == NULL )
		return -1;
	else
		return (ps->stats[13] & PSF_USERINPUT_JUMP)?qtrue:qfalse;
}



uint32_t getTime( void ) {
	return g_syscall( CG_MILLISECONDS );
}
