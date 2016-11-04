#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "grammar.h"

/* ---------------------------------------------------------------------- *
 * Private constants
 * ---------------------------------------------------------------------- */

#define MAX_LINE_LEN ( 1024 )
#define WORK_BUFFER_LEN ( 1024 * 64 )

/* ---------------------------------------------------------------------- *
 * Private (static) methods
 * ---------------------------------------------------------------------- */

static int s_parseProductionIntoGrammar( grGRAMMAR* grammar, char* line );
static int s_addProductionToGrammar( grGRAMMAR* grammar, char* left, char* right, int weight );
static int s_addProductionToGroup( grPRODUCTIONGROUP* group, char* right, int weight );
static grPRODUCTION* s_selectProd( grPRODUCTIONGROUP* group );
static int s_loadGrammarFromFile( grGRAMMAR* grammar, char* filename );
static int s_doLoadStuff( grGRAMMAR* grammar, char* symbol, char* filename );

/* ---------------------------------------------------------------------- *
 * Public method implementation
 * ---------------------------------------------------------------------- */

grGRAMMAR* grLoadGrammar( char* filename ) {
  grGRAMMAR *grammar;

  grammar = (grGRAMMAR*)malloc( sizeof( grGRAMMAR ) );
  memset( grammar, 0, sizeof( *grammar ) );

  if( s_loadGrammarFromFile( grammar, filename ) != 0 ) {
    free( grammar );
    grammar = 0;
  }

  return grammar;
}


void grDestroyGrammar( grGRAMMAR* grammar ) {
  grPRODUCTIONGROUP* group;
  grPRODUCTIONGROUP* nextGrp;
  grPRODUCTION*      prod;
  grPRODUCTION*      nextProd;

  group = grammar->groups;
  while( group != NULL ) {
    nextGrp = group->next;

    prod = group->productions;
    while( prod != NULL ) {
      nextProd = prod->next;
      free( prod->product );
      free( prod );
      prod = nextProd;
    }

    free( group->left );
    free( group );
    group = nextGrp;
  }

  free( grammar );
}


void grBuildPhrase( grGRAMMAR* grammar, char* dest, int len ) {
  char *buffer;
  int   bufferLen;
  int   prodLen;
  int   leftLen;
  grPRODUCTIONGROUP* group;
  grPRODUCTION* prod;
  int   match;
  char* pos;

  *dest = 0;

  if( grammar->startSymbol == NULL ) {
    return;
  }

  buffer = (char*)malloc( WORK_BUFFER_LEN );
  strcpy( buffer, grammar->startSymbol );
  bufferLen = strlen( buffer );

  do {
    match = 0;
    for( group = grammar->groups; group != NULL; group = group->next ) {
      pos = strstr( buffer, group->left );
      if( pos != NULL ) {
        match = 1;

        bufferLen -= ( leftLen = strlen( group->left ) );
        prod = s_selectProd( group );
        bufferLen += ( prodLen = strlen( prod->product ) );
        if( bufferLen >= WORK_BUFFER_LEN ) {
          /* terminate processing -- we've overrun our buffer */
          match = 0;
        } else {
          memmove( pos+prodLen, pos+leftLen, strlen( pos+leftLen ) + 1 );
          strncpy( pos, prod->product, prodLen );
        }
        break;
      }
    }
  } while( match );

  strncpy( dest, buffer, len );
  dest[ len - 1 ] = 0;

  free( buffer );
}

/* ---------------------------------------------------------------------- *
 * Private (static) method implementation
 * ---------------------------------------------------------------------- */

static int s_parseProductionIntoGrammar( grGRAMMAR* grammar, char* line ) {
  char* left;
  char* right;
  char* pweight;
  int   weight;

  left = line;
  right = strchr( line, '=' );
  if( right == NULL ) {
    /* malformed production line - no equals sign given */
    return -1;
  }

  *right = 0;
  right++;

  if( *line == '\0' ) {
    /* malformed production line -- no left-side given */
    return -2;
  }

  /* do not trim the left or right sides -- assume remaining whitespace
   * is intentional */

  /* look for a weight indicator in the left side */
  pweight = left;
  do {
    pweight = strchr( pweight, ':' );
    if( pweight == NULL ) {
      break;
    }
    /* make sure the one we've found is not escaped */
    if( ( pweight > left ) && ( *(pweight-1) != '\\' ) ) {
      *pweight = 0;
      pweight++;
      break;
    }
    /* otherwise, look further */
    pweight++;
  } while( 1 );

  if( *left == '\0' ) {
    /* malformed production line -- left consisted entirely of weight */
    return -3;
  }

  if( pweight == NULL ) {
    weight = 1;
  } else {
    weight = atoi( pweight );
    /* weight may be 0 -- in this case, it is assumed that the user set it
     * to zero to disable the given production */
  }

  s_addProductionToGrammar( grammar, left, right, weight );
  return 0;
}


static int s_addProductionToGrammar( grGRAMMAR* grammar, char* left, char* right, int weight ) {
  grPRODUCTIONGROUP* group;
  grPRODUCTIONGROUP* last;

  last = NULL;
  group = grammar->groups;
  while( group != NULL ) {
    if( strcmp( group->left, left ) == 0 ) {
      s_addProductionToGroup( group, right, weight );
      return 0;
    }
    last = group;
    group = group->next;
  }

  /* the left-side was not found, we need to define a new production group */
  group = (grPRODUCTIONGROUP*)malloc( sizeof( grPRODUCTIONGROUP ) );
  memset( group, 0, sizeof( *group ) );

  group->left = strdup( left );
  s_addProductionToGroup( group, right, weight );

  /* if the start symbol has not been set, set it to the current symbol */
  if( grammar->startSymbol == NULL ) {
    grammar->startSymbol = group->left;
  }

  if( last == NULL ) {
    grammar->groups = group;
  } else {
    last->next = group;
  }

  grammar->groupCount++;

  return 0;
}


static int s_addProductionToGroup( grPRODUCTIONGROUP* group, char* right, int weight ) {
  grPRODUCTION* prod;
  grPRODUCTION* newProd;

  newProd = (grPRODUCTION*)malloc( sizeof( grPRODUCTION ) );
  memset( newProd, 0, sizeof( *newProd ) );

  newProd->weight = weight;
  newProd->product = strdup( right );
  group->totalWeight += weight;

  prod = group->productions;
  if( prod == NULL ) {
    group->productions = newProd;
  } else {
    while( prod->next != NULL ) {
      prod = prod->next;
    }
    prod->next = newProd;
  }

  group->productionCount++;

  return 0;
}


static grPRODUCTION* s_selectProd( grPRODUCTIONGROUP* group ) {
  int d;
  int c;
  grPRODUCTION* p;

  d = rand() % group->totalWeight + 1;
  c = 0;
  for( p = group->productions; p != NULL; p = p->next ) {
    c += p->weight;
    if( d <= c ) {
      return p;
    }
  }

  return NULL;
}


static int s_loadGrammarFromFile( grGRAMMAR* grammar, char* filename ) {
  FILE *f;
  char line[ MAX_LINE_LEN + 1 ];
  char *rc;
  char *s;
  char *p;
  char *e;
  int len;

  f = fopen( filename, "rt" );
  if( f == NULL ) {
    return -1;
  }

  rc = fgets( line, sizeof( line ), f );
  while( rc != NULL ) {

    len = strlen( line );
    
    /* ignore blank lines */
    if( len > 0 ) {

      /* ignore trailing whitespace */
      rc = line + len - 1;
      while( ( rc >= line ) && ( isspace( *rc ) ) ) {
        *rc = '\0';
        rc--;
      }

      /* ignore leading whitespace */
      rc = line;
      while( ( *rc != '\0' ) && ( isspace( *rc ) ) ) {
        rc++;
      }

      /* ignore lines that contain only whitespace */
      if( *rc != '\0' ) {

        /* ignore comment lines */
        if( *rc != '#' ) {

          /* add the line into the grammar */
          s_parseProductionIntoGrammar( grammar, rc );
        } else { 

          /* if it is a comment, check for a processor directive */
          rc++;
          while( ( *rc != '\0' ) && ( isspace( *rc ) ) ) {
            rc++;
          }

          if( *rc != '\0' ) {
            s = strtok( rc, " " );
            if( s != 0 ) {
              if( strcmp( s, "include" ) == 0 ) {
                s = strtok( 0, "\n" );
                if( *s == '"' ) s++;
                p = strchr( s, '"' );
                if( p != 0 ) {
                  *p = 0;
                }
                s_loadGrammarFromFile( grammar, s );
              } else if( strcmp( s, "stuff" ) == 0 ) {
                s = strtok( 0, " " );
                p = strtok( 0, "\n" );
                if( *p == '"' ) p++;
                e = strchr( p, '"' );
                if( e != 0 ) {
                  *e = 0;
                }
                s_doLoadStuff( grammar, s, p );
              }
            }
          }
        }
      }
    }

    rc = fgets( line, sizeof( line ), f );
  }

  fclose( f );

  return 0;
}


static int s_doLoadStuff( grGRAMMAR* grammar, char* symbol, char* filename ) {
  FILE *f;
  char line[ MAX_LINE_LEN + 1 ];
  char *rc;
  char *s;
  char *p;
  int len;

  f = fopen( filename, "rt" );
  if( f == NULL ) {
    return -1;
  }

  rc = fgets( line, sizeof( line ), f );
  while( rc != NULL ) {

    len = strlen( line );
    
    /* ignore blank lines */
    if( len > 0 ) {

      /* ignore trailing whitespace */
      rc = line + len - 1;
      while( ( rc >= line ) && ( isspace( *rc ) ) ) {
        *rc = '\0';
        rc--;
      }

      /* ignore leading whitespace */
      rc = line;
      while( ( *rc != '\0' ) && ( isspace( *rc ) ) ) {
        rc++;
      }

      /* ignore lines that contain only whitespace */
      if( *rc != '\0' ) {

        /* ignore comment lines */
        if( *rc != '#' ) {

          /* add the line into the grammar */
          s_addProductionToGrammar( grammar, symbol, rc, 1 );
        } else { 

          /* if it is a comment, check for a processor directive */
          rc++;
          while( ( *rc != '\0' ) && ( isspace( *rc ) ) ) {
            rc++;
          }

          if( *rc != '\0' ) {
            s = strtok( rc, " " );
            if( s != 0 ) {
              if( strcmp( s, "include" ) == 0 ) {
                s = strtok( 0, "\n" );
                if( *s == '"' ) s++;
                p = strchr( s, '"' );
                if( p != 0 ) {
                  *p = 0;
                }
                s_doLoadStuff( grammar, symbol, s );
              }
            }
          }
        }
      }
    }

    rc = fgets( line, sizeof( line ), f );
  }

  fclose( f );

  return 0;
}

