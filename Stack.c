/*
 * Stack.c
 *
 *  Created on: Oct 12, 2018
 *      Author: mijaz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RecursiveDescent.h"
#include "Stack.h"

struct StackNode {

	Node tn;
	String data;
	StackNode next;

};

StackNode new_StackNode(String s, StackNode next) {

	StackNode this = (StackNode) malloc(sizeof(struct StackNode));
	this -> tn = (Node) malloc(sizeof(struct Node));
	this -> data = s;
	this -> next = next;
	return this;

}

struct Stack {
	StackNode head;
};

Stack new_Stack() {
	Stack this = (Stack) malloc(sizeof(struct Stack));
	this -> head = NULL;
	return this;
}

Type getTypeFromString(String str) {

	if (!strcmp(str, "<E>")) {
		return E;
	} else if (!strcmp(str, "<D>")) {
		return D;
	} else if (!strcmp(str, "<NT>")) {
		return NT;
	} else if (!strcmp(str, "<N>")) {
		return N;
	} else if (!strcmp(str, "<T>")) {
		return T;
	} else if (!strcmp(str, "<TT>")) {
		return TT;
	} else if (!strcmp(str, "<F>")) {
		return F;
	} else if (!strcmp(str, "<FT>")) {
		return FT;
	} else {
		return TERMINAL;
	}

}

bool isEmpty(Stack s) {
	return s -> head == NULL;
}

void push(Stack s, String k, char c) {

	StackNode temp = new_StackNode(k, s -> head);
	temp -> tn = new_Node(getTypeFromString(k));
	temp -> tn -> c = c;

	s -> head = temp;
}

StackNode pop(Stack s) {

	if (s -> head == NULL) {
		printf("Stack is Empty");
		return NULL;
	}

	StackNode data = s -> head;
	s -> head = s -> head -> next;
	return data;
}

StackNode peek(Stack s) {
	return s -> head;
}
