/* ---------------------------------------------------------------------- *
 * This file is in the public domain, and may be used, modified, and
 * distributed without restriction (though the author would like to be
 * given credit).
 * ---------------------------------------------------------------------- *
 * Dungeon CGI Front-end
 *
 * Author: Jamis Buck
 * Homepage: http://rover.byu.edu/jgb3/generators.html
 *
 * This CGI front end employs two other libraries that are freely available
 * online:
 *
 *   - qDecoder (available from http://www.qDecoder.org) is a CGI library
 *     for use by CGI applications.
 *   - gd (available from http://www.boutell.com/gd/) is a graphics library
 *     used for creating and modifying images.  In the case of this program,
 *     gd is the tool that creates the dungeon maps in .PNG format.
 * ---------------------------------------------------------------------- */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "gameutil.h"
#include "jbdungeon.h"
#include "jbdungeondata.h"
#include "jbdungeonpaintergd.h"

#include "gd.h"

#include "gdfontt.h"
#include "gdfonts.h"
#include "gdfontmb.h"
#include "gdfontl.h"
#include "gdfontg.h"

#include "writetem.h"
#include "qDecoder.h"

#define TEMPATH "tem/"
#define WEBIMGPATH "/temp/img/"

#ifdef WIN32
#define CGINAME     "dungeon.exe"
#define LOGLOCATION "c:\\dungeon.log"
#define CTRLOCATION "c:\\dungeon.cnt"
#define IMGPATH "d:\\apache\\htdocs\\temp\\img\\"
#else
#define CGINAME     "dungeon.cgi"
#define LOGLOCATION "/home/jgb3/dungeon.log"
#define CTRLOCATION "/home/jgb3/dungeon.cnt"
#define IMGPATH "/home/httpd/html/temp/img/"
#endif

static char url[512];
static time_t seedn;

/* logs access to the CGI */
void logAccess( char* url ) {
  FILE *f;
  char buffer[512];
  time_t t;
  char *host;

  f = fopen( LOGLOCATION, "at" );
  if( f == NULL ) {
    printf( "content-type: text/html\r\n\r\n" );
    printf( "could not open log file: %d (%s)\n", errno, strerror( errno ) );
    return;
  }

  t = time( NULL );
  strftime( buffer, sizeof( buffer ), "[%d %b %Y %H:%M:%S]", localtime( &t ) );

  host = getenv( "REMOTE_ADDR" );
  fprintf( f, "%s %s %s\n", buffer, host, url );
  fclose( f );
}


int getCounter() {
  FILE *f;
  char  buffer[32];
  int   count;

  f = fopen( CTRLOCATION, "r+t" );
  if( f == NULL ) {
    f = fopen( CTRLOCATION, "w+t" );
    if( f == NULL ) {
      return 0;
    }
  }

  fgets( buffer, sizeof( buffer ), f );
  count = atoi( buffer ) + 1;
  rewind( f );
  fprintf( f, "%d", count );
  fclose( f );

  return count;
}


static void strrepl( char* buf, char* srch, char* repl ) {
  char* p;
  int   slen;
  int   rlen;

  slen = strlen( srch );
  rlen = strlen( repl );

  p = strstr( buf, srch );
  while( p != NULL ) {
    memmove( p+rlen, p+slen, strlen( p + slen ) + 1 );
    strncpy( p, repl, rlen );
    p = strstr( p+rlen, srch );
  }
}


#define NORTH ( 1 )
#define SOUTH ( 2 )
#define EAST  ( 3 )
#define WEST  ( 4 )

int getWallOrientation( JBDungeonRoom* room, JBDungeonWall* wall, int *ofs ) {
  int minx;
  int maxx;
  int miny;
  int maxy;

  minx = ( wall->pt1.x < wall->pt2.x ? wall->pt1.x : wall->pt2.x );
  maxx = ( wall->pt1.x > wall->pt2.x ? wall->pt1.x : wall->pt2.x );
  miny = ( wall->pt1.y < wall->pt2.y ? wall->pt1.y : wall->pt2.y );
  maxy = ( wall->pt1.y > wall->pt2.y ? wall->pt1.y : wall->pt2.y );

  if( minx < room->topLeft.x ) {
    *ofs = miny - room->topLeft.y + 1;
    return WEST;
  }

  if( maxx >= room->topLeft.x + room->size.x ) {
    *ofs = miny - room->topLeft.y + 1;
    return EAST;
  }

  if( miny < room->topLeft.y ) {
    *ofs = minx - room->topLeft.x + 1;
    return NORTH;
  }

  if( maxy >= room->topLeft.y + room->size.y ) {
    *ofs = minx - room->topLeft.x + 1;
    return SOUTH;
  }

  *ofs = 0;
  return 0;
}


int displayDungeonDescription( wtSTREAM_t* stream, wtGENERIC_t data, char* other ){
  JBDungeon* dungeon;
  int        level;
  int        roomCount;
  int        i;
  int        j;
  JBDungeonRoom* room;
  char       hugeBuffer[32 * 1024];
  int        ofs;
  char*      p;
  char*      tmp;
  int        blockIsOpen;

  logAccess( url );

  dungeon = (JBDungeon*)data;
  level = qiValue( "level" );
  if( level < 1 ) {
    level = 1;
  }

  JBDungeonDescription( dungeon, qiValue( "level" ) );

  wtPrint( stream, "<P>\n" );

  roomCount = dungeon->getRoomCount();
  for( i = 0; i < roomCount; i++ ) {
    room = dungeon->getRoom( i );

    wtPrintf( stream, "<B>Room #%d:</B>\n<UL>\n", i+1 );

    for( j = 0; j < room->wallCount; j++ ) {
      if( room->walls[ j ]->type == JBDungeonWall::c_WALL ) {
        continue;
      }

      wtPrintf( stream, "<LI>Door" );

      switch( getWallOrientation( room, room->walls[ j ], &ofs ) ) {
        case NORTH:
          wtPrintf( stream, " (north, %d from west)", ofs );
          break;
        case SOUTH:
          wtPrintf( stream, " (south, %d from west)", ofs );
          break;
        case EAST:
          wtPrintf( stream, " (east, %d from north)", ofs );
          break;
        case WEST:
          wtPrintf( stream, " (west, %d from north)", ofs );
          break;
      }

      wtPrint( stream, ":  " );

      if( room->walls[ j ]->data != 0 ) {
        room->walls[ j ]->data->getDatumDescription( hugeBuffer );
        strrepl( hugeBuffer, "\n", "<BR>\n" );
        wtPrint( stream, hugeBuffer );
      } else if( room->walls[ j ]->type == JBDungeonWall::c_DOOR ) {
        wtPrint( stream, "(normal)" );
      } else if( room->walls[ j ]->type == JBDungeonWall::c_SECRETDOOR ) {
        wtPrint( stream, "(secret)" );
      } else if( room->walls[ j ]->type == JBDungeonWall::c_CONCEALEDDOOR ) {
        wtPrint( stream, "(concealed)" );
      }

      wtPrint( stream, "\n" );
    }

    room->data->getDatumDescription( hugeBuffer );
    strrepl( hugeBuffer, "\n", "<BR>\n" );
    strrepl( hugeBuffer, "~B", "<B>" );
    strrepl( hugeBuffer, "~b", "</B>" );
    strrepl( hugeBuffer, "~I", "<I>" );
    strrepl( hugeBuffer, "~i", "</I>" );
    strrepl( hugeBuffer, "~n", "\n" );

    tmp = hugeBuffer;
    blockIsOpen = 0;
    while( ( p = strtok( tmp, DUNGEON_DATA_DELIM ) ) != 0 ) {
      tmp = 0;
      
      if( *p == '$' ) {
        if( blockIsOpen ) {
          wtPrintf( stream, "</UL>" );
        }
        blockIsOpen = 0;
      } else if( *p == '!' ) {
        p++;
        wtPrintf( stream, "<LI>%s\n", p );
        wtPrintf( stream, "<UL>\n" );
        blockIsOpen = 1;
      } else {
        wtPrintf( stream, "<LI>%s\n", p );
      }
    }

    if( blockIsOpen ) {
      wtPrintf( stream, "</UL>\n" );
    }

    wtPrintf( stream, "</UL>\n" );
  }

  return 0;
}


JBDungeon* prepareDungeon() {
  char* width;
  char* roomcnt;
  char* height;
  char* minroomw;
  char* maxroomw;
  char* minroomh;
  char* maxroomh;
  char* sparse;
  char* secret;
  char* random;
  char* concealed;
  char* deadends;
  char* resolution;

  float minMod;
  float maxMod;

  JBDungeonOptions dungeonOpts;
  JBDungeon* dungeon;

  int area;
  int aveRoomArea;
  int lw;

  width = qValue( "width" );
  roomcnt = qValue( "roomcnt" );
  height = qValue( "height" );
  minroomw = qValue( "minroomw" );
  maxroomw = qValue( "maxroomw" );
  minroomh = qValue( "minroomh" );
  maxroomh = qValue( "maxroomh" );
  sparse = qValue( "sparse" );
  secret = qValue( "secret" );
  random = qValue( "random" );
  concealed = qValue( "concealed" );
  deadends = qValue( "deadends" );
  resolution = qValue( "resolution" );

  dungeonOpts.size.x = atoi( width );
  dungeonOpts.size.y = atoi( height );
  dungeonOpts.seed = seedn;
  dungeonOpts.randomness = atoi( random );
  dungeonOpts.clearDeadends = atoi( deadends );

//  dungeonOpts.mask = new JBMazeMask( "d:\\dev\\roger.txt" );

  if( dungeonOpts.mask != 0 ) {
    dungeonOpts.size.x = dungeonOpts.mask->getWidth();
    dungeonOpts.size.y = dungeonOpts.mask->getHeight();
  }

  area = dungeonOpts.size.x * dungeonOpts.size.y;
  lw = (int)( ( dungeonOpts.size.x + dungeonOpts.size.y ) * 0.5 );

  if( strcmp( sparse, "very" ) == 0 ) {
    dungeonOpts.sparseness = lw;
  } else if( strcmp( sparse, "quite" ) == 0 ) {
    dungeonOpts.sparseness = (int)( lw * 0.75 );
  } else if( strcmp( sparse, "some" ) == 0 ) {
    dungeonOpts.sparseness = (int)( lw * 0.5 );
  } else if( strcmp( sparse, "crowd" ) == 0 ) {
    dungeonOpts.sparseness = (int)( lw * 0.25 );
  } else if( strcmp( sparse, "dense" ) == 0 ) {
    dungeonOpts.sparseness = 0;
  }

  dungeonOpts.minRoomX = atoi( minroomw );
  dungeonOpts.maxRoomX = atoi( maxroomw );
  dungeonOpts.minRoomY = atoi( minroomh );
  dungeonOpts.maxRoomY = atoi( maxroomh );

  aveRoomArea = (int)
                ( ( ( dungeonOpts.maxRoomX + dungeonOpts.minRoomX ) / 2.0 ) +
                ( ( dungeonOpts.maxRoomY + dungeonOpts.minRoomY ) / 2.0 ) );

  if( strcmp( roomcnt, "none" ) == 0 ) {
    minMod = 0;
    maxMod = 0;
  } else if( strcmp( roomcnt, "few" ) == 0 ) {
    minMod = 0.5;
    maxMod = 1;
  } else if( strcmp( roomcnt, "some" ) == 0 ) {
    minMod = 1;
    maxMod = 2;
  } else if( strcmp( roomcnt, "many" ) == 0 ) {
    minMod = 2;
    maxMod = 4;
  } else if( strcmp( roomcnt, "lots" ) == 0 ) {
    minMod = 4;
    maxMod = 8;
  }

  if( aveRoomArea == 0 ) {
    dungeonOpts.minRoomCount = dungeonOpts.maxRoomCount = 0;
  } else {
    dungeonOpts.minRoomCount = (int)( ( lw * 4.0 / aveRoomArea ) * minMod );
    dungeonOpts.maxRoomCount = (int)( ( lw * 4.0 / aveRoomArea ) * maxMod );
  }

  dungeonOpts.secretDoors = atoi( secret );
  dungeonOpts.concealedDoors = atoi( concealed );

  dungeon = new JBDungeon( dungeonOpts );
  dungeon->setDataPath( TEMPATH );

  return dungeon;
}


int displayDungeon( void ) {
  wtTAG_t *tags[5];

  char  fname[1024];
  char  buffer[20];

  wtDELEGATE_t roomDesc;

  JBDungeon* dungeon;

  dungeon = prepareDungeon();

  sprintf( fname, "/cgi-bin/%s&imageonly=1", url );

  roomDesc.handler = displayDungeonDescription;
  roomDesc.userData = dungeon;

  tags[0] = wtTagReplace( "MAPIMG", fname );
  tags[1] = wtTagDelegate( "ROOMDESC", &roomDesc );
  tags[2] = wtTagReplaceI( "SEED", seedn );

  commify( buffer, getCounter() );
  tags[3] = wtTagReplace( "COUNTER", buffer );

  tags[4] = 0;

  wtWriteTemplateToFile( stdout, TEMPATH "dungeon_desc.tem", tags );
  wtFreeTagList( tags );

  delete dungeon;

  return 0;
}


void imageOnly() {
  gdImagePtr image;
  JBDungeon* dungeon;
  JBDungeonPainterGD* painter;

  printf( "content-type: image/png\r\n" );
  printf( "Pragma: no-cache\r\n" );
  printf( "Expires: Thu, 1 Jan 1970 00:00:01 GMT\r\n\r\n" );

  dungeon = prepareDungeon();
  painter = new JBDungeonPainterGD( dungeon, qiValue( "resolution" ), 5 );

  painter->paint();
  image = painter->getImage();

#ifdef WIN32
  _setmode( _fileno( stdout ), _O_BINARY );
#endif

  gdImagePng( image, stdout );

  delete painter;
}


int main( int argc, char* argv[] ) {
  time_t t;
  wtTAG_t *tags[3];
  char buffer[12];  

//  putenv( "REQUEST_METHOD=GET" );
//  putenv( "QUERY_STRING=width=16&roomcnt=some&height=16&minroomw=2&maxroomw=5&sparse=some&minroomh=2&maxroomh=5&random=40&secret=5&deadends=100&concealed=10&level=1&resolution=20&seed=973963837&imageonly=1" );

  qDecoder();

  t = time( NULL );
  seedn = qiValue( "seed" );
  if( seedn < 1 ) {
    seedn = t;
    sprintf( url, "%s?%s%d", CGINAME, getenv( "QUERY_STRING" ), seedn );
  } else {
    sprintf( url, "%s?%s", CGINAME, getenv( "QUERY_STRING" ) );
  }

  if( qiValue( "imageonly" ) ) {
    imageOnly();
    qFree();
    return 0;
  }

  printf( "content-type: text/html\r\n" );
  printf( "Pragma: no-cache\r\n" );
  printf( "Expires: Thu, 1 Jan 1970 00:00:01 GMT\r\n\r\n" );

  if( qValueDefault( 0, "width" ) != 0 ) {
    displayDungeon();
  } else {
    commify( buffer, getCounter() );
    tags[0] = wtTagReplace( "COUNTER", buffer );
    tags[1] = wtTagReplace( "CGINAME", CGINAME );

    tags[2] = 0;

    wtWriteTemplateToFile( stdout, TEMPATH "dungeon_main.tem", tags );
    wtFreeTagList( tags );
  }
    
  qFree();

  return 0;
}