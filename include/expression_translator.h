
#include <string>
#include <iostream>
#include "Stack.h" 


using namespace std;

enum TypeElement {
	Operation,
	UnarOp,
	Value,
	dValue
};

class Lexema {
	string str;
	TypeElement type;
public:
	Lexema(string _str = " ", TypeElement _type = Value) : str(_str), type(_type) {};

	bool operator==(const Lexema& l) const
	{
		return (str == l.str && type == l.type);
	}

	bool operator!=(const Lexema& l) const
	{
		return !(str == l.str && type == l.type);
	}


	string getStr()
	{
		return str;
	}
	TypeElement getType()
	{
		return type;
	}

	int priority()
	{
		string op = "()+-*/";
		if (type == Value)
			throw "exeption";
		if (type == UnarOp)
			return 4;
		return op.find(str) / 2; //íîìåð îïåðàöèè â ñòðîêå op äåëèòü íà 2
	}
	friend ostream& operator << (ostream& out, Lexema& p) {
		out << "{" << p.str << ", ";
		if (p.type == Operation) {
			out << "operation";
		}
		else if (p.type == Value) {
			out << "value";
		};
		out << "}";
		return out;
	}
};



void print(Queue <Lexema> t) {
	while (!t.IsEmpty()) {
		cout << t.Top() << endl;
		t.Pop();
	}
	cout << endl;
}

class LexAnalysis { // ñòðîêó ïðåîáðàçîâàòü â î÷åðåäü èç ëåêñåì
	Queue<Lexema> problem;
public:
	Queue <Lexema> lex(string input) {
		Queue<Lexema>res;
		input += ' ';
		int i = 0;
		int flag = 0;
		string tmp = "";
		string op = "+-*/()";
		//string uop = "-";
		string sep = " \n\t";
		int state = 0;// åñëè state 0 , òî íà ïðîøëîì øàãå íå áûëî ÷èñëî, åñëè 1-òî çàïèñûâàëè ÷èñëëî íà ïðîøëîì øàãå.
		for (i = 0; i < input.size(); i++) {
			char c = input[i];
			int fres;
			switch (state)
			{
			case 0:
				if (c >= '0' && c <= '9') {
					tmp = c;
					state = 1;
					break;
				}
				if (c == '.') {
					tmp = c;
					state = 3;
					break;
				}
				fres = op.find(c);// ñîäåðæèòñÿ ëè ñ â ñòðîêå op   // ÂÎÇÂÐÀÙÀÅÒ -1 ÅÑËÈ ñ íå âõîäèò â op
				if (fres >= 0) {
					tmp = c;

					if (c == '-')
					{
						flag = 1;
						if (!res.IsEmpty()) {
							Lexema l("+", Operation);
							res.Push(l);
						}
						Lexema l1("(", Operation);
						res.Push(l1);
						Lexema l2("0", Value);
						res.Push(l2);
						Lexema l3("-", Operation);
						res.Push(l3);
					}
					else
					{
						Lexema l(tmp, Operation);
						res.Push(l);
					}
					state = 2;
					break;
				}
				
				fres = sep.find(c);
				if (fres >= 0) {
					tmp = "";
					break;
				}
				if (c == ')') {
					tmp = c;
					Lexema l(tmp, Operation);
					res.Push(l);
					state = 0;
					break;
				}
				throw "unexpected lex";
				break;
			case 1:
				if (c >= '0' && c <= '9') {
					tmp += c;
					state = 1;
					break;
				}
				fres = op.find(c);
				if (fres >= 0) {
					Lexema l(tmp, Value);
					res.Push(l);
					if (flag)
					{
						Lexema l69(")", Operation);
						res.Push(l69);
						flag = 0;
					}
					tmp = c;
					if (c == '-')
					{
						flag = 1;
						Lexema l0("+", Operation);
						res.Push(l0);
						Lexema l1("(", Operation);
						res.Push(l1);
						Lexema l2("0", Value);
						res.Push(l2);
						Lexema l3("-", Operation);
						res.Push(l3);
					}
					else
					{
						Lexema l0(tmp, Operation);
						res.Push(l0);
					}
					state = 2;
					break;
				}
				fres = sep.find(c);
				if (fres >= 0) {
					Lexema l(tmp, Value);
					res.Push(l);
					if (flag)
					{
						Lexema l69(")", Operation);
						res.Push(l69);
						flag = 0;
					}
					state = 0;
					break;
				}
				if (c == '.') {
					tmp += c;
					state = 3;
					break;
				}
				throw "unexpected lex";
			case 2:
				if (c >= '0' && c <= '9') {
					tmp = c;
					state = 1;
					break;
				}
				if (c == '.') {
					tmp = c;
					state = 3;
					break;
				}
				
				fres = op.find(c);
				if (fres >= 0) {
					tmp = c;
					if (c == '-')
					{
						flag = 1;
						Lexema l1("(", Operation);
						res.Push(l1);
						Lexema l2("0", Value);
						res.Push(l2);
						Lexema l3("-", Operation);
						res.Push(l3);
					}
					else
					{
						Lexema l0(tmp, Operation);
						res.Push(l0);
					}
					if (c == ')') state = 0;
					else
						state = 2;
					break;
				}
				fres = sep.find(c);
				if (fres >= 0) {
					tmp = "";
					break;
				}
				throw "unexpected lex";
			case 3:
				if (c >= '0' && c <= '9') {
					tmp += c;
					state = 4;
					break;
				}
				throw "unexpected lex";
			case 4:
				if (c >= '0' && c <= '9') {
					tmp += c;
					break;
				}
				if (c == ')') {
					Lexema l1(tmp, dValue);
					res.Push(l1);
					if (flag)
					{
						Lexema l69(")", Operation);
						res.Push(l69);
						flag = 0;
					}
					tmp = c;
					Lexema l2(tmp, Operation);
					res.Push(l2);
					state = 0;
					break;
				}
				fres = op.find(c);
				if (fres >= 0) {
					Lexema l1(tmp, dValue);
					res.Push(l1);
					if (flag)
					{
						Lexema l69(")", Operation);
						res.Push(l69);
						flag = 0;
					}
					tmp = c;
					if (c == '-')
					{
						flag = 1;
						Lexema l0("+", Operation);
						res.Push(l0);
						Lexema l1("(", Operation);
						res.Push(l1);
						Lexema l2("0", Value);
						res.Push(l2);
						Lexema l3("-", Operation);
						res.Push(l3);
					}
					else
					{
						Lexema l0(tmp, Operation);
						res.Push(l0);
					}
					state = 2;
					break;
				}
				fres = sep.find(c);
				if (fres >= 0) {
					Lexema l(tmp, dValue);
					res.Push(l);
					if (flag)
					{
						Lexema l69(")", Operation);
						res.Push(l69);
						flag = 0;
					}
					state = 0;
					break;
				}
			default:
				break;
			}

		}
		return res;
	}

	LexAnalysis(string s = "") : problem(lex(s)) {};
	Queue<Lexema>& getproblem()
	{
		return problem;
	}

};



class exc { //ïîêàçûâàåò îøèáêó è íà êàêîé ïîçèöèè
	string str;
	int index;
public:
	exc(string s, int i) : str(s), index(i) {}
	friend ostream& operator<<(ostream& out, exc e)
	{
		out << e.str << e.index << endl;
		return out;
	}
};

class SyntaxAnalysis
{

	void CorrectCheck(Queue<Lexema> p) {
		int flag = 0;
		int iter = 1;
		Lexema prev = p.Top();
		p.Pop();
		if (prev.getStr() == "(") flag++;
		if (prev.getStr() == ")")
			throw exc("incorrect ')' operation before '(' in pos ", iter);
		iter++;
		while (!p.IsEmpty())
		{
			if (prev.getType() == p.Top().getType())// ïðîâåðêà íà 2 ïîäðÿä îäèíàêîâûå ëåêñåìû
				if (prev.getStr() != "(" && prev.getStr() != ")" && p.Top().getStr() != "(" && p.Top().getStr() != ")")
				{
					throw exc("expected diff type of lexem in pos ", iter);
				}
			prev = p.Top();
			p.Pop();
			if (prev.getStr() == "(") flag++;
			if (prev.getStr() == ")")
			{
				flag--;
				if (flag < 0)
				{
					throw exc("incorrect ')' operation before '(' in pos ", iter);
				}
			}
			iter++;
		}

		if (flag)
		{
			throw exc("number of '(' not equal to ')' ", -1);
		}
	}

public:
	SyntaxAnalysis() {};
	Queue<Lexema> rev(Queue<Lexema> clone)// èç îáû÷íîé â ïîñòôèêñíóþ
	{
		try { CorrectCheck(clone); }
		catch (exc e) { cout << e; throw - 1; }

		Queue<Lexema> reverse;
		Stack<Lexema> st;
		while (!clone.IsEmpty())
		{
			if (clone.Top().getType() == Value || clone.Top().getType() == dValue)
			{
				reverse.Push(clone.Top());
			}
			if (clone.Top().getType() == Operation)
			{
				if (clone.Top().getStr() == "(") st.Push(clone.Top());
				else if (clone.Top().getStr() == ")")
				{
					while (st.Top().priority() != clone.Top().priority())
						reverse.Push(st.Pop());
					st.Pop();
				}
				else
				{
					while ((!st.IsEmpty()) && (st.Top().priority() >= clone.Top().priority()))
					{
						reverse.Push(st.Pop());
					}
					st.Push(clone.Top());
				}
			}
			clone.Pop();
		}
		while (!st.IsEmpty())
			reverse.Push(st.Pop());
		return reverse;
	}
};

int str_to_int(string s)
{
	int res = 0;
	for (int i = 0; i < s.length(); i++)
		res = res * 10 + s[i] - '0';
	return res;
}

class Calculator
{
public:
	Calculator() {};
	double calculate(Queue<Lexema> p)
	{
		Stack<double> st;
		while (!p.IsEmpty())
		{
			if (p.Top().getType() == Value)
				st.Push(stod(p.Top().getStr()));
			if (p.Top().getType() == dValue)
				st.Push(stod(p.Top().getStr()));
			
			if (p.Top().getType() == Operation)
			{
				double r = st.Pop();
				double l = st.Pop();
				switch (p.Top().getStr()[0])
				{
				case '+': st.Push(l + r);
					break;
				case '-': st.Push(l - r);
					break;
				case '*': st.Push(l * r);
					break;
				case '/': if (r == 0) throw "divider is 0";
					st.Push(l / r);
					break;
				}
			}
			p.Pop();
		}
		return st.Top();
	}
};

class parser {
	LexAnalysis Lex;
	SyntaxAnalysis St;
	Calculator calc;
	string problem;
	Queue<Lexema> straight_func;
	Queue<Lexema> reverse_func;
	int answer;
public:
	parser(string s = "") : problem(s), answer(NAN) {};
	void setProblem(string s) { problem = s; answer = NAN; }
	void calculate_all()
	{
		straight_func = Lex.lex(problem);
		reverse_func = St.rev(straight_func);
		answer = calc.calculate(reverse_func);
	}
	string getProblem()
	{
		return problem;
	}
	double getAnswer()
	{
		if (answer == NAN) calculate_all(); return answer;
	}

};



