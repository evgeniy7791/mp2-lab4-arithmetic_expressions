


#include <iostream>

template<typename T>

class Stack
{
	T* pMem;
	size_t size;
	size_t capacity;

	void Resize()
	{
		capacity = (size + 1) * 2;
		T* tmpMem = new T[capacity];
		std::copy(pMem, pMem + size, tmpMem);
		delete[] pMem;
		pMem = tmpMem;
	}

public:
	Stack()
	{
		size = 0;
		capacity = 1;
		pMem = new T[capacity];
	}

	Stack(const Stack& st)
	{
		size = st.size;
		capacity = st.capacity;
		pMem = new T[st.capacity];
		for (size_t i = 0; i < size; i++) {
			pMem[i] = st.pMem[i];
		}
	}

	~Stack()
	{
		delete[] pMem;
	}

	Stack& operator=(const Stack st)
	{
		delete[] pMem;
		size = st.size;
		capacity = st.capacity;
		pMem = new T[st.capacity];
		for (size_t i = 0; i < size; i++) {
			pMem[i] = st.pMem[i];
		}
		return *this;
	}



	T Top()
	{
		if (size <= 0) throw "Stack is empty";
		return pMem[size - 1];
	}

	void Push(T elem)
	{
		if (size == capacity - 1) Resize();
		pMem[size++] = elem;

	}

	T Pop()
	{
		if (size <= 0) throw "Stack is empty";
		return pMem[--size];
	}

	bool IsEmpty()
	{
		return size <= 0;
	}

	size_t Get_size()
	{
		return size;
	}
};


template <typename T>
class Queue {
	T* pMem;
	size_t size;
	size_t capacity;
	size_t head;
	size_t tail;

	void Resize()
	{
		T* tmpMem = new T[(size + 1) * 2];
		if (tail > head) {
			std::copy(pMem + head, pMem + tail, tmpMem);
		}
		else {
			std::copy(pMem + head, pMem + capacity, tmpMem);
			std::copy(pMem, pMem + tail, tmpMem + (capacity - head));
		}
		delete[] pMem;
		head = 0;
		tail = capacity;
		capacity = (size + 1) * 2;
		pMem = tmpMem;
	}

public:
	Queue()
	{
		size = 0;
		capacity = 1;
		pMem = new T[capacity];
		head = 0;
		tail = 0;
	}

	Queue(const Queue& q)
	{
		size = q.size;
		capacity = q.capacity;
		head = q.head;
		tail = q.tail;
		pMem = new T[q.capacity];
		for (size_t i = 0; i < capacity; i++) {
			this->pMem[i] = q.pMem[i];
		}
	}

	~Queue()
	{
		delete[] pMem;
	}

	Queue operator=(const Queue& q)
	{
		delete[] pMem;
		size = q.size;
		capacity = q.capacity;
		head = q.head;
		tail = q.tail;
		pMem = new T[q.capacity];
		for (size_t i = 0; i < capacity; i++) {
			this->pMem[i] = q.pMem[i];
		}
		return*this;
	}

	bool operator==(const Queue& q) const
	{
		if (size != q.size)
			return 0;
		for (size_t i = head; i != (tail + 1) % capacity; i = (i + 1) % capacity)
			if (pMem[i] != q.pMem[i])
				return 0;
		return 1;
	}


	void Push(T elem)
	{
		if (tail == head && size != 0)
			Resize();
		pMem[tail] = elem;
		tail = (tail + 1) % capacity;
		size++;
	}

	T Pop()
	{
		if (size <= 0) throw "Queue is empty";
		T tmp = pMem[head];
		head = (head + 1) % capacity;
		size--;
		return tmp;

		
	}

	T Top()
	{
		if (size <= 0) throw "Queue is empty";
		return pMem[head];
	}

	bool IsEmpty() const
	{
		return size <= 0;
	}



	size_t Get_size() const
	{
		return size;
	}
};
