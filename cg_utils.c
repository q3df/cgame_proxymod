#include <stdarg.h>
#include <stdio.h>

#include "cg_local.h"

#ifdef _WIN32
	#define vsnprintf _vsnprintf
#endif

char* vaf(char* format, ...) {
	va_list	argptr;
	static char str[1024];

	va_start(argptr, format);
	vsnprintf(str, 1024, format, argptr);
	va_end(argptr);

	return str;
}
