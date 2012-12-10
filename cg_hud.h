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



typedef struct {
	uint32_t weapons;
	float xPos;
	float yPos;
	vec4_t textColor;
	uint8_t ammo[16];
} hud_ammo_t;



void hud_setup( void );
void hud_draw( void );
int8_t hud_vBarSetup( hud_bar_t *bar, float xPosAdj, float yPosAdj, float widthAdj, float heightAdj );
int8_t hud_vBarDraw( float percent, hud_bar_t *bar );
int8_t hud_hBarDraw( float percent, hud_bar_t *bar );

int8_t hud_ammoSetup( void );
int8_t hud_ammoDraw( hud_ammo_t *hud );

// helper
int8_t hud_boxDraw( float x, float y, float w, float h, vec4_t color );



#endif // __CG_HUD_H__
