#ifndef __WTSTREAM_H__
#define __WTSTREAM_H__

/* ---------------------------------------------------------------------- *
 * Dependencies
 * ---------------------------------------------------------------------- */

#include <stdio.h>     /* needed for the FILE datatype */

/* ---------------------------------------------------------------------- *
 * Constant definitions
 * ---------------------------------------------------------------------- */

/* stream types */
#define stNOSTREAM   ( 0 )      /* think "/dev/null" */
#define stFILE       ( 1 )      /* stdout, etc. */
#define stBUFFER     ( 2 )      /* write to a buffer */

/* ---------------------------------------------------------------------- *
 * Macro definitions
 * ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Typedefs
 * ---------------------------------------------------------------------- */

typedef struct __wtstream_t__    wtSTREAM_t;

/* ---------------------------------------------------------------------- *
 * Structures
 * ---------------------------------------------------------------------- */

struct __wtstream_t__ {
  int type;
  union {
    FILE *fp;
    struct {
      int   length;
      char *handle;
    } buffer;
  } stream;
};

/* ---------------------------------------------------------------------- *
 * Public methods
 * ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

wtSTREAM_t* wtOpenFileStream( char* fname, char* mode );
wtSTREAM_t* wtOpenBufferStream();
wtSTREAM_t* wtOpenNullStream();
void        wtCloseStream( wtSTREAM_t* stream );

void wtPrint( wtSTREAM_t *stream, char *buffer );

void wtPrintf( wtSTREAM_t *stream, char *format, ... );

#ifdef __cplusplus
}
#endif

#endif /* __WTSTREAM_H__ */
