CFLAGS = -ansi -pedantic -Wall -Werror
TESTS = fsm-test coffee-test

test: $(TESTS)

coffee-test: coffee.o

coffee-test.o: fsm.h coffee.h

fsm-test.o : fsm.h

.PHONY: clean
clean:
	rm *.o $(TESTS)
