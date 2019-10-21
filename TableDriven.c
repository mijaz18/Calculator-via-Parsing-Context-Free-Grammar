/*
 * TableDriven.c
 *
 *  Created on: Oct 8, 2018
 *      Author: mijaz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TableDriven.h"
#include "Table.h"
#include "Stack.h"
#include <stdbool.h>

struct StackNode {

	Node tn;
	String data;
	StackNode next;

};


struct State2 {
	Stack stack;
	String expression;
	int idx;
};


State2 new_State2(String expression) {
	State2 this = (State2) malloc(sizeof(struct State2));
	this -> stack = new_Stack();
	push(this -> stack, "<E>", ' ');
	this -> expression = expression;
	this -> idx = 0;
	return this;
}

int get_Category_Index(String category, Table table) {
	for (int i=0; i<8; i++) {
		if (!strcmp(table -> category_symbols[i], category)) {
			return i;
		}
	}
	return -1;
}

int get_Symbol_Index(Table table, char c) {
	for (int i=0; i<17; i++) {
		if (table -> input_symbols[i] == c) {
			return i;
		}
	}
	return -1;
}

String get_Production(Table table, String category, char c) {


	//this is necessary because 0 is the same as null in c
	if (c == '\0') {
		return NULL;
	}

	int row = get_Category_Index(category, table);
	int col = get_Symbol_Index(table, c);

	int production = table -> table_driver[row][col];

	if (production == -1) {
		return NULL;
	}

	return table -> productions[production];
}

bool isTerminal(String category) {
	if (!strcmp(category, "(") || !strcmp(category, ")")
			|| !strcmp(category, "0") || !strcmp(category, "1")
			|| !strcmp(category, "2") || !strcmp(category, "3")
			|| !strcmp(category, "4") || !strcmp(category, "5")
			|| !strcmp(category, "6") || !strcmp(category, "7")
			|| !strcmp(category, "8") || !strcmp(category, "9")
			|| !strcmp(category, "+") || !strcmp(category, "-")
			|| !strcmp(category, "/") || !strcmp(category, "*")){
		return true;
	}

	return false;
}


bool evaluate(String expression, Node* n) {

	State2 s = new_State2(expression);
	Table t = new_Table();
	*n = (peek(s -> stack) -> tn);
	//printf("%s", getTypeName(n -> type));
	//return true;


	while (true) {

		StackNode top = pop(s -> stack);
		String category = top -> data;
		Node node = top ->tn;
		node -> c = s -> expression [s -> idx];

		//printf("%s", getTypeName(node ->type));

		if (!strcmp(category, "e")) {
			//do nothing
			node -> c = 'e';
		}

		else if (isTerminal(category)) {

			if (category[0] == s -> expression [s -> idx]) {
				s -> idx ++;
			}
			else {
				*n = NULL; //return null tree
				return false;
			}

		}

		else {


			String production = get_Production(t, category, s -> expression[s -> idx]);

			if (production == NULL) {
				//try matching epsilon
				production = get_Production(t, category, 'e');
			}

			if (production == NULL) {
				*n = NULL; //return null tree
				return false;
			}

			String str = "";

			int i=0;
			int child = 0;
			while(production[i]!='\0') {
				if (production[i]!=',') {

					//for appending a character to the end of a string
					size_t len = strlen(str);
					char *str2 = malloc(len + 1 + 1 ); //one for extra char, one for '/0'
					strcpy(str2, str);
					str2[len] = production[i];
					str2[len + 1] = '\0';
					str = str2;

				}
				else {
					push(s -> stack, str, ' ');
					str = "";
					if (child == 0) {
						node ->right = peek(s -> stack) -> tn;
					}else if (child == 1) {
						node ->center = peek(s -> stack) -> tn;
					}

					child++;

				}
				i++;
			}
			push(s -> stack, str, ' ');
			node ->left = peek(s -> stack) -> tn;


		}

		//if we have finished reading string
		if (s -> expression[s -> idx] == '\0' && isEmpty(s -> stack)) {

			return true;

		}

	}

}

