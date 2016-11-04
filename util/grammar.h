#ifndef __GRAMMAR_H__
#define __GRAMMAR_H__

/* ---------------------------------------------------------------------- *
 * Typedefs
 * ---------------------------------------------------------------------- */

typedef struct __grproduction__      grPRODUCTION;
typedef struct __grproductiongroup__ grPRODUCTIONGROUP;
typedef struct __grgrammar__         grGRAMMAR;

/* ---------------------------------------------------------------------- *
 * Structures
 * ---------------------------------------------------------------------- */

struct __grproduction__ {
  int           weight;
  char*         product;
  grPRODUCTION* next;
};


struct __grproductiongroup__ {
  char*              left;
  int                totalWeight;
  int                productionCount;
  grPRODUCTION*      productions;
  grPRODUCTIONGROUP* next;
};


struct __grgrammar__ {
  char*              startSymbol;
  int                groupCount;
  grPRODUCTIONGROUP* groups;
};

/* ---------------------------------------------------------------------- *
 * Public methods
 * ---------------------------------------------------------------------- */

grGRAMMAR* grLoadGrammar( char* filename );
void       grDestroyGrammar( grGRAMMAR* grammar );

void       grBuildPhrase( grGRAMMAR* grammar, char* dest, int len );

#endif /* __GRAMMAR_H__ */
