/*
 * Table.c
 *
 *  Created on: Oct 12, 2018
 *      Author: mijaz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Table.h"
#include "Stack.h"
#include <stdbool.h>


void fill_Input_Symbols(Table table) {
	for (int i=0; i<10; i++) {
		int zero_ascii = '0';
		table -> input_symbols[i] = (char) (zero_ascii + i);
	}
	table -> input_symbols[10] = '(';
	table -> input_symbols[11] = ')';
	table -> input_symbols[12] = '*';
	table -> input_symbols[13] = '/';
	table -> input_symbols[14] = '+';
	table -> input_symbols[15] = '-';
	table -> input_symbols[16] = 'e';
}

void fill_Category_Symbols(Table table) {
	table -> category_symbols[0] = "<E>";
	table -> category_symbols[1] = "<TT>";
	table -> category_symbols[2] = "<T>";
	table -> category_symbols[3] = "<FT>";
	table -> category_symbols[4] = "<F>";
	table -> category_symbols[5] = "<N>";
	table -> category_symbols[6] = "<NT>";
	table -> category_symbols[7] = "<D>";
}

//productions are stored in reverse order because
//they will be pushed to stack in reverse order
void fill_Productions_In_Reverse_Order(Table table) {
	table -> productions[0] = "0";
	table -> productions[1] = "1";
	table -> productions[2] = "2";
	table -> productions[3] = "3";
	table -> productions[4] = "4";
	table -> productions[5] = "5";
	table -> productions[6] = "6";
	table -> productions[7] = "7";
	table -> productions[8] = "8";
	table -> productions[9] = "9";
	table -> productions[10] = "e";
	table -> productions[11] = "<N>";
	table -> productions[12] = "<NT>,<D>";
	table -> productions[13] = "<TT>,<T>";
	table -> productions[14] = "<TT>,<T>,+";
	table -> productions[15] = "<TT>,<T>,-";
	table -> productions[16] = "<FT>,<F>";
	table -> productions[17] = "),<E>,(";
	table -> productions[18] = "<FT>,<F>,*";
	table -> productions[19] = "<FT>,<F>,/";
}

void fill_Row_Table_Driver(Table table, int row, int from, int to, int val) {
	for (int i=from; i<=to; i++) {
		table -> table_driver[row][i] = val;
	}
}

void fill_Table_Driver(Table table) {
	//fill row 0
	fill_Row_Table_Driver(table, 0, 0, 10, 13);
	fill_Row_Table_Driver(table, 0, 11, 16, -1);

	//fill row 1
	fill_Row_Table_Driver(table, 1, 0, 13, -1);
	table -> table_driver[1][14] = 14;
	table -> table_driver[1][15] = 15;
	table -> table_driver[1][16] = 10;

	//fill row 2
	fill_Row_Table_Driver(table, 2, 0, 10, 16);
	fill_Row_Table_Driver(table, 2, 11, 16, -1);

	//fill row 3
	fill_Row_Table_Driver(table, 3, 0, 11, -1);
	table -> table_driver[3][12] = 18;
	table -> table_driver[3][13] = 19;
	fill_Row_Table_Driver(table, 3, 14, 15, -1);
	table -> table_driver[3][16] = 10;

	//fill row 4
	fill_Row_Table_Driver(table, 4, 0, 9, 11);
	table -> table_driver[4][10] = 17;
	fill_Row_Table_Driver(table, 4, 11, 16, -1);

	//fill row 5
	fill_Row_Table_Driver(table, 5, 0, 9, 12);
	fill_Row_Table_Driver(table, 5, 10, 16, -1);

	//fill row 6
	fill_Row_Table_Driver(table, 6, 0, 9, 11);
	fill_Row_Table_Driver(table, 6, 10, 15, -1);
	table -> table_driver[6][16] = 10;

	//fill row 7
	for (int i=0; i<10; i++) {
		table -> table_driver[7][i] = i;
	}
	fill_Row_Table_Driver(table, 7, 10, 16, -1);
}

void fill_Table(Table table) {
	fill_Input_Symbols(table);
	fill_Category_Symbols(table);
	fill_Productions_In_Reverse_Order(table);
	fill_Table_Driver(table);
}

void print_Table(Table table) {
	for (int i=0; i<8; i++) {
		for (int j=0; j<17; j++) {
			printf("%i\t", table -> table_driver[i][j]);
		}
		printf("\n");
	}
}

Table new_Table() {
	Table this = (Table) malloc(sizeof(struct Table));

	this -> table_driver = (int**) calloc(8, sizeof(int*));
	for (int i=0; i<8; i++) {
		this -> table_driver[i] = (int*) calloc(17, sizeof(int));
	}

	this -> input_symbols = (char*) calloc(17, sizeof(char));

	this -> category_symbols = (char**) calloc(8, sizeof(char*));
	for (int i=0; i<8; i++) {
		this -> category_symbols[i] = (char*) calloc(4, sizeof(char));
	}

	this -> productions = (char**) calloc(20, sizeof(char*));
	for (int i=0; i<20; i++) {
		this -> productions[i] = (char*) calloc(10, sizeof(char));
	}

	fill_Table(this);

	return this;
}
