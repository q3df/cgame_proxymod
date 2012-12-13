#include "cg_local.h"
#include "cg_draw.h"
#include "cg_hud.h"
#include "cg_cvar.h"
#include "cg_utils.h"



//static hud_bar_t bar;
static hud_ammo_t ammo;



void hud_setup( void ) {
//	hud_vBarSetup( &bar, 230, 400, 200, 20 );
	hud_ammoSetup( );
}



void hud_update( void ) {
	// TODO: check if this call is required
	hud_ammoSetup( );
}



void hud_draw( void ) {
	float hud_draw, hud_ammo_draw;

	cvar_getFloat( "mdd_hud_draw", &hud_draw );
	if( !hud_draw )
		return;

	cvar_getFloat( "mdd_hud_ammo_draw", &hud_ammo_draw );
//	cvar_getFloat( "cg_fov", &cg_fov );

//	hud_vBarDraw( cg_fov, &bar );

	if( hud_ammo_draw )
		hud_ammoDraw( &ammo );
}



/*
 *
 * Setup and Draw BARS
 *
 */
int8_t hud_vBarDraw( float percent, hud_bar_t *bar ) {
	float barLength;

	// sanity checks
	if( percent > 100 ) {
		percent = 100.0;
	}

	if( bar == NULL ) {
		return qfalse;
	}

	bar->value = percent;
	barLength = (bar->width * bar->value) / (100.0 * 2.0);

	hud_boxDraw( bar->xPos, bar->yPos, bar->width, bar->height, bar->colorBackdrop );

	// left half of bar
	g_syscall( CG_R_SETCOLOR, bar->colorBar );
	CG_DrawPic( bar->xPos, bar->yPos, barLength, bar->height, cgs.media.gfxWhiteShader );

	// right half of bar
	g_syscall( CG_R_SETCOLOR, bar->colorBar );
	CG_DrawPic( bar->xPos+bar->width-barLength, bar->yPos, barLength, bar->height, cgs.media.gfxWhiteShader );

	return qtrue;
}



int8_t hud_hBarDraw( float percent, hud_bar_t *bar ) {
	// TODO: implement
	return qtrue;
}



int8_t hud_boxDraw( float x, float y, float w, float h, vec4_t color ) {
	// Draw a simple 50% transparent box to put graphs into
	vec4_t backdrop;
	backdrop[0] = color[0];
	backdrop[1] = color[1];
	backdrop[2] = color[2];
	backdrop[3] = color[3];

	g_syscall( CG_R_SETCOLOR, backdrop );
	CG_DrawPic( x, y, w, h, cgs.media.gfxWhiteShader ); // backdrop

	// make border stand out
	backdrop[3] += 0.5;
	if( backdrop[3] > 1.0 ) {
		backdrop[3] = 1.0;
	}

	g_syscall( CG_R_SETCOLOR, backdrop );
	CG_DrawPic( x, y-1, w, 1, cgs.media.gfxWhiteShader );     // North
	CG_DrawPic( x, y+h, w, 1, cgs.media.gfxWhiteShader );     // South
	CG_DrawPic( x+w, y-1, 1, h+2, cgs.media.gfxWhiteShader ); // East
	CG_DrawPic( x-1, y-1, 1, h+2, cgs.media.gfxWhiteShader ); // West

  return qtrue;
}



int8_t hud_vBarSetup( hud_bar_t *bar, float xPosAdj, float yPosAdj, float widthAdj, float heightAdj ) {
	// Position graph on adjusted 640x480 grid
	// Switch to native resolution and draw graph
	// Bar slides in from both sides and hits in the center
	float mdd_hud_opacity;

	cvar_getFloat( "mdd_hud_opacity", &mdd_hud_opacity );

	bar->width  = widthAdj;
	bar->height = heightAdj;
	bar->xPos   = xPosAdj;
	bar->yPos   = yPosAdj;

	bar->colorBackdrop[0] = 1.0;
	bar->colorBackdrop[1] = 1.0;
	bar->colorBackdrop[2] = 1.0;
	bar->colorBackdrop[3] = mdd_hud_opacity;
	bar->colorBar[0] = 0.8;
	bar->colorBar[1] = 0.0;
	bar->colorBar[2] = 1.0;
	bar->colorBar[3] = mdd_hud_opacity;

	// convert adjusted coordinates to native ones
	convertAdjustedToNative( &bar->xPos, &bar->yPos, &bar->width, &bar->height );
	return qtrue;
}



/*
 *
 * Setup and Draw AMMO HUD
 *
 */

int8_t hud_ammoSetup( void ) {
	float mdd_hud_opacity;
	float xPosAdj, yPosAdj, size;

	cvar_getFloat( "mdd_hud_opacity", &mdd_hud_opacity );
	cvar_getFloat( "mdd_hud_ammo_offsetX", &xPosAdj );
	cvar_getFloat( "mdd_hud_ammo_offsetY", &yPosAdj );
	cvar_getFloat( "mdd_hud_ammo_size", &size );

	ammo.xPos = xPosAdj;
	ammo.yPos = yPosAdj;
	ammo.size = size;

	ammo.textColor[0] = 1.0;
	ammo.textColor[1] = 1.0;
	ammo.textColor[2] = 1.0;
	ammo.textColor[3] = mdd_hud_opacity;

	convertAdjustedToNative( &ammo.xPos, &ammo.yPos, NULL, NULL );
	return qtrue;
}



int8_t hud_ammoDraw( hud_ammo_t *hud ) {
	uint32_t y, i;
	playerState_t *ps;
	float size;
	uint16_t hasWeapon;
	uint16_t ammo;

	ps = getPs( );
	size = hud->size;

	// TODO: display block sign in case ammo without weapon

	y = hud->yPos;
	for( i=1; i<9; i++ ) {
		ammo = ps->ammo[i+1];
		hasWeapon = ps->stats[STAT_WEAPONS] & (1<<(i+1));

		if( !ammo && !hasWeapon ) {
			continue;
		}

		CG_DrawPic( hud->xPos, y, size, size, cgs.media.gfxAmmo[i] );

		if( !hasWeapon ) {
			// mark weapon as unavailible
			CG_DrawPic( hud->xPos, y, size, size, cgs.media.gfxDeferSymbol );
		}

		CG_DrawText( hud->xPos, y+(size/4), (size/2), hud->textColor, qtrue, vaf("%i", ps->ammo[i+1]) );
		y += size;
	}


	// mdd_hud_ammo_weapons is a bitfield that contains the weapons that should be displayed

	// TODO: color the text of the ammo red in case of low ammo
	// TODO: make textsize cvar dependant
	return qtrue;
}
