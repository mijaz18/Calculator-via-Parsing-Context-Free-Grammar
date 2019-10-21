/*
 * Main.c
 *
 *  Created on: Oct 4, 2018
 *      Author: mijaz
 */

/*
 * <D> -> 0 | 1 | 2 | ... | 9
 * <NT> -> <N> | e
 * <N> -> <D> <NT>
 * <E> -> <T> <TT>
 * <TT> -> + - <T> <TT> | e
 * <T> -> <F> <FT>
 * <F> -> <N> | (<E>)
 * <FT> -> / * <F> <FT> | e
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RecursiveDescent.h"


State new_State(String s) {
	State this = (State) malloc(sizeof(struct State));
	this -> expression = s;
	this -> idx = 0;
	return this;
}

char* getTypeName(Type t)
{
   switch (t)
   {
      case D: return "D";
      case NT: return "NT";
      case N: return "N";
      case E: return "E";
      case TT: return "TT";
      case T: return "T";
      case F: return "F";
      case FT: return "FT";
      case TERMINAL: return ""; //this statement should never get run
      default: return ""; //this statement should never get run
   }
}

Node new_Node(Type type) {
	Node this = (Node) malloc(sizeof(struct Node));
	this -> center = NULL;
	this -> right = NULL;
	this -> left = NULL;
	this -> type = type;
	return this;
}

Node digits_func(State s) {

	if (s -> expression[s -> idx] == '0' || s -> expression[s -> idx] == '1' ||
			s -> expression[s -> idx] == '2' || s -> expression[s -> idx] == '3' ||
			s -> expression[s -> idx] == '4' || s -> expression[s -> idx] == '5' ||
			s -> expression[s -> idx] == '6' || s -> expression[s -> idx] == '7' ||
			s -> expression[s -> idx] == '8' || s -> expression[s -> idx] == '9') {

		Node n = new_Node(D);
		Node child = new_Node(TERMINAL);
		child -> c = s -> expression[s -> idx];

		s -> idx = s -> idx + 1;
		n -> center = child;
		return n;
	}
	return NULL;
}

Node operators_func(State s) {

	if (s -> expression[s -> idx] == '+' || s -> expression[s -> idx] == '-' ||
			s -> expression[s -> idx] == '*' || s -> expression[s -> idx] == '/') {
		Node n = new_Node(TERMINAL);
		n -> c = s -> expression[s -> idx];

		s -> idx = s -> idx + 1;
		return n;
	}
	return NULL;
}

Node epsilon_func() {
	Node n = new_Node(TERMINAL);
	n -> c = 'e';
	return n;
}

Node E_func(State s) {
	Node lc = T_func(s);
	if (lc == NULL) {
		return NULL;
	}

	Node rc = TT_func(s);
	if (rc == NULL) {
		return NULL;
	}

	Node n = new_Node(E);
	n -> left = lc;
	n -> right = rc;

	return n;
}

Node N_func(State s) {
	Node lc = digits_func(s);
	if (lc == NULL) {
		return NULL;
	}
	Node rc = NT_func(s);
	if (rc == NULL) {
		return NULL;
	}

	Node n = new_Node(N);
	n -> left = lc;
	n -> right = rc;
	return n;
}


Node F_func(State s) {

	int save = s -> idx;

	//possibility one
	Node p1 = N_func(s);
	if (p1 != NULL) {
		Node n = new_Node(F);
		n -> center = p1;
		return n;
	}

	//possibility two
	s -> idx = save;

	if (s -> expression[s -> idx] != '(') {
		return NULL;
	}

	s -> idx = s -> idx + 1;

	Node p2 = E_func(s);
	if (p2 == NULL) {
		return NULL;
	}

	if (s -> expression[s -> idx] != ')') {
		return NULL;
	}

	s -> idx = s -> idx + 1;

	Node n = new_Node(F);
	n -> left = new_Node(TERMINAL);
	n -> left -> c = '(';
	n -> center = p2;
	n -> right = new_Node(TERMINAL);
	n -> right -> c = ')';

	return n;
}



Node FT_func(State s) {

	int save = s -> idx;

	//possibility one
	if (s -> expression[s -> idx] == '*' || s -> expression[s -> idx] == '/') {
		Node n = new_Node(FT);
		n -> left = operators_func(s);

		n -> center = F_func(s);
		n -> right = FT_func(s);

		if (n -> center != NULL && n -> right != NULL) {
			return n;
		}
	}

	//possibility two
	s -> idx = save;

	Node n = new_Node(FT);
	n -> center = epsilon_func();
	return n;
}

Node T_func(State s) {

	Node lc = F_func(s);
	if (lc == NULL) {
		return NULL;
	}
	Node rc = FT_func(s);
	if (rc == NULL) {
		return NULL;
	}

	Node n = new_Node(T);
	n -> left = lc;
	n -> right = rc;
	return n;
}

Node TT_func(State s) {

	int save = s -> idx;

	//possibility one
	if (s -> expression[s -> idx] == '+' || s -> expression[s -> idx] == '-') {
		Node n = new_Node(TT);
		n -> left = operators_func(s);

		n -> center = T_func(s);
		n -> right = TT_func(s);

		if (n -> center != NULL && n -> right != NULL) {
			return n;
		}
	}

	//possibility two
	s -> idx = save;

	Node n = new_Node(TT);
	n -> center = epsilon_func();
	return n;
}

Node NT_func(State s) {

	int save = s -> idx;

	//possibility one
	Node p1 = N_func(s);
	if (p1 != NULL) {
		Node n = new_Node(NT);
		n -> center = p1;
		return n;
	}

	//possibility two
	s -> idx = save;
	Node p2 = epsilon_func();
	if (p2 != NULL) {
		Node n = new_Node(NT);
		n -> center = p2;
		return n;
	}

	//possibility three
	return NULL;
}

void printTabs(int numTabs) {
	for (int i=0; i<numTabs; i++) {
		printf("\t");
	}
}

void printTreeHelper(Node n, int numTabs) {

	if (n != NULL) {
		printTabs(numTabs);

		if (n -> type != TERMINAL) {
			printf("%s", getTypeName(n -> type));
			printf("\n");
			printTreeHelper(n->left, numTabs+1);
			printTreeHelper(n->center, numTabs+1);
			printTreeHelper(n->right, numTabs+1);
		} else {
			printf("%c", n -> c);
			printf("\n");
		}
	}

}

void printTree(Node n) {
	printTreeHelper(n, 0);
}
