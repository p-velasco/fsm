CFLAGS = -ansi -pedantic -Wall -Werror

test: fsm-test coffee-test

coffee-test.o: fsm.h

fsm-test.o : fsm.h

.PHONY: clean
clean:
	rm *.o fsm-test coffee-test
