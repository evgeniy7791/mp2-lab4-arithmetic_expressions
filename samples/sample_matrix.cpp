// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//


#include <iostream>
#include <string>
#include "expression_translator.h"

using namespace std;


void main()
{
	parser parser;
	string str;
	char flag;
	while (true) {
		str = "";
		flag = ' ';
		cout << "type an expression, type ` to end" << endl;
		while (flag != '`') {
			str += flag;
			cin >> flag;
		}
		if (str == " ") return;
		parser.setProblem(str);
		cout << parser.getAnswer() << endl;
	}
}
