#include "expression_translator.h"

#include <gtest.h>



TEST(parser, priority1)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex("+", Operation);
	EXPECT_EQ(lex.priority(), 1);
}

TEST(parser, priority2)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex("-", Operation);
	EXPECT_EQ(lex.priority(), 1);
}


TEST(parser, priority3)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex("6", Value);
	ASSERT_ANY_THROW(lex.priority());
}

TEST(parser, priority4)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex("*", Operation);
	EXPECT_EQ(lex.priority(), 2);
}

TEST(parser, priority5)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex("/", Operation);
	EXPECT_EQ(lex.priority(), 2);
}

TEST(parser, priority6)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex("(", Operation);
	EXPECT_EQ(lex.priority(), 0);
}

TEST(parser, priority7)
{
	string str = "3 + ( 123 -10)/ 50 *	\t	30 \n";
	Lexema lex(")", Operation);
	EXPECT_EQ(lex.priority(), 0);
}

TEST(parser, Lex1)
{
	string str = "1+2";
	Lexema l("1", Value);
	Lexema m("+", Operation);
	Lexema n("2", Value);
	Queue <Lexema>q;
	q.Push(l);
	q.Push(m);
	q.Push(n);
	LexAnalysis lex;
	EXPECT_EQ(q, lex.lex(str));
}

TEST(parser, syn_analysis)
{
	string str = "1+2";
	Lexema l("1", Value);
	Lexema m("+", Operation);
	Lexema n("2", Value);
	Queue <Lexema>q1;
	Queue <Lexema>q2;
	q1.Push(l);
	q1.Push(m);
	q1.Push(n);
	q2.Push(l);
	q2.Push(n);
	q2.Push(m);
	SyntaxAnalysis lex;
	EXPECT_EQ(q2, lex.rev(q1));
}

TEST(parser, syn_analysis222)
{
	string str = "(1+2)";
	Lexema l("1", Value);
	Lexema m("+", Operation);
	Lexema n("2", Value);
	Queue <Lexema>q2;
	q2.Push(l);
	q2.Push(n);
	q2.Push(m);
	SyntaxAnalysis lex;
	LexAnalysis mark;

	EXPECT_EQ(q2, lex.rev(mark.lex(str)));
}

TEST(parser, rightbasic)
{
	string str = "3 + ( 110 -10)/ 50 *	\t	30 \n";
	cout << str;
	Queue <Lexema> lex_res;
	LexAnalysis l;
	lex_res = l.lex(str);
	print(lex_res);
	SyntaxAnalysis s;
	cout << endl;
	print(s.rev(lex_res));
	Calculator c;
	EXPECT_EQ(c.calculate(s.rev(lex_res)), 63);
}

TEST(parser, rightbasicd)
{
	string str = "3.5 + ( 110.9 -10.4)/ 50 *	\t	30.0 \n";
	cout << str;
	Queue <Lexema> lex_res;
	LexAnalysis l;
	lex_res = l.lex(str);
	print(lex_res);
	SyntaxAnalysis s;
	cout << endl;
	print(s.rev(lex_res));
	Calculator c;
	EXPECT_EQ(c.calculate(s.rev(lex_res)), 63.8);
}

TEST(parser, rightbasicd0)
{
	string str = "-3.5 + ( -110.9 -10.4)/ -50 *	\t	-30.0 \n";
	cout << str;
	Queue <Lexema> lex_res;
	LexAnalysis l;
	lex_res = l.lex(str);
	print(lex_res);
	SyntaxAnalysis s;
	cout << endl;
	print(s.rev(lex_res));
	Calculator c;
	EXPECT_EQ(c.calculate(s.rev(lex_res)), -76.28);
}

TEST(parser, syntexep1)
{
	string str = "3 + ) 123 -10(/ 50 *	\t	30 \n";
	cout << str;
	Queue <Lexema> lex_res;
	LexAnalysis l;
	lex_res = l.lex(str);
	SyntaxAnalysis s;
	ASSERT_ANY_THROW(print(s.rev(lex_res)));
}
TEST(parser, syntexep2)
{
	string str = "3 + ( 123 - -10)/ 50 *	\t	30 \n";
	cout << str;
	Queue <Lexema> lex_res;
	LexAnalysis l;
	lex_res = l.lex(str);
	SyntaxAnalysis s;
	ASSERT_ANY_THROW(print(s.rev(lex_res)));
}
TEST(parser, syntexep3)
{
	string str = "3 + ( (123 -10)/ 50 *	\t	30 \n";
	cout << str;
	Queue <Lexema> lex_res;
	LexAnalysis l;
	lex_res = l.lex(str);
	SyntaxAnalysis s;
	ASSERT_ANY_THROW(print(s.rev(lex_res)));
}

TEST(parser, str_to_int)
{
	string str = "193";
	EXPECT_EQ(193, str_to_int(str));
}





