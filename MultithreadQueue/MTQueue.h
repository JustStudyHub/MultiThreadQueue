#pragma once
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
		Elem* m_prevElem;
		T m_value;
	};
	size_t m_numOfElem;
	static const size_t m_maxElemNum = 100;
	Elem* m_frontElem;
	Elem* m_backElem;
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
	m_prevElem = nullptr;
}

template <typename T>
T MTQueue<T>::Pop()
{
	if (m_frontElem == nullptr)
	{
		return 0;
	}
	else
	{
		T res = m_frontElem->m_value;
		Elem* temp = m_frontElem->m_prevElem;
		delete m_frontElem;
		m_frontElem = temp;
		--m_numOfElem;
		return res;
	}
}

template <typename T>
void MTQueue<T>::Push(T elem)
{
	if (m_numOfElem == 0)
	{
		m_frontElem = new Elem();
		m_frontElem->m_value = elem;
		m_numOfElem = 1;
		return;
	}
	if (m_numOfElem == m_maxElemNum)
	{

	}

	Elem* tempPtr = m_frontElem;
	m_frontElem = new Elem();
	m_frontElem->m_prevElem = tempPtr;
	m_frontElem->m_value = elem;
	++m_numOfElem;
}