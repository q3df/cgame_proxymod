#ifndef __UTILS_H__
#define __UTILS_H__



#define ARRAY_LEN(x)  (sizeof(x) / sizeof(*(x)))



// strings
char* vaf(char* format, ...);
const char *getConfigString( int32_t index );

playerState_t *getPs( void );

#endif // __UTILS_H__
