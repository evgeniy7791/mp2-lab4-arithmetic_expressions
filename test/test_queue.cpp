#include "stack.h"

#include <gtest.h>



TEST(Queue, can_create_queue) 
{
	ASSERT_NO_THROW(Queue<int> q);
}

TEST(Queue, can_push) 
{
	Queue<int> q;
	ASSERT_NO_THROW(q.Push(10));
}

TEST(Queue, can_pop_no_empty_queue) 
{
	Queue<int> q;
	q.Push(10);
	ASSERT_NO_THROW(q.Pop());
}

TEST(Queue, cant_pop_empty_queue) 
{
	Queue<int> q;
	ASSERT_ANY_THROW(q.Pop());
}

TEST(Queue, top_work_correctly_1)
{
	Queue<int> q;
	q.Push(20);
	q.Push(15);
	q.Push(30);
	EXPECT_EQ(20, q.Top());
}

TEST(Queue, top_work_correctly_2)
{
	Queue<int> q;
	q.Push(10);
	q.Pop();
	ASSERT_ANY_THROW(q.Pop());
}

TEST(Queue, top_work_correctly_3)
{
	Queue<int> q;
	q.Push(20);
	q.Push(15);
	q.Push(30);
	q.Pop();
	EXPECT_EQ(15, q.Top());
}

TEST(Queue, empty) 
{
	Queue<int> q;
	ASSERT_NO_THROW(q.IsEmpty());
}

TEST(Queue, IsEmpty_work_correctly_1) 
{
	Queue<int> q;
	EXPECT_EQ(1, q.IsEmpty());
}

TEST(Queue, empty_work_correctly_2) 
{
	Queue<int> q;
	q.Push(15);
	EXPECT_EQ(0, q.IsEmpty());
}

TEST(Queue, IsEmpty_work_correctly_3)
{
	Queue<int> q;
	q.Push(20);
	q.Pop();
	EXPECT_EQ(1, q.IsEmpty());
}

TEST(Queue, Get_size_work_correctly_1)
{
	Queue<int> q;
	q.Push(10);
	q.Push(20);
	q.Push(5);
	q.Push(8);
	q.Push(7);
	q.Pop();
	q.Push(90);
	EXPECT_EQ(5, q.Get_size());
}

TEST(Queue, Get_size_work_correctly_2)
{
	Stack<int> q;
	EXPECT_EQ(0, q.Get_size());
}

TEST(Queue, copy_queue_is_correctly)
{
	Queue<int> q1;
	q1.Push(2);
	q1.Push(1);
	Queue<int> q2(q1);
	EXPECT_EQ(q2.Top(), q1.Top());
	EXPECT_EQ(q1.Get_size(), q2.Get_size());

}

TEST(Queue, operator_copy_queue_is_correctly)
{
	Queue<int> q1, q2;
	q1.Push(2);
	q2 = q1;
	EXPECT_EQ(q2.Top(), q1.Top());
	EXPECT_EQ(q1.Get_size(), q2.Get_size());

}

TEST(Queue, operator_marka)
{
	Queue<int> q1;
	q1.Push(2);
	q1.Push(1);
	Queue<int> q2(q1);
	EXPECT_EQ(q2, q1);
	

}