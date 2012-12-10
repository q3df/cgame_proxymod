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
	if( xAdj != NULL )
		*xAdj = ((cgs.glconfig.vidWidth)  / 640.0) * (*xAdj);

	if( yAdj != NULL )
		*yAdj = ((cgs.glconfig.vidHeight) / 480.0) * (*yAdj);

	if( wAdj != NULL )
		*wAdj = ((cgs.glconfig.vidWidth)  / 640.0) * (*wAdj);

	if( hAdj != NULL )
		*hAdj = ((cgs.glconfig.vidHeight) / 480.0) * (*hAdj);

	return;
}



void convertNativeToAdjusted ( float *x, float *y, float *w, float *h ) {
	;// TODO: implement
}



void drawChar( int32_t x, int32_t y, int32_t width, int32_t height, uint8_t c ) {
	int32_t row, col;
	float frow, fcol;
	float size;

	row = c>>4;
	col = c&15;

	frow = row*0.0625;
	fcol = col*0.0625;
	size = 0.0625;

	g_syscall( CG_R_DRAWSTRETCHPIC,
		PASSFLOAT(x), PASSFLOAT(y), PASSFLOAT(width), PASSFLOAT(height),
		PASSFLOAT(fcol), PASSFLOAT(frow), PASSFLOAT(fcol+size), PASSFLOAT(frow+size),
		cgs.media.gfxCharsetShader
	);
}



void CG_DrawText( float x, float y, float sizePx, vec4_t color, uint8_t alignRight, const char *string ) {
	// TODO: color
	const char *s;
	float tmpX;
	uint32_t len;
	int32_t i;

	if( string == NULL )
		return;

	s = string;
	tmpX = x;

	if( alignRight ) {
		len = strlen( string );
		for( i=len-1; i>=0; i-- ) {
			tmpX -= sizePx;
			drawChar( tmpX, y, sizePx, sizePx, s[i] );
		}
	}
	else {
		// align left
		while( *s != '\0' ) {
			drawChar( tmpX, y, sizePx, sizePx, *s );
			s++;
			tmpX += sizePx;
		}
	}
}
