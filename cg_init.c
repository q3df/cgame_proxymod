/*
	==============================
	Written by id software, nightmare and hk of mdd
	This file is part of mdd client proxymod.

	mdd client proxymod is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mdd client proxymod is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mdd client proxymod.  If not, see <http://www.gnu.org/licenses/>.
	==============================
	Note: mdd client proxymod contains large quantities from the quake III arena source code
*/
#include <math.h>
#include <stdlib.h>

#include "cg_local.h"
#include "cg_init.h"
#include "cg_draw.h"
#include "cg_hud.h"
#include "cg_cvar.h"
#include "cg_utils.h"



syscall_t g_syscall = NULL;
__DLLEXPORT__ void dllEntry( syscall_t psyscall ) {
	g_syscall = psyscall;
}



void cg_init( int32_t cmd, int32_t clientNum ) {

	g_syscall( CG_PRINT, vaf("^7[^1m^3D^1d^7] cgame-proxy: %s\n", VERSION) );
	initVM();

	// g_syscall( CG_MEMSET, ...)
	memset( &cgs, 0, sizeof( cgs ) );

	init_gfx( clientNum );
	init_hud( );
	init_cvars( );
}



void init_gfx( int32_t clientNum ) {
	cgs.clientNum = clientNum;
	
	g_syscall( CG_GETGLCONFIG, &cgs.glconfig ); // rendering configuration
	cgs.screenXScale = cgs.glconfig.vidWidth  / 640.0;
	cgs.screenYScale = cgs.glconfig.vidHeight / 480.0;

	g_syscall( CG_GETGAMESTATE, &cgs.gameState );

	cgs.levelStartTime = atof( getConfigString(21) ); // levelStartTime

	cgs.media.gfxDeferSymbol     = g_syscall( CG_R_REGISTERSHADER, "gfx/2d/defer" );
	cgs.media.gfxCharsetShader   = g_syscall( CG_R_REGISTERSHADER, "gfx/2d/bigchars" );
	cgs.media.gfxWhiteShader     = g_syscall( CG_R_REGISTERSHADER, "white" );
	cgs.media.gfxCharsetProp     = g_syscall( CG_R_REGISTERSHADER, "menu/art/font1_prop.tga" );
	cgs.media.gfxCharsetPropGlow = g_syscall( CG_R_REGISTERSHADER, "menu/art/font1_prop_glo.tga" );
	cgs.media.gfxCharsetPropB    = g_syscall( CG_R_REGISTERSHADER, "menu/art/font2_prop.tga" );
}



void init_hud( void ) {
	// cgs.media.gfxLogo = g_syscall( CG_R_REGISTERSHADER, "gfx/mdd/rd-mini" );
	cgs.media.gfxAmmo[0] = g_syscall( CG_R_REGISTERSHADER, "icons/iconw_gauntlet" );
	cgs.media.gfxAmmo[1] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_machinegun" );
	cgs.media.gfxAmmo[2] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_shotgun" );
	cgs.media.gfxAmmo[3] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_grenade" );
	cgs.media.gfxAmmo[4] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_rocket" );
	cgs.media.gfxAmmo[5] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_lightning" );
	cgs.media.gfxAmmo[6] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_railgun" );
	cgs.media.gfxAmmo[7] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_plasma" );
	cgs.media.gfxAmmo[8] = g_syscall( CG_R_REGISTERSHADER, "icons/icona_bfg" );

	hud_setup( );
}
