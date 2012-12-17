#ifndef __UTILS_H__
#define __UTILS_H__



#define ARRAY_LEN(x)  (sizeof(x) / sizeof(*(x)))

#define PSF_USERINPUT_NONE     0
#define PSF_USERINPUT_FORWARD  1
#define PSF_USERINPUT_BACKWARD 2
#define PSF_USERINPUT_LEFT     8
#define PSF_USERINPUT_RIGHT    16
#define PSF_USERINPUT_JUMP     32
#define PSF_USERINPUT_CROUCH   64
#define PSF_USERINPUT_ATTACK   256
#define PSF_USERINPUT_WALK     512

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

snapshot_t *getSnap( void );
playerState_t *getPs( void );
int8_t isInAir( playerState_t *ps );
int8_t isJumping( playerState_t *ps );
uint32_t getTime( void );



#endif // __UTILS_H__
