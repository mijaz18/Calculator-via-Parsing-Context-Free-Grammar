/*
 * Calculator.h
 *
 *  Created on: Oct 13, 2018
 *      Author: mijaz
 */
#include "Structs.h"

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

extern String compute(Node tree);
extern double stringToDouble(String s);
extern String doubleToString(double d);
extern String concatenate(String s1, String s2, String s3);
extern String charToString(char c);
extern String appendCharToString(String str, char c);
extern double add(String exp);
extern double multiply(String exp);

#endif /* CALCULATOR_H_ */
