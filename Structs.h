/*
 * Structs.h
 *
 *  Created on: Oct 15, 2018
 *      Author: mijaz
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_
typedef char* String;

typedef enum Type Type;
typedef struct State* State;
typedef struct Table* Table;
typedef struct Node* Node;

enum Type {
	D, NT, N, E, TT, T, F, FT, TERMINAL
};

struct Node {
	Type type;
	char c;
	Node left;
	Node center;
	Node right;
};

struct State {

	char* expression;
	int idx;

};

struct Table {

	int **table_driver;

	char* input_symbols;
	char** category_symbols;
	char** productions;

};

#endif /* STRUCTS_H_ */
