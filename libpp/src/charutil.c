/*
 * dhutil.c
 *
 */

#include <stdio.h>
#include <string.h>

#include "charutil.h"

/* chop off the last char  */
char *chop( char *string ) {
    string[ strlen( string ) - 1 ] = '\0';
    return string;
}

/* Remove leading and trailing space.
 * This function alters the original 
 * char array (s), and returns a 
 * pointer to it as well.
 */
char *stripWhiteSpace( char* s ) {
    int flag = 0;
    char *c1;
    char *c2;

    /* remove trailing space */
    int len = strlen( s );
    if ( len > 0 ) {
        c1 = s + strlen(s) - 1;
        while ( c1 != s && *c1 == ' ' ) 
            *c1-- = '\0';
    }

    /* remove leading space */
    c1 = c2 = s;
    for( ; *c1 != '\0'; c1++ ) {
        if ( !flag && *c1 != ' ' && *c1 != '\t' )
            flag = 1;
        if ( flag )
            *c2++ = *c1;
    }
    
    *c2 = '\0';

    return s;
    
}
