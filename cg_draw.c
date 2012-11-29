#include "cg_local.h"
#include "cg_draw.h"



int PASSFLOAT( float x ) {
	float floatTemp;
	floatTemp = x;
	return *(int *)&floatTemp;
}



int32_t CG_DrawActiveFrame( int32_t serverTime, stereoFrame_t stereoView, qboolean demoPlayback ) {
	CG_DrawAdjPic( 640-210, 10, 200, 200, cgs.media.gfxLogo );
	return 0;
}



void CG_DrawAdjPic( float x, float y, float width, float height, qhandle_t hShader ) {
	CG_AdjustFrom640( &x, &y, &width, &height );
	g_syscall( CG_R_DRAWSTRETCHPIC, PASSFLOAT(x), PASSFLOAT(y), PASSFLOAT(width), PASSFLOAT(height), PASSFLOAT(0), PASSFLOAT(0), PASSFLOAT(1), PASSFLOAT(1), hShader );
}



void CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader ) {
	g_syscall( CG_R_DRAWSTRETCHPIC, x, y, width, height, 0, 0, 1, 1, hShader );
}




/*
================
CG_AdjustFrom640

Adjusted for resolution and screen aspect ratio
================
*/
void CG_AdjustFrom640( float *x, float *y, float *w, float *h ) {
#if 0
	// adjust for wide screens
	if ( cgs.glconfig.vidWidth * 480 > cgs.glconfig.vidHeight * 640 ) {
		*x += 0.5 * ( cgs.glconfig.vidWidth - ( cgs.glconfig.vidHeight * 640 / 480 ) );
	}
#endif
	// scale for screen sizes
	*x *= cgs.screenXScale;
	*y *= cgs.screenYScale;
	*w *= cgs.screenXScale;
	*h *= cgs.screenYScale;
}
