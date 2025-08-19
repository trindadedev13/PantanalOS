#ifndef __PANTANAL_TYPES_H__
#define __PANTANAL_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;
typedef uint32_t size_t;

/** C Types */
#ifndef __cplusplus
/** boolean type */
#define false 0
#define true 1
#define bool uint8_t

/** null definition */
#define NULL ((void*)0)
#define null ((void*)0)
#endif

#ifdef __cplusplus
}
#endif

#endif