GCC = gcc
BUILDFLAG = -lglut -lGLU -lGL -lm
DEPFLAG = 

PROG = groupf
PROGSRC = score.c result.c timelimit.c objects.c game.c game_client.c
PROGOBJ = $(PROGSRC:%.c=%.o)
PROGDEP = $(PROGSRC:%.c=%.d)

MOVE = move
MOVESRC = carrot.c diamond.c objects.c objects_draw.c objects_move.c
MOVEOBJ = $(MOVESRC:%.c=%.o)
MOVEDEP = $(MOVESRC:%.c=%.d)

PROGS = $(PROG) $(MOVE)
OBJS = $(PROGOBJ) $(MOVEOBJ)
DEPS = $(PROGDEP) $(MOVEDEP)

$(PROG): $(PROGOBJ)
	$(GCC) -o $@ $(PROGOBJ) $(BUILDFLAG)

$(MOVE): $(MOVEOBJ)
	$(GCC) -o $@ $(MOVEOBJ) $(BUILDFLAG)

%.o: %.c
	${GCC} $< -MM -MP -MF $*.d
	${GCC} -c $< -o $@

ifeq ($(findstring clean,${MAKECMDGOALS}),)
-include ${DEPS}
endif

.PHONY: clean
clean:
	rm -f $(PROGS) $(OBJS) $(DEPS)