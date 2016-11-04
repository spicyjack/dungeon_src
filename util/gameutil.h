#ifndef __GAMEUTIL_H__
#define __GAMEUTIL_H__

#ifdef unix
#define rand  random
#define srand srandom
#endif

typedef struct __weightedlist__ WEIGHTEDLIST;

struct __weightedlist__ {
  long          data;
  int           weight;
  WEIGHTEDLIST* next;
};

/* ---------------------------------------------------------------------- *
 * Functions
 * ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------- *
 * Formats 'n', inserting commas as the thousands and millions separator.
 * ---------------------------------------------------------------------- */
void commify( char* buf, int n );

/* ---------------------------------------------------------------------- *
 * Rolls the given-sided die, 'count' number of times.  Thus, 3d20 would
 * be rolled as "rollDice( 3, 20 )".
 * ---------------------------------------------------------------------- */
int rollDice( int count, int sides );

/* ---------------------------------------------------------------------- *
 * Randomly selects a number between 'lo' and 'hi' (inclusive)
 * ---------------------------------------------------------------------- */
long selectBetween( long lo, long hi );

/* ---------------------------------------------------------------------- *
 * Selects a very large random number
 * ---------------------------------------------------------------------- */
long longRand( void );

/* ---------------------------------------------------------------------- *
 * Returns the ordinal suffix (th, st, nd, rd) for the given number.
 * ---------------------------------------------------------------------- */
char* getOrdinalSuffix( int num );

/* ---------------------------------------------------------------------- *
 * Adds the given data to the weighted list with the given weight.
 * ---------------------------------------------------------------------- */
int addToWeightedList( WEIGHTEDLIST** list, long data, int weight );

/* ---------------------------------------------------------------------- *
 * Retrieves the item with the given index in it's weight range from the 
 * weighted list.
 * ---------------------------------------------------------------------- */
long getWeightedItem( WEIGHTEDLIST** list, int index, int* count );

/* ---------------------------------------------------------------------- *
 * Destroys the given weighted list.
 * ---------------------------------------------------------------------- */
void destroyWeightedList( WEIGHTEDLIST** list );

#ifdef __cplusplus
}
#endif

#endif /* __GAMEUTIL_H__ */
