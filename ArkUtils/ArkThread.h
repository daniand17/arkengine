#pragma once

#include <thread>

namespace ArkThreading
{
	class WorkerTask
	{
	public:
		virtual void init();
		virtual void run();
	};

	class ArkThread
	{
	public:
		ArkThread(WorkerTask * workerTask) : mWorkerTask(workerTask), mThread(&ArkThread::run, this) {}
		void run()
		{
			std::move(mWorkerTask);
			mWorkerTask->init();
			mWorkerTask->run();
		}

	private:
		std::thread mThread;
		WorkerTask * mWorkerTask;
	};
}

