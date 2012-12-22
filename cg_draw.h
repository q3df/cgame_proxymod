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
