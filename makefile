OBJS =  amaze.o maze.o cell.o queue.o cda.o
MAIN = amaze
OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

all : $(MAIN)

test : $(MAIN)
	./amaze -c 3 3 m.data -s m.data m.solved -d m.solved
	
valgrind : $(MAIN)
	valgrind ./amaze -c 3 3 m.data -s m.data m.solved -d m.solved

amaze : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o amaze

amaze.o : amaze.c amaze.h maze.o
	gcc $(OOPTS) amaze.c

cell.o : cell.c cell.h
	gcc $(OOPTS) cell.c

maze.o : maze.c maze.h cell.o queue.o
	gcc $(OOPTS) maze.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h cda.o
	gcc $(OOPTS) queue.c

da.o : da.c da.h
	gcc $(OOPTS) da.c

cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c

clean	:
		rm -f $(OBJS) $(MAIN)