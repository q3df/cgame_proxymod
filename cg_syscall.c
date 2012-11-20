#include "cg_local.h"

//handling syscalls from QVM (passing them to engine)
//this adds the base VM address to a given value
#define add(x)    ((x) ? (void*)((x) + (int)memoryBase) : NULL)
//this subtracts the base VM address from a given value
#define sub(x)    ((x) ? (void*)((x) - (int)memoryBase) : NULL)
//this gets an argument value
#define arg(x)    (args[(x)])
//this adds the base VM address to an argument value
#define ptr(x)    (add(arg(x)))

#define _ptr(x)   (add(x)) // ???

int QDECL VM_SysCalls(byte *memoryBase, int cmd, int *args) {

	switch( cmd ) {
	case CG_PRINT: // void trap_Printf( const char *fmt )
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_ERROR: // void trap_Error( const char *fmt )
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_MILLISECONDS: // int trap_Milliseconds( void )
		return g_syscall( cmd );

	case CG_ARGC: // int trap_Argc( void )
		return g_syscall(cmd);

	case CG_ARGV: // void trap_Argv( int n, char *buffer, int bufferLength )
		g_syscall( cmd, arg(0), ptr(1), arg(2) );
		return 0;

	case CG_ARGS:
		g_syscall( cmd, ptr(0), arg(1) );
		return 0;

	case CG_FS_FOPENFILE: // int   trap_FS_FOpenFile( const char *qpath, fileHandle_t *f, fsMode_t mode )
		return g_syscall( cmd, ptr(0), ptr(1), arg(2) );

	case CG_FS_READ: // void  trap_FS_Read( void *buffer, int len, fileHandle_t f )
		g_syscall( cmd, ptr(0), arg(1), arg(2) );
		return 0;

	case CG_FS_WRITE: // void  trap_FS_Write( const void *buffer, int len, fileHandle_t f )
		g_syscall( cmd, ptr(0), arg(1), arg(2) );
		return 0;

	case CG_FS_FCLOSEFILE: // void  trap_FS_FCloseFile( fileHandle_t f )
		g_syscall( cmd, arg(0) );
		return 0;

	case CG_FS_SEEK: // int trap_FS_Seek( fileHandle_t f, long offset, int origin )
		return g_syscall( cmd, arg(0), arg(1), arg(2) );

	case CG_SENDCONSOLECOMMAND: // void  trap_SendConsoleCommand( int exec_when, const char *text )
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_CVAR_REGISTER: // void  trap_Cvar_Register( vmCvar_t *cvar, const char *var_name, const char *value, int flags )
		g_syscall( cmd, ptr(0), ptr(1), ptr(2), arg(3) );
		return 0;

	case CG_CVAR_UPDATE: // void  trap_Cvar_Update( vmCvar_t *cvar )
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_CVAR_SET: // void trap_Cvar_Set( const char *var_name, const char *value )
		g_syscall( cmd, ptr(0), ptr(1) );
		return 0;

	case CG_CVAR_VARIABLESTRINGBUFFER: // void trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize )
		g_syscall( cmd, ptr(0), ptr(1), arg(2) );
		return 0;

	case CG_ADDCOMMAND: // void CL_AddCgameCommand( const char *cmdName )
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_REMOVECOMMAND: 
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_SENDCLIENTCOMMAND:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_UPDATESCREEN:
		g_syscall( cmd );
		return 0;
	case CG_CM_LOADMAP:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_CM_NUMINLINEMODELS:
		return g_syscall( cmd );
	case CG_CM_INLINEMODEL:
		return g_syscall( cmd, arg(0) );
	case CG_CM_TEMPBOXMODEL:
		return g_syscall( cmd, ptr(0), ptr(1) );
	case CG_CM_TEMPCAPSULEMODEL:
		return g_syscall( cmd, ptr(0), ptr(1) );
	case CG_CM_POINTCONTENTS:
		return g_syscall( cmd, ptr(0), arg(1) );
	case CG_CM_TRANSFORMEDPOINTCONTENTS:
		return g_syscall( cmd, ptr(0), arg(1), ptr(2), ptr(3) );
	case CG_CM_BOXTRACE:
		g_syscall( cmd, ptr(0), ptr(1), ptr(2), ptr(3), ptr(4), arg(5), arg(6));
		return 0;
	case CG_CM_CAPSULETRACE:
		g_syscall( cmd, ptr(0), ptr(1), ptr(2), ptr(3), ptr(4), arg(5), arg(6));
		return 0;
	case CG_CM_TRANSFORMEDBOXTRACE:
		g_syscall( cmd, ptr(0), ptr(1), ptr(2), ptr(3), ptr(4), arg(5), arg(6), ptr(7), ptr(8));
		return 0;
	case CG_CM_TRANSFORMEDCAPSULETRACE:
		g_syscall( cmd, ptr(0), ptr(1), ptr(2), ptr(3), ptr(4), arg(5), arg(6), ptr(7), ptr(8));
		return 0;
	case CG_CM_MARKFRAGMENTS:
		return g_syscall( cmd, arg(0), ptr(1), ptr(2), arg(3), ptr(4), arg(5), ptr(6) );
	case CG_S_STARTSOUND:
		g_syscall( cmd, ptr(0), arg(1), arg(2), arg(3) );
		return 0;
	case CG_S_STARTLOCALSOUND:
		g_syscall( cmd, arg(0), arg(1) );
		return 0;
	case CG_S_CLEARLOOPINGSOUNDS:
		g_syscall( cmd, arg(0));
		return 0;
	case CG_S_ADDLOOPINGSOUND:
		g_syscall( cmd, arg(0), ptr(1), ptr(2), arg(3) );
		return 0;
	case CG_S_ADDREALLOOPINGSOUND:
		g_syscall( cmd, arg(0), ptr(1), ptr(2), arg(3) );
		return 0;
	case CG_S_STOPLOOPINGSOUND:
		g_syscall( cmd, arg(0) );
		return 0;
	case CG_S_UPDATEENTITYPOSITION:
		g_syscall( cmd, arg(0), ptr(1) );
		return 0;
	case CG_S_RESPATIALIZE:
		g_syscall( cmd, arg(0), ptr(1), ptr(2), arg(3) );
		return 0;
	case CG_S_REGISTERSOUND:
		return g_syscall( cmd, ptr(0), arg(1) );
	case CG_S_STARTBACKGROUNDTRACK:
		g_syscall( cmd, ptr(0), ptr(1) );
		return 0;
	case CG_R_LOADWORLDMAP:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_R_REGISTERMODEL:
		return g_syscall( cmd, ptr(0) );
	case CG_R_REGISTERSKIN:
		return g_syscall( cmd, ptr(0) );
	case CG_R_REGISTERSHADER:
		return g_syscall( cmd, ptr(0) );

	case CG_R_REGISTERSHADERNOMIP:
		return g_syscall( cmd, ptr(0) );
	case CG_R_REGISTERFONT:
		g_syscall( cmd, ptr(0), arg(1), ptr(2));
	case CG_R_CLEARSCENE:
		g_syscall( cmd );
		return 0;
	case CG_R_ADDREFENTITYTOSCENE:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_R_ADDPOLYTOSCENE:
		g_syscall( cmd, arg(0), arg(1), ptr(2) );
		return 0;
	case CG_R_ADDPOLYSTOSCENE:
		g_syscall( cmd, arg(0), arg(1), ptr(2), arg(3) );
		return 0;
	case CG_R_LIGHTFORPOINT:
		return g_syscall( cmd, ptr(0), ptr(1), ptr(2), ptr(3) );
	case CG_R_ADDLIGHTTOSCENE:
		g_syscall( cmd, ptr(0), arg(1), arg(2), arg(3), arg(4) );
		return 0;
	case CG_R_ADDADDITIVELIGHTTOSCENE:
		g_syscall( cmd, ptr(0), arg(1), arg(2), arg(3), arg(4) );
		return 0;
	case CG_R_RENDERSCENE:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_R_SETCOLOR:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_R_DRAWSTRETCHPIC:
		g_syscall( cmd, arg(0), arg(1), arg(2), arg(3), arg(4), arg(5), arg(6), arg(7), arg(8) );
		return 0;
	case CG_R_MODELBOUNDS:
		g_syscall( cmd, arg(0), ptr(1), ptr(2) );
		return 0;
	case CG_R_LERPTAG:
		return g_syscall( cmd, ptr(0), arg(1), arg(2), arg(3), arg(4), ptr(5) );
	case CG_GETGLCONFIG:
		g_syscall( cmd, ptr(0) );
		return 0;
	case CG_GETGAMESTATE: // void CL_GetGameState( gameState_t *gs )
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_GETCURRENTSNAPSHOTNUMBER: // void  CL_GetCurrentSnapshotNumber( int *snapshotNumber, int *serverTime )
		g_syscall( cmd, ptr(0), ptr(1) );
		return 0;

	case CG_GETSNAPSHOT: // qboolean  CL_GetSnapshot( int snapshotNumber, snapshot_t *snapshot )
		return g_syscall( cmd, arg(0), ptr(1) );

	case CG_GETSERVERCOMMAND: // qboolean CL_GetServerCommand( int serverCommandNumber )
		return g_syscall( cmd, arg(0) );

	case CG_GETCURRENTCMDNUMBER:
		return g_syscall( cmd );

	case CG_GETUSERCMD: // qboolean CL_GetUserCmd( int cmdNumber, usercmd_t *ucmd )
		return g_syscall( cmd, arg(0), ptr(1) );

	case CG_SETUSERCMDVALUE: // void CL_SetUserCmdValue( int userCmdValue, float sensitivityScale )
		g_syscall( cmd, arg(0), arg(1) );
		return 0;

	case CG_MEMORY_REMAINING:
		return g_syscall( cmd );
  case CG_KEY_ISDOWN:
		return g_syscall( cmd, arg(0) );
  case CG_KEY_GETCATCHER:
		return g_syscall( cmd );
  case CG_KEY_SETCATCHER:
		g_syscall( cmd, arg(0) );
	return 0;
  case CG_KEY_GETKEY:
		return g_syscall( cmd, ptr(0) );
	case CG_MEMSET:
		g_syscall( cmd, ptr(0), arg(1), arg(2) );
		return 0;
	case CG_MEMCPY:
		g_syscall( cmd, ptr(0), ptr(1), arg(2) );
		return 0;
	case CG_STRNCPY:
		return g_syscall( cmd, ptr(0), ptr(1), arg(2) );
	case CG_SIN:
		return g_syscall( cmd, arg(0) );
	case CG_COS:
		return g_syscall( cmd, arg(0) );
	case CG_ATAN2:
		return g_syscall( cmd, arg(0), arg(1) );
	case CG_SQRT:
		return g_syscall( cmd, arg(0) );
	case CG_FLOOR:
		return g_syscall( cmd, arg(0) );
	case CG_CEIL:
		return g_syscall( cmd, arg(0) );
	case CG_ACOS:
		return g_syscall( cmd, arg(0) );

	case CG_PC_ADD_GLOBAL_DEFINE:
		return g_syscall( cmd, ptr(0) );
	case CG_PC_LOAD_SOURCE:
		return g_syscall( cmd, ptr(0) );
	case CG_PC_FREE_SOURCE:
		return g_syscall( cmd, arg(0) );
	case CG_PC_READ_TOKEN:
		return g_syscall( cmd, arg(0), ptr(1) );
	case CG_PC_SOURCE_FILE_AND_LINE:
		return g_syscall( cmd, arg(0), ptr(1), ptr(2) );

	case CG_S_STOPBACKGROUNDTRACK:
		g_syscall( cmd );
		return 0;

	case CG_REAL_TIME:
		return g_syscall( cmd, ptr(0) );
	case CG_SNAPVECTOR:
		g_syscall( cmd, ptr(0) );
		return 0;

	case CG_CIN_PLAYCINEMATIC:
	  return g_syscall( cmd, ptr(0), arg(1), arg(2), arg(3), arg(4), arg(5));

	case CG_CIN_STOPCINEMATIC:
	  return g_syscall( cmd, arg(0) );

	case CG_CIN_RUNCINEMATIC:
	  return g_syscall( cmd, arg(0) );

	case CG_CIN_DRAWCINEMATIC:
	  g_syscall( cmd, arg(0));
	  return 0;

	case CG_CIN_SETEXTENTS:
	  g_syscall( cmd, arg(0), arg(1), arg(2), arg(3), arg(4));
	  return 0;

	case CG_R_REMAP_SHADER:
		g_syscall( cmd, ptr(0), ptr(1), ptr(2) );
		return 0;

/*
	case CG_LOADCAMERA:
		return loadCamera(ptr(0));

	case CG_STARTCAMERA:
		startCamera(args[1]);
		return 0;

	case CG_GETCAMERAINFO:
		return getCameraInfo(args[1), ptr(1), ptr(2));
*/
	case CG_GET_ENTITY_TOKEN:
		return g_syscall( cmd, ptr(0), arg(1) );
	case CG_R_INPVS:
		return g_syscall( cmd, ptr(0), ptr(1) );

	default:
		return 0;
	}
	return 0;
}
