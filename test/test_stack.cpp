#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_Stack) 
{
	ASSERT_NO_THROW(Stack<int> st);
}

TEST(Stack, can_push)
{
	Stack<int> st;
	ASSERT_NO_THROW(st.Push(10));
}

TEST(Stack, can_pop_no_empty_Stack)
{
	Stack<int> st;
	st.Push(10);
	ASSERT_NO_THROW(st.Pop());
}

TEST(Stack, cant_pop_empty_Stack) 
{
	Stack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}

TEST(Stack, top_work_correctly_1) 
{
	Stack<int> st;
	st.Push(10);
	st.Push(20);
	EXPECT_EQ(20, st.Top());
}

TEST(Stack, top_work_correctly_2) 
{
	Stack<int> st;
	st.Push(10);
	st.Pop();
	ASSERT_ANY_THROW(st.Pop());
}

TEST(Stack, empty) 
{
	Stack<int> st;
	ASSERT_NO_THROW(st.IsEmpty());
}

TEST(Stack, IsEmpty_work_correctly_1)
{
	Stack<int> st;
	EXPECT_EQ(1, st.IsEmpty());
}

TEST(Stack, IsEmpty_work_correctly_2)
{
	Stack<int> st;
	st.Push(10);
	st.Push(20);
	EXPECT_EQ(0, st.IsEmpty());
}

TEST(Stack, IsEmpty_work_correctly_3) {
	Stack<int> st;
	st.Push(10);
	st.Pop();
	EXPECT_EQ(1, st.IsEmpty());
}

TEST(Stack, Get_size_work_correctly_1) {
	Stack<int> st;
	st.Push(10);
	st.Push(20);
	st.Push(5);
	st.Push(8);
	st.Push(7);
	st.Pop();
	st.Push(90);
	EXPECT_EQ(5, st.Get_size());
}

TEST(Stack, Get_size_work_correctly_2) {
	Stack<int> st;
	EXPECT_EQ(0, st.Get_size());
}

TEST(Stack, copy_another_Stack_is_correctly) {
	Stack<int> st1;
	st1.Push(20);
	st1.Push(10);
	Stack<int> st2(st1);
	EXPECT_EQ(st2.Top(), st1.Top());
	EXPECT_EQ(st1.Get_size(), st2.Get_size());

}

TEST(Stack, operator_copy_another_Stack_is_correctly) {
	Stack<int> st1;
	Stack<int> st2;
	st1.Push(10);
	st1.Push(7);
	st1.Pop();
	st2 = st1;
	EXPECT_EQ(st2.Top(), st1.Top());
	EXPECT_EQ(st1.Get_size(), st2.Get_size());
}

