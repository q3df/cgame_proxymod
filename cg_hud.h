#ifndef __CG_HUD_H__
#define __CG_HUD_H__


typedef struct {
	float width;
	float height;
	float xPos;
	float yPos;
	vec4_t colorBar;
	vec4_t colorBackdrop;
	float value;
} hud_bar_t;



void hud_draw( void );
int8_t hud_vBarSetup( hud_bar_t *bar, float xPosAdj, float yPosAdj, float widthAdj, float heightAdj );
int8_t hud_vBarDraw( float percent, hud_bar_t *bar );
int8_t hud_hBarDraw( float percent, hud_bar_t *bar );

// helper
int8_t hud_boxDraw( float x, float y, float w, float h, vec4_t color );


#endif // __CG_HUD_H__
