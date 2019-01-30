#include "pch.h"


int main()
{
	std::vector<std::thread> tVec;
	MTQueue<int> tQueue;
	size_t queueMaxSize = 10'000;
	size_t firstThread = queueMaxSize - 3'000;
	size_t secondThread = queueMaxSize - firstThread;
	int resSum = 0;
	std::atomic<int> sum = 0;
	int checkSum = queueMaxSize / 2 * (queueMaxSize - 1);
	std::thread th([&]()
	{
		for (int i = 0; i < firstThread; i++)
		{
			sum += tQueue.Pop();
		}
	});

	for (int i = 0; i < 10; i++)
	{
		tVec.push_back(std::thread([&]() {
			for (int j = 0; j < 1'000; ++j)
				tQueue.Push(j);
		}));
	}
	for (int i = 0; i < secondThread; i++)
	{
		sum += tQueue.Pop();
	}
	for (int i = 0; i < 10; i++)
	{
		tVec[i].join();
	}

	th.join();
	resSum = sum;
	return 0;
}