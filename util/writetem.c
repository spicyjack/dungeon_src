#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "writetem.h"
#include "wtstream.h"

/* ---------------------------------------------------------------------- *
 * Constant definitions
 * ---------------------------------------------------------------------- */

#define DELIM_START     "<!--%"
#define DELIM_END       "%-->"

#define MAX_POSSIBLE_BUFFER_LEN  ( 64000 )

/* ---------------------------------------------------------------------- *
 * Private (static) methods
 * ---------------------------------------------------------------------- */

static int s_wtTagReplaceHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other );
static int s_wtTagReplaceIHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other );
static int s_wtTagDelegateHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other );

/* ---------------------------------------------------------------------- *
 * Public method implementation
 * ---------------------------------------------------------------------- */

void wtFreeTagList( wtTAG_t **tags ) {
  int i;

  for( i = 0; tags[ i ] != NULL; i++ ) {
    free( tags[ i ] );
  }
}


int wtWriteTemplate( wtSTREAM_t  *stream,
                     char        *templateFile,
                     wtTAG_t    **tags ) 
{
  FILE *temFile;
  int   len;
  int   i;
  int   rc;
  char *temContents;
  char *pos;
  char *start;
  char *end;
  char *other;

  temFile = fopen( templateFile, "rt" );
  if( temFile == NULL ) {
    return -1;
  }

  fseek( temFile, 0, SEEK_END );
  len = ftell( temFile );
  rewind( temFile );

  temContents = (char*)malloc( len + 1 );
  fread( temContents, 1, len, temFile );
  fclose( temFile );

  temContents[ len ] = 0;
  start = temContents;
  while( ( pos = strstr( start, DELIM_START ) ) != NULL ) {
    *pos = '\0';
    pos += strlen( DELIM_START );

    wtPrint( stream, start );

    end = strstr( pos, DELIM_END );
    
    if( end == NULL ) {
      start = pos + strlen( DELIM_START ) - 1;
      continue;
    } 
      
    *end = '\0';
    end += strlen( DELIM_END );

    /* look for a ':' to indicate additional data */
    other = strchr( pos, ':' );
    if( other != NULL ) {
      *other = 0;
      other++;
    }

    /* look for a matching token */
    for( i = 0; tags[ i ] != NULL; i++ ) {
      if( strcmp( tags[ i ]->tag, pos ) == 0 ) {
        tags[ i ]->handler( stream, tags[ i ]->data, other );
        break;
      }
    }

    start = end;
  }

  wtPrint( stream, start );

  free( temContents );

  return 0;
}


int wtWriteTemplateToFile( FILE     *f, 
                           char     *templateFile,
                           wtTAG_t **tags )
{
  wtSTREAM_t stream;

  stream.type = stFILE;
  stream.stream.fp = f;

  return wtWriteTemplate( &stream, templateFile, tags );
}


int wtWriteTemplateToBuffer( char    **buffer,
                             char     *templateFile,
                             wtTAG_t **tags )
{
  wtSTREAM_t stream;
  int        rc;

  *buffer = NULL;

  stream.type = stBUFFER;
  stream.stream.buffer.length = 0;
  stream.stream.buffer.handle = NULL;

  rc = wtWriteTemplate( &stream, templateFile, tags );

  *buffer = stream.stream.buffer.handle;

  return rc;
}


wtTAG_t *wtTagReplace( char* tag, char* data ) {
  wtTAG_t *newTag;

  newTag = (wtTAG_t*)malloc( sizeof( wtTAG_t ) );
  newTag->tag = tag;
  newTag->data = data;
  newTag->handler = s_wtTagReplaceHandler;

  return newTag;
}


wtTAG_t *wtTagReplaceI( char* tag, int data ) {
  wtTAG_t *newTag;

  newTag = (wtTAG_t*)malloc( sizeof( wtTAG_t ) );
  newTag->tag = tag;
  newTag->data = (wtGENERIC_t)data;
  newTag->handler = s_wtTagReplaceIHandler;

  return newTag;
}


wtTAG_t *wtTagDelegate( char* tag, wtDELEGATE_t *handler ) {
  wtTAG_t *newTag;

  newTag = (wtTAG_t*)malloc( sizeof( wtTAG_t ) );
  newTag->tag = tag;
  newTag->data = handler;
  newTag->handler = s_wtTagDelegateHandler;

  return newTag;
}


int wtConditionalHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other ) {
  wtIF_t *ifData;
  int     rc;

  ifData = (wtIF_t*)data;

  if( ifData->value == NULL ) {
    ifData->value = "";
  }
  if( other == NULL ) {
    other = "";
  }

  rc = strcmp( ifData->value, other );
  if( ifData->neg ) {
    if( rc == 0 ) {
      rc = 1;
    } else {
      rc = 0;
    }
  }

  if( rc == 0 ) {
    wtPrint( stream, ifData->text );
  }

  return 0;
}

/* ---------------------------------------------------------------------- *
 * Private (static) method implementation
 * ---------------------------------------------------------------------- */

static int s_wtTagReplaceHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other ) {
  wtPrint( stream, (char*)data );
  return 0;
}


static int s_wtTagReplaceIHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other ) {
  char buffer[256];

  sprintf( buffer, "%d", (int)data );
  wtPrint( stream, buffer );

  return 0;
}


static int s_wtTagDelegateHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other ) {
  wtDELEGATE_t *d;

  d = (wtDELEGATE_t*)data;
  return d->handler( stream, d->userData, other );
}
