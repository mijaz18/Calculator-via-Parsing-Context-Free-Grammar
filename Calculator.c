/*
 * Calculator.c
 *
 *  Created on: Oct 13, 2018
 *      Author: mijaz
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Calculator.h"


double stringToDouble(String s) {
	double d;
	sscanf(s, "%lf", &d);
	return d;
}

String doubleToString(double d) {
	String output = (char*) calloc(50, sizeof(char));
	snprintf(output, 50, "%f", d);
	return output;
}

String concatenate(String s1, String s2, String s3) {
	char* str = (char*) calloc(120, sizeof(char));
	strcpy(str, s1);
	strcat(str, s2);
	strcat(str, s3);
	return str;
}

String appendCharToString(String str, char c) {
	int length = strlen(str);
	char *str2 = malloc(length + 1 + 1 ); //one for extra char, one for '\0'
	strcpy(str2, str);
	str2[length] = c;
	str2[length + 1] = '\0';
	return str2;
}

String charToString(char c) {
	char* str = (char*) calloc(2, sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return str;
}

bool isDigit(char c) {
	return c == '0' || c == '1' || c == '2' || c == '3' || c == '4'
			|| c == '5' || c == '6' || c == '7' ||  c == '8' || c == '9';
}

bool canBeAdded(String s) {
	if (s[0] == '-') {
		if (isDigit(s[1])) {
			for (int i=2; i<strlen(s); i++) {
				if (s[i] == '+' || s[i] == '-') {
					return true;
				}
			}
		}
	}
	else {
		if (isDigit(s[0])) {
			for (int i=1; i<strlen(s); i++) {
				if (s[i] == '+' || s[i] == '-') {
					return true;
				}
			}
		}
	}

	return false;
}

bool canBeMultiplied(String s) {
	if (s[0] == '-') {
		if (isDigit(s[1])) {
			for (int i=2; i<strlen(s); i++) {
				if (s[i] == '*' || s[i] == '/') {
					return true;
				}
			}
		}
	}
	else {
		if (isDigit(s[0])) {
			for (int i=1; i<strlen(s); i++) {
				if (s[i] == '*' || s[i] == '/') {
					return true;
				}
			}
		}
	}

	return false;
}

double add(String exp) {
	double soFar = 0;
	String build = "";

	for (int i=0; i<strlen(exp); i++) {
		if (exp[i] == '+') {
			soFar += stringToDouble(build);
			build = "";
		}
		else if (exp[i] == '-') {
			soFar += stringToDouble(build);
			build = "-";
		}
		else {
			build = appendCharToString(build, exp[i]);
		}
	}

	soFar += stringToDouble(build);

	return soFar;
}

double multiply(String exp) {
	double soFar = 0;
	String build = "";
	bool firstNum = true;
	bool multiply = true;

	for (int i=0; i<strlen(exp); i++) {
		if (exp[i] == '*') {
			if (firstNum) {
				soFar = stringToDouble(build);
				firstNum = false;
			}
			else {
				if (multiply) {
					soFar *= stringToDouble(build);
				}
				else {
					soFar /= stringToDouble(build);
				}
			}
			build = "";
			multiply = true;
		}
		else if (exp[i] == '/') {
			if (firstNum) {
				soFar = stringToDouble(build);
				firstNum = false;
			}
			else {
				if (multiply) {
					soFar *= stringToDouble(build);
				}
				else {
					soFar /= stringToDouble(build);
				}
			}
			build = "";
			multiply = false;
		}
		else {
			build = appendCharToString(build, exp[i]);
		}
	}

	if (multiply) {
		soFar *= stringToDouble(build);
	}
	else {
		soFar /= stringToDouble(build);
	}

	return soFar;
}


String compute(Node tree) {

	if (tree == NULL) {
		return "";
	}

	String lc = compute(tree -> left);
	String mc = compute(tree -> center);
	String rc = compute(tree -> right);
	String exp = concatenate(lc, mc, rc);

	switch(tree -> type) {

		case E:
			if (canBeAdded(exp)) {
				double sum = add(exp);
				return doubleToString(sum);
			}
			else {
				return exp;
			}
		case T:
			if (canBeMultiplied(exp)) {
				double prod = multiply(exp);
				return doubleToString(prod);
			}
			else {
				return exp;
			}
		case F:
			if (lc[0] == '(') {
				return mc;
			}
			else {
				return exp;
			}
		case FT:
			if (exp[0] == 'e') {
				return "";
			}
			else {
				return exp;
			}
		case TT:
			if (exp[0] == 'e') {
				return "";
			}
			else {
				return exp;
			}
		case N:
			return exp;
		case NT:
			if (exp[0] == 'e') {
				return "";
			}
			else {
				return exp;
			}
		case D:
			return exp;
		case TERMINAL:
			return charToString(tree -> c);
		default: return ""; //this statement should never get run

	}
}
