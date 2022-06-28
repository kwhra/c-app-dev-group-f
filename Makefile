GCC = gcc
GCCFLAGS = -lglut -lGLU -lGL -lm

PROG = groupf
PROGOBJ = game_client.o

$(PROG): $(PROGOBJ)
	$(GCC) -o $@ $(PROGOBJ) $(GCCFLAGS)

.SUFFIXES: .c .o

.c.o:
	$(GCC) $(GCCFLAGS) -c $<

clean:
	rm -f $(PROG)
	rm -f *.o