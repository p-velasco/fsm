#include <stdio.h>
#include "fsm.h"

typedef struct {
	Fsm _parent;
	int i;
} FsmTest;

typedef struct {
	Event _parent;
	char e;
} EventTest;

enum {EVENT_A, EVENT_B};

FsmState fsmTestInit(FsmTest *);
void fsmTestStateA(FsmTest *, const EventTest *);
void fsmTestStateB(FsmTest *, const EventTest *);

FsmState fsmTestInit(FsmTest *fsm)
{
	fsm->i = 0;
	return (FsmState) &fsmTestStateA;
}

void fsmTestStateA(FsmTest *fsm, const EventTest *event)
{
	switch (((Event *)event)->id) {
		case EVENT_A:
			if (fsm->i < 10) fsm->i++;
			printf("STATE A, EVENT A, %d\n", (fsm->i));
			break;
		case EVENT_B:
			printf("STATE A, EVENT B, %d\n", (fsm->i));
			fsmTransition(fsm, &fsmTestStateB);
			break;
	}
}

void fsmTestStateB(FsmTest *fsm, const EventTest *event)
{
	switch (((Event *)event)->id) {
		case EVENT_A:
			printf("STATE B, EVENT A, %d\n", (fsm->i));
			fsmTransition(fsm, &fsmTestStateA);
			break;
		case EVENT_B:
			if (fsm->i > 0) fsm->i--;
			printf("STATE B, EVENT B, %d\n", (fsm->i));
			break;
	}
}

int main (void)
{
	FsmTest machine;
	EventTest event;
	int c;

	fsmCreate(&machine, &fsmTestInit);

	while(1) {
		c = getc(stdin);
		switch (c) {
			case 'a':
				event._parent.id = EVENT_A;
				break;
			case 'b':
				event._parent.id = EVENT_B;
				break;
			default:
				return 0;
		}
		fsmDispatch(&machine, &event);
	}
}
