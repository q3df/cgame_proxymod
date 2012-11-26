#ifndef __CG_MAIN_H__
#define __CG_MAIN_H__



typedef enum {
	CG_INIT,
	//	void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum )
	// called when the level loads or when the renderer is restarted
	// all media should be registered at this time
	// cgame will display loading status by calling SCR_Update, which
	// will call CG_DrawInformation during the loading process
	// reliableCommandSequence will be 0 on fresh loads, but higher for
	// demos, tourney restarts, or vid_restarts

	CG_SHUTDOWN,
	//	void (*CG_Shutdown)( void );
	// oportunity to flush and close any open files

	CG_CONSOLE_COMMAND,
	//	qboolean (*CG_ConsoleCommand)( void );
	// a console command has been issued locally that is not recognized by the
	// main game system.
	// use Cmd_Argc() / Cmd_Argv() to read the command, return qfalse if the
	// command is not known to the game

	CG_DRAW_ACTIVE_FRAME,
	//	void (*CG_DrawActiveFrame)( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
	// Generates and draws a game scene and status information at the given time.
	// If demoPlayback is set, local movement prediction will not be enabled

	CG_CROSSHAIR_PLAYER,
	//	int (*CG_CrosshairPlayer)( void );

	CG_LAST_ATTACKER,
	//	int (*CG_LastAttacker)( void );

	CG_KEY_EVENT,
	//	void	(*CG_KeyEvent)( int key, qboolean down );

	CG_MOUSE_EVENT,
	//	void	(*CG_MouseEvent)( int dx, int dy );

	CG_EVENT_HANDLING
	//	void (*CG_EventHandling)(int type);
} cgameExport_t;

int cg_init( int cmd, int clientNum );



#endif // __CG_MAIN_H__
