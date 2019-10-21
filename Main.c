/*
 * Main.c
 *
 *  Created on: Oct 8, 2018
 *      Author: mijaz
 */

#include "RecursiveDescent.h"
#include "TableDriven.h"
#include "Calculator.h"
#include <string.h>
#include <stdio.h>
#include "Structs.h"

void expr() {


	while(1) {

		printf("\n----------------------------------\n");

		printf("Enter a mathematical expression to be evaluated or quit to exit\n");
		char input[128];
		fgets(input,100,stdin);
		input[strlen(input) - 1] = '\0';
		if (!strcmp(input, "quit")) {
			return;
		}

		State s = new_State(input);
		Node tree = E_func(s);

		bool valid = false;

		if (tree != NULL && s -> expression[s -> idx] == '\0') {

			printf("Parse Tree generated from Recursive Descent:\n");
			printTree(tree);
			printf("\n\n\nEvaluation = %s\n\n", compute(tree));
			valid = true;

		}

		Node tree2;

		if (evaluate(input, &tree2)) {

			printf("Parse Tree generated from Table Driven Parsing:\n");
			printTree(tree2);
			printf("\n\n\nEvaluation = %s\n\n", compute(tree2));
			valid = true;

		}

		if (!valid) {
			printf("This is an invalid mathematical expression according to our grammar\n");
		}

	}

}


int main(int argc, char* argv[]) {

	expr();

}
