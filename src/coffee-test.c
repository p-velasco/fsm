#include <stdio.h>
#include "fsm.h"

typedef struct {
	Fsm _parent;
} FsmCoffee;

typedef struct {
	Event _parent;
} EventCoffee;

enum {MONEY_EVENT, BUTTON_EVENT, TIMEOUT_EVENT};

FsmState fsmCoffeeInit(FsmCoffee *);
void fsmCoffeeIdle(FsmCoffee *, const EventCoffee *);
void fsmCoffeeWaitButton(FsmCoffee *, const EventCoffee *);
void fsmCoffeeServeCup(FsmCoffee *, const EventCoffee *);
void fsmCoffeeServeCoffee(FsmCoffee *, const EventCoffee *);

FsmState fsmCoffeeInit(FsmCoffee *fsm)
{
	return (FsmState) &fsmCoffeeIdle;
}

void fsmCoffeeIdle(FsmCoffee *fsm, const EventCoffee *event)
{
	switch (((Event *)event)->id) {
		case MONEY_EVENT:
			printf("Enough money\n");
			fsmTransition(fsm, &fsmCoffeeWaitButton);
			break;
	}
}

void fsmCoffeeWaitButton(FsmCoffee *fsm, const EventCoffee *event)
{
	switch (((Event *)event)->id) {
		case BUTTON_EVENT:
			printf("Button pressed, starting to serve\n");
			printf("Starting timer\n");
			fsmTransition(fsm, &fsmCoffeeServeCup);
			break;
	}
}

void fsmCoffeeServeCup(FsmCoffee *fsm, const EventCoffee *event)
{
	switch (((Event *)event)->id) {
		case TIMEOUT_EVENT:
			printf("Dispense coffee\n");
			printf("Starting timer\n");
			fsmTransition(fsm, &fsmCoffeeServeCoffee);
			break;
	}
}

void fsmCoffeeServeCoffee(FsmCoffee *fsm, const EventCoffee *event)
{
	switch (((Event *)event)->id) {
		case TIMEOUT_EVENT:
			printf("Coffee served\n");
			printf("Charging money\n");
			fsmTransition(fsm, &fsmCoffeeIdle);
			break;
	}
}

int main (void)
{
	FsmCoffee machine;
	EventCoffee event;
	int c;

	fsmCreate(&machine, &fsmCoffeeInit);

	while(1) {
		c = getc(stdin);
		getc(stdin); /* Skip the enter key */
		switch (c) {
			case 'm':
				event._parent.id = MONEY_EVENT;
				break;
			case 'b':
				event._parent.id = BUTTON_EVENT;
				break;
			case 't':
				event._parent.id = TIMEOUT_EVENT;
				break;
			default:
				return 0;
		}
		fsmDispatch(&machine, &event);
	}
}
