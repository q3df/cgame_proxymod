#include "cg_local.h"
#include "cg_draw.h"
#include "cg_hud.h"
#include "cg_cvar.h"
#include "cg_utils.h"



static hud_t hud;
static hud_ammo_t ammo;
static hud_jumpDelay_t jump;


void hud_setup( void ) {
	hud_baseSetup( &hud );
	hud_ammoSetup( &ammo );
	hud_jumpDelaySetup( &jump );
}



void hud_update( void ) {
	// TODO: instead of just calling setup
	// TODO: we check which structs require an update
	hud_setup( );
	//hud_jumpDelaySetup( &jump );
}



int8_t hud_baseSetup( hud_t *h ) {
	float hud_opacity=1.0;

	cvar_getFloat( "mdd_hud_opacity", &hud_opacity );

	h->color[0] = 1.0;
	h->color[1] = 1.0;
	h->color[2] = 1.0;
	h->color[3] = hud_opacity;

	return qtrue;
}



void hud_draw( void ) {
	float hud_draw, hud_ammo_draw, hud_jumpDelay_draw;

	cvar_getFloat( "mdd_hud_draw", &hud_draw );
	if( !hud_draw )
		return;

	cvar_getFloat( "mdd_hud_ammo_draw", &hud_ammo_draw );
	cvar_getFloat( "mdd_hud_jumpDelay_draw", &hud_jumpDelay_draw );

	if( hud_ammo_draw )
		hud_ammoDraw( &ammo );

	if( hud_jumpDelay_draw ) {
		hud_jumpDelayControl( &jump );
		hud_jumpDelayDraw( &jump );
	}

	// make sure the last color doesn't leak into defrag's UI
	g_syscall( CG_R_SETCOLOR, colorWhite );
}



/*
 *
 * Setup and Draw BARS
 *
 */

/*
int8_t hud_vBarDraw( float percent, hud_bar_t *bar ) {
	float barLength;

	// sanity checks
	if( percent > 100 ) {
		percent = 100.0;
	}

	if( bar == NULL ) {
		return qfalse;
	}

	bar->value = percent;
	barLength = (bar->width * bar->value) / (100.0 * 2.0);

	hud_boxDraw( bar->xPos, bar->yPos, bar->width, bar->height, bar->colorBackdrop );

	// left half of bar
	g_syscall( CG_R_SETCOLOR, bar->colorBar );
	CG_DrawPic( bar->xPos, bar->yPos, barLength, bar->height, cgs.media.gfxWhiteShader );

	// right half of bar
	g_syscall( CG_R_SETCOLOR, bar->colorBar );
	CG_DrawPic( bar->xPos+bar->width-barLength, bar->yPos, barLength, bar->height, cgs.media.gfxWhiteShader );

	return qtrue;
}
*/

/*
int8_t hud_hBarDraw( float percent, hud_bar_t *bar ) {
	// TODO: implement
	return qtrue;
}
*/


int8_t hud_boxDraw( float x, float y, float w, float h ) {
	// Draw a simple transparent box to put graphs into
	vec4_t backdrop;

	backdrop[0] = hud.color[0];
	backdrop[1] = hud.color[1];
	backdrop[2] = hud.color[2];
	backdrop[3] = hud.color[3];


	g_syscall( CG_R_SETCOLOR, backdrop );
	CG_DrawPic( x, y, w, h, cgs.media.gfxWhiteShader ); // backdrop

	// make border stand out
	backdrop[3] += 0.5;
	if( backdrop[3] > 1.0 ) {
		backdrop[3] = 1.0;
	}

	g_syscall( CG_R_SETCOLOR, backdrop );
	CG_DrawPic( x, y-1, w, 1, cgs.media.gfxWhiteShader );     // North
	CG_DrawPic( x, y+h, w, 1, cgs.media.gfxWhiteShader );     // South
	CG_DrawPic( x+w, y-1, 1, h+2, cgs.media.gfxWhiteShader ); // East
	CG_DrawPic( x-1, y-1, 1, h+2, cgs.media.gfxWhiteShader ); // West

  return qtrue;
}


/*
int8_t hud_vBarSetup( hud_bar_t *bar, float xPosAdj, float yPosAdj, float widthAdj, float heightAdj ) {
	// Position graph on adjusted 640x480 grid
	// Switch to native resolution and draw graph
	// Bar slides in from both sides and hits in the center
	float mdd_hud_opacity;

	cvar_getFloat( "mdd_hud_opacity", &mdd_hud_opacity );

	bar->width  = widthAdj;
	bar->height = heightAdj;
	bar->xPos   = xPosAdj;
	bar->yPos   = yPosAdj;

	bar->colorBackdrop[0] = 1.0;
	bar->colorBackdrop[1] = 1.0;
	bar->colorBackdrop[2] = 1.0;
	bar->colorBackdrop[3] = mdd_hud_opacity;
	bar->colorBar[0] = 0.8;
	bar->colorBar[1] = 0.0;
	bar->colorBar[2] = 1.0;
	bar->colorBar[3] = mdd_hud_opacity;

	// convert adjusted coordinates to native ones
	convertAdjustedToNative( &bar->xPos, &bar->yPos, &bar->width, &bar->height );
	return qtrue;
}
*/


/*
 *
 * Ammo Hud
 *
 */

int8_t hud_ammoSetup( hud_ammo_t *ammoHud ) {
	float mdd_hud_opacity;
	float xPosAdj, yPosAdj, size;

	cvar_getFloat( "mdd_hud_opacity", &mdd_hud_opacity );
	cvar_getFloat( "mdd_hud_ammo_offsetX", &xPosAdj );
	cvar_getFloat( "mdd_hud_ammo_offsetY", &yPosAdj );
	cvar_getFloat( "mdd_hud_ammo_size", &size );

	ammoHud->xPos = xPosAdj;
	ammoHud->yPos = yPosAdj;
	ammoHud->size = size;

	ammoHud->colorText[0] = 1.0;
	ammoHud->colorText[1] = 1.0;
	ammoHud->colorText[2] = 1.0;
	ammoHud->colorText[3] = 1.0;

	ammoHud->colorBackdrop[0] = 0.0;
	ammoHud->colorBackdrop[1] = 0.0;
	ammoHud->colorBackdrop[2] = 0.0;
	ammoHud->colorBackdrop[3] = mdd_hud_opacity;

	convertAdjustedToNative( &ammoHud->xPos, &ammoHud->yPos, NULL, NULL );
	return qtrue;
}



int8_t hud_ammoDraw( hud_ammo_t *ammoHud ) {
	uint32_t y, i;
	playerState_t *ps;
	float size;
	uint16_t hasWeapon;
	uint16_t ammo;

	ps = getPs( );
	size = ammoHud->size;

	// TODO: in case "give all" do not display the hud

	y = ammoHud->yPos;
	for( i=1; i<9; i++ ) {
		ammo = ps->ammo[i+1];
		hasWeapon = ps->stats[STAT_WEAPONS] & (1<<(i+1));

		if( !ammo && !hasWeapon ) {
			continue;
		}

		g_syscall( CG_R_SETCOLOR, ammoHud->colorBackdrop );
		CG_DrawPic( ammoHud->xPos, y, size, size, cgs.media.gfxWhiteShader );
		g_syscall( CG_R_SETCOLOR, colorWhite );

		CG_DrawPic( ammoHud->xPos, y, size, size, cgs.media.gfxAmmo[i] );

		if( !hasWeapon ) {
			// mark weapon as unavailible
			CG_DrawPic( ammoHud->xPos, y, size, size, cgs.media.gfxDeferSymbol );
		}

		CG_DrawText( ammoHud->xPos, y+(size/4), (size/2), ammoHud->colorText, qtrue, vaf("%i", ps->ammo[i+1]) );
		y += size;
	}


	// TODO: color the text of the ammo red in case of low ammo
	// TODO: make textsize cvar dependant
	return qtrue;
}



/*
 *
 * Jump Delay Hud
 *
 */
int8_t hud_jumpDelaySetup( hud_jumpDelay_t *jumpHud ) {
	float xPos, yPos, widthPx, heightPx;
	float textPosX, textPosY, textSize;
	float mdd_hud_opacity;
	float draw;

	cvar_getFloat( "mdd_hud_opacity", &mdd_hud_opacity );
	cvar_getFloat( "mdd_hud_jumpDelay_draw",         &draw );
	cvar_getFloat( "mdd_hud_jumpDelay_graphWidth",   &widthPx );
	cvar_getFloat( "mdd_hud_jumpDelay_graphHeight",  &heightPx );
	cvar_getFloat( "mdd_hud_jumpDelay_graphOffsetX", &xPos );
	cvar_getFloat( "mdd_hud_jumpDelay_graphOffsetY", &yPos );
	cvar_getFloat( "mdd_hud_jumpDelay_textOffsetX",  &textPosX );
	cvar_getFloat( "mdd_hud_jumpDelay_textOffsetY",  &textPosY );
	cvar_getFloat( "mdd_hud_jumpDelay_textSize",     &textSize );

	convertAdjustedToNative( &xPos, &yPos, &textPosX, &textPosY );

	jumpHud->mode = draw; // 0=off, 1=text, 2=graph, 3=text and graph

	jumpHud->xPos = xPos;
	jumpHud->yPos = yPos;
	jumpHud->width = widthPx;
	jumpHud->height = heightPx;

	jumpHud->preJumpColor[0] = 0.0;
	jumpHud->preJumpColor[1] = 0.0;
	jumpHud->preJumpColor[2] = 1.0;
	jumpHud->preJumpColor[3] = mdd_hud_opacity +0.5;
	if( jumpHud->preJumpColor[3] > 1.0 )
		jumpHud->preJumpColor[3] = 1.0;

	jumpHud->postJumpColor[0] = 1.0;
	jumpHud->postJumpColor[1] = 0.0;
	jumpHud->postJumpColor[2] = 0.0;
	jumpHud->postJumpColor[3] = mdd_hud_opacity +0.5;
	if( jumpHud->postJumpColor[3] > 1.0 )
		jumpHud->postJumpColor[3] = 1.0;

	jumpHud->textColor[0] = 1.0;
	jumpHud->textColor[1] = 1.0;
	jumpHud->textColor[2] = 1.0;
	jumpHud->textColor[3] = 1.0;

	jumpHud->textPosX = textPosX;
	jumpHud->textPosY = textPosY;
	jumpHud->textSize = textSize;

	return qtrue;
}


int8_t hud_jumpDelayDraw( hud_jumpDelay_t *jumpHud ) {
	const float rangeMs=300;
	float middle, upHeight, downHeight, barUp, barDown;

	middle = jumpHud->yPos + (jumpHud->height / 2.0);
	barUp = jumpHud->postDelay;
	barDown = jumpHud->preDelay;

	// clamp values
	if( jumpHud->postDelay > rangeMs )
		barUp = rangeMs;

	if( jumpHud->preDelay > rangeMs )
		barDown = rangeMs;

	upHeight = (jumpHud->height/2) * (barUp / rangeMs);
	downHeight = (jumpHud->height/2) * (barDown / rangeMs);

	// draw graph
	if(jumpHud->mode & 2 ) {
		hud_boxDraw( jumpHud->xPos, jumpHud->yPos, jumpHud->width, jumpHud->height );

		g_syscall( CG_R_SETCOLOR, jumpHud->preJumpColor );
		CG_DrawPic( jumpHud->xPos, middle , jumpHud->width, downHeight, cgs.media.gfxWhiteShader );

		g_syscall( CG_R_SETCOLOR, jumpHud->postJumpColor );
		CG_DrawPic( jumpHud->xPos, (middle-upHeight), jumpHud->width, upHeight, cgs.media.gfxWhiteShader );
	}
	// draw text next to it
	if( jumpHud->mode & 1 ) {
 		CG_DrawText( jumpHud->textPosX, jumpHud->textPosY, jumpHud->textSize, jumpHud->textColor, qfalse, vaf("%i ms", jumpHud->fullDelay) );
	}

	return qtrue;
}



int8_t hud_jumpDelayControl( hud_jumpDelay_t *jumpHud ) {
	int8_t inAir=0, jump=0, state=0, lastState=0;
	uint32_t now;
	playerState_t *ps;
	/*
	 * To draw this hud we have to make a little state machine
	 *
	 * AIR_NOJUMP:        The player is midair, not holding the jump button
	 * AIR_JUMP:          The player is midair, holding jump button
	 * GROUND_JUMP:       The player is on the ground, holding jump button
	 * GROUND_NOJUMP:     The player is on the ground, not holding jump button
	 * AIR_JUMPNORELEASE: The player is midair, without releasing the jump button
	 */

	now = getSnap( )->serverTime;
	ps = getPs( );
	inAir = isInAir( ps );
	jump = isJumping( ps );
	lastState = jumpHud->lastState;



	// determine current state
	switch( lastState ) {
		case AIR_JUMP:
		case AIR_NOJUMP:
			if( inAir ) {
				if( jump )
					state = AIR_JUMP;
				else
					state = AIR_NOJUMP;
			}
			else {
				if( jump )
					state = GROUND_JUMP;
				else
					state = GROUND_NOJUMP;
			}
		break;

		// edge case at end of cycle
		case GROUND_NOJUMP:
		case GROUND_JUMP:
		case AIR_JUMPNORELEASE:
			if( inAir ) {
				if( jump )
					state = AIR_JUMPNORELEASE;
				else
					state = AIR_NOJUMP;
			}
			else {
				if( jump )
					state = GROUND_JUMP;
				else
					state = GROUND_NOJUMP;
			}
			break;

		default:
			state = GROUND_NOJUMP;
		break;
	}


	// act on current state
	switch( state ) {
		case AIR_NOJUMP:
			jumpHud->fullDelay = jumpHud->postDelay + jumpHud->preDelay;
			if( lastState == AIR_JUMP ) {
				jumpHud->preDelay  = 0;
				jumpHud->postDelay = 0;
			}
			// we spend the most time in this state
			// that is why here we show the last jump stats
		break;

		case AIR_JUMP:
			if( lastState == AIR_NOJUMP ) {
				jumpHud->t_jumpPreGround = now;
			}
			jumpHud->preDelay = now - jumpHud->t_jumpPreGround; // ms
		break;

		case GROUND_JUMP:
			if( lastState == AIR_JUMP ) {
				jumpHud->t_groundTouch = now;
			}
				jumpHud->postDelay = 0;
		break;

		case GROUND_NOJUMP:
			jumpHud->t_jumpPreGround = now; // display 0 on 2nd jump CJ
			jumpHud->t_groundTouch = now;
			jumpHud->preDelay = 0;
			jumpHud->postDelay = 0;
		break;

		case AIR_JUMPNORELEASE:
			jumpHud->postDelay = now - jumpHud->t_groundTouch; // ms
		break;

		default:
		break;
	}

//	g_syscall( CG_PRINT, vaf("%u\n", state));
	jumpHud->lastState = state;

	return qtrue;
}

