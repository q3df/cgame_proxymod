#include <math.h>
#include "cg_local.h"



syscall_t g_syscall = NULL;
__DLLEXPORT__ void dllEntry(syscall_t psyscall) {
	g_syscall = psyscall;
}



void cg_init( int cmd, int clientNum ) {

	g_syscall( CG_PRINT, "^7[^1m^3D^1d^7] cgame-proxy\n");
	initVM();

	// g_syscall( CG_MEMSET, ...)
	memset( &cgs, 0, sizeof( cgs ) );
}
