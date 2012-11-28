#include "cg_local.h"
#include "cg_consolecmds.h"



qboolean *CG_ConsoleCommand( void ) {
  char cmdBuffer[256];
	uint32_t argc;

	argc = g_syscall( CG_ARGC );
	g_syscall( CG_ARGV, 0, cmdBuffer, sizeof(cmdBuffer) );

	//g_syscall( CG_PRINT, vaf("^6%s^7\n", cmdBuffer) );
	// TODO: check if the player uses one of our commands

	return qfalse; // not a command
}
