#include "cg_local.h"
#include "cg_main.h"

cgs_t cgs;


/* CLIENT to VM */
__DLLEXPORT__ int vmMain( int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11 ) {
	int ret;

	/* PRE CALL */
	switch( cmd ) {

		case CG_INIT: // void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum )
			cg_init( cmd, arg2 );
		break;

		case CG_CONSOLE_COMMAND: // qboolean (*CG_ConsoleCommand)( void );
			CG_ConsoleCommand( );
		break;

		case CG_DRAW_ACTIVE_FRAME: // void (*CG_DrawActiveFrame)( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
		break;

		case CG_CROSSHAIR_PLAYER: // int (*CG_CrosshairPlayer)( void );
		break;

		case CG_LAST_ATTACKER: // int (*CG_LastAttacker)( void );
		break;

		case CG_KEY_EVENT: // void  (*CG_KeyEvent)( int key, qboolean down );
		break;

		case CG_MOUSE_EVENT: // void  (*CG_MouseEvent)( int dx, int dy );
		break;

		case CG_EVENT_HANDLING: // void (*CG_EventHandling)(int type);
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
		case CG_INIT: // void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum )
		break;

		case CG_CONSOLE_COMMAND: // qboolean (*CG_ConsoleCommand)( void );
		break;

		case CG_DRAW_ACTIVE_FRAME: // void (*CG_DrawActiveFrame)( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback )
		break;

		case CG_CROSSHAIR_PLAYER: // int (*CG_CrosshairPlayer)( void )
		break;

		case CG_LAST_ATTACKER: // int (*CG_LastAttacker)( void );
		break;

		case CG_KEY_EVENT: // void (*CG_KeyEvent)( int key, qboolean down )
		break;

		case CG_MOUSE_EVENT: // void (*CG_MouseEvent)( int dx, int dy )
		break;

		case CG_EVENT_HANDLING: // void (*CG_EventHandling)(int type)
		break;

		case CG_SHUTDOWN: // void (*CG_Shutdown)( void )
			callVM_Destroy();
		break;
	}

	return ret;
}
