#ifndef __CG_DRAW_H__
#define __CG_DRAW_H__



void CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader );
void CG_DrawAdjPic( float x, float y, float width, float height, qhandle_t hShader );
void CG_AdjustFrom640( float *x, float *y, float *w, float *h );



#endif // __CG_DRAW_H__
