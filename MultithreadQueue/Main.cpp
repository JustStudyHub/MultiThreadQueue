#include "pch.h"


int main()
{
	std::vector<std::thread> tVec;
	MTQueue<int> testQueue;
	std::thread th([&]()
	{
		for (int i = 0; i < 100; i++)
		{
			std::cout << testQueue.Pop() << std::endl;
		}
	});
	
	for (int i = 0; i < 10; i++)
	{
		tVec.push_back(std::thread([&]() {
			for (int j = 0; j < 20; ++j)
			testQueue.Push(j);
		}));		
	}
	for (int i = 0; i < 100; i++)
	{
		std::cout << testQueue.Pop() << std::endl;
	}
	for (int i = 0; i < 10; i++)
	{
		tVec[i].join();
	}
	th.join();
	return 0;
}