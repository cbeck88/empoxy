/***
 * Some functions that we need to implement, like getting pointers to
 * glGetString, etc.,
 * need to be done using the emscripten-provided OpenGL header.
 * This is not compatible with the epoxy OpenGL header, therefore it
 * must be done in a separate compilation unit.
 */

#include <epoxy/common.h>
#include <GL/gl.h>
#include <string.h>

EPOXY_IMPORTEXPORT void *
epoxy_em_bootstrap(const char * str) {
  if (0 == strcmp("glGetString", str)) {
    return &glGetString;
  }
  return &glGetIntegerv;
}
