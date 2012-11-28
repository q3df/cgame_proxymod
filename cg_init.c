#include <math.h>
#include "cg_local.h"



syscall_t g_syscall = NULL;
__DLLEXPORT__ void dllEntry( syscall_t psyscall ) {
	g_syscall = psyscall;
}



void cg_init( int32_t cmd, int32_t clientNum ) {

	g_syscall( CG_PRINT, "^7[^1m^3D^1d^7] cgame-proxy\n" );
	initVM();

	// g_syscall( CG_MEMSET, ...)
	memset( &cgs, 0, sizeof( cgs ) );

	init_gfx( clientNum );
}



void init_gfx( int32_t clientNum ) {
	cgs.clientNum = clientNum;
	
	g_syscall( CG_GETGLCONFIG, &cgs.glconfig ); // rendering configuration
	cgs.screenXScale = cgs.glconfig.vidWidth  / 640.0;
	cgs.screenYScale = cgs.glconfig.vidHeight / 480.0;

	g_syscall( CG_GETGAMESTATE, &cgs.gameState );

	cgs.levelStartTime = atoi( CG_ConfigString(21) ); // levelStartTime
	
	cgs.gfxCharsetShader   = g_syscall( CG_R_REGISTERSHADER, "gfx/2d/bigchars" );
	cgs.gfxWhiteShader     = g_syscall( CG_R_REGISTERSHADER, "white" );
	cgs.gfxCharsetProp     = g_syscall( CG_R_REGISTERSHADER, "menu/art/font1_prop.tga" );
	cgs.gfxCharsetPropGlow = g_syscall( CG_R_REGISTERSHADER, "menu/art/font1_prop_glo.tga" );
	cgs.gfxCharsetPropB    = g_syscall( CG_R_REGISTERSHADER, "menu/art/font2_prop.tga" );
}



void init_hud( void ) {
	cgs.gfxLogo = g_syscall( CG_R_REGISTERSHADER, "gfx/mdd/logo.tga" );
}
