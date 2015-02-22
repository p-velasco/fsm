#ifndef __LSEL_FSM_H
#define __LSEL_FSM_H

typedef struct Fsm Fsm;
typedef struct Event Event;

/* Pointer to state function */
typedef void (*FsmState)(Fsm *, const Event *);

/* Pointer to init funcion */
typedef FsmState (*FsmInit)(Fsm *);

/* Base Fsm struct */
struct Fsm {
	FsmState state;
};

/* Base Event struct */
struct Event {
	int id;
};

#define fsmCreate(fsm, init) (((Fsm *)(fsm))->state = (init)(fsm))
#define fsmDispatch(fsm, event) (*((Fsm *)(fsm))->state)((Fsm *)(fsm), (Event *)(event))
#define fsmTransition(fsm, dest) (((Fsm *)(fsm))->state = (FsmState)(dest))

#endif
