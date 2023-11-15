#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H 1

#include <stdint.h>

#ifndef _SSIZE_T_DECLARED
typedef int32_t ssize_t;
#define	_SSIZE_T_DECLARED
#endif

#ifndef _SUSECONDS_T_DECLARED
typedef int32_t suseconds_t;
#define	_SUSECONDS_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef __SIZE_TYPE__ size_t;
#define	_SIZE_T_DECLARED
#endif

#ifndef _TIME_T_DECLARED
typedef int64_t time_t;
#define	_TIME_T_DECLARED
#endif

#endif
