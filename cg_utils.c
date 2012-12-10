#include <stdarg.h>
#include <stdio.h>

#include "cg_local.h"

#ifdef _WIN32
	#define vsnprintf _vsnprintf
#endif

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



playerState_t *getPs( void ) {
	static snapshot_t tmp;
	uint32_t curSnapNum;
	uint32_t servertime;

 	g_syscall( CG_GETCURRENTSNAPSHOTNUMBER, &curSnapNum, &servertime );
	g_syscall( CG_GETSNAPSHOT, curSnapNum, &tmp );

	return &tmp.ps;
}
