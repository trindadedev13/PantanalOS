#ifndef __PANTANAL_CSTR_H__
#define __PANTANAL_CSTR_H__

#include "Pantanal/types.h"

#ifdef __cplusplus
extern "C" {
#endif

static int str_cmp(const char* s1, const char* s2) {
  while (*s1 && (*s1 == *s2)) {
    ++s1;
    ++s2;
  }
  return (uint8_t)*s1 - (uint8_t)*s2;
}

#ifdef __cplusplus
}
#endif

#endif