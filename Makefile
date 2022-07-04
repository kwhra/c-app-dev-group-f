GCC = gcc
GCCFLAGS = -lglut -lGLU -lGL -lm

PROG = groupf
PROGOBJ = score.o result.o timelimit.o game.o game_client.o

$(PROG): $(PROGOBJ)
	$(GCC) -o $@ $(PROGOBJ) $(GCCFLAGS)

.SUFFIXES: .c .o

.c.o:
	$(GCC) $(GCCFLAGS) -c $<

clean:
	rm -f $(PROG)
	rm -f *.o