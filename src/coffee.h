#ifndef __LSEL_COFFEE_H
#define __LSEL_COFFEE_H

#include "fsm.h"

typedef struct {
	Fsm _parent;
} FsmCoffee;

typedef struct {
	Event _parent;
} EventCoffee;

typedef enum {MONEY_EVENT, BUTTON_EVENT, TIMEOUT_EVENT} CoffeeEvents;

FsmState fsmCoffeeInit(FsmCoffee *);

#endif
