#ifndef TEXTURE_LOADER_MAC_H
#define TEXTURE_LOADER_MAC_H

#include "gl.h"

/* GL_UNSIGNED_INT_... is a hack to convert ARGB format into RGBA.  The
 * BGRA extension is supported on all Apple hardware, so we don't bother
 * checking for it.
 */
#if TARGET_RT_BIG_ENDIAN
#  define ARGB_FORMAT GL_BGRA
#  define ARGB_TYPE GL_UNSIGNED_INT_8_8_8_8_REV
#elif TARGET_RT_LITTLE_ENDIAN
#  define ARGB_FORMAT GL_BGRA
#  define ARGB_TYPE GL_UNSIGNED_INT_8_8_8_8
#else
#  error Target endianness not specified, please use Apple gcc.
#endif


int is_power_2(int);
void flip_data(char*, int, int);
GLuint texture_load(const char*);
GLuint texture_load_data(unsigned char*, int, int, int, int, GLint, GLenum, GLenum);
int texture_is_valid_dimensions(int, int);

#endif