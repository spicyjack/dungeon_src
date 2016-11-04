#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "wtstream.h"

/* ---------------------------------------------------------------------- *
 * Constant definitions
 * ---------------------------------------------------------------------- */

#define MAX_POSSIBLE_BUFFER_LEN  ( 64000 )

/* ---------------------------------------------------------------------- *
 * Public method implementation
 * ---------------------------------------------------------------------- */

wtSTREAM_t* wtOpenFileStream( char* fname, char* mode ) {
  wtSTREAM_t* stream;
  FILE*       f;

  f = fopen( fname, mode );
  if( f == NULL ) {
    return NULL;
  }

  stream = (wtSTREAM_t*)malloc( sizeof( wtSTREAM_t ) );
  memset( stream, 0, sizeof( *stream ) );

  stream->type = stFILE;
  stream->stream.fp = f;

  return stream;
}


wtSTREAM_t* wtOpenBufferStream() {
  wtSTREAM_t* stream;

  stream = (wtSTREAM_t*)malloc( sizeof( wtSTREAM_t ) );
  memset( stream, 0, sizeof( *stream ) );

  stream->type = stBUFFER;
  stream->stream.buffer.length = 0;
  stream->stream.buffer.handle = NULL;  

  return stream;
}


wtSTREAM_t* wtOpenNullStream() {
  wtSTREAM_t* stream;

  stream = (wtSTREAM_t*)malloc( sizeof( wtSTREAM_t ) );
  memset( stream, 0, sizeof( *stream ) );

  stream->type = stNOSTREAM;

  return stream;  
}


void wtCloseStream( wtSTREAM_t* stream ) {
  switch( stream->type ) {
    case stFILE:
      fclose( stream->stream.fp );
      break;

    case stBUFFER:
      if( stream->stream.buffer.length > 0 ) {
        free( stream->stream.buffer.handle );
      }
      break;

    case stNOSTREAM:
      break;
  }

  free( stream );
}


void wtPrint( wtSTREAM_t *stream, char *buffer ) {
  char *temp;
  int   len;

  switch( stream->type ) {
    case stNOSTREAM:
      break;

    case stFILE:
      fputs( buffer, stream->stream.fp );
      break;

    case stBUFFER:
      len = strlen( buffer );
      if( len > 0 ) {
        temp = (char*)malloc( stream->stream.buffer.length + len + 1 );
        if( stream->stream.buffer.length > 0 ) {
          strcpy( temp, stream->stream.buffer.handle );
        }

        strcpy( &temp[ stream->stream.buffer.length ], buffer );

        if( stream->stream.buffer.length > 0 ) {
          free( stream->stream.buffer.handle );
        }

        stream->stream.buffer.length += len;
        stream->stream.buffer.handle = temp;
      }
      break;
  }        
}


void wtPrintf( wtSTREAM_t *stream, char *format, ... ) {
  va_list  args;
  char    *buffer;

  va_start( args, format );

  buffer = (char*)malloc( MAX_POSSIBLE_BUFFER_LEN );
  vsprintf( buffer, format, args );

  va_end( args );

  wtPrint( stream, buffer );

  free( buffer );
}
