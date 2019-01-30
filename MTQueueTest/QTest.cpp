#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MTQueueTest
{		
	TEST_CLASS(TestPush)
	{
	public:		

		TEST_METHOD(PushInOneThread)
		{
			MTQueue<int> tQueue1;
			size_t queueMaxSize = 10'000; //real Queue Max Size
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue1.Push(i);
			}
			Assert::AreEqual(tQueue1.Size(), queueMaxSize);

			MTQueue<int> tQueue2;
			queueMaxSize -= 500;
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue2.Push(i);
			}
			Assert::AreEqual(tQueue2.Size(), queueMaxSize);
		}

		TEST_METHOD(PushInTwoThread)
		{
			MTQueue<int> tQueue1;
			size_t queueMaxSize = 10'000;  //real Queue Max Size
			size_t firstThread = queueMaxSize - 30;
			size_t secondThread = queueMaxSize - firstThread;
			std::thread th1([&]() {
				for (int i = 0; i < firstThread; ++i)
				{
					tQueue1.Push(i);
				}
			});
			for (int i = 0; i < secondThread; ++i)
			{
				tQueue1.Push(i);
			}
			th1.join();
			Assert::AreEqual(tQueue1.Size(), queueMaxSize);

			MTQueue<int> tQueue2;
			queueMaxSize = 7'000;
			firstThread = queueMaxSize - 300;
			secondThread = queueMaxSize - firstThread;
			std::thread th2([&]() {
				for (int i = 0; i < firstThread; ++i)
				{
					tQueue2.Push(i);
				}
			});
			for (int i = 0; i < secondThread; ++i)
			{
				tQueue2.Push(i);
			}
			th2.join();
			Assert::AreEqual(tQueue2.Size(), queueMaxSize);
		}
	};

	TEST_CLASS(TestPop)
	{
	public:

		TEST_METHOD(PopInOneThread)
		{
			MTQueue<int> tQueue1;
			size_t queueMaxSize = 10'000; //real Queue Max Size
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue1.Push(i);
			}
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue1.Pop();
			}
			Assert::AreEqual(tQueue1.Size(), (size_t)0);

			MTQueue<int> tQueue2;
			queueMaxSize -= 500;
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue2.Push(i);
			}
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue2.Pop();
			}
			Assert::AreEqual(tQueue2.Size(), (size_t)0);

			queueMaxSize = 10'000;
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue2.Push(i);
			}
			for (int i = 0; i < queueMaxSize - 3333; ++i)
			{
				tQueue2.Pop();
			}
			Assert::AreEqual(tQueue2.Size(), (size_t)3333);
		}

		TEST_METHOD(PopInTwoThreadZero)
		{
			MTQueue<int> tQueue1;
			size_t queueMaxSize = 10000;  //real Queue Max Size
			size_t firstThread = queueMaxSize - 3'760;
			size_t secondThread = queueMaxSize - firstThread;
			std::thread th1([&]() {
				for (int i = 0; i < firstThread; ++i)
				{
					tQueue1.Pop();
				}
			});
			std::thread th2([&]() {
				for (int i = 0; i < secondThread; ++i)
				{
					tQueue1.Pop();
				}
			});
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue1.Push(i);
			}
			th1.join();
			th2.join();
			Assert::AreEqual(tQueue1.Size(), (size_t)0);
		}
		TEST_METHOD(PopInTwoThread)
		{
			MTQueue<int> tQueue1;
			size_t queueMaxSize = 10000;  //real Queue Max Size
			size_t firstThread = queueMaxSize - 3'760;
			size_t secondThread = queueMaxSize - firstThread - 2'100;
			size_t resSize = queueMaxSize - firstThread - secondThread;
			std::thread th1([&]() {
				for (int i = 0; i < firstThread; ++i)
				{
					tQueue1.Pop();
				}
			});
			std::thread th2([&]() {
				for (int i = 0; i < secondThread; ++i)
				{
					tQueue1.Pop();
				}
			});
			for (int i = 0; i < queueMaxSize; ++i)
			{
				tQueue1.Push(i);
			}
			th1.join();
			th2.join();
			Assert::AreEqual(tQueue1.Size(), resSize);
		}
	};

	TEST_CLASS(TestPopPush)
	{
	public:

		TEST_METHOD(MultipleThread)
		{
			std::vector<std::thread> tVec;
			MTQueue<int> tQueue;
			size_t queueMaxSize = 10'000;
			size_t firstThread = queueMaxSize - 3'000;
			size_t secondThread = queueMaxSize - firstThread;
			std::thread th([&]()
			{
				for (int i = 0; i < firstThread; i++)
				{
					std::cout << tQueue.Pop() << std::endl;
				}
			});

			for (int i = 0; i < 10; i++)
			{
				tVec.push_back(std::thread([&]() {
					for (int j = 0; j < 1000; ++j)
						tQueue.Push(j);
				}));
			}
			for (int i = 0; i < secondThread; i++)
			{
				std::cout << tQueue.Pop() << std::endl;
			}
			for (int i = 0; i < 10; i++)
			{
				tVec[i].join();
			}
			
			th.join();
			Assert::AreEqual(tQueue.Size(), (size_t)0);
		}
	};
}