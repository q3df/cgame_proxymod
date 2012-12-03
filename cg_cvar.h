#ifndef __CG_CVAR_H__
#define __CG_CVAR_H__



#define MAX_CVAR_VALUE_STRING 256



typedef uint32_t cvarHandle_t;

typedef struct {
	cvarHandle_t  handle;
	int     modificationCount;
	float   value;
	int     integer;
	char    string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;



void cvar_sniffRegister( vmCvar_t *cvar, const char *var_name, const char *value, int32_t flags );
int8_t cvar_getInt( const char *var_name, int32_t *value );



#endif // __CG_CVAR_H__
