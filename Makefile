OPTS=-I../qDecoder -Igd-1.8.3 -Idnd/include -Idnd/treasure -Idnd/npc -Idnd/dungeon -Iutil
#LIBS=-Lgd-1.8.3 -lgd -L/usr/lib -lpng -ljpeg -L/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.90.29 -lstdc++
LIBS=-Lgd-1.8.3 -lgd -L/usr/lib -lpng -ljpeg

all: dungeon.cgi

WEBOBJS=\
	dnd/web/dungeoncgi.cpp \
	dnd/treasure/treasureEngine.c \
	dnd/npc/npcEngine.c \
	dnd/dungeon/jbmaze.cpp \
	dnd/dungeon/jbmazemask.cpp \
	dnd/dungeon/jbdungeon.cpp \
	dnd/dungeon/jbdungeondata.cpp \
	dnd/dungeon/jbdungeonpainter.cpp \
	dnd/dungeon/jbdungeonpaintergd.cpp \
	dnd/src/dndutil.c \
	util/writetem.c \
	util/wtstream.c \
	util/gameutil.c \
	util/grammar.c \
	../qDecoder/qDecoder.c

dungeon.cgi: makefile $(WEBOBJS)
	g++ -O3 $(OPTS) -o dungeon.cgi $(WEBOBJS) $(LIBS)

