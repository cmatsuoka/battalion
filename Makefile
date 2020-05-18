CC       = gcc
CFLAGS   = -O2 -g -Wall -DDATADIR=\"$(DATADIR)\" -DSCOREDIR=\"$(SCOREDIR)\"
LD       = gcc
LDFLAGS  =
INSTALL  = install
BINDIR   = /usr/local/bin
MANDIR   = /usr/local/man/man6
DATADIR  = /usr/local/games/battalion
SCOREDIR = /var/local/battalion
ASSETS   = DATA MUSIC SOUNDS TEXTURES
LIBS     = -lGL -lGLU -lalut -lopenal -lm -lX11 -lXext
OBJS 	 = battalion.o audio.o net.o gprim.o graphics.o objects.o text.o update.o tk.o font.o
BIN      = battalion

.c.o:
	$(CC) -c -o $*.o $(CFLAGS) $<

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(BIN) $(OBJS) *~

install: all
	mkdir -p $(DESTDIR)$(BINDIR) $(DESTDIR)$(MANDIR) $(DESTDIR)$(SCOREDIR)
	$(INSTALL) -s -g games -m 2755 $(BIN) $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 0644 $(BIN).man $(DESTDIR)$(MANDIR)/$(BIN).6
	$(INSTALL) -g games -m 0644 /dev/null $(DESTDIR)$(SCOREDIR)/battalion_hiscore
	for f in $(ASSETS); do \
	    mkdir -p $(DESTDIR)$(DATADIR)/$$f; \
	    $(INSTALL) -m 0644 $$f/* $(DESTDIR)$(DATADIR)/$$f; \
	done

audio.o: audio.c audio.h battalion.h tk.h
battalion.o: battalion.c battalion.h tk.h audio.h
font.o: font.c tk.h
gprim.o: gprim.c gprim.h battalion.h tk.h
graphics.o: graphics.c battalion.h tk.h gprim.h
net.o: net.c battalion.h tk.h
objects.o: objects.c battalion.h tk.h gprim.h
text.o: text.c battalion.h tk.h
tk.o: tk.c battalion.h tk.h
update.o: update.c battalion.h tk.h
