#include <stdio.h>
#include "fsm.h"
#include "coffee.h"

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
