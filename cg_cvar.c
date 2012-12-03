#include <stdlib.h>
#include "cg_local.h"
#include "cg_cvar.h"


int8_t cvar_register( char *name, char *value ) {
	return 0;
}



int8_t cvar_getInt( const char *var_name, int32_t *value ) {
	char buffer[1024];

	g_syscall( CG_CVAR_VARIABLESTRINGBUFFER, var_name, buffer, 256 );
	*value = atoi( buffer ); // can't tell if 0 or ERROR
	// TODO: make this return qfalse in case of error -> no atoi()

	return qtrue;
}
