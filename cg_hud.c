#include "cg_local.h"
#include "cg_draw.h"
#include "cg_hud.h"
#include "cg_cvar.h"



void hud_draw( void ) {
	int32_t cg_fov;
	hud_bar_t x;

	hud_vBarSetup( &x, 230, 400, 200, 20 );

	cvar_getInt( "cg_fov", &cg_fov );
	hud_vBarDraw( cg_fov, &x );
}



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

	bar->width  = widthAdj;
	bar->height = heightAdj;
	bar->xPos   = xPosAdj;
	bar->yPos   = yPosAdj;

	bar->colorBackdrop[0] = 1.0;
	bar->colorBackdrop[1] = 1.0;
	bar->colorBackdrop[2] = 1.0;
	bar->colorBackdrop[3] = 0.5;
	bar->colorBar[0] = 0.8;
	bar->colorBar[1] = 0.0;
	bar->colorBar[2] = 1.0;
	bar->colorBar[3] = 0.8;

	// convert adjusted coordinates to native ones
	convertAdjustedToNative( &bar->xPos, &bar->yPos, &bar->width, &bar->height );
	return qtrue;
}
