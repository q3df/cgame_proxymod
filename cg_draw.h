#ifndef __CG_DRAW_H__
#define __CG_DRAW_H__



typedef enum {
	STEREO_CENTER,
	STEREO_LEFT,
	STEREO_RIGHT
} stereoFrame_t;



int32_t CG_DrawActiveFrame( int32_t serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
void    CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader );
void    CG_DrawAdjPic( float x, float y, float width, float height, qhandle_t hShader );
void    CG_AdjustFrom640( float *x, float *y, float *w, float *h );
void    convertAdjustedToNative ( float *xAdj, float *yAdj, float *wAdj, float *hAdj );
void    convertNativeToAdjusted ( float *x, float *y, float *w, float *h );
void    drawChar( int32_t x, int32_t y, int32_t width, int32_t height, uint8_t c );
void    CG_DrawText( float x, float y, float sizePx, vec4_t color, uint8_t alignRight, const char *string );
int8_t  getColor( uint8_t color, float opacity, vec4_t c );


#endif // __CG_DRAW_H__
