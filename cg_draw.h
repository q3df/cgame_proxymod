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


#endif // __CG_DRAW_H__
