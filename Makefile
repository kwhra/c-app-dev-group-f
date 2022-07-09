GCC = gcc
BUILDFLAG = -lglut -lGLU -lGL -lm
DEPFLAG = 

MOVE = move
MOVESRC = 
MOVEOBJ = $(MOVESRC:%.c=%.o)
MOVEDEP = $(MOVESRC:%.c=%.d)

PROG = groupf
PROGSRC = carrot.c diamond.c objects.c objects_draw.c objects_move.c\
score.c result.c timeleft.c game.c game_client.c
PROGOBJ = $(PROGSRC:%.c=%.o)
PROGDEP = $(PROGSRC:%.c=%.d)

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