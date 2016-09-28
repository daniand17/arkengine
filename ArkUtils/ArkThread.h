#pragma once

#include <thread>

namespace ArkThreading
{
	class WorkerTask
	{
	public:
		void initialize() { init(); }
		void runTask() { run(); }
	protected:
		virtual void init() = 0;
		virtual void run() = 0;
	};

	class ArkThread
	{
	public:
		ArkThread(WorkerTask * workerTask) : mWorkerTask(workerTask), mThread(&ArkThread::run, this) {}
		void join() { mThread.join(); }

	private:
		void run()
		{
			if ( mWorkerTask )
			{
				std::move(mWorkerTask);
				mWorkerTask->initialize();
				mWorkerTask->runTask();
			}
			
		}
		std::thread mThread;
		WorkerTask * mWorkerTask;
	};
}

