#ifndef portability_h
#define portability_h

#ifdef WIN32

#include <io.h>
#include <time.h>
#define isnan _isnan
#define unlink _unlink
#define access _access
#define isnan _isnan
#define mkdir _mkdir
#define strdup _strdup
#define chmod _chmod
/*
#define tmpnam tmpnam_s
#define tempnam _tempnam
#define strtok strtok_s
*/


#else 

#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <dirent.h>
#endif 

#endif // portability_h
