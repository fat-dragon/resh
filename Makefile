# $Id: Makefile 1216 2011-12-28 07:39:53Z cross $

O=		o
D=		so

CC=		egcc
RM=		rm
CFLAGS=		-Wall -Werror -g -I. -std=c11
LDFLAGS=	
LIBS=		-lreadline -ltermcap

PROG=		resh
OBJS=		resh.$O dyncmd.$O nav.$O read.$O token.$O util.$O var.$O
EGGS=		eggs/catalog.egg eggs/chad.egg eggs/cls.egg eggs/cmd.egg \
		eggs/dir.egg eggs/head.egg eggs/joshua.egg eggs/porter.egg \
		eggs/push.egg

SHOBJS=		bbs.$D cat.$D clear.$D eggs.$D env.$D fortune.$D help.$D \
		lc.$D ls.$D man.$D passwd.$D pg.$D ps.$D \
		pwd.$D sync.$D unix.$D who.$D

all:		$(PROG) pg

$(PROG):	$(OBJS) $(SHOBJS)
		$(CC) -o $(PROG) $(OBJS) $(LDFLAGS) $(LIBS)

pg:		pg.o util.o
		$(CC) -o pg pg.o util.o $(LDFLAGS) $(LIBS)

eggs.c:		$(EGGS)
		./mkegg $(EGGS) > eggs.c

$(SHOBJS):

clean:
		$(RM) -f $(PROG) $(OBJS) $(SHOBJS) pg pg.o eggs.c

install:	all
		install -c $(SHOBJS) /fat-dragon/lib/resh
		mv /fat-dragon/lib/resh/eggs.so /fat-dragon/lib/resh/eggbasket.so
		install -c resh-help /fat-dragon/lib/resh
		install -c resh /fat-dragon/bin

.SUFFIXES:	.so

.c.$D:
		$(CC) $(CFLAGS) -shared -fPIC $< util.o var.o -o $@ $(LDFLAGS) $(LIBS)
