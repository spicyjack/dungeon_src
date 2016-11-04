#ifndef __WRITETEM_H__
#define __WRITETEM_H__

/* ---------------------------------------------------------------------- *
 * Dependencies
 * ---------------------------------------------------------------------- */

#include <stdio.h>     /* needed for the FILE datatype */
#include "wtstream.h"

/* ---------------------------------------------------------------------- *
 * Constant definitions
 * ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Macro definitions
 * ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Typedefs
 * ---------------------------------------------------------------------- */

typedef struct __wttag_t__       wtTAG_t;
typedef struct __wtdelegate_t__  wtDELEGATE_t;
typedef struct __wtif_t__        wtIF_t;
typedef void                    *wtGENERIC_t;

typedef int (*wtTAGHANDLER_t)( wtSTREAM_t *stream, wtGENERIC_t data, char* other );

/* ---------------------------------------------------------------------- *
 * Structures
 * ---------------------------------------------------------------------- */

struct __wttag_t__ {
  char           *tag;
  wtGENERIC_t     data;
  wtTAGHANDLER_t  handler;
  wtGENERIC_t     userData;
};

struct __wtdelegate_t__ {
  wtTAGHANDLER_t handler;
  wtGENERIC_t    userData;
};

struct __wtif_t__ {
  char* value;
  int   neg;
  char* text;
};

/* ---------------------------------------------------------------------- *
 * Public methods
 * ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

void wtFreeTagList( wtTAG_t **tags );

int  wtWriteTemplate( wtSTREAM_t  *stream,
                      char        *templateFile,
                      wtTAG_t    **tags );

int  wtWriteTemplateToFile( FILE     *f, 
                            char     *templateFile,
                            wtTAG_t **tags );

int  wtWriteTemplateToBuffer( char    **buffer,
                              char     *templateFile,
                              wtTAG_t **tags );

wtTAG_t *wtTagReplace( char* tag, char* data );
wtTAG_t *wtTagReplaceI( char* tag, int data );
wtTAG_t *wtTagDelegate( char* tag, wtDELEGATE_t *handler );

int wtConditionalHandler( wtSTREAM_t *stream, wtGENERIC_t data, char* other );

#ifdef __cplusplus
}
#endif

#endif /* __WRITETEM_H__ */
