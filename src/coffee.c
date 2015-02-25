#include <stdio.h>
#include "fsm.h"
#include "coffee.h"

static void fsmCoffeeIdle(FsmCoffee *, const EventCoffee *);
static void fsmCoffeeWaitButton(FsmCoffee *, const EventCoffee *);
static void fsmCoffeeServeCup(FsmCoffee *, const EventCoffee *);
static void fsmCoffeeServeCoffee(FsmCoffee *, const EventCoffee *);
static void fsmCoffeeServeMilk(FsmCoffee *, const EventCoffee *);

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
			printf("Dispense cup");
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
			printf("Dispense milk\n");
			printf("Starting timer\n");
			fsmTransition(fsm, &fsmCoffeeServeMilk);
			break;
	}
}

void fsmCoffeeServeMilk(FsmCoffee *fsm, const EventCoffee *event)
{
	switch (((Event *)event)->id) {
		case TIMEOUT_EVENT:
			printf("Coffee served\n");
			printf("Charging money\n");
			fsmTransition(fsm, &fsmCoffeeIdle);
			break;
	}
}
