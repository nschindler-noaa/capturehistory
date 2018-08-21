/*
 * charutil.h
 */

#ifndef charutil_h
#define charutil_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define LBUFSIZE 2560
#define MBUFSIZE  512
#define SBUFSIZE  128

/* typedef */
typedef char SBuf[SBUFSIZE];
typedef char MBuf[MBUFSIZE];
typedef char LBuf[LBUFSIZE];
typedef LBuf Buffer;

char *chop( char *string );
char *stripWhiteSpace( char* string );

#ifdef __cplusplus
}
#endif


#endif




