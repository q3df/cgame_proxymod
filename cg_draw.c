#include "cg_local.h"
#include "cg_hud.h"
#include "cg_draw.h"




// DELME
void draw_compass( void );



int PASSFLOAT( float x ) {
	float floatTemp;
	floatTemp = x;
	return *(int *)&floatTemp;
}



int32_t CG_DrawActiveFrame( int32_t serverTime, stereoFrame_t stereoView, qboolean demoPlayback ) {
	hud_draw( );
	return 0;
}



void CG_DrawAdjPic( float x, float y, float width, float height, qhandle_t hShader ) {
	CG_AdjustFrom640( &x, &y, &width, &height );
	g_syscall( CG_R_DRAWSTRETCHPIC, PASSFLOAT(x), PASSFLOAT(y), PASSFLOAT(width), PASSFLOAT(height), PASSFLOAT(0), PASSFLOAT(0), PASSFLOAT(1), PASSFLOAT(1), hShader );
}



void CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader ) {
	g_syscall( CG_R_DRAWSTRETCHPIC, PASSFLOAT(x), PASSFLOAT(y), PASSFLOAT(width), PASSFLOAT(height), PASSFLOAT(0), PASSFLOAT(0), PASSFLOAT(1), PASSFLOAT(1), hShader );
}






/*
 *
 * HUD
 *
 */



float yawToY( float yaw ) {
	float fov;

	fov = 130.0;
	//	fov = g_syscall( );
	return 0.0;
	// TODO: MAGIC TRANSFORMATION!
}



float pitchToX ( float pitch ) {
	return 0.0;
	// TODO: MAGIC TRANSFORMATION!
}



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


void convertAdjustedToNative ( float *xAdj, float *yAdj, float *wAdj, float *hAdj ) {
	*xAdj = (((float)cgs.glconfig.vidWidth)  / 640.0) * (*xAdj);
	*yAdj = (((float)cgs.glconfig.vidHeight) / 480.0) * (*yAdj);

	*wAdj = (((float)cgs.glconfig.vidWidth)  / 640.0) * (*wAdj);
	*hAdj = (((float)cgs.glconfig.vidHeight) / 480.0) * (*hAdj);
}



void convertNativeToAdjusted ( float *x, float *y, float *w, float *h ) {
	;// TODO: implement
}
