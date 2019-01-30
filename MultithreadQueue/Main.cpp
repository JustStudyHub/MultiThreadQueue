#include "pch.h"


int main()
{
	std::vector<std::thread> tVec;
	MTQueue<int> tQueue;
	size_t queueMaxSize = 10'000;
	size_t firstThread = queueMaxSize - 3'000;
	size_t secondThread = queueMaxSize - firstThread;
	size_t threadCount = 10;
	int resSum = 0;
	std::atomic<int> sum = 0;
	int checkSum = threadCount * (queueMaxSize / 20 * (queueMaxSize / 10 - 1));
	std::thread th1([&]()
	{
		for (int i = 0; i < firstThread; i++)
		{
			sum += tQueue.Pop();
		}
	});

	std::thread th2([&]()
	{
		for (int i = 0; i < secondThread; i++)
		{
			sum += tQueue.Pop();
		}
	});

	for (int i = 0; i < threadCount; i++)
	{
		tVec.push_back(std::thread([&]() {
			for (int j = 0; j < 1'000; ++j)
				tQueue.Push(j);
		}));
	}
	
	for (int i = 0; i < threadCount; i++)
	{
		tVec[i].join();
	}

	char flag = ' ';
	std::cout << "Press q to fin... \n";
	std::cin >> flag;

	if (flag == 'q')
	{
		th1.detach();
		th2.detach();
	}
	else
	{
		th1.join();
		th2.join();
	}
	
	resSum = sum;
	if (resSum == checkSum)
	{
		std::cout << "Sucsess!";
	}
	else
	{
		std::cout << "Fail!";
	}
	return 0;
}