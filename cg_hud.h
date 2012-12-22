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
#ifndef __CG_HUD_H__
#define __CG_HUD_H__



typedef struct {
	vec4_t color;
} hud_t;



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
	float xPos;
	float yPos;
	float size;
	uint8_t ammo[16];
	vec4_t colorText;
	vec4_t colorBackdrop;
} hud_ammo_t;



typedef struct {
	float xPos;
	float yPos;
	float textPosX;
	float textPosY;
	float textSize;
	float width;
	float height;

	uint32_t mode;

	// timestamps for computation
	uint32_t t_jumpPreGround;
	uint32_t t_nojumpPostGround;
	uint32_t t_groundTouch;

	// state machine
	uint8_t  lastState;

	// draw data
	int32_t postDelay;
	int32_t preDelay;
	int32_t fullDelay;

	vec4_t postJumpColor;
	vec4_t preJumpColor;
	vec4_t textColor;
} hud_jumpDelay_t;



enum {
	AIR_NOJUMP,
	AIR_JUMP,
	GROUND_JUMP,
	GROUND_NOJUMP,
	AIR_JUMPNORELEASE
};


void hud_setup( void );
void hud_update( void );
int8_t hud_baseSetup( hud_t *h );
void hud_draw( void );
int8_t hud_vBarSetup( hud_bar_t *bar, float xPosAdj, float yPosAdj, float widthAdj, float heightAdj );
int8_t hud_vBarDraw( float percent, hud_bar_t *bar );
int8_t hud_hBarDraw( float percent, hud_bar_t *bar );

int8_t hud_ammoSetup( hud_ammo_t *hud );
int8_t hud_ammoDraw( hud_ammo_t *hud );

int8_t hud_jumpDelaySetup( hud_jumpDelay_t *jumpHud );
int8_t hud_jumpDelayControl( hud_jumpDelay_t *jumpHud );
int8_t hud_jumpDelayDraw( hud_jumpDelay_t *jumpHud );

// helper
int8_t hud_boxDraw( float x, float y, float w, float h );



#endif // __CG_HUD_H__
