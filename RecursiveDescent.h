/*
 * RecursiveDescent.h
 *
 *  Created on: Oct 8, 2018
 *      Author: mijaz
 */

#include "Structs.h"

#ifndef RECURSIVEDESCENT_H_
#define RECURSIVEDESCENT_H_


extern Node new_Node(Type t);
extern State new_State(String s);
extern Node NT_func(State s);
extern Node N_func(State s);
extern Node E_func(State s);
extern Node TT_func(State s);
extern Node T_func(State s);
extern Node F_func(State s);
extern Node FT_func(State s);
extern Node epsilon_func();
extern Node digits_func(State s);
extern Node operators_func(State s);
extern void printTree(Node n);
extern String getTypeName(Type t);

#endif /* RECURSIVEDESCENT_H_ */
