GCC = gcc
BUILDFLAG = -lglut -lGLU -lGL -lm
DEPFLAG = -MM -MP -MF

PLAY = player
PLAYSRC = hit_action.c ground.c player.c main.c 
PLAYOBJ = $(PLAYSRC:%.c=%.o)
PLAYDEP = $(PLAYSRC:%.c=%.d)

MOVE1 = move1
MOVE1SRC = carrot.c objectmove_bkup.c
MOVE1OBJ = $(MOVE1SRC:%.c=%.o)
MOVE1DEP = $(MOVE1SRC:%.c=%.d)

MOVE = move
MOVESRC = carrot.c diamond.c objects.c objects_draw.c objects_move.c
MOVEOBJ = $(MOVESRC:%.c=%.o)
MOVEDEP = $(MOVESRC:%.c=%.d)

PROG = groupf
PROGSRC = hit.c hit_action.c ground.c player.c\
carrot.c diamond.c objects.c objects_draw.c objects_move.c\
score.c result.c timeleft.c game.c game_client.c
PROGOBJ = $(PROGSRC:%.c=%.o)
PROGDEP = $(PROGSRC:%.c=%.d)

PROGS = $(PROG) $(MOVE) $(MOVE1) $(PLAY)
OBJS = $(PROGOBJ) $(MOVEOBJ) $(MOVE1OBJ) $(PLAYOBJ)
DEPS = $(PROGDEP) $(MOVEDEP) $(MOVE1DEP) $(PLAYDEP)

$(PROG): $(PROGOBJ) 
	$(GCC) -o $@ $(PROGOBJ) $(BUILDFLAG)

$(MOVE): $(MOVEOBJ)
	$(GCC) -o $@ $(MOVEOBJ) $(BUILDFLAG)

$(MOVE1): $(MOVE1OBJ)
	$(GCC) -o $@ $(MOVE1OBJ) $(BUILDFLAG)

$(PLAY): $(PLAYOBJ)
	$(GCC) -o $@ $(PLAYOBJ) $(BUILDFLAG)


%.o: %.c
	${GCC} $< $(DEPFLAG) $*.d
	${GCC} -c $< -o $@

ifeq ($(findstring clean,${MAKECMDGOALS}),)
-include ${DEPS}
endif

.PHONY: clean
clean:
	rm -f $(PROGS) $(OBJS) $(DEPS)