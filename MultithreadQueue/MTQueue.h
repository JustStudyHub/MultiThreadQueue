#pragma once
#include "pch.h"

template <typename T>
class MTQueue
{
public:
	MTQueue();
	~MTQueue();
	T Pop();
	void Push(T elem);
private:
	struct Elem
	{
		Elem();
		Elem* m_nextElem;
		T m_value;
	};
	bool Empty();
	size_t m_numOfElem;
	static const size_t m_maxElemNum = 100;
	Elem* m_frontElem;
	Elem* m_backElem;
	std::condition_variable m_condVar;
	//std::condition_variable m_condPop;
	std::mutex m_mutex;
	//std::mutex m_popMtx;
};

template <typename T>
MTQueue<T>::MTQueue()
{
	m_numOfElem = 0;
	m_frontElem = nullptr;
}

template <typename T>
MTQueue<T>::~MTQueue()
{
	while (m_frontElem != nullptr)
	{
		this->Pop();
	}
}

template <typename T>
MTQueue<T>::Elem::Elem()
{
	m_nextElem = nullptr;
}

template <typename T>
T MTQueue<T>::Pop()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	while (Empty())
	{
		m_condVar.wait(lock);
	}

	T res = m_frontElem->m_value;
	Elem* temp = m_frontElem->m_nextElem;
	delete m_frontElem;
	m_frontElem = temp;
	--m_numOfElem;
	m_condVar.notify_one();
	return res;
}

template <typename T>
void MTQueue<T>::Push(T elem)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_numOfElem == 0)
	{
		m_backElem = new Elem();		
		m_backElem->m_value = elem;
		m_frontElem = m_backElem;
		m_numOfElem = 1;
		m_condVar.notify_one();
		return;
	}

	while (m_numOfElem == m_maxElemNum)
	{
		m_condVar.wait(lock);
	}

	Elem* tempPtr = m_backElem;
	m_backElem = new Elem();
	m_backElem->m_value = elem;
	tempPtr->m_nextElem = m_backElem;
	++m_numOfElem;
	m_condVar.notify_one();
}

template <typename T>
bool MTQueue<T>::Empty()
{
	return (m_numOfElem == 0);
}