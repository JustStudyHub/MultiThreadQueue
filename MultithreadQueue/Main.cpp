
#include "pch.h"
#include <iostream>
#include "MTQueue.h"

int main()
{
	MTQueue<int> testQueue;
	for (int i = 0; i < 15; i++)
	{
		testQueue.Push(i);
	}
	for (int i = 0; i < 15; i++)
	{
		std::cout << testQueue.Pop() << std::endl;
	}
    std::cout << "Hello World!\n"; 
	return 0;
}