#include "cg_local.h"
#include "cg_consolecmds.h"



qboolean *CG_ConsoleCommand( void ) {
/*
  const char  *cmd;
  int   i;

  cmd = CG_Argv(0);

  for ( i = 0 ; i < ARRAY_LEN( commands ) ; i++ ) {
    if ( !Q_stricmp( cmd, commands[i].cmd ) ) {
      commands[i].function();
      return qtrue;
    }
  }

  return qfalse;
*/


	return qfalse; // not a command
}
