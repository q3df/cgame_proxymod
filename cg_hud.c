#include "cg_local.h"
#include "cg_draw.h"
#include "cg_hud.h"



void hud_draw( void ) {
	hud_bar_t x;

	x = hud_vBarSetup( 230, 400, 200, 20 );
	hud_vBarDraw( 100.0, x );
}



int8_t hud_vBarDraw( float percent, hud_bar_t bar ) {
	float barLength;

	bar.value = percent;
	barLength = (bar.width * bar.value) / (100.0 * 2.0);

	hud_boxDraw( bar.xPos, bar.yPos, bar.width, bar.height, bar.colorBackdrop );

	// left half of bar
	g_syscall( CG_R_SETCOLOR, bar.colorBar );
	CG_DrawPic( bar.xPos, bar.yPos, barLength, bar.height, cgs.media.gfxWhiteShader );

	// right half of bar
	g_syscall( CG_R_SETCOLOR, bar.colorBar );
	CG_DrawPic( bar.xPos+bar.width-barLength, bar.yPos, barLength, bar.height, cgs.media.gfxWhiteShader );

	return 0;
}



int8_t hud_hBarDraw( float percent, hud_bar_t bar ) {
	return 0;
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

  return 0;
}



hud_bar_t hud_vBarSetup( float xPosAdj, float yPosAdj, float widthAdj, float heightAdj ) {
	// Position graph on adjusted 640x480 grid
	// Switch to native resolution and draw graph
	// Bar slides in from both sides and hits in the center
	hud_bar_t tmp;

	tmp.width  = widthAdj;
	tmp.height = heightAdj;
	tmp.xPos   = xPosAdj;
	tmp.yPos   = yPosAdj;

	tmp.colorBackdrop[0] = 1.0;
	tmp.colorBackdrop[1] = 1.0;
	tmp.colorBackdrop[2] = 1.0;
	tmp.colorBackdrop[3] = 0.5;
	tmp.colorBar[0] = 0.8;
	tmp.colorBar[1] = 0.0;
	tmp.colorBar[2] = 1.0;
	tmp.colorBar[3] = 0.8;

	// convert adjusted coordinates to native ones
	convertAdjustedToNative( &tmp.xPos, &tmp.yPos, &tmp.width, &tmp.height );
	return tmp;
}
