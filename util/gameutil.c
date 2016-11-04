#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gameutil.h"


void commify( char* buf, int n ) {
  int i;
  int c;

  c = 0;
  buf[0] = 0;

  i = n / 1000000;
  if( c || ( i > 0 ) ) {
    if( c ) {
      sprintf( &buf[strlen(buf)], "%03d,", i );
    } else {
      sprintf( &buf[strlen(buf)], "%d,", i );
    }
    c = 1;
    if( n >= 1000000 ) {
      n %= 1000000;
    }
  }

  i = n / 1000;
  if( c || ( i > 0 ) ) {
    if( c ) {
      sprintf( &buf[strlen(buf)], "%03d,", i );
    } else {
      sprintf( &buf[strlen(buf)], "%d,", i );
    }
    if( n >= 1000 ) {
      n %= 1000;
    }
    c = 1;
  } 

  if( c ) {
    sprintf( &buf[ strlen(buf)], "%03d", n );
  } else {
    sprintf( &buf[ strlen(buf)], "%d", n );
  }
}


int rollDice( int count, int sides ) {
  int i;
  int total;

  total = 0;
  for( i = 0; i < count; i++ ) {
    total += rand() % sides + 1;
  }

  return total;
}


long selectBetween( long lo, long hi ) {
  long r;

  r = longRand();
  return ( r % ( hi - lo + 1 ) + lo );
}


long longRand( void ) {
  long r1;
  long r2;
  long r;
  int  i;
  int  bit;
  static int bits[16] = { 0x0001, 0x0002, 0x0004, 0x0008,
                          0x0010, 0x0020, 0x0040, 0x0080,
                          0x0100, 0x0200, 0x0400, 0x0800,
                          0x1000, 0x2000, 0x4000, 0x8000 };

  r1 = rand();
  r2 = rand();
  r = 0;
  for( i = 0; i < 32; i++ ) {
    bit = i >> 1; /* div by 2 */
    if( i % 2 == 0 ) {
      r |= ( ( r1 & bits[bit] ) >> bit ) << i;
    } else {
      r |= ( ( r2 & bits[bit] ) >> bit ) << i;
    }
  }

  r &= 0x7FFFFFFF;

  return r;
}


char* getOrdinalSuffix( int num ) {
  if( ( num >= 10 ) && ( num <= 20 ) ) {
    return "th";
  }
  switch( num % 10 ) {
    case 1:
      return "st";
    case 2:
      return "nd";
    case 3:
      return "rd";
  }

  return "th";
}


int addToWeightedList( WEIGHTEDLIST** list, long data, int weight ) {
  WEIGHTEDLIST* item;
  WEIGHTEDLIST* i;

  item = (WEIGHTEDLIST*)malloc( sizeof( WEIGHTEDLIST ) );
  memset( item, 0, sizeof( *item ) );

  item->data = data;
  item->weight = weight;

  if( *list == 0 ) {
    *list = item;
  } else {
    i = *list;
    while( i->next != 0 ) {
      i = i->next;
    }
    i->next = item;
  }

  return weight;
}


long getWeightedItem( WEIGHTEDLIST** list, int index, int* count ) {
  int total;
  long data;
  WEIGHTEDLIST* i;
  WEIGHTEDLIST* p;

  i = *list;
  p = 0;
  total = 0;
  while( i != 0 ) {
    total += i->weight;
    if( index <= total ) {
      data = i->data;
      if( p == 0 ) {
        *list = i->next;
      } else {
        p->next = i->next;
      }
      *count -= i->weight;
      free( i );
      return data;
    }
    p = i;
    i = i->next;
  }

  return -1;
}


void destroyWeightedList( WEIGHTEDLIST** list ) {
  WEIGHTEDLIST* i;
  WEIGHTEDLIST* n;

  i = *list;
  while( i != 0 ) {
    n = i->next;
    free( i );
    i = n;
  }
  *list = 0;
}


