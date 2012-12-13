#ifndef __UTILS_H__
#define __UTILS_H__



#define ARRAY_LEN(x)  (sizeof(x) / sizeof(*(x)))



extern vec4_t    colorBlack;
extern vec4_t    colorRed;
extern vec4_t    colorGreen;
extern vec4_t    colorBlue;
extern vec4_t    colorYellow;
extern vec4_t    colorMagenta;
extern vec4_t    colorCyan;
extern vec4_t    colorWhite;
extern vec4_t    colorLtGrey;
extern vec4_t    colorMdGrey;
extern vec4_t    colorDkGrey;



// strings
char* vaf(char* format, ...);
const char *getConfigString( int32_t index );

playerState_t *getPs( void );

#endif // __UTILS_H__
