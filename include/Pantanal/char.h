#ifndef __PANTANAL_CHAR_H__
#define __PANTANAL_CHAR_H__

#include "Pantanal/types.h"

#ifdef __cplusplus
extern "C" {
#endif

static bool is_space(char c) {
  return ((c == ' ') || (c == '\n') || (c == '\t'));
}

static bool is_digit(char c) {
  return ((c >= '0') && (c <= '9'));
}

static bool is_alpha(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

#ifdef __cplusplus
}
#endif

#endif