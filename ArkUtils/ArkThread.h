#pragma once

#include <thread>
#include <mutex>

#include "ArkString.h"

#define SCOPE_LOCKER ArkThreading::ScopeLock


namespace ArkThreading
{
	class WorkerTask
	{
	public:
		void initialize() { init(); }
		void runTask() { mIsRunning = true; run(); }
	protected:
		virtual void init() = 0;
		virtual void run() = 0;

	private:
		bool mIsRunning = false;
	};

	class ArkThread
	{
	public:
		ArkThread(WorkerTask * workerTask) : mWorkerTask(workerTask), mThread(NULL) {}
		void init() { mThread = new std::thread(&ArkThread::run, this); }
		void join() { mThread->join(); }
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
		std::thread * mThread;
		WorkerTask * mWorkerTask;
	};

	class ArkMutex : public std::mutex
	{
	};

	class ScopeLock
	{
	public:
		ScopeLock(ArkMutex * mutex, ArkString reason)
			: m_lock(mutex)
			, m_reason(reason)
		{
			m_lock->lock();
		}

		~ScopeLock()
		{
			m_lock->unlock();
		}
	private:
		ArkMutex * m_lock;
		ArkString m_reason;
	};
}

