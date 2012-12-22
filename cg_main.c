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
#include "cg_local.h"
#include "cg_main.h"
#include "cg_consolecmds.h"
#include "cg_draw.h"

cgs_t cgs;


/* CLIENT to VM */
__DLLEXPORT__ int32_t vmMain( int32_t cmd, int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8, int32_t arg9, int32_t arg10, int32_t arg11 ) {
	int32_t ret;

	/* PRE CALL */
	switch( cmd ) {

		case CG_INIT: // void CG_Init( int32_t serverMessageNum, int32_t serverCommandSequence, int32_t clientNum )
			cg_init( cmd, arg2 );
		break;

		case CG_CONSOLE_COMMAND: // qboolean (*CG_ConsoleCommand)( void );
			CG_ConsoleCommand( );
		break;

		case CG_DRAW_ACTIVE_FRAME: // void (*CG_DrawActiveFrame)( int32_t serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
			cgs.time = arg0; // servertime
		break;

		case CG_CROSSHAIR_PLAYER: // int32_t (*CG_CrosshairPlayer)( void );
		break;

		case CG_LAST_ATTACKER: // int32_t (*CG_LastAttacker)( void );
		break;

		case CG_KEY_EVENT: // void  (*CG_KeyEvent)( int32_t key, qboolean down );
		break;

		case CG_MOUSE_EVENT: // void  (*CG_MouseEvent)( int32_t dx, int32_t dy );
		break;

		case CG_EVENT_HANDLING: // void (*CG_EventHandling)(int32_t type);
		break;

		case CG_SHUTDOWN: // void (*CG_Shutdown)( void );
		break;

		case -1:
			setVMPtr( arg0 );
			return 0;
		break;
	}


	/* call vmMain() in the VM (defrag) */
	ret = callVM(cmd, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);


	/* POST CALL */
	switch(cmd) {
		case CG_INIT: // void CG_Init( int32_t serverMessageNum, int32_t serverCommandSequence, int32_t clientNum )
		break;

		case CG_CONSOLE_COMMAND: // qboolean (*CG_ConsoleCommand)( void );
		break;

		case CG_DRAW_ACTIVE_FRAME: // void (*CG_DrawActiveFrame)( int32_t serverTime, stereoFrame_t stereoView, qboolean demoPlayback )
			CG_DrawActiveFrame( arg0, arg1, arg2 );
		break;

		case CG_CROSSHAIR_PLAYER: // int32_t (*CG_CrosshairPlayer)( void )
		break;

		case CG_LAST_ATTACKER: // int32_t (*CG_LastAttacker)( void );
		break;

		case CG_KEY_EVENT: // void (*CG_KeyEvent)( int32_t key, qboolean down )
		break;

		case CG_MOUSE_EVENT: // void (*CG_MouseEvent)( int32_t dx, int32_t dy )
		break;

		case CG_EVENT_HANDLING: // void (*CG_EventHandling)(int32_t type)
		break;

		case CG_SHUTDOWN: // void (*CG_Shutdown)( void )
			callVM_Destroy();
		break;
	}

	return ret;
}
